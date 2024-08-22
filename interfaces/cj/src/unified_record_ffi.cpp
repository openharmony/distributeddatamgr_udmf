
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


using namespace OHOS::FFI;
using namespace OHOS::UDMF;

namespace OHOS {
namespace UDMF {
extern "C" {

int64_t FfiOHOSUDMFUnifiedRecordConstructor(){
    auto nativeCJUnifiedRecord = FFIData::Create<CUnifiedRecord>();
    if (nativeCJUnifiedRecord == nullptr) {
        return -1;
    }
    return nativeCJUnifiedRecord->GetID();
}


int64_t FfiOHOSUDMFUnifiedRecordConstructorwithType(const char* type,CJValueType value){
    auto nativeCJUnifiedRecord = FFIData::Create<CUnifiedRecord>(type,value);
    if (nativeCJUnifiedRecord == nullptr) {
        return -1;
    }
    return nativeCJUnifiedRecord->GetID();
}

char*   FfiOHOSUDMFUnifiedRecordGetType(int64_t unifiedId){
    auto instance = FFIData::GetData<CUnifiedRecord>(unifiedId);
    if (instance == nullptr) {
        return nullptr;
    }
    return instance->GetType();
    
}

CJValueType   FfiOHOSUDMFUnifiedRecordGetValue(int64_t unifiedId){
    auto instance = FFIData::GetData<CUnifiedRecord>(unifiedId);
    if (instance == nullptr) {
        CJValueType r;
        return r;
    }
    return instance->GetValue();
}




}
}
}

