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

#include "ohos.data.unifiedDataChannel.proj.hpp"
#include "ohos.data.unifiedDataChannel.impl.hpp"
#include "stdexcept"
#include "taihe_common_utils.h"
#include "taihe/runtime.hpp"
#include "udmf_client.h"
#include "unified_data.h"
#include "unified_data_taihe.h"
#include "unified_record.h"

namespace {
namespace taiheUdmf = OHOS::UDMF;
static constexpr int PARAMETERSERROR = 401;

::ohos::data::unifiedDataChannel::Summary CreateSummary()
{
    ::taihe::map<::taihe::string, double> summary;
    return {summary, 0};
}

void InsertDataSync(::ohos::data::unifiedDataChannel::Options const& options,
    ::ohos::data::unifiedDataChannel::weak::UnifiedDataInner data)
{
    taiheUdmf::CustomOption customOption;
    if (!options.intention.has_value()) {
        taihe::set_business_error(PARAMETERSERROR, "Parameter error.");
        return;
    }
    customOption.intention = taiheUdmf::ConvertIntention(options.intention.value());
    auto unifiedDataImpl = reinterpret_cast<UnifiedDataImpl*>(data->GetInner());
    auto unifiedData = unifiedDataImpl->value_;
    std::string key;
    auto status = taiheUdmf::UdmfClient::GetInstance().SetData(customOption, *unifiedData, key);
    if (status != taiheUdmf::E_OK) {
        taihe::set_business_error(PARAMETERSERROR, "Parameter error.");
        return;
    }
}

::taihe::array<::ohos::data::unifiedDataChannel::UnifiedDataInner> QueryDataSync(
    ::ohos::data::unifiedDataChannel::Options const& options)
{
    taiheUdmf::QueryOption queryOption;
    std::vector<::ohos::data::unifiedDataChannel::UnifiedDataInner> dataImpls;
    if (!options.intention.has_value() && !options.key.has_value()) {
        taihe::set_business_error(PARAMETERSERROR, "Parameter error.");
        return ::taihe::array<::ohos::data::unifiedDataChannel::UnifiedDataInner>(dataImpls);
    }
    queryOption.intention = taiheUdmf::ConvertIntention(options.intention.value());
    queryOption.key = options.key.value();
    std::vector<taiheUdmf::UnifiedData> unifiedDataSet;
    auto status = taiheUdmf::UdmfClient::GetInstance().GetBatchData(queryOption, unifiedDataSet);
    if (status != taiheUdmf::E_OK) {
        taihe::set_business_error(PARAMETERSERROR, "Parameter error.");
        return ::taihe::array<::ohos::data::unifiedDataChannel::UnifiedDataInner>(dataImpls);
    }
    for (auto &data : unifiedDataSet) {
        auto dataImpl = taihe::make_holder<UnifiedDataImpl, ::ohos::data::unifiedDataChannel::UnifiedDataInner>();
        auto dataImplPtr = reinterpret_cast<UnifiedDataImpl*>(dataImpl->GetInner());
        dataImplPtr->value_ = std::make_shared<taiheUdmf::UnifiedData>(data);
        dataImpls.push_back(dataImpl);
    }
    return ::taihe::array<::ohos::data::unifiedDataChannel::UnifiedDataInner>(dataImpls);
}
}  // namespace

TH_EXPORT_CPP_API_CreateSummary(CreateSummary);
TH_EXPORT_CPP_API_InsertDataSync(InsertDataSync);
TH_EXPORT_CPP_API_QueryDataSync(QueryDataSync);
// NOLINTEND
