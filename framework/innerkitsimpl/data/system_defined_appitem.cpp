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
    SetType(SYSTEM_DEFINED_APP_ITEM);
}

SystemDefinedAppItem::SystemDefinedAppItem(UDType type, ValueType value) : SystemDefinedRecord(type, value)
{
    SetType(SYSTEM_DEFINED_APP_ITEM);
    if (std::holds_alternative<std::shared_ptr<Object>>(value)) {
        auto object = std::get<std::shared_ptr<Object>>(value);
        object->GetValue(APP_ID, appId_);
        object->GetValue(APP_NAME, appName_);
        object->GetValue(APP_ICON_ID, appIconId_);
        object->GetValue(APP_LABEL_ID, appLabelId_);
        object->GetValue(BUNDLE_NAME, bundleName_);
        object->GetValue(ABILITY_NAME, abilityName_);
        std::shared_ptr<Object> detailObj = nullptr;
        if (object->GetValue(DETAILS, detailObj)) {
            details_ = ObjectUtils::ConvertToUDDetails(detailObj);
        }
    }
}

int64_t SystemDefinedAppItem::GetSize()
{
    return static_cast<int64_t>(UnifiedDataUtils::GetDetailsSize(this->details_) + this->appId_.size() +
        this->appName_.size() + this->appIconId_.size() + this->appLabelId_.size() + this->bundleName_.size() +
        this->abilityName_.size()) + GetInnerEntriesSize();
}

std::string SystemDefinedAppItem::GetAppId() const
{
    return this->appId_;
}

void SystemDefinedAppItem::SetAppId(const std::string &appId)
{
    this->appId_ = appId;
    if (std::holds_alternative<std::shared_ptr<Object>>(value_)) {
        std::get<std::shared_ptr<Object>>(value_)->value_[APP_ID] = appId_;
    }
}

std::string SystemDefinedAppItem::GetAppName() const
{
    return this->appName_;
}

void SystemDefinedAppItem::SetAppName(const std::string &appName)
{
    this->appName_ = appName;
    if (std::holds_alternative<std::shared_ptr<Object>>(value_)) {
        std::get<std::shared_ptr<Object>>(value_)->value_[APP_NAME] = appName_;
    }
}

std::string SystemDefinedAppItem::GetAppIconId() const
{
    return this->appIconId_;
}

void SystemDefinedAppItem::SetAppIconId(const std::string &appIconId)
{
    this->appIconId_ = appIconId;
    if (std::holds_alternative<std::shared_ptr<Object>>(value_)) {
        std::get<std::shared_ptr<Object>>(value_)->value_[APP_ICON_ID] = appIconId_;
    }
}

std::string SystemDefinedAppItem::GetAppLabelId() const
{
    return this->appLabelId_;
}

void SystemDefinedAppItem::SetAppLabelId(const std::string &appLabelId)
{
    this->appLabelId_ = appLabelId;
    if (std::holds_alternative<std::shared_ptr<Object>>(value_)) {
        std::get<std::shared_ptr<Object>>(value_)->value_[APP_LABEL_ID] = appLabelId_;
    }
}

std::string SystemDefinedAppItem::GetBundleName() const
{
    return this->bundleName_;
}

void SystemDefinedAppItem::SetBundleName(const std::string &bundleName)
{
    this->bundleName_ = bundleName;
    if (std::holds_alternative<std::shared_ptr<Object>>(value_)) {
        std::get<std::shared_ptr<Object>>(value_)->value_[BUNDLE_NAME] = bundleName_;
    }
}

std::string SystemDefinedAppItem::GetAbilityName() const
{
    return this->abilityName_;
}

void SystemDefinedAppItem::SetAbilityName(const std::string &abilityName)
{
    this->abilityName_ = abilityName;
    if (std::holds_alternative<std::shared_ptr<Object>>(value_)) {
        std::get<std::shared_ptr<Object>>(value_)->value_[ABILITY_NAME] = abilityName_;
    }
}

void SystemDefinedAppItem::SetItems(UDDetails &details)
{
    for (auto &item : details) {
        auto* value = std::get_if<std::string>(&item.second);
        if (value == nullptr) {
            continue;
        }
        if (item.first == APP_ID) {
            SetAppId(*value);
        }
        if (item.first == APP_NAME) {
            SetAppName(*value);
        }
        if (item.first == APP_ICON_ID) {
            SetAppIconId(*value);
        }
        if (item.first == APP_LABEL_ID) {
            SetAppLabelId(*value);
        }
        if (item.first == BUNDLE_NAME) {
            SetBundleName(*value);
        }
        if (item.first == ABILITY_NAME) {
            SetAbilityName(*value);
        }
    }
}

UDDetails SystemDefinedAppItem::GetItems()
{
    UDDetails items;
    items[APP_ID] = GetAppId();
    items[APP_NAME] = GetAppName();
    items[APP_ICON_ID] = GetAppIconId();
    items[APP_LABEL_ID] = GetAppLabelId();
    items[BUNDLE_NAME] = GetBundleName();
    items[ABILITY_NAME] = GetAbilityName();
    return items;
}

void SystemDefinedAppItem::InitObject()
{
    if (!std::holds_alternative<std::shared_ptr<Object>>(value_)) {
        auto value = value_;
        value_ = std::make_shared<Object>();
        auto object = std::get<std::shared_ptr<Object>>(value_);
        object->value_[UNIFORM_DATA_TYPE] = UtdUtils::GetUtdIdFromUtdEnum(dataType_);
        object->value_[APP_ID] = appId_;
        object->value_[APP_NAME] = appName_;
        object->value_[APP_ICON_ID] = appIconId_;
        object->value_[APP_LABEL_ID] = appLabelId_;
        object->value_[BUNDLE_NAME] = bundleName_;
        object->value_[ABILITY_NAME] = abilityName_;
        object->value_[DETAILS] = ObjectUtils::ConvertToObject(details_);
        object->value_.insert_or_assign(VALUE_TYPE, std::move(value));
    }
}
} // namespace UDMF
} // namespace OHOS