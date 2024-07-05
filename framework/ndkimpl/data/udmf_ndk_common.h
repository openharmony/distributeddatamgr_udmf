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

#ifndef UDMF_NDK_COMMON_H
#define UDMF_NDK_COMMON_H

#include "unified_record.h"
#include "unified_data.h"
#include <mutex>
#include <cstdint>

struct Uds_Object_Ptr {
    const int64_t id;
    std::shared_ptr<OHOS::UDMF::Object> obj;
    std::mutex mutex;
    Uds_Object_Ptr(int id);
    const char* GetUdsValue(const char* paramName);
    int SetUdsValue(const char* paramName, const char* pramValue);
};

enum UDMF_NdkStructId : std::int64_t {
    UTD_STRUCT_ID = 1002930,
    UDS_PLAIN_TEXT_STRUCT_ID,
    UDS_HYPERLINK_STRUCT_ID,
    UDS_HTML_STRUCT_ID,
    UDS_APP_ITEM_STRUCT_ID,
    UDMF_UNIFIED_DATA_STRUCT_ID,
    UDMF_UNIFIED_RECORD_STRUCT_ID,
    UDMF_UNIFIED_DATA_PROPERTIES_ID,
};

struct OH_Utd {
    const int64_t id = UTD_STRUCT_ID;
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

struct OH_UdsPlainText : public Uds_Object_Ptr {
    OH_UdsPlainText();
};
struct OH_UdsHyperlink : public Uds_Object_Ptr {
    OH_UdsHyperlink();
};
struct OH_UdsHtml : public Uds_Object_Ptr {
    OH_UdsHtml();
};
struct OH_UdsAppItem : public Uds_Object_Ptr {
    OH_UdsAppItem();
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

bool IsInvalidUdsObjectPtr(const Uds_Object_Ptr* pThis, int id);

#endif
