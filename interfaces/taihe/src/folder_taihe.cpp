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