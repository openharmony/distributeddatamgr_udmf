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

OHOS::Media::PixelMap *DecodeTlv(const unsigned char *buff, unsigned int size)
{
    std::vector<uint8_t> val(buff, buff + size);
    return OHOS::Media::PixelMap::DecodeTlv(val);
}

bool EncodeTlv(const OHOS::Media::PixelMap *pixelMap, unsigned char **buff, unsigned int *size)
{
    std::vector<uint8_t> val;
    if (!pixelMap->EncodeTlv(val)) {
        LOG_ERROR(UDMF_KITS_INNER, "Encode pixelMap failed");
        return false;
    }
    *buff = new (std::nothrow) unsigned char[val.size()];
    if (buff == nullptr) {
        LOG_ERROR(UDMF_KITS_INNER, "Apply memory failed");
        return false;
    }
    std::copy(val.begin(), val.end(), *buff);
    *size = val.size();
    return true;
}

OHOS::Media::PixelMap *GetPixelMapFromRawData(
    const unsigned char *buff, unsigned int size, const PixelMapDetails details)
{
    std::vector<uint8_t> rawData(buff, buff + size);
    OHOS::Media::InitializationOptions opts;
    opts.size.width = details.width;
    opts.size.height = details.height;
    opts.pixelFormat = static_cast<OHOS::Media::PixelFormat>(details.pixelFormat);
    LOG_INFO(UDMF_KITS_INNER,
        "PixelMap width = %{public}d, height = %{public}d, pixelFormat = %{public}d, rawData size = %{public}zu",
        opts.size.width, opts.size.height, opts.pixelFormat, rawData.size());
    // This create does not do pre-multiplication.
    opts.alphaType = OHOS::Media::AlphaType::IMAGE_ALPHA_TYPE_UNPREMUL;
    opts.srcPixelFormat = opts.pixelFormat;
    auto pixelMap = OHOS::Media::PixelMap::Create(
        reinterpret_cast<uint32_t*>(rawData.data()), rawData.size() / BYTES_PER_COLOR, opts);
    if (pixelMap == nullptr) {
        LOG_ERROR(UDMF_KITS_INNER, "Create PixelMap from rawData failed");
        return nullptr;
    }
    return pixelMap.release();
}

PixelMapDetails *ParseInfoFromPixelMap(OHOS::Media::PixelMap *pixelMap, unsigned char **buff, unsigned int *size)
{
    if (pixelMap == nullptr) {
        LOG_ERROR(UDMF_KITS_INNER, "PixelMap is null");
        return nullptr;
    }
    auto details = new (std::nothrow) PixelMapDetails;
    if (details == nullptr) {
        LOG_ERROR(UDMF_KITS_INNER, "Apply memory failed");
        return nullptr;
    }
    details->width = pixelMap->GetWidth();
    details->height = pixelMap->GetHeight();
    details->pixelFormat = static_cast<int32_t>(pixelMap->GetPixelFormat());
    details->alphaType = static_cast<int32_t>(pixelMap->GetAlphaType());
    auto status = pixelMap->ReadPixels(pixelMap->GetByteCount(), *buff);
    if (status != OHOS::Media::SUCCESS) {
        LOG_ERROR(UDMF_KITS_INNER, "Get Pixels error, status = %{public}u", status);
        *size = 0;
    } else {
        *size = pixelMap->GetByteCount();
    }
    return details; // TO BE DELETED
}