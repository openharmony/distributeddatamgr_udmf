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

namespace OHOS {
namespace UDMF {
static constexpr UDType FILE_TYPES[] = {FILE, AUDIO, FOLDER, IMAGE, VIDEO};
static constexpr const char *FILE_SCHEME = "file";

UnifiedRecord::UnifiedRecord()
{
    dataType_ = UD_BUTT;
}

UnifiedRecord::UnifiedRecord(UDType type)
{
    dataType_ = type;
    utdId_ = UtdUtils::GetUtdIdFromUtdEnum(type);
}

UnifiedRecord::UnifiedRecord(UDType type, ValueType value)
{
    dataType_ = type;
    utdId_ = UtdUtils::GetUtdIdFromUtdEnum(type);
    value_ = value;
    if (std::holds_alternative<std::shared_ptr<Object>>(value_)) {
        hasObject_ = true;
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
    types.push_back(utdId_);
    return types;
}

void UnifiedRecord::SetType(const UDType &type)
{
    dataType_ = type;
    utdId_ = UtdUtils::GetUtdIdFromUtdEnum(type);
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
    return utdId == utdId_;
}

void UnifiedRecord::AddEntry(const std::string &utdId, ValueType &&value)
{
    std::lock_guard<std::recursive_mutex> lock(mutex_);
    if (utdId == utdId_ || utdId_.empty()) {
        utdId_ = utdId;
        value_ = std::move(value);
        auto udType = static_cast<UDType>(UtdUtils::GetUtdEnumFromUtdId(utdId_));
        if (udType != UD_BUTT) {
            dataType_ = udType;
        } else {
            dataType_ = APPLICATION_DEFINED_RECORD;
        }
    } else {
        entries_->insert_or_assign(utdId, std::move(value));
    }
}

ValueType UnifiedRecord::GetEntry(const std::string &utdId)
{
    std::lock_guard<std::recursive_mutex> lock(mutex_);
    if (utdId_ == utdId && !(std::holds_alternative<std::monostate>(value_))) {
        return value_;
    }
    auto it = entries_->find(utdId);
    if (it != entries_->end() && !(std::holds_alternative<std::monostate>(it->second))) {
        return it->second;
    }
    auto getter = GetterSystem::GetInstance().GetGetter(channelName_);
    if (getter != nullptr && (utdId_ == utdId || it != entries_->end())) {
        auto value = getter->GetValueByType(dataId_, recordId_, utdId);
        if (std::holds_alternative<std::monostate>(value)) {
            LOG_ERROR(UDMF_FRAMEWORK, "get value failed, utdId: %{public}s", utdId.c_str());
            return std::monostate();
        }
        AddEntry(utdId, ValueType(value));
        return value;
    }
    return std::monostate();
}

std::shared_ptr<std::map<std::string, ValueType>> UnifiedRecord::GetEntries()
{
    auto res = std::make_shared<std::map<std::string, ValueType>>(*entries_);
    if (!utdId_.empty()) {
        if (!std::holds_alternative<std::shared_ptr<Object>>(value_)) {
            InitObject();
            ValueType value = value_;
            res->insert_or_assign(utdId_, std::move(value));
            auto object = std::get<std::shared_ptr<Object>>(value_);
            value_ = object->value_[VALUE_TYPE];   // restore value_
        } else {
            res->insert_or_assign(utdId_, value_);
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

void UnifiedRecord::SetUtdId(const std::string& utdId)
{
    utdId_ = utdId;
}

std::string UnifiedRecord::GetUtdId() const
{
    return utdId_;
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

bool UnifiedRecord::HasObject()
{
    return hasObject_;
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
    Uri uri(fileUri);
    std::string scheme = uri.GetScheme();
    std::transform(scheme.begin(), scheme.end(), scheme.begin(), ::tolower);
    if (uri.GetAuthority().empty() || scheme != FILE_SCHEME) {
        LOG_INFO(UDMF_FRAMEWORK, "Get uri authority empty or uri scheme not equals to file.");
        return false;
    }
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

} // namespace UDMF
} // namespace OHOS