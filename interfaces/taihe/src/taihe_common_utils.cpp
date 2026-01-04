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
#define LOG_TAG "UDMF_TAIHE_COMMON_UTILS"

#include "ani_common_utils.h"
#include "ani_common_want.h"
#include "pixel_map_taihe_ani.h"
#include "taihe_common_utils.h"
#include "unified_meta.h"

namespace OHOS {
namespace UDMF {
using ConvertorToTaiheFunc = ::taiheChannel::ValueType (*)(std::shared_ptr<Object>);
static const std::map<std::string, ConvertorToTaiheFunc> CONVERTORS_TO_TAIHE = {
    {"general.plain-text", ConvertPlainText},
    {"general.hyperlink", ConvertHyperlink},
    {"general.html", ConvertHTML},
    {"openharmony.app-item", ConvertOpenHarmonyAppItem},
    {"general.content-form", ConvertContentForm},
    {"openharmony.form", ConvertForm},
    {"general.file-uri", ConvertFileUri},
    {"openharmony.pixel-map", ConvertPixelMap},
};

using thTypeTag = taiheChannel::ValueType::tag_t;
static const std::map<thTypeTag, std::function<ValueType(taiheChannel::ValueType)>> CONVERTORS_TO_OBJ = {
    {thTypeTag::intType, [](taiheChannel::ValueType value) {return value.get_intType_ref();}},
    {thTypeTag::longType, [](taiheChannel::ValueType value) {return value.get_longType_ref();}},
    {thTypeTag::doubleType, [](taiheChannel::ValueType value) {return value.get_doubleType_ref();}},
    {thTypeTag::string, [](taiheChannel::ValueType value) {return std::string(value.get_string_ref());}},
    {thTypeTag::boolean, [](taiheChannel::ValueType value) {return value.get_boolean_ref();}},
    {thTypeTag::ArrayBuffer, [](taiheChannel::ValueType value) {
        taihe::array<uint8_t> arrayBuffer = value.get_ArrayBuffer_ref();
        std::vector<uint8_t> valueVec(arrayBuffer.begin(), arrayBuffer.end());
        return valueVec;
    }},
    {thTypeTag::nullType, [](taiheChannel::ValueType value) {return nullptr;}},
    {thTypeTag::undefinedType, [](taiheChannel::ValueType value) {return std::monostate();}},
    {thTypeTag::form, [](taiheChannel::ValueType value) {
        ::taiheStruct::Form obj = value.get_form_ref();
        return ConvertForm(obj);
    }},
    {thTypeTag::openHarmonyAppItem, [](taiheChannel::ValueType value) {
        ::taiheStruct::OpenHarmonyAppItem obj = value.get_openHarmonyAppItem_ref();
        return ConvertAppItem(obj);
    }},
    {thTypeTag::plainText, [](taiheChannel::ValueType value) {
        ::taiheStruct::PlainText obj = value.get_plainText_ref();
        return ConvertPlainText(obj);
    }},
    {thTypeTag::hyperlink, [](taiheChannel::ValueType value) {
        ::taiheStruct::Hyperlink obj = value.get_hyperlink_ref();
        return ConvertHyperlink(obj);
    }},
    {thTypeTag::html, [](taiheChannel::ValueType value) {
        ::taiheStruct::HTML obj = value.get_html_ref();
        return ConvertHTML(obj);
    }},
    {thTypeTag::contentForm, [](taiheChannel::ValueType value) {
        ::taiheStruct::ContentForm obj = value.get_contentForm_ref();
        return ConvertContentForm(obj);
    }},
    {thTypeTag::fileUri, [](taiheChannel::ValueType value) {
        ::taiheStruct::FileUri obj = value.get_fileUri_ref();
        return ConvertFileUri(obj);
    }},
    {thTypeTag::pixelMap, [](taiheChannel::ValueType value) {
        ::taiheStruct::PixelMap obj = value.get_pixelMap_ref();
        return ConvertPixelMap(obj);
    }},
};

OHOS::UDMF::Intention ConvertIntention(::taiheChannel::Intention value)
{
    switch (value.get_key()) {
        case ::taiheChannel::Intention::key_t::DATA_HUB:
            return OHOS::UDMF::Intention::UD_INTENTION_DATA_HUB;
        case ::taiheChannel::Intention::key_t::DRAG:
            return OHOS::UDMF::Intention::UD_INTENTION_DRAG;
        case ::taiheChannel::Intention::key_t::SYSTEM_SHARE:
            return OHOS::UDMF::Intention::UD_INTENTION_SYSTEM_SHARE;
        case ::taiheChannel::Intention::key_t::PICKER:
            return OHOS::UDMF::Intention::UD_INTENTION_PICKER;
        case ::taiheChannel::Intention::key_t::MENU:
            return OHOS::UDMF::Intention::UD_INTENTION_MENU;
        default:
            return OHOS::UDMF::Intention::UD_INTENTION_BUTT;
    }
}

ValueType ConvertValueType(ani_env *env, const ::taihe::string_view &type,
    ::taiheChannel::ValueType const& value)
{
    auto convertor = CONVERTORS_TO_OBJ.find(value.get_tag());
    if (convertor != CONVERTORS_TO_OBJ.end()) {
        return convertor->second(value);
    }
    auto obj = value.get_recordData_ref();
    if (type == "openharmony.pixel-map") {
        auto pixelMapVal = reinterpret_cast<ani_object>(obj.get_object_ref());
        return OHOS::Media::PixelMapTaiheAni::GetNativePixelMap(env, pixelMapVal);
    } else if (type == "openharmony.want") {
        OHOS::AAFwk::Want want;
        auto wantVal = reinterpret_cast<ani_object>(obj.get_object_ref());
        OHOS::AppExecFwk::UnwrapWant(env, wantVal, want);
        return std::make_shared<OHOS::AAFwk::Want>(want);
    }
    return ConvertRecordData(env, obj, 0);
}

ValueType ConvertRecordData(ani_env *env, ::taiheChannel::RecordData const& value, int depth)
{
    if (depth > MAX_RECURSIVE) {
        LOG_ERROR(UDMF_ANI, "Exceeding the maximum recursion depth");
        return nullptr;
    }
    ValueType valueType = nullptr;
    switch (value.get_tag()) {
        case taiheChannel::RecordData::tag_t::nullType:
            valueType = nullptr;
            break;
        case taiheChannel::RecordData::tag_t::undefinedType:
            valueType = std::monostate();
            break;
        case taiheChannel::RecordData::tag_t::recordMap: {
            auto recordMap = value.get_recordMap_ref();
            auto obj = std::make_shared<Object>();
            for (auto &item : recordMap) {
                std::string attrName(item.first);
                obj->value_[attrName] = ConvertRecordData(env, item.second, depth + 1);
            }
            valueType = std::move(obj);
            break;
        }
        case taiheChannel::RecordData::tag_t::object: {
            auto in = reinterpret_cast<ani_object>(value.get_object_ref());
            ConverObject(env, in, valueType, depth + 1);
            break;
        }
        case taiheChannel::RecordData::tag_t::recordArray: {
            break;
        }
    }
    return valueType;
}

::taiheChannel::ValueType ConvertValueType(const ValueType &value)
{
    if (std::holds_alternative<double>(value)) {
        return ::taiheChannel::ValueType::make_doubleType(std::get<double>(value));
    }
    if (std::holds_alternative<int32_t>(value)) {
        return ::taiheChannel::ValueType::make_intType(std::get<int32_t>(value));
    }
    if (std::holds_alternative<int64_t>(value)) {
        return ::taiheChannel::ValueType::make_longType(std::get<int64_t>(value));
    }
    if (std::holds_alternative<bool>(value)) {
        return ::taiheChannel::ValueType::make_boolean(std::get<bool>(value));
    }
    if (std::holds_alternative<std::string>(value)) {
        return ::taiheChannel::ValueType::make_string(std::get<std::string>(value));
    }
    if (std::holds_alternative<std::vector<uint8_t>>(value)) {
        std::vector<uint8_t> dataArray = std::get<std::vector<uint8_t>>(value);
        return ::taiheChannel::ValueType::make_ArrayBuffer(taihe::array<uint8_t>(dataArray));
    }
    if (std::holds_alternative<std::shared_ptr<OHOS::AAFwk::Want>>(value)) {
        auto want = std::get<std::shared_ptr<OHOS::AAFwk::Want>>(value);
        ani_object wantObj = OHOS::AppExecFwk::WrapWant(taihe::get_env(), *want);
        uintptr_t wantPtr = reinterpret_cast<uintptr_t>(wantObj);
        return ::taiheChannel::ValueType::make_object(wantPtr);
    }
    if (std::holds_alternative<std::shared_ptr<OHOS::Media::PixelMap>>(value)) {
        auto pixelMap = std::get<std::shared_ptr<OHOS::Media::PixelMap>>(value);
        ani_object pixelMapObj = OHOS::Media::PixelMapTaiheAni::CreateEtsPixelMap(taihe::get_env(), pixelMap);
        uintptr_t pixelMapPtr = reinterpret_cast<uintptr_t>(pixelMapObj);
        if (pixelMapPtr != 0) {
            LOG_INFO(UDMF_ANI, "<PixelMap> is not null");
        }
        return ::taiheChannel::ValueType::make_object(pixelMapPtr);
    }
    if (std::holds_alternative<std::shared_ptr<Object>>(value)) {
        auto obj = std::get<std::shared_ptr<Object>>(value);
        std::string type;
        if (obj->GetValue(UNIFORM_DATA_TYPE, type)) {
            auto convertor = CONVERTORS_TO_TAIHE.find(type);
            if (convertor != CONVERTORS_TO_TAIHE.end()) {
                return convertor->second(obj);
            }
        }
        return ::taiheChannel::ValueType::make_recordData(ConvertRecordData(obj, 0));
    }
    if (std::holds_alternative<nullptr_t>(value)) {
        return ::taiheChannel::ValueType::make_undefinedType();
    }
    if (std::holds_alternative<std::monostate>(value)) {
        return ::taiheChannel::ValueType::make_nullType();
    }
    return ::taiheChannel::ValueType::make_nullType();
}

::taiheChannel::RecordData ConvertRecordData(std::shared_ptr<Object> object, int depth)
{
    taihe::map<taihe::string, ::taiheChannel::RecordData> recordMap;
    if (depth > MAX_RECURSIVE) {
        LOG_ERROR(UDMF_ANI, "Exceeding the maximum recursion depth");
        return ::taiheChannel::RecordData::make_recordMap(recordMap);
    }
    for (auto &[key, value] : object->value_) {
        if (std::holds_alternative<double>(value)) {
            auto d = std::get<double>(value);
            ani_object doubleObj {};
            auto status = SetDouble(::taihe::get_env(), d, doubleObj);
            if (status != ANI_OK) {
                continue;
            }
            uintptr_t doulePtr = reinterpret_cast<uintptr_t>(doubleObj);
            recordMap.emplace(key, ::taiheChannel::RecordData::make_object(doulePtr));
            continue;
        } else if (std::holds_alternative<int32_t>(value)) {
            auto i32 = std::get<int32_t>(value);
            ani_object intObj {};
            auto status = SetInt(::taihe::get_env(), i32, intObj);
            if (status != ANI_OK) {
                continue;
            }
            uintptr_t intPtr = reinterpret_cast<uintptr_t>(intObj);
            recordMap.emplace(key, ::taiheChannel::RecordData::make_object(intPtr));
            continue;
        } else if (std::holds_alternative<int64_t>(value)) {
            auto i64 = std::get<int64_t>(value);
            ani_object longObj {};
            auto status = SetLong(::taihe::get_env(), i64, longObj);
            if (status != ANI_OK) {
                continue;
            }
            uintptr_t longPtr = reinterpret_cast<uintptr_t>(longObj);
            recordMap.emplace(key, ::taiheChannel::RecordData::make_object(longPtr));
            continue;
        } else if (std::holds_alternative<bool>(value)) {
            auto b = std::get<bool>(value);
            ani_object boolObj {};
            auto status = SetBoolean(::taihe::get_env(), b, boolObj);
            if (status != ANI_OK) {
                continue;
            }
            uintptr_t boolPtr = reinterpret_cast<uintptr_t>(boolObj);
            recordMap.emplace(key, ::taiheChannel::RecordData::make_object(boolPtr));
            continue;
        } else if (std::holds_alternative<std::string>(value)) {
            auto s = std::get<std::string>(value);
            ani_string strObj;
            auto env = ::taihe::get_env();
            if (env->String_NewUTF8(s.c_str(), s.size(), &strObj) != ANI_OK) {
                LOG_INFO(UDMF_ANI, "String_NewUTF8 failed");
            }
            uintptr_t strPtr = reinterpret_cast<uintptr_t>(strObj);
            recordMap.emplace(key, ::taiheChannel::RecordData::make_object(strPtr));
            continue;
        } else if (std::holds_alternative<std::vector<uint8_t>>(value)) {
            std::vector<uint8_t> dataArray = std::get<std::vector<uint8_t>>(value);
            ani_arraybuffer arrayBufferObj {};
            auto status = SetArrayBuffer(taihe::get_env(), dataArray, arrayBufferObj);
            if (status != ANI_OK) {
                continue;
            }
            uintptr_t bufferPtr = reinterpret_cast<uintptr_t>(arrayBufferObj);
            recordMap.emplace(key, ::taiheChannel::RecordData::make_object(bufferPtr));
            continue;
        } else if (std::holds_alternative<std::shared_ptr<OHOS::AAFwk::Want>>(value)) {
            auto want = std::get<std::shared_ptr<OHOS::AAFwk::Want>>(value);
            ani_object wantObj = OHOS::AppExecFwk::WrapWant(taihe::get_env(), *want);
            uintptr_t wantPtr = reinterpret_cast<uintptr_t>(wantObj);
            recordMap.emplace(key, ::taiheChannel::RecordData::make_object(wantPtr));
            continue;
        } else if (std::holds_alternative<std::shared_ptr<OHOS::Media::PixelMap>>(value)) {
            auto pixelMap = std::get<std::shared_ptr<OHOS::Media::PixelMap>>(value);
            ani_object pixelMapObj = OHOS::Media::PixelMapTaiheAni::CreateEtsPixelMap(taihe::get_env(), pixelMap);
            uintptr_t pixelMapPtr = reinterpret_cast<uintptr_t>(pixelMapObj);
            if (pixelMapPtr != 0) {
                LOG_INFO(UDMF_ANI, "<PixelMap> is not null");
            }
            recordMap.emplace(key, ::taiheChannel::RecordData::make_object(pixelMapPtr));
            continue;
        } else if (std::holds_alternative<std::shared_ptr<Object>>(value)) {
            recordMap.emplace(key, ConvertRecordData(std::get<std::shared_ptr<Object>>(value), depth + 1));
            continue;
        } else if (std::holds_alternative<nullptr_t>(value)) {
            recordMap.emplace(key, ::taiheChannel::RecordData::make_nullType());
            continue;
        } else if (std::holds_alternative<std::monostate>(value)) {
            recordMap.emplace(key, ::taiheChannel::RecordData::make_undefinedType());
            continue;
        }
    }
    return ::taiheChannel::RecordData::make_recordMap(recordMap);
}

UDDetails ConvertUDDetails(const ::taihe::map_view<::taihe::string, ::taihe::string> &details)
{
    UDDetails udmfDetails;
    for (auto &item : details) {
        if (item.first.empty()) {
            continue;
        }
        udmfDetails.insert(std::make_pair(std::string(item.first), std::string(item.second)));
    }
    return udmfDetails;
}

::taihe::map<::taihe::string, ::taihe::string> ConvertUDDetailsToString(const UDDetails &details)
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
    LOG_INFO(UDMF_ANI, "taiheDetails size is %{public}zu", taiheDetails.size());
    return taiheDetails;
}

UDDetails ConvertUDDetailsToUnion(
    const ::taihe::map_view<::taihe::string, ::taiheChannel::DetailsValue> &details)
{
    UDDetails udmfDetails;
    for (auto &item : details) {
        if (item.first.empty()) {
            continue;
        }
        UDVariant value;
        switch (item.second.get_tag()) {
            case taiheChannel::DetailsValue::tag_t::intType:
                value = item.second.get_intType_ref();
                break;
            case taiheChannel::DetailsValue::tag_t::longType:
                value = item.second.get_longType_ref();
                break;
            case taiheChannel::DetailsValue::tag_t::doubleType:
                value = item.second.get_doubleType_ref();
                break;
            case taiheChannel::DetailsValue::tag_t::string:
                value = std::string(item.second.get_string_ref());
                break;
            case taiheChannel::DetailsValue::tag_t::Uint8Array:
                value = std::vector<uint8_t>(item.second.get_Uint8Array_ref().begin(),
                    item.second.get_Uint8Array_ref().end());
                break;
        }

        udmfDetails.insert(std::make_pair(std::string(item.first), value));
    }
    return udmfDetails;
}

::taihe::map<::taihe::string, ::taiheChannel::DetailsValue> ConvertUDDetailsToUnion(
    const UDDetails &details)
{
    ::taihe::map<::taihe::string, ::taiheChannel::DetailsValue> taiheDetails;
    for (auto &item : details) {
        if (item.first.empty()) {
            continue;
        }
        if (std::holds_alternative<double>(item.second)) {
            taiheDetails.emplace(::taihe::string(item.first),
                ::taiheChannel::DetailsValue::make_doubleType(std::get<double>(item.second)));
            continue;
        }
        if (std::holds_alternative<int64_t>(item.second)) {
            taiheDetails.emplace(::taihe::string(item.first),
                ::taiheChannel::DetailsValue::make_longType(std::get<int64_t>(item.second)));
            continue;
        }
        if (std::holds_alternative<int32_t>(item.second)) {
            taiheDetails.emplace(::taihe::string(item.first),
                ::taiheChannel::DetailsValue::make_intType(std::get<int32_t>(item.second)));
            continue;
        }
        if (std::holds_alternative<std::string>(item.second)) {
            taiheDetails.emplace(::taihe::string(item.first),
                ::taiheChannel::DetailsValue::make_string(std::get<std::string>(item.second)));
            continue;
        }
        if (std::holds_alternative<std::vector<uint8_t>>(item.second)) {
            std::vector<uint8_t> dataArray = std::get<std::vector<uint8_t>>(item.second);
            taiheDetails.emplace(::taihe::string(item.first),
                ::taiheChannel::DetailsValue::make_Uint8Array(taihe::array<uint8_t>(dataArray)));
            continue;
        }
    }
    return taiheDetails;
}

OHOS::UDMF::ShareOptions ConvertShareOptions(::taiheChannel::ShareOptions value)
{
    switch (value.get_key()) {
        case ::taiheChannel::ShareOptions::key_t::IN_APP:
            return OHOS::UDMF::ShareOptions::IN_APP;
        case ::taiheChannel::ShareOptions::key_t::CROSS_APP:
            return OHOS::UDMF::ShareOptions::CROSS_APP;
        default:
            return OHOS::UDMF::ShareOptions::SHARE_OPTIONS_BUTT;
    }
}

::taiheChannel::ShareOptions ConvertShareOptions(OHOS::UDMF::ShareOptions value)
{
    switch (value) {
        case OHOS::UDMF::ShareOptions::IN_APP:
            return ::taiheChannel::ShareOptions::key_t::IN_APP;
        default:
            return ::taiheChannel::ShareOptions::key_t::CROSS_APP;
    }
}

OHOS::UDMF::Visibility ConvertVisibility(::taiheChannel::Visibility value)
{
    switch (value.get_key()) {
        case ::taiheChannel::Visibility::key_t::ALL:
            return OHOS::UDMF::Visibility::VISIBILITY_ALL;
        case ::taiheChannel::Visibility::key_t::OWN_PROCESS:
            return OHOS::UDMF::Visibility::VISIBILITY_OWN_PROCESS;
        default:
            return OHOS::UDMF::Visibility::VISIBILITY_BUTT;
    }
}

::taihe::map<::taihe::string, ::taiheStruct::DetailsValue> ConvertUDSUDDetailsToUnion(
    const UDDetails &details)
{
    ::taihe::map<::taihe::string, ::taiheStruct::DetailsValue> taiheDetails;
    for (auto &item : details) {
        if (item.first.empty()) {
            continue;
        }
        if (std::holds_alternative<double>(item.second)) {
            taiheDetails.emplace(::taihe::string(item.first),
                ::taiheStruct::DetailsValue::make_doubleType(std::get<double>(item.second)));
            continue;
        }
        if (std::holds_alternative<int64_t>(item.second)) {
            taiheDetails.emplace(::taihe::string(item.first),
                ::taiheStruct::DetailsValue::make_longType(std::get<int64_t>(item.second)));
            continue;
        }
        if (std::holds_alternative<int32_t>(item.second)) {
            taiheDetails.emplace(::taihe::string(item.first),
                ::taiheStruct::DetailsValue::make_intType(std::get<int32_t>(item.second)));
            continue;
        }
        if (std::holds_alternative<std::string>(item.second)) {
            taiheDetails.emplace(::taihe::string(item.first),
                ::taiheStruct::DetailsValue::make_string(std::get<std::string>(item.second)));
            continue;
        }
        if (std::holds_alternative<std::vector<uint8_t>>(item.second)) {
            std::vector<uint8_t> dataArray = std::get<std::vector<uint8_t>>(item.second);
            taiheDetails.emplace(::taihe::string(item.first),
                ::taiheStruct::DetailsValue::make_Uint8Array(taihe::array<uint8_t>(dataArray)));
            continue;
        }
    }
    return taiheDetails;
}

UDDetails ConvertUDSUDDetailsToUnion(
    const ::taihe::map<::taihe::string, ::taiheStruct::DetailsValue> &details)
{
    UDDetails udmfDetails;
    for (auto &item : details) {
        if (item.first.empty()) {
            continue;
        }
        UDVariant value;
        switch (item.second.get_tag()) {
            case taiheStruct::DetailsValue::tag_t::intType:
                value = item.second.get_intType_ref();
                break;
            case taiheStruct::DetailsValue::tag_t::longType:
                value = item.second.get_longType_ref();
                break;
            case taiheStruct::DetailsValue::tag_t::doubleType:
                value = item.second.get_doubleType_ref();
                break;
            case taiheStruct::DetailsValue::tag_t::string:
                value = std::string(item.second.get_string_ref());
                break;
            case taiheStruct::DetailsValue::tag_t::Uint8Array:
                value = std::vector<uint8_t>(item.second.get_Uint8Array_ref().begin(),
                    item.second.get_Uint8Array_ref().end());
                break;
        }
        udmfDetails.insert(std::make_pair(std::string(item.first), value));
    }
    return udmfDetails;
}

::taiheChannel::ValueType ConvertPlainText(std::shared_ptr<Object> udsObj)
{
    std::string uniformDataType;
    udsObj->GetValue(UNIFORM_DATA_TYPE, uniformDataType);
    std::string textContent;
    udsObj->GetValue("textContent", textContent);
    std::string textAbstract;
    ::taihe::optional<::taihe::string> thOpAbstract;
    if (udsObj->GetValue("abstract", textAbstract) || udsObj->GetValue("textAbstract", textAbstract)) {
        ::taihe::string thTextAbstract = ::taihe::string(std::move(textAbstract));
        thOpAbstract.emplace(std::move(thTextAbstract));
    }
    std::shared_ptr<Object> detailsPtr;
    ::taihe::optional<::taihe::map<::taihe::string, ::taihe::string>> thOpDetails;
    if (udsObj->GetValue("details", detailsPtr)) {
        UDDetails details = ObjectUtils::ConvertToUDDetails(detailsPtr);
        auto thDetails = ConvertUDDetailsToString(details);
        thOpDetails.emplace(std::move(thDetails));
    }
    ::taihe::string thType = ::taihe::string(uniformDataType);
    ::taihe::string thTextContent = ::taihe::string(textContent);
    ::ohos::data::uniformDataStruct::PlainText plainText = ::ohos::data::uniformDataStruct::PlainText {
        std::move(thType),
        std::move(thTextContent),
        std::move(thOpAbstract),
        std::move(thOpDetails)
    };
    return ::taiheChannel::ValueType::make_plainText(plainText);
}

std::shared_ptr<Object> ConvertPlainText(::taiheStruct::PlainText &text)
{
    std::shared_ptr<Object> obj = std::make_shared<Object>();
    obj->value_["uniformDataType"] = std::string(text.uniformDataType);
    obj->value_["textContent"] = std::string(text.textContent);
    if (text.textAbstract.has_value()) {
        obj->value_["textAbstract"] = std::string(text.textAbstract.value());
    }
    if (text.details.has_value()) {
        auto udDetails = ConvertUDDetails(text.details.value());
        obj->value_["details"] = ObjectUtils::ConvertToObject(udDetails);
    }
    return obj;
}

::taiheChannel::ValueType ConvertHyperlink(std::shared_ptr<Object> udsObj)
{
    std::string uniformDataType;
    udsObj->GetValue(UNIFORM_DATA_TYPE, uniformDataType);
    std::string url;
    udsObj->GetValue("url", url);
    ::taihe::string thType = ::taihe::string(uniformDataType);
    ::taihe::string thUrl = ::taihe::string(url);

    ::taihe::optional<::taihe::string> thDescriptionOpt;
    std::string description;
    if (udsObj->GetValue("description", description)) {
        ::taihe::string thDescription = ::taihe::string(std::move(description));
        thDescriptionOpt.emplace(std::move(thDescription));
    }
    std::shared_ptr<Object> detailsPtr;
    ::taihe::optional<::taihe::map<::taihe::string, ::taihe::string>> thOpDetails;
    if (udsObj->GetValue("details", detailsPtr)) {
        UDDetails details = ObjectUtils::ConvertToUDDetails(detailsPtr);
        auto thDetails = ConvertUDDetailsToString(details);
        thOpDetails.emplace(std::move(thDetails));
    }
    ::ohos::data::uniformDataStruct::Hyperlink hyperlink = ::ohos::data::uniformDataStruct::Hyperlink {
        std::move(thType),
        std::move(thUrl),
        std::move(thDescriptionOpt),
        std::move(thOpDetails)
    };
    return ::taiheChannel::ValueType::make_hyperlink(hyperlink);
}

std::shared_ptr<Object> ConvertHyperlink(::taiheStruct::Hyperlink &link)
{
    std::shared_ptr<Object> obj = std::make_shared<Object>();
    obj->value_["uniformDataType"] = std::string(link.uniformDataType);
    obj->value_["url"] = std::string(link.url);
    if (link.description.has_value()) {
        obj->value_["description"] = std::string(link.description.value());
    }
    if (link.details.has_value()) {
        auto udDetails = ConvertUDDetails(link.details.value());
        obj->value_["details"] = ObjectUtils::ConvertToObject(udDetails);
    }
    return obj;
}

::taiheChannel::ValueType ConvertHTML(std::shared_ptr<Object> udsObj)
{
    std::string uniformDataType;
    udsObj->GetValue(UNIFORM_DATA_TYPE, uniformDataType);
    std::string htmlContent;
    udsObj->GetValue("htmlContent", htmlContent);
    ::taihe::string thType = ::taihe::string(uniformDataType);
    ::taihe::string thHtmlContent = ::taihe::string(htmlContent);

    ::taihe::optional<::taihe::string> thPlainContentOpt;
    std::string plainContent;
    if (udsObj->GetValue("plainContent", plainContent)) {
        ::taihe::string thPlainContent = ::taihe::string(std::move(plainContent));
        thPlainContentOpt.emplace(std::move(thPlainContent));
    }
    std::shared_ptr<Object> detailsPtr;
    ::taihe::optional<::taihe::map<::taihe::string, ::taihe::string>> thOpDetails;
    if (udsObj->GetValue("details", detailsPtr)) {
        UDDetails details = ObjectUtils::ConvertToUDDetails(detailsPtr);
        auto thDetails = ConvertUDDetailsToString(details);
        thOpDetails.emplace(std::move(thDetails));
    }
    ::ohos::data::uniformDataStruct::HTML html = ::ohos::data::uniformDataStruct::HTML {
        std::move(thType),
        std::move(thHtmlContent),
        std::move(thPlainContentOpt),
        std::move(thOpDetails)
    };
    return ::taiheChannel::ValueType::make_html(html);
}

std::shared_ptr<Object> ConvertHTML(::taiheStruct::HTML &html)
{
    std::shared_ptr<Object> obj = std::make_shared<Object>();
    obj->value_["uniformDataType"] = std::string(html.uniformDataType);
    obj->value_["htmlContent"] = std::string(html.htmlContent);
    if (html.plainContent.has_value()) {
        obj->value_["plainContent"] = std::string(html.plainContent.value());
    }
    if (html.details.has_value()) {
        auto udDetails = ConvertUDDetails(html.details.value());
        obj->value_["details"] = ObjectUtils::ConvertToObject(udDetails);
    }
    return obj;
}

::taiheChannel::ValueType ConvertOpenHarmonyAppItem(std::shared_ptr<Object> udsObj)
{
    std::string uniformDataType;
    udsObj->GetValue(UNIFORM_DATA_TYPE, uniformDataType);
    std::string appId;
    udsObj->GetValue("appId", appId);
    std::string appName;
    udsObj->GetValue("appName", appName);
    std::string appIconId;
    udsObj->GetValue("appIconId", appIconId);
    std::string appLabelId;
    udsObj->GetValue("appLabelId", appLabelId);
    std::string bundleName;
    udsObj->GetValue("bundleName", bundleName);
    std::string abilityName;
    udsObj->GetValue("abilityName", abilityName);
    ::taihe::string thType = ::taihe::string(uniformDataType);
    ::taihe::string thAppId = ::taihe::string(appId);
    ::taihe::string thAppName = ::taihe::string(appName);
    ::taihe::string thAppIconId = ::taihe::string(appIconId);
    ::taihe::string thAppLabelId = ::taihe::string(appLabelId);
    ::taihe::string thBundleName = ::taihe::string(bundleName);
    ::taihe::string thAbilityName = ::taihe::string(abilityName);
    std::shared_ptr<Object> detailsPtr;
    ::taihe::optional<::taihe::map<::taihe::string, ::taiheStruct::DetailsValue>> thOpDetails;
    if (udsObj->GetValue("details", detailsPtr)) {
        UDDetails details = ObjectUtils::ConvertToUDDetails(detailsPtr);
        auto thDetails = ConvertUDSUDDetailsToUnion(details);
        thOpDetails.emplace(std::move(thDetails));
    }
    ::ohos::data::uniformDataStruct::OpenHarmonyAppItem openHarmonyAppItem =
            ::ohos::data::uniformDataStruct::OpenHarmonyAppItem {
        std::move(thType),
        std::move(thAppId),
        std::move(thAppName),
        std::move(thAppIconId),
        std::move(thAppLabelId),
        std::move(thBundleName),
        std::move(thAbilityName),
        std::move(thOpDetails)
    };
    return ::taiheChannel::ValueType::make_openHarmonyAppItem(openHarmonyAppItem);
}

std::shared_ptr<Object> ConvertAppItem(::taiheStruct::OpenHarmonyAppItem &item)
{
    std::shared_ptr<Object> obj = std::make_shared<Object>();
    obj->value_["uniformDataType"] = std::string(item.uniformDataType);
    obj->value_["appId"] = std::string(item.appId);
    obj->value_["appName"] = std::string(item.appName);
    obj->value_["appIconId"] = std::string(item.appIconId);
    obj->value_["appLabelId"] = std::string(item.appLabelId);
    obj->value_["bundleName"] = std::string(item.bundleName);
    obj->value_["abilityName"] = std::string(item.abilityName);
    if (item.details.has_value()) {
        auto udDetails = ConvertUDSUDDetailsToUnion(item.details.value());
        obj->value_["details"] = ObjectUtils::ConvertToObject(udDetails);
    }
    return obj;
}

::taiheChannel::ValueType ConvertContentForm(std::shared_ptr<Object> udsObj)
{
    std::string uniformDataType;
    udsObj->GetValue(UNIFORM_DATA_TYPE, uniformDataType);
    std::string title;
    udsObj->GetValue("title", title);
    ::taihe::string thType = ::taihe::string(uniformDataType);
    ::taihe::string thTitle = ::taihe::string(title);
    std::vector<uint8_t> thumbData;
    ::taihe::optional<::taihe::array<uint8_t>> thThumbDataOpt;
    if (udsObj->GetValue("thumbData", thumbData)) {
        ::taihe::array<uint8_t> thThumbData = ::taihe::array<uint8_t>(thumbData);
        thThumbDataOpt.emplace(thThumbData);
    }
    ::taihe::optional<::taihe::string> thDescriptionOpt;
    std::string description;
    if (udsObj->GetValue("description", description)) {
        ::taihe::string thDescription = ::taihe::string(std::move(description));
        thDescriptionOpt.emplace(std::move(thDescription));
    }
    std::vector<uint8_t> appIcon;
    ::taihe::optional<::taihe::array<uint8_t>> thAppIconOpt;
    if (udsObj->GetValue("appIcon", appIcon)) {
        ::taihe::array<uint8_t> thAppIcon = ::taihe::array<uint8_t>(appIcon);
        thAppIconOpt.emplace(thAppIcon);
    }
    ::taihe::optional<::taihe::string> thAppNameOpt;
    std::string appName;
    if (udsObj->GetValue("appName", appName)) {
        ::taihe::string thAppName = ::taihe::string(std::move(appName));
        thAppNameOpt.emplace(std::move(thAppName));
    }
    ::taihe::optional<::taihe::string> thLinkUriOpt;
    std::string linkUri;
    if (udsObj->GetValue("linkUri", linkUri)) {
        ::taihe::string thLinkUri = ::taihe::string(std::move(linkUri));
        thLinkUriOpt.emplace(std::move(thLinkUri));
    }
    ::ohos::data::uniformDataStruct::ContentForm contentForm = ::ohos::data::uniformDataStruct::ContentForm {
        std::move(thType),
        std::move(thThumbDataOpt),
        std::move(thDescriptionOpt),
        std::move(thTitle),
        std::move(thAppIconOpt),
        std::move(thAppNameOpt),
        std::move(thLinkUriOpt)
    };
    return ::taiheChannel::ValueType::make_contentForm(std::move(contentForm));
}

std::shared_ptr<Object> ConvertContentForm(::taiheStruct::ContentForm &form)
{
    std::shared_ptr<Object> obj = std::make_shared<Object>();
    obj->value_["uniformDataType"] = std::string(form.uniformDataType);
    if (form.thumbData.has_value()) {
        ::taihe::array<uint8_t> thThumbData = form.thumbData.value();
        std::vector<uint8_t> valueVec(thThumbData.begin(), thThumbData.end());
        obj->value_["thumbData"] = std::move(valueVec);
    }
    if (form.description.has_value()) {
        obj->value_["description"] = std::string(form.description.value());
    }
    obj->value_["title"] = std::string(form.title);
    if (form.appIcon.has_value()) {
        ::taihe::array<uint8_t> thAppIcon = form.appIcon.value();
        std::vector<uint8_t> valueVec(thAppIcon.begin(), thAppIcon.end());
        obj->value_["appIcon"] = std::move(valueVec);
    }
    if (form.appName.has_value()) {
        obj->value_["appName"] = std::string(form.appName.value());
    }
    if (form.linkUri.has_value()) {
        obj->value_["linkUri"] = std::string(form.linkUri.value());
    }
    return obj;
}

::taiheChannel::ValueType ConvertForm(std::shared_ptr<Object> udsObj)
{
    std::string uniformDataType;
    udsObj->GetValue(UNIFORM_DATA_TYPE, uniformDataType);
    int32_t formId;
    udsObj->GetValue("formId", formId);
    std::string formName;
    udsObj->GetValue("formName", formName);
    std::string bundleName;
    udsObj->GetValue("bundleName", bundleName);
    std::string abilityName;
    udsObj->GetValue("abilityName", abilityName);
    std::string module;
    udsObj->GetValue("module", module);
    ::taihe::string thType = ::taihe::string(uniformDataType);
    ::taihe::string thFormName = ::taihe::string(formName);
    ::taihe::string thBundleName = ::taihe::string(bundleName);
    ::taihe::string thAbilityName = ::taihe::string(abilityName);
    ::taihe::string thModule = ::taihe::string(module);
    std::shared_ptr<Object> detailsPtr;
    ::taihe::optional<::taihe::map<::taihe::string, ::taiheStruct::DetailsValue>> thOpDetails;
    if (udsObj->GetValue("details", detailsPtr)) {
        UDDetails details = ObjectUtils::ConvertToUDDetails(detailsPtr);
        auto thDetails = ConvertUDSUDDetailsToUnion(details);
        thOpDetails.emplace(std::move(thDetails));
    }
    ::ohos::data::uniformDataStruct::Form form = ::ohos::data::uniformDataStruct::Form {
        std::move(thType),
        formId,
        std::move(thFormName),
        std::move(thBundleName),
        std::move(thAbilityName),
        std::move(thModule),
        std::move(thOpDetails)
    };
    return ::taiheChannel::ValueType::make_form(form);
}

std::shared_ptr<Object> ConvertForm(::taiheStruct::Form &form)
{
    std::shared_ptr<Object> obj = std::make_shared<Object>();
    obj->value_["uniformDataType"] = std::string(form.uniformDataType);
    obj->value_["formId"] = form.formId;
    obj->value_["formName"] = std::string(form.formName);
    obj->value_["bundleName"] = std::string(form.bundleName);
    obj->value_["abilityName"] = std::string(form.abilityName);
    obj->value_["module"] = std::string(form.module);
    if (form.details.has_value()) {
        auto udDetails = ConvertUDSUDDetailsToUnion(form.details.value());
        obj->value_["details"] = ObjectUtils::ConvertToObject(udDetails);
    }
    return obj;
}

::taiheChannel::ValueType ConvertFileUri(std::shared_ptr<Object> udsObj)
{
    std::string uniformDataType;
    udsObj->GetValue(UNIFORM_DATA_TYPE, uniformDataType);
    std::string oriUri;
    udsObj->GetValue("oriUri", oriUri);
    std::string fileType;
    udsObj->GetValue("fileType", fileType);
    ::taihe::string thType = ::taihe::string(uniformDataType);
    ::taihe::string thOriUri = ::taihe::string(oriUri);
    ::taihe::string thFileType = ::taihe::string(fileType);
    std::shared_ptr<Object> detailsPtr;
    ::taihe::optional<::taihe::map<::taihe::string, ::taiheStruct::DetailsValue>> thOpDetails;
    if (udsObj->GetValue("details", detailsPtr)) {
        UDDetails details = ObjectUtils::ConvertToUDDetails(detailsPtr);
        auto thDetails = ConvertUDSUDDetailsToUnion(details);
        thOpDetails.emplace(std::move(thDetails));
    }
    ::ohos::data::uniformDataStruct::FileUri fileUri = ::ohos::data::uniformDataStruct::FileUri {
        std::move(thType),
        std::move(thOriUri),
        std::move(thFileType),
        std::move(thOpDetails)
    };
    return ::taiheChannel::ValueType::make_fileUri(fileUri);
}

std::shared_ptr<Object> ConvertFileUri(::taiheStruct::FileUri &file)
{
    std::shared_ptr<Object> obj = std::make_shared<Object>();
    obj->value_["uniformDataType"] = std::string(file.uniformDataType);
    obj->value_["oriUri"] = std::string(file.oriUri);
    obj->value_["fileType"] = std::string(file.fileType);
    if (file.details.has_value()) {
        auto udDetails = ConvertUDSUDDetailsToUnion(file.details.value());
        obj->value_["details"] = ObjectUtils::ConvertToObject(udDetails);
    }
    return obj;
}

::taiheChannel::ValueType ConvertPixelMap(std::shared_ptr<Object> udsObj)
{
    std::string uniformDataType;
    udsObj->GetValue(UNIFORM_DATA_TYPE, uniformDataType);
    std::shared_ptr<OHOS::Media::PixelMap> pixelMapObj;
    udsObj->GetValue("pixelMap", pixelMapObj);
    ani_object aniPixel =
        OHOS::Media::PixelMapTaiheAni::CreateEtsPixelMap(taihe::get_env(), pixelMapObj);
    ::taihe::string thType = ::taihe::string(uniformDataType);
    if (aniPixel == nullptr) {
        return ::taiheChannel::ValueType::make_nullType();
    }

    std::shared_ptr<Object> detailsPtr;
    ::taihe::optional<::taihe::map<::taihe::string, ::taiheStruct::DetailsValue>> thOpDetails;
    if (udsObj->GetValue("details", detailsPtr)) {
        UDDetails details = ObjectUtils::ConvertToUDDetails(detailsPtr);
        auto thDetails = ConvertUDSUDDetailsToUnion(details);
        thOpDetails.emplace(std::move(thDetails));
    }
    ::ohos::data::uniformDataStruct::PixelMap pixelMap = ::ohos::data::uniformDataStruct::PixelMap {
        std::move(thType),
        std::move(thOpDetails),
        reinterpret_cast<uintptr_t>(aniPixel)
    };
    return ::taiheChannel::ValueType::make_pixelMap(std::move(pixelMap));
}

std::shared_ptr<Object> ConvertPixelMap(::taiheStruct::PixelMap &pixel)
{
    std::shared_ptr<Object> obj = std::make_shared<Object>();
    obj->value_["uniformDataType"] = std::string(pixel.uniformDataType);
    if (pixel.details.has_value()) {
        auto udDetails = ConvertUDSUDDetailsToUnion(pixel.details.value());
        obj->value_["details"] = ObjectUtils::ConvertToObject(udDetails);
    }
    auto pixelMapVal = reinterpret_cast<ani_object>(pixel.pixelMap);
    obj->value_["pixelMap"] = OHOS::Media::PixelMapTaiheAni::GetNativePixelMap(taihe::get_env(), pixelMapVal);
    return obj;
}

::taihe::array<::taihe::string> ConvertStringVectorToTaiheArray(const std::vector<std::string>& stringVector)
{
    std::vector<::taihe::string> keys;
    keys.reserve(stringVector.size());
    for (const auto& s : stringVector) {
        keys.emplace_back(s.c_str());
    }
    return ::taihe::array<::taihe::string>(::taihe::copy_data, keys.begin(), keys.size());
}

OHOS::UDMF::UnifiedDataProperties ConvertUnifiedDataProperties(::taiheChannel::UnifiedDataProperties &value)
{
    OHOS::UDMF::UnifiedDataProperties properties;
    if (value.tag.has_value()) {
        properties.tag = std::string(value.tag.value());
    }
    if (value.extras.has_value()) {
        OHOS::AAFwk::WantParams want;
        auto object = reinterpret_cast<ani_ref>(value.extras.value());
        if (OHOS::AppExecFwk::UnwrapWantParams(taihe::get_env(), object, want)) {
            properties.extras = want;
        }
    }
    if (value.shareOptions.has_value()) {
        properties.shareOptions = ConvertShareOptions(value.shareOptions.value());
    }
    return properties;
}

::taiheChannel::UnifiedDataProperties ConvertUnifiedDataProperties(OHOS::UDMF::UnifiedDataProperties &value)
{
    auto tagOpt = ::taihe::optional<::taihe::string>::make(::taihe::string(value.tag));

    auto extrasOpt = ::taihe::optional<uintptr_t>::make(reinterpret_cast<uintptr_t>
        (OHOS::AppExecFwk::WrapWantParams(taihe::get_env(), value.extras)));

    auto shareOptionsOpt = ::taihe::optional<::taiheChannel::ShareOptions>::make(
        ConvertShareOptions(value.shareOptions));

    ::taihe::optional<::taihe::callback<uintptr_t(::taihe::string_view type)>> getDelayDataOpt;

    ani_object aniTimeStamp {};
    SetTimestamp(taihe::get_env(), static_cast<double>(value.timestamp), aniTimeStamp);
    auto timestampOpt = ::taihe::optional<uintptr_t>::make(reinterpret_cast<uintptr_t>(aniTimeStamp));

    auto taiheProperties = ::taiheChannel::UnifiedDataProperties {
        std::move(tagOpt),
        std::move(timestampOpt),
        std::move(shareOptionsOpt),
        std::move(getDelayDataOpt),
        std::move(extrasOpt),
    };
    return taiheProperties;
}
} // namespace UDMF
} // namespace OHOS