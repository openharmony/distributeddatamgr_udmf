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

#include "aip_napi_error.h"

#include <optional>

#include "aip_log.h"

#undef LOG_TAG
#define LOG_TAG "AipNapiError"

namespace OHOS {
namespace DataIntelligence {
napi_value CreateIntelligenceError(const napi_env &env, int32_t errorCode, const std::string &errorMsg)
{
    napi_value businessError = nullptr;
    napi_value code = nullptr;
    napi_value msg = nullptr;
    NAPI_CALL(env, napi_create_int32(env, errorCode, &code));
    NAPI_CALL(env, napi_create_string_utf8(env, errorMsg.c_str(), NAPI_AUTO_LENGTH, &msg));
    napi_create_error(env, nullptr, msg, &businessError);
    napi_set_named_property(env, businessError, "code", code);
    return businessError;
}

std::optional<std::string> GetIntelligenceErrMsg(int32_t errorCode)
{
    auto iter = ERROR_MESSAGES.find(errorCode);
    if (iter != ERROR_MESSAGES.end()) {
        return iter->second;
    }
    AIP_HILOGE("Error, messages not found");
    return std::nullopt;
}

void ThrowIntelligenceErr(const napi_env &env, int32_t errorCode, const std::string &printMsg)
{
    AIP_HILOGE("printMsg:%{public}s, errorCode:%{public}d", printMsg.c_str(), errorCode);
    std::optional<std::string> msg = GetIntelligenceErrMsg(errorCode);
    if (!msg) {
        AIP_HILOGE("errorCode:%{public}d is invalid", errorCode);
        return;
    }
    napi_value error = CreateIntelligenceError(env, errorCode, msg.value());
    napi_throw(env, error);
}

void ThrowIntelligenceErrByPromise(const napi_env &env, int32_t errorCode, const std::string &printMsg,
    napi_value &value)
{
    AIP_HILOGE("printMsg:%{public}s, errorCode:%{public}d", printMsg.c_str(), errorCode);
    std::optional<std::string> msg = GetIntelligenceErrMsg(errorCode);
    if (!msg) {
        AIP_HILOGE("errorCode:%{public}d is invalid", errorCode);
        return;
    }
    value = CreateIntelligenceError(env, errorCode, msg.value());
}
} // namespace DataIntelligence
} // namespae OHOS