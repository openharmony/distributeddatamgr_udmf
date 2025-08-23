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

#define LOG_TAG "UDMF_DEFINED_APPITEM"

#include <dlfcn.h>

#include "defined_appitem_taihe.h"
#include "interop_js/arkts_esvalue.h"
#include "interop_js/arkts_interop_js_api.h"
#include "logger.h"
#include "system_defined_appitem_napi.h"
#include "taihe_common_utils.h"
#include "taihe/runtime.hpp"

namespace OHOS {
namespace UDMF {
using CreateInstance = napi_value (*)(napi_env, std::shared_ptr<SystemDefinedAppItem>);
SystemDefinedAppItemTaihe::SystemDefinedAppItemTaihe()
{
    this->value_ = std::make_shared<SystemDefinedAppItem>();
}

SystemDefinedAppItemTaihe::SystemDefinedAppItemTaihe(std::shared_ptr<SystemDefinedAppItem> value)
{
    this->value_ = value;
}

::taihe::string SystemDefinedAppItemTaihe::GetType()
{
    return ::taihe::string(UtdUtils::GetUtdIdFromUtdEnum(this->value_->GetType()));
}

::taiheChannel::ValueType SystemDefinedAppItemTaihe::GetValue()
{
    return ConvertValueType(this->value_->GetValue());
}

::taihe::optional<::taihe::map<::taihe::string, ::taiheChannel::DetailsValue>> SystemDefinedAppItemTaihe::GetDetails()
{
    return ::taihe::optional<::taihe::map<::taihe::string, ::taiheChannel::DetailsValue>>::make(
        ConvertUDDetailsToUnion(this->value_->GetDetails()));
}

void SystemDefinedAppItemTaihe::SetDetails(
    const ::taihe::map_view<::taihe::string, ::taiheChannel::DetailsValue> &details)
{
    UDDetails udmfDetails = ConvertUDDetailsToUnion(details);
    this->value_->SetDetails(udmfDetails);
}

::taihe::string SystemDefinedAppItemTaihe::GetAppId()
{
    return ::taihe::string(this->value_->GetAppId());
}

void SystemDefinedAppItemTaihe::SetAppId(const ::taihe::string_view &appId)
{
    std::string appIdStr(appId);
    this->value_->SetAppId(appIdStr);
}

::taihe::string SystemDefinedAppItemTaihe::GetAppName()
{
    return ::taihe::string(this->value_->GetAppName());
}

void SystemDefinedAppItemTaihe::SetAppName(const ::taihe::string_view &appName)
{
    std::string appNameStr(appName);
    this->value_->SetAppName(appNameStr);
}

::taihe::string SystemDefinedAppItemTaihe::GetAppIconId()
{
    return ::taihe::string(this->value_->GetAppIconId());
}

void SystemDefinedAppItemTaihe::SetAppIconId(const ::taihe::string_view &appIconId)
{
    std::string appIconIdStr(appIconId);
    this->value_->SetAppIconId(appIconIdStr);
}

::taihe::string SystemDefinedAppItemTaihe::GetAppLabelId()
{
    return ::taihe::string(this->value_->GetAppLabelId());
}

void SystemDefinedAppItemTaihe::SetAppLabelId(const ::taihe::string_view &appLabelId)
{
    std::string appLabelIdStr(appLabelId);
    this->value_->SetAppLabelId(appLabelIdStr);
}

::taihe::string SystemDefinedAppItemTaihe::GetBundleName()
{
    return ::taihe::string(this->value_->GetBundleName());
}

void SystemDefinedAppItemTaihe::SetBundleName(const ::taihe::string_view &bundleName)
{
    std::string bundleNameStr(bundleName);
    this->value_->SetBundleName(bundleNameStr);
}

::taihe::string SystemDefinedAppItemTaihe::GetAbilityName()
{
    return ::taihe::string(this->value_->GetAbilityName());
}

void SystemDefinedAppItemTaihe::SetAbilityName(const ::taihe::string_view &abilityName)
{
    std::string abilityNameStr(abilityName);
    this->value_->SetAbilityName(abilityNameStr);
}

int64_t SystemDefinedAppItemTaihe::GetInner()
{
    return reinterpret_cast<int64_t>(this);
}

::taiheChannel::SystemDefinedAppItemInner CreateSystemDefinedAppItem()
{
    return taihe::make_holder<SystemDefinedAppItemTaihe, ::taiheChannel::SystemDefinedAppItemInner>();
}

::taiheChannel::SystemDefinedAppItemInner SystemDefinedAppItemTransferStaticImpl(uintptr_t input)
{
    ani_object esValue = reinterpret_cast<ani_object>(input);
    void *nativePtr = nullptr;
    if (!arkts_esvalue_unwrap(taihe::get_env(), esValue, &nativePtr) || nativePtr == nullptr) {
        LOG_ERROR(UDMF_ANI, "unwrap esvalue failed");
        return taihe::make_holder<SystemDefinedAppItemTaihe, ::taiheChannel::SystemDefinedAppItemInner>();
    }
    auto appItemNapi = reinterpret_cast<SystemDefinedAppItemNapi *>(nativePtr);
    if (appItemNapi == nullptr || appItemNapi->value_ == nullptr) {
        LOG_ERROR(UDMF_ANI, "cast SystemDefinedAppItemNapi failed");
        return taihe::make_holder<SystemDefinedAppItemTaihe, ::taiheChannel::SystemDefinedAppItemInner>();
    }
    return taihe::make_holder<SystemDefinedAppItemTaihe,
        ::taiheChannel::SystemDefinedAppItemInner>(appItemNapi->value_);
}

uintptr_t SystemDefinedAppItemTransferDynamicImpl(::taiheChannel::weak::SystemDefinedAppItemInner input)
{
    auto applicationPtr = input->GetInner();
    auto applicationInnerPtr = reinterpret_cast<SystemDefinedAppItemTaihe *>(applicationPtr);
    if (applicationInnerPtr == nullptr) {
        LOG_ERROR(UDMF_ANI, "cast native pointer failed");
        return 0;
    }
    std::shared_ptr<SystemDefinedAppItem> systemDefinedAppItem = applicationInnerPtr->value_;
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
    CreateInstance newInstance = reinterpret_cast<CreateInstance>(dlsym(handle, "GetEtsSysAppItem"));
    if (newInstance == nullptr) {
        LOG_ERROR(UDMF_ANI, "dlsym get func failed, %{public}s", dlerror());
        arkts_napi_scope_close_n(jsenv, 0, nullptr, nullptr);
        dlclose(handle);
        return 0;
    }
    napi_value instance = newInstance(jsenv, systemDefinedAppItem);
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

TH_EXPORT_CPP_API_CreateSystemDefinedAppItem(OHOS::UDMF::CreateSystemDefinedAppItem);
TH_EXPORT_CPP_API_SystemDefinedAppItemTransferStaticImpl(OHOS::UDMF::SystemDefinedAppItemTransferStaticImpl);
TH_EXPORT_CPP_API_SystemDefinedAppItemTransferDynamicImpl(OHOS::UDMF::SystemDefinedAppItemTransferDynamicImpl);