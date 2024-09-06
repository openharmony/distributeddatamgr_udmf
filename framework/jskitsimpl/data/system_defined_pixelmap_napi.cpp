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
#define LOG_TAG "SystemDefinedPixelMapNapi"
#include "system_defined_pixelmap_napi.h"

#include "system_defined_pixelmap.h"
#include "napi_data_utils.h"
#include "napi_error_utils.h"
#include "napi_queue.h"
#include "unified_record_napi.h"
#include "system_defined_record_napi.h"

namespace OHOS {
namespace UDMF {
napi_value SystemDefinedPixelMapNapi::Constructor(napi_env env)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "SystemDefinedPixelMapNapi");
    napi_property_descriptor properties[] = {
        /* SystemDefinedPixelMap extends UnifiedRecord */
        DECLARE_NAPI_FUNCTION("getType", UnifiedRecordNapi::GetType),
        DECLARE_NAPI_FUNCTION("getValue", UnifiedRecordNapi::GetValue),
        /* SystemDefinedPixelMap extends SystemDefinedRecord */
        DECLARE_NAPI_GETTER_SETTER("details", SystemDefinedRecordNapi::GetDetails, SystemDefinedRecordNapi::SetDetails),
        /* SystemDefinedPixelMap properties */
        DECLARE_NAPI_GETTER_SETTER("rawData", GetRawData, SetRawData),
    };
    size_t count = sizeof(properties) / sizeof(properties[0]);
    return NapiDataUtils::DefineClass(env, "SystemDefinedPixelMap", properties, count, SystemDefinedPixelMapNapi::New);
}

napi_value SystemDefinedPixelMapNapi::New(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "SystemDefinedPixelMapNapi");
    auto ctxt = std::make_shared<ContextBase>();
    ctxt->GetCbInfoSync(env, info);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_ERROR, ctxt->error);

    auto *sdPixelMap = new (std::nothrow) SystemDefinedPixelMapNapi();
    ASSERT_ERR(ctxt->env, sdPixelMap != nullptr, Status::E_ERROR, "no memory for system defined pixel map!");
    sdPixelMap->value_ = std::make_shared<SystemDefinedPixelMap>();
    ASSERT_CALL(env, napi_wrap(env, ctxt->self, sdPixelMap, Destructor, nullptr, nullptr), sdPixelMap);
    return ctxt->self;
}

void SystemDefinedPixelMapNapi::NewInstance(napi_env env, std::shared_ptr<UnifiedRecord> in, napi_value &out)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "SystemDefinedPixelMapNapi");
    ASSERT_CALL_VOID(env, napi_new_instance(env, Constructor(env), 0, nullptr, &out));
    auto *sdPixelMap = new (std::nothrow) SystemDefinedPixelMapNapi();
    ASSERT_ERR_VOID(env, sdPixelMap != nullptr, Status::E_ERROR, "no memory for system defined pixel map!");
    sdPixelMap->value_ = std::static_pointer_cast<SystemDefinedPixelMap>(in);
    ASSERT_CALL_DELETE(env, napi_wrap(env, out, sdPixelMap, Destructor, nullptr, nullptr), sdPixelMap);
}

void SystemDefinedPixelMapNapi::Destructor(napi_env env, void *data, void *hint)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "SystemDefinedPixelMapNapi finalize.");
    auto *sdPixelMap = static_cast<SystemDefinedPixelMapNapi *>(data);
    ASSERT_VOID(sdPixelMap != nullptr, "finalize null!");
    delete sdPixelMap;
}

SystemDefinedPixelMapNapi *SystemDefinedPixelMapNapi::GetSystemDefinedPixelMap(
    napi_env env, napi_callback_info info, std::shared_ptr<ContextBase> ctxt)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "SystemDefinedPixelMapNapi");
    ctxt->GetCbInfoSync(env, info);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_ERROR, ctxt->error);
    return static_cast<SystemDefinedPixelMapNapi *>(ctxt->native);
}

napi_value SystemDefinedPixelMapNapi::GetRawData(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "SystemDefinedPixelMapNapi");
    auto ctxt = std::make_shared<ContextBase>();
    auto sdPixelMap = GetSystemDefinedPixelMap(env, info, ctxt);
    ASSERT_ERR(ctxt->env, (sdPixelMap != nullptr && sdPixelMap->value_ != nullptr), Status::E_ERROR,
        "invalid object!");
    ctxt->status = NapiDataUtils::SetValue(env, sdPixelMap->value_->GetRawData(), ctxt->output);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_ERROR, "set raw data failed!");
    return ctxt->output;
}

napi_value SystemDefinedPixelMapNapi::SetRawData(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "SystemDefinedPixelMapNapi");
    auto ctxt = std::make_shared<ContextBase>();
    std::vector<uint8_t> pixelMap;
    auto input = [env, ctxt, &pixelMap](size_t argc, napi_value *argv) {
        ASSERT_BUSINESS_ERR(ctxt, argc >= 1,
            Status::E_INVALID_PARAMETERS, "Parameter error: Mandatory parameters are left unspecified");
        ctxt->status = NapiDataUtils::GetValue(env, argv[0], pixelMap);
        ASSERT_BUSINESS_ERR(ctxt, ctxt->status == napi_ok,
            Status::E_INVALID_PARAMETERS, "Parameter error: parameter rawData type must be Uint8Array");
    };
    ctxt->GetCbInfoSync(env, info, input);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_ERROR, ctxt->error);
    auto sdPixelMap = static_cast<SystemDefinedPixelMapNapi *>(ctxt->native);
    ASSERT_ERR(ctxt->env, (sdPixelMap != nullptr && sdPixelMap->value_ != nullptr), Status::E_ERROR,
        "invalid object!");
    sdPixelMap->value_->SetRawData(pixelMap);
    return nullptr;
}
} // namespace UDMF
} // namespace OHOS