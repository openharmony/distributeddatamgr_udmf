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
#define LOG_TAG "SummaryNapi"
#include "summary_napi.h"

#include "napi_data_utils.h"
#include "napi_error_utils.h"
#include "napi_queue.h"
#include "unified_types.h"

namespace OHOS {
namespace UDMF {
napi_value SummaryNapi::Constructor(napi_env env)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "SummaryNapi");
    napi_property_descriptor properties[] = {
        DECLARE_NAPI_GETTER_SETTER("summary", GetSummary, nullptr),
        DECLARE_NAPI_GETTER_SETTER("totalSize", GetTotal, nullptr),
    };
    size_t count = sizeof(properties) / sizeof(properties[0]);
    return NapiDataUtils::DefineClass(env, "Summary", properties, count, SummaryNapi::New);
}

napi_value SummaryNapi::New(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "SummaryNapi");
    auto ctxt = std::make_shared<ContextBase>();
    ctxt->GetCbInfoSync(env, info);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_ERROR, ctxt->error);

    auto *summary = new (std::nothrow) SummaryNapi();
    ASSERT_ERR(ctxt->env, summary != nullptr, Status::E_ERROR, "no memory for summary!");
    summary->value_ = std::make_shared<Summary>();
    ASSERT_CALL(env, napi_wrap(env, ctxt->self, summary, Destructor, nullptr, nullptr), summary);
    return ctxt->self;
}

void SummaryNapi::Destructor(napi_env env, void *data, void *hint)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "SummaryNapi finalize.");
    auto *summary = static_cast<SummaryNapi *>(data);
    ASSERT_VOID(summary != nullptr, "finalize null!");
    delete summary;
}

void SummaryNapi::NewInstance(napi_env env, std::shared_ptr<Summary> in, napi_value &out)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "SummaryNapi");
    ASSERT_CALL_VOID(env, napi_new_instance(env, Constructor(env), 0, nullptr, &out));
    auto *summary = new (std::nothrow) SummaryNapi();
    ASSERT_ERR_VOID(env, summary != nullptr, Status::E_ERROR, "no memory for summary!");
    summary->value_ = in;
    ASSERT_CALL_DELETE(env, napi_wrap(env, out, summary, Destructor, nullptr, nullptr), summary);
}

SummaryNapi *SummaryNapi::GetDataSummary(napi_env env, napi_callback_info info, std::shared_ptr<ContextBase> ctxt)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "SummaryNapi");
    ctxt->GetCbInfoSync(env, info);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_ERROR, ctxt->error);
    return static_cast<SummaryNapi *>(ctxt->native);
}

napi_value SummaryNapi::GetSummary(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "SummaryNapi");
    auto ctxt = std::make_shared<ContextBase>();
    auto summary = GetDataSummary(env, info, ctxt);
    ASSERT_ERR(ctxt->env, (summary != nullptr && summary->value_ != nullptr), Status::E_ERROR,
        "invalid object!");
    ctxt->status = NapiDataUtils::SetValue(env, summary->value_->summary, ctxt->output);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_ERROR, "set summery failed!");
    return ctxt->output;
}

napi_value SummaryNapi::GetTotal(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "SummaryNapi");
    auto ctxt = std::make_shared<ContextBase>();
    auto summary = GetDataSummary(env, info, ctxt);
    ASSERT_ERR(ctxt->env, (summary != nullptr && summary->value_ != nullptr), Status::E_ERROR,
        "invalid object!");
    ctxt->status = NapiDataUtils::SetValue(env, summary->value_->totalSize, ctxt->output);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_ERROR, "set total failed!");
    return ctxt->output;
}
} // namespace UDMF
} // namespace OHOS