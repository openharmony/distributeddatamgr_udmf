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

#define LOG_TAG "TlvObject"
#include "tlv_object.h"
#include <string>
#include <map>
#include "logger.h"

namespace OHOS {
namespace UDMF {
TLVObject::TLVObject(std::vector<std::uint8_t> &buffer)
{
    total_ += buffer.size();
    buffer_ = &buffer;
    cursor_ = 0;
    file_ = nullptr;
}

void TLVObject::SetFile(std::FILE *file)
{
    file_ = file;
}

void TLVObject::UpdateSize()
{
    if (file_ != nullptr) {
        return;
    }
    buffer_->resize(total_);
}

std::vector<std::uint8_t> TLVObject::GetBuffer()
{
    return *buffer_;
}

void TLVObject::Count(const uint32_t value)
{
    total_ += sizeof(value) + sizeof(TLVHead);
}

void TLVObject::Count(const uint64_t value)
{
    total_ += sizeof(value) + sizeof(TLVHead);
}

void TLVObject::Count(const int32_t value)
{
    total_ += sizeof(value) + sizeof(TLVHead);
}

void TLVObject::Count(const int64_t value)
{
    total_ += sizeof(value) + sizeof(TLVHead);
}

void TLVObject::Count(const float value)
{
    total_ += sizeof(value) + sizeof(TLVHead);
}

void TLVObject::Count(const double value)
{
    total_ += sizeof(value) + sizeof(TLVHead);
}

void TLVObject::Count(const std::string &value)
{
    total_ += value.size() + sizeof(TLVHead);
}

void TLVObject::Count(const std::vector<uint8_t> &value)
{
    std::size_t expectSize = sizeof(TLVHead);
    expectSize += value.size();
    total_ += expectSize;
}

void TLVObject::Count(const UDDetails &value)
{
    for (auto &item : value) {
        Count(item.first);
        Count(item.second);
    }
    total_ += sizeof(TLVHead);
}

void TLVObject::Count(const UnifiedKey &value)
{
    Count(value.key);
    Count(value.intention);
    Count(value.bundleName);
    Count(value.groupId);
}

void TLVObject::Count(const Privilege &value)
{
    Count(value.tokenId);
    Count(value.readPermission);
    Count(value.writePermission);
}

void TLVObject::Count(const OHOS::AAFwk::Want &value)
{
    std::size_t expectSize = sizeof(TLVHead);
    Parcel parcel;
    if (!value.Marshalling(parcel)) {
        LOG_ERROR(TlvObject, "Marshalling Want failed.");
        return;
    }
    expectSize += parcel.GetDataSize();
    total_ += expectSize;
}

void TLVObject::Count(const OHOS::Media::PixelMap &value)
{
    std::size_t expectSize = sizeof(TLVHead);
    std::vector<std::uint8_t> val;
    if (!value.EncodeTlv(val)) {
        LOG_ERROR(TlvObject, "Marshalling PixelMap failed.");
        return;
    }
    expectSize += val.size();
    total_ += expectSize;
}

void TLVObject::Count(const Object &value)
{
    for (auto &item : value.value_) {
        Count(item.first);
        Count(item.second);
    }
    total_ += sizeof(TLVHead);
}

void TLVObject::Count(const std::monostate &value)
{
    total_ += sizeof(TLVHead);
}

bool TLVObject::WriteString(const std::string &value)
{
    PrepareBuffer(sizeof(TLVHead) + value.size());
    if (!HasExpectBuffer(sizeof(TLVHead) + value.size())) {
        return false;
    }
    auto *tlvHead = reinterpret_cast<TLVHead *>(buffer_->data() + cursor_);
    tlvHead->tag = HostToNet(static_cast<uint16_t>(TAG::TAG_STRING));
    tlvHead->len = HostToNet((uint32_t)value.size());
    if (!value.empty()) {
        auto err = memcpy_s(tlvHead->value, value.size(), value.c_str(), value.size());
        if (err != EOK) {
            return false;
        }
    }
    if (!SaveBufferToFile()) {
        return false;
    }
    cursor_ += sizeof(TLVHead) + value.size();
    return true;
}

bool TLVObject::ReadString(std::string &value)
{
    TLVHead head {};
    if (!ReadHead(head)) {
        return false;
    }
    if (!HasExpectBuffer(head.len)) {
        return false;
    }
    if (!LoadBufferFormFile(head.len)) {
        return false;
    }
    value.append(reinterpret_cast<const char *>(buffer_->data() + cursor_), head.len);
    cursor_ += head.len;
    if (file_ != nullptr) {
        cursor_ += sizeof(TLVHead);
    }
    return true;
}

bool TLVObject::WriteVector(const std::vector<uint8_t> &value)
{
    PrepareBuffer(sizeof(TLVHead) + value.size());
    if (!HasExpectBuffer(sizeof(TLVHead) + value.size())) {
        return false;
    }
    WriteHead(static_cast<uint16_t>(TAG::TAG_VECTOR), cursor_, value.size());
    cursor_ += sizeof(TLVHead);

    if (!value.empty()) {
        auto err = memcpy_s(buffer_->data() + cursor_, buffer_->size() - cursor_, value.data(), value.size());
        if (err != EOK) {
            return false;
        }
    }
    if (!SaveBufferToFile()) {
        return false;
    }
    cursor_ += value.size();
    return true;
}

bool TLVObject::ReadVector(std::vector<uint8_t> &value)
{
    TLVHead head {};
    if (!ReadHead(head)) {
        return false;
    }
    if (!HasExpectBuffer(head.len)) {
        return false;
    }
    if (!LoadBufferFormFile(head.len)) {
        return false;
    }
    std::vector<uint8_t> buff(buffer_->data() + cursor_, buffer_->data() + cursor_ + head.len);
    value = std::move(buff);
    cursor_ += head.len;
    if (file_ != nullptr) {
        cursor_ += sizeof(TLVHead);
    }
    return true;
}

bool TLVObject::WriteVariantInner(TAG &tag, const UDVariant &value)
{
    auto int32Value = std::get_if<int32_t>(&value);
    if (int32Value != nullptr) {
        if (!WriteBasic(TAG::TAG_INT32, std::get<int32_t>(value))) {
            return false;
        }
        tag = TAG::TAG_INT32;
    }
    auto int64Value = std::get_if<int64_t>(&value);
    if (int64Value != nullptr) {
        if (!WriteBasic(TAG::TAG_INT64, std::get<int64_t>(value))) {
            return false;
        }
        tag = TAG::TAG_INT64;
    }
    auto boolValue = std::get_if<bool>(&value);
    if (boolValue != nullptr) {
        if (!WriteBasic(TAG::TAG_BOOL, std::get<bool>(value))) {
            return false;
        }
        tag = TAG::TAG_BOOL;
    }
    auto doubleValue = std::get_if<double>(&value);
    if (doubleValue != nullptr) {
        if (!WriteBasic(TAG::TAG_DOUBLE, std::get<double>(value))) {
            return false;
        }
        tag = TAG::TAG_DOUBLE;
    }
    auto stringValue = std::get_if<std::string>(&value);
    if (stringValue != nullptr) {
        if (!WriteString(std::get<std::string>(value))) {
            return false;
        }
        tag = TAG::TAG_STRING;
    }
    auto vectorValue = std::get_if<std::vector<uint8_t>>(&value);
    if (vectorValue != nullptr) {
        if (!WriteVector(std::get<std::vector<uint8_t>>(value))) {
            return false;
        }
        tag = TAG::TAG_VECTOR;
    }
    return true;
}

bool TLVObject::WriteVariant(const UDVariant &value)
{
    if (!HasExpectBuffer(sizeof(TLVHead))) {
        return false;
    }
    if (file_ != nullptr) {
        std::vector<uint8_t> reserved {};
        reserved.resize(sizeof(TLVHead));
        if (fwrite(reserved.data(), sizeof(uint8_t), reserved.size(), file_) != reserved.size()) {
            return false;
        }
    }
    auto tagCursor = cursor_;
    cursor_ += sizeof(TLVHead);
    auto valueCursor = cursor_;
    TAG tag = TAG::TAG_BUTT;
    if (!WriteVariantInner(tag, value)) {
        return false;
    }
    PrepareHeader(cursor_, tagCursor, valueCursor);
    WriteHead(static_cast<uint16_t>(tag), tagCursor, cursor_ - valueCursor);
    if (!SaveBufferToFile()) {
        return false;
    }
    if (file_ != nullptr) {
        fseek(file_, 0, SEEK_END);
        cursor_ += sizeof(TLVHead);
    }
    return true;
}

bool TLVObject::ReadVariantInner(uint16_t tag, UDVariant &value)
{
    switch (tag) {
        case static_cast<uint16_t>(TAG::TAG_INT32): {
            int32_t int32Value;
            if (!ReadBasic(int32Value)) {
                return false;
            }
            value.emplace<int32_t>(int32Value);
            break;
        }
        case static_cast<uint16_t>(TAG::TAG_INT64): {
            int64_t int64Value;
            if (!ReadBasic(int64Value)) {
                return false;
            }
            value.emplace<int64_t>(int64Value);
            break;
        }
        case static_cast<uint16_t>(TAG::TAG_BOOL): {
            bool boolValue;
            if (!ReadBasic(boolValue)) {
                return false;
            }
            value.emplace<bool>(boolValue);
            break;
        }
        case static_cast<uint16_t>(TAG::TAG_DOUBLE): {
            double doubleValue;
            if (!ReadBasic(doubleValue)) {
                return false;
            }
            value.emplace<double>(doubleValue);
            break;
        }
        default: {
            return false;
        }
    }
    return true;
}

bool TLVObject::ReadVariant(UDVariant &value)
{
    TLVHead head {};
    if (!ReadHead(head)) {
        return false;
    }
    if (!HasExpectBuffer(head.len)) {
        return false;
    }
    switch (head.tag) {
        case static_cast<uint16_t>(TAG::TAG_INT32):
        case static_cast<uint16_t>(TAG::TAG_INT64):
        case static_cast<uint16_t>(TAG::TAG_BOOL):
        case static_cast<uint16_t>(TAG::TAG_DOUBLE): {
            if (!ReadVariantInner(head.tag, value)) {
                return false;
            }
            break;
        }
        case static_cast<uint16_t>(TAG::TAG_STRING): {
            std::string stringValue;
            if (!ReadString(stringValue)) {
                return false;
            }
            value.emplace<std::string>(stringValue);
            break;
        }
        case static_cast<uint16_t>(TAG::TAG_VECTOR): {
            std::vector<uint8_t> vectorValue;
            if (!ReadVector(vectorValue)) {
                return false;
            }
            value.emplace<std::vector<uint8_t>>(vectorValue);
            break;
        }
        default: {
            return false;
        }
    }

    if (file_ != nullptr) {
        cursor_ += sizeof(TLVHead);
    }
    return true;
}

bool TLVObject::WriteVariantInner(TAG &tag, const ValueType &value)
{
    auto int32Value = std::get_if<int32_t>(&value);
    if (int32Value != nullptr) {
        if (!WriteBasic(TAG::TAG_INT32, std::get<int32_t>(value))) {
            return false;
        }
        tag = TAG::TAG_INT32;
    }
    auto int64Value = std::get_if<int64_t>(&value);
    if (int64Value != nullptr) {
        if (!WriteBasic(TAG::TAG_INT64, std::get<int64_t>(value))) {
            return false;
        }
        tag = TAG::TAG_INT64;
    }
    auto boolValue = std::get_if<bool>(&value);
    if (boolValue != nullptr) {
        if (!WriteBasic(TAG::TAG_BOOL, std::get<bool>(value))) {
            return false;
        }
        tag = TAG::TAG_BOOL;
    }
    auto doubleValue = std::get_if<double>(&value);
    if (doubleValue != nullptr) {
        if (!WriteBasic(TAG::TAG_DOUBLE, std::get<double>(value))) {
            return false;
        }
        tag = TAG::TAG_DOUBLE;
    }
    auto stringValue = std::get_if<std::string>(&value);
    if (stringValue != nullptr) {
        if (!WriteString(std::get<std::string>(value))) {
            return false;
        }
        tag = TAG::TAG_STRING;
    }
    auto vectorValue = std::get_if<std::vector<uint8_t>>(&value);
    if (vectorValue != nullptr) {
        if (!WriteVector(std::get<std::vector<uint8_t>>(value))) {
            return false;
        }
        tag = TAG::TAG_VECTOR;
    }
    auto wantValue = std::get_if<std::shared_ptr<OHOS::AAFwk::Want>>(&value);
    if (wantValue != nullptr) {
        if (!WriteWant(std::get<std::shared_ptr<OHOS::AAFwk::Want>>(value))) {
            return false;
        }
        tag = TAG::TAG_WANT;
    }
    auto pixelMapValue = std::get_if<std::shared_ptr<OHOS::Media::PixelMap>>(&value);
    if (pixelMapValue != nullptr) {
        if (!WritePixelMap(std::get<std::shared_ptr<OHOS::Media::PixelMap>>(value))) {
            return false;
        }
        tag = TAG::TAG_PIXELMAP;
    }
    auto objectValue = std::get_if<std::shared_ptr<Object>>(&value);
    if (objectValue != nullptr) {
        if (!WriteMap(std::get<std::shared_ptr<Object>>(value))) {
            return false;
        }
        tag = TAG::TAG_OBJECT;
    }
    return true;
}

bool TLVObject::WriteVariant(const ValueType &value)
{
    if (!HasExpectBuffer(sizeof(TLVHead))) {
        return false;
    }
    if (file_ != nullptr) {
        std::vector<uint8_t> reserved {};
        reserved.resize(sizeof(TLVHead));
        if (fwrite(reserved.data(), sizeof(uint8_t), reserved.size(), file_) != reserved.size()) {
            return false;
        }
    }
    auto tagCursor = cursor_;
    cursor_ += sizeof(TLVHead);
    auto valueCursor = cursor_;
    TAG tag = TAG::TAG_BUTT;
    if (!WriteVariantInner(tag, value)) {
        return false;
    }
    PrepareHeader(cursor_, tagCursor, valueCursor);
    WriteHead(static_cast<uint16_t>(tag), tagCursor, cursor_ - valueCursor);
    if (!SaveBufferToFile()) {
        return false;
    }
    if (file_ != nullptr) {
        fseek(file_, 0, SEEK_END);
        cursor_ += sizeof(TLVHead);
    }
    return true;
}

bool TLVObject::ReadVariantInner(uint16_t tag, ValueType &value)
{
    switch (tag) {
        case static_cast<uint16_t>(TAG::TAG_INT32): {
            int32_t int32Value;
            if (!ReadBasic(int32Value)) {
                return false;
            }
            value.emplace<int32_t>(int32Value);
            break;
        }
        case static_cast<uint16_t>(TAG::TAG_INT64): {
            int64_t int64Value;
            if (!ReadBasic(int64Value)) {
                return false;
            }
            value.emplace<int64_t>(int64Value);
            break;
        }
        case static_cast<uint16_t>(TAG::TAG_BOOL): {
            bool boolValue;
            if (!ReadBasic(boolValue)) {
                return false;
            }
            value.emplace<bool>(boolValue);
            break;
        }
        case static_cast<uint16_t>(TAG::TAG_DOUBLE): {
            double doubleValue;
            if (!ReadBasic(doubleValue)) {
                return false;
            }
            value.emplace<double>(doubleValue);
            break;
        }
        default: {
            return false;
        }
    }
    return true;
}

bool TLVObject::ReadVariant(ValueType &value)
{
    TLVHead head {};
    if (!ReadHead(head)) {
        return false;
    }
    if (!HasExpectBuffer(head.len)) {
        return false;
    }
    switch (head.tag) {
        case static_cast<uint16_t>(TAG::TAG_INT32):
        case static_cast<uint16_t>(TAG::TAG_INT64):
        case static_cast<uint16_t>(TAG::TAG_BOOL):
        case static_cast<uint16_t>(TAG::TAG_DOUBLE): {
            if (!ReadVariantInner(head.tag, value)) {
                return false;
            }
            break;
        }
        case static_cast<uint16_t>(TAG::TAG_STRING): {
            std::string stringValue;
            if (!ReadString(stringValue)) {
                return false;
            }
            value.emplace<std::string>(stringValue);
            break;
        }
        case static_cast<uint16_t>(TAG::TAG_VECTOR): {
            std::vector<uint8_t> vectorValue;
            if (!ReadVector(vectorValue)) {
                return false;
            }
            value.emplace<std::vector<uint8_t>>(vectorValue);
            break;
        }
        case static_cast<uint16_t>(TAG::TAG_WANT): {
            std::shared_ptr<OHOS::AAFwk::Want> wantValue = nullptr;
            if (!ReadWant(wantValue)) {
                return false;
            }
            value.emplace<std::shared_ptr<OHOS::AAFwk::Want>>(wantValue);
            break;
        }
        case static_cast<uint16_t>(TAG::TAG_PIXELMAP): {
            std::shared_ptr<OHOS::Media::PixelMap> pixelMapValue = nullptr;
            if (!ReadPixelMap(pixelMapValue)) {
                return false;
            }
            value.emplace<std::shared_ptr<OHOS::Media::PixelMap>>(pixelMapValue);
            break;
        }
        case static_cast<uint16_t>(TAG::TAG_OBJECT): {
            std::shared_ptr<Object> objectValue = nullptr;
            if (!ReadMap(objectValue)) {
                return false;
            }
            value.emplace<std::shared_ptr<Object>>(objectValue);
            break;
        }
        default: {
            return false;
        }
    }
    if (file_ != nullptr) {
        cursor_ += sizeof(TLVHead);
    }
    return true;
}

bool TLVObject::WriteMap(const UDDetails &value)
{
    if (!HasExpectBuffer(sizeof(TLVHead))) {
        return false;
    }
    if (file_ != nullptr) {
        std::vector<uint8_t> reserved {};
        reserved.resize(sizeof(TLVHead));
        if (fwrite(reserved.data(), sizeof(uint8_t), reserved.size(), file_) != reserved.size()) {
            return false;
        }
    }

    auto tagCursor = cursor_;
    cursor_ += sizeof(TLVHead);
    auto valueCursor = cursor_;

    size_t total = 0;
    for (const auto &item : value) {
        if (!WriteString(item.first)) {
            return false;
        }
        total += cursor_;

        if (!WriteVariant(item.second)) {
            return false;
        }
        total += cursor_;
    }
    PrepareHeader(total, tagCursor, valueCursor);
    WriteHead(static_cast<uint16_t>(TAG::TAG_MAP), tagCursor, cursor_ - valueCursor);
    if (!SaveBufferToFile()) {
        return false;
    }
    if (file_ != nullptr) {
        fseek(file_, 0, SEEK_END);
    }
    return true;
}

bool TLVObject::ReadMap(UDDetails &value)
{
    TLVHead head {};
    if (!ReadHead(head)) {
        return false;
    }
    if (!HasExpectBuffer(head.len)) {
        return false;
    }
    if (file_ != nullptr) {
        cursor_ = 0;
    }
    auto mapEnd = cursor_ + head.len;
    size_t total = 0;
    while ((file_ == nullptr && cursor_ < mapEnd) || (file_ != nullptr && total < head.len)) {
        std::string itemKey = "";
        if (!ReadString(itemKey)) {
            return false;
        }
        total += cursor_;
        UDVariant itemValue;
        if (!ReadVariant(itemValue)) {
            return false;
        }
        total += cursor_;
        value.emplace(itemKey, itemValue);
    }
    return true;
}

bool TLVObject::WriteMap(const std::shared_ptr<Object> &value)
{
    if (!HasExpectBuffer(sizeof(TLVHead))) {
        return false;
    }
    if (file_ != nullptr) {
        std::vector<uint8_t> reserved {};
        reserved.resize(sizeof(TLVHead));
        if (fwrite(reserved.data(), sizeof(uint8_t), reserved.size(), file_) != reserved.size()) {
            return false;
        }
    }

    auto tagCursor = cursor_;
    cursor_ += sizeof(TLVHead);
    auto valueCursor = cursor_;

    size_t total = 0;
    for (const auto &item : value->value_) {
        if (!WriteString(item.first)) {
            return false;
        }
        total += cursor_;

        if (!WriteVariant(item.second)) {
            return false;
        }
        total += cursor_;
    }
    PrepareHeader(total, tagCursor, valueCursor);
    WriteHead(static_cast<uint16_t>(TAG::TAG_MAP), tagCursor, cursor_ - valueCursor);
    if (!SaveBufferToFile()) {
        return false;
    }
    if (file_ != nullptr) {
        fseek(file_, 0, SEEK_END);
    }
    return true;
}

bool TLVObject::ReadMap(std::shared_ptr<Object> &value)
{
    TLVHead head {};
    if (!ReadHead(head)) {
        return false;
    }
    if (!HasExpectBuffer(head.len)) {
        return false;
    }
    if (file_ != nullptr) {
        cursor_ = 0;
    }
    value = std::make_shared<Object>();
    auto mapEnd = cursor_ + head.len;
    size_t total = 0;
    while ((file_ == nullptr && cursor_ < mapEnd) || (file_ != nullptr && total < head.len)) {
        std::string itemKey = "";
        if (!ReadString(itemKey)) {
            return false;
        }
        total += cursor_;
        ValueType itemValue;
        if (!ReadVariant(itemValue)) {
            return false;
        }
        total += cursor_;
        value->value_.emplace(itemKey, itemValue);
    }
    return true;
}

bool TLVObject::WriteWant(const std::shared_ptr<OHOS::AAFwk::Want> &value)
{
    Parcel parcel;
    if (!value->Marshalling(parcel)) {
        LOG_ERROR(TlvObject, "Marshalling Want failed.");
        return false;
    }
    auto size = parcel.GetDataSize();
    auto buffer = parcel.GetData();

    PrepareBuffer(sizeof(TLVHead) + size);
    if (!HasExpectBuffer(sizeof(TLVHead) + size)) {
        return false;
    }
    WriteHead(static_cast<uint16_t>(TAG::TAG_WANT), cursor_, size);
    cursor_ += sizeof(TLVHead);

    if (size != 0) {
        auto err = memcpy_s(buffer_->data() + cursor_, buffer_->size() - cursor_,
            reinterpret_cast<const void *>(buffer), size);
        if (err != EOK) {
            return false;
        }
    }
    if (SaveBufferToFile()) {
        return false;
    }
    cursor_ += size;
    return true;
}

bool TLVObject::ReadWant(std::shared_ptr<OHOS::AAFwk::Want> &value)
{
    TLVHead head {};
    if (!ReadHead(head)) {
        return false;
    }
    if (!HasExpectBuffer(head.len)) {
        return false;
    }
    if (!LoadBufferFormFile(head.len)) {
        return false;
    }
    std::vector<uint8_t> buff(buffer_->data() + cursor_, buffer_->data() + cursor_ + head.len);

    auto buffer = (uintptr_t)(buff.data() + cursor_);
    cursor_ += head.len;
    if (file_ != nullptr) {
        cursor_ += sizeof(TLVHead);
    }

    Parcel parcel;
    if (!parcel.ParseFrom(buffer, head.len)) {
        return false;
    }
    auto want = AAFwk::Want::Unmarshalling(parcel);
    if (want != nullptr) {
        return false;
    }
    value = std::make_shared<OHOS::AAFwk::Want>(*want);
    return true;
}

bool TLVObject::WritePixelMap(const std::shared_ptr<OHOS::Media::PixelMap> &value)
{
    std::vector<std::uint8_t> val;
    if (!value->EncodeTlv(val)) {
        return false;
    }

    PrepareBuffer(sizeof(TLVHead) + val.size());
    if (!HasExpectBuffer(sizeof(TLVHead) + val.size())) {
        return false;
    }
    WriteHead(static_cast<uint16_t>(TAG::TAG_PIXELMAP), cursor_, val.size());
    cursor_ += sizeof(TLVHead);

    if (!val.empty()) {
        auto err = memcpy_s(buffer_->data() + cursor_, buffer_->size() - cursor_, val.data(), val.size());
        if (err != EOK) {
            return false;
        }
    }
    if (!SaveBufferToFile()) {
        return false;
    }
    cursor_ += val.size();
    return true;
}

bool TLVObject::ReadPixelMap(std::shared_ptr<OHOS::Media::PixelMap> &value)
{
    TLVHead head {};
    if (!ReadHead(head)) {
        return false;
    }
    if (!HasExpectBuffer(head.len)) {
        return false;
    }
    if (!LoadBufferFormFile(head.len)) {
        return false;
    }
    std::vector<uint8_t> buff(buffer_->data() + cursor_, buffer_->data() + cursor_ + head.len);
    value = std::shared_ptr<OHOS::Media::PixelMap>(OHOS::Media::PixelMap::DecodeTlv(buff));

    cursor_ += head.len;
    if (file_ != nullptr) {
        cursor_ += sizeof(TLVHead);
    }
    return true;
}

bool TLVObject::ReadHead(TLVHead &head)
{
    if (!LoadBufferFormFile(sizeof(TLVHead))) {
        return false;
    }
    if (!HasExpectBuffer(sizeof(TLVHead))) {
        return false;
    }
    const auto *pHead = reinterpret_cast<const TLVHead *>(buffer_->data() + cursor_);
    if (!HasExpectBuffer(NetToHost(pHead->len)) &&
        !HasExpectBuffer(NetToHost(pHead->len) + sizeof(TLVHead))) {
        return false;
    }
    head.tag = NetToHost(pHead->tag);
    head.len = NetToHost(pHead->len);
    cursor_ += sizeof(TLVHead);
    return true;
}

void TLVObject::WriteHead(uint16_t type, size_t tagCursor, uint32_t len)
{
    auto *tlvHead = reinterpret_cast<TLVHead *>(buffer_->data() + tagCursor);
    tlvHead->tag = HostToNet(type);
    tlvHead->len = HostToNet(len);
}

bool TLVObject::HasExpectBuffer(const uint32_t expectLen) const
{
    if (file_ != nullptr) {
        return true;
    }
    if (buffer_== nullptr) {
        return false;
    }
    return buffer_->size() >= cursor_ && buffer_->size() - cursor_ >= expectLen;
}

void TLVObject::PrepareHeader(size_t size, size_t &tagCursor, size_t &valueCursor)
{
    if (file_ != nullptr) {
        cursor_ = size;
        fseek(file_, -static_cast<long long>(cursor_) - sizeof(TLVHead), SEEK_CUR);
        buffer_->resize(sizeof(TLVHead));
        tagCursor  = 0;
        valueCursor = 0;
    }
}

void TLVObject::PrepareBuffer(size_t size)
{
    if (file_ == nullptr) {
        return;
    }
    buffer_->resize(size);
    cursor_ = 0;
}

bool TLVObject::SaveBufferToFile()
{
    if (file_ == nullptr) {
        return true;
    }
    auto count = fwrite(buffer_->data(), sizeof(uint8_t), buffer_->size(), file_);
    if (count != buffer_->size()) {
        return false;
    }
    return true;
}

bool TLVObject::LoadBufferFormFile(size_t size)
{
    if (file_ == nullptr) {
        return true;
    }
    buffer_->resize(size);
    auto count = fread(buffer_->data(), sizeof(uint8_t), buffer_->size(), file_);
    if (count != buffer_->size()) {
        return false;
    }
    cursor_ = 0;
    return true;
}
} // namespace UDMF
} // namespace OHOS