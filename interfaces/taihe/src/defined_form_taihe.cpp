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

namespace OHOS {
namespace UDMF {
SystemDefinedFormTaihe::SystemDefinedFormTaihe()
{
    this->value_ = std::make_shared<SystemDefinedForm>();
}

::taihe::string SystemDefinedFormTaihe::GetType()
{
    return ::taihe::string(UtdUtils::GetUtdIdFromUtdEnum(this->value_->GetType()));
}

::taiheChannel::ValueType SystemDefinedFormTaihe::GetValue()
{
    return ConvertValueType(this->value_->GetValue());
}

::taihe::optional<::taihe::map<::taihe::string, ::taiheChannel::DetailsValue>> SystemDefinedFormTaihe::GetDetails()
{
    return ::taihe::optional<::taihe::map<::taihe::string, ::taiheChannel::DetailsValue>>::make(
        ConvertUDDetailsToUnion(this->value_->GetDetails()));
}

void SystemDefinedFormTaihe::SetDetails(
    ::taihe::map_view<::taihe::string, ::taiheChannel::DetailsValue> details)
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

void SystemDefinedFormTaihe::SetFormName(::taihe::string_view formName)
{
    std::string name(formName);
    this->value_->SetFormName(name);
}

::taihe::string SystemDefinedFormTaihe::GetBundleName()
{
    return ::taihe::string(this->value_->GetBundleName());
}

void SystemDefinedFormTaihe::SetBundleName(::taihe::string_view bundleName)
{
    std::string name(bundleName);
    this->value_->SetBundleName(name);
}

::taihe::string SystemDefinedFormTaihe::GetAbilityName()
{
    return ::taihe::string(this->value_->GetAbilityName());
}

void SystemDefinedFormTaihe::SetAbilityName(::taihe::string_view abilityName)
{
    std::string name(abilityName);
    this->value_->SetAbilityName(name);
}

::taihe::string SystemDefinedFormTaihe::GetModule()
{
    return ::taihe::string(this->value_->GetModule());
}

void SystemDefinedFormTaihe::SetModule(::taihe::string_view module)
{
    std::string mudule(module);
    this->value_->SetModule(mudule);
}

int64_t SystemDefinedFormTaihe::GetInner()
{
    return reinterpret_cast<int64_t>(this);
}
} // namespace UDMF
} // namespace OHOS

::taiheChannel::SystemDefinedFormInner CreateSystemDefinedForm()
{
    return taihe::make_holder<OHOS::UDMF::SystemDefinedFormTaihe, ::taiheChannel::SystemDefinedFormInner>();
}

TH_EXPORT_CPP_API_CreateSystemDefinedForm(CreateSystemDefinedForm);
