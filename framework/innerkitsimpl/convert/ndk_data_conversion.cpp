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

#include "ndk_data_conversion.h"
#include "unified_data.h"
#include "udmf_capi_common.h"
#include "error_code.h"

namespace OHOS::UDMF {
    Status NdkDataConversion::GetNativeUnifiedData(std::shared_ptr<OH_UdmfData> ndkData,
                                                   std::shared_ptr<UnifiedData> &data)
    {
        if (ndkData == nullptr || data == nullptr || ndkData->cid != NdkStructId::UDMF_UNIFIED_DATA_STRUCT_ID) {
            return Status::E_INVALID_PARAMETERS;
        }
        data = ndkData->unifiedData_;
        return Status::E_OK;
    }

    Status NdkDataConversion::GetNdkUnifiedData(std::shared_ptr<UnifiedData> data,
                                                std::shared_ptr<OH_UdmfData> &ndkData)
    {
        if (data == nullptr || ndkData == nullptr || ndkData->cid != NdkStructId::UDMF_UNIFIED_DATA_STRUCT_ID) {
            return Status::E_INVALID_PARAMETERS;
        }
        ndkData->unifiedData_ = data;
        return Status::E_OK;
    }
}