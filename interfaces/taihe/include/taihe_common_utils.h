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

#ifndef UDMF_TAIHE_COMMON_UTILS_H
#define UDMF_TAIHE_COMMON_UTILS_H

#include "unified_meta.h"
#include "ohos.data.unifiedDataChannel.proj.hpp"
#include "ohos.data.unifiedDataChannel.impl.hpp"
#include "ani.h"
namespace taiheUdmf = OHOS::UDMF;
namespace OHOS {
namespace UDMF {
taiheUdmf::Intention ConvertIntention(::ohos::data::unifiedDataChannel::Intention value);

taiheUdmf::ValueType ConvertValueType(ani_env *env, ::taihe::string_view type,
        ::ohos::data::unifiedDataChannel::ValueType const& value);

::ohos::data::unifiedDataChannel::ValueType ConvertValueType(const taiheUdmf::ValueType &value);

taiheUdmf::UDDetails ConvertUDDetails(::taihe::map_view<::taihe::string, ::taihe::string> details);

::taihe::map_view<::taihe::string, ::taihe::string> ConvertUDDetailsToString(const taiheUdmf::UDDetails &details);

::taihe::map_view<::taihe::string, ::ohos::data::unifiedDataChannel::DetailsValue> ConvertUDDetailsToUnion(
        const taiheUdmf::UDDetails &details);

taiheUdmf::UDDetails ConvertUDDetailsToUnion(
    const ::taihe::map_view<::taihe::string, ::ohos::data::unifiedDataChannel::DetailsValue> &details);

} // namespace UDMF
} // namespace OHOS
#endif // UDMF_TAIHE_COMMON_UTILS_H