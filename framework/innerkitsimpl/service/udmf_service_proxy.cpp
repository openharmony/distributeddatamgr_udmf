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
#define LOG_TAG "UdmfServiceProxy"
#include "udmf_service_proxy.h"

#include "logger.h"
#include "udmf_types_util.h"
#include "udmf_conversion.h"

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

UdmfServiceProxy::UdmfServiceProxy(const sptr<IRemoteObject> &object) : IRemoteProxy<IUdmfService>(object)
{
}

int32_t UdmfServiceProxy::SetData(CustomOption &option, UnifiedData &unifiedData, std::string &key)
{
    UdmfConversion::InitValueObject(unifiedData);
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
    UdmfConversion::ConvertRecordToSubclass(unifiedData);
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
    UdmfConversion::ConvertRecordToSubclass(unifiedDataSet);
    return status;
}

int32_t UdmfServiceProxy::UpdateData(const QueryOption &query, UnifiedData &unifiedData)
{
    UdmfConversion::InitValueObject(unifiedData);
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
        LOG_ERROR(UDMF_SERVICE, "status:0x%{public}x,key: %{public}s, intention:%{public}d", status, query.key.c_str(),
                  query.intention);
        return status;
    }
    if (!ITypesUtil::Unmarshal(reply, unifiedDataSet)) {
        LOG_ERROR(UDMF_SERVICE, "Unmarshal unifiedDataSet failed!");
        return E_READ_PARCEL_ERROR;
    }
    UdmfConversion::ConvertRecordToSubclass(unifiedDataSet);
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

int32_t UdmfServiceProxy::IsRemoteData(const QueryOption &query, bool &result)
{
    MessageParcel reply;
    int32_t status = IPC_SEND(UdmfServiceInterfaceCode::IS_REMOTE_DATA, reply, query);
    if (status != E_OK) {
        LOG_ERROR(UDMF_SERVICE, "status:0x%{public}x, key:%{public}s!", status, query.key.c_str());
        return status;
    }
    if (!ITypesUtil::Unmarshal(reply, result)) {
        LOG_ERROR(UDMF_SERVICE, "Unmarshal result failed!");
        return E_READ_PARCEL_ERROR;
    }
    return status;
}

int32_t UdmfServiceProxy::SetAppShareOption(const std::string &intention, int32_t shareOption)
{
    MessageParcel reply;
    int32_t status = IPC_SEND(UdmfServiceInterfaceCode::SET_APP_SHARE_OPTION, reply, intention, shareOption);
    if (status != E_OK) {
        LOG_ERROR(UDMF_SERVICE, "status:0x%{public}x!", status);
        return status;
    }
    LOG_DEBUG(UDMF_SERVICE, "end.");
    return status;
}

int32_t UdmfServiceProxy::GetAppShareOption(const std::string &intention, int32_t &shareOption)
{
    MessageParcel reply;
    int32_t status = IPC_SEND(UdmfServiceInterfaceCode::GET_APP_SHARE_OPTION, reply, intention);
    if (status != E_OK) {
        LOG_WARN(UDMF_SERVICE, "status:0x%{public}x!", status);
        return status;
    }

    if (!ITypesUtil::Unmarshal(reply, shareOption)) {
        LOG_ERROR(UDMF_SERVICE, "Unmarshal shareOption failed!");
        return E_READ_PARCEL_ERROR;
    }
    LOG_DEBUG(UDMF_SERVICE, "end.");
    return status;
}

int32_t UdmfServiceProxy::RemoveAppShareOption(const std::string &intention)
{
    MessageParcel reply;
    int32_t status = IPC_SEND(UdmfServiceInterfaceCode::REMOVE_APP_SHARE_OPTION, reply, intention);
    if (status != E_OK) {
        LOG_ERROR(UDMF_SERVICE, "status:0x%{public}x!", status);
        return status;
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

int32_t UdmfServiceProxy::ObtainAsynProcess(AsyncProcessInfo &processInfo)
{
    MessageParcel reply;
    int32_t status = IPC_SEND(UdmfServiceInterfaceCode::OBTAIN_ASYN_PROCESS, reply, processInfo);
    if (status != E_OK) {
        LOG_ERROR(UDMF_SERVICE, "status:0x%{public}x", status);
        return status;
    }
    if (!ITypesUtil::Unmarshal(reply, processInfo)) {
        LOG_ERROR(UDMF_SERVICE, "Unmarshal AsyncProcessInfo failed!");
        return E_READ_PARCEL_ERROR;
    }
    return E_OK;
}

int32_t UdmfServiceProxy::ClearAsynProcessByKey(const std::string &businessUdKey)
{
    MessageParcel reply;
    int32_t status = IPC_SEND(UdmfServiceInterfaceCode::CLEAR_ASYN_PROCESS_BY_KEY, reply, businessUdKey);
    if (status != E_OK) {
        LOG_ERROR(UDMF_SERVICE, "status:0x%{public}x", status);
        return status;
    }
    return E_OK;
}

int32_t UdmfServiceProxy::SetDelayInfo(const DataLoadInfo &dataLoadInfo, sptr<IRemoteObject> iUdmfNotifier,
    std::string &key)
{
    MessageParcel reply;
    int32_t status = IPC_SEND(UdmfServiceInterfaceCode::SET_DELAY_INFO, reply, dataLoadInfo, iUdmfNotifier);
    if (status != E_OK) {
        LOG_ERROR(UDMF_SERVICE, "status:0x%{public}x", status);
        return status;
    }
    if (!ITypesUtil::Unmarshal(reply, key)) {
        LOG_ERROR(UDMF_SERVICE, "Unmarshal status failed!");
        return E_READ_PARCEL_ERROR;
    }
    return E_OK;
}

int32_t UdmfServiceProxy::PushDelayData(const std::string &key, UnifiedData &unifiedData)
{
    UdmfConversion::InitValueObject(unifiedData);
    MessageParcel reply;

    int32_t status = IPC_SEND(UdmfServiceInterfaceCode::SET_DELAY_DATA, reply, key, unifiedData);
    if (status != E_OK) {
        LOG_ERROR(UDMF_SERVICE, "status:0x%{public}x", status);
        return status;
    }
    return E_OK;
}

int32_t UdmfServiceProxy::GetDataIfAvailable(const DataLoadInfo &dataLoadInfo, sptr<IRemoteObject> iUdmfNotifier,
    std::shared_ptr<UnifiedData> unifiedData)
{
    MessageParcel reply;
    int32_t status = IPC_SEND(UdmfServiceInterfaceCode::GET_DELAY_DATA, reply, dataLoadInfo, iUdmfNotifier);
    if (status != E_OK) {
        LOG_ERROR(UDMF_SERVICE, "status:0x%{public}x, key:%{public}s!", status, dataLoadInfo.udKey.c_str());
        return status;
    }
    UnifiedData data;
    if (!ITypesUtil::Unmarshal(reply, data)) {
        LOG_ERROR(UDMF_SERVICE, "Unmarshal UnifiedData failed!");
        return E_READ_PARCEL_ERROR;
    }
    if (!data.IsEmpty()) {
        UdmfConversion::ConvertRecordToSubclass(data);
        *unifiedData = data;
    }
    return status;
}
} // namespace UDMF
} // namespace OHOS