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
#include "preset_type_descriptors.h"
#include "utd_graph.h"
namespace OHOS {
namespace UDMF {
UtdClient::UtdClient()
{
    descriptors_ = PresetTypeDescriptors::GetInstance().GetTypeDescriptors();
    SetDataToGraph();
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
    for (const auto &utdType : descriptors_) {
        if (utdType.GetTypeId() == typeId) {
            descriptor = std::make_shared<TypeDescriptor>(utdType);
            LOG_DEBUG(UDMF_CLIENT, "get descriptor success. %{public}s ", typeId.c_str());
            return Status::E_OK;
        }
    }
    return Status::E_OK;
}

Status UtdClient::GetUniformDataTypeByFilenameExtension(const std::string &fileExtension, const std::string &belongs,
                                                        std::string &typeId)
{
    for (auto &utdType : descriptors_) {
        std::vector<std::string> filenameExtensions = utdType.GetFilenameExtensions();
        if (find(filenameExtensions.begin(), filenameExtensions.end(), fileExtension) != filenameExtensions.end()) {
            typeId = utdType.GetTypeId();
            break;
        }
    }

    // the  find typeId is not belongs to the belongs.
    if (!typeId.empty() && !belongs.empty() && belongs != typeId &&
        !UtdGraph::GetInstance().IsRelatedOrNot(belongs, typeId)) {
        typeId = "";
    }
    return Status::E_OK;
}

Status UtdClient::GetUniformDataTypeByMIMEType(const std::string &mimeType, const std::string &belongs,
                                               std::string &typeId)
{
    for (auto &utdType : descriptors_) {
        std::vector<std::string> mimeTypes = utdType.GetMimeTypes();
        if (find(mimeTypes.begin(), mimeTypes.end(), mimeType) != mimeTypes.end()) {
            typeId = utdType.GetTypeId();
            break;
        }
    }
    // the  find typeId is not belongs to the belongs.
    if (!typeId.empty() && !belongs.empty() && belongs != typeId &&
        !UtdGraph::GetInstance().IsRelatedOrNot(belongs, typeId)) {
        typeId = "";
    }
    return Status::E_OK;
}

void UtdClient::SetDataToGraph()
{
    uint32_t descriptorsNum = static_cast<uint32_t>(descriptors_.size());
    for (uint32_t i = 0; i < descriptorsNum; i++) {
        UtdGraph::GetInstance().AddLocateDatas(i, descriptors_[i].GetTypeId());
    }

    std::vector<std::vector<uint32_t>> edges;
    for (auto &descriptor : descriptors_) {
        std::set<std::string> belongs = descriptor.GetBelongingToTypes();
        for (auto belongType : belongs) {
            edges.push_back({UtdGraph::GetInstance().GetLocateIndex(belongType), 
                             UtdGraph::GetInstance().GetLocateIndex(descriptor.GetTypeId())});
        }
    }
    UtdGraph::GetInstance().SetDataToGraph(descriptorsNum, edges);
}
} // namespace UDMF
} // namespace OHOS