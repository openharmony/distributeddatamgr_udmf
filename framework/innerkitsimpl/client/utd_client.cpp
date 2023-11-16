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
namespace OHOS {
namespace UDMF {
UtdClient::UtdClient()
{
    descriptorCfgs_ = PresetTypeDescriptors::GetInstance().GetTypeCfgs();
    UtdGraph::GetInstance().InitUtdGraph(descriptorCfgs_);
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
    if (belongsTo != DEFAULT_TYPE_ID && !UtdGraph::GetInstance().IsValidType(belongsTo)) {
        LOG_ERROR(UDMF_CLIENT, "invalid belongsTo. fileExtension:%{public}s, belongsTo:%{public}s ",
                  fileExtension.c_str(), belongsTo.c_str());
        return Status::E_INVALID_PARAMETERS;
    }

    for (auto &utdTypeCfg : descriptorCfgs_) {
        std::vector<std::string> fileExtensions = utdTypeCfg.filenameExtensions;
        if (find(fileExtensions.begin(), fileExtensions.end(), fileExtension) != fileExtensions.end()) {
            typeId = utdTypeCfg.typeId;
            break;
        }
    }

    // the find typeId is not belongsTo to the belongsTo.
    if (!typeId.empty() && belongsTo != DEFAULT_TYPE_ID && belongsTo != typeId &&
        !UtdGraph::GetInstance().IsLowerLevelType(belongsTo, typeId)) {
        typeId = "";
    }
    return Status::E_OK;
}

Status UtdClient::GetUniformDataTypeByMIMEType(const std::string &mimeType, std::string &typeId,
                                               std::string belongsTo)
{
    if (belongsTo != DEFAULT_TYPE_ID && !UtdGraph::GetInstance().IsValidType(belongsTo)) {
        LOG_ERROR(UDMF_CLIENT, "invalid belongsTo. mimeType:%{public}s, belongsTo:%{public}s ",
                  mimeType.c_str(), belongsTo.c_str());
        return Status::E_INVALID_PARAMETERS;
    }

    for (auto &utdTypeCfg : descriptorCfgs_) {
        std::vector<std::string> mimeTypes = utdTypeCfg.mimeTypes;
        if (find(mimeTypes.begin(), mimeTypes.end(), mimeType) != mimeTypes.end()) {
            typeId = utdTypeCfg.typeId;
            break;
        }
    }
    // the find typeId is not belongsTo to the belongsTo.
    if (!typeId.empty() && belongsTo != DEFAULT_TYPE_ID && belongsTo != typeId &&
        !UtdGraph::GetInstance().IsLowerLevelType(belongsTo, typeId)) {
        typeId = "";
    }
    return Status::E_OK;
}
} // namespace UDMF
} // namespace OHOS