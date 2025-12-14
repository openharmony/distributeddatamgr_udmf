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
#define LOG_TAG "UDMF_HTML_TAIHE"

#include "logger.h"
#include "html_taihe.h"
#include "taihe_common_utils.h"
#include "taihe/runtime.hpp"
#include "unified_record_taihe.h"

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

::taihe::array<::taihe::string> HtmlTaihe::GetTypes()
{
    std::vector<std::string> res;
    if (!this->value_) {
        LOG_ERROR(UDMF_ANI, "Inner value is null.");
        taihe::set_business_error(PARAMETERSERROR, "invalid object!");
        return ::taihe::array<::taihe::string>(taihe::copy_data_t{}, res.data(), res.size());
    }
    res = this->value_->GetTypes();
    return ::taihe::array<::taihe::string>(taihe::copy_data_t{}, res.data(), res.size());
}

void HtmlTaihe::AddEntry(::taihe::string_view type, ::taiheChannel::ValueType value)
{
    if (type.empty()) {
        LOG_ERROR(UDMF_ANI, "Inner value is empty.");
        taihe::set_business_error(PARAMETERSERROR, "Parameter error: parameter type must be string");
        return;
    }

    if (!this->value_) {
        LOG_ERROR(UDMF_ANI, "Inner value is null.");
        taihe::set_business_error(PARAMETERSERROR, "invalid object!");
        return;
    }
    ValueType valueType = ConvertValueType(::taihe::get_env(), type, value);

    if (this->value_->GetType() == UD_BUTT) {
        UDType utdType = APPLICATION_DEFINED_RECORD;
        if (UtdUtils::IsValidUtdId(std::string(type))) {
            utdType = static_cast<UDType>(UtdUtils::GetUtdEnumFromUtdId(std::string(type)));
        }
        this->value_ = std::make_shared<Html>(utdType, valueType);
        if (!this->value_) {
            taihe::set_business_error(PARAMETERSERROR, "Parameter error: unsupported type");
            return;
        }
    } else {
        this->value_->AddEntry(std::string(type), std::move(valueType));
    }
    return;
}

::taiheChannel::ValueType HtmlTaihe::GetEntry(::taihe::string_view type)
{
    if (!this->value_) {
        LOG_ERROR(UDMF_ANI, "Inner value is null.");
        taihe::set_business_error(PARAMETERSERROR, "invalid object!");
        return ::taiheChannel::ValueType::make_nullType();
    }
    return ConvertValueType(this->value_->GetEntry(std::string(type)));
}

::taihe::map<::taihe::string, ::taiheChannel::ValueType> HtmlTaihe::GetEntries()
{
    ::taihe::map<::taihe::string, ::taiheChannel::ValueType> res;
    if (!this->value_) {
        LOG_ERROR(UDMF_ANI, "Inner value is null.");
        taihe::set_business_error(PARAMETERSERROR, "invalid object!");
        return res;
    }
    auto entries = this->value_->GetEntries();
    if (!entries) {
        LOG_ERROR(UDMF_ANI, "entries value is null.");
        return res;
    }
    for (auto &entry : *entries) {
        res.emplace(::taihe::string(entry.first), ConvertValueType(entry.second));
    }
    return res;
}

::taihe::optional<::taihe::map<::taihe::string, ::taihe::string>> HtmlTaihe::GetDetails()
{
    return ::taihe::optional<::taihe::map<::taihe::string, ::taihe::string>>::make(
        ConvertUDDetailsToString(this->value_->GetDetails()));
}

void HtmlTaihe::SetDetails(const ::taihe::map_view<::taihe::string, ::taihe::string> &details)
{
    if (details.size() == 0) {
        return;
    }
    auto udmfDetails = ConvertUDDetails(details);
    this->value_->SetDetails(udmfDetails);
}

void HtmlTaihe::SetHtmlContent(const ::taihe::string_view &htmlContent)
{
    std::string content(htmlContent);
    this->value_->SetHtmlContent(content);
}

::taihe::string HtmlTaihe::GetHtmlContent()
{
    return ::taihe::string(this->value_->GetHtmlContent());
}

void HtmlTaihe::SetPlainContent(const ::taihe::string_view &plainContent)
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