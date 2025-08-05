/*
 * Copyright (C) 2025 Huawei Device Co., Ltd.
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
#include "iremote_broker.h"
#include "message_parcel_mock.h"

namespace OHOS {
using namespace OHOS::UDMF;

Parcelable::Parcelable() : Parcelable(false)
{}

Parcelable::Parcelable(bool asRemote)
{
    asRemote_ = asRemote;
    behavior_ = 0;
}

bool MessageParcel::WriteInterfaceToken(std::u16string name)
{
    if (UdmfMessageParcel::messageParcel == nullptr) {
        return false;
    }
    return UdmfMessageParcel::messageParcel->WriteInterfaceToken(name);
}

std::u16string MessageParcel::ReadInterfaceToken()
{
    if (UdmfMessageParcel::messageParcel == nullptr) {
        return std::u16string();
    }
    return UdmfMessageParcel::messageParcel->ReadInterfaceToken();
}

bool Parcel::WriteParcelable(const Parcelable *object)
{
    if (UdmfMessageParcel::messageParcel == nullptr) {
        return false;
    }
    return UdmfMessageParcel::messageParcel->WriteParcelable(object);
}

bool Parcel::WriteInt32(int32_t value)
{
    if (UdmfMessageParcel::messageParcel == nullptr) {
        return false;
    }
    return UdmfMessageParcel::messageParcel->WriteInt32(value);
}

int32_t Parcel::ReadInt32()
{
    if (UdmfMessageParcel::messageParcel == nullptr) {
        return -1; // -1: default err
    }
    return UdmfMessageParcel::messageParcel->ReadInt32();
}

bool Parcel::ReadInt32(int32_t &value)
{
    if (UdmfMessageParcel::messageParcel == nullptr) {
        return false;
    }
    return UdmfMessageParcel::messageParcel->ReadInt32(value);
}

bool Parcel::WriteRemoteObject(const Parcelable *object)
{
    if (UdmfMessageParcel::messageParcel == nullptr) {
        return false;
    }
    return UdmfMessageParcel::messageParcel->WriteRemoteObject(object);
}

bool MessageParcel::WriteRemoteObject(const sptr<IRemoteObject> &object)
{
    if (UdmfMessageParcel::messageParcel == nullptr) {
        return false;
    }
    return UdmfMessageParcel::messageParcel->WriteRemoteObject(object);
}

sptr<IRemoteObject> MessageParcel::ReadRemoteObject()
{
    if (UdmfMessageParcel::messageParcel == nullptr) {
        return nullptr;
    }
    return UdmfMessageParcel::messageParcel->ReadRemoteObject();
}

bool Parcel::ReadBool()
{
    if (UdmfMessageParcel::messageParcel == nullptr) {
        return false;
    }
    return UdmfMessageParcel::messageParcel->ReadBool();
}

bool Parcel::ReadBool(bool &value)
{
    if (UdmfMessageParcel::messageParcel == nullptr) {
        return false;
    }
    return UdmfMessageParcel::messageParcel->ReadBool(value);
}

bool Parcel::WriteBool(bool value)
{
    if (UdmfMessageParcel::messageParcel == nullptr) {
        return false;
    }
    return UdmfMessageParcel::messageParcel->WriteBool(value);
}

bool Parcel::WriteString(const std::string &value)
{
    if (UdmfMessageParcel::messageParcel == nullptr) {
        return false;
    }
    return UdmfMessageParcel::messageParcel->WriteString(value);
}

bool Parcel::WriteCString(const char *value)
{
    if (UdmfMessageParcel::messageParcel == nullptr) {
        return false;
    }
    return UdmfMessageParcel::messageParcel->WriteCString(value);
}

bool Parcel::ReadString(std::string &value)
{
    if (UdmfMessageParcel::messageParcel == nullptr) {
        return false;
    }
    return UdmfMessageParcel::messageParcel->ReadString(value);
}

bool Parcel::ReadStringVector(std::vector<std::string> *value)
{
    if (UdmfMessageParcel::messageParcel == nullptr) {
        return false;
    }
    return UdmfMessageParcel::messageParcel->ReadStringVector(value);
}

bool MessageParcel::WriteFileDescriptor(int fd)
{
    if (UdmfMessageParcel::messageParcel == nullptr) {
        return false;
    }
    return UdmfMessageParcel::messageParcel->WriteFileDescriptor(fd);
}

int MessageParcel::ReadFileDescriptor()
{
    if (UdmfMessageParcel::messageParcel == nullptr) {
        return -1; // -1: default err
    }
    return UdmfMessageParcel::messageParcel->ReadFileDescriptor();
}

bool Parcel::ReadUint32(uint32_t &value)
{
    if (UdmfMessageParcel::messageParcel == nullptr) {
        return false;
    }
    return UdmfMessageParcel::messageParcel->ReadUint32(value);
}

bool Parcel::WriteUint64(uint64_t value)
{
    if (UdmfMessageParcel::messageParcel == nullptr) {
        return false;
    }
    return UdmfMessageParcel::messageParcel->WriteUint64(value);
}

bool Parcel::WriteUint16(uint16_t value)
{
    if (UdmfMessageParcel::messageParcel == nullptr) {
        return false;
    }
    return UdmfMessageParcel::messageParcel->WriteUint16(value);
}

bool Parcel::ReadUint64(uint64_t &value)
{
    if (UdmfMessageParcel::messageParcel == nullptr) {
        return false;
    }
    return UdmfMessageParcel::messageParcel->ReadUint64(value);
}

bool Parcel::WriteStringVector(const std::vector<std::string> &val)
{
    if (UdmfMessageParcel::messageParcel == nullptr) {
        return false;
    }
    return UdmfMessageParcel::messageParcel->WriteStringVector(val);
}

bool Parcel::WriteUint32(uint32_t value)
{
    if (UdmfMessageParcel::messageParcel) {
        return UdmfMessageParcel::messageParcel->WriteUint32(value);
    }
    return false;
}

bool MessageParcel::WriteRawData(const void *data, size_t size)
{
    if (UdmfMessageParcel::messageParcel) {
        return UdmfMessageParcel::messageParcel->WriteRawData(data, size);
    }
    return false;
}

const void *MessageParcel::ReadRawData(size_t size)
{
    if (UdmfMessageParcel::messageParcel) {
        return UdmfMessageParcel::messageParcel->ReadRawData(size);
    }
    return nullptr;
}

uint32_t Parcel::ReadUint32()
{
    if (UdmfMessageParcel::messageParcel) {
        return UdmfMessageParcel::messageParcel->ReadUint32();
    }
    return 1; // : default value
}

size_t Parcel::GetDataSize() const
{
    if (UdmfMessageParcel::messageParcel) {
        return UdmfMessageParcel::messageParcel->GetDataSize();
    }
    return 1; // : default value
}
} // namespace OHOS