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

HTMLInnerImpl::HTMLInnerImpl() {
    this->value_ = std::make_shared<taiheUdmf::Html>();
}

::taihe::string HTMLInnerImpl::GetType() {
    return ::taihe::string(taiheUdmf::UtdUtils::GetUtdIdFromUtdEnum(this->value_->GetType()));
}

::ohos::data::unifiedDataChannel::ValueType HTMLInnerImpl::GetValue() {
    return taiheUdmf::ConvertValueType(this->value_->GetValue());
}

::taihe::optional<::taihe::map<::taihe::string, ::taihe::string>> HTMLInnerImpl::GetDetails() {
    return ::taihe::optional<::taihe::map<::taihe::string, ::taihe::string>>::make(
        taiheUdmf::ConvertUDDetailsToString(this->value_->GetDetails()));
}

void HTMLInnerImpl::SetDetails(::taihe::map_view<::taihe::string, ::taihe::string> details) {
    if (details.size() == 0) {
        return;
    }
    auto udmfDetails = taiheUdmf::ConvertUDDetails(details);
    this->value_->SetDetails(udmfDetails);
}

void HTMLInnerImpl::SetHtmlContent(::taihe::string_view htmlContent) {
    std::string content(htmlContent);
    this->value_->SetHtmlContent(content);
}

::taihe::string HTMLInnerImpl::GetHtmlContent() {
    return ::taihe::string(this->value_->GetHtmlContent());
}

void HTMLInnerImpl::SetPlainContent(::taihe::string_view plainContent) {
    std::string content(plainContent);
    this->value_->SetPlainContent(content);
}

::taihe::string HTMLInnerImpl::GetPlainContent() {
    return ::taihe::string(this->value_->GetPlainContent());
}

int64_t HTMLInnerImpl::GetInner() {
    return reinterpret_cast<int64_t>(this);
}

::ohos::data::unifiedDataChannel::HTMLInner CreateHtml()
{
    return taihe::make_holder<HTMLInnerImpl, ::ohos::data::unifiedDataChannel::HTMLInner>();
}

TH_EXPORT_CPP_API_CreateHtml(CreateHtml);