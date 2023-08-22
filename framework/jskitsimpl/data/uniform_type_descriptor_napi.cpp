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

#include "uniform_type_descriptor_napi.h"

#include "napi_data_utils.h"
#include "napi_error_utils.h"
#include "napi_queue.h"
#include "unified_meta.h"

namespace OHOS {
namespace UDMF {
napi_value UniformTypeDescriptorNapi::UniformTypeDescriptorInit(napi_env env, napi_value exports)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "UniformTypeDescriptorNapi");
    napi_value uniformDataType = CreateUniformDataType(env);
    napi_property_descriptor desc[] = {
        DECLARE_NAPI_PROPERTY("UniformDataType", uniformDataType),
    };

    NAPI_CALL(env, napi_define_properties(env, exports, sizeof(desc) / sizeof(desc[0]), desc));
    return exports;
}

napi_value UniformTypeDescriptorNapi::CreateUniformDataType(napi_env env)
{
    napi_value uniformDataType = nullptr;
    napi_create_object(env, &uniformDataType);
    SetNamedProperty(env, uniformDataType, JS_UD_TYPE_NAME_MAP.at(TEXT), UD_TYPE_MAP.at(TEXT));
    SetNamedProperty(env, uniformDataType, JS_UD_TYPE_NAME_MAP.at(PLAIN_TEXT), UD_TYPE_MAP.at(PLAIN_TEXT));
    SetNamedProperty(env, uniformDataType, JS_UD_TYPE_NAME_MAP.at(HTML), UD_TYPE_MAP.at(HTML));
    SetNamedProperty(env, uniformDataType, JS_UD_TYPE_NAME_MAP.at(HYPERLINK), UD_TYPE_MAP.at(HYPERLINK));
    SetNamedProperty(env, uniformDataType, JS_UD_TYPE_NAME_MAP.at(FILE), UD_TYPE_MAP.at(FILE));
    SetNamedProperty(env, uniformDataType, JS_UD_TYPE_NAME_MAP.at(IMAGE), UD_TYPE_MAP.at(IMAGE));
    SetNamedProperty(env, uniformDataType, JS_UD_TYPE_NAME_MAP.at(VIDEO), UD_TYPE_MAP.at(VIDEO));
    SetNamedProperty(env, uniformDataType, JS_UD_TYPE_NAME_MAP.at(AUDIO), UD_TYPE_MAP.at(AUDIO));
    SetNamedProperty(env, uniformDataType, JS_UD_TYPE_NAME_MAP.at(FOLDER), UD_TYPE_MAP.at(FOLDER));
    SetNamedProperty(env, uniformDataType, JS_UD_TYPE_NAME_MAP.at(SYSTEM_DEFINED_RECORD),
        UD_TYPE_MAP.at(SYSTEM_DEFINED_RECORD));
    SetNamedProperty(env, uniformDataType, JS_UD_TYPE_NAME_MAP.at(SYSTEM_DEFINED_FORM),
        UD_TYPE_MAP.at(SYSTEM_DEFINED_FORM));
    SetNamedProperty(env, uniformDataType, JS_UD_TYPE_NAME_MAP.at(SYSTEM_DEFINED_APP_ITEM),
        UD_TYPE_MAP.at(SYSTEM_DEFINED_APP_ITEM));
    SetNamedProperty(env, uniformDataType, JS_UD_TYPE_NAME_MAP.at(SYSTEM_DEFINED_PIXEL_MAP),
        UD_TYPE_MAP.at(SYSTEM_DEFINED_PIXEL_MAP));
    SetNamedProperty(env, uniformDataType, JS_UD_TYPE_NAME_MAP.at(APPLICATION_DEFINED_RECORD),
        UD_TYPE_MAP.at(APPLICATION_DEFINED_RECORD));
    napi_object_freeze(env, uniformDataType);
    return uniformDataType;
}

napi_status UniformTypeDescriptorNapi::SetNamedProperty(napi_env env, napi_value &obj, const std::string &name,
    const std::string &value)
{
    napi_value property = nullptr;
    napi_status status = NapiDataUtils::SetValue(env, value, property);
    ASSERT(status == napi_ok, "string to napi_value failed!", status);
    status = napi_set_named_property(env, obj, name.c_str(), property);
    ASSERT(status == napi_ok, "napi_set_named_property failed!", status);
    return status;
}
} // namespace UDMF
} // namespace OHOS