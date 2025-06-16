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

#include "html_taihe.h"
#include "taihe_common_utils.h"
namespace OHOS {
namespace UDMF {
HtmlTaihe::HtmlTaihe()
{
    this->value_ = std::make_shared<Html>();
}

::taihe::string HtmlTaihe::GetType()
{
    return ::taihe::string(UtdUtils::GetUtdIdFromUtdEnum(this->value_->GetType()));
}

::taiheChannel::ValueType HtmlTaihe::GetValue()
{
    return ConvertValueType(this->value_->GetValue());
}

::taihe::optional<::taihe::map<::taihe::string, ::taihe::string>> HtmlTaihe::GetDetails()
{
    return ::taihe::optional<::taihe::map<::taihe::string, ::taihe::string>>::make(
        ConvertUDDetailsToString(this->value_->GetDetails()));
}

void HtmlTaihe::SetDetails(::taihe::map_view<::taihe::string, ::taihe::string> details)
{
    if (details.size() == 0) {
        return;
    }
    auto udmfDetails = ConvertUDDetails(details);
    this->value_->SetDetails(udmfDetails);
}

void HtmlTaihe::SetHtmlContent(::taihe::string_view htmlContent)
{
    std::string content(htmlContent);
    this->value_->SetHtmlContent(content);
}

::taihe::string HtmlTaihe::GetHtmlContent()
{
    return ::taihe::string(this->value_->GetHtmlContent());
}

void HtmlTaihe::SetPlainContent(::taihe::string_view plainContent)
{
    std::string content(plainContent);
    this->value_->SetPlainContent(content);
}

::taihe::string HtmlTaihe::GetPlainContent()
{
    return ::taihe::string(this->value_->GetPlainContent());
}

int64_t HtmlTaihe::GetInner()
{
    return reinterpret_cast<int64_t>(this);
}
} // namespace UDMF
} // namespace OHOS

::taiheChannel::HTMLInner CreateHtml()
{
    return taihe::make_holder<OHOS::UDMF::HtmlTaihe, ::taiheChannel::HTMLInner>();
}

TH_EXPORT_CPP_API_CreateHtml(CreateHtml);