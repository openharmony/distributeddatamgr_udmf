/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#ifndef UDMF_UNIFIED_DATA_H
#define UDMF_UNIFIED_DATA_H

#include "unified_data_properties.h"
#include "unified_record.h"

namespace OHOS {
namespace UDMF {
class UnifiedData {
public:
    UnifiedData();
    explicit UnifiedData(std::shared_ptr<UnifiedDataProperties> properties);

    int64_t GetSize();
    std::string GetGroupId() const;

    std::shared_ptr<Runtime> GetRuntime() const;
    void SetRuntime(Runtime &runtime);

    void AddRecord(const std::shared_ptr<UnifiedRecord> &record);
    void AddRecords(const std::vector<std::shared_ptr<UnifiedRecord>> &records);
    std::shared_ptr<UnifiedRecord> GetRecordAt(std::size_t index);
    void SetRecords(std::vector<std::shared_ptr<UnifiedRecord>> records);
    std::vector<std::shared_ptr<UnifiedRecord>> GetRecords() const;

    std::vector<UDType> GetUDTypes() const;
    std::string GetTypes();
    std::vector<std::string> GetTypesLabels() const;
    bool HasType(const std::string &type) const;

    bool IsEmpty() const;
    bool IsValid();
    bool IsComplete();

    void SetProperties(std::shared_ptr<UnifiedDataProperties> properties);
    std::shared_ptr<UnifiedDataProperties> GetProperties() const;

    static constexpr int64_t MAX_DATA_SIZE = 200 * 1024 * 1024;

private:
    std::shared_ptr<Runtime> runtime_;
    std::vector<std::shared_ptr<UnifiedRecord>> records_;
    std::shared_ptr<UnifiedDataProperties> properties_;
};
} // namespace UDMF
} // namespace OHOS
#endif // UDMF_UNIFIED_DATA_H
