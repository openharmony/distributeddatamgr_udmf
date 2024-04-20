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

SystemDefinedAppItem::SystemDefinedAppItem(UDType type, ValueType value) : SystemDefinedRecord(type, value) {}

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
}

std::string SystemDefinedAppItem::GetAppName() const
{
    return this->appName_;
}

void SystemDefinedAppItem::SetAppName(const std::string &appName)
{
    this->appName_ = appName;
}

std::string SystemDefinedAppItem::GetAppIconId() const
{
    return this->appIconId_;
}

void SystemDefinedAppItem::SetAppIconId(const std::string &appIconId)
{
    this->appIconId_ = appIconId;
}

std::string SystemDefinedAppItem::GetAppLabelId() const
{
    return this->appLabelId_;
}

void SystemDefinedAppItem::SetAppLabelId(const std::string &appLabelId)
{
    this->appLabelId_ = appLabelId;
}

std::string SystemDefinedAppItem::GetBundleName() const
{
    return this->bundleName_;
}

void SystemDefinedAppItem::SetBundleName(const std::string &bundleName)
{
    this->bundleName_ = bundleName;
}

std::string SystemDefinedAppItem::GetAbilityName() const
{
    return this->abilityName_;
}

void SystemDefinedAppItem::SetAbilityName(const std::string &abilityName)
{
    this->abilityName_ = abilityName;
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
} // namespace UDMF
} // namespace OHOS