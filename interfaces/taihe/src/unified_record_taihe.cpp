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

#define LOG_TAG "UNIFIED_RECORD_TAIHE"

#include "unified_record_taihe.h"
#include "taihe/runtime.hpp"
#include "logger.h"
#include "ani_common_want.h"
#include "pixel_map_taihe_ani.h"
#include "taihe_common_utils.h"

UnifiedRecordInnerImpl::UnifiedRecordInnerImpl()
{
    this->value_ = std::make_shared<taiheUdmf::UnifiedRecord>();
}

UnifiedRecordInnerImpl::UnifiedRecordInnerImpl(::taihe::string_view type,
    ::ohos::data::unifiedDataChannel::ValueType const& value)
{
    taiheUdmf::ValueType valueType = taiheUdmf::ConvertValueType(::taihe::get_env(), type, value);
    taiheUdmf::UDType utdType = taiheUdmf::APPLICATION_DEFINED_RECORD;
    if (taiheUdmf::UtdUtils::IsValidUtdId(std::string(type))) {
        utdType = static_cast<taiheUdmf::UDType>(taiheUdmf::UtdUtils::GetUtdEnumFromUtdId(std::string(type)));
    }
    this->value_ = std::make_shared<taiheUdmf::UnifiedRecord>(utdType, valueType);
}

::taihe::string UnifiedRecordInnerImpl::GetType()
{
    return ::taihe::string(taiheUdmf::UtdUtils::GetUtdIdFromUtdEnum(this->value_->GetType()));
}

::ohos::data::unifiedDataChannel::ValueType UnifiedRecordInnerImpl::GetValue()
{
    return taiheUdmf::ConvertValueType(this->value_->GetValue());
}

int64_t UnifiedRecordInnerImpl::GetInner()
{
    return reinterpret_cast<int64_t>(this);
}

::ohos::data::unifiedDataChannel::UnifiedRecordInner CreateUnifiedRecord()
{
    return taihe::make_holder<UnifiedRecordInnerImpl, ::ohos::data::unifiedDataChannel::UnifiedRecordInner>();
}

::ohos::data::unifiedDataChannel::UnifiedRecordInner CreateUnifiedRecordWithParams(::taihe::string_view type,
    ::ohos::data::unifiedDataChannel::ValueType const& value)
{
    return taihe::make_holder<UnifiedRecordInnerImpl, ::ohos::data::unifiedDataChannel::UnifiedRecordInner>(type, value);
}

TH_EXPORT_CPP_API_CreateUnifiedRecord(CreateUnifiedRecord);
TH_EXPORT_CPP_API_CreateUnifiedRecordWithParams(CreateUnifiedRecordWithParams);