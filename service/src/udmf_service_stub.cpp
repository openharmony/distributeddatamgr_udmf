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

#include "udmf_service_stub.h"

#include <vector>

#include "accesstoken_kit.h"
#include "ipc_skeleton.h"

#include "logger.h"
#include "udmf_types_util.h"
#include "unified_data.h"
#include "unified_meta.h"
#include "tlv_util.h"

namespace OHOS {
namespace UDMF {
UdmfServiceStub::UdmfServiceStub()
{
    memberFuncMap_[static_cast<uint32_t>(SET_DATA)] = &UdmfServiceStub::OnSetData;
    memberFuncMap_[static_cast<uint32_t>(GET_DATA)] = &UdmfServiceStub::OnGetData;
    memberFuncMap_[static_cast<uint32_t>(GET_SUMMARY)] = &UdmfServiceStub::OnGetSummary;
    memberFuncMap_[static_cast<uint32_t>(ADD_PRIVILEGE)] = &UdmfServiceStub::OnAddPrivilege;
    memberFuncMap_[static_cast<uint32_t>(SYNC)] = &UdmfServiceStub::OnSync;
}

UdmfServiceStub::~UdmfServiceStub()
{
    memberFuncMap_.clear();
}

int UdmfServiceStub::OnRemoteRequest(uint32_t code, MessageParcel &data, MessageParcel &reply)
{
    LOG_INFO(UDMF_SERVICE, "start##code = %{public}u", code);
    std::u16string myDescripter = UdmfServiceStub::GetDescriptor();
    std::u16string remoteDescripter = data.ReadInterfaceToken();
    if (myDescripter != remoteDescripter) {
        LOG_ERROR(UDMF_SERVICE, "end##descriptor checked fail");
        return -1;
    }
    if (CODE_HEAD > code || code >= CODE_BUTT) {
        return -1;
    }
    auto itFunc = memberFuncMap_.find(code);
    if (itFunc != memberFuncMap_.end()) {
        auto memberFunc = itFunc->second;
        if (memberFunc != nullptr) {
            return (this->*memberFunc)(data, reply);
        }
    }
    LOG_INFO(UDMF_SERVICE, "end##ret = -1");
    return -1;
}

int32_t UdmfServiceStub::OnSetData(MessageParcel &data, MessageParcel &reply)
{
    LOG_INFO(UDMF_SERVICE, "start");
    CustomOption customOption;
    if (!ITypesUtil::Unmarshal(data, customOption)) {
        return IPC_STUB_INVALID_DATA_ERR;
    }
    UnifiedData unifiedData;
    int32_t count = data.ReadInt32();
    if (count > MAX_RECORD_NUM) {
        LOG_ERROR(UDMF_SERVICE, "Excessive record: %{public}d!", count);
        return E_INVALID_VALUE;
    }
    for (int32_t index = 0; index < count; ++index) {
        std::shared_ptr<UnifiedRecord> record;
        int32_t size = data.ReadInt32();
        if (size == 0) {
            continue;
        }
        const uint8_t *rawData = reinterpret_cast<const uint8_t *>(data.ReadRawData(size));
        if (rawData == nullptr) {
            return IPC_STUB_INVALID_DATA_ERR;
        }
        std::vector<uint8_t> recordBytes(rawData, rawData + size);
        auto recordTlv = TLVObject(recordBytes);
        if (!TLVUtil::Reading(record, recordTlv)) {
            return IPC_STUB_INVALID_DATA_ERR;
        }
        unifiedData.AddRecord(record);
    }
    if (unifiedData.GetRecords().empty()) {
        LOG_ERROR(UDMF_SERVICE, "Empty data without any record!");
        return E_INVALID_VALUE;
    }
    if (unifiedData.GetSize() > UdmfService::MAX_DATA_SIZE) {
        LOG_ERROR(UDMF_SERVICE, "Exceeded data limit!");
        return E_INVALID_VALUE;
    }
    for (const auto &record : unifiedData.GetRecords()) {
        if (record->GetSize() > UdmfService::MAX_RECORD_SIZE) {
            return E_INVALID_VALUE;
        }
    }
    uint32_t token = static_cast<uint32_t>(IPCSkeleton::GetCallingTokenID());
    customOption.tokenId = token;
    std::string key;
    int32_t status = SetData(customOption, unifiedData, key);
    if (!ITypesUtil::Marshal(reply, status, key)) {
        LOG_ERROR(UDMF_SERVICE, "Marshal key: %{public}s", key.c_str());
        return IPC_STUB_WRITE_PARCEL_ERR;
    }
    return E_OK;
}

int32_t UdmfServiceStub::OnGetData(MessageParcel &data, MessageParcel &reply)
{
    LOG_INFO(UDMF_SERVICE, "start");
    QueryOption query;
    if (!ITypesUtil::Unmarshal(data, query)) {
        LOG_ERROR(UDMF_SERVICE, "Unmarshal query");
        return IPC_STUB_INVALID_DATA_ERR;
    }
    uint32_t token = static_cast<uint32_t>(IPCSkeleton::GetCallingTokenID());
    query.tokenId = token;
    int32_t pid = static_cast<int>(IPCSkeleton::GetCallingPid());
    query.pid = pid;
    UnifiedData unifiedData;
    int32_t status = GetData(query, unifiedData);
    if (!ITypesUtil::Marshal(reply, status)) {
        LOG_ERROR(UDMF_SERVICE, "Marshal ud data, key: %{public}s", query.key.c_str());
        return IPC_STUB_WRITE_PARCEL_ERR;
    }
    auto size = unifiedData.GetRecords().size();
    if (!reply.WriteInt32(static_cast<int32_t>(size))) {
        return E_WRITE_PARCEL_ERROR;
    }
    for (const auto &record : unifiedData.GetRecords()) {
        if (record == nullptr) {
            continue;
        }
        std::vector<uint8_t> recordBytes;
        auto recordTlv = TLVObject(recordBytes);
        if (!TLVUtil::Writing(record, recordTlv)) {
            LOG_ERROR(UDMF_SERVICE, "TLVUtil writing unified record failed.");
            return E_WRITE_PARCEL_ERROR;
        }
        if (!reply.WriteInt32(static_cast<int32_t>(recordBytes.size())) ||
            !reply.WriteRawData(recordBytes.data(), recordBytes.size())) {
            return E_WRITE_PARCEL_ERROR;
        }
    }
    return E_OK;
}

int32_t UdmfServiceStub::OnGetSummary(MessageParcel &data, MessageParcel &reply)
{
    LOG_INFO(UDMF_SERVICE, "start");
    QueryOption query;
    if (!ITypesUtil::Unmarshal(data, query)) {
        LOG_ERROR(UDMF_SERVICE, "Unmarshal query");
        return IPC_STUB_INVALID_DATA_ERR;
    }
    uint32_t token = static_cast<uint32_t>(IPCSkeleton::GetCallingTokenID());
    query.tokenId = token;
    Summary summary;
    int32_t status = GetSummary(query, summary);
    if (!ITypesUtil::Marshal(reply, status, summary)) {
        LOG_ERROR(UDMF_SERVICE, "Marshal summary, key: %{public}s", query.key.c_str());
        return IPC_STUB_WRITE_PARCEL_ERR;
    }
    return E_OK;
}

int32_t UdmfServiceStub::OnAddPrivilege(MessageParcel &data, MessageParcel &reply)
{
    LOG_INFO(UDMF_SERVICE, "start");
    QueryOption query;
    Privilege privilege;
    if (!ITypesUtil::Unmarshal(data, query, privilege)) {
        LOG_ERROR(UDMF_SERVICE, "Unmarshal query and privilege");
        return IPC_STUB_INVALID_DATA_ERR;
    }
    uint32_t token = static_cast<uint32_t>(IPCSkeleton::GetCallingTokenID());
    query.tokenId = token;
    int32_t status = AddPrivilege(query, privilege);
    if (!ITypesUtil::Marshal(reply, status)) {
        LOG_ERROR(UDMF_SERVICE, "Marshal status, key: %{public}s", query.key.c_str());
        return IPC_STUB_WRITE_PARCEL_ERR;
    }
    return E_OK;
}

int32_t UdmfServiceStub::OnSync(MessageParcel &data, MessageParcel &reply)
{
    LOG_INFO(UDMF_SERVICE, "start");
    QueryOption query;
    std::vector<std::string> devices;
    if (!ITypesUtil::Unmarshal(data, query, devices)) {
        LOG_ERROR(UDMF_SERVICE, "Unmarshal query and devices");
        return IPC_STUB_INVALID_DATA_ERR;
    }
    uint32_t token = static_cast<uint32_t>(IPCSkeleton::GetCallingTokenID());
    query.tokenId = token;
    int32_t status = Sync(query, devices);
    if (!ITypesUtil::Marshal(reply, status)) {
        LOG_ERROR(UDMF_SERVICE, "Marshal status, key: %{public}s", query.key.c_str());
        return IPC_STUB_WRITE_PARCEL_ERR;
    }
    return E_OK;
}

/*
 * Check whether the caller has the permission to access data.
 */
bool UdmfServiceStub::VerifyPermission(const std::string &permission)
{
#ifdef UDMF_PERMISSION_ENABLED
    uint32_t tokenId = IPCSkeleton::GetCallingTokenID();
    int32_t result = Security::AccessToken::AccessTokenKit::VerifyAccessToken(tokenId, permission);
    return result == Security::AccessToken::TypePermissionState::PERMISSION_GRANTED;
#else
    return true;
#endif // UDMF_PERMISSION_ENABLED
}
} // namespace UDMF
} // namespace OHOS