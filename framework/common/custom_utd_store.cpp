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
#define LOG_TAG "CustomUtdStore"
#include "custom_utd_store.h"
#include <fstream>
#include <sstream>
#include <sys/stat.h>
#include "logger.h"
#include "preset_type_descriptors.h"
#include "unistd.h"
#include "utd_cfgs_checker.h"
#include "utd_graph.h"
#ifdef WITH_SELINUX
#include <policycoreutils.h>
#endif
namespace OHOS {
namespace UDMF {
constexpr const char* UTD_CFG_FILE = "utd-adt.json";
constexpr const char* DYNAMIC_UTD_CFG_FILE = "utd-dynamic.json";
constexpr const char* CUSTOM_UTD_HAP_DIR = "/data/utd/utd-adt.json";
constexpr const char* DYNAMIC_UTD_HAP_DIR = "/data/utd/utd-dynamic.json";
constexpr const char* CUSTOM_UTD_SA_DIR = "/data/service/el1/";
constexpr const char* OLD_CUSTOM_UTD_SA_SUB_DIR = "/distributeddata/utd/";
constexpr const char* CUSTOM_UTD_SA_SUB_DIR = "/utdtypes/utd/";
constexpr const char* TEMP_FILE_SUFFIX = ".tmp";

CustomUtdStore::CustomUtdStore()
{
}

CustomUtdStore::~CustomUtdStore()
{
}

CustomUtdStore &CustomUtdStore::GetInstance()
{
    static CustomUtdStore utdCustomPersistence;
    return utdCustomPersistence;
}

std::vector<TypeDescriptorCfg> CustomUtdStore::GetCustomUtd(bool isHap, int32_t userId)
{
    std::string path = GetCustomUtdPath(isHap, userId);
    std::vector<TypeDescriptorCfg> utdTypes;
    auto ret = ReadTypeCfgs(path, utdTypes);
    if (ret != E_OK) {
        LOG_ERROR(UDMF_CLIENT, "ReadTypeCfgs failed, ret = %{public}d.", ret);
        return {};
    }
    return utdTypes;
}

std::vector<TypeDescriptorCfg> CustomUtdStore::GetDynamicUtd(bool isHap, int32_t userId)
{
    std::string path = GetDynamicUtdPath(isHap, userId);
    std::vector<TypeDescriptorCfg> utdTypes;
    auto ret = ReadTypeCfgs(path, utdTypes);
    if (ret != E_OK) {
        LOG_ERROR(UDMF_CLIENT, "ReadTypeCfgs failed, ret = %{public}d.", ret);
        return {};
    }
    return utdTypes;
}

std::string CustomUtdStore::GetCustomUtdPath(bool isHap, int32_t userId)
{
    if (isHap) {
        return CUSTOM_UTD_HAP_DIR;
    }
    std::string userIdStr = std::to_string(userId);
    std::string path = std::string(CUSTOM_UTD_SA_DIR).append(userIdStr).append(CUSTOM_UTD_SA_SUB_DIR);
    std::string oldPath = std::string(CUSTOM_UTD_SA_DIR).append(userIdStr).append(OLD_CUSTOM_UTD_SA_SUB_DIR);
    path = (access(path.c_str(), F_OK) != 0 && access(oldPath.c_str(), F_OK) == 0) ? oldPath : path;
    path.append(UTD_CFG_FILE);
    return path;
}

std::string CustomUtdStore::GetDynamicUtdPath(bool isHap, int32_t userId)
{
    if (isHap) {
        return DYNAMIC_UTD_HAP_DIR;
    }
    return std::string(CUSTOM_UTD_SA_DIR).append(std::to_string(userId)).append(CUSTOM_UTD_SA_SUB_DIR).
        append(DYNAMIC_UTD_CFG_FILE);
}

int32_t CustomUtdStore::ReadTypeCfgs(const std::string &filePath, std::vector<TypeDescriptorCfg> &utdTypes)
{
    std::ifstream fin(filePath);
    if (!fin.is_open()) {
        LOG_ERROR(UDMF_CLIENT, "Failed to open custom utd file, errno=%{public}d", errno);
        return E_FS_ERROR;
    }

    std::ostringstream buffer;
    buffer << fin.rdbuf();
    if (fin.fail() && !fin.eof()) {
        LOG_ERROR(UDMF_CLIENT, "Error reading file, errno=%{public}d", errno);
        return E_FS_ERROR;
    }

    std::string jsonStr = buffer.str();
    if (!utdJsonParser_.ParseStoredCustomUtdJson(jsonStr, utdTypes)) {
        LOG_ERROR(UDMF_CLIENT, "Failed to parse custom utd json");
        utdTypes.clear();
        return E_JSON_CONVERT_FAILED;
    }
    return E_OK;
}

int32_t CustomUtdStore::SaveTypeCfgs(const std::vector<TypeDescriptorCfg> &customUtdTypes, UtdTypeCategory category,
    int32_t userId)
{
    LOG_DEBUG(UDMF_CLIENT, "customUtdTypes total:%{public}zu.", customUtdTypes.size());
    std::string jsonData;
    if (!utdJsonParser_.ConvertUtdCfgsToJson(customUtdTypes, jsonData)) {
        LOG_ERROR(UDMF_CLIENT, "ConvertUtdCfgsToJson failed");
        return E_JSON_CONVERT_FAILED;
    }
    std::string fileDir =
        std::string(CUSTOM_UTD_SA_DIR).append(std::to_string(userId)).append(CUSTOM_UTD_SA_SUB_DIR);
    if (!CreateDirectory(fileDir)) {
        LOG_ERROR(UDMF_CLIENT, "CreateDirectory failed");
        return E_FS_ERROR;
    }
    std::string filePath = category == UtdTypeCategory::STATIC_TYPE ?
        fileDir + UTD_CFG_FILE : fileDir + DYNAMIC_UTD_CFG_FILE;
    return SaveCfgFile(jsonData, filePath);
}

int32_t CustomUtdStore::SaveCfgFile(const std::string &jsonData, const std::string &cfgFilePath)
{
    std::string tempFilePath = cfgFilePath + TEMP_FILE_SUFFIX;
    std::ofstream ofs;
    ofs.open(tempFilePath, std::ios::out | std::ios::trunc);
    
    if (!ofs.is_open()) {
        LOG_ERROR(UDMF_CLIENT, "open temp cfg failed");
        return E_FS_ERROR;
    }
    ofs << jsonData << std::endl;
    if (!ofs.good()) {
        LOG_ERROR(UDMF_CLIENT, "write temp cfg failed");
        ofs.close();
        std::remove(tempFilePath.c_str());
        return E_FS_ERROR;
    }
    ofs.close();

    if (std::rename(tempFilePath.c_str(), cfgFilePath.c_str()) != 0) {
        LOG_ERROR(UDMF_CLIENT, "rename temp cfg failed, errno: %{public}d", errno);
        std::remove(tempFilePath.c_str());
        return E_FS_ERROR;
    }
    return E_OK;
}

bool CustomUtdStore::CreateDirectory(const std::string &path) const
{
    if (access(path.c_str(), F_OK) == 0) {
        return true;
    }

    std::string::size_type index = 0;
    do {
        std::string subPath;
        index = path.find('/', index + 1);
        if (index == std::string::npos) {
            subPath = path;
        } else {
            subPath = path.substr(0, index);
        }

        if (access(subPath.c_str(), F_OK) != 0) {
            if (mkdir(subPath.c_str(), (S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH)) != 0) {
                LOG_WARN(UDMF_CLIENT, "CreateDirectory, fail.");
                return false;
            }
        }
    } while (index != std::string::npos);

    if (access(path.c_str(), F_OK) == 0) {
#ifdef WITH_SELINUX
        Restorecon(path.c_str());
#endif
        return true;
    }
    LOG_ERROR(UDMF_CLIENT, "CreateDirectory fail.");
    return false;
}

bool CustomUtdStore::InstallCustomUtds(const std::string &jsonStr, UtdUpdateContext &context)
{
    CustomUtdCfgs typeCfgs;
    if (!utdJsonParser_.ParseUserCustomUtdJson(jsonStr, typeCfgs.first, typeCfgs.second)) {
        LOG_ERROR(UDMF_CLIENT, "Parse json failed. bundleName:%{public}s", context.bundleName.c_str());
        return false;
    }

    auto status = UtdCfgsChecker::GetInstance().CheckTypeDescriptors(
        typeCfgs, UtdTypeCategory::STATIC_TYPE, context);
    if (status != E_OK) {
        LOG_ERROR(UDMF_CLIENT, "check type descriptors failed, bundleName:%{public}s, status = %{public}d",
            context.bundleName.c_str(), status);
        return false;
    }

    ProcessUtdForSave(typeCfgs, context.installedCustomUtdCfgs, context.bundleName);
    if (SaveTypeCfgs(context.installedCustomUtdCfgs, UtdTypeCategory::STATIC_TYPE, context.userId) != E_OK) {
        LOG_ERROR(UDMF_CLIENT, "Save failed, bundleName: %{public}s", context.bundleName.c_str());
        return false;
    }
    return true;
}

bool CustomUtdStore::UninstallCustomUtds(UtdUpdateContext &context)
{
    auto shouldRemove = [&context](auto& cfg) {
        if (cfg.ownerBundle == context.bundleName) {
            cfg.ownerBundle.clear();
        }
        cfg.installerBundles.erase(context.bundleName);
        return cfg.installerBundles.empty();
    };
    context.installedCustomUtdCfgs.erase(std::remove_if(
        context.installedCustomUtdCfgs.begin(), context.installedCustomUtdCfgs.end(), shouldRemove),
        context.installedCustomUtdCfgs.end());
    
    if (!UtdCfgsChecker::GetInstance().CheckBelongingToTypes(context.installedCustomUtdCfgs, context.presetCfgs)) {
        LOG_ERROR(UDMF_CLIENT, "belongingToTypes check failed. bundleName:%{public}s", context.bundleName.c_str());
        return false;
    }
    if (SaveTypeCfgs(context.installedCustomUtdCfgs, UtdTypeCategory::STATIC_TYPE, context.userId) != E_OK) {
        LOG_ERROR(UDMF_CLIENT, "Save type cfgs failed, bundleName: %{public}s", context.bundleName.c_str());
        return false;
    }
    return true;
}

Status CustomUtdStore::InstallDynamicUtds(const std::vector<TypeDescriptorCfg> &dynamicUtds, UtdUpdateContext &context)
{
    auto installedTypes = context.installedCustomUtdCfgs;
    installedTypes.insert(installedTypes.end(),
        context.installedDynamicUtdCfgs.begin(), context.installedDynamicUtdCfgs.end());

    CustomUtdCfgs typeCfgs = { dynamicUtds, {} };
    auto status = UtdCfgsChecker::GetInstance().CheckTypeDescriptors(
        typeCfgs, UtdTypeCategory::DYNAMIC_TYPE, context);
    if (status != E_OK) {
        LOG_ERROR(UDMF_CLIENT, "check type descriptors failed, bundleName:%{public}s, status = %{public}d",
            context.bundleName.c_str(), status);
        return status;
    }

    for (auto dynamicUtd : dynamicUtds) {
        dynamicUtd.installerBundles.emplace(context.bundleName);
        dynamicUtd.ownerBundle = context.bundleName;
        context.installedDynamicUtdCfgs.push_back(std::move(dynamicUtd));
    }
    if (SaveTypeCfgs(context.installedDynamicUtdCfgs, UtdTypeCategory::DYNAMIC_TYPE, context.userId) != E_OK) {
        LOG_ERROR(UDMF_CLIENT, "Save failed, bundleName: %{public}s", context.bundleName.c_str());
        return E_FS_ERROR;
    }
    return E_OK;
}

Status CustomUtdStore::UninstallDynamicUtds(const std::vector<std::string> &dynamicTypeIds, UtdUpdateContext &context)
{
    if (!UtdCfgsChecker::GetInstance().CheckTypeIdsFormat(dynamicTypeIds)) {
        LOG_ERROR(UDMF_CLIENT, "CheckTypeIdsFormat not pass");
        return E_INVALID_TYPE_ID;
    }
    for (const auto &typeId : dynamicTypeIds) {
        auto it = find_if(context.installedDynamicUtdCfgs.begin(), context.installedDynamicUtdCfgs.end(),
            [&typeId](const TypeDescriptorCfg &typeCfg) { return typeCfg.typeId == typeId; });
        if (it == context.installedDynamicUtdCfgs.end()) {
            LOG_ERROR(UDMF_CLIENT, "typeId not installed");
            return E_INVALID_TYPE_ID;
        }
        if (it->ownerBundle != context.bundleName) {
            LOG_ERROR(UDMF_CLIENT, "bundleName:%{public}s not install typeId", context.bundleName.c_str());
            return E_INVALID_TYPE_ID;
        }
        context.installedDynamicUtdCfgs.erase(it);
    }

    auto installedTypes = context.installedDynamicUtdCfgs;
    installedTypes.insert(installedTypes.end(),
        context.installedCustomUtdCfgs.begin(), context.installedCustomUtdCfgs.end());
    
    if (!UtdCfgsChecker::GetInstance().CheckBelongingToTypes(installedTypes, context.presetCfgs)) {
        LOG_ERROR(UDMF_CLIENT, "belongingToTypes check failed. bundleName:%{public}s", context.bundleName.c_str());
        return E_INVALID_TYPE_ID;
    }
    if (SaveTypeCfgs(context.installedDynamicUtdCfgs, UtdTypeCategory::DYNAMIC_TYPE, context.userId) != E_OK) {
        LOG_ERROR(UDMF_CLIENT, "Save type cfgs failed, bundleName: %{public}s", context.bundleName.c_str());
        return E_FS_ERROR;
    }
    return E_OK;
}

void CustomUtdStore::ProcessUtdForSave(const CustomUtdCfgs &utdTypes, std::vector<TypeDescriptorCfg> &customTyepCfgs,
    const std::string &bundleName)
{
    for (TypeDescriptorCfg declarationType : utdTypes.first) {
        for (auto iter = customTyepCfgs.begin(); iter != customTyepCfgs.end();) {
            if (iter->typeId == declarationType.typeId) {
                declarationType.installerBundles = iter->installerBundles;
                iter = customTyepCfgs.erase(iter);
            } else {
                iter++;
            }
        }
        declarationType.installerBundles.emplace(bundleName);
        declarationType.ownerBundle = bundleName;
        customTyepCfgs.push_back(declarationType);
    }
    for (TypeDescriptorCfg referenceType : utdTypes.second) {
        bool found = false;
        for (auto &typeCfg : customTyepCfgs) {
            if (typeCfg.typeId == referenceType.typeId) {
                typeCfg.installerBundles.emplace(bundleName);
                found = true;
                break;
            }
        }
        if (!found) {
            referenceType.installerBundles.emplace(bundleName);
            customTyepCfgs.push_back(referenceType);
        }
    }
}

UtdFileInfo CustomUtdStore::GetCustomUtdInfo(bool isHap, int32_t userId)
{
    UtdFileInfo info = {0};
    std::string path = GetCustomUtdPath(isHap, userId);
    struct stat fileStat;
    if (stat(path.c_str(), &fileStat) != 0) {
        LOG_WARN(UDMF_CLIENT, "custom utd file not exist");
        return info;
    }

    info.lastTime = fileStat.st_mtime;
    info.size = static_cast<uint64_t>(fileStat.st_size);
    return info;
}

Status CustomUtdStore::UninstallDynamicUtds(UtdUpdateContext &context)
{
    bool modifiyDynamicUtd = false;
    for (auto it = context.installedDynamicUtdCfgs.begin(); it != context.installedDynamicUtdCfgs.end();) {
        if (it->ownerBundle == context.bundleName) {
            it = context.installedDynamicUtdCfgs.erase(it);
            modifiyDynamicUtd = true;
        } else {
            it++;
        }
    }
    if (modifiyDynamicUtd &&
        SaveTypeCfgs(context.installedDynamicUtdCfgs, UtdTypeCategory::DYNAMIC_TYPE, context.userId) != E_OK) {
        LOG_ERROR(UDMF_CLIENT, "Save failed, bundleName: %{public}s", context.bundleName.c_str());
        return E_FS_ERROR;
    }
    return E_OK;
}
} // namespace UDMF
} // namespace OHOS