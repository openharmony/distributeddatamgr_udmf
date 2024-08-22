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
// #include "napi_base_context.h"
#include "ffi_remote_data.h"
#include "cj_common_ffi.h"




// #include "data_query.h"

// #include "distributed_kv_store_log.h"
#include "unified_record_impl.h"

namespace OHOS {
namespace UDMF {
    
extern "C" {
    
    FFI_EXPORT int64_t FfiOHOSUDMFUnifiedRecordConstructor();
    FFI_EXPORT int64_t FfiOHOSUDMFUnifiedRecordConstructorwithType(const char* type,CJValueType value);
    FFI_EXPORT char*   FfiOHOSUDMFUnifiedRecordGetType(int64_t unifiedId);
    FFI_EXPORT CJValueType   FfiOHOSUDMFUnifiedRecordGetValue(int64_t unifiedId);
}

}
}

#endif