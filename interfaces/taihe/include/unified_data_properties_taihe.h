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

#ifndef UDMF_UNIFIED_DATA_PROPERTIES_TAIHE_H
#define UDMF_UNIFIED_DATA_PROPERTIES_TAIHE_H

#include "ohos.data.unifiedDataChannel.proj.hpp"
#include "ohos.data.unifiedDataChannel.impl.hpp"
#include "unified_data_properties.h"
#include "taihe_common_utils.h"

namespace taiheChannel = ohos::data::unifiedDataChannel;
namespace OHOS {
namespace UDMF {
class UnifiedDataPropertiesTaihe {
public:
    UnifiedDataPropertiesTaihe();
    UnifiedDataPropertiesTaihe(std::shared_ptr<UnifiedDataProperties> value, ani_fn_object fn);

    ::taihe::string GetTag();
    void SetTag(::taihe::string);
    ::taihe::map<::taihe::string, uintptr_t> GetExtras();
    void SetExtras(::taihe::map<::taihe::string, uintptr_t> extras);
    uintptr_t GetTimestamp();
    ::taiheChannel::ShareOptions GetShareOptions();
    void SetShareOptions(::taiheChannel::ShareOptions shareOptions);
    int64_t GetInner();
    uintptr_t GetDelayData();
    void SetDelayData(uintptr_t setDelayData);

    std::shared_ptr<UnifiedDataProperties> value_;
    ani_fn_object delayData_ = nullptr;
};
} // namespace UDMF
} // namespace OHOS
#endif // UDMF_UNIFIED_DATA_PROPERTIES_TAIHE_H