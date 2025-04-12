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

#ifndef RAG_SESSION_NAPI_H
#define RAG_SESSION_NAPI_H

#include <string>
#include <uv.h>

#include "i_aip_core_manager.h"
#include "rag_chatllm_impl.h"
#include "napi/native_api.h"

namespace OHOS {
namespace DataIntelligence {
class RAGSessionNapi;
struct AsyncCreateRAGSession {
    napi_async_work asyncWork;
    napi_deferred deferred;
    IAipCoreManager* ragAipCoreManagerPtr;
    ContextParam context;
    ConfigStruct config;
    int32_t ret;
    napi_value result;
};

struct AsyncStreamRun {
    napi_async_work asyncWork;
    napi_deferred deferred;
    RAGSessionNapi* sessionNapi;
    std::string question;
    OptionStruct option;
    StreamStruct stream;
    int32_t ret;
};

using StreamRunCallbackWorkParam = struct StreamRunCallbackWorkParam {
    StreamStruct stream;
    int32_t errCode;
    napi_env env;
    napi_ref ref;
    napi_ref thisJsRef;
    std::shared_ptr<ThreadLockInfo> lockInfo;
};

class RAGSessionNapi {
public:
    explicit RAGSessionNapi(IAipCoreManager *aipAipCoreManager);
    ~RAGSessionNapi();
    static napi_value Init(napi_env env, napi_value exports);
private:
    static napi_value CreateRAGSession(napi_env env, napi_callback_info info);
    static napi_value StreamRun(napi_env env, napi_callback_info info);
    static napi_value Close(napi_env env, napi_callback_info info);
    static napi_value WrapAipCoreManager(napi_env env, IAipCoreManager* ragAipCoreManager);
    static void CreateRAGSessionExecutionCB(napi_env env, void *data);
    static void CreateRAGSessionCompleteCB(napi_env env, napi_status status, void *data);
    static bool CreateAsyncCreateRAGSession(napi_env env, AsyncCreateRAGSession *asyncCreateRAGSession);
    static bool CreateAsyncStreamRunExecution(napi_env env, AsyncStreamRun *asyncStreamRun);
    static bool CreateAsyncCloseExecution(napi_env env, AsyncStreamRun *asyncClose);
    static void CloseExecutionCB(napi_env env, void *data);
    static void CloseCompleteCB(napi_env env, napi_status status, void *data);
    static napi_status ParseStreamRunArgs(napi_env env, napi_callback_info info, std::string &question,
        OptionStruct &option, RAGSessionNapi **sessionNapi);
    static void StreamRunExecutionCB(napi_env env, void *data);
    static void StreamRunCompleteCB(napi_env env, napi_status status, void *data);
    static void StreamRunCallbackExecute(RAGSessionNapi *session_napi, StreamStruct stream, int32_t errCode);
    static void StreamRunCallbackWorkerFunc(uv_work_t *work, int inStatus);
    static void StreamRunCallbackJSExecute (StreamRunCallbackWorkParam *workParam);
    static AipCoreManagerHandle aipAipCoreMgrHandle_;
    static napi_ref callbackRef_;
    static napi_threadsafe_function tsfn_;

    napi_env env_ = nullptr;
    napi_ref ref_ = nullptr;
    napi_ref thisJsRef_ = nullptr;
    IAipCoreManager *aipAipCoreManager_;
};
} // namespace DataIntelligence
} // namespace OHOS
#endif // RAG_SESSION_NAPI_H
 