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

#define LOG_TAG "AniIntelligenceImpl"

#include <algorithm>
#include <climits>
#include "data_intelligence_impl.h"
#include "logger.h"

#undef LOG_TAG
#define LOG_TAG "intelligence"

namespace intelligence {
using namespace OHOS::UDMF;
const int32_t ERR_OK = 0;
static constexpr int PARAMETERS_ERROR = 401;
static constexpr int DEVICE_EXCEPTION_ERROR = 801;
static constexpr int RET_INNER_ERROR = 31300000;
static constexpr uint8_t NUM_0 = 0;
static constexpr uint8_t NUM_1 = 1;
#ifdef __aarch64__
constexpr const char *AIP_MANAGER_PATH = "/system/lib64/platformsdk/libaip_core.z.so";
#else
constexpr const char *AIP_MANAGER_PATH = "libaip_core.z.so";
#endif
OHOS::DataIntelligence::AipCoreManagerHandle textAipCoreMgrHandle_{};
OHOS::DataIntelligence::AipCoreManagerHandle imgAipCoreMgrHandle_{};
OHOS::DataIntelligence::IAipCoreManager* textAipCoreManager_ = nullptr;
OHOS::DataIntelligence::IAipCoreManager *imageAipCoreManager_ = nullptr;

bool LoadAlgoLibrary(const std::string &fileName, OHOS::DataIntelligence::AipCoreManagerHandle &managerHandle)
{
    if (managerHandle.handle != nullptr) {
        LOG_ERROR(UDMF_ANI, "%{public}s handle has exists", LOG_TAG);
        return false;
    }
    if (fileName.empty()) {
        LOG_ERROR(UDMF_ANI, "%{public}s algoPath is empty", LOG_TAG);
        return false;
    }
    char libRealPath[PATH_MAX] = {};
    if (realpath(fileName.c_str(), libRealPath) == nullptr) {
        LOG_ERROR("%{public}s get absolute algoPath error, %{public}d", LOG_TAG, errno);
        return false;
    }
    managerHandle.handle = dlopen(libRealPath, RTLD_LAZY);
    if (managerHandle.handle == nullptr) {
        LOG_ERROR(UDMF_ANI, "%{public}s cannot load lib error: %{public}s", LOG_TAG, dlerror());
        return false;
    }
    managerHandle.create = reinterpret_cast<OHOS::DataIntelligence::IAipCoreManager *(*)()>(
        dlsym(managerHandle.handle, "Create"));
    managerHandle.destroy = reinterpret_cast<void (*)(const OHOS::DataIntelligence::IAipCoreManager *)>
        (dlsym(managerHandle.handle, "Destroy"));
    if (managerHandle.create == nullptr || managerHandle.destroy == nullptr) {
        dlclose(managerHandle.handle);
        managerHandle.Clear();
        LOG_ERROR(UDMF_ANI, "%{public}s Failed to create and destroy algo", LOG_TAG);
        return false;
    }
    managerHandle.pAipManager = managerHandle.create();
    return true;
}

bool UnLoadAlgoLibrary(OHOS::DataIntelligence::AipCoreManagerHandle &managerHandle)
{
    if (managerHandle.handle == nullptr) {
        LOG_ERROR(UDMF_ANI, "%{public}s handle is nullptr", LOG_TAG);
        return false;
    }

    if (managerHandle.pAipManager != nullptr && managerHandle.destroy != nullptr) {
        managerHandle.destroy(managerHandle.pAipManager);
        managerHandle.pAipManager = nullptr;
    }

    dlclose(managerHandle.handle);
    managerHandle.Clear();
    return true;
}

TextEmbeddingImpl::TextEmbeddingImpl()
{
    if (!LoadAlgoLibrary(AIP_MANAGER_PATH, textAipCoreMgrHandle_)) {
        LOG_ERROR(UDMF_ANI, "%{public}s LoadAlgoLibrary failed", LOG_TAG);
    }
    if (textAipCoreMgrHandle_.pAipManager) {
        textAipCoreManager_ = textAipCoreMgrHandle_.pAipManager;
    } else {
        textAipCoreManager_ = new (std::nothrow) OHOS::DataIntelligence::IAipCoreManagerImpl();
    }
};

TextEmbeddingImpl::~TextEmbeddingImpl()
{
    UnLoadAlgoLibrary(textAipCoreMgrHandle_);
    textAipCoreManager_ = nullptr;
}

void TextEmbeddingImpl::loadModel()
{
    if (!textAipCoreManager_) {
        LOG_ERROR(UDMF_ANI, "%{public}s textAipCoreManager_ is nullptr", LOG_TAG);
        taihe::set_business_error(PARAMETERS_ERROR, "check param error.");
        return;
    }
    auto ret = textAipCoreManager_->LoadTextModel();
    if (ret != ERR_OK) {
        LOG_ERROR(UDMF_ANI, "%{public}s LoadTextModel failed! ret:%{public}d", LOG_TAG, ret);
        if (ret == DEVICE_EXCEPTION_ERROR) {
            taihe::set_business_error(DEVICE_EXCEPTION_ERROR, "The device does not support this API.");
        } else {
            taihe::set_business_error(RET_INNER_ERROR, "Inner error.");
        }
    }
}

void TextEmbeddingImpl::releaseModel()
{
    if (!textAipCoreManager_) {
        LOG_ERROR(UDMF_ANI, "%{public}s textAipCoreManager_ is nullptr", LOG_TAG);
        taihe::set_business_error(PARAMETERS_ERROR, "check param error.");
        return;
    }
    auto ret = textAipCoreManager_->ReleaseTextModel();
    if (ret != ERR_OK) {
        LOG_ERROR(UDMF_ANI, "%{public}s ReleaseTextModel failed! ret:%{public}d", LOG_TAG, ret);
        if (ret == DEVICE_EXCEPTION_ERROR) {
            taihe::set_business_error(DEVICE_EXCEPTION_ERROR, "The device does not support this API.");
        } else {
            taihe::set_business_error(RET_INNER_ERROR, "Inner error.");
        }
    }
}

::taihe::array<double> TextEmbeddingImpl::getEmbedding(::taihe::string_view text)
{
    if (!textAipCoreManager_) {
        LOG_ERROR(UDMF_ANI, "%{public}s textAipCoreManager_ is nullptr", LOG_TAG);
        taihe::set_business_error(PARAMETERS_ERROR, "check param error.");
        return ::taihe::array<double>(nullptr, 0);
    }
    std::vector<float> result;
    int32_t ret = textAipCoreManager_->GetTextEmbedding(std::string(text), result);
    if (ret != ERR_OK) {
        LOG_ERROR(UDMF_ANI, "%{public}s GetTextEmbedding string failed! ret:%{public}d", LOG_TAG, ret);
        if (ret == DEVICE_EXCEPTION_ERROR) {
            taihe::set_business_error(DEVICE_EXCEPTION_ERROR, "The device does not support this API.");
        } else {
            taihe::set_business_error(RET_INNER_ERROR, "Inner error.");
        }
        return ::taihe::array<double>(nullptr, 0);
    }
    std::vector<double> res(result.size());
    std::transform(result.begin(), result.end(), res.begin(), [](float val) { return static_cast<double>(val); });
    return ::taihe::array<double>(res);
}

::taihe::array<::taihe::array<double>> TextEmbeddingImpl::getEmbeddingArray(
    ::taihe::array_view<::taihe::string> batchTexts)
{
    if (!textAipCoreManager_) {
        LOG_ERROR(UDMF_ANI, "%{public}s textAipCoreManager_ is nullptr", LOG_TAG);
        taihe::set_business_error(PARAMETERS_ERROR, "check param error.");
        return ::taihe::array<::taihe::array<double>>(nullptr, 0);
    }
    std::vector<std::vector<float>> result;
    std::vector<std::string> texts(batchTexts.size());
    std::transform(batchTexts.begin(), batchTexts.end(), texts.begin(),
        [](::taihe::string val) { return std::string(val); });
    int32_t ret = textAipCoreManager_->GetTextEmbedding(texts, result);
    if (ret != ERR_OK) {
        LOG_ERROR(UDMF_ANI, "%{public}s GetTextEmbedding Array failed! ret:%{public}d", LOG_TAG, ret);
        if (ret == DEVICE_EXCEPTION_ERROR) {
            taihe::set_business_error(DEVICE_EXCEPTION_ERROR, "The device does not support this API.");
        } else {
            taihe::set_business_error(RET_INNER_ERROR, "Inner error.");
        }
        return ::taihe::array<::taihe::array<double>>(nullptr, 0);
    }
    std::vector<::taihe::array<double>> res;
    for (size_t i = 0; i < result.size(); ++i) {
        std::vector<double> node(result[i].size());
        std::transform(result[i].begin(), result[i].end(), node.begin(),
            [](float val) { return static_cast<double>(val); });
        res.push_back(::taihe::array<double>(node));
    }
    return ::taihe::array<::taihe::array<double>>(res);
}

ImageEmbeddingImpl::ImageEmbeddingImpl()
{
    if (!LoadAlgoLibrary(AIP_MANAGER_PATH, imgAipCoreMgrHandle_)) {
        LOG_ERROR(UDMF_ANI, "%{public}s LoadAlgoLibrary failed", LOG_TAG);
    }
    if (imgAipCoreMgrHandle_.pAipManager) {
        imageAipCoreManager_ = imgAipCoreMgrHandle_.pAipManager;
    } else {
        imageAipCoreManager_ = new (std::nothrow) OHOS::DataIntelligence::IAipCoreManagerImpl();
    }
}

ImageEmbeddingImpl::~ImageEmbeddingImpl()
{
    UnLoadAlgoLibrary(imgAipCoreMgrHandle_);
    imageAipCoreManager_ = nullptr;
}

void ImageEmbeddingImpl::loadModel()
{
    if (!imageAipCoreManager_) {
        LOG_ERROR(UDMF_ANI, "%{public}s imageAipCoreManager_ is nullptr", LOG_TAG);
        taihe::set_business_error(PARAMETERS_ERROR, "check param error.");
        return;
    }
    auto ret = imageAipCoreManager_->LoadImageModel();
    if (ret != ERR_OK) {
        LOG_ERROR(UDMF_ANI, "%{public}s LoadImageModel failed! ret:%{public}d", LOG_TAG, ret);
        if (ret == DEVICE_EXCEPTION_ERROR) {
            taihe::set_business_error(DEVICE_EXCEPTION_ERROR, "The device does not support this API.");
        } else {
            taihe::set_business_error(RET_INNER_ERROR, "Inner error.");
        }
    }
}

void ImageEmbeddingImpl::releaseModel()
{
    if (!imageAipCoreManager_) {
        LOG_ERROR(UDMF_ANI, "%{public}s imageAipCoreManager_ is nullptr", LOG_TAG);
        taihe::set_business_error(PARAMETERS_ERROR, "check param error.");
        return;
    }
    auto ret = imageAipCoreManager_->ReleaseImageModel();
    if (ret != ERR_OK) {
        LOG_ERROR(UDMF_ANI, "%{public}s ReleaseImageModel failed! ret:%{public}d", LOG_TAG, ret);
        if (ret == DEVICE_EXCEPTION_ERROR) {
            taihe::set_business_error(DEVICE_EXCEPTION_ERROR, "The device does not support this API.");
        } else {
            taihe::set_business_error(RET_INNER_ERROR, "Inner error.");
        }
    }
}

::taihe::array<double> ImageEmbeddingImpl::getEmbedding(::taihe::string_view image)
{
    if (!imageAipCoreManager_) {
        LOG_ERROR(UDMF_ANI, "%{public}s imageAipCoreManager_ is nullptr", LOG_TAG);
        taihe::set_business_error(PARAMETERS_ERROR, "check param error.");
        return ::taihe::array<double>(nullptr, 0);
    }
    std::vector<float> result;
    int32_t ret = imageAipCoreManager_->GetImageEmbedding(std::string(image), result);
    if (ret != ERR_OK) {
        LOG_ERROR(UDMF_ANI, "%{public}s GetImageEmbedding failed! ret:%{public}d", LOG_TAG, ret);
        if (ret == DEVICE_EXCEPTION_ERROR) {
            taihe::set_business_error(DEVICE_EXCEPTION_ERROR, "The device does not support this API.");
        } else {
            taihe::set_business_error(RET_INNER_ERROR, "Inner error.");
        }
        return ::taihe::array<double>(nullptr, 0);
    }
    std::vector<double> res(result.size());
    std::transform(result.begin(), result.end(), res.begin(), [](float val) { return static_cast<double>(val); });
    return ::taihe::array<double>(res);
}

::ohos::data::intelligence::TextEmbedding getTextEmbeddingModelSync(
    ::ohos::data::intelligence::ModelConfig const& config)
{
    ::ohos::data::intelligence::TextEmbedding textEmbed =
        taihe::make_holder<TextEmbeddingImpl, ::ohos::data::intelligence::TextEmbedding>();
    if (!textAipCoreManager_) {
        LOG_ERROR(UDMF_ANI, "%{public}s textAipCoreManager_ is nullptr", LOG_TAG);
        taihe::set_business_error(PARAMETERS_ERROR, "check param error.");
        return ::taihe::make_holder<TextEmbeddingImpl, ::ohos::data::intelligence::TextEmbedding>();
    }
    OHOS::DataIntelligence::ModelConfigData cfgData {
        .versionValue = config.version,
        .isNPUAvailableValue = config.isNpuAvailable,
        .cachePathValue = config.isNpuAvailable ? std::string(config.cachePath.value()) : ""
    };

    int32_t ret = textAipCoreManager_ ->InitTextModel(cfgData);
    if (ret != ERR_OK) {
        LOG_ERROR(UDMF_ANI, "%{public}s GetTextEmbeddingModel failed! ret:%{public}d", LOG_TAG, ret);
        if (ret == DEVICE_EXCEPTION_ERROR) {
            taihe::set_business_error(DEVICE_EXCEPTION_ERROR, "The device does not support this API.");
        } else {
            taihe::set_business_error(RET_INNER_ERROR, "Inner error.");
        }
        return taihe::make_holder<TextEmbeddingImpl, ::ohos::data::intelligence::TextEmbedding>();
    }
    return textEmbed;
}


::ohos::data::intelligence::ImageEmbedding getImageEmbeddingModelSync(
    ::ohos::data::intelligence::ModelConfig const& config)
{
    ::ohos::data::intelligence::ImageEmbedding imageEmbed =
        taihe::make_holder<ImageEmbeddingImpl, ::ohos::data::intelligence::ImageEmbedding>();
    if (!imageAipCoreManager_) {
        LOG_ERROR(UDMF_ANI, "%{public}s imageAipCoreManager_ is nullptr", LOG_TAG);
        taihe::set_business_error(PARAMETERS_ERROR, "check param error.");
        return taihe::make_holder<ImageEmbeddingImpl, ::ohos::data::intelligence::ImageEmbedding>();
    }
    OHOS::DataIntelligence::ModelConfigData cfgData {
        .versionValue = config.version,
        .isNPUAvailableValue = config.isNpuAvailable,
        .cachePathValue = config.isNpuAvailable ? std::string(config.cachePath.value()) : ""
    };
    int32_t ret = imageAipCoreManager_ ->InitImageModel(cfgData);
    if (ret != ERR_OK) {
        LOG_ERROR(UDMF_ANI, "%{public}s getImageEmbeddingModel failed! ret:%{public}d", LOG_TAG, ret);
        if (ret == DEVICE_EXCEPTION_ERROR) {
            taihe::set_business_error(DEVICE_EXCEPTION_ERROR, "The device does not support this API.");
        } else {
            taihe::set_business_error(RET_INNER_ERROR, "Inner error.");
        }
        return taihe::make_holder<ImageEmbeddingImpl, ::ohos::data::intelligence::ImageEmbedding>();
    }
    return imageEmbed;
}

::taihe::array<::taihe::string> splitTextSync(::taihe::string_view text,
    ::ohos::data::intelligence::SplitConfig const& config)
{
    ::ohos::data::intelligence::TextEmbedding textEmbed =
        taihe::make_holder<TextEmbeddingImpl, ::ohos::data::intelligence::TextEmbedding>();
    if (!textAipCoreManager_) {
        LOG_ERROR(UDMF_ANI, "%{public}s textAipCoreManager_ is nullptr", LOG_TAG);
        taihe::set_business_error(PARAMETERS_ERROR, "check param error.");
        return ::taihe::array<::taihe::string>(nullptr, 0);
    }
    if (!textAipCoreManager_->CheckDeviceType()) {
        LOG_ERROR(UDMF_ANI, "%{public}s CheckDeviceType failed", LOG_TAG);
        taihe::set_business_error(DEVICE_EXCEPTION_ERROR, "The device does not support this API.");
        return ::taihe::array<::taihe::string>(nullptr, 0);
    }
    if (config.size <= NUM_0 || config.overlapRatio < NUM_0 || config.overlapRatio >= NUM_1) {
        LOG_ERROR(UDMF_ANI, "%{public}s The parameter value range is incorrect", LOG_TAG);
        taihe::set_business_error(PARAMETERS_ERROR, "check param error.");
        return ::taihe::array<::taihe::string>(nullptr, 0);
    }
    std::vector<std::string> result;
    int32_t ret = textAipCoreManager_->SplitText(std::string(text), config.size, config.overlapRatio, result);
    if (ret != ERR_OK) {
        LOG_ERROR(UDMF_ANI, "%{public}s SplitText failed! ret:%{public}d", LOG_TAG, ret);
        if (ret == DEVICE_EXCEPTION_ERROR) {
            taihe::set_business_error(DEVICE_EXCEPTION_ERROR, "The device does not support this API.");
        } else {
            taihe::set_business_error(RET_INNER_ERROR, "Inner error.");
        }
        return ::taihe::array<::taihe::string>(nullptr, 0);
    }
    std::vector<::taihe::string> res;
    for (auto str : result) {
        res.push_back(::taihe::string(str));
    }
    return ::taihe::array<::taihe::string>(res);
}
}  // namespace

// Since these macros are auto-generate, lint will cause false positive.
// NOLINTBEGIN
TH_EXPORT_CPP_API_getTextEmbeddingModelSync(intelligence::getTextEmbeddingModelSync);
TH_EXPORT_CPP_API_getImageEmbeddingModelSync(intelligence::getImageEmbeddingModelSync);
TH_EXPORT_CPP_API_splitTextSync(intelligence::splitTextSync);
// NOLINTEND
