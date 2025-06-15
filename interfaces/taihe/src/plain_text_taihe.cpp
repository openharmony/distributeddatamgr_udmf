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

PlainTextInnerImpl::PlainTextInnerImpl()
{
    this->value_ = std::make_shared<taiheUdmf::PlainText>();
}

::taihe::string PlainTextInnerImpl::GetType()
{
    return ::taihe::string(taiheUdmf::UtdUtils::GetUtdIdFromUtdEnum(this->value_->GetType()));
}

::ohos::data::unifiedDataChannel::ValueType PlainTextInnerImpl::GetValue()
{
    return taiheUdmf::ConvertValueType(this->value_->GetValue());
}

::taihe::optional<::taihe::map<::taihe::string, ::taihe::string>> PlainTextInnerImpl::GetDetails()
{
    return ::taihe::optional<::taihe::map<::taihe::string, ::taihe::string>>::make(
        taiheUdmf::ConvertUDDetailsToString(this->value_->GetDetails()));
}

void PlainTextInnerImpl::SetDetails(::taihe::map_view<::taihe::string, ::taihe::string> details)
{
    if (details.size() == 0) {
        return;
    }
    auto udmfDetails = taiheUdmf::ConvertUDDetails(details);
    this->value_->SetDetails(udmfDetails);
}

void PlainTextInnerImpl::SetTextContent(::taihe::string_view textContent)
{
    std::string content(textContent);
    this->value_->SetContent(content);
}

::taihe::string PlainTextInnerImpl::GetTextContent()
{
    return ::taihe::string(this->value_->GetContent());
}

int64_t PlainTextInnerImpl::GetInner()
{
    return reinterpret_cast<int64_t>(this);
}



::ohos::data::unifiedDataChannel::PlainTextInner CreatePlainText()
{
    return taihe::make_holder<PlainTextInnerImpl, ::ohos::data::unifiedDataChannel::PlainTextInner>();
}

TH_EXPORT_CPP_API_CreatePlainText(CreatePlainText);