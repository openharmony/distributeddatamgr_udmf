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

#ifndef UDMF_UNIFORM_TYPE_DESCRIPTOR_FFI_H
#define UDMF_UNIFORM_TYPE_DESCRIPTOR_FFI_H

#include <cstdint>
#include "ffi_remote_data.h"
#include "cj_common_ffi.h"

#include "uniform_type_descriptor_impl.h"

namespace OHOS {
namespace UDMF {
extern "C" {
    FFI_EXPORT int64_t FfiUDMFUniformTypeDescriptorGetTypeDescriptor(const char *typeId);
    FFI_EXPORT char *FfiUDMFUniformTypeDescriptorGetUniformDataTypeByFilenameExtension
        (const char *cFilenameExtension, const char *cBelongsTo);
    FFI_EXPORT char *FfiUDMFUniformTypeDescriptorGetUniformDataTypeByMIMEType
        (const char *cMimeType, const char *cBelongsTo);
}
}
}

#endif