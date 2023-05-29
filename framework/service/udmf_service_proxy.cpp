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
#include "udmf_types_util.h"
#include "tlv_util.h"

namespace OHOS {
namespace UDMF {
#define IPC_SEND(code, reply, ...)                                     \
    ({                                                                 \
        int32_t __status = E_OK;                                       \
        do {                                                           \
            MessageParcel request;                                     \
            if (!request.WriteInterfaceToken(GetDescriptor())) {       \
                __status = E_WRITE_PARCEL_ERROR;                       \
                break;                                                 \
            }                                                          \
            if (!ITypesUtil::Marshal(request, ##__VA_ARGS__)) {        \
                __status = E_WRITE_PARCEL_ERROR;                       \
                break;                                                 \
            }                                                          \
            MessageOption option;                                      \
            auto result = SendRequest((code), request, reply, option); \
            if (result != 0) {                                         \
                __status = E_IPC;                                      \
                break;                                                 \
            }                                                          \
                                                                       \
            ITypesUtil::Unmarshal(reply, __status);                    \
        } while (0);                                                   \
        __status;                                                      \
    })


UdmfServiceProxy::UdmfServiceProxy(const sptr<IRemoteObject> &object) : IRemoteProxy<IUdmfService>(object)
{
}

int32_t UdmfServiceProxy::SetData(CustomOption &option, UnifiedData &unifiedData, std::string &key)
{
    LOG_INFO(UDMF_SERVICE, "start, tag: %{public}d", option.intention);
    if (!UnifiedDataUtils::IsValidIntention(option.intention)) {
        LOG_ERROR(UDMF_SERVICE, "Invalid intention");
        return E_INVALID_PARAMETERS;
    }
    if (unifiedData.GetRecords().empty()) {
        LOG_ERROR(UDMF_SERVICE, "Empty data without any record!");
        return E_INVALID_VALUE;
    }
    if (unifiedData.GetRecords().size() > UdmfService::MAX_RECORD_NUM) {
        LOG_ERROR(UDMF_SERVICE, "Excessive record: %{public}zu!", unifiedData.GetRecords().size());
        return E_INVALID_VALUE;
    }
    if (unifiedData.GetSize() > UdmfService::MAX_DATA_SIZE) {
        return E_INVALID_VALUE;
    }
    MessageParcel request;
    if (!request.WriteInterfaceToken(GetDescriptor())) {
        return E_WRITE_PARCEL_ERROR;
    }
    if (!ITypesUtil::Marshal(request, option)) {
        return E_WRITE_PARCEL_ERROR;
    }
    auto size = unifiedData.GetRecords().size();
    if (!request.WriteInt32(static_cast<int32_t>(size))) {
        return E_WRITE_PARCEL_ERROR;
    }
    for (const auto &record : unifiedData.GetRecords()) {
        if (record->GetSize() > UdmfService::MAX_RECORD_SIZE) {
            return E_INVALID_VALUE;
        }
        std::vector<uint8_t> recordBytes;
        auto recordTlv = TLVObject(recordBytes);
        if (!TLVUtil::Writing(record, recordTlv)) {
            return E_WRITE_PARCEL_ERROR;
        }
        if (!request.WriteInt32(static_cast<int32_t>(recordBytes.size())) ||
            !request.WriteRawData(recordBytes.data(), recordBytes.size())) {
            return E_WRITE_PARCEL_ERROR;
        }
    }
    MessageParcel reply;
    MessageOption messageOption;
    int error = Remote()->SendRequest(SET_DATA, request, reply, messageOption);
    if (error != 0) {
        return E_WRITE_PARCEL_ERROR;
    }
    int32_t status;
    ITypesUtil::Unmarshal(reply, status, key);
    return status;
}

int32_t UdmfServiceProxy::GetData(QueryOption &query, UnifiedData &unifiedData)
{
    LOG_INFO(UDMF_SERVICE, "start, tag: %{public}s", query.key.c_str());
    UnifiedKey key(query.key);
    if (!key.IsValid()) {
        LOG_ERROR(UDMF_SERVICE, "invalid key");
        return E_INVALID_PARAMETERS;
    }
    MessageParcel reply;
    int32_t status = IPC_SEND(GET_DATA, reply, query);
    if (status != E_OK) {
        LOG_ERROR(UDMF_SERVICE, "status:0x%{public}x, key:%{public}s", status, query.key.c_str());
        return status;
    }

    int32_t count = reply.ReadInt32();
    for (int32_t index = 0; index < count; ++index) {
        std::shared_ptr<UnifiedRecord> record;
        auto size = reply.ReadInt32();
        if (size == 0) {
            continue;
        }
        const uint8_t *rawData = reinterpret_cast<const uint8_t *>(reply.ReadRawData(size));
        std::vector<uint8_t> recordBytes(rawData, rawData + size);
        auto recordTlv = TLVObject(recordBytes);
        if (!TLVUtil::Reading(record, recordTlv)) {
            LOG_ERROR(UDMF_SERVICE, "Unmarshall unified record failed.");
            return IPC_STUB_INVALID_DATA_ERR;
        }
        unifiedData.AddRecord(record);
    }

    LOG_DEBUG(UDMF_SERVICE, "end.");
    return status;
}

int32_t UdmfServiceProxy::GetSummary(QueryOption &query, Summary &summary)
{
    LOG_INFO(UDMF_SERVICE, "start, tag: %{public}s", query.key.c_str());
    UnifiedKey key(query.key);
    if (!key.IsValid()) {
        LOG_ERROR(UDMF_SERVICE, "invalid key");
        return E_INVALID_PARAMETERS;
    }
    MessageParcel reply;
    int32_t status = IPC_SEND(GET_SUMMARY, reply, query);
    if (status != E_OK) {
        LOG_ERROR(UDMF_SERVICE, "status:0x%{public}x, key:%{public}s", status, query.key.c_str());
        return status;
    }
    ITypesUtil::Unmarshal(reply, summary);
    LOG_DEBUG(UDMF_SERVICE, "end.");
    return status;
}

int32_t UdmfServiceProxy::AddPrivilege(QueryOption &query, Privilege &privilege)
{
    LOG_INFO(UDMF_SERVICE, "start, key: %{public}s", query.key.c_str());
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
    LOG_INFO(UDMF_SERVICE, "start, key: %{public}s", query.key.c_str());
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
        return E_SA_DIED;
    }
    int err = remote->SendRequest(code, data, reply, option);
    LOG_DEBUG(UDMF_SERVICE, "err: %{public}d", err);
    return err;
}
} // namespace UDMF
} // namespace OHOS