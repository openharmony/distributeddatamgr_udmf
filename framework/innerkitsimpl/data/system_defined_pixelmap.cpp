/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
#define LOG_TAG "SystemDefinedPixelMap"

#include "system_defined_pixelmap.h"
#include "logger.h"
#include "pixelmap_loader.h"

namespace OHOS {
namespace UDMF {
static constexpr size_t BYTES_PER_COLOR = sizeof(uint32_t);
static constexpr const char* PIXEL_MAP_WIDTH = "width";
static constexpr const char* PIXEL_MAP_HEIGHT = "height";
static constexpr const char* PIXEL_MAP_FORMAT = "pixel-format";
static constexpr const char* PIXEL_MAP_ALPHA_TYPE = "alpha-type";
SystemDefinedPixelMap::SystemDefinedPixelMap()
{
    SetType(SYSTEM_DEFINED_PIXEL_MAP);
}

SystemDefinedPixelMap::SystemDefinedPixelMap(std::vector<uint8_t> &data)
{
    SetType(SYSTEM_DEFINED_PIXEL_MAP);
    this->rawData_ = std::move(data);
}

SystemDefinedPixelMap::SystemDefinedPixelMap(UDType type, ValueType value) : SystemDefinedRecord(type, value)
{
    SetType(SYSTEM_DEFINED_PIXEL_MAP);
    if (std::holds_alternative<std::vector<uint8_t>>(value)) {
        rawData_ = std::get<std::vector<uint8_t>>(value);
        return;
    } else if (std::holds_alternative<std::shared_ptr<OHOS::Media::PixelMap>>(value)) {
        auto pixelMap = std::get<std::shared_ptr<OHOS::Media::PixelMap>>(value);
        ParseInfoFromPixelMap(pixelMap);
    } else if (std::holds_alternative<std::shared_ptr<Object>>(value)) {
        auto object = std::get<std::shared_ptr<Object>>(value);
        auto it = object->value_.find(PIXEL_MAP);
        if (it == object->value_.end()) {
            return;
        }
        if (std::holds_alternative<std::shared_ptr<OHOS::Media::PixelMap>>(it->second)) {
            auto pixelMap = std::get<std::shared_ptr<OHOS::Media::PixelMap>>(it->second);
            ParseInfoFromPixelMap(pixelMap);
        } else if (std::holds_alternative<std::vector<uint8_t>>(it->second)) {
            rawData_ = std::get<std::vector<uint8_t>>(it->second);
        }
    }
}

int64_t SystemDefinedPixelMap::GetSize()
{
    return static_cast<int64_t>(UnifiedDataUtils::GetDetailsSize(this->details_) + rawData_.size()) +
        GetInnerEntriesSize();
}

std::vector<uint8_t> SystemDefinedPixelMap::GetRawData() const
{
    return this->rawData_;
}

void SystemDefinedPixelMap::SetRawData(const std::vector<uint8_t> &rawData)
{
    this->rawData_ = rawData;
    if (std::holds_alternative<std::shared_ptr<Object>>(value_)) {
        auto object = std::get<std::shared_ptr<Object>>(value_);
        auto pixelMap = GetPixelMapFromRawData();
        if (pixelMap == nullptr) {
            LOG_ERROR(UDMF_KITS_INNER, "Get pixelMap from rawData fail!");
            object->value_[PIXEL_MAP] = rawData;
            return;
        }
        object->value_[PIXEL_MAP] = pixelMap;
    }
}

void SystemDefinedPixelMap::InitObject()
{
    if (!std::holds_alternative<std::shared_ptr<Object>>(value_)) {
        auto value = value_;
        value_ = std::make_shared<Object>();
        auto object = std::get<std::shared_ptr<Object>>(value_);
        auto pixelMap = GetPixelMapFromRawData();
        if (pixelMap == nullptr) {
            LOG_ERROR(UDMF_KITS_INNER, "Get pixelMap from rawData fail!");
            object->value_[PIXEL_MAP] = rawData_;
        } else {
            object->value_[PIXEL_MAP] = pixelMap;
        }
        object->value_[UNIFORM_DATA_TYPE] = UtdUtils::GetUtdIdFromUtdEnum(dataType_);
        object->value_[DETAILS] = ObjectUtils::ConvertToObject(details_);
        object->value_.insert_or_assign(VALUE_TYPE, std::move(value));
    }
}

std::shared_ptr<OHOS::Media::PixelMap> SystemDefinedPixelMap::GetPixelMapFromRawData()
{
    if (rawData_.size() % BYTES_PER_COLOR != 0) {
        LOG_ERROR(UDMF_KITS_INNER, "RawData size error, size = %{public}zu", rawData_.size());
        return nullptr;
    }
    auto details = ObjectUtils::ConvertToObject(details_);
    if (details == nullptr) {
        LOG_ERROR(UDMF_KITS_INNER, "No details");
        return nullptr;
    }
    PixelMapDetails pixelMapDetails;
    pixelMapDetails.width = details->GetValue(PIXEL_MAP_WIDTH, pixelMapDetails.width) ? pixelMapDetails.width : -1;
    pixelMapDetails.height = details->GetValue(PIXEL_MAP_HEIGHT, pixelMapDetails.height) ? pixelMapDetails.height : -1;
    pixelMapDetails.pixelFormat = details->GetValue(PIXEL_MAP_FORMAT, pixelMapDetails.pixelFormat) 
        ? pixelMapDetails.pixelFormat : static_cast<int32_t>(OHOS::Media::PixelFormat::UNKNOWN);
    PixelMapLoader loader;
    return loader.GetPixelMapFromRawData(rawData_, pixelMapDetails);
}

void SystemDefinedPixelMap::ParseInfoFromPixelMap(std::shared_ptr<OHOS::Media::PixelMap> pixelMap)
{
    if (pixelMap == nullptr) {
        LOG_ERROR(UDMF_KITS_INNER, "PixelMap is null");
        return;
    }
    PixelMapLoader loader;
    auto details = loader.ParseInfoFromPixelMap(pixelMap, rawData_);
    if (details == nullptr) {
        LOG_ERROR(UDMF_KITS_INNER, "Parse info failed");
        return;
    }
    details_[PIXEL_MAP_WIDTH] = details->width;
    details_[PIXEL_MAP_HEIGHT] = details->height;
    details_[PIXEL_MAP_FORMAT] = details->pixelFormat;
    details_[PIXEL_MAP_ALPHA_TYPE] = details->alphaType;
}
} // namespace UDMF
} // namespace OHOS