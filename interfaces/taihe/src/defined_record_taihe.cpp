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

#include "defined_record_taihe.h"
#include "taihe_common_utils.h"

namespace OHOS {
namespace UDMF {
SystemDefinedRecordTaihe::SystemDefinedRecordTaihe()
{
    this->value_ = std::make_shared<SystemDefinedRecord>();
}

::taihe::string SystemDefinedRecordTaihe::GetType()
{
    return ::taihe::string(UtdUtils::GetUtdIdFromUtdEnum(this->value_->GetType()));
}

::taiheChannel::ValueType SystemDefinedRecordTaihe::GetValue()
{
    return ConvertValueType(this->value_->GetValue());
}

::taihe::optional<::taihe::map<::taihe::string, ::taiheChannel::DetailsValue>> SystemDefinedRecordTaihe::GetDetails()
{
    return ::taihe::optional<::taihe::map<::taihe::string, ::taiheChannel::DetailsValue>>::make(
        ConvertUDDetailsToUnion(this->value_->GetDetails()));
}

void SystemDefinedRecordTaihe::SetDetails(
    const::taihe::map_view<::taihe::string, ::taiheChannel::DetailsValue> &details)
{
    UDDetails udmfDetails = ConvertUDDetailsToUnion(details);
    this->value_->SetDetails(udmfDetails);
}

int64_t SystemDefinedRecordTaihe::GetInner()
{
    return reinterpret_cast<int64_t>(this);
}
} // namespace UDMF
} // namespace OHOS

::taiheChannel::SystemDefinedRecordInner CreateSystemDefinedRecord()
{
    return taihe::make_holder<OHOS::UDMF::SystemDefinedRecordTaihe,
        ::taiheChannel::SystemDefinedRecordInner>();
}

TH_EXPORT_CPP_API_CreateSystemDefinedRecord(CreateSystemDefinedRecord);