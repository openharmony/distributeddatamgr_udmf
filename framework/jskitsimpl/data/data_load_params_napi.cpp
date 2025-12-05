/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#define LOG_TAG "DataLoadParamsNapi"
#include "data_load_params_napi.h"

#include "logger.h"
#include "napi_data_utils.h"
#include "unified_data_napi.h"
#include "udmf_client.h"
#include "udmf_utils.h"

namespace OHOS {
namespace UDMF {
ConcurrentMap<std::string, napi_threadsafe_function> DataLoadParamsNapi::tsfns_;

bool DataLoadParamsNapi::Convert2NativeValue(napi_env env, napi_value in, DataLoadParams &dataLoadParams)
{
    napi_value jsDataLoadInfo = nullptr;
    NAPI_CALL_BASE(env, napi_get_named_property(env, in, "dataLoadInfo", &jsDataLoadInfo), false);
    NAPI_CALL_BASE(env, NapiDataUtils::GetValue(env, jsDataLoadInfo, dataLoadParams.dataLoadInfo), false);
    napi_value loadHandler = nullptr;
    NAPI_CALL_BASE(env, napi_get_named_property(env, in, "delayedDataLoadHandler", &loadHandler), false);
    napi_valuetype handlerType = napi_undefined;
    NAPI_CALL_BASE(env, napi_typeof(env, loadHandler, &handlerType), false);
    if (handlerType == napi_null || handlerType == napi_undefined) {
        LOG_INFO(UDMF_KITS_NAPI, "Aync data load handler is empty!");
        NAPI_CALL_BASE(env, napi_get_named_property(env, in, "loadHandler", &loadHandler), false);
    }
    if (handlerType == napi_null || handlerType == napi_undefined) {
        LOG_INFO(UDMF_KITS_NAPI, "Data load handler is empty!");
        return false;
    }
    dataLoadParams.dataLoadInfo.sequenceKey = UTILS::GenerateId();
    tsfns_.Compute(dataLoadParams.dataLoadInfo.sequenceKey, [&](const std::string &k, napi_threadsafe_function &tsfn) {
        if (tsfn != nullptr) {
            LOG_WARN(UDMF_KITS_NAPI, "Listener has existed!");
            napi_release_threadsafe_function(tsfn, napi_tsfn_release);
            tsfn = nullptr;
        }
        napi_value workName;
        napi_create_string_utf8(env, "threadsafe_function", NAPI_AUTO_LENGTH, &workName);
        auto status = napi_create_threadsafe_function(env, loadHandler, nullptr, workName, 0, 1, nullptr,
            nullptr, nullptr, CallDataLoadHandler, &tsfn);
        if (status != napi_ok) {
            LOG_ERROR(UDMF_KITS_NAPI, "napi_create_threadsafe_function failed, status=%{public}d", status);
            return false;
        }
        return true;
    });
    AssignDataLoadParams(dataLoadParams);
    return true;
}

void DataLoadParamsNapi::CallDataLoadHandler(napi_env env, napi_value callback, void *context, void *data)
{
    std::unique_ptr<DataLoadArgs> infoArgs(static_cast<DataLoadArgs*>(data));
    napi_value param;
    auto status = NapiDataUtils::SetValue(env, infoArgs->dataLoadInfo, param);
    if (status != napi_ok) {
        LOG_ERROR(UDMF_KITS_NAPI, "SetValue dataLoadInfo failed, status=%{public}d", status);
        return;
    }
    napi_value result = nullptr;
    status = napi_call_function(env, nullptr, callback, 1, &param, &result);
    if (status != napi_ok || result == nullptr) {
        LOG_ERROR(UDMF_KITS_NAPI, "napi_call_function failed, status=%{public}d", status);
        return;
    }
    bool isPromise = false;
    napi_is_promise(env, result, &isPromise);
    if (!isPromise) {
        LOG_INFO(UDMF_KITS_NAPI, "Not promise");
        HandleUnifiedData(env, infoArgs->udKey, result);
        return;
    }
    HandlePromise(env, result, std::move(infoArgs));
}

napi_status DataLoadParamsNapi::HandlePromise(napi_env env, napi_value promise, std::unique_ptr<DataLoadArgs> data)
{
    napi_value thenName;
    auto status = napi_create_string_utf8(env, "then", NAPI_AUTO_LENGTH, &thenName);
    if (status != napi_ok) {
        LOG_ERROR(UDMF_KITS_NAPI, "napi_create_string_utf8 failed, status=%{public}d", status);
        return status;
    }
    napi_value thenFunc;
    status = napi_get_property(env, promise, thenName, &thenFunc);
    if (status != napi_ok) {
        LOG_ERROR(UDMF_KITS_NAPI, "napi_get_property failed, status=%{public}d", status);
        return status;
    }
    napi_value thenHandler;
    DataLoadArgs *args = data.release();
    napi_create_function(env, "asyncThen", NAPI_AUTO_LENGTH, PromiseThenHandler, args, &thenHandler);
    if (status != napi_ok) {
        LOG_ERROR(UDMF_KITS_NAPI, "napi_create_function asyncThen failed, status=%{public}d", status);
        delete args;
        return status;
    }
    napi_value catchHandler;
    napi_create_function(env, "asyncCatch", NAPI_AUTO_LENGTH, PromiseCatchHandler, args, &catchHandler);
    if (status != napi_ok) {
        LOG_ERROR(UDMF_KITS_NAPI, "napi_create_function asyncCatch failed, status=%{public}d", status);
        delete args;
        return status;
    }
    size_t argsSize = 2;
    napi_value thenArgs[2] = { thenHandler, catchHandler };
    status = napi_call_function(env, promise, thenFunc, argsSize, thenArgs, NULL);
    if (status != napi_ok) {
        LOG_ERROR(UDMF_KITS_NAPI, "Call then failed, status=%{public}d", status);
        delete args;
        return status;
    }
    return napi_ok;
}

napi_value DataLoadParamsNapi::PromiseThenHandler(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value args[1];
    std::unique_ptr<DataLoadArgs> infoArgs;
    auto status = napi_get_cb_info(env, info, &argc, args, NULL, (void **)&infoArgs);
    if (status != napi_ok || !infoArgs) {
        LOG_ERROR(UDMF_KITS_NAPI, "napi_get_cb_info failed, status=%{public}d", status);
        return NULL;
    }
    std::string udKey = infoArgs->udKey;
    auto ret = HandleUnifiedData(env, udKey, args[0]);
    napi_value promiseRet;
    NapiDataUtils::SetValue(env, ret, promiseRet);
    return promiseRet;
}

napi_value DataLoadParamsNapi::PromiseCatchHandler(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value args[1];
    std::unique_ptr<DataLoadArgs> infoArgs;
    auto status = napi_get_cb_info(env, info, &argc, args, NULL, (void **)&infoArgs);
    if (status != napi_ok) {
        LOG_ERROR(UDMF_KITS_NAPI, "napi_get_cb_info failed, status=%{public}d", status);
    }
    return NULL;
}

int32_t DataLoadParamsNapi::HandleUnifiedData(napi_env env, std::string udKey, napi_value data)
{
    napi_valuetype type = napi_undefined;
    napi_typeof(env, data, &type);
    if (type == napi_null) {
        LOG_ERROR(UDMF_KITS_NAPI, "DataLoad has no data");
        return E_INVALID_PARAMETERS;
    }
    UnifiedDataNapi *unifiedDataNapi = nullptr;
    auto status = napi_unwrap(env, data, reinterpret_cast<void **>(&unifiedDataNapi));
    if (status != napi_ok || unifiedDataNapi == nullptr) {
        LOG_ERROR(UDMF_KITS_NAPI, "napi_unwrap data failed, status=%{public}d", status);
        return E_ERROR;
    }
    auto ret = UdmfClient::GetInstance().PushDelayData(udKey, *unifiedDataNapi->value_);
    if (ret != E_OK) {
        LOG_ERROR(UDMF_KITS_NAPI, "SetData failed, status=%{public}d", ret);
    }
    return ret;
}

void DataLoadParamsNapi::AssignDataLoadParams(DataLoadParams &dataLoadParams)
{
    dataLoadParams.loadHandler = [](const std::string &udKey, const DataLoadInfo &dataLoadInfo) {
        LOG_INFO(UDMF_KITS_NAPI, "Load handler Start.");
        auto seqKey = UTILS::GetSequenceKey(udKey);
        if (seqKey.empty()) {
            LOG_ERROR(UDMF_KITS_NAPI, "Error udKey:%{public}s", udKey.c_str());
            return;
        }
        bool tsfnExist = tsfns_.ComputeIfPresent(seqKey, [&](const std::string &key, napi_threadsafe_function &tsfn) {
            auto infoArgs = std::make_unique<DataLoadArgs>();
            if (infoArgs == nullptr) {
                LOG_ERROR(UDMF_KITS_NAPI, "No space for dataLoadArgs, udKey=%{public}s", udKey.c_str());
                return false;
            }
            infoArgs->udKey = udKey;
            infoArgs->dataLoadInfo = dataLoadInfo;
            DataLoadArgs *data = infoArgs.release();
            auto status = napi_call_threadsafe_function(tsfn, data, napi_tsfn_blocking);
            if (status != napi_ok) {
                LOG_ERROR(UDMF_KITS_NAPI, "call func failed,status=%{public}d,udKey=%{public}s", status, udKey.c_str());
                delete data;
            }
            napi_release_threadsafe_function(tsfn, napi_tsfn_release);
            return false;
        });
        if (!tsfnExist) { LOG_ERROR(UDMF_KITS_NAPI, "Tsfn not exist, udKey=%{public}s", udKey.c_str()); }
    };
}
} // namespace UDMF
} // namespace OHOS