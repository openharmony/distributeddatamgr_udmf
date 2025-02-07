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

#ifndef UDMF_SYSTEM_DEFINED_FORM_H
#define UDMF_SYSTEM_DEFINED_FORM_H

#include "system_defined_record.h"
#include "visibility.h"
namespace OHOS {
namespace UDMF {
class SystemDefinedForm : public SystemDefinedRecord {
public:
    API_EXPORT SystemDefinedForm();
    API_EXPORT SystemDefinedForm(UDType type, ValueType value);

    int64_t API_EXPORT GetSize() override;

    int32_t API_EXPORT GetFormId() const;
    void API_EXPORT SetFormId(const int32_t &formId);
    std::string API_EXPORT GetFormName() const;
    void API_EXPORT SetFormName(const std::string &formName);
    std::string API_EXPORT GetBundleName() const;
    void API_EXPORT SetBundleName(const std::string &bundleName);
    std::string API_EXPORT GetAbilityName() const;
    void API_EXPORT SetAbilityName(const std::string &abilityName);
    std::string API_EXPORT GetModule() const;
    void API_EXPORT SetModule(const std::string &module);

    void API_EXPORT SetItems(UDDetails &details);
    UDDetails API_EXPORT GetItems();

    void InitObject() override;

private:
    int32_t formId_{-1};
    std::string formName_;
    std::string bundleName_;
    std::string abilityName_;
    std::string module_;

};
} // namespace UDMF
} // namespace OHOS
#endif // UDMF_SYSTEM_DEFINED_FORM_H
