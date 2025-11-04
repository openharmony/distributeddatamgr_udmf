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

#ifndef UTD_SERVICE_CLIENT_H
#define UTD_SERVICE_CLIENT_H

#include <mutex>
#include <string>
#include "ikvstore_data_service.h"
#include "iremote_object.h"
#include "utd_service.h"
#include "utd_service_proxy.h"

namespace OHOS {
namespace UDMF {
class UtdServiceClient final : public UtdService {
public:
    static std::shared_ptr<UtdServiceClient> GetInstance();
    int32_t RegServiceNotifier(sptr<IRemoteObject> iUtdNotifier) override;
    int32_t RegisterTypeDescriptors(const std::vector<TypeDescriptorCfg> &descriptors) override;
    int32_t UnregisterTypeDescriptors(const std::vector<std::string> &typeIds) override;

    explicit UtdServiceClient(const sptr<UtdServiceProxy> &proxy);
    ~UtdServiceClient() override = default;
private:
    static sptr<DistributedKv::IKvStoreDataService> GetDistributedKvDataService();

    class ServiceDeathRecipient : public IRemoteObject::DeathRecipient {
    public:
        ServiceDeathRecipient();
        virtual ~ServiceDeathRecipient();

        void OnRemoteDied(const wptr<IRemoteObject> &remote) override;
    };

    static std::shared_ptr<UtdServiceClient> instance_;
    static std::mutex mutex_;
    static sptr<DistributedKv::IKvStoreDataService> kvDataServiceProxy_;
    sptr<UtdServiceProxy> utdProxy_;
};
} // namespace UDMF
} // namespace OHOS
#endif // UTD_SERVICE_CLIENT_H
