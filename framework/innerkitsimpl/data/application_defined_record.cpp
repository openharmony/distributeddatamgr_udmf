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

#include "application_defined_record.h"

namespace OHOS {
namespace UDMF {
ApplicationDefinedRecord::ApplicationDefinedRecord() : UnifiedRecord(APPLICATION_DEFINED_RECORD)
{
}

ApplicationDefinedRecord::ApplicationDefinedRecord(std::string type) : UnifiedRecord(APPLICATION_DEFINED_RECORD)
{
    this->applicationDefinedType = std::move(type);
}

ApplicationDefinedRecord::ApplicationDefinedRecord(std::string type, std::vector<uint8_t> &data)
    : UnifiedRecord(APPLICATION_DEFINED_RECORD)
{
    this->applicationDefinedType = std::move(type);
    this->rawData_ = std::move(data);
}

ApplicationDefinedRecord::ApplicationDefinedRecord(UDType type, ValueType value) : UnifiedRecord(type, value)
{
    if (std::holds_alternative<std::vector<uint8_t>>(value)) {
        rawData_ = std::get<std::vector<uint8_t>>(value);
    }
}

int64_t ApplicationDefinedRecord::GetSize()
{
    return rawData_.size() + applicationDefinedType.size();
}

std::string ApplicationDefinedRecord::GetApplicationDefinedType() const
{
    return this->applicationDefinedType;
}

void ApplicationDefinedRecord::SetApplicationDefinedType(const std::string &type)
{
    this->applicationDefinedType = type;
}

std::vector<uint8_t> ApplicationDefinedRecord::GetRawData() const
{
    return this->rawData_;
}

void ApplicationDefinedRecord::SetRawData(const std::vector<uint8_t> &rawData)
{
    this->rawData_ = rawData;
}
} // namespace UDMF
} // namespace OHOS
