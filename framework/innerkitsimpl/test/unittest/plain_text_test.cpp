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
#define LOG_TAG "PlainTextTest"

#include <unistd.h>
#include <gtest/gtest.h>
#include <string>

#include "logger.h"
#include "plain_text.h"
#include "udmf_capi_common.h"

using namespace testing::ext;
using namespace OHOS::UDMF;
using namespace OHOS;
namespace OHOS::Test {
using namespace std;

class PlainTextTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void PlainTextTest::SetUpTestCase()
{
}

void PlainTextTest::TearDownTestCase()
{
}

void PlainTextTest::SetUp()
{
}

void PlainTextTest::TearDown()
{
}

/**
* @tc.name: PlainText001
* @tc.desc: Abnormal testcase of PlainText, because content is equal to MAX_TEXT_LEN
* @tc.type: FUNC
*/
HWTEST_F(PlainTextTest, PlainText001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "PlainText001 begin.");
    const std::string content(MAX_TEXT_LEN, 'a');
    const std::string abstract = "abstract";
    PlainText plainText(content, abstract);
    EXPECT_NE(plainText.dataType_, PLAIN_TEXT);
    EXPECT_NE(plainText.content_, content);
    EXPECT_NE(plainText.abstract_, abstract);
    LOG_INFO(UDMF_TEST, "PlainText001 end.");
}

/**
* @tc.name: SetContent002
* @tc.desc: Abnormal testcase of SetContent, because text is equal to MAX_TEXT_LEN
* @tc.type: FUNC
*/
HWTEST_F(PlainTextTest, SetContent002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetContent002 begin.");
    const std::string text(MAX_TEXT_LEN, 'a');
    PlainText plainText;
    plainText.SetContent(text);
    EXPECT_NE(plainText.content_, text);
    LOG_INFO(UDMF_TEST, "SetContent002 end.");
}

/**
* @tc.name: SetAbstract003
* @tc.desc: Abnormal testcase of SetAbstract, because abstract is equal to MAX_TEXT_LEN
* @tc.type: FUNC
*/
HWTEST_F(PlainTextTest, SetAbstract003, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetAbstract003 begin.");
    const std::string abstract(MAX_TEXT_LEN, 'a');
    PlainText plainText;
    plainText.SetAbstract(abstract);
    EXPECT_NE(plainText.abstract_, abstract);
    LOG_INFO(UDMF_TEST, "SetAbstract003 end.");
}
} // OHOS::Test