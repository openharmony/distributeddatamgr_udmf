/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License a
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "aip_napi_utils.h"

#include <dlfcn.h>
#include <memory>

#include "js_ability.h"
#include "aip_log.h"

#undef LOG_TAG
#define LOG_TAG "AipNapiUtils"

namespace OHOS {
namespace DataIntelligence {
namespace {
using namespace OHOS::AppDataMgrJsKit;
static constexpr uint32_t MAX_VALUE_LENGTH = 1024 * 1024 * 8; // the max length of all kand of out string value
static constexpr uint8_t CONFIG_LENGTH_1 = 2;
static constexpr uint8_t CONFIG_LENGTH_2 = 3;
static constexpr uint32_t MAX_STR_PARAM_LEN = 512;
constexpr const char *PATH_SPLIT = "/";
struct OperatorInfo {
    const char *operatorStr;
    int32_t operatorEnum;
};
} // namespace

bool AipNapiUtils::LoadAlgoLibrary(const std::string &libraryName, AipCoreManagerHandle &aipMgrHandler)
{
    AIP_HILOGD("Enter");
    if (aipMgrHandler.handle != nullptr) {
        AIP_HILOGE("handle has exists");
        return false;
    }

    if (libraryName.empty()) {
        AIP_HILOGE("algoPath is empty");
        return false;
    }
    char libRealPath[PATH_MAX] = {};
    if (realpath(libraryName.c_str(), libRealPath) == nullptr) {
        AIP_HILOGE("get absolute algoPath error, %{public}d", errno);
        return false;
    }

    aipMgrHandler.handle = dlopen(libRealPath, RTLD_LAZY);
    if (aipMgrHandler.handle == nullptr) {
        AIP_HILOGE("cannot load lib error: %{public}s", dlerror());
        return false;
    }

    aipMgrHandler.create = reinterpret_cast<IAipCoreManager *(*)()>(dlsym(aipMgrHandler.handle, "Create"));
    aipMgrHandler.destroy = reinterpret_cast<void (*)(const IAipCoreManager *)>(dlsym(aipMgrHandler.handle, "Destroy"));
    if (aipMgrHandler.create == nullptr || aipMgrHandler.destroy == nullptr) {
        dlclose(aipMgrHandler.handle);
        aipMgrHandler.Clear();
        AIP_HILOGE("Failed to create and destroy algo");
        return false;
    }
    
    aipMgrHandler.pAipManager = aipMgrHandler.create();
    AIP_HILOGD("Exit");
    return true;
}

bool AipNapiUtils::UnLoadAlgoLibrary(AipCoreManagerHandle &aipMgrHandler)
{
    AIP_HILOGD("Enter");
    if (aipMgrHandler.handle == nullptr) {
        AIP_HILOGE("handle is nullptr");
        return false;
    }

    if (aipMgrHandler.pAipManager != nullptr && aipMgrHandler.destroy != nullptr) {
        aipMgrHandler.destroy(aipMgrHandler.pAipManager);
        aipMgrHandler.pAipManager = nullptr;
    }

    dlclose(aipMgrHandler.handle);
    aipMgrHandler.Clear();
    AIP_HILOGD("Exit");
    return true;
}

IAipCoreManager *AipNapiUtils::GetAlgoObj(AipCoreManagerHandle &aipMgrHandler)
{
    AIP_HILOGD("Enter");
    if (aipMgrHandler.handle == nullptr) {
        AIP_HILOGE("handle is nullptr");
        return nullptr;
    }

    if (aipMgrHandler.pAipManager != nullptr) {
        AIP_HILOGD("pAipManager already exists");
        return aipMgrHandler.pAipManager;
    }

    if (aipMgrHandler.create == nullptr) {
        AIP_HILOGE("create is nullptr");
        return nullptr;
    }

    aipMgrHandler.pAipManager = aipMgrHandler.create();
    AIP_HILOGD("Exit");
    return aipMgrHandler.pAipManager;
}

bool AipNapiUtils::ValidateArgsType(napi_env env, napi_value *args, size_t argc,
    const std::vector<std::string> &expectedTypes)
{
    AIP_HILOGD("Enter");
    napi_status status = napi_ok;
    napi_valuetype valueType = napi_undefined;

    if (argc != expectedTypes.size()) {
        AIP_HILOGE("Wrong number of arguments");
        return false;
    }

    for (size_t i = 0; i < argc; ++i) {
        status = napi_typeof(env, args[i], &valueType);
        if (status != napi_ok) {
            AIP_HILOGE("Error while checking arguments types");
            return false;
        }
        std::string expectedType = expectedTypes[i];
        if ((expectedType == "string" && valueType != napi_string) ||
            (expectedType == "object" && valueType != napi_object) ||
            (expectedType == "number" && valueType != napi_number) ||
            (expectedType == "function" && valueType != napi_function)) {
            AIP_HILOGE("Wrong argument type");
            return false;
        }
    }
    return true;
}

bool AipNapiUtils::TransJsToStr(napi_env env, napi_value value, std::string &str)
{
    size_t strlen = 0;
    napi_status status = napi_get_value_string_utf8(env, value, nullptr, 0, &strlen);
    if (status != napi_ok) {
        AIP_HILOGE("Error string length invalid");
        return false;
    }
    if (strlen > MAX_STR_PARAM_LEN) {
        AIP_HILOGE("The string length invalid");
        return false;
    }
    std::vector<char> buf(strlen + 1);
    status = napi_get_value_string_utf8(env, value, buf.data(), strlen + 1, &strlen);
    if (status != napi_ok) {
        AIP_HILOGE("napi_get_value_string_utf8 failed");
        return false;
    }
    str = buf.data();
    return true;
}

bool AipNapiUtils::TransJsToStrUnlimited(napi_env env, napi_value value, std::string &str)
{
    size_t strlen = 0;
    napi_status status = napi_get_value_string_utf8(env, value, nullptr, 0, &strlen);
    if (status != napi_ok) {
        AIP_HILOGE("Error string length invalid");
        return false;
    }
    std::vector<char> buf(strlen + 1);
    status = napi_get_value_string_utf8(env, value, buf.data(), strlen + 1, &strlen);
    if (status != napi_ok) {
        AIP_HILOGE("napi_get_value_string_utf8 failed");
        return false;
    }
    str = buf.data();
    return true;
}

bool AipNapiUtils::TransJsToInt32(napi_env env, napi_value value, int32_t &res)
{
    napi_status status = napi_get_value_int32(env, value, &res);
    if (status != napi_ok) {
        AIP_HILOGE("napi_get_value_int32 failed");
        return false;
    }
    return true;
}

bool AipNapiUtils::TransJsToDouble(napi_env env, napi_value value, double &res)
{
    napi_status status = napi_get_value_double(env, value, &res);
    if (status != napi_ok) {
        AIP_HILOGE("napi_get_value_double failed");
        return false;
    }
    return true;
}

bool AipNapiUtils::TransJsToBool(napi_env env, napi_value value, bool &res)
{
    napi_status status = napi_get_value_bool(env, value, &res);
    if (status != napi_ok) {
        return false;
    }
    return true;
}

void AipNapiUtils::CreateStringData(napi_env env, napi_value aipServiceValue, napi_value result, const std::string name,
    std::string &content)
{
    napi_status ret = napi_create_string_utf8(env, content.c_str(), NAPI_AUTO_LENGTH, &aipServiceValue);
    if (ret != napi_ok) {
        AIP_HILOGE("napi_create_string_utf8 failed");
        return;
    }

    ret = napi_set_named_property(env, result, name.c_str(), aipServiceValue);
    if (ret != napi_ok) {
        AIP_HILOGE("napi_set_named_property failed");
    }
}

void AipNapiUtils::CreateInt32Data(napi_env env, napi_value aipServiceValue, napi_value result, const std::string name,
    int32_t value)
{
    napi_status ret = napi_create_int32(env, value, &aipServiceValue);
    if (ret != napi_ok) {
        AIP_HILOGE("napi_create_int32 failed");
        return;
    }

    ret = napi_set_named_property(env, result, name.c_str(), aipServiceValue);
    if (ret != napi_ok) {
        AIP_HILOGE("napi_set_named_property failed");
    }
}

void AipNapiUtils::CreateDoubleData(napi_env env, double value, napi_value *result)
{
    napi_status ret = napi_create_double(env, value, result);
    if (ret != napi_ok) {
        AIP_HILOGE("napi_create_int32 failed");
        return;
    }
}

void AipNapiUtils::SetInt32Property(napi_env env, napi_value targetObj, int32_t value, const char *propName)
{
    napi_value prop = nullptr;
    napi_status ret = napi_create_int32(env, value, &prop);
    if (ret != napi_ok) {
        AIP_HILOGE("napi_create_int32 failed");
        return;
    }
    SetPropertyName(env, targetObj, propName, prop);
}

void AipNapiUtils::SetStringProperty(napi_env env, napi_value targetObj, std::string value, const char *propName)
{
    napi_value prop = nullptr;
    napi_status ret = napi_create_string_utf8(env, value.c_str(), value.size(), &prop);
    if (ret != napi_ok) {
        AIP_HILOGE("napi_create_int32 failed");
        return;
    }
    SetPropertyName(env, targetObj, propName, prop);
}

void AipNapiUtils::SetPropertyName(napi_env env, napi_value targetObj, const char *propName, napi_value propValue)
{
    napi_status status = napi_set_named_property(env, targetObj, propName, propValue);
    if (status != napi_ok) {
        AIP_HILOGE("napi_set_named_property failed");
        return;
    }
}

bool AipNapiUtils::CheckModelConfig(napi_env env, napi_value value)
{
    napi_valuetype valuetype;
    napi_status status = napi_typeof(env, value, &valuetype);
    if (status != napi_ok || valuetype != napi_object) {
        AIP_HILOGE("ModelConfig is not object");
        return false;
    }

    napi_value KeysArray;
    status = napi_get_property_names(env, value, &KeysArray);
    if (status != napi_ok) {
        AIP_HILOGE("Failed to get property names");
        return false;
    }

    uint32_t length;
    status = napi_get_array_length(env, KeysArray, &length);
    if (status != napi_ok) {
        AIP_HILOGE("Failed to get array length");
        return false;
    }

    if (length != CONFIG_LENGTH_1 && length != CONFIG_LENGTH_2) {
        AIP_HILOGE("The modelConfig length is failed");
        return false;
    }
    return true;
}

napi_status AipNapiUtils::Convert2Value(napi_env env, napi_value in, bool &out)
{
    return napi_get_value_bool(env, in, &out);
}

napi_status AipNapiUtils::Convert2Value(napi_env env, napi_value in, int32_t &out)
{
    return napi_get_value_int32(env, in, &out);
}

napi_status AipNapiUtils::Convert2Value(napi_env env, napi_value in, uint32_t &out)
{
    return napi_get_value_uint32(env, in, &out);
}

napi_status AipNapiUtils::Convert2Value(napi_env env, napi_value in, std::vector<uint8_t> &out)
{
    bool isTypedArray = false;
    napi_is_typedarray(env, in, &isTypedArray);
    if (!isTypedArray) {
        return napi_invalid_arg;
    }

    napi_typedarray_type type;
    napi_value input_buffer = nullptr;
    size_t byte_offset = 0;
    size_t length = 0;
    void *tmp = nullptr;
    auto status = napi_get_typedarray_info(env, in, &type, &length, &tmp, &input_buffer, &byte_offset);
    if (status != napi_ok || type != napi_uint8_array) {
        return napi_invalid_arg;
    }

    out = (tmp != nullptr ? std::vector<uint8_t>(static_cast<uint8_t *>(tmp), static_cast<uint8_t *>(tmp) + length)
        : std::vector<uint8_t>());
    return status;
}

napi_status AipNapiUtils::Convert2Value(napi_env env, napi_value in, int64_t &out)
{
    return napi_get_value_int64(env, in, &out);
}

napi_status AipNapiUtils::Convert2Value(napi_env env, napi_value in, std::string &out)
{
    napi_valuetype type = napi_undefined;
    napi_status status = napi_typeof(env, in, &type);
    LOG_ERROR_RETURN((status == napi_ok) && (type == napi_string), "The parameter type is not a string.",
        napi_invalid_arg);
    size_t buffSize = 0;
    napi_get_value_string_utf8(env, in, nullptr, 0, &buffSize);
    // cut down with 0 if more than MAX_VALUE_LENGTH
    if (buffSize >= MAX_VALUE_LENGTH - 1) {
        buffSize = MAX_VALUE_LENGTH - 1;
    }
    std::unique_ptr<char[]> buffer = std::make_unique<char[]>(buffSize + 1);
    LOG_ERROR_RETURN(buffer, "Buffer data is nullptr.", napi_invalid_arg);
    status = napi_get_value_string_utf8(env, in, buffer.get(), buffSize + 1, &buffSize);
    LOG_ERROR_RETURN(status == napi_ok, "napi_get_value_string_utf8 failed", napi_invalid_arg);
    out = std::string(buffer.get());
    return status;
}

napi_status AipNapiUtils::Convert2Value(napi_env env, napi_value in, std::vector<float> &out)
{
    bool isTypedArray = false;
    napi_is_typedarray(env, in, &isTypedArray);
    if (!isTypedArray) {
        return napi_invalid_arg;
    }

    napi_typedarray_type type;
    napi_value input_buffer = nullptr;
    size_t byte_offset = 0;
    size_t length = 0;
    void *tmp = nullptr;
    auto status = napi_get_typedarray_info(env, in, &type, &length, &tmp, &input_buffer, &byte_offset);
    if (status != napi_ok || type != napi_float32_array) {
        return napi_invalid_arg;
    }

    out = (tmp != nullptr
                  ? std::vector<float>(static_cast<float *>(tmp), static_cast<float *>(tmp) + length / sizeof(float))
                  : std::vector<float>());
    return status;
}

napi_status AipNapiUtils::Convert2Value(napi_env env, napi_value in, float &out)
{
    double tmp;
    napi_status status = napi_get_value_double(env, in, &tmp);
    out = tmp;
    return status;
}

napi_status AipNapiUtils::Convert2Value(napi_env env, napi_value in, double &out)
{
    return napi_get_value_double(env, in, &out);
}

bool AipNapiUtils::IsNull(napi_env env, napi_value value)
{
    napi_valuetype type = napi_undefined;
    napi_status status = napi_typeof(env, value, &type);
    return status == napi_ok && (type == napi_undefined || type == napi_null);
}

std::pair<napi_status, napi_value> AipNapiUtils::GetInnerValue(
    napi_env env, napi_value in, const std::string &prop, bool optional)
{
    bool hasProp = false;
    napi_status status = napi_has_named_property(env, in, prop.c_str(), &hasProp);
    if (status != napi_ok) {
        return std::make_pair(napi_generic_failure, nullptr);
    }
    if (!hasProp) {
        status = optional ? napi_ok : napi_generic_failure;
        return std::make_pair(status, nullptr);
    }
    napi_value inner = nullptr;
    status = napi_get_named_property(env, in, prop.c_str(), &inner);
    if (status != napi_ok || inner == nullptr) {
        return std::make_pair(napi_generic_failure, nullptr);
    }
    if (optional && AipNapiUtils::IsNull(env, inner)) {
        return std::make_pair(napi_ok, nullptr);
    }
    return std::make_pair(napi_ok, inner);
}

std::string GetCustomDatabasePath(
    const std::string &rootDir, const std::string &name, const std::string &customDir)
{
    std::string databasePath;
    databasePath.append(rootDir).append(PATH_SPLIT).append(customDir).append(PATH_SPLIT).append(name);
    return databasePath;
}

std::string GetDefaultDatabasePath(
    const std::string &baseDir, const std::string &name, const std::string &customDir)
{
    std::string databaseDir;
    databaseDir.append(baseDir).append("/rdb/").append(customDir).append(PATH_SPLIT).append(name);
    return databaseDir;
}

napi_status AipNapiUtils::Convert2Value(napi_env env, const napi_value &in, napi_value &out)
{
    out = in;
    return napi_ok;
}

napi_status AipNapiUtils::Convert2JSValue(napi_env env, const std::vector<uint8_t> &in, napi_value &out)
{
    void *native = nullptr;
    napi_value buffer = nullptr;
    napi_status status = napi_create_arraybuffer(env, in.size(), &native, &buffer);
    if (status != napi_ok) {
        return status;
    }
    for (size_t i = 0; i < in.size(); i++) {
        *(static_cast<uint8_t *>(native) + i) = in[i];
    }
    status = napi_create_typedarray(env, napi_uint8_array, in.size(), buffer, 0, &out);
    if (status != napi_ok) {
        return status;
    }
    return napi_ok;
}

napi_status AipNapiUtils::Convert2JSValue(napi_env env, const std::vector<float> &in, napi_value &out)
{
    float *native = nullptr;
    napi_value buffer = nullptr;
    napi_status status = napi_create_arraybuffer(env, in.size() * sizeof(float), (void **)&native, &buffer);
    if (status != napi_ok) {
        return status;
    }
    if (native == nullptr) {
        return status;
    }
    for (size_t i = 0; i < in.size(); i++) {
        *(native + i) = in[i];
    }
    status = napi_create_typedarray(env, napi_float32_array, in.size(), buffer, 0, &out);
    if (status != napi_ok) {
        return status;
    }
    return napi_ok;
}

napi_status AipNapiUtils::Convert2JSValue(napi_env env, const std::string &in, napi_value &out)
{
    return napi_create_string_utf8(env, in.c_str(), in.size(), &out);
}

napi_status AipNapiUtils::Convert2JSValue(napi_env env, const double &in, napi_value &out)
{
    return napi_create_double(env, in, &out);
}

napi_status AipNapiUtils::Convert2JSValue(napi_env env, const bool &in, napi_value &out)
{
    return napi_get_boolean(env, in, &out);
}

napi_status AipNapiUtils::Convert2JSValue(napi_env env, const int32_t &in, napi_value &out)
{
    return napi_create_int32(env, in, &out);
}

napi_status AipNapiUtils::Convert2JSValue(napi_env env, const int64_t &in, napi_value &out)
{
    return napi_create_int64(env, in, &out);
}

napi_status AipNapiUtils::Convert2JSValue(napi_env env, const uint64_t &in, napi_value &out)
{
    return napi_create_bigint_uint64(env, in, &out);
}

napi_status AipNapiUtils::Convert2JSValue(napi_env env, const std::map<std::string, double> &in, napi_value &out)
{
    napi_create_object(env, &out);
    for (auto const &[key, value] : in) {
        napi_value jsValue = nullptr;
        Convert2JSValue(env, value, jsValue);
        napi_set_named_property(env, out, key.c_str(), jsValue);
    }
    return napi_ok;
}
} // namespace DataIntelligence
} // namespace OHOS
