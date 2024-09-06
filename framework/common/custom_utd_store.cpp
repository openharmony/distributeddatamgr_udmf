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
#include "unistd.h"
#include "error_code.h"
#include "logger.h"
#ifdef WITH_SELINUX
#include <policycoreutils.h>
#endif
namespace OHOS {
namespace UDMF {
constexpr const char* UTD_CFG_FILE = "utd-adt.json";

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

std::vector<TypeDescriptorCfg> CustomUtdStore::GetTypeCfgs(const std::string &cfgFilePath)
{
    LOG_DEBUG(UDMF_CLIENT, "get utdcustom from cfg, Path:%{public}s.", cfgFilePath.c_str());
    std::string jsonStr;
    std::ifstream fin(cfgFilePath);
    while (fin.good()) {
        std::string line;
        std::getline(fin, line);
        jsonStr += line;
    }
    std::vector<TypeDescriptorCfg> customUtdTypes;
    utdJsonParser_.ParseStoredCustomUtdJson(jsonStr, customUtdTypes);
    LOG_DEBUG(UDMF_CLIENT, "GetTypeCfgs, customUtdTypes total:%{public}zu.", customUtdTypes.size());
    return customUtdTypes;
}

int32_t CustomUtdStore::SaveTypeCfgs(const std::vector<TypeDescriptorCfg> &customUtdTypes,
                                     const std::string &cfgFilePath)
{
    std::string jsonData;
    std::string cfgFileName = UTD_CFG_FILE;
    std::string cfgFileDir = cfgFilePath.substr(0, cfgFilePath.length() - cfgFileName.length());
    if (utdJsonParser_.ConvertUtdCfgsToJson(customUtdTypes, jsonData) && CreateDirectory(cfgFileDir)) {
        SavaCfgFile(jsonData, cfgFilePath);
    }
    return 0;
}

int32_t CustomUtdStore::SavaCfgFile(const std::string &jsonData, const std::string &cfgFilePath)
{
    std::ofstream ofs;
    LOG_DEBUG(UDMF_CLIENT, "set cfg start, path:%{public}s ", cfgFilePath.c_str());
    ofs.open(cfgFilePath, 0x02);
    LOG_DEBUG(UDMF_CLIENT, "set cfg, is_open= %{public}d", ofs.is_open());
    ofs << jsonData << std::endl;
    ofs.close();
    LOG_DEBUG(UDMF_CLIENT, "set cfg end.");
    return 0;
}

bool CustomUtdStore::CreateDirectory(const std::string &path) const
{
    LOG_DEBUG(UDMF_CLIENT, "CreateDirectory start, path:%{public}s ", path.c_str());
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
                LOG_WARN(UDMF_CLIENT, "CreateDirectory, fail. path:%{public}s, subPath:%{public}s.",
                         path.c_str(), subPath.c_str());
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
} // namespace UDMF
} // namespace OHOS