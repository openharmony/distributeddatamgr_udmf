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
napi_value UnifiedDataNapi::Constructor(napi_env env)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "UnifiedDataNapi");
    napi_property_descriptor properties[] = {
        /* UnifiedData properties */
        DECLARE_NAPI_FUNCTION("addRecord", AddRecord),
        DECLARE_NAPI_FUNCTION("getRecords", GetRecords),
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
} // namespace UDMF
} // namespace OHOS