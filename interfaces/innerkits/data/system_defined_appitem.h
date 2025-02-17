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

#ifndef UDMF_SYSTEM_DEFINED_APPITEM_H
#define UDMF_SYSTEM_DEFINED_APPITEM_H

#include "system_defined_record.h"
#include "visibility.h"

namespace OHOS {
namespace UDMF {
class SystemDefinedAppItem : public SystemDefinedRecord {
public:
    API_EXPORT SystemDefinedAppItem();
    API_EXPORT SystemDefinedAppItem(UDType type, ValueType value);

    int64_t API_EXPORT GetSize() override;

    std::string API_EXPORT GetAppId() const;
    void API_EXPORT SetAppId(const std::string &appId);
    std::string API_EXPORT GetAppName() const;
    void API_EXPORT SetAppName(const std::string &appName);
    std::string API_EXPORT GetAppIconId() const;
    void API_EXPORT SetAppIconId(const std::string &appIconId);
    std::string API_EXPORT GetAppLabelId() const;
    void API_EXPORT SetAppLabelId(const std::string &appLabelId);
    std::string API_EXPORT GetBundleName() const;
    void API_EXPORT SetBundleName(const std::string &bundleName);
    std::string API_EXPORT GetAbilityName() const;
    void API_EXPORT SetAbilityName(const std::string &abilityName);
    void API_EXPORT SetItems(UDDetails &details);
    UDDetails API_EXPORT GetItems();
    void InitObject() override;

    static bool CheckValue(const ValueType &value);
private:
    std::string appId_;
    std::string appName_;
    std::string appIconId_;
    std::string appLabelId_;
    std::string bundleName_;
    std::string abilityName_;
};
} // namespace UDMF
} // namespace OHOS
#endif // UDMF_SYSTEM_DEFINED_APPITEM_H
