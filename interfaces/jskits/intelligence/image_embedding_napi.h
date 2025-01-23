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

#ifndef IMAGE_EMBEDDING_NAPI_H
#define IMAGE_EMBEDDING_NAPI_H

#include <uv.h>
#include <refbase.h>

#include "i_aip_core_manager.h"
#include "napi/native_api.h"
#include "napi/native_node_api.h"

namespace OHOS {
namespace DataIntelligence {
class ImageEmbeddingNapi {
public:
    ImageEmbeddingNapi();
    ~ImageEmbeddingNapi();

    static napi_value Init(napi_env env, napi_value exports);
    static napi_value LoadModel(napi_env env, napi_callback_info info);
    static napi_value ReleaseModel(napi_env env, napi_callback_info info);
    static napi_value GetEmbedding(napi_env env, napi_callback_info info);
    static napi_value GetImageEmbeddingModel(napi_env env, napi_callback_info info);
    static napi_value Constructor(napi_env env, napi_callback_info info);
    static void Destructor(napi_env env, void *nativeObject, void *finalize);

    struct AsyncGetImageEmbeddingModelData {
        napi_async_work asyncWork;
        napi_deferred deferred;
        ModelConfigData config;
        napi_value res;
        int32_t ret;
    };

private:
    static bool LoadAsyncExecution(napi_env env, napi_deferred deferred);
    static bool ReleaseAsyncExecution(napi_env env, napi_deferred deferred);
    static bool GetEmbeddingAsyncExecution(napi_env env, napi_deferred deferred, std::string str);
    static bool CreateAsyncImgModelExecution(napi_env env, AsyncGetImageEmbeddingModelData *asyncModelData);
    static void GetImgEmbeddingModelExecutionCB(napi_env env, void *data);
    static void GetImgEmbeddingModelCompleteCB(napi_env env, napi_status status, void *data);
    static bool ParseModelConfig(napi_env env, napi_value *args, size_t argc, ModelConfigData *textModelConfig);
    static void LoadExecuteCB(napi_env env, void *data);
    static void LoadCompleteCB(napi_env env, napi_status status, void *data);
    static void ReleaseExecuteCB(napi_env env, void *data);
    static void ReleaseCompleteCB(napi_env env, napi_status status, void *data);
    static void GetEmbeddingExecuteCB(napi_env env, void *data);
    static void GetEmbeddingCompleteCB(napi_env env, napi_status status, void *data);
    napi_env env_;
    static thread_local napi_ref sConstructor_;
    static AipCoreManagerHandle imgAipCoreMgrHandle_;
    static IAipCoreManager *imageAipCoreManager_;
};
} // namespace DataIntelligence
} // namespace OHOS
#endif // IMAGE_EMBEDDING_NAPI_H
