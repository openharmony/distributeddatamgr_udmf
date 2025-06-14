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

#include "defined_pixelmap_taihe.h"
#include "taihe_common_utils.h"

SystemDefinedPixelMapInnerImpl::SystemDefinedPixelMapInnerImpl()
{
    this->value_ = std::make_shared<taiheUdmf::SystemDefinedPixelMap>();
}

::taihe::string SystemDefinedPixelMapInnerImpl::GetType()
{
    return ::taihe::string(taiheUdmf::UtdUtils::GetUtdIdFromUtdEnum(this->value_->GetType()));
}

::ohos::data::unifiedDataChannel::ValueType SystemDefinedPixelMapInnerImpl::GetValue()
{
    return taiheUdmf::ConvertValueType(this->value_->GetValue());
}

::taihe::optional<::taihe::map<::taihe::string, ::ohos::data::unifiedDataChannel::DetailsValue>> SystemDefinedPixelMapInnerImpl::GetDetails()
{
    return ::taihe::optional<::taihe::map<::taihe::string, ::ohos::data::unifiedDataChannel::DetailsValue>>::make(
        taiheUdmf::ConvertUDDetailsToUnion(this->value_->GetDetails()));
}

void SystemDefinedPixelMapInnerImpl::SetDetails(::taihe::map_view<::taihe::string, ::ohos::data::unifiedDataChannel::DetailsValue> details)
{
    taiheUdmf::UDDetails udmfDetails = taiheUdmf::ConvertUDDetailsToUnion(details);
    this->value_->SetDetails(udmfDetails);
}

::taihe::optional<::taihe::array<uint8_t>> SystemDefinedPixelMapInnerImpl::GetRawData()
{
    auto rawData = this->value_->GetRawData();
    return ::taihe::optional<::taihe::array<uint8_t>>::make(
        ::taihe::array<uint8_t>(rawData));
}

void SystemDefinedPixelMapInnerImpl::SetRawData(::taihe::array_view<uint8_t> rawData)
{
    if (rawData.size() == 0) {
        return;
    }
    std::vector<uint8_t> rawDataVec(rawData.begin(), rawData.end());
    this->value_->SetRawData(rawDataVec);
}

int64_t SystemDefinedPixelMapInnerImpl::GetInner()
{
    return reinterpret_cast<int64_t>(this);
}

::ohos::data::unifiedDataChannel::SystemDefinedPixelMapInner CreateSystemDefinedPixelMap()
{
    return taihe::make_holder<SystemDefinedPixelMapInnerImpl, ::ohos::data::unifiedDataChannel::SystemDefinedPixelMapInner>();
}


TH_EXPORT_CPP_API_CreateSystemDefinedPixelMap(CreateSystemDefinedPixelMap);
