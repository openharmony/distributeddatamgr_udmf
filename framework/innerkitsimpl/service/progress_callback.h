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

#ifndef OHOS_PROGRESS_CALLBACK_H
#define OHOS_PROGRESS_CALLBACK_H

#include <iremote_broker.h>
#include <iremote_stub.h>

namespace OHOS {
namespace UDMF {

class IPasteboardSignal : public IRemoteBroker {
public:
    IPasteboardSignal() = default;
    virtual ~IPasteboardSignal() override = default;

    DECLARE_INTERFACE_DESCRIPTOR(u"ohos.miscservices.dialog.callback");
    virtual void HandleProgressSignalValue(MessageParcel &data) = 0;
};

class PasteboardSignalStub : public IRemoteStub<IPasteboardSignal> {
public:
    PasteboardSignalStub() = default;
    virtual ~PasteboardSignalStub() override = default;

    int32_t OnRemoteRequest(uint32_t code, MessageParcel &data, MessageParcel &reply, MessageOption &option) override;
private:
};

class PasteboardSignalCallback : public PasteboardSignalStub {
public:
    PasteboardSignalCallback() = default;
    virtual ~PasteboardSignalCallback() override = default;

    void HandleProgressSignalValue(MessageParcel &data) override;
};
} // namespace UDMF
} // namespace OHOS
#endif // OHOS_PROGRESS_CALLBACK_H