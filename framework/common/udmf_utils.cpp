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
#include "udmf_utils.h"
#include <random>
#include <sstream>

namespace OHOS {
namespace UDMF {
namespace UTILS {
static constexpr int ID_LEN = 32;
static constexpr int MINIMUM = 48;
static constexpr int MAXIMUM = 121;
const char SPECIAL = '^';

std::vector<std::string> StrSplit(std::string str, std::string subStr)
{
    std::vector<std::string> result;
    char *s = str.data();
    char *p = strtok(s, subStr.c_str());
    while (p) {
        std::string tmp = p;
        result.push_back(p);
        p = strtok(NULL, subStr.c_str());
    }
    return result;
}

std::vector<uint8_t> Random(int32_t len, int32_t minimum, int32_t maximum)
{
    std::random_device randomDevice;
    std::uniform_int_distribution<int> distribution(minimum, maximum);
    std::vector<uint8_t> key(len);
    for (int32_t i = 0; i < len; i++) {
        key[i] = static_cast<uint8_t>(distribution(randomDevice));
    }
    return key;
}

std::string GenerateId()
{
    std::vector<uint8_t> randomDevices = Random(ID_LEN, MINIMUM, MAXIMUM);
    std::stringstream idStr;
    for (auto &randomDevice : randomDevices) {
        auto asc = randomDevice;
        asc = asc >= SPECIAL ? asc + 1 : asc;
        idStr << static_cast<uint8_t>(asc);
    }
    return idStr.str();
}
} // namespace UTILS
} // namespace UDMF
} // namespace OHOS