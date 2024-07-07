/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "system_defined_appitem.h"

namespace OHOS {
namespace UDMF {
SystemDefinedAppItem::SystemDefinedAppItem()
{
    this->dataType_ = SYSTEM_DEFINED_APP_ITEM;
}

SystemDefinedAppItem::SystemDefinedAppItem(UDType type, ValueType value) : SystemDefinedRecord(type, value)
{
    this->dataType_ = SYSTEM_DEFINED_APP_ITEM;
    if (std::holds_alternative<std::shared_ptr<Object>>(value)) {
        auto object = std::get<std::shared_ptr<Object>>(value);
        object->GetValue(APPID, appId_);
        object->GetValue(APPNAME, appName_);
        object->GetValue(APPICONID, appIconId_);
        object->GetValue(APPLABELID, appLabelId_);
        object->GetValue(BUNDLENAME, bundleName_);
        object->GetValue(ABILITYNAME, abilityName_);
        std::shared_ptr<Object> detailObj = nullptr;
        if (object->GetValue(DETAILS, detailObj)) {
            details_ = ObjectUtils::ConvertToUDDetails(detailObj);
        }
    }
}

int64_t SystemDefinedAppItem::GetSize()
{
    return UnifiedDataUtils::GetDetailsSize(this->details_) + this->appId_.size() + this->appName_.size()
           + this->appIconId_.size() + this->appLabelId_.size() + this->bundleName_.size() + this->abilityName_.size();
}

std::string SystemDefinedAppItem::GetAppId() const
{
    return this->appId_;
}

void SystemDefinedAppItem::SetAppId(const std::string &appId)
{
    this->appId_ = appId;
    InitObject();
}

std::string SystemDefinedAppItem::GetAppName() const
{
    return this->appName_;
}

void SystemDefinedAppItem::SetAppName(const std::string &appName)
{
    this->appName_ = appName;
    InitObject();
}

std::string SystemDefinedAppItem::GetAppIconId() const
{
    return this->appIconId_;
}

void SystemDefinedAppItem::SetAppIconId(const std::string &appIconId)
{
    this->appIconId_ = appIconId;
    InitObject();
}

std::string SystemDefinedAppItem::GetAppLabelId() const
{
    return this->appLabelId_;
}

void SystemDefinedAppItem::SetAppLabelId(const std::string &appLabelId)
{
    this->appLabelId_ = appLabelId;
    InitObject();
}

std::string SystemDefinedAppItem::GetBundleName() const
{
    return this->bundleName_;
}

void SystemDefinedAppItem::SetBundleName(const std::string &bundleName)
{
    this->bundleName_ = bundleName;
    InitObject();
}

std::string SystemDefinedAppItem::GetAbilityName() const
{
    return this->abilityName_;
}

void SystemDefinedAppItem::SetAbilityName(const std::string &abilityName)
{
    this->abilityName_ = abilityName;
    InitObject();
}

void SystemDefinedAppItem::SetItems(UDDetails &details)
{
    for (auto &item : details) {
        auto* value = std::get_if<std::string>(&item.second);
        if (value == nullptr) {
            continue;
        }
        if (item.first == APPID) {
            SetAppId(*value);
        }
        if (item.first == APPNAME) {
            SetAppName(*value);
        }
        if (item.first == APPICONID) {
            SetAppIconId(*value);
        }
        if (item.first == APPLABELID) {
            SetAppLabelId(*value);
        }
        if (item.first == BUNDLENAME) {
            SetBundleName(*value);
        }
        if (item.first == ABILITYNAME) {
            SetAbilityName(*value);
        }
    }
    InitObject();
}

UDDetails SystemDefinedAppItem::GetItems()
{
    UDDetails items;
    items[APPID] = GetAppId();
    items[APPNAME] = GetAppName();
    items[APPICONID] = GetAppIconId();
    items[APPLABELID] = GetAppLabelId();
    items[BUNDLENAME] = GetBundleName();
    items[ABILITYNAME] = GetAbilityName();
    return items;
}

void SystemDefinedAppItem::InitObject()
{
    if (std::holds_alternative<std::monostate>(value_)) {
        value_ = std::make_shared<Object>();
    }
    if (std::holds_alternative<std::shared_ptr<Object>>(value_)) {
        auto object = std::get<std::shared_ptr<Object>>(value_);
        object->value_[UNIFORM_DATA_TYPE] = UtdUtils::GetUtdIdFromUtdEnum(dataType_);
        object->value_[APPID] = appId_;
        object->value_[APPNAME] = appName_;
        object->value_[APPICONID] = appIconId_;
        object->value_[APPLABELID] = appLabelId_;
        object->value_[BUNDLENAME] = bundleName_;
        object->value_[ABILITYNAME] = abilityName_;
        object->value_[DETAILS] = ObjectUtils::ConvertToObject(details_);
    }
}

bool SystemDefinedAppItem::CheckValue(const ValueType &value)
{
    if (!std::holds_alternative<std::shared_ptr<Object>>(value)) {
        return true;
    }
    auto object = std::get<std::shared_ptr<Object>>(value);

    bool IsValid = true;
    IsValid = IsValid && object->HasStrValue(UNIFORM_DATA_TYPE);
    IsValid = IsValid && object->HasStrValue(APPID);
    IsValid = IsValid && object->HasStrValue(APPNAME);
    IsValid = IsValid && object->HasStrValue(APPICONID);
    IsValid = IsValid && object->HasStrValue(APPLABELID);
    IsValid = IsValid && object->HasStrValue(BUNDLENAME);
    IsValid = IsValid && object->HasStrValue(ABILITYNAME);

    auto isValidDetail = [](const auto& pair) {
        const ValueType& value = pair.second;
        return std::holds_alternative<int32_t>(value) || std::holds_alternative<int64_t>(value) ||
               std::holds_alternative<double>(value) || std::holds_alternative<std::string>(value) ||
               std::holds_alternative<std::vector<uint8_t>>(value);
    };
    std::shared_ptr<Object> detailObj = nullptr;
    if (object->GetValue(DETAILS, detailObj)) {
        IsValid = IsValid && std::all_of(detailObj->value_.begin(), detailObj->value_.end(), isValidDetail);
    }

    auto isValidKey = [](const auto& pair) {
        const std::string& key = pair.first;
        return key == UNIFORM_DATA_TYPE || key == APPID || key == APPNAME || key == APPICONID ||
                key == APPLABELID || key == BUNDLENAME || key == ABILITYNAME || key == DETAILS;
    };
    IsValid = IsValid && std::all_of(object->value_.begin(), object->value_.end(), isValidKey);
    return IsValid;
}
} // namespace UDMF
} // namespace OHOS