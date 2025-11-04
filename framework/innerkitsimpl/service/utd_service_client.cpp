 /*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
#define LOG_TAG "UtdServiceClient"
#include "utd_service_client.h"

#include "iservice_registry.h"
#include "datamgr_service_proxy.h"
#include "system_ability_definition.h"
#include "logger.h"

namespace OHOS {
namespace UDMF {
std::shared_ptr<UtdServiceClient> UtdServiceClient::instance_;
std::mutex UtdServiceClient::mutex_;
sptr<DistributedKv::IKvStoreDataService> UtdServiceClient::kvDataServiceProxy_;

UtdServiceClient::UtdServiceClient(const sptr<UtdServiceProxy> &proxy) : utdProxy_(proxy)
{
    LOG_INFO(UDMF_SERVICE, "construct");
}

std::shared_ptr<UtdServiceClient> UtdServiceClient::GetInstance()
{
    std::lock_guard<decltype(mutex_)> lockGuard(mutex_);
    if (instance_ != nullptr) {
        return instance_;
    }
    sptr<DistributedKv::IKvStoreDataService> ability = GetDistributedKvDataService();
    if (ability == nullptr) {
        return nullptr;
    }
    sptr<IRemoteObject> service = ability->GetFeatureInterface("utd");
    if (service == nullptr) {
        return nullptr;
    }
    sptr<UtdServiceProxy> proxy = iface_cast<UtdServiceProxy>(service);
    if (proxy == nullptr) {
        return nullptr;
    }
    instance_ = std::make_shared<UtdServiceClient>(proxy);
    return instance_;
}

sptr<DistributedKv::IKvStoreDataService> UtdServiceClient::GetDistributedKvDataService()
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
    sptr<UtdServiceClient::ServiceDeathRecipient> deathRecipientPtr = new (std::nothrow)ServiceDeathRecipient();
    if (deathRecipientPtr == nullptr) {
        return nullptr;
    }
    if ((remote->IsProxyObject()) && (!remote->AddDeathRecipient(deathRecipientPtr))) {
        LOG_ERROR(UDMF_SERVICE, "Add death recipient fail!");
    }
    return kvDataServiceProxy_;
}

UtdServiceClient::ServiceDeathRecipient::ServiceDeathRecipient()
{
    LOG_INFO(UDMF_SERVICE, "Construct!");
}

UtdServiceClient::ServiceDeathRecipient::~ServiceDeathRecipient()
{
    LOG_INFO(UDMF_SERVICE, "Destruct!");
}

void UtdServiceClient::ServiceDeathRecipient::OnRemoteDied(const wptr<IRemoteObject> &remote)
{
    LOG_WARN(UDMF_SERVICE, "DistributedDataService die!");
    std::lock_guard<decltype(mutex_)> lockGuard(mutex_);
    kvDataServiceProxy_ = nullptr;
    instance_ = nullptr;
}

int32_t UtdServiceClient::RegServiceNotifier(sptr<IRemoteObject> iUtdNotifier)
{
    return utdProxy_->RegServiceNotifier(iUtdNotifier);
}

int32_t UtdServiceClient::RegisterTypeDescriptors(const std::vector<TypeDescriptorCfg> &descriptors)
{
    return utdProxy_->RegisterTypeDescriptors(descriptors);
}

int32_t UtdServiceClient::UnregisterTypeDescriptors(const std::vector<std::string> &typeIds)
{
    return utdProxy_->UnregisterTypeDescriptors(typeIds);
}

} // namespace UDMF
} // namespace OHOS