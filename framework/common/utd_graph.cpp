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
#define LOG_TAG "UtdGraph"
#include "utd_graph.h"
#include "logger.h"
namespace OHOS {
namespace UDMF {
UtdGraph::UtdGraph()
{
    LOG_INFO(UDMF_CLIENT, "construct UtdGraph sucess.");
}

UtdGraph::~UtdGraph()
{
}

UtdGraph &UtdGraph::GetInstance()
{
    static auto instance = new UtdGraph();
    return *instance;
}

bool UtdGraph::IsValidType(const std::string &node)
{
    if (typeIdIndex_.find(node) == typeIdIndex_.end()) {
        LOG_ERROR(UDMF_CLIENT, "invalid typeId. typeId:%{public}s ", node.c_str());
        return false;
    }
    return true;
}

int32_t UtdGraph::GetIndex(const std::string &node)
{
    auto idx = typeIdIndex_.find(node);
    if (idx == typeIdIndex_.end()) {
        return -1;
    }
    return idx->second;
}

void UtdGraph::InitUtdGraph(const std::vector<TypeDescriptorCfg> &descriptorCfgs)
{
    typeIdIndex_.clear();
    uint32_t descriptorsNum = static_cast<uint32_t>(descriptorCfgs.size());
    std::unique_lock<std::shared_mutex> Lock(graphMutex_);
    graph_ = new Graph(descriptorsNum);
    for (uint32_t i = 0; i < descriptorsNum; i++) {
        typeIdIndex_.insert(std::make_pair(descriptorCfgs[i].typeId, i));
    }
    for (const auto &descriptorCfg : descriptorCfgs) {
        std::set<std::string> belongsTo = descriptorCfg.belongingToTypes;
        for (auto belongsToType : belongsTo) {
            AddEdge(belongsToType, descriptorCfg.typeId);
        }
    }
    LOG_INFO(UDMF_CLIENT, "InitUtdGraph success, descriptorsNum:%{public}u. ", descriptorsNum);
}

void UtdGraph::AddEdge(const std::string &startNode, const std::string &endNode)
{
    int32_t start = GetIndex(startNode);
    int32_t end = GetIndex(endNode);
    if (start < 0 || end < 0) {
        LOG_WARN(UDMF_CLIENT, "abnormal edge, startNode:%{public}s, endNode:%{public}s. ",
                 startNode.c_str(), endNode.c_str());
        return;
    }
    graph_->AddEdge(start, end);
}

bool UtdGraph::IsLowerLevelType(const std::string &lowerLevelType, const std::string &heigitLevelType)
{
    bool isFind = false;
    int32_t start = GetIndex(lowerLevelType);
    int32_t end = GetIndex(heigitLevelType);
    if (start < 0 || end < 0) {
        return false;
    }
    uint32_t uStart = static_cast<uint32_t>(start);
    uint32_t uEnd = static_cast<uint32_t>(end);
    std::shared_lock<decltype(graphMutex_)> Lock(graphMutex_);
    graph_->Dfs(uStart, [&isFind, &uEnd](uint32_t currNode)-> bool {
        if (uEnd == currNode) {
            isFind = true;
            return true;
        }
        return false;
    });
    return isFind;
}

bool UtdGraph::IsDAG()
{
    std::shared_lock<decltype(graphMutex_)> Lock(graphMutex_);
    return graph_->DfsUnconnectedGraph([&](uint32_t currNode) -> bool {return false; });
}
} // namespace UDMF
} // namespace OHOS
