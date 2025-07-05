/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define LOG_TAG "TlvUtil"

#include "tlv_util.h"
#include "udmf_utils.h"
#include "logger.h"
#include "pixelmap_loader.h"
#include "tlv_object.h"

namespace OHOS {
namespace TLVUtil {
template <> size_t CountBufferSize(const std::nullptr_t &input, TLVObject &data)
{
    return data.CountHead();
}

template <> bool Writing(const std::nullptr_t &input, TLVObject &data, TAG tag)
{
    InitWhenFirst(input, data);
    return data.WriteHead(static_cast<uint16_t>(tag), 0);
}

template <> bool Reading(std::nullptr_t &output, TLVObject &data, const TLVHead &head)
{
    return data.Read(output, head);
}

template <> size_t CountBufferSize(const std::monostate &input, TLVObject &data)
{
    return data.Count(input);
}

template <> bool Writing(const std::monostate &input, TLVObject &data, TAG tag)
{
    InitWhenFirst(input, data);
    return data.Write(tag, input);
}

template <> bool Reading(std::monostate &output, TLVObject &data, const TLVHead &head)
{
    return data.Read(output, head);
}

template <> size_t CountBufferSize(const std::string &input, TLVObject &data)
{
    return data.Count(input);
}

template <> bool Writing(const std::string &input, TLVObject &data, TAG tag)
{
    InitWhenFirst(input, data);
    return data.Write(tag, input);
}

template <> bool Reading(std::string &output, TLVObject &data, const TLVHead &head)
{
    return data.Read(output, head);
}

template <> size_t CountBufferSize(const std::vector<uint8_t> &input, TLVObject &data)
{
    return data.Count(input);
}

template <> bool Writing(const std::vector<uint8_t> &input, TLVObject &data, TAG tag)
{
    InitWhenFirst(input, data);
    return data.Write(tag, input);
}

template <> bool Reading(std::vector<uint8_t> &output, TLVObject &data, const TLVHead &head)
{
    return data.Read(output, head);
}

template <> size_t CountBufferSize(const UDType &input, TLVObject &data)
{
    int32_t type = input;
    return data.CountBasic(type);
}

template <> bool Writing(const UDType &input, TLVObject &data, TAG tag)
{
    InitWhenFirst(input, data);
    int32_t type = input;
    return data.WriteBasic(tag, type);
}

template <> bool Reading(UDType &output, TLVObject &data, const TLVHead &head)
{
    int32_t type;
    if (!Reading(type, data, head)) {
        return false;
    }
    if (type < UDType::ENTITY || type >= UDType::UD_BUTT) {
        return false;
    }
    output = static_cast<UDType>(type);
    return true;
}

template <> size_t CountBufferSize(const DataStatus &input, TLVObject &data)
{
    int32_t status = input;
    return data.CountBasic(status);
}

template <> bool Writing(const DataStatus &input, TLVObject &data, TAG tag)
{
    InitWhenFirst(input, data);
    int32_t status = input;
    return data.WriteBasic(tag, status);
}

template <> bool Reading(DataStatus &output, TLVObject &data, const TLVHead &head)
{
    int32_t status;
    if (!data.ReadBasic(status, head)) {
        return false;
    }
    if (status < DataStatus::WORKING || status >= DataStatus::FADE) {
        return false;
    }
    output = static_cast<DataStatus>(status);
    return true;
}

template <> size_t CountBufferSize(const Object &input, TLVObject &data)
{
    return data.CountHead() + CountBufferSize(input.value_, data);
}

template <> bool Writing(const Object &input, TLVObject &data, TAG tag)
{
    InitWhenFirst(input, data);
    auto tagCursor = data.GetCursor();
    data.OffsetHead();
    if (!Writing(input.value_, data, TAG::TAG_OBJECT_VALUE)) {
        return false;
    }
    return data.WriteBackHead(static_cast<uint16_t>(tag), tagCursor, data.GetCursor() - tagCursor - sizeof(TLVHead));
}
template <> bool Reading(Object &output, TLVObject &data, const TLVHead &head)
{
    TLVHead headValue{};
    if (!data.ReadHead(headValue)) {
        return false;
    }
    if (headValue.tag != static_cast<uint16_t>(TAG::TAG_OBJECT_VALUE)) {
        return false;
    }
    if (!Reading(output.value_, data, headValue)) {
        return false;
    }
    return true;
}

template <> size_t CountBufferSize(const UnifiedKey &input, TLVObject &data)
{
    return data.CountHead() + data.Count(input.key) + data.Count(input.intention) + data.Count(input.bundleName) +
        data.Count(input.groupId);
}
template <> bool Writing(const UnifiedKey &input, TLVObject &data, TAG tag)
{
    InitWhenFirst(input, data);
    auto tagCursor = data.GetCursor();
    data.OffsetHead();
    if (!data.Write(TAG::TAG_KEY, input.key)) {
        return false;
    }
    if (!data.Write(TAG::TAG_INTENTION, input.intention)) {
        return false;
    }
    if (!data.Write(TAG::TAG_BUNDLE_NAME, input.bundleName)) {
        return false;
    }
    if (!data.Write(TAG::TAG_GROUP_ID, input.groupId)) {
        return false;
    }
    return data.WriteBackHead(static_cast<uint16_t>(tag), tagCursor, data.GetCursor() - tagCursor - sizeof(TLVHead));
}

template <> bool Reading(UnifiedKey &output, TLVObject &data, const TLVHead &head)
{
    auto endCursor = data.GetCursor() + head.len;
    while (data.GetCursor() < endCursor) {
        TLVHead headItem{};
        if (!data.ReadHead(headItem)) {
            return false;
        }
        switch (headItem.tag) {
            case static_cast<uint16_t>(TAG::TAG_KEY):
                if (!data.Read(output.key, headItem)) {
                    return false;
                }
                break;
            case static_cast<uint16_t>(TAG::TAG_INTENTION):
                if (!data.Read(output.intention, headItem)) {
                    return false;
                }
                break;
            case static_cast<uint16_t>(TAG::TAG_BUNDLE_NAME):
                if (!data.Read(output.bundleName, headItem)) {
                    return false;
                }
                break;
            case static_cast<uint16_t>(TAG::TAG_GROUP_ID):
                if (!data.Read(output.groupId, headItem)) {
                    return false;
                }
                break;
            default:
                data.Skip(headItem);
        }
    }
    return true;
}

template <> size_t CountBufferSize(const UnifiedData &input, TLVObject &data)
{
    return data.CountHead() + data.Count(input.GetSdkVersion()) + TLVUtil::CountBufferSize(input.GetRecords(), data) +
        TLVUtil::CountBufferSize(input.GetProperties(), data);
}

template <> bool Writing(const UnifiedData &input, TLVObject &data, TAG tag)
{
    InitWhenFirst(input, data);
    auto tagCursor = data.GetCursor();
    data.OffsetHead();
    if (!data.Write(TAG::TAG_VERSION, input.GetSdkVersion())) {
        return false;
    }
    if (!TLVUtil::Writing(input.GetRecords(), data, TAG::TAG_UNIFIED_RECORD)) {
        return false;
    }
    if (!TLVUtil::Writing(input.GetProperties(), data, TAG::TAG_UNIFIED_PROPERTIES)) {
        return false;
    }
    return data.WriteBackHead(static_cast<uint16_t>(tag), tagCursor, data.GetCursor() - tagCursor - sizeof(TLVHead));
}

template <> bool Reading(UnifiedData &output, TLVObject &data, const TLVHead &head)
{
    auto endCursor = data.GetCursor() + head.len;
    while (data.GetCursor() < endCursor) {
        TLVHead headItem{};
        if (!data.ReadHead(headItem)) {
            return false;
        }
        if (headItem.tag == static_cast<uint16_t>(TAG::TAG_VERSION)) {
            std::string version;
            if (!Reading(version, data, headItem)) {
                return false;
            }
            output.SetSdkVersion(version);
            continue;
        }
        if (headItem.tag == static_cast<uint16_t>(TAG::TAG_UNIFIED_RECORD)) {
            auto records = output.GetRecords();
            if (!Reading(records, data, headItem)) {
                return false;
            }
            output.SetRecords(records);
            continue;
        }
        if (headItem.tag == static_cast<uint16_t>(TAG::TAG_UNIFIED_PROPERTIES)) {
            auto properties = output.GetProperties();
            if (!Reading(properties, data, headItem)) {
                return false;
            }
            output.SetProperties(std::move(properties));
            continue;
        }
        data.Skip(headItem);
    }
    return true;
}

template <> size_t CountBufferSize(const UnifiedDataProperties &input, TLVObject &data)
{
    return data.CountHead() + data.Count(input.tag) + data.CountBasic(input.timestamp) +
        data.CountBasic(static_cast<int32_t>(input.shareOptions))  + TLVUtil::CountBufferSize(input.extras, data);
}

template <> bool Writing(const UnifiedDataProperties &input, TLVObject &data, TAG tag)
{
    InitWhenFirst(input, data);
    auto tagCursor = data.GetCursor();
    data.OffsetHead();
    if (!data.Write(TAG::TAG_PROPERTIES_TAG, input.tag)) {
        return false;
    }
    if (!data.WriteBasic(TAG::TAG_PROPERTIES_TIMESTAMP, input.timestamp)) {
        return false;
    }
    if (!data.WriteBasic(TAG::TAG_PROPERTIES_SHARE_OPTIONS, static_cast<int32_t>(input.shareOptions))) {
        return false;
    }
    if (!TLVUtil::Writing(input.extras, data, TAG::TAG_PROPERTIES_EXTRAS)) {
        return false;
    }
    return data.WriteBackHead(static_cast<uint16_t>(tag), tagCursor, data.GetCursor() - tagCursor - sizeof(TLVHead));
}

template <> bool Reading(UnifiedDataProperties &output, TLVObject &data, const TLVHead &head)
{
    auto endCursor = data.GetCursor() + head.len;
    while (data.GetCursor() < endCursor) {
        TLVHead headItem{};
        if (!data.ReadHead(headItem)) {
            return false;
        }
        bool result = true;
        switch (headItem.tag) {
            case static_cast<uint16_t>(TAG::TAG_PROPERTIES_TAG):
                result = data.Read(output.tag, headItem);
                break;
            case static_cast<uint16_t>(TAG::TAG_PROPERTIES_TIMESTAMP):
                result = data.ReadBasic(output.timestamp, headItem);
                break;
            case static_cast<uint16_t>(TAG::TAG_PROPERTIES_SHARE_OPTIONS):
                result = TLVUtil::Reading(output.shareOptions, data, headItem);
                break;
            case static_cast<uint16_t>(TAG::TAG_PROPERTIES_EXTRAS):
                result = TLVUtil::Reading(output.extras, data, headItem);
                break;
            default:
                result = data.Skip(headItem);
        }
        if (!result) {
            return false;
        }
    }
    return true;
}

template <> bool Reading(ShareOptions &output, TLVObject &data, const TLVHead &head)
{
    int32_t shareOptions;
    if (!Reading(shareOptions, data, head)) {
        return false;
    }
    if (shareOptions < ShareOptions::IN_APP || shareOptions >= ShareOptions::SHARE_OPTIONS_BUTT) {
        return false;
    }
    output = static_cast<ShareOptions>(shareOptions);
    return true;
}

template <> size_t CountBufferSize(const OHOS::AAFwk::WantParams &input, TLVObject &data)
{
    Parcel parcel;
    if (!input.Marshalling(parcel)) {
        LOG_ERROR(UDMF_FRAMEWORK, "Marshalling want error when Count");
        return 0;
    }
    auto size = parcel.GetDataSize();
    std::vector<std::uint8_t> val(size);
    return CountBufferSize(val, data);
}

template <> bool Writing(const OHOS::AAFwk::WantParams &input, TLVObject &data, TAG tag)
{
    InitWhenFirst(input, data);
    Parcel parcel;
    if (!input.Marshalling(parcel)) {
        LOG_ERROR(UDMF_FRAMEWORK, "Marshalling wantParams error in tlv write. tag=%{public}hu", tag);
        return false;
    }
    auto size = parcel.GetDataSize();
    auto buffer = parcel.GetData();
    std::vector<std::uint8_t> val(size);
    if (size != 0) {
        auto err = memcpy_s(val.data(), size, reinterpret_cast<const void *>(buffer), size);
        if (err != EOK) {
            LOG_ERROR(UDMF_FRAMEWORK, "memcpy error in tlv write wantParams. tag=%{public}hu", tag);
            return false;
        }
    }
    return data.Write(tag, val);
}

template <> bool Reading(OHOS::AAFwk::WantParams &output, TLVObject &data, const TLVHead &head)
{
    std::vector<std::uint8_t> val;
    if (!data.Read(val, head)) {
        LOG_ERROR(UDMF_FRAMEWORK, "Reading u8 vector error.");
        return false;
    }

    std::shared_ptr<Parcel> parcel = std::make_shared<Parcel>();
    auto buffer = malloc(val.size());
    if (buffer == nullptr) {
        LOG_ERROR(UDMF_FRAMEWORK, "malloc error in tlv read. tag=%{public}hu", head.tag);
        return false;
    }
    auto err = memcpy_s(buffer, val.size(), val.data(), val.size());
    if (err != EOK) {
        LOG_ERROR(UDMF_FRAMEWORK, "memcpy_s error in tlv read wantParams. tag=%{public}hu", head.tag);
        free(buffer);
        return false;
    }
    if (!parcel->ParseFrom((uintptr_t)buffer, head.len)) {
        LOG_ERROR(UDMF_FRAMEWORK, "ParseFrom error in tlv read wantParams. tag=%{public}hu", head.tag);
        free(buffer);
        return false;
    }
    // The pointer returned by Unmarshalling needs to be manually deleted.
    auto wantParams = AAFwk::WantParams::Unmarshalling(*parcel);
    if (wantParams == nullptr) {
        LOG_ERROR(UDMF_FRAMEWORK, "Unmarshalling wantParams error in tlv read. tag=%{public}hu", head.tag);
        return false;
    }
    output = *wantParams;
    delete wantParams;
    return true;
}

template <> size_t CountBufferSize(const UnifiedRecord &input, TLVObject &data)
{
    return data.CountHead() + data.CountBasic(static_cast<int32_t>(input.GetType())) +
        data.Count(input.GetUid()) + CountBufferSize(input.GetOriginValue(), data) + data.Count(input.GetUtdId()) +
        data.Count(input.GetUtdId2()) + CountBufferSize(input.GetInnerEntries(), data) +
        CountBufferSize(input.GetUris(), data);
}

template <> bool Writing(const UnifiedRecord &input, TLVObject &data, TAG tag)
{
    InitWhenFirst(input, data);
    auto tagCursor = data.GetCursor();
    data.OffsetHead();
    if (!data.WriteBasic(TAG::TAG_UD_TYPE, static_cast<int32_t>(input.GetType()))) {
        return false;
    }
    if (!data.Write(TAG::TAG_UID, input.GetUid())) {
        return false;
    }
    if (!TLVUtil::Writing(input.GetOriginValue(), data, TAG::TAG_RECORD_VALUE)) {
        return false;
    }
    if (!data.Write(TAG::TAG_RECORD_UTD_ID, input.GetUtdId())) {
        return false;
    }
    if (!data.Write(TAG::TAG_RECORD_UTD_ID2, input.GetUtdId2())) {
        return false;
    }
    if (!TLVUtil::Writing(input.GetInnerEntries(), data, TAG::TAG_RECORD_ENTRIES)) {
        return false;
    }
    if (!TLVUtil::Writing(input.GetUris(), data, TAG::TAG_RECORD_URIS)) {
        return false;
    }
    return data.WriteBackHead(static_cast<uint16_t>(tag), tagCursor, data.GetCursor() - tagCursor - sizeof(TLVHead));
}

template <> bool Reading(UnifiedRecord &output, TLVObject &data, const TLVHead &head)
{
    auto endCursor = data.GetCursor() + head.len;
    UDType dataType;
    std::string uid;
    ValueType value;
    while (data.GetCursor() < endCursor) {
        TLVHead headItem{};
        if (!data.ReadHead(headItem)) {
            return false;
        }
        std::string utdId;
        std::string utdId2;
        std::shared_ptr<std::map<std::string, ValueType>> entries;
        std::vector<UriInfo> uriInfos;
        switch (headItem.tag) {
            case static_cast<uint16_t>(TAG::TAG_UD_TYPE):
                if (!TLVUtil::Reading(dataType, data, headItem)) {
                    return false;
                }
                output.SetType(dataType);
                break;
            case static_cast<uint16_t>(TAG::TAG_UID):
                if (!data.Read(uid, headItem)) {
                    return false;
                }
                output.SetUid(uid);
                break;
            case static_cast<uint16_t>(TAG::TAG_RECORD_VALUE):
                if (!TLVUtil::Reading(value, data, headItem)) {
                    return false;
                }
                output.SetValue(value);
                break;
            case static_cast<uint16_t>(TAG::TAG_RECORD_UTD_ID):
                if (!data.Read(utdId, headItem)) {
                    return false;
                }
                output.SetUtdId(std::move(utdId));
                break;
            case static_cast<uint16_t>(TAG::TAG_RECORD_UTD_ID2):
                if (!data.Read(utdId2, headItem)) {
                    return false;
                }
                output.SetUtdId2(std::move(utdId2));
                break;
            case static_cast<uint16_t>(TAG::TAG_RECORD_ENTRIES):
                if (!TLVUtil::Reading(entries, data, headItem)) {
                    return false;
                }
                output.SetInnerEntries(entries);
                break;
            case static_cast<uint16_t>(TAG::TAG_RECORD_URIS):
                if (!TLVUtil::Reading(uriInfos, data, headItem)) {
                    return false;
                }
                output.SetUris(std::move(uriInfos));
                break;
            default:
                data.Skip(headItem);
        }
    }
    return true;
}

template <> size_t CountBufferSize(const Runtime &input, TLVObject &data)
{
    return data.CountHead() + data.CountBasic(input.isPrivate) + data.CountBasic(input.dataVersion) +
        data.CountBasic(input.recordTotalNum) + data.CountBasic(input.tokenId) +
        data.CountBasic(static_cast<int64_t>(input.createTime)) +
        data.CountBasic(static_cast<int64_t>(input.lastModifiedTime)) +
        data.CountBasic(static_cast<int32_t>(input.dataStatus)) + data.Count(input.sourcePackage) +
        data.Count(input.createPackage) + data.Count(input.deviceId) + TLVUtil::CountBufferSize(input.key, data) +
        data.Count(input.sdkVersion) + TLVUtil::CountBufferSize(input.privileges, data) +
        data.CountBasic(static_cast<int32_t>(input.visibility)) + data.Count(input.appId);
}

template <> bool Writing(const Runtime &input, TLVObject &data, TAG tag)
{
    InitWhenFirst(input, data);
    auto tagCursor = data.GetCursor();
    data.OffsetHead();
    if (!TLVUtil::Writing(input.key, data, TAG::TAG_KEY)) {
        return false;
    }
    if (!data.WriteBasic(TAG::TAG_IS_PRIVATE, input.isPrivate)) {
        return false;
    }
    if (!TLVUtil::Writing(input.privileges, data, TAG::TAG_PRIVILEGE)) {
        return false;
    }
    if (!data.WriteBasic(TAG::TAG_CREATE_TIME, static_cast<int64_t>(input.createTime))) {
        return false;
    }
    if (!data.Write(TAG::TAG_SOURCE_PACKAGE, input.sourcePackage)) {
        return false;
    }
    if (!data.WriteBasic(TAG::TAG_DATA_STATUS, static_cast<int32_t>(input.dataStatus))) {
        return false;
    }
    if (!data.WriteBasic(TAG::TAG_DATA_VERSION, input.dataVersion)) {
        return false;
    }
    if (!data.WriteBasic(TAG::TAG_LAST_MODIFIED_TIME, static_cast<int64_t>(input.lastModifiedTime))) {
        return false;
    }
    if (!data.Write(TAG::TAG_CREATE_PACKAGE, input.createPackage)) {
        return false;
    }
    if (!data.Write(TAG::TAG_DEVICE_ID, input.deviceId)) {
        return false;
    }
    if (!data.WriteBasic(TAG::TAG_RECORD_TOTAL_NUM, input.recordTotalNum)) {
        return false;
    }
    if (!data.WriteBasic(TAG::TAG_TOKEN_ID, input.tokenId)) {
        return false;
    }
    if (!TLVUtil::Writing(input.sdkVersion, data, TAG::TAG_VERSION)) {
        return false;
    }
    if (!data.WriteBasic(TAG::TAG_VISIBILITY, static_cast<int32_t>(input.visibility))) {
        return false;
    }
    if (!TLVUtil::Writing(input.appId, data, TAG::TAG_APP_ID)) {
        return false;
    }
    return data.WriteBackHead(static_cast<uint16_t>(tag), tagCursor, data.GetCursor() - tagCursor - sizeof(TLVHead));
}

template <> bool Reading(Runtime &output, TLVObject &data, const TLVHead &head)
{
    auto endCursor = data.GetCursor() + head.len;
    while (data.GetCursor() < endCursor) {
        TLVHead headItem{};
        if (!data.ReadHead(headItem)) {
            return false;
        }
        bool result = true;
        int64_t createTime = 0;
        int64_t lastModifiedTime = 0;
        int32_t visibility = 0;
        switch (headItem.tag) {
            case static_cast<uint16_t>(TAG::TAG_KEY):
                result = TLVUtil::Reading(output.key, data, headItem);
                break;
            case static_cast<uint16_t>(TAG::TAG_IS_PRIVATE):
                result = data.ReadBasic(output.isPrivate, headItem);
                break;
            case static_cast<uint16_t>(TAG::TAG_PRIVILEGE):
                result = TLVUtil::Reading(output.privileges, data, headItem);
                break;
            case static_cast<uint16_t>(TAG::TAG_CREATE_TIME):
                result = data.ReadBasic(createTime, headItem);
                output.createTime = static_cast<time_t>(createTime);
                break;
            case static_cast<uint16_t>(TAG::TAG_SOURCE_PACKAGE):
                result = data.Read(output.sourcePackage, headItem);
                break;
            case static_cast<uint16_t>(TAG::TAG_DATA_STATUS):
                result = TLVUtil::Reading(output.dataStatus, data, headItem);
                break;
            case static_cast<uint16_t>(TAG::TAG_DATA_VERSION):
                result = data.ReadBasic(output.dataVersion, headItem);
                break;
            case static_cast<uint16_t>(TAG::TAG_LAST_MODIFIED_TIME):
                result = data.ReadBasic(lastModifiedTime, headItem);
                output.lastModifiedTime = static_cast<time_t>(lastModifiedTime);
                break;
            case static_cast<uint16_t>(TAG::TAG_CREATE_PACKAGE):
                result = data.Read(output.createPackage, headItem);
                break;
            case static_cast<uint16_t>(TAG::TAG_DEVICE_ID):
                result = data.Read(output.deviceId, headItem);
                break;
            case static_cast<uint16_t>(TAG::TAG_RECORD_TOTAL_NUM):
                result = data.ReadBasic(output.recordTotalNum, headItem);
                break;
            case static_cast<uint16_t>(TAG::TAG_TOKEN_ID):
                result = data.ReadBasic(output.tokenId, headItem);
                break;
            case static_cast<uint16_t>(TAG::TAG_VERSION):
                result = data.Read(output.sdkVersion, headItem);
                break;
            case static_cast<uint16_t>(TAG::TAG_VISIBILITY):
                result = data.ReadBasic(visibility, headItem);
                output.visibility = static_cast<UDMF::Visibility>(visibility);
                break;
            case static_cast<uint16_t>(TAG::TAG_APP_ID):
                result = data.Read(output.appId, headItem);
                break;
            default:
                result = data.Skip(headItem);
        }
        if (!result) {
            return false;
        }
    }
    return true;
}

template <> size_t CountBufferSize(const Privilege &input, TLVObject &data)
{
    return data.CountHead() + data.CountBasic(input.tokenId) + data.Count(input.readPermission) +
        data.Count(input.writePermission);
}

template <> bool Writing(const Privilege &input, TLVObject &data, TAG tag)
{
    InitWhenFirst(input, data);
    auto tagCursor = data.GetCursor();
    data.OffsetHead();
    if (!data.WriteBasic(TAG::TAG_TOKEN_ID, input.tokenId)) {
        return false;
    }
    if (!data.Write(TAG::TAG_READPERMISSION, input.readPermission)) {
        return false;
    }
    if (!data.Write(TAG::TAG_WRITEPERMISSION, input.writePermission)) {
        return false;
    }
    return data.WriteBackHead(static_cast<uint16_t>(tag), tagCursor, data.GetCursor() - tagCursor - sizeof(TLVHead));
}

template <> bool Reading(Privilege &output, TLVObject &data, const TLVHead &head)
{
    auto endCursor = data.GetCursor() + head.len;
    while (data.GetCursor() < endCursor) {
        TLVHead headItem{};
        if (!data.ReadHead(headItem)) {
            return false;
        }
        switch (headItem.tag) {
            case static_cast<uint16_t>(TAG::TAG_TOKEN_ID):
                if (!data.ReadBasic(output.tokenId, headItem)) {
                    return false;
                }
                break;
            case static_cast<uint16_t>(TAG::TAG_READPERMISSION):
                if (!data.Read(output.readPermission, headItem)) {
                    return false;
                }
                break;
            case static_cast<uint16_t>(TAG::TAG_WRITEPERMISSION):
                if (!data.Read(output.writePermission, headItem)) {
                    return false;
                }
                break;
            default:
                data.Skip(headItem);
        }
    }
    return true;
}

template <> size_t CountBufferSize(const UriInfo &input, TLVObject &data)
{
    return data.CountHead() + data.CountBasic(input.position) + data.Count(input.oriUri) +
        data.Count(input.dfsUri) + data.Count(input.authUri);
}

template <> bool Writing(const UriInfo &input, TLVObject &data, TAG tag)
{
    InitWhenFirst(input, data);
    auto tagCursor = data.GetCursor();
    data.OffsetHead();
    if (!TLVUtil::Writing(input.oriUri, data, TAG::TAG_URI_ORI)) {
        return false;
    }
    if (!TLVUtil::Writing(input.dfsUri, data, TAG::TAG_URI_DFS)) {
        return false;
    }
    if (!TLVUtil::Writing(input.authUri, data, TAG::TAG_URI_AUTH)) {
        return false;
    }
    if (!data.WriteBasic(TAG::TAG_URI_POS, input.position)) {
        return false;
    }
    return data.WriteBackHead(static_cast<uint16_t>(tag), tagCursor, data.GetCursor() - tagCursor - sizeof(TLVHead));
}

template <> bool Reading(UriInfo &output, TLVObject &data, const TLVHead &head)
{
    auto endCursor = data.GetCursor() + head.len;
    while (data.GetCursor() < endCursor) {
        TLVHead headItem{};
        if (!data.ReadHead(headItem)) {
            return false;
        }
        bool result = true;
        switch (headItem.tag) {
            case static_cast<uint16_t>(TAG::TAG_URI_ORI):
                result = TLVUtil::Reading(output.oriUri, data, headItem);
                break;
            case static_cast<uint16_t>(TAG::TAG_URI_DFS):
                result = TLVUtil::Reading(output.dfsUri, data, headItem);
                break;
            case static_cast<uint16_t>(TAG::TAG_URI_AUTH):
                result = TLVUtil::Reading(output.authUri, data, headItem);
                break;
            case static_cast<uint16_t>(TAG::TAG_URI_POS):
                result = data.ReadBasic(output.position, headItem);
                break;
            default:
                result = data.Skip(headItem);
        }
        if (!result) {
            return false;
        }
    }
    return true;
}

template <> size_t CountBufferSize(const std::shared_ptr<OHOS::Media::PixelMap> &input, TLVObject &data)
{
    std::vector<std::uint8_t> val;
    PixelMapLoader loader;
    if (!loader.EncodeTlv(input, val)) {
        LOG_ERROR(UDMF_FRAMEWORK, "Encode pixelMap error when CountBufferSize");
        return 0;
    }
    return CountBufferSize(val, data);
}

template <> bool Writing(const std::shared_ptr<OHOS::Media::PixelMap> &input, TLVObject &data, TAG tag)
{
    InitWhenFirst(input, data);
    std::vector<std::uint8_t> val;
    PixelMapLoader loader;
    if (!loader.EncodeTlv(input, val)) {
        LOG_ERROR(UDMF_FRAMEWORK, "Encode pixelMap error when Writing");
        return false;
    }
    return data.Write(tag, val);
}

template <> bool Reading(std::shared_ptr<OHOS::Media::PixelMap> &output, TLVObject &data, const TLVHead &head)
{
    std::vector<std::uint8_t> val;
    if (!data.Read(val, head)) {
        LOG_ERROR(UDMF_FRAMEWORK, "Reading u8 vector error.");
        return false;
    }
    PixelMapLoader loader;
    output = loader.DecodeTlv(val);
    if (output == nullptr) {
        LOG_ERROR(UDMF_FRAMEWORK, "DecodeTlv pixelMap error when Reading.");
        return false;
    }
    return true;
}

template <> size_t CountBufferSize(const std::shared_ptr<std::map<std::string, ValueType>> &input, TLVObject &data)
{
    if (input == nullptr) {
        return data.CountHead();
    }
    return CountBufferSize(*input, data);
}

template <> bool Writing(const std::shared_ptr<std::map<std::string, ValueType>> &input, TLVObject &data, TAG tag)
{
    if (input == nullptr) {
        return false;
    }
    InitWhenFirst(input, data);
    return Writing(*input, data, tag);
}

template <> bool Reading(std::shared_ptr<std::map<std::string, ValueType>> &output,
    TLVObject &data, const TLVHead &head)
{
    if (output == nullptr) {
        output = std::make_shared<std::map<std::string, ValueType>>();
    }
    return Reading(*output, data, head);
}

template <> size_t CountBufferSize(const std::shared_ptr<OHOS::AAFwk::Want> &input, TLVObject &data)
{
    Parcel parcel;
    if (!input->Marshalling(parcel)) {
        LOG_ERROR(UDMF_FRAMEWORK, "Marshalling want error when Count");
        return 0;
    }
    auto size = parcel.GetDataSize();
    std::vector<std::uint8_t> val(size);
    return CountBufferSize(val, data);
}

template <> bool Writing(const std::shared_ptr<OHOS::AAFwk::Want> &input, TLVObject &data, TAG tag)
{
    InitWhenFirst(input, data);
    Parcel parcel;
    if (!input->Marshalling(parcel)) {
        LOG_ERROR(UDMF_FRAMEWORK, "Marshalling want error in tlv write. tag=%{public}hu", tag);
        return false;
    }
    auto size = parcel.GetDataSize();
    auto buffer = parcel.GetData();
    std::vector<std::uint8_t> val(size);
    if (size != 0) {
        auto err = memcpy_s(val.data(), size, reinterpret_cast<const void *>(buffer), size);
        if (err != EOK) {
            LOG_ERROR(UDMF_FRAMEWORK, "memcpy error in tlv write want. tag=%{public}hu", tag);
            return false;
        }
    }
    return data.Write(tag, val);
}

template <> bool Reading(std::shared_ptr<OHOS::AAFwk::Want> &output, TLVObject &data, const TLVHead &head)
{
    std::vector<std::uint8_t> val;
    if (!data.Read(val, head)) {
        LOG_ERROR(UDMF_FRAMEWORK, "Reading u8 vector error.");
        return false;
    }

    std::shared_ptr<Parcel> parcel = std::make_shared<Parcel>();
    auto buffer = malloc(val.size());
    if (buffer == nullptr) {
        LOG_ERROR(UDMF_FRAMEWORK, "malloc error in tlv read. tag=%{public}hu", head.tag);
        return false;
    }
    auto err = memcpy_s(buffer, val.size(), val.data(), val.size());
    if (err != EOK) {
        LOG_ERROR(UDMF_FRAMEWORK, "memcpy_s error in tlv read want. tag=%{public}hu", head.tag);
        free(buffer);
        return false;
    }
    if (!parcel->ParseFrom((uintptr_t)buffer, head.len)) {
        LOG_ERROR(UDMF_FRAMEWORK, "ParseFrom error in tlv read want. tag=%{public}hu", head.tag);
        free(buffer);
        return false;
    }
    auto want = AAFwk::Want::Unmarshalling(*parcel);
    if (want == nullptr) {
        LOG_ERROR(UDMF_FRAMEWORK, "Unmarshalling want error in tlv read. tag=%{public}hu", head.tag);
        return false;
    }
    output = std::shared_ptr<OHOS::AAFwk::Want>(want);
    return true;
}

template <> size_t CountBufferSize(const Summary &input, TLVObject &data)
{
    return data.CountHead() + CountBufferSize(input.summary, data) + data.CountBasic(input.totalSize) +
        CountBufferSize(input.fileTypes, data);
}

template <> bool Writing(const Summary &input, TLVObject &data, TAG tag)
{
    InitWhenFirst(input, data);
    auto tagCursor = data.GetCursor();
    data.OffsetHead();
    if (!TLVUtil::Writing(input.summary, data, TAG::TAG_SUMMARY_MAP)) {
        return false;
    }
    if (!data.WriteBasic(TAG::TAG_SUMMARY_SIZE, input.totalSize)) {
        return false;
    }
    if (!TLVUtil::Writing(input.fileTypes, data, TAG::TAG_SUMMARY_FILE_TYPES)) {
        return false;
    }
    return data.WriteBackHead(static_cast<uint16_t>(tag), tagCursor, data.GetCursor() - tagCursor - sizeof(TLVHead));
}

template <> bool Reading(Summary &output, TLVObject &data, const TLVHead &head)
{
    auto endCursor = data.GetCursor() + head.len;
    while (data.GetCursor() < endCursor) {
        TLVHead headItem{};
        if (!data.ReadHead(headItem)) {
            return false;
        }
        switch (headItem.tag) {
            case static_cast<uint16_t>(TAG::TAG_SUMMARY_MAP):
                if (!TLVUtil::Reading(output.summary, data, headItem)) {
                    return false;
                }
                break;
            case static_cast<uint16_t>(TAG::TAG_SUMMARY_SIZE):
                if (!data.ReadBasic(output.totalSize, headItem)) {
                    return false;
                }
                break;
            case static_cast<uint16_t>(TAG::TAG_SUMMARY_FILE_TYPES):
                if (!TLVUtil::Reading(output.fileTypes, data, headItem)) {
                    return false;
                }
                break;
            default:
                data.Skip(headItem);
        }
    }
    return true;
}

template <> size_t API_EXPORT CountBufferSize(const DataLoadInfo &input, TLVObject &data)
{
    return data.CountHead() + data.Count(input.sequenceKey) + CountBufferSize(input.types, data) +
        data.CountBasic(input.recordCount);
}

template <> bool API_EXPORT Writing(const DataLoadInfo &input, TLVObject &data, TAG tag)
{
    InitWhenFirst(input, data);
    auto tagCursor = data.GetCursor();
    data.OffsetHead();
    if (!TLVUtil::Writing(input.sequenceKey, data, TAG::TAG_DATA_LOAD_KEY)) {
        return false;
    }
    if (!TLVUtil::Writing(input.types, data, TAG::TAG_SET_TYPES)) {
        return false;
    }
    if (!data.WriteBasic(TAG::TAG_RECORD_COUNT, input.recordCount)) {
        return false;
    }
    return data.WriteBackHead(static_cast<uint16_t>(tag), tagCursor, data.GetCursor() - tagCursor - sizeof(TLVHead));
}

template <> bool API_EXPORT Reading(DataLoadInfo &output, TLVObject &data, const TLVHead &head)
{
    auto endCursor = data.GetCursor() + head.len;
    while (data.GetCursor() < endCursor) {
        TLVHead headItem{};
        if (!data.ReadHead(headItem)) {
            return false;
        }
        switch (headItem.tag) {
            case static_cast<uint16_t>(TAG::TAG_DATA_LOAD_KEY):
                if (!TLVUtil::Reading(output.sequenceKey, data, headItem)) {
                    return false;
                }
                break;
            case static_cast<uint16_t>(TAG::TAG_SET_TYPES):
                if (!TLVUtil::Reading(output.types, data, headItem)) {
                    return false;
                }
                break;
            case static_cast<uint16_t>(TAG::TAG_RECORD_COUNT):
                if (!data.ReadBasic(output.recordCount, headItem)) {
                    return false;
                }
                break;
            default:
                data.Skip(headItem);
        }
    }
    return true;
}
} // namespace TLVUtil
} // namespace OHOS
