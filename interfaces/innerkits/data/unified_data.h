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
#include "visibility.h"
namespace OHOS {
namespace UDMF {
class UnifiedData {
public:
    API_EXPORT UnifiedData();
    explicit API_EXPORT UnifiedData(std::shared_ptr<UnifiedDataProperties> properties);

    int64_t API_EXPORT GetSize();
    std::string GetGroupId() const;

    std::shared_ptr<Runtime> API_EXPORT GetRuntime() const;
    void API_EXPORT SetRuntime(Runtime &runtime);

    void API_EXPORT AddRecord(const std::shared_ptr<UnifiedRecord> &record);
    void API_EXPORT AddRecords(const std::vector<std::shared_ptr<UnifiedRecord>> &records);
    std::shared_ptr<UnifiedRecord> API_EXPORT GetRecordAt(std::size_t index) const;
    void API_EXPORT SetRecords(std::vector<std::shared_ptr<UnifiedRecord>> records);
    std::vector<std::shared_ptr<UnifiedRecord>> API_EXPORT GetRecords() const;

    std::vector<std::string> API_EXPORT GetTypesLabels() const;
    bool API_EXPORT HasType(const std::string &type) const;
    std::vector<std::string> API_EXPORT GetEntriesTypes() const;
    bool API_EXPORT HasTypeInEntries(const std::string &type) const;

    bool API_EXPORT IsEmpty() const;
    bool API_EXPORT IsValid();
    bool API_EXPORT IsComplete();
    bool HasFileType() const;

    void API_EXPORT SetProperties(std::shared_ptr<UnifiedDataProperties> properties);
    std::shared_ptr<UnifiedDataProperties> API_EXPORT GetProperties() const;

    void API_EXPORT SetDataId(uint32_t dataId);
    uint32_t GetDataId() const;
    void SetChannelName(const std::string &name);
    std::vector<std::string> GetFileUris() const;

    static constexpr int64_t MAX_DATA_SIZE = 200 * 1024 * 1024;

private:
    std::set<std::string> GetTypIds() const;

    uint32_t dataId_ = 0;
    uint32_t recordId_ = 0;
    std::string channelName_;
    std::shared_ptr<Runtime> runtime_;
    std::vector<std::shared_ptr<UnifiedRecord>> records_;
    std::shared_ptr<UnifiedDataProperties> properties_;
};
} // namespace UDMF
} // namespace OHOS
#endif // UDMF_UNIFIED_DATA_H
