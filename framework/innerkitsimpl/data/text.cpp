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
}

int64_t Text::GetSize()
{
    return UnifiedDataUtils::GetDetailsSize(this->details_);
}

void Text::SetDetails(UDDetails &variantMap)
{
    this->details_ = variantMap;
    InitObject();
}

UDDetails Text::GetDetails() const
{
    return this->details_;
}

void Text::InitObject()
{
    if (std::holds_alternative<std::shared_ptr<Object>>(value_)) {
        auto object = std::get<std::shared_ptr<Object>>(value_);
        object->value_[DETAILS] = ObjectUtils::ConvertToObject(details_);
    }
}
} // namespace UDMF
} // namespace OHOS
