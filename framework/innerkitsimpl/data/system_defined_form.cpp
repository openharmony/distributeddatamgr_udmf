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

#include "system_defined_form.h"

namespace OHOS {
namespace UDMF {
SystemDefinedForm::SystemDefinedForm()
{
    SetType(SYSTEM_DEFINED_FORM);
}

SystemDefinedForm::SystemDefinedForm(UDType type, ValueType value) : SystemDefinedRecord(type, value)
{
    SetType(SYSTEM_DEFINED_FORM);
    if (std::holds_alternative<std::shared_ptr<Object>>(value)) {
        auto object = std::get<std::shared_ptr<Object>>(value);
        object->GetValue(FORMID, formId_);
        object->GetValue(FORMNAME, formName_);
        object->GetValue(BUNDLE_NAME, bundleName_);
        object->GetValue(ABILITY_NAME, abilityName_);
        object->GetValue(MODULE, module_);
        std::shared_ptr<Object> detailObj = nullptr;
        if (object->GetValue(DETAILS, detailObj)) {
            details_ = ObjectUtils::ConvertToUDDetails(detailObj);
        }
        hasObject_ = true;
    }
}

int64_t SystemDefinedForm::GetSize()
{
    return static_cast<int64_t>(UnifiedDataUtils::GetDetailsSize(this->details_) + sizeof(formId_) +
        this->formName_.size() + this->bundleName_.size() + this->abilityName_.size() + this->module_.size()) +
        GetInnerEntriesSize();
}

int32_t SystemDefinedForm::GetFormId() const
{
    return this->formId_;
}

void SystemDefinedForm::SetFormId(const int32_t &formId)
{
    this->formId_ = formId;
    if (std::holds_alternative<std::shared_ptr<Object>>(value_)) {
        std::get<std::shared_ptr<Object>>(value_)->value_[FORMID] = formId_;
    }
}

std::string SystemDefinedForm::GetFormName() const
{
    return this->formName_;
}

void SystemDefinedForm::SetFormName(const std::string &formName)
{
    this->formName_ = formName;
    if (std::holds_alternative<std::shared_ptr<Object>>(value_)) {
        std::get<std::shared_ptr<Object>>(value_)->value_[FORMNAME] = formName_;
    }
}

std::string SystemDefinedForm::GetBundleName() const
{
    return this->bundleName_;
}

void SystemDefinedForm::SetBundleName(const std::string &bundleName)
{
    this->bundleName_ = bundleName;
    if (std::holds_alternative<std::shared_ptr<Object>>(value_)) {
        std::get<std::shared_ptr<Object>>(value_)->value_[BUNDLE_NAME] = bundleName_;
    }
}

std::string SystemDefinedForm::GetAbilityName() const
{
    return this->abilityName_;
}

void SystemDefinedForm::SetAbilityName(const std::string &abilityName)
{
    this->abilityName_ = abilityName;
    if (std::holds_alternative<std::shared_ptr<Object>>(value_)) {
        std::get<std::shared_ptr<Object>>(value_)->value_[ABILITY_NAME] = abilityName_;
    }
}

std::string SystemDefinedForm::GetModule() const
{
    return this->module_;
}

void SystemDefinedForm::SetModule(const std::string &module)
{
    this->module_ = module;
    if (std::holds_alternative<std::shared_ptr<Object>>(value_)) {
        std::get<std::shared_ptr<Object>>(value_)->value_[MODULE] = module_;
    }
}

void SystemDefinedForm::SetItems(UDDetails& details)
{
    for (auto &item : details) {
        auto* value = std::get_if<std::string>(&item.second);
        auto* intValue = std::get_if<int32_t>(&item.second);
        if (value == nullptr && intValue == nullptr) {
            continue;
        }
        if (intValue != nullptr && item.first == FORMID) {
            SetFormId(*intValue);
            continue;
        }
        if (value == nullptr) {
            continue;
        }
        if (item.first == FORMNAME) {
            SetFormName(*value);
        }
        if (item.first == MODULE) {
            SetModule(*value);
        }
        if (item.first == BUNDLE_NAME) {
            SetBundleName(*value);
        }
        if (item.first == ABILITY_NAME) {
            SetAbilityName(*value);
        }
    }
}

UDDetails SystemDefinedForm::GetItems()
{
    UDDetails items;
    items[FORMID] = GetFormId();
    items[FORMNAME] = GetFormName();
    items[MODULE] = GetModule();
    items[BUNDLE_NAME] = GetBundleName();
    items[ABILITY_NAME] = GetAbilityName();
    return items;
}

void SystemDefinedForm::InitObject()
{
    if (!std::holds_alternative<std::shared_ptr<Object>>(value_)) {
        auto value = value_;
        value_ = std::make_shared<Object>();
        auto object = std::get<std::shared_ptr<Object>>(value_);
        object->value_[UNIFORM_DATA_TYPE] = UtdUtils::GetUtdIdFromUtdEnum(dataType_);
        object->value_[FORMID] = formId_;
        object->value_[FORMNAME] = formName_;
        object->value_[BUNDLE_NAME] = bundleName_;
        object->value_[ABILITY_NAME] = abilityName_;
        object->value_[MODULE] = module_;
        object->value_[DETAILS] = ObjectUtils::ConvertToObject(details_);
        object->value_.insert_or_assign(VALUE_TYPE, std::move(value));
    }
}

} // namespace UDMF
} // namespace OHOS
