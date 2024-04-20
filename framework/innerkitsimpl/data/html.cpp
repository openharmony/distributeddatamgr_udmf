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
    if (std::holds_alternative<std::string>(value)) {
        htmlContent_ = std::get<std::string>(value);
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
}
} // namespace UDMF
} // namespace OHOS