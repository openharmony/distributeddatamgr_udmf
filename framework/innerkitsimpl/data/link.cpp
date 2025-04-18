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

#include "link.h"

namespace OHOS {
namespace UDMF {
Link::Link() : Link("", "")
{
}

Link::Link(const std::string &url) : Link(url, "")
{
}

Link::Link(UDType type, ValueType value) : Text(type, value)
{
    SetType(HYPERLINK);
    if (std::holds_alternative<std::string>(value)) {
        url_ = std::get<std::string>(value);
    } else if (std::holds_alternative<std::shared_ptr<Object>>(value)) {
        auto object = std::get<std::shared_ptr<Object>>(value);
        object->GetValue(URL, url_);
        object->GetValue(DESCRIPTION, description_);
        std::shared_ptr<Object> detailObj = nullptr;
        if (object->GetValue(DETAILS, detailObj)) {
            details_ = ObjectUtils::ConvertToUDDetails(detailObj);
        }
    }
}

Link::Link(const std::string &url, const std::string &description)
{
    if (url.length() >= MAX_TEXT_LEN || description.length() >= MAX_TEXT_LEN) {
        return;
    }
    SetType(HYPERLINK);
    this->url_ = url;
    this->description_ = description;
}

int64_t Link::GetSize()
{
    return static_cast<int64_t>(UnifiedDataUtils::GetDetailsSize(this->details_) + this->url_.size() +
        this->description_.size()) + GetInnerEntriesSize();
}

std::string Link::GetUrl() const
{
    return this->url_;
}

void Link::SetUrl(const std::string &url)
{
    if (url.length() >= MAX_TEXT_LEN) {
        return;
    }
    this->url_ = url;
    if (std::holds_alternative<std::shared_ptr<Object>>(value_)) {
        std::get<std::shared_ptr<Object>>(value_)->value_[URL] = url_;
    }
}

std::string Link::GetDescription() const
{
    return this->description_;
}

void Link::SetDescription(const std::string &description)
{
    if (description.length() >= MAX_TEXT_LEN) {
        return;
    }
    this->description_ = description;
    if (std::holds_alternative<std::shared_ptr<Object>>(value_)) {
        std::get<std::shared_ptr<Object>>(value_)->value_[DESCRIPTION] = description_;
    }
}

void Link::InitObject()
{
    if (!std::holds_alternative<std::shared_ptr<Object>>(value_)) {
        auto value = value_;
        value_ = std::make_shared<Object>();
        auto object = std::get<std::shared_ptr<Object>>(value_);
        object->value_[UNIFORM_DATA_TYPE] = UtdUtils::GetUtdIdFromUtdEnum(dataType_);
        object->value_[URL] = url_;
        object->value_[DESCRIPTION] = description_;
        object->value_[DETAILS] = ObjectUtils::ConvertToObject(details_);
        object->value_.insert_or_assign(VALUE_TYPE, std::move(value));
    }
}
} // namespace UDMF
} // namespace OHOS