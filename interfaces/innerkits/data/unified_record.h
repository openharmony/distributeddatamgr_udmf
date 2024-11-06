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

#ifndef UDMF_UNIFIED_RECORD_H
#define UDMF_UNIFIED_RECORD_H

#include <memory>
#include <string>
#include <vector>
#include "entry_getter.h"
#include "visibility.h"
#include "unified_types.h"

namespace OHOS {
namespace UDMF {
class API_EXPORT UnifiedRecord {
public:
    UnifiedRecord();
    explicit UnifiedRecord(UDType type);
    UnifiedRecord(UDType type, ValueType value);
    virtual ~UnifiedRecord() = default;

    UDType GetType() const;
    void SetType(const UDType &type);
    virtual int64_t GetSize();

    std::string GetUid() const;
    void SetUid(const std::string &id);
    ValueType GetValue();
    void SetValue(const ValueType &value);
    ValueType GetOriginValue() const;

    void SetUtdId(const std::string &utdId);
    std::set<std::string> GetUtdIds() const;
    std::string GetUtdId() const;

    bool HasType(const std::string &utdId) const;
    void AddEntry(const std::string &utdId, ValueType &&value);
    ValueType GetEntry(const std::string &utdId);
    std::shared_ptr<std::map<std::string, ValueType>> GetEntries() const;
	
    void SetEntryGetter(const std::vector<std::string> &utdIds, const std::shared_ptr<EntryGetter> &entryGetter);
    std::shared_ptr<EntryGetter> GetEntryGetter();
    void SetDataId(uint32_t dataId);
    uint32_t GetDataId() const;
    void SetRecordId(uint32_t recordId);
    uint32_t GetRecordId() const;
    void SetChannelName(const std::string &channelName);

    virtual void InitObject();
    bool HasObject();
protected:
    static constexpr const char *UNIFORM_DATA_TYPE = "uniformDataType";
    static constexpr const char *DETAILS = "details";
    UDType dataType_;
    ValueType value_;
    bool hasObject_ = false;
private:
    std::string uid_; // unique identifier
    std::string utdId_;
    std::shared_ptr<std::map<std::string, ValueType>> entries_ = std::make_shared<std::map<std::string, ValueType>>();
    uint32_t dataId_ = 0;
    uint32_t recordId_ = 0;
    std::string channelName_;
    std::shared_ptr<EntryGetter> entryGetter_;
};
} // namespace UDMF
} // namespace OHOS
#endif // UDMF_UNIFIED_RECORD_H
