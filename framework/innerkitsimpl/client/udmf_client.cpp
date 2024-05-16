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
#define LOG_TAG "UdmfClient"
#include "udmf_client.h"

#include "dds_trace.h"
#include "udmf_radar_reporter.h"

#include "error_code.h"
#include "logger.h"
#include "udmf_service_client.h"

namespace OHOS {
namespace UDMF {
const std::string TAG = "UdmfClient::";
using namespace OHOS::DistributedDataDfx;
using namespace RadarReporter;
UdmfClient &UdmfClient::GetInstance()
{
    static auto instance_ = new UdmfClient();
    return *instance_;
}

Status UdmfClient::SetData(CustomOption &option, UnifiedData &unifiedData, std::string &key)
{
    DdsTrace trace(
        std::string(TAG) + std::string(__FUNCTION__), TraceSwitch::BYTRACE_ON | TraceSwitch::TRACE_CHAIN_ON);
    RADAR_REPORT(BizScene::SET_DATA, SetDataStage::SET_DATA_BEGIN, StageRes::IDLE, BIZ_STATE, BizState::DFX_BEGIN);
    auto service = UdmfServiceClient::GetInstance();
    if (service == nullptr) {
        LOG_ERROR(UDMF_CLIENT, "Service unavailable");
        RADAR_REPORT(BizScene::SET_DATA, SetDataStage::SET_DATA_BEGIN, StageRes::FAILED, ERROR_CODE, E_IPC,
                     BIZ_STATE, BizState::DFX_ABNORMAL_END);
        return E_IPC;
    }
    int32_t ret = service->SetData(option, unifiedData, key);
    if (ret != E_OK) {
        RADAR_REPORT(BizScene::SET_DATA, SetDataStage::SET_DATA_END, StageRes::FAILED, ERROR_CODE, ret,
                     BIZ_STATE, BizState::DFX_ABNORMAL_END);
        LOG_ERROR(UDMF_CLIENT, "failed! ret = %{public}d", ret);
    }
    RADAR_REPORT(BizScene::SET_DATA, SetDataStage::SET_DATA_END, StageRes::SUCCESS,
                 BIZ_STATE, BizState::DFX_NORMAL_END);
    return static_cast<Status>(ret);
}

Status UdmfClient::GetData(const QueryOption &query, UnifiedData &unifiedData)
{
    DdsTrace trace(
        std::string(TAG) + std::string(__FUNCTION__), TraceSwitch::BYTRACE_ON | TraceSwitch::TRACE_CHAIN_ON);
    RADAR_REPORT(BizScene::GET_DATA, GetDataStage::GET_DATA_BEGIN, StageRes::IDLE, BIZ_STATE, BizState::DFX_BEGIN);
    auto service = UdmfServiceClient::GetInstance();
    if (service == nullptr) {
        LOG_ERROR(UDMF_CLIENT, "Service unavailable");
        RADAR_REPORT(BizScene::GET_DATA, GetDataStage::GET_DATA_BEGIN, StageRes::FAILED, ERROR_CODE, E_IPC,
                     BIZ_STATE, BizState::DFX_ABNORMAL_END);
        return E_IPC;
    }
    int32_t ret = service->GetData(query, unifiedData);
    if (ret != E_OK) {
        RADAR_REPORT(BizScene::GET_DATA, GetDataStage::GET_DATA_END, StageRes::FAILED, ERROR_CODE, ret,
                     BIZ_STATE, BizState::DFX_ABNORMAL_END);
        LOG_ERROR(UDMF_CLIENT, "failed! ret = %{public}d", ret);
    }
    RADAR_REPORT(BizScene::GET_DATA, GetDataStage::GET_DATA_END, StageRes::SUCCESS,
                 BIZ_STATE, BizState::DFX_NORMAL_END);
    return static_cast<Status>(ret);
}

Status UdmfClient::GetBatchData(const QueryOption &query, std::vector<UnifiedData> &unifiedDataSet)
{
    DdsTrace trace(
        std::string(TAG) + std::string(__FUNCTION__), TraceSwitch::BYTRACE_ON | TraceSwitch::TRACE_CHAIN_ON);
    auto service = UdmfServiceClient::GetInstance();
    if (service == nullptr) {
        LOG_ERROR(UDMF_CLIENT, "Service unavailable");
        return E_IPC;
    }
    int32_t ret = service->GetBatchData(query, unifiedDataSet);
    if (ret != E_OK) {
        LOG_ERROR(UDMF_CLIENT, "failed! ret = %{public}d", ret);
    }
    return static_cast<Status>(ret);
}

Status UdmfClient::UpdateData(const QueryOption &query, UnifiedData &unifiedData)
{
    DdsTrace trace(
        std::string(TAG) + std::string(__FUNCTION__), TraceSwitch::BYTRACE_ON | TraceSwitch::TRACE_CHAIN_ON);
    auto service = UdmfServiceClient::GetInstance();
    if (service == nullptr) {
        LOG_ERROR(UDMF_CLIENT, "Service unavailable");
        return E_IPC;
    }
    int32_t ret = service->UpdateData(query, unifiedData);
    if (ret != E_OK) {
        LOG_ERROR(UDMF_CLIENT, "failed! ret = %{public}d", ret);
    }
    return static_cast<Status>(ret);
}

Status UdmfClient::DeleteData(const QueryOption &query, std::vector<UnifiedData> &unifiedDataSet)
{
    DdsTrace trace(
        std::string(TAG) + std::string(__FUNCTION__), TraceSwitch::BYTRACE_ON | TraceSwitch::TRACE_CHAIN_ON);
    auto service = UdmfServiceClient::GetInstance();
    if (service == nullptr) {
        LOG_ERROR(UDMF_CLIENT, "Service unavailable");
        return E_IPC;
    }
    int32_t ret = service->DeleteData(query, unifiedDataSet);
    if (ret != E_OK) {
        LOG_ERROR(UDMF_CLIENT, "failed! ret = %{public}d", ret);
    }
    return static_cast<Status>(ret);
}

Status UdmfClient::GetSummary(const QueryOption &query, Summary &summary)
{
    DdsTrace trace(
        std::string(TAG) + std::string(__FUNCTION__), TraceSwitch::BYTRACE_ON | TraceSwitch::TRACE_CHAIN_ON);
    auto service = UdmfServiceClient::GetInstance();
    if (service == nullptr) {
        LOG_ERROR(UDMF_CLIENT, "Service unavailable");
        return E_IPC;
    }
    int32_t ret = service->GetSummary(query, summary);
    if (ret != E_OK) {
        LOG_ERROR(UDMF_CLIENT, "failed! ret = %{public}d", ret);
    }
    return static_cast<Status>(ret);
}

Status UdmfClient::AddPrivilege(const QueryOption &query, Privilege &privilege)
{
    DdsTrace trace(
        std::string(TAG) + std::string(__FUNCTION__), TraceSwitch::BYTRACE_ON | TraceSwitch::TRACE_CHAIN_ON);
    auto service = UdmfServiceClient::GetInstance();
    if (service == nullptr) {
        LOG_ERROR(UDMF_CLIENT, "Service unavailable");
        return E_IPC;
    }
    int32_t ret = service->AddPrivilege(query, privilege);
    if (ret != E_OK) {
        LOG_ERROR(UDMF_CLIENT, "failed! ret = %{public}d", ret);
    }
    return static_cast<Status>(ret);
}

Status UdmfClient::Sync(const QueryOption &query, const std::vector<std::string> &devices)
{
    DdsTrace trace(
        std::string(TAG) + std::string(__FUNCTION__), TraceSwitch::BYTRACE_ON | TraceSwitch::TRACE_CHAIN_ON);
    auto service = UdmfServiceClient::GetInstance();
    if (service == nullptr) {
        LOG_ERROR(UDMF_CLIENT, "Service unavailable");
        return E_IPC;
    }
    int32_t ret = service->Sync(query, devices);
    if (ret != E_OK) {
        LOG_ERROR(UDMF_CLIENT, "failed! ret = %{public}d", ret);
    }
    return static_cast<Status>(ret);
}

Status UdmfClient::IsRemoteData(const QueryOption &query, bool &result)
{
    DdsTrace trace(
        std::string(TAG) + std::string(__FUNCTION__), TraceSwitch::BYTRACE_ON | TraceSwitch::TRACE_CHAIN_ON);
    auto service = UdmfServiceClient::GetInstance();
    if (service == nullptr) {
        LOG_ERROR(UDMF_CLIENT, "Service unavailable");
        return E_IPC;
    }
    int32_t ret = service->IsRemoteData(query, result);
    if (ret != E_OK) {
        LOG_ERROR(UDMF_CLIENT, "failed! ret = %{public}d", ret);
    }
    return static_cast<Status>(ret);
}
} // namespace UDMF
} // namespace OHOS