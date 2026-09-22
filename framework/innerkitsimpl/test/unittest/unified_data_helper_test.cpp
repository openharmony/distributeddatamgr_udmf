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

#include <algorithm>
#include <unistd.h>
#include <gtest/gtest.h>
#include <string>

#include "logger.h"
#include "udmf_capi_common.h"
#include "unified_data_helper.h"
#include "file_uri.h"
#include "unified_meta.h"
#include "file.h"
#include "folder.h"

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

/**
* @tc.name: Pack001
* @tc.desc: Normal testcase of Pack, pack UnifiedData with empty records
* @tc.type: FUNC
*/
HWTEST_F(UnifiedDataHelperTest, Pack001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "Pack001 begin.");
    UnifiedData data;
    bool ret = UnifiedDataHelper::Pack(data);
    EXPECT_TRUE(ret);
    auto records = data.GetRecords();
    EXPECT_EQ(records.size(), 1);
    EXPECT_EQ(records[0]->GetType(), UDType::FILE);
    LOG_INFO(UDMF_TEST, "Pack001 end.");
}

/**
* @tc.name: Pack002
* @tc.desc: Normal testcase of Pack, pack UnifiedData with one valid record
* @tc.type: FUNC
*/
HWTEST_F(UnifiedDataHelperTest, Pack002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "Pack002 begin.");
    UnifiedData data;
    auto record = std::make_shared<UnifiedRecord>(UDType::TEXT);
    record->SetUtdId("general.text");
    data.AddRecord(record);
    bool ret = UnifiedDataHelper::Pack(data);
    EXPECT_TRUE(ret);
    auto records = data.GetRecords();
    EXPECT_EQ(records.size(), 1);
    EXPECT_EQ(records[0]->GetType(), UDType::FILE);
    LOG_INFO(UDMF_TEST, "Pack002 end.");
}

/**
* @tc.name: GetSummary002
* @tc.desc: Abnormal testcase of GetSummary with nullptr record
* @tc.type: FUNC
*/
HWTEST_F(UnifiedDataHelperTest, GetSummary002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetSummary002 begin.");
    UnifiedData data;
    data.records_ = {nullptr};
    Summary summary;
    UnifiedDataHelper::GetSummary(data, summary);
    EXPECT_EQ(summary.totalSize, 0);
    LOG_INFO(UDMF_TEST, "GetSummary002 end.");
}

/**
* @tc.name: GetSummary003
* @tc.desc: Verify duplicate formats are removed from summaryFormat
* @tc.type: FUNC
*/
HWTEST_F(UnifiedDataHelperTest, GetSummary003, TestSize.Level1)
{
    UnifiedData data;
    for (int32_t i = 0; i < 2; ++i) {
        auto object = std::make_shared<Object>();
        object->value_[UNIFORM_DATA_TYPE] = GENERAL_FILE_URI;
        object->value_[ORI_URI] = "file://test/image.png";
        object->value_[FILE_TYPE] = "general.png";
        data.AddRecord(std::make_shared<UnifiedRecord>(UDType::FILE_URI, object));
    }

    Summary summary;
    UnifiedDataHelper::GetSummary(data, summary);

    ASSERT_EQ(summary.summaryFormat.count("general.png"), 1);
    const auto &formats = summary.summaryFormat.at("general.png");
    ASSERT_EQ(formats.size(), 1);
    EXPECT_EQ(formats.front(), Uds_Type::UDS_FILE_URI);
}

/**
* @tc.name: GetSummary004
* @tc.desc: Verify distinct formats for the same type are retained in summaryFormat
* @tc.type: FUNC
*/
HWTEST_F(UnifiedDataHelperTest, GetSummary004, TestSize.Level1)
{
    UnifiedData data;
    data.AddRecord(std::make_shared<UnifiedRecord>(UDType::HTML, std::string("<p>test</p>")));
    auto object = std::make_shared<Object>();
    object->value_[UNIFORM_DATA_TYPE] = GENERAL_FILE_URI;
    object->value_[ORI_URI] = "file://test/index.html";
    object->value_[FILE_TYPE] = "general.html";
    data.AddRecord(std::make_shared<UnifiedRecord>(UDType::FILE_URI, object));

    Summary summary;
    UnifiedDataHelper::GetSummary(data, summary);

    ASSERT_EQ(summary.summaryFormat.count("general.html"), 1);
    const auto &formats = summary.summaryFormat.at("general.html");
    ASSERT_EQ(formats.size(), 2);
    EXPECT_NE(std::find(formats.begin(), formats.end(), Uds_Type::UDS_HTML), formats.end());
    EXPECT_NE(std::find(formats.begin(), formats.end(), Uds_Type::UDS_FILE_URI), formats.end());
}

/**
* @tc.name: LoadUDataFromFile_MaxDataSize001
* @tc.desc: Test MAX_DATA_SIZE constant is correctly defined as 200MB
* @tc.type: FUNC
*/
HWTEST_F(UnifiedDataHelperTest, LoadUDataFromFile_MaxDataSize001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "LoadUDataFromFile_MaxDataSize001 begin.");
    constexpr int64_t expectedMaxSize = 200 * 1024 * 1024;
    EXPECT_EQ(UnifiedData::MAX_DATA_SIZE, expectedMaxSize);
    LOG_INFO(UDMF_TEST, "LoadUDataFromFile_MaxDataSize001 end.");
}

/**
* @tc.name: IsTempUData_EmptyData001
* @tc.desc: Test IsTempUData with empty data
* @tc.type: FUNC
*/
HWTEST_F(UnifiedDataHelperTest, IsTempUData_EmptyData001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "IsTempUData_EmptyData001 begin.");
    UnifiedData data;
    bool ret = UnifiedDataHelper::IsTempUData(data);
    EXPECT_FALSE(ret);
    LOG_INFO(UDMF_TEST, "IsTempUData_EmptyData001 end.");
}

/**
* @tc.name: IsTempUData_NullptrRecord001
* @tc.desc: Test IsTempUData with nullptr record
* @tc.type: FUNC
*/
HWTEST_F(UnifiedDataHelperTest, IsTempUData_NullptrRecord001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "IsTempUData_NullptrRecord001 begin.");
    UnifiedData data;
    data.records_ = {nullptr};
    bool ret = UnifiedDataHelper::IsTempUData(data);
    EXPECT_FALSE(ret);
    LOG_INFO(UDMF_TEST, "IsTempUData_NullptrRecord001 end.");
}

/**
* @tc.name: IsTempUData_NonFileRecord001
* @tc.desc: Test IsTempUData with non-FILE record
* @tc.type: FUNC
*/
HWTEST_F(UnifiedDataHelperTest, IsTempUData_NonFileRecord001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "IsTempUData_NonFileRecord001 begin.");
    UnifiedData data;
    auto record = std::make_shared<UnifiedRecord>(UDType::TEXT);
    data.AddRecord(record);
    bool ret = UnifiedDataHelper::IsTempUData(data);
    EXPECT_FALSE(ret);
    LOG_INFO(UDMF_TEST, "IsTempUData_NonFileRecord001 end.");
}

/**
* @tc.name: GetSummary_FileExtensions001
* @tc.desc: Test GetSummary with file URI extension extraction
* @tc.type: FUNC
*/
HWTEST_F(UnifiedDataHelperTest, GetSummary_FileExtensions001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetSummary_FileExtensions001 begin.");
    UnifiedData data;
    auto file = std::make_shared<File>("file:///data/test.jpg");
    data.AddRecord(file);

    Summary summary;
    UnifiedDataHelper::GetSummary(data, summary);

    auto extensions = summary.filenameExtensions;
    EXPECT_FALSE(extensions.empty());
    if (!extensions.empty()) {
        EXPECT_EQ(extensions[0], ".jpg");
    }
    LOG_INFO(UDMF_TEST, "GetSummary_FileExtensions001 end.");
}

/**
* @tc.name: GetSummary_FileExtensions002
* @tc.desc: Test GetSummary with multiple file URIs
* @tc.type: FUNC
*/
HWTEST_F(UnifiedDataHelperTest, GetSummary_FileExtensions002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetSummary_FileExtensions002 begin.");
    UnifiedData data;
    auto file1 = std::make_shared<File>("file:///data/test.jpg");
    auto file2 = std::make_shared<File>("file:///data/test2.png");
    data.AddRecord(file1);
    data.AddRecord(file2);

    Summary summary;
    UnifiedDataHelper::GetSummary(data, summary);

    auto extensions = summary.filenameExtensions;
    EXPECT_EQ(extensions.size(), 2);
    if (extensions.size() == 2) {
        EXPECT_NE(std::find(extensions.begin(), extensions.end(), ".jpg"), extensions.end());
        EXPECT_NE(std::find(extensions.begin(), extensions.end(), ".png"), extensions.end());
    }
    LOG_INFO(UDMF_TEST, "GetSummary_FileExtensions002 end.");
}

/**
* @tc.name: GetSummary_FileExtensions003
* @tc.desc: Test GetSummary with non-file URI
* @tc.type: FUNC
*/
HWTEST_F(UnifiedDataHelperTest, GetSummary_FileExtensions003, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetSummary_FileExtensions003 begin.");
    UnifiedData data;
    auto file = std::make_shared<File>("http://example.com/test.jpg");
    data.AddRecord(file);

    Summary summary;
    UnifiedDataHelper::GetSummary(data, summary);

    auto extensions = summary.filenameExtensions;
    EXPECT_TRUE(extensions.empty());
    LOG_INFO(UDMF_TEST, "GetSummary_FileExtensions003 end.");
}

/**
* @tc.name: GetSummary_FileExtensions004
 * @tc.desc: Test filenameExtensions with leading period, lowercase and dedup
* @tc.type: FUNC
*/
HWTEST_F(UnifiedDataHelperTest, GetSummary_FileExtensions004, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetSummary_FileExtensions004 begin.");
    UnifiedData data;
    auto file1 = std::make_shared<File>("file:///data/test.JPG");
    auto file2 = std::make_shared<File>("file:///data/test2.jpg");
    data.AddRecord(file1);
    data.AddRecord(file2);

    Summary summary;
    UnifiedDataHelper::GetSummary(data, summary);

    auto extensions = summary.filenameExtensions;
    EXPECT_EQ(extensions.size(), 1);
    if (!extensions.empty()) {
        EXPECT_EQ(extensions[0], ".jpg");
    }
    LOG_INFO(UDMF_TEST, "GetSummary_FileExtensions004 end.");
}

/**
 * @tc.name: GetSummary_FileExtensions005
 * @tc.desc: Test GetSummary extracts extension from a general.file-uri (FILE_URI) record
 * @tc.type: FUNC
 */
HWTEST_F(UnifiedDataHelperTest, GetSummary_FileExtensions005, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetSummary_FileExtensions005 begin.");
    UnifiedData data;
    std::shared_ptr<Object> fileUriObj = std::make_shared<Object>();
    fileUriObj->value_[ORI_URI] = "file:///data/test.jpg";
    data.AddRecord(std::make_shared<UnifiedRecord>(UDType::FILE_URI, fileUriObj));

    Summary summary;
    UnifiedDataHelper::GetSummary(data, summary);

    auto extensions = summary.filenameExtensions;
    EXPECT_EQ(extensions.size(), 1);
    if (!extensions.empty()) {
        EXPECT_EQ(extensions[0], ".jpg");
    }
    LOG_INFO(UDMF_TEST, "GetSummary_FileExtensions005 end.");
}

/**
 * @tc.name: GetSummary_FileExtensions006
 * @tc.desc: Test GetSummary skips non-file URI of a general.file-uri record
 * @tc.type: FUNC
 */
HWTEST_F(UnifiedDataHelperTest, GetSummary_FileExtensions006, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetSummary_FileExtensions006 begin.");
    UnifiedData data;
    std::shared_ptr<Object> fileUriObj = std::make_shared<Object>();
    fileUriObj->value_[ORI_URI] = "http://example.com/test.jpg";
    data.AddRecord(std::make_shared<UnifiedRecord>(UDType::FILE_URI, fileUriObj));

    Summary summary;
    UnifiedDataHelper::GetSummary(data, summary);

    EXPECT_TRUE(summary.filenameExtensions.empty());
    LOG_INFO(UDMF_TEST, "GetSummary_FileExtensions006 end.");
}

/**
 * @tc.name: GetSummary_FilenameExtensions_MultiDot001
 * @tc.desc: Test archive.tar.gz returns the last extension .gz
 * @tc.type: FUNC
 */
HWTEST_F(UnifiedDataHelperTest, GetSummary_FilenameExtensions_MultiDot001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetSummary_FilenameExtensions_MultiDot001 begin.");
    UnifiedData data;
    auto file = std::make_shared<File>("file:///data/archive.tar.gz");
    data.AddRecord(file);

    Summary summary;
    UnifiedDataHelper::GetSummary(data, summary);
    auto extensions = summary.filenameExtensions;
    EXPECT_EQ(extensions.size(), 1);
    if (!extensions.empty()) {
        EXPECT_EQ(extensions[0], ".gz");
    }
    LOG_INFO(UDMF_TEST, "GetSummary_FilenameExtensions_MultiDot001 end.");
}

/**
 * @tc.name: GetSummary_FilenameExtensions_EdgeCases001
 * @tc.desc: Test hidden file, no dot and trailing dot return empty
 * @tc.type: FUNC
 */
HWTEST_F(UnifiedDataHelperTest, GetSummary_FilenameExtensions_EdgeCases001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetSummary_FilenameExtensions_EdgeCases001 begin.");
    UnifiedData data;
    auto hidden = std::make_shared<File>("file:///data/.profile");
    auto noDot = std::make_shared<File>("file:///data/README");
    auto trailingDot = std::make_shared<File>("file:///data/name.");
    data.AddRecord(hidden);
    data.AddRecord(noDot);
    data.AddRecord(trailingDot);

    Summary summary;
    UnifiedDataHelper::GetSummary(data, summary);
    auto extensions = summary.filenameExtensions;
    EXPECT_TRUE(extensions.empty());
    LOG_INFO(UDMF_TEST, "GetSummary_FilenameExtensions_EdgeCases001 end.");
}

/**
 * @tc.name: GetSummary_FilenameExtensions_TooLong001
 * @tc.desc: Test extension exceeding max length returns empty
 * @tc.type: FUNC
 */
HWTEST_F(UnifiedDataHelperTest, GetSummary_FilenameExtensions_TooLong001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetSummary_FilenameExtensions_TooLong001 begin.");
    UnifiedData data;
    std::string longExt(200, 'x');
    auto file = std::make_shared<File>("file:///data/test." + longExt);
    data.AddRecord(file);

    Summary summary;
    UnifiedDataHelper::GetSummary(data, summary);
    auto extensions = summary.filenameExtensions;
    EXPECT_TRUE(extensions.empty());
    LOG_INFO(UDMF_TEST, "GetSummary_FilenameExtensions_TooLong001 end.");
}

/**
 * @tc.name: GetSummary_FilenameExtensions_QueryFragment001
 * @tc.desc: Test query and fragment do not affect the extension
 * @tc.type: FUNC
 */
HWTEST_F(UnifiedDataHelperTest, GetSummary_FilenameExtensions_QueryFragment001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetSummary_FilenameExtensions_QueryFragment001 begin.");
    UnifiedData data;
    auto file = std::make_shared<File>("file:///data/photo.png?x=.jpg#y");
    data.AddRecord(file);

    Summary summary;
    UnifiedDataHelper::GetSummary(data, summary);
    auto extensions = summary.filenameExtensions;
    EXPECT_EQ(extensions.size(), 1);
    if (!extensions.empty()) {
        EXPECT_EQ(extensions[0], ".png");
    }
    LOG_INFO(UDMF_TEST, "GetSummary_FilenameExtensions_QueryFragment001 end.");
}

/**
 * @tc.name: GetSummary_FilenameExtensions_TempData001
 * @tc.desc: Test packed temp data does not yield the temporary file extension
 * @tc.type: FUNC
 */
HWTEST_F(UnifiedDataHelperTest, GetSummary_FilenameExtensions_TempData001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetSummary_FilenameExtensions_TempData001 begin.");
    UnifiedData data;
    auto file = std::make_shared<File>("file:///data/test.jpg");
    data.AddRecord(file);
    EXPECT_TRUE(UnifiedDataHelper::Pack(data));

    Summary summary;
    UnifiedDataHelper::GetSummary(data, summary);
    auto extensions = summary.filenameExtensions;
    EXPECT_TRUE(extensions.empty());
    LOG_INFO(UDMF_TEST, "GetSummary_FilenameExtensions_TempData001 end.");
}

/**
 * @tc.name: GetSummary_FilenameExtensions_NonFile001
 * @tc.desc: Test non-file records (text/html) do not yield extensions
 * @tc.type: FUNC
 */
HWTEST_F(UnifiedDataHelperTest, GetSummary_FilenameExtensions_NonFile001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetSummary_FilenameExtensions_NonFile001 begin.");
    UnifiedData data;
    auto text = std::make_shared<UnifiedRecord>(UDType::TEXT);
    auto html = std::make_shared<UnifiedRecord>(UDType::HTML);
    data.AddRecord(text);
    data.AddRecord(html);

    Summary summary;
    UnifiedDataHelper::GetSummary(data, summary);
    auto extensions = summary.filenameExtensions;
    EXPECT_TRUE(extensions.empty());
    LOG_INFO(UDMF_TEST, "GetSummary_FilenameExtensions_NonFile001 end.");
}

/**
 * @tc.name: GetSummary_FilenameExtensions_Order001
 * @tc.desc: Test extensions preserve first occurrence order
 * @tc.type: FUNC
 */
HWTEST_F(UnifiedDataHelperTest, GetSummary_FilenameExtensions_Order001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetSummary_FilenameExtensions_Order001 begin.");
    UnifiedData data;
    auto file1 = std::make_shared<File>("file:///data/a.gif");
    auto file2 = std::make_shared<File>("file:///data/b.jpg");
    auto file3 = std::make_shared<File>("file:///data/c.png");
    data.AddRecord(file1);
    data.AddRecord(file2);
    data.AddRecord(file3);

    Summary summary;
    UnifiedDataHelper::GetSummary(data, summary);
    auto extensions = summary.filenameExtensions;
    ASSERT_EQ(extensions.size(), 3);
    EXPECT_EQ(extensions[0], ".gif");
    EXPECT_EQ(extensions[1], ".jpg");
    EXPECT_EQ(extensions[2], ".png");
    LOG_INFO(UDMF_TEST, "GetSummary_FilenameExtensions_Order001 end.");
}

/**
 * @tc.name: GetSummary_FilenameExtensions_EmptyData001
 * @tc.desc: Test empty UnifiedData yields empty extensions
 * @tc.type: FUNC
 */
HWTEST_F(UnifiedDataHelperTest, GetSummary_FilenameExtensions_EmptyData001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetSummary_FilenameExtensions_EmptyData001 begin.");
    UnifiedData data;
    Summary summary;
    UnifiedDataHelper::GetSummary(data, summary);
    auto extensions = summary.filenameExtensions;
    EXPECT_TRUE(extensions.empty());
    LOG_INFO(UDMF_TEST, "GetSummary_FilenameExtensions_EmptyData001 end.");
}

/**
 * @tc.name: GetSummary_FilenameExtensions_Folder001
 * @tc.desc: Test folder record does not yield extensions
 * @tc.type: FUNC
 */
HWTEST_F(UnifiedDataHelperTest, GetSummary_FilenameExtensions_Folder001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetSummary_FilenameExtensions_Folder001 begin.");
    UnifiedData data;
    auto folder = std::make_shared<Folder>("file:///data/folder.name/");
    data.AddRecord(folder);

    Summary summary;
    UnifiedDataHelper::GetSummary(data, summary);
    auto extensions = summary.filenameExtensions;
    EXPECT_TRUE(extensions.empty());
    LOG_INFO(UDMF_TEST, "GetSummary_FilenameExtensions_Folder001 end.");
}

/**
 * @tc.name: GetSummary_FilenameExtensions_InvalidUri001
 * @tc.desc: Test empty URI yields empty extensions
 * @tc.type: FUNC
 */
HWTEST_F(UnifiedDataHelperTest, GetSummary_FilenameExtensions_InvalidUri001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetSummary_FilenameExtensions_InvalidUri001 begin.");
    UnifiedData data;
    auto file = std::make_shared<File>("");
    data.AddRecord(file);

    Summary summary;
    UnifiedDataHelper::GetSummary(data, summary);
    auto extensions = summary.filenameExtensions;
    EXPECT_TRUE(extensions.empty());
    LOG_INFO(UDMF_TEST, "GetSummary_FilenameExtensions_InvalidUri001 end.");
}

/**
 * @tc.name: GetSummary_FilenameExtensions_LargeFile001
 * @tc.desc: Test a large file (big size) still yields the correct extension without reading content
 * @tc.type: FUNC
 */
HWTEST_F(UnifiedDataHelperTest, GetSummary_FilenameExtensions_LargeFile001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetSummary_FilenameExtensions_LargeFile001 begin.");
    UnifiedData data;
    auto largeFile = std::make_shared<File>("file:///data/storage/el2/base/haps/large_video.mp4");
    UDDetails details;
    details.insert({ "large_content", std::string(10 * 1024 * 1024, 'x') });
    largeFile->SetDetails(details);
    data.AddRecord(largeFile);

    EXPECT_GT(largeFile->GetSize(), 10 * 1024 * 1024);
    Summary summary;
    UnifiedDataHelper::GetSummary(data, summary);
    auto extensions = summary.filenameExtensions;
    ASSERT_EQ(extensions.size(), 1);
    EXPECT_EQ(extensions[0], ".mp4");
    LOG_INFO(UDMF_TEST, "GetSummary_FilenameExtensions_LargeFile001 end.");
}

/**
 * @tc.name: GetSummary_FilenameExtensions_NonFileScheme001
 * @tc.desc: Test non file:// scheme and relative path yield empty extensions
 * @tc.type: FUNC
 */
HWTEST_F(UnifiedDataHelperTest, GetSummary_FilenameExtensions_NonFileScheme001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetSummary_FilenameExtensions_NonFileScheme001 begin.");
    UnifiedData data;
    auto https = std::make_shared<File>("https://data/storage/el2/base/haps/101.png");
    auto content = std::make_shared<File>("content://media/external/images/101.jpg");
    auto relative = std::make_shared<File>("data/storage/el2/base/haps/101.txt");
    data.AddRecord(https);
    data.AddRecord(content);
    data.AddRecord(relative);

    Summary summary;
    UnifiedDataHelper::GetSummary(data, summary);
    auto extensions = summary.filenameExtensions;
    EXPECT_TRUE(extensions.empty());
    LOG_INFO(UDMF_TEST, "GetSummary_FilenameExtensions_NonFileScheme001 end.");
}

/**
 * @tc.name: GetSummary_FilenameExtensions_CaseInsensitive001
 * @tc.desc: Test case-insensitive dedup and first-occurrence order
 * @tc.type: FUNC
 */
HWTEST_F(UnifiedDataHelperTest, GetSummary_FilenameExtensions_CaseInsensitive001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetSummary_FilenameExtensions_CaseInsensitive001 begin.");
    UnifiedData data;
    auto jpg = std::make_shared<File>("file:///data/a.jpg");
    auto png = std::make_shared<File>("file:///data/b.png");
    auto jpgUpper = std::make_shared<File>("file:///data/c.JPG");
    data.AddRecord(jpg);
    data.AddRecord(png);
    data.AddRecord(jpgUpper);

    Summary summary;
    UnifiedDataHelper::GetSummary(data, summary);
    auto extensions = summary.filenameExtensions;
    ASSERT_EQ(extensions.size(), 2);
    EXPECT_EQ(extensions[0], ".jpg");
    EXPECT_EQ(extensions[1], ".png");
    LOG_INFO(UDMF_TEST, "GetSummary_FilenameExtensions_CaseInsensitive001 end.");
}

/**
 * @tc.name: GetSummary_FilenameExtensions_Backslash001
 * @tc.desc: Test backslash path separator still yields the correct extension
 * @tc.type: FUNC
 */
HWTEST_F(UnifiedDataHelperTest, GetSummary_FilenameExtensions_Backslash001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetSummary_FilenameExtensions_Backslash001 begin.");
    UnifiedData data;
    auto file = std::make_shared<File>("file:///data\\storage\\el2\\base\\haps\\101.png");
    data.AddRecord(file);

    Summary summary;
    UnifiedDataHelper::GetSummary(data, summary);
    auto extensions = summary.filenameExtensions;
    ASSERT_EQ(extensions.size(), 1);
    EXPECT_EQ(extensions[0], ".png");
    LOG_INFO(UDMF_TEST, "GetSummary_FilenameExtensions_Backslash001 end.");
}

/**
 * @tc.name: GetSummary_FilenameExtensions_TrailingSlash001
 * @tc.desc: Test directory URI with trailing slash yields empty extensions
 * @tc.type: FUNC
 */
HWTEST_F(UnifiedDataHelperTest, GetSummary_FilenameExtensions_TrailingSlash001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetSummary_FilenameExtensions_TrailingSlash001 begin.");
    UnifiedData data;
    auto dir = std::make_shared<File>("file:///data/dir/");
    data.AddRecord(dir);

    Summary summary;
    UnifiedDataHelper::GetSummary(data, summary);
    auto extensions = summary.filenameExtensions;
    EXPECT_TRUE(extensions.empty());
    LOG_INFO(UDMF_TEST, "GetSummary_FilenameExtensions_TrailingSlash001 end.");
}

/**
 * @tc.name: GetSummary_FilenameExtensions_NullRecord001
 * @tc.desc: Test null record is skipped without yielding extensions
 * @tc.type: FUNC
 */
HWTEST_F(UnifiedDataHelperTest, GetSummary_FilenameExtensions_NullRecord001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetSummary_FilenameExtensions_NullRecord001 begin.");
    UnifiedData data;
    data.AddRecord(nullptr);

    Summary summary;
    UnifiedDataHelper::GetSummary(data, summary);
    auto extensions = summary.filenameExtensions;
    EXPECT_TRUE(extensions.empty());
    LOG_INFO(UDMF_TEST, "GetSummary_FilenameExtensions_NullRecord001 end.");
}

/**
 * @tc.name: GetSummary_FilenameExtensions_FragmentOnly001
 * @tc.desc: Test fragment without query does not affect the extension
 * @tc.type: FUNC
 */
HWTEST_F(UnifiedDataHelperTest, GetSummary_FilenameExtensions_FragmentOnly001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetSummary_FilenameExtensions_FragmentOnly001 begin.");
    UnifiedData data;
    auto file = std::make_shared<File>("file:///data/photo.png#frag");
    data.AddRecord(file);

    Summary summary;
    UnifiedDataHelper::GetSummary(data, summary);
    auto extensions = summary.filenameExtensions;
    ASSERT_EQ(extensions.size(), 1);
    EXPECT_EQ(extensions[0], ".png");
    LOG_INFO(UDMF_TEST, "GetSummary_FilenameExtensions_FragmentOnly001 end.");
}
} // OHOS::Test
