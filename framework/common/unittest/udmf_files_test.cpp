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
* @tc.name: Copy002
* @tc.desc: normal copy test
* @tc.type: FUNC
*/
HWTEST_F(CopyFileTest, Copy002, TestSize.Level1)
{
    std::string srcUri = "test_src.txt";
    std::string destUri = "test_dest.txt";
    auto record = std::make_shared<UnifiedRecord>();
    auto asyncHelper = std::make_unique<AsyncHelper>();
    UdmfCopyFile::CopyContext context(asyncHelper);

    bool result = UdmfCopyFile::GetInstance().CopyFile(srcUri, destUri, record, context);
    EXPECT_TRUE(result);
    EXPECT_EQ(context.status, E_OK);
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
* @tc.name: GetFileName001
* @tc.desc: GetFileName Should Handle Remote Files Correctly
* @tc.type: FUNC
*/
HWTEST_F(CopyFileTest, GetFileName001, TestSize.Level1)
{
    std::string remoteFile = "file://data/storage/el2/distributedfiles/103.png";
    auto result = UdmfCopyFile::GetInstance().GetFileName(remoteFile);
    ASSERT_EQ(result, "103.png");
}

/**
* @tc.name: GetFileName002
* @tc.desc: GetFileName Should Handle Remote Files Correctly
* @tc.type: FUNC
*/
HWTEST_F(CopyFileTest, GetFileName002, TestSize.Level1)
{
    std::string remoteFile = "file://data/storage/el2/distributedfiles/103.png?networkid=xxx";
    auto result = UdmfCopyFile::GetInstance().GetFileName(remoteFile);
    ASSERT_EQ(result, "103.png");
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

/**
* @tc.name: Marshalling003
* @tc.desc: Normal testcase of Marshalling
* @tc.type: FUNC
*/
HWTEST_F(UdmfTypesUtilTest, Marshalling003, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "Marshalling003 begin.");
    AsyncProcessInfo input;
    input.srcDevName = "srcDevName";
    input.syncFinished = 0;
    input.syncTotal = 1;
    input.syncId = 2;
    input.permFnished = 3;
    input.permTotal = 4;
    MessageParcel parcel;
    bool ret = ITypesUtil::Marshalling(input, parcel);
    EXPECT_TRUE(ret);
    LOG_INFO(UDMF_TEST, "Marshalling003 end.");
}

/**
* @tc.name: Marshalling004
* @tc.desc: Normal testcase of Marshalling
* @tc.type: FUNC
*/
HWTEST_F(UdmfTypesUtilTest, Marshalling004, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "Marshalling004 begin.");
    UnifiedData unifiedData;
    std::vector<UnifiedData> input = {unifiedData};
    MessageParcel parcel;
    bool ret = ITypesUtil::Marshalling(input, parcel);
    EXPECT_TRUE(ret);
    LOG_INFO(UDMF_TEST, "Marshalling004 end.");
}

/**
* @tc.name: Marshalling005
* @tc.desc: Normal testcase of Marshalling
* @tc.type: FUNC
*/
HWTEST_F(UdmfTypesUtilTest, Marshalling005, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "Marshalling005 begin.");
    UDType input = UDType::ENTITY;
    MessageParcel parcel;
    bool ret = ITypesUtil::Marshalling(input, parcel);
    EXPECT_TRUE(ret);
    LOG_INFO(UDMF_TEST, "Marshalling005 end.");
}

/**
* @tc.name: Unmarshalling008
* @tc.desc: Normal testcase of Unmarshalling
* @tc.type: FUNC
*/
HWTEST_F(UdmfTypesUtilTest, Unmarshalling008, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "Unmarshalling008 begin.");
    UDType input = UDType::ENTITY;
    MessageParcel parcel;
    ITypesUtil::Marshalling(input, parcel);
    UDType output;
    bool ret = ITypesUtil::Unmarshalling(output, parcel);
    EXPECT_EQ(input, output);
    EXPECT_TRUE(ret);
    LOG_INFO(UDMF_TEST, "Unmarshalling008 end.");
}

/**
* @tc.name: Unmarshalling009
* @tc.desc: Normal testcase of Unmarshalling
* @tc.type: FUNC
*/
HWTEST_F(UdmfTypesUtilTest, Unmarshalling009, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "Unmarshalling009 begin.");
    Intention input = Intention::UD_INTENTION_DRAG;
    MessageParcel parcel;
    ITypesUtil::Marshalling(input, parcel);
    Intention output;
    bool ret = ITypesUtil::Unmarshalling(output, parcel);
    EXPECT_EQ(input, output);
    EXPECT_TRUE(ret);
    LOG_INFO(UDMF_TEST, "Unmarshalling009 end.");
}

/**
* @tc.name: Unmarshalling010
* @tc.desc: Normal testcase of Unmarshalling
* @tc.type: FUNC
*/
HWTEST_F(UdmfTypesUtilTest, Unmarshalling010, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "Unmarshalling010 begin.");
    DataLoadInfo input;
    input.sequenceKey = "seq_2023";
    input.types = {"typeA", "typeB", "typeC"};
    input.recordCount = 1000;

    MessageParcel parcel;
    ITypesUtil::Marshalling(input, parcel);
    DataLoadInfo output;
    bool ret = ITypesUtil::Unmarshalling(output, parcel);
    EXPECT_TRUE(ret);
    EXPECT_EQ(input.sequenceKey, output.sequenceKey);
    EXPECT_EQ(input.recordCount, output.recordCount);
    ASSERT_EQ(input.types.size(), output.types.size());
    for (auto &item : input.types) {
        EXPECT_TRUE(output.types.find(item) != output.types.end());
    }
    LOG_INFO(UDMF_TEST, "Unmarshalling010 end.");
}

/**
 * @tc.name: CheckTypeDescriptors_001
 * @tc.desc: Normal testcase of CheckTypeDescriptors
 * @tc.type: FUNC
 */
HWTEST_F(UtdCfgsCheckerTest, CheckTypeDescriptors_001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "CheckTypeDescriptors_001 begin.");
    CustomUtdCfgs typeCfgs;
    TypeDescriptorCfg tdc1;
    tdc1.typeId = "com.demo.test.type";
    tdc1.filenameExtensions = {".abc"};
    tdc1.belongingToTypes = {"com.demo.test.parent"};
    tdc1.mimeTypes = {"parent/abc"};
    std::vector<TypeDescriptorCfg> first = {tdc1};
    TypeDescriptorCfg tdc2;
    tdc2.typeId = "com.demo.test.type2";
    tdc2.filenameExtensions = {".abc2"};
    tdc2.belongingToTypes = {"com.demo.test.parent2"};
    tdc2.mimeTypes = {"parent2/abc"};
    std::vector<TypeDescriptorCfg> second = {tdc2};
    CustomUtdCfgs customUtdCfgs = {first, second};

    TypeDescriptorCfg preTdc1;
    preTdc1.typeId = "com.demo.test.parent";
    TypeDescriptorCfg preTdc2;
    preTdc2.typeId = "com.demo.test.parent2";
    std::vector<TypeDescriptorCfg> presetCfgs = {preTdc1, preTdc2};

    std::vector<TypeDescriptorCfg> customCfgs = {};
    std::string bundleName("com.demo.test");

    bool result = UtdCfgsChecker::GetInstance().CheckTypeDescriptors(customUtdCfgs, presetCfgs, customCfgs, bundleName);
    EXPECT_TRUE(result);
    LOG_INFO(UDMF_TEST, "CheckTypeDescriptors_001 end.");
}

/**
 * @tc.name: CheckTypeDescriptors_002
 * @tc.desc: testcase of CheckTypeDescriptors: failed to match the regular expression
 * @tc.type: FUNC
 */
HWTEST_F(UtdCfgsCheckerTest, CheckTypeDescriptors_002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "CheckTypeDescriptors_002 begin.");
    CustomUtdCfgs typeCfgs;
    TypeDescriptorCfg tdc1;
    tdc1.typeId = "com.demo.test.type";
    std::vector<TypeDescriptorCfg> first = {tdc1};
    TypeDescriptorCfg tdc2;
    tdc2.typeId = "errorTypeId";
    std::vector<TypeDescriptorCfg> second = {tdc2};
    CustomUtdCfgs customUtdCfgs1 = {first, second};

    TypeDescriptorCfg preTdc1;
    preTdc1.typeId = "com.demo.test.parent";
    TypeDescriptorCfg preTdc2;
    preTdc2.typeId = "com.demo.test.parent2";
    std::vector<TypeDescriptorCfg> presetCfgs = {preTdc1, preTdc2};

    std::vector<TypeDescriptorCfg> customCfgs = {};
    std::string bundleName("com.demo.test");

    bool result = UtdCfgsChecker::GetInstance().CheckTypeDescriptors(customUtdCfgs1, presetCfgs, customCfgs,
        bundleName);
    EXPECT_FALSE(result);

    CustomUtdCfgs customUtdCfgs2 = {second, first};
    result = UtdCfgsChecker::GetInstance().CheckTypeDescriptors(customUtdCfgs2, presetCfgs, customCfgs, bundleName);
    EXPECT_FALSE(result);
    LOG_INFO(UDMF_TEST, "CheckTypeDescriptors_002 end.");
}

/**
 * @tc.name: CheckTypeDescriptors_003
 * @tc.desc: testcase of CheckTypeDescriptors: empty testcase
 * @tc.type: FUNC
 */
HWTEST_F(UtdCfgsCheckerTest, CheckTypeDescriptors_003, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "CheckTypeDescriptors_003 begin.");
    CustomUtdCfgs typeCfgs;
    std::vector<TypeDescriptorCfg> first = {};
    std::vector<TypeDescriptorCfg> second = {};
    CustomUtdCfgs customUtdCfgs = {first, second};
    std::vector<TypeDescriptorCfg> presetCfgs = {};
    std::vector<TypeDescriptorCfg> customCfgs = {};
    std::string bundleName("com.demo.test");

    bool result = UtdCfgsChecker::GetInstance().CheckTypeDescriptors(customUtdCfgs, presetCfgs, customCfgs, bundleName);
    EXPECT_FALSE(result);
    LOG_INFO(UDMF_TEST, "CheckTypeDescriptors_003 end.");
}

/**
 * @tc.name: CheckTypeDescriptors_004
 * @tc.desc: testcase of CheckTypeDescriptors: filename, belongingToType or mimeType not match
 * @tc.type: FUNC
 */
HWTEST_F(UtdCfgsCheckerTest, CheckTypeDescriptors_004, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "CheckTypeDescriptors_004 begin.");
    CustomUtdCfgs typeCfgs;
    TypeDescriptorCfg tdc1;
    tdc1.typeId = "com.demo.test.type";
    std::vector<TypeDescriptorCfg> first = {tdc1};
    TypeDescriptorCfg tdc2;
    tdc2.typeId = "com.demo.test.type2";
    tdc2.filenameExtensions = {".abc2"};
    tdc2.belongingToTypes = {"com.demo.test.parent2"};
    tdc2.mimeTypes = {"parent2/abc"};
    std::vector<TypeDescriptorCfg> second = {tdc2};
    CustomUtdCfgs customUtdCfgs = {first, second};

    TypeDescriptorCfg preTdc1;
    preTdc1.typeId = "com.demo.test.parent";
    TypeDescriptorCfg preTdc2;
    preTdc2.typeId = "com.demo.test.parent2";
    std::vector<TypeDescriptorCfg> presetCfgs = {preTdc1, preTdc2};

    std::vector<TypeDescriptorCfg> customCfgs = {};
    std::string bundleName("com.demo.test");

    bool result = UtdCfgsChecker::GetInstance().CheckTypeDescriptors(customUtdCfgs, presetCfgs, customCfgs, bundleName);
    EXPECT_FALSE(result);

    tdc1.filenameExtensions = {".abc"};
    first = {tdc1};
    customUtdCfgs = {first, second};
    result = UtdCfgsChecker::GetInstance().CheckTypeDescriptors(customUtdCfgs, presetCfgs, customCfgs, bundleName);
    EXPECT_FALSE(result);

    tdc1.belongingToTypes = {"com.demo.test.parent"};
    tdc1.mimeTypes = {""};
    first = {tdc1};
    customUtdCfgs = {first, second};
    result = UtdCfgsChecker::GetInstance().CheckTypeDescriptors(customUtdCfgs, presetCfgs, customCfgs, bundleName);
    EXPECT_FALSE(result);

    tdc1.mimeTypes = {"parent/abc"};
    first = {tdc1};
    customUtdCfgs = {first, second};
    result = UtdCfgsChecker::GetInstance().CheckTypeDescriptors(customUtdCfgs, presetCfgs, customCfgs, bundleName);
    EXPECT_TRUE(result);
    LOG_INFO(UDMF_TEST, "CheckTypeDescriptors_004 end.");
}

} // OHOS::Test