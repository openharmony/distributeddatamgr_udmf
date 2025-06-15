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

SystemDefinedRecordInnerImpl::SystemDefinedRecordInnerImpl()
{
    this->value_ = std::make_shared<taiheUdmf::SystemDefinedRecord>();
}

::taihe::string SystemDefinedRecordInnerImpl::GetType()
{
    return ::taihe::string(taiheUdmf::UtdUtils::GetUtdIdFromUtdEnum(this->value_->GetType()));
}

::ohos::data::unifiedDataChannel::ValueType SystemDefinedRecordInnerImpl::GetValue()
{
    return taiheUdmf::ConvertValueType(this->value_->GetValue());
}

::taihe::optional<::taihe::map<::taihe::string, ::ohos::data::unifiedDataChannel::DetailsValue>>
    SystemDefinedRecordInnerImpl::GetDetails()
{
    return ::taihe::optional<::taihe::map<::taihe::string, ::ohos::data::unifiedDataChannel::DetailsValue>>::make(
        taiheUdmf::ConvertUDDetailsToUnion(this->value_->GetDetails()));
}

void SystemDefinedRecordInnerImpl::SetDetails(
    ::taihe::map_view<::taihe::string, ::ohos::data::unifiedDataChannel::DetailsValue> details)
{
    taiheUdmf::UDDetails udmfDetails = taiheUdmf::ConvertUDDetailsToUnion(details);
    this->value_->SetDetails(udmfDetails);
}

int64_t SystemDefinedRecordInnerImpl::GetInner()
{
    return reinterpret_cast<int64_t>(this);
}

::ohos::data::unifiedDataChannel::SystemDefinedRecordInner CreateSystemDefinedRecord()
{
    return taihe::make_holder<SystemDefinedRecordInnerImpl,
        ::ohos::data::unifiedDataChannel::SystemDefinedRecordInner>();
}

TH_EXPORT_CPP_API_CreateSystemDefinedRecord(CreateSystemDefinedRecord);