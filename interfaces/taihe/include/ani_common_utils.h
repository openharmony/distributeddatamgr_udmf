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

#ifndef UDMF_ANI_COMMON_UTILS_H
#define UDMF_ANI_COMMON_UTILS_H

#include "ani.h"
#include "async_task_params.h"
#include "logger.h"
#include "unified_data.h"

namespace OHOS {
namespace UDMF {
static constexpr int MAX_RECURSIVE = 20;
enum ObjectType : int32_t {
    OBJ_UNDEFINED = 0,
    OBJ_NULL,
    OBJ_INT,
    OBJ_LONG,
    OBJ_DOUBLE,
    OBJ_STRING,
    OBJ_BOOL,
    OBJ_ARRAY_BUFFER,
    OBJ_UINT8_ARRAY,
    OBJ_MAP,
    OBJ_OBJECT,
    OBJ_BUTT,
};
ani_ref WrapMapParams(ani_env *env, const std::map<std::string, int64_t> &mapParams);
ani_status SetInt(ani_env *env, int32_t value, ani_object &intObj);
ani_status SetLong(ani_env *env, int64_t value, ani_object &longObj);
ani_status SetDouble(ani_env *env, double value, ani_object &doubleObj);
ani_status SetBoolean(ani_env *env, bool value, ani_object &boolObj);
ani_status SetArrayBuffer(ani_env *env, std::vector<uint8_t> value, ani_arraybuffer &arrayBufferObj);
ani_status SetMap(ani_env *env, std::map<std::string, int64_t> value, ani_object &arrayBufferObj);
ani_status SetTimestamp(ani_env *env, double timestamp, ani_object &aniDate);
bool SetFieldRef(ani_env *env, ani_class cls, ani_object object, const std::string &fieldName, ani_ref value);
bool InnerWrapMapParams(ani_env *env, ani_class wantCls, ani_object wantObject,
    const std::map<std::string, int64_t> &mapParams);

ObjectType GetObjectType(ani_env *env, ani_object obj);
std::vector<std::string> GetObjectKeys(ani_env *env, ani_object obj);
ani_status GetInt(ani_env *env, ani_object in, int32_t &out);
ani_status GetLong(ani_env *env, ani_object in, int64_t &out);
ani_status GetDouble(ani_env *env, ani_object in, double &out);
ani_status GetString(ani_env *env, ani_object in, std::string &out);
ani_status GetBool(ani_env *env, ani_object in, bool &out);
ani_status GetArrayBuffer(ani_env *env, ani_object in, std::vector<uint8_t> &out);
ani_status GetUint8Array(ani_env *env, ani_object in, std::vector<uint8_t> &out);
ani_status GetMap(ani_env *env, ani_object in, std::shared_ptr<Object> &out, int depth);
ani_status GetObject(ani_env *env, ani_object in, ValueType &out, int depth);
ani_status ConverObject(ani_env *env, ani_object object, ValueType &valueType, int depth);
bool IsNullOrUndefined(ani_env *env, ani_object aniObj);

} // namespace UDMF
} // namespace OHOS
#endif // UDMF_ANI_COMMON_UTILS_H