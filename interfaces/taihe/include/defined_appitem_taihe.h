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

#ifndef UDMF_SYSTEMDEFINEDAPPITEM_H
#define UDMF_SYSTEMDEFINEDAPPITEM_H

#include "ohos.data.unifiedDataChannel.proj.hpp"
#include "ohos.data.unifiedDataChannel.impl.hpp"
#include "system_defined_appitem.h"

namespace taiheChannel = ohos::data::unifiedDataChannel;

namespace OHOS {
namespace UDMF {
class SystemDefinedAppItemTaihe {
public:
    SystemDefinedAppItemTaihe();
    SystemDefinedAppItemTaihe(std::shared_ptr<SystemDefinedAppItem> value);

    ::taihe::string GetType();
    taiheChannel::ValueType GetValue();
    ::taihe::array<::taihe::string> GetTypes();
    void AddEntry(::taihe::string_view type, ::taiheChannel::ValueType value);
    ::taiheChannel::ValueType GetEntry(::taihe::string_view type);
    ::taihe::map<::taihe::string, ::taiheChannel::ValueType> GetEntries();
    ::taihe::optional<::taihe::map<::taihe::string, taiheChannel::DetailsValue>> GetDetails();
    void SetDetails(const ::taihe::map_view<::taihe::string, taiheChannel::DetailsValue> &details);
    ::taihe::string GetAppId();
    void SetAppId(const ::taihe::string_view &appId);
    ::taihe::string GetAppName();
    void SetAppName(const ::taihe::string_view &appName);
    ::taihe::string GetAppIconId();	
    void SetAppIconId(const ::taihe::string_view &appIconId);	
    ::taihe::string GetAppLabelId();	
    void SetAppLabelId(const ::taihe::string_view &appLabelId);
    ::taihe::string GetBundleName();
    void SetBundleName(const ::taihe::string_view &bundleName);
    ::taihe::string GetAbilityName();
    void SetAbilityName(const ::taihe::string_view &abilityName);
    int64_t GetInner();

    std::shared_ptr<SystemDefinedAppItem> value_;
};

} // namespace UDMF
} // namespace OHOS
#endif // UDMF_SYSTEMDEFINEDAPPITEM_H