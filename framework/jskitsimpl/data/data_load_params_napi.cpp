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
    napi_value jsLoadHandler = nullptr;
    NAPI_CALL_BASE(env, napi_get_named_property(env, in, "loadHandler", &jsLoadHandler), false);
    dataLoadParams.dataLoadInfo.sequenceKey = UTILS::GenerateId();
    tsfns_.Compute(dataLoadParams.dataLoadInfo.sequenceKey, [&](const std::string &k, napi_threadsafe_function &tsfn) {
        if (tsfn != nullptr) {
            LOG_WARN(UDMF_KITS_NAPI, "Listener has existed!");
            napi_release_threadsafe_function(tsfn, napi_tsfn_release);
            tsfn = nullptr;
        }
        napi_value workName;
        napi_create_string_utf8(env, "threadsafe_function", NAPI_AUTO_LENGTH, &workName);
        auto status = napi_create_threadsafe_function(env, jsLoadHandler, nullptr, workName, 0, 1, nullptr,
            nullptr, nullptr, CallDataLoadHandler, &tsfn);
        if (status != napi_ok) {
            LOG_ERROR(UDMF_KITS_NAPI, "napi_create_threadsafe_function failed, status=%{public}d", status);
            return false;
        }
        return true;
    });
    dataLoadParams.loadHandler = [](const std::string &udKey, const DataLoadInfo &dataLoadInfo) {
        LOG_INFO(UDMF_KITS_NAPI, "Load handler Start.");
        auto seqKey = UTILS::GetSequenceKey(udKey);
        if (seqKey.empty()) {
            LOG_ERROR(UDMF_KITS_NAPI, "Error udKey:%{public}s", udKey.c_str());
            return;
        }
        bool tsfnExist = tsfns_.ComputeIfPresent(seqKey, [&](const std::string &key, napi_threadsafe_function &tsfn) {
            DataLoadArgs *infoArgs = new (std::nothrow) DataLoadArgs;
            if (infoArgs == nullptr) {
                LOG_ERROR(UDMF_KITS_NAPI, "No space for dataLoadArgs, udKey=%{public}s", udKey.c_str());
                return false;
            }
            infoArgs->udKey = udKey;
            infoArgs->dataLoadInfo = dataLoadInfo;
            auto status = napi_call_threadsafe_function(tsfn, infoArgs, napi_tsfn_blocking);
            if (status != napi_ok) {
                LOG_ERROR(UDMF_KITS_NAPI, "call func failed,status=%{public}d,udKey=%{public}s", status, udKey.c_str());
            }
            napi_release_threadsafe_function(tsfn, napi_tsfn_release);
            return false;
        });
        if (!tsfnExist) { LOG_ERROR(UDMF_KITS_NAPI, "Tsfn not exist, udKey=%{public}s", udKey.c_str()); }
    };
    return true;
}

void DataLoadParamsNapi::CallDataLoadHandler(napi_env env, napi_value callback, void *context, void *data)
{
    DataLoadArgs* infoArgs = static_cast<DataLoadArgs*>(data);
    std::string udKey = infoArgs->udKey;
    napi_value param;
    auto status = NapiDataUtils::SetValue(env, infoArgs->dataLoadInfo, param);
    delete infoArgs;
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
    LOG_INFO(UDMF_KITS_NAPI, "Call napi_call_function end.");
    napi_valuetype type = napi_undefined;
    napi_typeof(env, result, &type);
    if (type == napi_null) {
        LOG_ERROR(UDMF_KITS_NAPI, "DataLoad has no data");
        return;
    }
    UnifiedDataNapi *unifiedDataNapi = nullptr;
    status = napi_unwrap(env, result, reinterpret_cast<void **>(&unifiedDataNapi));
    if (status != napi_ok || unifiedDataNapi == nullptr) {
        LOG_ERROR(UDMF_KITS_NAPI, "napi_unwrap data failed, status=%{public}d", status);
        return;
    }

    auto ret = UdmfClient::GetInstance().PushDelayData(udKey, *unifiedDataNapi->value_);
    if (ret != E_OK) {
        LOG_ERROR(UDMF_KITS_NAPI, "SetData failed, status=%{public}d", ret);
    }
}
} // namespace UDMF
} // namespace OHOS