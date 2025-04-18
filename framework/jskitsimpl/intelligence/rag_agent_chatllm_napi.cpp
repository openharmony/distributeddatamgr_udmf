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

#include "rag_agent_chatllm_napi.h"

#include "aip_log.h"
#include "aip_napi_utils.h"

#undef LOG_TAG
#define LOG_TAG "ChatLLMNNapi"

namespace OHOS {
namespace DataIntelligence {

napi_value RAGAgentChatLLMNapi::Constructor(napi_env env, napi_callback_info info)
{
    napi_value args;
    napi_get_cb_info(env, info, nullptr, nullptr, &args, nullptr);
    return args;
}

napi_value RAGAgentChatLLMNapi::Init(napi_env env, napi_value exports)
{
    if (const napi_status status = InitEnum(env, exports); status != napi_ok) {
        AIP_HILOGI("InitEnum fail.");
        return nullptr;
    }
    napi_value chatLLMClass;
    napi_define_class(env, "ChatLLM", NAPI_AUTO_LENGTH, Constructor, nullptr, 0, nullptr, &chatLLMClass);
    napi_set_named_property(env, exports, "ChatLLM", chatLLMClass);
    return exports;
}

napi_status RAGAgentChatLLMNapi::InitEnum(napi_env env, napi_value exports)
{
    napi_value llmRequestStatus;
    if (const napi_status status = napi_create_object(env, &llmRequestStatus); status != napi_ok) {
        AIP_HILOGE("create napi object fail.");
        return status;
    }
    AipNapiUtils::SetInt32Property(env, llmRequestStatus, LLM_SUCCESS, "LLM_SUCCESS");
    AipNapiUtils::SetInt32Property(env, llmRequestStatus, LLM_ERROR, "LLM_ERROR");
    AipNapiUtils::SetInt32Property(env, llmRequestStatus, LLM_LOAD_FAILED, "LLM_LOAD_FAILED");
    AipNapiUtils::SetInt32Property(env, llmRequestStatus, LLM_TIMEOUT, "LLM_TIMEOUT");
    AipNapiUtils::SetInt32Property(env, llmRequestStatus, LLM_BUSY, "LLM_BUSY");
    AipNapiUtils::SetPropertyName(env, exports, "LLMRequestStatus", llmRequestStatus);
    return napi_ok;
}

}
}