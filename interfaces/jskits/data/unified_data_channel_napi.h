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

#ifndef UDMF_NAPI_H
#define UDMF_NAPI_H

#include <string>

#include "napi/native_api.h"
#include "napi/native_node_api.h"

namespace OHOS {
namespace UDMF {
class UnifiedDataChannelNapi {
public:
    static napi_value UnifiedDataChannelInit(napi_env env, napi_value exports);

private:
    static napi_value CreateIntention(napi_env env);
    static napi_status SetNamedProperty(napi_env env, napi_value &obj, const std::string &name,
        const std::string &value);
    static napi_value InsertData(napi_env env, napi_callback_info info);
    static napi_value UpdateData(napi_env env, napi_callback_info info);
    static napi_value QueryData(napi_env env, napi_callback_info info);
    static napi_value DeleteData(napi_env env, napi_callback_info info);
    static napi_status GetNamedProperty(napi_env env, napi_value &obj, const std::string &key, std::string &value);
    static napi_value CreateShareOptions(napi_env env, napi_callback_info info);
    static napi_value SetAppShareOptions(napi_env env, napi_callback_info info);
    static napi_value RemoveAppShareOptions(napi_env env, napi_callback_info info);
};
} // namespace UDMF
} // namespace OHOS

#endif // UDMF_NAPI_H
