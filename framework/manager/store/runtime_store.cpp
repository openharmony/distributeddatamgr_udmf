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

#include "runtime_store.h"

#include <vector>

#include "logger.h"
#include "tlv_util.h"

namespace OHOS {
namespace UDMF {
using namespace DistributedDB;
const std::string RuntimeStore::APP_ID = "distributeddata";
const std::string RuntimeStore::DATA_PREFIX = "udmf://";
const std::string RuntimeStore::BASE_DIR = "/data/service/el1/public/database/distributeddata/kvdb";

RuntimeStore::RuntimeStore(std::string storeId) : delegateManager_(APP_ID, "default"), storeId_(storeId)
{
    LOG_INFO(UDMF_SERVICE, "Construct runtimeStore: %{public}s.", storeId_.c_str());
}

RuntimeStore::~RuntimeStore()
{
    LOG_INFO(UDMF_SERVICE, "Destruct runtimeStore: %{public}s.", storeId_.c_str());
    Close();
}

Status RuntimeStore::Put(const UnifiedData &unifiedData)
{
    std::vector<Entry> entries;
    std::string unifiedKey = unifiedData.GetRuntime()->key.GetUnifiedKey();
    // add unified record
    for (const auto &record : unifiedData.GetRecords()) {
        if (record == nullptr) {
            continue;
        }

        std::vector<uint8_t> recordBytes;
        auto recordTlv = TLVObject(recordBytes);
        if (!TLVUtil::Writing(record, recordTlv)) {
            LOG_ERROR(UDMF_SERVICE, "Marshall unified record failed.");
            return E_INVALID_PARAMETERS;
        }

        std::string recordKeyStr = unifiedKey + "/" + record->GetUid();
        Key recordKey = { recordKeyStr.begin(), recordKeyStr.end() };
        Entry entry = { recordKey, recordBytes };
        entries.push_back(entry);
    }
    // add runtime info
    std::vector<uint8_t> runtimeBytes;
    auto runtimeTlv = TLVObject(runtimeBytes);
    if (!TLVUtil::Writing(*unifiedData.GetRuntime(), runtimeTlv)) {
        LOG_ERROR(UDMF_SERVICE, "Marshall runtime info failed.");
        return E_UNKNOWN;
    }
    Key runtimeKey = { unifiedKey.begin(), unifiedKey.end() };
    Entry entry = { runtimeKey, runtimeBytes };
    entries.push_back(entry);
    auto status = kvStore_->PutBatch(entries);
    if (status != DBStatus::OK) {
        LOG_ERROR(UDMF_SERVICE, "KvStore putBatch failed, status: %{public}d.", static_cast<int>(status));
        return E_DB_ERROR;
    }
    return E_OK;
}

Status RuntimeStore::Get(const UnifiedKey &key, UnifiedData &unifiedData)
{
    Query dbQuery = Query::Select();
    std::vector<uint8_t> prefix = { key.key.begin(), key.key.end() };
    dbQuery.PrefixKey(prefix);
    std::vector<Entry> entries;
    auto status = kvStore_->GetEntries(dbQuery, entries);
    if (status != DBStatus::OK && status != DBStatus::NOT_FOUND) {
        LOG_ERROR(UDMF_SERVICE, "KvStore getEntries failed, status: %{public}d.", static_cast<int>(status));
        return E_DB_ERROR;
    }

    for (const auto &entry : entries) {
        std::string keyStr(entry.key.begin(), entry.key.end());
        if (keyStr == key.key) {
            Runtime runtime;
            auto runtimeTlv = TLVObject(const_cast<std::vector<uint8_t> &>(entry.value));
            if (!TLVUtil::Reading(runtime, runtimeTlv)) {
                LOG_ERROR(UDMF_SERVICE, "Unmarshall runtime info failed.");
                return E_UNKNOWN;
            }
            unifiedData.SetRuntime(runtime);
        } else {
            std::shared_ptr<UnifiedRecord> record;
            auto recordTlv = TLVObject(const_cast<std::vector<uint8_t> &>(entry.value));
            if (!TLVUtil::Reading(record, recordTlv)) {
                LOG_ERROR(UDMF_SERVICE, "Unmarshall unified record failed.");
                return E_UNKNOWN;
            }
            unifiedData.AddRecord(record);
        }
    }
    return E_OK;
}

Status RuntimeStore::GetSummary(const UnifiedKey &key, Summary &summary)
{
    UnifiedData unifiedData;
    if (Get(key, unifiedData) != E_OK) {
        LOG_ERROR(UDMF_SERVICE, "Get unified data failed.");
        return E_DB_ERROR;
    }

    for (const auto &record : unifiedData.GetRecords()) {
        int64_t recordSize = record->GetSize();
        auto it = summary.summary.find(UD_TYPE_MAP.at(record->GetType()));
        if (it == summary.summary.end()) {
            summary.summary[UD_TYPE_MAP.at(record->GetType())] = recordSize;
        } else {
            summary.summary[UD_TYPE_MAP.at(record->GetType())] += recordSize;
        }
        summary.totalSize += recordSize;
    }
    return E_OK;
}

Status RuntimeStore::Update(const UnifiedData &unifiedData)
{
    UnifiedKey unifiedKey = unifiedData.GetRuntime()->key;
    if (Delete(unifiedKey) != E_OK) {
        LOG_ERROR(UDMF_SERVICE, "Delete unified data failed.");
        return E_DB_ERROR;
    }

    if (Put(unifiedData) != E_OK) {
        LOG_ERROR(UDMF_SERVICE, "Put unified data failed.");
        return E_DB_ERROR;
    }
    return E_OK;
}

Status RuntimeStore::Delete(const UnifiedKey &key)
{
    UnifiedData unifiedData;
    if (Get(key, unifiedData) != E_OK) {
        LOG_ERROR(UDMF_SERVICE, "Get unifiedData failed.");
    }

    std::vector<Key> keys;
    keys.push_back({ key.key.begin(), key.key.end() });
    for (const auto &record : unifiedData.GetRecords()) {
        std::string recordKey = key.key + "/" + record->GetUid();
        keys.push_back({ recordKey.begin(), recordKey.end() });
    }
    auto status = kvStore_->DeleteBatch(keys);
    if (status != DBStatus::OK) {
        LOG_ERROR(UDMF_SERVICE, "DeleteBatch kvStore failed, status: %{public}d.", static_cast<int>(status));
        return E_DB_ERROR;
    }
    return E_OK;
}

Status RuntimeStore::Sync(const std::vector<std::string> &devices)
{
    auto onComplete = [this](const std::map<std::string, DBStatus> &) {
        LOG_ERROR(UDMF_SERVICE, "Runtime kvStore sync complete.");
    };
    auto status = kvStore_->Sync(devices, SyncMode::SYNC_MODE_PUSH_ONLY, onComplete);
    if (status != DBStatus::OK) {
        LOG_ERROR(UDMF_SERVICE, "Sync kvStore failed, status: %{public}d.", static_cast<int>(status));
        return E_DB_ERROR;
    }
    return E_OK;
}

bool RuntimeStore::Clear()
{
    Query dbQuery = Query::Select();
    std::vector<uint8_t> prefix = { DATA_PREFIX.begin(), DATA_PREFIX.end() };
    dbQuery.PrefixKey(prefix);
    std::vector<Entry> entries;
    DBStatus status = kvStore_->GetEntries(dbQuery, entries);
    if (status != DBStatus::OK && status != DBStatus::NOT_FOUND) {
        LOG_ERROR(UDMF_SERVICE, "KvStore getEntries failed, status: %{public}d.", static_cast<int>(status));
        return false;
    }

    if (entries.empty()) {
        return true;
    }

    std::vector<Key> keys;
    for (const auto &entry : entries) {
        keys.push_back(entry.key);
    }
    status = kvStore_->DeleteBatch(keys);
    if (status != DBStatus::OK) {
        LOG_ERROR(UDMF_SERVICE, "DeleteBatch kvStore failed, status: %{public}d.", static_cast<int>(status));
        return false;
    }
    return true;
}

void RuntimeStore::Close()
{
    delegateManager_.CloseKvStore(kvStore_.get());
}

bool RuntimeStore::Init()
{
    KvStoreConfig kvStoreConfig{ BASE_DIR };
    delegateManager_.SetKvStoreConfig(kvStoreConfig);

    DBStatus dbStatusTmp = DBStatus::NOT_SUPPORT;
    KvStoreNbDelegate::Option option;
    option.createIfNecessary = true;
    option.isMemoryDb = false;
    option.createDirByStoreIdOnly = true;
    option.isEncryptedDb = false;
    option.isNeedRmCorruptedDb = true;
    option.syncDualTupleMode = true;
    int32_t securityLevel = 2;
    option.secOption = { securityLevel, DistributedDB::ECE };
    DistributedDB::KvStoreNbDelegate *delegate = nullptr;
    delegateManager_.GetKvStore(storeId_, option,
        [&delegate, &dbStatusTmp](DBStatus dbStatus, KvStoreNbDelegate *nbDelegate) {
            delegate = nbDelegate;
            dbStatusTmp = dbStatus;
        });
    if (dbStatusTmp != DBStatus::OK) {
        LOG_ERROR(UDMF_SERVICE, "GetKvStore return error status: %{public}d.", static_cast<int>(dbStatusTmp));
        return false;
    }

    auto release = [this](KvStoreNbDelegate *delegate) {
        LOG_INFO(UDMF_SERVICE, "Release runtime kvStore.");
        if (delegate == nullptr) {
            return;
        }

        auto result = delegateManager_.CloseKvStore(delegate);
        if (result != DBStatus::OK) {
            LOG_ERROR(UDMF_SERVICE, "Close runtime kvStore return error status: %{public}d", static_cast<int>(result));
        }
    };
    kvStore_ = std::shared_ptr<KvStoreNbDelegate>(delegate, release);
    return true;
}
} // namespace UDMF
} // namespace OHOS