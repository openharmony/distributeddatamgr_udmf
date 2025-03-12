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
#include "unified_meta.h"
#include "visibility.h"
#include "unified_types.h"

namespace OHOS {
namespace UDMF {
class UnifiedRecord {
public:
    API_EXPORT UnifiedRecord();
    explicit API_EXPORT UnifiedRecord(UDType type);
    API_EXPORT UnifiedRecord(UDType type, ValueType value);
    virtual ~UnifiedRecord() = default;

    API_EXPORT UnifiedRecord(const UnifiedRecord& other) = delete;
    API_EXPORT UnifiedRecord& operator=(const UnifiedRecord& other) = delete;
    API_EXPORT UnifiedRecord(UnifiedRecord &&other) = delete;
    API_EXPORT UnifiedRecord& operator=(UnifiedRecord &&other) = delete;

    UDType API_EXPORT GetType() const;
    std::vector<std::string> API_EXPORT GetTypes() const;
    void API_EXPORT SetType(const UDType &type);
    virtual int64_t API_EXPORT GetSize();

    std::string API_EXPORT GetUid() const;
    void API_EXPORT SetUid(const std::string &id);
    ValueType API_EXPORT GetValue();
    void SetValue(const ValueType &value);
    ValueType API_EXPORT GetOriginValue() const;

    void API_EXPORT SetUtdId(const std::string &utdId);
    std::set<std::string> API_EXPORT GetUtdIds() const;
    std::string API_EXPORT GetUtdId() const;

    bool API_EXPORT HasType(const std::string &utdId) const;
    void API_EXPORT AddEntry(const std::string &utdId, ValueType &&value);
    ValueType API_EXPORT GetEntry(const std::string &utdId);
    std::shared_ptr<std::map<std::string, ValueType>> API_EXPORT GetEntries();
    std::shared_ptr<std::map<std::string, ValueType>> API_EXPORT GetInnerEntries() const;
    void SetInnerEntries(std::shared_ptr<std::map<std::string, ValueType>> entries);
    int64_t GetInnerEntriesSize() const;
	
    void API_EXPORT SetEntryGetter(const std::vector<std::string> &utdIds,
        const std::shared_ptr<EntryGetter> &entryGetter);
    std::shared_ptr<EntryGetter> API_EXPORT GetEntryGetter();
    void API_EXPORT SetDataId(uint32_t dataId);
    uint32_t API_EXPORT GetDataId() const;
    void API_EXPORT SetRecordId(uint32_t recordId);
    uint32_t API_EXPORT GetRecordId() const;
    void API_EXPORT SetChannelName(const std::string &channelName);

    virtual void InitObject();
    bool HasObject();
    bool HasFileType(std::string &fileUri) const;
    void SetFileUri(const std::string &fileUri);

    std::vector<UriInfo> GetUris() const;
    void SetUris(std::vector<UriInfo> uris);
    void API_EXPORT ClearUris();
    void API_EXPORT ComputeUris(const std::function<bool(UriInfo &)> &action);
protected:
    UDType dataType_;
    std::string utdId_;
    ValueType value_;
    bool hasObject_ = false;
private:
    void AddFileUriType(std::set<std::string> &utdIds, const std::shared_ptr<Object> &fileUri) const;
    std::string uid_; // unique identifier
    std::shared_ptr<std::map<std::string, ValueType>> entries_ = std::make_shared<std::map<std::string, ValueType>>();
    std::vector<UriInfo> uris_;
    uint32_t dataId_ = 0;
    uint32_t recordId_ = 0;
    std::string channelName_;
    std::shared_ptr<EntryGetter> entryGetter_;
    mutable std::recursive_mutex mutex_;
};
} // namespace UDMF
} // namespace OHOS
#endif // UDMF_UNIFIED_RECORD_H
