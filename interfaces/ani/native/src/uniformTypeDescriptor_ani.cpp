 /*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define LOG_TAG "UniformTypeDescriptorAni"

#include "ani_utils.h"
#include "logger.h"
#include "error_code.h"
#include "utd_client.h"
#include <ani.h>

using namespace OHOS::UDMF;

static ani_string GetUniformDataTypeByFilenameExtension(ani_env *env, ani_string filenameExtension,
    ani_object belongsTo)
{
    LOG_ERROR(UDMF_KITS_NAPI, "GetUniformDataTypeByFilenameExtension is called!");
    std::string filenameExtension_ = AniStringUtils::ToStd(env, filenameExtension);
    ani_boolean isUndefined;
    if (ANI_OK != env->Reference_IsUndefined(belongsTo, &isUndefined)) {
        LOG_ERROR(UDMF_KITS_NAPI, "Object_GetFieldByName_Ref isRepeat failed.");
        return nullptr;
    }
    std::string typeId;
    auto status = E_OK;
    if (isUndefined) {
        status = UtdClient::GetInstance().GetUniformDataTypeByFilenameExtension(filenameExtension_, typeId);
    } else {
        std::string belongsTo_ = AniStringUtils::ToStd(env, static_cast<ani_string>(belongsTo));
        status = UtdClient::GetInstance().GetUniformDataTypeByFilenameExtension(filenameExtension_, typeId, belongsTo_);
    }

    if (status != E_OK) {
        LOG_ERROR(UDMF_KITS_NAPI, "invalid arguments!");
        return nullptr;
    }

    if (!typeId.empty()) {
        return AniStringUtils::ToAni(env, typeId);
    }
    return nullptr;
}


ANI_EXPORT ani_status ANI_Constructor(ani_vm *vm, uint32_t *result)
{
    ani_env *env;
    if (ANI_OK != vm->GetEnv(ANI_VERSION_1, &env)) {
        LOG_ERROR(UDMF_KITS_NAPI, "Unsupported ANI_VERSION_1");
        return ANI_ERROR;
    }

    static const char *nsName = "L@ohos/data/uniformTypeDescriptor/uniformTypeDescriptor;";
    ani_namespace ns;
    if (ANI_OK != env->FindNamespace(nsName, &ns)) {
        LOG_ERROR(UDMF_KITS_NAPI, "Not found %{public}s", nsName);
        return ANI_ERROR;
    }

    std::array methods = {
        ani_native_function {"getUniformDataTypeByFilenameExtension", nullptr,
            reinterpret_cast<void *>(GetUniformDataTypeByFilenameExtension) },
    };

    if (ANI_OK != env->Namespace_BindNativeFunctions(ns, methods.data(), methods.size())) {
        LOG_ERROR(UDMF_KITS_NAPI, "Cannot bind native methods to %{public}s", nsName);
        return ANI_ERROR;
    };

    if (result == nullptr) {
        LOG_ERROR(UDMF_KITS_NAPI, "param result is null");
        return ANI_ERROR;
    }
    *result = ANI_VERSION_1;
    return ANI_OK;
}