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

#include "unified_data_taihe.h"
#include "unified_record_taihe.h"

UnifiedDataImpl::UnifiedDataImpl()
{
    this->value_ = std::make_shared<taiheUdmf::UnifiedData>();
}

void UnifiedDataImpl::AddRecord(::ohos::data::unifiedDataChannel::weak::UnifiedRecord unifiedRecord)
{
    auto unifiedRecordImpl = reinterpret_cast<UnifiedRecordImpl*>(unifiedRecord->GetInner());
    this->value_->AddRecord(unifiedRecordImpl->value_);
}

::taihe::array<::ohos::data::unifiedDataChannel::UnifiedRecord> UnifiedDataImpl::GetRecords()
{
    auto records = this->value_->GetRecords();
    std::vector<::ohos::data::unifiedDataChannel::UnifiedRecord> recordsImpls;
    for (auto &record : records) {
        auto recordImpl = taihe::make_holder<UnifiedRecordImpl, ::ohos::data::unifiedDataChannel::UnifiedRecord>();
        auto recordImplPtr = reinterpret_cast<UnifiedRecordImpl*>(recordImpl->GetInner());
        recordImplPtr->value_ = record;
        recordsImpls.push_back(recordImpl);
    }
    return ::taihe::array<::ohos::data::unifiedDataChannel::UnifiedRecord>(recordsImpls);
}

int64_t UnifiedDataImpl::GetInner()
{
    return reinterpret_cast<int64_t>(this);
}

::ohos::data::unifiedDataChannel::UnifiedData CreateUnifiedData()
{
    return taihe::make_holder<UnifiedDataImpl, ::ohos::data::unifiedDataChannel::UnifiedData>();
}

::ohos::data::unifiedDataChannel::UnifiedData CreateUnifiedDataWithParams(
    ::ohos::data::unifiedDataChannel::weak::UnifiedRecord unifiedRecord)
{
    auto unifiedData = taihe::make_holder<UnifiedDataImpl, ::ohos::data::unifiedDataChannel::UnifiedData>();
    auto unifiedDataImpl = reinterpret_cast<UnifiedDataImpl*>(unifiedData->GetInner());
    auto unifiedRecordImpl = reinterpret_cast<UnifiedRecordImpl*>(unifiedRecord->GetInner());
    unifiedDataImpl->value_->AddRecord(unifiedRecordImpl->value_);
    return unifiedData;
}

TH_EXPORT_CPP_API_CreateUnifiedData(CreateUnifiedData);
TH_EXPORT_CPP_API_CreateUnifiedDataWithParams(CreateUnifiedDataWithParams);