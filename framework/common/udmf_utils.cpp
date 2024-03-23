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
namespace OHOS {
namespace UDMF {
namespace UTILS {
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
} // namespace UTILS
} // namespace UDMF
} // namespace OHOS