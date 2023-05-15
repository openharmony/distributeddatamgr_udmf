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

namespace OHOS {
namespace UDMF {
class SystemDefinedForm : public SystemDefinedRecord {
public:
    SystemDefinedForm();

    int64_t GetSize() override;

    int32_t GetFormId() const;
    void SetFormId(const int32_t &formId);
    std::string GetFormName() const;
    void SetFormName(const std::string &formName);
    std::string GetBundleName() const;
    void SetBundleName(const std::string &bundleName);
    std::string GetAbilityName() const;
    void SetAbilityName(const std::string &abilityName);
    std::string GetModule() const;
    void SetModule(const std::string &module);

private:
    int32_t formId_;
    std::string formName_;
    std::string bundleName_;
    std::string abilityName_;
    std::string module_;
};
} // namespace UDMF
} // namespace OHOS
#endif //UDMF_SYSTEM_DEFINED_FORM_H
