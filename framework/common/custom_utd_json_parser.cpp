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
#define LOG_TAG "CustomUtdJsonParser"
#include "custom_utd_json_parser.h"
#include "logger.h"
namespace OHOS {
namespace UDMF {
constexpr const char* TYPEID = "typeId";
constexpr const char* BELONGINGTOTYPES = "belongingToTypes";
constexpr const char* FILE_NAME_EXTENSTENSIONS = "filenameExtensions";
constexpr const char* MIME_TYPES = "mimeTypes";
constexpr const char* DESCRIPTION = "description";
constexpr const char* REFERENCE_URL = "referenceURL";
constexpr const char* ICON_FILE = "iconFile";
constexpr const char* OWNER = "ownerBundle";
constexpr const char* INSTALLERS = "installerBundles";
constexpr const size_t MAX_UTD_CUSTOM_SIZE = 1024 * 1024;
constexpr const size_t JSON_DUMP_INDENT = 4;

CustomUtdJsonParser::CustomUtdJsonParser()
{
}

CustomUtdJsonParser::~CustomUtdJsonParser()
{
}

bool CustomUtdJsonParser::ParseStoredCustomUtdJson(const std::string &jsonData,
                                                   std::vector<TypeDescriptorCfg> &typesCfg)
{
    if (jsonData.empty()) {
        return false;
    }
    auto jsonRoot = json::parse(jsonData, nullptr, false);
    if (jsonRoot.is_discarded()) {
        LOG_ERROR(UDMF_CLIENT, "Failed to parse JSON: invalid format.");
        return false;
    }
    if (!jsonRoot.is_object()) {
        LOG_ERROR(UDMF_CLIENT, "Parsed JSON root is not an object");
        return false;
    }
    if (!GetTypeDescriptors(jsonRoot, UTD_CUSTOM, typesCfg)) {
        LOG_ERROR(UDMF_CLIENT, "Failed to get type descriptors");
        return false;
    }
    return true;
}

bool CustomUtdJsonParser::ParseUserCustomUtdJson(const std::string &jsonData,
                                                 std::vector<TypeDescriptorCfg> &typesDeclarations,
                                                 std::vector<TypeDescriptorCfg> &typesReference)
{
    if (jsonData.empty()) {
        return false;
    }
    auto jsonRoot = json::parse(jsonData, nullptr, false);
    if (jsonRoot.is_discarded()) {
        LOG_ERROR(UDMF_CLIENT, "Failed to parse JSON: invalid format.");
        return false;
    }
    if (!jsonRoot.is_object()) {
        LOG_ERROR(UDMF_CLIENT, "Parsed JSON root is not an object");
        return false;
    }
    if (!GetTypeDescriptors(jsonRoot, UTD_CUSTOM_DECLARATION, typesDeclarations) ||
        !GetTypeDescriptors(jsonRoot, UTD_CUSTOM_REFERENCE, typesReference)) {
        LOG_ERROR(UDMF_CLIENT, "Failed to get type descriptors");
        return false;
    }
    LOG_INFO(UDMF_CLIENT, "DeclarationsSize:%{public}zu, ReferenceSize:%{public}zu",
             typesDeclarations.size(), typesReference.size());
    return true;
}

bool CustomUtdJsonParser::ConvertUtdCfgsToJson(const std::vector<TypeDescriptorCfg> &typesCfg, std::string &jsonData)
{
    json root;
    json customUtds = json::array();

    for (const auto &utdTypeCfg : typesCfg) {
        json item;
        item[TYPEID] = utdTypeCfg.typeId;
        item[BELONGINGTOTYPES] = utdTypeCfg.belongingToTypes;
        item[FILE_NAME_EXTENSTENSIONS] = utdTypeCfg.filenameExtensions;
        item[MIME_TYPES] = utdTypeCfg.mimeTypes;
        item[DESCRIPTION] = utdTypeCfg.description;
        item[REFERENCE_URL] = utdTypeCfg.referenceURL;
        item[ICON_FILE] = utdTypeCfg.iconFile;
        item[OWNER] = utdTypeCfg.ownerBundle;
        item[INSTALLERS] = utdTypeCfg.installerBundles;
        customUtds.push_back(std::move(item));
    }
    
    root[UTD_CUSTOM] = customUtds;
    jsonData = root.dump(JSON_DUMP_INDENT);
    return true;
}

bool CustomUtdJsonParser::GetTypeDescriptors(const json &jsonRoot, const std::string &nodeName,
                                             std::vector<TypeDescriptorCfg> &typesCfg)
{
    if (!jsonRoot.contains(nodeName)) {
        return true;
    }
    if (!jsonRoot[nodeName].is_array()) {
        LOG_ERROR(UDMF_CLIENT, "subNode %{public}s is null or not array.", nodeName.c_str());
        return false;
    }
    const auto &subNode = jsonRoot[nodeName];
    if (subNode.size() > MAX_UTD_CUSTOM_SIZE) {
        LOG_ERROR(UDMF_CLIENT, "itemNum is too large");
        return false;
    }

    for (const auto &item : subNode) {
        if (!item.is_object()) {
            LOG_ERROR(UDMF_CLIENT, "item is not object.");
            return false;
        }

        TypeDescriptorCfg typeCfg;
        typeCfg.typeId = GetStringValue(&item, TYPEID);
        typeCfg.belongingToTypes = GetStringArrayValue(&item, BELONGINGTOTYPES);
        typeCfg.filenameExtensions = GetStringArrayValue(&item, FILE_NAME_EXTENSTENSIONS);
        typeCfg.mimeTypes = GetStringArrayValue(&item, MIME_TYPES);
        typeCfg.description = GetStringValue(&item, DESCRIPTION);
        typeCfg.referenceURL = GetStringValue(&item, REFERENCE_URL);
        typeCfg.iconFile = GetStringValue(&item, ICON_FILE);
        typeCfg.ownerBundle = GetStringValue(&item, OWNER);
        auto installers = GetStringArrayValue(&item, INSTALLERS);
        typeCfg.installerBundles.insert(installers.begin(), installers.end());
        typesCfg.push_back(std::move(typeCfg));
    }
    return true;
}

std::string CustomUtdJsonParser::GetStringValue(const json *node, const std::string &nodeName)
{
    if (!node->is_object()) {
        return "";
    }
    for (auto it = node->begin(); it != node->end(); ++it) {
        if (strcasecmp(it.key().c_str(), nodeName.c_str()) == 0) {
            return it.value().is_string() ? it.value().get<std::string>() : "";
        }
    }
    return "";
}

std::vector<std::string> CustomUtdJsonParser::GetStringArrayValue(const json *node, const std::string &nodeName)
{
    std::vector<std::string> result;
    if (!node->is_object()) {
        return result;
    }
    for (auto it = node->begin(); it != node->end(); ++it) {
        if (strcasecmp(it.key().c_str(), nodeName.c_str()) != 0 || !it.value().is_array()) {
            continue;
        }
        for (const auto &element : it.value()) {
            if (element.is_string()) {
                result.push_back(element.get<std::string>());
            }
        }
    }
    return result;
}
} // namespace UDMF
} // namespace OHOS