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
#include "text_napi.h"

#include "logger.h"
#include "text.h"
#include "napi_data_utils.h"
#include "napi_error_utils.h"
#include "napi_queue.h"
#include "unified_record_napi.h"

namespace OHOS {
namespace UDMF {
napi_value TextNapi::Constructor(napi_env env)
{
    napi_property_descriptor properties[] = {
        /* Text extends UnifiedRecord */
        DECLARE_NAPI_FUNCTION("getType", UnifiedRecordNapi::GetType),
        /* Text property */
        DECLARE_NAPI_GETTER_SETTER("details", GetDetails, SetDetails),
    };
    size_t count = sizeof(properties) / sizeof(properties[0]);
    return NapiDataUtils::DefineClass(env, "Text", properties, count, TextNapi::New);
}

napi_value TextNapi::New(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "TextNapi::New");
    auto ctxt = std::make_shared<ContextBase>();
    ctxt->GetCbInfoSync(env, info);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_INVALID_PARAMETERS, "invalid arguments!");

    auto *text = new (std::nothrow) TextNapi();
    ASSERT_ERR(ctxt->env, text != nullptr, Status::E_FORBIDDEN, "no memory for text!");
    text->value_ = std::make_shared<Text>();
    ASSERT_CALL(env, napi_wrap(env, ctxt->self, text, Destructor, nullptr, nullptr), text);
    return ctxt->self;
}

void TextNapi::NewInstance(napi_env env, std::shared_ptr<UnifiedRecord> in, napi_value &out)
{
    ASSERT_CALL_VOID(env, napi_new_instance(env, Constructor(env), 0, nullptr, &out));
    auto *text = new (std::nothrow) TextNapi();
    ASSERT_ERR_VOID(env, text != nullptr, Status::E_FORBIDDEN, "no memory for text!");
    text->value_ = std::reinterpret_pointer_cast<Text>(in);
    ASSERT_CALL_DELETE(env, napi_wrap(env, out, text, Destructor, nullptr, nullptr), text);
}

void TextNapi::Destructor(napi_env env, void *data, void *hint)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "Text finalize.");
    auto *text = reinterpret_cast<TextNapi *>(data);
    ASSERT_VOID(text != nullptr, "finalize null!");
    delete text;
}

TextNapi *TextNapi::GetText(napi_env env, napi_callback_info info, std::shared_ptr<ContextBase> ctxt)
{
    ctxt->GetCbInfoSync(env, info);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_INVALID_PARAMETERS, "invalid arguments!");
    return reinterpret_cast<TextNapi *>(ctxt->native);
}

napi_value TextNapi::GetDetails(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "start");
    auto ctxt = std::make_shared<ContextBase>();
    auto text = GetText(env, info, ctxt);
    ASSERT_ERR(
        ctxt->env, (text != nullptr && text->value_ != nullptr), Status::E_INVALID_PARAMETERS, "invalid object!");
    ctxt->status = NapiDataUtils::SetValue(env, text->value_->GetDetails(), ctxt->output);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_INVALID_PARAMETERS, "set details failed!");
    return ctxt->output;
}

napi_value TextNapi::SetDetails(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "start");
    auto ctxt = std::make_shared<ContextBase>();
    UDDetails details;
    auto input = [env, ctxt, &details](size_t argc, napi_value *argv) {
        ASSERT_BUSINESS_ERR(ctxt, argc == 1, Status::E_INVALID_PARAMETERS, "invalid arguments!");
        ctxt->status = NapiDataUtils::GetValue(env, argv[0], details);
        ASSERT_BUSINESS_ERR(ctxt, ctxt->status == napi_ok, Status::E_INVALID_PARAMETERS, "invalid arguments!");
    };
    ctxt->GetCbInfoSync(env, info, input);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_INVALID_PARAMETERS, "invalid arguments!");
    auto text = reinterpret_cast<TextNapi *>(ctxt->native);
    ASSERT_ERR(
        ctxt->env, (text != nullptr && text->value_ != nullptr), Status::E_INVALID_PARAMETERS, "invalid object!");
    text->value_->SetDetails(details);
    return nullptr;
}
} // namespace UDMF
} // namespace OHOS