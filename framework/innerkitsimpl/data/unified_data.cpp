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

#include "unified_data.h"

namespace OHOS {
namespace UDMF {
int64_t UnifiedData::GetSize()
{
    int64_t totalSize = 0;
    for (const auto &record : this->records_) {
        totalSize += record->GetSize();
    }
    return totalSize;
}

std::string UnifiedData::GetGroupId() const
{
    return this->runtime_->key.groupId;
}

std::shared_ptr<Runtime> UnifiedData::GetRuntime() const
{
    return this->runtime_;
}

void UnifiedData::SetRuntime(Runtime &runtime)
{
    this->runtime_ = std::make_shared<Runtime>(runtime);
}

void UnifiedData::AddRecord(const std::shared_ptr<UnifiedRecord> &record)
{
    if (record == nullptr) {
        return;
    }
    this->records_.emplace_back(record);
    if (records_.size() > MAX_RECORD_NUM) {
        std::vector<std::shared_ptr<UnifiedRecord>> new_records(records_.begin(), records_.end() - 1);
        this->records_ = new_records;
    }
}

std::shared_ptr<UnifiedRecord> UnifiedData::GetRecordAt(std::size_t index)
{
    if (records_.size() > index) {
        return records_[index];
    }
    return nullptr;
}

void UnifiedData::SetRecords(std::vector<std::shared_ptr<UnifiedRecord>> records)
{
    this->records_ = std::move(records);
}

std::vector<std::shared_ptr<UnifiedRecord>> UnifiedData::GetRecords() const
{
    return this->records_;
}

std::vector<UDType> UnifiedData::GetUDTypes()
{
    std::vector<UDType> typeSet;
    for (const std::shared_ptr<UnifiedRecord> &record : records_) {
        typeSet.push_back(record->GetType());
    }
    return typeSet;
}

bool UnifiedData::IsEmpty() const
{
    return records_.empty();
}
} // namespace UDMF
} // namespace OHOS