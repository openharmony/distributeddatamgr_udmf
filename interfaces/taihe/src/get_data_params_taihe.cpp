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
#define LOG_TAG "GetDataParamsTaihe"
#include "get_data_params_taihe.h"
#include "udmf_ani_converter_utils.h"
#include "logger.h"
namespace OHOS {
namespace UDMF {
static constexpr int32_t PROGRESS_INIT = 0;
static constexpr int32_t PROGRESS_ALL_FINISHED = 100;
ConcurrentMap<std::string, ani_fn_object> GetDataParamsTaihe::anifns;
bool GetDataParamsTaihe::Convert2NativeValue(ani_env *env, ani_object in, GetDataParams &getDataParams, const std::string &key)
{
    ani_ref progressIndicator;
    auto status = env->Object_GetFieldByName_Ref(in, "progressIndicator", &progressIndicator);
    if (status != ANI_OK) {
        LOG_ERROR(UDMF_ANI, "Object_GetFieldByName_Ref failed.");
        return false;
    }
    ani_int progressIndicatorValue;
    status = env->EnumItem_GetValue_Int(static_cast<ani_enum_item>(progressIndicator), &progressIndicatorValue);
    if (status != ANI_OK) {
        LOG_ERROR(UDMF_ANI, "EnumItem_GetValue_Int failed.");
        return false;
    }
    getDataParams.progressIndicator = static_cast<ProgressIndicator>(progressIndicatorValue);
    ani_ref dataProgressListener;
    status = env->Object_GetFieldByName_Ref(in, "dataProgressListener", &dataProgressListener);
    if (status != ANI_OK) {
        LOG_ERROR(UDMF_ANI, "Object_GetFieldByName_Ref failed.");
        return false;
    }
    if (!SetProgressListener(env, getDataParams, static_cast<ani_fn_object>(dataProgressListener), key)) {
        LOG_ERROR(UDMF_ANI, "SetProgressListener failed.");
        return false;
    }
    ani_ref destUri;
    status = env->Object_GetFieldByName_Ref(in, "destUri", &destUri);
    if (status != ANI_OK) {
        LOG_ERROR(UDMF_ANI, "Object_GetFieldByName_Ref failed.");
        return false;
    }
    ani_size destUriLength;
    status = env->String_GetUTF8Size(static_cast<ani_string>(destUri), &destUriLength);
    if (status != ANI_OK) {
        LOG_ERROR(UDMF_ANI, "String_GetUTF8Size failed.");
        return false;
    }
    std::vector<char> destUriChars(destUriLength + 1);
    char *utf8Buffer = destUriChars.data();
    ani_size bytesWritten = 0;
    status = env->String_GetUTF8(static_cast<ani_string>(destUri), utf8Buffer, destUriLength + 1, &bytesWritten);
    if (status != ANI_OK) {
        LOG_ERROR(UDMF_ANI, "String_GetUTF8 failed.");
        return false;
    }
    utf8Buffer[bytesWritten] = '\0';
    getDataParams.destUri = std::string(utf8Buffer);

    ani_ref fileConflictOptions;
    status = env->Object_GetFieldByName_Ref(in, "fileConflictOptions", &fileConflictOptions);
    if (status != ANI_OK) {
        LOG_ERROR(UDMF_ANI, "Object_GetFieldByName_Ref failed.");
        return false;
    }
    ani_int fileConflictOptionsValue;
    status = env->EnumItem_GetValue_Int(static_cast<ani_enum_item>(fileConflictOptions), &fileConflictOptionsValue);
    if (status != ANI_OK) {
        LOG_ERROR(UDMF_ANI, "EnumItem_GetValue_Int failed.");
        return false;
    }
    getDataParams.fileConflictOptions = static_cast<FileConflictOptions>(fileConflictOptionsValue);
    return true;
}

bool GetDataParamsTaihe::SetProgressListener(ani_env *env, GetDataParams &getDataParams,
    ani_fn_object callback, const std::string &key)
{
    anifns.Compute(key, [&](const std::string &key, ani_fn_object &anifn) {
        if (anifn != nullptr) {
            LOG_WARN(UDMF_ANI, "Listener has existed!");
            env->GlobalReference_Delete(anifn);
            anifn = nullptr;
        }
        ani_ref anifnTemp;
        if (ANI_OK != env->GlobalReference_Create(callback, &anifnTemp)) {
            LOG_ERROR(UDMF_ANI, "napi_create_threadsafe_function failed.");
            return false;
        }
        anifn = std::move(static_cast<ani_fn_object>(anifnTemp));
        return true;
    });
    ani_vm *vm = nullptr;
    auto status = env->GetVM(&vm);
    if (status != ANI_OK || vm == nullptr) {
        LOG_ERROR(UDMF_ANI, "Get vm failed.");
    }
    getDataParams.progressListener = [key, &vm](ProgressInfo progressInfo, std::shared_ptr<UnifiedData> data) {
        bool listenerExist = anifns.ComputeIfPresent(key, [&](const std::string &key, ani_fn_object &anifn) {
            ani_env *workerEnv = nullptr;
            ani_options aniArgs {0, nullptr};
            auto status = vm->AttachCurrentThread(&aniArgs, ANI_VERSION_1, &workerEnv);
            if (status != ANI_OK) {
                LOG_ERROR(UDMF_ANI, "AttachCurrentThread failed, status=%{public}d", status);
                return false;
            }
            ani_object aniData = AniConverter::WrapUnifiedData(workerEnv, data);
            ani_object aniProgress = AniConverter::WrapProgressInfo(workerEnv, progressInfo);
            std::vector<ani_ref> listenerArgs({aniProgress, aniData});
            status = workerEnv->FunctionalObject_Call(anifn, listenerArgs.size(), listenerArgs.data(), nullptr);
            if (status != ANI_OK) {
                LOG_ERROR(UDMF_ANI, "Call callback function failed, status=%{public}d", status);
                return false;
            }
            if (progressInfo.progress >= PROGRESS_ALL_FINISHED ||
                progressInfo.progress < PROGRESS_INIT) {
                workerEnv->GlobalReference_Delete(anifn);
                return false;
            }
            return true;
        });
        if (!listenerExist) {
            LOG_INFO(UDMF_ANI, "No listener exist.");
        }
    };
    return true;
}

} // namespace UDMF
} // namespace OHOS
