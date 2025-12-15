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

#include "ani_common_want.h"
#include "ani_common_utils.h"
#include "logger.h"
#include "pixel_map_taihe_ani.h"

namespace OHOS {
namespace UDMF {

constexpr const char* RECORD_SERIALIZE_TOOL_CLASS_NAME = "@ohos.app.ability.Want.RecordSerializeTool";
constexpr const char* CLASSNAME_NULL = "std.core.Null";
constexpr const char* CLASSNAME_INT = "std.core.Int";
constexpr const char* CLASSNAME_LONG = "std.core.Long";
constexpr const char* CLASSNAME_DOUBLE = "std.core.Double";
constexpr const char* CLASSNAME_STRING = "std.core.String";
constexpr const char* CLASSNAME_BOOLEAN = "std.core.Boolean";
constexpr const char* CLASSNAME_ARRAY_BUFFER = "escompat.ArrayBuffer";
constexpr const char* CLASSNAME_RECORD = "escompat.Record";
constexpr const char* CLASSNAME_OBJECT = "std.core.Object";
constexpr const int MAX_KEY_COUNT = 10 * 1024;
constexpr const int MAX_DATA_BYTES = 100 * 1024 * 1024;


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

ani_status SetTimestamp(ani_env *env, double timestamp, ani_object &aniDate)
{
    ani_class cls {};
    auto status = env->FindClass("escompat.Date", &cls);
    if (status != ANI_OK) {
        LOG_ERROR(UDMF_ANI, "FindClass failed, status:%{public}d", status);
        return status;
    }
    ani_method ctorMethod {};
    status = env->Class_FindMethod(cls, "<ctor>",
        "X{C{std.core.Double}C{std.core.String}C{escompat.Date}}:", &ctorMethod);
    if (status != ANI_OK) {
        LOG_ERROR(UDMF_ANI, "Class_FindMethod failed, status:%{public}d", status);
        return status;
    }
    ani_object aniDoubleObject {};
    status = SetDouble(env, timestamp, aniDoubleObject);
    if (status != ANI_OK) {
        LOG_ERROR(UDMF_ANI, "SetDouble failed, status:%{public}d", status);
        return status;
    }
    status = env->Object_New(cls, ctorMethod, &aniDate, aniDoubleObject);
    if (status != ANI_OK) {
        LOG_ERROR(UDMF_ANI, "Object_New failed, status:%{public}d", status);
        return status;
    }
    return ANI_OK;
}

ani_status SetInt(ani_env *env, int32_t value, ani_object &intObj)
{
    ani_class intCls;
    ani_status status = ANI_ERROR;
    if ((status = env->FindClass(CLASSNAME_INT, &intCls)) != ANI_OK) {
        LOG_ERROR(UDMF_ANI, "FindClass failed, status : %{public}d", status);
        return status;
    }
    ani_method intCtor;
    if ((status = env->Class_FindMethod(intCls, "<ctor>", "i:", &intCtor)) != ANI_OK) {
        LOG_ERROR(UDMF_ANI, "Class_FindMethod failed, status : %{public}d", status);
        return status;
    }
    if ((status = env->Object_New(intCls, intCtor, &intObj, value)) != ANI_OK) {
        LOG_ERROR(UDMF_ANI, "Object_New failed, status : %{public}d", status);
        return status;
    }
    return ANI_OK;
}

ani_status SetLong(ani_env *env, int64_t value, ani_object &longObj)
{
    ani_class longCls;
    ani_status status = ANI_ERROR;
    if ((status = env->FindClass(CLASSNAME_LONG, &longCls)) != ANI_OK) {
        LOG_ERROR(UDMF_ANI, "FindClass failed, status : %{public}d", status);
        return status;
    }
    ani_method longCtor;
    if ((status = env->Class_FindMethod(longCls, "<ctor>", "l:", &longCtor)) != ANI_OK) {
        LOG_ERROR(UDMF_ANI, "Class_FindMethod failed, status : %{public}d", status);
        return status;
    }
    if ((status = env->Object_New(longCls, longCtor, &longObj, value)) != ANI_OK) {
        LOG_ERROR(UDMF_ANI, "Object_New failed, status : %{public}d", status);
        return status;
    }
    return ANI_OK;
}

ani_status SetDouble(ani_env *env, double value, ani_object &doubleObj)
{
    ani_class doubleCls;
    ani_status status = ANI_ERROR;
    if ((status = env->FindClass(CLASSNAME_DOUBLE, &doubleCls)) != ANI_OK) {
        LOG_ERROR(UDMF_ANI, "FindClass failed, status : %{public}d", status);
        return status;
    }
    ani_method doubleCtor;
    if ((status = env->Class_FindMethod(doubleCls, "<ctor>", "d:", &doubleCtor)) != ANI_OK) {
        LOG_ERROR(UDMF_ANI, "Class_FindMethod failed, status : %{public}d", status);
        return status;
    }
    if ((status = env->Object_New(doubleCls, doubleCtor, &doubleObj, value)) != ANI_OK) {
        LOG_ERROR(UDMF_ANI, "Object_New failed, status : %{public}d", status);
        return status;
    }
    return ANI_OK;
}

ani_status SetBoolean(ani_env *env, bool value, ani_object &boolObj)
{
    ani_class boolCls;
    ani_status status = ANI_ERROR;
    if ((status = env->FindClass(CLASSNAME_BOOLEAN, &boolCls)) != ANI_OK) {
        LOG_ERROR(UDMF_ANI, "FindClass failed, status : %{public}d", status);
        return status;
    }
    ani_method boolCtor;
    if ((status = env->Class_FindMethod(boolCls, "<ctor>", "z:", &boolCtor)) != ANI_OK) {
        LOG_ERROR(UDMF_ANI, "Class_FindMethod failed, status : %{public}d", status);
        return status;
    }
    if ((status = env->Object_New(boolCls, boolCtor, &boolObj, value)) != ANI_OK) {
        LOG_ERROR(UDMF_ANI, "Object_New failed, status : %{public}d", status);
        return status;
    }
    return ANI_OK;
}

ani_status SetMap(ani_env *env, std::map<std::string, int64_t> value, ani_object &mapObj)
{
    ani_class recordCls;
    ani_status status = ANI_ERROR;
    if ((status = env->FindClass(CLASSNAME_RECORD, &recordCls)) != ANI_OK) {
        LOG_ERROR(UDMF_ANI, "FindClass failed, status : %{public}d", status);
        return status;
    }
    ani_method recordCtor;
    if ((status = env->Class_FindMethod(recordCls, "<ctor>", ":", &recordCtor)) != ANI_OK) {
        LOG_ERROR(UDMF_ANI, "Class_FindMethod failed, status : %{public}d", status);
        return status;
    }
    if ((status = env->Object_New(recordCls, recordCtor, &mapObj, mapObj)) != ANI_OK) {
        LOG_ERROR(UDMF_ANI, "Object_New failed, status : %{public}d", status);
        return status;
    }
    for (const auto& [key, val] : value) {
        ani_string aniKey = {};
        status = env->String_NewUTF8(key.c_str(), key.size(), &aniKey);
        if (status != ANI_OK) {
            LOG_WARN(UDMF_ANI, "String_NewUTF8 failed, status : %{public}d", status);
            continue;
        }
        ani_object aniVal {};
        status = SetLong(env, val, aniVal);
        if (status != ANI_OK) {
            LOG_WARN(UDMF_ANI, "SetLong failed, status : %{public}d", status);
            continue;
        }
        ani_method recordSetter;
        if ((status = env->Class_FindMethod(recordCls, "$_set", "C{std.core.Object}:", &recordSetter)) != ANI_OK) {
            LOG_WARN(UDMF_ANI, "FindClass failed, status : %{public}d", status);
            continue;
        }
        status = env->Object_CallMethod_Void(mapObj, recordSetter, aniKey, aniVal);
        if (status != ANI_OK) {
            LOG_WARN(UDMF_ANI, "Object_CallMethod_Void status : %{public}d", status);
            continue;
        }
    }
    return ANI_OK;
}

ani_status SetArrayBuffer(ani_env *env, std::vector<uint8_t> value, ani_arraybuffer &arrayBufferObj)
{
    if (value.empty()) {
        LOG_ERROR(UDMF_ANI, "ArrayBuffer value is empty.");
        return ANI_ERROR;
    }
    auto valueLen = value.size();
    if (valueLen > MAX_DATA_BYTES) {
        LOG_ERROR(UDMF_ANI, "The number of data bytes exceeds the maximum value.");
        return ANI_ERROR;
    }
    void *buffer = nullptr;
    auto status = env->CreateArrayBuffer(valueLen, &buffer, &arrayBufferObj);
    if (status != ANI_OK || buffer == nullptr) {
        LOG_ERROR(UDMF_ANI, "CreateArrayBuffer failed, status:%{public}d", status);
        return status;
    }
    std::copy(value.begin(), value.end(), reinterpret_cast<uint8_t*>(buffer));
    return ANI_OK;
}

bool SetFieldRef(ani_env *env, ani_class cls, ani_object object, const std::string &fieldName, ani_ref value)
{
    ani_status status = env->Object_SetPropertyByName_Ref(object, fieldName.c_str(), value);
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

ObjectType GetObjectType(ani_env *env, ani_object obj)
{
    ani_boolean isUndefined = ANI_FALSE;
    ani_status status = env->Reference_IsUndefined(obj, &isUndefined);
    if (status != ANI_OK) {
        LOG_ERROR(UDMF_ANI, "Reference_IsUndefined fail %{public}d", status);
        return ObjectType::OBJ_BUTT;
    }
    if (isUndefined) {
        return ObjectType::OBJ_UNDEFINED;
    }
    std::map<ObjectType, std::string> typeClassMap = {
        {ObjectType::OBJ_NULL, CLASSNAME_NULL},
        {ObjectType::OBJ_INT, CLASSNAME_INT},
        {ObjectType::OBJ_LONG, CLASSNAME_LONG},
        {ObjectType::OBJ_DOUBLE, CLASSNAME_DOUBLE},
        {ObjectType::OBJ_STRING, CLASSNAME_STRING},
        {ObjectType::OBJ_BOOL, CLASSNAME_BOOLEAN},
        {ObjectType::OBJ_ARRAY_BUFFER, CLASSNAME_ARRAY_BUFFER},
        {ObjectType::OBJ_MAP, CLASSNAME_RECORD},
        {ObjectType::OBJ_OBJECT, CLASSNAME_OBJECT},
    };
    ani_class cls {};
    ani_boolean isType = ANI_FALSE;
    for (auto const &[type, className] : typeClassMap) {
        status = env->FindClass(className.c_str(), &cls);
        if (status != ANI_OK) {
            continue;
        }
        status = env->Object_InstanceOf(obj, cls, &isType);
        if (status != ANI_OK) {
            continue;
        }
        if (isType) {
            return type;
        }
    }
    return ObjectType::OBJ_BUTT;
}

std::vector<std::string> GetObjectKeys(ani_env *env, ani_object obj)
{
    std::vector<std::string> keys;
    ani_class cls {};
    env->FindClass(CLASSNAME_OBJECT, &cls);
    ani_ref result;
    auto status = env->Class_CallStaticMethodByName_Ref(
        cls, "keys", "C{std.core.Object}:C{escompat.Array}", &result, obj);
    if (status != ANI_OK) {
        LOG_ERROR(UDMF_ANI, "Class_CallStaticMethodByName_Ref fail %{public}d", status);
        return keys;
    }
    ani_array aniKeys = static_cast<ani_array>(result);
    ani_size size;
    if (ANI_OK != env->Array_GetLength(aniKeys, &size)) {
        LOG_ERROR(UDMF_ANI, "Array_GetLength fail");
        return keys;
    }
    for (ani_size i = 0; i < size ; i++) {
        ani_ref string_ref;
        auto status = env->Array_Get(aniKeys, i, &string_ref);
        if (status != ANI_OK) {
            LOG_WARN(UDMF_ANI, "Array_Get fail");
            continue;
        }
        std::string key;
        status = GetString(env, static_cast<ani_object>(string_ref), key);
        if (status != ANI_OK) {
            LOG_WARN(UDMF_ANI, "GetString fail");
            continue;
        }
        keys.emplace_back(key);
    }
    return keys;
}

ani_status GetInt(ani_env *env, ani_object in, int32_t &out)
{
    ani_int value = 0;
    auto status = env->Object_CallMethodByName_Int(in, "toInt", ":i", &value);
    if (status != ANI_OK) {
        LOG_ERROR(UDMF_ANI, "GetInt fail, status:%{public}d", status);
        return status;
    }
    out = value;
    return ANI_OK;
}

ani_status GetLong(ani_env *env, ani_object in, int64_t &out)
{
    ani_long value = 0;
    auto status = env->Object_CallMethodByName_Long(in, "toLong", ":l", &value);
    if (status != ANI_OK) {
        LOG_ERROR(UDMF_ANI, "GetLong fail, status:%{public}d", status);
        return status;
    }
    out = value;
    return ANI_OK;
}

ani_status GetDouble(ani_env *env, ani_object in, double &out)
{
    ani_double value = 0;
    auto status = env->Object_CallMethodByName_Double(in, "toDouble", ":d", &value);
    if (status != ANI_OK) {
        LOG_ERROR(UDMF_ANI, "GetDouble fail, status:%{public}d", status);
        return status;
    }
    out = value;
    return ANI_OK;
}

ani_status GetString(ani_env *env, ani_object in, std::string &out)
{
    ani_size sz {};
    ani_string aniStr = static_cast<ani_string>(in);
    auto status = env->String_GetUTF8Size(aniStr, &sz);
    if (status != ANI_OK) {
        LOG_ERROR(UDMF_ANI, "String_GetUTF8Size fail, status:%{public}d", status);
        return status;
    }
    if (sz > MAX_DATA_BYTES) {
        LOG_ERROR(UDMF_ANI, "GetString failed, string size exceed max limit %{public}d bytes", MAX_DATA_BYTES);
        return ANI_ERROR;
    }
    std::string result(sz + 1, 0);
    status = env->String_GetUTF8(aniStr, result.data(), result.size(), &sz);
    if (status != ANI_OK) {
        LOG_ERROR(UDMF_ANI, "String_GetUTF8 fail, status:%{public}d", status);
        return status;
    }
    result.resize(sz);
    out = std::move(result);
    return ANI_OK;
}

ani_status GetBool(ani_env *env, ani_object in, bool &out)
{
    ani_boolean value = 0;
    auto status = env->Object_CallMethodByName_Boolean(in, "toBoolean", ":z", &value);
    if (status != ANI_OK) {
        LOG_ERROR(UDMF_ANI, "GetBool fail, status:%{public}d", status);
        return status;
    }
    out = value;
    return ANI_OK;
}

ani_status GetArrayBuffer(ani_env *env, ani_object in, std::vector<uint8_t> &out)
{
    void *data;
    ani_size dataLen;
    auto status = env->ArrayBuffer_GetInfo(static_cast<ani_arraybuffer>(in), &data, &dataLen);
    if (status != ANI_OK) {
        LOG_ERROR(UDMF_ANI, "GetArrayBuffer fail, status:%{public}d", status);
        return status;
    }
    if (dataLen > 0) {
        out = std::vector<uint8_t>(reinterpret_cast<uint8_t *>(data), reinterpret_cast<uint8_t *>(data) + dataLen);
    }
    return ANI_OK;
}

ani_status GetMap(ani_env *env, ani_object in, std::shared_ptr<Object> &out, int depth)
{
    if (depth > MAX_RECURSIVE) {
        LOG_ERROR(UDMF_ANI, "Exceeding the maximum recursion depth");
        return ANI_ERROR;
    }
    ani_ref keys;
    ani_status status = env->Object_CallMethodByName_Ref(in, "keys", ":C{escompat.IterableIterator}", &keys);
    if (status != ANI_OK) {
        LOG_ERROR(UDMF_ANI, "Failed to get keys iterator, status %{public}d", status);
        return status;
    }
    out = std::make_shared<Object>();
    for (int loopCount = 0; loopCount < MAX_KEY_COUNT; ++loopCount) {
        ani_ref next;
        ani_boolean done;
        status = env->Object_CallMethodByName_Ref(static_cast<ani_object>(keys), "next", nullptr, &next);
        if (status != ANI_OK) {
            LOG_ERROR(UDMF_ANI, "Failed to get next key, status %{public}d", status);
            break;
        }
        status = env->Object_GetFieldByName_Boolean(static_cast<ani_object>(next), "done", &done);
        if (status != ANI_OK) {
            LOG_ERROR(UDMF_ANI, "Failed to check iterator done, status %{public}d", status);
            break;
        }
        if (done) {
            break;
        }
        ani_ref key_value;
        status = env->Object_GetFieldByName_Ref(static_cast<ani_object>(next), "value", &key_value);
        if (status != ANI_OK) {
            LOG_WARN(UDMF_ANI, "Failed to get key value, status %{public}d", status);
            continue;
        }
        ani_ref value_obj;
        status = env->Object_CallMethodByName_Ref(in, "$_get", nullptr, &value_obj, key_value);
        if (status != ANI_OK) {
            LOG_WARN(UDMF_ANI, "Failed to get value for key, status %{public}d", status);
            continue;
        }
        std::string key;
        status = GetString(env, static_cast<ani_object>(key_value), key);
        if (status != ANI_OK) {
            LOG_WARN(UDMF_ANI, "Failed to get sring for key, status %{public}d", status);
            continue;
        }
        ValueType value;
        status = ConverObject(env, static_cast<ani_object>(value_obj), value, depth + 1);
        if (status != ANI_OK) {
            LOG_WARN(UDMF_ANI, "Failed to get sring for key, status %{public}d", status);
            continue;
        }
        out->value_[key] = value;
    }
    return ANI_OK;
}

ani_status GetObject(ani_env *env, ani_object in, ValueType &out, int depth)
{
    if (depth > MAX_RECURSIVE) {
        LOG_ERROR(UDMF_ANI, "Exceeding the maximum recursion depth");
        return ANI_ERROR;
    }
    auto keys = GetObjectKeys(env, in);
    if (std::find(keys.begin(), keys.end(), "uniformDataType") != keys.end()) {
        ani_ref aniType {};
        auto status = env->Object_GetPropertyByName_Ref(in, "uniformDataType", &aniType);
        if (status != ANI_OK) {
            LOG_ERROR(UDMF_ANI, "Object_GetPropertyByName_Ref fail");
            return ANI_ERROR;
        }
        std::string type;
        status = GetString(env, static_cast<ani_object>(aniType), type);
        if (status != ANI_OK) {
            LOG_ERROR(UDMF_ANI, "GetString fail");
            return ANI_ERROR;
        }
        if (type == "openharmony.want") {
            OHOS::AAFwk::Want want;
            OHOS::AppExecFwk::UnwrapWant(env, in, want);
            out = std::make_shared<OHOS::AAFwk::Want>(want);
            return ANI_OK;
        } else if (type == "openharmony.pixel-map") {
            out = OHOS::Media::PixelMapTaiheAni::GetNativePixelMap(env, in);
            return ANI_OK;
        }
    }
    auto objectPtr = std::make_shared<Object>();
    for (auto const &key : keys) {
        ani_ref aniValue {};
        auto status = env->Object_GetPropertyByName_Ref(in, key.c_str(), &aniValue);
        if (status != ANI_OK) {
            LOG_WARN(UDMF_ANI, "Object_GetPropertyByName_Ref fail");
            continue;
        }
        ValueType value = nullptr;
        status = ConverObject(env, static_cast<ani_object>(aniValue), value, depth + 1);
        if (status != ANI_OK) {
            LOG_WARN(UDMF_ANI, "ConverObject fail");
            continue;
        }
        objectPtr->value_[key] = value;
    }
    out = objectPtr;
    return ANI_OK;
}

ani_status ConverObject(ani_env *env, ani_object aniObj, ValueType &valueType, int depth)
{
    if (depth > MAX_RECURSIVE) {
        LOG_ERROR(UDMF_ANI, "Exceeding the maximum recursion depth");
        return ANI_ERROR;
    }
    auto type = GetObjectType(env, aniObj);
    if (type == ObjectType::OBJ_BUTT) {
        LOG_ERROR(UDMF_ANI, "Invalid object type");
        return ANI_ERROR;
    } else if (type == ObjectType::OBJ_NULL) {
        valueType = std::monostate();
        return ANI_OK;
    } else if (type == ObjectType::OBJ_UNDEFINED) {
        valueType = nullptr;
        return ANI_OK;
    } else if (type == ObjectType::OBJ_INT) {
        int32_t value = 0;
        auto status = GetInt(env, aniObj, value);
        if (status != ANI_OK) {
            LOG_ERROR(UDMF_ANI, "GetInt fail, status:%{public}d", status);
            return status;
        }
        valueType = value;
        return ANI_OK;
    } else if (type == ObjectType::OBJ_LONG) {
        int64_t value = 0;
        auto status = GetLong(env, aniObj, value);
        if (status != ANI_OK) {
            LOG_ERROR(UDMF_ANI, "GetLong fail, status:%{public}d", status);
            return status;
        }
        valueType = value;
        return ANI_OK;
    } else if (type == ObjectType::OBJ_DOUBLE) {
        double value = 0;
        auto status = GetDouble(env, aniObj, value);
        if (status != ANI_OK) {
            LOG_ERROR(UDMF_ANI, "GetDouble fail, status:%{public}d", status);
            return status;
        }
        valueType = value;
        return ANI_OK;
    } else if (type == ObjectType::OBJ_STRING) {
        std::string value;
        auto status = GetString(env, aniObj, value);
        if (status != ANI_OK) {
            LOG_ERROR(UDMF_ANI, "GetString fail, status:%{public}d", status);
            return status;
        }
        valueType = std::move(value);
        return ANI_OK;
    } else if (type == ObjectType::OBJ_BOOL) {
        bool value = false;
        auto status = GetBool(env, aniObj, value);
        if (status != ANI_OK) {
            LOG_ERROR(UDMF_ANI, "GetBool fail, status:%{public}d", status);
            return status;
        }
        valueType = value;
        return ANI_OK;
    } else if (type == ObjectType::OBJ_ARRAY_BUFFER) {
        std::vector<uint8_t> value;
        auto status = GetArrayBuffer(env, aniObj, value);
        if (status != ANI_OK) {
            LOG_ERROR(UDMF_ANI, "GetArrayBuffer fail, status:%{public}d", status);
            return status;
        }
        valueType = std::move(value);
        return ANI_OK;
    } else if (type == ObjectType::OBJ_MAP) {
        std::shared_ptr<Object> value;
        auto status = GetMap(env, aniObj, value, depth + 1);
        if (status != ANI_OK) {
            LOG_ERROR(UDMF_ANI, "GetMap fail, status:%{public}d", status);
            return status;
        }
        valueType = value;
        return ANI_OK;
    } else if (type == ObjectType::OBJ_OBJECT) {
        auto status = GetObject(env, aniObj, valueType, depth + 1);
        if (status != ANI_OK) {
            LOG_ERROR(UDMF_ANI, "GetObject fail, status:%{public}d", status);
            return status;
        }
        return ANI_OK;
    }
    return ANI_OK;
}
} // namespace UDMF
} // namespace OHOS