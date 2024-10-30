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

#ifndef UDMF_TLV_OBJECT_H
#define UDMF_TLV_OBJECT_H
#include <cstddef>
#include <type_traits>
#include "securec.h"
#include "unified_meta.h"
#include "endian_converter.h"
#include "tlv_tag.h"

namespace OHOS {
namespace UDMF {
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
    size_t GetTotal();
    size_t GetCursor();
    size_t OffsetHead();
    void ResetCursor();

    size_t Count(const std::string &value);
    size_t Count(const std::vector<uint8_t> &value);
    size_t Count(const OHOS::AAFwk::Want &value);
    size_t Count(const std::monostate &value);
    size_t Count(const void *value);

    bool Write(TAG tag, const std::string &value);
    bool Write(TAG tag, const std::vector<uint8_t> &value);
    bool Write(TAG tag, const OHOS::AAFwk::Want &value);
    bool Write(TAG tag, const std::monostate &value);
    bool Write(TAG tag, const void *value);

    bool Read(std::string &value, const TLVHead &head);
    bool Read(std::vector<uint8_t> &value, const TLVHead &head);
    bool Read(OHOS::AAFwk::Want &value, const TLVHead &head);
    bool Read(std::monostate &value, const TLVHead &head);
    bool Read(void *value, const TLVHead &head);

    template <typename T> size_t CountBasic(const T &value);
    template <typename T> bool WriteBasic(TAG type, const T &value);
    template <typename T> bool ReadBasic(T &value, const TLVHead &head);

    size_t CountHead();
    bool WriteHead(uint16_t tag, uint32_t len);
    bool WriteBackHead(uint16_t tag, size_t tagCursor, uint32_t len);
    bool ReadHead(TLVHead &head);

    bool Skip(TLVHead &head);
    bool HasExpectBuffer(const uint32_t expectLen) const;
    bool SaveBufferToFile();
    bool SaveBufferToFileFront(size_t tagCursor, uint32_t len);
    bool LoadBufferFormFile(size_t size);


private:
    void PrepareBufferForFile(size_t size);
    std::uint8_t *GetStartCursor();

    std::size_t total_ = 0;
    std::size_t cursor_ = 0;
    std::vector<std::uint8_t> *buffer_;
    std::FILE *file_ = nullptr;
};

template <typename T> size_t TLVObject::CountBasic(const T &value)
{
    static_assert(std::is_fundamental<T>::value, "T must be a fundamental type.");
    auto size = sizeof(value) + sizeof(TLVHead);
    total_ += size;
    return size;
}

template <typename T> bool TLVObject::WriteBasic(TAG type, const T &value)
{
    static_assert(std::is_fundamental<T>::value, "T must be a fundamental type.");
    if (!HasExpectBuffer(sizeof(TLVHead) + sizeof(value))) {
        return false;
    }
    auto tlvHead = reinterpret_cast<TLVHead *>(GetStartCursor());
    tlvHead->tag = HostToNet(static_cast<uint16_t>(type));
    tlvHead->len = HostToNet((uint32_t)sizeof(value));
    auto valueBuff = HostToNet(value);
    if (memcpy_s(tlvHead->value, sizeof(value), &valueBuff, sizeof(value)) != EOK) {
        return false;
    }
    cursor_ += sizeof(TLVHead) + sizeof(value);
    return SaveBufferToFile();
}

template <typename T> bool TLVObject::ReadBasic(T &value, const TLVHead &head)
{
    static_assert(std::is_fundamental<T>::value, "T must be a fundamental type.");
    if (head.len == 0 || head.len != sizeof(T)) {
        return false;
    }
    if (!HasExpectBuffer(head.len)) {
        return false;
    }
    if (!LoadBufferFormFile(head.len)) {
        return false;
    }
    auto startCursor = GetStartCursor();
    auto ret = memcpy_s(&value, sizeof(T), startCursor, sizeof(T));
    if (ret != EOK) {
        return false;
    }
    value = NetToHost(value);
    cursor_ += sizeof(T);
    return true;
}
} // namespace UDMF
} // namespace OHOS
#endif // UDMF_TLV_OBJECT_H
