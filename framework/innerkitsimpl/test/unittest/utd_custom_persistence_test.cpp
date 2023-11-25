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

#include <gtest/gtest.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "logger.h"
#include "utd_custom_persistence.h"
#include "utd_common.h"

using namespace testing::ext;
using namespace OHOS::UDMF;
using namespace OHOS;
namespace OHOS::Test {
constexpr const char* TEST_CFG_FILE = "/data/100_test/utd-adt.json";
constexpr const char* TEST_CFG_DIR = "/data/100_test";

constexpr const char* TEST_DATA2 = "{\
  \"utdCustom\": [{\
    \"typeId\": \"com.example.utdtest.document\",\
    \"belongingToTypes\": [\"com.example.utdtest2.document\"],\
    \"FilenameExtensions\": [\".mydocument\", \".mydoc\"],\
    \"mimeTypes\": [\"application/my-document\", \"application/my-doc\"],\
    \"description\": \"My document.\",\
    \"referenceURL\": \"http://www.mycompany.com/my-document.html\",\
    \"iconFile\": \"resources/my-document.png\",\
    \"installers\":[\"com.example.utdtest\"],\
    \"owner\":\"com.example.utdtest\"\
  }, {\
    \"typeId\": \"com.example.utdtest2.document\",\
    \"belongingToTypes\": [\"general.object\"],\
    \"FilenameExtensions\": [\".mydocument2\", \".mydoc2\"],\
    \"mimeTypes\": [\"application/my-document2\", \"application/my-doc2\"],\
    \"description\": \"My document 2.\",\
    \"referenceURL\": \"hhttp://www.mycompany.com/my-document2.html\",\
    \"iconFile\": \"resources/my-document2.png\",\
    \"installers\":[\"com.example.utdtest2\", \"com.example.utdtest\"],\
    \"owner\":\"com.example.utdtest2\"\
  }]\
}";

class UtdCustomPersistenceTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void UtdCustomPersistenceTest::SetUpTestCase()
{
}

void UtdCustomPersistenceTest::TearDownTestCase()
{
}

void UtdCustomPersistenceTest::SetUp()
{
}

void UtdCustomPersistenceTest::TearDown()
{
    if (remove(TEST_CFG_FILE) == 0) {
        rmdir(TEST_CFG_DIR);
        LOG_INFO(UDMF_TEST, "Removed file success, %{public}s.", TEST_CFG_FILE);
    } else {
        LOG_INFO(UDMF_TEST, "Failed to remove the file., %{public}s.", TEST_CFG_FILE);
    }
}

/**
* @tc.name: PersistingCustomUtdData001
* @tc.desc: PersistingCustomUtdData
* @tc.type: FUNC
*/
HWTEST_F(UtdCustomPersistenceTest, PersistingCustomUtdData001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "PersistingCustomUtdData001 begin.");
    std::vector<TypeDescriptorCfg> typesCfg;
    UtdJsonParse parse;
    parse.ParseJsonData(TEST_DATA2, typesCfg);
    auto status = UtdCustomPersistence::GetInstance().PersistingCustomUtdData(typesCfg, TEST_CFG_FILE);
    EXPECT_EQ(status, E_OK);

    typesCfg.clear();
    typesCfg = UtdCustomPersistence::GetInstance().GetCustomTypesFromCfg(TEST_CFG_FILE);
    TypeDescriptorCfg type1 = *(typesCfg.begin());
    EXPECT_EQ(type1.typeId, "com.example.utdtest.document");
    EXPECT_EQ(*(type1.belongingToTypes.begin()), "com.example.utdtest2.document");
    EXPECT_EQ(*(type1.filenameExtensions.begin()), ".mydocument");
    EXPECT_EQ(*(type1.mimeTypes.begin()), "application/my-document");
    EXPECT_EQ(type1.description, "My document.");
    EXPECT_EQ(type1.referenceURL, "http://www.mycompany.com/my-document.html");
    EXPECT_EQ(type1.iconFile, "resources/my-document.png");
    EXPECT_EQ(*(type1.installers.begin()), "com.example.utdtest");
    EXPECT_EQ(type1.owner, "com.example.utdtest");

    LOG_INFO(UDMF_TEST, "PersistingCustomUtdData001 end.");
}
} // OHOS::Test