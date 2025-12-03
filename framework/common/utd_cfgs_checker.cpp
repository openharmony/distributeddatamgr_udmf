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

#include <unordered_set>
#include "utd_graph.h"
#include "logger.h"

namespace OHOS {
namespace UDMF {
constexpr const char *TYPE_ID_REGEX = "[a-zA-Z0-9/.-]+$";
constexpr const char FILE_EXTENSION_PREFIX = '.';
constexpr const int32_t MAX_UTD_SIZE = 50;
constexpr const size_t MAX_UTD_LENGTH = 200;
constexpr const int32_t MAX_TYPEID_SIZE = 127;
constexpr const int32_t MAX_EXTENSION_SIZE = 127;
constexpr const int32_t MAX_MIMETYPE_SIZE = 127;
constexpr const int32_t MAX_DESCRIPTION_SIZE = 255;
constexpr const int32_t MAX_REFERENCE_SIZE = 255;
constexpr const int32_t MAX_ICON_FILE_SIZE = 255;

const std::regex UtdCfgsChecker::typeIdPattern_(TYPE_ID_REGEX);

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

Status UtdCfgsChecker::CheckTypeDescriptors(CustomUtdCfgs &typeCfgs, UtdTypeCategory typeCategory,
    const UtdUpdateContext &context)
{
    if (!CheckTypeCfgsFormat(typeCfgs)) {
        LOG_ERROR(UDMF_CLIENT, "CheckTypeCfgsFormat not pass, bundleName: %{public}s.", context.bundleName.c_str());
        return E_FORMAT_ERROR;
    }
    if (typeCategory == UtdTypeCategory::DYNAMIC_TYPE && !CheckDynamicTypesSize(typeCfgs, context)) {
        LOG_ERROR(UDMF_CLIENT, "CheckDynamicTypesSize not pass, bundleName: %{public}s.", context.bundleName.c_str());
        return E_FORMAT_ERROR;
    }
    auto status = CheckTypeIdsContent(typeCfgs, context.bundleName);
    if (status != E_OK) {
        LOG_ERROR(UDMF_CLIENT, "CheckTypeIdsContent not pass, bundleName: %{public}s, status = %{public}d.",
            context.bundleName.c_str(), status);
        return status;
    }
    if (!CheckTypesRelation(typeCfgs, typeCategory, context)) {
        LOG_ERROR(UDMF_CLIENT, "CheckTypesRelation not pass, bundleName: %{public}s.", context.bundleName.c_str());
        return E_CONTENT_ERROR;
    }
    return E_OK;
}

Status UtdCfgsChecker::CheckTypeIdsContent(CustomUtdCfgs &typeCfgs, const std::string &bundleName)
{
#ifndef CROSS_PLATFORM
    try {
#endif
        for (auto declarationType: typeCfgs.first) {
            if (declarationType.typeId.find(bundleName) != 0) {
                LOG_ERROR(UDMF_CLIENT, "Declaration typeId does not start with bundleName");
                return E_CONTENT_ERROR;
            }
            if (!std::regex_match(declarationType.typeId, typeIdPattern_)) {
                LOG_ERROR(UDMF_CLIENT, "Declaration typeId check failed, bundleName: %{public}s", bundleName.c_str());
                return E_FORMAT_ERROR;
            }
        }
        for (auto referenceTypes: typeCfgs.second) {
            if (!std::regex_match(referenceTypes.typeId, typeIdPattern_)) {
                LOG_ERROR(UDMF_CLIENT, "Reference typeId check failed, bundleName: %{public}s", bundleName.c_str());
                return E_FORMAT_ERROR;
            }
        }
#ifndef CROSS_PLATFORM
    } catch (const std::regex_error& e) {
        LOG_ERROR(UDMF_CLIENT, "catch regex_error, bundleName: %{public}s.", bundleName.c_str());
        return E_FORMAT_ERROR;
    }
#endif
    return E_OK;
}

bool UtdCfgsChecker::CheckTypeCfgsFormat(const CustomUtdCfgs &typeCfgs)
{
    auto allTypes = typeCfgs.first;
    allTypes.insert(allTypes.end(), typeCfgs.second.begin(), typeCfgs.second.end());
    return CheckTypeCfgsSize(allTypes);
}

bool UtdCfgsChecker::CheckTypeCfgsSize(const std::vector<TypeDescriptorCfg> &typeCfgs)
{
    if (typeCfgs.empty() || typeCfgs.size() > MAX_UTD_SIZE) {
        LOG_ERROR(UDMF_CLIENT, "typeCfgs is empty or size exceeds max size");
        return false;
    }
    for (auto &typeCfg : typeCfgs) {
        if (typeCfg.typeId.empty() || typeCfg.typeId.size() > MAX_TYPEID_SIZE) {
            LOG_ERROR(UDMF_CLIENT, "typeId format error");
            return false;
        }
        if (typeCfg.belongingToTypes.empty() || typeCfg.belongingToTypes.size() > MAX_UTD_SIZE) {
            LOG_ERROR(UDMF_CLIENT, "BelongingToTypes format error");
            return false;
        }
        for (auto &typeId : typeCfg.belongingToTypes) {
            if (typeId.empty() || typeId.size() > MAX_TYPEID_SIZE) {
                LOG_ERROR(UDMF_CLIENT, "BelongingToTypes format error");
                return false;
            }
        }
        if (typeCfg.filenameExtensions.size() > MAX_UTD_SIZE || typeCfg.mimeTypes.size() > MAX_UTD_SIZE) {
            LOG_ERROR(UDMF_CLIENT, "length format error");
            return false;
        }
        for (auto &filenames : typeCfg.filenameExtensions) {
            if (filenames.size() <= 1 || filenames[0] != FILE_EXTENSION_PREFIX ||
                filenames.size() > MAX_EXTENSION_SIZE) {
                LOG_ERROR(UDMF_CLIENT, "Extension not valid");
                return false;
            }
        }
        for (auto &mimeType : typeCfg.mimeTypes) {
            if (mimeType.empty() || mimeType.size() > MAX_MIMETYPE_SIZE) {
                LOG_ERROR(UDMF_CLIENT, "mimeType format error");
                return false;
            }
        }
        if (typeCfg.description.size() > MAX_DESCRIPTION_SIZE || typeCfg.referenceURL.size() > MAX_REFERENCE_SIZE ||
            typeCfg.iconFile.size() > MAX_ICON_FILE_SIZE) {
            LOG_ERROR(UDMF_CLIENT, "typeCfg string length error");
            return false;
        }
    }
    return true;
}

bool UtdCfgsChecker::CheckDynamicTypesSize(CustomUtdCfgs &typeCfgs, const UtdUpdateContext &context)
{
    auto dynamicTypesSize = std::count_if(context.installedDynamicUtdCfgs.begin(),
        context.installedDynamicUtdCfgs.end(), [&context](const TypeDescriptorCfg &typeCfg) {
            return typeCfg.ownerBundle == context.bundleName;
        });
    if (static_cast<size_t>(dynamicTypesSize) + typeCfgs.first.size() > MAX_UTD_LENGTH) {
        LOG_ERROR(UDMF_CLIENT, "dynamic types size exceeds max length");
        return false;
    }
    return true;
}

bool UtdCfgsChecker::CheckTypeIdsFormat(const std::vector<std::string> &typeIds)
{
    if (typeIds.empty() || typeIds.size() > MAX_UTD_SIZE) {
        LOG_ERROR(UDMF_CLIENT, "typeIds is empty or size exceeds max size");
        return false;
    }
    for (auto &typeId : typeIds) {
        if (typeId.empty() || typeId.size() > MAX_TYPEID_SIZE) {
            LOG_ERROR(UDMF_CLIENT, "typeId format error");
            return false;
        }
    }
    return true;
}

bool UtdCfgsChecker::CheckTypesRelation(CustomUtdCfgs &typeCfgs,
    UtdTypeCategory typeCategory, const UtdUpdateContext &context)
{
    if (!CheckTypeIdUniqueness(typeCfgs, typeCategory, context)) {
        LOG_ERROR(UDMF_CLIENT, "TypeId uniqueness check failed.");
        return false;
    }

    std::vector<TypeDescriptorCfg> inputTypeCfgs = typeCfgs.first;
    inputTypeCfgs.insert(inputTypeCfgs.end(), typeCfgs.second.begin(), typeCfgs.second.end());
    if (!CheckBelongingToTypes(inputTypeCfgs, context.presetCfgs)) {
        LOG_ERROR(UDMF_CLIENT, "BelongingToType check failed.");
        return false;
    }

    auto installedTypes = context.installedCustomUtdCfgs;
    installedTypes.insert(installedTypes.end(),
        context.installedDynamicUtdCfgs.begin(), context.installedDynamicUtdCfgs.end());
    if (!CanConstructDAG(typeCfgs, context.presetCfgs, installedTypes)) {
        LOG_ERROR(UDMF_CLIENT, "Can not construct DAG.");
        return false;
    }
    return true;
}

bool UtdCfgsChecker::CheckTypeIdUniqueness(const CustomUtdCfgs &typeCfgs,
    UtdTypeCategory typeCategory, const UtdUpdateContext &context)
{
    std::unordered_set<std::string> seenIds;
    for (auto &typeCfg: context.presetCfgs) {
        seenIds.insert(typeCfg.typeId);
    }
    for (auto &typeCfg: context.installedDynamicUtdCfgs) {
        seenIds.insert(typeCfg.typeId);
    }
    for (auto &typeCfg: typeCfgs.second) {
        if (!seenIds.insert(typeCfg.typeId).second) {
            LOG_ERROR(UDMF_CLIENT, "Find duplicated installing typeIds.");
            return false;
        }
    }
    for (auto &typeCfg: context.installedCustomUtdCfgs) {
        // not check reference type while installing static type
        if (typeCategory == UtdTypeCategory::STATIC_TYPE && typeCfg.ownerBundle.empty()) {
            continue;
        }
        seenIds.insert(typeCfg.typeId);
    }
    for (auto &typeCfg: typeCfgs.first) {
        if (!seenIds.insert(typeCfg.typeId).second) {
            LOG_ERROR(UDMF_CLIENT, "Find duplicated installing typeIds.");
            return false;
        }
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
                LOG_ERROR(UDMF_CLIENT, "BelongingToType can not be an empty string");
                return false;
            }
            if (inputCfg.typeId == belongingToType) {
                LOG_ERROR(UDMF_CLIENT, "TypeId cannot equals belongingToType");
                return false;
            }
            if (find(typeIds.begin(), typeIds.end(), belongingToType) == typeIds.end()) {
                LOG_ERROR(UDMF_CLIENT, "BelongingToType can not find in typeIds");
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
        auto graph = UtdGraph::GetInstance().ConstructNewGraph(allTypeCfgs);
        if (graph->IsDAG()) {
            return true;
        }
    }
    return false;
}
} // namespace UDMF
} // namespace OHOS
