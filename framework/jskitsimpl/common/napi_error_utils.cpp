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
#define LOG_TAG "NapiErrorCode"
#include "napi_error_utils.h"

namespace OHOS {
namespace UDMF {
using NapiErrorCode = OHOS::UDMF::NapiErrorCode;

static constexpr NapiErrorCode JS_ERROR_CODE_MSGS[] = {
    { Status::E_NO_PERMISSION, 201, "Permission denied!" },
    { Status::E_INVALID_PARAMETERS, 401, "Parameter error." },
    { Status::E_SETTINGS_EXISTED, 20400001,
      "Settings already exist. To reconfigure, remove the existing sharing options." },
    { Status::E_NO_SYSTEM_PERMISSION, 202,
      "Permission denied, application which is not a system application uses system API." },
};

const std::optional<NapiErrorCode> GetErrorCode(int32_t errorCode)
{
    auto napiErrorCode = NapiErrorCode{ errorCode, -1, "" };
    auto iter = std::lower_bound(JS_ERROR_CODE_MSGS,
        JS_ERROR_CODE_MSGS + sizeof(JS_ERROR_CODE_MSGS) / sizeof(JS_ERROR_CODE_MSGS[0]), napiErrorCode,
        [](const NapiErrorCode &napiErrorCode1, const NapiErrorCode &napiErrorCode2) {
            return napiErrorCode1.status < napiErrorCode2.status;
        });
    if (iter < JS_ERROR_CODE_MSGS + sizeof(JS_ERROR_CODE_MSGS) / sizeof(JS_ERROR_CODE_MSGS[0]) &&
        iter->status == errorCode) {
        return *iter;
    }
    return std::nullopt;
}

Status GenerateNapiError(Status error, int32_t &errCode, std::string &errMessage)
{
    auto errormsg = GetErrorCode(error);
    if (errormsg.has_value()) {
        auto napiError = errormsg.value();
        errCode = napiError.jsCode;
        errMessage = napiError.message;
    } else {
        // unmatched status return unified error code
        errCode = -1;
        errMessage = "";
    }
    LOG_DEBUG(UDMF_KITS_NAPI, "GenerateNapiError errCode is %{public}d", errCode);
    if (errCode == 0) {
        return Status::E_OK;
    }
    return error;
}

void ThrowNapiError(napi_env env, int32_t status, const std::string &errMessage, bool isParamsCheck)
{
    if (status == Status::E_OK) {
        return;
    }
    auto errorMsg = GetErrorCode(status);
    NapiErrorCode napiError;
    if (errorMsg.has_value()) {
        napiError = errorMsg.value();
    } else {
        napiError.jsCode = -1;
        napiError.message = "";
    }

    std::string message(napiError.message);
    if (isParamsCheck) {
        auto paramsCheckError = 401;
        napiError.jsCode = paramsCheckError;
        message += errMessage;
    }

    std::string jsCode;
    if (napiError.jsCode == -1) {
        jsCode = "";
    } else {
        jsCode = std::to_string(napiError.jsCode);
    }
    LOG_INFO(UDMF_KITS_NAPI, "ThrowNapiError, status:%{public}d, jsCode: %{public}s, message: %{public}s",
             status, jsCode.c_str(), errMessage.c_str());
    napi_throw_error(env, jsCode.c_str(), message.c_str());
}
} // namespace UDMF
} // namespace OHOS
