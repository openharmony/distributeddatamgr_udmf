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

#include "defined_appitem_taihe.h"
#include "taihe_common_utils.h"

namespace OHOS {
namespace UDMF {
SystemDefinedAppItemTaihe::SystemDefinedAppItemTaihe()
{
    this->value_ = std::make_shared<SystemDefinedAppItem>();
}

::taihe::string SystemDefinedAppItemTaihe::GetType()
{
    return ::taihe::string(UtdUtils::GetUtdIdFromUtdEnum(this->value_->GetType()));
}

::taiheChannel::ValueType SystemDefinedAppItemTaihe::GetValue()
{
    return ConvertValueType(this->value_->GetValue());
}

::taihe::optional<::taihe::map<::taihe::string, ::taiheChannel::DetailsValue>>
    SystemDefinedAppItemTaihe::GetDetails()
{
    return ::taihe::optional<::taihe::map<::taihe::string, ::taiheChannel::DetailsValue>>::make(
        ConvertUDDetailsToUnion(this->value_->GetDetails()));
}

void SystemDefinedAppItemTaihe::SetDetails(
    ::taihe::map_view<::taihe::string, ::taiheChannel::DetailsValue> details)
{
    UDDetails udmfDetails = ConvertUDDetailsToUnion(details);
    this->value_->SetDetails(udmfDetails);
}

::taihe::string SystemDefinedAppItemTaihe::GetAppId()
{
    return ::taihe::string(this->value_->GetAppId());
}

void SystemDefinedAppItemTaihe::SetAppId(::taihe::string_view appId)
{
    std::string appIdStr(appId);
    this->value_->SetAppId(appIdStr);
}

::taihe::string SystemDefinedAppItemTaihe::GetAppName()
{
    return ::taihe::string(this->value_->GetAppName());
}

void SystemDefinedAppItemTaihe::SetAppName(::taihe::string_view appName)
{
    std::string appNameStr(appName);
    this->value_->SetAppName(appNameStr);
}

::taihe::string SystemDefinedAppItemTaihe::GetAppIconId()
{
    return ::taihe::string(this->value_->GetAppIconId());
}

void SystemDefinedAppItemTaihe::SetAppIconId(::taihe::string_view appIconId)
{
    std::string appIconIdStr(appIconId);
    this->value_->SetAppIconId(appIconIdStr);
}

::taihe::string SystemDefinedAppItemTaihe::GetAppLabelId()
{
    return ::taihe::string(this->value_->GetAppLabelId());
}

void SystemDefinedAppItemTaihe::SetAppLabelId(::taihe::string_view appLabelId)
{
    std::string appLabelIdStr(appLabelId);
    this->value_->SetAppLabelId(appLabelIdStr);
}

::taihe::string SystemDefinedAppItemTaihe::GetBundleName()
{
    return ::taihe::string(this->value_->GetBundleName());
}

void SystemDefinedAppItemTaihe::SetBundleName(::taihe::string_view bundleName)
{
    std::string bundleNameStr(bundleName);
    this->value_->SetBundleName(bundleNameStr);
}

::taihe::string SystemDefinedAppItemTaihe::GetAbilityName()
{
    return ::taihe::string(this->value_->GetAbilityName());
}

void SystemDefinedAppItemTaihe::SetAbilityName(::taihe::string_view abilityName)
{
    std::string abilityNameStr(abilityName);
    this->value_->SetAbilityName(abilityNameStr);
}

int64_t SystemDefinedAppItemTaihe::GetInner()
{
    return reinterpret_cast<int64_t>(this);
}
} // namespace UDMF
} // namespace OHOS

::taiheChannel::SystemDefinedAppItemInner CreateSystemDefinedAppItem()
{
    return taihe::make_holder<OHOS::UDMF::SystemDefinedAppItemTaihe,
        ::taiheChannel::SystemDefinedAppItemInner>();
}

TH_EXPORT_CPP_API_CreateSystemDefinedAppItem(CreateSystemDefinedAppItem);