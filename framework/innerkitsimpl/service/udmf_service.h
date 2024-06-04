/*
 * Copyright (c) 2022 Huawei Device Co., Ltd.
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

#ifndef UDMF_SERVICE_H
#define UDMF_SERVICE_H

#include <string>
#include <vector>

#include "iremote_broker.h"

#include "error_code.h"
#include "unified_data.h"
#include "unified_meta.h"
#include "unified_types.h"

namespace OHOS {
namespace UDMF {
/*
 * UDMF service interface
 */
class UdmfService {
public:
    DECLARE_INTERFACE_DESCRIPTOR(u"OHOS.UDMF.UdmfService");
    UdmfService() = default;
    virtual ~UdmfService() = default;

    virtual int32_t SetData(CustomOption &option, UnifiedData &unifiedData, std::string &key) = 0;
    virtual int32_t GetData(const QueryOption &query, UnifiedData &unifiedData) = 0;
    virtual int32_t GetBatchData(const QueryOption &query, std::vector<UnifiedData> &unifiedDataSet) = 0;
    virtual int32_t UpdateData(const QueryOption &query, UnifiedData &unifiedData) = 0;
    virtual int32_t DeleteData(const QueryOption &query, std::vector<UnifiedData> &unifiedDataSet) = 0;
    virtual int32_t GetSummary(const QueryOption &query, Summary &summary) = 0;
    virtual int32_t AddPrivilege(const QueryOption &query, Privilege &privilege) = 0;
    virtual int32_t Sync(const QueryOption &query, const std::vector<std::string> &devices) = 0;
    virtual int32_t IsRemoteData(const QueryOption &query, bool &result) = 0;
    virtual int32_t SetAppShareOption(const std::string &intention, int32_t shareOption) = 0;
    virtual int32_t GetAppShareOption(const std::string &intention, int32_t &shareOption) = 0;
    virtual int32_t RemoveAppShareOption(const std::string &intention) = 0;
};
} // namespace UDMF
} // namespace OHOS
#endif // UDMF_SERVICE_H