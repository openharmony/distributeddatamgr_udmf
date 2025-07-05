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
#define LOG_TAG "PixelmapWrapper"
#include "pixelmap_wrapper.h"

#include "logger.h"
#include "media_errors.h"
#include "pixel_map.h"

using namespace OHOS::UDMF;

static constexpr size_t BYTES_PER_COLOR = sizeof(uint32_t);

#ifdef __cplusplus
extern "C" {
#endif

OHOS::Media::PixelMap *DecodeTlv(const PixelMapDetails details)
{
    return OHOS::Media::PixelMap::DecodeTlv(details.rawData->get());
}

bool EncodeTlv(const OHOS::Media::PixelMap *pixelMap, PixelMapDetails *details)
{
    if (details == nullptr) {
        LOG_ERROR(UDMF_KITS_INNER, "details is null");
        return false;
    }
    auto &rawData = *(details->rawDataResult);
    return pixelMap->EncodeTlv(rawData);
}

OHOS::Media::PixelMap *GetPixelMapFromRawData(const PixelMapDetails details)
{
    OHOS::Media::InitializationOptions opts;
    opts.size.width = details.width;
    opts.size.height = details.height;
    opts.pixelFormat = static_cast<OHOS::Media::PixelFormat>(details.pixelFormat);
    if (!details.rawData.has_value()) {
        return nullptr;
    }
    // This create does not do pre-multiplication.
    opts.alphaType = OHOS::Media::AlphaType::IMAGE_ALPHA_TYPE_UNPREMUL;
    LOG_INFO(UDMF_KITS_INNER,
        "PixelMap width = %{public}d, height = %{public}d, pixelFormat = %{public}d, rawData size = %{public}zu",
        opts.size.width, opts.size.height, opts.pixelFormat, details.
        rawData->get().size());
    opts.srcPixelFormat = opts.pixelFormat;
    auto pixelMap = OHOS::Media::PixelMap::Create(
        reinterpret_cast<const uint32_t *>(details.rawData->get().data()),
        details.rawData->get().size() / BYTES_PER_COLOR, opts);
    if (pixelMap == nullptr) {
        LOG_ERROR(UDMF_KITS_INNER, "Create PixelMap from rawData failed");
        return nullptr;
    }
    return pixelMap.release();
}

PixelMapDetails *ParseInfoFromPixelMap(OHOS::Media::PixelMap *pixelMap)
{
    if (pixelMap == nullptr) {
        LOG_ERROR(UDMF_KITS_INNER, "PixelMap is null");
        return nullptr;
    }
    auto details = new (std::nothrow) PixelMapDetails;
    if (details == nullptr) {
        LOG_ERROR(UDMF_KITS_INNER, "Apply memory for details failed");
        return nullptr;
    }
    details->width = pixelMap->GetWidth();
    details->height = pixelMap->GetHeight();
    details->pixelFormat = static_cast<int32_t>(pixelMap->GetPixelFormat());
    details->alphaType = static_cast<int32_t>(pixelMap->GetAlphaType());
    auto length = pixelMap->GetByteCount();
    if (length <= 0) {
        LOG_ERROR(UDMF_KITS_INNER, "Has no length");
        return details;
    }
    std::vector<uint8_t> rawData;
    rawData.resize(length);
    auto status = pixelMap->ReadPixels(length, rawData.data());
    if (status != OHOS::Media::SUCCESS) {
        LOG_ERROR(UDMF_KITS_INNER, "Get Pixels error, status = %{public}u", status);
        return details;
    }
    details->rawDataResult.emplace(std::move(rawData));
    return details;
}

#ifdef __cplusplus
};
#endif