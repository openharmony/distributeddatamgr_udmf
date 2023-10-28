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
struct EdgeNode {  // 边表结点
    uint32_t adjIndex;     //  存储顶点的下标
    EdgeNode* next;   //  连接下一个邻点
};

struct VertexNode { // 顶点表结点
    int value;
    EdgeNode* firstEdge;
};
using Action = std::function<bool(uint32_t node)>;
class Graph {
public:
    void CreateAdjList(uint32_t vesNum, std::vector<std::vector<uint32_t>> edges);
    void Dfs(uint32_t startNode, bool isInit, Action action);  // 指定点遍历,指定条件结束
    std::vector<uint32_t> DfsUnconnectedGraph();   // dfs非联通图完全遍历
private:
    static constexpr uint32_t MAX_LENGTH = 500;
    uint32_t vesNum_;      // 顶点数
    VertexNode adjList_[MAX_LENGTH];  // 邻接表
    uint32_t visited_[MAX_LENGTH]; // 判断是否有被访问过, 下标=顶点值
};
} // namespace UDMF
} // namespace OHOS
#endif // UDMF_GRAPH_H