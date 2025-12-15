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

#include <dlfcn.h>

#include "application_defined_record_napi.h"
#include "application_defined_record_taihe.h"
#include "interop_js/arkts_esvalue.h"
#include "interop_js/arkts_interop_js_api.h"
#include "logger.h"
#include "taihe_common_utils.h"
#include "taihe/runtime.hpp"
#include "unified_record_taihe.h"

namespace OHOS {
namespace UDMF {
using CreateInstance = napi_value (*)(napi_env, std::shared_ptr<ApplicationDefinedRecord>);
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

::taihe::array<::taihe::string> ApplicationDefinedRecordTaihe::GetTypes()
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

void ApplicationDefinedRecordTaihe::AddEntry(::taihe::string_view type, ::taiheChannel::ValueType value)
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
        UDType utdType = SYSTEM_DEFINED_RECORD;
        if (UtdUtils::IsValidUtdId(std::string(type))) {
            utdType = static_cast<UDType>(UtdUtils::GetUtdEnumFromUtdId(std::string(type)));
        }
        this->value_ = std::make_shared<ApplicationDefinedRecord>(utdType, valueType);
        if (!this->value_) {
            taihe::set_business_error(PARAMETERSERROR, "Parameter error: unsupported type");
            return;
        }
    } else {
        this->value_->AddEntry(std::string(type), std::move(valueType));
    }
    return;
}

::taiheChannel::ValueType ApplicationDefinedRecordTaihe::GetEntry(::taihe::string_view type)
{
    if (!this->value_) {
        LOG_ERROR(UDMF_ANI, "Inner value is null.");
        taihe::set_business_error(PARAMETERSERROR, "invalid object!");
        return ::taiheChannel::ValueType::make_nullType();
    }
    return ConvertValueType(this->value_->GetEntry(std::string(type)));
}

::taihe::map<::taihe::string, ::taiheChannel::ValueType> ApplicationDefinedRecordTaihe::GetEntries()
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
    auto appNapi = reinterpret_cast<ApplicationDefinedRecordNapi *>(nativePtr);
    if (appNapi == nullptr || appNapi->value_ == nullptr) {
        LOG_ERROR(UDMF_ANI, "cast ApplicationDefinedRecordNapi failed");
        return taihe::make_holder<ApplicationDefinedRecordTaihe, ::taiheChannel::ApplicationDefinedRecordInner>();
    }
    return taihe::make_holder<ApplicationDefinedRecordTaihe,
        ::taiheChannel::ApplicationDefinedRecordInner>(appNapi->value_);
}

uintptr_t ApplicationDefinedRecordTransferDynamicImpl(::taiheChannel::weak::ApplicationDefinedRecordInner input)
{
    auto applicationPtr = input->GetInner();
    auto applicationInnerPtr = reinterpret_cast<ApplicationDefinedRecordTaihe *>(applicationPtr);
    if (applicationInnerPtr == nullptr) {
        LOG_ERROR(UDMF_ANI, "cast native pointer failed");
        return 0;
    }
    std::shared_ptr<ApplicationDefinedRecord> applicationDefinedRecord = applicationInnerPtr->value_;
    applicationInnerPtr = nullptr;
    napi_env jsenv;
    if (!arkts_napi_scope_open(taihe::get_env(), &jsenv)) {
        LOG_ERROR(UDMF_ANI, "arkts_napi_scope_open failed");
        return 0;
    }
    auto handle = dlopen(NEW_INSTANCE_LIB.c_str(), RTLD_NOW);
    if (handle == nullptr) {
        LOG_ERROR(UDMF_ANI, "dlopen failed");
        arkts_napi_scope_close_n(jsenv, 0, nullptr, nullptr);
        return 0;
    }
    CreateInstance newInstance = reinterpret_cast<CreateInstance>(dlsym(handle, "GetEtsAppRecord"));
    if (newInstance == nullptr) {
        LOG_ERROR(UDMF_ANI, "dlsym get func failed, %{public}s", dlerror());
        arkts_napi_scope_close_n(jsenv, 0, nullptr, nullptr);
        dlclose(handle);
        return 0;
    }
    napi_value instance = newInstance(jsenv, applicationDefinedRecord);
    dlclose(handle);
    if (instance == nullptr) {
        LOG_ERROR(UDMF_ANI, "instance is nullptr");
        arkts_napi_scope_close_n(jsenv, 0, nullptr, nullptr);
        return 0;
    }
    uintptr_t result = 0;
    arkts_napi_scope_close_n(jsenv, 1, &instance, reinterpret_cast<ani_ref*>(&result));
    return result;
}
} // namespace UDMF
} // namespace OHOS

TH_EXPORT_CPP_API_createApplicationDefinedRecord(OHOS::UDMF::createApplicationDefinedRecord);
TH_EXPORT_CPP_API_ApplicationDefinedRecordTransferStaticImpl(OHOS::UDMF::ApplicationDefinedRecordTransferStaticImpl);
TH_EXPORT_CPP_API_ApplicationDefinedRecordTransferDynamicImpl(OHOS::UDMF::ApplicationDefinedRecordTransferDynamicImpl);