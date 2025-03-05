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

#ifndef RETRIEVAL_NAPI_H
#define RETRIEVAL_NAPI_H

#include <string>
#include <map>
#include <uv.h>
#include <refbase.h>

#include "i_aip_core_manager.h"
#include "napi/native_api.h"
#include "napi/native_node_api.h"

namespace OHOS {
namespace DataIntelligence {
class RetrievalNapi;
struct AsyncGetRetriever {
    napi_async_work asyncWork;
    napi_deferred deferred;
    RetrievalConfigStruct config;
    IAipCoreManager* retrievalAipCoreManagerPtr;
    int32_t ret;
};
struct AsyncRetrieve {
    napi_async_work asyncWork;
    napi_deferred deferred;
    RetrievalConditionStruct retrievalCondition;
    IAipCoreManager* retrievalAipCoreManagerPtr;
    RetrievalResponseStruct retrievalResponse;
    napi_value res;
    int32_t ret;
};
class RetrievalNapi {
public:
    RetrievalNapi();
    ~RetrievalNapi();

    static napi_value Init(napi_env env, napi_value exports);
    static napi_value GetRetriever(napi_env env, napi_callback_info info);
    static napi_value Retrieve(napi_env env, napi_callback_info info);
    static napi_value RetrieverConstructor(napi_env env, napi_callback_info info);
    static napi_value WrapAipCoreManager(napi_env env, IAipCoreManager* retrievalAipCoreManager);

private:
    static bool LoadAsyncExecution(napi_env env, napi_deferred deferred);
    static bool CreateAsyncGetRetrieverExecution(napi_env env, AsyncGetRetriever *asyncGetRetriever);
    static bool CreateAsyncRetrieveExecution(napi_env env, AsyncRetrieve *asyncRetrieve);
    static void GetRetrieverExecutionCB(napi_env env, void *data);
    static void GetRetrieverCompleteCB(napi_env env, napi_status status, void *data);
    static void RetrieveExecutionCB(napi_env env, void *data);
    static void RetrieveCompleteCB(napi_env env, napi_status status, void *data);
    napi_env env_;
    static AipCoreManagerHandle retrievalAipCoreMgrHandle_;
};
} // namespace DataIntelligence
} // namespace OHOS
#endif // RETRIEVAL_NAPI_H
