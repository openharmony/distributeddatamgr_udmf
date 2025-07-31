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

#include "hyperlink_taihe.h"
#include "taihe_common_utils.h"

namespace OHOS {
namespace UDMF {
HyperlinkTaihe::HyperlinkTaihe()
{
    this->value_ = std::make_shared<Link>();
}

::taihe::string HyperlinkTaihe::GetType()
{
    return ::taihe::string(UtdUtils::GetUtdIdFromUtdEnum(this->value_->GetType()));
}

::taiheChannel::ValueType HyperlinkTaihe::GetValue()
{
    return ConvertValueType(this->value_->GetValue());
}

::taihe::optional<::taihe::map<::taihe::string, ::taihe::string>> HyperlinkTaihe::GetDetails()
{
    return ::taihe::optional<::taihe::map<::taihe::string, ::taihe::string>>::make(
        ConvertUDDetailsToString(this->value_->GetDetails()));
}

void HyperlinkTaihe::SetDetails(const ::taihe::map_view<::taihe::string, ::taihe::string> &details)
{
    if (details.size() == 0) {
        return;
    }
    auto udmfDetails = ConvertUDDetails(details);
    this->value_->SetDetails(udmfDetails);
}

void HyperlinkTaihe::SetUrl(const ::taihe::string_view &url)
{
    std::string urlStr(url);
    this->value_->SetUrl(urlStr);
}

::taihe::string HyperlinkTaihe::GetUrl()
{
    return ::taihe::string(this->value_->GetUrl());
}

void HyperlinkTaihe::SetDescription(const ::taihe::string_view &description)
{
    std::string desc(description);
    this->value_->SetDescription(desc);
}

::taihe::string HyperlinkTaihe::GetDescription()
{
    return ::taihe::string(this->value_->GetDescription());
}

int64_t HyperlinkTaihe::GetInner()
{
    return reinterpret_cast<int64_t>(this);
}
} // namespace UDMF
} // namespace OHOS

::taiheChannel::HyperlinkInner CreateHyperlink()
{
    return taihe::make_holder<OHOS::UDMF::HyperlinkTaihe, ::taiheChannel::HyperlinkInner>();
}

TH_EXPORT_CPP_API_CreateHyperlink(CreateHyperlink);