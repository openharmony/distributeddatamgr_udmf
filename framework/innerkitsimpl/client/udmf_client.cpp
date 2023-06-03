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
    LOG_DEBUG(UDMF_CLIENT, "start.");
    auto service = UdmfServiceClient::GetInstance();
    if (service == nullptr) {
        LOG_ERROR(UDMF_CLIENT, "Service unavailable");
        return E_ERROR;
    }

    int32_t ret = service->SetData(option, unifiedData, key);
    return static_cast<Status>(ret);
}

Status UdmfClient::GetData(const QueryOption &query, UnifiedData &unifiedData)
{
    LOG_DEBUG(UDMF_CLIENT, "start.");
    auto service = UdmfServiceClient::GetInstance();
    if (service == nullptr) {
        LOG_ERROR(UDMF_CLIENT, "Service unavailable");
        return E_ERROR;
    }

    int32_t ret = service->GetData(query, unifiedData);
    LOG_DEBUG(UDMF_SERVICE, "Getdata : ret =  %{public}d!", ret);
    return static_cast<Status>(ret);
}

Status UdmfClient::GetBatchData(const QueryOption &query, std::vector<UnifiedData> &unifiedDataSet)
{
    LOG_DEBUG(UDMF_CLIENT, "start.");
    auto service = UdmfServiceClient::GetInstance();
    if (service == nullptr) {
        LOG_ERROR(UDMF_CLIENT, "Service unavailable");
        return E_ERROR;
    }

    int32_t ret = service->GetBatchData(query, unifiedDataSet);
    return static_cast<Status>(ret);
}

Status UdmfClient::UpdateData(const QueryOption &query, UnifiedData &unifiedData)
{
    LOG_DEBUG(UDMF_CLIENT, "start.");
    auto service = UdmfServiceClient::GetInstance();
    if (service == nullptr) {
        LOG_ERROR(UDMF_CLIENT, "Service unavailable");
        return E_ERROR;
    }

    int32_t ret = service->UpdateData(query, unifiedData);
    return static_cast<Status>(ret);
}

Status UdmfClient::DeleteData(const QueryOption &query, std::vector<UnifiedData> &unifiedDataSet)
{
    LOG_DEBUG(UDMF_CLIENT, "start.");
    auto service = UdmfServiceClient::GetInstance();
    if (service == nullptr) {
        LOG_ERROR(UDMF_CLIENT, "Service unavailable");
        return E_ERROR;
    }

    int32_t ret = service->DeleteData(query, unifiedDataSet);
    return static_cast<Status>(ret);
}

Status UdmfClient::GetSummary(const QueryOption &query, Summary &summary)
{
    LOG_DEBUG(UDMF_CLIENT, "start.");
    auto service = UdmfServiceClient::GetInstance();
    if (service == nullptr) {
        LOG_ERROR(UDMF_CLIENT, "Service unavailable");
        return E_ERROR;
    }

    int32_t ret = service->GetSummary(query, summary);
    return static_cast<Status>(ret);
}

Status UdmfClient::AddPrivilege(const QueryOption &query, Privilege &privilege)
{
    LOG_DEBUG(UDMF_CLIENT, "start.");
    auto service = UdmfServiceClient::GetInstance();
    if (service == nullptr) {
        LOG_ERROR(UDMF_CLIENT, "Service unavailable");
        return E_ERROR;
    }

    int32_t ret = service->AddPrivilege(query, privilege);
    return static_cast<Status>(ret);
}

Status UdmfClient::Sync(const QueryOption &query, const std::vector<std::string> &devices)
{
    LOG_DEBUG(UDMF_CLIENT, "start.");
    auto service = UdmfServiceClient::GetInstance();
    if (service == nullptr) {
        LOG_ERROR(UDMF_CLIENT, "Service unavailable");
        return E_ERROR;
    }

    int32_t ret = service->Sync(query, devices);
    return static_cast<Status>(ret);
}
} // namespace UDMF
} // namespace OHOS