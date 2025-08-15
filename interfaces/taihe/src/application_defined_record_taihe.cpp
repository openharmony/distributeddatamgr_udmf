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

#define LOG_TAG "UDMF_DEFINED_APPLICATION"

#include "application_defined_record_napi.h"
#include "application_defined_record_taihe.h"
#include "interop_js/arkts_esvalue.h"
#include "logger.h"
#include "taihe_common_utils.h"
#include "taihe/runtime.hpp"

namespace OHOS {
namespace UDMF {
ApplicationDefinedRecordTaihe::ApplicationDefinedRecordTaihe()
{
    this->value_ = std::make_shared<ApplicationDefinedRecord>();
}

ApplicationDefinedRecordTaihe::ApplicationDefinedRecordTaihe(std::shared_ptr<ApplicationDefinedRecord> value)
{
    this->value_ = value;
}
::taihe::string ApplicationDefinedRecordTaihe::GetType()
{
    return ::taihe::string(UtdUtils::GetUtdIdFromUtdEnum(this->value_->GetType()));
}

::taiheChannel::ValueType ApplicationDefinedRecordTaihe::GetValue()
{
    return ConvertValueType(this->value_->GetValue());
}

::taihe::string ApplicationDefinedRecordTaihe::GetApplicationDefinedType()
{
    return ::taihe::string(this->value_->GetApplicationDefinedType());
}

void ApplicationDefinedRecordTaihe::SetApplicationDefinedType(const ::taihe::string_view &applicationDefinedType)
{
    std::string type(applicationDefinedType);
    this->value_->SetApplicationDefinedType(type);
}

::taihe::optional<::taihe::array<uint8_t>> ApplicationDefinedRecordTaihe::GetRawData()
{
    auto rawData = this->value_->GetRawData();
    return ::taihe::optional<::taihe::array<uint8_t>>::make(
        ::taihe::array<uint8_t>(rawData));
}

void ApplicationDefinedRecordTaihe::SetRawData(const ::taihe::array_view<uint8_t> &rawData)
{
    if (rawData.size() == 0) {
        return;
    }
    std::vector<uint8_t> rawDataVec(rawData.begin(), rawData.end());
    this->value_->SetRawData(rawDataVec);
}

int64_t ApplicationDefinedRecordTaihe::GetInner()
{
    return reinterpret_cast<int64_t>(this);
}

::taiheChannel::ApplicationDefinedRecordInner createApplicationDefinedRecord()
{
    return taihe::make_holder<ApplicationDefinedRecordTaihe, ::taiheChannel::ApplicationDefinedRecordInner>();
}

::taiheChannel::ApplicationDefinedRecordInner ApplicationDefinedRecordTransferStaticImpl(uintptr_t input)
{
    ani_object esValue = reinterpret_cast<ani_object>(input);
    void *nativePtr = nullptr;
    if (!arkts_esvalue_unwrap(taihe::get_env(), esValue, &nativePtr) || nativePtr == nullptr) {
        LOG_ERROR(UDMF_ANI, "unwrap esvalue failed");
        return taihe::make_holder<ApplicationDefinedRecordTaihe, ::taiheChannel::ApplicationDefinedRecordInner>();
    }
    auto appNapi = reinterpret_cast<OHOS::UDMF::ApplicationDefinedRecordNapi *>(nativePtr);
    if (appNapi == nullptr || appNapi->value_ == nullptr) {
        LOG_ERROR(UDMF_ANI, "cast ApplicationDefinedRecord failed");
        return taihe::make_holder<ApplicationDefinedRecordTaihe, ::taiheChannel::ApplicationDefinedRecordInner>();
    }
    return taihe::make_holder<ApplicationDefinedRecordTaihe,
        ::taiheChannel::ApplicationDefinedRecordInner>(appNapi->value_);
}

uintptr_t ApplicationDefinedRecordTransferDynamicImpl(::taiheChannel::weak::ApplicationDefinedRecordInner input)
{
    return 0;
}
} // namespace UDMF
} // namespace OHOS

TH_EXPORT_CPP_API_createApplicationDefinedRecord(OHOS::UDMF::createApplicationDefinedRecord);
TH_EXPORT_CPP_API_ApplicationDefinedRecordTransferStaticImpl(OHOS::UDMF::ApplicationDefinedRecordTransferStaticImpl);
TH_EXPORT_CPP_API_ApplicationDefinedRecordTransferDynamicImpl(OHOS::UDMF::ApplicationDefinedRecordTransferDynamicImpl);