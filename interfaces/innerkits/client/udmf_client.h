/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef UDMF_CLIENT_H
#define UDMF_CLIENT_H

#include <string>
#include <vector>

#include "unified_data.h"
#include "error_code.h"
#include "unified_meta.h"
#include "unified_types.h"
#include "visibility.h"
namespace OHOS {
namespace UDMF {
class API_EXPORT UdmfClient {
public:
    static UdmfClient &GetInstance();

    Status SetData(CustomOption &option, UnifiedData &unifiedData, std::string &key);
    Status GetData(const QueryOption &query, UnifiedData &unifiedData);
    Status GetBatchData(const QueryOption &query, std::vector<UnifiedData> &unifiedDataSet);
    Status UpdateData(const QueryOption &query, UnifiedData &unifiedData);
    Status DeleteData(const QueryOption &query, std::vector<UnifiedData> &unifiedDataSet);
    Status GetSummary(const QueryOption &query, Summary& summary);
    Status AddPrivilege(const QueryOption &query, Privilege &privilege);
    Status Sync(const QueryOption &query, const std::vector<std::string> &devices);
    Status IsRemoteData(const QueryOption &query, bool &result);
};
} // namespace UDMF
} // namespace OHOS
#endif // UDMF_CLIENT_H