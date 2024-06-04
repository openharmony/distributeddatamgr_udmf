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

#ifndef UDMF_SERVICE_CLIENT_H
#define UDMF_SERVICE_CLIENT_H

#include <mutex>
#include <string>

#include "ikvstore_data_service.h"
#include "iremote_object.h"
#include "udmf_service.h"
#include "udmf_service_proxy.h"

namespace OHOS {
namespace UDMF {
class UdmfServiceClient final : public UdmfService {
public:
    explicit UdmfServiceClient(const sptr<UdmfServiceProxy> &proxy);
    ~UdmfServiceClient() override = default;
    static std::shared_ptr<UdmfServiceClient> GetInstance();

    int32_t SetData(CustomOption &option, UnifiedData &unifiedData, std::string &key) override;
    int32_t GetData(const QueryOption &query, UnifiedData &unifiedData) override;
    int32_t GetBatchData(const QueryOption &query, std::vector<UnifiedData> &unifiedDataSet) override;
    int32_t UpdateData(const QueryOption &query, UnifiedData &unifiedData) override;
    int32_t DeleteData(const QueryOption &query, std::vector<UnifiedData> &unifiedDataSet) override;
    int32_t GetSummary(const QueryOption &query, Summary &summary) override;
    int32_t AddPrivilege(const QueryOption &query, Privilege &privilege) override;
    int32_t Sync(const QueryOption &query, const std::vector<std::string> &devices) override;
    int32_t IsRemoteData(const QueryOption &query, bool &result) override;
    int32_t SetAppShareOption(const std::string &intention, int32_t shareOption) override;
    int32_t GetAppShareOption(const std::string &intention, int32_t &shareOption) override;
    int32_t RemoveAppShareOption(const std::string &intention) override;

private:
    class ServiceDeathRecipient : public IRemoteObject::DeathRecipient {
    public:
        ServiceDeathRecipient();
        virtual ~ServiceDeathRecipient();

        void OnRemoteDied(const wptr<IRemoteObject> &remote) override;
    };

    static std::shared_ptr<UdmfServiceClient> instance_;
    static std::mutex mutex_;
    static sptr<DistributedKv::IKvStoreDataService> kvDataServiceProxy_;
    static sptr<DistributedKv::IKvStoreDataService> GetDistributedKvDataService();
    sptr<UdmfServiceProxy> udmfProxy_;
};
} // namespace UDMF
} // namespace OHOS
#endif // UDMF_SERVICE_CLIENT_H