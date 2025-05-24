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
#define LOG_TAG "DataParamsConversion"
#include "data_params_conversion.h"
#include "logger.h"
#include "ndk_data_conversion.h"
#include "udmf_client.h"
#include "udmf_utils.h"

namespace OHOS::UDMF {
Status DataParamsConversion::GetInnerDataParams(OH_UdmfGetDataParams &ndkDataParams, QueryOption &query,
    GetDataParams &dataParams)
{
    if (ndkDataParams.dataProgressListener == nullptr || query.key.size() == 0) {
        return Status::E_INVALID_PARAMETERS;
    }
    dataParams.query = query;
    if (ndkDataParams.destUri.size() > 0) {
        dataParams.destUri = ndkDataParams.destUri;
    }
    dataParams.fileConflictOptions = static_cast<FileConflictOptions>(ndkDataParams.fileConflictOptions);
    dataParams.progressIndicator = static_cast<ProgressIndicator>(ndkDataParams.progressIndicator);
    dataParams.progressListener = [ndkDataParams](ProgressInfo progressInfo, std::shared_ptr<UnifiedData> data) {
        OH_Udmf_ProgressInfo ndkProgrssInfo;
        ndkProgrssInfo.progress = progressInfo.progress;
        ndkProgrssInfo.status = progressInfo.progressStatus;
        if (data == nullptr) {
            ndkDataParams.dataProgressListener(&ndkProgrssInfo, nullptr);
            return;
        }
        OH_UdmfData *ndkData = OH_UdmfData_Create();
        NdkDataConversion::GetNdkUnifiedData(data, ndkData);
        ndkDataParams.dataProgressListener(&ndkProgrssInfo, ndkData);
        OH_UdmfData_Destroy(ndkData);
    };
    std::set<std::string> types;
    for (size_t i = 0; i < ndkDataParams.acceptableInfo.typesCount; i++) {
        types.insert(ndkDataParams.acceptableInfo.typesArray[i]);
    }
    dataParams.acceptableInfo = {
        .types = types,
        .recordCount = ndkDataParams.acceptableInfo.recordsCount,
    };
    return Status::E_OK;
}

Status DataParamsConversion::GetDataLoaderParams(const OH_UdmfDataLoadParams &ndkDataParams,
    DataLoadParams &dataLoadParams)
{
    if (ndkDataParams.dataLoadHandler == nullptr) {
        LOG_ERROR(UDMF_CAPI, "DataLoadHandler is null");
        return Status::E_INVALID_PARAMETERS;
    }
    std::set<std::string> types;
    for (size_t i = 0; i < ndkDataParams.dataLoadInfo.typesCount; i++) {
        types.insert(ndkDataParams.dataLoadInfo.typesArray[i]);
    }
    dataLoadParams.dataLoadInfo = {
        .sequenceKey = UTILS::GenerateId(),
        .types = types,
        .recordCount = ndkDataParams.dataLoadInfo.recordsCount,
    };
    dataLoadParams.loadHandler = [ndkDataParams](const std::string &udKey, const DataLoadInfo &dataLoadInfo) {
        std::vector<std::string> types(dataLoadInfo.types.begin(), dataLoadInfo.types.end());
        OH_UdmfDataLoadInfo ndkDataLoadInfo {
            .typesArray = NdkDataConversion::StrVectorToTypesArray(types),
            .typesCount = types.size(),
            .recordsCount = dataLoadInfo.recordCount,
        };
        OH_UdmfData *data = ndkDataParams.dataLoadHandler(&ndkDataLoadInfo);
        if (data == nullptr || data->unifiedData_ == nullptr) {
            LOG_ERROR(UDMF_CAPI, "Data is null");
            return;
        }
        auto status = UdmfClient::GetInstance().PushDelayData(udKey, *data->unifiedData_);
        if (status != Status::E_OK) {
            LOG_ERROR(UDMF_CAPI, "Set delay data failed, status = %{public}d", status);
        }
    };
    return Status::E_OK;
}
}
