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
#define LOG_TAG "PlainTextNapi"
#include "plain_text_napi.h"

#include "napi_data_utils.h"
#include "napi_error_utils.h"
#include "napi_queue.h"
#include "plain_text.h"
#include "text_napi.h"
#include "unified_record_napi.h"

namespace OHOS {
namespace UDMF {
napi_value PlainTextNapi::Constructor(napi_env env)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "PlainTextNapi");
    napi_property_descriptor properties[] = {
        /* PlainText extends UnifiedRecord */
        DECLARE_NAPI_FUNCTION("getType", UnifiedRecordNapi::GetType),
        DECLARE_NAPI_FUNCTION("getValue", UnifiedRecordNapi::GetValue),
        /* PlainText extends Text */
        DECLARE_NAPI_GETTER_SETTER("details", TextNapi::GetDetails, TextNapi::SetDetails),
        /* PlainText properties */
        DECLARE_NAPI_GETTER_SETTER("textContent", GetContent, SetContent),
        DECLARE_NAPI_GETTER_SETTER("abstract", GetAbstract, SetAbstract),
    };
    size_t count = sizeof(properties) / sizeof(properties[0]);
    return NapiDataUtils::DefineClass(env, "PlainText", properties, count, PlainTextNapi::New);
}

napi_value PlainTextNapi::New(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "PlainTextNapi");
    auto ctxt = std::make_shared<ContextBase>();
    ctxt->GetCbInfoSync(env, info);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_ERROR, ctxt->error);

    auto *plainText = new (std::nothrow) PlainTextNapi();
    ASSERT_ERR(ctxt->env, plainText != nullptr, Status::E_ERROR, "no memory for plain text!");
    plainText->value_ = std::make_shared<PlainText>();
    ASSERT_CALL(env, napi_wrap(env, ctxt->self, plainText, Destructor, nullptr, nullptr), plainText);
    return ctxt->self;
}

void PlainTextNapi::NewInstance(napi_env env, std::shared_ptr<UnifiedRecord> in, napi_value &out)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "PlainTextNapi");
    ASSERT_CALL_VOID(env, napi_new_instance(env, Constructor(env), 0, nullptr, &out));
    auto *plainText = new (std::nothrow) PlainTextNapi();
    ASSERT_ERR_VOID(env, plainText != nullptr, Status::E_ERROR, "no memory for plain text!");
    plainText->value_ = std::static_pointer_cast<PlainText>(in);
    ASSERT_CALL_DELETE(env, napi_wrap(env, out, plainText, Destructor, nullptr, nullptr), plainText);
}

void PlainTextNapi::Destructor(napi_env env, void *data, void *hint)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "PlainTextNapi finalize.");
    auto *plainText = static_cast<PlainTextNapi *>(data);
    ASSERT_VOID(plainText != nullptr, "finalize null!");
    delete plainText;
}

PlainTextNapi *PlainTextNapi::GetPlainText(napi_env env, napi_callback_info info, std::shared_ptr<ContextBase> ctxt)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "PlainTextNapi");
    ctxt->GetCbInfoSync(env, info);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_ERROR, ctxt->error);
    return static_cast<PlainTextNapi *>(ctxt->native);
}

napi_value PlainTextNapi::GetContent(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "PlainTextNapi");
    auto ctxt = std::make_shared<ContextBase>();
    auto plainText = GetPlainText(env, info, ctxt);
    ASSERT_ERR(ctxt->env, (plainText != nullptr && plainText->value_ != nullptr), Status::E_ERROR,
        "invalid object!");
    ctxt->status = NapiDataUtils::SetValue(env, plainText->value_->GetContent(), ctxt->output);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_ERROR, "set text content failed!");
    return ctxt->output;
}

napi_value PlainTextNapi::SetContent(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "PlainTextNapi");
    auto ctxt = std::make_shared<ContextBase>();
    std::string content;
    auto input = [env, ctxt, &content](size_t argc, napi_value *argv) {
        ASSERT_BUSINESS_ERR(ctxt, argc >= 1,
            Status::E_INVALID_PARAMETERS, "Parameter error: Mandatory parameters are left unspecified");
        ctxt->status = NapiDataUtils::GetValue(env, argv[0], content);
        ASSERT_BUSINESS_ERR(ctxt, ctxt->status == napi_ok,
            Status::E_INVALID_PARAMETERS, "Parameter error: parameter content type must be string");
    };
    ctxt->GetCbInfoSync(env, info, input);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_ERROR, ctxt->error);
    auto plainText = static_cast<PlainTextNapi *>(ctxt->native);
    ASSERT_ERR(ctxt->env, (plainText != nullptr && plainText->value_ != nullptr), Status::E_ERROR,
        "invalid object!");
    plainText->value_->SetContent(content);
    return nullptr;
}

napi_value PlainTextNapi::GetAbstract(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "PlainTextNapi");
    auto ctxt = std::make_shared<ContextBase>();
    auto plainText = GetPlainText(env, info, ctxt);
    ASSERT_ERR(ctxt->env, (plainText != nullptr && plainText->value_ != nullptr), Status::E_ERROR,
        "invalid object!");
    ctxt->status = NapiDataUtils::SetValue(env, plainText->value_->GetAbstract(), ctxt->output);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_ERROR, "set abstract failed!");
    return ctxt->output;
}

napi_value PlainTextNapi::SetAbstract(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "PlainTextNapi");
    auto ctxt = std::make_shared<ContextBase>();
    std::string abstract;
    auto input = [env, ctxt, &abstract](size_t argc, napi_value *argv) {
        ASSERT_BUSINESS_ERR(ctxt, argc >= 1,
            Status::E_INVALID_PARAMETERS, "Parameter error: Mandatory parameters are left unspecified");
        ctxt->status = NapiDataUtils::GetValue(env, argv[0], abstract);
        ASSERT_BUSINESS_ERR(ctxt, ctxt->status == napi_ok,
            Status::E_INVALID_PARAMETERS, "Parameter error: parameter abstract type must be string");
    };
    ctxt->GetCbInfoSync(env, info, input);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_ERROR, ctxt->error);
    auto plainText = static_cast<PlainTextNapi *>(ctxt->native);
    ASSERT_ERR(ctxt->env, (plainText != nullptr && plainText->value_ != nullptr), Status::E_ERROR,
        "invalid object!");
    plainText->value_->SetAbstract(abstract);
    return nullptr;
}
} // namespace UDMF
} // namespace OHOS