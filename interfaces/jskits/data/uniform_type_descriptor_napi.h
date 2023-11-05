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

#ifndef UNIFORM_TYPE_DESCRIPTOR_NAPI_H
#define UNIFORM_TYPE_DESCRIPTOR_NAPI_H

#include <string>

#include "napi/native_api.h"
#include "napi/native_node_api.h"

namespace OHOS {
namespace UDMF {
class UniformTypeDescriptorNapi {
public:
    static napi_value UniformTypeDescriptorInit(napi_env env, napi_value exports);
    static napi_value GetTypeDescriptor(napi_env env, napi_callback_info info);
    static napi_value GetUniformDataTypeByFilenameExtension(napi_env env, napi_callback_info info);
    static napi_value GetUniformDataTypeByMIMEType(napi_env env, napi_callback_info info);

private:
    static napi_value CreateUniformDataType(napi_env env);
    static napi_status SetNamedProperty(napi_env env, napi_value &obj, const std::string &name,
        const std::string &value);
};
}
}
#endif // UNIFORM_TYPE_DESCRIPTOR_NAPI_H
