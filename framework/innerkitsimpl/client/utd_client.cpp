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

#include "utd_client.h"
#include "logger.h"
#include "utd_graph.h"
#include "custom_utd_store.h"
#include <algorithm>
namespace OHOS {
namespace UDMF {
constexpr const char* CUSTOM_TYPE_CFG_PATH = "/data/utd/utd-adt.json";
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
    descriptorCfgs_ = PresetTypeDescriptors::GetInstance().GetPresetTypes();
    std::vector<TypeDescriptorCfg> customTypes =
        CustomUtdStore::GetInstance().GetTypeCfgs(CUSTOM_TYPE_CFG_PATH);
    if (!customTypes.empty()) {
        descriptorCfgs_.insert(descriptorCfgs_.end(), customTypes.begin(), customTypes.end());
    }
    UtdGraph::GetInstance().InitUtdGraph(descriptorCfgs_);
}

Status UtdClient::GetTypeDescriptor(const std::string &typeId, std::shared_ptr<TypeDescriptor> &descriptor)
{
    for (const auto &utdTypeCfg : descriptorCfgs_) {
        if (utdTypeCfg.typeId == typeId) {
            descriptor = std::make_shared<TypeDescriptor>(utdTypeCfg);
            LOG_DEBUG(UDMF_CLIENT, "get descriptor success. %{public}s ", typeId.c_str());
            return Status::E_OK;
        }
    }
    return Status::E_OK;
}

Status UtdClient::GetUniformDataTypeByFilenameExtension(const std::string &fileExtension, std::string &typeId,
                                                        std::string belongsTo)
{
    std::string fileExtensionLower = fileExtension;
    std::transform(fileExtension.begin(), fileExtension.end(), fileExtensionLower.begin(), ::tolower);
    if (belongsTo != DEFAULT_TYPE_ID && !UtdGraph::GetInstance().IsValidType(belongsTo)) {
        LOG_ERROR(UDMF_CLIENT, "invalid belongsTo. fileExtension:%{public}s, belongsTo:%{public}s ",
                  fileExtension.c_str(), belongsTo.c_str());
        return Status::E_INVALID_PARAMETERS;
    }

    for (const auto &utdTypeCfg : descriptorCfgs_) {
        std::vector<std::string> fileExtensions = utdTypeCfg.filenameExtensions;
        if (find(fileExtensions.begin(), fileExtensions.end(), fileExtensionLower) != fileExtensions.end()) {
            typeId = utdTypeCfg.typeId;
            break;
        }
    }

    // the find typeId is not belongsTo to the belongsTo.
    if (!typeId.empty() && belongsTo != DEFAULT_TYPE_ID && belongsTo != typeId &&
        !UtdGraph::GetInstance().IsLowerLevelType(belongsTo, typeId)) {
        typeId = "";
    }

    if (!typeId.empty()) {
        if (fileExtensionLower[0] == '.') {
            typeId = "dynamic" + fileExtensionLower;
        } else {
            typeId = "dynamic." + fileExtensionLower;
        }
    }
    return Status::E_OK;
}

Status UtdClient::GetUniformDataTypeByMIMEType(const std::string &mimeType, std::string &typeId,
                                               std::string belongsTo)
{
    std::string mimeTypeLower = mimeType;
    std::transform(mimeType.begin(), mimeType.end(), mimeTypeLower.begin(), ::tolower);
    if (belongsTo != DEFAULT_TYPE_ID && !UtdGraph::GetInstance().IsValidType(belongsTo)) {
        LOG_ERROR(UDMF_CLIENT, "invalid belongsTo. mimeType:%{public}s, belongsTo:%{public}s ",
                  mimeType.c_str(), belongsTo.c_str());
        return Status::E_INVALID_PARAMETERS;
    }

    for (const auto &utdTypeCfg : descriptorCfgs_) {
        std::vector<std::string> mimeTypes = utdTypeCfg.mimeTypes;
        if (find(mimeTypes.begin(), mimeTypes.end(), mimeTypeLower) != mimeTypes.end()) {
            typeId = utdTypeCfg.typeId;
            break;
        }
    }
    // the find typeId is not belongsTo to the belongsTo.
    if (!typeId.empty() && belongsTo != DEFAULT_TYPE_ID && belongsTo != typeId &&
        !UtdGraph::GetInstance().IsLowerLevelType(belongsTo, typeId)) {
        typeId = "";
    }
    
    if (!typeId.empty()) {
        typeId = "dynamic." + mimeTypeLower;
    }

    return Status::E_OK;
}
} // namespace UDMF
} // namespace OHOS
