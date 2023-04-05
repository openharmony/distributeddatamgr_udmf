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

#ifndef UDMF_TLV_OBJECT_H
#define UDMF_TLV_OBJECT_H

#include "logger.h"
#include "securec.h"
#include "error_code.h"
#include "unified_meta.h"
#include "unified_types.h"
#include "endian_converter.h"

namespace OHOS {
namespace UDMF {
enum TAG : uint16_t {
    TAG_INT32 = 0x0000,
    TAG_INT64,
    TAG_BOOL,
    TAG_DOUBLE,
    TAG_STRING,
    TAG_VECTOR,
    TAG_MAP,
    TAG_BUTT,
};

#pragma pack(1)
struct TLVHead {
    uint16_t tag;
    uint32_t len;
    std::uint8_t value[0];
};
#pragma pack()

class TLVObject {
public:
    TLVObject() = default;
    ~TLVObject() = default;
    explicit TLVObject(std::vector<std::uint8_t> &buffer)
    {
        total_ += buffer.size();
        buffer_ = &buffer;
        cursor_ = 0;
    }

    void UpdateSize()
    {
        buffer_->resize(total_);
    }

    std::vector<std::uint8_t> GetBuffer()
    {
        return *buffer_;
    }

    void Count(const int32_t value)
    {
        total_ += sizeof(value) + sizeof(TLVHead);
    }

    void Count(const int64_t value)
    {
        total_ += sizeof(value) + sizeof(TLVHead);
    }

    void Count(const float value)
    {
        total_ += sizeof(value) + sizeof(TLVHead);
    }

    void Count(const double value)
    {
        total_ += sizeof(value) + sizeof(TLVHead);
    }

    void Count(const std::string &value)
    {
        total_ += value.size() + sizeof(TLVHead);
    }

    void Count(const std::vector<uint8_t> &value)
    {
        std::size_t expectSize = sizeof(TLVHead);
        expectSize += value.size();
        total_ += expectSize;
    }

    void Count(const UDVariant &value)
    {
        total_ += sizeof(TLVHead);
        auto int32Value = std::get_if<int32_t>(&value);
        if (int32Value != nullptr) {
            Count(std::get<int32_t>(value));
            return;
        }
        auto int64Value = std::get_if<int64_t>(&value);
        if (int64Value != nullptr) {
            Count(std::get<int64_t>(value));
            return;
        }
        auto boolValue = std::get_if<bool>(&value);
        if (boolValue != nullptr) {
            Count(std::get<bool>(value));
            return;
        }
        auto doubleValue = std::get_if<double>(&value);
        if (doubleValue != nullptr) {
            Count(std::get<double>(value));
            return;
        }
        auto strValue = std::get_if<std::string>(&value);
        if (strValue != nullptr) {
            Count(std::get<std::string>(value));
            return;
        }
        auto vecValue = std::get_if<std::vector<uint8_t>>(&value);
        if (vecValue != nullptr) {
            Count(std::get<std::vector<uint8_t>>(value));
            return;
        }
        total_ += sizeof(TLVHead);
    }

    void Count(const UDDetails &value)
    {
        for (auto &item : value) {
            Count(item.first);
            Count(item.second);
        }
        total_ += sizeof(TLVHead);
    }

    void Count(const UnifiedKey &value)
    {
        Count(value.key);
        Count(value.intention);
        Count(value.bundleName);
        Count(value.groupId);
    }

    void Count(const Privilege &value)
    {
        Count(value.tokenId);
        Count(value.pid);
        Count(value.readPermission);
        Count(value.writePermission);
    }

    template<typename T>
    bool WriteBasic(uint16_t type, const T &value)
    {
        if (!HasExpectBuffer(sizeof(TLVHead) + sizeof(value))) {
            return false;
        }
        auto *tlvHead = reinterpret_cast<TLVHead*>(buffer_->data() + cursor_);
        tlvHead->tag = HostToNet(type);
        tlvHead->len = HostToNet((uint32_t)sizeof(value));
        auto valueBuff = HostToNet(value);
        auto ret = memcpy_s(tlvHead->value, sizeof(value), &valueBuff, sizeof(value));
        if (ret != EOK) {
            return false;
        }
        cursor_ += sizeof(TLVHead) + sizeof(value);
        return true;
    }

    template<typename T>
    bool ReadBasic(T &value)
    {
        TLVHead head{};
        if (!ReadHead(head)) {
            return false;
        }
        if (head.len == 0) {
            return false;
        }
        if (!HasExpectBuffer(head.len)) {
            return false;
        }
        auto ret = memcpy_s(&value, sizeof(T), buffer_->data() + cursor_, sizeof(T));
        if (ret != EOK) {
            return false;
        }
        value = NetToHost(value);
        cursor_ += sizeof(T);
        return true;
    }

    bool WriteString(const std::string &value)
    {
        if (!HasExpectBuffer(sizeof(TLVHead) + value.size())) {
            return false;
        }
        auto *tlvHead = reinterpret_cast<TLVHead *>(buffer_->data() + cursor_);
        tlvHead->tag = HostToNet(TAG_STRING);
        tlvHead->len = HostToNet((uint32_t)value.size());
        if (!value.empty()) {
            auto err = memcpy_s(tlvHead->value, value.size(), value.c_str(), value.size());
            if (err != EOK) {
                return false;
            }
        }
        cursor_ += sizeof(TLVHead) + value.size();
        return true;
    }

    bool ReadString(std::string &value)
    {
        TLVHead head{};
        if (!ReadHead(head)) {
            return false;
        }
        if (!HasExpectBuffer(head.len)) {
            return false;
        }
        value.append(reinterpret_cast<const char *>(buffer_->data() + cursor_), head.len);
        cursor_ += head.len;
        return true;
    }

    bool WriteVector(const std::vector<uint8_t> &value)
    {
        if (!HasExpectBuffer(sizeof(TLVHead) + value.size())) {
            return false;
        }
        WriteHead(TAG_VECTOR, cursor_, value.size());
        cursor_ += sizeof(TLVHead);

        if (!value.empty()) {
            auto err = memcpy_s(buffer_->data() + cursor_, buffer_->size() - cursor_, value.data(), value.size());
            if (err != EOK) {
                return false;
            }
        }
        cursor_ += value.size();
        return true;
    }

    bool ReadVector(std::vector<uint8_t> &value)
    {
        TLVHead head{};
        if (!ReadHead(head)) {
            return false;
        }
        if (!HasExpectBuffer(head.len)) {
            return false;
        }
        std::vector<uint8_t> buff(buffer_->data() + cursor_, buffer_->data() + cursor_ + head.len);
        value = std::move(buff);
        cursor_ += head.len;
        return true;
    }

    bool WriteVariant(const UDVariant &value)
    {
        if (!HasExpectBuffer(sizeof(TLVHead))) {
            return false;
        }
        auto tagCursor = cursor_;
        cursor_ += sizeof(TLVHead);
        auto valueCursor = cursor_;
        TAG tag = TAG::TAG_BUTT;
        auto int32Value = std::get_if<int32_t>(&value);
        if (int32Value != nullptr) {
            if (!WriteBasic(TAG_INT32, std::get<int32_t>(value))) {
                return false;
            }
            tag = TAG::TAG_INT32;
        }
        auto int64Value = std::get_if<int64_t>(&value);
        if (int64Value != nullptr) {
            if (!WriteBasic(TAG_INT64, std::get<int64_t>(value))) {
                return false;
            }
            tag = TAG::TAG_INT64;
        }
        auto boolValue = std::get_if<bool>(&value);
        if (boolValue != nullptr) {
            if (!WriteBasic(TAG_BOOL, std::get<bool>(value))) {
                return false;
            }
            tag = TAG::TAG_BOOL;
        }
        auto doubleValue = std::get_if<double>(&value);
        if (doubleValue != nullptr) {
            if (!WriteBasic(TAG_DOUBLE, std::get<double>(value))) {
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
        WriteHead(tag, tagCursor, cursor_ - valueCursor);
        return true;
    }

    bool ReadVariant(UDVariant &value)
    {
        TLVHead head{};
        if (!ReadHead(head)) {
            return false;
        }
        if (!HasExpectBuffer(head.len)) {
            return false;
        }
        switch (head.tag) {
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
        return true;
    }

    bool WriteMap(const UDDetails &value)
    {
        if (!HasExpectBuffer(sizeof(TLVHead))) {
            return false;
        }

        auto tagCursor = cursor_;
        cursor_ += sizeof(TLVHead);
        auto valueCursor = cursor_;

        for (auto &item : value) {
            if (!WriteString(item.first)) {
                return false;
            }
            if (!WriteVariant(item.second)) {
                return false;
            }
        }

        WriteHead(TAG_MAP, tagCursor, cursor_ - valueCursor);
        return true;
    }

    bool ReadMap(UDDetails &value)
    {
        TLVHead head{};
        if (!ReadHead(head)) {
            return false;
        }
        if (!HasExpectBuffer(head.len)) {
            return false;
        }
        auto mapEnd = cursor_ + head.len;
        while (cursor_ < mapEnd) {
            std::string itemKey;
            if (!ReadString(itemKey)) {
                return false;
            }
            UDVariant itemValue;
            if (!ReadVariant(itemValue)) {
                return false;
            }
            value.emplace(itemKey, itemValue);
        }
        return true;
    }

private:
    inline bool ReadHead(TLVHead &head)
    {
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

    inline void WriteHead(uint16_t type, size_t tagCursor, uint32_t len)
    {
        auto *tlvHead = reinterpret_cast<TLVHead *>(buffer_->data() + tagCursor);
        tlvHead->tag = HostToNet(type);
        tlvHead->len = HostToNet(len);
    }

    inline bool HasExpectBuffer(const uint32_t expectLen) const
    {
        return buffer_->size() >= cursor_ && buffer_->size() - cursor_ >= expectLen;
    }

    std::size_t total_ = 0;
    std::size_t cursor_ = 0;
    std::vector<std::uint8_t> *buffer_;
};
} // namespace UDMF
} // namespace OHOS
#endif // UDMF_TLV_OBJECT_H
