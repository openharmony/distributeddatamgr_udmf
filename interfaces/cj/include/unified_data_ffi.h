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

#ifndef UDMF_UNIFIED_DATA_FFI_H
#define UDMF_UNIFIED_DATA_FFI_H

#include <cstdint>
#include "ffi_remote_data.h"
#include "cj_common_ffi.h"

#include "unified_data_impl.h"

namespace OHOS {
namespace UDMF {
extern "C" {
    FFI_EXPORT int64_t FfiOHOSUDMFUnifiedDataConstructor();
    FFI_EXPORT int64_t FfiOHOSUDMFUnifiedDataConstructorwWithRecord(int64_t unifiedRecordId);
    FFI_EXPORT void FfiOHOSUDMFUnifiedDataAddRecord(int64_t unifiedDataId, int64_t unifiedRecordId);
    FFI_EXPORT CArrUnifiedRecord FfiOHOSUDMFUnifiedDataGetRecords(int64_t unifiedDataId);
    FFI_EXPORT bool FfiOHOSUDMFUnifiedDataHasType(int64_t unifiedDataId, const char *type);
    FFI_EXPORT CArrString FfiOHOSUDMFUnifiedDataGetTypes(int64_t unifiedDataId);
}
}
}

#endif