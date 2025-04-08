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

namespace OHOS {
namespace UDMF {
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
        SetPixelMapDetails(pixelMap);
        if (!SetRawDataFromPixels(pixelMap)) {
            LOG_ERROR(UDMF_KITS_INNER, "Set rawData fail!");
        }
    } else if (std::holds_alternative<std::shared_ptr<Object>>(value)) {
        auto object = std::get<std::shared_ptr<Object>>(value);
        auto it = object->value_.find(PIXEL_MAP);
        if (it == object->value_.end()) {
            return;
        }
        if (std::holds_alternative<std::shared_ptr<OHOS::Media::PixelMap>>(it->second)) {
            auto pixelMap = std::get<std::shared_ptr<OHOS::Media::PixelMap>>(it->second);
            SetPixelMapDetails(pixelMap);
            if (!SetRawDataFromPixels(pixelMap)) {
                LOG_ERROR(UDMF_KITS_INNER, "Set rawData fail!");
            }
        } else if (std::holds_alternative<std::vector<uint8_t>>(it->second)) {
            rawData_ = std::get<std::vector<uint8_t>>(it->second);
        }
    }
}

void SystemDefinedPixelMap::SetPixelMapDetails(const std::shared_ptr<OHOS::Media::PixelMap> pixelMap)
{
    details_["width"] = pixelMap->GetWidth();
    details_["heigth"] = pixelMap->GetHeight();
    details_["pixel-format"] = static_cast<int32_t>(pixelMap->GetPixelFormat());
    details_["alpha-type"] = static_cast<int32_t>(pixelMap->GetAlphaType());
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
        object->value_[PIXEL_MAP] = std::move(pixelMap);
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
            object->value_[PIXEL_MAP] = std::move(pixelMap);
        }
        object->value_[UNIFORM_DATA_TYPE] = UtdUtils::GetUtdIdFromUtdEnum(dataType_);
        object->value_[DETAILS] = ObjectUtils::ConvertToObject(details_);
        object->value_.insert_or_assign(VALUE_TYPE, std::move(value));
    }
}

bool SystemDefinedPixelMap::SetRawDataFromPixels(const std::shared_ptr<OHOS::Media::PixelMap> pixelMap)
{
    if (pixelMap == nullptr) {
        return false;
    }
    rawData_.resize(pixelMap->GetByteCount());
    auto status = pixelMap->ReadPixels(pixelMap->GetByteCount(), rawData_.data());
    if (status != 0) {
        LOG_ERROR(UDMF_KITS_INNER, "Get Pixels error, status = %{public}u", status);
        rawData_.clear();
        return false;
    }
    return true;
}

std::unique_ptr<Media::PixelMap> SystemDefinedPixelMap::GetPixelMapFromRawData()
{
    Media::InitializationOptions opts;
    auto details = ObjectUtils::ConvertToObject(details_);
    if (details->GetValue("width", opts.size.width) &&
        details->GetValue("height", opts.size.height) &&
        details->GetValue("pixel-format", opts.pixelFormat) &&
        details->GetValue("alpha-type", opts.alphaType)) {
        if (rawData_.size() % 4 != 0) {
            LOG_ERROR(UDMF_KITS_INNER, "RawData size error, size = %{public}zu", rawData_.size());
            return nullptr;
        }
        return Media::PixelMap::Create(
            reinterpret_cast<uint32_t*>(rawData_.data()), rawData_.size() / 4, opts);
    }
    LOG_ERROR(UDMF_KITS_INNER, "PixelMap data incomplete, size = %{public}zu", rawData_.size());
    return nullptr;
}
} // namespace UDMF
} // namespace OHOS