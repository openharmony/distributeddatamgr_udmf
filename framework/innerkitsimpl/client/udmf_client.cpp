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

#include "udmf_client.h"

#include "error_code.h"
#include "logger.h"
#include "udmf_service_client.h"

namespace OHOS {
namespace UDMF {
UdmfClient &UdmfClient::GetInstance()
{
    static auto instance_ = new UdmfClient();
    return *instance_;
}

Status UdmfClient::SetData(CustomOption &option, UnifiedData &unifiedData, std::string &key)
{
    LOG_INFO(UDMF_CLIENT, "start.");
    auto service = UdmfServiceClient::GetInstance();
    if (service == nullptr) {
        LOG_ERROR(UDMF_CLIENT, "Service unavailable");
        return E_ERROR;
    }

    int32_t ret = service->SetData(option, unifiedData, key);
    return static_cast<Status>(ret);
}

Status UdmfClient::GetData(QueryOption &query, UnifiedData &unifiedData)
{
    LOG_INFO(UDMF_CLIENT, "start.");
    auto service = UdmfServiceClient::GetInstance();
    if (service == nullptr) {
        LOG_ERROR(UDMF_CLIENT, "Service unavailable");
        return E_ERROR;
    }

    int32_t ret = service->GetData(query, unifiedData);
    return static_cast<Status>(ret);
}

Status UdmfClient::GetSummary(QueryOption &query, Summary &summary)
{
    LOG_INFO(UDMF_CLIENT, "start.");
    auto service = UdmfServiceClient::GetInstance();
    if (service == nullptr) {
        LOG_ERROR(UDMF_CLIENT, "Service unavailable");
        return E_ERROR;
    }

    int32_t ret = service->GetSummary(query, summary);
    return static_cast<Status>(ret);
}

Status UdmfClient::AddPrivilege(QueryOption &query, Privilege &privilege)
{
    LOG_INFO(UDMF_CLIENT, "start.");
    auto service = UdmfServiceClient::GetInstance();
    if (service == nullptr) {
        LOG_ERROR(UDMF_CLIENT, "Service unavailable");
        return E_ERROR;
    }

    int32_t ret = service->AddPrivilege(query, privilege);
    return static_cast<Status>(ret);
}
} // namespace UDMF
} // namespace OHOS