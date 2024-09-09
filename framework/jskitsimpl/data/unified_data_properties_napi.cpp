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
#include "unified_meta.h"

namespace OHOS {
namespace UDMF {
napi_value UnifiedDataPropertiesNapi::Constructor(napi_env env)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "UnifiedDataPropertiesNapi");
    napi_property_descriptor properties[] = {
        DECLARE_NAPI_GETTER_SETTER("extras", GetExtras, SetExtras),
        DECLARE_NAPI_GETTER_SETTER("tag", GetTag, SetTag),
        DECLARE_NAPI_GETTER_SETTER("shareOptions", GetShareOptions, SetShareOptions),
        DECLARE_NAPI_GETTER("timestamp", GetTimestamp),
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
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_ERROR, ctxt->error);

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
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_ERROR, ctxt->error);
    return reinterpret_cast<UnifiedDataPropertiesNapi*>(ctxt->native);
}

napi_value UnifiedDataPropertiesNapi::GetExtras(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "UnifiedDataPropertiesNapi");
    auto ctxt = std::make_shared<ContextBase>();
    auto properties = GetPropertiesNapi(env, info, ctxt);
    ASSERT_ERR(ctxt->env, (properties != nullptr && properties->value_ != nullptr),
        Status::E_ERROR, "invalid object!");
    ctxt->output = OHOS::AppExecFwk::WrapWantParams(env, properties->value_->extras);
    return ctxt->output;
}

napi_value UnifiedDataPropertiesNapi::SetExtras(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "UnifiedDataPropertiesNapi");
    auto ctxt = std::make_shared<ContextBase>();
    AAFwk::WantParams value;
    auto input = [env, ctxt, &value](size_t argc, napi_value* argv) {
        ASSERT_BUSINESS_ERR(ctxt, argc >= 1, Status::E_ERROR, "Mandatory parameters are left unspecified");
        bool ret = OHOS::AppExecFwk::UnwrapWantParams(env, argv[0], value);
        ASSERT_BUSINESS_ERR(ctxt, ret, Status::E_ERROR, "parameter extras type must be Record<string, object>");
    };
    ctxt->GetCbInfoSync(env, info, input);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_ERROR, ctxt->error);
    auto properties = static_cast<UnifiedDataPropertiesNapi*>(ctxt->native);
    ASSERT_ERR(ctxt->env, (properties != nullptr && properties->value_ != nullptr),
        Status::E_ERROR, "invalid object!");
    properties->value_->extras = value;
    return nullptr;
}

napi_value UnifiedDataPropertiesNapi::GetTag(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "UnifiedDataPropertiesNapi");
    auto ctxt = std::make_shared<ContextBase>();
    auto properties = GetPropertiesNapi(env, info, ctxt);
    ASSERT_ERR(ctxt->env, (properties != nullptr && properties->value_ != nullptr),
        Status::E_ERROR, "invalid object!");
    ctxt->status = NapiDataUtils::SetValue(env, properties->value_->tag, ctxt->output);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_ERROR, "set tag failed");
    return ctxt->output;
}

napi_value UnifiedDataPropertiesNapi::SetTag(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "UnifiedDataPropertiesNapi");
    auto ctxt = std::make_shared<ContextBase>();
    std::string tag;
    auto input = [env, ctxt, &tag](size_t argc, napi_value* argv) {
        ASSERT_BUSINESS_ERR(ctxt, argc >= 1, Status::E_ERROR, "Mandatory parameters are left unspecified");
        ctxt->status = NapiDataUtils::GetValue(env, argv[0], tag);
        ASSERT_BUSINESS_ERR(ctxt, ctxt->status == napi_ok, Status::E_ERROR, "parameter tag type must be string");
    };
    ctxt->GetCbInfoSync(env, info, input);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_ERROR, ctxt->error);
    auto properties = static_cast<UnifiedDataPropertiesNapi*>(ctxt->native);
    ASSERT_ERR(ctxt->env, (properties != nullptr && properties->value_ != nullptr),
        Status::E_ERROR, "invalid object!");
    properties->value_->tag = tag;
    return nullptr;
}

napi_value UnifiedDataPropertiesNapi::GetShareOptions(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "UnifiedDataPropertiesNapi");
    auto ctxt = std::make_shared<ContextBase>();
    auto properties = GetPropertiesNapi(env, info, ctxt);
    ASSERT_ERR(ctxt->env, (properties != nullptr && properties->value_ != nullptr),
        Status::E_ERROR, "invalid object!");
    ctxt->status = NapiDataUtils::SetValue(env, properties->value_->shareOptions, ctxt->output);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_ERROR, "set ShareOptions failed");
    return ctxt->output;
}

napi_value UnifiedDataPropertiesNapi::SetShareOptions(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "UnifiedDataPropertiesNapi");
    auto ctxt = std::make_shared<ContextBase>();
    int32_t shareOptionsValue = ShareOptions::CROSS_APP;
    auto input = [env, ctxt, &shareOptionsValue](size_t argc, napi_value *argv) {
        ASSERT_BUSINESS_ERR(ctxt, argc >= 1, Status::E_ERROR, "Mandatory parameters are left unspecified");
        ctxt->status = NapiDataUtils::GetValue(env, argv[0], shareOptionsValue);
        ASSERT_BUSINESS_ERR(ctxt, ctxt->status == napi_ok,
            Status::E_ERROR, "parameter shareOptions type must be ShareOptions");
    };
    ctxt->GetCbInfoSync(env, info, input);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_ERROR, ctxt->error);
    auto properties = static_cast<UnifiedDataPropertiesNapi *>(ctxt->native);
    ASSERT_ERR(ctxt->env, (properties != nullptr && properties->value_ != nullptr),
        Status::E_ERROR, "invalid object!");
    properties->value_->shareOptions = static_cast<ShareOptions>(shareOptionsValue);
    return nullptr;
}

napi_value UnifiedDataPropertiesNapi::GetTimestamp(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "UnifiedDataPropertiesNapi");
    auto ctxt = std::make_shared<ContextBase>();
    auto properties = GetPropertiesNapi(env, info, ctxt);
    ASSERT_ERR(ctxt->env, (properties != nullptr && properties->value_ != nullptr),
        Status::E_ERROR, "invalid object!");
    ctxt->status = napi_create_date(env, properties->value_->timestamp, &ctxt->output);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_ERROR, "set timestamp failed");
    return ctxt->output;
}

napi_value UnifiedDataPropertiesNapi::GetDelayData(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "UnifiedDataPropertiesNapi");
    auto ctxt = std::make_shared<ContextBase>();
    auto properties = GetPropertiesNapi(env, info, ctxt);
    ASSERT_ERR(ctxt->env, (properties != nullptr && properties->value_ != nullptr),
        Status::E_ERROR, "invalid object!");
    if (properties->delayDataRef_ == nullptr) {
        LOG_INFO(UDMF_KITS_NAPI, "get GetDelayData undefined");
        napi_value undefinedValue;
        napi_get_undefined(env, &undefinedValue);
        return undefinedValue;
    }
    ctxt->status = napi_get_reference_value(env, properties->delayDataRef_, &ctxt->output);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_ERROR, "set delayData failed");
    return ctxt->output;
}

napi_value UnifiedDataPropertiesNapi::SetDelayData(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "UnifiedDataPropertiesNapi");
    auto ctxt = std::make_shared<ContextBase>();
    napi_value handler;
    napi_ref ref;
    auto input = [env, ctxt, &handler](size_t argc, napi_value* argv) {
        ASSERT_BUSINESS_ERR(ctxt, argc >= 1, Status::E_ERROR, "Mandatory parameters are left unspecified");
        napi_valuetype valueType = napi_undefined;
        ctxt->status = napi_typeof(env, argv[0], &valueType);
        ASSERT_BUSINESS_ERR(ctxt, ctxt->status == napi_ok && valueType == napi_function,
            Status::E_ERROR, "parameter getDelayData type must be GetDelayData");
        handler = argv[0];
    };
    ctxt->GetCbInfoSync(env, info, input);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_ERROR, ctxt->error);
    auto properties = static_cast<UnifiedDataPropertiesNapi *>(ctxt->native);
    ASSERT_ERR(ctxt->env, (properties != nullptr && properties->value_ != nullptr),
        Status::E_ERROR, "invalid object!");
    ctxt->status = napi_create_reference(env, handler, 1, &ref);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_ERROR, "napi_create_reference failed");
    properties->delayDataRef_ = ref;
    return nullptr;
}
} // namespace UDMF
} // namespace OHOS