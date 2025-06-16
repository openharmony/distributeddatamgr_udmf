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

#include "summary_taihe.h"

namespace OHOS {
namespace UDMF {
SummaryTaihe::SummaryTaihe()
{
    this->value_ = std::make_shared<Summary>();
}

::taihe::map<::taihe::string, double> SummaryTaihe::GetSummary()
{
    ::taihe::map<::taihe::string, double> summary;
    for (auto &item : this->value_->summary) {
        summary.emplace(::taihe::string(item.first), item.second);
    }
    return summary;
}

double SummaryTaihe::GetTotalSize()
{
    return this->value_->totalSize;
}

int64_t SummaryTaihe::GetInner()
{
    return reinterpret_cast<int64_t>(this);
}
} // namespace UDMF
} // namespace OHOS

::ohos::data::unifiedDataChannel::Summary CreateSummary()
{
    return taihe::make_holder<OHOS::UDMF::SummaryTaihe, taiheChannel::Summary>();
}

TH_EXPORT_CPP_API_CreateSummary(CreateSummary);