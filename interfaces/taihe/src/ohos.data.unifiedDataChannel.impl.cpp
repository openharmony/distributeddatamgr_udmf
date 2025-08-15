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

#include "interop_js/arkts_esvalue.h"
#include "logger.h"
#include "ohos.data.unifiedDataChannel.proj.hpp"
#include "ohos.data.unifiedDataChannel.impl.hpp"
#include "plain_text.h"
#include "stdexcept"
#include "summary_napi.h"
#include "taihe_common_utils.h"
#include "taihe/runtime.hpp"
#include "udmf_client.h"
#include "unified_data.h"
#include "unified_data_taihe.h"
#include "unified_record.h"

namespace OHOS {
namespace UDMF {
namespace taiheChannel = ohos::data::unifiedDataChannel;

::taiheChannel::Summary CreateSummary()
{
    ::taihe::map<::taihe::string, int64_t> summary;
    return {summary, 0};
}

::taihe::string InsertDataSync(::taiheChannel::Options const& options,
    ::taiheChannel::weak::UnifiedDataInner data)
{
    CustomOption customOption;
    if (!options.intention.has_value()) {
        LOG_ERROR(UDMF_ANI, "Intention is empty");
        taihe::set_business_error(PARAMETERSERROR, "Parameter error.");
        return "";
    }
    
    customOption.intention = ConvertIntention(options.intention.value());
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
    queryOption.intention = ConvertIntention(options.intention.value());
    queryOption.key = options.key.value();
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

::taiheChannel::Summary SummaryTransferStaticImpl(uintptr_t input) {
    ani_object esValue = reinterpret_cast<ani_object>(input);
    void *nativePtr = nullptr;
    ::taihe::map<::taihe::string, int64_t> summary;
    if (!arkts_esvalue_unwrap(taihe::get_env(), esValue, &nativePtr) || nativePtr == nullptr) {
        LOG_INFO(UDMF_ANI, "unwrap esvalue failed");
        return {summary, 0};
    }
    auto summaryNapi = reinterpret_cast<OHOS::UDMF::SummaryNapi *>(nativePtr);
    if (summaryNapi == nullptr || summaryNapi->value_ == nullptr) {
        LOG_INFO(UDMF_ANI, "cast summary failed");
        return {summary, 0};
    }
    for (const auto &item : summaryNapi->value_->summary) {
        summary.emplace(::taihe::string(item.first), item.second);
    }
    return {summary, summaryNapi->value_->totalSize};
}

uintptr_t SummaryTransferDynamicImpl(::taiheChannel::Summary const& input) {
    return 0;
}
} // namespace UDMF
} // namespace OHOS

TH_EXPORT_CPP_API_CreateSummary(OHOS::UDMF::CreateSummary);
TH_EXPORT_CPP_API_InsertDataSync(OHOS::UDMF::InsertDataSync);
TH_EXPORT_CPP_API_QueryDataSync(OHOS::UDMF::QueryDataSync);
TH_EXPORT_CPP_API_SummaryTransferStaticImpl(OHOS::UDMF::SummaryTransferStaticImpl);
TH_EXPORT_CPP_API_SummaryTransferDynamicImpl(OHOS::UDMF::SummaryTransferDynamicImpl);