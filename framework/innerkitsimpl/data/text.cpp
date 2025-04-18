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

#include "text.h"

namespace OHOS {
namespace UDMF {
Text::Text() : UnifiedRecord(TEXT)
{
}

Text::Text(UDDetails &variantMap) : UnifiedRecord(TEXT)
{
    this->details_ = variantMap;
}

Text::Text(UDType type, ValueType value) : UnifiedRecord(type, value)
{
    SetType(TEXT);
    if (std::holds_alternative<std::shared_ptr<Object>>(value)) {
        auto object = std::get<std::shared_ptr<Object>>(value);
        std::shared_ptr<Object> detailObj = nullptr;
        if (object->GetValue(DETAILS, detailObj)) {
            details_ = ObjectUtils::ConvertToUDDetails(detailObj);
        }
    }
}

int64_t Text::GetSize()
{
    return static_cast<int64_t>(UnifiedDataUtils::GetDetailsSize(this->details_)) + GetInnerEntriesSize();
}

void Text::SetDetails(UDDetails &variantMap)
{
    this->details_ = variantMap;
    if (std::holds_alternative<std::shared_ptr<Object>>(value_)) {
        std::get<std::shared_ptr<Object>>(value_)->value_[DETAILS] = ObjectUtils::ConvertToObject(details_);
    }
}

UDDetails Text::GetDetails() const
{
    return this->details_;
}

void Text::InitObject()
{
    if (!std::holds_alternative<std::shared_ptr<Object>>(value_)) {
        auto value = value_;
        value_ = std::make_shared<Object>();
        auto object = std::get<std::shared_ptr<Object>>(value_);
        object->value_[DETAILS] = ObjectUtils::ConvertToObject(details_);
        object->value_.insert_or_assign(VALUE_TYPE, std::move(value));
    }
}
} // namespace UDMF
} // namespace OHOS
