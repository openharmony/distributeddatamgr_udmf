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

#define LOG_TAG "UDMF_DEFINED_PIXELMAP"

#include "defined_pixelmap_taihe.h"
#include "interop_js/arkts_esvalue.h"
#include "logger.h"
#include "system_defined_pixelmap_napi.h"
#include "taihe_common_utils.h"
#include "taihe/runtime.hpp"

namespace OHOS {
namespace UDMF {
SystemDefinedPixelMapTaihe::SystemDefinedPixelMapTaihe()
{
    this->value_ = std::make_shared<SystemDefinedPixelMap>();
}

SystemDefinedPixelMapTaihe::SystemDefinedPixelMapTaihe(std::shared_ptr<SystemDefinedPixelMap> value)
{
    this->value_ = value;
}

::taihe::string SystemDefinedPixelMapTaihe::GetType()
{
    return ::taihe::string(UtdUtils::GetUtdIdFromUtdEnum(this->value_->GetType()));
}

::taiheChannel::ValueType SystemDefinedPixelMapTaihe::GetValue()
{
    return ConvertValueType(this->value_->GetValue());
}

::taihe::optional<::taihe::map<::taihe::string, ::taiheChannel::DetailsValue>> SystemDefinedPixelMapTaihe::GetDetails()
{
    return ::taihe::optional<::taihe::map<::taihe::string, ::taiheChannel::DetailsValue>>::make(
        ConvertUDDetailsToUnion(this->value_->GetDetails()));
}

void SystemDefinedPixelMapTaihe::SetDetails(
    const ::taihe::map_view<::taihe::string, ::taiheChannel::DetailsValue> &details)
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

void SystemDefinedPixelMapTaihe::SetRawData(const ::taihe::array_view<uint8_t> &rawData)
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

::taiheChannel::SystemDefinedPixelMapInner CreateSystemDefinedPixelMap()
{
    return taihe::make_holder<SystemDefinedPixelMapTaihe, ::taiheChannel::SystemDefinedPixelMapInner>();
}

::taiheChannel::SystemDefinedPixelMapInner SystemDefinedPixelMapTransferStaticImpl(uintptr_t input)
{
    ani_object esValue = reinterpret_cast<ani_object>(input);
    void *nativePtr = nullptr;
    if (!arkts_esvalue_unwrap(taihe::get_env(), esValue, &nativePtr) || nativePtr == nullptr) {
        LOG_ERROR(UDMF_ANI, "unwrap esvalue failed");
        return taihe::make_holder<SystemDefinedPixelMapTaihe, ::taiheChannel::SystemDefinedPixelMapInner>();
    }
    auto pixelMapNapi = reinterpret_cast<OHOS::UDMF::SystemDefinedPixelMapNapi *>(nativePtr);
    if (pixelMapNapi == nullptr || pixelMapNapi->value_ == nullptr) {
        LOG_ERROR(UDMF_ANI, "cast SystemDefinedPixelMap failed");
        return taihe::make_holder<SystemDefinedPixelMapTaihe, ::taiheChannel::SystemDefinedPixelMapInner>();
    }
    return taihe::make_holder<SystemDefinedPixelMapTaihe,
        ::taiheChannel::SystemDefinedPixelMapInner>(pixelMapNapi->value_);
}

uintptr_t SystemDefinedPixelMapTransferDynamicImpl(::taiheChannel::weak::SystemDefinedPixelMapInner input)
{
    return 0;
}
} // namespace UDMF
} // namespace OHOS

TH_EXPORT_CPP_API_CreateSystemDefinedPixelMap(OHOS::UDMF::CreateSystemDefinedPixelMap);
TH_EXPORT_CPP_API_SystemDefinedPixelMapTransferStaticImpl(OHOS::UDMF::SystemDefinedPixelMapTransferStaticImpl);
TH_EXPORT_CPP_API_SystemDefinedPixelMapTransferDynamicImpl(OHOS::UDMF::SystemDefinedPixelMapTransferDynamicImpl);