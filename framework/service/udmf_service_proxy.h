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

#ifndef UDMF_SERVICE_PROXY_H
#define UDMF_SERVICE_PROXY_H

#include <string>

#include "iremote_broker.h"
#include "iremote_proxy.h"

#include "udmf_service.h"

namespace OHOS {
namespace UDMF {
class IUdmfService : public UdmfService, public IRemoteBroker {
public:
    using UdmfService::UdmfService;
};

class UdmfServiceProxy : public IRemoteProxy<IUdmfService> {
public:
    explicit UdmfServiceProxy(const sptr<IRemoteObject> &object);

    int32_t SetData(CustomOption &option, UnifiedData &unifiedData, std::string &key) override;
    int32_t GetData(QueryOption &query, UnifiedData &unifiedData) override;
    int32_t GetSummary(QueryOption &query, Summary &summary) override;
    int32_t AddPrivilege(QueryOption &query, Privilege &privilege) override;

private:
    static inline BrokerDelegator<UdmfServiceProxy> delegator_;
    int32_t SendRequest(FCode code, MessageParcel &data, MessageParcel &reply, MessageOption &option);
};
} // namespace UDMF
} // namespace OHOS
#endif // UDMF_SERVICE_PROXY_H