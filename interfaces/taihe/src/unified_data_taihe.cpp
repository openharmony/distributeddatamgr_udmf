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
#define LOG_TAG "UNIFIED_DATA_TAIHE"
#include "unified_data_taihe.h"
#include "unified_record_taihe.h"
#include "file_taihe.h"
#include "logger.h"

static inline OHOS::HiviewDFX::HiLogLabel LogLabel()
{
    return { LOG_CORE, 0xD001656, "UDMF" };
}


UnifiedDataImpl::UnifiedDataImpl()
{
    this->value_ = std::make_shared<taiheUdmf::UnifiedData>();
}

void UnifiedDataImpl::AddRecord1(::ohos::data::unifiedDataChannel::AllRecords const& unifiedRecord)
{
    switch (unifiedRecord.get_tag()) {
        case ::ohos::data::unifiedDataChannel::AllRecords::tag_t::unifiedRecord: {
            auto unifiedRecordInnerImpl = reinterpret_cast<UnifiedRecordInnerImpl*>(unifiedRecord.get_unifiedRecord_ref()->GetInner());
            this->value_->AddRecord(unifiedRecordInnerImpl->value_);
            LOG_INFO(UDMF_ANI, "wjc add record case base");
            break;
        }
        case ::ohos::data::unifiedDataChannel::AllRecords::tag_t::file: {
            auto fileInnerImpl = reinterpret_cast<FileInnerImpl*>(unifiedRecord.get_file_ref()->GetInner());
            this->value_->AddRecord(fileInnerImpl->value_);
            LOG_INFO(UDMF_ANI, "wjc add record case file");
            break;
        }
    }
}

::taihe::array<::ohos::data::unifiedDataChannel::AllRecords> UnifiedDataImpl::GetRecords1()
{
    auto records = this->value_->GetRecords();
    LOG_INFO(UDMF_ANI, "wjc records size: %{public}zu", records.size());
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
            auto fileInnerImpl = taihe::make_holder<FileInnerImpl, ::ohos::data::unifiedDataChannel::FileInner>();
            auto fileInnerImplPtr = reinterpret_cast<FileInnerImpl*>(fileInnerImpl->GetInner());
            fileInnerImplPtr->value_ = std::static_pointer_cast<taiheUdmf::File>(in);
            LOG_INFO(UDMF_ANI, "wjc record case file");
            return ::ohos::data::unifiedDataChannel::AllRecords::make_file(fileInnerImpl);
        }
        default:
            auto recordImpl = taihe::make_holder<UnifiedRecordInnerImpl, ::ohos::data::unifiedDataChannel::UnifiedRecordInner>();
            auto recordImplPtr = reinterpret_cast<UnifiedRecordInnerImpl*>(recordImpl->GetInner());
            recordImplPtr->value_ = in;
            LOG_INFO(UDMF_ANI, "wjc record case base");
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
            auto unifiedRecordInnerImpl = reinterpret_cast<UnifiedRecordInnerImpl*>(unifiedRecord.get_unifiedRecord_ref()->GetInner());
            unifiedDataImpl->value_->AddRecord(unifiedRecordInnerImpl->value_);
            break;
        }
        case ::ohos::data::unifiedDataChannel::AllRecords::tag_t::file: {
            auto fileInnerImpl = reinterpret_cast<FileInnerImpl*>(unifiedRecord.get_file_ref()->GetInner());
            unifiedDataImpl->value_->AddRecord(fileInnerImpl->value_);
            break;
        }
    }
    return unifiedData;
}

TH_EXPORT_CPP_API_CreateUnifiedData(CreateUnifiedData);
TH_EXPORT_CPP_API_CreateUnifiedDataWithParams(CreateUnifiedDataWithParams);