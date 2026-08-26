/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#include "unified_types.h"

namespace OHOS {
namespace UDMF {
std::vector<std::string> Summary::GetFileExtensionsByType(const std::string &typeId) const
{
    auto it = typeToFileExtensions.find(typeId);
    if (it != typeToFileExtensions.end()) {
        return it->second;
    }
    return {};
}

std::vector<std::string> Summary::GetAllFileExtensions() const
{
    std::vector<std::string> allExtensions;
    for (const auto &[typeId, extensions] : typeToFileExtensions) {
        for (const auto &ext : extensions) {
            if (std::find(allExtensions.begin(), allExtensions.end(), ext) == allExtensions.end()) {
                allExtensions.push_back(ext);
            }
        }
    }
    return allExtensions;
}
} // namespace UDMF
} // namespace OHOS
