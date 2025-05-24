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

#ifndef UDMF_NOTIFIER_STUB_H
#define UDMF_NOTIFIER_STUB_H

#include <functional>
#include <iremote_stub.h>
#include "iudmf_notifier.h"
#include "unified_data.h"

namespace OHOS {
namespace UDMF {

class UdmfNotifierStub : public IRemoteStub<IUdmfNotifier> {
public:
    int32_t OnRemoteRequest(uint32_t code, MessageParcel &data, MessageParcel &reply, MessageOption &option) override;
};

class UdmfNotifierClient : public UdmfNotifierStub {
public:
    UdmfNotifierClient(LoadHandler loadHandler_);
    virtual ~UdmfNotifierClient() = default;

    void HandleDelayObserver(const std::string &key, const DataLoadInfo &dataLoadInfo) override;

private:
    LoadHandler loadHandler_;
};

class DelayDataCallbackStub : public IRemoteStub<IDelayDataCallback> {
public:
    int32_t OnRemoteRequest(uint32_t code, MessageParcel &data, MessageParcel &reply, MessageOption &option) override;
};

class DelayDataCallbackClient : public DelayDataCallbackStub {
public:
    using DataCallback = std::function<void(const std::string &udKey, const UnifiedData &unifiedData)>;

    DelayDataCallbackClient(DataCallback dataCallback);
    virtual ~DelayDataCallbackClient() = default;
    void DelayDataCallback(const std::string &key, const UnifiedData &data) override;

private:
    DataCallback dataCallback_;
};


} // namespace UDMF
} // namespace OHOS
#endif // UDMF_NOTIFIER_STUB_H