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

uint32_t UtdGraph::GetLocateIndex(const std::string &node) // 顶点数据和下标转换
{
    std::shared_lock<decltype(vesNodesMutex_)> vesNodesLock(vesNodesMutex_);
    return vesNodes_.at(node);
}
void UtdGraph::AddLocateDatas(uint32_t index, std::string node)
{
    std::unique_lock<std::shared_mutex> vesNodesLock(vesNodesMutex_);
    vesNodes_.insert({ node, index });
}

void UtdGraph::SetDataToGraph(uint32_t vesNum, std::vector<std::vector<uint32_t>> edges)
{
    std::unique_lock<std::shared_mutex> graphLock(graphMutex_);
    graph_.CreateAdjList(vesNum, edges);
}

bool UtdGraph::IsRelatedOrNot(const std::string &startNode, const std::string &endNode)
{
    bool isFind = false;
    uint32_t start = GetLocateIndex(startNode);
    uint32_t end = GetLocateIndex(endNode);
    std::shared_lock<decltype(graphMutex_)> graphLock(graphMutex_);
    graph_.Dfs(start, true, [&](uint32_t currNode)-> bool {
        if (end == currNode) {
            isFind = true;
            return true;
        }
        return false;
    });
    return isFind;
}
} // namespace UDMF
} // namespace OHOS
