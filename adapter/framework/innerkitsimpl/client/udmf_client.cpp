/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#include "udmf_client.h"

namespace OHOS {
namespace UDMF {
UdmfClient &UdmfClient::GetInstance()
{
    static UdmfClient instance;
    return instance;
}

Status UdmfClient::SetData(CustomOption &option, UnifiedData &unifiedData, std::string &key)
{
    return E_OK;
}

Status UdmfClient::GetData(const QueryOption &query, UnifiedData &unifiedData)
{
    return E_OK;
}

Status UdmfClient::GetBatchData(const QueryOption &query, std::vector<UnifiedData> &unifiedDataSet)
{
    return E_OK;
}

Status UdmfClient::UpdateData(const QueryOption &query, UnifiedData &unifiedData)
{
    return E_OK;
}

Status UdmfClient::DeleteData(const QueryOption &query, std::vector<UnifiedData> &unifiedDataSet)
{
    return E_OK;
}

Status UdmfClient::GetSummary(const QueryOption &query, Summary &summary)
{
    return E_OK;
}

Status UdmfClient::AddPrivilege(const QueryOption &query, Privilege &privilege)
{
    return E_OK;
}

Status UdmfClient::Sync(const QueryOption &query, const std::vector<std::string> &devices)
{
    return E_OK;
}

Status UdmfClient::IsRemoteData(const QueryOption &query, bool &result)
{
    return E_OK;
}

Status UdmfClient::SetAppShareOption(const std::string &intention, enum ShareOptions shareOption)
{
    return E_OK;
}

Status UdmfClient::GetAppShareOption(const std::string &intention, enum ShareOptions &shareOption)
{
    return E_OK;
}


Status UdmfClient::RemoveAppShareOption(const std::string &intention)
{
    return E_OK;
}

std::string UdmfClient::GetSelfBundleName()
{
    return std::string("");
}
} // namespace UDMF
} // namespace OHOS