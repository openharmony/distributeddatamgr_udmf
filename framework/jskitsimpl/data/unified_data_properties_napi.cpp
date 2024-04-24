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
#define LOG_TAG "UnifiedDataPropertiesNapi"
#include "unified_data_properties_napi.h"

#include "napi_data_utils.h"
#include "napi_error_utils.h"
#include "unified_data.h"

namespace OHOS {
namespace UDMF {
napi_value UnifiedDataPropertiesNapi::Constructor(napi_env env)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "UnifiedDataPropertiesNapi");
    napi_property_descriptor properties[] = {
        DECLARE_NAPI_GETTER_SETTER("extras", GetExtras, SetExtras),
        DECLARE_NAPI_GETTER_SETTER("tag", GetTag, SetTag),
        DECLARE_NAPI_GETTER_SETTER("shareOptions", GetShareOption, SetShareOption),
        DECLARE_NAPI_GETTER_SETTER("timestamp", GetTimestamp, SetTimestamp),
        DECLARE_NAPI_GETTER_SETTER("getDelayData", GetDelayData, SetDelayData),
    };
    size_t count = sizeof(properties) / sizeof(properties[0]);
    return NapiDataUtils::DefineClass(env, "UnifiedDataProperties", properties, count, UnifiedDataPropertiesNapi::New);
}

napi_value UnifiedDataPropertiesNapi::New(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "UnifiedDataPropertiesNapi");
    auto ctxt = std::make_shared<ContextBase>();
    ctxt->GetCbInfoSync(env, info);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_INVALID_PARAMETERS, "invalid arguments!");

    auto* properties = new (std::nothrow) UnifiedDataPropertiesNapi();
    ASSERT_ERR(ctxt->env, properties != nullptr, Status::E_ERROR, "no memory for properties!");

    properties->value_ = std::make_shared<UnifiedDataProperties>();
    ASSERT_CALL(env, napi_wrap(env, ctxt->self, properties, Destructor, nullptr, nullptr), properties);
    return ctxt->self;
}

void UnifiedDataPropertiesNapi::Destructor(napi_env env, void *data, void *hint)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "UnifiedDataPropertiesNapi finalize.");
    auto *properties = static_cast<UnifiedDataPropertiesNapi *>(data);
    ASSERT_VOID(properties != nullptr, "finalize null!");
    delete properties;
}

UnifiedDataPropertiesNapi* UnifiedDataPropertiesNapi::GetPropertiesNapi(
    napi_env env, napi_callback_info info, std::shared_ptr<ContextBase> ctxt)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "UnifiedDataPropertiesNapi");
    ctxt->GetCbInfoSync(env, info);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_INVALID_PARAMETERS, "invalid arguments!");
    return reinterpret_cast<UnifiedDataPropertiesNapi*>(ctxt->native);
}

napi_value UnifiedDataPropertiesNapi::GetExtras(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "UnifiedDataPropertiesNapi");
    auto ctxt = std::make_shared<ContextBase>();
    auto properties = GetPropertiesNapi(env, info, ctxt);
    ASSERT_ERR(ctxt->env, (properties != nullptr && properties->value_ != nullptr),
        Status::E_INVALID_PARAMETERS, "invalid arguments!");
    ctxt->output = OHOS::AppExecFwk::WrapWantParams(env, properties->value_->extras);
    return ctxt->output;
}

napi_value UnifiedDataPropertiesNapi::SetExtras(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "UnifiedDataPropertiesNapi");
    auto ctxt = std::make_shared<ContextBase>();
    AAFwk::WantParams value;
    auto input = [env, ctxt, &value](size_t argc, napi_value* argv) {
        ASSERT_BUSINESS_ERR(ctxt, argc >= 1, Status::E_INVALID_PARAMETERS, "invalid arguments!");
        bool ret = OHOS::AppExecFwk::UnwrapWantParams(env, argv[0], value);
        ASSERT_BUSINESS_ERR(ctxt, ret, Status::E_INVALID_PARAMETERS, "invalid arguments!");
    };
    ctxt->GetCbInfoSync(env, info, input);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_INVALID_PARAMETERS, "invalid arguments!");
    auto properties = static_cast<UnifiedDataPropertiesNapi*>(ctxt->native);
    ASSERT_ERR(ctxt->env, (properties != nullptr && properties->value_ != nullptr),
        Status::E_INVALID_PARAMETERS, "invalid arguments!");
    properties->value_->extras = value;
    return nullptr;
}

napi_value UnifiedDataPropertiesNapi::GetTag(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "UnifiedDataPropertiesNapi");
    auto ctxt = std::make_shared<ContextBase>();
    auto properties = GetPropertiesNapi(env, info, ctxt);
    ASSERT_ERR(ctxt->env, (properties != nullptr && properties->value_ != nullptr),
        Status::E_INVALID_PARAMETERS, "invalid object!");
    ctxt->status = NapiDataUtils::SetValue(env, properties->value_->tag, ctxt->output);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_INVALID_PARAMETERS, "invalid arguments!");
    return ctxt->output;
}

napi_value UnifiedDataPropertiesNapi::SetTag(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "UnifiedDataPropertiesNapi");
    auto ctxt = std::make_shared<ContextBase>();
    std::string tag;
    auto input = [env, ctxt, &tag](size_t argc, napi_value* argv) {
        ASSERT_BUSINESS_ERR(ctxt, argc >= 1, Status::E_INVALID_PARAMETERS, "invalid arguments!");
        ctxt->status = NapiDataUtils::GetValue(env, argv[0], tag);
        ASSERT_BUSINESS_ERR(ctxt, ctxt->status == napi_ok, Status::E_INVALID_PARAMETERS, "invalid arguments!");
    };
    ctxt->GetCbInfoSync(env, info, input);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_INVALID_PARAMETERS, "invalid arguments!");
    auto properties = static_cast<UnifiedDataPropertiesNapi*>(ctxt->native);
    ASSERT_ERR(ctxt->env, (properties != nullptr && properties->value_ != nullptr),
        Status::E_INVALID_PARAMETERS, "invalid arguments!");
    properties->value_->tag = tag;
    return nullptr;
}

napi_value UnifiedDataPropertiesNapi::GetShareOption(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "UnifiedDataPropertiesNapi");
    auto ctxt = std::make_shared<ContextBase>();
    auto properties = GetPropertiesNapi(env, info, ctxt);
    ASSERT_ERR(ctxt->env, (properties != nullptr && properties->value_ != nullptr),
        Status::E_INVALID_PARAMETERS, "invalid arguments!");
    ctxt->status = NapiDataUtils::SetValue(env, properties->value_->shareOption, ctxt->output);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_INVALID_PARAMETERS, "invalid arguments!");
    return ctxt->output;
}

napi_value UnifiedDataPropertiesNapi::SetShareOption(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "UnifiedDataPropertiesNapi");
    auto ctxt = std::make_shared<ContextBase>();
    int32_t shareOptionValue = ShareOption::CROSS_APP;
    auto input = [env, ctxt, &shareOptionValue](size_t argc, napi_value *argv) {
        ASSERT_BUSINESS_ERR(ctxt, argc >= 1, Status::E_INVALID_PARAMETERS, "invalid arguments!");
        ctxt->status = NapiDataUtils::GetValue(env, argv[0], shareOptionValue);
        ASSERT_BUSINESS_ERR(ctxt, ctxt->status == napi_ok, Status::E_INVALID_PARAMETERS, "invalid arguments!");
    };
    ctxt->GetCbInfoSync(env, info, input);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_INVALID_PARAMETERS, "invalid arguments!");
    auto properties = static_cast<UnifiedDataPropertiesNapi *>(ctxt->native);
    ASSERT_ERR(ctxt->env, (properties != nullptr && properties->value_ != nullptr),
        Status::E_INVALID_PARAMETERS, "invalid arguments!");
    properties->value_->shareOption = static_cast<ShareOption>(shareOptionValue);
    return nullptr;
}

napi_value UnifiedDataPropertiesNapi::GetTimestamp(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "UnifiedDataPropertiesNapi");
    auto ctxt = std::make_shared<ContextBase>();
    auto properties = GetPropertiesNapi(env, info, ctxt);
    ASSERT_ERR(ctxt->env, (properties != nullptr && properties->value_ != nullptr),
        Status::E_INVALID_PARAMETERS, "invalid arguments!");
    ctxt->status = napi_create_date(env, properties->value_->timestamp, &ctxt->output);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_INVALID_PARAMETERS, "invalid arguments!");
    return ctxt->output;
}

napi_value UnifiedDataPropertiesNapi::SetTimestamp(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "UnifiedDataPropertiesNapi");
    auto ctxt = std::make_shared<ContextBase>();
    double timestampValue = 0;
    auto input = [env, ctxt, &timestampValue](size_t argc, napi_value *argv) {
        ASSERT_BUSINESS_ERR(ctxt, argc >= 1, Status::E_INVALID_PARAMETERS, "invalid arguments!");
        ctxt->status = napi_get_date_value(env, argv[0], &timestampValue);
        ASSERT_BUSINESS_ERR(ctxt, ctxt->status == napi_ok, Status::E_INVALID_PARAMETERS, "invalid arguments!");
    };
    ctxt->GetCbInfoSync(env, info, input);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_INVALID_PARAMETERS, "invalid arguments!");
    auto properties = static_cast<UnifiedDataPropertiesNapi *>(ctxt->native);
    ASSERT_ERR(ctxt->env, (properties != nullptr && properties->value_ != nullptr),
        Status::E_INVALID_PARAMETERS, "invalid arguments!");
    properties->value_->timestamp = timestampValue;
    return nullptr;
}

napi_value UnifiedDataPropertiesNapi::GetDelayData(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "UnifiedDataPropertiesNapi");
    auto ctxt = std::make_shared<ContextBase>();
    auto properties = GetPropertiesNapi(env, info, ctxt);
    ASSERT_ERR(ctxt->env, (properties != nullptr && properties->value_ != nullptr),
        Status::E_INVALID_PARAMETERS, "invalid arguments!");
    if (properties->delayDataRef_ == nullptr) {
        LOG_INFO(UDMF_KITS_NAPI, "get GetDelayData undefined");
        napi_value undefinedValue;
        napi_get_undefined(env, &undefinedValue);
        return undefinedValue;
    }
    ctxt->status = napi_get_reference_value(env, properties->delayDataRef_, &ctxt->output);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_INVALID_PARAMETERS, "invalid arguments!");
    return ctxt->output;
}

napi_value UnifiedDataPropertiesNapi::SetDelayData(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "UnifiedDataPropertiesNapi");
    auto ctxt = std::make_shared<ContextBase>();
    napi_value handler;
    napi_ref ref;
    auto input = [env, ctxt, &handler](size_t argc, napi_value* argv) {
        ASSERT_BUSINESS_ERR(ctxt, argc >= 1, Status::E_INVALID_PARAMETERS, "invalid arguments!");
        napi_valuetype valueType = napi_undefined;
        ctxt->status = napi_typeof(env, argv[0], &valueType);
        ASSERT_BUSINESS_ERR(ctxt, ctxt->status == napi_ok && valueType == napi_function,
            Status::E_INVALID_PARAMETERS, "invalid arguments!");
        handler = argv[0];
    };
    ctxt->GetCbInfoSync(env, info, input);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_INVALID_PARAMETERS, "invalid arguments!");
    auto properties = static_cast<UnifiedDataPropertiesNapi *>(ctxt->native);
    ASSERT_ERR(ctxt->env, (properties != nullptr && properties->value_ != nullptr),
        Status::E_INVALID_PARAMETERS, "invalid arguments!");
    ctxt->status = napi_create_reference(env, handler, 1, &ref);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_INVALID_PARAMETERS, "invalid arguments!");
    properties->delayDataRef_ = ref;
    return nullptr;
}
} // namespace UDMF
} // namespace OHOS