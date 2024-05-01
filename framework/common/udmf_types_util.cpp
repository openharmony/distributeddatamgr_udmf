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
#define LOG_TAG "UdmfTypesUtil"
#include "udmf_types_util.h"

#include <string>

#include "logger.h"
#include "tlv_util.h"

namespace OHOS {
namespace ITypesUtil {
using namespace UDMF;
template<>
bool Marshalling(const UnifiedData &input, MessageParcel &parcel)
{
    std::vector<uint8_t> dataBytes;
    auto recordTlv = TLVObject(dataBytes);
    if (!TLVUtil::Writing(input, recordTlv)) {
        LOG_ERROR(UDMF_SERVICE, "TLV writing failed!");
        return false;
    }
    if (!parcel.WriteInt32(static_cast<int32_t>(dataBytes.size()))
        || !parcel.WriteRawData(dataBytes.data(), dataBytes.size())) {
        LOG_ERROR(UDMF_SERVICE, "Marshall unified data failed!");
        return false;
    }
    return true;
}

template<>
bool Unmarshalling(UnifiedData &output, MessageParcel &parcel)
{
    auto size = parcel.ReadInt32();
    if (size == 0) {
        LOG_ERROR(UDMF_SERVICE, "UnifiedData is empty!");
        return false;
    }
    auto rawData = parcel.ReadRawData(size);
    if (rawData == nullptr) {
        LOG_ERROR(UDMF_SERVICE, "RawData is null!");
        return false;
    }
    const uint8_t *data = reinterpret_cast<const uint8_t *>(rawData);
    std::vector<uint8_t> dataBytes(data, data + size);
    auto recordTlv = TLVObject(dataBytes);
    if (!TLVUtil::Reading(output, recordTlv)) {
        LOG_ERROR(UDMF_SERVICE, "Unmarshall unified data failed!");
        return false;
    }
    return true;
}

template<>
bool Marshalling(const std::vector<UnifiedData> &input, MessageParcel &parcel)
{
    std::vector<uint8_t> dataSetBytes;
    auto recordTlv = TLVObject(dataSetBytes);
    if (!TLVUtil::Writing(input, recordTlv)) {
        LOG_ERROR(UDMF_SERVICE, "TLV writing failed!");
        return false;
    }
    if (!parcel.WriteInt32(static_cast<int32_t>(dataSetBytes.size()))
        || !parcel.WriteRawData(dataSetBytes.data(), dataSetBytes.size())) {
        LOG_ERROR(UDMF_SERVICE, "Marshall unified data set failed!");
        return false;
    }
    return true;
}

template<>
bool Unmarshalling(std::vector<UnifiedData> &output, MessageParcel &parcel)
{
    auto size = parcel.ReadInt32();
    if (size == 0) {
        LOG_ERROR(UDMF_SERVICE, "UnifiedDataSet is empty!");
        return false;
    }
    const uint8_t *rawData = reinterpret_cast<const uint8_t *>(parcel.ReadRawData(size));
    if (rawData == nullptr) {
        LOG_ERROR(UDMF_SERVICE, "RawData is null!");
        return false;
    }
    std::vector<uint8_t> dataSetBytes(rawData, rawData + size);
    auto recordTlv = TLVObject(dataSetBytes);
    if (!TLVUtil::Reading(output, recordTlv)) {
        LOG_ERROR(UDMF_SERVICE, "Unmarshall unified data set failed!");
        return false;
    }
    return true;
}

template<>
bool Marshalling(const Summary &input, MessageParcel &parcel)
{
    return ITypesUtil::Marshal(parcel, input.summary, input.totalSize);
}

template<>
bool Unmarshalling(Summary &output, MessageParcel &parcel)
{
    return ITypesUtil::Unmarshal(parcel, output.summary, output.totalSize);
}

template<>
bool Marshalling(const Privilege &input, MessageParcel &parcel)
{
    return ITypesUtil::Marshal(parcel, input.tokenId, input.readPermission, input.writePermission);
}

template<>
bool Unmarshalling(Privilege &output, MessageParcel &parcel)
{
    return ITypesUtil::Unmarshal(parcel, output.tokenId, output.readPermission, output.writePermission);
}

template<>
bool Marshalling(const CustomOption &input, MessageParcel &parcel)
{
    return ITypesUtil::Marshal(parcel, input.intention);
}

template<>
bool Unmarshalling(CustomOption &output, MessageParcel &parcel)
{
    return ITypesUtil::Unmarshal(parcel, output.intention);
}

template<>
bool Marshalling(const QueryOption &input, MessageParcel &parcel)
{
    return ITypesUtil::Marshal(parcel, input.key, input.intention);
}

template<>
bool Unmarshalling(QueryOption &output, MessageParcel &parcel)
{
    return ITypesUtil::Unmarshal(parcel, output.key, output.intention);
}

template<>
bool Marshalling(const UDType &input, MessageParcel &parcel)
{
    int32_t type = input;
    return ITypesUtil::Marshal(parcel, type);
}

template<>
bool Unmarshalling(UDType &output, MessageParcel &parcel)
{
    int32_t type;
    if (!ITypesUtil::Unmarshal(parcel, type)) {
        LOG_ERROR(UDMF_FRAMEWORK, "Unmarshal UDType failed!");
        return false;
    }
    if (type < ENTITY || type >= UD_BUTT) {
        LOG_ERROR(UDMF_FRAMEWORK, "invalid UDType!");
        return false;
    }
    output = static_cast<UDType>(type);
    return true;
}

template<>
bool Marshalling(const Intention &input, MessageParcel &parcel)
{
    int32_t intention = input;
    return ITypesUtil::Marshal(parcel, intention);
}

template<>
bool Unmarshalling(Intention &output, MessageParcel &parcel)
{
    int32_t intention;
    if (!ITypesUtil::Unmarshal(parcel, intention)) {
        LOG_ERROR(UDMF_FRAMEWORK, "Unmarshal Intention failed!");
        return false;
    }
    if (intention < UD_INTENTION_BASE || intention > UD_INTENTION_BUTT) {
        LOG_ERROR(UDMF_FRAMEWORK, "invalid Intention!");
        return false;
    }
    output = static_cast<Intention>(intention);
    return true;
}
} // namespace ITypesUtil
} // namespace OHOS