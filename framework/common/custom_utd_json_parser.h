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

#ifndef UDMF_CUSTOM_UTD_JSON_PARSER_H
#define UDMF_CUSTOM_UTD_JSON_PARSER_H
#include <nlohmann/json.hpp>

#include "utd_common.h"
namespace OHOS {
namespace UDMF {
class CustomUtdJsonParser {
public:
    using json = nlohmann::json;
    CustomUtdJsonParser();
    ~CustomUtdJsonParser();
    bool ParseStoredCustomUtdJson(const std::string &jsonData, std::vector<TypeDescriptorCfg> &typesCfg);
    bool ParseUserCustomUtdJson(const std::string &jsonData, std::vector<TypeDescriptorCfg> &typesDeclarations,
                          std::vector<TypeDescriptorCfg> &typesReference);
    bool ConvertUtdCfgsToJson(const std::vector<TypeDescriptorCfg> &typesCfg, std::string &jsonData);
    bool GetTypeDescriptors(const json &jsonRoot, const std::string &nodeName,
                            std::vector<TypeDescriptorCfg> &typesCfg);

private:
    bool GetTypeDescriptorsFromArray(const json &subNode, std::vector<TypeDescriptorCfg> &typesCfg);
    bool GetEncodedTypeDescriptors(const json &subNode, std::vector<TypeDescriptorCfg> &typesCfg);
    bool GetEncodedTypeDescriptor(const json &strings, const json &record, TypeDescriptorCfg &typeCfg);
    std::string GetEncodedString(const json &strings, const json &indexNode);
    std::vector<std::string> GetEncodedStringArray(const json &strings, const json &indexNode);
    void SetEncodedStringArray(TypeDescriptorCfg &typeCfg, std::vector<std::string> &&values);
    void SetEncodedStringValue(TypeDescriptorCfg &typeCfg, std::string &&value);
    std::string GetStringValue(const json *node, const std::string &nodeName);
    std::vector<std::string> GetStringArrayValue(const json *node, const std::string &nodeName);
};
} // namespace UDMF
} // namespace OHOS
#endif // UDMF_CUSTOM_UTD_JSON_PARSER_H
