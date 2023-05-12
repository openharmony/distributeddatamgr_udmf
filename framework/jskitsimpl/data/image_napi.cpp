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

#include "image_napi.h"

#include "logger.h"
#include "image.h"
#include "napi_data_utils.h"
#include "napi_error_utils.h"
#include "napi_queue.h"
#include "unified_record_napi.h"
#include "file_napi.h"

namespace OHOS {
namespace UDMF {
napi_value ImageNapi::Constructor(napi_env env)
{
    napi_property_descriptor properties[] = {
        /* Image extends UnifiedRecord */
        DECLARE_NAPI_FUNCTION("getType", UnifiedRecordNapi::GetType),
        /* Image extends File */
        DECLARE_NAPI_GETTER_SETTER("details", FileNapi::GetDetails, FileNapi::SetDetails),
        DECLARE_NAPI_GETTER_SETTER("imageUri", FileNapi::GetUri, FileNapi::SetUri),
    };
    size_t count = sizeof(properties) / sizeof(properties[0]);
    return NapiDataUtils::DefineClass(env, "Image", properties, count, ImageNapi::New);
}

napi_value ImageNapi::New(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "ImageNapi::New");
    auto ctxt = std::make_shared<ContextBase>();
    ctxt->GetCbInfoSync(env, info);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_INVALID_PARAMETERS, "invalid arguments!");

    auto *image = new (std::nothrow) ImageNapi();
    ASSERT_ERR(ctxt->env, image != nullptr, Status::E_FORBIDDEN, "no memory for image!");
    image->value_ = std::make_shared<Image>();
    ASSERT_CALL(env, napi_wrap(env, ctxt->self, image, Destructor, nullptr, nullptr), image);
    return ctxt->self;
}

void ImageNapi::NewInstance(napi_env env, std::shared_ptr<UnifiedRecord> in, napi_value &out)
{
    ASSERT_CALL_VOID(env, napi_new_instance(env, Constructor(env), 0, nullptr, &out));
    auto *image = new (std::nothrow) ImageNapi();
    ASSERT_ERR_VOID(env, image != nullptr, Status::E_FORBIDDEN, "no memory for image!");
    image->value_ = std::reinterpret_pointer_cast<Image>(in);
    ASSERT_CALL_DELETE(env, napi_wrap(env, out, image, Destructor, nullptr, nullptr), image);
}

void ImageNapi::Destructor(napi_env env, void *data, void *hint)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "Image finalize.");
    auto *image = static_cast<ImageNapi *>(data);
    ASSERT_VOID(image != nullptr, "finalize null!");
    delete image;
}
} // namespace UDMF
} // namespace OHOS