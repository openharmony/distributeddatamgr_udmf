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

#include "plain_text.h"

namespace OHOS {
namespace UDMF {
PlainText::PlainText() : PlainText("", "")
{
}

PlainText::PlainText(const std::string &content, const std::string &abstract)
{
    if (content.length() >= MAX_TEXT_LEN) {
        return;
    }
    this->dataType_ = PLAIN_TEXT;
    this->content_ = content;
    this->abstract_ = abstract;
}

PlainText::PlainText(UDType type, ValueType value) : Text(type, value)
{
    if (std::holds_alternative<std::string>(value)) {
        content_ = std::get<std::string>(value);
    }
}

int64_t PlainText::GetSize()
{
    return UnifiedDataUtils::GetDetailsSize(this->details_) + this->content_.size() + this->abstract_.size();
}

std::string PlainText::GetContent() const
{
    return this->content_;
}

void PlainText::SetContent(const std::string &text)
{
    if (text.length() >= MAX_TEXT_LEN) {
        return;
    }
    this->content_ = text;
}

std::string PlainText::GetAbstract() const
{
    return this->abstract_;
}

void PlainText::SetAbstract(const std::string &abstract)
{
    if (abstract.length() >= MAX_TEXT_LEN) {
        return;
    }
    this->abstract_ = abstract;
}
} // namespace UDMF
} // namespace OHOS
