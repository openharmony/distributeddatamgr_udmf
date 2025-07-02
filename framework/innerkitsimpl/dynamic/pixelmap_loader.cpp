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
#define LOG_TAG "PixelmapLoader"

#include "pixelmap_loader.h"

#include <dlfcn.h>
#include <thread>
#include "logger.h"
#include "pixel_map.h"

namespace OHOS {
namespace UDMF {

static constexpr const char* PIXEL_MAP_WRAPPER_SO_NAME = "libpixelmap_wrapper.z.so";
static constexpr const char* DECODE_TLV = "DecodeTlv";
static constexpr const char* ENCODE_TLV = "EncodeTlv";
static constexpr const char* GET_PIXEL_MAP_FROM_RAW_DATA = "GetPixelMapFromRawData";
static constexpr const char* PARSE_INFO_FROM_PIXEL_MAP = "ParseInfoFromPixelMap";
static constexpr const int DELAY_DESTRUCTION_INTERVAL = 10;


PixelMapLoader::PixelMapLoader()
{
    handler_ = dlopen(PIXEL_MAP_WRAPPER_SO_NAME, RTLD_LAZY);
    if (handler_ == nullptr) {
        LOG_ERROR(UDMF_KITS_INNER, "load so fail! msg=%{public}s", dlerror());
    }
}

PixelMapLoader::~PixelMapLoader()
{
    if (handler_ == nullptr) {
        return;
    }
    auto handler = handler_;
    std::thread([handler]() {
        std::this_thread::sleep_for(std::chrono::seconds(DELAY_DESTRUCTION_INTERVAL));
        dlclose(handler);
    }).detach();
    handler_ = nullptr;
}

std::shared_ptr<OHOS::Media::PixelMap> PixelMapLoader::DecodeTlv(std::vector<uint8_t> &buff)
{
    if (buff.empty()) {
        LOG_ERROR(UDMF_KITS_INNER, "buff is empty!");
        return nullptr;
    }
    if (handler_ == nullptr) {
        LOG_ERROR(UDMF_KITS_INNER, "load so fail!");
        return nullptr;
    }
    PixelMapDetails details;
    details.rawData = std::ref(buff);
    auto loadDecodeTlv = (LoadDecodeTlv)dlsym(handler_, DECODE_TLV);
    if (loadDecodeTlv == nullptr) {
        LOG_ERROR(UDMF_KITS_INNER, "dlsym error! msg=%{public}s", dlerror());
        return nullptr;
    }
    return std::shared_ptr<OHOS::Media::PixelMap>(loadDecodeTlv(details));
}

bool PixelMapLoader::EncodeTlv(const std::shared_ptr<OHOS::Media::PixelMap> pixelMap, std::vector<uint8_t> &buff)
{
    if (pixelMap == nullptr) {
        LOG_ERROR(UDMF_KITS_INNER, "pixelMap is nullptr!");
        return false;
    }
    if (handler_ == nullptr) {
        LOG_ERROR(UDMF_KITS_INNER, "load so fail!");
        return false;
    }
    auto loadEncodeTlv = (LoadEncodeTlv)dlsym(handler_, ENCODE_TLV);
    if (loadEncodeTlv == nullptr) {
        LOG_ERROR(UDMF_KITS_INNER, "dlsym error! msg=%{public}s", dlerror());
        return false;
    }
    auto details = std::make_shared<PixelMapDetails>();
    auto result = loadEncodeTlv(pixelMap.get(), details.get());
    if (details->rawDataResult->empty()) {
        LOG_ERROR(UDMF_KITS_INNER, "encodeTlv fail");
        return result;
    }
    buff = std::move(*details->rawDataResult);
    return result;
}

std::shared_ptr<OHOS::Media::PixelMap> PixelMapLoader::GetPixelMapFromRawData(const PixelMapDetails &details)
{
    if (!details.rawData.has_value()) {
        LOG_ERROR(UDMF_KITS_INNER, "buff is empty!");
        return nullptr;
    }
    if (handler_ == nullptr) {
        LOG_ERROR(UDMF_KITS_INNER, "load so fail!");
        return nullptr;
    }
    auto loadGetPixelMapFromRawData = (LoadGetPixelMapFromRawData)dlsym(handler_, GET_PIXEL_MAP_FROM_RAW_DATA);
    if (loadGetPixelMapFromRawData == nullptr) {
        LOG_ERROR(UDMF_KITS_INNER, "dlsym error! msg=%{public}s", dlerror());
        return nullptr;
    }
    return std::shared_ptr<OHOS::Media::PixelMap>(loadGetPixelMapFromRawData(details));
}

std::shared_ptr<PixelMapDetails> PixelMapLoader::ParseInfoFromPixelMap(
    const std::shared_ptr<OHOS::Media::PixelMap> pixelMap)
{
    if (pixelMap == nullptr) {
        LOG_ERROR(UDMF_KITS_INNER, "pixelMap is nullptr!");
        return nullptr;
    }
    if (handler_ == nullptr) {
        LOG_ERROR(UDMF_KITS_INNER, "handler_ is null");
        return nullptr;
    }
    auto loadParseInfoFromPixelMap = (LoadParseInfoFromPixelMap)dlsym(handler_, PARSE_INFO_FROM_PIXEL_MAP);
    if (loadParseInfoFromPixelMap == nullptr) {
        LOG_ERROR(UDMF_KITS_INNER, "dlsym error! msg=%{public}s", dlerror());
        return nullptr;
    }
    return std::shared_ptr<PixelMapDetails>(loadParseInfoFromPixelMap(pixelMap.get()));
}

} // namespace UDMF
} // namespace OHOS