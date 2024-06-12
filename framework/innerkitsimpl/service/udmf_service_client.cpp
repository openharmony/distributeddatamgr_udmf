/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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
#define LOG_TAG "UdmfServiceClient"
#include "udmf_service_client.h"

#include "iservice_registry.h"
#include "datamgr_service_proxy.h"
#include "system_ability_definition.h"
#include "unified_data_helper.h"

#include "logger.h"

namespace OHOS {
namespace UDMF {
std::shared_ptr<UdmfServiceClient> UdmfServiceClient::instance_;
std::mutex UdmfServiceClient::mutex_;
sptr<DistributedKv::IKvStoreDataService> UdmfServiceClient::kvDataServiceProxy_;

UdmfServiceClient::UdmfServiceClient(const sptr<UdmfServiceProxy> &proxy) : udmfProxy_(proxy)
{
    LOG_INFO(UDMF_SERVICE, "construct");
}

std::shared_ptr<UdmfServiceClient> UdmfServiceClient::GetInstance()
{
    std::lock_guard<decltype(mutex_)> lockGuard(mutex_);
    if (instance_ != nullptr) {
        return instance_;
    }
    sptr<DistributedKv::IKvStoreDataService> ability = GetDistributedKvDataService();
    if (ability == nullptr) {
        return nullptr;
    }
    sptr<IRemoteObject> service = ability->GetFeatureInterface("udmf");
    if (service == nullptr) {
        return nullptr;
    }
    sptr<UdmfServiceProxy> proxy = iface_cast<UdmfServiceProxy>(service);
    if (proxy == nullptr) {
        return nullptr;
    }
    instance_ = std::make_shared<UdmfServiceClient>(proxy);
    return instance_;
}

sptr<DistributedKv::IKvStoreDataService> UdmfServiceClient::GetDistributedKvDataService()
{
    if (kvDataServiceProxy_ != nullptr) {
        return kvDataServiceProxy_;
    }
    LOG_INFO(UDMF_SERVICE, "create remote proxy.");
    auto samgr = SystemAbilityManagerClient::GetInstance().GetSystemAbilityManager();
    if (samgr == nullptr) {
        LOG_ERROR(UDMF_SERVICE, "get samgr fail.");
        return nullptr;
    }

    auto remote = samgr->CheckSystemAbility(DISTRIBUTED_KV_DATA_SERVICE_ABILITY_ID);
    kvDataServiceProxy_ = iface_cast<DistributedKv::DataMgrServiceProxy>(remote);
    if (kvDataServiceProxy_ == nullptr) {
        LOG_ERROR(UDMF_SERVICE, "initialize proxy failed.");
        return nullptr;
    }
    sptr<UdmfServiceClient::ServiceDeathRecipient> deathRecipientPtr = new (std::nothrow)ServiceDeathRecipient();
    if (deathRecipientPtr == nullptr) {
        return nullptr;
    }
    if ((remote->IsProxyObject()) && (!remote->AddDeathRecipient(deathRecipientPtr))) {
        LOG_ERROR(UDMF_SERVICE, "Add death recipient fail!");
    }
    return kvDataServiceProxy_;
}

UdmfServiceClient::ServiceDeathRecipient::ServiceDeathRecipient()
{
    LOG_INFO(UDMF_SERVICE, "Construct!");
}

UdmfServiceClient::ServiceDeathRecipient::~ServiceDeathRecipient()
{
    LOG_INFO(UDMF_SERVICE, "Destruct!");
}

void UdmfServiceClient::ServiceDeathRecipient::OnRemoteDied(const wptr<IRemoteObject> &remote)
{
    LOG_WARN(UDMF_SERVICE, "DistributedDataService die!");
    std::lock_guard<decltype(mutex_)> lockGuard(mutex_);
    kvDataServiceProxy_ = nullptr;
    instance_ = nullptr;
}

int32_t UdmfServiceClient::SetData(CustomOption &option, UnifiedData &unifiedData, std::string &key)
{
    LOG_DEBUG(UDMF_SERVICE, "start, tag: %{public}d", option.intention);
    if (!UnifiedDataUtils::IsValidIntention(option.intention)) {
        LOG_ERROR(UDMF_SERVICE, "Invalid intention");
        return E_INVALID_PARAMETERS;
    }

    if (!unifiedData.IsValid()) {
        LOG_ERROR(UDMF_SERVICE, "UnifiedData is invalid.");
        return E_INVALID_PARAMETERS;
    }
    if (UnifiedDataHelper::ExceedKVSizeLimit(unifiedData)) {
        if (!UnifiedDataHelper::Pack(unifiedData)) {
            LOG_ERROR(UDMF_SERVICE, "Failed to pack unified data.");
            return E_FS_ERROR;
        }
    }
    return udmfProxy_->SetData(option, unifiedData, key);
}

int32_t UdmfServiceClient::GetData(const QueryOption &query, UnifiedData &unifiedData)
{
    LOG_DEBUG(UDMF_SERVICE, "start, tag: %{public}s", query.key.c_str());
    UnifiedKey key(query.key);
    if (!key.IsValid()) {
        LOG_ERROR(UDMF_SERVICE, "invalid key");
        return E_INVALID_PARAMETERS;
    }

    auto err = udmfProxy_->GetData(query, unifiedData);
    if (err == E_OK) {
        if (UnifiedDataHelper::IsTempUData(unifiedData)) {
            if (!UnifiedDataHelper::Unpack(unifiedData)) {
                LOG_ERROR(UDMF_SERVICE, "failed to unpack unified data");
                return E_FS_ERROR;
            }
        }
    }
    return err;
}

int32_t UdmfServiceClient::GetBatchData(const QueryOption &query, std::vector<UnifiedData> &unifiedDataSet)
{
    LOG_DEBUG(UDMF_SERVICE, "start, tag: intention = %{public}d, key = %{public}s", query.intention, query.key.c_str());
    auto find = UD_INTENTION_MAP.find(query.intention);
    std::string intention = find == UD_INTENTION_MAP.end() ? intention : find->second;
    if (!UnifiedDataUtils::IsValidOptions(query.key, intention)) {
        LOG_ERROR(UDMF_SERVICE, "invalid option, query.key: %{public}s, intention: %{public}s", query.key.c_str(),
            intention.c_str());
        return E_INVALID_PARAMETERS;
    }
    std::vector<UnifiedData> tempDataSet {};
    auto err = udmfProxy_->GetBatchData(query, tempDataSet);
    if (err != E_OK) {
        return err;
    }
    for (auto &data : tempDataSet) {
        if (UnifiedDataHelper::IsTempUData(data)) {
            if (!UnifiedDataHelper::Unpack(data)) {
                LOG_ERROR(UDMF_SERVICE, "failed to unpack unified data");
                return E_FS_ERROR;
            }
        }
        unifiedDataSet.emplace_back(data);
    }
    return E_OK;
}

int32_t UdmfServiceClient::UpdateData(const QueryOption &query, UnifiedData &unifiedData)
{
    LOG_DEBUG(UDMF_SERVICE, "start, tag: %{public}s", query.key.c_str());
    UnifiedKey key(query.key);
    if (!key.IsValid() || !UnifiedDataUtils::IsPersist(key.intention)) {
        LOG_ERROR(UDMF_SERVICE, "invalid key, key.intention: %{public}s", key.intention.c_str());
        return E_INVALID_PARAMETERS;
    }

    if (!unifiedData.IsValid()) {
        LOG_ERROR(UDMF_SERVICE, "UnifiedData is invalid.");
        return E_INVALID_PARAMETERS;
    }
    if (UnifiedDataHelper::ExceedKVSizeLimit(unifiedData)) {
        if (!UnifiedDataHelper::Pack(unifiedData)) {
            LOG_ERROR(UDMF_SERVICE, "Failed to pack unified data.");
            return E_FS_ERROR;
        }
    }
    return udmfProxy_->UpdateData(query, unifiedData);
}

int32_t UdmfServiceClient::DeleteData(const QueryOption &query, std::vector<UnifiedData> &unifiedDataSet)
{
    LOG_DEBUG(UDMF_SERVICE, "start, tag: intention = %{public}d, key = %{public}s", query.intention, query.key.c_str());
    auto find = UD_INTENTION_MAP.find(query.intention);
    std::string intention = find == UD_INTENTION_MAP.end() ? intention : find->second;
    if (!UnifiedDataUtils::IsValidOptions(query.key, intention)) {
        LOG_ERROR(UDMF_SERVICE, "invalid option, query.key: %{public}s, intention: %{public}s", query.key.c_str(),
            intention.c_str());
        return E_INVALID_PARAMETERS;
    }
    return udmfProxy_->DeleteData(query, unifiedDataSet);
}

int32_t UdmfServiceClient::GetSummary(const QueryOption &query, Summary &summary)
{
    LOG_DEBUG(UDMF_SERVICE, "start, tag: %{public}s", query.key.c_str());
    UnifiedKey key(query.key);
    if (!key.IsValid()) {
        LOG_ERROR(UDMF_SERVICE, "invalid key");
        return E_INVALID_PARAMETERS;
    }
    return udmfProxy_->GetSummary(query, summary);
}

int32_t UdmfServiceClient::AddPrivilege(const QueryOption &query, Privilege &privilege)
{
    LOG_DEBUG(UDMF_SERVICE, "start, key: %{public}s", query.key.c_str());
    UnifiedKey key(query.key);
    if (!key.IsValid()) {
        LOG_ERROR(UDMF_SERVICE, "invalid key");
        return E_INVALID_PARAMETERS;
    }
    return udmfProxy_->AddPrivilege(query, privilege);
}

int32_t UdmfServiceClient::Sync(const QueryOption &query, const std::vector<std::string> &devices)
{
    LOG_DEBUG(UDMF_SERVICE, "start, key: %{public}s", query.key.c_str());
    UnifiedKey key(query.key);
    if (!key.IsValid()) {
        LOG_ERROR(UDMF_SERVICE, "invalid key");
        return E_INVALID_PARAMETERS;
    }
    return udmfProxy_->Sync(query, devices);
}

int32_t UdmfServiceClient::IsRemoteData(const QueryOption &query, bool &result)
{
    LOG_DEBUG(UDMF_SERVICE, "start, key: %{public}s", query.key.c_str());
    UnifiedKey key(query.key);
    if (!key.IsValid()) {
        LOG_ERROR(UDMF_SERVICE, "invalid key");
        return E_INVALID_PARAMETERS;
    }
    return udmfProxy_->IsRemoteData(query, result);
}

int32_t UdmfServiceClient::SetAppShareOption(const std::string &intention, int32_t shareOption)
{
    LOG_DEBUG(UDMF_SERVICE, "start, intention: %{public}s, shareOption: %{public}d",
              intention.c_str(), shareOption);
    if (intention.empty() || shareOption < IN_APP || shareOption > CROSS_APP) {
        LOG_ERROR(UDMF_SERVICE, "invalid parameters");
        return E_INVALID_PARAMETERS;
    }
    return udmfProxy_->SetAppShareOption(intention, shareOption);
}

int32_t UdmfServiceClient::GetAppShareOption(const std::string &intention, int32_t &shareOption)
{
    LOG_DEBUG(UDMF_SERVICE, "start, intention: %{public}s", intention.c_str());
    if (intention.empty()) {
        LOG_ERROR(UDMF_SERVICE, "invalid parameters");
        return E_INVALID_PARAMETERS;
    }
    return udmfProxy_->GetAppShareOption(intention, shareOption);
}

int32_t UdmfServiceClient::RemoveAppShareOption(const std::string &intention)
{
    LOG_DEBUG(UDMF_SERVICE, "start, intention: %{public}s", intention.c_str());
    if (intention.empty()) {
        LOG_ERROR(UDMF_SERVICE, "invalid parameters");
        return E_INVALID_PARAMETERS;
    }
    return udmfProxy_->RemoveAppShareOption(intention);
}
} // namespace UDMF
} // namespace OHOS