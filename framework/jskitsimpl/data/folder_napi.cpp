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
#define LOG_TAG "FolderNapi"
#include "folder_napi.h"

#include "file_napi.h"
#include "folder.h"
#include "napi_data_utils.h"
#include "napi_error_utils.h"
#include "napi_queue.h"
#include "unified_record_napi.h"

namespace OHOS {
namespace UDMF {
napi_value FolderNapi::Constructor(napi_env env)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "FolderNapi");
    napi_property_descriptor properties[] = {
        /* Folder extends UnifiedRecord */
        DECLARE_NAPI_FUNCTION("getType", UnifiedRecordNapi::GetType),
        DECLARE_NAPI_FUNCTION("getValue", UnifiedRecordNapi::GetValue),
        /* Folder extends File */
        DECLARE_NAPI_GETTER_SETTER("details", FileNapi::GetDetails, FileNapi::SetDetails),
        DECLARE_NAPI_GETTER_SETTER("uri", FileNapi::GetUri, FileNapi::SetUri),
        /* Folder properties */
        DECLARE_NAPI_GETTER_SETTER("folderUri", GetFolderUri, SetFolderUri),
    };
    size_t count = sizeof(properties) / sizeof(properties[0]);
    return NapiDataUtils::DefineClass(env, "Folder", properties, count, FolderNapi::New);
}

napi_value FolderNapi::New(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "FolderNapi");
    auto ctxt = std::make_shared<ContextBase>();
    ctxt->GetCbInfoSync(env, info);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_ERROR, ctxt->error);

    auto *folder = new (std::nothrow) FolderNapi();
    ASSERT_ERR(ctxt->env, folder != nullptr, Status::E_ERROR, "no memory for folder!");
    folder->value_ = std::make_shared<Folder>();
    ASSERT_CALL(env, napi_wrap(env, ctxt->self, folder, Destructor, nullptr, nullptr), folder);
    return ctxt->self;
}

void FolderNapi::NewInstance(napi_env env, std::shared_ptr<UnifiedRecord> in, napi_value &out)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "FolderNapi");
    ASSERT_CALL_VOID(env, napi_new_instance(env, Constructor(env), 0, nullptr, &out));
    auto *folder = new (std::nothrow) FolderNapi();
    ASSERT_ERR_VOID(env, folder != nullptr, Status::E_ERROR, "no memory for folder!");
    folder->value_ = std::static_pointer_cast<Folder>(in);
    ASSERT_CALL_DELETE(env, napi_wrap(env, out, folder, Destructor, nullptr, nullptr), folder);
}

void FolderNapi::Destructor(napi_env env, void *data, void *hint)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "FolderNapi finalize.");
    auto *folder = static_cast<FolderNapi *>(data);
    ASSERT_VOID(folder != nullptr, "finalize null!");
    delete folder;
}

FolderNapi *FolderNapi::GetFolder(napi_env env, napi_callback_info info, std::shared_ptr<ContextBase> ctxt)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "FolderNapi");
    ctxt->GetCbInfoSync(env, info);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_ERROR, ctxt->error);
    return static_cast<FolderNapi *>(ctxt->native);
}

napi_value FolderNapi::GetFolderUri(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "FolderNapi");
    auto ctxt = std::make_shared<ContextBase>();
    auto folder = GetFolder(env, info, ctxt);
    ASSERT_ERR(
        ctxt->env, (folder != nullptr && folder->value_ != nullptr), Status::E_ERROR, "invalid object!");
    ctxt->status = NapiDataUtils::SetValue(env, folder->value_->GetUri(), ctxt->output);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_ERROR, "set folder uri failed!");
    return ctxt->output;
}

napi_value FolderNapi::SetFolderUri(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "FolderNapi");
    auto ctxt = std::make_shared<ContextBase>();
    std::string uri;
    auto input = [env, ctxt, &uri](size_t argc, napi_value *argv) {
        ASSERT_BUSINESS_ERR(ctxt, argc >= 1,
            Status::E_INVALID_PARAMETERS, "Parameter error: Mandatory parameters are left unspecified");
        ctxt->status = NapiDataUtils::GetValue(env, argv[0], uri);
        ASSERT_BUSINESS_ERR(ctxt, ctxt->status == napi_ok,
            Status::E_INVALID_PARAMETERS, "Parameter error: parameter folderUri type must be string");
    };
    ctxt->GetCbInfoSync(env, info, input);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_ERROR, ctxt->error);
    auto folder = static_cast<FolderNapi *>(ctxt->native);
    ASSERT_ERR(
        ctxt->env, (folder != nullptr && folder->value_ != nullptr), Status::E_ERROR, "invalid object!");
    folder->value_->SetUri(uri);
    return nullptr;
}
} // namespace UDMF
} // namespace OHOS