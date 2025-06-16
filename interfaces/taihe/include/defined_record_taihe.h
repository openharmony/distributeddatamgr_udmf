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

#ifndef UDMF_SYSTEMDEFINEDRECORD_H
#define UDMF_SYSTEMDEFINEDRECORD_H

#include "ohos.data.unifiedDataChannel.proj.hpp"
#include "ohos.data.unifiedDataChannel.impl.hpp"
#include "system_defined_record.h"

namespace taiheChannel = ohos::data::unifiedDataChannel;
namespace OHOS {
namespace UDMF {
class SystemDefinedRecordTaihe {
public:
    SystemDefinedRecordTaihe();

    ::taihe::string GetType();
    ::taiheChannel::ValueType GetValue();

    ::taihe::optional<::taihe::map<::taihe::string, ::taiheChannel::DetailsValue>> GetDetails();
    void SetDetails(::taihe::map_view<::taihe::string, ::taiheChannel::DetailsValue> details);
    int64_t GetInner();

    std::shared_ptr<SystemDefinedRecord> value_;
};
} // namespace UDMF
} // namespace OHOS
#endif // UDMF_SYSTEMDEFINEDRECORD_H