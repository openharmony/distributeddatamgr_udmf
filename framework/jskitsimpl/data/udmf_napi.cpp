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
#include "udmf_napi.h"

#include <unordered_map>

#include "logger.h"
#include "napi_data_utils.h"
#include "napi_error_utils.h"
#include "napi_queue.h"
#include "unified_meta.h"

namespace OHOS {
namespace UDMF {
napi_value UDMFNapi::UDMFInit(napi_env env, napi_value exports)
{
    napi_property_descriptor desc[] = {
        DECLARE_NAPI_GETTER("UnifiedDataType", CreateUnifiedDataType),
    };

    NAPI_CALL(env, napi_define_properties(env, exports, sizeof(desc) / sizeof(desc[0]), desc));
    return exports;
}

napi_value UDMFNapi::CreateUnifiedDataType(napi_env env, napi_callback_info info)
{
    napi_value unifiedDataType = nullptr;
    napi_create_object(env, &unifiedDataType);
    SetNamedProperty(env, unifiedDataType, JS_UD_TYPE_NAME_MAP.at(TEXT), UD_TYPE_MAP.at(TEXT));
    SetNamedProperty(env, unifiedDataType, JS_UD_TYPE_NAME_MAP.at(PLAIN_TEXT), UD_TYPE_MAP.at(PLAIN_TEXT));
    SetNamedProperty(env, unifiedDataType, JS_UD_TYPE_NAME_MAP.at(HTML), UD_TYPE_MAP.at(HTML));
    SetNamedProperty(env, unifiedDataType, JS_UD_TYPE_NAME_MAP.at(HYPER_LINK), UD_TYPE_MAP.at(HYPER_LINK));
    SetNamedProperty(env, unifiedDataType, JS_UD_TYPE_NAME_MAP.at(IMAGE), UD_TYPE_MAP.at(IMAGE));
    SetNamedProperty(env, unifiedDataType, JS_UD_TYPE_NAME_MAP.at(VIDEO), UD_TYPE_MAP.at(VIDEO));
    SetNamedProperty(
        env, unifiedDataType, JS_UD_TYPE_NAME_MAP.at(SYSTEM_DEFINED_RECORD), UD_TYPE_MAP.at(SYSTEM_DEFINED_RECORD));
    SetNamedProperty(
        env, unifiedDataType, JS_UD_TYPE_NAME_MAP.at(SYSTEM_DEFINED_FORM), UD_TYPE_MAP.at(SYSTEM_DEFINED_FORM));
    SetNamedProperty(env, unifiedDataType, JS_UD_TYPE_NAME_MAP.at(SYSTEM_DEFINED_APP_ITEM),
        UD_TYPE_MAP.at(SYSTEM_DEFINED_APP_ITEM));
    SetNamedProperty(env, unifiedDataType, JS_UD_TYPE_NAME_MAP.at(SYSTEM_DEFINED_PIXEL_MAP),
        UD_TYPE_MAP.at(SYSTEM_DEFINED_PIXEL_MAP));
    napi_object_freeze(env, unifiedDataType);
    return unifiedDataType;
}

napi_status UDMFNapi::SetNamedProperty(napi_env env, napi_value &obj, const std::string &name, const std::string &value)
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