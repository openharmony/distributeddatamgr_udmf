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
#include "visibility.h"
namespace OHOS {
namespace UDMF {
namespace UTILS {
std::vector<uint8_t> Random(int32_t len, int32_t minimum = 0,
                            int32_t maximum = std::numeric_limits<uint8_t>::max());
std::string API_EXPORT GenerateId();
std::string GetSdkVersionByToken(uint32_t tokenId);
std::string GetCurrentSdkVersion();
bool API_EXPORT IsTokenNative();
bool API_EXPORT IsNativeCallingToken();
std::string API_EXPORT GetSequenceKey(const std::string &udKey);

} // namespace UTILS
} // namespace UDMF
} // namespace OHOS

#endif /* UDMF_UTILS_H */
