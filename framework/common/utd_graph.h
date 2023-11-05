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

#ifndef UDMF_UTD_GRAPH_H
#define UDMF_UTD_GRAPH_H

#include <vector>
#include <map>
#include <stack>
#include <string>
#include <shared_mutex>
#include <graph.h>

namespace OHOS {
namespace UDMF {
class UtdGraph {
public:
    static UtdGraph &GetInstance();
    uint32_t GetLocateIndex(const std::string &node);
    bool IsInvalidType(const std::string &node);
    void AddLocateDatas(uint32_t index, std::string node);
    void SetDataToGraph(uint32_t vesNum, std::vector<std::vector<uint32_t>> edges);
    bool IsRelatedOrNot(const std::string &startNode, const std::string &endNode);
private:
    UtdGraph();
    ~UtdGraph();
    UtdGraph(const UtdGraph &obj) = delete;
    UtdGraph &operator=(const UtdGraph &obj) = delete;
    mutable std::shared_mutex graphMutex_;
    Graph graph_;
    mutable std::shared_mutex vertexConversionTableMutex_;
    std::map<std::string, uint32_t> vertexConversionTable_;
};
} // namespace UDMF
} // namespace OHOS
#endif // UDMF_UTD_GRAPH_H
