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
#include <map>
#include <shared_mutex>

#include "concurrent_map.h"
#include "error_code.h"
#include "unified_data.h"
#include "unified_meta.h"
#include "unified_types.h"
#include "visibility.h"
namespace OHOS {
namespace UDMF {
class UdmfClient {
public:
    static UdmfClient API_EXPORT &GetInstance();

    Status API_EXPORT SetData(CustomOption &option, UnifiedData &unifiedData, std::string &key);
    Status API_EXPORT GetData(const QueryOption &query, UnifiedData &unifiedData);
    Status API_EXPORT GetBatchData(const QueryOption &query, std::vector<UnifiedData> &unifiedDataSet);
    Status API_EXPORT UpdateData(const QueryOption &query, UnifiedData &unifiedData);
    Status API_EXPORT DeleteData(const QueryOption &query, std::vector<UnifiedData> &unifiedDataSet);
    Status API_EXPORT GetSummary(const QueryOption &query, Summary& summary);
    Status API_EXPORT AddPrivilege(const QueryOption &query, Privilege &privilege);
    Status API_EXPORT Sync(const QueryOption &query, const std::vector<std::string> &devices);
    Status API_EXPORT IsRemoteData(const QueryOption &query, bool &result);
    Status API_EXPORT SetAppShareOption(const std::string &intention, enum ShareOptions shareOption);
    Status API_EXPORT RemoveAppShareOption(const std::string &intention);
    Status API_EXPORT GetAppShareOption(const std::string &intention, enum ShareOptions &shareOption);

private:
    UdmfClient() = default;
    ~UdmfClient() = default;
    UdmfClient(const UdmfClient &obj) = delete;
    UdmfClient &operator=(const UdmfClient &obj) = delete;
    std::string GetSelfBundleName();

    ConcurrentMap<std::string, UnifiedData> dataCache_;
};
} // namespace UDMF
} // namespace OHOS
#endif // UDMF_CLIENT_H