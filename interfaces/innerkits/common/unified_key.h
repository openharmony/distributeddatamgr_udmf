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

#ifndef UDMF_UNIFIED_KEY_H
#define UDMF_UNIFIED_KEY_H

#include <bitset>
#include <string>

namespace OHOS {
namespace UDMF {
constexpr int MAX_BIT_SIZE = 128;
struct UnifiedKey {
    UnifiedKey() = default;
    explicit UnifiedKey(std::string key);
    UnifiedKey(std::string intention, std::string bundle, std::string groupId);
    std::string key;
    std::string intention;
    std::string bundleName;
    std::string groupId;
    std::string GetUnifiedKey();
    bool IsValid();
    void PreliminaryWork();
    bool CheckCharacter(std::string data, std::bitset<MAX_BIT_SIZE> rule);
};
} // namespace UDMF
} // namespace OHOS
#endif // UDMF_UNIFIED_KEY_H