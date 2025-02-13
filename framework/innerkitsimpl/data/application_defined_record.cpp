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
    SetUtdId(this->applicationDefinedType);
}

ApplicationDefinedRecord::ApplicationDefinedRecord(std::string type, std::vector<uint8_t> &data)
    : UnifiedRecord(APPLICATION_DEFINED_RECORD)
{
    this->applicationDefinedType = std::move(type);
    this->rawData_ = std::move(data);
    SetUtdId(this->applicationDefinedType);
}

ApplicationDefinedRecord::ApplicationDefinedRecord(UDType type, ValueType value)
    : UnifiedRecord(type, value)
{
    this->dataType_ = APPLICATION_DEFINED_RECORD;
    if (std::holds_alternative<std::vector<uint8_t>>(value)) {
        rawData_ = std::get<std::vector<uint8_t>>(value);
    } else if (std::holds_alternative<std::shared_ptr<Object>>(value)) {
        auto object = std::get<std::shared_ptr<Object>>(value);
        object->GetValue(APPLICATION_DEFINED_TYPE, applicationDefinedType);
        object->GetValue(RAW_DATA, rawData_);
        hasObject_ = true;
    }
    if (applicationDefinedType.empty()) {
        applicationDefinedType = UtdUtils::GetUtdIdFromUtdEnum(type);
    }
    SetUtdId(this->applicationDefinedType);
}

int64_t ApplicationDefinedRecord::GetSize()
{
    return static_cast<int64_t>(rawData_.size()) + GetInnerEntriesSize();
}

std::string ApplicationDefinedRecord::GetApplicationDefinedType() const
{
    return this->applicationDefinedType;
}

void ApplicationDefinedRecord::SetApplicationDefinedType(const std::string &type)
{
    this->applicationDefinedType = type;
    if (std::holds_alternative<std::shared_ptr<Object>>(value_)) {
        auto object = std::get<std::shared_ptr<Object>>(value_);
        object->value_[APPLICATION_DEFINED_TYPE] = applicationDefinedType;
    }
}

std::vector<uint8_t> ApplicationDefinedRecord::GetRawData() const
{
    return this->rawData_;
}

void ApplicationDefinedRecord::SetRawData(const std::vector<uint8_t> &rawData)
{
    this->rawData_ = rawData;
    if (std::holds_alternative<std::shared_ptr<Object>>(value_)) {
        auto object = std::get<std::shared_ptr<Object>>(value_);
        object->value_[RAW_DATA] = rawData_;
    }
}

void ApplicationDefinedRecord::InitObject()
{
    if (!std::holds_alternative<std::shared_ptr<Object>>(value_)) {
        auto value = value_;
        value_ = std::make_shared<Object>();
        auto object = std::get<std::shared_ptr<Object>>(value_);
        object->value_[UNIFORM_DATA_TYPE] = UtdUtils::GetUtdIdFromUtdEnum(dataType_);
        object->value_[APPLICATION_DEFINED_TYPE] = applicationDefinedType;
        object->value_[RAW_DATA] = rawData_;
        object->value_[APPLICATION_DEFINED_RECORD_MARK] = true;
        object->value_.insert_or_assign(VALUE_TYPE, std::move(value));
    }
}

} // namespace UDMF
} // namespace OHOS
