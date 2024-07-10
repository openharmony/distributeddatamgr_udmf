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
#define LOG_TAG "EndianConverter"
#include "endian_converter.h"

#include "error_code.h"
#include "logger.h"
#include "securec.h"

namespace OHOS {
namespace UDMF {
float HostToNet(float value)
{
    uint32_t temp;
    auto err = memcpy_s(&temp, sizeof(temp), &value, sizeof(temp));
    if (err != E_OK) {
        LOG_ERROR(UDMF_KITS_NAPI, "memcpy_s error: %{public}d", err);
    }
    temp = htole32(temp);
    err = memcpy_s(&value, sizeof(value), &temp, sizeof(value));
    if (err != E_OK) {
        LOG_ERROR(UDMF_KITS_NAPI, "memcpy_s error: %{public}d", err);
    }
    return value;
}

float NetToHost(float value)
{
    uint32_t temp;
    auto err = memcpy_s(&temp, sizeof(temp), &value, sizeof(temp));
    if (err != E_OK) {
        LOG_ERROR(UDMF_KITS_NAPI, "memcpy_s error: %{public}d", err);
    }
    temp = le32toh(temp);
    err = memcpy_s(&value, sizeof(value), &temp, sizeof(value));
    if (err != E_OK) {
        LOG_ERROR(UDMF_KITS_NAPI, "memcpy_s error: %{public}d", err);
    }
    return value;
}

double HostToNet(double value)
{
    uint64_t temp;
    auto err = memcpy_s(&temp, sizeof(temp), &value, sizeof(temp));
    if (err != E_OK) {
        LOG_ERROR(UDMF_KITS_NAPI, "memcpy_s error: %{public}d", err);
    }
    temp = htole64(temp);
    err = memcpy_s(&value, sizeof(value), &temp, sizeof(value));
    if (err != E_OK) {
        LOG_ERROR(UDMF_KITS_NAPI, "memcpy_s error: %{public}d", err);
    }
    return value;
}

double NetToHost(double value)
{
    uint64_t temp;
    auto err = memcpy_s(&temp, sizeof(temp), &value, sizeof(temp));
    if (err != E_OK) {
        LOG_ERROR(UDMF_KITS_NAPI, "memcpy_s error: %{public}d", err);
    }
    temp = le64toh(temp);
    err = memcpy_s(&value, sizeof(value), &temp, sizeof(value));
    if (err != E_OK) {
        LOG_ERROR(UDMF_KITS_NAPI, "memcpy_s error: %{public}d", err);
    }
    return value;
}
} // namespace UDMF
} // namespace OHOS