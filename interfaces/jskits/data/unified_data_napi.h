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

#ifndef UDMF_UNIFIED_DATA_NAPI_H
#define UDMF_UNIFIED_DATA_NAPI_H

#include "unified_data_properties_napi.h"

namespace OHOS {
namespace UDMF {
class UnifiedData;
class UnifiedRecord;
class UnifiedDataNapi {
public:
    static napi_value Constructor(napi_env env);
    static napi_status NewInstance(napi_env env, std::shared_ptr<UnifiedData> in, napi_value &out);
    UnifiedDataPropertiesNapi *GetPropertiesNapi(napi_env env);
    
    std::shared_ptr<UnifiedData> value_;
    napi_ref propertyRef_ = nullptr;

private:
    static napi_value New(napi_env env, napi_callback_info info);
    static void Destructor(napi_env env, void *data, void *hint);
    static UnifiedDataNapi *GetUnifiedData(napi_env env, napi_callback_info info);

    static napi_value AddRecord(napi_env env, napi_callback_info info);
    static napi_value GetRecords(napi_env env, napi_callback_info info);
    static void GetRecord(napi_env env, std::shared_ptr<UnifiedRecord> in, napi_value &out);

    static napi_value GetTypes(napi_env env, napi_callback_info info);
    static napi_value HasType(napi_env env, napi_callback_info info);
    static napi_value GetProperties(napi_env env, napi_callback_info info);
    static napi_value SetProperties(napi_env env, napi_callback_info info);
    static napi_ref NewWithRef(napi_env env, size_t argc, napi_value *argv, void **out, napi_value constructor);
    static napi_status Unwrap(napi_env env, napi_value in, void **out, napi_value constructor);
};
} // namespace UDMF
} // namespace OHOS
#endif // UDMF_UNIFIED_DATA_NAPI_H
