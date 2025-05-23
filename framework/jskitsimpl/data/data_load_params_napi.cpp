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
    LOG_DEBUG(UDMF_KITS_NAPI, "zzz Start.");
    napi_value jsDataLoadInfo = nullptr;
    NAPI_CALL_BASE(env, napi_get_named_property(env, in, "dataLoadInfo", &jsDataLoadInfo), false);
    NAPI_CALL_BASE(env, NapiDataUtils::GetValue(env, jsDataLoadInfo, dataLoadParams.dataLoadInfo), false);
    napi_value jsLoadHandler = nullptr;
    NAPI_CALL_BASE(env, napi_get_named_property(env, in, "loadHandler", &jsLoadHandler), false);

    dataLoadParams.dataLoadInfo.udKey = UTILS::GenerateId();
    tsfns_.Compute(dataLoadParams.dataLoadInfo.udKey, [&](const std::string &key, napi_threadsafe_function &tsfn) {
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
        LOG_INFO(UDMF_KITS_NAPI, "zzz Load handler Start.");
        auto handlerKey = UTILS::GetHandlerKey(udKey);
        if (handlerKey.empty()) {
            LOG_ERROR(UDMF_KITS_NAPI, "Error udKey:%{public}s", udKey.c_str());
            return;
        }
        bool tsfnExist = tsfns_.ComputeIfPresent(handlerKey, [&](const std::string &key, napi_threadsafe_function &tsfn){
            DataLoadArgs *infoArgs = new (std::nothrow) DataLoadArgs;
            if (infoArgs == nullptr) {
                LOG_ERROR(UDMF_KITS_NAPI, "No space for dataLoadArgs, udKey=%{public}s", udKey.c_str());
                return false;
            }
            infoArgs->udKey = udKey;
            infoArgs->dataLoadInfo = dataLoadInfo;
            auto status = napi_call_threadsafe_function(tsfn, infoArgs, napi_tsfn_blocking);
            if (status != napi_ok) {
                LOG_ERROR(UDMF_KITS_NAPI, "napi_call_threadsafe_function failed, status=%{public}d, udKey=%{public}s", status, udKey.c_str());
            }
            return false;
        });
        if (!tsfnExist) {
            LOG_ERROR(UDMF_KITS_NAPI, "Tsfn not exist, udKey=%{public}s", udKey.c_str());
        }
    };
    return true;
}

void DataLoadParamsNapi::CallDataLoadHandler(napi_env env, napi_value callback, void *context, void *data)
{
    DataLoadArgs* infoArgs = static_cast<DataLoadArgs*>(data);
    std::string udKey = infoArgs->udKey;
    napi_value param;
    LOG_ERROR(UDMF_KITS_NAPI, "zzz 85");
    auto status = NapiDataUtils::SetValue(env, infoArgs->dataLoadInfo, param);
    LOG_ERROR(UDMF_KITS_NAPI, "zzz 92");
    delete infoArgs;
    if (status != napi_ok) {
        LOG_ERROR(UDMF_KITS_NAPI, "SetValue dataLoadInfo failed, status=%{public}d", status);
        return;
    }
    LOG_ERROR(UDMF_KITS_NAPI, "zzz 87");

    napi_value result = nullptr;
    status = napi_call_function(env, nullptr, callback, 1, &param, &result);
    LOG_ERROR(UDMF_KITS_NAPI, "zzz 102");
    if (status != napi_ok || result == nullptr) {
        LOG_ERROR(UDMF_KITS_NAPI, "napi_call_function failed, status=%{public}d", status);
        return;
    }
    LOG_ERROR(UDMF_KITS_NAPI, "zzz 107");
    napi_valuetype type = napi_undefined;
    napi_typeof(env, result, &type);
    LOG_ERROR(UDMF_KITS_NAPI, "zzz 110");
    if (type == napi_null) {
        LOG_ERROR(UDMF_KITS_NAPI, "DataLoad has no data");
        return;
    }
    UnifiedDataNapi *unifiedDataNapi = nullptr;
    napi_unwrap(env, result, reinterpret_cast<void **>(&unifiedDataNapi));

    auto ret = UdmfClient::GetInstance().SetDelayData(udKey, *unifiedDataNapi->value_);
    if (ret != E_OK) {
        LOG_ERROR(UDMF_KITS_NAPI, "SetData failed, status=%{public}d", ret);
    }
}
} // namespace UDMF
} // namespace OHOS