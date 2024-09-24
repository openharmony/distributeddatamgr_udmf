/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#define LOG_TAG "EndianConverterTest"

#include <unistd.h>
#include <gtest/gtest.h>
#include <string>

#include "logger.h"
#include "endian_converter.h"

using namespace testing::ext;
using namespace OHOS::UDMF;
using namespace OHOS;
namespace OHOS::Test {
using namespace std;

class EndianConverterTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void EndianConverterTest::SetUpTestCase()
{
}

void EndianConverterTest::TearDownTestCase()
{
}

void EndianConverterTest::SetUp()
{
}

void EndianConverterTest::TearDown()
{
}

/**
* @tc.name: HostToNet001
* @tc.desc: Normal testcase of HostToNet
* @tc.type: FUNC
*/
HWTEST_F(EndianConverterTest, HostToNet001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "HostToNet001 begin.");
    float value = 3.1415926;
    float ret = HostToNet(value);
    EXPECT_EQ(ret, value);
    LOG_INFO(UDMF_TEST, "HostToNet001 end.");
}

/**
* @tc.name: NetToHost001
* @tc.desc: Normal testcase of NetToHost
* @tc.type: FUNC
*/
HWTEST_F(EndianConverterTest, NetToHost001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "NetToHost001 begin.");
    float value = 3.1415926;
    float ret = NetToHost(value);
    EXPECT_EQ(ret, value);
    LOG_INFO(UDMF_TEST, "NetToHost001 end.");
}

/**
* @tc.name: HostToNet002
* @tc.desc: Normal testcase of HostToNet
* @tc.type: FUNC
*/
HWTEST_F(EndianConverterTest, HostToNet002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "HostToNet002 begin.");
    double value = 3.14;
    double ret = HostToNet(value);
    EXPECT_EQ(ret, value);
    LOG_INFO(UDMF_TEST, "HostToNet002 end.");
}

/**
* @tc.name: NetToHost002
* @tc.desc: Normal testcase of NetToHost
* @tc.type: FUNC
*/
HWTEST_F(EndianConverterTest, NetToHost002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "NetToHost002 begin.");
    double value = 3.14;
    double ret = NetToHost(value);
    EXPECT_EQ(ret, value);
    LOG_INFO(UDMF_TEST, "NetToHost002 end.");
}
} // OHOS::Test