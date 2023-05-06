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

#include "data_manager.h"

#include "logger.h"
#include "preprocess_utils.h"
#include "checker_manager.h"
#include "file.h"
#include "uri_permission_manager.h"

namespace OHOS {
namespace UDMF {
const std::string MSDP_PROCESS_NAME = "msdp_sa";
DataManager::DataManager()
{
    authorizationMap_[UD_INTENTION_MAP.at(UD_INTENTION_DRAG)] = MSDP_PROCESS_NAME;
    CheckerManager::GetInstance().LoadCheckers();
}

DataManager::~DataManager()
{
}

DataManager &DataManager::GetInstance()
{
    static DataManager instance;
    return instance;
}

int32_t DataManager::SaveData(CustomOption &option, UnifiedData &unifiedData, std::string &key)
{
    if (unifiedData.GetRecords().empty()) {
        LOG_ERROR(UDMF_FRAMEWORK, "Invalid parameters, have no record");
        return E_INVALID_PARAMETERS;
    }

    if (!UnifiedDataUtils::IsValidIntention(option.intention)) {
        LOG_ERROR(UDMF_FRAMEWORK, "Invalid parameters intention: %{public}d.", option.intention);
        return E_INVALID_PARAMETERS;
    }

    // imput runtime info before put it into store and save one privilege
    PreProcessUtils utils = PreProcessUtils::GetInstance();
    if (!utils.RuntimeDataImputation(unifiedData, option)) {
        LOG_ERROR(UDMF_FRAMEWORK, "Imputation failed, %{public}s", utils.errorStr.c_str());
        return E_UNKNOWN;
    }
    for (const auto &record : unifiedData.GetRecords()) {
        record->SetUid(PreProcessUtils::GetInstance().IdGenerator());
    }

    std::string intention = unifiedData.GetRuntime()->key.intention;
    auto store = storeCache_.GetStore(intention);
    if (store == nullptr) {
        LOG_ERROR(UDMF_FRAMEWORK, "Get store failed, intention: %{public}s.", intention.c_str());
        return E_DB_ERROR;
    }

    if (!store->Clear()) {
        LOG_ERROR(UDMF_FRAMEWORK, "Clear store failed, intention: %{public}s.", intention.c_str());
        return E_DB_ERROR;
    }

    if (store->Put(unifiedData) != E_OK) {
        LOG_ERROR(UDMF_FRAMEWORK, "Put unified data failed, intention: %{public}s.", intention.c_str());
        return E_DB_ERROR;
    }
    key = unifiedData.GetRuntime()->key.GetUnifiedKey();
    return E_OK;
}

int32_t DataManager::RetrieveData(QueryOption &query, UnifiedData &unifiedData)
{
    UnifiedKey key(query.key);
    if (!key.IsValid()) {
        LOG_ERROR(UDMF_FRAMEWORK, "Unified key: %{public}s is invalid.", query.key.c_str());
        return E_INVALID_PARAMETERS;
    }

    auto store = storeCache_.GetStore(key.intention);
    if (store == nullptr) {
        LOG_ERROR(UDMF_FRAMEWORK, "Get store failed, intention: %{public}s.", key.intention.c_str());
        return E_DB_ERROR;
    }

    UnifiedData tmpData;
    int32_t res = store->Get(key, tmpData);
    if (res != E_OK) {
        LOG_ERROR(UDMF_FRAMEWORK, "Get data from store failed, intention: %{public}s.", key.intention.c_str());
        return res;
    }

    if (tmpData.IsEmpty()) {
        return E_OK;
    }

    std::shared_ptr<Runtime> runtime = tmpData.GetRuntime();
    CheckerManager::CheckInfo info;
    info.tokenId = query.tokenId;
    info.pid = query.pid;
    if (!CheckerManager::GetInstance().IsValid(runtime->privileges, info)) {
        LOG_ERROR(UDMF_FRAMEWORK, "Invalid caller, intention: %{public}s.", key.intention.c_str());
        return E_INVALID_OPERATION;
    }

    auto records = tmpData.GetRecords();
    for (auto record : records) {
        auto type = record->GetType();
        if (type == UDType::FILE || type == UDType::IMAGE || type == UDType::VIDEO) {
            std::string bundleName;
            if (!PreProcessUtils::GetInstance().GetHapBundleNameByToken(query.tokenId, bundleName)) {
                return E_ERROR;
            }
            auto file = static_cast<File *>(record.get());
            if (UriPermissionManager::GetInstance().GrantUriPermission(file->GetUri(), bundleName) != E_OK) {
                return E_ERROR;
            }
        }
    }

    unifiedData = tmpData;

    if (store->Delete(key) != E_OK) {
        LOG_ERROR(UDMF_FRAMEWORK, "Remove data failed, intention: %{public}s.", key.intention.c_str());
        return E_DB_ERROR;
    }
    return E_OK;
}

int32_t DataManager::GetSummary(QueryOption &query, Summary &summary)
{
    UnifiedKey key(query.key);
    if (!key.IsValid()) {
        LOG_ERROR(UDMF_FRAMEWORK, "Unified key: %{public}s is invalid.", query.key.c_str());
        return E_INVALID_PARAMETERS;
    }

    auto store = storeCache_.GetStore(key.intention);
    if (store == nullptr) {
        LOG_ERROR(UDMF_FRAMEWORK, "Get store failed, intention: %{public}s.", key.intention.c_str());
        return E_DB_ERROR;
    }

    if (store->GetSummary(key, summary) != E_OK) {
        LOG_ERROR(UDMF_FRAMEWORK, "Store get summary failed, intention: %{public}s.", key.intention.c_str());
        return E_DB_ERROR;
    }
    return E_OK;
}

int32_t DataManager::AddPrivilege(QueryOption &query, const Privilege &privilege)
{
    UnifiedKey key(query.key);
    if (!key.IsValid()) {
        LOG_ERROR(UDMF_FRAMEWORK, "Unified key: %{public}s is invalid.", query.key.c_str());
        return E_INVALID_PARAMETERS;
    }

    std::string processName;
    PreProcessUtils utils = PreProcessUtils::GetInstance();
    if (!utils.GetNativeProcessNameByToken(query.tokenId, processName)) {
        LOG_ERROR(UDMF_FRAMEWORK, "%{public}s", utils.errorStr.c_str());
        return E_UNKNOWN;
    }

    if (processName != authorizationMap_[key.intention]) {
        LOG_ERROR(UDMF_FRAMEWORK, "Process: %{public}s have no permission", processName.c_str());
        return E_FORBIDDEN;
    }

    auto store = storeCache_.GetStore(key.intention);
    if (store == nullptr) {
        LOG_ERROR(UDMF_FRAMEWORK, "Get store failed, intention: %{public}s.", key.intention.c_str());
        return E_DB_ERROR;
    }

    UnifiedData data;
    int32_t res = store->Get(key, data);
    if (res != E_OK) {
        LOG_ERROR(UDMF_FRAMEWORK, "Get data from store failed, intention: %{public}s.", key.intention.c_str());
        return res;
    }

    if (data.IsEmpty()) {
        LOG_ERROR(UDMF_FRAMEWORK, "Invalid parameters, unified data has no record, intention: %{public}s.",
            key.intention.c_str());
        return E_INVALID_PARAMETERS;
    }

    data.GetRuntime()->privileges.emplace_back(privilege);
    if (store->Update(data) != E_OK) {
        LOG_ERROR(UDMF_FRAMEWORK, "Update unified data failed, intention: %{public}s.", key.intention.c_str());
        return E_DB_ERROR;
    }
    return E_OK;
}

int32_t DataManager::Sync(const QueryOption &query, const std::vector<std::string> &devices)
{
    UnifiedKey key(query.key);
    if (!key.IsValid()) {
        LOG_ERROR(UDMF_FRAMEWORK, "Unified key: %{public}s is invalid.", query.key.c_str());
        return E_INVALID_PARAMETERS;
    }

    auto store = storeCache_.GetStore(key.intention);
    if (store == nullptr) {
        LOG_ERROR(UDMF_FRAMEWORK, "Get store failed, intention: %{public}s.", key.intention.c_str());
        return E_DB_ERROR;
    }

    if (store->Sync(devices) != E_OK) {
        LOG_ERROR(UDMF_FRAMEWORK, "Store sync failed, intention: %{public}s.", key.intention.c_str());
        return E_DB_ERROR;
    }
    return E_OK;
}
} // namespace UDMF
} // namespace OHOS