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
#define LOG_TAG "UnifiedDataNapi"
#include "unified_data_napi.h"
#include "application_defined_record_napi.h"
#include "audio_napi.h"
#include "file_napi.h"
#include "folder_napi.h"
#include "html_napi.h"
#include "image_napi.h"
#include "link_napi.h"
#include "napi_data_utils.h"
#include "napi_error_utils.h"
#include "plain_text_napi.h"
#include "system_defined_appitem_napi.h"
#include "system_defined_form_napi.h"
#include "system_defined_pixelmap_napi.h"
#include "system_defined_record_napi.h"
#include "text_napi.h"
#include "unified_data.h"
#include "unified_record_napi.h"
#include "video_napi.h"

namespace OHOS {
namespace UDMF {
napi_value UnifiedDataPropertiesNapi::Constructor(napi_env env)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "UnifiedDataPropertiesNapi");
    napi_property_descriptor properties[] = {
        DECLARE_NAPI_GETTER_SETTER("extras", GetExtras, SetExtras),
        DECLARE_NAPI_GETTER_SETTER("tag", GetTag, SetTag),
        DECLARE_NAPI_GETTER_SETTER("shareOption", GetShareOption, SetShareOption),
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

UnifiedDataPropertiesNapi* UnifiedDataPropertiesNapi::GetPropertiesNapi(napi_env env, napi_callback_info info, std::shared_ptr<ContextBase> ctxt)
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
    ASSERT_ERR(
        ctxt->env, (properties != nullptr && properties->value_ != nullptr), Status::E_INVALID_PARAMETERS, "invalid object!");
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
        LOG_INFO(UDMF_KITS_NAPI, "extras ret = %{public}d", ret);
    };
    ctxt->GetCbInfoSync(env, info, input);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_INVALID_PARAMETERS, "invalid arguments!");
    auto properties = static_cast<UnifiedDataPropertiesNapi*>(ctxt->native);
    ASSERT_ERR(
        ctxt->env, (properties != nullptr && properties->value_ != nullptr), Status::E_INVALID_PARAMETERS, "invalid object!");
    properties->value_->extras = value;
    return nullptr;
}

napi_value UnifiedDataPropertiesNapi::GetTag(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "UnifiedDataPropertiesNapi");
    auto ctxt = std::make_shared<ContextBase>();
    auto properties = GetPropertiesNapi(env, info, ctxt);
    ASSERT_ERR(
        ctxt->env, (properties != nullptr && properties->value_ != nullptr), Status::E_INVALID_PARAMETERS, "invalid object!");
    ctxt->status = NapiDataUtils::SetValue(env, properties->value_->tag, ctxt->output);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_INVALID_PARAMETERS, "set properties tag failed!");
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
    ASSERT_ERR(
        ctxt->env, (properties != nullptr && properties->value_ != nullptr), Status::E_INVALID_PARAMETERS, "invalid object!");
    properties->value_->tag = tag;
    return nullptr;
}

napi_value UnifiedDataPropertiesNapi::GetShareOption(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "UnifiedDataPropertiesNapi");
    auto ctxt = std::make_shared<ContextBase>();
    auto properties = GetPropertiesNapi(env, info, ctxt);
    ASSERT_ERR(
        ctxt->env, (properties != nullptr && properties->value_ != nullptr), Status::E_INVALID_PARAMETERS, "invalid object!");
    ctxt->status = NapiDataUtils::SetValue(env, properties->value_->shareOption, ctxt->output);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_INVALID_PARAMETERS, "set properties shareOption failed!");
    return ctxt->output;
}

napi_value UnifiedDataPropertiesNapi::SetShareOption(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "UnifiedDataPropertiesNapi");
    auto ctxt = std::make_shared<ContextBase>();
    int32_t shareOptionValue = ShareOption::IN_APP;
    auto input = [env, ctxt, &shareOptionValue](size_t argc, napi_value *argv) {
        ASSERT_BUSINESS_ERR(ctxt, argc >= 1, Status::E_INVALID_PARAMETERS, "invalid arguments!");
        ctxt->status = NapiDataUtils::GetValue(env, argv[0], shareOptionValue);
        ASSERT_BUSINESS_ERR(ctxt, ctxt->status == napi_ok, Status::E_INVALID_PARAMETERS, "invalid arguments!");
    };
    ctxt->GetCbInfoSync(env, info, input);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_INVALID_PARAMETERS, "invalid arguments!");
    auto properties = static_cast<UnifiedDataPropertiesNapi *>(ctxt->native);
    ASSERT_ERR(
        ctxt->env, (properties != nullptr && properties->value_ != nullptr), Status::E_INVALID_PARAMETERS, "invalid object!");
    properties->value_->shareOption = static_cast<ShareOption>(shareOptionValue);
    return nullptr;
}

napi_value UnifiedDataPropertiesNapi::GetTimestamp(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "UnifiedDataPropertiesNapi");
    auto ctxt = std::make_shared<ContextBase>();
    auto properties = GetPropertiesNapi(env, info, ctxt);
    ASSERT_ERR(
        ctxt->env, (properties != nullptr && properties->value_ != nullptr), Status::E_INVALID_PARAMETERS, "invalid object!");
    ctxt->status = napi_create_date(env, properties->value_->timestamp, &ctxt->output);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_INVALID_PARAMETERS, "set properties timestamp failed!");
    return ctxt->output;
}

napi_value UnifiedDataPropertiesNapi::SetTimestamp(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "UnifiedDataPropertiesNapi");
    auto ctxt = std::make_shared<ContextBase>();
    double timestampValue;
    auto input = [env, ctxt, &timestampValue](size_t argc, napi_value *argv) {
        ASSERT_BUSINESS_ERR(ctxt, argc >= 1, Status::E_INVALID_PARAMETERS, "invalid arguments!");
        ctxt->status = napi_get_date_value(env, argv[0], &timestampValue);
        ASSERT_BUSINESS_ERR(ctxt, ctxt->status == napi_ok, Status::E_INVALID_PARAMETERS, "invalid arguments!");
    };
    ctxt->GetCbInfoSync(env, info, input);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_INVALID_PARAMETERS, "invalid arguments!");
    auto properties = static_cast<UnifiedDataPropertiesNapi *>(ctxt->native);
    ASSERT_ERR(
        ctxt->env, (properties != nullptr && properties->value_ != nullptr), Status::E_INVALID_PARAMETERS, "invalid object!");
    properties->value_->timestamp = timestampValue;
    return nullptr;
}

napi_value UnifiedDataPropertiesNapi::GetDelayData(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "UnifiedDataPropertiesNapi");
    auto ctxt = std::make_shared<ContextBase>();
    auto properties = GetPropertiesNapi(env, info, ctxt);
    ASSERT_ERR(
        ctxt->env, (properties != nullptr && properties->value_ != nullptr), Status::E_INVALID_PARAMETERS, "invalid object!");
    if (properties->delayDataRef_ == nullptr) {
        LOG_INFO(UDMF_KITS_NAPI, "get GetDelayData undefined");
        napi_value undefinedValue;
        napi_get_undefined(env, &undefinedValue);
        return undefinedValue;
    }
    ctxt->status = napi_get_reference_value(env, properties->delayDataRef_, &ctxt->output);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_INVALID_PARAMETERS, "set properties getDelayData failed!");
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
        napi_typeof(env, argv[0], &valueType);
        ASSERT_BUSINESS_ERR(ctxt, valueType == napi_function, Status::E_INVALID_PARAMETERS, "callback is not a function");
        handler = argv[0];
    };
    ctxt->GetCbInfoSync(env, info, input);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_INVALID_PARAMETERS, "invalid arguments!");
    auto properties = static_cast<UnifiedDataPropertiesNapi *>(ctxt->native);
    ASSERT_ERR(
        ctxt->env, (properties != nullptr && properties->value_ != nullptr), Status::E_INVALID_PARAMETERS, "invalid object!");
    ctxt->status = napi_create_reference(env, handler, 1, &ref);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_INVALID_PARAMETERS, "invalid arguments!");
    properties->delayDataRef_ = ref;
    return nullptr;
}

napi_value UnifiedDataNapi::Constructor(napi_env env)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "UnifiedDataNapi");
    napi_property_descriptor properties[] = {
        /* UnifiedData properties */
        DECLARE_NAPI_FUNCTION("addRecord", AddRecord),
        DECLARE_NAPI_FUNCTION("getRecords", GetRecords),
        DECLARE_NAPI_GETTER_SETTER("properties", GetProperties, SetProperties),
    };
    size_t count = sizeof(properties) / sizeof(properties[0]);
    return NapiDataUtils::DefineClass(env, "UnifiedData", properties, count, UnifiedDataNapi::New);
}

napi_value UnifiedDataNapi::New(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "UnifiedDataNapi");
    UnifiedRecordNapi *uRecord = nullptr;
    auto ctxt = std::make_shared<ContextBase>();
    auto input = [env, info, ctxt, &uRecord](size_t argc, napi_value *argv) {
        // required 1 arguments :: <UnifiedRecord*>
        ASSERT_BUSINESS_ERR(ctxt, argc <= 1, Status::E_INVALID_PARAMETERS, "invalid arguments!");
        if (argc == 1) {
            ctxt->status = napi_unwrap(env, *argv, reinterpret_cast<void **>(&uRecord));
            ASSERT_BUSINESS_ERR(ctxt, (ctxt->status == napi_ok && uRecord != nullptr && uRecord->value_ != nullptr),
                Status::E_INVALID_PARAMETERS, "invalid object!");
            ctxt->status = UnifiedDataUtils::IsValidType(uRecord->value_->GetType()) ? napi_ok : napi_invalid_arg;
            ASSERT_BUSINESS_ERR(ctxt, ctxt->status == napi_ok, Status::E_INVALID_PARAMETERS, "invalid type!");
        }
    };

    // Parsing input parameters
    ctxt->GetCbInfoSync(env, info, input);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_INVALID_PARAMETERS, "invalid arguments!");
    auto *uData = new (std::nothrow) UnifiedDataNapi();
    ASSERT_ERR(ctxt->env, uData != nullptr, Status::E_ERROR, "no memory for unified data!");

    // Create and bind UnifiedDataPropertiesNapi
    int argc = 0;
    napi_value argv[0] = {};
    UnifiedDataPropertiesNapi* propertiesNapi = nullptr;
    uData->ref_ = NewWithRef(env, argc, argv, reinterpret_cast<void **>(&propertiesNapi), UnifiedDataPropertiesNapi::Constructor(env));

    uData->value_ = std::make_shared<UnifiedData>(propertiesNapi->value_);
    if (uRecord) {
        uData->value_->AddRecord(uRecord->value_);
    }
    ASSERT_CALL(env, napi_wrap(env, ctxt->self, uData, Destructor, nullptr, nullptr), uData);
    return ctxt->self;
}

void UnifiedDataNapi::Destructor(napi_env env, void *data, void *hint)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "UnifiedDataNapi finalize.");
    auto *uData = static_cast<UnifiedDataNapi *>(data);
    ASSERT_VOID(uData != nullptr, "finalize null!");
    delete uData;
}

napi_status UnifiedDataNapi::NewInstance(napi_env env, std::shared_ptr<UnifiedData> in, napi_value &out)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "UnifiedDataNapi");
    ASSERT_CALL_STATUS(env, napi_new_instance(env, Constructor(env), 0, nullptr, &out));
    auto *unifiedData = new (std::nothrow) UnifiedDataNapi();
    ASSERT_ERR_STATUS(env, unifiedData != nullptr, Status::E_ERROR, "no memory for unified data!");
    unifiedData->value_ = in;
    ASSERT_CALL_DELETE_STATUS(env, napi_wrap(env, out, unifiedData, Destructor, nullptr, nullptr), unifiedData);
    return napi_ok;
}

UnifiedDataNapi *UnifiedDataNapi::GetUnifiedData(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "UnifiedDataNapi");
    auto ctxt = std::make_shared<ContextBase>();
    ctxt->GetCbInfoSync(env, info);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_INVALID_PARAMETERS, "invalid arguments!");
    return static_cast<UnifiedDataNapi *>(ctxt->native);
}

napi_value UnifiedDataNapi::AddRecord(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "UnifiedDataNapi");
    UnifiedRecordNapi *uRecord = nullptr;
    auto ctxt = std::make_shared<ContextBase>();
    auto input = [env, info, ctxt, &uRecord](size_t argc, napi_value *argv) {
        ASSERT_BUSINESS_ERR(ctxt, argc >= 1, Status::E_INVALID_PARAMETERS, "invalid arguments!");
        ctxt->status = napi_unwrap(env, *argv, reinterpret_cast<void **>(&uRecord));
        ASSERT_BUSINESS_ERR(ctxt, (ctxt->status == napi_ok && uRecord != nullptr && uRecord->value_ != nullptr),
            Status::E_INVALID_PARAMETERS, "invalid object!");
        ctxt->status = UnifiedDataUtils::IsValidType(uRecord->value_->GetType()) ? napi_ok : napi_invalid_arg;
        ASSERT_BUSINESS_ERR(ctxt, ctxt->status == napi_ok, Status::E_INVALID_PARAMETERS, "invalid type!");
    };
    ctxt->GetCbInfoSync(env, info, input);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_INVALID_PARAMETERS, "invalid arguments!");
    auto *uData = static_cast<UnifiedDataNapi *>(ctxt->native);
    ASSERT_ERR(
        ctxt->env, (uData != nullptr && uData->value_ != nullptr), Status::E_INVALID_PARAMETERS, "invalid object!");
    uData->value_->AddRecord(uRecord->value_);
    return nullptr;
}

napi_value UnifiedDataNapi::GetRecords(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "UnifiedDataNapi");
    auto ctxt = std::make_shared<ContextBase>();
    auto uData = GetUnifiedData(env, info);
    ASSERT_ERR(
        ctxt->env, (uData != nullptr && uData->value_ != nullptr), Status::E_INVALID_PARAMETERS, "invalid object!");
    std::vector<std::shared_ptr<UnifiedRecord>> records = uData->value_->GetRecords();
    napi_status status = napi_create_array_with_length(env, records.size(), &ctxt->output);
    ASSERT_ERR(ctxt->env, status == napi_ok, Status::E_ERROR, "init array failed!");
    int index = 0;
    for (const std::shared_ptr<UnifiedRecord> &recordPtr : records) {
        napi_value recordNapi = nullptr;
        GetRecord(env, recordPtr, recordNapi);
        ctxt->status = napi_set_element(env, ctxt->output, index++, recordNapi);
        ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_ERROR, "set element failed!");
    }
    return ctxt->output;
}

void UnifiedDataNapi::GetRecord(napi_env env, std::shared_ptr<UnifiedRecord> in, napi_value &out)
{
    switch (in->GetType()) {
        case TEXT: {
            TextNapi::NewInstance(env, in, out);
            break;
        }
        case PLAIN_TEXT: {
            PlainTextNapi::NewInstance(env, in, out);
            break;
        }
        case HTML: {
            HtmlNapi::NewInstance(env, in, out);
            break;
        }
        case HYPERLINK: {
            LinkNapi::NewInstance(env, in, out);
            break;
        }
        case FILE: {
            FileNapi::NewInstance(env, in, out);
            break;
        }
        case IMAGE: {
            ImageNapi::NewInstance(env, in, out);
            break;
        }
        case VIDEO: {
            VideoNapi::NewInstance(env, in, out);
            break;
        }
        case AUDIO: {
            AudioNapi::NewInstance(env, in, out);
            break;
        }
        case FOLDER: {
            FolderNapi::NewInstance(env, in, out);
            break;
        }
        case SYSTEM_DEFINED_RECORD: {
            SystemDefinedRecordNapi::NewInstance(env, in, out);
            break;
        }
        case SYSTEM_DEFINED_APP_ITEM: {
            SystemDefinedAppItemNapi::NewInstance(env, in, out);
            break;
        }
        case SYSTEM_DEFINED_FORM: {
            SystemDefinedFormNapi::NewInstance(env, in, out);
            break;
        }
        case SYSTEM_DEFINED_PIXEL_MAP: {
            SystemDefinedPixelMapNapi::NewInstance(env, in, out);
            break;
        }
        case APPLICATION_DEFINED_RECORD: {
            ApplicationDefinedRecordNapi::NewInstance(env, in, out);
            break;
        }
        default:
            LOG_INFO(UDMF_KITS_NAPI, "GetRecord default");
            break;
    }
}

napi_value UnifiedDataNapi::HasType(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "UnifiedDataNapi");
    std::string type;
    auto ctxt = std::make_shared<ContextBase>();
    auto input = [env, info, ctxt, &type](size_t argc, napi_value *argv) {
        ASSERT_BUSINESS_ERR(ctxt, argc >= 1, Status::E_INVALID_PARAMETERS, "invalid arguments!");
        ctxt->status = NapiDataUtils::GetValue(env, argv[0], type);
        ASSERT_BUSINESS_ERR(ctxt, ctxt->status == napi_ok, Status::E_INVALID_PARAMETERS, "invalid arguments!");
    };
    ctxt->GetCbInfoSync(env, info, input);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_INVALID_PARAMETERS, "invalid arguments!");
    auto *uData = static_cast<UnifiedDataNapi *>(ctxt->native);
    ASSERT_ERR(
        ctxt->env, (uData != nullptr && uData->value_ != nullptr), Status::E_INVALID_PARAMETERS, "invalid object!");
    bool ret = uData->value_->HasType(type);
    napi_value result = nullptr;
    napi_get_boolean(env, ret, &result);
    return result;
}

napi_value UnifiedDataNapi::GetTypes(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "UnifiedDataNapi");
    auto uData = GetUnifiedData(env, info);
    ASSERT_ERR(env, (uData != nullptr && uData->value_ != nullptr), Status::E_INVALID_PARAMETERS, "invalid object!");

    std::vector<std::string> Types = uData->value_->GetTypesLabels();
    napi_value nTypes = nullptr;
    napi_status status = napi_create_array(env, &nTypes);
    ASSERT_ERR(env, status == napi_ok, Status::E_ERROR, "create array fail!");

    size_t index = 0;
    napi_value value = nullptr;
    for (auto type : Types) {
        napi_create_string_utf8(env, type.c_str(), NAPI_AUTO_LENGTH, &value);
        napi_set_element(env, nTypes, index, value);
        index++;
    }
    return nTypes;
}

napi_value UnifiedDataNapi::GetProperties(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "UnifiedDataNapi");
    napi_value value;
    auto uData = GetUnifiedData(env, info);
    ASSERT_ERR(env, (uData != nullptr && uData->value_ != nullptr), Status::E_INVALID_PARAMETERS, "invalid object!");
    NAPI_CALL(env, napi_get_reference_value(env, uData->ref_, &value));
    return value;
}

UnifiedDataPropertiesNapi* UnifiedDataNapi::GetPropertiesNapi(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "UnifiedDataNapi");
    napi_value value;
    auto uData = GetUnifiedData(env, info);
    ASSERT_ERR(env, (uData != nullptr && uData->value_ != nullptr), Status::E_INVALID_PARAMETERS, "invalid object!");
    NAPI_CALL(env, napi_get_reference_value(env, uData->ref_, &value));

    void** out = nullptr;
    napi_status status = napi_unwrap(env, value, out);
    ASSERT_ERR(env, status == napi_ok && out != nullptr, Status::E_ERROR, "napi_unwrap failed");
    return static_cast<UnifiedDataPropertiesNapi*>(*out);
}

napi_value UnifiedDataNapi::SetProperties(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "UnifiedDataNapi");
    auto ctxt = std::make_shared<ContextBase>();
    auto input = [env, ctxt](size_t argc, napi_value* argv) {
        ASSERT_BUSINESS_ERR(ctxt, argc >= 1, Status::E_INVALID_PARAMETERS, "invalid arguments!");
        UnifiedDataPropertiesNapi* propertiesNapi = nullptr;
        ctxt->status = Unwrap(env, argv[0], reinterpret_cast<void**>(&propertiesNapi), UnifiedDataPropertiesNapi::Constructor(env));
        ASSERT_BUSINESS_ERR(ctxt, propertiesNapi != nullptr, Status::E_INVALID_PARAMETERS, "invalid arguments!");

        auto uData = static_cast<UnifiedDataNapi*>(ctxt->native);
        if (uData->ref_ != nullptr) {
            napi_delete_reference(env, uData->ref_);
        }
        ctxt->status = napi_create_reference(env, argv[0], 1, &uData->ref_);
        ASSERT_BUSINESS_ERR(ctxt, ctxt->status == napi_ok, Status::E_INVALID_PARAMETERS, "napi_create_reference to properties failed!");
        uData->value_->SetProperties(propertiesNapi->value_);
    };
    ctxt->GetCbInfoSync(env, info, input);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_INVALID_PARAMETERS, "invalid arguments!");
    return ctxt->self;
}

napi_ref UnifiedDataNapi::NewWithRef(napi_env env, size_t argc, napi_value* argv, void** out, napi_value constructor)
{
    napi_value object = nullptr;
    napi_status status = napi_new_instance(env, constructor, argc, argv, &object);
    ASSERT_ERR(env, status == napi_ok && object != nullptr, Status::E_ERROR, "napi_new_instance failed");

    status = napi_unwrap(env, object, out);
    ASSERT_ERR(env, status == napi_ok && out != nullptr, Status::E_ERROR, "napi_unwrap failed");

    napi_ref ref = nullptr;
    status = napi_create_reference(env, object, 1, &ref);
    ASSERT_ERR(env, status == napi_ok && ref != nullptr, Status::E_ERROR, "napi_create_reference failed");
    return ref;
}

napi_status UnifiedDataNapi::Unwrap(napi_env env, napi_value in, void** out, napi_value constructor)
{
    if (constructor != nullptr) {
        bool isInstance = false;
        napi_instanceof(env, in, constructor, &isInstance);
        if (!isInstance) {
            LOG_ERROR(UDMF_KITS_NAPI, "not a instance of *");
            return napi_invalid_arg;
        }
    }
    return napi_unwrap(env, in, out);
}
} // namespace UDMF
} // namespace OHOS