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
struct ErrCodeMapping {
    int32_t nativeErrCode;
    int32_t tsErrCode;
};

constexpr ErrCodeMapping NATIVE_ERR_CODE2TS_ERR_CODE[] = {
    { NATIVE_DATABASE_CORRUPTED, DATABASE_CORRUPTED },
    { NATIVE_DATABASE_ALREADY_CLOSED, DATABASE_ALREADY_CLOSED },
    { NATIVE_DATABASE_IS_BUSY, DATABASE_IS_BUSY },
    { NATIVE_DATABASE_GENERIC_ERROD, DATABASE_GENERIC_ERROD },
    { NATIVE_DATABASE_PERMISSION_DENIED, DATABASE_PERMISSION_DENIED },
    { NATIVE_DATABASE_FILE_IS_LOCKED, DATABASE_FILE_IS_LOCKED },
    { NATIVE_DATABASE_OUT_OF_MEMORY, DATABASE_OUT_OF_MEMORY },
    { NATIVE_DATABASE_IO_ERROR, DATABASE_IO_ERROR },
    { NATIVE_DATABASE_WAL_FILE_EXCEEDS_LIMIT, DATABASE_WAL_FILE_EXCEEDS_LIMIT },
    { NATIVE_E_RECALL_FAILURE, RETRIEVAL_E_RECALL_FAILURE },
    { NATIVE_E_RERANK_FAILURE, RETRIEVAL_E_RERANK_FAILURE },
    { NATIVE_E_INVALID_NUMBER, RETRIEVAL_E_INVALID_NUMBER },
    { NATIVE_E_INVALID_PRIMARY_KEY, RETRIEVAL_E_INVALID_PRIMARY_KEY },
    { NATIVE_E_UNSUPPORTED_COMPOSITE_PRIMARY_KEY, RETRIEVAL_E_UNSUPPORTED_COMPOSITE_PRIMARY_KEY },
    { NATIVE_E_EMPTY_STRING_FIELD, RETRIEVAL_E_EMPTY_STRING_FIELD },
    { NATIVE_E_INVALID_FILTER_INPUT, RETRIEVAL_E_INVALID_FILTER_INPUT },
    { NATIVE_E_INVALID_RECALL_FIELD, RETRIEVAL_E_INVALID_RECALL_FIELD },
    { NATIVE_E_HIGH_VECTOR_SIMILARITY_THRESHOLD, RETRIEVAL_E_HIGH_VECTOR_SIMILARITY_THRESHOLD },
    { NATIVE_E_RERANK_METHOD_MISMATCH, RETRIEVAL_E_RERANK_METHOD_MISMATCH },
    { NATIVE_E_EMPTY_PARAMETER, RETRIEVAL_E_EMPTY_PARAMETER }
};

struct ErrMessage {
    int32_t code;
    const char *message;
};

constexpr ErrMessage ERROR_MESSAGES [] = {
    { PARAM_EXCEPTION, "Params check failed." },
    { DEVICE_EXCEPTION, "The device does not support this API." },
    { INNER_ERROR, "Inner error." },
    { DATABASE_CORRUPTED, "Database corrupted." },
    { DATABASE_ALREADY_CLOSED, "Already closed." },
    { DATABASE_IS_BUSY, "The database is busy." },
    { DATABASE_OUT_OF_MEMORY, "The database is out of memory." },
    { DATABASE_GENERIC_ERROD, "SQLite: Generic error." },
    { DATABASE_PERMISSION_DENIED, "SQLite: Access permission denied." },
    { DATABASE_FILE_IS_LOCKED, "SQLite: The database file is locked." },
    { DATABASE_IO_ERROR, "SQLite: Some kind of disk I/O error occurred." },
    { DATABASE_WAL_FILE_EXCEEDS_LIMIT, "SQLite: The WAL file size exceeds the default limit." },
    { RETRIEVAL_E_RECALL_FAILURE, "Retrieval: An error occurred during the recall phase." },
    { RETRIEVAL_E_RERANK_FAILURE, "Retrieval: An error occurred during the re-ranking phase." },
    { RETRIEVAL_E_INVALID_NUMBER,
        "Retrieval: The value of the numerical parameter is outside the constrained range." },
    { RETRIEVAL_E_INVALID_PRIMARY_KEY, "Retrieval: There are invalid primary keys." },
    { RETRIEVAL_E_UNSUPPORTED_COMPOSITE_PRIMARY_KEY,
        "Retrieval: A re-ranking algorithm that does not support composite primary keys was used." },
    { RETRIEVAL_E_EMPTY_STRING_FIELD, "Retrieval: There are fields with empty strings." },
    { RETRIEVAL_E_INVALID_FILTER_INPUT, "Retrieval: The filter input is invalid." },
    { RETRIEVAL_E_INVALID_RECALL_FIELD, "Retrieval: There are invalid recall names in RecallCondition." },
    { RETRIEVAL_E_HIGH_VECTOR_SIMILARITY_THRESHOLD, "Retrieval: The vector similarity threshold in VectorQuery is "
        "higher than the tiered threshold in VectorRerankParameter." },
    { RETRIEVAL_E_RERANK_METHOD_MISMATCH, "Retrieval: RerankMethod parameters do not match the channel type." },
    { RETRIEVAL_E_EMPTY_PARAMETER,
        "Retrieval: There exists a parameter value that should not be empty but is actually empty." }
};

int32_t ConvertErrCodeNative2Ts(int32_t nativeErrCode)
{
    int left = 0;
    int right = sizeof(NATIVE_ERR_CODE2TS_ERR_CODE) / sizeof(NATIVE_ERR_CODE2TS_ERR_CODE[0]) - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (NATIVE_ERR_CODE2TS_ERR_CODE[mid].nativeErrCode == nativeErrCode) {
            return NATIVE_ERR_CODE2TS_ERR_CODE[mid].tsErrCode;
        } else if (NATIVE_ERR_CODE2TS_ERR_CODE[mid].nativeErrCode < nativeErrCode) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return DATABASE_GENERIC_ERROD;
}


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
    int left = 0;
    int right = sizeof(ERROR_MESSAGES) / sizeof(ERROR_MESSAGES[0]) - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (ERROR_MESSAGES[mid].code == errorCode) {
            return ERROR_MESSAGES[mid].message;
        } else if (ERROR_MESSAGES[mid].code < errorCode) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
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