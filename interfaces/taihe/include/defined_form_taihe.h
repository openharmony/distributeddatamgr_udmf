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

#ifndef UDMF_SYSTEMDEFINEDFORM_H
#define UDMF_SYSTEMDEFINEDFORM_H

#include "ohos.data.unifiedDataChannel.proj.hpp"
#include "ohos.data.unifiedDataChannel.impl.hpp"
#include "system_defined_form.h"

namespace taiheUdmf = OHOS::UDMF;

class SystemDefinedFormInnerImpl {
public:
    SystemDefinedFormInnerImpl();

    ::taihe::string GetType();
    ::ohos::data::unifiedDataChannel::ValueType GetValue();

    ::taihe::optional<::taihe::map<::taihe::string, ::ohos::data::unifiedDataChannel::DetailsValue>> GetDetails();
    void SetDetails(::taihe::map_view<::taihe::string, ::ohos::data::unifiedDataChannel::DetailsValue> details);
    double GetFormId();
    void SetFormId(double formId);
    ::taihe::string GetFormName();
    void SetFormName(::taihe::string_view formName);
    ::taihe::string GetBundleName();
    void SetBundleName(::taihe::string_view bundleName);
    ::taihe::string GetAbilityName();
    void SetAbilityName(::taihe::string_view abilityName);
    ::taihe::string GetModule();
    void SetModule(::taihe::string_view module);
    int64_t GetInner();

    std::shared_ptr<taiheUdmf::SystemDefinedForm> value_;
};
#endif // UDMF_SYSTEMDEFINEDFORM_H