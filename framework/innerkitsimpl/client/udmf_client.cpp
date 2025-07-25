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
#include "udmf_notifier_stub.h"
#include "unified_data_helper.h"
#include "unified_html_record_process.h"

namespace OHOS {
namespace UDMF {
constexpr const char *TAG = "UdmfClient::";
constexpr const char *BUNDLE_IN_APP = "udmf.inapp.data";
static constexpr int KEY_LEN = 32;
using namespace OHOS::DistributedDataDfx;
using namespace RadarReporter;
UdmfClient &UdmfClient::GetInstance()
{
    static UdmfClient instance;
    return instance;
}

void UdmfClient::ProcessDragIfInApp(UnifiedData &unifiedData, std::string &intentionDrag, std::string &key)
{
    std::string bundleName = BUNDLE_IN_APP;
    UnifiedKey udKey = UnifiedKey(intentionDrag, bundleName, UTILS::GenerateId());
    key = udKey.GetUnifiedKey();
    dataCache_.Clear();
    dataCache_.Insert(key, unifiedData);
    LOG_INFO(UDMF_CLIENT, "SetData in app success, bundleName:%{public}s.", bundleName.c_str());
    RadarReporterAdapter::ReportNormal(std::string(__FUNCTION__),
        BizScene::SET_DATA, SetDataStage::SET_DATA_END, StageRes::SUCCESS, BizState::DFX_END);
}

Status UdmfClient::SetData(CustomOption &option, UnifiedData &unifiedData, std::string &key)
{
    DdsTrace trace(
        std::string(TAG) + std::string(__FUNCTION__), TraceSwitch::BYTRACE_ON | TraceSwitch::TRACE_CHAIN_ON);
    RadarReporterAdapter::ReportNormal(std::string(__FUNCTION__),
        BizScene::SET_DATA, SetDataStage::SET_DATA_BEGIN, StageRes::IDLE, BizState::DFX_BEGIN);
    if (!UnifiedDataUtils::IsValidIntention(option.intention)) {
        LOG_ERROR(UDMF_SERVICE, "Invalid intention");
        return E_INVALID_PARAMETERS;
    }
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
        auto intentionDrag = UD_INTENTION_MAP.at(option.intention);
        auto status = GetAppShareOption(intentionDrag, shareOption);
        if (status != E_NOT_FOUND && status != E_OK) {
            RadarReporterAdapter::ReportFail(std::string(__FUNCTION__),
                BizScene::SET_DATA, SetDataStage::SET_DATA_END, StageRes::FAILED, status, BizState::DFX_END);
            LOG_ERROR(UDMF_CLIENT, "get appShareOption fail, intention:%{public}s", intentionDrag.c_str());
            return static_cast<Status>(status);
        }
        if (shareOption == ShareOptions::IN_APP) {
            ProcessDragIfInApp(unifiedData, intentionDrag, key);
            return E_OK;
        }
        if (unifiedData.HasType(UtdUtils::GetUtdIdFromUtdEnum(UDType::HTML))) {
            UnifiedHtmlRecordProcess::GetUriFromHtmlRecord(unifiedData);
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
    if (GetDataFromCache(query, unifiedData) == E_OK) {
        RadarReporterAdapter::ReportNormal(std::string(__FUNCTION__),
            BizScene::GET_DATA, GetDataStage::GET_DATA_END, StageRes::SUCCESS, BizState::DFX_END);
        return E_OK;
    }
    LOG_INFO(UDMF_CLIENT, "Data not found in cache. key = %{public}s", query.key.c_str());
    int32_t ret = service->GetData(query, unifiedData);
    if (ret != E_OK) {
        RadarReporterAdapter::ReportFail(std::string(__FUNCTION__),
            BizScene::GET_DATA, GetDataStage::GET_DATA_END, StageRes::FAILED, ret, BizState::DFX_END);
        LOG_ERROR(UDMF_CLIENT, "failed! ret = %{public}d", ret);
        return static_cast<Status>(ret);
    }
    if (unifiedData.HasType(UtdUtils::GetUtdIdFromUtdEnum(UDType::HTML))) {
        UnifiedHtmlRecordProcess::RebuildHtmlRecord(unifiedData);
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
    for (auto &data : unifiedDataSet) {
        data.ClearUriInfo();
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
        LOG_INFO(UDMF_CLIENT, "No share option was obtained, ret = %{public}d", ret);
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

Status UdmfClient::GetDataFromCache(const QueryOption &query, UnifiedData &unifiedData)
{
    auto it = dataCache_.Find(query.key);
    if (it.first) {
        unifiedData = it.second;
        dataCache_.Erase(query.key);
        return E_OK;
    }
    return E_NOT_FOUND;
}

Status UdmfClient::GetParentType(Summary &oldSummary, Summary &newSummary)
{
    newSummary = oldSummary;
    if (oldSummary.fileTypes.empty()) {
        LOG_ERROR(UDMF_CLIENT, "fileTypes is empty.");
        return E_OK;
    }
    std::map<std::string, int64_t> tmpSummary;
    auto types = oldSummary.fileTypes;
    std::set<std::string> summaryKey;
    for (auto item : oldSummary.summary) {
        // This type does not belong to the basic file types or is not a file type.
        if (UnifiedDataUtils::IsFilterFileType(item.first) ||
            (std::find(types.begin(), types.end(), item.first) == types.end())) {
            UnifiedDataUtils::MergeSummary(tmpSummary, summaryKey, item.first, item.second);
        } else {
            auto type = UnifiedDataUtils::IsFileSubType(item.first);
            UnifiedDataUtils::MergeSummary(tmpSummary, summaryKey, type, item.second);
        }
    }
    newSummary.summary = tmpSummary;
    return E_OK;
}

Status UdmfClient::SetDelayInfo(const DataLoadParams &dataLoadParams, std::string &key)
{
    if (dataLoadParams.dataLoadInfo.sequenceKey.length() != KEY_LEN) {
        LOG_ERROR(UDMF_CLIENT, "Invalid key=%{public}s", dataLoadParams.dataLoadInfo.sequenceKey.c_str());
        return E_INVALID_PARAMETERS;
    }
    auto service = UdmfServiceClient::GetInstance();
    if (service == nullptr) {
        LOG_ERROR(UDMF_CLIENT, "Service unavailable");
        return E_IPC;
    }
    sptr<IRemoteObject> iUdmfNotifier = new (std::nothrow) UdmfNotifierClient(dataLoadParams.loadHandler);
    if (iUdmfNotifier == nullptr) {
        LOG_ERROR(UDMF_CLIENT, "IUdmfNotifier unavailable");
        return E_IPC;
    }
    auto ret = service->SetDelayInfo(dataLoadParams.dataLoadInfo, iUdmfNotifier, key);
    if (ret != E_OK) {
        LOG_ERROR(UDMF_CLIENT, "Failed, ret = %{public}d, udkey = %{public}s.", ret, key.c_str());
    }
    return static_cast<Status>(ret);
}

Status UdmfClient::PushDelayData(const std::string &key, UnifiedData &unifiedData)
{
    if (key.empty()) {
        LOG_ERROR(UDMF_CLIENT, "Empty key");
        return E_INVALID_PARAMETERS;
    }
    auto service = UdmfServiceClient::GetInstance();
    if (service == nullptr) {
        LOG_ERROR(UDMF_CLIENT, "Service unavailable");
        return E_IPC;
    }
    auto status = service->PushDelayData(key, unifiedData);
    if (status != E_OK) {
        LOG_ERROR(UDMF_CLIENT, "Failed, ret = %{public}d", status);
    }
    return static_cast<Status>(status);
}

Status UdmfClient::GetDataIfAvailable(const std::string &key, const DataLoadInfo &dataLoadInfo,
    sptr<IRemoteObject> iUdmfNotifier, std::shared_ptr<UnifiedData> unifiedData)
{
    if (key.empty() || iUdmfNotifier == nullptr) {
        LOG_ERROR(UDMF_CLIENT, "Empty key or notifier");
        return E_INVALID_PARAMETERS;
    }
    auto service = UdmfServiceClient::GetInstance();
    if (service == nullptr) {
        LOG_ERROR(UDMF_CLIENT, "Service unavailable");
        return E_IPC;
    }
    int32_t ret = service->GetDataIfAvailable(key, dataLoadInfo, iUdmfNotifier, unifiedData);
    if (ret != E_OK) {
        LOG_ERROR(UDMF_CLIENT, "Failed! ret = %{public}d", ret);
        return static_cast<Status>(ret);
    }
    return E_OK;
}

std::string UdmfClient::GetBundleNameByUdKey(const std::string &key)
{
    UnifiedKey udkey(key);
    if (!udkey.IsValid()) {
        LOG_ERROR(UDMF_CLIENT, "IsValid udkey:%{public}s", key.c_str());
        return "";
    }
    return udkey.bundleName;
}

} // namespace UDMF
} // namespace OHOS