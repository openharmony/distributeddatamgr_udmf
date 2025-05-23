/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef DATA_LOAD_PARAMS_NAPI_H
#define DATA_LOAD_PARAMS_NAPI_H

#include "async_task_params.h"
#include "concurrent_map.h"
#include "napi/native_api.h"
#include "napi/native_node_api.h"
#include "visibility.h"
#include <string>

namespace OHOS {
namespace UDMF {

class DataLoadParamsNapi {
public:
    API_EXPORT static bool Convert2NativeValue(napi_env env, napi_value in, DataLoadParams &dataLoadParams);

private:
    struct DataLoadArgs {
        std::string udKey;
        DataLoadInfo dataLoadInfo;
    };
    static napi_value CreateDataLoadInfo(napi_env env, const DataLoadInfo &dataLoadInfo);
    static void CallDataLoadHandler(napi_env env, napi_value callback, void *context, void *data);
    
    static ConcurrentMap<std::string, napi_threadsafe_function> tsfns_;
};

} // namespace UDMF
} // namespace OHOS
#endif // DATA_LOAD_PARAMS_NAPI_H