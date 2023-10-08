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

#ifndef UDMF_UTD_CONFIG_H
#define UDMF_UTD_CONFIG_H
#include <string>
#include <vector>
#include <set>
#include <map>
#include <cstdint>
#include "visibility.h"
#include "cJSON.h"
#include "type_descriptor.h"
namespace OHOS {
namespace UDMF {
class UtdConfig {
public:
    using json = cJSON;
    static UtdConfig &GetInstance();
    std::map<std::string, TypeDescriptor>& GetDescriptorsFromConfig();

private:
    static constexpr const char *CONF_PATH = "/system/etc/distributeddata/conf/utd";
    UtdConfig();
    ~UtdConfig();
    int32_t ParseJsonData();
    std::set<std::string> GetBelongingToTypes(const json &node);
    std::string GetStringValue(const json &node, const std::string &nodeName);
    std::vector<std::string> GetStringArrayValue(const json &node, const std::string &nodeName);
    std::map<std::string, TypeDescriptor> utdConfig_;
    std::string file_;
};
} // namespace UDMF
} // namespace OHOS
#endif // UDMF_UTD_CONFIG_H
