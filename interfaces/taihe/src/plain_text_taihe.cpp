/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "plain_text_taihe.h"
#include "taihe_common_utils.h"
namespace OHOS {
namespace UDMF {
PlainTextTaihe::PlainTextTaihe()
{
    this->value_ = std::make_shared<PlainText>();
}

::taihe::string PlainTextTaihe::GetType()
{
    return ::taihe::string(UtdUtils::GetUtdIdFromUtdEnum(this->value_->GetType()));
}

::taiheChannel::ValueType PlainTextTaihe::GetValue()
{
    return ConvertValueType(this->value_->GetValue());
}

::taihe::optional<::taihe::map<::taihe::string, ::taihe::string>> PlainTextTaihe::GetDetails()
{
    return ::taihe::optional<::taihe::map<::taihe::string, ::taihe::string>>::make(
        ConvertUDDetailsToString(this->value_->GetDetails()));
}

void PlainTextTaihe::SetDetails(::taihe::map_view<::taihe::string, ::taihe::string> details)
{
    if (details.size() == 0) {
        return;
    }
    auto udmfDetails = ConvertUDDetails(details);
    this->value_->SetDetails(udmfDetails);
}

void PlainTextTaihe::SetTextContent(::taihe::string_view textContent)
{
    std::string content(textContent);
    this->value_->SetContent(content);
}

::taihe::string PlainTextTaihe::GetTextContent()
{
    return ::taihe::string(this->value_->GetContent());
}

int64_t PlainTextTaihe::GetInner()
{
    return reinterpret_cast<int64_t>(this);
}
} // namespace UDMF
} // namespace OHOS

::taiheChannel::PlainTextInner CreatePlainText()
{
    return taihe::make_holder<OHOS::UDMF::PlainTextTaihe, ::taiheChannel::PlainTextInner>();
}

TH_EXPORT_CPP_API_CreatePlainText(CreatePlainText);