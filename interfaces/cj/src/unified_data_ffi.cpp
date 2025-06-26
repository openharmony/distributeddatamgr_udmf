
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

#include "securec.h"

#include "unified_data_ffi.h"
#include "unified_data_impl.h"
#include "unified_record_impl.h"
#include "unified_data_parameter_parse.h"
#include "cj_common_ffi.h"

#include "utils.h"

using namespace OHOS::FFI;
using namespace OHOS::UDMF;

namespace OHOS {
namespace UDMF {
extern "C" {

int64_t FfiUDMFUnifiedDataConstructor()
{
    auto nativeCJUnifiedData = FFIData::Create<CUnifiedData>();
    if (nativeCJUnifiedData == nullptr) {
        return -1;
    }
    return nativeCJUnifiedData->GetID();
}

int64_t FfiUDMFUnifiedDataConstructorWithRecord(int64_t unifiedRecordId)
{
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

void FfiUDMFUnifiedDataAddRecord(int64_t unifiedDataId, int64_t unifiedRecordId)
{
    auto record = FFIData::GetData<CUnifiedRecord>(unifiedRecordId);
    if (record == nullptr) {
        return;
    }

    auto data = FFIData::GetData<CUnifiedData>(unifiedDataId);
    if (data == nullptr) {
        return;
    }

    data->AddRecord(record);
}

CArrUnifiedRecord FfiUDMFUnifiedDataGetRecords(int64_t unifiedDataId)
{
    auto data = FFIData::GetData<CUnifiedData>(unifiedDataId);
    if (data == nullptr) {
        return CArrUnifiedRecord {};
    }

    return data->GetRecords();
}

bool FfiUDMFUnifiedDataHasType(int64_t unifiedDataId, const char *type)
{
    auto data = FFIData::GetData<CUnifiedData>(unifiedDataId);
    if (data == nullptr) {
        return false;
    }

    return data->HasType(type);
}

CArrString FfiUDMFUnifiedDataGetTypes(int64_t unifiedDataId)
{
    auto data = FFIData::GetData<CUnifiedData>(unifiedDataId);
    if (data == nullptr) {
        return CArrString {};
    }

    return data->GetTypes();
}

CUnifiedDataProperties FfiUDMFGetProperties(int64_t unifiedDataId)
{
    auto data = FFIData::GetData<CUnifiedData>(unifiedDataId);
    CUnifiedDataProperties ret = { .extras = {}, .tag = nullptr, .timestamp = 0, .shareOptions = 1 };
    if (data == nullptr) {
        return ret;
    }
    std::shared_ptr<UDMF::UnifiedDataProperties> uni = data->unifiedData_->GetProperties();
    int32_t code = NO_ERROR;
    ParseParameters(uni->extras, ret.extras, code);
    if (code != NO_ERROR) {
        return ret;
    }
    ret.tag = Utils::MallocCString(uni->tag);
    ret.timestamp = uni->timestamp;
    // In arkts initial enum value is not public ,so use public initial value CROSS_APP.
    if (uni->shareOptions == IN_APP || uni->shareOptions == CROSS_APP) {
        ret.shareOptions = uni->shareOptions;
    }
    return ret;
}

void FfiUDMFSetProperties(int64_t unifiedDataId, CUnifiedDataProperties properties)
{
    auto data = FFIData::GetData<CUnifiedData>(unifiedDataId);
    if (data == nullptr) {
        return;
    }
    auto prop = data->unifiedData_->GetProperties();
    AAFwk::WantParams wantP;
    SetDataParameters(properties.extras, wantP);
    prop->extras = wantP;
    prop->tag = Utils::MallocCString(properties.tag);
    prop->shareOptions = UDMF::ShareOptions(properties.shareOptions);
    data->unifiedData_->SetProperties(prop);
}

FFI_EXPORT void FfiUDMFFreeDataProperties(CUnifiedDataProperties *properties)
{
    CParameters *p = properties->extras.head;
    for (int64_t i = 0; i < properties->extras.size; i++) {
        free(p[i].key);
        free(p[i].value);
        p[i].key = nullptr;
        p[i].value = nullptr;
    }
    free(p);
    free(properties->tag);
    p = nullptr;
    properties->tag = nullptr;
}

FFI_EXPORT void FfiUDMFFreeCArrString(CArrString *arrStr)
{
    Utils::FreeCArrString(*arrStr);
}
}
} // namespace UDMF
} // namespace OHOS
