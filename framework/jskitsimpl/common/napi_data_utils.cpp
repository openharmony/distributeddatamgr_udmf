/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
#define LOG_TAG "NapiDataUtils"
#include "napi_data_utils.h"

namespace OHOS {
namespace UDMF {
constexpr int32_t STR_MAX_LENGTH = 4096;
constexpr size_t STR_TAIL_LENGTH = 1;

static const std::map<napi_valuetype, ValueType> objectValueTypeMap = {
    {napi_valuetype::napi_number, double()},
    {napi_valuetype::napi_string, std::string()},
    {napi_valuetype::napi_boolean, bool()},
    {napi_valuetype::napi_undefined, std::monostate()},
    {napi_valuetype::napi_null, nullptr}
};

static const std::set<std::string> udsAttributeKeySet = {"details", "thumbData", "appIcon", "arrayBuffer"};
/* napi_value <-> bool */
napi_status NapiDataUtils::GetValue(napi_env env, napi_value in, bool &out)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "napi_value <- bool");
    return napi_get_value_bool(env, in, &out);
}

napi_status NapiDataUtils::SetValue(napi_env env, const bool &in, napi_value &out)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "napi_value -> bool");
    return napi_get_boolean(env, in, &out);
}

/* napi_value <-> int32_t */
napi_status NapiDataUtils::GetValue(napi_env env, napi_value in, int32_t &out)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "napi_value -> int32_t");
    return napi_get_value_int32(env, in, &out);
}

napi_status NapiDataUtils::SetValue(napi_env env, const int32_t &in, napi_value &out)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "napi_value <- int32_t");
    return napi_create_int32(env, in, &out);
}

/* napi_value <-> uint32_t */
napi_status NapiDataUtils::GetValue(napi_env env, napi_value in, uint32_t &out)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "napi_value -> int32_t");
    return napi_get_value_uint32(env, in, &out);
}

napi_status NapiDataUtils::SetValue(napi_env env, const uint32_t &in, napi_value &out)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "napi_value <- int32_t");
    return napi_create_uint32(env, in, &out);
}

/* napi_value <-> int64_t */
napi_status NapiDataUtils::GetValue(napi_env env, napi_value in, int64_t &out)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "napi_value -> int64_t");
    return napi_get_value_int64(env, in, &out);
}

napi_status NapiDataUtils::SetValue(napi_env env, const int64_t &in, napi_value &out)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "napi_value <- int64_t");
    return napi_create_int64(env, in, &out);
}

/* napi_value <-> float */
napi_status NapiDataUtils::GetValue(napi_env env, napi_value in, float &out)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "napi_value -> float");
    double tmp;
    napi_status status = napi_get_value_double(env, in, &tmp);
    out = tmp;
    return status;
}

napi_status NapiDataUtils::SetValue(napi_env env, const float &in, napi_value &out)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "napi_value <- float");
    double tmp = in;
    return napi_create_double(env, tmp, &out);
}

/* napi_value <-> double */
napi_status NapiDataUtils::GetValue(napi_env env, napi_value in, double &out)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "napi_value -> double");
    return napi_get_value_double(env, in, &out);
}

napi_status NapiDataUtils::SetValue(napi_env env, const double &in, napi_value &out)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "napi_value <- double");
    return napi_create_double(env, in, &out);
}

/* napi_value <-> std::string */
napi_status NapiDataUtils::GetValue(napi_env env, napi_value in, std::string &out)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "napi_value <- string");
    napi_valuetype type = napi_undefined;
    napi_status status = napi_typeof(env, in, &type);
    LOG_ERROR_RETURN((status == napi_ok) && (type == napi_string), "invalid type", napi_invalid_arg);

    size_t maxLen = STR_MAX_LENGTH;
    status = napi_get_value_string_utf8(env, in, NULL, 0, &maxLen);
    if (maxLen == 0) {
        return status;
    }
    char *buf = new (std::nothrow) char[maxLen + STR_TAIL_LENGTH];
    if (buf != nullptr) {
        size_t len = 0;
        status = napi_get_value_string_utf8(env, in, buf, maxLen + STR_TAIL_LENGTH, &len);
        if (status == napi_ok) {
            buf[len] = 0;
            out = std::string(buf);
        }
        delete[] buf;
    } else {
        status = napi_generic_failure;
    }
    return status;
}

napi_status NapiDataUtils::SetValue(napi_env env, const std::string &in, napi_value &out)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "napi_value <- std::string %{public}d", (int)in.length());
    return napi_create_string_utf8(env, in.c_str(), in.size(), &out);
}

/* napi_value <-> std::vector<std::string> */
napi_status NapiDataUtils::GetValue(napi_env env, napi_value in, std::vector<std::string> &out)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "napi_value -> std::vector<std::string>");
    bool isArray = false;
    napi_is_array(env, in, &isArray);
    LOG_ERROR_RETURN(isArray, "not an array", napi_invalid_arg);

    uint32_t length = 0;
    napi_status status = napi_get_array_length(env, in, &length);
    LOG_ERROR_RETURN((status == napi_ok) && (length > 0), "get_array failed!", napi_invalid_arg);
    for (uint32_t i = 0; i < length; ++i) {
        napi_value item = nullptr;
        status = napi_get_element(env, in, i, &item);
        LOG_ERROR_RETURN((item != nullptr) && (status == napi_ok), "no element", napi_invalid_arg);
        std::string value;
        status = GetValue(env, item, value);
        LOG_ERROR_RETURN(status == napi_ok, "not a string", napi_invalid_arg);
        out.push_back(value);
    }
    return status;
}

napi_status NapiDataUtils::SetValue(napi_env env, const std::vector<std::string> &in, napi_value &out)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "napi_value <- std::vector<std::string>");
    napi_status status = napi_create_array_with_length(env, in.size(), &out);
    LOG_ERROR_RETURN(status == napi_ok, "create array failed!", status);
    int index = 0;
    for (auto &item : in) {
        napi_value element = nullptr;
        SetValue(env, item, element);
        status = napi_set_element(env, out, index++, element);
        LOG_ERROR_RETURN((status == napi_ok), "napi_set_element failed!", status);
    }
    return status;
}

/* napi_value <-> std::vector<uint8_t> */
napi_status NapiDataUtils::GetValue(napi_env env, napi_value in, std::vector<uint8_t> &out)
{
    out.clear();
    LOG_DEBUG(UDMF_KITS_NAPI, "napi_value -> std::vector<uint8_t> ");

    bool isTypedArray = false;
    auto status = napi_is_typedarray(env, in, &isTypedArray);
    if (status != napi_ok || !isTypedArray) {
        return napi_invalid_arg;
    }

    napi_typedarray_type type = napi_biguint64_array;
    size_t length = 0;
    napi_value buffer = nullptr;
    size_t offset = 0;
    void *data = nullptr;
    status = napi_get_typedarray_info(env, in, &type, &length, &data, &buffer, &offset);
    LOG_DEBUG(UDMF_KITS_NAPI, "array type=%{public}d length=%{public}d offset=%{public}d  status=%{public}d",
        (int)type, (int)length, (int)offset, status);
    LOG_ERROR_RETURN(status == napi_ok, "napi_get_typedarray_info failed!", napi_invalid_arg);
    LOG_ERROR_RETURN(type == napi_uint8_array, "is not Uint8Array!", napi_invalid_arg);
    if (length > 0) {
        out.assign(static_cast<uint8_t *>(data), static_cast<uint8_t *>(data) + length);
    }
    return status;
}

napi_status NapiDataUtils::SetValue(napi_env env, const std::vector<uint8_t> &in, napi_value &out)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "napi_value <- std::vector<uint8_t> ");
    LOG_ERROR_RETURN(in.size() > 0, "invalid std::vector<uint8_t>", napi_invalid_arg);
    void *data = nullptr;
    napi_value buffer = nullptr;
    napi_status status = napi_create_arraybuffer(env, in.size(), &data, &buffer);
    LOG_ERROR_RETURN((status == napi_ok), "create array buffer failed!", status);

    if (memcpy_s(data, in.size(), in.data(), in.size()) != EOK) {
        LOG_ERROR(UDMF_KITS_NAPI, "memcpy_s not EOK");
        return napi_invalid_arg;
    }
    status = napi_create_typedarray(env, napi_uint8_array, in.size(), buffer, 0, &out);
    LOG_ERROR_RETURN((status == napi_ok), "napi_value <- std::vector<uint8_t> invalid value", status);
    return status;
}

/* napi_value <-> std::map<std::string, int32_t> */
napi_status NapiDataUtils::GetValue(napi_env env, napi_value in, std::map<std::string, int32_t> &out)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "napi_value -> std::map<std::string, int32_t> ");
    (void)(env);
    (void)(in);
    (void)(out);
    LOG_ERROR_RETURN(false, "std::map<std::string, uint32_t> from napi_value, unsupported!", napi_invalid_arg);
    return napi_invalid_arg;
}

napi_status NapiDataUtils::SetValue(napi_env env, const std::map<std::string, int32_t> &in, napi_value &out)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "napi_value <- std::map<std::string, int32_t> ");
    napi_status status = napi_create_array_with_length(env, in.size(), &out);
    LOG_ERROR_RETURN((status == napi_ok), "invalid object", status);
    int index = 0;
    for (const auto &[key, value] : in) {
        napi_value element = nullptr;
        napi_create_array_with_length(env, TUPLE_SIZE, &element);
        napi_value jsKey = nullptr;
        napi_create_string_utf8(env, key.c_str(), key.size(), &jsKey);
        napi_set_element(env, element, TUPLE_KEY, jsKey);
        napi_value jsValue = nullptr;
        napi_create_int32(env, static_cast<int32_t>(value), &jsValue);
        napi_set_element(env, element, TUPLE_VALUE, jsValue);
        napi_set_element(env, out, index++, element);
    }
    return status;
}

/* napi_value <-> std::map<std::string, int64_t> */
napi_status NapiDataUtils::GetValue(napi_env env, napi_value in, std::map<std::string, int64_t> &out)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "napi_value -> std::map<std::string, int64_t> ");
    (void)(env);
    (void)(in);
    (void)(out);
    LOG_ERROR_RETURN(false, "std::map<std::string, int64_t> from napi_value, unsupported!", napi_invalid_arg);
    return napi_invalid_arg;
}

napi_status NapiDataUtils::SetValueToArray(napi_env env, const std::map<std::string, int64_t> &in, napi_value &out)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "napi_value <- std::map<std::string, int64_t> ");
    napi_status status = napi_create_array_with_length(env, in.size(), &out);
    LOG_ERROR_RETURN((status == napi_ok), "invalid object", status);
    int index = 0;
    for (const auto &[key, value] : in) {
        napi_value element = nullptr;
        napi_create_array_with_length(env, TUPLE_SIZE, &element);
        napi_value jsKey = nullptr;
        napi_create_string_utf8(env, key.c_str(), key.size(), &jsKey);
        napi_set_element(env, element, TUPLE_KEY, jsKey);
        napi_value jsValue = nullptr;
        napi_create_int64(env, static_cast<int64_t>(value), &jsValue);
        napi_set_element(env, element, TUPLE_VALUE, jsValue);
        napi_set_element(env, out, index++, element);
    }
    return status;
}

napi_status NapiDataUtils::GetValue(napi_env env, napi_value in, std::set<std::string> &out)
{
    napi_value global;
    napi_value iterator;
    napi_value values_fn;
    napi_get_global(env, &global);
    napi_get_named_property(env, in, "values", &values_fn);
    napi_call_function(env, in, values_fn, 0, nullptr, &iterator);

    napi_value next_fn;
    napi_value result_obj;
    napi_value done_val;
    napi_value value_val;
    bool done = false;

    while (!done) {
        napi_get_named_property(env, iterator, "next", &next_fn);
        napi_call_function(env, iterator, next_fn, 0, nullptr, &result_obj);

        napi_get_named_property(env, result_obj, "done", &done_val);
        napi_get_value_bool(env, done_val, &done);
        if (done) break;

        napi_get_named_property(env, result_obj, "value", &value_val);

        size_t str_len;
        napi_get_value_string_utf8(env, value_val, nullptr, 0, &str_len);
        std::string str(str_len, '\0');
        napi_get_value_string_utf8(env, value_val, &str[0], str_len + 1, nullptr);

        out.insert(str);
    }
    return napi_ok;
}

napi_status NapiDataUtils::SetValue(napi_env env, const std::set<std::string> &in, napi_value &out)
{
    std::vector<std::string> vec(in.begin(), in.end());
    napi_value jsArray;
    NapiDataUtils::SetValue(env, vec, jsArray);

    napi_value global;
    napi_get_global(env, &global);

    napi_value setConstructor;
    napi_get_named_property(env, global, "Set", &setConstructor);

    napi_value argv[1] = { jsArray };
    napi_new_instance(env, setConstructor, 1, argv, &out);
    return napi_ok;
}

/* napi_value <-> UDVariant */
napi_status NapiDataUtils::GetValue(napi_env env, napi_value in, UDVariant &out)
{
    napi_valuetype type = napi_undefined;
    napi_status status = napi_typeof(env, in, &type);
    LOG_ERROR_RETURN((status == napi_ok), "invalid type", status);
    switch (type) {
        case napi_boolean: {
            bool vBool = false;
            status = GetValue(env, in, vBool);
            out = vBool;
            break;
        }
        case napi_number: {
            double vNum = 0.0f;
            status = GetValue(env, in, vNum);
            out = vNum;
            break;
        }
        case napi_string: {
            std::string vString;
            status = GetValue(env, in, vString);
            out = vString;
            break;
        }
        case napi_object: {
            std::vector<uint8_t> vct;
            status = GetValue(env, in, vct);
            out = vct;
            break;
        }
        default:
            LOG_ERROR(UDMF_KITS_NAPI,
                "napi_value <- UDVariant not [Uint8Array | string | boolean | number] type=%{public}d", type);
            status = napi_invalid_arg;
            break;
    }
    return status;
}

napi_status NapiDataUtils::SetValue(napi_env env, const UDVariant &in, napi_value &out)
{
    auto strValue = std::get_if<std::string>(&in);
    if (strValue != nullptr) {
        return SetValue(env, *strValue, out);
    }
    auto intValue = std::get_if<int32_t>(&in);
    if (intValue != nullptr) {
        return SetValue(env, *intValue, out);
    }
    auto pUint8 = std::get_if<std::vector<uint8_t>>(&in);
    if (pUint8 != nullptr) {
        return SetValue(env, *pUint8, out);
    }
    auto boolValue = std::get_if<bool>(&in);
    if (boolValue != nullptr) {
        return SetValue(env, *boolValue, out);
    }
    auto dblValue = std::get_if<double>(&in);
    if (dblValue != nullptr) {
        return SetValue(env, *dblValue, out);
    }

    LOG_ERROR(UDMF_KITS_NAPI, "napi_value <- UDVariant  INVALID value type");
    return napi_invalid_arg;
}

/* napi_value <-> UDDetails */
napi_status NapiDataUtils::GetValue(napi_env env, napi_value in, UDDetails &out)
{
    if (!IsTypeForNapiValue(env, in, napi_object)) {
        return napi_invalid_arg;
    }
    napi_value jsProNameList = nullptr;
    uint32_t jsProCount = 0;

    NAPI_CALL_BASE(env, napi_get_property_names(env, in, &jsProNameList), napi_invalid_arg);
    NAPI_CALL_BASE(env, napi_get_array_length(env, jsProNameList, &jsProCount), napi_invalid_arg);

    napi_value jsProName = nullptr;
    napi_value jsProValue = nullptr;
    for (uint32_t index = 0; index < jsProCount; index++) {
        NAPI_CALL_BASE(env, napi_get_element(env, jsProNameList, index, &jsProName), napi_invalid_arg);
        if (!IsTypeForNapiValue(env, jsProName, napi_string)) {
            return napi_invalid_arg;
        }
        std::string strProName;
        GetValue(env, jsProName, strProName);

        NAPI_CALL_BASE(env, napi_get_named_property(env, in, strProName.c_str(), &jsProValue), napi_invalid_arg);
        UDVariant natValue;
        GetValue(env, jsProValue, natValue);
        out[strProName] = natValue;
    }
    return napi_ok;
}

napi_status NapiDataUtils::SetValue(napi_env env, const UDDetails &in, napi_value &out)
{
    NAPI_CALL_BASE(env, napi_create_object(env, &out), napi_invalid_arg);
    for (std::pair<std::string, UDVariant> prop : in) {
        napi_value jsProValue = nullptr;
        SetValue(env, prop.second, jsProValue);
        NAPI_CALL_BASE(env, napi_set_named_property(env, out, prop.first.c_str(), jsProValue), napi_invalid_arg);
    }
    return napi_ok;
}

napi_status NapiDataUtils::GetValue(napi_env env, napi_value in, std::shared_ptr<TypeDescriptor> &descriptor)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "napi_value -> std::GetValue TypeDescriptor");
    napi_valuetype type = napi_undefined;
    napi_status status = napi_typeof(env, in, &type);
    LOG_ERROR_RETURN((status == napi_ok) && (type == napi_object), "invalid type", napi_invalid_arg);
    TypeDescriptorNapi *descriptorNapi = nullptr;
    auto unwrap = napi_unwrap(env, in, reinterpret_cast<void **>(&descriptorNapi));
    LOG_ERROR_RETURN((descriptorNapi != nullptr || unwrap == napi_ok), "invalid type", napi_invalid_arg);
    descriptor = descriptorNapi->value_;
    if (descriptor == nullptr) {
        LOG_DEBUG(UDMF_KITS_NAPI, "napi_value -> GetValue TypeDescriptor failed ");
    }
    return napi_ok;
}

napi_status NapiDataUtils::GetValue(napi_env env, napi_value in, std::shared_ptr<OHOS::Media::PixelMap> &pixelMap)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "napi_value -> std::shared_ptr<OHOS::Media::PixelMap>");
    pixelMap = OHOS::Media::PixelMapNapi::GetPixelMap(env, in);
    return napi_ok;
}

napi_status NapiDataUtils::SetValue(napi_env env, const std::shared_ptr<OHOS::Media::PixelMap> &in, napi_value &out)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "napi_value <- std::shared_ptr<OHOS::Media::PixelMap>");
    out = OHOS::Media::PixelMapNapi::CreatePixelMap(env, in);
    return napi_ok;
}

napi_status NapiDataUtils::GetValue(napi_env env, napi_value in, std::shared_ptr<OHOS::AAFwk::Want> &wantPtr)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "napi_value -> std::shared_ptr<OHOS::AAFwk::Want>");
    OHOS::AAFwk::Want want;
    AppExecFwk::UnwrapWant(env, in, want);
    wantPtr = std::make_shared<OHOS::AAFwk::Want>(want);
    return napi_ok;
}

napi_status NapiDataUtils::SetValue(napi_env env, const std::shared_ptr<OHOS::AAFwk::Want> &in, napi_value &out)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "napi_value <- std::shared_ptr<OHOS::AAFwk::Want>");
    out = OHOS::AppExecFwk::WrapWant(env, *in);
    return napi_ok;
}

napi_status NapiDataUtils::GetValue(napi_env env, napi_value in, std::shared_ptr<Object> &object)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "napi_value -> std::GetValue Object");
    napi_value attributeNames = nullptr;
    NAPI_CALL_BASE(env, napi_get_property_names(env, in, &attributeNames), napi_invalid_arg);
    uint32_t attributesNum = 0;
    NAPI_CALL_BASE(env, napi_get_array_length(env, attributeNames, &attributesNum), napi_invalid_arg);
    for (uint32_t i = 0; i < attributesNum; i++) {
        napi_value attributeNameNapi = nullptr;
        NAPI_CALL_BASE(env, napi_get_element(env, attributeNames, i, &attributeNameNapi), napi_invalid_arg);
        size_t len = 0;
        char str[STR_MAX_SIZE] = { 0 };
        NAPI_CALL_BASE(env, napi_get_value_string_utf8(
            env, attributeNameNapi, str, STR_MAX_SIZE, &len), napi_invalid_arg);
        std::string attributeName = str;
        napi_value attributeValueNapi = nullptr;
        NAPI_CALL_BASE(env, napi_get_named_property(env, in, str, &attributeValueNapi), napi_invalid_arg);

        bool isArrayBuffer = false;
        NAPI_CALL_BASE(env, napi_is_arraybuffer(env, attributeValueNapi, &isArrayBuffer), napi_invalid_arg);
        if (isArrayBuffer) {
            void *data = nullptr;
            size_t dataLen = 0;
            NAPI_CALL_BASE(env, napi_get_arraybuffer_info(env, attributeValueNapi, &data, &dataLen), napi_invalid_arg);
            object->value_[attributeName] = std::vector<uint8_t>(
                reinterpret_cast<uint8_t *>(data), reinterpret_cast<uint8_t *>(data) + dataLen);
            continue;
        }
        napi_valuetype valueType = napi_undefined;
        NAPI_CALL_BASE(env, napi_typeof(env, attributeValueNapi, &valueType), napi_invalid_arg);
        napi_status status = napi_ok;
        if (valueType == napi_valuetype::napi_object) {
            status = ProcessNapiObject(env, in, attributeName, attributeValueNapi, object);
            if (status != napi_ok) {
                return status;
            }
        } else {
            auto it = objectValueTypeMap.find(valueType);
            if (it != objectValueTypeMap.end()) {
                object->value_[attributeName] = it->second;
            } else {
                return napi_invalid_arg;
            }
        }
        std::visit([&](auto &value) {status = NapiDataUtils::GetValue(env, attributeValueNapi, value);},
            object->value_[attributeName]);
        if (status != napi_ok) {
            return status;
        }
    }
    return napi_ok;
}

napi_status NapiDataUtils::ProcessNapiObject(napi_env env, napi_value in, std::string &attributeName,
    napi_value attributeValueNapi, std::shared_ptr<Object> object)
{
    if (attributeName == PIXEL_MAP) {
        object->value_[attributeName] = std::shared_ptr<OHOS::Media::PixelMap>();
        return napi_ok;
    }
    bool isUint8Array = false;
    napi_value constructor = nullptr;
    NAPI_CALL_BASE(env, napi_get_named_property(env, attributeValueNapi, "constructor", &constructor),
        napi_invalid_arg);
    napi_value global = nullptr;
    NAPI_CALL_BASE(env, napi_get_global(env, &global), napi_invalid_arg);
    napi_value uint8ArrayConstructor = nullptr;
    NAPI_CALL_BASE(env, napi_get_named_property(env, global, "Uint8Array", &uint8ArrayConstructor), napi_invalid_arg);
    NAPI_CALL_BASE(env, napi_strict_equals(env, constructor, uint8ArrayConstructor, &isUint8Array), napi_invalid_arg);
    if (isUint8Array && (udsAttributeKeySet.find(attributeName) != udsAttributeKeySet.end())) {
        napi_value jsProValue = nullptr;
        NAPI_CALL_BASE(env, napi_get_named_property(env, in, attributeName.c_str(), &jsProValue), napi_invalid_arg);
        std::vector<uint8_t> array;
        auto status = GetValue(env, jsProValue, array);
        if (status != napi_ok) {
            LOG_ERROR(UDMF_KITS_NAPI, "Get Uint8Array error: %{public}d", status);
            return status;
        }
        object->value_[attributeName] = array;
        return napi_ok;
    }
    object->value_[attributeName] = std::make_shared<Object>();
    return napi_ok;
}

napi_status NapiDataUtils::SetValue(napi_env env, const std::shared_ptr<Object> &object, napi_value &out)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "napi_value -> std::GetValue Object");
    napi_create_object(env, &out);
    for (auto &[key, value] : object->value_) {
        napi_value valueNapi = nullptr;
        if (std::holds_alternative<std::vector<uint8_t>>(value) &&
            (udsAttributeKeySet.find(key) == udsAttributeKeySet.end())) {
            auto array = std::get<std::vector<uint8_t>>(value);
            void *data = nullptr;
            size_t len = array.size();
            NAPI_CALL_BASE(env, napi_create_arraybuffer(env, len, &data, &valueNapi), napi_generic_failure);
            if (memcpy_s(data, len, reinterpret_cast<const void *>(array.data()), len) != 0) {
                LOG_ERROR(UDMF_KITS_NAPI, "memcpy_s failed");
                return napi_generic_failure;
            }
        } else if (std::holds_alternative<std::vector<uint8_t>>(value) &&
            (udsAttributeKeySet.find(key) != udsAttributeKeySet.end())) {
                auto array = std::get<std::vector<uint8_t>>(value);
                void *data = nullptr;
                napi_value buffer = nullptr;
                NAPI_CALL_BASE(env, napi_create_arraybuffer(env, array.size(), &data, &buffer), napi_generic_failure);
                if (!array.empty() && memcpy_s(data, array.size(), array.data(), array.size()) != 0) {
                    LOG_ERROR(UDMF_KITS_NAPI, "memcpy_s failed");
                    return napi_generic_failure;
                }
                NAPI_CALL_BASE(env, napi_create_typedarray(env, napi_uint8_array, array.size(), buffer, 0, &valueNapi),
                    napi_generic_failure);
        } else {
            std::visit([&](const auto &value) {NapiDataUtils::SetValue(env, value, valueNapi);}, value);
        }
        napi_set_named_property(env, out, key.c_str(), valueNapi);
    }
    return napi_ok;
}

napi_status NapiDataUtils::GetValue(napi_env env, napi_value in, std::monostate &out)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "napi_value -> std::monostate");
    out = std::monostate{};
    return napi_ok;
}

napi_status NapiDataUtils::SetValue(napi_env env, const std::monostate &in, napi_value &out)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "napi_value <- std::monostate");
    return napi_get_undefined(env, &out);
}

napi_status NapiDataUtils::GetValue(napi_env env, napi_value in, nullptr_t &out)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "napi_value -> null");
    out = nullptr;
    return napi_ok;
}

napi_status NapiDataUtils::SetValue(napi_env env, const nullptr_t &in, napi_value &out)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "napi_value <- null");
    return napi_get_null(env, &out);
}

napi_status NapiDataUtils::SetValue(napi_env env, const ProgressInfo &in, napi_value &out)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "napi_value <- ProgressInfo");
    napi_create_object(env, &out);

    napi_value jsPercentage = nullptr;
    SetValue(env, in.progress, jsPercentage);
    NAPI_CALL_BASE(env, napi_set_named_property(env, out, "progress", jsPercentage), napi_invalid_arg);

    napi_value jsListenerStatus = nullptr;
    SetValue(env, in.progressStatus, jsListenerStatus);
    NAPI_CALL_BASE(env, napi_set_named_property(env, out, "status", jsListenerStatus), napi_invalid_arg);
    return napi_ok;
}

napi_status NapiDataUtils::SetValue(napi_env env, const DataLoadInfo &in, napi_value &out)
{
    LOG_ERROR(UDMF_KITS_NAPI, "napi_value <- DataLoadInfo");
    napi_create_object(env, &out);

    napi_value jsRecordCount = nullptr;
    NAPI_CALL_BASE(env, SetValue(env, in.recordCount, jsRecordCount), napi_invalid_arg);
    NAPI_CALL_BASE(env, napi_set_named_property(env, out, "recordCount", jsRecordCount), napi_invalid_arg);

    napi_value jsTypes = nullptr;
    NAPI_CALL_BASE(env, SetValue(env, in.types, jsTypes), napi_invalid_arg);
    NAPI_CALL_BASE(env, napi_set_named_property(env, out, "types", jsTypes), napi_invalid_arg);
    return napi_ok;
}

napi_status NapiDataUtils::GetValue(napi_env env, napi_value in, DataLoadInfo &out)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "napi_value -> DataLoadInfo");
    napi_value jsTypes = nullptr;
    NAPI_CALL_BASE(env, GetOptionalNamedProperty(env, in, "types", jsTypes), napi_invalid_arg);
    if (jsTypes != nullptr) {
        NAPI_CALL_BASE(env, NapiDataUtils::GetValue(env, jsTypes, out.types), napi_invalid_arg);
    }

    out.recordCount = 0;
    napi_value jsRecordCount = nullptr;
    NAPI_CALL_BASE(env, GetOptionalNamedProperty(env, in, "recordCount", jsRecordCount), napi_invalid_arg);
    if (jsRecordCount != nullptr) {
        double count = 0;
        NAPI_CALL_BASE(env, NapiDataUtils::GetValue(env, jsRecordCount, count), napi_invalid_arg);
        if (!std::isfinite(count)) {
            LOG_WARN(UDMF_KITS_NAPI, "recordCount is not a finite number");
            return napi_ok;
        }
        count = std::floor(count);
        if (count < 0 || count > static_cast<double>(UINT32_MAX)) {
            LOG_WARN(UDMF_KITS_NAPI, "recordCount out of range: %{public}f", count);
            return napi_ok;
        }
        out.recordCount = static_cast<uint32_t>(count);
    }
    return napi_ok;
}

napi_status NapiDataUtils::GetValue(napi_env env, napi_value in, std::vector<TypeDescriptorCfg> &out)
{
    bool isArray = false;
    napi_is_array(env, in, &isArray);
    LOG_ERROR_RETURN(isArray, "not an array", napi_invalid_arg);

    uint32_t length = 0;
    napi_status status = napi_get_array_length(env, in, &length);
    LOG_ERROR_RETURN(status == napi_ok, "get_array failed!", napi_invalid_arg);
    for (uint32_t i = 0; i < length; ++i) {
        napi_value item = nullptr;
        status = napi_get_element(env, in, i, &item);
        LOG_ERROR_RETURN((item != nullptr) && (status == napi_ok), "no element", napi_invalid_arg);
        std::shared_ptr<TypeDescriptor> value = nullptr;
        status = GetValue(env, item, value);
        LOG_ERROR_RETURN(status == napi_ok && value != nullptr, "not a TypeDescriptor", napi_invalid_arg);

        TypeDescriptorCfg typeCfg;
        typeCfg.typeId = value->GetTypeId();
        typeCfg.belongingToTypes = value->GetBelongingToTypes();
        typeCfg.mimeTypes = value->GetMimeTypes();
        typeCfg.description = value->GetDescription();
        typeCfg.filenameExtensions = value->GetFilenameExtensions();
        typeCfg.iconFile = value->GetIconFile();
        typeCfg.referenceURL = value->GetReferenceURL();
        out.push_back(std::move(typeCfg));
    }
    return status;
}

bool NapiDataUtils::IsTypeForNapiValue(napi_env env, napi_value param, napi_valuetype expectType)
{
    napi_valuetype valueType = napi_undefined;

    if (param == nullptr) {
        return false;
    }

    if (napi_typeof(env, param, &valueType) != napi_ok) {
        return false;
    }

    return valueType == expectType;
}

bool NapiDataUtils::IsNull(napi_env env, napi_value value)
{
    napi_valuetype type = napi_undefined;
    napi_status status = napi_typeof(env, value, &type);
    if (status == napi_ok && (type == napi_undefined || type == napi_null)) {
        return true;
    }
    if (type == napi_string) {
        size_t len;
        napi_get_value_string_utf8(env, value, NULL, 0, &len);
        return len == 0;
    }
    return false;
}

bool NapiDataUtils::IsUndefinedOrNull(napi_env env, napi_value value)
{
    napi_valuetype type = napi_undefined;
    napi_status status = napi_typeof(env, value, &type);
    if (status == napi_ok && (type == napi_undefined || type == napi_null)) {
        return true;
    }
    return false;
}

napi_value NapiDataUtils::DefineClass(napi_env env, const std::string &name,
    const napi_property_descriptor *properties, size_t count, napi_callback newcb)
{
    // base64("data.udmf") as rootPropName, i.e. global.<root>
    constexpr const char *rootPropName = "ZGF0YS51ZG1m";
    napi_value root = nullptr;
    bool hasRoot = false;
    napi_value global = nullptr;
    napi_get_global(env, &global);
    napi_has_named_property(env, global, rootPropName, &hasRoot);
    if (hasRoot) {
        napi_get_named_property(env, global, rootPropName, &root);
    } else {
        napi_create_object(env, &root);
        napi_set_named_property(env, global, rootPropName, root);
    }

    std::string propName = "constructor_of_" + name;
    napi_value constructor = nullptr;
    bool hasProp = false;
    napi_has_named_property(env, root, propName.c_str(), &hasProp);
    if (hasProp) {
        napi_get_named_property(env, root, propName.c_str(), &constructor);
        if (constructor != nullptr) {
            LOG_DEBUG(UDMF_KITS_NAPI, "got data.distributeddata.%{public}s as constructor", propName.c_str());
            return constructor;
        }
        hasProp = false; // no constructor.
    }

    NAPI_CALL_BASE(env,
        napi_define_class(env, name.c_str(), name.size(), newcb, nullptr, count, properties, &constructor),
        nullptr);
    NAPI_ASSERT(env, constructor != nullptr, "napi_define_class failed!");

    if (!hasProp) {
        napi_set_named_property(env, root, propName.c_str(), constructor);
        LOG_DEBUG(UDMF_KITS_NAPI, "save constructor to data.distributeddata.%{public}s", propName.c_str());
    }
    return constructor;
}

napi_status NapiDataUtils::GetOptionalNamedProperty(napi_env env, napi_value &obj, const std::string &key,
    napi_value &napiValue)
{
    bool hasKey = false;
    napi_status status = napi_has_named_property(env, obj, key.c_str(), &hasKey);
    if (status != napi_ok) {
        LOG_ERROR(UDMF_KITS_NAPI, "napi_has_named_property failed, name = %{public}s", key.c_str());
        return status;
    }
    if (!hasKey) {
        napiValue = nullptr;
        return napi_ok;
    }
    status = napi_get_named_property(env, obj, key.c_str(), &napiValue);
    if (status != napi_ok || napiValue == nullptr) {
        LOG_ERROR(UDMF_KITS_NAPI, "napi_get_named_property failed, name = %{public}s", key.c_str());
        return napi_generic_failure;
    }
    if (IsNull(env, napiValue)) {
        napiValue = nullptr;
        return napi_ok;
    }
    return napi_ok;
}

napi_status NapiDataUtils::SetValue(napi_env env, const std::map<std::string, int64_t> &in, napi_value &out)
{
    NAPI_CALL_BASE(env, napi_create_object(env, &out), napi_invalid_arg);
    for (const auto &[key, value] : in) {
        napi_value jsProValue = nullptr;
        NAPI_CALL_BASE(env, SetValue(env, value, jsProValue), napi_invalid_arg);
        NAPI_CALL_BASE(env, napi_set_named_property(env, out, key.c_str(), jsProValue), napi_invalid_arg);
    }
    return napi_ok;
}
} // namespace UDMF
} // namespace OHOS
