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

#include "link_napi.h"

#include "logger.h"
#include "link.h"
#include "napi_data_utils.h"
#include "napi_error_utils.h"
#include "napi_queue.h"
#include "unified_record_napi.h"
#include "text_napi.h"

namespace OHOS {
namespace UDMF {
napi_value LinkNapi::Constructor(napi_env env)
{
    napi_property_descriptor properties[] = {
        /* Link extends UnifiedRecord */
        DECLARE_NAPI_FUNCTION("getType", UnifiedRecordNapi::GetType),
        /* Link extends Text */
        DECLARE_NAPI_GETTER_SETTER("details", TextNapi::GetDetails, TextNapi::SetDetails),
        /* Link property */
        DECLARE_NAPI_GETTER_SETTER("url", GetUrl, SetUrl),
        DECLARE_NAPI_GETTER_SETTER("description", GetDescription, SetDescription),
    };
    size_t count = sizeof(properties) / sizeof(properties[0]);
    return NapiDataUtils::DefineClass(env, "HyperLink", properties, count, LinkNapi::New);
}

napi_value LinkNapi::New(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "LinkNapi::New");
    auto ctxt = std::make_shared<ContextBase>();

    ctxt->GetCbInfoSync(env, info);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_INVALID_PARAMETERS, "invalid arguments!");

    auto *link = new (std::nothrow) LinkNapi();
    ASSERT_ERR(ctxt->env, link != nullptr, Status::E_FORBIDDEN, "no memory for link!");
    link->value_ = std::make_shared<Link>();
    ASSERT_CALL(env, napi_wrap(env, ctxt->self, link, Destructor, nullptr, nullptr), link);
    return ctxt->self;
}

void LinkNapi::NewInstance(napi_env env, std::shared_ptr<UnifiedRecord> in, napi_value &out)
{
    ASSERT_CALL_VOID(env, napi_new_instance(env, Constructor(env), 0, nullptr, &out));
    auto *link = new (std::nothrow) LinkNapi();
    ASSERT_ERR_VOID(env, link != nullptr, Status::E_FORBIDDEN, "no memory for link!");
    link->value_ = std::reinterpret_pointer_cast<Link>(in);
    ASSERT_CALL_DELETE(env, napi_wrap(env, out, link, Destructor, nullptr, nullptr), link);
}

void LinkNapi::Destructor(napi_env env, void *data, void *hint)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "Link finalize.");
    auto *link = reinterpret_cast<LinkNapi *>(data);
    ASSERT_VOID(link != nullptr, "finalize null!");
    delete link;
}

LinkNapi *LinkNapi::GetLink(napi_env env, napi_callback_info info, std::shared_ptr<ContextBase> ctxt)
{
    ctxt->GetCbInfoSync(env, info);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_INVALID_PARAMETERS, "invalid arguments!");
    return reinterpret_cast<LinkNapi *>(ctxt->native);
}

napi_value LinkNapi::GetUrl(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "start");
    auto ctxt = std::make_shared<ContextBase>();
    auto link = GetLink(env, info, ctxt);
    ASSERT_ERR(
        ctxt->env, (link != nullptr && link->value_ != nullptr), Status::E_INVALID_PARAMETERS, "invalid object!");
    ctxt->status = NapiDataUtils::SetValue(env, link->value_->GetUrl(), ctxt->output);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_INVALID_PARAMETERS, "set url failed!");
    return ctxt->output;
}

napi_value LinkNapi::SetUrl(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "start");
    auto ctxt = std::make_shared<ContextBase>();
    std::string url;
    auto input = [env, ctxt, &url](size_t argc, napi_value *argv) {
        ASSERT_BUSINESS_ERR(ctxt, argc == 1, Status::E_INVALID_PARAMETERS, "invalid arguments!");
        ctxt->status = NapiDataUtils::GetValue(env, argv[0], url);
        ASSERT_BUSINESS_ERR(ctxt, ctxt->status == napi_ok, Status::E_INVALID_PARAMETERS, "invalid arguments!");
    };
    ctxt->GetCbInfoSync(env, info, input);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_INVALID_PARAMETERS, "invalid arguments!");
    auto link = reinterpret_cast<LinkNapi *>(ctxt->native);
    ASSERT_ERR(
        ctxt->env, (link != nullptr && link->value_ != nullptr), Status::E_INVALID_PARAMETERS, "invalid object!");
    link->value_->SetUrl(url);
    return nullptr;
}

napi_value LinkNapi::GetDescription(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "start");
    auto ctxt = std::make_shared<ContextBase>();
    auto link = GetLink(env, info, ctxt);
    ASSERT_ERR(
        ctxt->env, (link != nullptr && link->value_ != nullptr), Status::E_INVALID_PARAMETERS, "invalid object!");
    ctxt->status = NapiDataUtils::SetValue(env, link->value_->GetDescription(), ctxt->output);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_INVALID_PARAMETERS, "set description failed!");
    return ctxt->output;
}

napi_value LinkNapi::SetDescription(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "start");
    auto ctxt = std::make_shared<ContextBase>();
    std::string description;
    auto input = [env, ctxt, &description](size_t argc, napi_value *argv) {
        ASSERT_BUSINESS_ERR(ctxt, argc == 1, Status::E_INVALID_PARAMETERS, "invalid arguments!");
        ctxt->status = NapiDataUtils::GetValue(env, argv[0], description);
        ASSERT_BUSINESS_ERR(ctxt, ctxt->status == napi_ok, Status::E_INVALID_PARAMETERS, "invalid arguments!");
    };
    ctxt->GetCbInfoSync(env, info, input);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_INVALID_PARAMETERS, "invalid arguments!");
    auto link = reinterpret_cast<LinkNapi *>(ctxt->native);
    ASSERT_ERR(
        ctxt->env, (link != nullptr && link->value_ != nullptr), Status::E_INVALID_PARAMETERS, "invalid object!");
    link->value_->SetDescription(description);
    return nullptr;
}
} // namespace UDMF
} // namespace OHOS