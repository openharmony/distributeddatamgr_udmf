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

#include "system_defined_record.h"

namespace OHOS {
namespace UDMF {
SystemDefinedRecord::SystemDefinedRecord() : UnifiedRecord(SYSTEM_DEFINED_RECORD)
{
}

int64_t SystemDefinedRecord::GetSize()
{
    return UnifiedDataUtils::GetDetailsSize(this->details_);
}

SystemDefinedRecord::SystemDefinedRecord(UDType type, ValueType value) : UnifiedRecord(type, value) {}

void SystemDefinedRecord::AddProperty(const std::string &property, UDVariant &value)
{
    auto it = details_.find(property);
    if (it == details_.end()) {
        details_.insert(std::make_pair(property, value));
    } else {
        details_[property] = value;
    }
}

UDVariant SystemDefinedRecord::GetPropertyByName(const std::string &property) const
{
    auto it = details_.find(property);
    if (it == details_.end()) {
        return nullptr;
    }
    return it->second;
}

void SystemDefinedRecord::SetDetails(UDDetails &details)
{
    this->details_ = details;
}

UDDetails SystemDefinedRecord::GetDetails() const
{
    return this->details_;
}
} // namespace UDMF
} // namespace OHOS