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

#include <algorithm>
#include <vector>

#include "logger.h"
#include "same_process_ipc_guard.h"
#include "tlv_util.h"

namespace OHOS {
namespace UDMF {
using namespace DistributedKv;
const AppId RuntimeStore::APP_ID = { "distributeddata" };
const std::string RuntimeStore::DATA_PREFIX = "udmf://";
const std::string RuntimeStore::BASE_DIR = "/data/service/el1/public/database/distributeddata";

RuntimeStore::RuntimeStore(const std::string &storeId) : storeId_({ storeId })
{
    LOG_INFO(UDMF_SERVICE, "Construct runtimeStore: %{public}s.", storeId_.storeId.c_str());
}

RuntimeStore::~RuntimeStore()
{
    LOG_INFO(UDMF_SERVICE, "Destruct runtimeStore: %{public}s.", storeId_.storeId.c_str());
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

        Entry entry = { Key(unifiedKey + "/" + record->GetUid()), Value(recordBytes) };
        entries.push_back(entry);
    }
    // add runtime info
    std::vector<uint8_t> runtimeBytes;
    auto runtimeTlv = TLVObject(runtimeBytes);
    if (!TLVUtil::Writing(*unifiedData.GetRuntime(), runtimeTlv)) {
        LOG_ERROR(UDMF_SERVICE, "Marshall runtime info failed.");
        return E_UNKNOWN;
    }
    Entry entry = { Key(unifiedKey), Value(runtimeBytes) };
    entries.push_back(entry);
    auto status = PutEntries(entries);
    return status;
}

Status RuntimeStore::Get(const std::string &key, UnifiedData &unifiedData)
{
    std::vector<Entry> entries;
    if (GetEntries(key, entries) != E_OK) {
        return E_DB_ERROR;
    }
    if (entries.empty()) {
        LOG_DEBUG(UDMF_FRAMEWORK, "entries is empty.");
        return E_OK;
    }
    for (const auto &entry : entries) {
        std::string keyStr = entry.key.ToString();
        if (keyStr == key) {
            Runtime runtime;
            auto runtimeTlv = TLVObject(const_cast<std::vector<uint8_t> &>(entry.value.Data()));
            if (!TLVUtil::Reading(runtime, runtimeTlv)) {
                LOG_ERROR(UDMF_SERVICE, "Unmarshall runtime info failed.");
                return E_UNKNOWN;
            }
            unifiedData.SetRuntime(runtime);
        } else {
            std::shared_ptr<UnifiedRecord> record;
            auto recordTlv = TLVObject(const_cast<std::vector<uint8_t> &>(entry.value.Data()));
            if (!TLVUtil::Reading(record, recordTlv)) {
                LOG_ERROR(UDMF_SERVICE, "Unmarshall unified record failed.");
                return E_UNKNOWN;
            }
            unifiedData.AddRecord(record);
        }
    }
    return E_OK;
}

Status RuntimeStore::GetSummary(const std::string &key, Summary &summary)
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
    std::string key = unifiedData.GetRuntime()->key.key;
    if (Delete(key) != E_OK) {
        LOG_ERROR(UDMF_SERVICE, "Delete unified data failed.");
        return E_DB_ERROR;
    }
    if (Put(unifiedData) != E_OK) {
        LOG_ERROR(UDMF_SERVICE, "Put unified data failed.");
        return E_DB_ERROR;
    }
    return E_OK;
}

Status RuntimeStore::Delete(const std::string &key)
{
    std::vector<Entry> entries;
    if (GetEntries(key, entries) != E_OK) {
        return E_DB_ERROR;
    }
    if (entries.empty()) {
        LOG_DEBUG(UDMF_FRAMEWORK, "entries is empty.");
        return E_OK;
    }
    std::vector<Key> keys;
    for (const auto &entry : entries) {
        keys.push_back(entry.key);
    }
    auto status = DeleteEntries(keys);
    return status;
}

Status RuntimeStore::DeleteBatch(const std::vector<std::string> &unifiedKeys)
{
    LOG_DEBUG(UDMF_SERVICE, "called!");
    if (unifiedKeys.empty()) {
        LOG_DEBUG(UDMF_SERVICE, "No need to delete!");
        return E_OK;
    }
    for (const std::string &unifiedKey : unifiedKeys) {
        if (Delete(unifiedKey) != E_OK) {
            return E_DB_ERROR;
        }
    }
    return E_OK;
}

Status RuntimeStore::Sync(const std::vector<std::string> &devices)
{
    SameProcessIpcGuard ipcGuard;
    DistributedKv::Status status = kvStore_->Sync(devices, SyncMode::PULL);
    if (status != DistributedKv::Status::SUCCESS) {
        LOG_ERROR(UDMF_SERVICE, "Sync kvStore failed, status: %{public}d.", status);
        return E_DB_ERROR;
    }
    return E_OK;
}

Status RuntimeStore::Clear()
{
    return Delete(DATA_PREFIX) != E_DB_ERROR ? E_OK : E_DB_ERROR;
}

Status RuntimeStore::GetBatchData(const std::string &dataPrefix, std::vector<UnifiedData> &unifiedDataSet)
{
    std::vector<Entry> entries;
    auto status = GetEntries(dataPrefix, entries);
    if (status != E_OK) {
        LOG_ERROR(UDMF_FRAMEWORK, "GetEntries failed.");
        return E_DB_ERROR;
    }
    if (entries.empty()) {
        LOG_DEBUG(UDMF_FRAMEWORK, "entries is empty.");
        return E_OK;
    }
    for (const auto &entry : entries) {
        UnifiedData data;
        std::string keyStr = entry.key.ToString();
        if (std::count(keyStr.begin(), keyStr.end(), '/') == SLASH_COUNT_IN_KEY) {
            status = Get(keyStr, data);
            unifiedDataSet.push_back(data);
        }
    }
    return status;
}

void RuntimeStore::Close()
{
    dataManager_.CloseKvStore(APP_ID, storeId_);
}

bool RuntimeStore::Init()
{
    Options options;
    options.autoSync = false;
    options.createIfMissing = true;
    options.rebuild = true;
    options.backup = false;
    options.securityLevel = SecurityLevel::S1;
    options.baseDir = BASE_DIR;
    options.area = Area::EL1;
    options.kvStoreType = KvStoreType::SINGLE_VERSION;
    SameProcessIpcGuard ipcGuard;
    DistributedKv::Status status = dataManager_.GetSingleKvStore(options, APP_ID, storeId_, kvStore_);
    if (status != DistributedKv::Status::SUCCESS) {
        LOG_ERROR(UDMF_SERVICE, "GetKvStore: %{public}s failed, status: %{public}d.", storeId_.storeId.c_str(), status);
        return false;
    }
    return true;
}

Status RuntimeStore::GetEntries(const std::string &dataPrefix, std::vector<Entry> &entries)
{
    DataQuery query;
    query.KeyPrefix(dataPrefix);
    query.OrderByWriteTime(true);
    auto status = kvStore_->GetEntries(query, entries);
    if (status != DistributedKv::Status::SUCCESS) {
        LOG_ERROR(UDMF_SERVICE, "KvStore getEntries failed, status: %{public}d.", static_cast<int>(status));
        return E_DB_ERROR;
    }
    return E_OK;
}

Status RuntimeStore::PutEntries(const std::vector<Entry> &entries)
{
    size_t size = entries.size();
    DistributedKv::Status status;
    for (size_t index = 0; index < size; index += MAX_BATCH_SIZE) {
        std::vector<Entry> batchEntries(
            entries.begin() + index, entries.begin() + std::min(index + MAX_BATCH_SIZE, size));
        status = kvStore_->PutBatch(batchEntries);
        if (status != DistributedKv::Status::SUCCESS) {
            LOG_ERROR(UDMF_SERVICE, "KvStore putBatch failed, status: %{public}d.", status);
            return E_DB_ERROR;
        }
    }
    return E_OK;
}

Status RuntimeStore::DeleteEntries(const std::vector<Key> &keys)
{
    size_t size = keys.size();
    DistributedKv::Status status;
    for (size_t index = 0; index < size; index += MAX_BATCH_SIZE) {
        std::vector<Key> batchKeys(keys.begin() + index, keys.begin() + std::min(index + MAX_BATCH_SIZE, size));
        status = kvStore_->DeleteBatch(batchKeys);
        if (status != DistributedKv::Status::SUCCESS) {
            LOG_ERROR(UDMF_SERVICE, "KvStore deleteBatch failed, status: %{public}d.", status);
            return E_DB_ERROR;
        }
    }
    return E_OK;
}
} // namespace UDMF
} // namespace OHOS