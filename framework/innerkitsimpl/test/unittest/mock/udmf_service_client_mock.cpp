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
#include "udmf_service_client_mock.h"

namespace OHOS::UDMF {
using namespace std;

std::shared_ptr<UdmfServiceClient> UdmfServiceClient::GetInstance()
{
    if (MUdmfServiceClient::udmfServiceClient == nullptr) {
        return nullptr;
    } else {
        return MUdmfServiceClient::udmfServiceClient->GetInstance();
    }
}

int32_t UdmfServiceClient::GetAppShareOption(const std::string &intention, int32_t &shareOption)
{
    if (MUdmfServiceClient::udmfServiceClient == nullptr) {
        return -1;
    } else {
        return MUdmfServiceClient::udmfServiceClient->GetAppShareOption(intention, shareOption);
    }
}

int32_t UdmfServiceClient::SetData(CustomOption &option, UnifiedData &unifiedData, std::string &key)
{
    if (MUdmfServiceClient::udmfServiceClient == nullptr) {
        return -1;
    } else {
        return MUdmfServiceClient::udmfServiceClient->SetData(option, unifiedData, key);
    }
}

int32_t UdmfServiceClient::GetData(const QueryOption &query, UnifiedData &unifiedData)
{
    if (MUdmfServiceClient::udmfServiceClient == nullptr) {
        return -1;
    } else {
        return MUdmfServiceClient::udmfServiceClient->GetData(query, unifiedData);
    }
}

int32_t UdmfServiceClient::GetBatchData(const QueryOption &query, std::vector<UnifiedData> &unifiedDataSet)
{
    if (MUdmfServiceClient::udmfServiceClient == nullptr) {
        return -1;
    } else {
        return MUdmfServiceClient::udmfServiceClient->GetBatchData(query, unifiedDataSet);
    }
}

int32_t UdmfServiceClient::DeleteData(const QueryOption &query, std::vector<UnifiedData> &unifiedDataSet)
{
    if (MUdmfServiceClient::udmfServiceClient == nullptr) {
        return -1;
    } else {
        return MUdmfServiceClient::udmfServiceClient->DeleteData(query, unifiedDataSet);
    }
}

int32_t UdmfServiceClient::UpdateData(const QueryOption &query, UnifiedData &unifiedData)
{
    if (MUdmfServiceClient::udmfServiceClient == nullptr) {
        return -1;
    } else {
        return MUdmfServiceClient::udmfServiceClient->UpdateData(query, unifiedData);
    }
}

int32_t UdmfServiceClient::GetSummary(const QueryOption &query, Summary &summary)
{
    if (MUdmfServiceClient::udmfServiceClient == nullptr) {
        return -1;
    } else {
        return MUdmfServiceClient::udmfServiceClient->GetSummary(query, summary);
    }
}

int32_t UdmfServiceClient::IsRemoteData(const QueryOption &query, bool &result)
{
    if (MUdmfServiceClient::udmfServiceClient == nullptr) {
        return -1;
    } else {
        return MUdmfServiceClient::udmfServiceClient->IsRemoteData(query, result);
    }
}

int32_t UdmfServiceClient::Sync(const QueryOption &query, const std::vector<std::string> &devices)
{
    if (MUdmfServiceClient::udmfServiceClient == nullptr) {
        return -1;
    } else {
        return MUdmfServiceClient::udmfServiceClient->Sync(query, devices);
    }
}

int32_t UdmfServiceClient::ClearAsynProcessByKey(const std::string &businessUdKey)
{
    if (MUdmfServiceClient::udmfServiceClient == nullptr) {
        return -1;
    } else {
        return MUdmfServiceClient::udmfServiceClient->ClearAsynProcessByKey(businessUdKey);
    }
}

int32_t UdmfServiceClient::SetAppShareOption(const std::string &intention, int32_t shareOption)
{
    if (MUdmfServiceClient::udmfServiceClient == nullptr) {
        return -1;
    } else {
        return MUdmfServiceClient::udmfServiceClient->SetAppShareOption(intention, shareOption);
    }
}


int32_t UdmfServiceClient::RemoveAppShareOption(const std::string &intention)
{
    if (MUdmfServiceClient::udmfServiceClient == nullptr) {
        return -1;
    } else {
        return MUdmfServiceClient::udmfServiceClient->RemoveAppShareOption(intention);
    }
}

int32_t UdmfServiceClient::AddPrivilege(const QueryOption &query, Privilege &privilege)
{
    if (MUdmfServiceClient::udmfServiceClient == nullptr) {
        return -1;
    } else {
        return MUdmfServiceClient::udmfServiceClient->AddPrivilege(query, privilege);
    }
}

int32_t UdmfServiceClient::ObtainAsynProcess(AsyncProcessInfo &processInfo)
{
    if (MUdmfServiceClient::udmfServiceClient == nullptr) {
        return -1;
    } else {
        return MUdmfServiceClient::udmfServiceClient->ObtainAsynProcess(processInfo);
    }
}

int32_t UdmfServiceClient::SetDelayInfo(const DataLoadInfo &dataLoadInfo, sptr<IRemoteObject> iUdmfNotifier,
    std::string &key)
{
    if (MUdmfServiceClient::udmfServiceClient == nullptr) {
        return -1;
    } else {
        return MUdmfServiceClient::udmfServiceClient->SetDelayInfo(dataLoadInfo, iUdmfNotifier, key);
    }
}

int32_t UdmfServiceClient::PushDelayData(const std::string &key, UnifiedData &unifiedData)
{
    if (MUdmfServiceClient::udmfServiceClient == nullptr) {
        return -1;
    } else {
        return MUdmfServiceClient::udmfServiceClient->PushDelayData(key, unifiedData);
    }
}

int32_t UdmfServiceClient::GetDataIfAvailable(const std::string &key, const DataLoadInfo &dataLoadInfo,
    sptr<IRemoteObject> iUdmfNotifier, std::shared_ptr<UnifiedData> unifiedData)
{
    if (MUdmfServiceClient::udmfServiceClient == nullptr) {
        return -1;
    } else {
        return MUdmfServiceClient::udmfServiceClient->GetDataIfAvailable(key, dataLoadInfo, iUdmfNotifier, unifiedData);
    }
}

int32_t UdmfServiceClient::PushAcceptableInfo(const QueryOption &query, const std::vector<std::string> &devices)
{
    if (MUdmfServiceClient::udmfServiceClient == nullptr) {
        return -1;
    } else {
        return MUdmfServiceClient::udmfServiceClient->PushAcceptableInfo(query, devices);
    }
}

int32_t UdmfServiceClient::SaveAcceptableInfo(const std::string &key, DataLoadInfo &info)
{
    if (MUdmfServiceClient::udmfServiceClient == nullptr) {
        return -1;
    } else {
        return MUdmfServiceClient::udmfServiceClient->SaveAcceptableInfo(key, info);
    }
}
} // namespace OHOS::UDMF
