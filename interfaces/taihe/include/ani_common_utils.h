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

#ifndef UDMF_ANI_COMMON_UTILS_H
#define UDMF_ANI_COMMON_UTILS_H

#include "ani.h"
#include "async_task_params.h"
#include "logger.h"
#include "unified_data.h"

namespace OHOS {
namespace UDMF {
ani_ref WrapMapParams(ani_env *env, const std::map<std::string, int64_t> &mapParams);

ani_object CreateInt(ani_env *env, ani_int value);

bool SetFieldRef(ani_env *env, ani_class cls, ani_object object, const std::string &fieldName, ani_ref value);

bool InnerWrapMapParams(ani_env* env, ani_class wantCls, ani_object wantObject,
    const std::map<std::string, int64_t> mapParams);

} // namespace UDMF
} // namespace OHOS
#endif // UDMF_ANI_COMMON_UTILS_H