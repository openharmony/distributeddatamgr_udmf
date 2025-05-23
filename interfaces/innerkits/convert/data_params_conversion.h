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

#ifndef DATA_PARAMS_CONVERSION_H
#define DATA_PARAMS_CONVERSION_H

#include "async_task_params.h"
#include "udmf_capi_common.h"

namespace OHOS::UDMF {
class DataParamsConversion {
public:
    static Status API_EXPORT GetInnerDataParams(OH_UdmfGetDataParams &ndkDataParams, QueryOption &query,
        GetDataParams &dataParams);
    static Status API_EXPORT GetDataLoaderParams(const OH_UdmfDataLoadParams &ndkDataParams, DataLoadParams &dataLoadParams);
};
}

#endif // DATA_PARAMS_CONVERSION_H