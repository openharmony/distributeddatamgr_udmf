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
    this->dataType_ = SYSTEM_DEFINED_PIXEL_MAP;
}

SystemDefinedPixelMap::SystemDefinedPixelMap(std::vector<uint8_t> &data)
{
    this->dataType_ = SYSTEM_DEFINED_PIXEL_MAP;
    this->rawData_ = std::move(data);
}

SystemDefinedPixelMap::SystemDefinedPixelMap(UDType type, ValueType value) : SystemDefinedRecord(type, value)
{
    this->dataType_ = SYSTEM_DEFINED_PIXEL_MAP;
    if (std::holds_alternative<std::vector<uint8_t>>(value)) {
        rawData_ = std::get<std::vector<uint8_t>>(value);
        return;
    }
    if (std::holds_alternative<std::shared_ptr<Object>>(value)) {
        auto object = std::get<std::shared_ptr<Object>>(value);
        auto it = object->value_.find(PIXEL_MAP);
        hasObject_ = true;
        if (it == object->value_.end()) {
            return;
        }
        if (std::holds_alternative<std::shared_ptr<OHOS::Media::PixelMap>>(it->second)) {
            auto pixelMap = std::get<std::shared_ptr<OHOS::Media::PixelMap>>(it->second);
            if (!pixelMap->EncodeTlv(rawData_)) {
                LOG_ERROR(UDMF_KITS_INNER, "pixelMap encode fail!");
            }
        } else if (std::holds_alternative<std::vector<uint8_t>>(it->second)) {
            rawData_ = std::get<std::vector<uint8_t>>(it->second);
        }
    }
}

int64_t SystemDefinedPixelMap::GetSize()
{
    return UnifiedDataUtils::GetDetailsSize(this->details_) + rawData_.size();
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
        auto pixelMap = std::shared_ptr<OHOS::Media::PixelMap>(OHOS::Media::PixelMap::DecodeTlv(rawData_));
        if (pixelMap == nullptr) {
            LOG_ERROR(UDMF_KITS_INNER, "pixelMap decode fail!");
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
        auto pixelMap = std::shared_ptr<OHOS::Media::PixelMap>(OHOS::Media::PixelMap::DecodeTlv(rawData_));
        if (pixelMap == nullptr) {
            LOG_ERROR(UDMF_KITS_INNER, "pixelMap decode fail!");
            object->value_[PIXEL_MAP] = rawData_;
        } else {
            object->value_[PIXEL_MAP] = pixelMap;
        }
        object->value_[DETAILS] = ObjectUtils::ConvertToObject(details_);
        object->value_["VALUE_TYPE"] = value;
    }
}

} // namespace UDMF
} // namespace OHOS