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

#include "data_mgr_meta.h"
#include "logger.h"
#include "preprocess_utils.h"

namespace OHOS {
namespace UDMF {
const std::string MSDP_PROCESS_NAME = "msdp_sa";
DataManager::DataManager()
{
    storeMap_[UD_INTENTION_MAP.at(UD_INTENTION_DRAG)] = std::make_shared<RuntimeDataStore>();
    authorizationMap_[UD_INTENTION_MAP.at(UD_INTENTION_DRAG)] = MSDP_PROCESS_NAME;
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
        LOG_ERROR(UDMF_FRAMEWORK, "invalid parameters, have no record");
        return E_INVALID_PARAMETERS;
    }
    if (!UnifiedDataUtils::IsValidIntention(option.intention)) {
        LOG_ERROR(UDMF_FRAMEWORK, "invalid parameters %{public}d", option.intention);
        return E_INVALID_PARAMETERS;
    }
    std::shared_ptr<BaseDataStore> store = storeMap_[UD_INTENTION_MAP.at(option.intention)];
    return store->SaveData(option, unifiedData, key);
}

int32_t DataManager::RetrieveData(QueryOption &query, UnifiedData &unifiedData)
{
    UnifiedKey key(query.key);
    std::shared_ptr<BaseDataStore> store = GetStore(key);
    if (store == nullptr) {
        LOG_ERROR(UDMF_FRAMEWORK, "invalid parameters %{public}s", key.key.c_str());
        return E_INVALID_PARAMETERS;
    }
    int32_t res = store->RetrieveData(key, unifiedData);
    if (res != E_OK) {
        LOG_ERROR(UDMF_FRAMEWORK, "error cur when read from container");
        return res;
    }
    std::shared_ptr<Runtime> runtime = unifiedData.GetRuntime();
    if (runtime->privilege.pid != query.pid) {
        LOG_ERROR(UDMF_FRAMEWORK, "invalid caller");
        return E_INVALID_OPERATION;
    }
    return E_OK;
}

int32_t DataManager::GetSummary(QueryOption &query, Summary &summary)
{
    UnifiedKey key(query.key);
    std::shared_ptr<BaseDataStore> store = GetStore(key);
    if (store == nullptr) {
        LOG_ERROR(UDMF_FRAMEWORK, "invalid parameters %{public}s", key.key.c_str());
        return E_INVALID_PARAMETERS;
    }
    return store->RetrieveDataAbstract(key, summary);
}

int32_t DataManager::AddPrivilege(QueryOption &query, Privilege &privilege)
{
    std::string processName;
    PreProcessUtils utils = PreProcessUtils::GetInstance();
    if (!utils.GetNativeProcessNameByToken(query.tokenId, processName)) {
        LOG_ERROR(UDMF_FRAMEWORK, "%{public}s", utils.errorStr.c_str());
        return E_UNKNOWN;
    }
    UnifiedKey key(query.key);
    std::shared_ptr<BaseDataStore> store = GetStore(key);
    if (processName != authorizationMap_[key.intention]) {
        LOG_ERROR(UDMF_FRAMEWORK, "process: %{public}s have no permission", processName.c_str());
        return E_FORBIDDEN;
    }
    if (store == nullptr) {
        LOG_ERROR(UDMF_FRAMEWORK, "invalid parameters %{public}s", key.key.c_str());
        return E_INVALID_PARAMETERS;
    }
    return store->AddPrivilege(key, privilege);
}

std::shared_ptr<BaseDataStore> DataManager::GetStore(UnifiedKey &key)
{
    if (!key.IsValid()) {
        LOG_ERROR(UDMF_FRAMEWORK, "invalid key");
        return nullptr;
    }

    auto storeIt = storeMap_.find(key.intention);
    if (storeIt == storeMap_.end()) {
        LOG_ERROR(UDMF_FRAMEWORK, "invalid intention");
        return nullptr;
    }
    return storeIt->second;
}
} // namespace UDMF
} // namespace OHOS