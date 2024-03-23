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

#ifndef UDMF_TYPE_DESCRIPTOR_NAPI_H
#define UDMF_TYPE_DESCRIPTOR_NAPI_H

#include <memory>

#include "napi/native_api.h"
#include "napi_error_utils.h"
#include "napi_queue.h"
#include "type_descriptor.h"

namespace OHOS {
namespace UDMF {
class TypeDescriptorNapi {
public:
    static void NewInstance(napi_env env, std::shared_ptr<TypeDescriptor> in, napi_value &out);
    static napi_value BelongsTo(napi_env env, napi_callback_info info);
    static napi_value IsLowerLevelType(napi_env env, napi_callback_info info);
    static napi_value IsHigherLevelType(napi_env env, napi_callback_info info);
    static napi_value Equals(napi_env env, napi_callback_info info);
    static napi_value Constructor(napi_env env);

    std::shared_ptr<TypeDescriptor> value_;

private:
    static napi_value New(napi_env env, napi_callback_info info);
    static void Destructor(napi_env env, void *data, void *hint);
    static TypeDescriptorNapi *GetDescriptorNapi(napi_env env, napi_callback_info info,
                                                 std::shared_ptr<ContextBase> &ctxt);
    static napi_value GetTypeId(napi_env env, napi_callback_info info);
    static napi_value GetBelongingToTypes(napi_env env, napi_callback_info info);
    static napi_value GetDescription(napi_env env, napi_callback_info info);
    static napi_value GetIconFile(napi_env env, napi_callback_info info);
    static napi_value GetReferenceURL(napi_env env, napi_callback_info info);
    static napi_value GetFilenameExtensions(napi_env env, napi_callback_info info);
    static napi_value GetMimeTypes(napi_env env, napi_callback_info info);
};
} // namespace UDMF
} // namespace OHOS
#endif // UDMF_TYPE_DESCRIPTOR_NAPI_H
