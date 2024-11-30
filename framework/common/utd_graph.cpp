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
    std::unique_lock<std::mutex> lock(graphMutex_);
    return graph_->IsValidType(node);
}

void UtdGraph::InitUtdGraph(const std::vector<TypeDescriptorCfg> &descriptorCfgs)
{
    std::map<std::string, uint32_t> typeIdIndex;
    uint32_t descriptorsNum = static_cast<uint32_t>(descriptorCfgs.size());
    for (uint32_t i = 0; i < descriptorsNum; i++) {
        typeIdIndex.insert(std::make_pair(descriptorCfgs[i].typeId, i));
    }
    std::unique_lock<std::mutex> lock(graphMutex_);
    graph_ = std::make_unique<Graph>(descriptorsNum, typeIdIndex);
    for (const auto &descriptorCfg : descriptorCfgs) {
        std::vector<std::string> belongsTo = descriptorCfg.belongingToTypes;
        for (auto belongsToType : belongsTo) {
            graph_->AddEdge(belongsToType, descriptorCfg.typeId);
        }
    }
    LOG_INFO(UDMF_CLIENT, "InitUtdGraph success, descriptorsNum:%{public}u. ", descriptorsNum);
}

bool UtdGraph::IsLowerLevelType(const std::string &lowerLevelType, const std::string &heigitLevelType)
{
    if (graph_ == nullptr) {
        LOG_ERROR(UDMF_CLIENT, "graph_ is nullptr.");
        return false;
    }
    std::unique_lock<std::mutex> lock(graphMutex_);
    bool isFind = false;
    int32_t start = graph_->GetIndex(lowerLevelType);
    int32_t end = graph_->GetIndex(heigitLevelType);
    if (start < 0 || end < 0) {
        return false;
    }
    uint32_t uStart = static_cast<uint32_t>(start);
    uint32_t uEnd = static_cast<uint32_t>(end);
    graph_->Dfs(uStart, [&isFind, &uEnd](uint32_t currNode)-> bool {
        if (uEnd == currNode) {
            isFind = true;
            return true;
        }
        return false;
    });
    return isFind;
}

std::unique_ptr<Graph> UtdGraph::ConstructNewGraph(const std::vector<TypeDescriptorCfg> &descriptorCfgs)
{
    std::map<std::string, uint32_t> typeIdIndex;
    uint32_t descriptorsNum = static_cast<uint32_t>(descriptorCfgs.size());
    for (uint32_t i = 0; i < descriptorsNum; i++) {
        typeIdIndex.insert(std::make_pair(descriptorCfgs[i].typeId, i));
    }
    auto graph = std::make_unique<Graph>(descriptorsNum, typeIdIndex);
    
    for (const auto &descriptorCfg : descriptorCfgs) {
        std::vector<std::string> belongsTo = descriptorCfg.belongingToTypes;
        for (auto belongsToType : belongsTo) {
            graph->AddEdge(belongsToType, descriptorCfg.typeId);
        }
    }
    return graph;
}

void UtdGraph::Update(std::unique_ptr<Graph> graph)
{
    std::unique_lock<std::mutex> lock(graphMutex_);
    graph_ = std::move(graph);
}
} // namespace UDMF
} // namespace OHOS
