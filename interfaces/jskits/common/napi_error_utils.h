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

#ifndef UDMF_ERROR_UTILS_H
#define UDMF_ERROR_UTILS_H

#include <map>
#include <optional>
#include <string>

#include "js_native_api.h"
#include "napi/native_common.h"

#include "error_code.h"
#include "logger.h"


namespace OHOS {
namespace UDMF {
struct NapiErrorCode {
    int32_t status;
    int32_t jsCode;
    const char *message;
};

const std::optional<NapiErrorCode> GetErrorCode(int32_t errorCode);
Status GenerateNapiError(Status error, int32_t &errCode, std::string &errMessage);
void ThrowNapiError(napi_env env, int32_t errCode, const std::string &errMessage, bool isParamsCheck = true);
napi_value GenerateErrorMsg(napi_env env, NapiErrorCode jsInfo);

#define ASSERT_ERR(env, assertion, errorcode, message) \
    do {                                               \
        if (!(assertion)) {                            \
            ThrowNapiError(env, errorcode, message);   \
            return nullptr;                            \
        }                                              \
    } while (0)

#define ASSERT_ERR_VOID(env, assertion, errorcode, message) \
    do {                                                    \
        if (!(assertion)) {                                 \
            ThrowNapiError(env, errorcode, message);        \
            return;                                         \
        }                                                   \
    } while (0)

#define ASSERT_ERR_STATUS(env, assertion, errorcode, message) \
    do {                                                    \
        if (!(assertion)) {                                 \
            ThrowNapiError(env, errorcode, message);        \
            return napi_generic_failure;                    \
        }                                                   \
    } while (0)

#define ASSERT_BUSINESS_ERR(ctxt, assertion, errorcode, message) \
    do {                                                         \
        if (!(assertion)) {                                      \
            (ctxt)->isThrowError = true;                         \
            ThrowNapiError((ctxt)->env, errorcode, message);     \
            return;                                              \
        }                                                        \
    } while (0)

#define ASSERT_PERMISSION_ERR(ctxt, assertion, errorCode, message)  \
    do {                                                            \
        if (!(assertion)) {                                         \
            (ctxt)->isThrowError = true;                            \
            ThrowNapiError((ctxt)->env, errorCode, message, false); \
            return;                                                 \
        }                                                           \
    } while (0)
} // namespace UDMF
} // namespace OHOS
#endif // UDMF_ERROR_UTILS_H
