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
#include "udmf_capi_common.h"
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
* @tc.desc: Abnormal testcase of Html, because htmlContent and plainContent are equal to MAX_TEXT_LEN
* @tc.type: FUNC
*/
HWTEST_F(HtmlTest, Html001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "Html001 begin.");
    const std::string htmlContent(MAX_TEXT_LEN, 'a');
    const std::string plainContent(MAX_TEXT_LEN, 'a');
    Html html(htmlContent, plainContent);
    EXPECT_NE(html.dataType_, HTML);
    EXPECT_TRUE(html.htmlContent_.empty());
    EXPECT_TRUE(html.plainContent_.empty());
    LOG_INFO(UDMF_TEST, "Html001 end.");
}

/**
* @tc.name: Html002
* @tc.desc: Abnormal testcase of Html, because plainContent and MAX_TEXT_LEN are equal
* @tc.type: FUNC
*/
HWTEST_F(HtmlTest, Html002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "Html002 begin.");
    const std::string htmlContent(20, 'a');
    const std::string plainContent(MAX_TEXT_LEN, 'a');
    Html html(htmlContent, plainContent);
    EXPECT_NE(html.dataType_, HTML);
    EXPECT_TRUE(html.htmlContent_.empty());
    EXPECT_TRUE(html.plainContent_.empty());
    LOG_INFO(UDMF_TEST, "Html002 end.");
}

/**
* @tc.name: Html003
* @tc.desc: Abnormal testcase of Html, because htmlContent and MAX_TEXT_LEN are equal
* @tc.type: FUNC
*/
HWTEST_F(HtmlTest, Html003, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "Html003 begin.");
    const std::string htmlContent(20, 'a');
    const std::string plainContent(MAX_TEXT_LEN, 'a');
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

/**
* @tc.name: SetHtmlContent006
* @tc.desc: Abnormal testcase of SetHtmlContent, because htmlContent and MAX_TEXT_LEN are equal
* @tc.type: FUNC
*/
HWTEST_F(HtmlTest, SetHtmlContent006, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetHtmlContent006 begin.");
    const std::string htmlContent(20 * 1024 * 1024, 'a');
    Html html;
    html.SetHtmlContent(htmlContent);
    EXPECT_NE(html.htmlContent_, htmlContent);
    LOG_INFO(UDMF_TEST, "SetHtmlContent006 end.");
}

/**
* @tc.name: SetPlainContent007
* @tc.desc: Abnormal testcase of SetPlainContent, because plainContent and MAX_TEXT_LEN are equal
* @tc.type: FUNC
*/
HWTEST_F(HtmlTest, SetPlainContent007, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetPlainContent007 begin.");
    const std::string plainContent(20 * 1024 * 1024, 'a');
    Html html;
    html.SetPlainContent(plainContent);
    EXPECT_NE(html.plainContent_, plainContent);
    LOG_INFO(UDMF_TEST, "SetPlainContent007 end.");
}

/**
* @tc.name: GetValue008
* @tc.desc: Normal testcase of GetValue
* @tc.type: FUNC
*/
HWTEST_F(HtmlTest, GetValue008, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetValue008 begin.");
    Html html;
    html.value_ = std::monostate{};
    html.htmlContent_ = "htmlContent";
    html.plainContent_ = "plainContent";
    html.GetValue();
    auto object = std::get<std::shared_ptr<Object>>(html.value_);
    auto details_ = std::get<std::shared_ptr<Object>>(object->value_[Html::DETAILS]);
    EXPECT_EQ(std::get<std::string>(object->value_[UNIFORM_DATA_TYPE]), "general.html");
    EXPECT_EQ(std::get<std::string>(object->value_[HTML_CONTENT]), html.htmlContent_);
    EXPECT_EQ(std::get<std::string>(object->value_[Html::PLAINT_CONTENT]), html.plainContent_);
    EXPECT_EQ(details_->value_.size(), 0);
    LOG_INFO(UDMF_TEST, "GetValue008 end.");
}
} // OHOS::Test