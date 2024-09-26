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
#define LOG_TAG "UtdClient"
#include <regex>
#include <thread>
#include "utd_client.h"
#include "logger.h"
#include "utd_graph.h"
#include "custom_utd_store.h"
#include "accesstoken_kit.h"
#include "ipc_skeleton.h"
#include "os_account_manager.h"
namespace OHOS {
namespace UDMF {
constexpr const char* CUSTOM_UTD_HAP_DIR = "/data/utd/utd-adt.json";
constexpr const char* CUSTOM_UTD_SA_DIR = "/data/service/el1/";
constexpr const char* CUSTOM_UTD_SA_SUB_DIR = "/distributeddata/utd/utd-adt.json";

UtdClient::UtdClient()
{
    Init();
    LOG_INFO(UDMF_CLIENT, "construct UtdClient sucess.");
}

UtdClient::~UtdClient()
{
}

UtdClient &UtdClient::GetInstance()
{
    static auto instance = new UtdClient();
    return *instance;
}

void UtdClient::Init()
{
    std::unique_lock<std::shared_mutex> lock(utdMutex_);
    descriptorCfgs_ = PresetTypeDescriptors::GetInstance().GetPresetTypes();
    std::string customUtdPath = GetCustomUtdPath();
    if (!customUtdPath.empty()) {
        std::vector<TypeDescriptorCfg> customTypes =
            CustomUtdStore::GetInstance().GetTypeCfgs(customUtdPath);
        LOG_INFO(UDMF_CLIENT, "get customUtd. path:%{public}s, size:%{public}zu",
                 customUtdPath.c_str(), customTypes.size());
        if (!customTypes.empty()) {
            descriptorCfgs_.insert(descriptorCfgs_.end(), customTypes.begin(), customTypes.end());
        }
    }
    UtdGraph::GetInstance().InitUtdGraph(descriptorCfgs_);
}

Status UtdClient::GetTypeDescriptor(const std::string &typeId, std::shared_ptr<TypeDescriptor> &descriptor)
{
    {
        std::shared_lock<std::shared_mutex> guard(utdMutex_);
        for (const auto &utdTypeCfg : descriptorCfgs_) {
            if (utdTypeCfg.typeId == typeId) {
                descriptor = std::make_shared<TypeDescriptor>(utdTypeCfg);
                LOG_DEBUG(UDMF_CLIENT, "get descriptor success. %{public}s ", typeId.c_str());
                return Status::E_OK;
            }
        }
    }
    if (typeId.find(FLEXIBLE_TYPE_FLAG) != typeId.npos) {
        LOG_DEBUG(UDMF_CLIENT, "get flexible descriptor. %{public}s ", typeId.c_str());
        return GetFlexibleTypeDescriptor(typeId, descriptor);
    }
    return Status::E_OK;
}

bool UtdClient::IsValidFileExtension(const std::string &fileExtension)
{
    if (fileExtension.empty()) {
        return false;
    }
    if (fileExtension[0] != '.' || fileExtension.find("?") != fileExtension.npos ||
        fileExtension.find(":") != fileExtension.npos || fileExtension.find("=") != fileExtension.npos ||
        fileExtension.find("\\") != fileExtension.npos) {
            return false;
    }

    return true;
}

bool UtdClient::IsValidMimeType(const std::string &mimeType)
{
    if (mimeType.empty()) {
        return false;
    }
    if (mimeType.find("?") != mimeType.npos || mimeType.find(":") != mimeType.npos ||
        mimeType.find("=") != mimeType.npos ||mimeType.find("\\") != mimeType.npos) {
            return false;
    }
    return true;
}

Status UtdClient::GetFlexibleTypeDescriptor(const std::string &typeId, std::shared_ptr<TypeDescriptor> &descriptor)
{
    TypeDescriptorCfg flexibleTypeDescriptorCfg;
    if (!FlexibleType::ParseFlexibleUtd(typeId, flexibleTypeDescriptorCfg)) {
        LOG_ERROR(UDMF_CLIENT, "ParseFlexibleUtd failed, invalid typeId: %{public}s", typeId.c_str());
        return Status::E_ERROR;
    }
    descriptor = std::make_shared<TypeDescriptor>(flexibleTypeDescriptorCfg);
    return Status::E_OK;
}

Status UtdClient::GetUniformDataTypeByFilenameExtension(const std::string &fileExtension, std::string &typeId,
                                                        std::string belongsTo)
{
    std::string lowerFileExtension = fileExtension;
    std::transform(lowerFileExtension.begin(), lowerFileExtension.end(), lowerFileExtension.begin(), ::tolower);
    if (belongsTo != DEFAULT_TYPE_ID && !UtdGraph::GetInstance().IsValidType(belongsTo)) {
        LOG_ERROR(UDMF_CLIENT, "invalid belongsTo. fileExtension:%{public}s, belongsTo:%{public}s ",
                  fileExtension.c_str(), belongsTo.c_str());
        return Status::E_INVALID_PARAMETERS;
    }
    {
        std::shared_lock<std::shared_mutex> guard(utdMutex_);
        for (const auto &utdTypeCfg : descriptorCfgs_) {
            for (auto fileEx : utdTypeCfg.filenameExtensions) {
                std::transform(fileEx.begin(), fileEx.end(), fileEx.begin(), ::tolower);
                if (fileEx == fileExtension) {
                    typeId = utdTypeCfg.typeId;
                    break;
                }
            }
        }
    }
    // the find typeId is not belongsTo to the belongsTo.
    if (!typeId.empty() && belongsTo != DEFAULT_TYPE_ID && belongsTo != typeId &&
        !UtdGraph::GetInstance().IsLowerLevelType(belongsTo, typeId)) {
        typeId = "";
    }

    if (typeId.empty()) {
        if (!IsValidFileExtension(lowerFileExtension)) {
            LOG_ERROR(UDMF_CLIENT, "invalid fileExtension. fileExtension:%{public}s, belongsTo:%{public}s ",
                      fileExtension.c_str(), belongsTo.c_str());
            return Status::E_INVALID_PARAMETERS;
        }
        typeId = FlexibleType::GenFlexibleUtd("", lowerFileExtension, belongsTo);
    }
    return Status::E_OK;
}

Status UtdClient::GetUniformDataTypesByFilenameExtension(const std::string &fileExtension,
    std::vector<std::string> &typeIds, const std::string &belongsTo)
{
    if (belongsTo != DEFAULT_TYPE_ID && !UtdGraph::GetInstance().IsValidType(belongsTo)) {
        LOG_ERROR(UDMF_CLIENT, "invalid belongsTo. fileExtension:%{public}s, belongsTo:%{public}s ",
            fileExtension.c_str(), belongsTo.c_str());
        return Status::E_INVALID_PARAMETERS;
    }
    if (!IsValidFileExtension(fileExtension)) {
        LOG_ERROR(UDMF_CLIENT, "invalid fileExtension. fileExtension:%{public}s, belongsTo:%{public}s ",
            fileExtension.c_str(), belongsTo.c_str());
        return Status::E_INVALID_PARAMETERS;
    }

    std::string lowerFileExtension = fileExtension;
    std::transform(lowerFileExtension.begin(), lowerFileExtension.end(), lowerFileExtension.begin(), ::tolower);
    std::vector<std::string> typeIdsInCfg;
    {
        std::shared_lock<std::shared_mutex> guard(utdMutex_);
        for (const auto &utdTypeCfg : descriptorCfgs_) {
            for (auto fileEx : utdTypeCfg.filenameExtensions) {
                std::transform(fileEx.begin(), fileEx.end(), fileEx.begin(), ::tolower);
                if (fileEx == fileExtension) {
                    typeIds.push_back(utdTypeCfg.typeId);
                    break;
                }
            }
        }
    }
    typeIds.clear();
    for (const auto &typeId : typeIdsInCfg) {
        // the find typeId is not belongsTo to the belongsTo.
        if (belongsTo != DEFAULT_TYPE_ID && belongsTo != typeId &&
            !UtdGraph::GetInstance().IsLowerLevelType(belongsTo, typeId)) {
            continue;
        }
        typeIds.emplace_back(typeId);
    }
    if (typeIds.empty()) {
        typeIds.emplace_back(FlexibleType::GenFlexibleUtd("", lowerFileExtension, belongsTo));
    }
    return Status::E_OK;
}

Status UtdClient::GetUniformDataTypeByMIMEType(const std::string &mimeType, std::string &typeId,
                                               std::string belongsTo)
{
    std::string lowerMimeType = mimeType;
    std::transform(lowerMimeType.begin(), lowerMimeType.end(), lowerMimeType.begin(), ::tolower);
    if (belongsTo != DEFAULT_TYPE_ID && !UtdGraph::GetInstance().IsValidType(belongsTo)) {
        LOG_ERROR(UDMF_CLIENT, "invalid belongsTo. mimeType:%{public}s, belongsTo:%{public}s ",
                  mimeType.c_str(), belongsTo.c_str());
        return Status::E_INVALID_PARAMETERS;
    }
    typeId = GetTypeIdFromCfg(lowerMimeType);
    // the find typeId is not belongsTo to the belongsTo.
    if (!typeId.empty() && belongsTo != DEFAULT_TYPE_ID && belongsTo != typeId &&
        !UtdGraph::GetInstance().IsLowerLevelType(belongsTo, typeId)) {
        typeId = "";
    }
    if (typeId.empty()) {
        if (!IsValidMimeType(mimeType)) {
            LOG_ERROR(UDMF_CLIENT, "invalid mimeType. mimeType:%{public}s, belongsTo:%{public}s ",
                      mimeType.c_str(), belongsTo.c_str());
            return Status::E_INVALID_PARAMETERS;
        }
        typeId = FlexibleType::GenFlexibleUtd(lowerMimeType, "", belongsTo);
    }
    return Status::E_OK;
}

std::string UtdClient::GetTypeIdFromCfg(const std::string &mimeType)
{
    std::shared_lock<std::shared_mutex> guard(utdMutex_);
    for (const auto &utdTypeCfg : descriptorCfgs_) {
        for (auto mime : utdTypeCfg.mimeTypes) {
            std::transform(mime.begin(), mime.end(), mime.begin(), ::tolower);
            if (mime == mimeType) {
                return utdTypeCfg.typeId;
            }
        }
    }
    if (mimeType.empty() || mimeType.back() != '*') {
        return "";
    }
    std::string prefixType = mimeType.substr(0, mimeType.length() - 1);
    for (const auto &utdTypeCfg : descriptorCfgs_) {
        for (auto mime : utdTypeCfg.mimeTypes) {
            std::transform(mime.begin(), mime.end(), mime.begin(), ::tolower);
            if (mime.rfind(prefixType, 0) == 0 && utdTypeCfg.belongingToTypes.size() > 0) {
                return utdTypeCfg.belongingToTypes[0];
            }
        }
    }
    return "";
}

Status UtdClient::GetUniformDataTypesByMIMEType(const std::string &mimeType, std::vector<std::string> &typeIds,
    const std::string &belongsTo)
{
    if (belongsTo != DEFAULT_TYPE_ID && !UtdGraph::GetInstance().IsValidType(belongsTo)) {
        LOG_ERROR(UDMF_CLIENT, "invalid belongsTo. mimeType:%{public}s, belongsTo:%{public}s ",
            mimeType.c_str(), belongsTo.c_str());
        return Status::E_INVALID_PARAMETERS;
    }
    if (!IsValidMimeType(mimeType)) {
        LOG_ERROR(UDMF_CLIENT, "invalid mimeType. mimeType:%{public}s, belongsTo:%{public}s ",
            mimeType.c_str(), belongsTo.c_str());
        return Status::E_INVALID_PARAMETERS;
    }

    std::string lowerMimeType = mimeType;
    std::transform(lowerMimeType.begin(), lowerMimeType.end(), lowerMimeType.begin(), ::tolower);
    std::vector<std::string> typeIdsInCfg = GetTypeIdsFromCfg(lowerMimeType);
    typeIds.clear();
    for (const auto &typeId : typeIdsInCfg) {
        // the find typeId is not belongsTo to the belongsTo.
        if (belongsTo != DEFAULT_TYPE_ID && belongsTo != typeId &&
            !UtdGraph::GetInstance().IsLowerLevelType(belongsTo, typeId)) {
            continue;
        }
        typeIds.emplace_back(typeId);
    }
    if (typeIds.empty()) {
        typeIds.emplace_back(FlexibleType::GenFlexibleUtd(lowerMimeType, "", belongsTo));
    }
    return Status::E_OK;
}

std::vector<std::string> UtdClient::GetTypeIdsFromCfg(const std::string &mimeType)
{
    bool prefixMatch = false;
    std::string prefixType;
    if (!mimeType.empty() && mimeType.back() == '*') {
        prefixType = mimeType.substr(0, mimeType.length() - 1);
        prefixMatch = true;
    }
    std::vector<std::string> typeIdsInCfg;

    std::shared_lock<std::shared_mutex> guard(utdMutex_);
    for (const auto &utdTypeCfg : descriptorCfgs_) {
        for (auto mime : utdTypeCfg.mimeTypes) {
            std::transform(mime.begin(), mime.end(), mime.begin(), ::tolower);
            if ((mime == mimeType) || (prefixMatch && mime.rfind(prefixType, 0) == 0)) {
                typeIdsInCfg.push_back(utdTypeCfg.typeId);
                break;
            }
        }
    }
    return typeIdsInCfg;
}

Status UtdClient::IsUtd(std::string typeId, bool &result)
{
    try {
        if (typeId.empty()) {
            result = false;
            return Status::E_INVALID_PARAMETERS;
        }
        if (typeId[0] == '.' || find(typeId.begin(), typeId.end(), '/') != typeId.end()) {
            result = false;
            return Status::E_OK;
        }
        constexpr const char *preSetTypeIdRegexRule =
            R"(^(general\.|openharmony\.|org\.|com\.|macos\.|debian\.|redhat\.|io\.|de\.|net\.)[a-z0-9-\.]+(\-[a-z0-9-]+)*$)";
        if (std::regex_match(typeId, std::regex(preSetTypeIdRegexRule))) {
            result = true;
            return Status::E_OK;
        }
        constexpr const char *customUtdRegexRule =
            R"(^([A-Za-z][\w]*[A-Za-z\d])(\.([A-Za-z\d]+_?)+[A-Za-z\d]+){2,}(\.[A-Za-z\d]+[-|\.]?[A-Za-z\d]+)+)";
        if (std::regex_match(typeId, std::regex(customUtdRegexRule))) {
            result = true;
            return Status::E_OK;
        }
        result = false;
    } catch (...) {
        LOG_ERROR(UDMF_CLIENT, "exception, typeId:%{public}s", typeId.c_str());
        result = false;
        return Status::E_ERROR;
    }
    LOG_ERROR(UDMF_CLIENT, "is not utd, typeId:%{public}s", typeId.c_str());
    return Status::E_OK;
}

bool UtdClient::IsHapTokenType()
{
    uint32_t tokenId = IPCSkeleton::GetSelfTokenID();
    auto tokenType = Security::AccessToken::AccessTokenKit::GetTokenTypeFlag(tokenId);
    LOG_DEBUG(UDMF_CLIENT, "GetTokenTypeFlag, tokenType = %{public}d.", tokenType);
    if (tokenType == Security::AccessToken::TypeATokenTypeEnum::TOKEN_HAP) {
        return true;
    }
    return false;
}

std::string UtdClient::GetCustomUtdPath()
{
    if (IsHapTokenType()) {
        return std::string(CUSTOM_UTD_HAP_DIR);
    }
    int32_t userId = DEFAULT_USER_ID;
    if (GetCurrentActiveUserId(userId) != Status::E_OK) {
        userId = DEFAULT_USER_ID;
    }
    std::string customUtdSaPath = std::string(CUSTOM_UTD_SA_DIR) +
                                  std::to_string(userId) + std::string(CUSTOM_UTD_SA_SUB_DIR);
    return customUtdSaPath;
}

Status UtdClient::GetCurrentActiveUserId(int32_t& userId)
{
    std::vector<int32_t> localIds;
    int32_t status = OHOS::AccountSA::OsAccountManager::QueryActiveOsAccountIds(localIds);
    if (status != Status::E_OK || localIds.empty()) {
        LOG_ERROR(UDMF_CLIENT, "Get OsAccountId fail, status:%{public}d", status);
        return Status::E_ERROR;
    }
    userId = localIds[0];
    return Status::E_OK;
}

void UtdClient::InstallCustomUtds(const std::string &bundleName, const std::string &jsonStr, int32_t user)
{
    if (IsHapTokenType()) {
        return;
    }
    LOG_INFO(UDMF_CLIENT, "start, bundleName:%{public}s, user:%{public}d", bundleName.c_str(), user);
    std::string path = CUSTOM_UTD_SA_DIR + std::to_string(user) + CUSTOM_UTD_SA_SUB_DIR;
    std::vector<TypeDescriptorCfg> customTyepCfgs = CustomUtdStore::GetInstance().GetTypeCfgs(path);
    if (!CustomUtdStore::GetInstance().UninstallCustomUtds(bundleName, path, customTyepCfgs)) {
        LOG_ERROR(UDMF_CLIENT, "custom utd installed failed. bundleName:%{public}s, user:%{public}d",
            bundleName.c_str(), user);
        return;
    }
    if (jsonStr.empty()) {
        return;
    }
    if (!CustomUtdStore::GetInstance().InstallCustomUtds(bundleName, jsonStr, path, customTyepCfgs)) {
        LOG_ERROR(UDMF_CLIENT, "no custom utd installed. bundleName:%{public}s, user:%{public}d",
            bundleName.c_str(), user);
        return;
    }
    UpdateGraph(customTyepCfgs);
}

void UtdClient::UninstallCustomUtds(const std::string &bundleName, int32_t user)
{
    if (IsHapTokenType()) {
        return;
    }
    LOG_INFO(UDMF_CLIENT, "start, bundleName:%{public}s, user:%{public}d", bundleName.c_str(), user);
    std::string path = CUSTOM_UTD_SA_DIR + std::to_string(user) + CUSTOM_UTD_SA_SUB_DIR;
    std::vector<TypeDescriptorCfg> customTyepCfgs = CustomUtdStore::GetInstance().GetTypeCfgs(path);
    const auto customUtdSize = customTyepCfgs.size();
    if (!CustomUtdStore::GetInstance().UninstallCustomUtds(bundleName, path, customTyepCfgs)) {
        LOG_ERROR(UDMF_CLIENT, "custom utd installed failed. bundleName:%{public}s, user:%{public}d",
            bundleName.c_str(), user);
        return;
    }
    if (customTyepCfgs.size() != customUtdSize) {
        UpdateGraph(customTyepCfgs);
    }
}

void UtdClient::UpdateGraph(const std::vector<TypeDescriptorCfg> &customTyepCfgs)
{
    std::vector<TypeDescriptorCfg> allTypeCfgs = PresetTypeDescriptors::GetInstance().GetPresetTypes();
    allTypeCfgs.insert(allTypeCfgs.end(), customTyepCfgs.begin(), customTyepCfgs.end());
    LOG_INFO(UDMF_CLIENT, "customTyepSize:%{public}zu, allTypeSize:%{public}zu",
        customTyepCfgs.size(), allTypeCfgs.size());
    auto graph = UtdGraph::GetInstance().ConstructNewGraph(allTypeCfgs);
    std::unique_lock<std::shared_mutex> lock(utdMutex_);
    UtdGraph::GetInstance().Update(std::move(graph));
    descriptorCfgs_ = allTypeCfgs;
}
} // namespace UDMF
} // namespace OHOS
