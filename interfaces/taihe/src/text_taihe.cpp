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

#include "text_taihe.h"
#include "taihe_common_utils.h"

TextInnerImpl::TextInnerImpl()
{
    this->value_ = std::make_shared<taiheUdmf::Text>();
}

::taihe::string TextInnerImpl::GetType()
{
    return ::taihe::string(taiheUdmf::UtdUtils::GetUtdIdFromUtdEnum(this->value_->GetType()));
}

::ohos::data::unifiedDataChannel::ValueType TextInnerImpl::GetValue()
{
    return taiheUdmf::ConvertValueType(this->value_->GetValue());
}

::taihe::optional<::taihe::map<::taihe::string, ::taihe::string>> TextInnerImpl::GetDetails()
{
    return ::taihe::optional<::taihe::map<::taihe::string, ::taihe::string>>::make(
        taiheUdmf::ConvertUDDetailsToString(this->value_->GetDetails()));
}

void TextInnerImpl::SetDetails(::taihe::map_view<::taihe::string, ::taihe::string> details)
{
    if (details.size() == 0) {
        return;
    }
    auto udmfDetails = taiheUdmf::ConvertUDDetails(details);
    this->value_->SetDetails(udmfDetails);
}

int64_t TextInnerImpl::GetInner()
{
    return reinterpret_cast<int64_t>(this);
}



::ohos::data::unifiedDataChannel::TextInner CreateText()
{
    return taihe::make_holder<TextInnerImpl, ::ohos::data::unifiedDataChannel::TextInner>();
}

TH_EXPORT_CPP_API_CreateText(CreateText);