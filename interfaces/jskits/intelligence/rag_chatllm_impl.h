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

#ifndef RAG_CHATLLM_IMPL_H
#define RAG_CHATLLM_IMPL_H
#include <condition_variable>
#include <uv.h>

#include "napi/native_node_api.h"
#include "i_aip_core_manager.h"

namespace OHOS {
namespace DataIntelligence {
using ThreadLockInfo = struct ThreadLockInfo {
    std::mutex mutex;
    std::condition_variable condition;
    bool ready = false;
};

using WorkParam = struct WorkParam {
    // input
    std::string query;
    std::shared_ptr<LLMStreamCallback> llmStreamCallback;
    napi_env env;
    napi_ref ref;
    // output
    napi_status status;
    int32_t result;
    // lock
    std::shared_ptr<ThreadLockInfo> lockInfo;
};
using StreamCallbackWorkParam = struct StreamCallbackWorkParam {
    // input
    LLMStreamAnswer answer;
    napi_env env;
};

class ChatLLM final : public IChatLLM {
public:
    ChatLLM(napi_env env, napi_ref streamChatRef);
    ~ChatLLM() override;
    TsLLMRequestStatus StreamChat(const std::string &query, const LLMStreamCallback &streamCallback) override;

    void SetRef(napi_ref streamChatRef);
    napi_ref GetRef();
private:
    static napi_value StreamCallbackFunc(napi_env env, napi_callback_info info);
    static void LLMStreamCallbackWorkerFunc(uv_work_t *work, int inStatus);
    static void CallJSStreamChat(napi_env env, napi_ref ref, WorkParam *llmWorkParam);
    static void HandlePromiseValue(napi_env env, napi_value promiseResult, WorkParam *llmWorkParam);
    static napi_value PromiseThenCallback(napi_env env, napi_callback_info info);
    static napi_value PromiseCatchCallback(napi_env env, napi_callback_info info);
    static void NativeCallbackAsync(napi_env env, const LLMStreamAnswer &answer);

    napi_env env_;
    napi_ref streamChatRef_;

    static std::shared_ptr<LLMStreamCallback> llmStreamCallback_;
    LLMStreamCallback streamCallback_;
};

}
}
#endif //RAG_CHATLLM_IMPL_H
