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
#define LOG_TAG "UnifiedDataHelperTest"

#include <unistd.h>
#include <gtest/gtest.h>
#include <string>

#include "logger.h"
#include "udmf_capi_common.h"
#include "unified_data_helper.h"
#include "file_uri.h"

using namespace testing::ext;
using namespace OHOS::UDMF;
using namespace OHOS;
namespace OHOS::Test {
using namespace std;

class UnifiedDataHelperTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void UnifiedDataHelperTest::SetUpTestCase()
{
}

void UnifiedDataHelperTest::TearDownTestCase()
{
}

void UnifiedDataHelperTest::SetUp()
{
}

void UnifiedDataHelperTest::TearDown()
{
}

constexpr mode_t MODE = 0700;
constexpr const char *TEMP_UNIFIED_DATA_ROOT_PATH = "data/storage/el2/base/temp/udata";

/**
* @tc.name: CreateDirIfNotExist001
* @tc.desc: Normal testcase of CreateDirIfNotExist
* @tc.type: FUNC
*/
HWTEST_F(UnifiedDataHelperTest, CreateDirIfNotExist001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "CreateDirIfNotExist001 begin.");
    const std::string dirPath = "storage/media/100/local/files/Pictures";
    const mode_t mode = MODE;
    UnifiedDataHelper unifiedDataHelper;
    unifiedDataHelper.CreateDirIfNotExist(dirPath, mode);
    EXPECT_TRUE(true);
    LOG_INFO(UDMF_TEST, "CreateDirIfNotExist001 end.");
}

/**
* @tc.name: CreateDirIfNotExist002
* @tc.desc: Abnormal testcase of CreateDirIfNotExist, the storage/el2/base/temp/udata path does not exist
* @tc.type: FUNC
*/
HWTEST_F(UnifiedDataHelperTest, CreateDirIfNotExist002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "CreateDirIfNotExist002 begin.");
    const std::string dirPath = "data/storage/el2/base/temp/udata";
    const mode_t mode = MODE;
    UnifiedDataHelper unifiedDataHelper;
    unifiedDataHelper.CreateDirIfNotExist(dirPath, mode);
    EXPECT_TRUE(true);
    LOG_INFO(UDMF_TEST, "CreateDirIfNotExist002 end.");
}

/**
* @tc.name: Unpack001
* @tc.desc: Abnormal testcase of Unpack, the records_ length is 0
* @tc.type: FUNC
*/
HWTEST_F(UnifiedDataHelperTest, Unpack001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "Unpack001 begin.");
    UnifiedData data;
    UnifiedDataHelper unifiedDataHelper;
    data.records_ = std::vector<std::shared_ptr<UnifiedRecord>>();
    bool ret = unifiedDataHelper.Unpack(data);
    EXPECT_FALSE(ret);
    LOG_INFO(UDMF_TEST, "Unpack001 end.");
}

/**
* @tc.name: Unpack002
* @tc.desc: Abnormal testcase of Unpack, the data is nullptr
* @tc.type: FUNC
*/
HWTEST_F(UnifiedDataHelperTest, Unpack002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "Unpack002 begin.");
    UnifiedData data;
    UnifiedDataHelper unifiedDataHelper;
    bool ret = unifiedDataHelper.Unpack(data);
    EXPECT_FALSE(ret);
    LOG_INFO(UDMF_TEST, "Unpack002 end.");
}

/**
* @tc.name: SaveUDataToFile001
* @tc.desc: Abnormal testcase of SaveUDataToFile, the data is nullptr
* @tc.type: FUNC
*/
HWTEST_F(UnifiedDataHelperTest, SaveUDataToFile001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SaveUDataToFile001 begin.");
    const std::string dataFile = "data/storage/el2/base/temp/udata";
    UnifiedData data;
    UnifiedDataHelper unifiedDataHelper;
    bool ret = unifiedDataHelper.SaveUDataToFile(dataFile, data);
    EXPECT_FALSE(ret);
    LOG_INFO(UDMF_TEST, "SaveUDataToFile001 end.");
}

/**
* @tc.name: SaveUDataToFile002
* @tc.desc: Normal testcase of SaveUDataToFile
* @tc.type: FUNC
*/
HWTEST_F(UnifiedDataHelperTest, SaveUDataToFile002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SaveUDataToFile002 begin.");
    const std::string dataFile = "data/test";
    UnifiedData data;
    UnifiedDataHelper unifiedDataHelper;
    bool ret = unifiedDataHelper.SaveUDataToFile(dataFile, data);
    EXPECT_TRUE(ret);
    LOG_INFO(UDMF_TEST, "SaveUDataToFile002 end.");
}

/**
* @tc.name: LoadUDataFromFile001
* @tc.desc: Abnormal testcase of LoadUDataFromFile, the data is nullptr
* @tc.type: FUNC
*/
HWTEST_F(UnifiedDataHelperTest, LoadUDataFromFile001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "LoadUDataFromFile001 begin.");
    const std::string dataFile = "data/storage/el2/base/temp/udata";
    UnifiedData data;
    UnifiedDataHelper unifiedDataHelper;
    bool ret = unifiedDataHelper.LoadUDataFromFile(dataFile, data);
    EXPECT_FALSE(ret);
    LOG_INFO(UDMF_TEST, "LoadUDataFromFile001 end.");
}

/**
* @tc.name: LoadUDataFromFile002
* @tc.desc: Abnormal testcase of LoadUDataFromFile, the data is nullptr
* @tc.type: FUNC
*/
HWTEST_F(UnifiedDataHelperTest, LoadUDataFromFile002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "LoadUDataFromFile002 begin.");
    const std::string dataFile = "data/test";
    UnifiedData data;
    UnifiedDataHelper unifiedDataHelper;
    bool ret = unifiedDataHelper.LoadUDataFromFile(dataFile, data);
    EXPECT_FALSE(ret);
    LOG_INFO(UDMF_TEST, "LoadUDataFromFile002 end.");
}

/**
* @tc.name: GetRootPath001
* @tc.desc: Abnormal testcase of GetRootPath, the rootPath_ is nullptr
* @tc.type: FUNC
*/
HWTEST_F(UnifiedDataHelperTest, GetRootPath001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetRootPath001 begin.");
    UnifiedDataHelper unifiedDataHelper;
    unifiedDataHelper.rootPath_ = "";
    std::string ret = unifiedDataHelper.GetRootPath();
    EXPECT_EQ(ret, TEMP_UNIFIED_DATA_ROOT_PATH);
    LOG_INFO(UDMF_TEST, "GetRootPath001 end.");
}

/**
* @tc.name: FileClose001
* @tc.desc: Abnormal testcase of FileClose, the file is null
* @tc.type: FUNC
*/
HWTEST_F(UnifiedDataHelperTest, FileClose001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "FileClose001 begin.");
    UnifiedDataHelper unifiedDataHelper;
    const std::string dataFile = "data/test";
    AppFileService::ModuleFileUri::FileUri fileUri(dataFile);
    std::string path = fileUri.GetRealPath();
    std::FILE *file = fopen(path.c_str(), "r");
    bool status = unifiedDataHelper.FileClose(file, true);
    EXPECT_TRUE(status);
    LOG_INFO(UDMF_TEST, "FileClose001 end.");
}

/**
* @tc.name: FileClose002
* @tc.desc: Abnormal testcase of FileClose, file is nullptr
* @tc.type: FUNC
*/
HWTEST_F(UnifiedDataHelperTest, FileClose002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "FileClose002 begin.");
    UnifiedDataHelper unifiedDataHelper;
    std::FILE *file = nullptr;
    bool status = unifiedDataHelper.FileClose(file, true);
    EXPECT_FALSE(status);
    LOG_INFO(UDMF_TEST, "FileClose002 end.");
}

/**
* @tc.name: GetSummary001
* @tc.desc: Abnormal testcase of GetSummary
* @tc.type: FUNC
*/
HWTEST_F(UnifiedDataHelperTest, GetSummary001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetSummary001 begin.");
    UnifiedDataHelper unifiedDataHelper;
    UnifiedData data;
    Summary summary;
    unifiedDataHelper.GetSummary(data, summary);
    EXPECT_TRUE(summary.tag.empty());
    std::shared_ptr<UnifiedDataProperties> properties = std::make_shared<UnifiedDataProperties>();
    std::string tag = "this is a tag of test GetSummary001";
    properties->tag = tag;
    data.SetProperties(std::move(properties));
    unifiedDataHelper.GetSummary(data, summary);
    EXPECT_EQ(summary.tag, tag);
    LOG_INFO(UDMF_TEST, "GetSummary001 end.");
}
} // OHOS::Test