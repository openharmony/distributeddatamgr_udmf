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

#include "native_module_intelligence.h"

#include "aip_log.h"

#undef LOG_TAG
#define LOG_TAG "NativeModuleIntelligence"

namespace OHOS {
namespace DataIntelligence {
static napi_value Export(napi_env env, napi_value exports)
{
    AIP_HILOGD("NativeModuleIntelligence call");
    TextEmbeddingNapi::Init(env, exports);
    ImageEmbeddingNapi::Init(env, exports);
    RetrievalNapi::Init(env, exports);
    return exports;
}

static napi_module DataIntelligenceModule = {
    .nm_version = 1,
    .nm_flags = 0,
    .nm_filename = nullptr,
    .nm_register_func = Export,
    .nm_modname = "data.intelligence",
    .nm_priv = ((void *)0),
    .reserved = { 0 }
};

extern "C" __attribute__((constructor)) void RegisterModule(void)
{
    napi_module_register(&DataIntelligenceModule);
}
} // namespace DataIntelligence
} // namespace OHOS