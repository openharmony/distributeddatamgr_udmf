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
#define LOG_TAG "UDMF_FOLDER_TAIHE"

#include "logger.h"
#include "folder_taihe.h"
#include "taihe_common_utils.h"
#include "taihe/runtime.hpp"
#include "unified_record_taihe.h"

namespace OHOS {
namespace UDMF {
FolderTaihe::FolderTaihe()
{
    this->value_ = std::make_shared<Folder>();
}

::taihe::string FolderTaihe::GetType()
{
    return ::taihe::string(UtdUtils::GetUtdIdFromUtdEnum(this->value_->GetType()));
}

::taiheChannel::ValueType FolderTaihe::GetValue()
{
    return ConvertValueType(this->value_->GetValue());
}

::taihe::array<::taihe::string> FolderTaihe::GetTypes()
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

void FolderTaihe::AddEntry(::taihe::string_view type, ::taiheChannel::ValueType value)
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
        this->value_ = std::make_shared<Folder>(utdType, valueType);
        if (!this->value_) {
            taihe::set_business_error(PARAMETERSERROR, "Parameter error: unsupported type");
            return;
        }
    } else {
        this->value_->AddEntry(std::string(type), std::move(valueType));
    }
    return;
}

::taiheChannel::ValueType FolderTaihe::GetEntry(::taihe::string_view type)
{
    if (!this->value_) {
        LOG_ERROR(UDMF_ANI, "Inner value is null.");
        taihe::set_business_error(PARAMETERSERROR, "invalid object!");
        return ::taiheChannel::ValueType::make_nullType();
    }
    return ConvertValueType(this->value_->GetEntry(std::string(type)));
}

::taihe::map<::taihe::string, ::taiheChannel::ValueType> FolderTaihe::GetEntries()
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

::taihe::string FolderTaihe::GetUri()
{
    return ::taihe::string(this->value_->GetUri());
}

void FolderTaihe::SetUri(const ::taihe::string_view &uri)
{
    std::string uriStr(uri);
    this->value_->SetUri(uriStr);
}

::taihe::optional<::taihe::map<::taihe::string, ::taihe::string>> FolderTaihe::GetDetails()
{
    return ::taihe::optional<::taihe::map<::taihe::string, ::taihe::string>>::make(
        ConvertUDDetailsToString(this->value_->GetDetails()));
}

void FolderTaihe::SetDetails(const ::taihe::map_view<::taihe::string, ::taihe::string> &details)
{
    if (details.size() == 0) {
        return;
    }
    auto udmfDetails = ConvertUDDetails(details);
    this->value_->SetDetails(udmfDetails);
}

::taihe::string FolderTaihe::GetFolderUri()
{
    return ::taihe::string(this->value_->GetUri());
}

void FolderTaihe::SetFolderUri(const ::taihe::string_view &folderUri)
{
    std::string folderUriStr(folderUri);
    this->value_->SetUri(folderUriStr);
}

int64_t FolderTaihe::GetInner()
{
    return reinterpret_cast<int64_t>(this);
}
} // namespace UDMF
} // namespace OHOS

::taiheChannel::FolderInner CreateUnifiedFolder()
{
    return taihe::make_holder<OHOS::UDMF::FolderTaihe, ::taiheChannel::FolderInner>();
}

TH_EXPORT_CPP_API_CreateUnifiedFolder(CreateUnifiedFolder);