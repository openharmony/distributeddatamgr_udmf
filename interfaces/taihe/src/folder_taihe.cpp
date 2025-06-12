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

#include "folder_taihe.h"
#include "taihe_common_utils.h"

FolderInnerImpl::FolderInnerImpl()
{
    this->value_ = std::make_shared<taiheUdmf::Folder>();
}

::taihe::string FolderInnerImpl::GetType()
{
    return ::taihe::string(taiheUdmf::UtdUtils::GetUtdIdFromUtdEnum(this->value_->GetType()));
}

::ohos::data::unifiedDataChannel::ValueType FolderInnerImpl::GetValue()
{
    return taiheUdmf::ConvertValueType(this->value_->GetValue());
}

::taihe::string FolderInnerImpl::GetUri()
{
    return ::taihe::string(this->value_->GetUri());
}

void FolderInnerImpl::SetUri(::taihe::string_view uri)
{
    std::string uriStr(uri);
    this->value_->SetUri(uriStr);
}

::taihe::optional<::taihe::map<::taihe::string, ::taihe::string>> FolderInnerImpl::GetDetails()
{
    return ::taihe::optional<::taihe::map<::taihe::string, ::taihe::string>>::make(
        taiheUdmf::ConvertUDDetailsToString(this->value_->GetDetails()));
}

void FolderInnerImpl::SetDetails(::taihe::map_view<::taihe::string, ::taihe::string> details)
{
    if (details.size() == 0) {
        return;
    }
    auto udmfDetails = taiheUdmf::ConvertUDDetails(details);
    this->value_->SetDetails(udmfDetails);
}

::taihe::string FolderInnerImpl::GetFolderUri()
{
    return ::taihe::string(this->value_->GetUri());
}

void FolderInnerImpl::SetFolderUri(::taihe::string_view folderUri)
{
    std::string folderUriStr(folderUri);
    this->value_->SetUri(folderUriStr);
}

int64_t FolderInnerImpl::GetInner()
{
    return reinterpret_cast<int64_t>(this);
}

::ohos::data::unifiedDataChannel::FolderInner CreateUnifiedFolder()
{
    return taihe::make_holder<FolderInnerImpl, ::ohos::data::unifiedDataChannel::FolderInner>();
}

TH_EXPORT_CPP_API_CreateUnifiedFolder(CreateUnifiedFolder);