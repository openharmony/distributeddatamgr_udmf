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
#include "xml_loader.h"

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
* @tc.name: SetHtmlContent001
* @tc.desc: Abnormal testcase of SetHtmlContent, because htmlContent and MAX_TEXT_LEN are equal
* @tc.type: FUNC
*/
HWTEST_F(HtmlTest, SetHtmlContent001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetHtmlContent001 begin.");
    const std::string htmlContent(20 * 1024 * 1024, 'a');
    Html html;
    html.SetHtmlContent(htmlContent);
    EXPECT_NE(html.htmlContent_, htmlContent);
    LOG_INFO(UDMF_TEST, "SetHtmlContent001 end.");
}

/**
* @tc.name: SetPlainContent002
* @tc.desc: Abnormal testcase of SetPlainContent, because plainContent and MAX_TEXT_LEN are equal
* @tc.type: FUNC
*/
HWTEST_F(HtmlTest, SetPlainContent002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetPlainContent002 begin.");
    const std::string plainContent(20 * 1024 * 1024, 'a');
    Html html;
    html.SetPlainContent(plainContent);
    EXPECT_NE(html.plainContent_, plainContent);
    LOG_INFO(UDMF_TEST, "SetPlainContent002 end.");
}

/**
* @tc.name: ExtractImgSrc001
* @tc.desc: Normal testcase of ExtractImgSrc
* @tc.type: FUNC
*/
HWTEST_F(HtmlTest, ExtractImgSrc001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "ExtractImgSrc001 begin.");
    XmlLoader xmlLoader;

    std::string html = R"HTML(
        <html>
            <body>
                <img src="file:///example.com/img1.png" />
                <img src="file:///test.com/img2.jpg" />
                <img src="file:///cdn.com/photo.png" />
            </body>
        </html>
    )HTML";

    std::vector<std::string> uris = xmlLoader.ExtractImgSrc(html);

    ASSERT_EQ(uris.size(), 3);
    EXPECT_EQ(uris[0], "file:///example.com/img1.png");
    EXPECT_EQ(uris[1], "file:///test.com/img2.jpg");
    EXPECT_EQ(uris[2], "file:///cdn.com/photo.png");
    LOG_INFO(UDMF_TEST, "ExtractImgSrc001 end.");
}

/**
* @tc.name: ExtractImgSrc002
* @tc.desc: Abnormal testcase of ExtractImgSrc, no valid img src
* @tc.type: FUNC
*/
HWTEST_F(HtmlTest, ExtractImgSrc002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "ExtractImgSrc002 begin.");
    XmlLoader xmlLoader;

    std::string html = R"HTML(
        <html>
            <body>
                <img src="https://example.com/img1.png" />
                <img src="http://test.com/img2.jpg" />
                <img src="file://cdn.com/photo.png" />
            </body>
        </html>
    )HTML";

    std::vector<std::string> uris = xmlLoader.ExtractImgSrc(html);
    EXPECT_TRUE(uris.empty());
    LOG_INFO(UDMF_TEST, "ExtractImgSrc002 end.");
}

/**
* @tc.name: ExtractImgSrc003
* @tc.desc: Abnormal testcase of ExtractImgSrc, no img tag
* @tc.type: FUNC
*/
HWTEST_F(HtmlTest, ExtractImgSrc003, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "ExtractImgSrc003 begin.");
    XmlLoader xmlLoader;

    std::string html = R"HTML(
        <html>
            <body>
                <p>No images here</p>
            </body>
        </html>
    )HTML";
    std::vector<std::string> uris = xmlLoader.ExtractImgSrc(html);
    EXPECT_TRUE(uris.empty());
    LOG_INFO(UDMF_TEST, "ExtractImgSrc003 end.");
}

/**
* @tc.name: ExtractImgSrc004
* @tc.desc: Abnormal testcase of ExtractImgSrc, no src attribute
* @tc.type: FUNC
*/
HWTEST_F(HtmlTest, ExtractImgSrc004, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "ExtractImgSrc004 begin.");
    XmlLoader xmlLoader;

    std::string html = R"HTML(
        <html>
            <body>
                <img alt="no src" />
            </body>
        </html>
    )HTML";

    std::vector<std::string> uris = xmlLoader.ExtractImgSrc(html);
    EXPECT_TRUE(uris.empty());
    LOG_INFO(UDMF_TEST, "ExtractImgSrc004 end.");
}

/**
* @tc.name: ExtractImgSrc005
* @tc.desc: Abnormal testcase of ExtractImgSrc, mixed valid and invalid img src
* @tc.type: FUNC
*/
HWTEST_F(HtmlTest, ExtractImgSrc005, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "ExtractImgSrc005 begin.");
    XmlLoader xmlLoader;

    std::string html = R"HTML(
        <html>
            <body>
                <img src="https://valid.com/1.png" />
                <img src="file:///invalid/local.png" />
                <img src="http://another.com/2.jpg" />
                <img src="file://another/local.png" />
            </body>
        </html>
    )HTML";

    std::vector<std::string> uris = xmlLoader.ExtractImgSrc(html);
    EXPECT_EQ(uris.size(), 1);
    EXPECT_EQ(uris[0], "file:///invalid/local.png");
    LOG_INFO(UDMF_TEST, "ExtractImgSrc005 end.");
}

/**
* @tc.name: ExtractImgSrc006
* @tc.desc: Normal testcase of ExtractImgSrc, in span tag
* @tc.type: FUNC
*/
HWTEST_F(HtmlTest, ExtractImgSrc006, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "ExtractImgSrc006 begin.");
    XmlLoader xmlLoader;

    std::string html = R"HTML(
        <html>
            <body>
                <span>
                    <img src="file:///inside-span.com/img.png" />
                </span>
                <img src="file:///outside-span.com/img.png" />
            </body>
        </html>
    )HTML";

    std::vector<std::string> uris = xmlLoader.ExtractImgSrc(html);
    EXPECT_EQ(uris.size(), 2);
    EXPECT_EQ(uris[0], "file:///inside-span.com/img.png");
    EXPECT_EQ(uris[1], "file:///outside-span.com/img.png");
    LOG_INFO(UDMF_TEST, "ExtractImgSrc006 end.");
}

/**
* @tc.name: ExtractImgSrc007
* @tc.desc: Normal testcase of ExtractImgSrc, in input tag
* @tc.type: FUNC
*/
HWTEST_F(HtmlTest, ExtractImgSrc007, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "ExtractImgSrc007 begin.");
    XmlLoader xmlLoader;

    std::string html = R"HTML(
        <html>
            <body>
                <input value="<img src="file:///outside-span.com/img.png" /> />
            </body>
        </html>
    )HTML";

    std::vector<std::string> uris = xmlLoader.ExtractImgSrc(html);
    EXPECT_EQ(uris.size(), 0);
    LOG_INFO(UDMF_TEST, "ExtractImgSrc007 end.");
}

/**
* @tc.name: ExtractImgSrc008
* @tc.desc: Normal testcase of ExtractImgSrc, in textarea tag
* @tc.type: FUNC
*/
HWTEST_F(HtmlTest, ExtractImgSrc008, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "ExtractImgSrc008 begin.");
    XmlLoader xmlLoader;

    std::string html = R"HTML(
        <html>
            <body>
                <textarea>
                    <img src="file:///inside-span.com/img.png" />
                </textarea>
            </body>
        </html>
    )HTML";

    std::vector<std::string> uris = xmlLoader.ExtractImgSrc(html);
    EXPECT_EQ(uris.size(), 0);
    LOG_INFO(UDMF_TEST, "ExtractImgSrc008 end.");
}

/**
* @tc.name: ExtractImgSrc009
* @tc.desc: Normal testcase of ExtractImgSrc, in comment tag
* @tc.type: FUNC
*/
HWTEST_F(HtmlTest, ExtractImgSrc009, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "ExtractImgSrc009 begin.");
    XmlLoader xmlLoader;

    std::string html = R"HTML(
        <html>
            <body>
                <!-- img src="file:///invalid/local.png" -->
                <!-- <img src="file:///inside-span.com/img.png" /> -->
            </body>
        </html>
    )HTML";

    std::vector<std::string> uris = xmlLoader.ExtractImgSrc(html);
    EXPECT_EQ(uris.size(), 0);
    LOG_INFO(UDMF_TEST, "ExtractImgSrc009 end.");
}
} // OHOS::Test