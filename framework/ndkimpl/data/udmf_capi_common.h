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

#ifndef UDMF_CAPI_COMMON_H
#define UDMF_CAPI_COMMON_H

#include "unified_record.h"
#include "unified_data.h"
#include <mutex>
#include <cstdint>

# define MAX_GENERAL_ENTRY_SIZE (100 * 1024 * 1024)

struct UdsObject {
    const int64_t cid;
    std::shared_ptr<OHOS::UDMF::Object> obj;
    std::mutex mutex;
    explicit UdsObject(int cid);
    template<typename T> bool HasObjectKey(const char* paramName);
    template<typename T> T* GetUdsValue(const char* paramName);
    template<typename T> int SetUdsValue(const char* paramName, const T &pramValue);
};

enum NdkStructId : std::int64_t {
    UTD_STRUCT_ID = 1002930,
    UDS_PLAIN_TEXT_STRUCT_ID,
    UDS_HYPERLINK_STRUCT_ID,
    UDS_HTML_STRUCT_ID,
    UDS_APP_ITEM_STRUCT_ID,
    UDMF_UNIFIED_DATA_STRUCT_ID,
    UDMF_UNIFIED_RECORD_STRUCT_ID,
    UDMF_UNIFIED_DATA_PROPERTIES_ID,
    UDS_FILE_URI_STRUCT_ID,
    UDS_PIXEL_MAP_STRUCT_ID,
    UDS_ARRAY_BUFFER_STRUCT_ID,
};

struct OH_Utd {
    const int64_t cid = UTD_STRUCT_ID;
    std::mutex mutex;
    std::string typeId;
    const char** belongingToTypes{nullptr};
    unsigned int belongingToTypesCount{0};
    const char** filenameExtensions{nullptr};
    unsigned int filenameExtensionsCount{0};
    const char** mimeTypes{nullptr};
    unsigned int mimeTypeCount{0};
    std::string description;
    std::string referenceURL;
    std::string iconFile;
};

struct OH_UdsPlainText : public UdsObject {
    OH_UdsPlainText();
};
struct OH_UdsHyperlink : public UdsObject {
    OH_UdsHyperlink();
};
struct OH_UdsHtml : public UdsObject {
    OH_UdsHtml();
};
struct OH_UdsAppItem : public UdsObject {
    OH_UdsAppItem();
};
struct OH_UdsFileUri : public UdsObject {
    OH_UdsFileUri();
};
struct OH_UdsPixelMap : public UdsObject {
    OH_UdsPixelMap();
};
struct OH_UdsArrayBuffer : public UdsObject {
    OH_UdsArrayBuffer();
};

struct OH_UdmfRecord {
    const int64_t cid = UDMF_UNIFIED_RECORD_STRUCT_ID;
    std::shared_ptr<OHOS::UDMF::UnifiedRecord> record_;
    unsigned char *recordData{nullptr};
    unsigned int recordDataLen{0};
    char **typesArray{nullptr};
    unsigned int typesCount{0};
    char *lastType{nullptr};
    std::mutex mutex;
};

struct OH_UdmfData {
    const int64_t cid = UDMF_UNIFIED_DATA_STRUCT_ID;
    std::shared_ptr<OHOS::UDMF::UnifiedData> unifiedData_;
    char **typesArray{nullptr};
    unsigned int typesCount{0};
    OH_UdmfRecord **records{nullptr};
    unsigned int recordsCount{0};
    std::mutex mutex;
};

struct OH_UdmfProperty {
    const int64_t cid = UDMF_UNIFIED_DATA_PROPERTIES_ID;
    std::shared_ptr<OHOS::UDMF::UnifiedDataProperties> properties_;
    std::mutex mutex;
    std::string extraStr;
};

bool IsInvalidUdsObjectPtr(const UdsObject* pThis, int cid);

bool IsInvalidUdsObjectByType(const UdsObject* pThis, const OHOS::UDMF::UDType& type);

#endif
