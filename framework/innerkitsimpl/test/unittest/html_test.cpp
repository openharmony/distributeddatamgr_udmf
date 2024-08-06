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
#define LOG_TAG "HtmlTest"

#include <unistd.h>
#include <gtest/gtest.h>
#include <string>

#include "logger.h"
#include "html.h"

using namespace testing::ext;
using namespace OHOS::UDMF;
using namespace OHOS;
namespace OHOS::Test {
using namespace std;

class HtmlTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void HtmlTest::SetUpTestCase()
{
}

void HtmlTest::TearDownTestCase()
{
}

void HtmlTest::SetUp()
{
}

void HtmlTest::TearDown()
{
}

/**
* @tc.name: Html001
* @tc.desc: Abnormal testcase of Html, because htmlContent and plainContent are longer than MAX_TEXT_LEN
* @tc.type: FUNC
*/
HWTEST_F(HtmlTest, Html001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "Html001 begin.");
    const std::string htmlContent(20 * 1024 * 1024, 'a');
    const std::string plainContent(20 * 1024 * 1024, 'a');
    Html html(htmlContent, plainContent);
    EXPECT_NE(html.dataType_, HTML);
    EXPECT_TRUE(html.htmlContent_.empty());
    EXPECT_TRUE(html.plainContent_.empty());
    LOG_INFO(UDMF_TEST, "Html001 end.");
}

/**
* @tc.name: Html002
* @tc.desc: Abnormal testcase of Html, because plainContent are longer than MAX_TEXT_LEN
* @tc.type: FUNC
*/
HWTEST_F(HtmlTest, Html002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "Html002 begin.");
    const std::string htmlContent(20, 'a');
    const std::string plainContent(20 * 1024 * 1024, 'a');
    Html html(htmlContent, plainContent);
    EXPECT_NE(html.dataType_, HTML);
    EXPECT_TRUE(html.htmlContent_.empty());
    EXPECT_TRUE(html.plainContent_.empty());
    LOG_INFO(UDMF_TEST, "Html002 end.");
}

/**
* @tc.name: Html003
* @tc.desc: Abnormal testcase of Html, because htmlContent are longer than MAX_TEXT_LEN
* @tc.type: FUNC
*/
HWTEST_F(HtmlTest, Html003, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "Html003 begin.");
    const std::string htmlContent(20, 'a');
    const std::string plainContent(20 * 1024 * 1024, 'a');
    Html html(htmlContent, plainContent);
    EXPECT_NE(html.dataType_, HTML);
    EXPECT_TRUE(html.htmlContent_.empty());
    EXPECT_TRUE(html.plainContent_.empty());
    LOG_INFO(UDMF_TEST, "Html003 end.");
}

/**
* @tc.name: Html004
* @tc.desc: Normal testcase of Html
* @tc.type: FUNC
*/
HWTEST_F(HtmlTest, Html004, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "Html004 begin.");
    const std::string htmlContent(20, 'a');
    const std::string plainContent(20, 'a');
    Html html(htmlContent, plainContent);
    EXPECT_EQ(html.dataType_, HTML);
    EXPECT_EQ(html.htmlContent_, htmlContent);
    EXPECT_EQ(html.plainContent_, plainContent);
    LOG_INFO(UDMF_TEST, "Html004 end.");
}

/**
* @tc.name: Html005
* @tc.desc: Normal testcase of Html
* @tc.type: FUNC
*/
HWTEST_F(HtmlTest, Html005, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "Html005 begin.");
    UDType type = UDType::ENTITY;
    ValueType value = "value";
    Html html(type, value);
    EXPECT_EQ(html.htmlContent_, std::get<std::string>(value));
    LOG_INFO(UDMF_TEST, "Html005 end.");
}
} // OHOS::Test