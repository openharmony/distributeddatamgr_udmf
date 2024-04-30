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
#define LOG_TAG "HtmlNapi"
#include "html_napi.h"

#include "html.h"
#include "napi_data_utils.h"
#include "napi_error_utils.h"
#include "napi_queue.h"
#include "text_napi.h"
#include "unified_record_napi.h"

namespace OHOS {
namespace UDMF {
napi_value HtmlNapi::Constructor(napi_env env)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "HtmlNapi");
    napi_property_descriptor properties[] = {
        /* Html extends UnifiedRecord */
        DECLARE_NAPI_FUNCTION("getType", UnifiedRecordNapi::GetType),
        DECLARE_NAPI_FUNCTION("getValue", UnifiedRecordNapi::GetValue),
        /* Html extends Text */
        DECLARE_NAPI_GETTER_SETTER("details", TextNapi::GetDetails, TextNapi::SetDetails),
        /* Html properties */
        DECLARE_NAPI_GETTER_SETTER("htmlContent", GetHtmlContent, SetHtmlContent),
        DECLARE_NAPI_GETTER_SETTER("plainContent", GetPlainContent, SetPlainContent),
    };
    size_t count = sizeof(properties) / sizeof(properties[0]);
    return NapiDataUtils::DefineClass(env, "HTML", properties, count, HtmlNapi::New);
}

napi_value HtmlNapi::New(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "HtmlNapi");
    auto ctxt = std::make_shared<ContextBase>();
    ctxt->GetCbInfoSync(env, info);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_ERROR, ctxt->error);

    auto *html = new (std::nothrow) HtmlNapi();
    ASSERT_ERR(ctxt->env, html != nullptr, Status::E_ERROR, "no memory for html!");
    html->value_ = std::make_shared<Html>();
    ASSERT_CALL(env, napi_wrap(env, ctxt->self, html, Destructor, nullptr, nullptr), html);
    return ctxt->self;
}

void HtmlNapi::NewInstance(napi_env env, std::shared_ptr<UnifiedRecord> in, napi_value &out)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "HtmlNapi");
    ASSERT_CALL_VOID(env, napi_new_instance(env, Constructor(env), 0, nullptr, &out));
    auto *html = new (std::nothrow) HtmlNapi();
    ASSERT_ERR_VOID(env, html != nullptr, Status::E_ERROR, "no memory for html!");
    html->value_ = std::static_pointer_cast<Html>(in);
    ASSERT_CALL_DELETE(env, napi_wrap(env, out, html, Destructor, nullptr, nullptr), html);
}

void HtmlNapi::Destructor(napi_env env, void *data, void *hint)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "HtmlNapi finalize.");
    auto *html = static_cast<HtmlNapi *>(data);
    ASSERT_VOID(html != nullptr, "finalize null!");
    delete html;
}

HtmlNapi *HtmlNapi::GetHtml(napi_env env, napi_callback_info info, std::shared_ptr<ContextBase> ctxt)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "HtmlNapi");
    ctxt->GetCbInfoSync(env, info);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_ERROR, ctxt->error);
    return static_cast<HtmlNapi *>(ctxt->native);
}

napi_value HtmlNapi::GetPlainContent(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "HtmlNapi");
    auto ctxt = std::make_shared<ContextBase>();
    auto html = GetHtml(env, info, ctxt);
    ASSERT_ERR(
        ctxt->env, (html != nullptr && html->value_ != nullptr), Status::E_ERROR, "invalid object!");
    ctxt->status = NapiDataUtils::SetValue(env, html->value_->GetPlainContent(), ctxt->output);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_ERROR, "set plain content failed!");
    return ctxt->output;
}

napi_value HtmlNapi::SetPlainContent(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "HtmlNapi");
    auto ctxt = std::make_shared<ContextBase>();
    std::string plainContent;
    auto input = [env, ctxt, &plainContent](size_t argc, napi_value *argv) {
        ASSERT_BUSINESS_ERR(ctxt, argc >= 1,
            Status::E_INVALID_PARAMETERS, "Parameter error: Mandatory parameters are left unspecified");
        ctxt->status = NapiDataUtils::GetValue(env, argv[0], plainContent);
        ASSERT_BUSINESS_ERR(ctxt, ctxt->status == napi_ok,
            Status::E_INVALID_PARAMETERS, "Parameter error: parameter plainContent type must be string");
    };
    ctxt->GetCbInfoSync(env, info, input);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_ERROR, ctxt->error);
    auto html = static_cast<HtmlNapi *>(ctxt->native);
    ASSERT_ERR(
        ctxt->env, (html != nullptr && html->value_ != nullptr), Status::E_ERROR, "invalid object!");
    html->value_->SetPlainContent(plainContent);
    return nullptr;
}

napi_value HtmlNapi::GetHtmlContent(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "HtmlNapi");
    auto ctxt = std::make_shared<ContextBase>();
    auto html = GetHtml(env, info, ctxt);
    ASSERT_ERR(
        ctxt->env, (html != nullptr && html->value_ != nullptr), Status::E_ERROR, "invalid object!");
    ctxt->status = NapiDataUtils::SetValue(env, html->value_->GetHtmlContent(), ctxt->output);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_ERROR, "set html failed!");
    return ctxt->output;
}

napi_value HtmlNapi::SetHtmlContent(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "HtmlNapi");
    auto ctxt = std::make_shared<ContextBase>();
    std::string htmlContent;
    auto input = [env, ctxt, &htmlContent](size_t argc, napi_value *argv) {
        ASSERT_BUSINESS_ERR(ctxt, argc >= 1,
            Status::E_INVALID_PARAMETERS, "Parameter error: Mandatory parameters are left unspecified");
        ctxt->status = NapiDataUtils::GetValue(env, argv[0], htmlContent);
        ASSERT_BUSINESS_ERR(ctxt, ctxt->status == napi_ok,
            Status::E_INVALID_PARAMETERS, "Parameter error: parameter htmlContent type must be string");
    };
    ctxt->GetCbInfoSync(env, info, input);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_ERROR, ctxt->error);
    auto html = static_cast<HtmlNapi *>(ctxt->native);
    ASSERT_ERR(
        ctxt->env, (html != nullptr && html->value_ != nullptr), Status::E_ERROR, "invalid object!");
    html->value_->SetHtmlContent(htmlContent);
    return nullptr;
}
} // namespace UDMF
} // namespace OHOS