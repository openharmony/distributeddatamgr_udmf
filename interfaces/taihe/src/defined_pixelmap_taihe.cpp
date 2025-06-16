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

namespace OHOS {
namespace UDMF {
SystemDefinedPixelMapTaihe::SystemDefinedPixelMapTaihe()
{
    this->value_ = std::make_shared<SystemDefinedPixelMap>();
}

::taihe::string SystemDefinedPixelMapTaihe::GetType()
{
    return ::taihe::string(UtdUtils::GetUtdIdFromUtdEnum(this->value_->GetType()));
}

::taiheChannel::ValueType SystemDefinedPixelMapTaihe::GetValue()
{
    return ConvertValueType(this->value_->GetValue());
}

::taihe::optional<::taihe::map<::taihe::string, ::taiheChannel::DetailsValue>>
    SystemDefinedPixelMapTaihe::GetDetails()
{
    return ::taihe::optional<::taihe::map<::taihe::string, ::taiheChannel::DetailsValue>>::make(
        ConvertUDDetailsToUnion(this->value_->GetDetails()));
}

void SystemDefinedPixelMapTaihe::SetDetails(
    ::taihe::map_view<::taihe::string, ::taiheChannel::DetailsValue> details)
{
    UDDetails udmfDetails = ConvertUDDetailsToUnion(details);
    this->value_->SetDetails(udmfDetails);
}

::taihe::optional<::taihe::array<uint8_t>> SystemDefinedPixelMapTaihe::GetRawData()
{
    auto rawData = this->value_->GetRawData();
    return ::taihe::optional<::taihe::array<uint8_t>>::make(
        ::taihe::array<uint8_t>(rawData));
}

void SystemDefinedPixelMapTaihe::SetRawData(::taihe::array_view<uint8_t> rawData)
{
    if (rawData.size() == 0) {
        return;
    }
    std::vector<uint8_t> rawDataVec(rawData.begin(), rawData.end());
    this->value_->SetRawData(rawDataVec);
}

int64_t SystemDefinedPixelMapTaihe::GetInner()
{
    return reinterpret_cast<int64_t>(this);
}
} // namespace UDMF
} // namespace OHOS

::taiheChannel::SystemDefinedPixelMapInner CreateSystemDefinedPixelMap()
{
    return taihe::make_holder<OHOS::UDMF::SystemDefinedPixelMapTaihe,
        ::taiheChannel::SystemDefinedPixelMapInner>();
}

TH_EXPORT_CPP_API_CreateSystemDefinedPixelMap(CreateSystemDefinedPixelMap);
