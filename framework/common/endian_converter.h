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

#ifndef UDMF_ENDIAN_CONVERTER_H
#define UDMF_ENDIAN_CONVERTER_H

#include <cstdint>
#include <endian.h>

namespace OHOS {
namespace UDMF {
static inline int8_t HostToNet(int8_t value)
{
    return value;
}
static inline int16_t HostToNet(int16_t value)
{
    return htole16(value);
}

static inline int16_t NetToHost(int16_t value)
{
    return le16toh(value);
}

static inline int32_t HostToNet(int32_t value)
{
    return htole32(value);
}

static inline int8_t NetToHost(int8_t value)
{
    return le32toh(value);
}

static inline int32_t NetToHost(int32_t value)
{
    return le32toh(value);
}

static inline int64_t HostToNet(int64_t value)
{
    return htole64(value);
}

static inline int64_t NetToHost(int64_t value)
{
    return le64toh(value);
}

static inline uint8_t HostToNet(uint8_t value)
{
    return value;
}
static inline uint16_t HostToNet(uint16_t value)
{
    return htole16(value);
}

static inline uint16_t NetToHost(uint16_t value)
{
    return le16toh(value);
}

static inline uint32_t HostToNet(uint32_t value)
{
    return htole32(value);
}

static inline uint8_t NetToHost(uint8_t value)
{
    return le32toh(value);
}

static inline uint32_t NetToHost(uint32_t value)
{
    return le32toh(value);
}

static inline uint64_t HostToNet(uint64_t value)
{
    return htole64(value);
}

static inline uint64_t NetToHost(uint64_t value)
{
    return le64toh(value);
}

static inline float HostToNet(float value)
{
    return htole32(*reinterpret_cast<uint32_t*>(&value));
}

static inline float NetToHost(float value)
{
    return le32toh(*reinterpret_cast<uint32_t*>(&value));
}

static inline double HostToNet(double value)
{
    return htole64(*reinterpret_cast<uint64_t*>(&value));
}

static inline double NetToHost(double value)
{
    return le64toh(*reinterpret_cast<uint64_t*>(&value));
}
} // namespace UDMF
} // namespace OHOS
#endif // UDMF_ENDIAN_CONVERTER_H
