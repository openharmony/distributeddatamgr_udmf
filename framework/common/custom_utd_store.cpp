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
constexpr const char* CUSTOM_UTD_HAP_DIR = "/data/utd/utd-adt.json";
constexpr const char* CUSTOM_UTD_SA_DIR = "/data/service/el1/";
constexpr const char* OLD_CUSTOM_UTD_SA_SUB_DIR = "/distributeddata/utd/";
constexpr const char* CUSTOM_UTD_SA_SUB_DIR = "/utdtypes/utd/";

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
    LOG_DEBUG(UDMF_CLIENT, "get utdcustom from cfg");

    std::string jsonStr;
    std::ifstream fin(path);
    while (fin.good()) {
        std::string line;
        std::getline(fin, line);
        jsonStr += line;
    }
    std::vector<TypeDescriptorCfg> customUtd;
    utdJsonParser_.ParseStoredCustomUtdJson(jsonStr, customUtd);
    LOG_DEBUG(UDMF_CLIENT, "CustomUtd total:%{public}zu.", customUtd.size());
    return customUtd;
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

int32_t CustomUtdStore::SaveTypeCfgs(const std::vector<TypeDescriptorCfg> &customUtdTypes, int32_t user)
{
    LOG_DEBUG(UDMF_CLIENT, "customUtdTypes total:%{public}zu.", customUtdTypes.size());
    std::string jsonData;
    std::string cfgFileDir = CUSTOM_UTD_SA_DIR + std::to_string(user) + CUSTOM_UTD_SA_SUB_DIR;
    if (utdJsonParser_.ConvertUtdCfgsToJson(customUtdTypes, jsonData) && CreateDirectory(cfgFileDir)) {
        SavaCfgFile(jsonData, cfgFileDir.append(UTD_CFG_FILE));
    }
    return 0;
}

int32_t CustomUtdStore::SavaCfgFile(const std::string &jsonData, const std::string &cfgFilePath)
{
    std::ofstream ofs;
    LOG_DEBUG(UDMF_CLIENT, "set cfg start, path:%{public}s ", cfgFilePath.c_str());
    ofs.open(cfgFilePath, 0x02);
    if (!ofs.is_open()) {
        LOG_ERROR(UDMF_CLIENT, "open cfg failed, path:%{public}s", cfgFilePath.c_str());
    }
    ofs << jsonData << std::endl;
    ofs.close();
    LOG_DEBUG(UDMF_CLIENT, "set cfg end.");
    return 0;
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

    return false;
}

bool CustomUtdStore::InstallCustomUtds(const std::string &bundleName, const std::string &jsonStr,
    int32_t user, std::vector<TypeDescriptorCfg> &customTyepCfgs)
{
    CustomUtdCfgs typeCfgs;
    if (!utdJsonParser_.ParseUserCustomUtdJson(jsonStr, typeCfgs.first, typeCfgs.second)) {
        LOG_ERROR(UDMF_CLIENT, "Parse json failed. bundleName:%{public}s", bundleName.c_str());
        return false;
    }
    std::vector<TypeDescriptorCfg> presetTypes = PresetTypeDescriptors::GetInstance().GetPresetTypes();

    if (!UtdCfgsChecker::GetInstance().CheckTypeDescriptors(
        typeCfgs, presetTypes, customTyepCfgs, bundleName)) {
        LOG_ERROR(UDMF_CLIENT, "check type descriptors failed, bundleName:%{public}s", bundleName.c_str());
        return false;
    }

    ProcessUtdForSave(typeCfgs, customTyepCfgs, bundleName);
    if (CustomUtdStore::GetInstance().SaveTypeCfgs(customTyepCfgs, user) != E_OK) {
        LOG_ERROR(UDMF_CLIENT, "Save failed, bundleName: %{public}s", bundleName.c_str());
        return false;
    }
    return true;
}

bool CustomUtdStore::UninstallCustomUtds(const std::string &bundleName, int32_t user,
    std::vector<TypeDescriptorCfg> &customTyepCfgs)
{
    for (auto iter = customTyepCfgs.begin(); iter != customTyepCfgs.end();) {
        auto it = find(iter->installerBundles.begin(), iter->installerBundles.end(), bundleName);
        if (it != iter->installerBundles.end()) {
            iter->installerBundles.erase(it);
        }
        if (iter->installerBundles.empty()) {
            iter = customTyepCfgs.erase(iter);
        } else {
            iter++;
        }
    }
    std::vector<TypeDescriptorCfg> presetTypes = PresetTypeDescriptors::GetInstance().GetPresetTypes();
    if (!UtdCfgsChecker::GetInstance().CheckBelongingToTypes(customTyepCfgs, presetTypes)) {
        LOG_ERROR(UDMF_CLIENT, "belongingToTypes check failed. bundleName:%{public}s", bundleName.c_str());
        return false;
    }
    if (CustomUtdStore::GetInstance().SaveTypeCfgs(customTyepCfgs, user) != E_OK) {
        LOG_ERROR(UDMF_CLIENT, "Save type cfgs failed, bundleName: %{public}s", bundleName.c_str());
        return false;
    }
    return true;
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
    info.size = fileStat.st_size;
    return info;
}
} // namespace UDMF
} // namespace OHOS