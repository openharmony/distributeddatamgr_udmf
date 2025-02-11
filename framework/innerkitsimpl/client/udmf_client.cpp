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
#include "udmf_conversion.h"
#include "udmf_radar_reporter.h"

#include "logger.h"
#include "udmf_service_client.h"
#include "udmf_utils.h"
#include "accesstoken_kit.h"
#include "ipc_skeleton.h"
#include "unified_data_helper.h"

namespace OHOS {
namespace UDMF {
constexpr const char *TAG = "UdmfClient::";
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
    RadarReporterAdapter::ReportNormal(std::string(__FUNCTION__),
        BizScene::SET_DATA, SetDataStage::SET_DATA_BEGIN, StageRes::IDLE, BizState::DFX_BEGIN);
    auto service = UdmfServiceClient::GetInstance();
    if (service == nullptr) {
        LOG_ERROR(UDMF_CLIENT, "Service unavailable");
        RadarReporterAdapter::ReportFail(std::string(__FUNCTION__),
            BizScene::SET_DATA, SetDataStage::SET_DATA_BEGIN, StageRes::FAILED, E_IPC, BizState::DFX_END);
        return E_IPC;
    }
    RadarReporterAdapter::ReportNormal(std::string(__FUNCTION__),
        BizScene::SET_DATA, SetDataStage::SET_DATA_BEGIN, StageRes::SUCCESS);
    if (option.intention == UD_INTENTION_DRAG) {
        ShareOptions shareOption = SHARE_OPTIONS_BUTT;
        auto status = GetAppShareOption(UD_INTENTION_MAP.at(option.intention), shareOption);
        if (status != E_NOT_FOUND && status != E_OK) {
            RadarReporterAdapter::ReportFail(std::string(__FUNCTION__),
                BizScene::SET_DATA, SetDataStage::SET_DATA_END, StageRes::FAILED, status, BizState::DFX_END);
            LOG_ERROR(UDMF_CLIENT, "get appShareOption fail, intention:%{public}s",
                      UD_INTENTION_MAP.at(option.intention).c_str());
            return static_cast<Status>(status);
        }
        if (shareOption == ShareOptions::IN_APP) {
            std::string bundleName = "udmf.inapp.data";
            UnifiedKey udKey = UnifiedKey(UD_INTENTION_MAP.at(option.intention), bundleName, UTILS::GenerateId());
            key = udKey.GetUnifiedKey();
            dataCache_.Clear();
            dataCache_.Insert(key, unifiedData);
            LOG_INFO(UDMF_CLIENT, "SetData in app success, bundleName:%{public}s.", bundleName.c_str());
            RadarReporterAdapter::ReportNormal(std::string(__FUNCTION__),
                BizScene::SET_DATA, SetDataStage::SET_DATA_END, StageRes::SUCCESS, BizState::DFX_END);
            return E_OK;
        }
    }
    int32_t ret = service->SetData(option, unifiedData, key);
    if (ret != E_OK) {
        RadarReporterAdapter::ReportFail(std::string(__FUNCTION__),
            BizScene::SET_DATA, SetDataStage::SET_DATA_END, StageRes::FAILED, ret, BizState::DFX_END);
        LOG_ERROR(UDMF_CLIENT, "failed! ret = %{public}d", ret);
        return static_cast<Status>(ret);
    }
    RadarReporterAdapter::ReportNormal(std::string(__FUNCTION__),
        BizScene::SET_DATA, SetDataStage::SET_DATA_END, StageRes::SUCCESS, BizState::DFX_END);
    return E_OK;
}

Status UdmfClient::GetData(const QueryOption &query, UnifiedData &unifiedData)
{
    DdsTrace trace(
        std::string(TAG) + std::string(__FUNCTION__), TraceSwitch::BYTRACE_ON | TraceSwitch::TRACE_CHAIN_ON);
    RadarReporterAdapter::ReportNormal(std::string(__FUNCTION__),
        BizScene::GET_DATA, GetDataStage::GET_DATA_BEGIN, StageRes::IDLE, BizState::DFX_BEGIN);
    auto service = UdmfServiceClient::GetInstance();
    if (service == nullptr) {
        LOG_ERROR(UDMF_CLIENT, "Service unavailable");
        RadarReporterAdapter::ReportFail(std::string(__FUNCTION__),
            BizScene::GET_DATA, GetDataStage::GET_DATA_BEGIN, StageRes::FAILED, E_IPC, BizState::DFX_END);
        return E_IPC;
    }
	RadarReporterAdapter::ReportNormal(std::string(__FUNCTION__),
        BizScene::GET_DATA, GetDataStage::GET_DATA_BEGIN, StageRes::SUCCESS);
    auto it = dataCache_.Find(query.key);
    if (it.first) {
        unifiedData = it.second;
        dataCache_.Erase(query.key);
        RadarReporterAdapter::ReportNormal(std::string(__FUNCTION__),
            BizScene::GET_DATA, GetDataStage::GET_DATA_END, StageRes::SUCCESS, BizState::DFX_END);
        return E_OK;
    }
    LOG_WARN(UDMF_CLIENT, "query data from cache failed! key = %{public}s", query.key.c_str());
    int32_t ret = service->GetData(query, unifiedData);
    if (ret != E_OK) {
        RadarReporterAdapter::ReportFail(std::string(__FUNCTION__),
            BizScene::GET_DATA, GetDataStage::GET_DATA_END, StageRes::FAILED, ret, BizState::DFX_END);
        LOG_ERROR(UDMF_CLIENT, "failed! ret = %{public}d", ret);
        return static_cast<Status>(ret);
    }
    RadarReporterAdapter::ReportNormal(std::string(__FUNCTION__),
        BizScene::GET_DATA, GetDataStage::GET_DATA_END, StageRes::SUCCESS, BizState::DFX_END);
    return E_OK;
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
    auto it = dataCache_.Find(query.key);
    if (it.first) {
        UdmfConversion::InitValueObject(it.second);
        UnifiedDataHelper::GetSummary(it.second, summary);
        LOG_INFO(UDMF_CLIENT, "GetSummary in cache! key = %{public}s", query.key.c_str());
        return E_OK;
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

Status UdmfClient::SetAppShareOption(const std::string &intention, enum ShareOptions shareOption)
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

Status UdmfClient::GetAppShareOption(const std::string &intention, enum ShareOptions &shareOption)
{
    DdsTrace trace(
        std::string(TAG) + std::string(__FUNCTION__), TraceSwitch::BYTRACE_ON | TraceSwitch::TRACE_CHAIN_ON);
    auto service = UdmfServiceClient::GetInstance();
    if (service == nullptr) {
        LOG_ERROR(UDMF_CLIENT, "Service unavailable");
        return E_IPC;
    }
    int32_t shareOptionRet = SHARE_OPTIONS_BUTT;
    int32_t ret = service->GetAppShareOption(intention, shareOptionRet);
    if (ShareOptionsUtil::IsValid(shareOptionRet)) {
        shareOption = static_cast<ShareOptions>(shareOptionRet);
    }
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