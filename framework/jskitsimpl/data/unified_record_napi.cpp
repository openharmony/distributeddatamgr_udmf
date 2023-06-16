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

#include "unified_record_napi.h"

#include "napi_data_utils.h"
#include "napi_error_utils.h"
#include "napi_queue.h"
#include "unified_record.h"

namespace OHOS {
namespace UDMF {
napi_value UnifiedRecordNapi::Constructor(napi_env env)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "UnifiedRecordNapi");
    napi_property_descriptor properties[] = {
        /* UnifiedRecord properties */
        DECLARE_NAPI_FUNCTION("getType", GetType),
    };
    size_t count = sizeof(properties) / sizeof(properties[0]);
    return NapiDataUtils::DefineClass(env, "UnifiedRecord", properties, count, UnifiedRecordNapi::New);
}

napi_value UnifiedRecordNapi::New(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "UnifiedRecordNapi");
    auto ctxt = std::make_shared<ContextBase>();
    ctxt->GetCbInfoSync(env, info);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_INVALID_PARAMETERS, "invalid arguments!");

    auto *udRecord = new (std::nothrow) UnifiedRecordNapi();
    ASSERT_ERR(ctxt->env, udRecord != nullptr, Status::E_FORBIDDEN, "no memory for unified record!");
    udRecord->value_ = std::make_shared<UnifiedRecord>();
    ASSERT_CALL(env, napi_wrap(env, ctxt->self, udRecord, Destructor, nullptr, nullptr), udRecord);
    return ctxt->self;
}

void UnifiedRecordNapi::Destructor(napi_env env, void *data, void *hint)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "UnifiedRecordNapi finalize.");
    auto *uRecord = static_cast<UnifiedRecordNapi *>(data);
    ASSERT_VOID(uRecord != nullptr, "finalize null!");
    delete uRecord;
}

UnifiedRecordNapi *UnifiedRecordNapi::GetUnifiedRecord(
    napi_env env, napi_callback_info info, std::shared_ptr<ContextBase> ctxt)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "UnifiedRecordNapi");
    ctxt->GetCbInfoSync(env, info);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_INVALID_PARAMETERS, "invalid arguments!");
    return static_cast<UnifiedRecordNapi *>(ctxt->native);
}

napi_value UnifiedRecordNapi::GetType(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "UnifiedRecordNapi");
    auto ctxt = std::make_shared<ContextBase>();
    auto uRecord = GetUnifiedRecord(env, info, ctxt);
    ASSERT_ERR(ctxt->env, (uRecord != nullptr && uRecord->value_ != nullptr), Status::E_INVALID_PARAMETERS,
        "invalid object!");
    ctxt->status = NapiDataUtils::SetValue(env, UD_TYPE_MAP.at(uRecord->value_->GetType()), ctxt->output);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_INVALID_PARAMETERS, "set type failed!");
    return ctxt->output;
}
} // namespace UDMF
} // namespace OHOS