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
#define LOG_TAG "VideoNapi"
#include "video_napi.h"

#include "file_napi.h"
#include "napi_data_utils.h"
#include "napi_error_utils.h"
#include "napi_queue.h"
#include "unified_record_napi.h"
#include "video.h"

namespace OHOS {
namespace UDMF {
napi_value VideoNapi::Constructor(napi_env env)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "VideoNapi");
    napi_property_descriptor properties[] = {
        /* Video extends UnifiedRecord */
        DECLARE_NAPI_FUNCTION("getType", UnifiedRecordNapi::GetType),
        DECLARE_NAPI_FUNCTION("getValue", UnifiedRecordNapi::GetValue),
        /* Video extends File */
        DECLARE_NAPI_GETTER_SETTER("details", FileNapi::GetDetails, FileNapi::SetDetails),
        DECLARE_NAPI_GETTER_SETTER("uri", FileNapi::GetUri, FileNapi::SetUri),
        /* Video properties */
        DECLARE_NAPI_GETTER_SETTER("videoUri", GetVideoUri, SetVideoUri),
    };
    size_t count = sizeof(properties) / sizeof(properties[0]);
    return NapiDataUtils::DefineClass(env, "Video", properties, count, VideoNapi::New);
}

napi_value VideoNapi::New(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "VideoNapi");
    auto ctxt = std::make_shared<ContextBase>();
    ctxt->GetCbInfoSync(env, info);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_ERROR, ctxt->error);

    auto *video = new (std::nothrow) VideoNapi();
    ASSERT_ERR(ctxt->env, video != nullptr, Status::E_ERROR, "no memory for video!");
    video->value_ = std::make_shared<Video>();
    ASSERT_CALL(env, napi_wrap(env, ctxt->self, video, Destructor, nullptr, nullptr), video);
    return ctxt->self;
}

void VideoNapi::NewInstance(napi_env env, std::shared_ptr<UnifiedRecord> in, napi_value &out)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "VideoNapi");
    ASSERT_CALL_VOID(env, napi_new_instance(env, Constructor(env), 0, nullptr, &out));
    auto *video = new (std::nothrow) VideoNapi();
    ASSERT_ERR_VOID(env, video != nullptr, Status::E_ERROR, "no memory for video!");
    video->value_ = std::static_pointer_cast<Video>(in);
    ASSERT_CALL_DELETE(env, napi_wrap(env, out, video, Destructor, nullptr, nullptr), video);
}

void VideoNapi::Destructor(napi_env env, void *data, void *hint)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "VideoNapi finalize.");
    auto *video = static_cast<VideoNapi *>(data);
    ASSERT_VOID(video != nullptr, "finalize null!");
    delete video;
}

VideoNapi *VideoNapi::GetVideo(napi_env env, napi_callback_info info, std::shared_ptr<ContextBase> ctxt)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "VideoNapi");
    ctxt->GetCbInfoSync(env, info);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_ERROR, ctxt->error);
    return static_cast<VideoNapi *>(ctxt->native);
}

napi_value VideoNapi::GetVideoUri(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "VideoNapi");
    auto ctxt = std::make_shared<ContextBase>();
    auto video = GetVideo(env, info, ctxt);
    ASSERT_ERR(
        ctxt->env, (video != nullptr && video->value_ != nullptr), Status::E_ERROR, "invalid object!");
    ctxt->status = NapiDataUtils::SetValue(env, video->value_->GetUri(), ctxt->output);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_ERROR, "set video uri failed!");
    return ctxt->output;
}

napi_value VideoNapi::SetVideoUri(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "VideoNapi");
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
    auto video = static_cast<VideoNapi *>(ctxt->native);
    ASSERT_ERR(
        ctxt->env, (video != nullptr && video->value_ != nullptr), Status::E_ERROR, "invalid object!");
    video->value_->SetUri(uri);
    return nullptr;
}
} // namespace UDMF
} // namespace OHOS