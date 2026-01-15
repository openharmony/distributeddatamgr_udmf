/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#define LOG_TAG "DDATA_LOAD_PARAMS_TAIHE"

#include "ani_common_utils.h"
#include "data_load_params_taihe.h"
#include "logger.h"
#include "udmf_ani_converter_utils.h"
#include "udmf_client.h"
#include "udmf_utils.h"

namespace OHOS {
namespace UDMF {
ConcurrentMap<std::string, ani_fn_object> DataLoadParamsTaihe::anifns;
bool DataLoadParamsTaihe::Convert2NativeValue(ani_env *env, ani_object in,
    DataLoadParams &dataLoadParams)
{
    if (!SetDataLoadInfo(env, in, dataLoadParams)) {
        LOG_ERROR(UDMF_ANI, "SetAcceptableInfo failed.");
    }
    dataLoadParams.dataLoadInfo.sequenceKey = UTILS::GenerateId();
    ani_ref loadHandler;
    bool isAsync = true;
    auto status = env->Object_GetPropertyByName_Ref(in, "delayedDataLoadHandler", &loadHandler);
    if (status != ANI_OK) {
        LOG_ERROR(UDMF_ANI, "Object_GetPropertyByName_Ref failed.");
        return false;
    }
    if (IsNullOrUndefined(env, static_cast<ani_object>(loadHandler))) {
        LOG_ERROR(UDMF_ANI, "loadHandler is null or undefined.");
        auto status = env->Object_GetPropertyByName_Ref(in, "loadHandler", &loadHandler);
        if (status != ANI_OK) {
            LOG_ERROR(UDMF_ANI, "Object_GetPropertyByName_Ref failed.");
            return false;
        }
        isAsync = false;
    }
    if (!SetLoadHandler(env, dataLoadParams, static_cast<ani_fn_object>(loadHandler), isAsync)) {
        LOG_ERROR(UDMF_ANI, "SetLoadHandler failed.");
        return false;
    }
    return true;
}

bool DataLoadParamsTaihe::SetDataLoadInfo(ani_env *env, ani_object in, DataLoadParams &dataLoadParams)
{
    ani_ref acceptableInfo;
    auto status = env->Object_GetPropertyByName_Ref(in, "dataLoadInfo", &acceptableInfo);
    if (status != ANI_OK) {
        LOG_ERROR(UDMF_ANI, "Object_GetPropertyByName_Ref failed.");
        return false;
    }
    ani_object dataLoadInfo = static_cast<ani_object>(acceptableInfo);
    if (IsNullOrUndefined(env, dataLoadInfo)) {
        LOG_ERROR(UDMF_ANI, "acceptableInfo is null or undefined.");
        return false;
    }
    status = GetAcceptableInfo(env, dataLoadInfo, dataLoadParams.dataLoadInfo);
    if (status != ANI_OK) {
        LOG_ERROR(UDMF_ANI, "GetAcceptableInfo failed.");
        return false;
    }
    return true;
}

bool DataLoadParamsTaihe::SetLoadHandler(
    ani_env *env, DataLoadParams &dataLoadParams, ani_fn_object callback, bool isAsync)
{
    SaveCallback(env, dataLoadParams, callback);
    ani_vm *vm = nullptr;
    auto status = env->GetVM(&vm);
    if (status != ANI_OK || vm == nullptr) {
        LOG_ERROR(UDMF_ANI, "Get vm failed.");
    }
    dataLoadParams.loadHandler = [vm, isAsync](std::string udKey, DataLoadInfo acceptableInfo) {
        LOG_INFO(UDMF_ANI, "Load handler Start.");
        auto seqKey = UTILS::GetSequenceKey(udKey);
        if (seqKey.empty()) {
            LOG_ERROR(UDMF_ANI, "Error udKey:%{public}s", udKey.c_str());
            return;
        }
        bool anifnExist = anifns.ComputeIfPresent(seqKey, [&](const std::string &key, ani_fn_object &anifn) {
            ani_env *workerEnv = nullptr;
            ani_options aniArgs {0, nullptr};
            if (vm == nullptr) {
                LOG_ERROR(UDMF_ANI, "vm is null.");
                return false;
            }
            auto status = vm->AttachCurrentThread(&aniArgs, ANI_VERSION_1, &workerEnv);
            if (status != ANI_OK) {
                LOG_ERROR(UDMF_ANI, "AttachCurrentThread failed, status=%{public}d", status);
                return false;
            }
            ani_ref result;
            status = CallHandler(workerEnv, anifn, acceptableInfo, isAsync, result);
            workerEnv->GlobalReference_Delete(anifn);
            if (status != ANI_OK) {
                LOG_ERROR(UDMF_ANI, "CallHandler failed, status=%{public}d", status);
                vm->DetachCurrentThread();
                return false;
            }
            HandleUnifiedData(workerEnv, udKey, static_cast<ani_object>(result));
            vm->DetachCurrentThread();
            return false;
        });
        if (!anifnExist) {
            LOG_INFO(UDMF_ANI, "No listener exists.");
        }
    };
    return true;
}

void DataLoadParamsTaihe::SaveCallback(ani_env *env, DataLoadParams &dataLoadParams, ani_fn_object callback)
{
    anifns.Compute(dataLoadParams.dataLoadInfo.sequenceKey, [&](const std::string &key, ani_fn_object &anifn) {
        if (anifn != nullptr) {
            LOG_WARN(UDMF_ANI, "Listener has existed!");
            env->GlobalReference_Delete(anifn);
            anifn = nullptr;
        }
        ani_ref anifnTemp;
        if (ANI_OK != env->GlobalReference_Create(callback, &anifnTemp)) {
            LOG_ERROR(UDMF_ANI, "GlobalReference_Create failed.");
            return false;
        }
        anifn = std::move(static_cast<ani_fn_object>(anifnTemp));
        return true;
    });
}

int32_t DataLoadParamsTaihe::HandleUnifiedData(ani_env *env, std::string udKey, ani_object aniData)
{
    if (IsNullOrUndefined(env, aniData)) {
        LOG_ERROR(UDMF_ANI, "Data is null or undefined.");
        return E_INVALID_PARAMETERS;
    }
    std::shared_ptr<UnifiedData> data = AniConverter::UnwrapUnifiedData(env, aniData);
    if (data == nullptr) {
        LOG_ERROR(UDMF_ANI, "Convert to unifiedData failed.");
        return E_INVALID_PARAMETERS;
    }
    auto ret = UdmfClient::GetInstance().PushDelayData(udKey, *data);
    if (ret != E_OK) {
        LOG_ERROR(UDMF_ANI, "SetData failed, status=%{public}d", ret);
    }
    return ret;
}

ani_status DataLoadParamsTaihe::CallHandler(ani_env *env, ani_fn_object &anifn,
    DataLoadInfo &acceptableInfo, bool isAsync, ani_ref &result)
{
    ani_object aniAcceptableInfo;
    auto status = SetAcceptableInfo(env, acceptableInfo, aniAcceptableInfo);
    if (status != ANI_OK) {
        LOG_ERROR(UDMF_ANI, "SetAcceptableInfo failed, status=%{public}d", status);
        return status;
    }
    if (!isAsync) {
        std::vector<ani_ref> handlerArgs({aniAcceptableInfo});
        status = env->FunctionalObject_Call(anifn, handlerArgs.size(), handlerArgs.data(), &result);
        if (status != ANI_OK) {
            LOG_ERROR(UDMF_ANI, "FunctionalObject_Call failed, status=%{public}d", status);
        }
        return status;
    }
    ani_namespace channelNm;
    status = env->FindNamespace("@ohos.data.unifiedDataChannel.unifiedDataChannel", &channelNm);
    if (status != ANI_OK) {
        LOG_ERROR(UDMF_ANI, "Module_FindNamespace failed, status=%{public}d", status);
        return status;
    }
    ani_function delayedFunc;
    status = env->Namespace_FindFunction(channelNm, "delayedDataLoadHandlerFunc", nullptr, &delayedFunc);
    if (status != ANI_OK) {
        LOG_ERROR(UDMF_ANI, "Namespace_FindFunction failed, status=%{public}d", status);
        return status;
    }
    status = env->Function_Call_Ref(delayedFunc, &result, anifn, aniAcceptableInfo);
    if (status != ANI_OK) {
        LOG_ERROR(UDMF_ANI, "FunctionalObject_Call failed, status=%{public}d", status);
    }
    return status;
}
} // namespace UDMF
} // namespace OHOS
