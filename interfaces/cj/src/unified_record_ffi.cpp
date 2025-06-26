
/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#include "unified_record_ffi.h"

#include "unified_record_impl.h"
#include "utils.h"

using namespace OHOS::FFI;
using namespace OHOS::UDMF;

namespace OHOS {
namespace UDMF {
extern "C" {

int64_t FfiUDMFUnifiedRecordConstructor()
{
    auto nativeCJUnifiedRecord = FFIData::Create<CUnifiedRecord>();
    if (nativeCJUnifiedRecord == nullptr) {
        return -1;
    }
    return nativeCJUnifiedRecord->GetID();
}

int64_t FfiUDMFUnifiedRecordConstructorwithOnlyType(const char *type)
{
    auto nativeCJUnifiedRecord = FFIData::Create<CUnifiedRecord>(type);
    if (nativeCJUnifiedRecord == nullptr) {
        return -1;
    }
    return nativeCJUnifiedRecord->GetID();
}

int64_t FfiUDMFUnifiedRecordConstructorwithType(const char *type, CJValueType value)
{
    auto nativeCJUnifiedRecord = FFIData::Create<CUnifiedRecord>(type, value);
    if (nativeCJUnifiedRecord == nullptr) {
        return -1;
    }
    return nativeCJUnifiedRecord->GetID();
}

char *FfiUDMFUnifiedRecordGetType(int64_t unifiedId)
{
    auto instance = FFIData::GetData<CUnifiedRecord>(unifiedId);
    if (instance == nullptr) {
        return nullptr;
    }
    return instance->GetType();
}

CJValueType FfiUDMFUnifiedRecordGetValue(int64_t unifiedId)
{
    auto instance = FFIData::GetData<CUnifiedRecord>(unifiedId);
    if (instance == nullptr) {
        return CJValueType {};
    }
    return instance->GetValue();
}

char *FfiUDMFFileGetUri(int64_t id)
{
    auto instance = FFIData::GetData<CUnifiedRecord>(id);
    if (instance == nullptr) {
        return nullptr;
    }
    return instance->GetFileUri();
}

void FfiUDMFFileSetUri(int64_t id, const char *uri)
{
    auto instance = FFIData::GetData<CUnifiedRecord>(id);
    if (instance == nullptr) {
        return;
    }
    instance->SetFileUri(uri);
}

CRecord FfiUDMFFileGetDetails(int64_t id)
{
    CRecord ret = { .keys = { .head = nullptr, .size = 0 }, .values = { .head = nullptr, .size = 0 } };
    auto instance = FFIData::GetData<CUnifiedRecord>(id);
    if (instance == nullptr) {
        return ret;
    }
    return instance->GetFileDetails();
}

void FfiUDMFFileSetDetails(int64_t id, CRecord record)
{
    std::map<std::string, std::string> details;
    auto instance = FFIData::GetData<CUnifiedRecord>(id);
    if (instance == nullptr) {
        return;
    }
    for (int64_t i = 0; i < record.keys.size; i++) {
        std::string key{record.keys.head[i]};
        std::string value{record.values.head[i]};
        details[key] = value;
    }
    instance->SetFileDetails(details);
}

char *FfiUDMFImageGetImageUri(int64_t id)
{
    auto instance = FFIData::GetData<CUnifiedRecord>(id);
    if (instance == nullptr) {
        return nullptr;
    }
    return instance->GetImageUri();
}

void FfiUDMFImageSetImageUri(int64_t id, const char *uri)
{
    auto instance = FFIData::GetData<CUnifiedRecord>(id);
    if (instance == nullptr) {
        return;
    }
    instance->SetImageUri(uri);
}

char *FfiUDMFVideoGetVideoUri(int64_t id)
{
    auto instance = FFIData::GetData<CUnifiedRecord>(id);
    if (instance == nullptr) {
        return nullptr;
    }
    return instance->GetVideoUri();
    }

    void FfiUDMFVideoSetVideoUri(int64_t id, const char *uri)
    {
    auto instance = FFIData::GetData<CUnifiedRecord>(id);
    if (instance == nullptr) {
        return;
    }
    instance->SetVideoUri(uri);
}

CRecord FfiUDMFTextGetDetails(int64_t id)
{
    CRecord ret = { .keys = { .head = nullptr, .size = 0 }, .values = { .head = nullptr, .size = 0 } };
    auto instance = FFIData::GetData<CUnifiedRecord>(id);
    if (instance == nullptr) {
        return ret;
    }
    return instance->GetTextDetails();
}

void FfiUDMFTextSetDetails(int64_t id, CRecord record)
{
    std::map<std::string, std::string> details;
    auto instance = FFIData::GetData<CUnifiedRecord>(id);
    if (instance == nullptr) {
        return;
    }
    for (int64_t i = 0; i < record.keys.size; i++) {
        std::string key{record.keys.head[i]};
        std::string value{record.values.head[i]};
        details[key] = value;
    }
    instance->SetTextDetails(details);
}

char *FfiUDMFHyperLinkGetUrl(int64_t id)
{
    auto instance = FFIData::GetData<CUnifiedRecord>(id);
    if (instance == nullptr) {
        return nullptr;
    }
    return instance->GetHyperLinkUrl();
}

void FfiUDMFHyperLinkSetUrl(int64_t id, const char *url)
{
    auto instance = FFIData::GetData<CUnifiedRecord>(id);
    if (instance == nullptr) {
        return;
    }
    instance->SetHyperLinkUrl(url);
}

char *FfiUDMFHyperLinkGetDescription(int64_t id)
{
    auto instance = FFIData::GetData<CUnifiedRecord>(id);
    if (instance == nullptr) {
        return nullptr;
    }
    return instance->GetHyperLinkDescription();
}

void FfiUDMFHyperLinkSetDescription(int64_t id, const char *description)
{
    auto instance = FFIData::GetData<CUnifiedRecord>(id);
    if (instance == nullptr) {
        return;
    }
    instance->SetHyperLinkDescription(description);
}

char *FfiUDMFPlainTextGetTextContent(int64_t id)
{
    auto instance = FFIData::GetData<CUnifiedRecord>(id);
    if (instance == nullptr) {
        return nullptr;
    }
    return instance->GetPlainTextContent();
}

void FfiUDMFPlainTextSetTextContent(int64_t id, const char *text)
{
    auto instance = FFIData::GetData<CUnifiedRecord>(id);
    if (instance == nullptr) {
        return;
    }
    instance->SetPlainTextContent(text);
}

char *FfiUDMFPlainTextGetAbstract(int64_t id)
{
    auto instance = FFIData::GetData<CUnifiedRecord>(id);
    if (instance == nullptr) {
        return nullptr;
    }
    return instance->GetPlainTextAbstract();
}

void FfiUDMFPlainTextSetAbstract(int64_t id, const char *abstr)
{
    auto instance = FFIData::GetData<CUnifiedRecord>(id);
    if (instance == nullptr) {
        return;
    }
    instance->SetPlainTextAbstract(abstr);
}

FFI_EXPORT void FfiUDMFFreeCjValueType(CJValueType *val)
{
    if (val->string != nullptr) {
        free(val->string);
        val->string = nullptr;
    }
    if (val->byteArray.head != nullptr) {
        free(val->byteArray.head);
        val->byteArray.head = nullptr;
        val->byteArray.size = 0;
    }
}

FFI_EXPORT void FfiUDMFFreeCRecord(CRecord *record)
{
    Utils::FreeCArrString(record->keys);
    Utils::FreeCArrString(record->values);
    record->keys.head = nullptr;
    record->keys.size = 0;
    record->values.head = nullptr;
    record->values.size = 0;
}
}
} // namespace UDMF
} // namespace OHOS
