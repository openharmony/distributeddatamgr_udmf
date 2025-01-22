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
#define LOG_TAG "ProcessCallback"
#include "progress_callback.h"

#include "error_code.h"
#include "ipc_skeleton.h"
#include "logger.h"
#include "udmf_async_client.h"


namespace OHOS {
namespace UDMF {
int32_t PasteboardSignalStub::OnRemoteRequest(uint32_t code, MessageParcel &data, MessageParcel &reply, MessageOption &option)
{
    std::u16string myDescriptor = PasteboardSignalStub::GetDescriptor();
    std::u16string remoteDescriptor = data.ReadInterfaceToken();
    if (myDescriptor != remoteDescriptor) {
        LOG_ERROR(UDMF_SERVICE, "Descriptor checked fail");
        return E_ERROR;
    }
    pid_t pid = IPCSkeleton::GetCallingPid();
    pid_t uid = IPCSkeleton::GetCallingUid();

    LOG_INFO(UDMF_SERVICE, "CallingPid=%{public}d, CallingUid=%{public}d, code=%{public}u", pid, uid, code);
    return HandleProgressSignalValue(data);

    return IPCObjectStub::OnRemoteRequest(code, data, reply, option);;
}

int32_t PasteboardSignalCallback::HandleProgressSignalValue(MessageParcel &data)
{
    std::string signalValue = data.ReadString();
    int32_t ret = UdmfAsyncClient::GetInstance().Cancel(signalValue);
    LOG_INFO(UDMF_SERVICE, "Cancel finished, ret=%{public}d.", ret);
    return ret;
}
} // namespace UDMF
} // namespace OHOS