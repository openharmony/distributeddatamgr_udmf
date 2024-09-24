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
#define LOG_TAG "LinkTest"

#include <unistd.h>
#include <gtest/gtest.h>
#include <string>

#include "logger.h"
#include "unified_record.h"
#include "link.h"

using namespace testing::ext;
using namespace OHOS::UDMF;
using namespace OHOS;
namespace OHOS::Test {
using namespace std;

class LinkTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void LinkTest::SetUpTestCase()
{
}

void LinkTest::TearDownTestCase()
{
}

void LinkTest::SetUp()
{
}

void LinkTest::TearDown()
{
}

/**
* @tc.name: LinkTest001
* @tc.desc: Normal testcase of Link
* @tc.type: FUNC
*/
HWTEST_F(LinkTest, LinkTest001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "LinkTest001 begin.");
    UDType type = UDType::ENTITY;
    ValueType value = "value";
    Link link(type, value);
    EXPECT_EQ(link.url_, std::get<std::string>(value));
    LOG_INFO(UDMF_TEST, "LinkTest001 end.");
}

/**
* @tc.name: LinkTest002
* @tc.desc: Abnormal testcase of Link,because url and description are equal to MAX_TEXT_LEN
* @tc.type: FUNC
*/
HWTEST_F(LinkTest, LinkTest002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "LinkTest002 begin.");
    const std::string url(MAX_TEXT_LEN, 'a');
    const std::string description(MAX_TEXT_LEN, 'a');
    Link link(url, description);
    EXPECT_NE(link.dataType_, HYPERLINK);
    EXPECT_NE(link.url_, url);
    EXPECT_NE(link.description_, description);
    LOG_INFO(UDMF_TEST, "LinkTest002 end.");
}

/**
* @tc.name: LinkTest003
* @tc.desc: Abnormal testcase of Link,because url and MAX_TEXT_LEN are equal
* @tc.type: FUNC
*/
HWTEST_F(LinkTest, LinkTest003, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "LinkTest003 begin.");
    const std::string url(MAX_TEXT_LEN, 'a');
    const std::string description(20, 'a');
    Link link(url, description);
    EXPECT_NE(link.dataType_, HYPERLINK);
    EXPECT_NE(link.url_, url);
    EXPECT_NE(link.description_, description);
    LOG_INFO(UDMF_TEST, "LinkTest003 end.");
}

/**
* @tc.name: LinkTest004
* @tc.desc: Abnormal testcase of Link,because description and MAX_TEXT_LEN are equal
* @tc.type: FUNC
*/
HWTEST_F(LinkTest, LinkTest004, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "LinkTest004 begin.");
    const std::string url(20, 'a');
    const std::string description(MAX_TEXT_LEN, 'a');
    Link link(url, description);
    EXPECT_NE(link.dataType_, HYPERLINK);
    EXPECT_NE(link.url_, url);
    EXPECT_NE(link.description_, description);
    LOG_INFO(UDMF_TEST, "LinkTest004 end.");
}

/**
* @tc.name: SetUrlTest001
* @tc.desc: Abnormal testcase of SetUrl,because url and MAX_TEXT_LEN are equal
* @tc.type: FUNC
*/
HWTEST_F(LinkTest, SetUrlTest001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetUrlTest001 begin.");
    const std::string url(MAX_TEXT_LEN, 'a');
    Link link;
    link.SetUrl(url);
    EXPECT_NE(link.url_, url);
    LOG_INFO(UDMF_TEST, "SetUrlTest001 end.");
}

/**
* @tc.name: SetDescription001
* @tc.desc: Abnormal testcase of SetDescription,because url and MAX_TEXT_LEN are equal
* @tc.type: FUNC
*/
HWTEST_F(LinkTest, SetDescription001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetDescription001 begin.");
    const std::string description(MAX_TEXT_LEN, 'a');
    Link link;
    link.SetDescription(description);
    EXPECT_NE(link.description_, description);
    LOG_INFO(UDMF_TEST, "SetDescription001 end.");
}

/**
* @tc.name: SetDescription002
* @tc.desc: Abnormal testcase of SetDescription,because description and MAX_TEXT_LEN are equal
* @tc.type: FUNC
*/
HWTEST_F(LinkTest, SetDescription002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetDescription002 begin.");
    const std::string description(MAX_TEXT_LEN, 'a');
    Link link;
    link.SetDescription(description);
    EXPECT_NE(link.description_, description);
    LOG_INFO(UDMF_TEST, "SetDescription002 end.");
}
} // OHOS::Test