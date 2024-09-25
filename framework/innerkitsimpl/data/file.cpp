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

#include "file.h"

namespace OHOS {
namespace UDMF {
File::File() : UnifiedRecord(FILE)
{
}

File::File(const std::string &uri) : UnifiedRecord(FILE)
{
    this->oriUri_ = uri;
}

File::File(UDType type, ValueType value) : UnifiedRecord(type, value)
{
    this->dataType_ = FILE;
    if (std::holds_alternative<std::string>(value)) {
        oriUri_ = std::get<std::string>(value);
    } else if (std::holds_alternative<std::shared_ptr<Object>>(value)) {
        auto object = std::get<std::shared_ptr<Object>>(value);
        object->GetValue(ORI_URI, oriUri_);
        object->GetValue(REMOTE_URI, remoteUri_);
        std::shared_ptr<Object> detailObj = nullptr;
        if (object->GetValue(DETAILS, detailObj)) {
            details_ = ObjectUtils::ConvertToUDDetails(detailObj);
        }
        hasObject_ = true;
    }
}

int64_t File::GetSize()
{
    return this->oriUri_.size() + this->remoteUri_.size();
}

std::string File::GetUri() const
{
    return this->oriUri_;
}

void File::SetUri(const std::string &uri)
{
    this->oriUri_ = uri;
    if (std::holds_alternative<std::shared_ptr<Object>>(value_)) {
        auto object = std::get<std::shared_ptr<Object>>(value_);
        object->value_[ORI_URI] = oriUri_;
    }
}

std::string File::GetRemoteUri() const
{
    return this->remoteUri_;
}

void File::SetRemoteUri(const std::string &uri)
{
    this->remoteUri_ = uri;
    if (std::holds_alternative<std::shared_ptr<Object>>(value_)) {
        auto object = std::get<std::shared_ptr<Object>>(value_);
        object->value_[REMOTE_URI] = remoteUri_;
    }
}

void File::SetDetails(UDDetails &variantMap)
{
    this->details_ = variantMap;
    if (std::holds_alternative<std::shared_ptr<Object>>(value_)) {
        auto object = std::get<std::shared_ptr<Object>>(value_);
        object->value_[DETAILS] = ObjectUtils::ConvertToObject(details_);
    }
}

UDDetails File::GetDetails() const
{
    return this->details_;
}

void File::InitObject()
{
    if (!std::holds_alternative<std::shared_ptr<Object>>(value_)) {
        auto value = value_;
        value_ = std::make_shared<Object>();
        auto object = std::get<std::shared_ptr<Object>>(value_);
        object->value_[UNIFORM_DATA_TYPE] = UtdUtils::GetUtdIdFromUtdEnum(dataType_);
        object->value_[ORI_URI] = oriUri_;
        object->value_[REMOTE_URI] = remoteUri_;
        object->value_[DETAILS] = ObjectUtils::ConvertToObject(details_);
        object->value_[VALUE_TYPE] = value;
    }
}

} // namespace UDMF
} // namespace OHOS
