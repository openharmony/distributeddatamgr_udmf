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

#define LOG_TAG "GetDataParamsNapi"
#include "get_data_params_napi.h"

#include "logger.h"
#include "napi_data_utils.h"
#include "unified_data_napi.h"

namespace OHOS {
namespace UDMF {
static constexpr int32_t PROGRESS_INIT = 0;
static constexpr int32_t PROGRESS_ALL_FINISHED = 100;
ConcurrentMap<std::string, napi_threadsafe_function> GetDataParamsNapi::tsfns;

bool GetDataParamsNapi::Convert2NativeValue(napi_env env, napi_value in,
    GetDataParams &getDataParams, const std::string &key)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "Start.");

    napi_value jsProgressIndicator = nullptr;
    NAPI_CALL_BASE(env, napi_get_named_property(env, in, "progressIndicator", &jsProgressIndicator), false);
    int32_t progressIndicator = static_cast<int32_t>(ProgressIndicator::NONE);
    NAPI_CALL_BASE(env, NapiDataUtils::GetValue(env, jsProgressIndicator, progressIndicator), false);
    getDataParams.progressIndicator = static_cast<ProgressIndicator>(progressIndicator);

    napi_value JsListener = nullptr;
    NAPI_CALL_BASE(env, napi_get_named_property(env, in, "dataProgressListener", &JsListener), false);
    napi_valuetype valueType = napi_undefined;
    NAPI_CALL_BASE(env, napi_typeof(env, JsListener, &valueType), false);
    NAPI_ASSERT_BASE(env, valueType == napi_function, "progressListener type must be DataProgressListener", false);
    if (!SetProgressListener(env, getDataParams, JsListener, key)) {
        LOG_ERROR(UDMF_KITS_NAPI, "SetProgressListener failed.");
        return false;
    }
    
    bool hasDestUri = false;
    NAPI_CALL_BASE(env, napi_has_named_property(env, in, "destUri", &hasDestUri), false);
    if (hasDestUri) {
        napi_value jsDestUri = nullptr;
        NAPI_CALL_BASE(env, napi_get_named_property(env, in, "destUri", &jsDestUri), false);
        NAPI_CALL_BASE(env, NapiDataUtils::GetValue(env, jsDestUri, getDataParams.destUri), false);
    }

    bool hasFileConflictOptions = false;
    NAPI_CALL_BASE(env, napi_has_named_property(env, in, "fileConflictOptions", &hasFileConflictOptions), false);
    if (hasFileConflictOptions) {
        napi_value jsFileConflictOptions = nullptr;
        NAPI_CALL_BASE(env, napi_get_named_property(env, in, "fileConflictOptions", &jsFileConflictOptions), false);
        int32_t fileConflictOptions = static_cast<int32_t>(FileConflictOptions::OVERWRITE);
        NAPI_CALL_BASE(env, NapiDataUtils::GetValue(env, jsFileConflictOptions, fileConflictOptions), false);
        getDataParams.fileConflictOptions = static_cast<FileConflictOptions>(fileConflictOptions);
    }

    return true;
}

bool GetDataParamsNapi::SetProgressListener(napi_env env, GetDataParams &getDataParams,
    napi_value callback, const std::string &key)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "Start.");
    tsfns.Compute(key, [&](const std::string &key, napi_threadsafe_function &tsfn) {
        if (tsfn != nullptr) {
            LOG_WARN(UDMF_KITS_NAPI, "Listener has existed!");
            napi_release_threadsafe_function(tsfn, napi_tsfn_release);
            tsfn = nullptr;
        }
        napi_value workName;
        napi_create_string_utf8(env, "threadsafe_function", NAPI_AUTO_LENGTH, &workName);
        auto status = napi_create_threadsafe_function(env, callback, nullptr, workName, 0, 1, nullptr,
            nullptr, nullptr, CallProgressListener, &tsfn);
        if (status != napi_ok) {
            LOG_ERROR(UDMF_KITS_NAPI, "napi_create_threadsafe_function failed, status=%{public}d", status);
            return false;
        }
        return true;
    });

    getDataParams.progressListener = [key](ProgressInfo progressInfo, std::shared_ptr<UnifiedData> data) {
        bool listenerExist = tsfns.ComputeIfPresent(key, [&](const std::string &key, napi_threadsafe_function &tsfn) {
            auto listenerArgs = CreateListenerArgs(progressInfo, data);
            if (listenerArgs == nullptr) {
                return false;
            }
            auto status = napi_call_threadsafe_function(tsfn, listenerArgs, napi_tsfn_blocking);
            if (status != napi_ok) {
                LOG_ERROR(UDMF_KITS_NAPI, "napi_call_threadsafe_function failed, status=%{public}d", status);
                return false;
            }
            if (progressInfo.progress >= PROGRESS_ALL_FINISHED ||
                progressInfo.progress < PROGRESS_INIT) {
                napi_release_threadsafe_function(tsfn, napi_tsfn_release);
                return false;
            }
            return true;
        });
        if (!listenerExist) {
            LOG_INFO(UDMF_KITS_NAPI, "No listener exist.");
        }
    };
    return true;
}

void GetDataParamsNapi::CallProgressListener(napi_env env, napi_value callback, void *context, void *data)
{
    ListenerArgs* listenerArgs = static_cast<ListenerArgs*>(data);
    napi_value param[ListenerArgs::ARGV_SIZE];

    NapiDataUtils::SetValue(env, listenerArgs->progressInfo, param[0]);

    if (listenerArgs->unifiedData == nullptr) {
        NapiDataUtils::SetValue(env, nullptr, param[1]);
    } else {
        std::shared_ptr<UnifiedData> unifiedData = std::make_shared<UnifiedData>();
        unifiedData->SetRecords(listenerArgs->unifiedData->GetRecords());
        UnifiedDataNapi::NewInstance(env, unifiedData, param[1]);
    }

    auto status = napi_call_function(env, nullptr, callback, ListenerArgs::ARGV_SIZE, param, nullptr);
    if (status != napi_ok) {
        LOG_ERROR(UDMF_KITS_NAPI, "napi_call_function failed, status=%{public}d", status);
    }

    DeleteListenerArgs(listenerArgs);
}

GetDataParamsNapi::ListenerArgs* GetDataParamsNapi::CreateListenerArgs(
    ProgressInfo progressInfo, std::shared_ptr<UnifiedData> data)
{
    auto listenerArgs = new (std::nothrow) ListenerArgs;
    if (listenerArgs == nullptr) {
        LOG_ERROR(UDMF_KITS_NAPI, "No memory for listenerArgs malloc");
        return nullptr;
    }
    listenerArgs->progressInfo = progressInfo;
    listenerArgs->unifiedData = nullptr;
    if (data != nullptr) {
        listenerArgs->unifiedData = new (std::nothrow) UnifiedData;
        if (listenerArgs->unifiedData == nullptr) {
            LOG_ERROR(UDMF_KITS_NAPI, "No memory for unifiedData malloc");
            delete listenerArgs;
            return nullptr;
        }
        listenerArgs->unifiedData->SetRecords(data->GetRecords());
    }
    return listenerArgs;
}

void GetDataParamsNapi::DeleteListenerArgs(ListenerArgs *listenerArgs)
{
    if (listenerArgs->unifiedData != nullptr) {
        delete listenerArgs->unifiedData;
        listenerArgs->unifiedData = nullptr;
    }
    delete listenerArgs;
    listenerArgs = nullptr;
}

} // namespace UDMF
} // namespace OHOS