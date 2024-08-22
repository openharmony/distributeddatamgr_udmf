
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

#include "unified_data_ffi.h"
#include "unified_data_impl.h"
#include "unified_record_impl.h"


using namespace OHOS::FFI;
using namespace OHOS::UDMF;

namespace OHOS {
namespace UDMF {
extern "C" {

int64_t FfiOHOSUDMFUnifiedDataConstructor(){
    auto nativeCJUnifiedData = FFIData::Create<CUnifiedData>();
    if (nativeCJUnifiedData == nullptr) {
        return -1;
    }
    return nativeCJUnifiedData->GetID();
}


int64_t FfiOHOSUDMFUnifiedDataConstructorWithRecord(int64_t unifiedRecordId){
    auto record = FFIData::GetData<CUnifiedRecord>(unifiedRecordId);
    if (record == nullptr) {
        return -1;
    }

    auto nativeCJUnifiedData = FFIData::Create<CUnifiedData>(record);
    if (nativeCJUnifiedData == nullptr) {
        return -1;
    }
    return nativeCJUnifiedData->GetID();
}



void  FfiOHOSUDMFUnifiedDataAddRecord(int64_t unifiedDataId,int64_t unifiedRecordId){
    auto record = FFIData::GetData<CUnifiedRecord>(unifiedRecordId);
    if (record == nullptr) {
        return ;
    }

    auto data = FFIData::GetData<CUnifiedData>(unifiedDataId);
    if (data == nullptr) {
        return ;
    }

    data->AddRecord(record);
}

CArrUnifiedRecord   FfiOHOSUDMFUnifiedDataGetRecords(int64_t unifiedDataId){
    auto data = FFIData::GetData<CUnifiedData>(unifiedDataId);
    if (data == nullptr) {
        CArrUnifiedRecord res;
        return res;
    }

    return data->GetRecords();

   

}



bool   FfiOHOSUDMFUnifiedDataHasType(int64_t unifiedDataId,const char* type){
    auto data = FFIData::GetData<CUnifiedData>(unifiedDataId);
    if (data == nullptr) {
        return false;
    }

    return data->HasType(type);
}


CArrString   FfiOHOSUDMFUnifiedDataGetTypes(int64_t unifiedDataId){
    auto data = FFIData::GetData<CUnifiedData>(unifiedDataId);
    if (data == nullptr) {
        CArrString res;
        return res;
    }

    return data->GetTypes();
}





}
}
}

