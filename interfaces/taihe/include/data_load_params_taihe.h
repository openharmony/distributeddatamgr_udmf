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

#ifndef UDMF_DATA_LOAD_PARAMS_TAIHE_H
#define UDMF_DATA_LOAD_PARAMS_TAIHE_H

#include "ani.h"
#include "async_task_params.h"
#include "concurrent_map.h"
#include "unified_data_taihe.h"
#include "ohos.data.unifiedDataChannel.UnifiedDataOrNull.ani.1.hpp"
#include "ohos.data.unifiedDataChannel.UnifiedDataOrNull.proj.1.hpp"
#include "ohos.data.unifiedDataChannel.UnifiedDataInner.ani.1.hpp"
#include "ohos.data.unifiedDataChannel.UnifiedDataInner.proj.1.hpp"
namespace taiheChannel = ohos::data::unifiedDataChannel;

namespace OHOS {
namespace UDMF {
class DataLoadParamsTaihe {
public:
    static bool Convert2NativeValue(ani_env *env, ani_object in, DataLoadParams &dataLoadParams);

private:
    static bool SetDataLoadInfo(ani_env *env, ani_object in, DataLoadParams &dataLoadParams);
    static void SaveCallback(ani_env *env, DataLoadParams &dataLoadParam, ani_fn_object callback);
    static bool SetLoadHandler(ani_env *env, DataLoadParams &dataLoadParam, ani_fn_object callback, bool isAsync);
    static int32_t HandleUnifiedData(ani_env *env, std::string udKey, ani_object data);
    static ani_status CallHandler(ani_env *env,
        ani_fn_object &anifn, DataLoadInfo &acceptableInfo, bool isAsync, ani_ref &result);

    static ConcurrentMap<std::string, ani_fn_object> anifns;
};
} // namespace UDMF
} // namespace OHOS
#endif // UDMF_DATA_LOAD_PARAMS_TAIHE_H