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
#define LOG_TAG "ApplicationUtdJsonParserTest"

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
* @tc.name: SetUrlTest005
* @tc.desc: Abnormal testcase of SetUrl,because url and MAX_TEXT_LEN are equal
* @tc.type: FUNC
*/
HWTEST_F(LinkTest, SetUrlTest005, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetUrlTest005 begin.");
    const std::string url(MAX_TEXT_LEN, 'a');
    Link link;
    link.SetUrl(url);
    EXPECT_NE(link.url_, url);
    LOG_INFO(UDMF_TEST, "SetUrlTest005 end.");
}

/**
* @tc.name: SetDescription006
* @tc.desc: Abnormal testcase of SetDescription,because url and MAX_TEXT_LEN are equal
* @tc.type: FUNC
*/
HWTEST_F(LinkTest, SetDescription006, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetDescription006 begin.");
    const std::string description(MAX_TEXT_LEN, 'a');
    Link link;
    link.SetDescription(description);
    EXPECT_NE(link.description_, description);
    LOG_INFO(UDMF_TEST, "SetDescription006 end.");
}

/**
* @tc.name: SetDescription007
* @tc.desc: Abnormal testcase of SetDescription,because description and MAX_TEXT_LEN are equal
* @tc.type: FUNC
*/
HWTEST_F(LinkTest, SetDescription007, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetDescription007 begin.");
    const std::string description(MAX_TEXT_LEN, 'a');
    Link link;
    link.SetDescription(description);
    EXPECT_NE(link.description_, description);
    LOG_INFO(UDMF_TEST, "SetDescription007 end.");
}

/**
* @tc.name: GetValue008
* @tc.desc: Abnormal testcase of GetValue,because description and MAX_TEXT_LEN are equal
* @tc.type: FUNC
*/
HWTEST_F(LinkTest, GetValue008, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetValue008 begin.");
    Link link;
    link.value_ = std::monostate{};
    link.url_ = "url_";
    link.description_ = "description_";
    link.GetValue();
    auto object = std::get<std::shared_ptr<Object>>(link.value_);
    auto details_ = std::get<std::shared_ptr<Object>>(object->value_[Link::DETAILS]);
    EXPECT_EQ(std::get<std::string>(object->value_[Link::UNIFORM_DATA_TYPE]), "general.hyperlink");
    EXPECT_EQ(std::get<std::string>(object->value_[Link::URL]), link.url_);
    EXPECT_EQ(std::get<std::string>(object->value_[Link::DESCRIPTION]), link.description_);
    EXPECT_EQ(details_->value_.size(), 0);
    LOG_INFO(UDMF_TEST, "GetValue008 end.");
}
} // OHOS::Test