/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef UDMF_DATA_INTELLIGENCE_IMPL_H
#define UDMF_DATA_INTELLIGENCE_IMPL_H

#include <dlfcn.h>
#include <stdexcept>
#include <string>

#include "i_aip_core_manager_impl.h"
#include "i_aip_core_manager.h"
#include "ohos.data.intelligence.impl.hpp"
#include "ohos.data.intelligence.proj.hpp"
#include "taihe/runtime.hpp"

namespace intelligence {
class TextEmbeddingImpl {
public:
    TextEmbeddingImpl();
    ~TextEmbeddingImpl();
    void loadModel();
    void releaseModel();
    ::taihe::array<double> getEmbedding(::taihe::string_view text);
    ::taihe::array<::taihe::array<double>> getEmbeddingArray(::taihe::array_view<::taihe::string> batchTexts);
};

class ImageEmbeddingImpl {
public:
    ImageEmbeddingImpl();
    ~ImageEmbeddingImpl();
    void loadModel();
    void releaseModel();
    ::taihe::array<double> getEmbedding(::taihe::string_view image);
};

bool LoadAlgoLibrary(const std::string &fileName, OHOS::DataIntelligence::AipCoreManagerHandle &managerHandle,
    bool isSingleton);
bool UnLoadAlgoLibrary(OHOS::DataIntelligence::AipCoreManagerHandle &managerHandle);
::ohos::data::intelligence::TextEmbedding getTextEmbeddingModelSync(
    ::ohos::data::intelligence::ModelConfig const& config);
::ohos::data::intelligence::ImageEmbedding getImageEmbeddingModelSync(
    ::ohos::data::intelligence::ModelConfig const& config);
::taihe::array<::taihe::string> splitTextSync(::taihe::string_view text,
    ::ohos::data::intelligence::SplitConfig const& config);
}  // namespace
#endif