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
#define LOG_TAG "UtdNotifier"
#include "utd_notifier.h"

#include "ipc_skeleton.h"
#include "logger.h"
#include "utd_client.h"
#include "utd_tlv_util.h"

namespace OHOS::UDMF {
constexpr UtdNotifierStub::Handler
    UtdNotifierStub::HANDLERS[static_cast<uint32_t>(UtdNotifierInterfaceCode::CODE_BUTT)];

int UtdNotifierStub::OnRemoteRequest(
        uint32_t code, MessageParcel &data, MessageParcel &reply, MessageOption &option)
{
    LOG_INFO(UDMF_SERVICE, "code:%{public}u callingPid:%{public}u", code, IPCSkeleton::GetCallingPid());
    std::u16string local = GetDescriptor();
    std::u16string remote = data.ReadInterfaceToken();
    if (local != remote) {
        LOG_ERROR(UDMF_SERVICE, "local is not equal to remote");
        return E_IPC;
    }

    if (code < static_cast<uint32_t>(UtdNotifierInterfaceCode::CODE_HEAD) ||
        code >= static_cast<uint32_t>(UtdNotifierInterfaceCode::CODE_BUTT)) {
        return E_IPC;
    }
    return (this->*HANDLERS[code])(data, reply);
}

int32_t UtdNotifierStub::OnRegisterDynamicUtd(MessageParcel &data, MessageParcel &reply)
{
    std::vector<TypeDescriptorCfg> descriptors;
    std::string bundleName;
    if (!ITypesUtil::Unmarshal(data, descriptors, bundleName)) {
        LOG_ERROR(UDMF_SERVICE, "Unmarshal failed!");
        return E_READ_PARCEL_ERROR;
    }
    auto status = RegisterDynamicUtd(descriptors, bundleName);
    if (!ITypesUtil::Marshal(reply, status)) {
        LOG_ERROR(UDMF_SERVICE, "Marshal status or key failed, status: %{public}d", status);
        return E_WRITE_PARCEL_ERROR;
    }
    return E_OK;
}

int32_t UtdNotifierStub::OnUnregisterDynamicUtd(MessageParcel &data, MessageParcel &reply)
{
    std::vector<std::string> typeIds;
    std::string bundleName;
    if (!ITypesUtil::Unmarshal(data, typeIds, bundleName)) {
        LOG_ERROR(UDMF_SERVICE, "Unmarshal failed!");
        return E_READ_PARCEL_ERROR;
    }
    auto status = UnregisterDynamicUtd(typeIds, bundleName);
    if (!ITypesUtil::Marshal(reply, status)) {
        LOG_ERROR(UDMF_SERVICE, "Marshal status or key failed, status: %{public}d", status);
        return E_WRITE_PARCEL_ERROR;
    }
    return E_OK;
}

int32_t UtdNotifierStub::OnDynamicUtdChange(MessageParcel &data, MessageParcel &reply)
{
    auto status = DynamicUtdChange();
    if (!ITypesUtil::Marshal(reply, status)) {
        LOG_ERROR(UDMF_SERVICE, "Marshal status or key failed, status: %{public}d", status);
        return E_WRITE_PARCEL_ERROR;
    }
    return E_OK;
}

int32_t UtdNotifierClient::RegisterDynamicUtd(const std::vector<TypeDescriptorCfg> &descriptors,
    const std::string &bundleName)
{
    return UtdClient::GetInstance().InstallDynamicUtds(bundleName, descriptors);
}

int32_t UtdNotifierClient::UnregisterDynamicUtd(const std::vector<std::string> &typeIds, const std::string &bundleName)
{
    return UtdClient::GetInstance().UninstallDynamicUtds(bundleName, typeIds);
}

int32_t UtdNotifierClient::DynamicUtdChange()
{
    return UtdClient::GetInstance().InitializeUtdTypes();
}

} // namespace OHOS::UDMF
