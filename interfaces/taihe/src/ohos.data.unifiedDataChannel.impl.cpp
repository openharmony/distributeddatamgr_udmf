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

#define LOG_TAG "UDMF_DATA_CHANNEL_TAIHE"

#include "logger.h"
#include "ohos.data.unifiedDataChannel.proj.hpp"
#include "ohos.data.unifiedDataChannel.impl.hpp"
#include "plain_text.h"
#include "stdexcept"
#include "taihe_common_utils.h"
#include "taihe/runtime.hpp"
#include "udmf_client.h"
#include "unified_data.h"
#include "unified_data_taihe.h"
#include "unified_record.h"
#include "unified_meta.h"

namespace OHOS {
namespace UDMF {
namespace taiheChannel = ohos::data::unifiedDataChannel;

bool IsValidOptionInfoNonDrag(UnifiedKey &key, const std::string &intention)
{
    if (UnifiedDataUtils::IsValidOptions(key, intention)) {
        return !key.key.empty() || intention == UD_INTENTION_MAP.at(Intention::UD_INTENTION_DATA_HUB);
    }
    return false;
}

::taihe::string InsertDataSync(::taiheChannel::Options const& options,
    ::taiheChannel::weak::UnifiedDataInner data)
{
    if (!options.intention.has_value()) {
        LOG_ERROR(UDMF_ANI, "Intention is empty");
        taihe::set_business_error(PARAMETERSERROR, "Parameter error.");
        return "";
    }
    auto intention = ConvertIntention(options.intention.value());
    if (!UnifiedDataUtils::IsPersist(intention)) {
        taihe::set_business_error(PARAMETERSERROR,
            "Parameter error: parameter options intention type must correspond to Intention");
        return "";
    }
    auto visibility = Visibility::VISIBILITY_ALL;
    if (options.visibility.has_value()) {
        visibility = ConvertVisibility(options.visibility.value());
        if (!UnifiedDataUtils::IsPersist(visibility)) {
            taihe::set_business_error(PARAMETERSERROR,
                "Parameter error: parameter options visibility type must correspond to Visibility");
            return "";
        }
    }
    CustomOption customOption;

    customOption.intention = intention;
    customOption.visibility = visibility;
    auto unifiedDataImpl = reinterpret_cast<OHOS::UDMF::UnifiedDataTaihe*>(data->GetInner());
    auto unifiedData = unifiedDataImpl->value_;
    std::string key;
    auto status = UdmfClient::GetInstance().SetData(customOption, *unifiedData, key);
    if (status != E_OK) {
        LOG_ERROR(UDMF_ANI, "Set data failed, status: %{public}d", status);
        taihe::set_business_error(PARAMETERSERROR, "Parameter error.");
        return "";
    }
    return ::taihe::string(key);
}

::taihe::array<::taiheChannel::UnifiedDataInner> QueryDataSync(
    ::taiheChannel::Options const& options)
{
    QueryOption queryOption;
    std::vector<::taiheChannel::UnifiedDataInner> dataImpls;

    if (!options.intention.has_value() && !options.key.has_value()) {
        LOG_ERROR(UDMF_ANI, "Intention and key are empty");
        taihe::set_business_error(PARAMETERSERROR, "Parameter error.");
        return ::taihe::array<::taiheChannel::UnifiedDataInner>(dataImpls);
    }
    if (options.intention.has_value()) {
        queryOption.intention = ConvertIntention(options.intention.value());
    }
    if (options.key.has_value()) {
        queryOption.key = options.key.value();
    }
    std::vector<UnifiedData> unifiedDataSet;
    auto status = UdmfClient::GetInstance().GetBatchData(queryOption, unifiedDataSet);
    if (status != E_OK) {
        LOG_ERROR(UDMF_ANI, "Get batch data failed, status: %{public}d", status);
        taihe::set_business_error(PARAMETERSERROR, "Parameter error.");
        return ::taihe::array<::taiheChannel::UnifiedDataInner>(dataImpls);
    }
    for (auto &data : unifiedDataSet) {
        auto dataImpl = taihe::make_holder<OHOS::UDMF::UnifiedDataTaihe, ::taiheChannel::UnifiedDataInner>();
        auto dataImplPtr = reinterpret_cast<OHOS::UDMF::UnifiedDataTaihe*>(dataImpl->GetInner());
        dataImplPtr->value_ = std::make_shared<UnifiedData>(data);
        dataImpls.push_back(dataImpl);
    }
    return ::taihe::array<::taiheChannel::UnifiedDataInner>(dataImpls);
}

void UpdateDataSync(::taiheChannel::Options const& options,
    ::taiheChannel::weak::UnifiedDataInner data)
{
    QueryOption queryOption;
    if (!options.key.has_value()) {
        LOG_ERROR(UDMF_ANI, "key is empty");
        taihe::set_business_error(PARAMETERSERROR,
            "Parameter error: parameter options intention type must correspond to Intention");
        return;
    }
    queryOption.key = options.key.value();
    UnifiedKey key(queryOption.key);
    if (!key.IsValid() || key.intention != UD_INTENTION_MAP.at(Intention::UD_INTENTION_DATA_HUB)) {
        LOG_ERROR(UDMF_ANI, "Parameter error.");
        taihe::set_business_error(PARAMETERSERROR,
            "Parameter error: parameter options intention type must correspond to Intention");
        return;
    }
    auto unifiedDataImpl = reinterpret_cast<OHOS::UDMF::UnifiedDataTaihe*>(data->GetInner());
    auto unifiedData = unifiedDataImpl->value_;
    auto status = UdmfClient::GetInstance().UpdateData(queryOption, *unifiedData);
    if (status != E_OK) {
        LOG_ERROR(UDMF_ANI, "Set data failed, status: %{public}d", status);
        taihe::set_business_error(PARAMETERSERROR, "Parameter error.");
        return;
    }
    return;
}

::taihe::array<::taiheChannel::UnifiedDataInner> DeleteDataSync(
    ::taiheChannel::Options const& options)
{
    QueryOption queryOption;
    std::vector<::taiheChannel::UnifiedDataInner> dataImpls;

    if (!options.intention.has_value() && !options.key.has_value()) {
        LOG_ERROR(UDMF_ANI, "Intention and key are empty");
        taihe::set_business_error(PARAMETERSERROR, "Parameter error.");
        return ::taihe::array<::taiheChannel::UnifiedDataInner>(dataImpls);
    }

    if (options.intention.has_value()) {
        queryOption.intention = ConvertIntention(options.intention.value());
    }

    if (options.key.has_value()) {
        std::string keyStr(std::string(options.key.value()));
        UnifiedKey key(keyStr);
        std::string intentionStr = options.intention.has_value() ? std::string(options.intention.value()) : "";
        if (!IsValidOptionInfoNonDrag(key, intentionStr)) {
            LOG_ERROR(UDMF_ANI, "Invalid key or intention for DeleteDataSync");
            taihe::set_business_error(PARAMETERSERROR, "Parameter error: DeleteDataSync");
            return ::taihe::array<::taiheChannel::UnifiedDataInner>(dataImpls);
        }
        queryOption.key = keyStr;
    }
    
    std::vector<UnifiedData> unifiedDataSet;
    auto status = UdmfClient::GetInstance().DeleteData(queryOption, unifiedDataSet);
    if (status != E_OK) {
        LOG_ERROR(UDMF_ANI, "DeleteData failed, status: %{public}d", status);
        taihe::set_business_error(PARAMETERSERROR, "Parameter error.");
        return ::taihe::array<::taiheChannel::UnifiedDataInner>(dataImpls);
    }
    for (auto &data : unifiedDataSet) {
        auto dataImpl = taihe::make_holder<OHOS::UDMF::UnifiedDataTaihe, ::taiheChannel::UnifiedDataInner>();
        auto dataImplPtr = reinterpret_cast<OHOS::UDMF::UnifiedDataTaihe*>(dataImpl->GetInner());
        dataImplPtr->value_ = std::make_shared<UnifiedData>(data);
        dataImpls.push_back(dataImpl);
    }
    return ::taihe::array<::taiheChannel::UnifiedDataInner>(dataImpls);
}

void RemoveAppShareOptions(::taiheChannel::Intention intention)
{
    auto temp = ConvertIntention(intention);
    if (temp != OHOS::UDMF::Intention::UD_INTENTION_DRAG) {
        LOG_ERROR(UDMF_ANI, "intention err, status: %{public}d", temp);
        taihe::set_business_error(PARAMETERSERROR, "Parameter error: The intention parameter is invalid!");
        return;
    }
    std::string intentionInner = UD_INTENTION_MAP.at(temp);
    std::transform(intentionInner.begin(), intentionInner.end(), intentionInner.begin(), ::tolower);
    auto status = UdmfClient::GetInstance().RemoveAppShareOption(intentionInner);
    if (status == E_NO_PERMISSION) {
        taihe::set_business_error(NOPERMISSION, "Permission denied!");
    }
    return;
}

void SetAppShareOptions(::taiheChannel::Intention intention, ::taiheChannel::ShareOptions shareOptions)
{
    auto temp = ConvertIntention(intention);
    if (temp != OHOS::UDMF::Intention::UD_INTENTION_DRAG) {
        LOG_ERROR(UDMF_ANI, "intention err, status: %{public}d", temp);
        taihe::set_business_error(PARAMETERSERROR, "Parameter error: The intention parameter is invalid!");
        return;
    }
    auto shareOptionsInner = ConvertShareOptions(shareOptions);
    if (shareOptionsInner == SHARE_OPTIONS_BUTT) {
        LOG_ERROR(UDMF_ANI, "intention err, status: %{public}d", shareOptionsInner);
        taihe::set_business_error(PARAMETERSERROR, "Parameter error: The shareOptions parameter is invalid!");
        return;
    }
    std::string intentionInner = UD_INTENTION_MAP.at(temp);
    std::transform(intentionInner.begin(), intentionInner.end(), intentionInner.begin(), ::tolower);
    auto status = UdmfClient::GetInstance().SetAppShareOption(intentionInner, shareOptionsInner);
    if (status == E_NO_PERMISSION) {
        taihe::set_business_error(NOPERMISSION, "Permission denied!");
    }
    if (status == E_SETTINGS_EXISTED) {
        taihe::set_business_error(ESETTINGSEXISTED,
            "Settings already exist. To reconfigure, remove the existing sharing options.");
    }
    if (status != E_OK) {
        taihe::set_business_error(PARAMETERSERROR, "invalid arguments!");
    }
    return;
}

void ConvertRecordsToEntriesSync(::taiheChannel::weak::UnifiedDataInner data)
{
    auto unifiedDataImpl = reinterpret_cast<OHOS::UDMF::UnifiedDataTaihe*>(data->GetInner());
    auto unifiedData = unifiedDataImpl->value_;
    unifiedData->ConvertRecordsToEntries();
    return;
}
} // namespace UDMF
} // namespace OHOS

TH_EXPORT_CPP_API_InsertDataSync(OHOS::UDMF::InsertDataSync);
TH_EXPORT_CPP_API_QueryDataSync(OHOS::UDMF::QueryDataSync);
TH_EXPORT_CPP_API_UpdateDataSync(OHOS::UDMF::UpdateDataSync);
TH_EXPORT_CPP_API_DeleteDataSync(OHOS::UDMF::DeleteDataSync);
TH_EXPORT_CPP_API_RemoveAppShareOptions(OHOS::UDMF::RemoveAppShareOptions);
TH_EXPORT_CPP_API_SetAppShareOptions(OHOS::UDMF::SetAppShareOptions);
TH_EXPORT_CPP_API_ConvertRecordsToEntriesSync(OHOS::UDMF::ConvertRecordsToEntriesSync);
