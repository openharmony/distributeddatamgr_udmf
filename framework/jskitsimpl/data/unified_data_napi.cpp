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
#include "napi_queue.h"
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
    NAPI_ASSERT(env, ctxt->status == napi_ok, "invalid arguments!");

    UnifiedDataPropertiesNapi* properties = new (std::nothrow) UnifiedDataPropertiesNapi();
    NAPI_ASSERT(env, properties != nullptr, "no memory for schema");

    auto finalize = [](napi_env env, void* data, void* hint) {
        LOG_DEBUG(UDMF_KITS_NAPI, "properties finalize.");
        auto* properties = reinterpret_cast<UnifiedDataPropertiesNapi*>(data);
        // ASSERT_BUSINESS_ERR(ctxt, properties != nullptr, Status::E_INVALID_PARAMETERS, "properties is null!");
        delete properties;
    };
    properties->value_ = std::make_shared<UnifiedDataProperties>();
    ASSERT_CALL(env, napi_wrap(env, ctxt->self, properties, finalize, nullptr, nullptr), properties);
    return ctxt->self;
}

UnifiedDataPropertiesNapi* UnifiedDataPropertiesNapi::GetPropertiesNapi(napi_env env, napi_callback_info info)
{
    auto ctxt = std::make_shared<ContextBase>();
    ctxt->GetCbInfoSync(env, info);
    NAPI_ASSERT(env, ctxt->status == napi_ok, "invalid arguments!");
    return reinterpret_cast<UnifiedDataPropertiesNapi*>(ctxt->native);
}

napi_value UnifiedDataPropertiesNapi::GetExtras(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "GetExtras");
    auto ctxt = std::make_shared<ContextBase>();
    auto properties = GetPropertiesNapi(env, info);
    ctxt->output = OHOS::AppExecFwk::WrapWantParams(env, properties->value_->extras);
    return ctxt->output;
}

napi_value UnifiedDataPropertiesNapi::SetExtras(napi_env env, napi_callback_info info)
{
    auto ctxt = std::make_shared<ContextBase>();
    AAFwk::WantParams vv;
    auto input = [env, ctxt, &vv](size_t argc, napi_value* argv) {
        bool ret = OHOS::AppExecFwk::UnwrapWantParams(env, argv[0], vv);
        LOG_INFO(UDMF_KITS_NAPI, "extras ret = %{public}d", ret);
    };
    ctxt->GetCbInfoSync(env, info, input);
    NAPI_ASSERT(env, ctxt->status == napi_ok, "invalid arguments!");

    auto properties = reinterpret_cast<UnifiedDataPropertiesNapi*>(ctxt->native);
    properties->value_->extras = vv;
    return nullptr;
}

napi_value UnifiedDataPropertiesNapi::GetTag(napi_env env, napi_callback_info info)
{
    auto ctxt = std::make_shared<ContextBase>();
    auto properties = GetPropertiesNapi(env, info);
    // CHECK_RETURN(fieldNode != nullptr, "getFieldNode nullptr!", nullptr);
    NapiDataUtils::SetValue(env, properties->value_->tag, ctxt->output);
    return ctxt->output;
}

napi_value UnifiedDataPropertiesNapi::SetTag(napi_env env, napi_callback_info info)
{
    auto ctxt = std::make_shared<ContextBase>();
    std::string vv;
    auto input = [env, ctxt, &vv](size_t argc, napi_value* argv) {
        // required 1 arguments :: <defaultValue>
        // CHECK_ARGS_RETURN_VOID(ctxt, argc == 1, "invalid arguments!");
        ctxt->status = NapiDataUtils::GetValue(env, argv[0], vv);
        // CHECK_STATUS_RETURN_VOID(ctxt, "invalid arg[0], i.e. invalid defaultValue!");
    };
    ctxt->GetCbInfoSync(env, info, input);
    NAPI_ASSERT(env, ctxt->status == napi_ok, "invalid arguments!");

    auto properties = reinterpret_cast<UnifiedDataPropertiesNapi*>(ctxt->native);
    properties->value_->tag = vv;
    return nullptr;
}

napi_value UnifiedDataPropertiesNapi::GetShareOption(napi_env env, napi_callback_info info)
{
    auto ctxt = std::make_shared<ContextBase>();
    auto properties = GetPropertiesNapi(env, info);
    // CHECK_RETURN(fieldNode != nullptr, "getFieldNode nullptr!", nullptr);
    NapiDataUtils::SetValue(env, properties->value_->shareOption, ctxt->output);
    return ctxt->output;
}

napi_value UnifiedDataPropertiesNapi::SetShareOption(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "SetShareOption");
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
    auto ctxt = std::make_shared<ContextBase>();
    auto properties = GetPropertiesNapi(env, info);
    // CHECK_RETURN(fieldNode != nullptr, "getFieldNode nullptr!", nullptr);
    // NapiDataUtils::SetValue(env, properties->value_->timestamp, ctxt->output);
    napi_create_date(env, properties->value_->timestamp, &ctxt->output);
    return ctxt->output;
}

napi_value UnifiedDataPropertiesNapi::SetTimestamp(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "SetTimestamp");
    auto ctxt = std::make_shared<ContextBase>();
    double timestampValue = ShareOption::IN_APP;
    auto input = [env, ctxt, &timestampValue](size_t argc, napi_value *argv) {
        ASSERT_BUSINESS_ERR(ctxt, argc >= 1, Status::E_INVALID_PARAMETERS, "invalid arguments!");
        // ctxt->status = NapiDataUtils::GetValue(env, argv[0], shareOptionValue);
        napi_get_date_value(env, argv[0], &timestampValue);
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
    auto ctxt = std::make_shared<ContextBase>();
    auto properties = GetPropertiesNapi(env, info);
    // CHECK_RETURN(fieldNode != nullptr, "getFieldNode nullptr!", nullptr);
    napi_get_reference_value(env, properties->delayDataRef_, &ctxt->output);
    return ctxt->output;
}

napi_value UnifiedDataPropertiesNapi::SetDelayData(napi_env env, napi_callback_info info)
{
    auto ctxt = std::make_shared<ContextBase>();
    napi_value handler;
    napi_ref ref;
    auto input = [env, ctxt, &handler](size_t argc, napi_value* argv) {
        handler = argv[0];
    };
    ctxt->GetCbInfoSync(env, info, input);
    NAPI_ASSERT(env, ctxt->status == napi_ok, "invalid arguments!");

    auto properties = reinterpret_cast<UnifiedDataPropertiesNapi*>(ctxt->native);
    napi_create_reference(env, handler, 1, &ref);
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
    uData->value_ = std::make_shared<UnifiedData>();
    if (uRecord) {
        uData->value_->AddRecord(uRecord->value_);
    }
    ASSERT_CALL(env, napi_wrap(env, ctxt->self, uData, Destructor, nullptr, nullptr), uData);

    int argc = 0;
    napi_value argv[0] = {};
    uData->ref_ = NewWithRef(env, argc, argv,
        reinterpret_cast<void**>(&uData->propertiesNapi_), UnifiedDataPropertiesNapi::Constructor(env));
    uData->value_->SetProperties(uData->propertiesNapi_->value_);
    return ctxt->self;
}

void UnifiedDataNapi::Destructor(napi_env env, void *data, void *hint)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "UnifiedDataNapi finalize.");
    auto *uData = static_cast<UnifiedDataNapi *>(data);
    ASSERT_VOID(uData != nullptr, "finalize null!");
    delete uData;
}

void UnifiedDataNapi::NewInstance(napi_env env, std::shared_ptr<UnifiedData> in, napi_value &out)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "UnifiedDataNapi");
    ASSERT_CALL_VOID(env, napi_new_instance(env, Constructor(env), 0, nullptr, &out));
    auto *unifiedData = new (std::nothrow) UnifiedDataNapi();
    ASSERT_ERR_VOID(env, unifiedData != nullptr, Status::E_ERROR, "no memory for unified data!");
    unifiedData->value_ = in;
    ASSERT_CALL_DELETE(env, napi_wrap(env, out, unifiedData, Destructor, nullptr, nullptr), unifiedData);
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
    size_t argc = 1;
    napi_value argv[1] = { 0 };
    napi_value thisVar = nullptr;

    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, argv, &thisVar, NULL));
    // if ((!CheckExpression(env, argc > 0, JSErrorCode::INVALID_PARAMETERS,
    //     "Parameter error. Wrong number of arguments.")) ||
    //     (!CheckArgsType(env, argv[0], napi_string, "Parameter error. The type of mimeType must be string."))) {
    //     return nullptr;
    // }

    std::string type;
    if (!NapiDataUtils::GetValue(env, argv[0], type)) {
        // PASTEBOARD_HILOGE(PASTEBOARD_MODULE_JS_NAPI, "Failed to GetValue!");
        return nullptr;
    }

    UnifiedDataNapi *obj = nullptr;
    napi_status status = napi_unwrap(env, thisVar, reinterpret_cast<void **>(&obj));
    if ((status != napi_ok) || (obj == nullptr)) {
        // PASTEBOARD_HILOGE(PASTEBOARD_MODULE_JS_NAPI, "Get AddHtmlRecord object failed");
        return nullptr;
    }

    bool ret = obj->value_->HasType(type);
    napi_value result = nullptr;
    napi_get_boolean(env, ret, &result);
    return result;
}

napi_value UnifiedDataNapi::GetTypes(napi_env env, napi_callback_info info)
{
    size_t argc = 1;
    napi_value argv[1] = { 0 };
    napi_value thisVar = nullptr;

    NAPI_CALL(env, napi_get_cb_info(env, info, &argc, argv, &thisVar, NULL));
    NAPI_ASSERT(env, argc >= 0, "Wrong number of arguments");

    UnifiedDataNapi *obj = nullptr;
    napi_status status = napi_unwrap(env, thisVar, reinterpret_cast<void **>(&obj));
    if ((status != napi_ok) || (obj == nullptr)) {
        // PASTEBOARD_HILOGE(PASTEBOARD_MODULE_JS_NAPI, "Get GetProperty object failed");
        return nullptr;
    }
    std::vector<std::string> Types = obj->value_->GetTypesVector();
    if (Types.size() == 0) {
        return nullptr;
    }

    napi_value nTypes = nullptr;
    if (napi_create_array(env, &nTypes) != napi_ok) {
        return nullptr;
    }
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
    auto ctxt = std::make_shared<ContextBase>();
    auto unifiedData = GetUnifiedData(env, info);
    NAPI_ASSERT(env, unifiedData->ref_ != nullptr, "no root, please set first!");
    NAPI_CALL(env, napi_get_reference_value(env, unifiedData->ref_, &ctxt->output));
    return ctxt->output;
}

napi_value UnifiedDataNapi::SetProperties(napi_env env, napi_callback_info info)
{
    auto ctxt = std::make_shared<ContextBase>();
    auto input = [env, ctxt](size_t argc, napi_value* argv) {
        // required 2 arguments :: <root-node>
        // CHECK_ARGS_RETURN_VOID(ctxt, argc == 1, "invalid arguments!");
        UnifiedDataPropertiesNapi* node = nullptr;
        ctxt->status = Unwrap(env, argv[0], reinterpret_cast<void**>(&node), UnifiedDataPropertiesNapi::Constructor(env));
        // CHECK_STATUS_RETURN_VOID(ctxt, "napi_unwrap to FieldNode failed");
        // CHECK_ARGS_RETURN_VOID(ctxt, node != nullptr, "invalid arg[0], i.e. invalid node!");

        auto schema = reinterpret_cast<UnifiedDataNapi*>(ctxt->native);
        if (schema->ref_ != nullptr) {
            napi_delete_reference(env, schema->ref_);
        }
        ctxt->status = napi_create_reference(env, argv[0], 1, &schema->ref_);
        // CHECK_STATUS_RETURN_VOID(ctxt, "napi_create_reference to FieldNode failed");
        schema->propertiesNapi_ = node;
        schema->value_->SetProperties(schema->propertiesNapi_->value_);
    };
    ctxt->GetCbInfoSync(env, info, input);
    NAPI_ASSERT(env, ctxt->status == napi_ok, "invalid arguments!");
    return ctxt->self;
}

napi_ref UnifiedDataNapi::NewWithRef(napi_env env, size_t argc, napi_value* argv, void** out, napi_value constructor)
{
    napi_value object = nullptr;
    napi_status status = napi_new_instance(env, constructor, argc, argv, &object);
    // CHECK_RETURN(status == napi_ok, "napi_new_instance failed", nullptr);
    // CHECK_RETURN(object != nullptr, "napi_new_instance failed", nullptr);

    status = napi_unwrap(env, object, out);
    // CHECK_RETURN(status == napi_ok, "napi_unwrap failed", nullptr);
    // CHECK_RETURN(out != nullptr, "napi_unwrap failed", nullptr);

    napi_ref ref = nullptr;
    status = napi_create_reference(env, object, 1, &ref);
    // CHECK_RETURN(status == napi_ok, "napi_create_referenc!e failed", nullptr);
    // CHECK_RETURN(ref != nullptr, "napi_create_referenc!e failed", nullptr);
    return ref;
}

napi_status UnifiedDataNapi::Unwrap(napi_env env, napi_value in, void** out, napi_value constructor)
{
    if (constructor != nullptr) {
        bool isInstance = false;
        napi_instanceof(env, in, constructor, &isInstance);
        if (!isInstance) {
            // ZLOGE("not a instance of *");
            return napi_invalid_arg;
        }
    }
    return napi_unwrap(env, in, out);
}
} // namespace UDMF
} // namespace OHOS