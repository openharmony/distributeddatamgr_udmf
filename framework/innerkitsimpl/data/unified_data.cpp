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
#define LOG_TAG "UnifiedData"
#include "unified_data.h"
#include <chrono>
#include <cinttypes>
#include "logger.h"

namespace OHOS {
namespace UDMF {
UnifiedData::UnifiedData()
{
    properties_ = std::make_shared<UnifiedDataProperties>();
    properties_->timestamp = std::chrono::steady_clock::now().time_since_epoch().count();
}

UnifiedData::UnifiedData(std::shared_ptr<UnifiedDataProperties> properties)
{
    properties_ = properties;
}

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
    this->records_.push_back(record);
}

void UnifiedData::AddRecords(const std::vector<std::shared_ptr<UnifiedRecord>> &records)
{
    for (auto &record :records) {
        if (record == nullptr) {
            return;
        }
        this->records_.push_back(record);
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

std::vector<UDType> UnifiedData::GetUDTypes() const
{
    std::vector<UDType> typeSet;
    for (const std::shared_ptr<UnifiedRecord> &record : records_) {
        typeSet.push_back(record->GetType());
    }
    return typeSet;
}

std::string UnifiedData::GetTypes()
{
    std::string types;
    for (const std::shared_ptr<UnifiedRecord> &record : records_) {
        types.append("-").append(UD_TYPE_MAP.at(record->GetType()));
    }
    return types;
}

std::vector<std::string> UnifiedData::GetTypesLabels() const
{
    std::vector<std::string> types;
    for (const std::shared_ptr<UnifiedRecord> &record : records_) {
        types.push_back(UD_TYPE_MAP.at(record->GetType()));
    }
    return types;
}

bool UnifiedData::HasType(const std::string &type) const
{
    for (const std::shared_ptr<UnifiedRecord> &record : records_) {
        if (UD_TYPE_MAP.at(record->GetType()) == type) {
            return true;
        }
    }
    return false;
}

bool UnifiedData::IsEmpty() const
{
    return records_.empty();
}

bool UnifiedData::IsValid()
{
    if (this->IsEmpty()) {
        LOG_ERROR(UDMF_FRAMEWORK, "Empty data without any record!");
        return false;
    }
    if (this->GetSize() > MAX_DATA_SIZE) {
        LOG_ERROR(UDMF_FRAMEWORK, "Exceeded data limit, UnifiedData size: %{public}" PRId64 " !", this->GetSize());
        return false;
    }
    return true;
}

bool UnifiedData::IsComplete()
{
    std::shared_ptr<Runtime> runtime = this->GetRuntime();
    if (runtime == nullptr) {
        return false;
    }
    if (static_cast<uint32_t>(this->GetRecords().size()) != runtime->recordTotalNum) {
        LOG_ERROR(UDMF_FRAMEWORK,
            "The records of unifiedData is incomplete, expected recordsNum is %{public}u, not %{public}zu.",
            runtime->recordTotalNum, this->GetRecords().size());
        return false;
    }
    return true;
}

void UnifiedData::SetProperties(std::shared_ptr<UnifiedDataProperties> properties)
{
    properties_ = properties;
}

std::shared_ptr<UnifiedDataProperties> UnifiedData::GetProperties() const
{
    return properties_;
}
} // namespace UDMF
} // namespace OHOS