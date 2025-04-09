/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License a
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef I_AIP_CORE_MANAGER_IMPL_H
#define I_AIP_CORE_MANAGER_IMPL_H

#include <string>
#include <vector>

#include "i_aip_core_manager.h"

namespace OHOS {
namespace DataIntelligence {
class IAipCoreManagerImpl : public IAipCoreManager {
public:
    IAipCoreManagerImpl() = default;
    ~IAipCoreManagerImpl() = default;

    int32_t InitRetriever(const RetrievalConfigStruct& retrievalConfig) override;
    int32_t Retrieve(const std::string query, const RetrievalConditionStruct &condition,
        RetrievalResponseStruct &retrievalResponse) override;
    int32_t InitTextModel(const ModelConfigData &config) override;
    int32_t InitImageModel(const ModelConfigData &config) override;
    int32_t LoadTextModel() override;
    int32_t ReleaseTextModel() override;
    int32_t GetTextEmbedding(std::string file, std::vector<float> &results) override;
    int32_t GetTextEmbedding(const std::vector<std::string> &files, std::vector<std::vector<float>> &results) override;
    int32_t LoadImageModel() override;
    int32_t ReleaseImageModel() override;
    int32_t GetImageEmbedding(std::string uri, std::vector<float> &results) override;
    int32_t SplitText(std::string text, int32_t size, float overlap, std::vector<std::string> &results) override;

    int32_t CreateRAGSession(const ContextParam &contex, const ConfigStruct &config) override;
    int32_t RAGSessionStreamRun(const std::string &question, const OptionStruct &option,
        std::function<void(const StreamStruct&, int32_t)> callback) override;
    int32_t ReleaseRAGSession() override;
    int32_t RAGSessionRun(const std::string &query, const OptionStruct &runOption, AnswerStruct &answer) override;
};
} // namespace DataIntelligence
} // namespace OHOS
#endif // I_AIP_CORE_MANAGER_IMPL_H
