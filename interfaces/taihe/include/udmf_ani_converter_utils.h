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

#ifndef UDMF_ANI_CONVERTER_UTILS_H
#define UDMF_ANI_CONVERTER_UTILS_H

#include "ani.h"
#include "unified_data.h"
#include "async_task_params.h"

namespace OHOS {
namespace UDMF {
class AniConverter {
public:
    static std::shared_ptr<UnifiedData> UnwrapUnifiedData(ani_env *env, ani_object object);

    static ani_object WrapUnifiedData(ani_env *env, std::shared_ptr<UnifiedData> unifiedData);

    static ani_object WrapProgressInfo(ani_env *env, ProgressInfo info);

    static std::shared_ptr<UnifiedRecord> UnwrapUnifiedRecord(ani_env *env, ani_object object);

    static ani_object WrapUnifiedRecord(ani_env *env, std::shared_ptr<UnifiedRecord> unifiedRecord);

    static ani_object WrapSummary(ani_env *env, std::shared_ptr<Summary> summary);

    static GetDataParams UnwrapGetDataParams(ani_env *env, ani_object object, const std::string &key);
};
} // namespace UDMF
} // namespace OHOS
#endif