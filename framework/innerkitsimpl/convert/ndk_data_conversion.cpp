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
#define LOG_TAG "NdkDataConversion"
#include "ndk_data_conversion.h"

#include "logger.h"
#include "securec.h"
namespace OHOS::UDMF {
static constexpr uint64_t MAX_RECORDS_COUNT = 4 * 1024 * 1024;
static constexpr uint64_t MAX_KEY_STRING_LEN = 1 * 1024 * 1024;

Status NdkDataConversion::GetNativeUnifiedData(OH_UdmfData* ndkData, std::shared_ptr<UnifiedData>& data)
{
    if (ndkData == nullptr || data == nullptr || ndkData->cid != NdkStructId::UDMF_UNIFIED_DATA_STRUCT_ID) {
        return Status::E_INVALID_PARAMETERS;
    }
    data = ndkData->unifiedData_;
    return Status::E_OK;
}

Status NdkDataConversion::GetNdkUnifiedData(std::shared_ptr<UnifiedData> data, OH_UdmfData* ndkData)
{
    if (data == nullptr || ndkData == nullptr || ndkData->cid != NdkStructId::UDMF_UNIFIED_DATA_STRUCT_ID) {
        return Status::E_INVALID_PARAMETERS;
    }
    ndkData->unifiedData_ = data;
    return Status::E_OK;
}

char** NdkDataConversion::StrVectorToTypesArray(const std::vector<std::string>& strVector)
{
    unsigned int vectorSize = strVector.size();
    if (vectorSize == 0 || vectorSize > MAX_RECORDS_COUNT) {
        return nullptr;
    }
    char** typesArray = new (std::nothrow) char* [vectorSize];
    if (typesArray == nullptr) {
        LOG_ERROR(UDMF_CAPI, "create types array failed!, vectorSize: %{public}d, MAX_RECORDS_COUNT: %{public}" PRIu64,
            vectorSize, MAX_RECORDS_COUNT);
        return nullptr;
    }
    for (unsigned int i = 0; i < vectorSize; ++i) {
        unsigned int strLen = strVector[i].length() + 1;
        if (strLen > MAX_KEY_STRING_LEN) {
            LOG_INFO(UDMF_CAPI, "string exceeds maximum length, length is %{public}d", strLen);
            DestroyStringArray(typesArray, vectorSize);
            return nullptr;
        }
        typesArray[i] = new (std::nothrow) char[strLen];
        if (typesArray[i] == nullptr ||
            (strcpy_s(typesArray[i], strLen, strVector[i].c_str())) != EOK) {
            LOG_ERROR(UDMF_CAPI, "string copy failed");
            DestroyStringArray(typesArray, vectorSize);
            return nullptr;
        }
    }
    return typesArray;
}

void NdkDataConversion::DestroyStringArray(char**& bufArray, unsigned int& count)
{
    if (bufArray == nullptr) {
        return;
    }
    for (unsigned int i = 0; i < count; i++) {
        if (bufArray[i] != nullptr) {
            delete[] bufArray[i];
            bufArray[i] = nullptr;
        }
    }
    delete[] bufArray;
    bufArray = nullptr;
    count = 0;
}
}