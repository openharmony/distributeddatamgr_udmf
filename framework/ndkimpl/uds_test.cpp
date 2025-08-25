/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define LOG_TAG "UdsTest"

#include <gtest/gtest.h>
#include <unistd.h>

#include "token_setproc.h"
#include "accesstoken_kit.h"
#include "nativetoken_kit.h"
#include "logger.h"
#include "pixelmap_native_impl.h"
#include "uds.h"
#include "udmf_capi_common.h"
#include "udmf_meta.h"
#include "udmf_err_code.h"

using namespace testing::ext;
using namespace OHOS::Security::AccessToken;
using namespace OHOS::UDMF;
using namespace OHOS;

namespace OHOS::Test {
class UdsTest : public testing::Test {
public:
    static void SetUpTestCase(void);
    static void TearDownTestCase(void);
    void SetUp();
    void TearDown();
    static bool CheckUnsignedChar(unsigned char* dst, unsigned char* src, int size);
};

void UdsTest::SetUpTestCase(void) {}

void UdsTest::TearDownTestCase(void) {}

void UdsTest::SetUp(void) {}

void UdsTest::TearDown(void) {}

bool UdsTest::CheckUnsignedChar(unsigned char* dst, unsigned char* src, int size)
{
    EXPECT_NE(dst, nullptr);
    EXPECT_NE(src, nullptr);
    for (int i = 0; i < size; ++i) {
        if (dst[i] != src[i]) {
            return false;
        }
    }
    return true;
}

/**
 * @tc.name: OH_UdsPlainText_Create_001
 * @tc.desc: Normal testcase of OH_UdsPlainText_Create
 * @tc.type: FUNC
 */
HWTEST_F(UdsTest, OH_UdsPlainText_Create_001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "OH_UdsPlainText_Create_001 begin.");
    auto plainText = OH_UdsPlainText_Create();
    EXPECT_EQ(UDMF_META_PLAIN_TEXT, *(std::get_if<std::string>(&(plainText->obj->value_[UNIFORM_DATA_TYPE]))));
    OH_UdsPlainText_Destroy(plainText);
    LOG_INFO(UDMF_TEST, "OH_UdsPlainText_Create_001 end.");
}

/**
 * @tc.name: OH_UdsPlainText_GetType_001
 * @tc.desc: Normal testcase of OH_UdsPlainText_GetType
 * @tc.type: FUNC
 */
HWTEST_F(UdsTest, OH_UdsPlainText_GetType_001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "OH_UdsPlainText_GetType_001 begin.");
    auto plainText = OH_UdsPlainText_Create();
    EXPECT_EQ(UDMF_META_PLAIN_TEXT, std::string(OH_UdsPlainText_GetType(plainText)));
    OH_UdsPlainText_Destroy(plainText);

    OH_UdsPlainText* plainTextNullptr = nullptr;
    EXPECT_EQ(nullptr, OH_UdsPlainText_GetType(plainTextNullptr));

    plainTextNullptr = new OH_UdsPlainText;
    EXPECT_EQ(nullptr, OH_UdsPlainText_GetType(plainTextNullptr));
    OH_UdsPlainText_Destroy(plainTextNullptr);
    LOG_INFO(UDMF_TEST, "OH_UdsPlainText_GetType_001 end.");
}

/**
 * @tc.name: OH_UdsPlainText_GetContent_001
 * @tc.desc: Normal testcase of OH_UdsPlainText_GetContent
 * @tc.type: FUNC
 */
HWTEST_F(UdsTest, OH_UdsPlainText_GetContent_001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "OH_UdsPlainText_GetContent_001 begin.");
    auto plainText = OH_UdsPlainText_Create();
    plainText->obj->value_[CONTENT] = "doing something";
    EXPECT_EQ("doing something", std::string(OH_UdsPlainText_GetContent(plainText)));
    OH_UdsPlainText_Destroy(plainText);

    OH_UdsPlainText* plainTextNullptr = nullptr;
    EXPECT_EQ(nullptr, OH_UdsPlainText_GetContent(plainTextNullptr));

    plainTextNullptr = new OH_UdsPlainText;
    EXPECT_EQ(nullptr, OH_UdsPlainText_GetContent(plainTextNullptr));
    OH_UdsPlainText_Destroy(plainTextNullptr);
    LOG_INFO(UDMF_TEST, "OH_UdsPlainText_GetContent_001 end.");
}

/**
 * @tc.name: OH_UdsPlainText_GetAbstract_001
 * @tc.desc: Normal testcase of OH_UdsPlainText_GetAbstract
 * @tc.type: FUNC
 */
HWTEST_F(UdsTest, OH_UdsPlainText_GetAbstract_001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "OH_UdsPlainText_GetAbstract_001 begin.");
    auto plainText = OH_UdsPlainText_Create();
    plainText->obj->value_[ABSTRACT] = "doing something";
    EXPECT_EQ("doing something", std::string(OH_UdsPlainText_GetAbstract(plainText)));
    OH_UdsPlainText_Destroy(plainText);

    OH_UdsPlainText* plainTextNullptr = nullptr;
    EXPECT_EQ(nullptr, OH_UdsPlainText_GetAbstract(plainTextNullptr));

    plainTextNullptr = new OH_UdsPlainText;
    EXPECT_EQ(nullptr, OH_UdsPlainText_GetAbstract(plainTextNullptr));
    OH_UdsPlainText_Destroy(plainTextNullptr);
    LOG_INFO(UDMF_TEST, "OH_UdsPlainText_GetAbstract_001 end.");
}

/**
 * @tc.name: OH_UdsPlainText_SetContent_001
 * @tc.desc: Normal testcase of OH_UdsPlainText_SetContent
 * @tc.type: FUNC
 */
HWTEST_F(UdsTest, OH_UdsPlainText_SetContent_001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "OH_UdsPlainText_SetContent_001 begin.");
    auto plainText = OH_UdsPlainText_Create();
    int result = OH_UdsPlainText_SetContent(plainText, "doing something");
    EXPECT_EQ(UDMF_E_OK, result);
    EXPECT_EQ("doing something", std::string(OH_UdsPlainText_GetContent(plainText)));

    result = OH_UdsPlainText_SetContent(nullptr, "doing something");
    EXPECT_EQ(UDMF_E_INVALID_PARAM, result);

    result = OH_UdsPlainText_SetContent(plainText, nullptr);
    EXPECT_EQ(UDMF_E_INVALID_PARAM, result);

    plainText->obj = nullptr;
    result = OH_UdsPlainText_SetContent(plainText, "doing something");
    EXPECT_EQ(UDMF_E_INVALID_PARAM, result);
    OH_UdsPlainText_Destroy(plainText);
    LOG_INFO(UDMF_TEST, "OH_UdsPlainText_SetContent_001 end.");
}

/**
 * @tc.name: OH_UdsPlainText_SetAbstract_001
 * @tc.desc: Normal testcase of OH_UdsPlainText_SetAbstract
 * @tc.type: FUNC
 */
HWTEST_F(UdsTest, OH_UdsPlainText_SetAbstract_001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "OH_UdsPlainText_SetAbstract_001 begin.");
    auto plainText = OH_UdsPlainText_Create();
    int result = OH_UdsPlainText_SetAbstract(plainText, "doing something");
    EXPECT_EQ(UDMF_E_OK, result);
    EXPECT_EQ("doing something", std::string(OH_UdsPlainText_GetAbstract(plainText)));

    result = OH_UdsPlainText_SetAbstract(nullptr, "doing something");
    EXPECT_EQ(UDMF_E_INVALID_PARAM, result);

    result = OH_UdsPlainText_SetAbstract(plainText, nullptr);
    EXPECT_EQ(UDMF_E_INVALID_PARAM, result);

    plainText->obj = nullptr;
    result = OH_UdsPlainText_SetAbstract(plainText, "doing something");
    EXPECT_EQ(UDMF_E_INVALID_PARAM, result);
    OH_UdsPlainText_Destroy(plainText);
    LOG_INFO(UDMF_TEST, "OH_UdsPlainText_SetAbstract_001 end.");
}

/**
 * @tc.name: OH_UdsHyperlink_Create_001
 * @tc.desc: Normal testcase of OH_UdsHyperlink_Create
 * @tc.type: FUNC
 */
HWTEST_F(UdsTest, OH_UdsHyperlink_Create_001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "OH_UdsHyperlink_Create_001 begin.");
    auto hyperlink = OH_UdsHyperlink_Create();
    EXPECT_EQ(UDMF_META_HYPERLINK, *(std::get_if<std::string>(&(hyperlink->obj)->value_[UNIFORM_DATA_TYPE])));
    OH_UdsHyperlink_Destroy(hyperlink);
    LOG_INFO(UDMF_TEST, "OH_UdsHyperlink_Create_001 end.");
}

/**
 * @tc.name: OH_UdsHyperlink_GetType_001
 * @tc.desc: Normal testcase of OH_UdsHyperlink_GetType
 * @tc.type: FUNC
 */
HWTEST_F(UdsTest, OH_UdsHyperlink_GetType_001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "OH_UdsHyperlink_GetType_001 begin.");
    auto hyperlink = OH_UdsHyperlink_Create();
    EXPECT_EQ(UDMF_META_HYPERLINK, std::string(OH_UdsHyperlink_GetType(hyperlink)));
    OH_UdsHyperlink_Destroy(hyperlink);

    OH_UdsHyperlink* hyperlinkNullptr = nullptr;
    EXPECT_EQ(nullptr, OH_UdsHyperlink_GetType(hyperlinkNullptr));

    hyperlinkNullptr = new OH_UdsHyperlink;
    EXPECT_EQ(nullptr, OH_UdsHyperlink_GetType(hyperlinkNullptr));
    OH_UdsHyperlink_Destroy(hyperlinkNullptr);
    LOG_INFO(UDMF_TEST, "OH_UdsHyperlink_GetType_001 end.");
}

/**
 * @tc.name: OH_UdsHyperlink_GetUrl_001
 * @tc.desc: Normal testcase of OH_UdsHyperlink_GetUrl
 * @tc.type: FUNC
 */
HWTEST_F(UdsTest, OH_UdsHyperlink_GetUrl_001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "OH_UdsHyperlink_GetUrl_001 begin.");
    auto hyperlink = OH_UdsHyperlink_Create();
    hyperlink->obj->value_[URL] = "www.xxx.com";
    EXPECT_EQ("www.xxx.com", std::string(OH_UdsHyperlink_GetUrl(hyperlink)));
    OH_UdsHyperlink_Destroy(hyperlink);

    OH_UdsHyperlink* hyperlinkNullptr = nullptr;
    EXPECT_EQ(nullptr, OH_UdsHyperlink_GetUrl(hyperlinkNullptr));

    hyperlinkNullptr = new OH_UdsHyperlink;
    EXPECT_EQ(nullptr, OH_UdsHyperlink_GetUrl(hyperlinkNullptr));
    OH_UdsHyperlink_Destroy(hyperlinkNullptr);
    LOG_INFO(UDMF_TEST, "OH_UdsHyperlink_GetUrl_001 end.");
}

/**
 * @tc.name: OH_UdsHyperlink_GetDescription_001
 * @tc.desc: Normal testcase of OH_UdsHyperlink_GetDescription
 * @tc.type: FUNC
 */
HWTEST_F(UdsTest, OH_UdsHyperlink_GetDescription_001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "OH_UdsHyperlink_GetDescription_001 begin.");
    auto hyperlink = OH_UdsHyperlink_Create();
    hyperlink->obj->value_[DESCRIPTION] = "do something";
    EXPECT_EQ("do something", std::string(OH_UdsHyperlink_GetDescription(hyperlink)));
    OH_UdsHyperlink_Destroy(hyperlink);

    OH_UdsHyperlink* hyperlinkNullptr = nullptr;
    EXPECT_EQ(nullptr, OH_UdsHyperlink_GetDescription(hyperlinkNullptr));

    hyperlinkNullptr = new OH_UdsHyperlink;
    EXPECT_EQ(nullptr, OH_UdsHyperlink_GetDescription(hyperlinkNullptr));
    OH_UdsHyperlink_Destroy(hyperlinkNullptr);
    LOG_INFO(UDMF_TEST, "OH_UdsHyperlink_GetDescription_001 end.");
}

/**
 * @tc.name: OH_UdsHyperlink_SetUrl_001
 * @tc.desc: Normal testcase of OH_UdsHyperlink_SetUrl
 * @tc.type: FUNC
 */
HWTEST_F(UdsTest, OH_UdsHyperlink_SetUrl_001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "OH_UdsHyperlink_SetUrl_001 begin.");
    auto hyperlink = OH_UdsHyperlink_Create();
    int result = OH_UdsHyperlink_SetUrl(hyperlink, "www.xxx.com");
    EXPECT_EQ(UDMF_E_OK, result);
    EXPECT_EQ("www.xxx.com", std::string(OH_UdsHyperlink_GetUrl(hyperlink)));

    result = OH_UdsHyperlink_SetUrl(nullptr, "www.xxx.com");
    EXPECT_EQ(UDMF_E_INVALID_PARAM, result);

    result = OH_UdsHyperlink_SetUrl(hyperlink, nullptr);
    EXPECT_EQ(UDMF_E_INVALID_PARAM, result);

    hyperlink->obj = nullptr;
    result = OH_UdsHyperlink_SetUrl(hyperlink, "www.xxx.com");
    EXPECT_EQ(UDMF_E_INVALID_PARAM, result);
    OH_UdsHyperlink_Destroy(hyperlink);
    LOG_INFO(UDMF_TEST, "OH_UdsHyperlink_SetUrl_001 end.");
}

/**
 * @tc.name: OH_UdsHyperlink_SetDescription_001
 * @tc.desc: Normal testcase of OH_UdsHyperlink_SetDescription
 * @tc.type: FUNC
 */
HWTEST_F(UdsTest, OH_UdsHyperlink_SetDescription_001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "OH_UdsHyperlink_SetDescription_001 begin.");
    auto hyperlink = OH_UdsHyperlink_Create();
    int result = OH_UdsHyperlink_SetDescription(hyperlink, "doing something");
    EXPECT_EQ(UDMF_E_OK, result);
    EXPECT_EQ("doing something", std::string(OH_UdsHyperlink_GetDescription(hyperlink)));

    result = OH_UdsHyperlink_SetDescription(nullptr, "doing something");
    EXPECT_EQ(UDMF_E_INVALID_PARAM, result);

    result = OH_UdsHyperlink_SetDescription(hyperlink, nullptr);
    EXPECT_EQ(UDMF_E_INVALID_PARAM, result);

    hyperlink->obj = nullptr;
    result = OH_UdsHyperlink_SetDescription(hyperlink, "doing something");
    EXPECT_EQ(UDMF_E_INVALID_PARAM, result);
    OH_UdsHyperlink_Destroy(hyperlink);
    LOG_INFO(UDMF_TEST, "OH_UdsHyperlink_SetDescription_001 end.");
}

/**
 * @tc.name: OH_UdsHtml_Create_001
 * @tc.desc: Normal testcase of OH_UdsHtml_Create
 * @tc.type: FUNC
 */
HWTEST_F(UdsTest, OH_UdsHtml_Create_001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "OH_UdsHtml_Create_001 begin.");
    auto html = OH_UdsHtml_Create();
    EXPECT_EQ(UDMF_META_HTML, *(std::get_if<std::string>(&(html->obj)->value_[UNIFORM_DATA_TYPE])));
    OH_UdsHtml_Destroy(html);
    LOG_INFO(UDMF_TEST, "OH_UdsHtml_Create_001 end.");
}

/**
 * @tc.name: OH_UdsHtml_GetType_001
 * @tc.desc: Normal testcase of OH_UdsHtml_GetType
 * @tc.type: FUNC
 */
HWTEST_F(UdsTest, OH_UdsHtml_GetType_001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "OH_UdsHtml_GetType_001 begin.");
    auto html = OH_UdsHtml_Create();
    EXPECT_EQ(UDMF_META_HTML, std::string(OH_UdsHtml_GetType(html)));
    OH_UdsHtml_Destroy(html);

    OH_UdsHtml* htmlNullptr = nullptr;
    EXPECT_EQ(nullptr, OH_UdsHtml_GetType(htmlNullptr));

    htmlNullptr = new OH_UdsHtml;
    EXPECT_EQ(nullptr, OH_UdsHtml_GetType(htmlNullptr));
    OH_UdsHtml_Destroy(htmlNullptr);
    LOG_INFO(UDMF_TEST, "OH_UdsHtml_GetType_001 end.");
}

/**
 * @tc.name: OH_UdsHtml_GetContent_001
 * @tc.desc: Normal testcase of OH_UdsHtml_GetContent
 * @tc.type: FUNC
 */
HWTEST_F(UdsTest, OH_UdsHtml_GetContent_001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "OH_UdsHtml_GetContent_001 begin.");
    auto html = OH_UdsHtml_Create();
    html->obj->value_[HTML_CONTENT] = "htmlxxxxx";
    EXPECT_EQ("htmlxxxxx", std::string(OH_UdsHtml_GetContent(html)));
    OH_UdsHtml_Destroy(html);

    OH_UdsHtml* htmlNullptr = nullptr;
    EXPECT_EQ(nullptr, OH_UdsHtml_GetContent(htmlNullptr));

    htmlNullptr = new OH_UdsHtml;
    EXPECT_EQ(nullptr, OH_UdsHtml_GetContent(htmlNullptr));
    OH_UdsHtml_Destroy(htmlNullptr);
    LOG_INFO(UDMF_TEST, "OH_UdsHtml_GetContent_001 end.");
}

/**
 * @tc.name: OH_UdsHtml_GetPlainContent_001
 * @tc.desc: Normal testcase of OH_UdsHtml_GetPlainContent
 * @tc.type: FUNC
 */
HWTEST_F(UdsTest, OH_UdsHtml_GetPlainContent_001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "OH_UdsHtml_GetPlainContent_001 begin.");
    auto html = OH_UdsHtml_Create();
    html->obj->value_[PLAIN_CONTENT] = "do something";
    EXPECT_EQ("do something", std::string(OH_UdsHtml_GetPlainContent(html)));
    OH_UdsHtml_Destroy(html);

    OH_UdsHtml* htmlNullptr = nullptr;
    EXPECT_EQ(nullptr, OH_UdsHtml_GetPlainContent(htmlNullptr));

    htmlNullptr = new OH_UdsHtml;
    EXPECT_EQ(nullptr, OH_UdsHtml_GetPlainContent(htmlNullptr));
    OH_UdsHtml_Destroy(htmlNullptr);
    LOG_INFO(UDMF_TEST, "OH_UdsHtml_GetPlainContent_001 end.");
}

/**
 * @tc.name: OH_UdsHtml_SetContent_001
 * @tc.desc: Normal testcase of OH_UdsHtml_SetContent
 * @tc.type: FUNC
 */
HWTEST_F(UdsTest, OH_UdsHtml_SetContent_001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "OH_UdsHtml_SetContent_001 begin.");
    auto html = OH_UdsHtml_Create();
    int result = OH_UdsHtml_SetContent(html, "htmlxxx");
    EXPECT_EQ(UDMF_E_OK, result);
    EXPECT_EQ("htmlxxx", std::string(OH_UdsHtml_GetContent(html)));

    result = OH_UdsHtml_SetContent(nullptr, "htmlxxx");
    EXPECT_EQ(UDMF_E_INVALID_PARAM, result);

    result = OH_UdsHtml_SetContent(html, nullptr);
    EXPECT_EQ(UDMF_E_INVALID_PARAM, result);

    html->obj = nullptr;
    result = OH_UdsHtml_SetContent(html, "htmlxxx");
    EXPECT_EQ(UDMF_E_INVALID_PARAM, result);
    OH_UdsHtml_Destroy(html);
    LOG_INFO(UDMF_TEST, "OH_UdsHtml_SetContent_001 end.");
}

/**
 * @tc.name: OH_UdsHtml_SetPlainContent_001
 * @tc.desc: Normal testcase of OH_UdsHtml_SetPlainContent
 * @tc.type: FUNC
 */
HWTEST_F(UdsTest, OH_UdsHtml_SetPlainContent_001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "OH_UdsHtml_SetPlainContent_001 begin.");
    auto html = OH_UdsHtml_Create();
    int result = OH_UdsHtml_SetPlainContent(html, "doing something");
    EXPECT_EQ(UDMF_E_OK, result);
    EXPECT_EQ("doing something", std::string(OH_UdsHtml_GetPlainContent(html)));

    result = OH_UdsHtml_SetPlainContent(nullptr, "doing something");
    EXPECT_EQ(UDMF_E_INVALID_PARAM, result);

    result = OH_UdsHtml_SetPlainContent(html, nullptr);
    EXPECT_EQ(UDMF_E_INVALID_PARAM, result);

    html->obj = nullptr;
    result = OH_UdsHtml_SetPlainContent(html, "doing something");
    EXPECT_EQ(UDMF_E_INVALID_PARAM, result);
    OH_UdsHtml_Destroy(html);
    LOG_INFO(UDMF_TEST, "OH_UdsHtml_SetPlainContent_001 end.");
}

/**
 * @tc.name: OH_UdsAppItem_Create_001
 * @tc.desc: Normal testcase of OH_UdsAppItem_Create
 * @tc.type: FUNC
 */
HWTEST_F(UdsTest, OH_UdsAppItem_Create_001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "OH_UdsAppItem_Create_001 begin.");
    auto appItem = OH_UdsAppItem_Create();
    EXPECT_EQ(UDMF_META_OPENHARMONY_APP_ITEM, *(std::get_if<std::string>(&(appItem->obj)->value_[UNIFORM_DATA_TYPE])));
    OH_UdsAppItem_Destroy(appItem);
    LOG_INFO(UDMF_TEST, "OH_UdsAppItem_Create_001 end.");
}

/**
 * @tc.name: OH_UdsAppItem_GetType_001
 * @tc.desc: Normal testcase of OH_UdsAppItem_GetType
 * @tc.type: FUNC
 */
HWTEST_F(UdsTest, OH_UdsAppItem_GetType_001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "OH_UdsAppItem_GetType_001 begin.");
    auto appItem = OH_UdsAppItem_Create();
    EXPECT_EQ(UDMF_META_OPENHARMONY_APP_ITEM, std::string(OH_UdsAppItem_GetType(appItem)));
    OH_UdsAppItem_Destroy(appItem);

    OH_UdsAppItem* appItemNullptr = nullptr;
    EXPECT_EQ(nullptr, OH_UdsAppItem_GetType(appItemNullptr));

    appItemNullptr = new OH_UdsAppItem;
    EXPECT_EQ(nullptr, OH_UdsAppItem_GetType(appItemNullptr));
    OH_UdsAppItem_Destroy(appItemNullptr);
    LOG_INFO(UDMF_TEST, "OH_UdsAppItem_GetType_001 end.");
}

/**
 * @tc.name: OH_UdsAppItem_GetId_001
 * @tc.desc: Normal testcase of OH_UdsAppItem_GetId
 * @tc.type: FUNC
 */
HWTEST_F(UdsTest, OH_UdsAppItem_GetId_001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "OH_UdsAppItem_GetId_001 begin.");
    auto appItem = OH_UdsAppItem_Create();
    appItem->obj->value_[APP_ID] = "com.xxx";
    EXPECT_EQ("com.xxx", std::string(OH_UdsAppItem_GetId(appItem)));
    OH_UdsAppItem_Destroy(appItem);

    OH_UdsAppItem* appItemNullptr = nullptr;
    EXPECT_EQ(nullptr, OH_UdsAppItem_GetId(appItemNullptr));

    appItemNullptr = new OH_UdsAppItem;
    EXPECT_EQ(nullptr, OH_UdsAppItem_GetId(appItemNullptr));
    OH_UdsAppItem_Destroy(appItemNullptr);
    LOG_INFO(UDMF_TEST, "OH_UdsAppItem_GetId_001 end.");
}

/**
 * @tc.name: OH_UdsAppItem_GetName_001
 * @tc.desc: Normal testcase of OH_UdsAppItem_GetName
 * @tc.type: FUNC
 */
HWTEST_F(UdsTest, OH_UdsAppItem_GetName_001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "OH_UdsAppItem_GetName_001 begin.");
    auto appItem = OH_UdsAppItem_Create();
    appItem->obj->value_[APP_NAME] = "OH";
    EXPECT_EQ("OH", std::string(OH_UdsAppItem_GetName(appItem)));
    OH_UdsAppItem_Destroy(appItem);

    OH_UdsAppItem* appItemNullptr = nullptr;
    EXPECT_EQ(nullptr, OH_UdsAppItem_GetName(appItemNullptr));

    appItemNullptr = new OH_UdsAppItem;
    EXPECT_EQ(nullptr, OH_UdsAppItem_GetName(appItemNullptr));
    OH_UdsAppItem_Destroy(appItemNullptr);
    LOG_INFO(UDMF_TEST, "OH_UdsAppItem_GetName_001 end.");
}

/**
 * @tc.name: OH_UdsAppItem_GetIconId_001
 * @tc.desc: Normal testcase of OH_UdsAppItem_GetIconId
 * @tc.type: FUNC
 */
HWTEST_F(UdsTest, OH_UdsAppItem_GetIconId_001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "OH_UdsAppItem_GetIconId_001 begin.");
    auto appItem = OH_UdsAppItem_Create();
    appItem->obj->value_[APP_ICON_ID] = "icon";
    EXPECT_EQ("icon", std::string(OH_UdsAppItem_GetIconId(appItem)));
    OH_UdsAppItem_Destroy(appItem);

    OH_UdsAppItem* appItemNullptr = nullptr;
    EXPECT_EQ(nullptr, OH_UdsAppItem_GetIconId(appItemNullptr));

    appItemNullptr = new OH_UdsAppItem;
    EXPECT_EQ(nullptr, OH_UdsAppItem_GetIconId(appItemNullptr));
    OH_UdsAppItem_Destroy(appItemNullptr);
    LOG_INFO(UDMF_TEST, "OH_UdsAppItem_GetIconId_001 end.");
}

/**
 * @tc.name: OH_UdsAppItem_GetLabelId_001
 * @tc.desc: Normal testcase of OH_UdsAppItem_GetLabelId
 * @tc.type: FUNC
 */
HWTEST_F(UdsTest, OH_UdsAppItem_GetLabelId_001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "OH_UdsAppItem_GetLabelId_001 begin.");
    auto appItem = OH_UdsAppItem_Create();
    appItem->obj->value_[APP_LABEL_ID] = "label";
    EXPECT_EQ("label", std::string(OH_UdsAppItem_GetLabelId(appItem)));
    OH_UdsAppItem_Destroy(appItem);

    OH_UdsAppItem* appItemNullptr = nullptr;
    EXPECT_EQ(nullptr, OH_UdsAppItem_GetLabelId(appItemNullptr));

    appItemNullptr = new OH_UdsAppItem;
    EXPECT_EQ(nullptr, OH_UdsAppItem_GetLabelId(appItemNullptr));
    OH_UdsAppItem_Destroy(appItemNullptr);
    LOG_INFO(UDMF_TEST, "OH_UdsAppItem_GetLabelId_001 end.");
}

/**
 * @tc.name: OH_UdsAppItem_GetBundleName_001
 * @tc.desc: Normal testcase of OH_UdsAppItem_GetBundleName
 * @tc.type: FUNC
 */
HWTEST_F(UdsTest, OH_UdsAppItem_GetBundleName_001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "OH_UdsAppItem_GetBundleName_001 begin.");
    auto appItem = OH_UdsAppItem_Create();
    appItem->obj->value_[BUNDLE_NAME] = "bundle";
    EXPECT_EQ("bundle", std::string(OH_UdsAppItem_GetBundleName(appItem)));
    OH_UdsAppItem_Destroy(appItem);

    OH_UdsAppItem* appItemNullptr = nullptr;
    EXPECT_EQ(nullptr, OH_UdsAppItem_GetBundleName(appItemNullptr));

    appItemNullptr = new OH_UdsAppItem;
    EXPECT_EQ(nullptr, OH_UdsAppItem_GetBundleName(appItemNullptr));
    OH_UdsAppItem_Destroy(appItemNullptr);
    LOG_INFO(UDMF_TEST, "OH_UdsAppItem_GetBundleName_001 end.");
}

/**
 * @tc.name: OH_UdsAppItem_GetAbilityName_001
 * @tc.desc: Normal testcase of OH_UdsAppItem_GetAbilityName
 * @tc.type: FUNC
 */
HWTEST_F(UdsTest, OH_UdsAppItem_GetAbilityName_001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "OH_UdsAppItem_GetAbilityName_001 begin.");
    auto appItem = OH_UdsAppItem_Create();
    appItem->obj->value_[ABILITY_NAME] = "ability";
    EXPECT_EQ("ability", std::string(OH_UdsAppItem_GetAbilityName(appItem)));
    OH_UdsAppItem_Destroy(appItem);

    OH_UdsAppItem* appItemNullptr = nullptr;
    EXPECT_EQ(nullptr, OH_UdsAppItem_GetAbilityName(appItemNullptr));

    appItemNullptr = new OH_UdsAppItem;
    EXPECT_EQ(nullptr, OH_UdsAppItem_GetAbilityName(appItemNullptr));
    OH_UdsAppItem_Destroy(appItemNullptr);
    LOG_INFO(UDMF_TEST, "OH_UdsAppItem_GetAbilityName_001 end.");
}

/**
 * @tc.name: OH_UdsAppItem_SetId_001
 * @tc.desc: Normal testcase of OH_UdsAppItem_SetId
 * @tc.type: FUNC
 */
HWTEST_F(UdsTest, OH_UdsAppItem_SetId_001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "OH_UdsAppItem_SetId_001 begin.");
    auto appItem = OH_UdsAppItem_Create();
    int result = OH_UdsAppItem_SetId(appItem, "com.xxx");
    EXPECT_EQ(UDMF_E_OK, result);
    EXPECT_EQ("com.xxx", std::string(OH_UdsAppItem_GetId(appItem)));

    result = OH_UdsAppItem_SetId(nullptr, "com.xxx");
    EXPECT_EQ(UDMF_E_INVALID_PARAM, result);

    result = OH_UdsAppItem_SetId(appItem, nullptr);
    EXPECT_EQ(UDMF_E_INVALID_PARAM, result);

    appItem->obj = nullptr;
    result = OH_UdsAppItem_SetId(appItem, "com.xxx");
    EXPECT_EQ(UDMF_E_INVALID_PARAM, result);
    OH_UdsAppItem_Destroy(appItem);
    LOG_INFO(UDMF_TEST, "OH_UdsAppItem_SetId_001 end.");
}

/**
 * @tc.name: OH_UdsAppItem_SetName_001
 * @tc.desc: Normal testcase of OH_UdsAppItem_SetName
 * @tc.type: FUNC
 */
HWTEST_F(UdsTest, OH_UdsAppItem_SetName_001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "OH_UdsAppItem_SetName_001 begin.");
    auto appItem = OH_UdsAppItem_Create();
    int result = OH_UdsAppItem_SetName(appItem, "OH");
    EXPECT_EQ(UDMF_E_OK, result);
    EXPECT_EQ("OH", std::string(OH_UdsAppItem_GetName(appItem)));

    result = OH_UdsAppItem_SetName(nullptr, "OH");
    EXPECT_EQ(UDMF_E_INVALID_PARAM, result);

    result = OH_UdsAppItem_SetName(appItem, nullptr);
    EXPECT_EQ(UDMF_E_INVALID_PARAM, result);

    appItem->obj = nullptr;
    result = OH_UdsAppItem_SetName(appItem, "OH");
    EXPECT_EQ(UDMF_E_INVALID_PARAM, result);
    OH_UdsAppItem_Destroy(appItem);
    LOG_INFO(UDMF_TEST, "OH_UdsAppItem_SetName_001 end.");
}

/**
 * @tc.name: OH_UdsAppItem_SetIconId_001
 * @tc.desc: Normal testcase of OH_UdsAppItem_SetIconId
 * @tc.type: FUNC
 */
HWTEST_F(UdsTest, OH_UdsAppItem_SetIconId_001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "OH_UdsAppItem_SetIconId_001 begin.");
    auto appItem = OH_UdsAppItem_Create();
    int result = OH_UdsAppItem_SetIconId(appItem, "icon");
    EXPECT_EQ(UDMF_E_OK, result);
    EXPECT_EQ("icon", std::string(OH_UdsAppItem_GetIconId(appItem)));

    result = OH_UdsAppItem_SetIconId(nullptr, "icon");
    EXPECT_EQ(UDMF_E_INVALID_PARAM, result);

    result = OH_UdsAppItem_SetIconId(appItem, nullptr);
    EXPECT_EQ(UDMF_E_INVALID_PARAM, result);

    appItem->obj = nullptr;
    result = OH_UdsAppItem_SetIconId(appItem, "icon");
    EXPECT_EQ(UDMF_E_INVALID_PARAM, result);
    OH_UdsAppItem_Destroy(appItem);
    LOG_INFO(UDMF_TEST, "OH_UdsAppItem_SetIconId_001 end.");
}

/**
 * @tc.name: OH_UdsAppItem_SetLabelId_001
 * @tc.desc: Normal testcase of OH_UdsAppItem_SetLabelId
 * @tc.type: FUNC
 */
HWTEST_F(UdsTest, OH_UdsAppItem_SetLabelId_001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "OH_UdsAppItem_SetLabelId_001 begin.");
    auto appItem = OH_UdsAppItem_Create();
    int result = OH_UdsAppItem_SetLabelId(appItem, "label");
    EXPECT_EQ(UDMF_E_OK, result);
    EXPECT_EQ("label", std::string(OH_UdsAppItem_GetLabelId(appItem)));

    result = OH_UdsAppItem_SetLabelId(nullptr, "label");
    EXPECT_EQ(UDMF_E_INVALID_PARAM, result);

    result = OH_UdsAppItem_SetLabelId(appItem, nullptr);
    EXPECT_EQ(UDMF_E_INVALID_PARAM, result);

    appItem->obj = nullptr;
    result = OH_UdsAppItem_SetLabelId(appItem, "label");
    EXPECT_EQ(UDMF_E_INVALID_PARAM, result);
    OH_UdsAppItem_Destroy(appItem);
    LOG_INFO(UDMF_TEST, "OH_UdsAppItem_SetLabelId_001 end.");
}

/**
 * @tc.name: OH_UdsAppItem_SetBundleName_001
 * @tc.desc: Normal testcase of OH_UdsAppItem_SetBundleName
 * @tc.type: FUNC
 */
HWTEST_F(UdsTest, OH_UdsAppItem_SetBundleName_001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "OH_UdsAppItem_SetBundleName_001 begin.");
    auto appItem = OH_UdsAppItem_Create();
    int result = OH_UdsAppItem_SetBundleName(appItem, "bundle");
    EXPECT_EQ(UDMF_E_OK, result);
    EXPECT_EQ("bundle", std::string(OH_UdsAppItem_GetBundleName(appItem)));

    result = OH_UdsAppItem_SetBundleName(nullptr, "bundle");
    EXPECT_EQ(UDMF_E_INVALID_PARAM, result);

    result = OH_UdsAppItem_SetBundleName(appItem, nullptr);
    EXPECT_EQ(UDMF_E_INVALID_PARAM, result);

    appItem->obj = nullptr;
    result = OH_UdsAppItem_SetBundleName(appItem, "bundle");
    EXPECT_EQ(UDMF_E_INVALID_PARAM, result);
    OH_UdsAppItem_Destroy(appItem);
    LOG_INFO(UDMF_TEST, "OH_UdsAppItem_SetBundleName_001 end.");
}

/**
 * @tc.name: OH_UdsAppItem_SetAbilityName_001
 * @tc.desc: Normal testcase of OH_UdsAppItem_SetAbilityName
 * @tc.type: FUNC
 */
HWTEST_F(UdsTest, OH_UdsAppItem_SetAbilityName_001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "OH_UdsAppItem_SetAbilityName_001 begin.");
    auto appItem = OH_UdsAppItem_Create();
    int result = OH_UdsAppItem_SetAbilityName(appItem, "ability");
    EXPECT_EQ(UDMF_E_OK, result);
    EXPECT_EQ("ability", std::string(OH_UdsAppItem_GetAbilityName(appItem)));

    result = OH_UdsAppItem_SetAbilityName(nullptr, "ability");
    EXPECT_EQ(UDMF_E_INVALID_PARAM, result);

    result = OH_UdsAppItem_SetAbilityName(appItem, nullptr);
    EXPECT_EQ(UDMF_E_INVALID_PARAM, result);

    appItem->obj = nullptr;
    result = OH_UdsAppItem_SetAbilityName(appItem, "ability");
    EXPECT_EQ(UDMF_E_INVALID_PARAM, result);
    OH_UdsAppItem_Destroy(appItem);
    LOG_INFO(UDMF_TEST, "OH_UdsAppItem_SetAbilityName_001 end.");
}

/**
 * @tc.name: OH_UdsFileUri_Create_001
 * @tc.desc: Normal testcase of OH_UdsFileUri_Create
 * @tc.type: FUNC
 */
HWTEST_F(UdsTest, OH_UdsFileUri_Create_001, TestSize.Level1)
{
    auto fileUri = OH_UdsFileUri_Create();
    EXPECT_EQ(UDMF_META_GENERAL_FILE_URI, *(std::get_if<std::string>(&(fileUri->obj)->value_[UNIFORM_DATA_TYPE])));
    OH_UdsFileUri_Destroy(fileUri);
}

/**
 * @tc.name: OH_UdsFileUri_GetType_001
 * @tc.desc: Normal testcase of OH_UdsFileUri_GetType
 * @tc.type: FUNC
 */
HWTEST_F(UdsTest, OH_UdsFileUri_GetType_001, TestSize.Level1)
{
    auto fileUri = OH_UdsFileUri_Create();
    EXPECT_EQ(UDMF_META_GENERAL_FILE_URI, std::string(OH_UdsFileUri_GetType(fileUri)));
    OH_UdsFileUri_Destroy(fileUri);

    OH_UdsFileUri* fileUriNullptr = nullptr;
    EXPECT_EQ(nullptr, OH_UdsFileUri_GetType(fileUriNullptr));

    fileUriNullptr = new OH_UdsFileUri;
    EXPECT_EQ(nullptr, OH_UdsFileUri_GetType(fileUriNullptr));
    OH_UdsFileUri_Destroy(fileUriNullptr);
}

/**
 * @tc.name: OH_UdsFileUri_GetFileUri_001
 * @tc.desc: Normal testcase of OH_UdsFileUri_GetFileUri
 * @tc.type: FUNC
 */
HWTEST_F(UdsTest, OH_UdsFileUri_GetFileUri_001, TestSize.Level1)
{
    auto fileUri = OH_UdsFileUri_Create();
    fileUri->obj->value_[FILE_URI_PARAM] = "fileUri";
    EXPECT_EQ("fileUri", std::string(OH_UdsFileUri_GetFileUri(fileUri)));
    OH_UdsFileUri_Destroy(fileUri);

    OH_UdsFileUri* fileUriNullptr = nullptr;
    EXPECT_EQ(nullptr, OH_UdsFileUri_GetFileUri(fileUriNullptr));

    fileUriNullptr = new OH_UdsFileUri;
    EXPECT_EQ(nullptr, OH_UdsFileUri_GetFileUri(fileUriNullptr));
    OH_UdsFileUri_Destroy(fileUriNullptr);
}

/**
 * @tc.name: OH_UdsFileUri_GetFileType_001
 * @tc.desc: Normal testcase of OH_UdsFileUri_GetFileType
 * @tc.type: FUNC
 */
HWTEST_F(UdsTest, OH_UdsFileUri_GetFileType_001, TestSize.Level1)
{
    auto fileUri = OH_UdsFileUri_Create();
    fileUri->obj->value_[FILE_TYPE] = "fileType";
    EXPECT_EQ("fileType", std::string(OH_UdsFileUri_GetFileType(fileUri)));
    OH_UdsFileUri_Destroy(fileUri);

    OH_UdsFileUri* fileUriNullptr = nullptr;
    EXPECT_EQ(nullptr, OH_UdsFileUri_GetFileType(fileUriNullptr));

    fileUriNullptr = new OH_UdsFileUri;
    EXPECT_EQ(nullptr, OH_UdsFileUri_GetFileType(fileUriNullptr));
    OH_UdsFileUri_Destroy(fileUriNullptr);
}

}
