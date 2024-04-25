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
#include <fstream>
#include <cJSON.h>
#include "error_code.h"
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

    cJSON* jsonRoot = cJSON_Parse(jsonData.c_str());
    if (jsonRoot != NULL && cJSON_IsObject(jsonRoot)) {
        GetTypeDescriptors(*jsonRoot, UTD_CUSTOM, typesCfg);
    }
    cJSON_Delete(jsonRoot);
    return true;
}

bool CustomUtdJsonParser::ParseUserCustomUtdJson(const std::string &jsonData,
                                                 std::vector<TypeDescriptorCfg> &typesDeclarations,
                                                 std::vector<TypeDescriptorCfg> &typesReference)
{
    if (jsonData.empty()) {
        return false;
    }
    // parse utd-adt.json to TypeDescriptorCfg obj
    cJSON* jsonRoot = cJSON_Parse(jsonData.c_str());
    if (jsonRoot != NULL && cJSON_IsObject(jsonRoot)) {
        GetTypeDescriptors(*jsonRoot, UTD_CUSTOM_DECLAEEARION, typesDeclarations);
        GetTypeDescriptors(*jsonRoot, UTD_CUSTOM_REFERENCE, typesReference);
    }
    cJSON_Delete(jsonRoot);
    return true;
}

bool CustomUtdJsonParser::ConvertUtdCfgsToJson(const std::vector<TypeDescriptorCfg> &typesCfg, std::string &jsonData)
{
    json* root = cJSON_CreateObject();
    json* CustomUTDs = cJSON_CreateArray();
    for (auto utdTypeCfg : typesCfg) {
        json* jsonItem = cJSON_CreateObject();
        cJSON_AddStringToObject(jsonItem, TYPEID, utdTypeCfg.typeId.c_str());
        std::vector<std::string> belongingToTypes(utdTypeCfg.belongingToTypes.begin(),
                                                  utdTypeCfg.belongingToTypes.end());
        AddJsonStringArray(belongingToTypes, BELONGINGTOTYPES, *jsonItem);
        AddJsonStringArray(utdTypeCfg.filenameExtensions, FILE_NAME_EXTENSTENSIONS, *jsonItem);
        AddJsonStringArray(utdTypeCfg.mimeTypes, MIME_TYPES, *jsonItem);
        cJSON_AddStringToObject(jsonItem, DESCRIPTION, utdTypeCfg.description.c_str());
        cJSON_AddStringToObject(jsonItem, REFERENCE_URL, utdTypeCfg.referenceURL.c_str());
        cJSON_AddStringToObject(jsonItem, ICON_FILE, utdTypeCfg.iconFile.c_str());
        cJSON_AddStringToObject(jsonItem, OWNER, utdTypeCfg.ownerBundle.c_str());
        std::vector<std::string> installerBundles(utdTypeCfg.installerBundles.begin(),
                                                  utdTypeCfg.installerBundles.end());
        AddJsonStringArray(installerBundles, INSTALLERS, *jsonItem);

        cJSON_AddItemToArray(CustomUTDs, jsonItem);
    }
    cJSON_AddItemToObject(root, UTD_CUSTOM, CustomUTDs);

    jsonData = cJSON_Print(root);
    cJSON_Delete(root);
    LOG_DEBUG(UDMF_CLIENT, "ConvertUtdCfgsToJson, jsonData size: %{public}zu.", jsonData.length());
    return true;
}

bool CustomUtdJsonParser::AddJsonStringArray(const std::vector<std::string> &datas, const std::string &nodeName,
                                             json &node)
{
    json *arrayNode = cJSON_AddArrayToObject(&node, nodeName.c_str());
    for (const auto &data : datas) {
        json* item = cJSON_CreateString(data.c_str());
        cJSON_AddItemToArray(arrayNode, item);
    }
    return true;
}

bool CustomUtdJsonParser::GetTypeDescriptors(const json &jsonRoot, const std::string &nodeName,
                                             std::vector<TypeDescriptorCfg> &typesCfg)
{
    if (cJSON_HasObjectItem(&jsonRoot, nodeName.c_str())) {
        cJSON *subNode = cJSON_GetObjectItem(&jsonRoot, nodeName.c_str());
        int itemNum = cJSON_GetArraySize(subNode);
        for (int i = 0; i < itemNum; i++) {
            cJSON *node = cJSON_GetArrayItem(subNode, i);
            TypeDescriptorCfg typeCfg;
            typeCfg.typeId = GetStringValue(*node, TYPEID);
            std::vector<std::string> belongingToTypes = GetStringArrayValue(*node, BELONGINGTOTYPES);
            typeCfg.belongingToTypes.insert(belongingToTypes.begin(), belongingToTypes.end());
            typeCfg.filenameExtensions = GetStringArrayValue(*node, FILE_NAME_EXTENSTENSIONS);
            typeCfg.mimeTypes = GetStringArrayValue(*node, MIME_TYPES);
            typeCfg.description = GetStringValue(*node, DESCRIPTION);
            typeCfg.referenceURL = GetStringValue(*node, REFERENCE_URL);
            typeCfg.iconFile = GetStringValue(*node, ICON_FILE);
            typeCfg.ownerBundle = GetStringValue(*node, OWNER);
            std::vector<std::string> installerBundles = GetStringArrayValue(*node, INSTALLERS);
            typeCfg.installerBundles.insert(installerBundles.begin(), installerBundles.end());
            typesCfg.push_back(typeCfg);
        }
    }
    return true;
}

std::string CustomUtdJsonParser::GetStringValue(const json &node, const std::string &nodeName)
{
    std::string value;
    if (!cJSON_IsNull(&node) && cJSON_IsObject(&node) && cJSON_HasObjectItem(&node, nodeName.c_str())) {
        cJSON *subNode = cJSON_GetObjectItem(&node, nodeName.c_str());
        if (cJSON_IsString(subNode)) {
            value = cJSON_GetStringValue(subNode);
        }
    }
    return value;
}

std::vector<std::string> CustomUtdJsonParser::GetStringArrayValue(const json &node, const std::string &nodeName)
{
    std::vector<std::string> values;
    if (!cJSON_IsNull(&node) && cJSON_IsObject(&node) && cJSON_HasObjectItem(&node, nodeName.c_str())) {
        cJSON *subNode = cJSON_GetObjectItem(&node, nodeName.c_str());
        if (cJSON_IsNull(subNode) || !cJSON_IsArray(subNode)) {
            return values;
        }
        for (int i = 0; i < cJSON_GetArraySize(subNode); i++) {
            json *item = cJSON_GetArrayItem(subNode, i);
            if (cJSON_IsString(item)) {
                values.emplace_back(cJSON_GetStringValue(item));
            }
        }
    }
    return values;
}
} // namespace UDMF
} // namespace OHOS