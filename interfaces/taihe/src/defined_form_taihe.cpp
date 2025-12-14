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

#define LOG_TAG "UDMF_DEFINED_FORM"

#include <dlfcn.h>

#include "defined_form_taihe.h"
#include "interop_js/arkts_esvalue.h"
#include "interop_js/arkts_interop_js_api.h"
#include "logger.h"
#include "system_defined_form_napi.h"
#include "taihe_common_utils.h"
#include "taihe/runtime.hpp"
#include "unified_record_taihe.h"

namespace OHOS {
namespace UDMF {
using CreateInstance = napi_value (*)(napi_env, std::shared_ptr<SystemDefinedForm>);
SystemDefinedFormTaihe::SystemDefinedFormTaihe()
{
    this->value_ = std::make_shared<SystemDefinedForm>();
}

SystemDefinedFormTaihe::SystemDefinedFormTaihe(std::shared_ptr<SystemDefinedForm> value)
{
    this->value_ = value;
}

::taihe::string SystemDefinedFormTaihe::GetType()
{
    return ::taihe::string(UtdUtils::GetUtdIdFromUtdEnum(this->value_->GetType()));
}

::taiheChannel::ValueType SystemDefinedFormTaihe::GetValue()
{
    return ConvertValueType(this->value_->GetValue());
}

::taihe::array<::taihe::string> SystemDefinedFormTaihe::GetTypes()
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

void SystemDefinedFormTaihe::AddEntry(::taihe::string_view type, ::taiheChannel::ValueType value)
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
        this->value_ = std::make_shared<SystemDefinedForm>(utdType, valueType);
        if (!this->value_) {
            taihe::set_business_error(PARAMETERSERROR, "Parameter error: unsupported type");
            return;
        }
    } else {
        this->value_->AddEntry(std::string(type), std::move(valueType));
    }
    return;
}

::taiheChannel::ValueType SystemDefinedFormTaihe::GetEntry(::taihe::string_view type)
{
    if (!this->value_) {
        LOG_ERROR(UDMF_ANI, "Inner value is null.");
        taihe::set_business_error(PARAMETERSERROR, "invalid object!");
        return ::taiheChannel::ValueType::make_nullType();
    }
    return ConvertValueType(this->value_->GetEntry(std::string(type)));
}

::taihe::map<::taihe::string, ::taiheChannel::ValueType> SystemDefinedFormTaihe::GetEntries()
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

::taihe::optional<::taihe::map<::taihe::string, ::taiheChannel::DetailsValue>> SystemDefinedFormTaihe::GetDetails()
{
    return ::taihe::optional<::taihe::map<::taihe::string, ::taiheChannel::DetailsValue>>::make(
        ConvertUDDetailsToUnion(this->value_->GetDetails()));
}

void SystemDefinedFormTaihe::SetDetails(
    const ::taihe::map_view<::taihe::string, ::taiheChannel::DetailsValue> &details)
{
    UDDetails udmfDetails = ConvertUDDetailsToUnion(details);
    this->value_->SetDetails(udmfDetails);
}

int32_t SystemDefinedFormTaihe::GetFormId()
{
    return this->value_->GetFormId();
}

void SystemDefinedFormTaihe::SetFormId(int32_t formId)
{
    this->value_->SetFormId(formId);
}

::taihe::string SystemDefinedFormTaihe::GetFormName()
{
    return ::taihe::string(this->value_->GetFormName());
}

void SystemDefinedFormTaihe::SetFormName(const::taihe::string_view &formName)
{
    std::string name(formName);
    this->value_->SetFormName(name);
}

::taihe::string SystemDefinedFormTaihe::GetBundleName()
{
    return ::taihe::string(this->value_->GetBundleName());
}

void SystemDefinedFormTaihe::SetBundleName(const::taihe::string_view &bundleName)
{
    std::string name(bundleName);
    this->value_->SetBundleName(name);
}

::taihe::string SystemDefinedFormTaihe::GetAbilityName()
{
    return ::taihe::string(this->value_->GetAbilityName());
}

void SystemDefinedFormTaihe::SetAbilityName(const::taihe::string_view &abilityName)
{
    std::string name(abilityName);
    this->value_->SetAbilityName(name);
}

::taihe::string SystemDefinedFormTaihe::GetModule()
{
    return ::taihe::string(this->value_->GetModule());
}

void SystemDefinedFormTaihe::SetModule(const::taihe::string_view &module)
{
    std::string mudule(module);
    this->value_->SetModule(mudule);
}

int64_t SystemDefinedFormTaihe::GetInner()
{
    return reinterpret_cast<int64_t>(this);
}

::taiheChannel::SystemDefinedFormInner CreateSystemDefinedForm()
{
    return taihe::make_holder<SystemDefinedFormTaihe, ::taiheChannel::SystemDefinedFormInner>();
}

::taiheChannel::SystemDefinedFormInner SystemDefinedFormTransferStaticImpl(uintptr_t input)
{
    ani_object esValue = reinterpret_cast<ani_object>(input);
    void *nativePtr = nullptr;
    if (!arkts_esvalue_unwrap(taihe::get_env(), esValue, &nativePtr) || nativePtr == nullptr) {
        LOG_ERROR(UDMF_ANI, "unwrap esvalue failed");
        return taihe::make_holder<SystemDefinedFormTaihe, ::taiheChannel::SystemDefinedFormInner>();
    }
    auto formNapi = reinterpret_cast<SystemDefinedFormNapi *>(nativePtr);
    if (formNapi == nullptr || formNapi->value_ == nullptr) {
        LOG_ERROR(UDMF_ANI, "cast SystemDefinedFormNapi failed");
        return taihe::make_holder<SystemDefinedFormTaihe, ::taiheChannel::SystemDefinedFormInner>();
    }
    return taihe::make_holder<SystemDefinedFormTaihe, ::taiheChannel::SystemDefinedFormInner>(formNapi->value_);
}

uintptr_t SystemDefinedFormTransferDynamicImpl(::taiheChannel::weak::SystemDefinedFormInner input)
{
    auto formPtr = input->GetInner();
    auto formInnerPtr = reinterpret_cast<SystemDefinedFormTaihe *>(formPtr);
    if (formInnerPtr == nullptr) {
        LOG_ERROR(UDMF_ANI, "cast native pointer failed");
        return 0;
    }
    std::shared_ptr<SystemDefinedForm> systemDefinedForm = formInnerPtr->value_;
    formInnerPtr = nullptr;
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
    CreateInstance newInstance = reinterpret_cast<CreateInstance>(dlsym(handle, "GetEtsSysForm"));
    if (newInstance == nullptr) {
        LOG_ERROR(UDMF_ANI, "dlsym get func failed, %{public}s", dlerror());
        arkts_napi_scope_close_n(jsenv, 0, nullptr, nullptr);
        dlclose(handle);
        return 0;
    }
    napi_value instance = newInstance(jsenv, systemDefinedForm);
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

TH_EXPORT_CPP_API_CreateSystemDefinedForm(OHOS::UDMF::CreateSystemDefinedForm);
TH_EXPORT_CPP_API_SystemDefinedFormTransferStaticImpl(OHOS::UDMF::SystemDefinedFormTransferStaticImpl);
TH_EXPORT_CPP_API_SystemDefinedFormTransferDynamicImpl(OHOS::UDMF::SystemDefinedFormTransferDynamicImpl);