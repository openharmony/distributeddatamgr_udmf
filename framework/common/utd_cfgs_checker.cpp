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
#define LOG_TAG "UtdCfgsChecker"
#include "utd_cfgs_checker.h"

#include <vector>
#include <regex>
#include "utd_graph.h"
#include "logger.h"

namespace OHOS {
namespace UDMF {
constexpr const char *TYPE_ID_REGEX = "[a-zA-Z0-9/.-]+$";
constexpr const char FILE_EXTENSION_PREFIX = '.';
constexpr const int32_t MAX_UTD_SIZE = 50;

UtdCfgsChecker::UtdCfgsChecker()
{
}

UtdCfgsChecker::~UtdCfgsChecker()
{
}

UtdCfgsChecker &UtdCfgsChecker::GetInstance()
{
    static auto instance = new UtdCfgsChecker();
    return *instance;
}

bool UtdCfgsChecker::CheckTypeDescriptors(CustomUtdCfgs &typeCfgs, const std::vector<TypeDescriptorCfg> &presetCfgs,
    const std::vector<TypeDescriptorCfg> &customCfgs, const std::string &bundleName)
{
    if (!CheckTypesFormat(typeCfgs, bundleName)) {
        LOG_ERROR(UDMF_CLIENT, "CheckTypesFormat not pass, bundleName: %{public}s.", bundleName.c_str());
        return false;
    }
    if (!CheckTypesRelation(typeCfgs, presetCfgs, customCfgs)) {
        LOG_ERROR(UDMF_CLIENT, "CheckTypesRelation not pass, bundleName: %{public}s.", bundleName.c_str());
        return false;
    }
    return true;
}

bool UtdCfgsChecker::CheckTypesFormat(CustomUtdCfgs &typeCfgs, const std::string &bundleName)
{
    for (auto declarationType: typeCfgs.first) {
        if (!std::regex_match(declarationType.typeId, std::regex(bundleName + TYPE_ID_REGEX))) {
            LOG_ERROR(UDMF_CLIENT, "Declaration typeId check failed, id: %{public}s, bundleName: %{public}s.",
                declarationType.typeId.c_str(), bundleName.c_str());
            return false;
        }
    }
    for (auto referenceTypes: typeCfgs.second) {
        if (!std::regex_match(referenceTypes.typeId, std::regex(TYPE_ID_REGEX))) {
            LOG_ERROR(UDMF_CLIENT, "Reference typeId check failed, id: %{public}s, bundleName: %{public}s.",
                referenceTypes.typeId.c_str(), bundleName.c_str());
            return false;
        }
    }
    std::vector<TypeDescriptorCfg> inputTypeCfgs;
    if (!typeCfgs.first.empty()) {
        inputTypeCfgs.insert(inputTypeCfgs.end(), typeCfgs.first.begin(), typeCfgs.first.end());
    }
    if (!typeCfgs.second.empty()) {
        inputTypeCfgs.insert(inputTypeCfgs.end(), typeCfgs.second.begin(), typeCfgs.second.end());
    }
    for (TypeDescriptorCfg &typeCfg : inputTypeCfgs) {
        for (std::string filenames : typeCfg.filenameExtensions) {
            if (!(filenames[0] == FILE_EXTENSION_PREFIX)) {
                LOG_ERROR(UDMF_CLIENT, "Extension not valid, extension: %{public}s, bundleName: %{public}s.",
                    filenames.c_str(), bundleName.c_str());
                return false;
            }
        }
        if (typeCfg.belongingToTypes.empty()) {
            LOG_ERROR(UDMF_CLIENT, "BelongingToTypes can not be empty, bundleName: %{public}s.", bundleName.c_str());
            return false;
        }
        for (std::string mimeType : typeCfg.mimeTypes) {
            if (mimeType.empty()) {
                LOG_ERROR(UDMF_CLIENT, "mimeType can not be an empty string, typeId: %{public}s.",
                    typeCfg.typeId.c_str());
                return false;
            }
        }
    }
    return true;
}

bool UtdCfgsChecker::CheckTypesRelation(CustomUtdCfgs &typeCfgs, const std::vector<TypeDescriptorCfg> &presetCfgs,
    const std::vector<TypeDescriptorCfg> &customCfgs)
{
    std::vector<TypeDescriptorCfg> inputTypeCfgs;
    if (!typeCfgs.first.empty()) {
        inputTypeCfgs.insert(inputTypeCfgs.end(), typeCfgs.first.begin(), typeCfgs.first.end());
    }
    if (!typeCfgs.second.empty()) {
        inputTypeCfgs.insert(inputTypeCfgs.end(), typeCfgs.second.begin(), typeCfgs.second.end());
    }
    std::vector<std::string> typeIds;
    for (auto &inputTypeCfg: inputTypeCfgs) {
        typeIds.push_back(inputTypeCfg.typeId);
    }
    if (typeIds.size() > MAX_UTD_SIZE) {
        LOG_ERROR(UDMF_CLIENT, "Create more UTDs than limit.");
        return false;
    }
    for (auto &presetCfg: presetCfgs) {
        typeIds.push_back(presetCfg.typeId);
    }
    if (std::set<std::string>(typeIds.begin(), typeIds.end()).size() != typeIds.size()) {
        LOG_ERROR(UDMF_CLIENT, "Find duplicated typeIds.");
        return false;
    }
    if (!CheckBelongingToTypes(inputTypeCfgs, presetCfgs)) {
        LOG_ERROR(UDMF_CLIENT, "BelongingToType check failed.");
        return false;
    }
    if (!CanConstructDAG(typeCfgs, presetCfgs, customCfgs)) {
        LOG_ERROR(UDMF_CLIENT, "Can not construct DAG.");
        return false;
    }
    return true;
}

bool UtdCfgsChecker::CheckBelongingToTypes(const std::vector<TypeDescriptorCfg> &typeCfgs,
    const std::vector<TypeDescriptorCfg> &presetCfgs)
{
    std::vector<std::string> typeIds;
    for (auto &typeCfg: typeCfgs) {
        typeIds.push_back(typeCfg.typeId);
    }
    for (auto &presetCfg: presetCfgs) {
        typeIds.push_back(presetCfg.typeId);
    }
    for (auto &inputCfg : typeCfgs) {
        for (std::string belongingToType : inputCfg.belongingToTypes) {
            if (belongingToType.empty()) {
                LOG_ERROR(UDMF_CLIENT, "BelongingToType can not be an empty string, typeId: %{public}s.",
                    inputCfg.typeId.c_str());
                return false;
            }
            if (inputCfg.typeId == belongingToType) {
                LOG_ERROR(UDMF_CLIENT, "TypeId cannot equals belongingToType, typeId: %{public}s.",
                    inputCfg.typeId.c_str());
                return false;
            }
            if (find(typeIds.begin(), typeIds.end(), belongingToType) == typeIds.end()) {
                LOG_ERROR(UDMF_CLIENT, "BelongingToType can not find in typeids, belongingToType: %{public}s.",
                    belongingToType.c_str());
                return false;
            }
        }
    }
    return true;
}

bool UtdCfgsChecker::CanConstructDAG(CustomUtdCfgs &typeCfgs, const std::vector<TypeDescriptorCfg> &presetCfgs,
    const std::vector<TypeDescriptorCfg> &customCfgs)
{
    std::vector<TypeDescriptorCfg> allTypeCfgs;
    if (!customCfgs.empty()) {
        allTypeCfgs.insert(allTypeCfgs.end(), customCfgs.begin(), customCfgs.end());
    }
    for (TypeDescriptorCfg &declarationType : typeCfgs.first) {
        for (auto iter = allTypeCfgs.begin(); iter != allTypeCfgs.end();) {
            if (iter->typeId == declarationType.typeId) {
                iter = allTypeCfgs.erase(iter);
            } else {
                iter ++;
            }
        }
        allTypeCfgs.push_back(declarationType);
    }
    for (TypeDescriptorCfg &referenceTypes : typeCfgs.second) {
        bool found = false;
        for (auto &typeCfg : allTypeCfgs) {
            if (typeCfg.typeId == referenceTypes.typeId) {
                found = true;
                break;
            }
        }
        if (!found) {
            allTypeCfgs.push_back(referenceTypes);
        }
    }
    if (!presetCfgs.empty()) {
        allTypeCfgs.insert(allTypeCfgs.end(), presetCfgs.begin(), presetCfgs.end());
    }
    if (!allTypeCfgs.empty()) {
        UtdGraph::GetInstance().InitUtdGraph(allTypeCfgs);
        if (UtdGraph::GetInstance().IsDAG()) {
            return true;
        }
    }
    return false;
}
} // namespace UDMF
} // namespace OHOS
