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

#ifndef UDMF_TLV_TAG_H
#define UDMF_TLV_TAG_H

#include <cstdint>

namespace OHOS::UDMF {
enum class TAG : uint16_t {
    TAG_NULL = 0x0000,
    TAG_MONOSTATE,
    TAG_UNDEFINED,
    TAG_INT8,
    TAG_INT16,
    TAG_INT32,
    TAG_INT64,
    TAG_UINT8,
    TAG_UINT16,
    TAG_UINT32,
    TAG_UINT64,
    TAG_FLOAT,
    TAG_DOUBLE,
    TAG_BOOL,
    TAG_STRING,
    TAG_VECTOR,
    TAG_VECTOR_SIZE,
    TAG_VECTOR_ITEM,
    TAG_MAP,
    TAG_MAP_PAIR,
    TAG_MAP_KEY,
    TAG_MAP_VALUE,
    TAG_VARIANT,
    TAG_VARIANT_INDEX,
    TAG_VARIANT_ITEM,
    TAG_BUTT = 0x1000,
    TAG_UNIFIED_DATA,
    TAG_UNIFIED_RECORD,
    TAG_VERSION,
    TAG_UD_TYPE,
    TAG_UID,
    TAG_RECORD_VALUE,
    TAG_KEY,
    TAG_INTENTION,
    TAG_BUNDLE_NAME,
    TAG_GROUP_ID,
    TAG_TOKEN_ID,
    TAG_READPERMISSION,
    TAG_WRITEPERMISSION,
    TAG_IS_PRIVATE,
    TAG_PRIVILEGE,
    TAG_CREATE_TIME,
    TAG_SOURCE_PACKAGE,
    TAG_DATA_STATUS,
    TAG_DATA_VERSION,
    TAG_LAST_MODIFIED_TIME,
    TAG_CREATE_PACKAGE,
    TAG_DEVICE_ID,
    TAG_RECORD_TOTAL_NUM,
    TAG_WANT,
    TAG_PIXELMAP,
    TAG_OBJECT_VALUE,
    TAG_RUNTIME,
    TAG_RECORD_UTD_ID,
    TAG_RECORD_ENTRIES,
    TAG_INNER_ENTRIES,
    TAG_URI_ORI,
    TAG_URI_DFS,
    TAG_URI_AUTH,
    TAG_URI_POS,
    TAG_RECORD_URIS,
    TAG_SUMMARY,
    TAG_SUMMARY_MAP,
    TAG_SUMMARY_SIZE,
    TAG_PROPERTIES,
    TAG_UNIFIED_PROPERTIES,
    TAG_PROPERTIES_TAG,
    TAG_PROPERTIES_TIMESTAMP,
    TAG_PROPERTIES_SHARE_OPTIONS,
    TAG_PROPERTIES_EXTRAS,
    TAG_RECORD_UTD_ID2,
    TAG_SUMMARY_FILE_TYPES,
	TAG_DATA_LOAD_INFO,
    TAG_DATA_LOAD_KEY,
    TAG_SET_TYPES,
    TAG_RECORD_COUNT,
    TAG_SET_ITEM,
    TAG_SET_SIZE,
    TAG_VISIBILITY,
    TAG_APP_ID,
};
}
#endif //UDMF_TLV_TAG_H
