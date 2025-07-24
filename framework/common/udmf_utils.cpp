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
#define LOG_TAG "UdmfUtils"

#include "udmf_utils.h"
#include <random>
#include <sstream>
#include "accesstoken_kit.h"
#include "ipc_skeleton.h"
#include "logger.h"

namespace OHOS {
namespace UDMF {
namespace UTILS {
static constexpr int ID_LEN = 32;
static constexpr int MINIMUM = 48;
static constexpr int MAXIMUM = 121;
constexpr char SPECIAL = '^';

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

bool IsTokenNative()
{
    uint32_t tokenId = IPCSkeleton::GetSelfTokenID();
    if (tokenId == 0) {
        return false;
    }
    auto tokenType = Security::AccessToken::AccessTokenKit::GetTokenTypeFlag(tokenId);
    return tokenType == Security::AccessToken::TypeATokenTypeEnum::TOKEN_NATIVE;
}

bool IsNativeCallingToken()
{
    uint32_t tokenId = IPCSkeleton::GetCallingTokenID();
    if (tokenId == 0) {
        return false;
    }
    auto tokenType = Security::AccessToken::AccessTokenKit::GetTokenTypeFlag(tokenId);
    return tokenType == Security::AccessToken::TypeATokenTypeEnum::TOKEN_NATIVE;
}

std::string GetSequenceKey(const std::string &udKey)
{
    auto pos = udKey.rfind('/');
    if (pos == std::string::npos || pos + 1 >= udKey.length()) {
        LOG_ERROR(UDMF_FRAMEWORK, "Error udKey:%{public}s", udKey.c_str());
        return "";
    }
    return udKey.substr(pos + 1);
}

} // namespace UTILS
} // namespace UDMF
} // namespace OHOS