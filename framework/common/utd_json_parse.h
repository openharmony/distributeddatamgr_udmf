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

#ifndef UDMF_UTD_JSON_PARSE_H
#define UDMF_UTD_JSON_PARSE_H
#include <string>
#include <vector>
#include <set>
#include <map>
#include <cstdint>
#include "visibility.h"
#include "cJSON.h"
#include "utd_common.h"
namespace OHOS {
namespace UDMF {
class UtdJsonParse {
public:
    using json = cJSON;
    UtdJsonParse();
    ~UtdJsonParse();
    int32_t ParseJsonData(const std::string &jsonData, std::vector<TypeDescriptorCfg> &typesCfg);
    int32_t ParseJsonData(const std::string &jsonData, std::vector<TypeDescriptorCfg> &typesDeclarations,
                          std::vector<TypeDescriptorCfg> &typesReference);
    int32_t ConvertUtdCustomToStr(std::vector<TypeDescriptorCfg> &typesCfg, std::string &jsonData);

private:
    int32_t ParseJsonDataFromCfg();
    int32_t AddJsonStringArray(std::vector<std::string> &datas, const std::string &attrName, json &node);
    bool GetSubNodeValue(const json &jsonRoot, const std::string &nodeName, std::vector<TypeDescriptorCfg> &typesCfg);
    std::string GetStringValue(const json &subNode, const std::string &nodeName);
    std::vector<std::string> GetStringArrayValue(const json &node, const std::string &nodeName);
    bool GetStringArrayValue(const json &subNode, std::vector<std::string> &value);
};
} // namespace UDMF
} // namespace OHOS
#endif // UDMF_UTD_JSON_PARSE_H