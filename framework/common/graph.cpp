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
#include "graph.h"
namespace OHOS {
namespace UDMF {
Graph::Graph(uint32_t vertexNum):vertexNum_(vertexNum)
{
    for (uint32_t node = 0; node < vertexNum_; node++) {
        adjList_.push_back({node, nullptr});
    }
    visited_.resize(vertexNum_);
    fill(visited_.begin(), visited_.end(), 0);
}

void Graph::AddEdge(uint32_t start, uint32_t end)
{
    EdgeNode *edge = new EdgeNode;  // add new edge
    edge->adjIndex = end;
    edge->next = adjList_[start].firstEdge;
    adjList_[start].firstEdge = edge;
}

bool Graph::Dfs(uint32_t startNode, Action action, bool isInit)
{
    if (isInit) {
        visited_.resize(vertexNum_);
        fill(visited_.begin(), visited_.end(), 0);
    }
    std::stack<uint32_t> nodes;
    EdgeNode *edge = nullptr;
    visited_[startNode] = 1;
    nodes.push(startNode);
    result_.push_back(startNode);
    if (action(adjList_[startNode].value)) {
        return true;
    }
    while (!nodes.empty()) {
        edge = adjList_[nodes.top()].firstEdge;
        while (edge) {
            if (visited_[edge->adjIndex] == 0) {
                visited_[edge->adjIndex] = 1;
                if (adjList_[edge->adjIndex].firstEdge != nullptr) {
                    auto iter = find(result_.begin(), result_.end(), adjList_[edge->adjIndex].firstEdge->adjIndex);
                    if (iter != result_.end() && visited_[adjList_[edge->adjIndex].firstEdge->adjIndex] == 1) {
                        return false;     // current node, iscycle
                    }
                }
                if (action(adjList_[edge->adjIndex].value)) {
                    return true;
                }
                result_.push_back(startNode);
                nodes.push(edge->adjIndex);
                edge = adjList_[edge->adjIndex].firstEdge;
            } else {
                edge = edge->next;
            }
        }
        if (edge == nullptr) {
            visited_[nodes.top()] = 2;  // 2: all edge of the adj is visited.
            nodes.pop();
        }
    }
    return true;
}

bool Graph::DfsUnconnectedGraph(Action action)
{
    visited_.resize(vertexNum_);
    fill(visited_.begin(), visited_.end(), 0);
    result_.clear();
    for (uint32_t node = 0; node < vertexNum_; node++) {
        if (!visited_[node]) {
            if (!Dfs(node, action, false)) {
                return false;
            }
        }
    }
    return true;
}
} // namespace UDMF
} // namespace OHOS
