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

#ifndef URI_PERMISSION_UTIL_H
#define URI_PERMISSION_UTIL_H

#include "unified_meta.h"

namespace OHOS {
namespace UDMF {
namespace UriPermissionUtil {
constexpr uint32_t READ_FLAG = 1u << 0;
constexpr uint32_t WRITE_FLAG = 1u << 1;
constexpr uint32_t PERSIST_FLAG = 1u << 2;

bool API_EXPORT IsValid(int32_t permission);
uint32_t API_EXPORT ToMask(UriPermission permission);
uint32_t API_EXPORT ToMask(const std::vector<UriPermission> &permissions);
uint32_t API_EXPORT ToMask(const std::vector<int32_t> &permissions);
uint32_t API_EXPORT NormalizeMask(uint32_t mask);
std::vector<UriPermission> API_EXPORT FromMask(uint32_t mask);
std::vector<int32_t> API_EXPORT ToInt32(const std::vector<UriPermission> &permissions);
std::vector<UriPermission> API_EXPORT FromInt32(const std::vector<int32_t> &permissions);
} // namespace UriPermissionUtil
} // namespace UDMF
} // namespace OHOS
#endif //URI_PERMISSION_UTIL_H