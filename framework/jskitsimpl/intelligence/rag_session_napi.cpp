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

#include "rag_session_napi.h"
#include <dlfcn.h>
#include <functional>
#include <node_api.h>
#include <string>
#include <utility>
#include <uv.h>

#include "aip_log.h"
#include "aip_napi_error.h"
#include "aip_napi_utils.h"
#include "i_aip_core_manager_impl.h"
#include "napi_trace.h"

#undef LOG_TAG
#define LOG_TAG "RAGSessionNapi"

namespace OHOS {
namespace DataIntelligence {
namespace {
const int32_t ERR_OK = 0;
constexpr const char *AIP_MANAGER_PATH = "libaip_core.z.so";
} // namespace
AipCoreManagerHandle RAGSessionNapi::aipAipCoreMgrHandle_{};
constexpr int STREAM_RUN_ARG_COUNT = 3;
constexpr int STREAM_RUN_QUESTION_ARG = 0;
constexpr int STREAM_RUN_OPTION_ARG = 1;
constexpr int STREAM_RUN_CALLBACK_ARG = 2;
constexpr int CREATE_SESSION_ARG_COUNT = 2;
constexpr int CREATE_SESSION_CONTEXT_ARG = 0;
constexpr int CREATE_SESSION_CONFIG_ARG = 1;

RAGSessionNapi::RAGSessionNapi(IAipCoreManager *aipAipCoreManager) : aipAipCoreManager_(aipAipCoreManager)
{
}

RAGSessionNapi::~RAGSessionNapi()
{
    if (env_ == nullptr) {
        AIP_HILOGE("env_ is nullptr.");
        return;
    }
    if (ref_ != nullptr) {
        napi_delete_reference(env_, ref_);
    }

    if (thisJsRef_ != nullptr) {
        napi_delete_reference(env_, thisJsRef_);
    }
}

napi_value RAGSessionNapi::Init(napi_env env, napi_value exports)
{
    napi_property_descriptor desc[] = {
        DECLARE_NAPI_FUNCTION("createRagSession", CreateRAGSession),
    };
    napi_status status = napi_define_properties(env, exports, sizeof(desc) / sizeof(desc[0]), desc);
    if (status != napi_ok) {
        AIP_HILOGE("define properties fail, status = %{public}d", status);
        return nullptr;
    }
    return exports;
}

napi_value RAGSessionNapi::WrapAipCoreManager(napi_env env, IAipCoreManager* ragAipCoreManager)
{
    if (ragAipCoreManager == nullptr) {
        AIP_HILOGE("ragAipCoreManager is nullptr.");
        return nullptr;
    }
    napi_value result;
    napi_status status = napi_create_object(env, &result);
    if (status != napi_ok) {
        return nullptr;
    }
    auto *sessionNapi = new (std::nothrow) RAGSessionNapi(ragAipCoreManager);
    if (sessionNapi == nullptr) {
        AIP_HILOGE("sessionNapi new failed");
        return nullptr;
    }
    status = napi_wrap(env, result, static_cast<void *>(sessionNapi), [](napi_env env, void *data, void *hint) {
        delete static_cast<RAGSessionNapi *>(data);
    }, nullptr, nullptr);
    if (status != napi_ok) {
        AIP_HILOGE("napi_wrap aipCoreMangager failed, erroCode is %{public}d", status);
        delete sessionNapi;
        return nullptr;
    }
    napi_value streamRunFn;
    status = napi_create_function(env, nullptr, NAPI_AUTO_LENGTH, StreamRun, nullptr, &streamRunFn);
    if (status != napi_ok) {
        delete sessionNapi;
        return nullptr;
    }
    status = napi_set_named_property(env, result, "streamRun", streamRunFn);
    if (status != napi_ok) {
        delete sessionNapi;
        return nullptr;
    }
    napi_value closeFn;
    status = napi_create_function(env, nullptr, NAPI_AUTO_LENGTH, Close, nullptr, &closeFn);
    if (status != napi_ok) {
        AIP_HILOGE("napi_create_function Close failed, erroCode is %{public}d", status);
        delete sessionNapi;
        return nullptr;
    }
    status = napi_set_named_property(env, result, "close", closeFn);
    if (status != napi_ok) {
        AIP_HILOGE("napi_set_named_property close failed, erroCode is %{public}d", status);
        delete sessionNapi;
        return nullptr;
    }
    AIP_HILOGI("Build rag session success.");
    return result;
}

napi_value RAGSessionNapi::CreateRAGSession(napi_env env, napi_callback_info info)
{
    napi_value args[CREATE_SESSION_ARG_COUNT] = { nullptr };
    size_t argc = CREATE_SESSION_ARG_COUNT;
    napi_status status = napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (status != napi_ok) {
        ThrowIntelligenceErr(env, INNER_ERROR, "napi_get_cb_info failed.");
        return nullptr;
    }
    ContextParam context;
    status = AipNapiUtils::Convert2Value(env, args[CREATE_SESSION_CONTEXT_ARG], context);
    if (status != napi_ok) {
        ThrowIntelligenceErr(env, PARAM_EXCEPTION, "Parse context failed.");
        return nullptr;
    }
    ConfigStruct config;
    status = AipNapiUtils::Convert2Value(env, args[CREATE_SESSION_CONFIG_ARG], config);
    if (status != napi_ok) {
        ThrowIntelligenceErr(env, PARAM_EXCEPTION, "Parse config failed.");
        return nullptr;
    }
    napi_value promise = nullptr;
    napi_deferred deferred = nullptr;
    status = napi_create_promise(env, &deferred, &promise);
    if (status != napi_ok) {
        ThrowIntelligenceErr(env, INNER_ERROR, "create promise failed");
        return nullptr;
    }
    auto asyncCreateRAGSession = new (std::nothrow) AsyncCreateRAGSession{
        .asyncWork = nullptr,
        .deferred = deferred,
        .context = context,
        .config = config
    };
    if (asyncCreateRAGSession == nullptr) {
        ThrowIntelligenceErr(env, INNER_ERROR, "Allocate memory failed.");
        return nullptr;
    }
    if (!CreateAsyncCreateRAGSession(env, asyncCreateRAGSession)) {
        delete asyncCreateRAGSession;
        ThrowIntelligenceErr(env, INNER_ERROR, "create CreateAsyncCreateRAGSession failed");
        return nullptr;
    }
    return promise;
}

bool RAGSessionNapi::CreateAsyncCreateRAGSession(napi_env env, AsyncCreateRAGSession *asyncCreateRAGSession)
{
    napi_value resourceName;
    napi_status status = napi_create_string_utf8(env, "CreateRAGSession", NAPI_AUTO_LENGTH, &resourceName);
    if (status != napi_ok) {
        AIP_HILOGE(" napi_create_string_utf8 failed.");
        return false;
    }
    status = napi_create_async_work(env, nullptr, resourceName, CreateRAGSessionExecutionCB, CreateRAGSessionCompleteCB,
        static_cast<void *>(asyncCreateRAGSession), &asyncCreateRAGSession->asyncWork);
    if (status != napi_ok) {
        AIP_HILOGE("napi_create_async_work failed. status: %{public}d", status);
        return false;
    }
    status = napi_queue_async_work_with_qos(env, asyncCreateRAGSession->asyncWork, napi_qos_default);
    if (status != napi_ok) {
        AIP_HILOGE("napi_queue_async_work_with_qos failed. status: %{public}d", status);
        napi_delete_async_work(env, asyncCreateRAGSession->asyncWork);
        return false;
    }
    return true;
}

void RAGSessionNapi::CreateRAGSessionExecutionCB(napi_env env, void *data)
{
    AsyncCreateRAGSession *asyncCreateRAGSession = static_cast<AsyncCreateRAGSession *>(data);
    auto config = asyncCreateRAGSession->config;
    auto context = asyncCreateRAGSession->context;
    IAipCoreManager *aipAipCoreManager = nullptr;
    if (aipAipCoreMgrHandle_.create == nullptr) {
        AipNapiUtils::LoadAlgoLibrary(AIP_MANAGER_PATH, aipAipCoreMgrHandle_, false);
    }
    if (aipAipCoreMgrHandle_.create != nullptr) {
        aipAipCoreManager = aipAipCoreMgrHandle_.create();
    }
    if (aipAipCoreManager == nullptr) {
        AIP_HILOGW("Init RAGSession success by new.");
        aipAipCoreManager = new (std::nothrow) IAipCoreManagerImpl();
    }
    if (aipAipCoreManager == nullptr) {
        AIP_HILOGE("Allocate memory failed.");
        return;
    }
    int32_t ret = aipAipCoreManager->CreateRAGSession(context, config);
    asyncCreateRAGSession->ret = ret;
    if (ret != ERR_OK) {
        AIP_HILOGE("init RAGSession failed, erroCode is %{public}d", ret);
        delete aipAipCoreManager;
        return;
    }
    asyncCreateRAGSession->ragAipCoreManagerPtr = aipAipCoreManager;
}

void RAGSessionNapi::CreateRAGSessionCompleteCB(napi_env env, napi_status status, void *data)
{
    AsyncCreateRAGSession *asyncCreateRAGSession = static_cast<AsyncCreateRAGSession *>(data);
    if (asyncCreateRAGSession == nullptr) {
        AIP_HILOGE("asyncCreateRAGSession is nullptr.");
        return;
    }
    auto ret = asyncCreateRAGSession->ret;
    napi_value result = nullptr;
    if (ret != ERR_OK) {
        if (ret == DEVICE_EXCEPTION) {
            ThrowIntelligenceErrByPromise(env, DEVICE_EXCEPTION, "CreateRAGSessionCompleteCB failed", result);
        } else {
            ThrowIntelligenceErrByPromise(env,
                ConvertErrCodeNative2Ts(ret), "CreateRAGSessionCompleteCB failed", result);
        }
        napi_reject_deferred(env, asyncCreateRAGSession->deferred, result);
    } else {
        result = WrapAipCoreManager(env, asyncCreateRAGSession->ragAipCoreManagerPtr);
        if (result == nullptr) {
            delete asyncCreateRAGSession->ragAipCoreManagerPtr;
            ThrowIntelligenceErrByPromise(env, INNER_ERROR, "CreateRAGSessionCompleteCB failed", result);
            napi_reject_deferred(env, asyncCreateRAGSession->deferred, result);
        }
        status = napi_resolve_deferred(env, asyncCreateRAGSession->deferred, result);
        if (status != napi_ok) {
            AIP_HILOGE("napi_resolve_deferred failed. status: %{public}d", status);
        }
    }
    status = napi_delete_async_work(env, asyncCreateRAGSession->asyncWork);
    if (status != napi_ok) {
        AIP_HILOGE("napi_delete_async_work failed. status: %{public}d", status);
    }
    delete asyncCreateRAGSession;
}

napi_value RAGSessionNapi::Close(napi_env env, napi_callback_info info)
{
    napi_value argv[1] = { nullptr };
    size_t argc = 1;
    napi_value jsThis = nullptr;
    napi_status status = napi_get_cb_info(env, info, &argc, argv, &jsThis, nullptr);
    if (status != napi_ok) {
        ThrowIntelligenceErr(env, INNER_ERROR, "napi_get_cb_info failed.");
        return nullptr;
    }

    napi_value promise = nullptr;
    napi_deferred deferred = nullptr;
    status = napi_create_promise(env, &deferred, &promise);
    if (status != napi_ok) {
        ThrowIntelligenceErr(env, INNER_ERROR, "create promise failed.");
        return nullptr;
    }
    RAGSessionNapi *sessionNapi;
    status = napi_unwrap(env, jsThis, reinterpret_cast<void **>(&sessionNapi));
    if (status != napi_ok || sessionNapi == nullptr || sessionNapi->aipAipCoreManager_ == nullptr) {
        ThrowIntelligenceErr(env, RAG_E_RAG_ALREADY_CLOSED, "RAG session napi has already closed.");
        return nullptr;
    }
    auto asyncClose = new (std::nothrow) AsyncStreamRun {
        .asyncWork = nullptr,
        .deferred = deferred,
        .sessionNapi = sessionNapi
    };
    if (asyncClose == nullptr) {
        ThrowIntelligenceErr(env, INNER_ERROR, "Allocate memory failed.");
        return nullptr;
    }
    if (!CreateAsyncCloseExecution(env, asyncClose)) {
        delete asyncClose;
        ThrowIntelligenceErr(env, INNER_ERROR, "CreateAsyncCloseExecution failed");
        return nullptr;
    }
    return promise;
}

bool RAGSessionNapi::CreateAsyncCloseExecution(napi_env env, AsyncStreamRun *asyncClose)
{
    napi_value resourceName;
    napi_status status = napi_create_string_utf8(env, "Close", NAPI_AUTO_LENGTH, &resourceName);
    if (status != napi_ok) {
        AIP_HILOGE(" napi_create_string_utf8 failed. status: %{public}d", status);
        return false;
    }
    status = napi_create_async_work(env, nullptr, resourceName, CloseExecutionCB, CloseCompleteCB,
        static_cast<void *>(asyncClose), &asyncClose->asyncWork);
    if (status != napi_ok) {
        AIP_HILOGE("napi_create_async_work failed. status: %{public}d", status);
        return false;
    }
    status = napi_queue_async_work_with_qos(env, asyncClose->asyncWork, napi_qos_default);
    if (status != napi_ok) {
        AIP_HILOGE("napi_queue_async_work_with_qos failed. status: %{public}d", status);
        napi_delete_async_work(env, asyncClose->asyncWork);
        return false;
    }
    return true;
}

void RAGSessionNapi::CloseExecutionCB(napi_env env, void *data)
{
    auto *asyncClose = static_cast<AsyncStreamRun *>(data);
    auto runAipCoreManagerPtr = asyncClose->sessionNapi->aipAipCoreManager_;
    int32_t result = runAipCoreManagerPtr->ReleaseRAGSession();
    asyncClose->ret = result;
    AIP_HILOGD("ReleaseRAGAgent result: %{public}d", asyncClose->ret);
}

void RAGSessionNapi::CloseCompleteCB(napi_env env, napi_status status, void *data)
{
    AsyncStreamRun *asyncClose = static_cast<AsyncStreamRun *>(data);
    auto ret = asyncClose->ret;
    if (ret != ERR_OK) {
        napi_value result = nullptr;
        if (ret == DEVICE_EXCEPTION) {
            ThrowIntelligenceErrByPromise(env, DEVICE_EXCEPTION, "CloseCompleteCB failed", result);
        } else {
            int32_t errCode = ConvertErrCodeNative2Ts(ret);
            ThrowIntelligenceErrByPromise(env, errCode, "CloseCompleteCB failed", result);
        }
        napi_reject_deferred(env, asyncClose->deferred, result);
    } else {
        napi_value undefined;
        napi_get_undefined(env, &undefined);
        napi_resolve_deferred(env, asyncClose->deferred, undefined);
    }
    status = napi_delete_async_work(env, asyncClose->asyncWork);
    if (status != napi_ok) {
        AIP_HILOGE("napi_delete_async_work failed. status: %{public}d", status);
    }
    if (asyncClose->sessionNapi != nullptr) {
        delete asyncClose->sessionNapi->aipAipCoreManager_;
    }
    delete asyncClose->sessionNapi;
    delete asyncClose;
    AIP_HILOGI("Rag session close success.");
}

napi_status RAGSessionNapi::ParseStreamRunArgs(napi_env env, napi_callback_info info, std::string &question,
    OptionStruct &option, RAGSessionNapi **sessionNapi)
{
    napi_value argv[STREAM_RUN_ARG_COUNT] = { nullptr };
    size_t argc = STREAM_RUN_ARG_COUNT;
    napi_value jsThis = nullptr;
    napi_status status = napi_get_cb_info(env, info, &argc, argv, &jsThis, nullptr);
    if (status != napi_ok) {
        ThrowIntelligenceErr(env, INNER_ERROR, "napi_get_cb_info failed.");
        return status;
    }
    if (argc != STREAM_RUN_ARG_COUNT) {
        ThrowIntelligenceErr(env, PARAM_EXCEPTION, "Param count error.");
        return napi_invalid_arg;
    }
    status = AipNapiUtils::Convert2Value(env, argv[STREAM_RUN_QUESTION_ARG], question);
    if (status != napi_ok) {
        ThrowIntelligenceErr(env, PARAM_EXCEPTION, "Parse question failed.");
        return status;
    }
    status = AipNapiUtils::Convert2Value(env, argv[STREAM_RUN_OPTION_ARG], option);
    if (status != napi_ok) {
        ThrowIntelligenceErr(env, PARAM_EXCEPTION, "Parse option failed.");
        return status;
    }
    napi_valuetype valueType = napi_undefined;
    napi_typeof(env, argv[STREAM_RUN_CALLBACK_ARG], &valueType);
    napi_ref callbackRef = nullptr;
    if (valueType == napi_function) {
        napi_create_reference(env, argv[STREAM_RUN_CALLBACK_ARG], 1, &callbackRef);
    } else {
        ThrowIntelligenceErr(env, PARAM_EXCEPTION, "Parse callback failed.");
    }
    status = napi_unwrap(env, jsThis, reinterpret_cast<void **>(sessionNapi));
    if (status != napi_ok || (*sessionNapi) == nullptr || (*sessionNapi)->aipAipCoreManager_ == nullptr) {
        ThrowIntelligenceErr(env, RAG_E_RAG_ALREADY_CLOSED, "Session is already closed.");
        return napi_invalid_arg;
    }
    napi_ref thisJsRef = nullptr;
    status = napi_create_reference(env, jsThis, 1, &thisJsRef);
    if (status != napi_ok) {
        return status;
    }
    (*sessionNapi)->env_ = env;
    (*sessionNapi)->ref_ = callbackRef;
    (*sessionNapi)->thisJsRef_ = thisJsRef;
    return napi_ok;
}

napi_value RAGSessionNapi::StreamRun(napi_env env, napi_callback_info info)
{
    DATA_INTELLIGENCE_HITRACE(std::string(__FUNCTION__));
    std::string question;
    OptionStruct option = { .answerWithRetrievalItem = false };
    RAGSessionNapi *sessionNapi = {0};

    napi_status status = ParseStreamRunArgs(env, info, question, option, &sessionNapi);
    if (status != napi_ok) {
        return nullptr;
    }

    napi_value promise = nullptr;
    napi_deferred deferred = nullptr;
    status = napi_create_promise(env, &deferred, &promise);
    if (status != napi_ok) {
        ThrowIntelligenceErr(env, INNER_ERROR, "create promise failed.");
        return nullptr;
    }

    auto asyncStreamRun = new (std::nothrow) AsyncStreamRun {
        .asyncWork = nullptr,
        .deferred = deferred,
        .sessionNapi = sessionNapi,
        .question = question,
        .option = option,
    };
    if (asyncStreamRun == nullptr) {
        ThrowIntelligenceErr(env, INNER_ERROR, "Allocate memory failed.");
        return nullptr;
    }
    if (!CreateAsyncStreamRunExecution(env, asyncStreamRun)) {
        delete asyncStreamRun;
        ThrowIntelligenceErr(env, INNER_ERROR, "CreateAsyncStreamRunExecution failed");
    }
    return promise;
}

bool RAGSessionNapi::CreateAsyncStreamRunExecution(napi_env env, AsyncStreamRun *asyncStreamRun)
{
    napi_value resourceName;
    napi_status status = napi_create_string_utf8(env, "StreamRun", NAPI_AUTO_LENGTH, &resourceName);
    if (status != napi_ok) {
        AIP_HILOGE(" napi_create_string_utf8 failed. status: %{public}d", status);
        return false;
    }
    status = napi_create_async_work(env, nullptr, resourceName, StreamRunExecutionCB, StreamRunCompleteCB,
        static_cast<void *>(asyncStreamRun), &asyncStreamRun->asyncWork);
    if (status != napi_ok) {
        AIP_HILOGE("napi_create_async_work failed");
        return false;
    }
    status = napi_queue_async_work_with_qos(env, asyncStreamRun->asyncWork, napi_qos_default);
    if (status != napi_ok) {
        AIP_HILOGE("napi_queue_async_work_with_qos failed. status: %{public}d", status);
        napi_delete_async_work(env, asyncStreamRun->asyncWork);
        return false;
    }
    return true;
}

void RAGSessionNapi::StreamRunExecutionCB(napi_env env, void *data)
{
    AsyncStreamRun *asyncStreamRun = static_cast<AsyncStreamRun *>(data);
    auto question = asyncStreamRun->question;
    auto option = asyncStreamRun->option;
    auto sessionNapi = asyncStreamRun->sessionNapi;
    std::function<void(StreamStruct, int32_t)> callBackFunction =
        [sessionNapi](const StreamStruct &stream, const int32_t errorCode) {
            AIP_HILOGD("streamRun callback result: %{public}d", errorCode);
            StreamRunCallbackExecute(sessionNapi, stream, errorCode);
    };
    int32_t result = sessionNapi->aipAipCoreManager_->RAGSessionStreamRun(question, option, callBackFunction);
    AIP_HILOGD("runAipCoreManagerPtr->StreamRun result: %{public}d", result);
    asyncStreamRun->ret = result;
}

void RAGSessionNapi::StreamRunCompleteCB(napi_env env, napi_status status, void *data)
{
    AsyncStreamRun *asyncStreamRun = static_cast<AsyncStreamRun *>(data);
    auto ret = asyncStreamRun->ret;
    if (ret != ERR_OK) {
        napi_value result = nullptr;
        if (ret == DEVICE_EXCEPTION) {
            ThrowIntelligenceErrByPromise(env, DEVICE_EXCEPTION, "StreamRunCompleteCB failed", result);
        } else {
            int32_t errCode = ConvertErrCodeNative2Ts(ret);
            ThrowIntelligenceErrByPromise(env, errCode, "StreamRunCompleteCB failed", result);
        }
        napi_reject_deferred(env, asyncStreamRun->deferred, result);
    } else {
        napi_value undefined;
        napi_get_undefined(env, &undefined);
        napi_resolve_deferred(env, asyncStreamRun->deferred, undefined);
    }
    status = napi_delete_async_work(env, asyncStreamRun->asyncWork);
    if (status != napi_ok) {
        AIP_HILOGE("napi_delete_async_work failed.");
    }
    delete asyncStreamRun;
}

void RAGSessionNapi::StreamRunCallbackJSExecute(StreamRunCallbackWorkParam *workParam)
{
    auto env = workParam->env;
    auto ref = workParam->ref;
    auto thisJsRef = workParam->thisJsRef;
    auto errCode = workParam->errCode;
    napi_value thisJs;
    if (thisJsRef == nullptr) {
        AIP_HILOGE("thisJs is nullptr");
        napi_get_undefined(env, &thisJs);
    } else {
        napi_status refStatus = napi_get_reference_value(env, thisJsRef, &thisJs);
        if (refStatus != napi_ok) {
            AIP_HILOGE("js this get failed. ret: %{public}d", refStatus);
            napi_get_undefined(env, &thisJs);
        }
    }
    napi_value errorNapi;
    napi_value streamNapi;
    if (errCode == 0) {
        napi_get_undefined(env, &errorNapi);
        napi_status status = AipNapiUtils::Convert2JSValue(env, workParam->stream, streamNapi);
        if (status != napi_ok) {
            AIP_HILOGE("stream struct Convert2JSValue failed. ret: %{public}d", status);
            return;
        }
    } else {
        ThrowIntelligenceErrByPromise(env, ConvertErrCodeNative2Ts(errCode),
            "streamRunCallbackWorkerFunc failed", errorNapi);
        napi_get_undefined(env, &streamNapi);
    }

    const napi_value argv[] = { errorNapi, streamNapi };
    size_t argc = 2;

    napi_value callback;
    napi_status status = napi_get_reference_value(env, ref, &callback);
    if (status != napi_ok) {
        AIP_HILOGE("js callback function get failed. ret: %{public}d", status);
        return;
    }
    status = napi_call_function(env, thisJs, callback, argc, argv, nullptr);
    if (status != napi_ok) {
        AIP_HILOGE("js callback function call failed. ret: %{public}d", status);
        return;
    }
}

void RAGSessionNapi::StreamRunCallbackWorkerFunc(uv_work_t *work, int inStatus)
{
    if (inStatus == UV_ECANCELED  || work == nullptr || work->data == nullptr) {
        AIP_HILOGE("invalid parameter");
        if (work != nullptr) {
            delete work;
            work = nullptr;
        }
        return;
    }

    auto *workParam = reinterpret_cast<StreamRunCallbackWorkParam *>(work->data);
    if (workParam->env == nullptr || workParam->ref == nullptr) {
        AIP_HILOGE("streamRun callback work param is null");
        delete workParam;
        workParam = nullptr;
        delete work;
        work = nullptr;
        return;
    }

    StreamRunCallbackJSExecute(workParam);

    delete workParam;
    workParam = nullptr;
    delete work;
    work = nullptr;
}

void RAGSessionNapi::StreamRunCallbackExecute(RAGSessionNapi *sessionNapi, StreamStruct stream, int32_t errCode)
{
    if (sessionNapi == nullptr || sessionNapi->env_ == nullptr || sessionNapi->ref_ == nullptr) {
        AIP_HILOGE("sessionNapi is nullptr: %{public}d", sessionNapi == nullptr);
        return;
    }
    uv_loop_s *loop = nullptr;
    auto env = sessionNapi->env_;
    auto ref = sessionNapi->ref_;
    auto thisJs = sessionNapi->thisJsRef_;
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
    auto *workParam = new (std::nothrow) StreamRunCallbackWorkParam {
        std::move(stream),
        errCode,
        env,
        ref,
        thisJs,
        std::make_shared<ThreadLockInfo>(),
    };
    if (workParam == nullptr) {
        delete work;
        work = nullptr;
        AIP_HILOGE("WorkParam is nullptr");
        return;
    }
    work->data = reinterpret_cast<void *>(workParam);
    int ret = uv_queue_work(loop, work, [](uv_work_t *work) { AIP_HILOGE("llm run callback"); },
        StreamRunCallbackWorkerFunc);
    if (ret != 0) {
        AIP_HILOGE("uv_queue_work running failed, ret: %{public}d", ret);
        delete workParam;
        workParam = nullptr;
        delete work;
        work = nullptr;
    }
}
} // namespace DataIntelligence
} // namespace OHOS
 