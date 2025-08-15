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

#define LOG_TAG "UDMF_DEFINED_RECORD"

#include "defined_record_taihe.h"
#include "interop_js/arkts_esvalue.h"
#include "logger.h"
#include "system_defined_record_napi.h"
#include "taihe_common_utils.h"
#include "taihe/runtime.hpp"

namespace OHOS {
namespace UDMF {
SystemDefinedRecordTaihe::SystemDefinedRecordTaihe()
{
    this->value_ = std::make_shared<SystemDefinedRecord>();
}

SystemDefinedRecordTaihe::SystemDefinedRecordTaihe(std::shared_ptr<SystemDefinedRecord> value)
{
    this->value_ = value;
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

::taiheChannel::SystemDefinedRecordInner CreateSystemDefinedRecord()
{
    return taihe::make_holder<SystemDefinedRecordTaihe, ::taiheChannel::SystemDefinedRecordInner>();
}

::taiheChannel::SystemDefinedRecordInner SystemDefinedRecordTransferStaticImpl(uintptr_t input)
{
    ani_object esValue = reinterpret_cast<ani_object>(input);
    void *nativePtr = nullptr;
    if (!arkts_esvalue_unwrap(taihe::get_env(), esValue, &nativePtr) || nativePtr == nullptr) {
        LOG_ERROR(UDMF_ANI, "unwrap esvalue failed");
        return taihe::make_holder<SystemDefinedRecordTaihe, ::taiheChannel::SystemDefinedRecordInner>();
    }
    auto recordNapi = reinterpret_cast<SystemDefinedRecordNapi *>(nativePtr);
    if (recordNapi == nullptr || recordNapi->value_ == nullptr) {
        LOG_ERROR(UDMF_ANI, "cast SystemDefinedRecord failed");
        return taihe::make_holder<SystemDefinedRecordTaihe, ::taiheChannel::SystemDefinedRecordInner>();
    }
    return taihe::make_holder<SystemDefinedRecordTaihe, ::taiheChannel::SystemDefinedRecordInner>(recordNapi->value_);
}

uintptr_t SystemDefinedRecordTransferDynamicImpl(::taiheChannel::weak::SystemDefinedRecordInner input)
{
    return 0;
}
} // namespace UDMF
} // namespace OHOS

TH_EXPORT_CPP_API_CreateSystemDefinedRecord(OHOS::UDMF::CreateSystemDefinedRecord);
TH_EXPORT_CPP_API_SystemDefinedRecordTransferStaticImpl(OHOS::UDMF::SystemDefinedRecordTransferStaticImpl);
TH_EXPORT_CPP_API_SystemDefinedRecordTransferDynamicImpl(OHOS::UDMF::SystemDefinedRecordTransferDynamicImpl);