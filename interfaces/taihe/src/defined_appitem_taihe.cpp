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

SystemDefinedAppItemInnerImpl::SystemDefinedAppItemInnerImpl()
{
    this->value_ = std::make_shared<taiheUdmf::SystemDefinedAppItem>();
}

::taihe::string SystemDefinedAppItemInnerImpl::GetType()
{
    return ::taihe::string(taiheUdmf::UtdUtils::GetUtdIdFromUtdEnum(this->value_->GetType()));
}

::ohos::data::unifiedDataChannel::ValueType SystemDefinedAppItemInnerImpl::GetValue()
{
    return taiheUdmf::ConvertValueType(this->value_->GetValue());
}

::taihe::optional<::taihe::map<::taihe::string, ::ohos::data::unifiedDataChannel::DetailsValue>> SystemDefinedAppItemInnerImpl::GetDetails()
{
    return ::taihe::optional<::taihe::map<::taihe::string, ::ohos::data::unifiedDataChannel::DetailsValue>>::make(
        taiheUdmf::ConvertUDDetailsToUnion(this->value_->GetDetails()));
}

void SystemDefinedAppItemInnerImpl::SetDetails(::taihe::map_view<::taihe::string, ::ohos::data::unifiedDataChannel::DetailsValue> details)
{
    taiheUdmf::UDDetails udmfDetails = taiheUdmf::ConvertUDDetailsToUnion(details);
    this->value_->SetDetails(udmfDetails);
}

::taihe::string SystemDefinedAppItemInnerImpl::GetAppId()
{
    return ::taihe::string(this->value_->GetAppId());
}

void SystemDefinedAppItemInnerImpl::SetAppId(::taihe::string_view appId)
{
    std::string appIdStr(appId);
    this->value_->SetAppId(appIdStr);
}

::taihe::string SystemDefinedAppItemInnerImpl::GetAppName()
{
    return ::taihe::string(this->value_->GetAppName());
}

void SystemDefinedAppItemInnerImpl::SetAppName(::taihe::string_view appName)
{
    std::string appNameStr(appName);
    this->value_->SetAppName(appNameStr);
}

::taihe::string SystemDefinedAppItemInnerImpl::GetAppIconId()
{
    return ::taihe::string(this->value_->GetAppIconId());
}

void SystemDefinedAppItemInnerImpl::SetAppIconId(::taihe::string_view appIconId)
{
    std::string appIconIdStr(appIconId);
    this->value_->SetAppIconId(appIconIdStr);
}

::taihe::string SystemDefinedAppItemInnerImpl::GetAppLabelId()
{
    return ::taihe::string(this->value_->GetAppLabelId());
}

void SystemDefinedAppItemInnerImpl::SetAppLabelId(::taihe::string_view appLabelId)
{
    std::string appLabelIdStr(appLabelId);
    this->value_->SetAppLabelId(appLabelIdStr);
}

::taihe::string SystemDefinedAppItemInnerImpl::GetBundleName()
{
    return ::taihe::string(this->value_->GetBundleName());
}

void SystemDefinedAppItemInnerImpl::SetBundleName(::taihe::string_view bundleName)
{
    std::string bundleNameStr(bundleName);
    this->value_->SetBundleName(bundleNameStr);
}

::taihe::string SystemDefinedAppItemInnerImpl::GetAbilityName()
{
    return ::taihe::string(this->value_->GetAbilityName());
}

void SystemDefinedAppItemInnerImpl::SetAbilityName(::taihe::string_view abilityName)
{
    std::string abilityNameStr(abilityName);
    this->value_->SetAbilityName(abilityNameStr);
}

int64_t SystemDefinedAppItemInnerImpl::GetInner()
{
    return reinterpret_cast<int64_t>(this);
}

::ohos::data::unifiedDataChannel::SystemDefinedAppItemInner CreateSystemDefinedAppItem()
{
    return taihe::make_holder<SystemDefinedAppItemInnerImpl, ::ohos::data::unifiedDataChannel::SystemDefinedAppItemInner>();
}

TH_EXPORT_CPP_API_CreateSystemDefinedAppItem(CreateSystemDefinedAppItem);