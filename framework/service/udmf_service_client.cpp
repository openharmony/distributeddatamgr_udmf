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

#include "udmf_service_client.h"

#include "iservice_registry.h"
#include "system_ability_definition.h"

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
    kvDataServiceProxy_ = iface_cast<DistributedKv::IKvStoreDataService>(remote);
    if (kvDataServiceProxy_ == nullptr) {
        LOG_ERROR(UDMF_SERVICE, "initialize proxy failed.");
        return nullptr;
    }
    return kvDataServiceProxy_;
}

int32_t UdmfServiceClient::SetData(CustomOption &option, UnifiedData &unifiedData, std::string &key)
{
    LOG_INFO(UDMF_SERVICE, "start");
    return udmfProxy_->SetData(option, unifiedData, key);
}

int32_t UdmfServiceClient::GetData(const QueryOption &query, UnifiedData &unifiedData)
{
    LOG_INFO(UDMF_SERVICE, "start");
    return udmfProxy_->GetData(query, unifiedData);
}

int32_t UdmfServiceClient::GetBatchData(const QueryOption &query, std::vector<UnifiedData> &unifiedDataSet)
{
    LOG_INFO(UDMF_SERVICE, "start");
    return udmfProxy_->GetBatchData(query, unifiedDataSet);
}

int32_t UdmfServiceClient::UpdateData(const QueryOption &query, UnifiedData &unifiedData)
{
    LOG_INFO(UDMF_SERVICE, "start");
    return udmfProxy_->UpdateData(query, unifiedData);
}

int32_t UdmfServiceClient::DeleteData(const QueryOption &query, std::vector<UnifiedData> &unifiedDataSet)
{
    LOG_INFO(UDMF_SERVICE, "start");
    return udmfProxy_->DeleteData(query, unifiedDataSet);
}

int32_t UdmfServiceClient::GetSummary(const QueryOption &query, Summary &summary)
{
    LOG_INFO(UDMF_SERVICE, "start");
    return udmfProxy_->GetSummary(query, summary);
}

int32_t UdmfServiceClient::AddPrivilege(const QueryOption &query, Privilege &privilege)
{
    LOG_INFO(UDMF_SERVICE, "start");
    return udmfProxy_->AddPrivilege(query, privilege);
}

int32_t UdmfServiceClient::Sync(const QueryOption &query, const std::vector<std::string> &devices)
{
    LOG_INFO(UDMF_SERVICE, "start");
    return udmfProxy_->Sync(query, devices);
}
} // namespace UDMF
} // namespace OHOS