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

struct UdsObject {
    const int64_t cid;
    std::shared_ptr<OHOS::UDMF::Object> obj;
    std::mutex mutex;
    explicit UdsObject(int cid);
    template<typename T> bool hasObjectKey(const char* paramName);
    template<typename T> T* GetUdsValue(const char* paramName);
    template<typename T> int SetUdsValue(const char* paramName, T pramValue);
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
    UDS_FORM_STRUCT_ID,
    UDS_FILE_URI_STRUCT_ID,
    UDS_PIXEL_MAP_STRUCT_ID
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
struct OH_UdsForm : public UdsObject {
    OH_UdsForm();
};
struct OH_UdsFileUri : public UdsObject {
    OH_UdsFileUri();
};
struct OH_UdsPixelMap : public UdsObject {
    OH_UdsPixelMap();
};

struct OH_UdmfRecord {
    const int64_t cid = UDMF_UNIFIED_RECORD_STRUCT_ID;
    std::shared_ptr<OHOS::UDMF::UnifiedRecord> record_;
    unsigned char *recordData{nullptr};
    unsigned int recordDataLen{0};
    char **typesArray{nullptr};
    unsigned int typesCount{0};
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

constexpr const char* UNIFORM_DATA_TYPE = "uniformDataType";
constexpr const char* CONTENT = "content";
constexpr const char* ABSTRACT = "abstract";
constexpr const char* URL = "url";
constexpr const char* DESCRIPTION = "description";
constexpr const char* HTML_CONTENT = "htmlContent";
constexpr const char* PLAIN_CONTENT = "plainContent";
constexpr const char* APP_ID = "appId";
constexpr const char* APP_NAME = "appName";
constexpr const char* APP_ICON_ID = "appIconId";
constexpr const char* APP_LABEL_ID = "appLabelId";
constexpr const char* BUNDLE_NAME = "bundleName";
constexpr const char* ABILITY_NAME = "abilityName";
constexpr const char* FORM_CONTENT = "formContent";
constexpr const char* FILE_URI = "fileUri";
constexpr const char* FILE_TYPE = "fileType";
constexpr const char* PIXEL_MAP = "pixelMap";

bool IsInvalidUdsObjectPtr(const UdsObject* pThis, int cid);

#endif
