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


#ifndef TEXT_EMBEDDING_NAPI_H
#define TEXT_EMBEDDING_NAPI_H

#include <uv.h>
#include <refbase.h>

#include "i_aip_core_manager.h"
#include "i_aip_core_manager_impl.h"
#include "napi/native_api.h"
#include "napi/native_node_api.h"
namespace OHOS {
namespace DataIntelligence {
class TextEmbeddingNapi {
public:
    TextEmbeddingNapi();
    ~TextEmbeddingNapi();

    static napi_value Init(napi_env env, napi_value exports);
    static napi_value LoadModel(napi_env env, napi_callback_info info);
    static napi_value ReleaseModel(napi_env env, napi_callback_info info);
    static napi_value GetEmbedding(napi_env env, napi_callback_info info);
    static napi_value SplitText(napi_env env, napi_callback_info info);
    static napi_value GetTextEmbeddingModel(napi_env env, napi_callback_info info);
    static napi_value TextConstructor(napi_env env, napi_callback_info info);
    static void Destructor(napi_env env, void *nativeObject, void *finalize);
    struct AsyncGetTextEmbeddingModelData {
        napi_async_work asyncWork;
        napi_deferred deferred;
        ModelConfigData config;
        napi_value res;
        int32_t ret;
    };

private:
    static bool LoadAsyncExecution(napi_env env, napi_deferred deferred);
    static bool ReleaseAsyncExecution(napi_env env, napi_deferred deferred);
    static bool GetEmbeddingStringAsyncExecution(napi_env env, napi_deferred deferred, std::string str);
    static bool GetEmbeddingArrayAsyncExecution(napi_env env, napi_deferred deferred, std::vector<std::string> text);
    static bool SplitTextAsyncExecution(napi_env env, napi_deferred deferred, std::string strArg, int32_t configSize,
        int32_t configOverlap);
    static napi_value StringType(napi_env env, napi_value args, napi_value promise, napi_deferred deferred);
    static napi_value ArrayType(napi_env env, napi_value args, napi_value promise, napi_deferred deferred);
    static bool ValidateAndDealArrayArgs(napi_env env, napi_value args, std::vector<std::string> &strArr);
    static bool GetProperties(napi_env env, napi_value args, napi_value &cfgSize, napi_value &cfgOverlap);
    static void LoadExecuteCB(napi_env env, void *data);
    static void LoadCompleteCB(napi_env env, napi_status status, void *data);
    static void ReleaseExecuteCB(napi_env env, void *data);
    static void ReleaseCompleteCB(napi_env env, napi_status status, void *data);
    static void GetEmbeddingStringExecuteCB(napi_env env, void *data);
    static void GetEmbeddingStringCompleteCB(napi_env env, napi_status status, void *data);
    static void GetEmbeddingArrayExecuteCB(napi_env env, void *data);
    static void GetEmbeddingArrayCompleteCB(napi_env env, napi_status status, void *data);
    static void SplitTextExecuteCB(napi_env env, void *data);
    static void SplitTextCompleteCB(napi_env env, napi_status status, void *data);
    static bool CreateAsyncTextModelExecution(napi_env env, AsyncGetTextEmbeddingModelData *asyncModelData);
    static void GetTextEmbeddingModelExecutionCB(napi_env env, void *data);
    static void GetTextEmbeddingModelCompleteCB(napi_env env, napi_status status, void *data);
    static bool ParseModelConfig(napi_env env, napi_value *args, ModelConfigData *textModelConfig);

    static thread_local napi_ref sConstructor_;
    static AipCoreManagerHandle textAipCoreMgrHandle_;
    napi_env env_;
    static IAipCoreManager *textAipCoreManager_;
};
} // namespace DataIntelligence
} // namespace OHOS
#endif // TEXT_EMBEDDING_NAPI_H