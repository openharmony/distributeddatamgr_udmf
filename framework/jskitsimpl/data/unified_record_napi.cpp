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

#include "plain_text.h"
#include "html.h"
#include "link.h"
#include "image.h"
#include "video.h"
#include "audio.h"
#include "folder.h"
#include "system_defined_appitem.h"
#include "system_defined_form.h"
#include "system_defined_pixelmap.h"
#include "application_defined_record.h"

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
    auto input = [env, ctxt, &type, &value](size_t argc, napi_value *argv) {
        ASSERT_BUSINESS_ERR(ctxt, argc == 0 || argc >= 2,
            Status::E_INVALID_PARAMETERS, "Parameter error: Mandatory parameters are left unspecified");
        if (argc >= 2) {
            ctxt->status = NapiDataUtils::GetValue(env, argv[0], type);
            ASSERT_BUSINESS_ERR(ctxt, ctxt->status == napi_ok && !type.empty(),
                Status::E_INVALID_PARAMETERS, "Parameter error: parameter type type must be string");
            value = argv[1];
        }
    };
    ctxt->GetCbInfoSync(env, info, input);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_ERROR, ctxt->error);

    auto *udRecord = new (std::nothrow) UnifiedRecordNapi();
    ASSERT_ERR(ctxt->env, udRecord != nullptr, Status::E_ERROR, "no memory for unified record!");
    if (value != nullptr) {
        udRecord->value_ = GenerateNativeRecord(env, type, value);
    } else {
        udRecord->value_ = std::make_shared<UnifiedRecord>();
    }
    ASSERT_CALL(env, napi_wrap(env, ctxt->self, udRecord, Destructor, nullptr, nullptr), udRecord);
    return ctxt->self;
}

std::shared_ptr<UnifiedRecord> UnifiedRecordNapi::GenerateNativeRecord(napi_env env, std::string type,
    napi_value valueNapi)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "UnifiedRecordNapi");
    ValueType value;
    GetNativeValue(env, type, valueNapi, value);

    UDType utdType = APPLICATION_DEFINED_RECORD;
    if (UtdUtils::IsValidUtdId(type)) {
        utdType = static_cast<UDType>(UtdUtils::GetUtdEnumFromUtdId(type));
    }

    std::map<UDType, std::function<std::shared_ptr<UnifiedRecord>(UDType, ValueType)>> constructors = {
        {TEXT, [](UDType type, ValueType value) { return std::make_shared<Text>(type, value); }},
        {PLAIN_TEXT, [](UDType type, ValueType value) { return std::make_shared<PlainText>(type, value); }},
        {HTML, [](UDType type, ValueType value) { return std::make_shared<Html>(type, value); }},
        {HYPERLINK, [](UDType type, ValueType value) { return std::make_shared<Link>(type, value); }},
        {FILE, [](UDType type, ValueType value) { return std::make_shared<File>(type, value); }},
        {IMAGE, [](UDType type, ValueType value) { return std::make_shared<Image>(type, value); }},
        {VIDEO, [](UDType type, ValueType value) { return std::make_shared<Video>(type, value); }},
        {AUDIO, [](UDType type, ValueType value) { return std::make_shared<Audio>(type, value); }},
        {FOLDER, [](UDType type, ValueType value) { return std::make_shared<Folder>(type, value); }},
        {SYSTEM_DEFINED_RECORD,
            [](UDType type, ValueType value) { return std::make_shared<SystemDefinedRecord>(type, value); }},
        {SYSTEM_DEFINED_APP_ITEM,
            [](UDType type, ValueType value) { return std::make_shared<SystemDefinedAppItem>(type, value); }},
        {SYSTEM_DEFINED_FORM,
            [](UDType type, ValueType value) { return std::make_shared<SystemDefinedForm>(type, value); }},
        {SYSTEM_DEFINED_PIXEL_MAP,
            [](UDType type, ValueType value) { return std::make_shared<SystemDefinedPixelMap>(type, value); }},
        {APPLICATION_DEFINED_RECORD,
            [](UDType type, ValueType value) { return std::make_shared<ApplicationDefinedRecord>(type, value); }},
    };

    auto constructor = constructors.find(utdType);
    if (constructor == constructors.end()) {
        return std::make_shared<UnifiedRecord>(utdType, value);
    }
    auto uRecord = constructor->second(utdType, value);
    if (utdType == APPLICATION_DEFINED_RECORD) {
        std::shared_ptr<ApplicationDefinedRecord> applicationDefinedRecord =
            std::static_pointer_cast<ApplicationDefinedRecord>(uRecord);
        applicationDefinedRecord->SetApplicationDefinedType(type);
    }
    return uRecord;
}

void UnifiedRecordNapi::GetNativeValue(napi_env env, std::string type, napi_value valueNapi, ValueType &value)
{
    bool isArrayBuffer = false;
    NAPI_CALL_RETURN_VOID(env, napi_is_arraybuffer(env, valueNapi, &isArrayBuffer));
    if (isArrayBuffer) {
        void *data = nullptr;
        size_t dataLen = 0;
        NAPI_CALL_RETURN_VOID(env, napi_get_arraybuffer_info(env, valueNapi, &data, &dataLen));
        value = std::vector<uint8_t>(reinterpret_cast<uint8_t *>(data), reinterpret_cast<uint8_t *>(data) + dataLen);
        return;
    }

    napi_status status;
    napi_valuetype valueType = napi_undefined;
    status = napi_typeof(env, valueNapi, &valueType);
    ASSERT_ERR_VOID(env, status == napi_ok,
        Status::E_INVALID_PARAMETERS, "Parameter error: parameter value type must be ValueType");
    if (valueType == napi_object) {
        if (type == "openharmony.pixel-map") {
            value = std::shared_ptr<OHOS::Media::PixelMap>(nullptr);
        } else if (type == "openharmony.want") {
            value = std::shared_ptr<OHOS::AAFwk::Want>(nullptr);
        } else {
            value = std::make_shared<Object>();
        }
    } else if (valueType == napi_string) {
        value = std::string();
    } else if (valueType == napi_number) {
        value = double();
    } else if (valueType == napi_boolean) {
        value = bool();
    } else if (valueType == napi_undefined) {
        value = std::monostate();
    } else if (valueType == napi_null) {
        value = nullptr;
    }
    std::visit([&](auto &value) { status = NapiDataUtils::GetValue(env, valueNapi, value); }, value);
    ASSERT_ERR_VOID(env, status == napi_ok, Status::E_ERROR, "get unifiedRecord failed");
}

void UnifiedRecordNapi::NewInstance(napi_env env, std::shared_ptr<UnifiedRecord> in, napi_value &out)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "UnifiedRecordNapi");
    ASSERT_CALL_VOID(env, napi_new_instance(env, Constructor(env), 0, nullptr, &out));
    auto *record = new (std::nothrow) UnifiedRecordNapi();
    ASSERT_ERR_VOID(env, record != nullptr, Status::E_ERROR, "no memory for unified record");
    record->value_ = in;
    ASSERT_CALL_DELETE(env, napi_wrap(env, out, record, Destructor, nullptr, nullptr), record);
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
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_ERROR, ctxt->error);
    return static_cast<UnifiedRecordNapi *>(ctxt->native);
}

napi_value UnifiedRecordNapi::GetType(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "UnifiedRecordNapi");
    auto ctxt = std::make_shared<ContextBase>();
    auto uRecord = GetUnifiedRecord(env, info, ctxt);
    ASSERT_ERR(ctxt->env, (uRecord != nullptr && uRecord->value_ != nullptr), Status::E_ERROR, "invalid object!");
    ctxt->status = NapiDataUtils::SetValue(env, UtdUtils::GetUtdIdFromUtdEnum(uRecord->value_->GetType()),
                                           ctxt->output);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_ERROR, "set type failed!");
    return ctxt->output;
}

napi_value UnifiedRecordNapi::GetValue(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "UnifiedRecordNapi");
    auto ctxt = std::make_shared<ContextBase>();
    auto uRecord = GetUnifiedRecord(env, info, ctxt);
    ASSERT_ERR(ctxt->env, (uRecord != nullptr && uRecord->value_ != nullptr), Status::E_ERROR, "invalid object!");
    if (std::holds_alternative<std::vector<uint8_t>>(uRecord->value_->GetValue())) {
        auto value = std::get<std::vector<uint8_t>>(uRecord->value_->GetValue());
        void *data = nullptr;
        size_t len = value.size();
        NAPI_CALL(env, napi_create_arraybuffer(env, len, &data, &ctxt->output));
        if (memcpy_s(data, len, reinterpret_cast<const void *>(value.data()), len) != 0) {
            LOG_ERROR(UDMF_KITS_NAPI, "memcpy_s failed");
            return nullptr;
        }
    } else {
        std::visit([&](const auto &value) { NapiDataUtils::SetValue(env, value, ctxt->output); },
            uRecord->value_->GetValue());
    }
    return ctxt->output;
}
} // namespace UDMF
} // namespace OHOS