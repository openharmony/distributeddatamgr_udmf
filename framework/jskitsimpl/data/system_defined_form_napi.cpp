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
#define LOG_TAG "SystemDefinedFormNapi"
#include "system_defined_form_napi.h"

#include "napi_data_utils.h"
#include "napi_error_utils.h"
#include "napi_queue.h"
#include "system_defined_form.h"
#include "system_defined_record_napi.h"
#include "unified_record_napi.h"

namespace OHOS {
namespace UDMF {
napi_value SystemDefinedFormNapi::Constructor(napi_env env)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "SystemDefinedFormNapi");
    napi_property_descriptor properties[] = {
        /* SystemDefinedForm extends UnifiedRecord */
        DECLARE_NAPI_FUNCTION("getType", UnifiedRecordNapi::GetType),
        DECLARE_NAPI_FUNCTION("getValue", UnifiedRecordNapi::GetValue),
        /* SystemDefinedForm extends SystemDefinedRecord */
        DECLARE_NAPI_GETTER_SETTER("details", SystemDefinedRecordNapi::GetDetails, SystemDefinedRecordNapi::SetDetails),
        /* SystemDefinedForm properties */
        DECLARE_NAPI_GETTER_SETTER("formId", GetFormId, SetFormId),
        DECLARE_NAPI_GETTER_SETTER("formName", GetFormName, SetFormName),
        DECLARE_NAPI_GETTER_SETTER("bundleName", GetBundleName, SetBundleName),
        DECLARE_NAPI_GETTER_SETTER("abilityName", GetAbilityName, SetAbilityName),
        DECLARE_NAPI_GETTER_SETTER("module", GetModule, SetModule),
    };
    size_t count = sizeof(properties) / sizeof(properties[0]);
    return NapiDataUtils::DefineClass(env, "SDForm", properties, count, SystemDefinedFormNapi::New);
}

napi_value SystemDefinedFormNapi::New(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "SystemDefinedFormNapi");
    auto ctxt = std::make_shared<ContextBase>();
    ctxt->GetCbInfoSync(env, info);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_ERROR, ctxt->error);

    auto *sdForm = new (std::nothrow) SystemDefinedFormNapi();
    ASSERT_ERR(ctxt->env, sdForm != nullptr, Status::E_ERROR, "no memory for system defined form!");
    sdForm->value_ = std::make_shared<SystemDefinedForm>();
    ASSERT_CALL(env, napi_wrap(env, ctxt->self, sdForm, Destructor, nullptr, nullptr), sdForm);
    return ctxt->self;
}

void SystemDefinedFormNapi::NewInstance(napi_env env, std::shared_ptr<UnifiedRecord> in, napi_value &out)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "SystemDefinedFormNapi");
    ASSERT_CALL_VOID(env, napi_new_instance(env, Constructor(env), 0, nullptr, &out));
    auto *sdForm = new (std::nothrow) SystemDefinedFormNapi();
    ASSERT_ERR_VOID(env, sdForm != nullptr, Status::E_ERROR, "no memory for system defined form!");
    sdForm->value_ = std::static_pointer_cast<SystemDefinedForm>(in);
    ASSERT_CALL_DELETE(env, napi_wrap(env, out, sdForm, Destructor, nullptr, nullptr), sdForm);
}

void SystemDefinedFormNapi::Destructor(napi_env env, void *data, void *hint)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "SystemDefinedFormNapi finalize.");
    auto *sdForm = static_cast<SystemDefinedFormNapi *>(data);
    ASSERT_VOID(sdForm != nullptr, "finalize null!");
    delete sdForm;
}

SystemDefinedFormNapi *SystemDefinedFormNapi::GetSystemDefinedForm(
    napi_env env, napi_callback_info info, std::shared_ptr<ContextBase> ctxt)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "SystemDefinedFormNapi");
    ctxt->GetCbInfoSync(env, info);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_ERROR, ctxt->error);
    return static_cast<SystemDefinedFormNapi *>(ctxt->native);
}

napi_value SystemDefinedFormNapi::GetFormId(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "SystemDefinedFormNapi");
    auto ctxt = std::make_shared<ContextBase>();
    auto sdForm = GetSystemDefinedForm(env, info, ctxt);
    ASSERT_ERR(
        ctxt->env, (sdForm != nullptr && sdForm->value_ != nullptr), Status::E_ERROR, "invalid object!");
    ctxt->status = NapiDataUtils::SetValue(env, sdForm->value_->GetFormId(), ctxt->output);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_ERROR, "set form id failed!");
    return ctxt->output;
}

napi_value SystemDefinedFormNapi::SetFormId(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "SystemDefinedFormNapi");
    auto ctxt = std::make_shared<ContextBase>();
    int32_t formId = 0;
    auto input = [env, ctxt, &formId](size_t argc, napi_value *argv) {
        ASSERT_BUSINESS_ERR(ctxt, argc >= 1,
            Status::E_INVALID_PARAMETERS, "Parameter error: Mandatory parameters are left unspecified");
        ctxt->status = NapiDataUtils::GetValue(env, argv[0], formId);
        ASSERT_BUSINESS_ERR(ctxt, ctxt->status == napi_ok,
            Status::E_INVALID_PARAMETERS, "Parameter error: parameter formId type must be number");
    };
    ctxt->GetCbInfoSync(env, info, input);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_ERROR, ctxt->error);
    auto sdForm = static_cast<SystemDefinedFormNapi *>(ctxt->native);
    ASSERT_ERR(
        ctxt->env, (sdForm != nullptr && sdForm->value_ != nullptr), Status::E_ERROR, "invalid object!");
    sdForm->value_->SetFormId(formId);
    return nullptr;
}

napi_value SystemDefinedFormNapi::GetFormName(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "SystemDefinedFormNapi");
    auto ctxt = std::make_shared<ContextBase>();
    auto sdForm = GetSystemDefinedForm(env, info, ctxt);
    ASSERT_ERR(
        ctxt->env, (sdForm != nullptr && sdForm->value_ != nullptr), Status::E_ERROR, "invalid object!");
    ctxt->status = NapiDataUtils::SetValue(env, sdForm->value_->GetFormName(), ctxt->output);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_ERROR, "set form name failed!");
    return ctxt->output;
}

napi_value SystemDefinedFormNapi::SetFormName(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "SystemDefinedFormNapi");
    auto ctxt = std::make_shared<ContextBase>();
    std::string formName;
    auto input = [env, ctxt, &formName](size_t argc, napi_value *argv) {
        ASSERT_BUSINESS_ERR(ctxt, argc >= 1,
            Status::E_INVALID_PARAMETERS, "Parameter error: Mandatory parameters are left unspecified");
        ctxt->status = NapiDataUtils::GetValue(env, argv[0], formName);
        ASSERT_BUSINESS_ERR(ctxt, ctxt->status == napi_ok,
            Status::E_INVALID_PARAMETERS, "Parameter error: parameter formName type must be string");
    };
    ctxt->GetCbInfoSync(env, info, input);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_ERROR, ctxt->error);
    auto sdForm = static_cast<SystemDefinedFormNapi *>(ctxt->native);
    ASSERT_ERR(
        ctxt->env, (sdForm != nullptr && sdForm->value_ != nullptr), Status::E_ERROR, "invalid object!");
    sdForm->value_->SetFormName(formName);
    return nullptr;
}

napi_value SystemDefinedFormNapi::GetBundleName(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "SystemDefinedFormNapi");
    auto ctxt = std::make_shared<ContextBase>();
    auto sdForm = GetSystemDefinedForm(env, info, ctxt);
    ASSERT_ERR(
        ctxt->env, (sdForm != nullptr && sdForm->value_ != nullptr), Status::E_ERROR, "invalid object!");
    ctxt->status = NapiDataUtils::SetValue(env, sdForm->value_->GetBundleName(), ctxt->output);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_ERROR, "set bundle name failed!");
    return ctxt->output;
}

napi_value SystemDefinedFormNapi::SetBundleName(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "SystemDefinedFormNapi");
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
    auto sdForm = static_cast<SystemDefinedFormNapi *>(ctxt->native);
    ASSERT_ERR(
        ctxt->env, (sdForm != nullptr && sdForm->value_ != nullptr), Status::E_ERROR, "invalid object!");
    sdForm->value_->SetBundleName(bundleName);
    return nullptr;
}

napi_value SystemDefinedFormNapi::GetAbilityName(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "SystemDefinedFormNapi");
    auto ctxt = std::make_shared<ContextBase>();
    auto sdForm = GetSystemDefinedForm(env, info, ctxt);
    ASSERT_ERR(
        ctxt->env, (sdForm != nullptr && sdForm->value_ != nullptr), Status::E_ERROR, "invalid object!");
    ctxt->status = NapiDataUtils::SetValue(env, sdForm->value_->GetAbilityName(), ctxt->output);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_ERROR, "set ability name failed!");
    return ctxt->output;
}

napi_value SystemDefinedFormNapi::SetAbilityName(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "SystemDefinedFormNapi");
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
    auto sdForm = static_cast<SystemDefinedFormNapi *>(ctxt->native);
    ASSERT_ERR(
        ctxt->env, (sdForm != nullptr && sdForm->value_ != nullptr), Status::E_ERROR, "invalid object!");
    sdForm->value_->SetAbilityName(abilityName);
    return nullptr;
}

napi_value SystemDefinedFormNapi::GetModule(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "SystemDefinedFormNapi");
    auto ctxt = std::make_shared<ContextBase>();
    auto sdForm = GetSystemDefinedForm(env, info, ctxt);
    ASSERT_ERR(
        ctxt->env, (sdForm != nullptr && sdForm->value_ != nullptr), Status::E_ERROR, "invalid object!");
    ctxt->status = NapiDataUtils::SetValue(env, sdForm->value_->GetModule(), ctxt->output);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_ERROR, "set module failed!");
    return ctxt->output;
}

napi_value SystemDefinedFormNapi::SetModule(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "SystemDefinedFormNapi");
    auto ctxt = std::make_shared<ContextBase>();
    std::string module;
    auto input = [env, ctxt, &module](size_t argc, napi_value *argv) {
        ASSERT_BUSINESS_ERR(ctxt, argc >= 1,
            Status::E_INVALID_PARAMETERS, "Parameter error: Mandatory parameters are left unspecified");
        ctxt->status = NapiDataUtils::GetValue(env, argv[0], module);
        ASSERT_BUSINESS_ERR(ctxt, ctxt->status == napi_ok,
            Status::E_INVALID_PARAMETERS, "Parameter error: parameter module type must be string");
    };
    ctxt->GetCbInfoSync(env, info, input);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_ERROR, ctxt->error);
    auto sdForm = static_cast<SystemDefinedFormNapi *>(ctxt->native);
    ASSERT_ERR(
        ctxt->env, (sdForm != nullptr && sdForm->value_ != nullptr), Status::E_ERROR, "invalid object!");
    sdForm->value_->SetModule(module);
    return nullptr;
}
} // namespace UDMF
} // namespace OHOS