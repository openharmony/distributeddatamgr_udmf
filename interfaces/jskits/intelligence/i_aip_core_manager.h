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
#ifndef I_AIP_CORE_MANAGER_H
#define I_AIP_CORE_MANAGER_H

#include <string>
#include <vector>

namespace OHOS {
namespace DataIntelligence {
struct ModelConfigData {
    int32_t versionValue;
    bool isNPUAvailableValue;
    std::string cachePathValue;
};

class IAipCoreManager {
public:
    IAipCoreManager() = default;
    virtual ~IAipCoreManager() = default;

    virtual int32_t InitTextModel(const ModelConfigData &config) = 0;
    virtual int32_t InitImageModel(const ModelConfigData &config) = 0;
    virtual int32_t LoadTextModel() = 0;
    virtual int32_t ReleaseTextModel() = 0;
    virtual int32_t GetTextEmbedding(std::string file, std::vector<float> &results) = 0;
    virtual int32_t GetTextEmbedding(const std::vector<std::string> &files,
        std::vector<std::vector<float>> &results) = 0;
    virtual int32_t LoadImageModel() = 0;
    virtual int32_t ReleaseImageModel() = 0;
    virtual int32_t GetImageEmbedding(std::string uri, std::vector<float> &results) = 0;
    virtual int32_t SplitText(std::string text, int32_t size, float overlap, std::vector<std::string> &results) = 0;
};

struct AipCoreManagerHandle {
    void *handle;
    IAipCoreManager *(*create)();
    void (*destroy)(const IAipCoreManager *);
    IAipCoreManager *pAipManager;
    AipCoreManagerHandle() : handle(nullptr), create(nullptr), destroy(nullptr), pAipManager(nullptr) {}
    ~AipCoreManagerHandle() {}
    void Clear()
    {
        handle = nullptr;
        create = nullptr;
        destroy = nullptr;
        pAipManager = nullptr;
    }
};
} // namespace DataIntelligence
} // namespace OHOS

#endif // I_AIP_CORE_MANAGER_H