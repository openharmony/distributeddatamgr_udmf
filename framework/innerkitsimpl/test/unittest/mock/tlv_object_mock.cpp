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

size_t TLVObject::GetTotal()
{
    return total_;
}

size_t TLVObject::GetCursor()
{
    return cursor_;
}

size_t TLVObject::OffsetHead()
{
    if (file_ != nullptr) {
        fseek(file_, sizeof(TLVHead), SEEK_CUR);
    }
    cursor_ += sizeof(TLVHead);
    return cursor_;
}

void TLVObject::ResetCursor()
{
    cursor_ = 0;
    if (file_ != nullptr) {
        fseek(file_, 0, SEEK_SET);
    }
}

size_t TLVObject::Count(const std::string &value)
{
    return sizeof(TLVHead);
}

size_t TLVObject::Count(const std::vector<uint8_t> &value)
{
    return sizeof(TLVHead);
}

size_t TLVObject::Count(const std::monostate &value)
{
    return sizeof(TLVHead);
}

size_t TLVObject::Count(const void *value)
{
    return sizeof(TLVHead);
}

bool TLVObject::Write(TAG tag, const std::string &value)
{
    return true;
}

bool TLVObject::Read(std::string &value, const TLVHead &head)
{
    return true;
}

bool TLVObject::Write(TAG tag, const std::vector<uint8_t> &value)
{
    return true;
}


bool TLVObject::Read(std::vector<uint8_t> &value, const TLVHead &head)
{
    return true;
}

bool TLVObject::Write(TAG tag, const std::monostate &value)
{
    return true;
}

bool TLVObject::Read(std::monostate &value, const TLVHead &head)
{
    return true;
}

bool TLVObject::Write(TAG tag, const void *value)
{
    return true;
}


bool TLVObject::Read(void *value, const TLVHead &head)
{
    return true;
}

size_t TLVObject::CountHead()
{
    return true;
}

bool TLVObject::WriteHead(uint16_t type, uint32_t len)
{
    return true;
}

bool TLVObject::WriteBackHead(uint16_t tag, size_t tagCursor, uint32_t len)
{
    return true;
}

bool TLVObject::ReadHead(TLVHead &head)
{
    return true;
}

bool TLVObject::Skip(TLVHead &head)
{
    return true;
}

bool TLVObject::HasExpectBuffer(const uint32_t expectLen) const
{
    return true;
}

void TLVObject::PrepareBufferForFile(size_t size) { }

std::uint8_t *TLVObject::GetStartCursor()
{
    return 0;
}

bool TLVObject::SaveBufferToFile()
{
    return true;
}

bool TLVObject::SaveBufferToFileFront(size_t tagCursor, uint32_t len)
{
    return true;
}

bool TLVObject::LoadBufferFormFile(size_t size)
{
    return true;
}
} // namespace UDMF
} // namespace OHOS
