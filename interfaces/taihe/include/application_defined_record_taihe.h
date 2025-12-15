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

#ifndef UDMF_APPLICATION_TAIHE_H
#define UDMF_APPLICATION_TAIHE_H

#include "application_defined_record.h"
#include "ohos.data.unifiedDataChannel.proj.hpp"
#include "ohos.data.unifiedDataChannel.impl.hpp"

namespace taiheChannel = ohos::data::unifiedDataChannel;
namespace OHOS {
namespace UDMF {
class ApplicationDefinedRecordTaihe {
public:
    ApplicationDefinedRecordTaihe();
    ApplicationDefinedRecordTaihe(std::shared_ptr<ApplicationDefinedRecord> value);

    ::taihe::string GetType();
    ::ohos::data::unifiedDataChannel::ValueType GetValue();
    ::taihe::array<::taihe::string> GetTypes();
    void AddEntry(::taihe::string_view type, ::taiheChannel::ValueType value);
    ::taiheChannel::ValueType GetEntry(::taihe::string_view type);
    ::taihe::map<::taihe::string, ::taiheChannel::ValueType> GetEntries();
    ::taihe::string GetApplicationDefinedType();
    void SetApplicationDefinedType(const ::taihe::string_view &applicationDefinedType);
    ::taihe::optional<::taihe::array<uint8_t>> GetRawData();
    void SetRawData(const ::taihe::array_view<uint8_t> &rawData);
    int64_t GetInner();

    std::shared_ptr<ApplicationDefinedRecord> value_;
};
} // namespace UDMF
} // namespace OHOS
#endif // UDMF_APPLICATION_TAIHE_H