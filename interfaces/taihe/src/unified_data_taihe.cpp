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
#include "file_taihe.h"

UnifiedDataImpl::UnifiedDataImpl()
{
    this->value_ = std::make_shared<taiheUdmf::UnifiedData>();
}

void UnifiedDataImpl::AddRecord(::ohos::data::unifiedDataChannel::AllRecords const& unifiedRecord)
{
    switch (unifiedRecord.get_tag()) {
        case ::ohos::data::unifiedDataChannel::AllRecords::tag_t::unifiedRecord: {
            auto unifiedRecordImpl = reinterpret_cast<UnifiedRecordImpl*>(unifiedRecord.get_unifiedRecord_ref()->GetInner());
            this->value_->AddRecord(unifiedRecordImpl->value_);
            break;
        }
        case ::ohos::data::unifiedDataChannel::AllRecords::tag_t::file: {
            auto fileImpl = reinterpret_cast<FileImpl*>(unifiedRecord.get_file_ref()->GetInner());
            this->value_->AddRecord(fileImpl->value_);
            break;
        }
    }
}

::taihe::array<::ohos::data::unifiedDataChannel::AllRecords> UnifiedDataImpl::GetRecords()
{
    auto records = this->value_->GetRecords();
    std::vector<::ohos::data::unifiedDataChannel::AllRecords> recordsImpls;
    for (auto &record : records) {
        recordsImpls.push_back(GetRecord(record));
    }
    return ::taihe::array<::ohos::data::unifiedDataChannel::AllRecords>(recordsImpls);
}

::ohos::data::unifiedDataChannel::AllRecords UnifiedDataImpl::GetRecord(std::shared_ptr<taiheUdmf::UnifiedRecord> in)
{
    switch (in->GetType()) {

        case taiheUdmf::FILE: {
            auto fileImpl = taihe::make_holder<FileImpl, ::ohos::data::unifiedDataChannel::File>();
            auto fileImplPtr = reinterpret_cast<FileImpl*>(fileImpl->GetInner());
            fileImplPtr->value_ = std::static_pointer_cast<taiheUdmf::File>(in);
            return ::ohos::data::unifiedDataChannel::AllRecords::make_file(fileImpl);
        }
        default:
            auto recordImpl = taihe::make_holder<UnifiedRecordImpl, ::ohos::data::unifiedDataChannel::UnifiedRecord>();
            auto recordImplPtr = reinterpret_cast<UnifiedRecordImpl*>(recordImpl->GetInner());
            recordImplPtr->value_ = in;
            return ::ohos::data::unifiedDataChannel::AllRecords::make_unifiedRecord(recordImpl);
    }
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
    ::ohos::data::unifiedDataChannel::AllRecords const& unifiedRecord)
{
    auto unifiedData = taihe::make_holder<UnifiedDataImpl, ::ohos::data::unifiedDataChannel::UnifiedData>();
    auto unifiedDataImpl = reinterpret_cast<UnifiedDataImpl*>(unifiedData->GetInner());
    switch (unifiedRecord.get_tag()) {
        case ::ohos::data::unifiedDataChannel::AllRecords::tag_t::unifiedRecord: {
            auto unifiedRecordImpl = reinterpret_cast<UnifiedRecordImpl*>(unifiedRecord.get_unifiedRecord_ref()->GetInner());
            unifiedDataImpl->value_->AddRecord(unifiedRecordImpl->value_);
            break;
        }
        case ::ohos::data::unifiedDataChannel::AllRecords::tag_t::file: {
            auto fileImpl = reinterpret_cast<FileImpl*>(unifiedRecord.get_file_ref()->GetInner());
            unifiedDataImpl->value_->AddRecord(fileImpl->value_);
            break;
        }
    }
    return unifiedData;
}

TH_EXPORT_CPP_API_CreateUnifiedData(CreateUnifiedData);
TH_EXPORT_CPP_API_CreateUnifiedDataWithParams(CreateUnifiedDataWithParams);