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
#define LOG_TAG "CustomUtdStoreTest"
#include <gtest/gtest.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "logger.h"
#include "custom_utd_store.h"
#include "utd_common.h"

using namespace testing::ext;
using namespace OHOS::UDMF;
using namespace OHOS;
namespace OHOS::Test {
constexpr const int32_t USERID = 1000000;
constexpr const char* TEST_CFG_FILE = "/data/1000000/utd-adt.json";
constexpr const char* TEST_CFG_DIR = "/data/1000000/";

constexpr const char* TEST_DATA2 = "{\
    \"CustomUTDs\": [{\
    \"typeId\": \"com.example.utdtest.document\",\
    \"belongingToTypes\": [\"com.example.utdtest2.document\"],\
    \"FilenameExtensions\": [\".mydocument\", \".mydoc\"],\
    \"mimeTypes\": [\"application/my-document\", \"application/my-doc\"],\
    \"description\": \"My document.\",\
    \"referenceURL\": \"http://www.mycompany.com/my-document.html\",\
    \"iconFile\": \"resources/my-document.png\",\
    \"installerBundles\":[\"com.example.utdtest\"],\
    \"ownerBundle\":\"com.example.utdtest\"\
    }, {\
    \"typeId\": \"com.example.utdtest2.document\",\
    \"belongingToTypes\": [\"general.object\"],\
    \"FilenameExtensions\": [\".mydocument2\", \".mydoc2\"],\
    \"mimeTypes\": [\"application/my-document2\", \"application/my-doc2\"],\
    \"description\": \"My document 2.\",\
    \"referenceURL\": \"hhttp://www.mycompany.com/my-document2.html\",\
    \"iconFile\": \"resources/my-document2.png\",\
    \"installerBundles\":[\"com.example.utdtest2\", \"com.example.utdtest\"],\
    \"ownerBundle\":\"com.example.utdtest2\"\
    }]}";

class CustomUtdStoreTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void CustomUtdStoreTest::SetUpTestCase()
{
}

void CustomUtdStoreTest::TearDownTestCase()
{
}

void CustomUtdStoreTest::SetUp()
{
}

void CustomUtdStoreTest::TearDown()
{
    if (remove(TEST_CFG_FILE) == 0) {
        rmdir(TEST_CFG_DIR);
        LOG_INFO(UDMF_TEST, "Removed file success, %{public}s.", TEST_CFG_FILE);
    } else {
        LOG_INFO(UDMF_TEST, "Failed to remove the file., %{public}s.", TEST_CFG_FILE);
    }
}

/**
* @tc.name: SaveTypeCfgs001
* @tc.desc: SaveTypeCfgs
* @tc.type: FUNC
*/
HWTEST_F(CustomUtdStoreTest, SaveTypeCfgs001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SaveTypeCfgs001 begin.");
    std::vector<TypeDescriptorCfg> typesCfg;
    CustomUtdJsonParser parser;
    parser.ParseStoredCustomUtdJson(TEST_DATA2, typesCfg);
    auto status = CustomUtdStore::GetInstance().SaveTypeCfgs(typesCfg, UtdTypeCategory::STATIC_TYPE, USERID);
    EXPECT_EQ(status, E_OK);

    typesCfg.clear();
    typesCfg = CustomUtdStore::GetInstance().GetCustomUtd(false, USERID);
    TypeDescriptorCfg type1 = *(typesCfg.begin());
    EXPECT_EQ(type1.typeId, "com.example.utdtest.document");
    EXPECT_EQ(*(type1.belongingToTypes.begin()), "com.example.utdtest2.document");
    EXPECT_EQ(*(type1.filenameExtensions.begin()), ".mydocument");
    EXPECT_EQ(*(type1.mimeTypes.begin()), "application/my-document");
    EXPECT_EQ(type1.description, "My document.");
    EXPECT_EQ(type1.referenceURL, "http://www.mycompany.com/my-document.html");
    EXPECT_EQ(type1.iconFile, "resources/my-document.png");
    EXPECT_EQ(*(type1.installerBundles.begin()), "com.example.utdtest");
    EXPECT_EQ(type1.ownerBundle, "com.example.utdtest");

    LOG_INFO(UDMF_TEST, "SaveTypeCfgs001 end.");
}

/**
* @tc.name: GetCustomUtdPathTest001
* @tc.desc: GetCustomUtdPath
* @tc.type: FUNC
*/
HWTEST_F(CustomUtdStoreTest, GetCustomUtdPathTest001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetCustomUtdPathTest001 begin.");

    std::string path = CustomUtdStore::GetInstance().GetCustomUtdPath(false, USERID);
    EXPECT_EQ(path, "/data/service/el1/1000000/utdtypes/utd/utd-adt.json");

    LOG_INFO(UDMF_TEST, "GetCustomUtdPathTest001 end.");
}

/**
* @tc.name: GetCustomUtdPathTest002
* @tc.desc: GetCustomUtdPath
* @tc.type: FUNC
*/
HWTEST_F(CustomUtdStoreTest, GetCustomUtdPathTest002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetCustomUtdPathTest002 begin.");

    std::string path = CustomUtdStore::GetInstance().GetCustomUtdPath(true, USERID);
    EXPECT_EQ(path, "/data/utd/utd-adt.json");

    LOG_INFO(UDMF_TEST, "GetCustomUtdPathTest002 end.");
}

/**
* @tc.name: GetCustomUtdInfoTest001
* @tc.desc: GetCustomUtdInfo
* @tc.type: FUNC
*/
HWTEST_F(CustomUtdStoreTest, GetCustomUtdInfoTest001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetCustomUtdInfoTest001 begin.");

    UtdFileInfo info = CustomUtdStore::GetInstance().GetCustomUtdInfo(true, USERID);
    EXPECT_EQ(info.size, 0);

    LOG_INFO(UDMF_TEST, "GetCustomUtdInfoTest001 end.");
}

/**
* @tc.name: GetCustomUtdInfoTest002
* @tc.desc: GetCustomUtdInfo
* @tc.type: FUNC
*/
HWTEST_F(CustomUtdStoreTest, GetCustomUtdInfoTest002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetCustomUtdInfoTest002 begin.");

    UtdFileInfo info = CustomUtdStore::GetInstance().GetCustomUtdInfo(false, USERID);
    EXPECT_EQ(info.size, strlen(TEST_DATA2) + 2);
    auto customUtds = CustomUtdStore::GetInstance().GetCustomUtd(false, USERID);
    EXPECT_EQ(customUtds.size(), 2);

    LOG_INFO(UDMF_TEST, "GetCustomUtdInfoTest002 end.");
}

/**
* @tc.name: ParseStoredCustomUtdJson001
* @tc.desc: empty json
* @tc.type: FUNC
*/
HWTEST_F(CustomUtdStoreTest, ParseStoredCustomUtdJson001, TestSize.Level1) {
    LOG_INFO(UDMF_TEST, "ParseStoredCustomUtdJson001 begin.");
    CustomUtdJsonParser parser;
    std::vector<TypeDescriptorCfg> typesCfg;
    bool ret = parser.ParseStoredCustomUtdJson("", typesCfg);

    EXPECT_FALSE(ret);
    EXPECT_TRUE(typesCfg.empty());
    LOG_INFO(UDMF_TEST, "ParseStoredCustomUtdJson001 end.");
}

/**
* @tc.name: ParseStoredCustomUtdJson002
* @tc.desc: Invalid Format
* @tc.type: FUNC
*/
HWTEST_F(CustomUtdStoreTest, ParseStoredCustomUtdJson002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "ParseStoredCustomUtdJson002 begin.");
    const std::string invalidJson = R"({
        "UniformDataTypeDeclarations": []
    )"; // syntax error

    CustomUtdJsonParser parser;
    std::vector<TypeDescriptorCfg> typesCfg;
    bool ret = parser.ParseStoredCustomUtdJson(invalidJson, typesCfg);

    EXPECT_FALSE(ret);
    EXPECT_TRUE(typesCfg.empty());
    LOG_INFO(UDMF_TEST, "ParseStoredCustomUtdJson002 end.");
}

/**
* @tc.name: ParseStoredCustomUtdJson003
* @tc.desc: invalid json
* @tc.type: FUNC
*/
HWTEST_F(CustomUtdStoreTest, ParseStoredCustomUtdJson003, TestSize.Level1) {
    LOG_INFO(UDMF_TEST, "ParseStoredCustomUtdJson003 begin.");
    CustomUtdJsonParser parser;
    std::vector<TypeDescriptorCfg> typesCfg;
    std::string invalidJson = "{invalid_json}";
    EXPECT_FALSE(parser.ParseStoredCustomUtdJson(invalidJson, typesCfg));
    EXPECT_TRUE(typesCfg.empty());
    LOG_INFO(UDMF_TEST, "ParseStoredCustomUtdJson003 end.");
}

/**
* @tc.name: ParseStoredCustomUtdJson004
* @tc.desc: root not object
* @tc.type: FUNC
*/
HWTEST_F(CustomUtdStoreTest, ParseStoredCustomUtdJson004, TestSize.Level1) {
    LOG_INFO(UDMF_TEST, "ParseStoredCustomUtdJson004 begin.");
    const std::string rootArrayJson = R"([
        { "TypeId": "com.example.custom.image" }
    ])";

    CustomUtdJsonParser parser;
    std::vector<TypeDescriptorCfg> typesCfg;
    bool ret = parser.ParseStoredCustomUtdJson(rootArrayJson, typesCfg);

    EXPECT_FALSE(ret);
    EXPECT_TRUE(typesCfg.empty());
    LOG_INFO(UDMF_TEST, "ParseStoredCustomUtdJson004 end.");
}

/**
* @tc.name: ParseStoredCustomUtdJson005
* @tc.desc: valid json
* @tc.type: FUNC
*/
HWTEST_F(CustomUtdStoreTest, ParseStoredCustomUtdJson005, TestSize.Level1) {
    LOG_INFO(UDMF_TEST, "ParseStoredCustomUtdJson005 begin.");

    const std::string validJson = R"({
        "CustomUTDs": [
            {
                "TypeId": "com.example.custom.image",
                "BelongingToTypes": ["general.image"],
                "FilenameExtensions": [".img", ".pic"],
                "MIMETypes": ["application/img", "application/pic"],
                "Description": "Custom image type",
                "ReferenceURL": ""
            }
        ]
    })";

    CustomUtdJsonParser parser;
    std::vector<TypeDescriptorCfg> typesCfg;
    bool ret = parser.ParseStoredCustomUtdJson(validJson, typesCfg);

    EXPECT_TRUE(ret);
    ASSERT_EQ(typesCfg.size(), 1u);
    EXPECT_EQ(typesCfg[0].typeId, "com.example.custom.image");
    EXPECT_EQ(typesCfg[0].belongingToTypes.size(), 1u);
    EXPECT_EQ(typesCfg[0].belongingToTypes[0], "general.image");

    LOG_INFO(UDMF_TEST, "ParseStoredCustomUtdJson005 end.");
}

/**
 * @tc.name: ParseUserCustomUtdJsonTest001
 * @tc.desc: parse a valid JSON containing declarations and references.
 * @tc.type: FUNC
 */
HWTEST_F(CustomUtdStoreTest, ParseUserCustomUtdJsonTest001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "ParseUserCustomUtdJsonTest001 begin.");
    const char *testJson = R"({
        "UniformDataTypeDeclarations": [
            {
                "TypeId": "com.example.thread.image",
                "BelongingToTypes": ["general.image"],
                "FilenameExtensions": [".myImage", ".khImage"],
                "MIMETypes": ["application/myImage", "application/khImage"],
                "Description": "My Image.",
                "ReferenceURL": ""
            }
        ],
        "ReferenceUniformDataTypeDeclarations": [
            {
                "TypeId": "com.example.thread.audio",
                "BelongingToTypes": ["general.audio"],
                "FilenameExtensions": [".myAudio", ".khAudio"],
                "MIMETypes": ["application/myAudio", "application/khAudio"],
                "Description": "My audio.",
                "ReferenceURL": ""
            }
        ]
    })";

    std::vector<TypeDescriptorCfg> declarations;
    std::vector<TypeDescriptorCfg> references;

    CustomUtdJsonParser parser;
    bool result = parser.ParseUserCustomUtdJson(testJson, declarations, references);

    EXPECT_TRUE(result);
    EXPECT_EQ(declarations.size(), 1);
    EXPECT_EQ(references.size(), 1);

    EXPECT_EQ(declarations[0].typeId, "com.example.thread.image");
    EXPECT_EQ(references[0].typeId, "com.example.thread.audio");
    LOG_INFO(UDMF_TEST, "ParseUserCustomUtdJsonTest001 end.");
}

/**
 * @tc.name: ParseUserCustomUtdJsonTest002
 * @tc.desc: Verify ParseUserCustomUtdJson returns false when given empty JSON string.
 * @tc.type: FUNC
 */
HWTEST_F(CustomUtdStoreTest, ParseUserCustomUtdJsonTest002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "ParseUserCustomUtdJsonTest002 begin.");
    std::vector<TypeDescriptorCfg> declarations;
    std::vector<TypeDescriptorCfg> references;

    CustomUtdJsonParser parser;
    bool result = parser.ParseUserCustomUtdJson("", declarations, references);

    EXPECT_FALSE(result);
    EXPECT_TRUE(declarations.empty());
    EXPECT_TRUE(references.empty());
    LOG_INFO(UDMF_TEST, "ParseUserCustomUtdJsonTest002 end.");
}

/**
 * @tc.name: ParseUserCustomUtdJsonTest003
 * @tc.desc: Verify ParseUserCustomUtdJson returns false for invalid JSON format.
 * @tc.type: FUNC
 */
HWTEST_F(CustomUtdStoreTest, ParseUserCustomUtdJsonTest003, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "ParseUserCustomUtdJsonTest003 begin.");
    const char *invalidJson = R"({ "UniformDataTypeDeclarations": [ )";

    std::vector<TypeDescriptorCfg> declarations;
    std::vector<TypeDescriptorCfg> references;

    CustomUtdJsonParser parser;
    bool result = parser.ParseUserCustomUtdJson(invalidJson, declarations, references);

    EXPECT_FALSE(result);
    EXPECT_TRUE(declarations.empty());
    EXPECT_TRUE(references.empty());
    LOG_INFO(UDMF_TEST, "ParseUserCustomUtdJsonTest003 end.");
}

/**
 * @tc.name: ParseUserCustomUtdJsonTest004
 * @tc.desc: Verify ParseUserCustomUtdJson returns false for invalid JSON format.
 * @tc.type: FUNC
 */
HWTEST_F(CustomUtdStoreTest, ParseUserCustomUtdJsonTest004, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "ParseUserCustomUtdJsonTest004 begin.");
    const char *invalidJson = R"([
        { "TypeId": "com.example.custom.image" }
    ])";

    std::vector<TypeDescriptorCfg> declarations;
    std::vector<TypeDescriptorCfg> references;

    CustomUtdJsonParser parser;
    bool result = parser.ParseUserCustomUtdJson(invalidJson, declarations, references);

    EXPECT_FALSE(result);
    EXPECT_TRUE(declarations.empty());
    EXPECT_TRUE(references.empty());
    LOG_INFO(UDMF_TEST, "ParseUserCustomUtdJsonTest004 end.");
}
} // OHOS::Test