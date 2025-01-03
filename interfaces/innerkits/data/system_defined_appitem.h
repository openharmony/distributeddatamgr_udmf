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
class API_EXPORT SystemDefinedAppItem : public SystemDefinedRecord {
public:
    SystemDefinedAppItem();
    SystemDefinedAppItem(UDType type, ValueType value);

    int64_t GetSize() override;

    std::string GetAppId() const;
    void SetAppId(const std::string &appId);
    std::string GetAppName() const;
    void SetAppName(const std::string &appName);
    std::string GetAppIconId() const;
    void SetAppIconId(const std::string &appIconId);
    std::string GetAppLabelId() const;
    void SetAppLabelId(const std::string &appLabelId);
    std::string GetBundleName() const;
    void SetBundleName(const std::string &bundleName);
    std::string GetAbilityName() const;
    void SetAbilityName(const std::string &abilityName);
    void SetItems(UDDetails &details);
    UDDetails GetItems();
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
