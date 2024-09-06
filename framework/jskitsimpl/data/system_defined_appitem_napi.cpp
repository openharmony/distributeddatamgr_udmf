/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
#define LOG_TAG "SystemDefinedAppItemNapi"
#include "system_defined_appitem_napi.h"

#include "napi_data_utils.h"
#include "napi_error_utils.h"
#include "napi_queue.h"
#include "system_defined_appitem.h"
#include "system_defined_record_napi.h"
#include "unified_record_napi.h"

namespace OHOS {
namespace UDMF {
napi_value SystemDefinedAppItemNapi::Constructor(napi_env env)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "SystemDefinedAppItemNapi");
    napi_property_descriptor properties[] = {
        /* SystemDefinedAppItem extends UnifiedRecord */
        DECLARE_NAPI_FUNCTION("getType", UnifiedRecordNapi::GetType),
        DECLARE_NAPI_FUNCTION("getValue", UnifiedRecordNapi::GetValue),
        /* SystemDefinedAppItem extends SystemDefinedRecord */
        DECLARE_NAPI_GETTER_SETTER("details", SystemDefinedRecordNapi::GetDetails, SystemDefinedRecordNapi::SetDetails),
        /* SystemDefinedAppItem properties */
        DECLARE_NAPI_GETTER_SETTER("appId", GetAppId, SetAppId),
        DECLARE_NAPI_GETTER_SETTER("appName", GetAppName, SetAppName),
        DECLARE_NAPI_GETTER_SETTER("appIconId", GetAppIconId, SetAppIconId),
        DECLARE_NAPI_GETTER_SETTER("appLabelId", GetAppLabelId, SetAppLabelId),
        DECLARE_NAPI_GETTER_SETTER("bundleName", GetBundleName, SetBundleName),
        DECLARE_NAPI_GETTER_SETTER("abilityName", GetAbilityName, SetAbilityName),
    };
    size_t count = sizeof(properties) / sizeof(properties[0]);
    return NapiDataUtils::DefineClass(env, "SDAppItem", properties, count, SystemDefinedAppItemNapi::New);
}

napi_value SystemDefinedAppItemNapi::New(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "SystemDefinedAppItemNapi");
    auto ctxt = std::make_shared<ContextBase>();
    ctxt->GetCbInfoSync(env, info);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_ERROR, ctxt->error);

    auto *sdAppItem = new (std::nothrow) SystemDefinedAppItemNapi();
    ASSERT_ERR(ctxt->env, sdAppItem != nullptr, Status::E_ERROR, "no memory for system defined appitem!");
    sdAppItem->value_ = std::make_shared<SystemDefinedAppItem>();
    ASSERT_CALL(env, napi_wrap(env, ctxt->self, sdAppItem, Destructor, nullptr, nullptr), sdAppItem);
    return ctxt->self;
}

void SystemDefinedAppItemNapi::NewInstance(napi_env env, std::shared_ptr<UnifiedRecord> in, napi_value &out)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "SystemDefinedAppItemNapi");
    ASSERT_CALL_VOID(env, napi_new_instance(env, Constructor(env), 0, nullptr, &out));
    auto *sdAppItem = new (std::nothrow) SystemDefinedAppItemNapi();
    ASSERT_ERR_VOID(env, sdAppItem != nullptr, Status::E_ERROR, "no memory for system defined appitem!");
    sdAppItem->value_ = std::static_pointer_cast<SystemDefinedAppItem>(in);
    ASSERT_CALL_DELETE(env, napi_wrap(env, out, sdAppItem, Destructor, nullptr, nullptr), sdAppItem);
}

void SystemDefinedAppItemNapi::Destructor(napi_env env, void *data, void *hint)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "SystemDefinedAppItemNapi finalize.");
    auto *sdAppItem = static_cast<SystemDefinedAppItemNapi *>(data);
    ASSERT_VOID(sdAppItem != nullptr, "finalize null!");
    delete sdAppItem;
}

SystemDefinedAppItemNapi *SystemDefinedAppItemNapi::GetSystemDefinedAppItem(
    napi_env env, napi_callback_info info, std::shared_ptr<ContextBase> ctxt)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "SystemDefinedAppItemNapi");
    ctxt->GetCbInfoSync(env, info);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_ERROR, ctxt->error);
    return static_cast<SystemDefinedAppItemNapi *>(ctxt->native);
}

napi_value SystemDefinedAppItemNapi::GetAppId(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "SystemDefinedAppItemNapi");
    auto ctxt = std::make_shared<ContextBase>();
    auto sdAppItem = GetSystemDefinedAppItem(env, info, ctxt);
    ASSERT_ERR(ctxt->env, (sdAppItem != nullptr && sdAppItem->value_ != nullptr), Status::E_ERROR,
        "invalid object!");
    ctxt->status = NapiDataUtils::SetValue(env, sdAppItem->value_->GetAppId(), ctxt->output);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_ERROR, "set app id failed!");
    return ctxt->output;
}

napi_value SystemDefinedAppItemNapi::SetAppId(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "SystemDefinedAppItemNapi");
    auto ctxt = std::make_shared<ContextBase>();
    std::string appId;
    auto input = [env, ctxt, &appId](size_t argc, napi_value *argv) {
        ASSERT_BUSINESS_ERR(ctxt, argc >= 1,
            Status::E_INVALID_PARAMETERS, "Parameter error: Mandatory parameters are left unspecified");
        ctxt->status = NapiDataUtils::GetValue(env, argv[0], appId);
        ASSERT_BUSINESS_ERR(ctxt, ctxt->status == napi_ok,
            Status::E_INVALID_PARAMETERS, "Parameter error: parameter appId type must be string");
    };
    ctxt->GetCbInfoSync(env, info, input);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_ERROR, ctxt->error);
    auto sdAppItem = static_cast<SystemDefinedAppItemNapi *>(ctxt->native);
    ASSERT_ERR(ctxt->env, (sdAppItem != nullptr && sdAppItem->value_ != nullptr), Status::E_ERROR,
        "invalid object!");
    sdAppItem->value_->SetAppId(appId);
    return nullptr;
}

napi_value SystemDefinedAppItemNapi::GetAppName(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "SystemDefinedAppItemNapi");
    auto ctxt = std::make_shared<ContextBase>();
    auto sdAppItem = GetSystemDefinedAppItem(env, info, ctxt);
    ASSERT_ERR(ctxt->env, (sdAppItem != nullptr && sdAppItem->value_ != nullptr), Status::E_ERROR,
        "invalid object!");
    ctxt->status = NapiDataUtils::SetValue(env, sdAppItem->value_->GetAppName(), ctxt->output);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_ERROR, "set app name failed!");
    return ctxt->output;
}

napi_value SystemDefinedAppItemNapi::SetAppName(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "SystemDefinedAppItemNapi");
    auto ctxt = std::make_shared<ContextBase>();
    std::string appName;
    auto input = [env, ctxt, &appName](size_t argc, napi_value *argv) {
        ASSERT_BUSINESS_ERR(ctxt, argc >= 1,
            Status::E_INVALID_PARAMETERS, "Parameter error: Mandatory parameters are left unspecified");
        ctxt->status = NapiDataUtils::GetValue(env, argv[0], appName);
        ASSERT_BUSINESS_ERR(ctxt, ctxt->status == napi_ok,
            Status::E_INVALID_PARAMETERS, "Parameter error: parameter appName type must be string");
    };
    ctxt->GetCbInfoSync(env, info, input);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_ERROR, ctxt->error);
    auto sdAppItem = static_cast<SystemDefinedAppItemNapi *>(ctxt->native);
    ASSERT_ERR(ctxt->env, (sdAppItem != nullptr && sdAppItem->value_ != nullptr), Status::E_ERROR,
        "invalid object!");
    sdAppItem->value_->SetAppName(appName);
    return nullptr;
}

napi_value SystemDefinedAppItemNapi::GetAppIconId(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "SystemDefinedAppItemNapi");
    auto ctxt = std::make_shared<ContextBase>();
    auto sdAppItem = GetSystemDefinedAppItem(env, info, ctxt);
    ASSERT_ERR(ctxt->env, (sdAppItem != nullptr && sdAppItem->value_ != nullptr), Status::E_ERROR,
        "invalid object!");
    ctxt->status = NapiDataUtils::SetValue(env, sdAppItem->value_->GetAppIconId(), ctxt->output);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_ERROR, "set app icon id failed!");
    return ctxt->output;
}

napi_value SystemDefinedAppItemNapi::SetAppIconId(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "SystemDefinedAppItemNapi");
    auto ctxt = std::make_shared<ContextBase>();
    std::string appIconId;
    auto input = [env, ctxt, &appIconId](size_t argc, napi_value *argv) {
        ASSERT_BUSINESS_ERR(ctxt, argc >= 1,
            Status::E_INVALID_PARAMETERS, "Parameter error: Mandatory parameters are left unspecified");
        ctxt->status = NapiDataUtils::GetValue(env, argv[0], appIconId);
        ASSERT_BUSINESS_ERR(ctxt, ctxt->status == napi_ok,
            Status::E_INVALID_PARAMETERS, "Parameter error: parameter appIconId type must be string");
    };
    ctxt->GetCbInfoSync(env, info, input);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_ERROR, ctxt->error);
    auto sdAppItem = static_cast<SystemDefinedAppItemNapi *>(ctxt->native);
    ASSERT_ERR(ctxt->env, (sdAppItem != nullptr && sdAppItem->value_ != nullptr), Status::E_ERROR,
        "invalid object!");
    sdAppItem->value_->SetAppIconId(appIconId);
    return nullptr;
}

napi_value SystemDefinedAppItemNapi::GetAppLabelId(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "SystemDefinedAppItemNapi");
    auto ctxt = std::make_shared<ContextBase>();
    auto sdAppItem = GetSystemDefinedAppItem(env, info, ctxt);
    ASSERT_ERR(ctxt->env, (sdAppItem != nullptr && sdAppItem->value_ != nullptr), Status::E_ERROR,
        "invalid object!");
    ctxt->status = NapiDataUtils::SetValue(env, sdAppItem->value_->GetAppLabelId(), ctxt->output);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_ERROR, "set app label id failed!");
    return ctxt->output;
}

napi_value SystemDefinedAppItemNapi::SetAppLabelId(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "SystemDefinedAppItemNapi");
    auto ctxt = std::make_shared<ContextBase>();
    std::string appLabelId;
    auto input = [env, ctxt, &appLabelId](size_t argc, napi_value *argv) {
        ASSERT_BUSINESS_ERR(ctxt, argc >= 1,
            Status::E_INVALID_PARAMETERS, "Parameter error: Mandatory parameters are left unspecified");
        ctxt->status = NapiDataUtils::GetValue(env, argv[0], appLabelId);
        ASSERT_BUSINESS_ERR(ctxt, ctxt->status == napi_ok,
            Status::E_INVALID_PARAMETERS, "Parameter error: parameter appLabelId type must be string");
    };
    ctxt->GetCbInfoSync(env, info, input);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_ERROR, ctxt->error);
    auto sdAppItem = static_cast<SystemDefinedAppItemNapi *>(ctxt->native);
    ASSERT_ERR(ctxt->env, (sdAppItem != nullptr && sdAppItem->value_ != nullptr), Status::E_ERROR,
        "invalid object!");
    sdAppItem->value_->SetAppLabelId(appLabelId);
    return nullptr;
}

napi_value SystemDefinedAppItemNapi::GetBundleName(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "SystemDefinedAppItemNapi");
    auto ctxt = std::make_shared<ContextBase>();
    auto sdAppItem = GetSystemDefinedAppItem(env, info, ctxt);
    ASSERT_ERR(ctxt->env, (sdAppItem != nullptr && sdAppItem->value_ != nullptr), Status::E_ERROR,
        "invalid object!");
    ctxt->status = NapiDataUtils::SetValue(env, sdAppItem->value_->GetBundleName(), ctxt->output);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_ERROR, "set bundle name failed!");
    return ctxt->output;
}

napi_value SystemDefinedAppItemNapi::SetBundleName(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "SystemDefinedAppItemNapi");
    auto ctxt = std::make_shared<ContextBase>();
    std::string bundleName;
    auto input = [env, ctxt, &bundleName](size_t argc, napi_value *argv) {
        ASSERT_BUSINESS_ERR(ctxt, argc >= 1,
            Status::E_INVALID_PARAMETERS, "Parameter error: Mandatory parameters are left unspecified");
        ctxt->status = NapiDataUtils::GetValue(env, argv[0], bundleName);
        ASSERT_BUSINESS_ERR(ctxt, ctxt->status == napi_ok,
            Status::E_INVALID_PARAMETERS, "Parameter error: parameter bundleName type must be string");
    };
    ctxt->GetCbInfoSync(env, info, input);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_ERROR, ctxt->error);
    auto sdAppItem = static_cast<SystemDefinedAppItemNapi *>(ctxt->native);
    ASSERT_ERR(ctxt->env, (sdAppItem != nullptr && sdAppItem->value_ != nullptr), Status::E_ERROR,
        "invalid object!");
    sdAppItem->value_->SetBundleName(bundleName);
    return nullptr;
}

napi_value SystemDefinedAppItemNapi::GetAbilityName(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "SystemDefinedAppItemNapi");
    auto ctxt = std::make_shared<ContextBase>();
    auto sdAppItem = GetSystemDefinedAppItem(env, info, ctxt);
    ASSERT_ERR(ctxt->env, (sdAppItem != nullptr && sdAppItem->value_ != nullptr), Status::E_ERROR,
        "invalid object!");
    ctxt->status = NapiDataUtils::SetValue(env, sdAppItem->value_->GetAbilityName(), ctxt->output);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_ERROR, "set ability name failed!");
    return ctxt->output;
}

napi_value SystemDefinedAppItemNapi::SetAbilityName(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "SystemDefinedAppItemNapi");
    auto ctxt = std::make_shared<ContextBase>();
    std::string abilityName;
    auto input = [env, ctxt, &abilityName](size_t argc, napi_value *argv) {
        ASSERT_BUSINESS_ERR(ctxt, argc >= 1,
            Status::E_INVALID_PARAMETERS, "Parameter error: Mandatory parameters are left unspecified");
        ctxt->status = NapiDataUtils::GetValue(env, argv[0], abilityName);
        ASSERT_BUSINESS_ERR(ctxt, ctxt->status == napi_ok,
            Status::E_INVALID_PARAMETERS, "Parameter error: parameter abilityName type must be string");
    };
    ctxt->GetCbInfoSync(env, info, input);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_ERROR, ctxt->error);
    auto sdAppItem = static_cast<SystemDefinedAppItemNapi *>(ctxt->native);
    ASSERT_ERR(ctxt->env, (sdAppItem != nullptr && sdAppItem->value_ != nullptr), Status::E_ERROR,
        "invalid object!");
    sdAppItem->value_->SetAbilityName(abilityName);
    return nullptr;
}
} // namespace UDMF
} // namespace OHOS