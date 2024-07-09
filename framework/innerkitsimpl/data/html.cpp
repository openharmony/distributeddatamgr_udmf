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

#include "html.h"

namespace OHOS {
namespace UDMF {
Html::Html()
{
    this->dataType_ = HTML;
}

Html::Html(const std::string &htmlContent, const std::string &plainContent)
{
    if (plainContent.length() >= MAX_TEXT_LEN || htmlContent.length() >= MAX_TEXT_LEN) {
        return;
    }
    this->dataType_ = HTML;
    this->htmlContent_ = htmlContent;
    this->plainContent_ = plainContent;
}

Html::Html(UDType type, ValueType value) : Text(type, value)
{
    this->dataType_ = HTML;
    if (std::holds_alternative<std::string>(value)) {
        htmlContent_ = std::get<std::string>(value);
    } else if (std::holds_alternative<std::shared_ptr<Object>>(value)) {
        auto object = std::get<std::shared_ptr<Object>>(value);
        object->GetValue(HTML_CONTENT, htmlContent_);
        object->GetValue(PLAINT_CONTENT, plainContent_);
        std::shared_ptr<Object> detailObj = nullptr;
        if (object->GetValue(DETAILS, detailObj)) {
            details_ = ObjectUtils::ConvertToUDDetails(detailObj);
        }
    }
}

int64_t Html::GetSize()
{
    return UnifiedDataUtils::GetDetailsSize(this->details_) + this->htmlContent_.size() + this->plainContent_.size();
}

std::string Html::GetHtmlContent() const
{
    return this->htmlContent_;
}

void Html::SetHtmlContent(const std::string &htmlContent)
{
    if (htmlContent.length() >= MAX_TEXT_LEN) {
        return;
    }
    this->htmlContent_ = htmlContent;
    InitObject();
}

std::string Html::GetPlainContent() const
{
    return this->plainContent_;
}

void Html::SetPlainContent(const std::string &plainContent)
{
    if (plainContent.length() >= MAX_TEXT_LEN) {
        return;
    }
    this->plainContent_ = plainContent;
    InitObject();
}

ValueType Html::GetValue()
{
    if (std::holds_alternative<std::monostate>(value_)) {
        value_ = std::make_shared<Object>();
    }
    InitObject();
    return value_;
}

void Html::InitObject()
{
    if (std::holds_alternative<std::shared_ptr<Object>>(value_)) {
        auto object = std::get<std::shared_ptr<Object>>(value_);
        object->value_[UNIFORM_DATA_TYPE] = UtdUtils::GetUtdIdFromUtdEnum(dataType_);
        object->value_[HTML_CONTENT] = htmlContent_;
        object->value_[PLAINT_CONTENT] = plainContent_;
        object->value_[DETAILS] = ObjectUtils::ConvertToObject(details_);
    }
}

bool Html::CheckValue(const ValueType &value)
{
    if (!std::holds_alternative<std::shared_ptr<Object>>(value)) {
        return true;
    }
    auto object = std::get<std::shared_ptr<Object>>(value);

    bool IsValid = true;
    IsValid = IsValid && object->HasStrValue(UNIFORM_DATA_TYPE);
    IsValid = IsValid && object->HasStrValue(HTML_CONTENT);

    auto isValidDetail = [](const auto& pair) {
        return std::holds_alternative<std::string>(pair.second);
    };
    std::shared_ptr<Object> detailObj = nullptr;
    if (object->GetValue(DETAILS, detailObj)) {
        IsValid = IsValid && std::all_of(detailObj->value_.begin(), detailObj->value_.end(), isValidDetail);
    }

    auto isValidKey = [](const auto& pair) {
        const std::string &key = pair.first;
        return key == UNIFORM_DATA_TYPE || key == HTML_CONTENT || key == PLAINT_CONTENT || key == DETAILS;
    };
    IsValid = IsValid && std::all_of(object->value_.begin(), object->value_.end(), isValidKey);
    return IsValid;
}
} // namespace UDMF
} // namespace OHOS