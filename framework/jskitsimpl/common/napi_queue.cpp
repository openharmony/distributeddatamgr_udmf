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
#define LOG_TAG "NapiQueue"
#include "napi_queue.h"

#include "logger.h"

namespace OHOS {
namespace UDMF {
ContextBase::~ContextBase()
{
    LOG_DEBUG(UDMF_KITS_NAPI, "no memory leak after callback or promise[resolved/rejected]");
    if (env != nullptr) {
        if (work != nullptr) {
            napi_delete_async_work(env, work);
        }
        if (callbackRef != nullptr) {
            napi_delete_reference(env, callbackRef);
        }
        napi_delete_reference(env, selfRef);
        env = nullptr;
    }
}

void ContextBase::GetCbInfo(napi_env envi, napi_callback_info info, NapiCbInfoParser parse, bool sync)
{
    env = envi;
    size_t argc = ARGC_MAX;
    napi_value argv[ARGC_MAX] = { nullptr };
    status = napi_get_cb_info(env, info, &argc, argv, &self, nullptr);
    ASSERT_STATUS(this, "napi_get_cb_info failed!");
    ASSERT_ARGS(this, argc <= ARGC_MAX, "too many arguments!");
    ASSERT_ARGS(this, self != nullptr, "no JavaScript this argument!");
    if (!sync) {
        napi_create_reference(env, self, 1, &selfRef);
    }
    status = napi_unwrap(env, self, &native);
    ASSERT_STATUS(this, "self unwrap failed!");

    if (!sync && (argc > 0)) {
        // get the last arguments :: <callback>
        size_t index = argc - 1;
        napi_valuetype type = napi_undefined;
        napi_status tyst = napi_typeof(env, argv[index], &type);
        if ((tyst == napi_ok) && (type == napi_function)) {
            status = napi_create_reference(env, argv[index], 1, &callbackRef);
            ASSERT_STATUS(this, "ref callback failed!");
            argc = index;
            LOG_DEBUG(UDMF_KITS_NAPI, "async callback, no promise");
        } else {
            LOG_DEBUG(UDMF_KITS_NAPI, "no callback, async pormose");
        }
    }

    if (parse) {
        parse(argc, argv);
    } else {
        ASSERT_ARGS(this, argc == 0, "required no arguments!");
    }
}

napi_value NapiQueue::AsyncWork(napi_env env, std::shared_ptr<ContextBase> ctxt, const std::string &name,
    NapiAsyncExecute execute, NapiAsyncComplete complete)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "NapiQueue::AsyncWork name = %{public}s", name.c_str());
    ctxt->execute = std::move(execute);
    ctxt->complete = std::move(complete);
    LOG_DEBUG(UDMF_KITS_NAPI, "NapiQueue::AsyncWork move func finish");
    napi_value promise = nullptr;
    if (ctxt->callbackRef == nullptr) {
        LOG_DEBUG(UDMF_KITS_NAPI, "NapiQueue::AsyncWork has promise");
        napi_create_promise(ctxt->env, &ctxt->deferred, &promise);
        LOG_DEBUG(UDMF_KITS_NAPI, "create deferred promise");
    } else {
        LOG_DEBUG(UDMF_KITS_NAPI, "NapiQueue::AsyncWork no promise");
        napi_get_undefined(ctxt->env, &promise);
    }
    napi_value resource = nullptr;
    LOG_DEBUG(UDMF_KITS_NAPI, "NapiQueue::AsyncWork create string start");
    napi_create_string_utf8(ctxt->env, name.c_str(), NAPI_AUTO_LENGTH, &resource);
    LOG_DEBUG(UDMF_KITS_NAPI, "NapiQueue::AsyncWork create string finish");
    napi_create_async_work(ctxt->env, nullptr, resource,
        [](napi_env env, void *data) {
            LOG_DEBUG(UDMF_KITS_NAPI, "NapiQueue::AsyncWork start execute");
            ASSERT_VOID(data != nullptr, "no data");
            auto ctxt = reinterpret_cast<ContextBase *>(data);
            LOG_DEBUG(UDMF_KITS_NAPI, "napi_async_execute_callback ctxt->status = %{public}d", ctxt->status);
            if (ctxt->execute && ctxt->status == napi_ok) {
                LOG_DEBUG(UDMF_KITS_NAPI, "NapiQueue::AsyncWork do user design execute");
                ctxt->execute();
            }
            LOG_DEBUG(UDMF_KITS_NAPI, "NapiQueue::AsyncWork finish execute");
        },
        [](napi_env env, napi_status status, void *data) {
            LOG_DEBUG(UDMF_KITS_NAPI, "NapiQueue::AsyncWork start output");
            ASSERT_VOID(data != nullptr, "no data");
            auto ctxt = reinterpret_cast<ContextBase *>(data);
            LOG_DEBUG(UDMF_KITS_NAPI, "napi_async_complete_callback status = %{public}d, ctxt->status = %{public}d",
                status, ctxt->status);
            if ((status != napi_ok) && (ctxt->status == napi_ok)) {
                LOG_DEBUG(UDMF_KITS_NAPI, "NapiQueue::AsyncWork check status");
                ctxt->status = status;
            }
            if ((ctxt->complete) && (status == napi_ok) && (ctxt->status == napi_ok)) {
                LOG_DEBUG(UDMF_KITS_NAPI, "NapiQueue::AsyncWork do user design output");
                ctxt->complete(ctxt->output);
            }
            GenerateOutput(ctxt);
            LOG_DEBUG(UDMF_KITS_NAPI, "NapiQueue::AsyncWork finish output");
        },
        reinterpret_cast<void *>(ctxt.get()), &ctxt->work);
    napi_queue_async_work(ctxt->env, ctxt->work);
    ctxt->hold = ctxt; // save crossing-thread ctxt.
    return promise;
}

void NapiQueue::GenerateOutput(ContextBase *ctxt)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "GenerateOutput start");
    napi_value result[RESULT_ALL] = { nullptr };
    LOG_DEBUG(UDMF_KITS_NAPI, "GenerateOutput ctxt->status = %{public}d", ctxt->status);
    if (ctxt->status == napi_ok) {
        napi_get_undefined(ctxt->env, &result[RESULT_ERROR]);
        if (ctxt->output == nullptr) {
            napi_get_undefined(ctxt->env, &ctxt->output);
        }
        result[RESULT_DATA] = ctxt->output;
    } else {
        napi_value code = nullptr;
        napi_value message = nullptr;
        if (ctxt->jsCode != 0 && ctxt->jsCode != -1) {
            napi_create_string_utf8(ctxt->env, std::to_string(ctxt->jsCode).c_str(), NAPI_AUTO_LENGTH, &code);
        }
        if (ctxt->jsCode == -1) {
            std::string jsCode;
            napi_create_string_utf8(ctxt->env, jsCode.c_str(), NAPI_AUTO_LENGTH, &code);
        }
        napi_create_string_utf8(ctxt->env, ctxt->error.c_str(), NAPI_AUTO_LENGTH, &message);
        napi_create_error(ctxt->env, code, message, &result[RESULT_ERROR]);
        napi_get_undefined(ctxt->env, &result[RESULT_DATA]);
    }
    if (ctxt->deferred != nullptr) {
        LOG_DEBUG(UDMF_KITS_NAPI, "GenerateOutput deferred branch");
        if (ctxt->status == napi_ok) {
            LOG_DEBUG(UDMF_KITS_NAPI, "deferred promise resolved");
            napi_resolve_deferred(ctxt->env, ctxt->deferred, result[RESULT_DATA]);
        } else {
            LOG_DEBUG(UDMF_KITS_NAPI, "deferred promise rejected");
            napi_reject_deferred(ctxt->env, ctxt->deferred, result[RESULT_ERROR]);
        }
    } else {
        napi_value callback = nullptr;
        napi_get_reference_value(ctxt->env, ctxt->callbackRef, &callback);
        napi_value callbackResult = nullptr;
        LOG_INFO(UDMF_KITS_NAPI, "GenerateOutput call callback function");
        LOG_DEBUG(UDMF_KITS_NAPI, "call callback function");
        napi_call_function(ctxt->env, nullptr, callback, RESULT_ALL, result, &callbackResult);
    }
    ctxt->hold.reset(); // release ctxt.
    LOG_DEBUG(UDMF_KITS_NAPI, "GenerateOutput stop");
}
} // namespace UDMF
} // namespace OHOS
