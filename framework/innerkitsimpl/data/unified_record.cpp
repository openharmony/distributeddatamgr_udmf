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

#include "getter_system.h"
#include "logger.h"

namespace OHOS {
namespace UDMF {
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

void UnifiedRecord::SetType(const UDType &type)
{
    dataType_ = type;
    utdId_ = UtdUtils::GetUtdIdFromUtdEnum(type);
}

int64_t UnifiedRecord::GetSize()
{
    return 0;
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
        AddEntry(utdId, ValueType(value));
        return value;
    }
    return std::monostate();
}

std::shared_ptr<std::map<std::string, ValueType>> UnifiedRecord::GetEntries() const
{
    auto res = std::make_shared<std::map<std::string, ValueType>>(*entries_);
    if (!utdId_.empty()) {
        res->insert_or_assign(utdId_, value_);
    }
    return res;
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

void UnifiedRecord::SetEntryGetter(const std::set<std::string> &utdIds, const std::shared_ptr<EntryGetter> entryGetter)
{
    for (auto utdId : utdIds) {
        AddEntry(utdId, ValueType());
    }
    entryGetter_ = std::move(entryGetter);
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
        object->value_["VALUE_TYPE"] = value;
    }
}

bool UnifiedRecord::HasObject()
{
    return hasObject_;
}

} // namespace UDMF
} // namespace OHOS