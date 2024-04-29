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
#define LOG_TAG "FileNapi"
#include "file_napi.h"

#include "file.h"
#include "napi_data_utils.h"
#include "napi_error_utils.h"
#include "napi_queue.h"
#include "unified_record_napi.h"

namespace OHOS {
namespace UDMF {
napi_value FileNapi::Constructor(napi_env env)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "FileNapi");
    napi_property_descriptor properties[] = {
        /* File extends UnifiedRecord */
        DECLARE_NAPI_FUNCTION("getType", UnifiedRecordNapi::GetType),
        DECLARE_NAPI_FUNCTION("getValue", UnifiedRecordNapi::GetValue),
        /* File properties */
        DECLARE_NAPI_GETTER_SETTER("details", GetDetails, SetDetails),
        DECLARE_NAPI_GETTER_SETTER("uri", GetUri, SetUri),
    };
    size_t count = sizeof(properties) / sizeof(properties[0]);
    return NapiDataUtils::DefineClass(env, "File", properties, count, FileNapi::New);
}

napi_value FileNapi::New(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "FileNapi");
    auto ctxt = std::make_shared<ContextBase>();
    ctxt->GetCbInfoSync(env, info);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_ERROR, ctxt->error);

    auto *file = new (std::nothrow) FileNapi();
    ASSERT_ERR(ctxt->env, file != nullptr, Status::E_ERROR, "no memory for file!");
    file->value_ = std::make_shared<File>();
    ASSERT_CALL(env, napi_wrap(env, ctxt->self, file, Destructor, nullptr, nullptr), file);
    return ctxt->self;
}

void FileNapi::NewInstance(napi_env env, std::shared_ptr<UnifiedRecord> in, napi_value &out)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "FileNapi");
    ASSERT_CALL_VOID(env, napi_new_instance(env, Constructor(env), 0, nullptr, &out));
    auto *file = new (std::nothrow) FileNapi();
    ASSERT_ERR_VOID(env, file != nullptr, Status::E_ERROR, "no memory for file!");
    file->value_ = std::static_pointer_cast<File>(in);
    ASSERT_CALL_DELETE(env, napi_wrap(env, out, file, Destructor, nullptr, nullptr), file);
}

void FileNapi::Destructor(napi_env env, void *data, void *hint)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "FileNapi finalize.");
    auto *file = static_cast<FileNapi *>(data);
    ASSERT_VOID(file != nullptr, "finalize null!");
    delete file;
}

FileNapi *FileNapi::GetFile(napi_env env, napi_callback_info info, std::shared_ptr<ContextBase> ctxt)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "FileNapi");
    ctxt->GetCbInfoSync(env, info);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_ERROR, ctxt->error);
    return static_cast<FileNapi *>(ctxt->native);
}

napi_value FileNapi::GetDetails(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "FileNapi");
    auto ctxt = std::make_shared<ContextBase>();
    auto file = GetFile(env, info, ctxt);
    ASSERT_ERR(
        ctxt->env, (file != nullptr && file->value_ != nullptr), Status::E_ERROR, "invalid object!");
    ctxt->status = NapiDataUtils::SetValue(env, file->value_->GetDetails(), ctxt->output);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_ERROR, "set details failed!");
    return ctxt->output;
}

napi_value FileNapi::SetDetails(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "FileNapi");
    auto ctxt = std::make_shared<ContextBase>();
    UDDetails details;
    auto input = [env, ctxt, &details](size_t argc, napi_value *argv) {
        ASSERT_BUSINESS_ERR(ctxt, argc >= 1,
            Status::E_INVALID_PARAMETERS, "Parameter error: Mandatory parameters are left unspecified");
        ctxt->status = NapiDataUtils::GetValue(env, argv[0], details);
        ASSERT_BUSINESS_ERR(ctxt, ctxt->status == napi_ok,
            Status::E_INVALID_PARAMETERS, "Parameter error: parameter details type must be Record<string, string>");
    };
    ctxt->GetCbInfoSync(env, info, input);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_ERROR, ctxt->error);
    auto file = static_cast<FileNapi *>(ctxt->native);
    ASSERT_ERR(
        ctxt->env, (file != nullptr && file->value_ != nullptr), Status::E_ERROR, "invalid object!");
    file->value_->SetDetails(details);
    return nullptr;
}

napi_value FileNapi::GetUri(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "FileNapi");
    auto ctxt = std::make_shared<ContextBase>();
    auto file = GetFile(env, info, ctxt);
    ASSERT_ERR(
        ctxt->env, (file != nullptr && file->value_ != nullptr), Status::E_ERROR, "invalid object!");
    ctxt->status = NapiDataUtils::SetValue(env, file->value_->GetUri(), ctxt->output);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_ERROR, "set uri failed!");
    return ctxt->output;
}

napi_value FileNapi::SetUri(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "FileNapi");
    auto ctxt = std::make_shared<ContextBase>();
    std::string uri;
    auto input = [env, ctxt, &uri](size_t argc, napi_value *argv) {
        ASSERT_BUSINESS_ERR(ctxt, argc >= 1,
            Status::E_INVALID_PARAMETERS, "Parameter error: Mandatory parameters are left unspecified");
        ctxt->status = NapiDataUtils::GetValue(env, argv[0], uri);
        ASSERT_BUSINESS_ERR(ctxt, ctxt->status == napi_ok,
            Status::E_INVALID_PARAMETERS, "Parameter error: parameter uri type must be string");
    };
    ctxt->GetCbInfoSync(env, info, input);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_ERROR, ctxt->error);
    auto file = static_cast<FileNapi *>(ctxt->native);
    ASSERT_ERR(
        ctxt->env, (file != nullptr && file->value_ != nullptr), Status::E_ERROR, "invalid object!");
    file->value_->SetUri(uri);
    return nullptr;
}
} // namespace UDMF
} // namespace OHOS