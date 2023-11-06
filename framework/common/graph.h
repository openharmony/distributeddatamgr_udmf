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

#ifndef UDMF_GRAPH_H
#define UDMF_GRAPH_H

#include <vector>
#include <iostream>
#include <stack>
#include <string>

namespace OHOS {
namespace UDMF {
struct EdgeNode {
    uint32_t adjIndex;
    EdgeNode* next;
};

struct VertexNode {
    uint32_t value;
    EdgeNode* firstEdge;
};
class Graph {
public:
    using Action = std::function<bool(uint32_t node)>;
    void CreateAdjList(uint32_t vertexNum, std::vector<std::vector<uint32_t>> edges);
    void Dfs(uint32_t startNode, bool isInit, Action action);
    // Specify traversal start node, whether initializing the visited map and end condition.
    std::vector<uint32_t> DfsUnconnectedGraph();
private:
    uint32_t vertexNum_;
    std::vector<VertexNode> adjList_;  // Adjacency List
    std::vector<uint32_t> visited_;    // Determine if it has been accessed, index=vertex value
};
} // namespace UDMF
} // namespace OHOS
#endif // UDMF_GRAPH_H