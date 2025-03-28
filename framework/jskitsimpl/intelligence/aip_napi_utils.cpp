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

#include "js_ability.h"
#include "aip_log.h"
#include "hilog/log_c.h"
#include "js_native_api_types.h"

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
static constexpr int32_t MIN_SECURITY_LEVEL = 1;
static constexpr int32_t MAX_SECURITY_LEVEL = 4;
struct OperatorInfo {
    const char *operatorStr;
    int32_t operatorEnum;
};
constexpr OperatorInfo OPERATOR_INFO [] = {
    { "!=", TsOperator::OP_NE },
    { "<", TsOperator::OP_LT },
    { "<=", TsOperator::OP_LE },
    { "=", TsOperator::OP_EQ },
    { ">", TsOperator::OP_GT },
    { ">=", TsOperator::OP_GE },
    { "BETWEEN", TsOperator::OP_BETWEEN },
    { "IN", TsOperator::OP_IN },
    { "LIKE", TsOperator::OP_LIKE },
    { "NOT_IN", TsOperator::OP_NOT_IN },
    { "NOT_LIKE", TsOperator::OP_NOT_LIKE },
};
} // namespace

int32_t AipNapiUtils::FindOperaotrEnum(std::string operatorStr)
{
    int left = 0;
    int right = sizeof(OPERATOR_INFO) / sizeof(OPERATOR_INFO[0]) - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (OPERATOR_INFO[mid].operatorStr == operatorStr) {
            return OPERATOR_INFO[mid].operatorEnum;
        } else if (OPERATOR_INFO[mid].operatorStr < operatorStr) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return TsOperator::BUTT;
}

bool AipNapiUtils::LoadAlgoLibrary(const std::string &libraryName, AipCoreManagerHandle &aipMgrHandler,
    bool isSingleton)
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

    aipMgrHandler.handle = dlopen(libraryName.c_str(), RTLD_LAZY);
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
    if (isSingleton) {
        aipMgrHandler.pAipManager = aipMgrHandler.create();
    }
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

napi_status AipNapiUtils::Convert2Value(napi_env env, napi_value in, RetrievalConfigStruct &out)
{
    napi_value channelConfigsNapi;
    napi_get_named_property(env, in, "channelConfigs", &channelConfigsNapi);
    std::vector<ChannelConfigStruct> channelConfigs;
    uint32_t arrayLength;
    napi_get_array_length(env, channelConfigsNapi, &arrayLength);
    for (uint32_t i = 0; i < arrayLength; ++i) {
        napi_value channelConfigNapi;
        napi_get_element(env, channelConfigsNapi, i, &channelConfigNapi);
        ChannelConfigStruct channelConfig;
        napi_value channTypeNapi;
        napi_get_named_property(env, channelConfigNapi, "channelType", &channTypeNapi);
        napi_status status = Convert2Value(env, channTypeNapi, channelConfig.channelType);
        LOG_ERROR_RETURN(status == napi_ok, "Failed to convert the field channelType.", napi_invalid_arg);
        LOG_ERROR_RETURN(channelConfig.channelType >= TsChannelType::VECTOR_DATABASE &&
            channelConfig.channelType <= TsChannelType::INVERTED_INDEX_DATABASE,
            "Field channelType illegal.", napi_invalid_arg);
        napi_value dbConfigNapi;
        napi_get_named_property(env, channelConfigNapi, "dbConfig", &dbConfigNapi);
        status = Convert2Value(env, dbConfigNapi, channelConfig.dbConfig);
        LOG_ERROR_RETURN(status == napi_ok, "Failed to convert the field dbConfig.", napi_invalid_arg);
        napi_value contextNapi;
        napi_get_named_property(env, channelConfigNapi, "context", &contextNapi);
        status = Convert2Value(env, contextNapi, channelConfig.context);
        LOG_ERROR_RETURN(status == napi_ok, "Failed to convert the field context.", napi_invalid_arg);
        channelConfigs.push_back(channelConfig);
    }
    out.channelConfigs = channelConfigs;
    return napi_ok;
}

static napi_status ConvertFilterValue(napi_env env, const napi_value &in, std::string &out)
{
    napi_valuetype type = napi_undefined;
    napi_status status = napi_typeof(env, in, &type);
    LOG_ERROR_RETURN((status == napi_ok), "invalid type", status);
    switch (type) {
        case napi_bigint: {
            int64_t valueInt64 = false;
            status = AipNapiUtils::Convert2Value(env, in, valueInt64);
            LOG_ERROR_RETURN((status == napi_ok), "Failed to convert the field filterValue.", status);
            out = std::to_string(valueInt64);
            break;
        }
        case napi_number: {
            double valueDouble;
            status = AipNapiUtils::Convert2Value(env, in, valueDouble);
            LOG_ERROR_RETURN((status == napi_ok), "Failed to convert the field filterValue.", status);
            out = std::to_string(valueDouble);
            break;
        }
        case napi_string: {
            status = AipNapiUtils::Convert2Value(env, in, out);
            LOG_ERROR_RETURN((status == napi_ok), "Failed to convert the field filterValue.", status);
            break;
        }
        default:
            AIP_HILOGE("type is illegal.");
            return napi_invalid_arg;
            break;
    }
    return napi_ok;
}

napi_status ConvertFilterRange(napi_env env, const napi_value &in, FilterInfoStruct &out)
{
    napi_value filterRangeNapi;
    napi_get_named_property(env, in, "filterRange", &filterRangeNapi);
    napi_value filterRangeMin;
    napi_get_named_property(env, filterRangeNapi, "min", &filterRangeMin);
    double min;
    napi_status status = AipNapiUtils::Convert2Value(env, filterRangeMin, min);
    out.range.first = std::to_string(min);
    LOG_ERROR_RETURN(status == napi_ok, "Failed to convert the field min in FilterRange.", napi_invalid_arg);
    napi_value filterRangeMax;
    napi_get_named_property(env, filterRangeNapi, "max", &filterRangeMax);
    double max;
    status = AipNapiUtils::Convert2Value(env, filterRangeMax, max);
    out.range.second = std::to_string(max);
    LOG_ERROR_RETURN(status == napi_ok, "Failed to convert the field max in FilterRange.", napi_invalid_arg);
    return napi_ok;
}

napi_status AipNapiUtils::Convert2Value(napi_env env, const napi_value &in, FilterInfoStruct &out)
{
    napi_value columnsNapi;
    napi_get_named_property(env, in, "columns", &columnsNapi);
    std::vector<std::string> columns;
    napi_status status = Convert2Value(env, columnsNapi, columns);
    LOG_ERROR_RETURN(status == napi_ok, "Failed to convert the field columns.", napi_invalid_arg);
    if (columns.size() == 1) {
        out.field = columns[0];
    } else {
        out.fields = columns;
    }
    bool isOperatorPresent = false;
    napi_has_named_property(env, in, "operator", &isOperatorPresent);
    if (isOperatorPresent) {
        napi_value operatorNapi;
        napi_get_named_property(env, in, "operator", &operatorNapi);
        std::string operatorStr;
        status = Convert2Value(env, operatorNapi, operatorStr);
        LOG_ERROR_RETURN(status == napi_ok, "Failed to convert the field operator.", napi_invalid_arg);
        auto operatorNum = FindOperaotrEnum(operatorStr);
        if (operatorNum != TsOperator::BUTT) {
            out.op = static_cast<TsOperator>(operatorNum);
        } else {
            AIP_HILOGE("Failed to convert the operator to an enum, operator: %{public}s", operatorStr.c_str());
            return napi_invalid_arg;
        }
    }
    bool isFilterValuePresent = false;
    napi_has_named_property(env, in, "filterValue", &isFilterValuePresent);
    if (isFilterValuePresent) {
        napi_value filterValueNapi;
        napi_get_named_property(env, in, "filterValue", &filterValueNapi);
        status = ConvertFilterValue(env, filterValueNapi, out.value);
        LOG_ERROR_RETURN(status == napi_ok, "Failed to convert the field filterValue.", napi_invalid_arg);
    }
    bool isFilterRangePresent = false;
    napi_has_named_property(env, in, "filterRange", &isFilterRangePresent);
    if (isFilterRangePresent) {
        status = ConvertFilterRange(env, in, out);
        LOG_ERROR_RETURN(status == napi_ok, "Failed to convert the field filterRange.", napi_invalid_arg);
    }
    return napi_ok;
}

napi_status AipNapiUtils::Convert2Value(napi_env env, const napi_value &in, RecallConditionStruct &out)
{
    napi_value fromClauseNapi;
    napi_get_named_property(env, in, "fromClause", &fromClauseNapi);
    napi_status status = Convert2Value(env, fromClauseNapi, out.fromClause);
    LOG_ERROR_RETURN(status == napi_ok, "Failed to convert the field fromClause.", napi_invalid_arg);
    LOG_ERROR_RETURN(!out.fromClause.empty(), "Field fromClause can't be empty.", napi_invalid_arg);
    napi_value primaryKeysNapi;
    napi_get_named_property(env, in, "primaryKey", &primaryKeysNapi);
    status = Convert2Value(env, primaryKeysNapi, out.primaryKey);
    LOG_ERROR_RETURN(status == napi_ok, "Failed to convert the field primaryKey.", napi_invalid_arg);
    LOG_ERROR_RETURN(!out.primaryKey.empty(), "Field primaryKey can't be empty.", napi_invalid_arg);
    napi_value responseColumnsNapi;
    napi_get_named_property(env, in, "responseColumns", &responseColumnsNapi);
    status = Convert2Value(env, responseColumnsNapi, out.responseColumns);
    LOG_ERROR_RETURN(status == napi_ok, "Failed to convert the field responseColumns.", napi_invalid_arg);
    LOG_ERROR_RETURN(!out.responseColumns.empty(), "Field responseColumns can't be empty.", napi_invalid_arg);
    bool isRecallNamePresent = false;
    napi_has_named_property(env, in, "recallName", &isRecallNamePresent);
    if (isRecallNamePresent) {
        napi_value recallNameNapi;
        napi_get_named_property(env, in, "recallName", &recallNameNapi);
        status = Convert2Value(env, recallNameNapi, out.recallName);
        LOG_ERROR_RETURN(status == napi_ok, "Failed to convert the field recallName.", napi_invalid_arg);
    }
    bool isDeepSizePresent = false;
    napi_has_named_property(env, in, "deepSize", &isDeepSizePresent);
    if (isDeepSizePresent) {
        napi_value deepSizeNapi;
        napi_get_named_property(env, in, "deepSize", &deepSizeNapi);
        status = Convert2Value(env, deepSizeNapi, out.deepSize);
        LOG_ERROR_RETURN(status == napi_ok, "Failed to convert the field deepSize.", napi_invalid_arg);
    }
    bool isFiltersPresent = false;
    napi_has_named_property(env, in, "filters", &isFiltersPresent);
    if (isFiltersPresent) {
        napi_value filtersNapi;
        napi_get_named_property(env, in, "filters", &filtersNapi);
        napi_status status = AipNapiUtils::Convert2Value(env, filtersNapi, out.filters);
        LOG_ERROR_RETURN(status == napi_ok, "Failed to convert the field filter.", napi_invalid_arg);
    }
    return napi_ok;
}

napi_status AipNapiUtils::Convert2Value(napi_env env, const napi_value &in, InvertedIndexStrategyStruct &out)
{
    bool isColumnWeightPresent = false;
    napi_has_named_property(env, in, "columnWeight", &isColumnWeightPresent);
    if (isColumnWeightPresent) {
        napi_value columnWeightNapi;
        napi_get_named_property(env, in, "columnWeight", &columnWeightNapi);
        napi_status status = Convert2Value(env, columnWeightNapi, out.fieldWeight);
        LOG_ERROR_RETURN(status == napi_ok, "Failed to convert the field columnWeight.", napi_invalid_arg);
    }
    return napi_ok;
}

napi_status AipNapiUtils::Convert2Value(napi_env env, const napi_value &in, Bm25StrategyStruct &out)
{
    napi_value bm25WeightNapi;
    napi_get_named_property(env, in, "bm25Weight", &bm25WeightNapi);
    napi_status status = Convert2Value(env, bm25WeightNapi, out.bm25Weight);
    LOG_ERROR_RETURN(status == napi_ok, "Failed to convert the field bm25Weight.", napi_invalid_arg);
    LOG_ERROR_RETURN(out.bm25Weight >= 0, "Field bm25Weight has an illegal value.", napi_invalid_arg);
    return napi_ok;
}

napi_status AipNapiUtils::Convert2Value(napi_env env, const napi_value &in, ExactMatchingStrategyStruct &out)
{
    napi_value exactMatchingWeightNapi;
    napi_get_named_property(env, in, "exactMatchingWeight", &exactMatchingWeightNapi);
    napi_status status = Convert2Value(env, exactMatchingWeightNapi, out.exactMatchingWeight);
    LOG_ERROR_RETURN(status == napi_ok, "Failed to convert the field exactMatchingWeight.", napi_invalid_arg);
    LOG_ERROR_RETURN(out.exactMatchingWeight >= 0, "Field exactMatchingWeight has an illegal value.",
        napi_invalid_arg);
    return napi_ok;
}

napi_status AipNapiUtils::Convert2Value(napi_env env, const napi_value &in, OutOfOrderStrategyStruct &out)
{
    napi_value proximityWeightNapi;
    napi_get_named_property(env, in, "proximityWeight", &proximityWeightNapi);
    napi_status status = Convert2Value(env, proximityWeightNapi, out.outOfOrderWeight);
    LOG_ERROR_RETURN(status == napi_ok, "convert field proximityWeight failed.", napi_invalid_arg);
    LOG_ERROR_RETURN(out.outOfOrderWeight >= 0, "field proximityWeight value illegal.",
        napi_invalid_arg);
    bool isColumnSlopsPresent = false;
    status = napi_has_named_property(env, in, "columnSlops", &isColumnSlopsPresent);
    if (isColumnSlopsPresent) {
        napi_value columnSlopsNapi;
        napi_get_named_property(env, in, "columnSlops", &columnSlopsNapi);
        status = Convert2Value(env, columnSlopsNapi, out.fieldSlops);
        LOG_ERROR_RETURN(status == napi_ok, "convert field columnSlops failed.", napi_invalid_arg);
    }
    return napi_ok;
}

static napi_status ConvertInvIdxStrategySubClass(napi_env env, const napi_value &in, int index,
    std::shared_ptr<InvertedIndexStrategyStruct> &out)
{
    napi_value invertedIndexStrategyNapi;
    napi_get_element(env, in, index, &invertedIndexStrategyNapi);
    bool isBm25WeightPresent = false;
    bool isExactMatchingWeightPresent = false;
    bool isProximityWeightPresent = false;
    napi_has_named_property(env, invertedIndexStrategyNapi, "bm25Weight", &isBm25WeightPresent);
    napi_has_named_property(env, invertedIndexStrategyNapi, "exactMatchingWeight", &isExactMatchingWeightPresent);
    napi_has_named_property(env, invertedIndexStrategyNapi, "proximityWeight", &isProximityWeightPresent);
    napi_status status;
    if (isBm25WeightPresent) {
        std::shared_ptr<Bm25StrategyStruct> strategyStruct =
            std::make_shared<Bm25StrategyStruct>();
        status = AipNapiUtils::Convert2Value(env, invertedIndexStrategyNapi, strategyStruct);
        LOG_ERROR_RETURN(status == napi_ok, "Failed to convert the field Bm25Strategy.", napi_invalid_arg);
        out = strategyStruct;
    } else if (isExactMatchingWeightPresent) {
        std::shared_ptr<ExactMatchingStrategyStruct> strategyStruct =
            std::make_shared<ExactMatchingStrategyStruct>();
        status = AipNapiUtils::Convert2Value(env, invertedIndexStrategyNapi, strategyStruct);
        LOG_ERROR_RETURN(status == napi_ok, "Failed to convert the field ExactMatchingStrategy.", napi_invalid_arg);
        out = strategyStruct;
    } else if (isProximityWeightPresent) {
        std::shared_ptr<OutOfOrderStrategyStruct> strategyStruct =
            std::make_shared<OutOfOrderStrategyStruct>();
        status = AipNapiUtils::Convert2Value(env, invertedIndexStrategyNapi, strategyStruct);
        LOG_ERROR_RETURN(status == napi_ok, "Failed to convert the field OutOfOrderStrategy.", napi_invalid_arg);
        out = strategyStruct;
    }
    status = AipNapiUtils::Convert2Value(env, invertedIndexStrategyNapi, out);
    LOG_ERROR_RETURN(status == napi_ok, "Failed to convert the InvertedIndexStrategyStruct.", napi_invalid_arg);
    return napi_ok;
}

napi_status AipNapiUtils::Convert2Value(napi_env env, const napi_value &in, InvertedIndexRecallConditionStruct &out)
{
    napi_value ftsTableNameNapi;
    napi_get_named_property(env, in, "ftsTableName", &ftsTableNameNapi);
    napi_status status = Convert2Value(env, ftsTableNameNapi, out.ftsTableName);
    LOG_ERROR_RETURN(status == napi_ok, "Failed to convert the field ftsTableName.", napi_invalid_arg);
    LOG_ERROR_RETURN(!out.ftsTableName.empty(), "The field named ftsTableName is empty.", napi_invalid_arg);
    bool isStrategyPresent = false;
    napi_has_named_property(env, in, "invertedIndexStrategies", &isStrategyPresent);
    if (!isStrategyPresent) {
        return napi_ok;
    }
    napi_value invertedIndexStrategiesNapi;
    napi_get_named_property(env, in, "invertedIndexStrategies", &invertedIndexStrategiesNapi);
    uint32_t arrayLength = 0;
    napi_get_array_length(env, invertedIndexStrategiesNapi, &arrayLength);
    std::vector<std::shared_ptr<InvertedIndexStrategyStruct>> invertedIndexStrategies;
    for (uint32_t i = 0; i < arrayLength; ++i) {
        std::shared_ptr<InvertedIndexStrategyStruct> invertedIndexStrategyStruct;
        status = ConvertInvIdxStrategySubClass(env, invertedIndexStrategiesNapi, i, invertedIndexStrategyStruct);
        LOG_ERROR_RETURN(status == napi_ok, "Failed to convert the InvertedIndexStrategy.", napi_invalid_arg);
        invertedIndexStrategies.push_back(invertedIndexStrategyStruct);
    }
    out.invertedIndexStrategies = invertedIndexStrategies;
    return napi_ok;
}

napi_status AipNapiUtils::Convert2Value(napi_env env, const napi_value &in, VectorChannelRerankParamsStruct &out)
{
    napi_value vectorWeightsNapi;
    napi_get_named_property(env, in, "vectorWeights", &vectorWeightsNapi);
    napi_status status = Convert2Value(env, vectorWeightsNapi, out.recallWeights);
    LOG_ERROR_RETURN(status == napi_ok, "Failed to convert the field vectorWeights.", napi_invalid_arg);
    bool isThresholdsPresent = false;
    napi_has_named_property(env, in, "thresholds", &isThresholdsPresent);
    if (isThresholdsPresent) {
        napi_value thresholdsNapi;
        napi_get_named_property(env, in, "thresholds", &thresholdsNapi);
        status = Convert2Value(env, thresholdsNapi, out.rankLevelThresholds);
        LOG_ERROR_RETURN(status == napi_ok, "convert field thresholds failed.", napi_invalid_arg);
    }
    bool isNumberInspectorPresent = false;
    napi_has_named_property(env, in, "numberInspector", &isNumberInspectorPresent);
    if (isNumberInspectorPresent) {
        napi_value numberInspectorNapi;
        napi_get_named_property(env, in, "numberInspector", &numberInspectorNapi);
        status = Convert2Value(env, numberInspectorNapi, out.numberFilterCheckFields);
        LOG_ERROR_RETURN(status == napi_ok, "Failed to convert the field numberInspector.", napi_invalid_arg);
    }
    return napi_ok;
}

napi_status AipNapiUtils::Convert2Value(napi_env env, const napi_value &in, InvertedIndexRerankParamsStruct &out)
{
    napi_value invertedIndexWeightsNapi;
    napi_get_named_property(env, in, "invertedIndexWeights", &invertedIndexWeightsNapi);
    napi_status status = Convert2Value(env, invertedIndexWeightsNapi, out.recallWeights);
    LOG_ERROR_RETURN(status == napi_ok, "Failed to convert the field invertedIndexWeights.", napi_invalid_arg);
    return napi_ok;
}

static napi_status ConvertRerankChannelParams(napi_env env, const napi_value &in, RerankParamsStruct &out)
{
    napi_value parametersNapi;
    napi_get_named_property(env, in, "parameters", &parametersNapi);
    napi_value keysNapi;
    napi_get_property_names(env, parametersNapi, &keysNapi);
    uint32_t keysLength;
    napi_get_array_length(env, keysNapi, &keysLength);
    napi_status status;
    std::map<int32_t, std::shared_ptr<ChannelRerankParamsStruct>> channelParameters;
    for (uint32_t i = 0; i < keysLength; ++i) {
        napi_value keyNapi;
        napi_get_element(env, keysNapi, i, &keyNapi);
        std::string keyStr;
        status = AipNapiUtils::Convert2Value(env, keyNapi, keyStr);
        LOG_ERROR_RETURN(status == napi_ok, "Failed to convert the channelType in parameters.", napi_invalid_arg);
        int32_t keyInt = std::stoi(keyStr);
        LOG_ERROR_RETURN(keyInt >= TsChannelType::VECTOR_DATABASE && keyInt <= TsChannelType::INVERTED_INDEX_DATABASE,
            "channelType is ileagl.", napi_invalid_arg);
        napi_value valueNapi;
        napi_get_property(env, parametersNapi, keyNapi, &valueNapi);
        std::shared_ptr<ChannelRerankParamsStruct> channelParams;
        bool isVectorWeightsPresent = false;
        napi_has_named_property(env, valueNapi, "vectorWeights", &isVectorWeightsPresent);
        if (isVectorWeightsPresent) {
            std::shared_ptr<VectorChannelRerankParamsStruct> vectorRerankParam =
                std::make_shared<VectorChannelRerankParamsStruct>();
            status = AipNapiUtils::Convert2Value(env, valueNapi, vectorRerankParam);
            LOG_ERROR_RETURN(status == napi_ok, "Failed to convert the VectorChannelRerankParams.", status);
            channelParameters[keyInt] = vectorRerankParam;
        } else {
            std::shared_ptr<InvertedIndexRerankParamsStruct> invIdxRerankParam =
                std::make_shared<InvertedIndexRerankParamsStruct>();
            status = AipNapiUtils::Convert2Value(env, valueNapi, invIdxRerankParam);
            LOG_ERROR_RETURN(status == napi_ok, "Failed to convert the InvertedIndexRerankParams.", status);
            channelParameters[keyInt] = invIdxRerankParam;
        }
    }
    out.channelParams = channelParameters;
    return napi_ok;
}

napi_status AipNapiUtils::Convert2Value(napi_env env, const napi_value &in, RerankParamsStruct &out)
{
    napi_value rankTypeNapi;
    napi_get_named_property(env, in, "rerankType", &rankTypeNapi);
    napi_status status = Convert2Value(env, rankTypeNapi, out.rankType);
    LOG_ERROR_RETURN(status == napi_ok, "Failed to convert the field rerankType.", napi_invalid_arg);
    LOG_ERROR_RETURN(out.rankType >= TsRerankType::RRF && out.rankType <= TsRerankType::FUSION_SCORE,
        "The field rankType is illegal. Please check its value..", napi_invalid_arg);

    bool isIsSoftmaxPresent = false;
    napi_has_named_property(env, in, "isSoftmaxNormalized", &isIsSoftmaxPresent);
    if (isIsSoftmaxPresent) {
        napi_value isSoftmaxNormalizedNapi;
        napi_get_named_property(env, in, "isSoftmaxNormalized", &isSoftmaxNormalizedNapi);
        status = Convert2Value(env, isSoftmaxNormalizedNapi, out.useScoreSoftmax);
        LOG_ERROR_RETURN(status == napi_ok, "Failed to convert the field isSoftmaxNormalized.", napi_invalid_arg);
    }
    bool isParametersPresent = false;
    napi_has_named_property(env, in, "parameters", &isParametersPresent);
    if (isParametersPresent) {
        status = ConvertRerankChannelParams(env, in, out);
        LOG_ERROR_RETURN(status == napi_ok, "Failed to convert the field parameters", napi_invalid_arg);
    }
    return napi_ok;
}

napi_status AipNapiUtils::Convert2Value(napi_env env, const napi_value &in, VectorQueryStruct &out)
{
    napi_value columnNapi;
    napi_get_named_property(env, in, "column", &columnNapi);
    napi_status status = Convert2Value(env, columnNapi, out.vectorColumn);
    LOG_ERROR_RETURN(status == napi_ok, "Failed to convert the field column.", napi_invalid_arg);
    LOG_ERROR_RETURN(!out.vectorColumn.empty(), "Field column cannot be empty.", napi_invalid_arg);
    napi_value valueNapi;
    napi_get_named_property(env, in, "value", &valueNapi);
    status = Convert2Value(env, valueNapi, out.vectorValue);
    LOG_ERROR_RETURN(status == napi_ok, "Failed to convert the field value.", napi_invalid_arg);
    bool isThresholdPresent = false;
    napi_has_named_property(env, in, "similarityThreshold", &isThresholdPresent);
    if (isThresholdPresent) {
        napi_value similarityThresholdNapi;
        napi_get_named_property(env, in, "similarityThreshold", &similarityThresholdNapi);
        status = Convert2Value(env, similarityThresholdNapi, out.similarityThreshold);
        LOG_ERROR_RETURN(status == napi_ok, "Failed to convert the field similarityThreshold.", napi_invalid_arg);
    }
    return napi_ok;
}

static napi_status ConvertRecallConditionSubClass(napi_env env, const napi_value &in, int index,
    std::shared_ptr<RecallConditionStruct> &out)
{
    napi_value recallConditionNapi;
    napi_get_element(env, in, index, &recallConditionNapi);
    bool isFtsTableNamePresent = false;
    bool isQueryPresent = false;
    napi_has_named_property(env, recallConditionNapi, "ftsTableName", &isFtsTableNamePresent);
    napi_has_named_property(env, recallConditionNapi, "query", &isQueryPresent);
    napi_status status;
    if (isFtsTableNamePresent) {
        std::shared_ptr<InvertedIndexRecallConditionStruct> recallConditionPtr =
            std::make_shared<InvertedIndexRecallConditionStruct>();
        status = AipNapiUtils::Convert2Value(env, recallConditionNapi, recallConditionPtr);
        LOG_ERROR_RETURN(status == napi_ok, "Failed to convert InvertedIndexRecallCondition.", napi_invalid_arg);
        out = recallConditionPtr;
    } else if (isQueryPresent) {
        std::shared_ptr<VectorRecallConditionStruct> recallConditionPtr =
            std::make_shared<VectorRecallConditionStruct>();
        napi_value vecotrQueryNapi;
        napi_get_named_property(env, recallConditionNapi, "query", &vecotrQueryNapi);
        VectorQueryStruct vecotrQuery;
        status = AipNapiUtils::Convert2Value(env, vecotrQueryNapi, vecotrQuery);
        LOG_ERROR_RETURN(status == napi_ok, "Failed to convert field vectorQuery.", napi_invalid_arg);
        recallConditionPtr->vectorQuery = vecotrQuery;
        out = recallConditionPtr;
    }
    status = AipNapiUtils::Convert2Value(env, recallConditionNapi, out);
    LOG_ERROR_RETURN(status == napi_ok, "Failed to convert the field recallCondition.", napi_invalid_arg);
    return napi_ok;
}

napi_status AipNapiUtils::Convert2Value(napi_env env, const napi_value &in, RetrievalConditionStruct &out)
{
    napi_value queryNapi;
    napi_get_named_property(env, in, "query", &queryNapi);
    napi_status status = Convert2Value(env, queryNapi, out.query);
    LOG_ERROR_RETURN(status == napi_ok, "Failed to convert the field query.", napi_invalid_arg);

    bool isResultCountPresent = false;
    napi_has_named_property(env, in, "resultCount", &isResultCountPresent);
    if (isResultCountPresent) {
        napi_value resultCountNapi;
        napi_get_named_property(env, in, "resultCount", &resultCountNapi);
        status = Convert2Value(env, resultCountNapi, out.topN);
        LOG_ERROR_RETURN(status == napi_ok, "Failed to convert the field resultCount.", napi_invalid_arg);
    }

    napi_value recallConditionsNapi;
    napi_get_named_property(env, in, "recallConditions", &recallConditionsNapi);
    uint32_t arrayLength = 0;
    napi_get_array_length(env, recallConditionsNapi, &arrayLength);
    LOG_ERROR_RETURN(arrayLength > 0, "Field recallConditions in RetrievalCondition has a length of zero.",
        napi_invalid_arg);
    std::vector<std::shared_ptr<RecallConditionStruct>> recallConditions;
    for (uint32_t i = 0; i < arrayLength; ++i) {
        std::shared_ptr<RecallConditionStruct> recallCondition;
        status = ConvertRecallConditionSubClass(env, recallConditionsNapi, i, recallCondition);
        LOG_ERROR_RETURN(status == napi_ok, "Failed to convert the RecallCondition.", napi_invalid_arg);
        recallConditions.push_back(recallCondition);
    }
    out.recallConditions = recallConditions;
    bool isRerankMethodPresent = false;
    napi_has_named_property(env, in, "rerankMethod", &isRerankMethodPresent);
    if (isRerankMethodPresent) {
        RerankParamsStruct rerankParamsStruct;
        napi_value rerankMethodNapi;
        napi_get_named_property(env, in, "rerankMethod", &rerankMethodNapi);
        status = Convert2Value(env, rerankMethodNapi, rerankParamsStruct);
        LOG_ERROR_RETURN(status == napi_ok, "Failed to convert the field rerankParamsStruct.", napi_invalid_arg);
        out.rerankParameter = rerankParamsStruct;
    }
    return napi_ok;
}

napi_status GetCurrentAbilityParam(napi_env env, napi_value in, ContextParam &param)
{
    std::shared_ptr<Context> context = JSAbility::GetCurrentAbility(env, in);
    if (context == nullptr) {
        return napi_invalid_arg;
    }
    param.baseDir = context->GetDatabaseDir();
    param.moduleName = context->GetModuleName();
    param.area = context->GetArea();
    param.bundleName = context->GetBundleName();
    param.isSystemApp = context->IsSystemAppCalled();
    return napi_ok;
}

napi_status AipNapiUtils::Convert2Value(napi_env env, const napi_value &in, ContextParam &context)
{
    if (in == nullptr) {
        AIP_HILOGI("hasProp is false -> fa stage");
        context.isStageMode = false;
        return GetCurrentAbilityParam(env, in, context);
    }

    int32_t status = GetNamedProperty(env, in, "stageMode", context.isStageMode);
    LOG_ERROR_RETURN(status == napi_ok, "get stageMode param failed", napi_invalid_arg);
    if (!context.isStageMode) {
        AIP_HILOGW("isStageMode is false -> fa stage");
        return GetCurrentAbilityParam(env, in, context);
    }
    AIP_HILOGD("Stage mode branch");
    status = GetNamedProperty(env, in, "databaseDir", context.baseDir);
    LOG_ERROR_RETURN(status == napi_ok, "get databaseDir failed.", napi_invalid_arg);
    status = GetNamedProperty(env, in, "area", context.area, true);
    LOG_ERROR_RETURN(status == napi_ok, "get area failed.", napi_invalid_arg);

    napi_value hapInfo = nullptr;
    GetNamedProperty(env, in, "currentHapModuleInfo", hapInfo);
    if (hapInfo != nullptr) {
        status = GetNamedProperty(env, hapInfo, "name", context.moduleName);
        LOG_ERROR_RETURN(status == napi_ok, "get currentHapModuleInfo.name failed.", napi_invalid_arg);
    }

    napi_value appInfo = nullptr;
    GetNamedProperty(env, in, "applicationInfo", appInfo);
    if (appInfo != nullptr) {
        status = GetNamedProperty(env, appInfo, "name", context.bundleName);
        LOG_ERROR_RETURN(status == napi_ok, "get applicationInfo.name failed.", napi_invalid_arg);
        status = GetNamedProperty(env, appInfo, "systemApp", context.isSystemApp, true);
        LOG_ERROR_RETURN(status == napi_ok, "get applicationInfo.systemApp failed.", napi_invalid_arg);
    }
    return napi_ok;
}

napi_status AipNapiUtils::Convert2Value(napi_env env, const napi_value &in, RdbConfig &out)
{
    int32_t status = GetNamedProperty(env, in, "encrypt", out.isEncrypt, true);
    LOG_ERROR_RETURN(status == napi_ok, "get encrypt failed.", napi_invalid_arg);

    status = GetNamedProperty(env, in, "securityLevel", out.securityLevel);
    LOG_ERROR_RETURN(status == napi_ok, "get securityLevel failed.", napi_invalid_arg);
    LOG_ERROR_RETURN(out.securityLevel > MIN_SECURITY_LEVEL && out.securityLevel < MAX_SECURITY_LEVEL,
        "securityLevel is invalid.", napi_invalid_arg);

    status = GetNamedProperty(env, in, "dataGroupId", out.dataGroupId, true);
    LOG_ERROR_RETURN(status == napi_ok, "get dataGroupId failed.", napi_invalid_arg);

    status = GetNamedProperty(env, in, "autoCleanDirtyData", out.isAutoClean, true);
    LOG_ERROR_RETURN(status == napi_ok, "get autoCleanDirtyData failed.", napi_invalid_arg);

    status = GetNamedProperty(env, in, "name", out.name);
    LOG_ERROR_RETURN(status == napi_ok, "get name failed.", napi_invalid_arg);

    status = GetNamedProperty(env, in, "customDir", out.customDir, true);
    LOG_ERROR_RETURN(status == napi_ok, "get customDir failed.", napi_invalid_arg);

    status = GetNamedProperty(env, in, "rootDir", out.rootDir, true);
    LOG_ERROR_RETURN(status == napi_ok, "get rootDir failed.", napi_invalid_arg);

    GetNamedProperty(env, in, "isSearchable", out.isSearchable, true);
    LOG_ERROR_RETURN(status == napi_ok, "get isSearchable failed.", napi_invalid_arg);

    GetNamedProperty(env, in, "vector", out.vector, true);
    LOG_ERROR_RETURN(status == napi_ok, "get vector failed.", napi_invalid_arg);

    GetNamedProperty(env, in, "allowRebuild", out.allowRebuild, true);
    LOG_ERROR_RETURN(status == napi_ok, "get allowRebuild failed.", napi_invalid_arg);

    GetNamedProperty(env, in, "isReadOnly", out.isReadOnly, true);
    LOG_ERROR_RETURN(status == napi_ok, "get isReadOnly failed.", napi_invalid_arg);

    GetNamedProperty(env, in, "pluginLibs", out.pluginLibs, true);
    LOG_ERROR_RETURN(status == napi_ok, "get pluginLibs failed.", napi_invalid_arg);

    status = GetNamedProperty(env, in, "haMode", out.haMode, true);
    LOG_ERROR_RETURN(status == napi_ok, "get haMode failed.", napi_invalid_arg);

    status = GetNamedProperty(env, in, "cryptoParam", out.cryptoParam, true);
    LOG_ERROR_RETURN(status == napi_ok, "get cryptoParam failed.", napi_invalid_arg);

    status = GetNamedProperty(env, in, "tokenizer", out.tokenizer, true);
    LOG_ERROR_RETURN(status == napi_ok, "get tokenizer failed.", napi_invalid_arg);
    return napi_ok;
}

napi_status AipNapiUtils::Convert2Value(napi_env env, const napi_value &in, CryptoParam &cryptoParam)
{
    napi_valuetype type = napi_undefined;
    napi_status status = napi_typeof(env, in, &type);
    LOG_ERROR_RETURN(status == napi_ok && type == napi_object, "napi_typeof failed.", napi_invalid_arg);
    status = GetNamedProperty(env, in, "encryptionKey", cryptoParam.encryptKey_);
    LOG_ERROR_RETURN(status == napi_ok, "get encryptionKey failed.", napi_invalid_arg);
    status = GetNamedProperty(env, in, "iterationCount", cryptoParam.iterNum);
    LOG_ERROR_RETURN(status == napi_ok, "get iterationCount failed.", napi_invalid_arg);
    status = GetNamedProperty(env, in, "encryptionAlgo", cryptoParam.encryptAlgo);
    LOG_ERROR_RETURN(status == napi_ok, "get encryptionAlgo failed.", napi_invalid_arg);
    status = GetNamedProperty(env, in, "hmacAlgo", cryptoParam.hmacAlgo);
    LOG_ERROR_RETURN(status == napi_ok, "get hmacAlgo failed.", napi_invalid_arg);
    status = GetNamedProperty(env, in, "kdfAlgo", cryptoParam.kdfAlgo);
    LOG_ERROR_RETURN(status == napi_ok, "get kdfAlgo failed.", napi_invalid_arg);
    status = GetNamedProperty(env, in, "cryptoPageSize", cryptoParam.cryptoPageSize);
    LOG_ERROR_RETURN(status == napi_ok, "get cryptoPageSize failed.", napi_invalid_arg);
    return napi_ok;
}

napi_status AipNapiUtils::Convert2Value(napi_env env, napi_value in, napi_value &out)
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

napi_status AipNapiUtils::Convert2JSValue(napi_env env, const DataIntelligence::RetrievalResponseStruct &in,
    napi_value &out)
{
    napi_create_object(env, &out);
    auto items = in.retrievalResults;
    napi_value values = nullptr;
    Convert2JSValue(env, items, values);
    napi_set_named_property(env, out, "records", values);
    return napi_ok;
}

napi_status AipNapiUtils::Convert2JSValue(napi_env env, const DataIntelligence::ItemInfoStruct &in, napi_value &out)
{
    napi_value jsPrimaryKey = nullptr;
    Convert2JSValue(env, in.primaryKey, jsPrimaryKey);
    napi_set_named_property(env, out, "primaryKey", jsPrimaryKey);

    napi_value jsScore = nullptr;
    Convert2JSValue(env, in.score, jsScore);
    napi_set_named_property(env, out, "score", jsScore);

    napi_value jsFields = nullptr;
    Convert2JSValue(env, in.fields, jsFields);
    napi_set_named_property(env, out, "columns", jsFields);

    napi_value jsRecallScores = nullptr;
    Convert2JSValue(env, in.recallScores, jsRecallScores);
    napi_set_named_property(env, out, "recallScores", jsRecallScores);

    napi_value jsFeatures = nullptr;
    Convert2JSValue(env, in.features, jsFeatures);
    napi_set_named_property(env, out, "features", jsFeatures);

    napi_value jsSimilarityLevel = nullptr;
    Convert2JSValue(env, in.similarityLevel, jsSimilarityLevel);
    napi_set_named_property(env, out, "similarityLevel", jsSimilarityLevel);

    return napi_ok;
}

napi_status AipNapiUtils::Convert2JSValue(napi_env env, const std::map<std::string, FieldType> &in, napi_value &out)
{
    napi_create_object(env, &out);
    for (auto const &[key, value] : in) {
        napi_value jsValue = nullptr;
        Convert2JSValue(env, value, jsValue);
        napi_set_named_property(env, out, key.c_str(), jsValue);
    }
    return napi_ok;
}

napi_status AipNapiUtils::Convert2JSValue(napi_env env,
    const std::map<int32_t, std::map<std::string, RecallScoreStruct>> &in, napi_value &out)
{
    napi_create_object(env, &out);
    for (auto const &[key, values] : in) {
        napi_value jsValues = nullptr;
        napi_create_object(env, &jsValues);
        for (auto const &[innerKey, value] : values) {
            napi_value jsValue = nullptr;
            napi_create_object(env, &jsValue);

            napi_value jsRecallScore = nullptr;
            Convert2JSValue(env, value.recallScore, jsRecallScore);
            napi_set_named_property(env, jsValue, "recallScore", jsRecallScore);

            napi_value jsReverseQuery = nullptr;
            Convert2JSValue(env, value.isOriginal, jsReverseQuery);
            napi_set_named_property(env, jsValue, "isReverseQuery", jsReverseQuery);

            napi_set_named_property(env, jsValues, innerKey.c_str(), jsValue);
        }
        napi_value jsKey = nullptr;
        Convert2JSValue(env, key, jsKey);
        napi_set_property(env, out, jsKey, jsValues);
    }
    return napi_ok;
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
