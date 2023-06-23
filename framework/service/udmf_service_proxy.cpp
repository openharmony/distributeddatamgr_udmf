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

#include "preprocess_utils.h"
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
            auto result = SendRequest((code), request, reply, option);                       \
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
    LOG_DEBUG(UDMF_SERVICE, "start, tag: %{public}d", option.intention);
    if (!UnifiedDataUtils::IsValidIntention(option.intention)) {
        LOG_ERROR(UDMF_SERVICE, "Invalid intention");
        return E_INVALID_PARAMETERS;
    }
    if (unifiedData.IsEmpty()) {
        LOG_ERROR(UDMF_SERVICE, "Empty data without any record!");
        return E_INVALID_PARAMETERS;
    }
    if (unifiedData.GetSize() > UdmfService::MAX_DATA_SIZE) {
        LOG_ERROR(UDMF_SERVICE, "Exceeded the limit!");
        return E_INVALID_PARAMETERS;
    }
    for (const auto &record : unifiedData.GetRecords()) {
        if (record == nullptr) {
            LOG_ERROR(UDMF_SERVICE, "record is nullptr!");
            return E_INVALID_PARAMETERS;
        }
        if (record->GetSize() > UdmfService::MAX_RECORD_SIZE) {
            LOG_ERROR(UDMF_SERVICE, "Exceeded record limit!");
            return E_INVALID_PARAMETERS;
        }
    }
    MessageParcel reply;
    int32_t status = IPC_SEND(SET_DATA, reply, option, unifiedData);
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
    LOG_DEBUG(UDMF_SERVICE, "start, tag: %{public}s", query.key.c_str());
    UnifiedKey key(query.key);
    if (!key.IsValid()) {
        LOG_ERROR(UDMF_SERVICE, "invalid key");
        return E_INVALID_PARAMETERS;
    }
    MessageParcel reply;
    int32_t status = IPC_SEND(GET_DATA, reply, query);
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
    LOG_DEBUG(UDMF_SERVICE, "start, tag: intention = %{public}d, key = %{public}s", query.intention, query.key.c_str());
    auto find = UD_INTENTION_MAP.find(query.intention);
    std::string intention = find == UD_INTENTION_MAP.end() ? intention : find->second;
    if (!UnifiedDataUtils::IsValidOptions(query.key, intention)) {
        LOG_ERROR(UDMF_SERVICE, "invalid option");
        return E_INVALID_PARAMETERS;
    }
    MessageParcel reply;
    int32_t status = IPC_SEND(GET_BATCH_DATA, reply, query);
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
    LOG_DEBUG(UDMF_SERVICE, "start, tag: %{public}s", query.key.c_str());
    UnifiedKey key(query.key);
    if (!key.IsValid() || !UnifiedDataUtils::IsPersist(key.intention)) {
        LOG_ERROR(UDMF_SERVICE, "invalid key");
        return E_INVALID_PARAMETERS;
    }
    if (unifiedData.GetSize() > UdmfService::MAX_DATA_SIZE) {
        LOG_ERROR(UDMF_SERVICE, "Exceeded the limit!");
        return E_INVALID_PARAMETERS;
    }
    if (unifiedData.IsEmpty()) {
        LOG_ERROR(UDMF_SERVICE, "Empty data without any record!");
        return E_INVALID_PARAMETERS;
    }
    for (const auto &record : unifiedData.GetRecords()) {
        if (record == nullptr) {
            LOG_ERROR(UDMF_SERVICE, "record is nullptr!");
            return E_INVALID_PARAMETERS;
        }
        if (record->GetSize() > UdmfService::MAX_RECORD_SIZE) {
            LOG_ERROR(UDMF_SERVICE, "Exceeded record limit!");
            return E_INVALID_PARAMETERS;
        }
    }
    MessageParcel reply;
    int32_t status = IPC_SEND(UPDATE_DATA, reply, query, unifiedData);
    if (status != E_OK) {
        LOG_ERROR(UDMF_SERVICE, "status:0x%{public}x!", status);
        return status;
    }
    return status;
}

int32_t UdmfServiceProxy::DeleteData(const QueryOption &query, std::vector<UnifiedData> &unifiedDataSet)
{
    LOG_DEBUG(UDMF_SERVICE, "start, tag: intention = %{public}d, key = %{public}s", query.intention, query.key.c_str());
    auto find = UD_INTENTION_MAP.find(query.intention);
    std::string intention = find == UD_INTENTION_MAP.end() ? intention : find->second;
    if (!UnifiedDataUtils::IsValidOptions(query.key, intention)) {
        LOG_ERROR(UDMF_SERVICE, "invalid option");
        return E_INVALID_PARAMETERS;
    }
    MessageParcel reply;
    int32_t status = IPC_SEND(DELETE_DATA, reply, query);
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
    LOG_DEBUG(UDMF_SERVICE, "start, tag: %{public}s", query.key.c_str());
    UnifiedKey key(query.key);
    if (!key.IsValid()) {
        LOG_ERROR(UDMF_SERVICE, "invalid key");
        return E_INVALID_PARAMETERS;
    }
    MessageParcel reply;
    int32_t status = IPC_SEND(GET_SUMMARY, reply, query);
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
    LOG_DEBUG(UDMF_SERVICE, "start, key: %{public}s", query.key.c_str());
    UnifiedKey key(query.key);
    if (!key.IsValid()) {
        LOG_ERROR(UDMF_SERVICE, "invalid key");
        return E_INVALID_PARAMETERS;
    }
    MessageParcel reply;
    int32_t status = IPC_SEND(ADD_PRIVILEGE, reply, query, privilege);
    if (status != E_OK) {
        LOG_ERROR(UDMF_SERVICE, "status:0x%{public}x, key:%{public}s", status, query.key.c_str());
    }
    LOG_DEBUG(UDMF_SERVICE, "end.");
    return status;
}

int32_t UdmfServiceProxy::Sync(const QueryOption &query, const std::vector<std::string> &devices)
{
    LOG_DEBUG(UDMF_SERVICE, "start, key: %{public}s", query.key.c_str());
    UnifiedKey key(query.key);
    if (!key.IsValid()) {
        LOG_ERROR(UDMF_SERVICE, "invalid key");
        return E_INVALID_PARAMETERS;
    }
    MessageParcel reply;
    int32_t status = IPC_SEND(SYNC, reply, query, devices);
    if (status != E_OK) {
        LOG_ERROR(UDMF_SERVICE, "status:0x%{public}x, key:%{public}s", status, query.key.c_str());
    }
    LOG_DEBUG(UDMF_SERVICE, "end.");
    return status;
}

int32_t UdmfServiceProxy::SendRequest(
    IUdmfService::FCode code, MessageParcel &data, MessageParcel &reply, MessageOption &option)
{
    sptr<IRemoteObject> remote = Remote();
    if (remote == nullptr) {
        return E_IPC;
    }
    int err = remote->SendRequest(code, data, reply, option);
    LOG_DEBUG(UDMF_SERVICE, "err: %{public}d", err);
    return err;
}
} // namespace UDMF
} // namespace OHOS