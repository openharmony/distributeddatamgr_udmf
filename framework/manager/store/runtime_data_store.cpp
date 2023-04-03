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

#include "runtime_data_store.h"

#include "error_code.h"
#include "logger.h"
#include "preprocess_utils.h"
#include "unified_data.h"
#include "unified_meta.h"

namespace OHOS {
namespace UDMF {
static const UDStoreMeta UD_Store_Meta[UD_INTENTION_SYS] = { { {}, RUNTIME, { OVERWRITE, { true } } } };

int32_t RuntimeDataStore::SaveData(CustomOption &option, UnifiedData &unifiedData, std::string &key)
{
    // imput runtime info before put it into store
    PreProcessUtils utils = PreProcessUtils::GetInstance();
    if (!utils.RuntimeDataImputation(unifiedData, option)) {
        LOG_ERROR(UDMF_FRAMEWORK, "imputation failed, %{public}s", utils.errorStr.c_str());
        return E_UNKNOWN;
    }
    std::shared_ptr<Runtime> runtime = unifiedData.GetRuntime();
    auto iterator = containerMap_.find(runtime->key.intention);
    if (iterator == containerMap_.end()) {
        UDStoreMeta storeMeta = UD_Store_Meta[option.intention];
        containerMap_[runtime->key.intention] = std::make_shared<RuntimeDataContainer>(storeMeta.containerMeta);
    }
    for (const std::shared_ptr<UnifiedRecord> &record : unifiedData.GetRecords()) {
        record->SetUid(PreProcessUtils::GetInstance().IdGenerator());
    }
    if (containerMap_[runtime->key.intention]->InsertData(unifiedData) != E_OK) {
        LOG_ERROR(UDMF_FRAMEWORK, "error cur when write into container");
        return E_ERROR;
    }
    key = runtime->key.GetUnifiedKey();
    return E_OK;
}

int32_t RuntimeDataStore::Update(UnifiedKey &key, UnifiedData &unifiedData)
{
    std::shared_ptr<BaseDataContainer> container = GetContainer(key);
    if (container == nullptr) {
        LOG_ERROR(UDMF_FRAMEWORK, "invalid parameters %{public}s", key.key.c_str());
        return E_INVALID_PARAMETERS;
    }
    return container->UpdateData(key.groupId, unifiedData);
}

int32_t RuntimeDataStore::RetrieveData(UnifiedKey &key, UnifiedData &unifiedData)
{
    std::shared_ptr<BaseDataContainer> container = GetContainer(key);
    if (container == nullptr) {
        LOG_ERROR(UDMF_FRAMEWORK, "invalid parameters %{public}s", key.key.c_str());
        return E_INVALID_PARAMETERS;
    }
    int32_t status = container->GetData(unifiedData);
    if (status != E_OK) {
        return status;
    }
    if (container->GetMode().lifeCycle.useOnlyOnce) {
        LOG_DEBUG(UDMF_FRAMEWORK, "clear after read");
        container->Clear();
    }
    return E_OK;
}

int32_t RuntimeDataStore::RetrieveDataAbstract(UnifiedKey &key, Summary &summary)
{
    std::shared_ptr<BaseDataContainer> container = GetContainer(key);
    if (container == nullptr) {
        LOG_ERROR(UDMF_FRAMEWORK, "invalid parameters %{public}s", key.key.c_str());
        return E_INVALID_PARAMETERS;
    }
    UnifiedData unifiedData;
    int32_t status = container->GetData(unifiedData);
    if (status != E_OK) {
        return status;
    }
    for (const std::shared_ptr<UnifiedRecord> &record : unifiedData.GetRecords()) {
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

int32_t RuntimeDataStore::AddPrivilege(UnifiedKey &key, Privilege &privilege)
{
    std::shared_ptr<BaseDataContainer> container = GetContainer(key);
    if (container == nullptr) {
        LOG_ERROR(UDMF_FRAMEWORK, "invalid parameters %{public}s", key.key.c_str());
        return E_INVALID_PARAMETERS;
    }
    UnifiedData unifiedData;
    int32_t status = container->GetData(unifiedData);
    if (status != E_OK) {
        return status;
    }
    unifiedData.GetRuntime()->privilege = privilege;
    return E_OK;
}

int32_t RuntimeDataStore::Clear(UnifiedKey &key)
{
    std::shared_ptr<BaseDataContainer> container = GetContainer(key);
    if (container == nullptr) {
        LOG_ERROR(UDMF_FRAMEWORK, "invalid parameters %{public}s", key.key.c_str());
        return E_INVALID_PARAMETERS;
    }
    return container->Clear();
}

std::shared_ptr<BaseDataContainer> RuntimeDataStore::GetContainer(UnifiedKey &key)
{
    auto iterator = containerMap_.find(key.intention);
    if (iterator == containerMap_.end()) {
        return nullptr;
    }
    return iterator->second;
}
} // namespace UDMF
} // namespace OHOS
