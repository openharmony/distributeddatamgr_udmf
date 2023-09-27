/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "udmf_service_proxy.h"

#include "ipc_types.h"

#include "logger.h"
#include "tlv_util.h"
#include "udmf_types_util.h"

namespace OHOS {
namespace UDMF {
#define IPC_SEND(code, reply, ...)                                                           \
    ({                                                                                       \
        int32_t __status = E_OK;                                                             \
        do {                                                                                 \
            MessageParcel request;                                                           \
            if (!request.WriteInterfaceToken(GetDescriptor())) {                             \
                __status = E_WRITE_PARCEL_ERROR;                                             \
                break;                                                                       \
            }                                                                                \
            if (!ITypesUtil::Marshal(request, ##__VA_ARGS__)) {                              \
                __status = E_WRITE_PARCEL_ERROR;                                             \
                break;                                                                       \
            }                                                                                \
            MessageOption option;                                                            \
            auto result = SendRequest(code, request, reply, option);                         \
            if (result != 0) {                                                               \
                LOG_ERROR(UDMF_SERVICE, "SendRequest failed, result = %{public}d!", result); \
                __status = E_IPC;                                                            \
                break;                                                                       \
            }                                                                                \
                                                                                             \
            ITypesUtil::Unmarshal(reply, __status);                                          \
        } while (0);                                                                         \
        __status;                                                                            \
    })

UdmfServiceProxy::UdmfServiceProxy(const sptr<IRemoteObject> &object) : IRemoteProxy<IUdmfService>(object)
{
}

int32_t UdmfServiceProxy::SetData(CustomOption &option, UnifiedData &unifiedData, std::string &key)
{
    MessageParcel reply;
    int32_t status = IPC_SEND(UdmfServiceInterfaceCode::SET_DATA, reply, option, unifiedData);
    if (status != E_OK) {
        LOG_ERROR(UDMF_SERVICE, "status:0x%{public}x!", status);
        return status;
    }
    if (!ITypesUtil::Unmarshal(reply, key)) {
        LOG_ERROR(UDMF_SERVICE, "Unmarshal status failed!");
        return E_READ_PARCEL_ERROR;
    }
    return status;
}

int32_t UdmfServiceProxy::GetData(const QueryOption &query, UnifiedData &unifiedData)
{
    MessageParcel reply;
    int32_t status = IPC_SEND(UdmfServiceInterfaceCode::GET_DATA, reply, query);
    if (status != E_OK) {
        LOG_ERROR(UDMF_SERVICE, "status:0x%{public}x, key:%{public}s!", status, query.key.c_str());
        return status;
    }
    if (!ITypesUtil::Unmarshal(reply, unifiedData)) {
        LOG_ERROR(UDMF_SERVICE, "Unmarshal UnifiedData failed!");
        return E_READ_PARCEL_ERROR;
    }
    return status;
}

int32_t UdmfServiceProxy::GetBatchData(const QueryOption &query, std::vector<UnifiedData> &unifiedDataSet)
{
    MessageParcel reply;
    int32_t status = IPC_SEND(UdmfServiceInterfaceCode::GET_BATCH_DATA, reply, query);
    if (status != E_OK) {
        LOG_ERROR(UDMF_SERVICE, "status:0x%{public}x, key:%{public}s, intention:%{public}d!", status,
                  query.key.c_str(), query.intention);
        return status;
    }
    if (!ITypesUtil::Unmarshal(reply, unifiedDataSet)) {
        LOG_ERROR(UDMF_SERVICE, "Unmarshal unifiedDataSet failed!");
        return E_READ_PARCEL_ERROR;
    }
    return status;
}

int32_t UdmfServiceProxy::UpdateData(const QueryOption &query, UnifiedData &unifiedData)
{
    MessageParcel reply;
    int32_t status = IPC_SEND(UdmfServiceInterfaceCode::UPDATE_DATA, reply, query, unifiedData);
    if (status != E_OK) {
        LOG_ERROR(UDMF_SERVICE, "status:0x%{public}x!", status);
        return status;
    }
    return status;
}

int32_t UdmfServiceProxy::DeleteData(const QueryOption &query, std::vector<UnifiedData> &unifiedDataSet)
{
    MessageParcel reply;
    int32_t status = IPC_SEND(UdmfServiceInterfaceCode::DELETE_DATA, reply, query);
    if (status != E_OK) {
        LOG_ERROR(UDMF_SERVICE, "status:0x%{public}x,key: %{public}s, intention:%{public}s", status, query.key.c_str(),
                  UD_INTENTION_MAP.at(query.intention).c_str());
        return status;
    }
    if (!ITypesUtil::Unmarshal(reply, unifiedDataSet)) {
        LOG_ERROR(UDMF_SERVICE, "Unmarshal unifiedDataSet failed!");
        return E_READ_PARCEL_ERROR;
    }
    LOG_DEBUG(UDMF_SERVICE, "end.");
    return status;
}

int32_t UdmfServiceProxy::GetSummary(const QueryOption &query, Summary &summary)
{
    MessageParcel reply;
    int32_t status = IPC_SEND(UdmfServiceInterfaceCode::GET_SUMMARY, reply, query);
    if (status != E_OK) {
        LOG_ERROR(UDMF_SERVICE, "status:0x%{public}x, key:%{public}s!", status, query.key.c_str());
        return status;
    }
    if (!ITypesUtil::Unmarshal(reply, summary)) {
        LOG_ERROR(UDMF_SERVICE, "Unmarshal summary failed!");
        return E_READ_PARCEL_ERROR;
    }
    LOG_DEBUG(UDMF_SERVICE, "end.");
    return status;
}

int32_t UdmfServiceProxy::AddPrivilege(const QueryOption &query, Privilege &privilege)
{
    MessageParcel reply;
    int32_t status = IPC_SEND(UdmfServiceInterfaceCode::ADD_PRIVILEGE, reply, query, privilege);
    if (status != E_OK) {
        LOG_ERROR(UDMF_SERVICE, "status:0x%{public}x, key:%{public}s", status, query.key.c_str());
    }
    LOG_DEBUG(UDMF_SERVICE, "end.");
    return status;
}

int32_t UdmfServiceProxy::Sync(const QueryOption &query, const std::vector<std::string> &devices)
{
    MessageParcel reply;
    int32_t status = IPC_SEND(UdmfServiceInterfaceCode::SYNC, reply, query, devices);
    if (status != E_OK) {
        LOG_ERROR(UDMF_SERVICE, "status:0x%{public}x, key:%{public}s", status, query.key.c_str());
    }
    LOG_DEBUG(UDMF_SERVICE, "end.");
    return status;
}

int32_t UdmfServiceProxy::SendRequest(UdmfServiceInterfaceCode code, MessageParcel &data,
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
} // namespace UDMF
} // namespace OHOS