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

#ifndef AIP_NAPI_UTILS_H
#define AIP_NAPI_UTILS_H

#include <type_traits>
#include <variant>

#include "i_aip_core_manager.h"
#include "napi/native_api.h"
#include "napi/native_node_api.h"

namespace OHOS {
namespace DataIntelligence {
class AipNapiUtils {
public:
    AipNapiUtils() = default;
    ~AipNapiUtils() = default;

    static int32_t FindOperaotrEnum(std::string operatorStr);
    static bool LoadAlgoLibrary(const std::string &libraryName, AipCoreManagerHandle &aipMgrHandler, bool isSingleton);
    static bool UnLoadAlgoLibrary(AipCoreManagerHandle &aipMgrHandler);
    static IAipCoreManager *GetAlgoObj(AipCoreManagerHandle &aipMgrHandler);
    static bool ValidateArgsType(napi_env env, napi_value *args, size_t argc,
        const std::vector<std::string> &expectedTypes);
    static bool TransJsToStr(napi_env env, napi_value value, std::string &str);
    static bool TransJsToStrUnlimited(napi_env env, napi_value value, std::string &str);
    static bool TransJsToInt32(napi_env env, napi_value value, int32_t &res);
    static bool TransJsToDouble(napi_env env, napi_value value, double &res);
    static bool TransJsToBool(napi_env env, napi_value value, bool &res);
    static void CreateStringData(napi_env env, napi_value aipServiceValue, napi_value result, const std::string name,
        std::string &content);
    static void CreateInt32Data(napi_env env, napi_value aipServiceValue, napi_value result, const std::string name,
        int32_t value);
    static void CreateDoubleData(napi_env env, double value, napi_value *result);
    static void SetInt32Property(napi_env env, napi_value targetObj, int32_t value, const char *propName);
    static void SetStringProperty(napi_env env, napi_value targetObj, std::string value, const char *propName);
    static void SetPropertyName(napi_env env, napi_value targetObj, const char *propName, napi_value propValue);
    static bool CheckModelConfig(napi_env env, napi_value value);

    static napi_status Convert2Value(napi_env env, napi_value in, bool &out);
    static napi_status Convert2Value(napi_env env, napi_value in, std::vector<uint8_t> &out);
    static napi_status Convert2Value(napi_env env, napi_value in, int32_t &out);
    static napi_status Convert2Value(napi_env env, napi_value in, uint32_t &out);
    static napi_status Convert2Value(napi_env env, napi_value in, int64_t &out);
    static napi_status Convert2Value(napi_env env, napi_value in, float &out);
    static napi_status Convert2Value(napi_env env, napi_value in, double &out);
    static napi_status Convert2Value(napi_env env, napi_value in, std::string &out);
    static napi_status Convert2Value(napi_env env, napi_value in, std::vector<float> &out);

    template <typename T>
    struct is_shared_ptr : std::false_type {};
    template <typename U>
    struct is_shared_ptr<std::shared_ptr<U>> : std::true_type {};

    template<typename T>
    static typename std::enable_if<!is_shared_ptr<T>::value, napi_status>::type
        Convert2Value(napi_env env, napi_value in, T &out);

    template<typename T>
    static typename std::enable_if<is_shared_ptr<T>::value, napi_status>::type
        Convert2Value(napi_env env, napi_value in, T &out)
    {
        return Convert2Value(env, in, *out);
    }

    static bool IsNull(napi_env env, napi_value value);

    static std::pair<napi_status, napi_value> GetInnerValue(napi_env env, napi_value in, const std::string &prop,
        bool optional);

    template<typename T>
    static inline napi_status GetNamedProperty(
        napi_env env, napi_value in, const std::string &prop, T &value, bool optional = false)
    {
        auto [status, jsValue] = GetInnerValue(env, in, prop, optional);
        if (jsValue == nullptr) {
            return status;
        }
        return Convert2Value(env, jsValue, value);
    };

    template<typename T>
    static napi_status Convert2Value(napi_env env, napi_value in, std::vector<T> &out);

    template<typename T>
    static napi_status Convert2Value(napi_env env, napi_value in, std::map<std::string, T> &out);

    template<typename T>
    static napi_status Convert2ValuePtr(napi_env env, napi_value in, std::shared_ptr<T> &out);

    static napi_status Convert2Value(napi_env env, napi_value in, RetrievalConfigStruct &out);
    static napi_status Convert2Value(napi_env env, const napi_value &in, FilterInfoStruct &out);
    static napi_status Convert2Value(napi_env env, const napi_value &in, RecallConditionStruct &out);
    static napi_status Convert2Value(napi_env env, const napi_value &in, InvertedIndexStrategyStruct &out);
    static napi_status Convert2Value(napi_env env, const napi_value &in, Bm25StrategyStruct &out);
    static napi_status Convert2Value(napi_env env, const napi_value &in, ExactMatchingStrategyStruct &out);
    static napi_status Convert2Value(napi_env env, const napi_value &in, OutOfOrderStrategyStruct &out);
    static napi_status Convert2Value(napi_env env, const napi_value &in, InvertedIndexRecallConditionStruct &out);
    static napi_status Convert2Value(napi_env env, const napi_value &in, ChannelRerankParamsStruct &out);
    static napi_status Convert2Value(napi_env env, const napi_value &in, VectorQueryStruct &out);
    static napi_status Convert2Value(napi_env env, const napi_value &in, RerankParamsStruct &out);
    static napi_status Convert2Value(napi_env env, const napi_value &in, RetrievalConditionStruct &out);
    static napi_status Convert2Value(napi_env env, const napi_value &in, VectorChannelRerankParamsStruct &out);
    static napi_status Convert2Value(napi_env env, const napi_value &in, InvertedIndexRerankParamsStruct &out);
    static napi_status Convert2Value(napi_env env, const napi_value &in, RdbConfig &out);
    static napi_status Convert2Value(napi_env env, const napi_value &in, CryptoParam &cryptoParam);
    static napi_status Convert2Value(napi_env env, const napi_value &in, ContextParam &context);
    static napi_status Convert2Value(napi_env env, const napi_value &in, napi_value &out);

    static napi_status Convert2JSValue(napi_env env, const std::vector<uint8_t> &in, napi_value &out);
    static napi_status Convert2JSValue(napi_env env, const std::vector<float> &in, napi_value &out);
    static napi_status Convert2JSValue(napi_env env, const std::string &in, napi_value &out);
    static napi_status Convert2JSValue(napi_env env, const int32_t &in, napi_value &out);
    static napi_status Convert2JSValue(napi_env env, const int64_t &in, napi_value &out);
    static napi_status Convert2JSValue(napi_env env, const uint64_t &in, napi_value &out);
    static napi_status Convert2JSValue(napi_env env, const double &in, napi_value &out);
    static napi_status Convert2JSValue(napi_env env, const bool &in, napi_value &out);
    static napi_status Convert2JSValue(napi_env env, const DataIntelligence::RetrievalResponseStruct &in,
        napi_value &out);
    static napi_status Convert2JSValue(napi_env env, const DataIntelligence::ItemInfoStruct &in, napi_value &out);
    static napi_status Convert2JSValue(napi_env env, const std::map<std::string, FieldType> &in, napi_value &out);
    static napi_status Convert2JSValue(napi_env env,
        const std::map<int32_t, std::map<std::string, RecallScoreStruct>> &in, napi_value &out);
    static napi_status Convert2JSValue(napi_env env, const std::map<std::string, double> &in, napi_value &out);
    template <typename T>
    static napi_status Convert2JSValue(napi_env env, const std::vector<T> &value, napi_value &out);

    template <typename T>
    static napi_status GetJSValue(napi_env env, const T &value, napi_value &out);

    template <typename T, typename First, typename... Types>
    static napi_status GetJSValue(napi_env env, const T &value, napi_value &out);

    template <typename... Types>
    static napi_status Convert2JSValue(napi_env env, const std::variant<Types...> &value, napi_value &out)
    {
        return GetJSValue<decltype(value), Types...>(env, value, out);
    }
};

template<typename T>
napi_status AipNapiUtils::Convert2Value(napi_env env, napi_value jsValue, std::vector<T> &value)
{
    bool isArray = false;
    napi_is_array(env, jsValue, &isArray);
    if (!isArray) {
        return napi_invalid_arg;
    }

    uint32_t arrLen = 0;
    napi_get_array_length(env, jsValue, &arrLen);
    if (arrLen == 0) {
        return napi_ok;
    }

    for (size_t i = 0; i < arrLen; ++i) {
        napi_value element;
        napi_get_element(env, jsValue, i, &element);
        T item;
        auto status = Convert2Value(env, element, item);
        if (status != napi_ok) {
            return napi_invalid_arg;
        }
        value.push_back(std::move(item));
    }
    return napi_ok;
}

template<typename T>
napi_status AipNapiUtils::Convert2Value(napi_env env, napi_value jsValue, std::map<std::string, T> &value)
{
    napi_value jsMapList = nullptr;
    uint32_t jsCount = 0;
    napi_status status = napi_get_property_names(env, jsValue, &jsMapList);
    if (status != napi_ok) {
        return napi_invalid_arg;
    }
    status = napi_get_array_length(env, jsMapList, &jsCount);
    if (status != napi_ok || jsCount <= 0) {
        return napi_invalid_arg;
    }
    napi_value jsKey = nullptr;
    napi_value jsVal = nullptr;
    for (uint32_t index = 0; index < jsCount; index++) {
        status = napi_get_element(env, jsMapList, index, &jsKey);
        if (status != napi_ok) {
            return napi_invalid_arg;
        }
        std::string key;
        int ret = Convert2Value(env, jsKey, key);
        if (ret != napi_ok) {
            return napi_invalid_arg;
        }
        status = napi_get_property(env, jsValue, jsKey, &jsVal);
        if (status != napi_ok || jsVal == nullptr) {
            return napi_invalid_arg;
        }
        T val;
        ret = Convert2Value(env, jsVal, val);
        if (ret != napi_ok) {
            return napi_invalid_arg;
        }
        value.insert(std::pair<std::string, T>(key, val));
    }
    return napi_ok;
}


template <typename T>
napi_status AipNapiUtils::Convert2JSValue(napi_env env, const std::vector<T> &value,
    napi_value &out)
{
    napi_status status = napi_create_array_with_length(env, value.size(), &out);
    if (status != napi_ok) {
        return status;
    }
    for (size_t i = 0; i < value.size(); ++i) {
        napi_value jsValue;
        napi_create_object(env, &jsValue);
        Convert2JSValue(env, value[i], jsValue);
        napi_set_element(env, out, i, jsValue);
    }
    return napi_ok;
}

template <typename T>
napi_status AipNapiUtils::GetJSValue(napi_env env, const T &value, napi_value &out)
{
    return napi_invalid_arg;
}

template <typename T, typename First, typename... Types>
napi_status AipNapiUtils::GetJSValue(napi_env env, const T &value, napi_value &out)
{
    auto *val = std::get_if<First>(&value);
    if (val != nullptr) {
        Convert2JSValue(env, *val, out);
        return napi_ok;
    }
    return GetJSValue<T, Types...>(env, value, out);
}

#define LOG_ERROR_RETURN(condition, message, retVal) \
    do {                                             \
        if (!(condition)) {                          \
            AIP_HILOGE(message);                     \
            return retVal;                           \
        }                                            \
    } while (0)
} // namespace DataIntelligence
} // namespace OHOS
#endif // AIP_NAPI_UTILS_H
