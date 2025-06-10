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

#ifndef UDMF_UNIFIED_RECORD_IMPL_H
#define UDMF_UNIFIED_RECORD_IMPL_H

#include "cj_common_ffi.h"
#include "ffi_remote_data.h"
#include "unified_record.h"

namespace OHOS {
namespace UDMF {
struct CRecord {
    CArrString keys;
    CArrString values;
};
 
struct CJValueType {
    int32_t integer32;
    int64_t integer64;
    double dou;
    bool boolean;
    char *string;
    CArrUI8 byteArray;
    int64_t pixelMapId;
    uint8_t tag;
};

enum TypeSymbol {
    INTEGER32 = 0,
    INTEGER64 = 1,
    DOUBLE = 2,
    BOOLEAN = 3,
    STRING = 4,
    BYTEARRAY = 5,
    PIXELMAP = 6,
    NULLTAG = 7,
    UNDEFINED = 8
};

class CUnifiedRecord : public OHOS::FFI::FFIData {
    DECL_TYPE(CUnifiedRecord, OHOS::FFI::FFIData)
public:
    CUnifiedRecord();
    CUnifiedRecord(const char *type);
    CUnifiedRecord(const char *type, CJValueType value);
    CJValueType ValueType2CJValueType(ValueType value);
    ValueType CJValueType2ValueType(CJValueType value);
    char *GetType();
    CJValueType GetValue();

    const std::shared_ptr<UDMF::UnifiedRecord> &GetUnifiedRecord() const;

    char *GetFileUri();
    void SetFileUri(const char *uri);
    CRecord GetFileDetails();
    void SetFileDetails(const std::map<std::string, std::string> &details);

    char *GetImageUri();
    void SetImageUri(const char *uri);

    char *GetVideoUri();
    void SetVideoUri(const char *uri);

    CRecord GetTextDetails();
    void SetTextDetails(const std::map<std::string, std::string> &details);

    char *GetHyperLinkUrl();
    void SetHyperLinkUrl(const char *url);

    char *GetHyperLinkDescription();
    void SetHyperLinkDescription(const char *description);

    char *GetPlainTextContent();
    void SetPlainTextContent(const char *text);

    char *GetPlainTextAbstract();
    void SetPlainTextAbstract(const char *abstr);
private:
    std::shared_ptr<UDMF::UnifiedRecord> unifiedRecord_;
    int64_t pixelMapId_ = 0;
};

char *CreateCStringFromString(const std::string &source);
} // namespace UDMF
} // namespace OHOS

#endif