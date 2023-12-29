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

#include <cstdio>
#include "securec.h"
#include "error_code.h"
#include "unified_meta.h"
#include "unified_types.h"
#include "endian_converter.h"

namespace OHOS {
namespace UDMF {
enum class TAG {
    TAG_INT32 = 0x0000,
    TAG_INT64,
    TAG_UINT32,
    TAG_UINT64,
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
    explicit TLVObject(std::vector<std::uint8_t> &buffer);
    void SetFile(std::FILE *file);
    void UpdateSize();
    std::vector<std::uint8_t> GetBuffer();
    void Count(const uint32_t value);
    void Count(const uint64_t value);
    void Count(const int32_t value);
    void Count(const int64_t value);
    void Count(const float value);
    void Count(const double value);
    void Count(const std::string &value);
    void Count(const std::vector<uint8_t> &value);
    void Count(const UDVariant &value);
    void Count(const UDDetails &value);
    void Count(const UnifiedKey &value);
    void Count(const Privilege &value);
    template<typename T> bool WriteBasic(TAG type, const T &value);
    template<typename T> bool ReadBasic(T &value);
    bool WriteString(const std::string &value);
    bool ReadString(std::string &value);
    bool WriteVector(const std::vector<uint8_t> &value);
    bool ReadVector(std::vector<uint8_t> &value);
    bool WriteVariant(const UDVariant &value);
    bool ReadVariant(UDVariant &value);
    bool WriteMap(const UDDetails &value);
    bool ReadMap(UDDetails &value);

private:
    bool WriteVariantInner(TAG &tag, const UDVariant &value);
    bool ReadVariantInner(uint16_t tag, UDVariant &value);
    bool ReadHead(TLVHead &head);
    void WriteHead(uint16_t type, size_t tagCursor, uint32_t len);
    bool HasExpectBuffer(const uint32_t expectLen) const;
    void PrepareHeader(size_t size, size_t &tagCursor, size_t &valueCursor);
    void PrepareBuffer(size_t size);
    bool SaveBufferToFile();
    bool LoadBufferFormFile(size_t size);

private:
    std::size_t total_ = 0;
    std::size_t cursor_ = 0;
    std::vector<std::uint8_t> *buffer_;
    std::FILE *file_ = nullptr;
};

template<typename T>
bool TLVObject::WriteBasic(TAG type, const T &value)
{
    PrepareBuffer(sizeof(TLVHead) + sizeof(value));
    if (!HasExpectBuffer(sizeof(TLVHead) + sizeof(value))) {
        return false;
    }
    auto *tlvHead = reinterpret_cast<TLVHead*>(buffer_->data() + cursor_);
    tlvHead->tag = HostToNet(static_cast<uint16_t>(type));
    tlvHead->len = HostToNet((uint32_t)sizeof(value));
    auto valueBuff = HostToNet(value);
    size_t maxSize = sizeof(value) + 1;
    auto ret = memcpy_s(tlvHead->value, maxSize, &valueBuff, sizeof(value));
    if (ret != EOK) {
        return false;
    }
    if (!SaveBufferToFile()) {
        return false;
    }
    cursor_ += sizeof(TLVHead) + sizeof(value);
    return true;
}

template<typename T>
bool TLVObject::ReadBasic(T &value)
{
    TLVHead head {};
    if (!ReadHead(head)) {
        return false;
    }
    if (head.len == 0 || head.len != sizeof(T)) {
        return false;
    }
    if (!HasExpectBuffer(head.len)) {
        return false;
    }
    if (!LoadBufferFormFile(head.len)) {
        return false;
    }
    auto ret = memcpy_s(&value, sizeof(T), buffer_->data() + cursor_, sizeof(T));
    if (ret != EOK) {
        return false;
    }
    value = NetToHost(value);
    cursor_ += sizeof(T);
    if (file_ != nullptr) {
        cursor_ += sizeof(TLVHead);
    }
    return true;
}

} // namespace UDMF
} // namespace OHOS
#endif // UDMF_TLV_OBJECT_H