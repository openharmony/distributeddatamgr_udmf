/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "cj_common_ffi.h"
#include "udmf_client.h"
#include "udmf_log.h"
#include "unified_data.h"
#include "unified_data_impl.h"
#include "unified_meta.h"
#include "unified_record_impl.h"
#include "utils.h"

using namespace OHOS::FFI;
using namespace OHOS::UDMF;

using ErrCode = int;

namespace OHOS {
namespace UDMF {
extern "C" {

FFI_EXPORT char *FfiUDMFInsertData(const char *intention, int64_t unifiedDataId, int32_t *errCode)
{
    *errCode = E_INVALID_PARAMETERS;
    std::string key;
    auto data = FFIData::GetData<CUnifiedData>(unifiedDataId);
    if (data == nullptr || data->unifiedData_ == nullptr) {
        LOGE("Get unified data failed!");
        return nullptr;
    }
    Intention it = UnifiedDataUtils::GetIntentionByString(intention);
    if (it == UD_INTENTION_DRAG) {
        LOGE("Parameter error: The intention parameter is invalid");
        return nullptr;
    }
    CustomOption option = { .intention = it };
    auto status = UdmfClient::GetInstance().SetData(option, *(data->unifiedData_), key);
    *errCode = status;
    if (status != E_OK) {
        LOGE("Insert data failed!");
    }
    return Utils::MallocCString(key);
}

FFI_EXPORT int32_t FfiUDMFUpdateData(const char *key, int64_t unifiedDataId)
{
    auto data = FFIData::GetData<CUnifiedData>(unifiedDataId);
    if (data == nullptr || data->unifiedData_ == nullptr) {
        LOGE("Get unified data failed!");
        return E_INVALID_PARAMETERS;
    }
    UnifiedKey verifyKey(key);
    if (!verifyKey.IsValid()) {
        LOGE("Parameter error: parameter key is invalid");
        return E_INVALID_PARAMETERS;
    }
    QueryOption option = { .key = key };
    auto status = UdmfClient::GetInstance().UpdateData(option, *(data->unifiedData_));
    if (status != E_OK) {
        LOGE("Update unified data failed!");
    }
    return status;
}

FFI_EXPORT CArrI64 FfiUDMFQueryData(const char *intention, const char *key, int32_t *errCode)
{
    *errCode = E_INVALID_PARAMETERS;
    CArrI64 queryData = { .head = nullptr, .size = 0 };
    Intention it = UnifiedDataUtils::GetIntentionByString(intention);
    if (it == UD_INTENTION_DRAG) {
        LOGE("Parameter error: the intention parameter is invalid");
        return queryData;
    }
    QueryOption option = { .key = key, .intention = it };
    std::vector<UnifiedData> unifiedDataSet;
    auto status = UdmfClient::GetInstance().GetBatchData(option, unifiedDataSet);
    *errCode = status;
    if (status != E_OK) {
        LOGE("Query unified data failed!");
        return queryData;
    }
    auto arr = static_cast<int64_t*>(malloc(sizeof(int64_t) * unifiedDataSet.size()));
    if (arr == nullptr) {
        LOGE("malloc error in queryData");
        return queryData;
    }
    for (uint64_t i = 0; i < unifiedDataSet.size(); i++) {
        std::shared_ptr<UnifiedData> unifiedDataItem = std::make_shared<UnifiedData>();
        auto cUnifiedData = FFIData::Create<CUnifiedData>();
        if (unifiedDataItem == nullptr || cUnifiedData == nullptr) {
            LOGE("Create unifiedData failed. Instance is null.");
            free(arr);
            arr = nullptr;
            return queryData;
        }
        unifiedDataItem->SetRecords(unifiedDataSet[i].GetRecords());
        unifiedDataItem->SetProperties(unifiedDataSet[i].GetProperties());
        cUnifiedData->unifiedData_ = unifiedDataItem;
        arr[i] = cUnifiedData->GetID();
    }
    queryData.head = arr;
    queryData.size = static_cast<int64_t>(unifiedDataSet.size());
    return queryData;
}

FFI_EXPORT CArrI64 FfiUDMFDeleteData(const char *intention, const char *key, int32_t *errCode)
{
    *errCode = E_INVALID_PARAMETERS;
    CArrI64 deleteData = { .head = nullptr, .size = 0 };
    Intention it = UnifiedDataUtils::GetIntentionByString(intention);
    if (it == UD_INTENTION_DRAG) {
        LOGE("Parameter error: the intention parameter is invalid");
        return deleteData;
    }
    QueryOption option = { .key = key, .intention = it };
    std::vector<UnifiedData> unifiedDataSet;
    auto status = UdmfClient::GetInstance().DeleteData(option, unifiedDataSet);
    *errCode = status;
    if (status != E_OK) {
        LOGE("Query unified data failed!");
        return deleteData;
    }
    auto arr = static_cast<int64_t*>(malloc(sizeof(int64_t) * unifiedDataSet.size()));
    if (arr == nullptr) {
        LOGE("malloc error in deleteData");
        return deleteData;
    }
    for (uint64_t i = 0; i < unifiedDataSet.size(); i++) {
        std::shared_ptr<UnifiedData> unifiedDataItem = std::make_shared<UnifiedData>();
        auto cUnifiedData = FFIData::Create<CUnifiedData>();
        if (unifiedDataItem == nullptr || cUnifiedData == nullptr) {
            LOGE("Create unifiedData failed. Instance is null.");
            free(arr);
            arr = nullptr;
            return deleteData;
        }
        unifiedDataItem->SetRecords(unifiedDataSet[i].GetRecords());
        unifiedDataItem->SetProperties(unifiedDataSet[i].GetProperties());
        cUnifiedData->unifiedData_ = unifiedDataItem;
        arr[i] = cUnifiedData->GetID();
    }
    deleteData.head = arr;
    deleteData.size = static_cast<int64_t>(unifiedDataSet.size());
    return deleteData;
}

FFI_EXPORT void FfiUDMFFreeStringData(char *str)
{
    free(str);
}

FFI_EXPORT void FfiUDMFFreeArrI64Data(CArrI64* ptr)
{
    if (ptr == nullptr || ptr->head == nullptr) {
        return;
    }
    free(ptr->head);
    ptr->head = nullptr;
}
}
} // namespace UDMF
} // namespace OHOS