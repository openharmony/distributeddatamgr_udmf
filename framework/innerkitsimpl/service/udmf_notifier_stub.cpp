/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
#define LOG_TAG "UdmfNotifierStub"
#include "udmf_notifier_stub.h"

#include "error_code.h"
#include "ipc_skeleton.h"
#include "logger.h"
#include "udmf_types_util.h"
#include "udmf_conversion.h"
#include "unified_html_record_process.h"

namespace OHOS {
namespace UDMF {

int32_t UdmfNotifierStub::OnRemoteRequest(uint32_t code, MessageParcel &data, MessageParcel &reply, MessageOption &option)
{
    LOG_ERROR(UDMF_SERVICE, "zzz start");
    LOG_INFO(UDMF_SERVICE, "code:%{public}u callingPid:%{public}u", code, IPCSkeleton::GetCallingPid());
    std::u16string local = GetDescriptor();
    std::u16string remote = data.ReadInterfaceToken();
    if (local != remote) {
        LOG_ERROR(UDMF_SERVICE, "local is not equal to remote");
        return -1;
    }

    std::string key;
    DataLoadInfo dataLoadInfo;
    if (!ITypesUtil::Unmarshal(data, key, dataLoadInfo)) {
        LOG_ERROR(UDMF_SERVICE, "Unmarshal failed!");
        return E_READ_PARCEL_ERROR;
    }

    HandleDelayObserver(key, dataLoadInfo);
    return 0;
}

UdmfNotifierClient::UdmfNotifierClient(LoadHandler loadHandler):loadHandler_(loadHandler) {}

void UdmfNotifierClient::HandleDelayObserver(const std::string &key, const DataLoadInfo &dataLoadInfo)
{
    auto updateTask = [=]() {
        loadHandler_(key, dataLoadInfo);
    };
    std::thread(updateTask).detach();
}



int32_t DelayDataCallbackStub::OnRemoteRequest(uint32_t code, MessageParcel &data, MessageParcel &reply, MessageOption &option)
{
    LOG_ERROR(UDMF_SERVICE, "zzz start");
    LOG_INFO(UDMF_SERVICE, "code:%{public}u callingPid:%{public}u", code, IPCSkeleton::GetCallingPid());
    std::u16string local = GetDescriptor();
    std::u16string remote = data.ReadInterfaceToken();
    if (local != remote) {
        LOG_ERROR(UDMF_SERVICE, "local is not equal to remote");
        return -1;
    }

    std::string key;
    UnifiedData unifiedData;
    if (!ITypesUtil::Unmarshal(data, key, unifiedData)) {
        LOG_ERROR(UDMF_SERVICE, "Unmarshal failed!");
        return E_READ_PARCEL_ERROR;
    }
    UdmfConversion::ConvertRecordToSubclass(unifiedData);

    if (unifiedData.HasType(UtdUtils::GetUtdIdFromUtdEnum(UDType::HTML))) {
        UnifiedHtmlRecordProcess::RebuildHtmlRecord(unifiedData);
    }
    DelayDataCallback(key, unifiedData);
    return 0;
}

DelayDataCallbackClient::DelayDataCallbackClient(DataCallback loadHandler):loadHandler_(loadHandler) {}

void DelayDataCallbackClient::DelayDataCallback(const std::string &key, const UnifiedData &unifiedData)
{
    auto updateTask = [=]() {
        loadHandler_(key, unifiedData);
    };
    std::thread(updateTask).detach();
}

} // namespace UDMF
} // namespace OHOS