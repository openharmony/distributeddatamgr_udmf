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
#ifndef UDMF_GET_DATA_PARAMS_H
#define UDMF_GET_DATA_PARAMS_H

#include "ani.h"
#include "ohos.data.unifiedDataChannel.proj.hpp"
#include "ohos.data.unifiedDataChannel.impl.hpp"
#include "concurrent_map.h"
#include "async_task_params.h"

namespace OHOS {
namespace UDMF {
class GetDataParamsTaihe {
public:
    static bool Convert2NativeValue(ani_env *env, ani_object in, GetDataParams &getDataParams, const std::string &key);

private:
    static bool SetProgressIndicator(ani_env *env, ani_object in, GetDataParams &getDataParams);
    static bool SetDestUri(ani_env *env, ani_object in, GetDataParams &getDataParams);
    static bool SetFileConflictOptions(ani_env *env, ani_object in, GetDataParams &getDataParams);
    static void SaveCallback(ani_env *env, GetDataParams &getDataParam,
        ani_fn_object callback, const std::string &key);
    static bool SetProgressListener(ani_env *env, GetDataParams &getDataParam,
        ani_fn_object callback, const std::string &key);

    static ConcurrentMap<std::string, ani_fn_object> anifns;
};
} // namespace UDMF
} // namespace OHOS
#endif // UDMF_GET_DATA_PARAMS_H