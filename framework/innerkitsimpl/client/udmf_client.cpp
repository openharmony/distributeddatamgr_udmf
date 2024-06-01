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
#include "udmf_utils.h"
#include "unified_data_cache.h"
#include "accesstoken_kit.h"
#include "ipc_skeleton.h"

namespace OHOS {
namespace UDMF {
const std::string TAG = "UdmfClient::";
using namespace OHOS::DistributedDataDfx;
using namespace RadarReporter;
UdmfClient &UdmfClient::GetInstance()
{
    static UdmfClient instance;
    return instance;
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
    std::string shareOption;
    GetAppShareOption(UD_INTENTION_MAP.at(option.intention), shareOption);
    if (shareOption == "IN_APP") {
        std::string bundleName = GetSelfBundleName();
        if (bundleName.empty()) {
            LOG_ERROR(UDMF_CLIENT, "get self bundleName empty.");
            return E_ERROR;
        }
        UnifiedKey udKey = UnifiedKey(UD_INTENTION_MAP.at(option.intention), bundleName, UTILS::GenerateId());
        key = udKey.GetUnifiedKey();
        UnifiedDataCache::GetInstance().SetUnifiedData(key, unifiedData);
        LOG_INFO(UDMF_CLIENT, "SetData in app success.");
        RADAR_REPORT(BizScene::SET_DATA, SetDataStage::SET_DATA_END, StageRes::SUCCESS,
                     BIZ_STATE, BizState::DFX_NORMAL_END);
        return E_OK;
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
    LOG_ERROR(UDMF_CLIENT, "glxtest GetData 1");

    auto service = UdmfServiceClient::GetInstance();
    if (service == nullptr) {
        LOG_ERROR(UDMF_CLIENT, "Service unavailable");
        RADAR_REPORT(BizScene::GET_DATA, GetDataStage::GET_DATA_BEGIN, StageRes::FAILED, ERROR_CODE, E_IPC,
                     BIZ_STATE, BizState::DFX_ABNORMAL_END);
        return E_IPC;
    }
    LOG_ERROR(UDMF_CLIENT, "glxtest GetData 2");
    UnifiedKey udKey = UnifiedKey(query.key);
    LOG_ERROR(UDMF_CLIENT, "glxtest GetData 3");
    if (!udKey.IsValid()) {
        LOG_ERROR(UDMF_CLIENT, "query.key is invalid, %{public}s.", query.key.c_str());
        return E_ERROR;
    }
    std::string shareOption;
    GetAppShareOption(udKey.intention, shareOption);
    LOG_ERROR(UDMF_CLIENT, "glxtest GetData 4");
    if (shareOption == "IN_APP") {
        auto status = UnifiedDataCache::GetInstance().GetUnifiedDatas(query.key, unifiedData);
        if (status != E_OK) {
            LOG_ERROR(UDMF_CLIENT, "failed! status = %{public}d", status);
            return E_NOT_FOUND;
        }
        UnifiedDataCache::GetInstance().ClearUnifiedDatas(query.key);
        RADAR_REPORT(BizScene::GET_DATA, GetDataStage::GET_DATA_END, StageRes::SUCCESS,
                     BIZ_STATE, BizState::DFX_NORMAL_END);
        return E_OK;
    }
    LOG_ERROR(UDMF_CLIENT, "glxtest GetData 4");

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

Status UdmfClient::SetAppShareOption(const std::string &intention, const std::string &shareOption)
{
    DdsTrace trace(
        std::string(TAG) + std::string(__FUNCTION__), TraceSwitch::BYTRACE_ON | TraceSwitch::TRACE_CHAIN_ON);
    auto service = UdmfServiceClient::GetInstance();
    if (service == nullptr) {
        LOG_ERROR(UDMF_CLIENT, "Service unavailable");
        return E_IPC;
    }
    int32_t ret = service->SetAppShareOption(intention, shareOption);
    if (ret != E_OK) {
        LOG_ERROR(UDMF_CLIENT, "failed! ret = %{public}d", ret);
    }
    return static_cast<Status>(ret);
}

Status UdmfClient::GetAppShareOption(const std::string &intention, std::string &shareOption)
{
    DdsTrace trace(
        std::string(TAG) + std::string(__FUNCTION__), TraceSwitch::BYTRACE_ON | TraceSwitch::TRACE_CHAIN_ON);
    auto service = UdmfServiceClient::GetInstance();
    if (service == nullptr) {
        LOG_ERROR(UDMF_CLIENT, "Service unavailable");
        return E_IPC;
    }
    int32_t ret = service->GetAppShareOption(intention, shareOption);
    if (ret != E_OK) {
        LOG_ERROR(UDMF_CLIENT, "failed! ret = %{public}d", ret);
    }
    return static_cast<Status>(ret);
}


Status UdmfClient::RemoveAppShareOption(const std::string &intention)
{
    DdsTrace trace(
        std::string(TAG) + std::string(__FUNCTION__), TraceSwitch::BYTRACE_ON | TraceSwitch::TRACE_CHAIN_ON);
    auto service = UdmfServiceClient::GetInstance();
    if (service == nullptr) {
        LOG_ERROR(UDMF_CLIENT, "Service unavailable");
        return E_IPC;
    }
    int32_t ret = service->RemoveAppShareOption(intention);
    if (ret != E_OK) {
        LOG_ERROR(UDMF_CLIENT, "failed! ret = %{public}d", ret);
    }
    return static_cast<Status>(ret);
}

std::string UdmfClient::GetSelfBundleName()
{
    uint32_t tokenId = IPCSkeleton::GetSelfTokenID();
    Security::AccessToken::HapTokenInfo hapInfo;
    if (Security::AccessToken::AccessTokenKit::GetHapTokenInfo(tokenId, hapInfo)
        != Security::AccessToken::AccessTokenKitRet::RET_SUCCESS) {
        return "";
    }
    return hapInfo.bundleName;
}
} // namespace UDMF
} // namespace OHOS