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
constexpr int BASE_DECIMAL = 10;
int32_t ProgressSignalStub::OnRemoteRequest(uint32_t code,
    MessageParcel &data, MessageParcel &reply, MessageOption &option)
{
    std::u16string myDescriptor = ProgressSignalStub::GetDescriptor();
    std::u16string remoteDescriptor = data.ReadInterfaceToken();
    if (myDescriptor != remoteDescriptor) {
        LOG_ERROR(UDMF_SERVICE, "Descriptor checked fail");
        return E_ERROR;
    }
    pid_t pid = IPCSkeleton::GetCallingPid();
    LOG_INFO(UDMF_SERVICE, "CallingPid=%{public}d, code=%{public}u", pid, code);
    HandleProgressSignalValue(data);
    return E_OK;
}

void ProgressSignalCallback::HandleProgressSignalValue(MessageParcel &data)
{
    int32_t cancelStatus = 0;
    std::string signalValue = data.ReadString();

    char* end = nullptr;
    errno = 0;
    uint32_t convertResult = std::strtoul(signalValue.c_str(), &end, BASE_DECIMAL);
    if (errno == ERANGE || end == signalValue || *end != '\0') {
        LOG_ERROR(UDMF_CLIENT, "Failed to convert signalValue, signalValue=%{public}s", signalValue.c_str());
        return;
    }

    if (convertResult > INT32_MAX) {
        LOG_ERROR(UDMF_CLIENT, "Signal value exceeds int32_t range, convertResult=%{public}u", convertResult);
        return;
    }

    cancelStatus = static_cast<int32_t>(convertResult);

    switch (cancelStatus) {
        case NORMAL_PASTE:
            break;
        case CANCEL_PASTE:
            UdmfAsyncClient::GetInstance().CancelOnSingleTask();
            break;
        case PASTE_TIME_OUT:
            LOG_ERROR(UDMF_CLIENT, "Progress timed out");
            break;
        default:
            LOG_ERROR(UDMF_CLIENT, "status error, status=%{public}d", cancelStatus);
            break;
    }
}
} // namespace UDMF
} // namespace OHOS