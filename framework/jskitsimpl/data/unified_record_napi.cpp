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
#define LOG_TAG "UnifiedRecordNapi"
#include "unified_record_napi.h"
#include "napi_common_want.h"
#include "napi_data_utils.h"
#include "napi_error_utils.h"
#include "napi_queue.h"
#include "pixel_map_napi.h"
#include "unified_record.h"

namespace OHOS {
namespace UDMF {
napi_value UnifiedRecordNapi::Constructor(napi_env env)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "UnifiedRecordNapi");
    napi_property_descriptor properties[] = {
        /* UnifiedRecord properties */
        DECLARE_NAPI_FUNCTION("getType", GetType),
        DECLARE_NAPI_FUNCTION("getValue", GetValue),
    };
    size_t count = sizeof(properties) / sizeof(properties[0]);
    return NapiDataUtils::DefineClass(env, "UnifiedRecord", properties, count, UnifiedRecordNapi::New);
}

napi_value UnifiedRecordNapi::New(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "UnifiedRecordNapi");
    auto ctxt = std::make_shared<ContextBase>();
    std::string type;
    napi_value value = nullptr;
    auto input = [env, ctxt, &type, &value](size_t argc, napi_value* argv) {
        ASSERT_BUSINESS_ERR(ctxt, argc == 0 || argc == 2, Status::E_INVALID_PARAMETERS, "invalid arguments!");
        if (argc == 2) {
            ctxt->status = NapiDataUtils::GetValue(env, argv[0], type);
            ASSERT_BUSINESS_ERR(ctxt, ctxt->status == napi_ok, E_INVALID_PARAMETERS, "invalid arg[0] arguments!");
            value = argv[1];
        }
    };
    ctxt->GetCbInfoSync(env, info, input);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_INVALID_PARAMETERS, "invalid arguments!");
    
    auto *udRecord = new (std::nothrow) UnifiedRecordNapi();
    ASSERT_ERR(ctxt->env, udRecord != nullptr, Status::E_ERROR, "no memory for unified record!");
    ASSERT_CALL(env, napi_wrap(env, ctxt->self, udRecord, Destructor, nullptr, nullptr), udRecord);

    if(value != nullptr) {
        AddValue(env, udRecord, type, value);
    }
    return ctxt->self;
}

void UnifiedRecordNapi::AddValue(napi_env env, UnifiedRecordNapi *udRecord, std::string type, napi_value value){
    auto ctxt = std::make_shared<ContextBase>();
    std::unordered_map<std::string, int32_t> type_map;
    for (const auto& pair : UD_TYPE_MAP) {
        type_map[pair.second] = pair.first;
    }
    UDType utdType = static_cast<UDType>(type_map[type]);

    bool isArrayBuffer = false;
    NAPI_CALL_RETURN_VOID(env, napi_is_arraybuffer(env, value, &isArrayBuffer));
    napi_valuetype valueType = napi_undefined;
    ctxt->status = napi_typeof(env, value, &valueType);
    ASSERT_ERR_VOID(ctxt->env, ctxt->status == napi_ok, Status::E_INVALID_PARAMETERS, "invalid arguments!");
    if (type == "openharmony.pixel-map") {
        UnifiedRecord record(utdType, Media::PixelMapNapi::GetPixelMap(env, value));
        udRecord->value_ = std::make_shared<UnifiedRecord>(utdType, Media::PixelMapNapi::GetPixelMap(env, value));
    } else if (type == "openharmony.want") {
        OHOS::AAFwk::Want want;
        AppExecFwk::UnwrapWant(env, value, want);
        udRecord->value_ = std::make_shared<UnifiedRecord>(utdType, std::make_shared<OHOS::AAFwk::Want>(want));
    } else if (isArrayBuffer) {
        void *data = nullptr;
        size_t dataLen = 0;
        NAPI_CALL_RETURN_VOID(env, napi_get_arraybuffer_info(env, value, &data, &dataLen));
        auto dataU8 = std::vector<uint8_t>(reinterpret_cast<uint8_t *>(data), reinterpret_cast<uint8_t *>(data) + dataLen);
        udRecord->value_ = std::make_shared<UnifiedRecord>(utdType, dataU8);
    } else if (valueType == napi_string) {
        std::string data;
        ctxt->status = NapiDataUtils::GetValue(env, value, data);
        ASSERT_ERR_VOID(ctxt->env, ctxt->status == napi_ok, Status::E_INVALID_PARAMETERS, "invalid arguments!");
        udRecord->value_ = std::make_shared<UnifiedRecord>(utdType, data);
    } else if (valueType == napi_number) {
        std::vector<uint8_t> data;
        ctxt->status = NapiDataUtils::GetValue(env, value, data);
        ASSERT_ERR_VOID(ctxt->env, ctxt->status == napi_ok, Status::E_INVALID_PARAMETERS, "invalid arguments!");
        udRecord->value_ = std::make_shared<UnifiedRecord>(utdType, data);
    } else {
        LOG_ERROR(UDMF_KITS_NAPI, "invalid arguments!");
    }
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

napi_value UnifiedRecordNapi::GetValue(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "UnifiedRecordNapi");
    auto ctxt = std::make_shared<ContextBase>();
    auto uRecord = GetUnifiedRecord(env, info, ctxt);
    ASSERT_ERR(ctxt->env, (uRecord != nullptr && uRecord->value_ != nullptr), Status::E_INVALID_PARAMETERS, "invalid object!");
    std::visit([&](const auto& value) { SetValueWrapper(env, value, ctxt->output); }, uRecord->value_->GetValue());
    return ctxt->output;
}
} // namespace UDMF
} // namespace OHOS