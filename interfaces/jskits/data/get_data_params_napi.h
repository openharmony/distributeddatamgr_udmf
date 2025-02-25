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

#ifndef UDMF_GET_DATA_PARAMS_NAPI_H
#define UDMF_GET_DATA_PARAMS_NAPI_H

#include "async_task_params.h"
#include "concurrent_map.h"
#include "napi/native_api.h"
#include "napi/native_node_api.h"
#include "visibility.h"

namespace OHOS {
namespace UDMF {

class API_EXPORT GetDataParamsNapi {
public:
    static bool Convert2NativeValue(napi_env env, napi_value in, GetDataParams &getDataParams, const std::string &key);

private:
    struct ListenerArgs {
        ProgressInfo progressInfo;
        UnifiedData *unifiedData;
        constexpr static size_t ARGV_SIZE = 2;
    };

    static bool SetProgressListener(napi_env env, GetDataParams &getDataParam,
        napi_value callback, const std::string &key);
    static void CallProgressListener(napi_env env, napi_value callback, void *context, void *data);
    static ListenerArgs* CreateListenerArgs(ProgressInfo progressInfo, std::shared_ptr<UnifiedData> data);
    static void DeleteListenerArgs(ListenerArgs *listenerArgs);

    static ConcurrentMap<std::string, napi_threadsafe_function> tsfns;
};

} // namespace UDMF
} // namespace OHOS
#endif // UDMF_GET_DATA_PARAMS_NAPI_H