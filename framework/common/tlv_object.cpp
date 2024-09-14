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

#define LOG_TAG "TlvObject"
#include "tlv_object.h"
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
    if (fseek(file_, 0, SEEK_END) != 0) {
        LOG_ERROR(UDMF_SERVICE, "fseek to end error!");
    }

    auto total = ftell(file_);
    if (total < 0) {
        LOG_ERROR(UDMF_SERVICE, "Values are out of range, total:%{public}ld", total);
        return;
    }
    total_ = static_cast<size_t>(total);
    ResetCursor();
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
        if (fseek(file_, sizeof(TLVHead), SEEK_CUR) != 0) {
            LOG_ERROR(UDMF_SERVICE, "OffsetHead file error!");
            return 0;
        }
    }
    cursor_ += sizeof(TLVHead);
    return cursor_;
}

void TLVObject::ResetCursor()
{
    cursor_ = 0;
    if (file_ != nullptr) {
        if (fseek(file_, 0, SEEK_SET) != 0) {
            LOG_ERROR(UDMF_SERVICE, "ResetCursor file error!");
        }
    }
}

size_t TLVObject::Count(const std::string &value)
{
    auto size = sizeof(TLVHead) + value.size();
    total_ += size;
    return size;
}

size_t TLVObject::Count(const std::vector<uint8_t> &value)
{
    auto size = sizeof(TLVHead) + value.size();
    total_ += size;
    return size;
}

size_t TLVObject::Count(const OHOS::AAFwk::Want &value)
{
    Parcel parcel;
    if (!value.Marshalling(parcel)) {
        LOG_ERROR(UDMF_FRAMEWORK, "Marshalling want error when Count");
        return 0;
    }
    auto size = sizeof(TLVHead) + parcel.GetDataSize();
    total_ += size;
    return size;
}

size_t TLVObject::Count(const std::monostate &value)
{
    auto size = sizeof(TLVHead);
    total_ += size;
    return size;
}

size_t TLVObject::Count(const void *value)
{
    auto size = sizeof(TLVHead);
    total_ += size;
    return size;
}

bool TLVObject::Write(TAG tag, const std::string &value)
{
    if (!HasExpectBuffer(sizeof(TLVHead) + value.size())) {
        LOG_ERROR(UDMF_FRAMEWORK, "Has no enough buffer in tlv write. tag=%{public}hu, value=%{public}s", tag,
            value.c_str());
        return false;
    }
    auto tlvHead = reinterpret_cast<TLVHead *>(GetStartCursor());
    tlvHead->tag = HostToNet(static_cast<uint16_t>(tag));
    tlvHead->len = HostToNet((uint32_t)value.size());
    if (!value.empty()) {
        auto err = memcpy_s(tlvHead->value, value.size(), value.c_str(), value.size());
        if (err != EOK) {
            LOG_ERROR(UDMF_FRAMEWORK, "memcpy error in tlv write. tag=%{public}hu, value=%{public}s", tag,
                value.c_str());
            return false;
        }
    }
    cursor_ += sizeof(TLVHead) + value.size();
    return SaveBufferToFile();
}

bool TLVObject::Read(std::string &value, const TLVHead &head)
{
    if (!HasExpectBuffer(head.len)) {
        LOG_ERROR(UDMF_FRAMEWORK, "Has no enough buffer in tlv read string. tag=%{public}hu", head.tag);
        return false;
    }
    if (!LoadBufferFormFile(head.len)) {
        LOG_ERROR(UDMF_FRAMEWORK, "LoadBufferFormFile error in tlv read string. tag=%{public}hu", head.tag);
        return false;
    }
    auto startCursor = GetStartCursor();
    value.append(reinterpret_cast<const char *>(startCursor), head.len);
    cursor_ += head.len;
    return true;
}

bool TLVObject::Write(TAG tag, const std::vector<uint8_t> &value)
{
    if (!HasExpectBuffer(sizeof(TLVHead) + value.size())) {
        LOG_ERROR(UDMF_FRAMEWORK, "Has no enough buffer in tlv write u8 vector. tag=%{public}hu", tag);
        return false;
    }
    auto tlvHead = reinterpret_cast<TLVHead *>(GetStartCursor());
    tlvHead->tag = HostToNet(static_cast<uint16_t>(tag));
    tlvHead->len = HostToNet(static_cast<uint32_t>(value.size()));
    if (!value.empty()) {
        auto err = memcpy_s(tlvHead->value, value.size(), value.data(), value.size());
        if (err != EOK) {
            LOG_ERROR(UDMF_FRAMEWORK, "memcpy error in tlv write u8 vector. tag=%{public}hu", tag);
            return false;
        }
    }
    cursor_ += sizeof(TLVHead) + value.size();
    return SaveBufferToFile();
}


bool TLVObject::Read(std::vector<uint8_t> &value, const TLVHead &head)
{
    if (!HasExpectBuffer(head.len)) {
        LOG_ERROR(UDMF_FRAMEWORK, "Has no enough buffer in tlv read u8 vector. tag=%{public}hu", head.tag);
        return false;
    }
    if (!LoadBufferFormFile(head.len)) {
        LOG_ERROR(UDMF_FRAMEWORK, "LoadBufferFormFile error in tlv read u8 vector. tag=%{public}hu", head.tag);
        return false;
    }
    auto startCursor = GetStartCursor();
    std::vector<uint8_t> buff(startCursor, startCursor + head.len);
    value = std::move(buff);
    cursor_ += head.len;
    return true;
}

bool TLVObject::Write(TAG tag, const OHOS::AAFwk::Want &value)
{
    Parcel parcel;
    if (!value.Marshalling(parcel)) {
        LOG_ERROR(UDMF_FRAMEWORK, "Marshalling want error in tlv write. tag=%{public}hu", tag);
        return false;
    }
    auto size = parcel.GetDataSize();
    auto buffer = parcel.GetData();

    if (!HasExpectBuffer(sizeof(TLVHead) + size)) {
        LOG_ERROR(UDMF_FRAMEWORK, "Has no enough buffer in tlv write want. tag=%{public}hu", tag);
        return false;
    }
    auto tlvHead = reinterpret_cast<TLVHead *>(GetStartCursor());
    tlvHead->tag = HostToNet(static_cast<uint16_t>(tag));
    tlvHead->len = HostToNet(static_cast<uint32_t>(size));
    if (size != 0) {
        auto err = memcpy_s(tlvHead->value, size, reinterpret_cast<const void *>(buffer), size);
        if (err != EOK) {
            LOG_ERROR(UDMF_FRAMEWORK, "memcpy error in tlv write want. tag=%{public}hu", tag);
            return false;
        }
    }
    cursor_ += sizeof(TLVHead) + size;
    return SaveBufferToFile();
}

bool TLVObject::Read(OHOS::AAFwk::Want &value, const TLVHead &head)
{
    if (!HasExpectBuffer(head.len)) {
        LOG_ERROR(UDMF_FRAMEWORK, "Has no enough buffer in tlv read want. tag=%{public}hu", head.tag);
        return false;
    }
    if (!LoadBufferFormFile(head.len)) {
        LOG_ERROR(UDMF_FRAMEWORK, "LoadBufferFormFile error in tlv read want. tag=%{public}hu", head.tag);
        return false;
    }
    auto startCursor = GetStartCursor();
    std::vector<uint8_t> buff(startCursor, startCursor + head.len);

    auto buffer = (uintptr_t)(buff.data() + cursor_);
    cursor_ += head.len;

    Parcel parcel;
    if (!parcel.ParseFrom(buffer, head.len)) {
        LOG_ERROR(UDMF_FRAMEWORK, "ParseFrom error in tlv read want. tag=%{public}hu", head.tag);
        return false;
    }
    auto want = AAFwk::Want::Unmarshalling(parcel);
    if (want == nullptr) {
        LOG_ERROR(UDMF_FRAMEWORK, "Unmarshalling want error in tlv read. tag=%{public}hu", head.tag);
        return false;
    }
    value = *want;
    return true;
}

bool TLVObject::Write(TAG tag, const std::monostate &value)
{
    return WriteHead(static_cast<uint16_t>(tag), (uint32_t)0);
}

bool TLVObject::Read(std::monostate &value, const TLVHead &head)
{
    return true;
}

bool TLVObject::Write(TAG tag, const void *value)
{
    return WriteHead(static_cast<uint16_t>(tag), (uint32_t)0);
}


bool TLVObject::Read(void *value, const TLVHead &head)
{
    value = nullptr;
    return true;
}

size_t TLVObject::CountHead()
{
    total_ += sizeof(TLVHead);
    return sizeof(TLVHead);
}

bool TLVObject::WriteHead(uint16_t tag, uint32_t len)
{
    if (!HasExpectBuffer(sizeof(TLVHead))) {
        LOG_ERROR(UDMF_FRAMEWORK, "Has no enough buffer in tlv write head. tag=%{public}hu", tag);
        return false;
    }
    PrepareBufferForFile(sizeof(TLVHead));
    auto tlvHead = reinterpret_cast<TLVHead *>(GetStartCursor());
    tlvHead->tag = HostToNet(tag);
    tlvHead->len = HostToNet(len);
    cursor_ += sizeof(TLVHead);
    return SaveBufferToFile();
}

bool TLVObject::WriteBackHead(uint16_t tag, size_t tagCursor, uint32_t len)
{
    auto startCursor = buffer_->data();
    if (file_ == nullptr) {
        startCursor += tagCursor;
    }
    auto tlvHead = reinterpret_cast<TLVHead *>(startCursor);
    tlvHead->tag = HostToNet(tag);
    tlvHead->len = HostToNet(len);
    return SaveBufferToFileFront(tagCursor, sizeof(TLVHead));
}

bool TLVObject::ReadHead(TLVHead &head)
{
    if (!HasExpectBuffer(sizeof(TLVHead))) {
        LOG_ERROR(UDMF_FRAMEWORK, "Has no enough buffer in tlv read head. tag=%{public}hu", head.tag);
        return false;
    }
    if (!LoadBufferFormFile(sizeof(TLVHead))) {
        LOG_ERROR(UDMF_FRAMEWORK, "LoadBufferFormFile error in tlv read head. tag=%{public}hu", head.tag);
        return false;
    }
    auto startCursor = GetStartCursor();
    const auto *pHead = reinterpret_cast<const TLVHead *>(startCursor);
    auto len = NetToHost(pHead->len);
    if (file_ == nullptr) {
        if (!HasExpectBuffer(len + sizeof(TLVHead))) {
            LOG_ERROR(UDMF_FRAMEWORK, "Has no enough buffer in tlv read head and len. tag=%{public}hu", head.tag);
            return false;
        }
    }

    head.tag = NetToHost(pHead->tag);
    head.len = len;
    cursor_ += sizeof(TLVHead);
    return true;
}

bool TLVObject::Skip(TLVHead &head)
{
    if (file_ != nullptr) {
        cursor_ += head.len;
        return fseek(file_, head.len * sizeof(uint8_t), SEEK_CUR) == 0;
    }
    if (total_ < head.len || total_ - head.len < cursor_) {
        LOG_ERROR(UDMF_FRAMEWORK, "Has no enough buffer in tlv skip. tag=%{public}hu", head.tag);
        return false;
    }
    cursor_ += head.len;
    return true;
}

bool TLVObject::HasExpectBuffer(const uint32_t expectLen) const
{
    if (buffer_ == nullptr) {
        return false;
    }
    if (file_ != nullptr) {
        buffer_->resize(expectLen);
        return true;
    }
    return buffer_->size() >= cursor_ && buffer_->size() - cursor_ >= expectLen;
}

void TLVObject::PrepareBufferForFile(size_t size)
{
    if (file_ == nullptr) {
        return;
    }
    buffer_->resize(size);
}

std::uint8_t *TLVObject::GetStartCursor()
{
    auto startCursor = buffer_->data();
    if (file_ == nullptr) {
        startCursor += cursor_;
    }
    return startCursor;
}

bool TLVObject::SaveBufferToFile()
{
    if (file_ == nullptr) {
        return true;
    }
    auto count = fwrite(buffer_->data(), sizeof(uint8_t), buffer_->size(), file_);
    if (count != buffer_->size()) {
        LOG_ERROR(UDMF_FRAMEWORK, "fwrite error!");
        return false;
    }
    return true;
}

bool TLVObject::SaveBufferToFileFront(size_t tagCursor, uint32_t len)
{
    if (file_ == nullptr) {
        return true;
    }
    int32_t leftOffset =
        -((static_cast<int32_t>(cursor_) - static_cast<int32_t>(tagCursor))) * static_cast<int32_t>(sizeof(uint8_t));
    if (fseek(file_, leftOffset * sizeof(uint8_t), SEEK_CUR) != 0) {
        LOG_ERROR(UDMF_FRAMEWORK, "file fseek left error!");
        return false;
    }
    auto count = fwrite(buffer_->data(), sizeof(uint8_t), sizeof(TLVHead), file_);
    if (count != sizeof(TLVHead)) {
        LOG_ERROR(UDMF_FRAMEWORK, "file write error!");
        return false;
    }
    int32_t rightOffset =
        static_cast<int32_t>(cursor_) - static_cast<int32_t>(tagCursor) - static_cast<int32_t>(sizeof(TLVHead));
    if (fseek(file_, rightOffset * sizeof(uint8_t), SEEK_CUR) != 0) {
        LOG_ERROR(UDMF_FRAMEWORK, "file fseek right error!");
        return false;
    }
    return true;
}

bool TLVObject::LoadBufferFormFile(size_t size)
{
    if (file_ == nullptr) {
        return true;
    }
    auto count = fread(buffer_->data(), sizeof(uint8_t), buffer_->size(), file_);
    if (count != buffer_->size()) {
        return false;
    }
    return true;
}
} // namespace UDMF
} // namespace OHOS
