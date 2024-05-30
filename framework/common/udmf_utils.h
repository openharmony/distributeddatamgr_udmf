/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef UDMF_UTILS_H
#define UDMF_UTILS_H

#include <string>
#include <vector>
namespace OHOS {
namespace UDMF {
namespace UTILS {
std::vector<std::string> StrSplit(std::string str, std::string subStr);
std::vector<uint8_t> Random(int32_t len, int32_t minimum = 0,
                            int32_t maximum = std::numeric_limits<uint8_t>::max());
std::string GenerateId();

} // namespace UTILS
} // namespace UDMF
} // namespace OHOS

#endif /* UDMF_UTILS_H */
