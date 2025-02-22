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

#include "i_aip_core_manager.h"
#include "napi/native_api.h"
#include "napi/native_node_api.h"

namespace OHOS {
namespace DataIntelligence {
class AipNapiUtils {
public:
    AipNapiUtils() = default;
    ~AipNapiUtils() = default;

    static bool LoadAlgoLibrary(const std::string &algoPath, AipCoreManagerHandle &aipMgrHandler);
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
    static void SetPropertyName(napi_env env, napi_value targetObj, const char *propName, napi_value propValue);
    static bool CheckModelConfig(napi_env env, napi_value value, uint32_t &length);
};
} // namespace DataIntelligence
} // namespace OHOS
#endif // AIP_NAPI_UTILS_H
