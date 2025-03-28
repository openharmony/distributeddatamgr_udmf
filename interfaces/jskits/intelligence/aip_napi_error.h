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
enum NativeErrCode : int32_t {
    NATIVE_DATABASE_CORRUPTED = 14800011,
    NATIVE_DATABASE_ALREADY_CLOSED = 14800014,
    NATIVE_DATABASE_IS_BUSY = 14800015,
    NATIVE_DATABASE_GENERIC_ERROD = 14800021,
    NATIVE_DATABASE_PERMISSION_DENIED = 14800023,
    NATIVE_DATABASE_FILE_IS_LOCKED = 14800024,
    NATIVE_DATABASE_OUT_OF_MEMORY = 14800026,
    NATIVE_DATABASE_IO_ERROR = 14800028,
    NATIVE_DATABASE_WAL_FILE_EXCEEDS_LIMIT = 14800047,
    NATIVE_E_RECALL_FAILURE = 28114948,
    NATIVE_E_RERANK_FAILURE = 28114949,
    NATIVE_E_INVALID_NUMBER = 28114950,
    NATIVE_E_INVALID_PRIMARY_KEY = 28114951,
    NATIVE_E_UNSUPPORTED_COMPOSITE_PRIMARY_KEY = 28114952,
    NATIVE_E_EMPTY_STRING_FIELD = 28114953,
    NATIVE_E_INVALID_FILTER_INPUT = 28114954,
    NATIVE_E_INVALID_RECALL_FIELD = 28114955,
    NATIVE_E_HIGH_VECTOR_SIMILARITY_THRESHOLD = 28114956,
    NATIVE_E_RERANK_METHOD_MISMATCH = 28114957,
    NATIVE_E_EMPTY_PARAMETER = 28114958,
};

enum TsErrCode : int32_t {
    PARAM_EXCEPTION = 401,
    DEVICE_EXCEPTION = 801,
    INNER_ERROR = 31300000,
    DATABASE_CORRUPTED = 31300001,
    DATABASE_ALREADY_CLOSED = 31300002,
    DATABASE_IS_BUSY = 31300003,
    DATABASE_OUT_OF_MEMORY = 31300004,
    DATABASE_GENERIC_ERROD = 31300100,
    DATABASE_PERMISSION_DENIED = 31300101,
    DATABASE_FILE_IS_LOCKED = 31300102,
    DATABASE_IO_ERROR = 31300103,
    DATABASE_WAL_FILE_EXCEEDS_LIMIT = 31300104,
    RETRIEVAL_E_RECALL_FAILURE = 31301000,
    RETRIEVAL_E_RERANK_FAILURE = 31301001,
    RETRIEVAL_E_INVALID_NUMBER = 31301002,
    RETRIEVAL_E_INVALID_PRIMARY_KEY = 31301003,
    RETRIEVAL_E_UNSUPPORTED_COMPOSITE_PRIMARY_KEY = 31301004,
    RETRIEVAL_E_EMPTY_STRING_FIELD = 31301005,
    RETRIEVAL_E_INVALID_FILTER_INPUT = 31301006,
    RETRIEVAL_E_INVALID_RECALL_FIELD = 31301007,
    RETRIEVAL_E_HIGH_VECTOR_SIMILARITY_THRESHOLD = 31301008,
    RETRIEVAL_E_RERANK_METHOD_MISMATCH = 31301009,
    RETRIEVAL_E_EMPTY_PARAMETER = 31301010,
};

int32_t ConvertErrCodeNative2Ts(int32_t nativeErrCode);
napi_value CreateIntelligenceError(const napi_env &env, int32_t errorCode, const std::string &errorMsg);
std::optional<std::string> GetIntelligenceErrMsg(int32_t errorCode);
void ThrowIntelligenceErr(const napi_env &env, int32_t errorCode, const std::string &printMsg);
void ThrowIntelligenceErrByPromise(const napi_env &env, int32_t errorCode, const std::string &printMsg,
    napi_value &value);
} // namespace DataIntelligence
} // namespae OHOS
#endif // AIP_NAPI_ERROR_H