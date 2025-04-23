/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
#define LOG_TAG "CopyFileTest"

#include <unistd.h>
#include <gtest/gtest.h>
#include <string>

#include "logger.h"
#include "udmf_copy_file.h"

using namespace testing::ext;
using namespace OHOS::UDMF;
using namespace OHOS;
namespace OHOS::Test {
using namespace std;

class CopyFileTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void CopyFileTest::SetUpTestCase()
{
}

void CopyFileTest::TearDownTestCase()
{
}

void CopyFileTest::SetUp()
{
}

void CopyFileTest::TearDown()
{
}

/**
* @tc.name: GetInstance
* @tc.desc: GetInstance Should Return Same Instance
* @tc.type: FUNC
*/
HWTEST_F(CopyFileTest, GetInstance, TestSize.Level1)
{
    auto& instance1 = UdmfCopyFile::GetInstance();
    auto& instance2 = UdmfCopyFile::GetInstance();
    ASSERT_EQ(&instance1, &instance2);
}

/**
* @tc.name: Copy001
* @tc.desc: Copy Should Return Canceled When ProgressQueue Is Cancel
* @tc.type: FUNC
*/
HWTEST_F(CopyFileTest, Copy001, TestSize.Level1)
{
    auto asyncHelper = std::make_unique<AsyncHelper>();
    asyncHelper->progressQueue.Cancel();
    ASSERT_TRUE(asyncHelper->progressQueue.IsCancel());

    auto result = UdmfCopyFile::GetInstance().Copy(asyncHelper);
    ASSERT_EQ(result, E_COPY_CANCELED);
}

/**
* @tc.name: ConstructDestUri
* @tc.desc: Construct DestUri Should Correctly Construct Destination Path
* @tc.type: FUNC
*/
HWTEST_F(CopyFileTest, ConstructDestUri, TestSize.Level1)
{
    std::string destUri = "/destination";
    std::string srcUri = "/source/file.txt";
    auto result = UdmfCopyFile::GetInstance().ConstructDestUri(destUri, srcUri);
    ASSERT_EQ(result, "/destination/file.txt");
}

/**
* @tc.name: GetFileName
* @tc.desc: GetFileName Should Handle Remote Files Correctly
* @tc.type: FUNC
*/
HWTEST_F(CopyFileTest, GetFileName, TestSize.Level1)
{
    std::string remoteFile = "file.txt?networkid=123";
    auto result = UdmfCopyFile::GetInstance().GetFileName(remoteFile);
    ASSERT_EQ(result, "file.txt");
}

/**
* @tc.name: HandleRecord
* @tc.desc: HandleRecord Should Add To Processed Data For Non FileType
* @tc.type: FUNC
*/
HWTEST_F(CopyFileTest, HandleRecord, TestSize.Level1)
{
    auto record = std::make_shared<UnifiedRecord>();
    auto helper = std::make_unique<AsyncHelper>();
    UdmfCopyFile::CopyContext context(helper);
    bool result = UdmfCopyFile::GetInstance().HandleRecord(record, context);
    ASSERT_TRUE(result);
    ASSERT_EQ(context.processedData->GetRecords().size(), 1);
}

} // OHOS::Test