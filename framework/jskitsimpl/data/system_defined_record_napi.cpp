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
#define LOG_TAG "SystemDefinedRecordNapi"
#include "system_defined_record_napi.h"

#include "system_defined_record.h"
#include "napi_data_utils.h"
#include "napi_error_utils.h"
#include "napi_queue.h"
#include "unified_record_napi.h"

namespace OHOS {
namespace UDMF {
napi_value SystemDefinedRecordNapi::Constructor(napi_env env)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "SystemDefinedRecordNapi");
    napi_property_descriptor properties[] = {
        /* SystemDefinedRecord extends UnifiedRecord */
        DECLARE_NAPI_FUNCTION("getType", UnifiedRecordNapi::GetType),
        DECLARE_NAPI_FUNCTION("getValue", UnifiedRecordNapi::GetValue),
        /* SystemDefinedRecord properties */
        DECLARE_NAPI_GETTER_SETTER("details", GetDetails, SetDetails),
    };
    size_t count = sizeof(properties) / sizeof(properties[0]);
    return NapiDataUtils::DefineClass(env, "SystemDefinedRecord", properties, count, SystemDefinedRecordNapi::New);
}

napi_value SystemDefinedRecordNapi::New(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "SystemDefinedRecordNapi");
    auto ctxt = std::make_shared<ContextBase>();
    ctxt->GetCbInfoSync(env, info);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_ERROR, ctxt->error);

    auto *sdRecord = new (std::nothrow) SystemDefinedRecordNapi();
    ASSERT_ERR(ctxt->env, sdRecord != nullptr, Status::E_ERROR, "no memory for system defined record!");
    sdRecord->value_ = std::make_shared<SystemDefinedRecord>();
    ASSERT_CALL(env, napi_wrap(env, ctxt->self, sdRecord, Destructor, nullptr, nullptr), sdRecord);
    return ctxt->self;
}

void SystemDefinedRecordNapi::NewInstance(napi_env env, std::shared_ptr<UnifiedRecord> in, napi_value &out)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "SystemDefinedRecordNapi");
    ASSERT_CALL_VOID(env, napi_new_instance(env, Constructor(env), 0, nullptr, &out));
    auto *sdRecord = new (std::nothrow) SystemDefinedRecordNapi();
    ASSERT_ERR_VOID(env, sdRecord != nullptr, Status::E_ERROR, "no memory for system defined record!");
    sdRecord->value_ = std::static_pointer_cast<SystemDefinedRecord>(in);
    ASSERT_CALL_DELETE(env, napi_wrap(env, out, sdRecord, Destructor, nullptr, nullptr), sdRecord);
}

void SystemDefinedRecordNapi::Destructor(napi_env env, void *data, void *hint)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "SystemDefinedRecordNapi finalize.");
    auto *sdRecord = static_cast<SystemDefinedRecordNapi *>(data);
    ASSERT_VOID(sdRecord != nullptr, "finalize null!");
    delete sdRecord;
}

SystemDefinedRecordNapi *SystemDefinedRecordNapi::GetSystemDefinedRecord(
    napi_env env, napi_callback_info info, std::shared_ptr<ContextBase> ctxt)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "SystemDefinedRecordNapi");
    ctxt->GetCbInfoSync(env, info);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_ERROR, ctxt->error);
    return static_cast<SystemDefinedRecordNapi *>(ctxt->native);
}

napi_value SystemDefinedRecordNapi::GetDetails(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "SystemDefinedRecordNapi");
    auto ctxt = std::make_shared<ContextBase>();
    auto sdRecord = GetSystemDefinedRecord(env, info, ctxt);
    ASSERT_ERR(ctxt->env, (sdRecord != nullptr && sdRecord->value_ != nullptr), Status::E_ERROR,
        "invalid object!");
    ctxt->status = NapiDataUtils::SetValue(env, sdRecord->value_->GetDetails(), ctxt->output);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_ERROR, "set details failed!");
    return ctxt->output;
}

napi_value SystemDefinedRecordNapi::SetDetails(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "SystemDefinedRecordNapi");
    auto ctxt = std::make_shared<ContextBase>();

    UDDetails details;
    auto input = [env, ctxt, &details](size_t argc, napi_value *argv) {
        ASSERT_BUSINESS_ERR(ctxt, argc >= 1,
            Status::E_INVALID_PARAMETERS, "Parameter error: Mandatory parameters are left unspecified");
        ctxt->status = NapiDataUtils::GetValue(env, argv[0], details);
        ASSERT_BUSINESS_ERR(ctxt, ctxt->status == napi_ok, Status::E_INVALID_PARAMETERS,
            "Parameter error: parameter details type must be Record<string, number | string | Uint8Array>");
    };
    ctxt->GetCbInfoSync(env, info, input);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_ERROR, ctxt->error);
    auto sdRecord = static_cast<SystemDefinedRecordNapi *>(ctxt->native);
    ASSERT_ERR(
        ctxt->env, (sdRecord != nullptr && sdRecord->value_ != nullptr), Status::E_ERROR,
        "invalid object!");
    sdRecord->value_->SetDetails(details);
    return nullptr;
}
} // namespace UDMF
} // namespace OHOS