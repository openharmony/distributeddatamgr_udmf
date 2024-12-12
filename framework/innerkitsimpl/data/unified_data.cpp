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
#include "logger.h"

namespace OHOS {
namespace UDMF {
UnifiedData::UnifiedData()
{
    properties_ = std::make_shared<UnifiedDataProperties>();
    auto duration = std::chrono::system_clock::now().time_since_epoch();
    properties_->timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
}

UnifiedData::UnifiedData(std::shared_ptr<UnifiedDataProperties> properties)
{
    if (properties == nullptr) {
        LOG_ERROR(UDMF_FRAMEWORK, "Invalid properties!");
        return;
    }
    properties_ = properties;
    auto duration = std::chrono::system_clock::now().time_since_epoch();
    properties_->timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
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
    record->SetRecordId(++recordId_);
    this->records_.push_back(record);
}

void UnifiedData::AddRecords(const std::vector<std::shared_ptr<UnifiedRecord>> &records)
{
    for (auto &record :records) {
        if (record == nullptr) {
            LOG_ERROR(UDMF_FRAMEWORK, "Invalid record, skip!");
            continue;
        }
        record->SetRecordId(++recordId_);
        this->records_.push_back(record);
    }
}

std::shared_ptr<UnifiedRecord> UnifiedData::GetRecordAt(std::size_t index) const
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

std::vector<std::string> UnifiedData::GetTypesLabels() const
{
    std::vector<std::string> types;
    for (const std::shared_ptr<UnifiedRecord> &record : records_) {
        types.push_back(UtdUtils::GetUtdIdFromUtdEnum(record->GetType()));
    }
    return types;
}

bool UnifiedData::HasType(const std::string &type) const
{
    for (const std::shared_ptr<UnifiedRecord> &record : records_) {
        if (UtdUtils::GetUtdIdFromUtdEnum(record->GetType()) == type) {
            return true;
        }
    }
    return false;
}

std::vector<std::string> UnifiedData::GetEntriesTypes() const
{
    std::set<std::string> labels;
    for (const auto &record : records_) {
        auto types = record->GetUtdIds();
        labels.insert(types.begin(), types.end());
    }
    return std::vector<std::string>(labels.begin(), labels.end());
}

bool UnifiedData::HasTypeInEntries(const std::string &type) const
{
    for (const auto &record : records_) {
        if (record == nullptr) {
            LOG_ERROR(UDMF_FRAMEWORK, "Invalid record, skip!");
            continue;
        }
        auto types = record->GetUtdIds();
        if (types.find(type) != types.end()) {
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

bool UnifiedData::HasFileType() const
{
    std::set<UDType> fileTypes = {UDType::FILE, UDType::IMAGE, UDType::VIDEO, UDType::AUDIO, UDType::FOLDER};
    auto types = GetUDTyps();
    for (auto udType : types) {
        if (fileTypes.find(udType) != fileTypes.end()) {
            return true;
        }
    }
    return false;
}

void UnifiedData::SetProperties(std::shared_ptr<UnifiedDataProperties> properties)
{
    if (!properties) {
        LOG_ERROR(UDMF_FRAMEWORK, "properties is null!");
        return;
    }
    if (properties_ == nullptr) {
        LOG_ERROR(UDMF_FRAMEWORK, "properties_ is nullptr!");
        return;
    }
    properties->timestamp = properties_->timestamp;
    properties_ = properties;
}

std::shared_ptr<UnifiedDataProperties> UnifiedData::GetProperties() const
{
    return properties_;
}

void UnifiedData::SetDataId(uint32_t dataId)
{
    dataId_ = dataId;
}

uint32_t UnifiedData::GetDataId() const
{
    return dataId_;
}

void UnifiedData::SetChannelName(const std::string &name)
{
    channelName_ = std::move(name);
}

std::set<UDType> UnifiedData::GetUDTyps() const
{
    std::set<UDType> types;
    for (const auto &record : records_) {
        types.insert(record->GetType());
    }
    return types;
}

} // namespace UDMF
} // namespace OHOS