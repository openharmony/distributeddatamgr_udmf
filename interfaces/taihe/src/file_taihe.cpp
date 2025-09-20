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

#include "file_taihe.h"
#include "taihe_common_utils.h"

namespace OHOS {
namespace UDMF {
FileTaihe::FileTaihe()
{
    this->value_ = std::make_shared<File>();
}

::taihe::string FileTaihe::GetType()
{
    return ::taihe::string(UtdUtils::GetUtdIdFromUtdEnum(this->value_->GetType()));
}

::taiheChannel::ValueType FileTaihe::GetValue()
{
    return ConvertValueType(this->value_->GetValue());
}

::taihe::string FileTaihe::GetUri()
{
    return ::taihe::string(this->value_->GetUri());
}

void FileTaihe::SetUri(const ::taihe::string_view &uri)
{
    std::string uriStr(uri);
    this->value_->SetUri(uriStr);
}

::taihe::optional<::taihe::map<::taihe::string, ::taihe::string>> FileTaihe::GetDetails()
{
    return ::taihe::optional<::taihe::map<::taihe::string, ::taihe::string>>::make(
        ConvertUDDetailsToString(this->value_->GetDetails()));
}

void FileTaihe::SetDetails(const ::taihe::map_view<::taihe::string, ::taihe::string> &details)
{
    if (details.size() == 0) {
        return;
    }
    auto udmfDetails = ConvertUDDetails(details);
    this->value_->SetDetails(udmfDetails);
}

int64_t FileTaihe::GetInner()
{
    return reinterpret_cast<int64_t>(this);
}
} // namespace UDMF
} // namespace OHOS

::taiheChannel::FileInner CreateUnifiedFile()
{
    return taihe::make_holder<OHOS::UDMF::FileTaihe, ::taiheChannel::FileInner>();
}

TH_EXPORT_CPP_API_CreateUnifiedFile(CreateUnifiedFile);