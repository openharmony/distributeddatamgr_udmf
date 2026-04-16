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
#define LOG_TAG "URI_PERMISSION_UTIL_H"

#include "uri_permission_util.h"

namespace OHOS {
namespace UDMF {
namespace UriPermissionUtil {
bool IsValid(int32_t permission)
{
    return permission >= static_cast<int32_t>(UriPermission::NONE) &&
        permission <= static_cast<int32_t>(UriPermission::PERSIST);
}

uint32_t ToMask(UriPermission permission)
{
    switch (permission) {
        case UriPermission::READ:
            return READ_FLAG;
        case UriPermission::WRITE:
            return WRITE_FLAG;
        case UriPermission::PERSIST:
            return PERSIST_FLAG;
        default:
            return 0;
    }
}

uint32_t ToMask(const std::vector<UriPermission> &permissions)
{
    uint32_t mask = 0;
    for (const auto &permission : permissions) {
        mask |= ToMask(permission);
    }
    return NormalizeMask(mask);
}

uint32_t ToMask(const std::vector<int32_t> &permissions)
{
    uint32_t mask = 0;
    for (const auto &permission : permissions) {
        if (!IsValid(permission)) {
            continue;
        }
        mask |= ToMask(static_cast<UriPermission>(permission));
    }
    return NormalizeMask(mask);
}

uint32_t NormalizeMask(uint32_t mask)
{
    if ((mask & (READ_FLAG | WRITE_FLAG)) == 0) {
        mask &= ~PERSIST_FLAG;
    }
    return mask;
}

std::vector<UriPermission> FromMask(uint32_t mask)
{
    std::vector<UriPermission> permissions;
    mask = NormalizeMask(mask);
    if ((mask & READ_FLAG) != 0) {
        permissions.emplace_back(UriPermission::READ);
    }
    if ((mask & WRITE_FLAG) != 0) {
        permissions.emplace_back(UriPermission::WRITE);
    }
    if ((mask & PERSIST_FLAG) != 0) {
        permissions.emplace_back(UriPermission::PERSIST);
    }
    if (permissions.empty()) {
        permissions.emplace_back(UriPermission::NONE);
    }
    return permissions;
}

std::vector<int32_t> ToInt32(const std::vector<UriPermission> &permissions)
{
    std::vector<int32_t> values;
    values.reserve(permissions.size());
    for (const auto &permission : permissions) {
        values.emplace_back(static_cast<int32_t>(permission));
    }
    return values;
}

std::vector<UriPermission> FromInt32(const std::vector<int32_t> &permissions)
{
    std::vector<UriPermission> values;
    values.reserve(permissions.size());
    for (const auto &permission : permissions) {
        if (!IsValid(permission)) {
            values.emplace_back(UriPermission::NONE);
            continue;
        }
        values.emplace_back(static_cast<UriPermission>(permission));
    }
    return values;
}
} // namespace UriPermissionUtil
} // namespace UDMF
} // namespace OHOS
