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
#include "utd_config.h"
#include <fstream>
#include <cJSON.h>
#include "error_code.h"
#include "logger.h"
namespace OHOS {
namespace UDMF {
#ifndef GET_NAME
#define GET_NAME(value) #value
#endif

UtdConfig::UtdConfig()
    : file_(std::string(CONF_PATH) + "/utd_config.json")
{
}

UtdConfig::~UtdConfig()
{
}

UtdConfig &UtdConfig::GetInstance()
{
    static UtdConfig utdConfig;
    return utdConfig;
}

int32_t UtdConfig::ParseJsonData()
{
    std::string jsonStr;
    std::ifstream fin(file_);
    while (fin.good()) {
        std::string line;
        std::getline(fin, line);
        jsonStr += line;
    }
    // parse utd_config.json to TypeDescriptor obj.
    cJSON* jsonRoot = cJSON_ParseWithLength(jsonStr.c_str(), jsonStr.size());
    if (jsonRoot != NULL && cJSON_IsObject(jsonRoot)) {
        cJSON *subNode = cJSON_GetObjectItem(jsonRoot, GET_NAME(utdConfig));
        int jsonSize = cJSON_GetArraySize(subNode);
        for (int i = 0; i < jsonSize; i++) {
            cJSON *node = cJSON_GetArrayItem(subNode, i);
            std::string typeId = GetStringValue(*node, GET_NAME(typeId));
            TypeDescriptor descriptor(typeId);
            descriptor.SetBelongingToTypes(GetBelongingToTypes(*node));
            descriptor.SetIconFile(GetStringValue(*node, GET_NAME(iconFile)));
            descriptor.SetDescription(GetStringValue(*node, GET_NAME(description)));
            descriptor.SetReferenceURL(GetStringValue(*node, GET_NAME(referenceURL)));
            descriptor.SetFilenameExtensions(GetStringArrayValue(*node, GET_NAME(filenameExtensions)));
            descriptor.SetMimeTypes(GetStringArrayValue(*node, GET_NAME(mimeTypes)));
            utdConfig_.insert({typeId, descriptor});
        }
    } else {
        cJSON_Delete(jsonRoot);
        return -1;
    }
    cJSON_Delete(jsonRoot);
    return 0;
}

std::set<std::string> UtdConfig::GetBelongingToTypes(const json &node)
{
    std::vector<std::string> belongingToTypes = GetStringArrayValue(node,  GET_NAME(belongingToTypes));
    std::set<std::string> types(belongingToTypes.begin(), belongingToTypes.end());
    return types;
}

std::string UtdConfig::GetStringValue(const json &node, const std::string &nodeName)
{
    std::string stringValue;
    if (!cJSON_IsNull(&node) && cJSON_IsObject(&node) && cJSON_HasObjectItem(&node, nodeName.c_str())) {
        cJSON *subNode = cJSON_GetObjectItem(&node, nodeName.c_str());
        stringValue = cJSON_GetStringValue(subNode);
    }
    return stringValue;
}

std::vector<std::string> UtdConfig::GetStringArrayValue(const json &node, const std::string &nodeName)
{
    std::vector<std::string> value;
    if (!cJSON_IsNull(&node) && cJSON_IsObject(&node) && cJSON_HasObjectItem(&node, nodeName.c_str())) {
        cJSON *subNode = cJSON_GetObjectItem(&node, nodeName.c_str());
        if (cJSON_IsNull(subNode) || !cJSON_IsArray(subNode)) {
            LOG_WARN(UDMF_CLIENT, "maybe null node, nodeName = %{public}s.", nodeName.c_str());
        }
        for (int i = 0; i < cJSON_GetArraySize(subNode); i++) {
            value.emplace_back(cJSON_GetStringValue(cJSON_GetArrayItem(subNode, i)));
        }
    }
    return value;
}

std::map<std::string, TypeDescriptor> &UtdConfig::GetDescriptorsFromConfig()
{
    if (utdConfig_.empty()) {
        int ret = ParseJsonData();
        LOG_WARN(UDMF_CLIENT, "utdconfig missing, ret = %{public}d.", ret);
    }
    return utdConfig_;
}
} // namespace UDMF
} // namespace OHOS
