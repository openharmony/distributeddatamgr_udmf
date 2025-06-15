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

#include "defined_form_taihe.h"
#include "taihe_common_utils.h"


SystemDefinedFormInnerImpl::SystemDefinedFormInnerImpl()
{
    this->value_ = std::make_shared<taiheUdmf::SystemDefinedForm>();
}

::taihe::string SystemDefinedFormInnerImpl::GetType()
{
    return ::taihe::string(taiheUdmf::UtdUtils::GetUtdIdFromUtdEnum(this->value_->GetType()));
}

::ohos::data::unifiedDataChannel::ValueType SystemDefinedFormInnerImpl::GetValue()
{
    return taiheUdmf::ConvertValueType(this->value_->GetValue());
}

::taihe::optional<::taihe::map<::taihe::string, ::ohos::data::unifiedDataChannel::DetailsValue>>
    SystemDefinedFormInnerImpl::GetDetails()
{
    return ::taihe::optional<::taihe::map<::taihe::string, ::ohos::data::unifiedDataChannel::DetailsValue>>::make(
        taiheUdmf::ConvertUDDetailsToUnion(this->value_->GetDetails()));
}

void SystemDefinedFormInnerImpl::SetDetails(
    ::taihe::map_view<::taihe::string, ::ohos::data::unifiedDataChannel::DetailsValue> details)
{
    taiheUdmf::UDDetails udmfDetails = taiheUdmf::ConvertUDDetailsToUnion(details);
    this->value_->SetDetails(udmfDetails);
}

double SystemDefinedFormInnerImpl::GetFormId()
{
    return this->value_->GetFormId();
}

void SystemDefinedFormInnerImpl::SetFormId(double formId)
{
    this->value_->SetFormId(formId);
}

::taihe::string SystemDefinedFormInnerImpl::GetFormName()
{
    return ::taihe::string(this->value_->GetFormName());
}

void SystemDefinedFormInnerImpl::SetFormName(::taihe::string_view formName)
{
    std::string name(formName);
    this->value_->SetFormName(name);
}

::taihe::string SystemDefinedFormInnerImpl::GetBundleName()
{
    return ::taihe::string(this->value_->GetBundleName());
}

void SystemDefinedFormInnerImpl::SetBundleName(::taihe::string_view bundleName)
{
    std::string name(bundleName);
    this->value_->SetBundleName(name);
}

::taihe::string SystemDefinedFormInnerImpl::GetAbilityName()
{
    return ::taihe::string(this->value_->GetAbilityName());
}

void SystemDefinedFormInnerImpl::SetAbilityName(::taihe::string_view abilityName)
{
    std::string name(abilityName);
    this->value_->SetAbilityName(name);
}

::taihe::string SystemDefinedFormInnerImpl::GetModule()
{
    return ::taihe::string(this->value_->GetModule());
}

void SystemDefinedFormInnerImpl::SetModule(::taihe::string_view module)
{
    std::string mudule(module);
    this->value_->SetModule(mudule);
}

int64_t SystemDefinedFormInnerImpl::GetInner()
{
    return reinterpret_cast<int64_t>(this);
}

::ohos::data::unifiedDataChannel::SystemDefinedFormInner CreateSystemDefinedForm()
{
    return taihe::make_holder<SystemDefinedFormInnerImpl, ::ohos::data::unifiedDataChannel::SystemDefinedFormInner>();
}

TH_EXPORT_CPP_API_CreateSystemDefinedForm(CreateSystemDefinedForm);
