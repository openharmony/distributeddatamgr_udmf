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
#define LOG_TAG "UDMF_TAIHE_COMMON_UTILS_H"
#include "taihe_common_utils.h"

#include "ani_common_want.h"
#include "pixel_map_taihe_ani.h"
#include "taihe/runtime.hpp"
#include "logger.h"

namespace OHOS {
namespace UDMF {
OHOS::UDMF::Intention ConvertIntention(::ohos::data::unifiedDataChannel::Intention value)
{
    switch (value.get_key()) {
        case ::ohos::data::unifiedDataChannel::Intention::key_t::DATA_HUB:
            return OHOS::UDMF::Intention::UD_INTENTION_DATA_HUB;
        default:
            return OHOS::UDMF::Intention::UD_INTENTION_DRAG;
    }
}

taiheUdmf::ValueType ConvertValueType(ani_env *env, ::taihe::string_view type,
    ::ohos::data::unifiedDataChannel::ValueType const& value)
{
    taiheUdmf::ValueType valueType = nullptr;
    switch (value.get_tag()) {
        case ohos::data::unifiedDataChannel::ValueType::tag_t::number:
            valueType = value.get_number_ref();
            break;
        case ohos::data::unifiedDataChannel::ValueType::tag_t::string:
            valueType = std::string(value.get_string_ref());
            break;
        case ohos::data::unifiedDataChannel::ValueType::tag_t::boolean:
            valueType = value.get_boolean_ref();
            break;
        case ohos::data::unifiedDataChannel::ValueType::tag_t::ArrayBuffer: {
            taihe::array<uint8_t> arrayBuffer = value.get_ArrayBuffer_ref();
            std::vector<uint8_t> valueVec(arrayBuffer.begin(), arrayBuffer.end());
            valueType = valueVec;
            break;
        }
        case ohos::data::unifiedDataChannel::ValueType::tag_t::nullType:
            valueType = std::monostate();
            break;
        case ohos::data::unifiedDataChannel::ValueType::tag_t::undefinedType:
            valueType = nullptr;
            break;
        case ohos::data::unifiedDataChannel::ValueType::tag_t::object: {
            ani_object obj = reinterpret_cast<ani_object>(value.get_object_ref());
            if (type ==  "openharmony.want") {
                OHOS::AAFwk::Want want;
                OHOS::AppExecFwk::UnwrapWant(env, obj, want);
                valueType = std::make_shared<OHOS::AAFwk::Want>(want);
            } else if (type ==  "openharmony.pixel-map") {
                valueType = OHOS::Media::PixelMapTaiheAni::GetNativePixelMap(env, obj);
            } else {
            }
            break;
        }
    }
    return valueType;
}

::ohos::data::unifiedDataChannel::ValueType ConvertValueType(const taiheUdmf::ValueType &value)
{
    if (std::holds_alternative<double>(value)) {
        return ::ohos::data::unifiedDataChannel::ValueType::make_number(std::get<double>(value));
    }
    if (std::holds_alternative<int32_t>(value)) {
        return ::ohos::data::unifiedDataChannel::ValueType::make_number(std::get<int32_t>(value));
    }
    if (std::holds_alternative<int64_t>(value)) {
        return ::ohos::data::unifiedDataChannel::ValueType::make_number(std::get<int64_t>(value));
    }
    if (std::holds_alternative<bool>(value)) {
        return ::ohos::data::unifiedDataChannel::ValueType::make_boolean(std::get<bool>(value));
    }
    if (std::holds_alternative<std::string>(value)) {
        return ::ohos::data::unifiedDataChannel::ValueType::make_string(std::get<std::string>(value));
    }
    if (std::holds_alternative<std::vector<uint8_t>>(value)) {
        std::vector<uint8_t> dataArray = std::get<std::vector<uint8_t>>(value);
        return ::ohos::data::unifiedDataChannel::ValueType::make_ArrayBuffer(taihe::array<uint8_t>(dataArray));
    }
    if (std::holds_alternative<std::shared_ptr<OHOS::AAFwk::Want>>(value)) {
        auto want = std::get<std::shared_ptr<OHOS::AAFwk::Want>>(value);
        ani_object wantObj = OHOS::AppExecFwk::WrapWant(taihe::get_env(), *want);
        uintptr_t wantPtr = reinterpret_cast<uintptr_t>(wantObj);
        return ::ohos::data::unifiedDataChannel::ValueType::make_object(wantPtr);
    }
    if (std::holds_alternative<std::shared_ptr<OHOS::Media::PixelMap>>(value)) {
        auto pixelMap = std::get<std::shared_ptr<OHOS::Media::PixelMap>>(value);
        ani_object pixelMapObj = OHOS::Media::PixelMapTaiheAni::CreateEtsPixelMap(taihe::get_env(), pixelMap);
        uintptr_t pixelMapPtr = reinterpret_cast<uintptr_t>(pixelMapObj);
        if (pixelMapPtr != 0) {
            LOG_INFO(UDMF_ANI, "<PixelMap> is not null");
        }
        return ::ohos::data::unifiedDataChannel::ValueType::make_object(pixelMapPtr);
    }
    if (std::holds_alternative<std::shared_ptr<taiheUdmf::Object>>(value)) {
    }
    if (std::holds_alternative<nullptr_t>(value)) {
        return ::ohos::data::unifiedDataChannel::ValueType::make_undefinedType();
    }
    if (std::holds_alternative<std::monostate>(value)) {
        return ::ohos::data::unifiedDataChannel::ValueType::make_nullType();
    }
    return ::ohos::data::unifiedDataChannel::ValueType::make_nullType();
}

taiheUdmf::UDDetails ConvertUDDetails(::taihe::map_view<::taihe::string, ::taihe::string> details)
{
    taiheUdmf::UDDetails udmfDetails;
    for (auto &item : details) {
        if (item.first.empty()) {
            continue;
        }
        udmfDetails.insert(std::make_pair(std::string(item.first), std::string(item.second)));
    }
    return udmfDetails;
}

::taihe::map_view<::taihe::string, ::taihe::string> ConvertUDDetailsToString(const taiheUdmf::UDDetails &details)
{
    ::taihe::map<::taihe::string, ::taihe::string> taiheDetails;
    for (auto &item : details) {
        if (item.first.empty()) {
            continue;
        }
        if (std::holds_alternative<std::string>(item.second)) {
            taiheDetails.emplace(::taihe::string(item.first), std::get<std::string>(item.second));
        }
    }
    LOG_INFO(UDMF_ANI, "wjc taiheDetails size is %{public}zu", taiheDetails.size());
    return taiheDetails;
}

taiheUdmf::UDDetails ConvertUDDetailsToUnion(
    const ::taihe::map_view<::taihe::string, ::ohos::data::unifiedDataChannel::DetailsValue> &details)
{
    taiheUdmf::UDDetails udmfDetails;
    for (auto &item : details) {
        if (item.first.empty()) {
            continue;
        }
        UDVariant value;
        switch (item.second.get_tag()) {
            case ohos::data::unifiedDataChannel::DetailsValue::tag_t::number:
                value = item.second.get_number_ref();
                break;
            case ohos::data::unifiedDataChannel::DetailsValue::tag_t::string:
                value = std::string(item.second.get_string_ref());
                break;
            case ohos::data::unifiedDataChannel::DetailsValue::tag_t::Uint8Array:
                value = std::vector<uint8_t>(item.second.get_Uint8Array_ref().begin(),
                    item.second.get_Uint8Array_ref().end());
                break;
        }

        udmfDetails.insert(std::make_pair(std::string(item.first), value));
    }
    return udmfDetails;
}

::taihe::map_view<::taihe::string, ::ohos::data::unifiedDataChannel::DetailsValue> ConvertUDDetailsToUnion(
    const taiheUdmf::UDDetails &details)
{
    ::taihe::map<::taihe::string, ::ohos::data::unifiedDataChannel::DetailsValue> taiheDetails;
    for (auto &item : details) {
        if (item.first.empty()) {
            continue;
        }
        if (std::holds_alternative<double>(item.second) || std::holds_alternative<int32_t>(item.second)
            || std::holds_alternative<int64_t>(item.second)) {
            taiheDetails.emplace(::taihe::string(item.first),
                ::ohos::data::unifiedDataChannel::DetailsValue::make_number(std::get<double>(item.second)));
            continue;
        }
        if (std::holds_alternative<std::string>(item.second)) {
            taiheDetails.emplace(::taihe::string(item.first),
                ::ohos::data::unifiedDataChannel::DetailsValue::make_string(std::get<std::string>(item.second)));
            continue;
        }
        if (std::holds_alternative<std::vector<uint8_t>>(item.second)) {
            std::vector<uint8_t> dataArray = std::get<std::vector<uint8_t>>(item.second);
            taiheDetails.emplace(::taihe::string(item.first),
                ::ohos::data::unifiedDataChannel::DetailsValue::make_Uint8Array(taihe::array<uint8_t>(dataArray)));
            continue;
        }
    }
    return taiheDetails;
}
} // namespace UDMF
} // namespace OHOS