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
#include "logger.h"
#include "unified_data.h"
#include "utd_client.h"

namespace OHOS {
namespace UDMF {
static const std::set<std::string> FILE_TYPES = {
    "general.file", "general.image", "general.video", "general.audio", "general.folder", "general.file-uri" };
static constexpr const char *RECORDS_TANSFER_TAG = "records_to_entries_data_format";
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
    this->SetSdkVersion(runtime.sdkVersion);
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
        std::vector<std::string> recordTypes = record->GetTypes();
        if (std::find(recordTypes.begin(), recordTypes.end(), type) != recordTypes.end()) {
            return true;
        }
    }
    return false;
}

bool UnifiedData::HasHigherFileType(const std::string &type) const
{
    std::set<std::string> types = GetTypIds();
    if (types.find(type) != types.end()) {
        return true;
    }
    if (!UnifiedDataUtils::IsFilterFileType(type)) {
        return false;
    }
    for (auto it = types.begin(); it != types.end(); ++it) {
        std::shared_ptr<TypeDescriptor> descriptor;
        UtdClient::GetInstance().GetTypeDescriptor(*it, descriptor);
        if (descriptor == nullptr) {
            continue;
        }
        bool isFileType = false;
        descriptor->BelongsTo(type, isFileType);
        if (isFileType) {
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
    auto types = GetTypIds();
    std::set<std::string> intersection;
    std::set_intersection(FILE_TYPES.begin(), FILE_TYPES.end(), types.begin(), types.end(),
        std::inserter(intersection, intersection.begin()));
    return !intersection.empty();
}

bool UnifiedData::HasUriInfo() const
{
    for (auto record : records_) {
        if (record == nullptr) {
            return false;
        }
        if (!record->GetUris().empty()) {
            return true;
        }
    }
    return false;
}

void UnifiedData::ClearUriInfo() const
{
    for (auto record : records_) {
        if (record == nullptr) {
            return;
        }
        record->ClearUris();
    }
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

std::set<std::string> UnifiedData::GetTypIds() const
{
    std::set<std::string> types;
    for (const auto &record : records_) {
        std::set<std::string> recordTypes = record->GetUtdIdsWithAddFileType(true);
        types.insert(recordTypes.begin(), recordTypes.end());
    }
    return types;
}

std::vector<std::string> UnifiedData::GetFileUris() const
{
    std::vector<std::string> uris;
    for (auto record : records_) {
        std::string oriUri;
        if (record == nullptr || !record->HasFileType(oriUri)) {
            continue;
        }
        uris.push_back(oriUri);
    }
    return uris;
}

bool UnifiedData::IsNeedTransferToEntries() const
{
    if (records_.size() <= 1) {
        return false;
    }
    if (properties_ == nullptr) {
        return false;
    }
    return properties_->tag == RECORDS_TANSFER_TAG;
}

void UnifiedData::ConvertRecordsToEntries()
{
    if (!IsNeedTransferToEntries()) {
        return;
    }
    std::shared_ptr<UnifiedRecord> recordFirst = records_[0];
    if (recordFirst == nullptr) {
        LOG_ERROR(UDMF_FRAMEWORK, "First record is null");
        return;
    }
    for (size_t i = 1; i < records_.size(); i++) {
        auto record = records_[i];
        if (record == nullptr) {
            continue;
        }
        if (record->GetUtdId2() == recordFirst->GetUtdId2()) {
            continue;
        }
        record->InitObject();
        recordFirst->AddEntry(record->GetUtdId2(), record->GetValue());
    }
    records_.erase(records_.begin() + 1, records_.end());
    LOG_INFO(UDMF_FRAMEWORK, "Convert records to entries finished");
}

std::string UnifiedData::GetSdkVersion() const
{
    return sdkVersion_;
}

void UnifiedData::SetSdkVersion(const std::string &version)
{
    sdkVersion_ = version;
}
} // namespace UDMF
} // namespace OHOS