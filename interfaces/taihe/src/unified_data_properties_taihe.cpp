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

#define LOG_TAG "UNIFIED_DATA_PROPERTIES_TAIHE"

#include "unified_data_properties_taihe.h"
#include "taihe/runtime.hpp"
#include "long_wrapper.h"
#include "ani_common_utils.h"
#include "ani_common_want.h"
#include "logger.h"

namespace taiheChannel = ohos::data::unifiedDataChannel;
namespace OHOS {
namespace UDMF {
UnifiedDataPropertiesTaihe::UnifiedDataPropertiesTaihe()
{
    this->value_ = std::make_shared<UnifiedDataProperties>();
}

UnifiedDataPropertiesTaihe::UnifiedDataPropertiesTaihe(std::shared_ptr<UnifiedDataProperties> value,
    ani_fn_object fn)
{
    this->value_ = value;
    if (!fn) {
        this->delayData_ = fn;
    }
}

::taihe::string UnifiedDataPropertiesTaihe::GetTag()
{
    if (!this->value_) {
        LOG_ERROR(UDMF_ANI, "Inner value is null.");
        return ::taihe::string("");
    }
    return ::taihe::string(this->value_->tag);
}

int64_t UnifiedDataPropertiesTaihe::GetInner()
{
    return reinterpret_cast<int64_t>(this);
}

void UnifiedDataPropertiesTaihe::SetTag(::taihe::string tag)
{
    if (!this->value_) {
        LOG_ERROR(UDMF_ANI, "Inner value is null.");
        return;
    }
    this->value_->tag = std::string(tag);
}


void UnifiedDataPropertiesTaihe::SetExtras(::taihe::map<::taihe::string, uintptr_t> extras)
{
    if (!this->value_) {
        LOG_ERROR(UDMF_ANI, "Inner value is null.");
        return;
    }
    for (const auto &extra : extras) {
        this->value_->extras.SetParam(std::string(extra.first),
            OHOS::AAFwk::Long::Box(extra.second));
    }
}

::taihe::map<::taihe::string, uintptr_t> UnifiedDataPropertiesTaihe::GetExtras()
{
    taihe::map<taihe::string, uintptr_t> extras;
    if (!this->value_) {
        LOG_ERROR(UDMF_ANI, "Inner value is null.");
        return extras;
    }
    const std::map<std::string, OHOS::sptr<OHOS::AAFwk::IInterface>> &mapExtras
        = this->value_->extras.GetParams();
    for (const auto &itMapExtras : mapExtras) {
        OHOS::AAFwk::ILong *extra = OHOS::AAFwk::ILong::Query(itMapExtras.second);
        if (extra != nullptr) {
            extras.emplace(taihe::string(itMapExtras.first), uintptr_t(OHOS::AAFwk::Long::Unbox(extra)));
        }
    }
    return extras;
}

uintptr_t UnifiedDataPropertiesTaihe::GetTimestamp()
{
    ani_env *env = taihe::get_env();
    ani_object aniDate {};
    if (env == nullptr || !this->value_) {
        LOG_ERROR(UDMF_ANI, "get_env or value is null");
        return reinterpret_cast<uintptr_t>(nullptr);
    }
    if (SetTimestamp(env, static_cast<double>(this->value_->timestamp), aniDate) != ANI_OK) {
        LOG_ERROR(UDMF_ANI, "SetTimestamp failed");
        return reinterpret_cast<uintptr_t>(nullptr);
    }
    return reinterpret_cast<uintptr_t>(aniDate);
}

void UnifiedDataPropertiesTaihe::SetShareOptions(::taiheChannel::ShareOptions shareOptions)
{
    if (!this->value_) {
        LOG_ERROR(UDMF_ANI, "Inner value is null.");
        return;
    }
    this->value_->shareOptions = ConvertShareOptions(shareOptions);
}

::taiheChannel::ShareOptions UnifiedDataPropertiesTaihe::GetShareOptions()
{
    if (!this->value_) {
        LOG_ERROR(UDMF_ANI, "Inner value is null.");
        return ConvertShareOptions(OHOS::UDMF::ShareOptions::IN_APP);
    }
    return ConvertShareOptions(this->value_->shareOptions);
}

uintptr_t UnifiedDataPropertiesTaihe::GetDelayData()
{
    return reinterpret_cast<uintptr_t>(this->delayData_);
}

void UnifiedDataPropertiesTaihe::SetDelayData(uintptr_t setDelayData)
{
    this->delayData_ = reinterpret_cast<ani_fn_object>(setDelayData);
}
} // namespace UDMF
} // namespace OHOS

::taiheChannel::UnifiedDataProperties CreateUnifiedDataProperties()
{
    return taihe::make_holder<OHOS::UDMF::UnifiedDataPropertiesTaihe, ::taiheChannel::UnifiedDataProperties>();
}

TH_EXPORT_CPP_API_CreateUnifiedDataProperties(CreateUnifiedDataProperties);