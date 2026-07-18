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
* @tc.name: ParseEncodedJsonData001
* @tc.desc: Parse encoded sparse UTD json
* @tc.type: FUNC
*/
HWTEST_F(CustomUtdJsonParserTest, ParseEncodedJsonData001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "ParseEncodedJsonData001 begin.");
    const char *testJson = R"({
        "UniformDataTypeDeclarations": {
            "fields": [
                "typeId",
                "belongingToTypes",
                "filenameExtensions",
                "mimeTypes",
                "description",
                "referenceURL",
                "iconFile"
            ],
            "strings": [
                "general.object",
                "*/*",
                "Base type for logical hierarchy.",
                "https://gitee.com/openharmony/docs",
                "general.text",
                "text/*",
                "Base type for all text.",
                "general.plain-text",
                ".txt",
                ".text",
                "text/plain",
                "Text of unspecified encoding, with no markup.",
                "sys.media.ohos_ic_normal_white_grid_txt"
            ],
            "records": [
                [0, [], null, {"value": [1], "Count": 1}, 2, 3],
                [4, {"value": [0], "Count": 1}, [], {"value": [5], "Count": 1}, 6, 3],
                [7, {"value": [4], "Count": 1}, {"value": [8, 9], "Count": 2},
                    {"value": [10], "Count": 1}, 11, 3, 12]
            ]
        }
    })";

    std::vector<TypeDescriptorCfg> typesCfg;
    std::vector<TypeDescriptorCfg> typesReference;
    CustomUtdJsonParser parser;
    bool result = parser.ParseUserCustomUtdJson(testJson, typesCfg, typesReference);

    EXPECT_TRUE(result);
    ASSERT_EQ(typesCfg.size(), 3);
    EXPECT_EQ(typesCfg[0].typeId, "general.object");
    EXPECT_TRUE(typesCfg[0].belongingToTypes.empty());
    EXPECT_EQ(*(typesCfg[0].mimeTypes.begin()), "*/*");
    EXPECT_EQ(typesCfg[0].description, "Base type for logical hierarchy.");
    EXPECT_EQ(typesCfg[0].referenceURL, "https://gitee.com/openharmony/docs");

    EXPECT_EQ(typesCfg[1].typeId, "general.text");
    EXPECT_EQ(*(typesCfg[1].belongingToTypes.begin()), "general.object");
    EXPECT_EQ(*(typesCfg[1].mimeTypes.begin()), "text/*");
    EXPECT_TRUE(typesCfg[1].filenameExtensions.empty());

    EXPECT_EQ(typesCfg[2].typeId, "general.plain-text");
    EXPECT_EQ(*(typesCfg[2].belongingToTypes.begin()), "general.text");
    EXPECT_EQ(typesCfg[2].filenameExtensions[0], ".txt");
    EXPECT_EQ(typesCfg[2].filenameExtensions[1], ".text");
    EXPECT_EQ(*(typesCfg[2].mimeTypes.begin()), "text/plain");
    EXPECT_EQ(typesCfg[2].iconFile, "sys.media.ohos_ic_normal_white_grid_txt");
    LOG_INFO(UDMF_TEST, "ParseEncodedJsonData001 end.");
}

/**
* @tc.name: ParseEncodedJsonData002
* @tc.desc: Reject encoded UTD records without a typeId
* @tc.type: FUNC
*/
HWTEST_F(CustomUtdJsonParserTest, ParseEncodedJsonData002, TestSize.Level1)
{
    const char *testJson = R"({
        "UniformDataTypeDeclarations": {
            "fields": ["typeId", "description"],
            "strings": ["description"],
            "records": [[]]
        }
    })";
    std::vector<TypeDescriptorCfg> typesCfg;
    std::vector<TypeDescriptorCfg> typesReference;
    CustomUtdJsonParser parser;
    EXPECT_FALSE(parser.ParseUserCustomUtdJson(testJson, typesCfg, typesReference));
    EXPECT_TRUE(typesCfg.empty());
}
} // OHOS::Test
