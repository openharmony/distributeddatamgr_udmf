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

#define LOG_TAG "UDMF_ANI_COMMON_UTILS"

#include "ani_common_utils.h"
#include "logger.h"

namespace OHOS {
namespace UDMF {

constexpr const char* RECORD_SERIALIZE_TOOL_CLASS_NAME = "@ohos.app.ability.Want.RecordSerializeTool";
constexpr const char* CLASSNAME_LONG = "std.core.Long";

ani_ref WrapMapParams(ani_env *env, const std::map<std::string, int64_t> &mapParams)
{
    ani_status status = ANI_ERROR;
    ani_class cls = nullptr;
    if ((status = env->FindClass(RECORD_SERIALIZE_TOOL_CLASS_NAME, &cls)) != ANI_OK) {
        LOG_ERROR(UDMF_ANI, "FindClass RecordSerializeTool failed, status : %{public}d", status);
    }
    if (cls == nullptr) {
        LOG_ERROR(UDMF_ANI, "RecordSerializeTool class null");
        return nullptr;
    }
    ani_static_method parseNoThrowMethod = nullptr;
    status = env->Class_FindStaticMethod(cls, "parseNoThrow", nullptr, &parseNoThrowMethod);
    if (status != ANI_OK) {
        LOG_ERROR(UDMF_ANI, "Failed to get parseNoThrow method, status : %{public}d", status);
        return nullptr;
    }

    nlohmann::json mapParamsJson = mapParams;
    std::string mapParamsString = mapParamsJson.dump();
    ani_string mapParamsAniString;
    status = env->String_NewUTF8(mapParamsString.c_str(), mapParamsString.length(), &mapParamsAniString);
    if (status != ANI_OK) {
        LOG_ERROR(UDMF_ANI, "String_NewUTF8 mapParamsString failed, status : %{public}d", status);
        return nullptr;
    }

    ani_ref mapParamsRef = nullptr;
    status = env->Class_CallStaticMethod_Ref(cls, parseNoThrowMethod, &mapParamsRef, mapParamsAniString);
    if (status != ANI_OK) {
        LOG_ERROR(UDMF_ANI, "Failed to call parseNoThrow method, status : %{public}d", status);
        return nullptr;
    }
    return mapParamsRef;
}

ani_object CreateLong(ani_env *env, int64_t value)
{
    if (env == nullptr) {
        LOG_ERROR(UDMF_ANI, "CreateLong fail, env is nullptr");
        return nullptr;
    }
    ani_class longCls;
    ani_status status = ANI_ERROR;
    if ((status = env->FindClass(CLASSNAME_LONG, &longCls)) != ANI_OK) {
        LOG_ERROR(UDMF_ANI, "FindClass status : %{public}d", status);
        return nullptr;
    }
    ani_method longCtor;
    if ((status = env->Class_FindMethod(longCls, "<ctor>", "J:V", &longCtor)) != ANI_OK) {
        LOG_ERROR(UDMF_ANI, "Class_FindMethod status : %{public}d", status);
        return nullptr;
    }
    ani_object longObj;
    if ((status = env->Object_New(longCls, longCtor, &longObj, value)) != ANI_OK) {
        LOG_ERROR(UDMF_ANI, "Object_New status : %{public}d", status);
        return nullptr;
    }
    return longObj;
}

bool SetFieldRef(ani_env *env, ani_class cls, ani_object object, const std::string &fieldName, ani_ref value)
{
    ani_field field = nullptr;
    ani_status status = env->Class_FindField(cls, fieldName.c_str(), &field);
    if (status != ANI_OK) {
        LOG_ERROR(UDMF_ANI, "FindField %{public}s failed, status: %{public}d", fieldName.c_str(), status);
        return false;
    }
    status = env->Object_SetField_Ref(object, field, value);
    if (status != ANI_OK) {
        LOG_ERROR(UDMF_ANI, "SetField_Ref %{public}s failed, status: %{public}d", fieldName.c_str(), status);
        return false;
    }
    return true;
}

bool InnerWrapMapParams(ani_env *env, ani_class mapCls, ani_object mapObject,
    const std::map<std::string, int64_t> &mapParams)
{
    ani_ref mapParamsRef = WrapMapParams(env, mapParams);
    if (mapParamsRef == nullptr) {
        LOG_ERROR(UDMF_ANI, "Failed to WrapWantParams");
        return false;
    }
    return SetFieldRef(env, mapCls, mapObject, "summary", mapParamsRef);
}
} // namespace UDMF
} // namespace OHOS