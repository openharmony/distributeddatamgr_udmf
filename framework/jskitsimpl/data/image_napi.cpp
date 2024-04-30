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
#define LOG_TAG "ImageNapi"
#include "image_napi.h"

#include "file_napi.h"
#include "image.h"
#include "napi_data_utils.h"
#include "napi_error_utils.h"
#include "napi_queue.h"
#include "unified_record_napi.h"

namespace OHOS {
namespace UDMF {
napi_value ImageNapi::Constructor(napi_env env)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "ImageNapi");
    napi_property_descriptor properties[] = {
        /* Image extends UnifiedRecord */
        DECLARE_NAPI_FUNCTION("getType", UnifiedRecordNapi::GetType),
        DECLARE_NAPI_FUNCTION("getValue", UnifiedRecordNapi::GetValue),
        /* Image extends File */
        DECLARE_NAPI_GETTER_SETTER("details", FileNapi::GetDetails, FileNapi::SetDetails),
        DECLARE_NAPI_GETTER_SETTER("uri", FileNapi::GetUri, FileNapi::SetUri),
        /* Image properties */
        DECLARE_NAPI_GETTER_SETTER("imageUri", GetImageUri, SetImageUri),
    };
    size_t count = sizeof(properties) / sizeof(properties[0]);
    return NapiDataUtils::DefineClass(env, "Image", properties, count, ImageNapi::New);
}

napi_value ImageNapi::New(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "ImageNapi");
    auto ctxt = std::make_shared<ContextBase>();
    ctxt->GetCbInfoSync(env, info);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_ERROR, ctxt->error);

    auto *image = new (std::nothrow) ImageNapi();
    ASSERT_ERR(ctxt->env, image != nullptr, Status::E_ERROR, "no memory for image!");
    image->value_ = std::make_shared<Image>();
    ASSERT_CALL(env, napi_wrap(env, ctxt->self, image, Destructor, nullptr, nullptr), image);
    return ctxt->self;
}

void ImageNapi::NewInstance(napi_env env, std::shared_ptr<UnifiedRecord> in, napi_value &out)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "ImageNapi");
    ASSERT_CALL_VOID(env, napi_new_instance(env, Constructor(env), 0, nullptr, &out));
    auto *image = new (std::nothrow) ImageNapi();
    ASSERT_ERR_VOID(env, image != nullptr, Status::E_ERROR, "no memory for image!");
    image->value_ = std::static_pointer_cast<Image>(in);
    ASSERT_CALL_DELETE(env, napi_wrap(env, out, image, Destructor, nullptr, nullptr), image);
}

void ImageNapi::Destructor(napi_env env, void *data, void *hint)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "ImageNapi finalize.");
    auto *image = static_cast<ImageNapi *>(data);
    ASSERT_VOID(image != nullptr, "finalize null!");
    delete image;
}

ImageNapi *ImageNapi::GetImage(napi_env env, napi_callback_info info, std::shared_ptr<ContextBase> ctxt)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "ImageNapi");
    ctxt->GetCbInfoSync(env, info);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_ERROR, ctxt->error);
    return static_cast<ImageNapi *>(ctxt->native);
}

napi_value ImageNapi::GetImageUri(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "ImageNapi");
    auto ctxt = std::make_shared<ContextBase>();
    auto image = GetImage(env, info, ctxt);
    ASSERT_ERR(
        ctxt->env, (image != nullptr && image->value_ != nullptr), Status::E_ERROR, "invalid object!");
    ctxt->status = NapiDataUtils::SetValue(env, image->value_->GetUri(), ctxt->output);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_ERROR, "set image uri failed!");
    return ctxt->output;
}

napi_value ImageNapi::SetImageUri(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "ImageNapi");
    auto ctxt = std::make_shared<ContextBase>();
    std::string uri;
    auto input = [env, ctxt, &uri](size_t argc, napi_value *argv) {
        ASSERT_BUSINESS_ERR(ctxt, argc >= 1,
            Status::E_INVALID_PARAMETERS, "Parameter error: Mandatory parameters are left unspecified");
        ctxt->status = NapiDataUtils::GetValue(env, argv[0], uri);
        ASSERT_BUSINESS_ERR(ctxt, ctxt->status == napi_ok,
            Status::E_INVALID_PARAMETERS, "Parameter error: parameter imageUri type must be string");
    };
    ctxt->GetCbInfoSync(env, info, input);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_ERROR, ctxt->error);
    auto image = static_cast<ImageNapi *>(ctxt->native);
    ASSERT_ERR(
        ctxt->env, (image != nullptr && image->value_ != nullptr), Status::E_ERROR, "invalid object!");
    image->value_->SetUri(uri);
    return nullptr;
}
} // namespace UDMF
} // namespace OHOS