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

#ifndef UDMF_UNIFIED_RECORD_FFI_H
#define UDMF_UNIFIED_RECORD_FFI_H

#include <cstdint>

#include "cj_common_ffi.h"
#include "ffi_remote_data.h"
#include "unified_record_impl.h"

namespace OHOS {
namespace UDMF {
extern "C" {
FFI_EXPORT int64_t FfiUDMFUnifiedRecordConstructor();
FFI_EXPORT int64_t FfiUDMFUnifiedRecordConstructorwithOnlyType(const char *type);
FFI_EXPORT int64_t FfiUDMFUnifiedRecordConstructorwithType(const char *type, CJValueType value);
FFI_EXPORT char *FfiUDMFUnifiedRecordGetType(int64_t unifiedId);
FFI_EXPORT CJValueType FfiUDMFUnifiedRecordGetValue(int64_t unifiedId);

FFI_EXPORT int64_t FfiUDMFFileSetUri(int64_t id, const char *uri);
FFI_EXPORT char *FfiUDMFFileGetUri(int64_t id);
FFI_EXPORT CRecord FfiUDMFFileGetDetails(int64_t id);
FFI_EXPORT int64_t FfiUDMFFileSetDetails(int64_t id, CRecord record);

FFI_EXPORT char *FfiUDMFImageGetImageUri(int64_t id);
FFI_EXPORT int64_t FfiUDMFImageSetImageUri(int64_t id, const char *uri);

FFI_EXPORT char *FfiUDMFVideoGetVideoUri(int64_t id);
FFI_EXPORT int64_t FfiUDMFVideoSetVideoUri(int64_t id, const char *uri);

FFI_EXPORT CRecord FfiUDMFTextGetDetails(int64_t id);
FFI_EXPORT int64_t FfiUDMFTextSetDetails(int64_t id, CRecord record);

FFI_EXPORT char *FfiUDMFHyperLinkGetUrl(int64_t id);
FFI_EXPORT int64_t FfiUDMFHyperLinkSetUrl(int64_t id, const char *url);

FFI_EXPORT char *FfiUDMFHyperLinkGetDescription(int64_t id);
FFI_EXPORT int64_t FfiUDMFHyperLinkSetDescription(int64_t id, const char *description);

FFI_EXPORT char *FfiUDMFPlainTextGetTextContent(int64_t id);
FFI_EXPORT int64_t FfiUDMFPlainTextSetTextContent(int64_t id, const char *text);

FFI_EXPORT char *FfiUDMFPlainTextGetAbstract(int64_t id);
FFI_EXPORT int64_t FfiUDMFPlainTextSetAbstract(int64_t id, const char *abstr);
}
} // namespace UDMF
} // namespace OHOS

#endif