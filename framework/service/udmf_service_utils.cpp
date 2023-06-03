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

#include "udmf_service_utils.h"


namespace OHOS {
namespace UDMF {
int32_t UdmfServiceUtils::MarshalUnifiedData(MessageParcel &data, const UnifiedData &unifiedData)
{
    auto size = unifiedData.GetRecords().size();
    if (!data.WriteInt32(static_cast<int32_t>(size))) {
        return E_WRITE_PARCEL_ERROR;
    }
    for (const auto &record : unifiedData.GetRecords()) {
        if (record == nullptr) {
            continue;
        }
        if (record->GetSize() > UdmfService::MAX_RECORD_SIZE) {
            return E_INVALID_VALUE;
        }
        std::vector<uint8_t> recordBytes;
        auto recordTlv = TLVObject(recordBytes);
        if (!TLVUtil::Writing(record, recordTlv)) {
            return E_WRITE_PARCEL_ERROR;
        }
        if (!data.WriteInt32(static_cast<int32_t>(recordBytes.size()))
            || !data.WriteRawData(recordBytes.data(), recordBytes.size())) {
            return E_WRITE_PARCEL_ERROR;
        }
    }
    return E_OK;
}

int32_t UdmfServiceUtils::UnMarshalUnifiedData(MessageParcel &data, UnifiedData &unifiedData)
{
    int32_t count = data.ReadInt32();
    for (int32_t index = 0; index < count; ++index) {
        std::shared_ptr<UnifiedRecord> record;
        auto size = data.ReadInt32();
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
            LOG_ERROR(UDMF_SERVICE, "Unmarshall unified record failed.");
            return IPC_STUB_INVALID_DATA_ERR;
        }
        unifiedData.AddRecord(record);
    }
    return E_OK;
}

int32_t UdmfServiceUtils::MarshalBatchUnifiedData(MessageParcel &data, const std::vector<UnifiedData> &unifiedDataSet)
{
    auto unifiedDataSetSize = unifiedDataSet.size();
    if (!data.WriteInt32(static_cast<int32_t>(unifiedDataSetSize))) {
        return E_WRITE_PARCEL_ERROR;
    }
    for (const auto &unifiedData : unifiedDataSet) {
        if (MarshalUnifiedData(data, unifiedData) != E_OK) {
            return E_WRITE_PARCEL_ERROR;
        }
    }
    return E_OK;
}

int32_t UdmfServiceUtils::UnMarshalBatchUnifiedData(MessageParcel &data, std::vector<UnifiedData> &unifiedDataSet)
{
    int32_t unifiedDataSetCount = data.ReadInt32();
    for (int32_t dataIndex = 0; dataIndex < unifiedDataSetCount; dataIndex++) {
        UnifiedData unifiedData;
        if (UnMarshalUnifiedData(data, unifiedData) != E_OK) {
            return E_READ_PARCEL_ERROR;
        }
        unifiedDataSet.push_back(unifiedData);
    }
    return E_OK;
}
} // namespace UDMF
} // namespace OHOS