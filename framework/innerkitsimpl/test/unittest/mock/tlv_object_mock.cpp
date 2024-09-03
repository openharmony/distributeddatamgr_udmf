/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include "tlv_object.h"

namespace OHOS {
namespace UDMF {
TLVObject::TLVObject(std::vector<std::uint8_t> &buffer)
{
    buffer_ = &buffer;
}

void TLVObject::SetFile(std::FILE *file)
{
}

void TLVObject::UpdateSize()
{
}

std::vector<std::uint8_t> TLVObject::GetBuffer()
{
    return *buffer_;
}

void TLVObject::Count(const uint32_t value)
{
}

void TLVObject::Count(const uint64_t value)
{
}

void TLVObject::Count(const int32_t value)
{
}

void TLVObject::Count(const int64_t value)
{
}

void TLVObject::Count(const float value)
{
}

void TLVObject::Count(const double value)
{
}

void TLVObject::Count(const std::string &value)
{
}

void TLVObject::Count(const std::vector<uint8_t> &value)
{
}

void TLVObject::Count(const UDVariant &value)
{
}

void TLVObject::Count(const ValueType &value)
{
}

void TLVObject::Count(const UDDetails &value)
{
}

void TLVObject::Count(const UnifiedKey &value)
{
}

void TLVObject::Count(const Privilege &value)
{
}

void TLVObject::Count(const std::shared_ptr<OHOS::AAFwk::Want> &value)
{
}

void TLVObject::Count(const std::shared_ptr<OHOS::Media::PixelMap> &value)
{
}

void TLVObject::Count(const std::shared_ptr<Object> &value)
{
}

void TLVObject::Count(const std::monostate &value)
{
}

void TLVObject::Count(const void *value)
{
}

bool TLVObject::WriteString(const std::string &value)
{
    return true;
}

bool TLVObject::ReadString(std::string &value)
{
    return true;
}

bool TLVObject::WriteVector(const std::vector<uint8_t> &value)
{
    return true;
}

bool TLVObject::ReadVector(std::vector<uint8_t> &value)
{
    return true;
}

bool TLVObject::WriteVariantInner(TAG &tag, const UDVariant &value)
{
    return true;
}

bool TLVObject::WriteVariant(const UDVariant &value)
{
    return true;
}

bool TLVObject::ReadVariantInner(uint16_t tag, UDVariant &value)
{
    return true;
}

bool TLVObject::ReadVariant(UDVariant &value)
{
    return true;
}

bool TLVObject::WriteVariantInner(TAG &tag, const ValueType &value)
{
    return true;
}

bool TLVObject::WriteVariant(const ValueType &value)
{
    return true;
}

bool TLVObject::ReadVariantInner(uint16_t tag, ValueType &value)
{
    return true;
}

bool TLVObject::ReadVariant(ValueType &value)
{
    return true;
}

bool TLVObject::WriteMap(const UDDetails &value)
{
    return true;
}

bool TLVObject::ReadMap(UDDetails &value)
{
    return true;
}

bool TLVObject::WriteObject(const std::shared_ptr<Object> &value)
{
    return true;
}

bool TLVObject::ReadObject(std::shared_ptr<Object> &value)
{
    return true;
}

bool TLVObject::WriteWant(const std::shared_ptr<OHOS::AAFwk::Want> &value)
{
    return true;
}

bool TLVObject::ReadWant(std::shared_ptr<OHOS::AAFwk::Want> &value)
{
    return true;
}

bool TLVObject::WritePixelMap(const std::shared_ptr<OHOS::Media::PixelMap> &value)
{
    return true;
}

bool TLVObject::ReadPixelMap(std::shared_ptr<OHOS::Media::PixelMap> &value)
{
    return false;
}

bool TLVObject::WriteUndefined(const std::monostate &value)
{
    return true;
}

bool TLVObject::ReadUndefined(std::monostate &value)
{
    return true;
}

bool TLVObject::WriteNull(const void *value)
{
    return true;
}

bool TLVObject::ReadNull(void *value)
{
    return true;
}

bool TLVObject::ReadHead(TLVHead &head)
{
    return true;
}

void TLVObject::WriteHead(uint16_t type, size_t tagCursor, uint32_t len)
{
}

bool TLVObject::HasExpectBuffer(const uint32_t expectLen) const
{
    return true;
}

bool TLVObject::PrepareHeader(size_t size, size_t &tagCursor, size_t &valueCursor)
{
    return true;
}

void TLVObject::PrepareBuffer(size_t size)
{
}

bool TLVObject::SaveBufferToFile()
{
    return true;
}

bool TLVObject::LoadBufferFormFile(size_t size)
{
    return true;
}
} // namespace UDMF
} // namespace OHOS