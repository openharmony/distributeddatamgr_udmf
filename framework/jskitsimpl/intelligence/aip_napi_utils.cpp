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

#include "aip_log.h"

#undef LOG_TAG
#define LOG_TAG "AipNapiUtils"

namespace OHOS {
namespace DataIntelligence {
namespace {
static constexpr uint32_t MAX_STR_PARAM_LEN = 512;
} // namespace
bool AipNapiUtils::LoadAlgoLibrary(const std::string &algoPath, AipCoreManagerHandle &aipMgrHandler)
{
    AIP_HILOGD("Enter");
    if (aipMgrHandler.handle != nullptr) {
        AIP_HILOGE("handle has exists");
        return false;
    }

    if (algoPath.empty()) {
        AIP_HILOGE("algoPath is empty");
        return false;
    }
    char libRealPath[PATH_MAX] = {};
    if (realpath(algoPath.c_str(), libRealPath) == nullptr) {
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
    if (strlen < 0 || strlen > MAX_STR_PARAM_LEN) {
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
    if (strlen < 0) {
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
} // namespace DataIntelligence
} // namespace OHOS
