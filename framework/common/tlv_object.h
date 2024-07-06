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
#include "visibility.h"
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
    TAG_WANT,
    TAG_PIXELMAP,
    TAG_OBJECT,
    TAG_BUTT,
};

#pragma pack(1)
struct TLVHead {
    uint16_t tag;
    uint32_t len;
    std::uint8_t value[0];
};
#pragma pack()

class API_EXPORT TLVObject {
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
    void Count(const UDDetails &value);
    void Count(const UnifiedKey &value);
    void Count(const Privilege &value);
    void Count(const OHOS::AAFwk::Want &value);
    void Count(const OHOS::Media::PixelMap &value);
    void Count(const Object &value);
    void Count(const std::monostate &value);
    template<typename T> void Count(const std::shared_ptr<T> value);
    template<typename _InTp> void CountVariant(uint32_t step, const _InTp& input);
    template<typename _InTp, typename _First, typename... _Rest>
    void CountVariant(uint32_t step, const _InTp& input);
    template<typename... _Types> void Count(const std::variant<_Types...>& input);

    template<typename T> bool WriteBasic(TAG type, const T &value);
    template<typename T> bool ReadBasic(T &value);
    bool WriteString(const std::string &value);
    bool ReadString(std::string &value);
    bool WriteVector(const std::vector<uint8_t> &value);
    bool ReadVector(std::vector<uint8_t> &value);
    bool WriteVariant(const UDVariant &value);
    bool ReadVariant(UDVariant &value);
    bool WriteVariant(const ValueType &value);
    bool ReadVariant(ValueType &value);
    bool WriteMap(const UDDetails &value);
    bool ReadMap(UDDetails &value);
    bool WriteMap(const std::shared_ptr<Object> &value);
    bool ReadMap(std::shared_ptr<Object> &value);
    bool WriteWant(const std::shared_ptr<OHOS::AAFwk::Want> &value);
    bool ReadWant(std::shared_ptr<OHOS::AAFwk::Want> &value);
    bool WritePixelMap(const std::shared_ptr<OHOS::Media::PixelMap> &value);
    bool ReadPixelMap(std::shared_ptr<OHOS::Media::PixelMap> &value);

private:
    bool WriteVariantInner(TAG &tag, const UDVariant &value);
    bool ReadVariantInner(uint16_t tag, UDVariant &value);
    bool WriteVariantInner(TAG &tag, const ValueType &value);
    bool ReadVariantInner(uint16_t tag, ValueType &value);
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

template<typename T>
void TLVObject::Count(const std::shared_ptr<T> value)
{
    if (value == nullptr) {
        return;
    }
    Count(*value);
}

template<typename _InTp>
void TLVObject::CountVariant(uint32_t step, const _InTp& input)
{
    total_ += sizeof(TLVHead);
}

template<typename _InTp, typename _First, typename... _Rest>
void TLVObject::CountVariant(uint32_t step, const _InTp& input)
{
    if (step == input.index()) {
        this->Count(std::get<_First>(input));
        return;
    }
    CountVariant<_InTp, _Rest...>(step + 1, input);
}

template<typename... _Types>
void TLVObject::Count(const std::variant<_Types...>& input)
{
    total_ += sizeof(TLVHead);
    CountVariant<decltype(input), _Types...>(0, input);
}
} // namespace UDMF
} // namespace OHOS
#endif // UDMF_TLV_OBJECT_H