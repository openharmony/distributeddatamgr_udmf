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
#define LOG_TAG "TextTest"

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

class TextTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void TextTest::SetUpTestCase()
{
}

void TextTest::TearDownTestCase()
{
}

void TextTest::SetUp()
{
}

void TextTest::TearDown()
{
}

/**
* @tc.name: Text001
* @tc.desc: Normal testcase of Text
* @tc.type: FUNC
*/
HWTEST_F(TextTest, Text001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "Text001 begin.");
    UDDetails variantMap;
    variantMap.insert({ "details", "details"});
    Text text(variantMap);
    EXPECT_EQ(text.details_, variantMap);
    LOG_INFO(UDMF_TEST, "Text001 end.");
}

/**
* @tc.name: InitObject001
* @tc.desc: Normal testcase of InitObject
* @tc.type: FUNC
*/
HWTEST_F(TextTest, InitObject001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "InitObject001 begin.");
    Text text;
    text.details_.insert({ "first", "second" });
    text.InitObject();
    auto object = std::get<std::shared_ptr<Object>>(text.value_);
    auto details = std::get<std::shared_ptr<Object>>(object->value_[Text::DETAILS]);
    EXPECT_NE(details->value_.size(), 0);
    LOG_INFO(UDMF_TEST, "InitObject001 end.");
}
} // OHOS::Test