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
#define LOG_TAG "UtdServiceProxy"
#include "utd_service_proxy.h"

#include "logger.h"
#include "utd_tlv_util.h"

namespace OHOS {
namespace UDMF {
#define IPC_SEND(code, reply, ...)                                                           \
    ({                                                                                       \
        int32_t ipcStatus = E_OK;                                                            \
        do {                                                                                 \
            MessageParcel request;                                                           \
            if (!request.WriteInterfaceToken(GetDescriptor())) {                             \
                ipcStatus = E_WRITE_PARCEL_ERROR;                                            \
                break;                                                                       \
            }                                                                                \
            if (!ITypesUtil::Marshal(request, ##__VA_ARGS__)) {                              \
                ipcStatus = E_WRITE_PARCEL_ERROR;                                            \
                break;                                                                       \
            }                                                                                \
            MessageOption option;                                                            \
            auto result = SendRequest(code, request, reply, option);                         \
            if (result != 0) {                                                               \
                LOG_ERROR(UDMF_SERVICE, "SendRequest failed, result = %{public}d!", result); \
                ipcStatus = E_IPC;                                                           \
                break;                                                                       \
            }                                                                                \
                                                                                             \
            ITypesUtil::Unmarshal(reply, ipcStatus);                                         \
        } while (0);                                                                         \
        ipcStatus;                                                                           \
    })

UtdServiceProxy::UtdServiceProxy(sptr<IRemoteObject> object) : IRemoteProxy<IUtdService>(object)
{
}

int32_t UtdServiceProxy::SendRequest(UtdServiceInterfaceCode code, MessageParcel &data,
    MessageParcel &reply, MessageOption &option)
{
    sptr<IRemoteObject> remote = Remote();
    if (remote == nullptr) {
        return E_IPC;
    }
    int err = remote->SendRequest(static_cast<uint32_t>(code), data, reply, option);
    LOG_DEBUG(UDMF_SERVICE, "err: %{public}d", err);
    return err;
}

int32_t UtdServiceProxy::RegServiceNotifier(sptr<IRemoteObject> iUtdNotifier)
{
    MessageParcel reply;
    int32_t status = IPC_SEND(UtdServiceInterfaceCode::SET_UTD_NOTIFIER, reply, iUtdNotifier);
    if (status != E_OK) {
        LOG_ERROR(UDMF_SERVICE, "status:%{public}d", status);
        return status;
    }
    int32_t regStatus = static_cast<int32_t>(E_IPC);
    if (!ITypesUtil::Unmarshal(reply, regStatus)) {
        LOG_ERROR(UDMF_SERVICE, "Unmarshal status failed!");
        return E_READ_PARCEL_ERROR;
    }
    if (regStatus != E_OK) {
        LOG_ERROR(UDMF_SERVICE, "regStatus:%{public}d", regStatus);
        return regStatus;
    }
    return E_OK;
}

int32_t UtdServiceProxy::RegisterTypeDescriptors(const std::vector<TypeDescriptorCfg> &descriptors)
{
    MessageParcel reply;
    int32_t status = IPC_SEND(UtdServiceInterfaceCode::REGISTER_UTD_TYPES, reply, descriptors);
    if (status != E_OK) {
        LOG_ERROR(UDMF_SERVICE, "status:%{public}d", status);
        return status;
    }
    if (!ITypesUtil::Unmarshal(reply)) {
        LOG_ERROR(UDMF_SERVICE, "Unmarshal status failed!");
        return E_READ_PARCEL_ERROR;
    }
    return E_OK;
}

int32_t UtdServiceProxy::UnregisterTypeDescriptors(const std::vector<std::string> &typeIds)
{
    MessageParcel reply;
    int32_t status = IPC_SEND(UtdServiceInterfaceCode::UNREGISTER_UTD_TYPES, reply, typeIds);
    if (status != E_OK) {
        LOG_ERROR(UDMF_SERVICE, "status:%{public}d", status);
        return status;
    }
    if (!ITypesUtil::Unmarshal(reply)) {
        LOG_ERROR(UDMF_SERVICE, "Unmarshal status failed!");
        return E_READ_PARCEL_ERROR;
    }
    return E_OK;
}

} // namespace UDMF
} // namespace OHOS