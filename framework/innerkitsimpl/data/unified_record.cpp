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
#define LOG_TAG "UnifiedRecord"
#include "unified_record.h"

#include "file.h"
#include "getter_system.h"
#include "logger.h"
#include "utd_client.h"

namespace OHOS {
namespace UDMF {
static constexpr UDType FILE_TYPES[] = {FILE, AUDIO, FOLDER, IMAGE, VIDEO};
static constexpr const char *FILE_SCHEME = "file";
static const std::set<std::string> FILE_SUB_TYPES = {
    "general.image", "general.video", "general.audio", "general.folder" };
static constexpr UDType UDC_RECORDS[] = {APPLICATION_DEFINED_RECORD, AUDIO, FILE, FOLDER, HTML, IMAGE, HYPERLINK,
    PLAIN_TEXT, SYSTEM_DEFINED_APP_ITEM, SYSTEM_DEFINED_FORM, SYSTEM_DEFINED_PIXEL_MAP, SYSTEM_DEFINED_RECORD,
    TEXT, VIDEO};

UnifiedRecord::UnifiedRecord()
{
    dataType_ = UD_BUTT;
}

UnifiedRecord::UnifiedRecord(UDType type)
{
    dataType_ = type;
    utdId_ = UtdUtils::GetUtdIdFromUtdEnum(type);
    utdId2_ = utdId_;
}

UnifiedRecord::UnifiedRecord(UDType type, ValueType value)
{
    dataType_ = type;
    utdId_ = UtdUtils::GetUtdIdFromUtdEnum(type);
    utdId2_ = utdId_;
    value_ = value;
    if (std::holds_alternative<std::shared_ptr<Object>>(value_)) {
        if (utdId_ == GENERAL_FILE_URI) {
            ObjectUtils::ProcessFileUriType(dataType_, value_);
        }
    }
}

UDType UnifiedRecord::GetType() const
{
    return this->dataType_;
}

std::vector<std::string> UnifiedRecord::GetTypes() const
{
    std::vector<std::string> types;
    for (auto it = entries_->begin(); it != entries_->end(); it++) {
        types.push_back(it->first);
    }
    types.push_back(utdId2_);
    return types;
}

void UnifiedRecord::SetType(const UDType &type)
{
    dataType_ = type;
    utdId_ = UtdUtils::GetUtdIdFromUtdEnum(type);
    utdId2_ = utdId_;
}

int64_t UnifiedRecord::GetSize()
{
    if (std::holds_alternative<std::shared_ptr<Object>>(value_)) {
        auto value = std::get<std::shared_ptr<Object>>(value_);
        if (value->value_.size() == 1) {
            return ObjectUtils::GetValueSize(value_, true) + GetInnerEntriesSize();
        }
    }
    return ObjectUtils::GetValueSize(value_, false) + GetInnerEntriesSize();
}

std::string UnifiedRecord::GetUid() const
{
    return this->uid_;
}

void UnifiedRecord::SetUid(const std::string &id)
{
    this->uid_ = id;
}

ValueType UnifiedRecord::GetValue()
{
    return value_;
}

void UnifiedRecord::SetValue(const ValueType &value)
{
    value_ = value;
}

ValueType UnifiedRecord::GetOriginValue() const
{
    return value_;
}

bool UnifiedRecord::HasType(const std::string &utdId) const
{
    if (entries_->find(utdId) != entries_->end()) {
        return true;
    }
    return utdId == utdId2_;
}

void UnifiedRecord::AddEntry(const std::string &utdId, ValueType &&value)
{
    std::lock_guard<std::recursive_mutex> lock(mutex_);
    if (utdId == utdId2_ || utdId2_.empty()) {
        utdId_ = utdId;
        utdId2_ = utdId_;
        value_ = std::move(value);
        auto udType = static_cast<UDType>(UtdUtils::GetUtdEnumFromUtdId(utdId2_));
        if (udType == UD_BUTT) {
            dataType_ = APPLICATION_DEFINED_RECORD;
            return;
        }
        if (utdId == GENERAL_FILE_URI && std::holds_alternative<std::shared_ptr<Object>>(value_)) {
            ObjectUtils::ProcessFileUriType(udType, value_);
        }
        dataType_ = udType;
    } else {
        entries_->insert_or_assign(utdId, std::move(value));
    }
}

ValueType UnifiedRecord::GetEntry(const std::string &utdId)
{
    std::lock_guard<std::recursive_mutex> lock(mutex_);
    if (utdId2_ == utdId && !(std::holds_alternative<std::monostate>(value_))) {
        auto value = value_;
        if (!std::holds_alternative<std::shared_ptr<Object>>(value_)
            && std::find(std::begin(UDC_RECORDS), std::end(UDC_RECORDS), dataType_) != std::end(UDC_RECORDS)) {
            InitObject();
            value = value_;
            auto obj = std::get<std::shared_ptr<Object>>(value_);
            value_ = obj->value_[VALUE_TYPE];
        }
        return value;
    }
    auto it = entries_->find(utdId);
    if (it != entries_->end() && !(std::holds_alternative<std::monostate>(it->second))) {
        return it->second;
    }
    auto getter = GetterSystem::GetInstance().GetGetter(channelName_);
    if (getter != nullptr && (utdId2_ == utdId || it != entries_->end())) {
        auto value = getter->GetValueByType(dataId_, recordId_, utdId);
        if (std::holds_alternative<std::monostate>(value)) {
            LOG_ERROR(UDMF_FRAMEWORK, "get value failed, utdId: %{public}s", utdId.c_str());
            return std::monostate();
        }
        AddEntry(utdId, ValueType(value));
        return value;
    }
    if (utdId2_ == utdId && std::holds_alternative<std::monostate>(value_)) {
        InitObject();
        auto value = value_;
        auto obj = std::get<std::shared_ptr<Object>>(value_);
        value_ = obj->value_[VALUE_TYPE];
        if (obj->value_.size() == 1) { // value_ size equals 1 means there are no datas
            return std::monostate();
        } else {
            return value;
        }
    }
    return std::monostate();
}

std::shared_ptr<std::map<std::string, ValueType>> UnifiedRecord::GetEntries()
{
    auto res = std::make_shared<std::map<std::string, ValueType>>(*entries_);
    if (!utdId2_.empty()) {
        if (!std::holds_alternative<std::shared_ptr<Object>>(value_)) {
            InitObject();
            ValueType value = value_;
            res->insert_or_assign(utdId2_, std::move(value));
            auto object = std::get<std::shared_ptr<Object>>(value_);
            value_ = object->value_[VALUE_TYPE];   // restore value_
        } else {
            res->insert_or_assign(utdId2_, value_);
        }
    }
    return res;
}

std::shared_ptr<std::map<std::string, ValueType>> UnifiedRecord::GetInnerEntries() const
{
    return entries_;
}

void UnifiedRecord::SetInnerEntries(std::shared_ptr<std::map<std::string, ValueType>> entries)
{
    entries_ = entries;
}

int64_t UnifiedRecord::GetInnerEntriesSize() const
{
    if (entries_ == nullptr) {
        return 0;
    }
    int64_t size = 0;
    for (auto &entry : *entries_) {
        size += ObjectUtils::GetValueSize(entry.second, false);
    }
    return size;
}

std::set<std::string> UnifiedRecord::GetUtdIds() const
{
    std::set<std::string> utdIds;
    if (!utdId_.empty()) {
        utdIds.emplace(utdId_);
    }
    for (const auto& [key, value] : *entries_) {
        utdIds.emplace(key);
    }
    return utdIds;
}

std::set<std::string> UnifiedRecord::GetUtdIdsWithAddFileType() const
{
    std::set<std::string> utdIds;
    if (!utdId2_.empty()) {
        utdIds.emplace(utdId2_);
        if (utdId2_ == GENERAL_FILE_URI && std::holds_alternative<std::shared_ptr<Object>>(value_)) {
            auto fileUri = std::get<std::shared_ptr<Object>>(value_);
            AddFileUriType(utdIds, fileUri);
        }
    }
    for (const auto& [key, value] : *entries_) {
        utdIds.emplace(key);
        if (key == GENERAL_FILE_URI && std::holds_alternative<std::shared_ptr<Object>>(value)) {
            auto fileUri = std::get<std::shared_ptr<Object>>(value);
            AddFileUriType(utdIds, fileUri);
        }
    }
    return utdIds;
}

void UnifiedRecord::SetUtdId(const std::string& utdId)
{
    utdId_ = utdId;
    utdId2_ = utdId;
}

std::string UnifiedRecord::GetUtdId() const
{
    return utdId_;
}

void UnifiedRecord::SetUtdId2(const std::string& utdId)
{
    utdId2_ = utdId;
}

std::string UnifiedRecord::GetUtdId2() const
{
    return utdId2_;
}

void UnifiedRecord::SetDataId(uint32_t dataId)
{
    dataId_ = dataId;
}

uint32_t UnifiedRecord::GetDataId() const
{
    return dataId_;
}

void UnifiedRecord::SetRecordId(uint32_t recordId)
{
    recordId_ = recordId;
}

uint32_t UnifiedRecord::GetRecordId() const
{
    return recordId_;
}

void UnifiedRecord::SetEntryGetter(
    const std::vector<std::string> &utdIds,
    const std::shared_ptr<EntryGetter> &entryGetter)
{
    for (auto const &utdId : utdIds) {
        if (HasType(utdId)) {
            LOG_WARN(UDMF_FRAMEWORK, "already has the utdId: %{public}s", utdId.c_str());
            continue;
        }
        AddEntry(utdId, ValueType());
    }
    entryGetter_ = entryGetter;
}

std::shared_ptr<EntryGetter> UnifiedRecord::GetEntryGetter()
{
    return entryGetter_;
}

void UnifiedRecord::SetChannelName(const std::string &channelName)
{
    channelName_ = channelName;
}

void UnifiedRecord::InitObject()
{
    if (!std::holds_alternative<std::shared_ptr<Object>>(value_)) {
        auto value = value_;
        value_ = std::make_shared<Object>();
        auto object = std::get<std::shared_ptr<Object>>(value_);
        object->value_.insert_or_assign(VALUE_TYPE, std::move(value));
    }
}

bool UnifiedRecord::HasFileType(std::string &fileUri) const
{
    fileUri.clear();
    if (std::holds_alternative<std::shared_ptr<Object>>(GetOriginValue())) {
        auto obj = std::get<std::shared_ptr<Object>>(GetOriginValue());
        if (obj->value_.find(ORI_URI) != obj->value_.end()) {
            obj->GetValue(ORI_URI, fileUri);
        }
    } else if (std::find(std::begin(FILE_TYPES), std::end(FILE_TYPES), GetType()) != std::end(FILE_TYPES)) {
        auto file = static_cast<const File*>(this);
        fileUri = file->GetUri();
    } else {
        return false;
    }

    if (fileUri.empty()) {
        LOG_ERROR(UDMF_FRAMEWORK, "Get uri empty, plase check the uri.");
        return false;
    }
#ifndef CROSS_PLATFORM
    Uri uri(fileUri);
    std::string scheme = uri.GetScheme();
    std::transform(scheme.begin(), scheme.end(), scheme.begin(), ::tolower);
    if (uri.GetAuthority().empty() || scheme != FILE_SCHEME) {
        LOG_INFO(UDMF_FRAMEWORK, "Get uri authority empty or uri scheme not equals to file.");
        return false;
    }
#endif
    return true;
}

void UnifiedRecord::SetFileUri(const std::string &fileUri)
{
    if (std::find(std::begin(FILE_TYPES), std::end(FILE_TYPES), GetType()) != std::end(FILE_TYPES)) {
        auto file = static_cast<File*>(this);
        file->SetUri(fileUri);
    } else if (std::holds_alternative<std::shared_ptr<Object>>(GetOriginValue())) {
        auto obj = std::get<std::shared_ptr<Object>>(GetOriginValue());
        obj->value_[ORI_URI] = fileUri;
    } else {
        LOG_ERROR(UDMF_FRAMEWORK, "Record has no uri.");
    }
}

std::vector<UriInfo> UnifiedRecord::GetUris() const
{
    return uris_;
}

void UnifiedRecord::SetUris(std::vector<UriInfo> uris)
{
    uris_ = std::move(uris);
}

void UnifiedRecord::ClearUris()
{
    uris_.clear();
}

void UnifiedRecord::ComputeUris(const std::function<bool(UriInfo &)> &action)
{
    for (auto &uri : uris_) {
        if (!action(uri)) {
            break;
        }
    }
}

void UnifiedRecord::AddFileUriType(std::set<std::string> &utdIds, const std::shared_ptr<Object> &fileUri) const
{
    if (fileUri == nullptr) {
        return;
    }
    std::string uniformDataType;
    if (fileUri->GetValue(UNIFORM_DATA_TYPE, uniformDataType) && uniformDataType == GENERAL_FILE_URI) {
        std::string fileType;
        if (fileUri->GetValue(FILE_TYPE, fileType) && !fileType.empty()) {
            utdIds.emplace(fileType);
        }
    }
}
} // namespace UDMF
} // namespace OHOS