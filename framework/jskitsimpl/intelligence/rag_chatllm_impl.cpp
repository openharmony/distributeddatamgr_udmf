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
#include "rag_chatllm_impl.h"

#include <future>
#include <uv.h>

#include "aip_log.h"
#include "aip_napi_error.h"
#include "aip_napi_utils.h"
#include "napi_trace.h"

#undef LOG_TAG
#define LOG_TAG "CreateRAGNapi"

namespace OHOS {
namespace DataIntelligence {
std::shared_ptr<LLMStreamCallback> ChatLLM::llmStreamCallback_ = nullptr;
constexpr int STREAM_CHAT_WORK_DEFAULT_WAIT = 2;
constexpr int JS_STREAM_CHAT_ARGS_COUNT = 2;

ChatLLM::ChatLLM(napi_env env, napi_ref streamChatRef) : env_(env), streamChatRef_(streamChatRef)
{
}

ChatLLM::~ChatLLM()
{
    napi_delete_reference(env_, streamChatRef_);
}

TsLLMRequestStatus ChatLLM::StreamChat(const std::string &query, const LLMStreamCallback &streamCallback)
{
    DATA_INTELLIGENCE_HITRACE(std::string(__FUNCTION__));
    AIP_HILOGD("Enter. queryLength: %{public}zu", query.length());
    if (streamChatRef_ == nullptr) {
        AIP_HILOGE("streamChatRef_ is nullptr");
        return LLM_ERROR;
    }
    llmStreamCallback_ = std::make_shared<LLMStreamCallback>(streamCallback);
    uv_loop_s *loop = nullptr;
    napi_get_uv_event_loop(env_, &loop);
    if (loop == nullptr) {
        AIP_HILOGE("loop instance is nullptr");
        return LLM_ERROR;
    }

    auto *work = new (std::nothrow) uv_work_t;
    if (work == nullptr) {
        AIP_HILOGE("work is nullptr");
        return LLM_ERROR;
    }
    auto *param = new (std::nothrow) WorkParam {
        query,
        std::make_shared<LLMStreamCallback>(streamCallback),
        env_,
        streamChatRef_,
        napi_ok,
        0,
        std::make_shared<ThreadLockInfo>(),
    };
    if (param == nullptr) {
        delete work;
        work = nullptr;
        AIP_HILOGE("WorkParam is nullptr");
        return LLM_ERROR;
    }
    work->data = reinterpret_cast<void *>(param);
    int ret = uv_queue_work(loop, work, [](uv_work_t *) { }, LLMStreamCallbackWorkerFunc);
    AIP_HILOGD("uv_queue_work running, ret: %{public}d, wait for llmStreamChatWorker", ret);

    std::unique_lock<std::mutex> lock(param->lockInfo->mutex);
    if (ret == 0 && param->lockInfo->condition.wait_for(lock, std::chrono::seconds(STREAM_CHAT_WORK_DEFAULT_WAIT),
        [param] { return param->lockInfo->ready; })) {
        AIP_HILOGE("call js callback not complete.");
    }
    AIP_HILOGD("llmStreamChatWorker end, ready: %{public}d, result: %{public}d", param->lockInfo->ready, param->result);
    int32_t retInt = param->result;

    delete param;
    param = nullptr;
    delete work;
    work = nullptr;
    return static_cast<TsLLMRequestStatus>(retInt);
}

void ChatLLM::SetRef(napi_ref streamChatRef)
{
    streamChatRef_ = streamChatRef;
}

napi_ref ChatLLM::GetRef()
{
    return streamChatRef_;
}

void ChatLLM::NativeCallbackAsync(napi_env env, const LLMStreamAnswer &answer)
{
    uv_loop_s *loop = nullptr;
    napi_get_uv_event_loop(env, &loop);
    if (loop == nullptr) {
        AIP_HILOGE("loop instance is nullptr");
        return;
    }
    auto *work = new (std::nothrow) uv_work_t;
    if (work == nullptr) {
        AIP_HILOGE("work is nullptr");
        return;
    }
    auto *param = new (std::nothrow) StreamCallbackWorkParam { answer, env };
    if (param == nullptr) {
        delete work;
        work = nullptr;
        AIP_HILOGE("WorkParam is nullptr");
        return;
    }
    work->data = reinterpret_cast<void *>(param);
    int ret = uv_queue_work(loop, work, [](uv_work_t *work) {
        if (work == nullptr || work->data == nullptr) {
            AIP_HILOGE("invalid parameter");
            return;
        }
        auto *workParam = reinterpret_cast<StreamCallbackWorkParam *>(work->data);
        llmStreamCallback_->operator()(workParam->answer);
    },  [](uv_work_t *work, int32_t status) {
        if (work == nullptr) {
            AIP_HILOGE("invalid parameter");
            return;
        }
        auto *workParam = reinterpret_cast<StreamCallbackWorkParam *>(work->data);
        delete workParam;
        workParam = nullptr;
        delete work;
        work = nullptr;
    });
    if (ret != 0) {
        AIP_HILOGE("uv_queue_work running failed, ret: %{public}d", ret);
        delete param;
        param = nullptr;
        delete work;
        work = nullptr;
    }
}

napi_value ChatLLM::StreamCallbackFunc(napi_env env, napi_callback_info info)
{
    napi_value result = nullptr;
    napi_get_null(env, &result);

    napi_value args[] = { nullptr };
    size_t size = 1;
    napi_value jsFunction;
    napi_status status = napi_get_cb_info(env, info, &size, args, nullptr, reinterpret_cast<void**>(&jsFunction));
    if (status != napi_ok) {
        AIP_HILOGE("napi_get_cb_info failed. status: %{public}d", status);
        return result;
    }

    if (llmStreamCallback_ == nullptr) {
        AIP_HILOGE("streamCallback is nullptr.");
        return result;
    }

    LLMStreamAnswer answer = {
        .isFinished = false,
        .chunk = "",
    };
    status = AipNapiUtils::Convert2Value(env, args[0], answer);
    if (status != napi_ok) {
        AIP_HILOGE("Failed to convert the LLMStreamAnswer. status: %{public}d", status);
        return result;
    }

    NativeCallbackAsync(env, answer);

    return result;
}

void ChatLLM::LLMStreamCallbackWorkerFunc(uv_work_t *work, int inStatus)
{
    if (work == nullptr || work->data == nullptr) {
        AIP_HILOGE("invalid parameter");
        return;
    }

    auto *llmWorkParam = reinterpret_cast<WorkParam *>(work->data);
    if (llmWorkParam->query.empty() || llmWorkParam->llmStreamCallback == nullptr
        || llmWorkParam->ref == nullptr) {
        AIP_HILOGE("param of llmWorkParam is null");
        return;
    }

    auto env = llmWorkParam->env;
    auto ref = llmWorkParam->ref;
    napi_handle_scope scope = nullptr;
    napi_open_handle_scope(env, &scope);
    if (scope == nullptr) {
        AIP_HILOGE("scope is null");
        return;
    }

    CallJSStreamChat(env, ref, llmWorkParam);

    napi_close_handle_scope(env, scope);
}

void ChatLLM::CallJSStreamChat(napi_env env, napi_ref ref, WorkParam *llmWorkParam)
{
    napi_value callback = nullptr;
    auto ret = napi_get_reference_value(env, ref, &callback);
    if (ret != napi_ok) {
        AIP_HILOGE("get js callback failed. ret: %{public}d", ret);
        return;
    }

    napi_value queryArg;
    napi_status status = napi_create_string_utf8(env, llmWorkParam->query.c_str(), NAPI_AUTO_LENGTH, &queryArg);
    if (status != napi_ok) {
        AIP_HILOGE("Failed to napi_create_string_utf8 for query. ret: %{public}d", status);
        return;
    }

    napi_value jsCallbackArg;
    status = napi_create_function(env, "callback", NAPI_AUTO_LENGTH, StreamCallbackFunc, nullptr, &jsCallbackArg);
    if (status != napi_ok) {
        AIP_HILOGE("Failed to napi_create_function for callback. ret: %{public}d", status);
        return;
    }

    napi_value jsStreamChat;
    status = napi_get_reference_value(env, ref, &jsStreamChat);
    if (status != napi_ok) {
        AIP_HILOGE("Failed to napi_get_reference_value for jsStreamChat. ret: %{public}d", status);
        return;
    }

    napi_value global;
    status = napi_get_global(env, &global);
    if (status != napi_ok) {
        AIP_HILOGE("Failed to napi_get_global from env. ret: %{public}d", status);
        return;
    }

    const napi_value args[JS_STREAM_CHAT_ARGS_COUNT] = { queryArg, jsCallbackArg };

    AIP_HILOGI("Begin call js.");
    napi_value promiseResult; // promise
    status = napi_call_function(env, global, jsStreamChat, JS_STREAM_CHAT_ARGS_COUNT, args, &promiseResult);
    if (status != napi_ok) {
        AIP_HILOGE("Failed to napi_call_function for jsStreamChat. ret: %{public}d", status);
        return;
    }

    HandlePromiseValue(env, promiseResult, llmWorkParam);
}

void ChatLLM::HandlePromiseValue(napi_env env, napi_value promiseResult, WorkParam *llmWorkParam)
{
    auto isPromise = false;
    napi_status status = napi_is_promise(env, promiseResult, &isPromise);
    if (status != napi_ok || !isPromise) {
        AIP_HILOGE("resultType is not promise. isPromise: %{public}d, ret: %{public}d", isPromise, status);
        return;
    }

    napi_value thenCallback;
    status = napi_create_function(env, nullptr, 0, PromiseThenCallback, llmWorkParam, &thenCallback);
    if (status != napi_ok) {
        AIP_HILOGE("Failed to create then callback. ret: %{public}d", status);
        return;
    }

    napi_value catchCallback;
    status = napi_create_function(env, nullptr, 0, PromiseCatchCallback, llmWorkParam, &catchCallback);
    if (status != napi_ok) {
        AIP_HILOGE("Failed to create catch callback. ret: %{public}d", status);
        return;
    }

    napi_value thenMethod;
    status = napi_get_named_property(env, promiseResult, "then", &thenMethod);
    if (status != napi_ok) {
        AIP_HILOGE("Failed to get then method. ret: %{public}d", status);
        return;
    }

    napi_value catchMethod;
    status = napi_get_named_property(env, promiseResult, "catch", &catchMethod);
    if (status != napi_ok) {
        AIP_HILOGE("Failed to get catch method. ret: %{public}d", status);
        return;
    }

    napi_value argsPromise[1] = { thenCallback };
    napi_value thenResult;
    status = napi_call_function(env, promiseResult, thenMethod, 1, argsPromise, &thenResult);
    if (status != napi_ok) {
        AIP_HILOGE("Failed to call then method. ret: %{public}d", status);
        return;
    }

    argsPromise[0] = catchCallback;
    napi_value catchResult;
    status = napi_call_function(env, promiseResult, catchMethod, 1, argsPromise, &catchResult);
    if (status != napi_ok) {
        AIP_HILOGE("Failed to call catch method. ret: %{public}d", status);
    }
}

napi_value ChatLLM::PromiseThenCallback(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value args[1] = {nullptr};
    void *paramIn = nullptr;
    napi_get_cb_info(env, info, &argc, args, nullptr, &paramIn);

    auto *callbackParam = static_cast<WorkParam*>(paramIn);
    if (callbackParam == nullptr) {
        AIP_HILOGE("callbackParam is null");
        return nullptr;
    }

    napi_valuetype resultType;
    napi_typeof(env, args[0], &resultType);
    if (resultType == napi_number) {
        int32_t number;
        napi_get_value_int32(env, args[0], &number);
        if (number != TsLLMRequestStatus::LLM_SUCCESS) {
            AIP_HILOGE("LLM return error. errCode: %{public}d", number);
        }
        callbackParam->result = number;
    } else {
        AIP_HILOGE("The resolved value is not a number, type: %{public}d", resultType);
    }

    std::unique_lock<std::mutex> lock(callbackParam->lockInfo->mutex);
    callbackParam->lockInfo->ready = true;
    AIP_HILOGD("begin notify_all");
    callbackParam->lockInfo->condition.notify_all();
    return nullptr;
}

napi_value ChatLLM::PromiseCatchCallback(napi_env env, napi_callback_info info)
{
    AIP_HILOGE("The promise function catch exception.");
    return nullptr;
}

}
}
