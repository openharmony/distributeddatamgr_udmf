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

#ifndef UDMF_NAPI_DATA_UTILS_H
#define UDMF_NAPI_DATA_UTILS_H

#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <variant>
#include <vector>

#include "napi/native_api.h"
#include "napi/native_common.h"
#include "napi/native_node_api.h"
#include "napi_common_want.h"
#include "securec.h"

#include "logger.h"
#include "unified_meta.h"
#include "type_descriptor.h"
#include "type_descriptor_napi.h"
#include "pixel_map_napi.h"

namespace OHOS {
namespace UDMF {
class NapiDataUtils {
public:
    /* napi_value <-> bool */
    static napi_status GetValue(napi_env env, napi_value in, bool &out);
    static napi_status SetValue(napi_env env, const bool &in, napi_value &out);

    /* napi_value <-> int32_t */
    static napi_status GetValue(napi_env env, napi_value in, int32_t &out);
    static napi_status SetValue(napi_env env, const int32_t &in, napi_value &out);

    /* napi_value <-> int64_t */
    static napi_status GetValue(napi_env env, napi_value in, int64_t &out);
    static napi_status SetValue(napi_env env, const int64_t &in, napi_value &out);

    /* napi_value <-> float */
    static napi_status GetValue(napi_env env, napi_value in, float &out);
    static napi_status SetValue(napi_env env, const float &in, napi_value &out);

    /* napi_value <-> double */
    static napi_status GetValue(napi_env env, napi_value in, double &out);
    static napi_status SetValue(napi_env env, const double &in, napi_value &out);

    /* napi_value <-> std::string */
    static napi_status GetValue(napi_env env, napi_value in, std::string &out);
    static napi_status SetValue(napi_env env, const std::string &in, napi_value &out);

    /* napi_value <-> std::vector<std::string> */
    static napi_status GetValue(napi_env env, napi_value in, std::vector<std::string> &out);
    static napi_status SetValue(napi_env env, const std::vector<std::string> &in, napi_value &out);

    /* napi_value <-> std::vector<uint8_t> */
    static napi_status GetValue(napi_env env, napi_value in, std::vector<uint8_t> &out);
    static napi_status SetValue(napi_env env, const std::vector<uint8_t> &in, napi_value &out);

    /* napi_value <-> std::map<std::string, int32_t> */
    static napi_status GetValue(napi_env env, napi_value in, std::map<std::string, int32_t> &out);
    static napi_status SetValue(napi_env env, const std::map<std::string, int32_t> &in, napi_value &out);

    /* napi_value <-> std::map<std::string, int64_t> */
    static napi_status GetValue(napi_env env, napi_value in, std::map<std::string, int64_t> &out);
    static napi_status SetValue(napi_env env, const std::map<std::string, int64_t> &in, napi_value &out);

    /* napi_value <-> UDVariant */
    static napi_status GetValue(napi_env env, napi_value in, UDVariant &out);
    static napi_status SetValue(napi_env env, const UDVariant &in, napi_value &out);

    /* napi_value <-> UDDetails */
    static napi_status GetValue(napi_env env, napi_value in, UDDetails &out);
    static napi_status SetValue(napi_env env, const UDDetails &in, napi_value &out);

    static napi_status GetValue(napi_env env, napi_value in, std::shared_ptr<TypeDescriptor> &descriptor);

    static napi_status GetValue(napi_env env, napi_value in, std::shared_ptr<OHOS::Media::PixelMap> &pixelMap);
    static napi_status SetValue(napi_env env, const std::shared_ptr<OHOS::Media::PixelMap> &in, napi_value &out);

    static napi_status GetValue(napi_env env, napi_value in, std::shared_ptr<OHOS::AAFwk::Want> &wantPtr);
    static napi_status SetValue(napi_env env, const std::shared_ptr<OHOS::AAFwk::Want> &in, napi_value &out);

    static bool IsTypeForNapiValue(napi_env env, napi_value param, napi_valuetype expectType);

    static bool IsNull(napi_env env, napi_value value);
    /* napi_define_class  wrapper */
    static napi_value DefineClass(napi_env env, const std::string &name, const napi_property_descriptor *properties,
        size_t count, napi_callback newcb);

private:
    enum {
        /* std::map<key, value> to js::tuple<key, value> */
        TUPLE_KEY = 0,
        TUPLE_VALUE,
        TUPLE_SIZE
    };
};

#define LOG_ERROR_RETURN(condition, message, retVal)                             \
    do {                                                                         \
        if (!(condition)) {                                                      \
            LOG_ERROR(UDMF_KITS_NAPI, "test (" #condition ") failed: " message); \
            return retVal;                                                       \
        }                                                                        \
    } while (0)

#define LOG_ERROR_RETURN_VOID(condition, message)                                \
    do {                                                                         \
        if (!(condition)) {                                                      \
            LOG_ERROR(UDMF_KITS_NAPI, "test (" #condition ") failed: " message); \
            return;                                                              \
        }                                                                        \
    } while (0)
} // namespace UDMF
} // namespace OHOS
#endif // UDMF_NAPI_DATA_UTILS_H
