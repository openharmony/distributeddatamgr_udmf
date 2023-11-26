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
    explicit Graph(uint32_t vertexNum);
    using Action = std::function<bool(uint32_t node)>;
    void AddEdge(uint32_t start, uint32_t end);
    bool Dfs(uint32_t startNode, Action action, bool isInit = true);
    bool DfsUnconnectedGraph(Action action);
private:
    uint32_t vertexNum_;
    std::vector<VertexNode> adjList_;  // Adjacency List
    std::vector<uint32_t> visited_;    // Determine whether the vertex has been accessed, index=vertex value
    std::vector<uint32_t> result_;
};
} // namespace UDMF
} // namespace OHOS
#endif // UDMF_GRAPH_H
