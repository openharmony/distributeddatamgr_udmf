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

#ifndef AIP_NAPI_ERROR_H
#define AIP_NAPI_ERROR_H

#include <map>
#include "napi/native_api.h"
#include "napi/native_node_api.h"

namespace OHOS {
namespace DataIntelligence {
constexpr int32_t PARAM_EXCEPTION{ 401 };
constexpr int32_t DEVICE_EXCEPTION{ 801 };
constexpr int32_t INNER_ERROR{ 31300000 };
const std::map<int32_t, std::string> ERROR_MESSAGES = {
    { PARAM_EXCEPTION, "Params check failed." },
    { DEVICE_EXCEPTION, "The device does not support this API." },
    { INNER_ERROR, "Inner error." },
};

napi_value CreateIntelligenceError(const napi_env &env, int32_t errorCode, const std::string &errorMsg);
std::optional<std::string> GetIntelligenceErrMsg(int32_t errorCode);
void ThrowIntelligenceErr(const napi_env &env, int32_t errorCode, const std::string &printMsg);
void ThrowIntelligenceErrByPromise(const napi_env &env, int32_t errorCode, const std::string &printMsg,
    napi_value &value);
} // namespace DataIntelligence
} // namespae OHOS
#endif // AIP_NAPI_ERROR_H