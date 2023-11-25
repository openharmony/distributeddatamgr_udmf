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

#include <gtest/gtest.h>

#include <unistd.h>

#include "logger.h"
#include "utd_common.h"
#include "graph.h"

using namespace testing::ext;
using namespace OHOS::UDMF;
using namespace OHOS;
namespace OHOS::Test {
enum TestNodes : int32_t {
    POINT_A = 0,
    POINT_B,
    POINT_C,
    POINT_D,
    POINT_E,
    POINT_F,
    POINT_G,
    POINT_H
};
class GraphTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void GraphTest::SetUpTestCase()
{
}

void GraphTest::TearDownTestCase()
{
}

void GraphTest::SetUp()
{
}

void GraphTest::TearDown()
{
}

/**
* @tc.name: DfsUnconnectedGraph001
* @tc.desc: DfsUnconnectedGraph
* @tc.type: FUNC
*/
HWTEST_F(GraphTest, DfsUnconnectedGraph001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "DfsUnconnectedGraph001 begin.");
    uint32_t vextexNum = 3;  // total point
    vector<vector<uint32_t>> edges={{POINT_A, POINT_B},
                                    {POINT_B, POINT_C},
                                    {POINT_C, POINT_A}
    };
    Graph graph(vextexNum);
    for (uint32_t i = 0; i < edges.size(); i++) {
      graph.AddEdge(edges[i][0], edges[i][1]);
    }
    bool circleFlag = graph.DfsUnconnectedGraph([&](uint32_t currNode) -> bool
                                                  { return false; });
    EXPECT_EQ(circleFlag, true);
    LOG_INFO(UDMF_TEST, "DfsUnconnectedGraph001 end.");
}

HWTEST_F(GraphTest, DfsUnconnectedGraph002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "DfsUnconnectedGraph002 begin.");
    uint32_t vextexNum = 2;
    vector<vector<uint32_t>> edges={{POINT_A, POINT_B},
                                    {POINT_B, POINT_A},
    };
    Graph graph(vextexNum);
    for (uint32_t i = 0; i < edges.size(); i++) {
      graph.AddEdge(edges[i][0], edges[i][1]);
    }
    bool circleFlag = graph.DfsUnconnectedGraph([&](uint32_t currNode) -> bool
                                                  { return false; });
    EXPECT_EQ(circleFlag, true);
    LOG_INFO(UDMF_TEST, "DfsUnconnectedGraph002 end.");
}

HWTEST_F(GraphTest, DfsUnconnectedGraph003, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "DfsUnconnectedGraph003 begin.");
    uint32_t vextexNum =8;
        vector<vector<uint32_t>> edges = {
            {POINT_A, POINT_B},
            {POINT_B, POINT_C},
            {POINT_C, POINT_D},
            {POINT_D, POINT_E},
            {POINT_D, POINT_E},
            {POINT_E, POINT_F},
            {POINT_E, POINT_G},
            {POINT_G, POINT_H},
            {POINT_H, POINT_E},
        };
    Graph graph(vextexNum);
    for (uint32_t i = 0; i < edges.size(); i++) {
      graph.AddEdge(edges[i][0], edges[i][1]);
    }
    bool circleFlag = graph.DfsUnconnectedGraph([&](uint32_t currNode) -> bool
                                                  { return false; });
    EXPECT_EQ(circleFlag, false);
    LOG_INFO(UDMF_TEST, "DfsUnconnectedGraph003 end.");
}

} // OHOS::Test