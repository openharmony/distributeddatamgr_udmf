/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
#define LOG_TAG "UnifiedDataExtensionTest"

#include <algorithm>
#include <gtest/gtest.h>
#include <string>

#include "audio.h"
#include "file.h"
#include "folder.h"
#include "image.h"
#include "logger.h"
#include "unified_data_extension.h"
#include "unified_data_helper.h"
#include "unified_meta.h"
#include "unified_record.h"
#include "video.h"

using namespace testing::ext;
using namespace OHOS::UDMF;
using namespace OHOS;
namespace OHOS::Test {
using namespace std;

class UnifiedDataExtensionTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void UnifiedDataExtensionTest::SetUpTestCase()
{
}

void UnifiedDataExtensionTest::TearDownTestCase()
{
}

void UnifiedDataExtensionTest::SetUp()
{
}

void UnifiedDataExtensionTest::TearDown()
{
}

/**
 * @tc.name: CollectFilenameExtensions_Normal001
 * @tc.desc: Collect distinct extensions from file records
 * @tc.type: FUNC
 */
HWTEST_F(UnifiedDataExtensionTest, CollectFilenameExtensions_Normal001, TestSize.Level1)
{
    UnifiedData data;
    data.AddRecord(std::make_shared<File>("file:///data/a.jpg"));
    data.AddRecord(std::make_shared<File>("file:///data/b.png"));

    auto extensions = CollectFilenameExtensions(data);
    ASSERT_EQ(extensions.size(), 2);
    EXPECT_NE(std::find(extensions.begin(), extensions.end(), ".jpg"), extensions.end());
    EXPECT_NE(std::find(extensions.begin(), extensions.end(), ".png"), extensions.end());
}

/**
 * @tc.name: CollectFilenameExtensions_CaseAndDedup002
 * @tc.desc: Extensions are lowercased and deduplicated
 * @tc.type: FUNC
 */
HWTEST_F(UnifiedDataExtensionTest, CollectFilenameExtensions_CaseAndDedup002, TestSize.Level1)
{
    UnifiedData data;
    data.AddRecord(std::make_shared<File>("file:///data/a.jpg"));
    data.AddRecord(std::make_shared<File>("file:///data/b.JPG"));
    data.AddRecord(std::make_shared<File>("file:///data/c.png"));

    auto extensions = CollectFilenameExtensions(data);
    ASSERT_EQ(extensions.size(), 2);
    EXPECT_NE(std::find(extensions.begin(), extensions.end(), ".jpg"), extensions.end());
    EXPECT_NE(std::find(extensions.begin(), extensions.end(), ".png"), extensions.end());
}

/**
 * @tc.name: CollectFilenameExtensions_FileSubtypes003
 * @tc.desc: Image, audio, video and folder records yield their extensions
 * @tc.type: FUNC
 */
HWTEST_F(UnifiedDataExtensionTest, CollectFilenameExtensions_FileSubtypes003, TestSize.Level1)
{
    UnifiedData data;
    data.AddRecord(std::make_shared<Image>("file:///data/a.png"));
    data.AddRecord(std::make_shared<Audio>("file:///data/b.mp3"));
    data.AddRecord(std::make_shared<Video>("file:///data/c.mp4"));
    data.AddRecord(std::make_shared<Folder>("file:///data/d.zip"));

    auto extensions = CollectFilenameExtensions(data);
    ASSERT_EQ(extensions.size(), 4);
    EXPECT_NE(std::find(extensions.begin(), extensions.end(), ".png"), extensions.end());
    EXPECT_NE(std::find(extensions.begin(), extensions.end(), ".mp3"), extensions.end());
    EXPECT_NE(std::find(extensions.begin(), extensions.end(), ".mp4"), extensions.end());
    EXPECT_NE(std::find(extensions.begin(), extensions.end(), ".zip"), extensions.end());
}

/**
 * @tc.name: CollectFilenameExtensions_SkipNonFile004
 * @tc.desc: Non-file records and non file:// uri are skipped
 * @tc.type: FUNC
 */
HWTEST_F(UnifiedDataExtensionTest, CollectFilenameExtensions_SkipNonFile004, TestSize.Level1)
{
    UnifiedData data;
    data.AddRecord(std::make_shared<UnifiedRecord>(UDType::TEXT));
    data.AddRecord(std::make_shared<UnifiedRecord>(UDType::HTML));
    data.AddRecord(std::make_shared<File>("http://example.com/a.jpg"));

    auto extensions = CollectFilenameExtensions(data);
    EXPECT_TRUE(extensions.empty());
}

/**
 * @tc.name: CollectFilenameExtensions_SkipTempAndNull005
 * @tc.desc: Temp-flag record and null record are skipped
 * @tc.type: FUNC
 */
HWTEST_F(UnifiedDataExtensionTest, CollectFilenameExtensions_SkipTempAndNull005, TestSize.Level1)
{
    UnifiedData data;
    auto tempFile = std::make_shared<File>("file:///data/temp.jpg");
    UDDetails details;
    details.insert(std::make_pair(TEMP_UNIFIED_DATA_FLAG, true));
    tempFile->SetDetails(details);
    data.AddRecord(tempFile);
    data.AddRecord(nullptr);

    auto extensions = CollectFilenameExtensions(data);
    EXPECT_TRUE(extensions.empty());
}

/**
 * @tc.name: CollectFilenameExtensions_QueryFragment006
 * @tc.desc: Query and fragment in the uri do not affect the extension
 * @tc.type: FUNC
 */
HWTEST_F(UnifiedDataExtensionTest, CollectFilenameExtensions_QueryFragment006, TestSize.Level1)
{
    UnifiedData data;
    data.AddRecord(std::make_shared<File>("file:///data/photo.png?x=.jpg#y"));

    auto extensions = CollectFilenameExtensions(data);
    ASSERT_EQ(extensions.size(), 1);
    EXPECT_EQ(extensions[0], ".png");
}

/**
 * @tc.name: CollectFilenameExtensions_EdgeCases007
 * @tc.desc: Hidden file, no dot, trailing dot and overlong extension are skipped
 * @tc.type: FUNC
 */
HWTEST_F(UnifiedDataExtensionTest, CollectFilenameExtensions_EdgeCases007, TestSize.Level1)
{
    UnifiedData data;
    data.AddRecord(std::make_shared<File>("file:///data/.profile"));
    data.AddRecord(std::make_shared<File>("file:///data/README"));
    data.AddRecord(std::make_shared<File>("file:///data/name."));
    std::string longExt(200, 'x');
    data.AddRecord(std::make_shared<File>("file:///data/test." + longExt));

    auto extensions = CollectFilenameExtensions(data);
    EXPECT_TRUE(extensions.empty());
}

/**
 * @tc.name: CollectFilenameExtensions_EmptyData008
 * @tc.desc: Empty unified data yields empty extensions
 * @tc.type: FUNC
 */
HWTEST_F(UnifiedDataExtensionTest, CollectFilenameExtensions_EmptyData008, TestSize.Level1)
{
    UnifiedData data;
    auto extensions = CollectFilenameExtensions(data);
    EXPECT_TRUE(extensions.empty());
}

/**
 * @tc.name: CollectFilenameExtensions_FileUri009
 * @tc.desc: general.file-uri (FILE_URI) records yield their extensions
 * @tc.type: FUNC
 */
HWTEST_F(UnifiedDataExtensionTest, CollectFilenameExtensions_FileUri009, TestSize.Level1)
{
    UnifiedData data;
    std::shared_ptr<Object> fileUriObj = std::make_shared<Object>();
    fileUriObj->value_[ORI_URI] = "file:///data/a.jpg";
    data.AddRecord(std::make_shared<UnifiedRecord>(UDType::FILE_URI, fileUriObj));

    auto extensions = CollectFilenameExtensions(data);
    ASSERT_EQ(extensions.size(), 1);
    EXPECT_EQ(extensions[0], ".jpg");
}

/**
 * @tc.name: CollectFilenameExtensions_FileUriCaseDedup010
 * @tc.desc: general.file-uri extensions are lowercased and deduplicated
 * @tc.type: FUNC
 */
HWTEST_F(UnifiedDataExtensionTest, CollectFilenameExtensions_FileUriCaseDedup010, TestSize.Level1)
{
    UnifiedData data;
    std::shared_ptr<Object> jpgObj = std::make_shared<Object>();
    jpgObj->value_[ORI_URI] = "file:///data/a.JPG";
    std::shared_ptr<Object> pngObj = std::make_shared<Object>();
    pngObj->value_[ORI_URI] = "file:///data/b.png";
    data.AddRecord(std::make_shared<UnifiedRecord>(UDType::FILE_URI, jpgObj));
    data.AddRecord(std::make_shared<UnifiedRecord>(UDType::FILE_URI, pngObj));

    auto extensions = CollectFilenameExtensions(data);
    ASSERT_EQ(extensions.size(), 2);
    EXPECT_NE(std::find(extensions.begin(), extensions.end(), ".jpg"), extensions.end());
    EXPECT_NE(std::find(extensions.begin(), extensions.end(), ".png"), extensions.end());
}

/**
 * @tc.name: CollectFilenameExtensions003
 * @tc.desc: Test CollectFilenameExtensions yields extensions for every file subtype
 * @tc.type: FUNC
 */
HWTEST_F(UnifiedDataExtensionTest, CollectFilenameExtensions003, TestSize.Level1)
{
    UnifiedData data;
    data.AddRecord(std::make_shared<Image>("file:///data/a.png"));
    data.AddRecord(std::make_shared<Audio>("file:///data/b.mp3"));
    data.AddRecord(std::make_shared<Video>("file:///data/c.mp4"));
    data.AddRecord(std::make_shared<Folder>("file:///data/d.zip"));
    auto extensions = CollectFilenameExtensions(data);
    ASSERT_EQ(extensions.size(), 4);
    EXPECT_NE(std::find(extensions.begin(), extensions.end(), ".png"), extensions.end());
    EXPECT_NE(std::find(extensions.begin(), extensions.end(), ".mp3"), extensions.end());
    EXPECT_NE(std::find(extensions.begin(), extensions.end(), ".mp4"), extensions.end());
    EXPECT_NE(std::find(extensions.begin(), extensions.end(), ".zip"), extensions.end());
}

/**
 * @tc.name: ExtractFileExtension_Normal001
 * @tc.desc: Test ExtractFileExtension returns the normalized extension
 * @tc.type: FUNC
 */
HWTEST_F(UnifiedDataExtensionTest, ExtractFileExtension_Normal001, TestSize.Level1)
{
    std::string jpgUri = "file:///data/test.jpg";
    std::string upperJpgUri = "file:///data/test.JPG";
    std::string multiDotUri = "file:///data/archive.tar.gz";
    EXPECT_EQ(ExtractFileExtension(jpgUri), ".jpg");
    EXPECT_EQ(ExtractFileExtension(upperJpgUri), ".jpg");
    EXPECT_EQ(ExtractFileExtension(multiDotUri), ".gz");
}

/**
 * @tc.name: ExtractFileExtension_QueryFragment002
 * @tc.desc: Test query and fragment do not affect the extension
 * @tc.type: FUNC
 */
HWTEST_F(UnifiedDataExtensionTest, ExtractFileExtension_QueryFragment002, TestSize.Level1)
{
    std::string queryFragmentUri = "file:///data/photo.png?x=.jpg#y";
    std::string queryOnlyUri = "file:///data/photo.png?width=100";
    std::string fragmentOnlyUri = "file:///data/photo.png#frag";
    EXPECT_EQ(ExtractFileExtension(queryFragmentUri), ".png");
    EXPECT_EQ(ExtractFileExtension(queryOnlyUri), ".png");
    EXPECT_EQ(ExtractFileExtension(fragmentOnlyUri), ".png");
}

/**
 * @tc.name: ExtractFileExtension_EdgeCases003
 * @tc.desc: Test empty, hidden, no dot, trailing dot, trailing slash and overlong uri
 * @tc.type: FUNC
 */
HWTEST_F(UnifiedDataExtensionTest, ExtractFileExtension_EdgeCases003, TestSize.Level1)
{
    std::string emptyUri = "";
    std::string hiddenUri = "file:///data/.profile";
    std::string noDotUri = "file:///data/README";
    std::string trailingDotUri = "file:///data/name.";
    std::string dirUri = "file:///data/dir/";
    std::string longExt(200, 'x');
    std::string tooLongUri = "file:///data/test." + longExt;
    EXPECT_EQ(ExtractFileExtension(emptyUri), "");
    EXPECT_EQ(ExtractFileExtension(hiddenUri), "");
    EXPECT_EQ(ExtractFileExtension(noDotUri), "");
    EXPECT_EQ(ExtractFileExtension(trailingDotUri), "");
    EXPECT_EQ(ExtractFileExtension(dirUri), "");
    EXPECT_EQ(ExtractFileExtension(tooLongUri), "");
}

/**
 * @tc.name: ExtractFileExtension_Backslash004
 * @tc.desc: Test backslash path separator yields the correct extension
 * @tc.type: FUNC
 */
HWTEST_F(UnifiedDataExtensionTest, ExtractFileExtension_Backslash004, TestSize.Level1)
{
    std::string backslashUri = "file:///data\\storage\\101.png";
    EXPECT_EQ(ExtractFileExtension(backslashUri), ".png");
}
} // OHOS::Test
