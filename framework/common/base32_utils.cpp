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

#include "base32_utils.h"

#include <string>

namespace OHOS {
namespace UDMF {
static char BASE32_CHARS[33] = "abcdefghijklmnopqrstuvwxyz234567";

static constexpr const uint32_t CHAR_ARRAY_LENGTH = 5;
static constexpr const uint32_t ASCII_CHAR_LENGTH = 8;

std::string Base32::Encode(const std::string &input)
{
    std::string result;
    uint32_t val = 0;
    uint32_t valbits = 0;
    for (char c : input) {
        val = (val << ASCII_CHAR_LENGTH) + c;
        valbits += ASCII_CHAR_LENGTH;
        while (valbits >= CHAR_ARRAY_LENGTH) {
            valbits -= CHAR_ARRAY_LENGTH;
            uint32_t index = (val >> valbits) & 0x1f;  // the 31st place.
            result += BASE32_CHARS[index];
        }
    }
    if (valbits > 0) {
        val <<= (CHAR_ARRAY_LENGTH - valbits);
        uint32_t index = val & 0x1f;  // the 31st place.
        result += BASE32_CHARS[index];
    }
    return result;
}

std::string Base32::Decode(const std::string &input)
{
    std::string result;
    uint32_t val = 0;
    uint32_t valbits = 0;
    for (char c : input) {
        if (c >= 'a' && c <= 'z') {
            val = (val << CHAR_ARRAY_LENGTH) + (c - 'a');
            valbits += CHAR_ARRAY_LENGTH;
        } else if (c >= '2' && c <= '7') {
            val = (val << CHAR_ARRAY_LENGTH) + (c - '2' + 26); // 26 : a-z
            valbits += CHAR_ARRAY_LENGTH;
        }
        if (valbits >= ASCII_CHAR_LENGTH) {
            valbits -= ASCII_CHAR_LENGTH;
            result += static_cast<char>(val >> valbits);
            val &= (1 << valbits) - 1;
        }
    }
    return result;
}

} // namespace UDMF
} // namespace OHOS

