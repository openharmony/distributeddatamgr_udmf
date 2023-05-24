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

#include "audio_napi.h"

#include "audio.h"
#include "file_napi.h"
#include "napi_data_utils.h"
#include "napi_error_utils.h"
#include "napi_queue.h"
#include "unified_record_napi.h"

namespace OHOS {
namespace UDMF {
napi_value AudioNapi::Constructor(napi_env env)
{
    napi_property_descriptor properties[] = {
        /* Audio extends UnifiedRecord */
        DECLARE_NAPI_FUNCTION("getType", UnifiedRecordNapi::GetType),
        /* Audio extends File */
        DECLARE_NAPI_GETTER_SETTER("details", FileNapi::GetDetails, FileNapi::SetDetails),
        DECLARE_NAPI_GETTER_SETTER("audioUri", FileNapi::GetUri, FileNapi::SetUri),
    };
    size_t count = sizeof(properties) / sizeof(properties[0]);
    return NapiDataUtils::DefineClass(env, "Audio", properties, count, AudioNapi::New);
}

napi_value AudioNapi::New(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "AudioNapi::New");
    auto ctxt = std::make_shared<ContextBase>();
    ctxt->GetCbInfoSync(env, info);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_INVALID_PARAMETERS, "invalid arguments!");

    auto *audio = new (std::nothrow) AudioNapi();
    ASSERT_ERR(ctxt->env, audio != nullptr, Status::E_FORBIDDEN, "no memory for audio!");
    audio->value_ = std::make_shared<Audio>();
    ASSERT_CALL(env, napi_wrap(env, ctxt->self, audio, Destructor, nullptr, nullptr), audio);
    return ctxt->self;
}

void AudioNapi::NewInstance(napi_env env, std::shared_ptr<UnifiedRecord> in, napi_value &out)
{
    ASSERT_CALL_VOID(env, napi_new_instance(env, Constructor(env), 0, nullptr, &out));
    auto *audio = new (std::nothrow) AudioNapi();
    ASSERT_ERR_VOID(env, audio != nullptr, Status::E_FORBIDDEN, "no memory for audio!");
    audio->value_ = std::reinterpret_pointer_cast<Audio>(in);
    ASSERT_CALL_DELETE(env, napi_wrap(env, out, audio, Destructor, nullptr, nullptr), audio);
}

void AudioNapi::Destructor(napi_env env, void *data, void *hint)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "Audio finalize.");
    auto *audio = static_cast<AudioNapi *>(data);
    ASSERT_VOID(audio != nullptr, "finalize null!");
    delete audio;
}
} // namespace UDMF
} // namespace OHOS