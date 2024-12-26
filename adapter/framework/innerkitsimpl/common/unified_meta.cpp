/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#define LOG_TAG "UnifiedMeta"
#include "unified_meta.h"

#include "logger.h"
#include "unified_key.h"

namespace OHOS {
namespace UDMF {

static constexpr std::initializer_list<std::string_view> NOT_NEED_COUNT_VALUE_LIST = {
    UNIFORM_DATA_TYPE, ARRAY_BUFFER_LENGTH, THUMB_DATA_LENGTH, APP_ICON_LENGTH
};

namespace UtdUtils {
bool IsValidUtdId(const std::string &utdId)
{
    for (const auto &item : UTD_TYPES) {
        if (item.UtdId == utdId) {
            return true;
        }
    }
    return false;
}

int32_t GetUtdEnumFromUtdId(const std::string &utdId)
{
    for (const auto &item : UTD_TYPES) {
        if (item.UtdId == utdId) {
            return item.UtdEnum;
        }
    }
    return UD_BUTT;
}

std::string GetUtdIdFromUtdEnum(int32_t utdType)
{
    for (const auto &item : UTD_TYPES) {
        if (item.UtdEnum == utdType) {
            return item.UtdId;
        }
    }
    return "";
}

std::vector<UtdType> GetUtdTypes()
{
    std::vector<UtdType> utdTypes(UTD_TYPES, UTD_TYPES + sizeof(UTD_TYPES) / sizeof(UtdType));
    return utdTypes;
}
} // namespace UtdUtils

bool UnifiedDataUtils::IsValidType(int32_t value)
{
    return value >= ENTITY && value < UD_BUTT;
}

bool UnifiedDataUtils::IsValidIntention(int32_t value)
{
    return value > UD_INTENTION_BASE && value < UD_INTENTION_BUTT;
}

static constexpr AppShareOption APP_SHARE_OPTIONS[] = {
    { IN_APP, "IN_APP"},
    { CROSS_APP, "CROSS_APP"},
};

bool ShareOptionsUtil::IsValid(int32_t shareOption)
{
    if (shareOption < 0 || shareOption >= SHARE_OPTIONS_BUTT) {
        return false;
    }
    return true;
}

int32_t ShareOptionsUtil::GetEnumNum(const std::string &shareOption)
{
    for (const auto &item : APP_SHARE_OPTIONS) {
        if (item.enumStr == shareOption) {
            return item.enumNum;
        }
    }
    return SHARE_OPTIONS_BUTT;
}

std::string ShareOptionsUtil::GetEnumStr(int32_t shareOption)
{
    for (const auto &item : APP_SHARE_OPTIONS) {
        if (item.enumNum == shareOption) {
            return item.enumStr;
        }
    }
    return "";
}

size_t UnifiedDataUtils::GetVariantSize(UDVariant &variant)
{
    auto int32Value = std::get_if<int32_t>(&variant);
    if (int32Value != nullptr) {
        return sizeof(std::get<int32_t>(variant));
    }
    auto int64Value = std::get_if<int64_t>(&variant);
    if (int64Value != nullptr) {
        return sizeof(std::get<int64_t>(variant));
    }
    auto boolValue = std::get_if<bool>(&variant);
    if (boolValue != nullptr) {
        return sizeof(std::get<bool>(variant));
    }
    auto doubleValue = std::get_if<double>(&variant);
    if (doubleValue != nullptr) {
        return sizeof(std::get<double>(variant));
    }
    auto strValue = std::get_if<std::string>(&variant);
    if (strValue != nullptr) {
        return std::get<std::string>(variant).size();
    }
    auto vecValue = std::get_if<std::vector<uint8_t>>(&variant);
    if (vecValue != nullptr) {
        return std::get<std::vector<uint8_t>>(variant).size();
    }
    return 0;
}

size_t UnifiedDataUtils::GetDetailsSize(UDDetails &details)
{
    size_t total = 0;
    for (std::pair<std::string, UDVariant> prop : details) {
        total += prop.first.size();
        total += GetVariantSize(prop.second);
    }
    return total;
}

bool UnifiedDataUtils::IsPersist(const Intention &intention)
{
    return intention >= UD_INTENTION_DATA_HUB && intention < UD_INTENTION_BUTT;
}

bool UnifiedDataUtils::IsPersist(const std::string &intention)
{
    return IsPersist(GetIntentionByString(intention));
}

Intention UnifiedDataUtils::GetIntentionByString(const std::string &intention)
{
    for (const auto &it : UD_INTENTION_MAP) {
        if (it.second == intention) {
            return static_cast<Intention>(it.first);
        }
    }
    return UD_INTENTION_BUTT;
}

bool UnifiedDataUtils::IsValidOptions(const std::string &key, std::string &intention)
{
    UnifiedKey unifiedKey(key);
    auto isValidKey = unifiedKey.IsValid();
    if (key.empty() && IsPersist(intention)) {
        return true;
    }
    if (intention.empty() && isValidKey && IsPersist(unifiedKey.intention)) {
        return true;
    }
    if (isValidKey && unifiedKey.intention == intention && IsPersist(intention)) {
        intention = "";
        return true;
    }
    return false;
}

std::shared_ptr<Object> ObjectUtils::ConvertToObject(UDDetails &details)
{
    Object object;
    for (auto [key, value] : details) {
        ConvertVariant(std::move(value), object.value_[key]);
    }
    return std::make_shared<Object>(object);
}

UDDetails ObjectUtils::ConvertToUDDetails(std::shared_ptr<Object> object)
{
    UDDetails details;
    if (object == nullptr) {
        return details;
    }
    for (auto [key, value] : object->value_) {
        if (!ConvertVariant(std::move(value), details[key])) {
            LOG_ERROR(UnifiedRecord, "object convert to UDDetails failed, object key is %{public}s", key.c_str());
        }
    }
    return details;
}

int64_t ObjectUtils::GetValueSize(const ValueType &value, bool isCalValueType)
{
    return 0;
}

int64_t ObjectUtils::GetObjectValueSize(const std::shared_ptr<Object> object, bool isCalValueType)
{
    return 0;
}

int64_t ObjectUtils::GetAllObjectSize(const std::shared_ptr<Object> object)
{
    return 0;
}
} // namespace UDMF
} // namespace OHOS