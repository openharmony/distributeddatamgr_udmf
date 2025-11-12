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

#ifndef UTD_SERVICE_PROXY_H
#define UTD_SERVICE_PROXY_H

#include <string>

#include "distributeddata_udmf_ipc_interface_code.h"
#include "iremote_broker.h"
#include "iremote_proxy.h"
#include "utd_service.h"

namespace OHOS {
namespace UDMF {
class IUtdService : public UtdService, public IRemoteBroker {};

class UtdServiceProxy : public IRemoteProxy<IUtdService> {
public:
    explicit UtdServiceProxy(sptr<IRemoteObject> object);

    int32_t RegServiceNotifier(sptr<IRemoteObject> iUtdNotifier) override;
    int32_t RegisterTypeDescriptors(const std::vector<TypeDescriptorCfg> &descriptors) override;
    int32_t UnregisterTypeDescriptors(const std::vector<std::string> &typeIds) override;

private:
    static inline BrokerDelegator<UtdServiceProxy> delegator_;
    int32_t SendRequest(UtdServiceInterfaceCode code, MessageParcel &data,
                        MessageParcel &reply, MessageOption &option);
};
} // namespace UDMF
} // namespace OHOS
#endif // UTD_SERVICE_PROXY_H
