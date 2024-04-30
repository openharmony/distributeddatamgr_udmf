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
#define LOG_TAG "ApplicationDefinedRecordNapi"
#include "application_defined_record_napi.h"

#include "application_defined_record.h"
#include "napi_data_utils.h"
#include "napi_error_utils.h"
#include "napi_queue.h"
#include "unified_record_napi.h"

namespace OHOS {
namespace UDMF {
napi_value ApplicationDefinedRecordNapi::Constructor(napi_env env)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "ApplicationDefinedRecordNapi");
    napi_property_descriptor properties[] = {
        /* ApplicationDefinedRecord extends UnifiedRecord */
        DECLARE_NAPI_FUNCTION("getType", UnifiedRecordNapi::GetType),
        DECLARE_NAPI_FUNCTION("getValue", UnifiedRecordNapi::GetValue),
        /* ApplicationDefinedRecord properties */
        DECLARE_NAPI_GETTER_SETTER("applicationDefinedType", GetApplicationDefinedType, SetApplicationDefinedType),
        DECLARE_NAPI_GETTER_SETTER("rawData", GetRawData, SetRawData),
    };
    size_t count = sizeof(properties) / sizeof(properties[0]);
    return NapiDataUtils::DefineClass(
        env, "ApplicationDefinedRecord", properties, count, ApplicationDefinedRecordNapi::New);
}

napi_value ApplicationDefinedRecordNapi::New(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "ApplicationDefinedRecordNapi");
    auto ctxt = std::make_shared<ContextBase>();
    ctxt->GetCbInfoSync(env, info);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_ERROR, ctxt->error);

    auto *record = new (std::nothrow) ApplicationDefinedRecordNapi();
    ASSERT_ERR(ctxt->env, record != nullptr, Status::E_ERROR, "no memory for application defined record!");
    record->value_ = std::make_shared<ApplicationDefinedRecord>();
    ASSERT_CALL(ctxt->env, napi_wrap(env, ctxt->self, record, Destructor, nullptr, nullptr), record);
    return ctxt->self;
}

void ApplicationDefinedRecordNapi::NewInstance(napi_env env, std::shared_ptr<UnifiedRecord> in, napi_value &out)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "ApplicationDefinedRecordNapi");
    ASSERT_CALL_VOID(env, napi_new_instance(env, Constructor(env), 0, nullptr, &out));
    auto *record = new (std::nothrow) ApplicationDefinedRecordNapi();
    ASSERT_ERR_VOID(env, record != nullptr, Status::E_ERROR, "no memory for application defined record!");
    record->value_ = std::static_pointer_cast<ApplicationDefinedRecord>(in);
    ASSERT_CALL_DELETE(env, napi_wrap(env, out, record, Destructor, nullptr, nullptr), record);
}

void ApplicationDefinedRecordNapi::Destructor(napi_env env, void *data, void *hint)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "ApplicationDefinedRecordNapi finalize.");
    auto *record = static_cast<ApplicationDefinedRecordNapi *>(data);
    ASSERT_VOID(record != nullptr, "finalize null!");
    delete record;
}

ApplicationDefinedRecordNapi *ApplicationDefinedRecordNapi::GetApplicationDefinedRecord(
    napi_env env, napi_callback_info info, std::shared_ptr<ContextBase> ctxt)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "ApplicationDefinedRecordNapi");
    ctxt->GetCbInfoSync(env, info);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_ERROR, ctxt->error);
    return static_cast<ApplicationDefinedRecordNapi *>(ctxt->native);
}

napi_value ApplicationDefinedRecordNapi::GetApplicationDefinedType(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "ApplicationDefinedRecordNapi");
    auto ctxt = std::make_shared<ContextBase>();
    auto record = GetApplicationDefinedRecord(env, info, ctxt);
    ASSERT_ERR(
        ctxt->env, (record != nullptr && record->value_ != nullptr), Status::E_ERROR, "invalid object!");
    ctxt->status = NapiDataUtils::SetValue(env, record->value_->GetApplicationDefinedType(), ctxt->output);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_ERROR, "set type failed!");
    return ctxt->output;
}

napi_value ApplicationDefinedRecordNapi::SetApplicationDefinedType(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "ApplicationDefinedRecordNapi");
    auto ctxt = std::make_shared<ContextBase>();
    std::string type;
    auto input = [env, ctxt, &type](size_t argc, napi_value *argv) {
        ASSERT_BUSINESS_ERR(ctxt, argc >= 1,
            Status::E_INVALID_PARAMETERS, "Parameter error: Mandatory parameters are left unspecified");
        ctxt->status = NapiDataUtils::GetValue(env, argv[0], type);
        ASSERT_BUSINESS_ERR(ctxt, ctxt->status == napi_ok,
            Status::E_INVALID_PARAMETERS, "Parameter error: parameter applicationDefinedType type must be string");
    };
    ctxt->GetCbInfoSync(env, info, input);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_ERROR, ctxt->error);
    auto record = static_cast<ApplicationDefinedRecordNapi *>(ctxt->native);
    ASSERT_ERR(
        ctxt->env, (record != nullptr && record->value_ != nullptr), Status::E_ERROR, "invalid object!");
    record->value_->SetApplicationDefinedType(type);
    return nullptr;
}

napi_value ApplicationDefinedRecordNapi::GetRawData(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "ApplicationDefinedRecordNapi");
    auto ctxt = std::make_shared<ContextBase>();
    auto record = GetApplicationDefinedRecord(env, info, ctxt);
    ASSERT_ERR(
        ctxt->env, (record != nullptr && record->value_ != nullptr), Status::E_ERROR, "invalid object!");
    ctxt->status = NapiDataUtils::SetValue(env, record->value_->GetRawData(), ctxt->output);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_ERROR, "set rawData failed!");
    return ctxt->output;
}

napi_value ApplicationDefinedRecordNapi::SetRawData(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "ApplicationDefinedRecordNapi");
    auto ctxt = std::make_shared<ContextBase>();
    std::vector<uint8_t> rawData;
    auto input = [env, ctxt, &rawData](size_t argc, napi_value *argv) {
        ASSERT_BUSINESS_ERR(ctxt, argc >= 1,
            Status::E_INVALID_PARAMETERS, "Parameter error: Mandatory parameters are left unspecified");
        ctxt->status = NapiDataUtils::GetValue(env, argv[0], rawData);
        ASSERT_BUSINESS_ERR(ctxt, ctxt->status == napi_ok,
            Status::E_INVALID_PARAMETERS, "Parameter error: parameter rawData type must be Uint8Array");
    };
    ctxt->GetCbInfoSync(env, info, input);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_ERROR, ctxt->error);
    auto record = static_cast<ApplicationDefinedRecordNapi *>(ctxt->native);
    ASSERT_ERR(
        ctxt->env, (record != nullptr && record->value_ != nullptr), Status::E_ERROR, "invalid object!");
    record->value_->SetRawData(rawData);
    return nullptr;
}
} // namespace UDMF
} // namespace OHOS
