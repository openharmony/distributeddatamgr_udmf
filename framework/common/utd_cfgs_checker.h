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

#ifndef UDMF_UTD_CFGS_CHERCKER_H
#define UDMF_UTD_CFGS_CHERCKER_H

#include <regex>

#include "utd_common.h"
#include "visibility.h"
namespace OHOS {
namespace UDMF {
class UtdCfgsChecker {
public:
    static UtdCfgsChecker & API_EXPORT GetInstance();
    Status CheckTypeDescriptors(CustomUtdCfgs &typeCfgs, const std::vector<TypeDescriptorCfg> &presetCfgs,
        const std::vector<TypeDescriptorCfg> &customCfgs, const std::string &bundleName);
    bool CheckBelongingToTypes(const std::vector<TypeDescriptorCfg> &typeCfgs,
        const std::vector<TypeDescriptorCfg> &presetCfgs);
    bool API_EXPORT CheckTypeCfgsFormat(const CustomUtdCfgs &typeCfgs);
    bool API_EXPORT CheckTypeIdsFormat(const std::vector<std::string> &typeIds);

private:
    UtdCfgsChecker();
    ~UtdCfgsChecker();
    UtdCfgsChecker(const UtdCfgsChecker &obj) = delete;
    UtdCfgsChecker &operator=(const UtdCfgsChecker &obj) = delete;
    Status CheckTypeIdsContent(CustomUtdCfgs &typeCfgs, const std::string &bundleName);
    bool CheckTypesRelation(CustomUtdCfgs &typeCfgs, const std::vector<TypeDescriptorCfg> &presetCfgs,
        const std::vector<TypeDescriptorCfg> &customCfgs);
    bool CanConstructDAG(CustomUtdCfgs &typeCfgs, const std::vector<TypeDescriptorCfg> &presetCfgs,
        const std::vector<TypeDescriptorCfg> &customCfgs);
    bool CheckTypeCfgsSize(const std::vector<TypeDescriptorCfg> &typeCfgs);

    static const std::regex typeIdPattern_;
};
}
}
#endif // UDMF_UTD_CFGS_CHERCKER_H
