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

#define LOG_TAG "PlainText"
#include "plain_text.h"
#include "logger.h"

namespace OHOS {
namespace UDMF {
PlainText::PlainText() : PlainText("", "")
{
    SetType(PLAIN_TEXT);
}

PlainText::PlainText(const std::string &content, const std::string &abstract)
{
    if (content.length() >= MAX_TEXT_LEN) {
        LOG_ERROR(UDMF_KITS_INNER, "content is too long, content.length:%{public}zu", content.length());
        return;
    }
    SetType(PLAIN_TEXT);
    this->content_ = content;
    this->abstract_ = abstract;
}

PlainText::PlainText(UDType type, ValueType value) : Text(type, value)
{
    SetType(PLAIN_TEXT);
    if (std::holds_alternative<std::string>(value)) {
        content_ = std::get<std::string>(value);
    } else if (std::holds_alternative<std::shared_ptr<Object>>(value)) {
        auto object = std::get<std::shared_ptr<Object>>(value);
        object->GetValue(CONTENT, content_);
        object->GetValue(ABSTRACT, abstract_);
        std::shared_ptr<Object> detailObj = nullptr;
        if (object->GetValue(DETAILS, detailObj)) {
            details_ = ObjectUtils::ConvertToUDDetails(detailObj);
        }
        hasObject_ = true;
    }
}

int64_t PlainText::GetSize()
{
    return UnifiedDataUtils::GetDetailsSize(this->details_) + this->content_.size() + this->abstract_.size() +
        GetInnerEntriesSize();
}

std::string PlainText::GetContent() const
{
    return this->content_;
}

void PlainText::SetContent(const std::string &text)
{
    if (text.length() >= MAX_TEXT_LEN) {
        LOG_ERROR(UDMF_KITS_INNER, "text is too long, text.length:%{public}zu", text.length());
        return;
    }
    this->content_ = text;
    if (std::holds_alternative<std::shared_ptr<Object>>(value_)) {
        auto object = std::get<std::shared_ptr<Object>>(value_);
        object->value_[CONTENT] = content_;
    }
}

std::string PlainText::GetAbstract() const
{
    return this->abstract_;
}

void PlainText::SetAbstract(const std::string &abstract)
{
    if (abstract.length() >= MAX_TEXT_LEN) {
        LOG_ERROR(UDMF_KITS_INNER, "abstract is too long!, abstract.length:%{public}zu", abstract.length());
        return;
    }
    this->abstract_ = abstract;
    if (std::holds_alternative<std::shared_ptr<Object>>(value_)) {
        auto object = std::get<std::shared_ptr<Object>>(value_);
        object->value_[ABSTRACT] = abstract_;
    }
}

void PlainText::InitObject()
{
    if (!std::holds_alternative<std::shared_ptr<Object>>(value_)) {
        auto value = value_;
        value_ = std::make_shared<Object>();
        auto object = std::get<std::shared_ptr<Object>>(value_);
        object->value_[UNIFORM_DATA_TYPE] = UtdUtils::GetUtdIdFromUtdEnum(dataType_);
        object->value_[CONTENT] = content_;
        object->value_[ABSTRACT] = abstract_;
        object->value_[DETAILS] = ObjectUtils::ConvertToObject(details_);
        object->value_.insert_or_assign(VALUE_TYPE, std::move(value));
    }
}
} // namespace UDMF
} // namespace OHOS
