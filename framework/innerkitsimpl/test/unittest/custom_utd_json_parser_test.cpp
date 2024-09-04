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
#define LOG_TAG "CustomUtdJsonParserTest"
#include <gtest/gtest.h>

#include <unistd.h>

#include "logger.h"
#include "utd_common.h"
#include "custom_utd_json_parser.h"

using namespace testing::ext;
using namespace OHOS::UDMF;
using namespace OHOS;
namespace OHOS::Test {
constexpr const char* TEST_DATA1 = "{\
    \"UniformDataTypeDeclarations\": [{\
    \"typeId\": \"com.example.utdtest.document\",\
    \"belongingToTypes\": [\"com.example.utdtest2.document\"],\
    \"FilenameExtensions\": [\".mydocument\", \".mydoc\"],\
    \"mimeTypes\": [\"application/my-document\", \"application/my-doc\"],\
    \"description\": \"My document.\",\
    \"referenceURL\": \"http://www.mycompany.com/my-document.html\",\
    \"iconFile\": \"resources/my-document.png\"\
    }],\
    \"ReferenceUniformDataTypeDeclarations\": [{\
    \"typeId\": \"com.example.utdtest2.document\",\
    \"belongingToTypes\": [\"general.object\"],\
    \"FilenameExtensions\": [\".mydocument2\", \".mydoc2\"],\
    \"mimeTypes\": [\"application/my-document2\", \"application/my-doc2\"],\
    \"description\": \"My document 2.\",\
    \"referenceURL\": \"http://www.mycompany.com/my-document2.html\",\
    \"iconFile\": \"resources/my-document2.png\"\
    }]}";

class CustomUtdJsonParserTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void CustomUtdJsonParserTest::SetUpTestCase()
{
}

void CustomUtdJsonParserTest::TearDownTestCase()
{
}

void CustomUtdJsonParserTest::SetUp()
{
}

void CustomUtdJsonParserTest::TearDown()
{
}

/**
* @tc.name: ParseJsonData001
* @tc.desc: ParseJson
* @tc.type: FUNC
*/
HWTEST_F(CustomUtdJsonParserTest, ParseJsonData001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "ParseJsonData001 begin.");
    std::vector<TypeDescriptorCfg> typesCfg1;
    std::vector<TypeDescriptorCfg> typesCfg2;
    CustomUtdJsonParser parser;
    parser.ParseUserCustomUtdJson(TEST_DATA1, typesCfg1, typesCfg2);
    TypeDescriptorCfg type1 = *(typesCfg1.begin());

    EXPECT_EQ(type1.typeId, "com.example.utdtest.document");
    EXPECT_EQ(*(type1.belongingToTypes.begin()), "com.example.utdtest2.document");
    EXPECT_EQ(*(type1.filenameExtensions.begin()), ".mydocument");
    EXPECT_EQ(*(type1.mimeTypes.begin()), "application/my-document");
    EXPECT_EQ(type1.description, "My document.");
    EXPECT_EQ(type1.referenceURL, "http://www.mycompany.com/my-document.html");
    EXPECT_EQ(type1.iconFile, "resources/my-document.png");

    TypeDescriptorCfg type2 = *(typesCfg2.begin());
    EXPECT_EQ(type2.typeId, "com.example.utdtest2.document");
    EXPECT_EQ(*(type2.belongingToTypes.begin()), "general.object");
    EXPECT_EQ(*(type2.filenameExtensions.begin()), ".mydocument2");
    EXPECT_EQ(*(type2.mimeTypes.begin()), "application/my-document2");
    EXPECT_EQ(type2.description, "My document 2.");
    EXPECT_EQ(type2.referenceURL, "http://www.mycompany.com/my-document2.html");
    EXPECT_EQ(type2.iconFile, "resources/my-document2.png");

    LOG_INFO(UDMF_TEST, "ParseJsonData001 end.");
}

/**
* @tc.name: ParseJsonData002
* @tc.desc: ParseJson, empty JsonData
* @tc.type: FUNC
*/
HWTEST_F(CustomUtdJsonParserTest, ParseJsonData002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "ParseJsonData002 begin.");
    std::vector<TypeDescriptorCfg> typesCfg1;
    std::vector<TypeDescriptorCfg> typesCfg2;
    std::string emptyJson = "";
    CustomUtdJsonParser parser;
    bool result = parser.ParseUserCustomUtdJson(emptyJson, typesCfg1, typesCfg2);
    EXPECT_EQ(result, false);
    LOG_INFO(UDMF_TEST, "ParseJsonData002 end.");
}

/**
* @tc.name: ParseJsonData003
* @tc.desc: ParseJson, invalid JsonData
* @tc.type: FUNC
*/
HWTEST_F(CustomUtdJsonParserTest, ParseJsonData003, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "ParseJsonData003 begin.");
    std::vector<TypeDescriptorCfg> typesCfg1;
    std::vector<TypeDescriptorCfg> typesCfg2;
    std::string invalidJson = "{ invalid json }\0";
    CustomUtdJsonParser parser;
    bool result = parser.ParseUserCustomUtdJson(invalidJson, typesCfg1, typesCfg2);
    EXPECT_EQ(result, true);
    EXPECT_EQ(typesCfg1.empty(), true);
    EXPECT_EQ(typesCfg2.empty(), true);

    invalidJson = R"({ ["item1", "item2", "item3"] })";
    result = parser.ParseUserCustomUtdJson(invalidJson, typesCfg1, typesCfg2);
    EXPECT_EQ(result, true);
    EXPECT_EQ(typesCfg1.empty(), true);
    EXPECT_EQ(typesCfg2.empty(), true);
    LOG_INFO(UDMF_TEST, "ParseJsonData003 end.");
}

/**
* @tc.name: ParseJsonData004
* @tc.desc: ParseJson, JsonData is valid but no data is needed
* @tc.type: FUNC
*/
HWTEST_F(CustomUtdJsonParserTest, ParseJsonData004, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "ParseJsonData004 begin.");
    std::vector<TypeDescriptorCfg> typesCfg1;
    std::vector<TypeDescriptorCfg> typesCfg2;
    std::string validJsonData = R"({"key": "value"})";
    CustomUtdJsonParser parser;
    bool result = parser.ParseUserCustomUtdJson(validJsonData, typesCfg1, typesCfg2);
    EXPECT_EQ(result, true);
    EXPECT_EQ(typesCfg1.empty(), true);
    EXPECT_EQ(typesCfg2.empty(), true);

    validJsonData = R"({"CustomUTDs": [{}]})";
    result = parser.ParseUserCustomUtdJson(validJsonData, typesCfg1, typesCfg2);
    EXPECT_EQ(result, true);
    EXPECT_EQ(typesCfg1.empty(), true);
    EXPECT_EQ(typesCfg2.empty(), true);
    LOG_INFO(UDMF_TEST, "ParseJsonData004 end.");
}
} // OHOS::Test