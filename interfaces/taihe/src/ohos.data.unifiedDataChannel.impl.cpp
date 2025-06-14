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
#define LOG_TAG "UNIFIED_CHANNEL_TAIHE"

#include "ohos.data.unifiedDataChannel.proj.hpp"
#include "ohos.data.unifiedDataChannel.impl.hpp"
#include "stdexcept"
#include "taihe_common_utils.h"
#include "taihe/runtime.hpp"
#include "udmf_client.h"
#include "unified_data.h"
#include "unified_data_taihe.h"
#include "unified_record.h"
#include "logger.h"
#include "plain_text.h"

static inline OHOS::HiviewDFX::HiLogLabel LogLabel()
{
    return { LOG_CORE, 0xD001656, "UDMF" };
}

namespace {
namespace taiheUdmf = OHOS::UDMF;
static constexpr int PARAMETERSERROR = 401;

::ohos::data::unifiedDataChannel::Summary CreateSummary()
{
    ::taihe::map<::taihe::string, double> summary;
    return {summary, 0};
}

::taihe::string InsertDataSync(::ohos::data::unifiedDataChannel::Options const& options,
    ::ohos::data::unifiedDataChannel::weak::UnifiedDataInner data)
{
    LOG_INFO(UDMF_ANI, "wjc InsertDataSync start");
    taiheUdmf::CustomOption customOption;
    if (!options.intention.has_value()) {
        LOG_INFO(UDMF_ANI, "wjc InsertDataSync 11");
        taihe::set_business_error(PARAMETERSERROR, "Parameter error.");
        return "";
    }
    
    customOption.intention = taiheUdmf::ConvertIntention(options.intention.value());
    LOG_INFO(UDMF_ANI, "wjc InsertDataSync 22");
    auto unifiedDataImpl = reinterpret_cast<UnifiedDataImpl*>(data->GetInner());
    auto unifiedData = unifiedDataImpl->value_;
    LOG_INFO(UDMF_ANI, "wjc InsertDataSync 33");
    std::string key;
    auto status = taiheUdmf::UdmfClient::GetInstance().SetData(customOption, *unifiedData, key);
    if (status != taiheUdmf::E_OK) {
        LOG_INFO(UDMF_ANI, "wjc InsertDataSync 44");
        taihe::set_business_error(PARAMETERSERROR, "Parameter error.");
        return "";
    }
    LOG_INFO(UDMF_ANI, "wjc InsertDataSync 55 key=%{public}s", key.c_str());
    return ::taihe::string(key);
}

::taihe::array<::ohos::data::unifiedDataChannel::UnifiedDataInner> QueryDataSync(
    ::ohos::data::unifiedDataChannel::Options const& options)
{
    LOG_INFO(UDMF_ANI, "wjc QueryDataSync start key=%{public}s", options.key.value().c_str());
    taiheUdmf::QueryOption queryOption;
    std::vector<::ohos::data::unifiedDataChannel::UnifiedDataInner> dataImpls;

    if (!options.intention.has_value() && !options.key.has_value()) {
        LOG_INFO(UDMF_ANI, "wjc QueryDataSync 11");
        taihe::set_business_error(PARAMETERSERROR, "Parameter error.");
        return ::taihe::array<::ohos::data::unifiedDataChannel::UnifiedDataInner>(dataImpls);
    }
    LOG_INFO(UDMF_ANI, "wjc QueryDataSync 22");
    queryOption.intention = taiheUdmf::ConvertIntention(options.intention.value());
    queryOption.key = options.key.value();
    std::vector<taiheUdmf::UnifiedData> unifiedDataSet;
    auto status = taiheUdmf::UdmfClient::GetInstance().GetBatchData(queryOption, unifiedDataSet);
    if (status != taiheUdmf::E_OK) {
        taihe::set_business_error(PARAMETERSERROR, "Parameter error.");
        return ::taihe::array<::ohos::data::unifiedDataChannel::UnifiedDataInner>(dataImpls);
    }
    LOG_INFO(UDMF_ANI, "wjc QueryDataSync 33");
    for (auto &data : unifiedDataSet) {
        LOG_INFO(UDMF_ANI, "wjc QueryDataSync 44");
        auto dataImpl = taihe::make_holder<UnifiedDataImpl, ::ohos::data::unifiedDataChannel::UnifiedDataInner>();
        auto dataImplPtr = reinterpret_cast<UnifiedDataImpl*>(dataImpl->GetInner());
        dataImplPtr->value_ = std::make_shared<taiheUdmf::UnifiedData>(data);
        dataImpls.push_back(dataImpl);
    }
    LOG_INFO(UDMF_ANI, "wjc QueryDataSync 55");
    return ::taihe::array<::ohos::data::unifiedDataChannel::UnifiedDataInner>(dataImpls);
}
}  // namespace

TH_EXPORT_CPP_API_CreateSummary(CreateSummary);
TH_EXPORT_CPP_API_InsertDataSync(InsertDataSync);
TH_EXPORT_CPP_API_QueryDataSync(QueryDataSync);
// NOLINTEND
