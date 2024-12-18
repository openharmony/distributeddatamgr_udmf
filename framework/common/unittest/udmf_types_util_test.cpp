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
#define LOG_TAG "UdmfTypesUtilTest"

#include <unistd.h>
#include <gtest/gtest.h>
#include <string>

#include "logger.h"
#include "udmf_types_util.h"
#include "unified_meta.h"
#include "text.h"
#include "plain_text.h"
#include "file.h"
#include "image.h"
#include "system_defined_record.h"
#include "system_defined_form.h"
#include "application_defined_record.h"
#include "unified_types.h"
#include "udmf_client.h"

using namespace testing::ext;
using namespace OHOS::UDMF;
using namespace OHOS;
namespace OHOS::Test {
using namespace std;

class UdmfTypesUtilTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void UdmfTypesUtilTest::SetUpTestCase()
{
}

void UdmfTypesUtilTest::TearDownTestCase()
{
}

void UdmfTypesUtilTest::SetUp()
{
}

void UdmfTypesUtilTest::TearDown()
{
}

/**
* @tc.name: Unmarshalling001
* @tc.desc: Abnormal testcase of Unmarshalling, parcel is null
* @tc.type: FUNC
*/
HWTEST_F(UdmfTypesUtilTest, Unmarshalling001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "Unmarshalling001 begin.");

    UnifiedData input;
    std::vector<std::shared_ptr<UnifiedRecord>> inputRecords = {
        std::make_shared<Text>(),
        std::make_shared<PlainText>(),
        std::make_shared<File>(),
        std::make_shared<Image>(),
        std::make_shared<SystemDefinedRecord>(),
        std::make_shared<SystemDefinedForm>(),
        std::make_shared<ApplicationDefinedRecord>()
    };
    input.SetRecords(inputRecords);
    MessageParcel parcel;
    bool ret = ITypesUtil::Unmarshalling(input, parcel);
    EXPECT_FALSE(ret);
    LOG_INFO(UDMF_TEST, "Unmarshalling001 end.");
}

/**
* @tc.name: Unmarshalling002
* @tc.desc: Abnormal testcase of Unmarshalling, parcel is null
* @tc.type: FUNC
*/
HWTEST_F(UdmfTypesUtilTest, Unmarshalling002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "Unmarshalling002 begin.");
    UnifiedData unifiedData;
    std::vector<UnifiedData> output = {unifiedData};
    MessageParcel parcel;
    bool ret = ITypesUtil::Unmarshalling(output, parcel);
    EXPECT_FALSE(ret);
    LOG_INFO(UDMF_TEST, "Unmarshalling002 end.");
}

/**
* @tc.name: Marshalling001
* @tc.desc: Normal testcase of Marshalling
* @tc.type: FUNC
*/
HWTEST_F(UdmfTypesUtilTest, Marshalling001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "Marshalling001 begin.");
    Summary input;
    input.summary.insert({"summary", 10});
    input.totalSize = 20;
    MessageParcel parcel;
    bool ret = ITypesUtil::Marshalling(input, parcel);
    EXPECT_EQ(ret, ITypesUtil::Marshal(parcel, input.summary, input.totalSize));
    LOG_INFO(UDMF_TEST, "Marshalling001 end.");
}

/**
* @tc.name: Unmarshalling003
* @tc.desc: Normal testcase of Unmarshalling
* @tc.type: FUNC
*/
HWTEST_F(UdmfTypesUtilTest, Unmarshalling003, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "Unmarshalling003 begin.");
    Privilege output;
    output.tokenId = 5;
    output.readPermission = "readPermission";
    output.writePermission = "writePermission";
    MessageParcel parcel;
    bool ret = ITypesUtil::Unmarshalling(output, parcel);
    EXPECT_EQ(ret, ITypesUtil::Unmarshal(parcel, output.tokenId, output.readPermission, output.writePermission));
    LOG_INFO(UDMF_TEST, "Unmarshalling003 end.");
}

/**
* @tc.name: Unmarshalling004
* @tc.desc: Normal testcase of Unmarshalling
* @tc.type: FUNC
*/
HWTEST_F(UdmfTypesUtilTest, Unmarshalling004, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "Unmarshalling004 begin.");
    CustomOption output;
    MessageParcel parcel;
    bool ret = ITypesUtil::Unmarshalling(output, parcel);
    EXPECT_EQ(ret, ITypesUtil::Unmarshal(parcel, output.intention));
    LOG_INFO(UDMF_TEST, "Unmarshalling004 end.");
}

/**
* @tc.name: Unmarshalling005
* @tc.desc: Normal testcase of Unmarshalling
* @tc.type: FUNC
*/
HWTEST_F(UdmfTypesUtilTest, Unmarshalling005, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "Unmarshalling005 begin.");
    QueryOption output;
    MessageParcel parcel;
    bool ret = ITypesUtil::Unmarshalling(output, parcel);
    EXPECT_EQ(ret, ITypesUtil::Unmarshal(parcel, output.key, output.intention));
    LOG_INFO(UDMF_TEST, "Unmarshalling005 end.");
}

/**
* @tc.name: Marshalling002
* @tc.desc: Normal testcase of Marshalling
* @tc.type: FUNC
*/
HWTEST_F(UdmfTypesUtilTest, Marshalling002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "Marshalling002 begin.");
    const UDType input = UDType::ENTITY;
    MessageParcel parcel;
    bool ret = ITypesUtil::Marshalling(input, parcel);
    EXPECT_EQ(ret, ITypesUtil::Marshal(parcel, input));
    LOG_INFO(UDMF_TEST, "Marshalling002 end.");
}

/**
* @tc.name: Unmarshalling006
* @tc.desc: Normal testcase of Unmarshalling
* @tc.type: FUNC
*/
HWTEST_F(UdmfTypesUtilTest, Unmarshalling006, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "Unmarshalling006 begin.");
    UDType output = UDType::ENTITY;
    MessageParcel parcel;
    bool ret = ITypesUtil::Unmarshalling(output, parcel);
    EXPECT_FALSE(ret);
    LOG_INFO(UDMF_TEST, "Unmarshalling006 end.");
}

/**
* @tc.name: Unmarshalling007
* @tc.desc: Normal testcase of Unmarshalling
* @tc.type: FUNC
*/
HWTEST_F(UdmfTypesUtilTest, Unmarshalling007, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "Unmarshalling007 begin.");
    Intention output = Intention::UD_INTENTION_DRAG;
    MessageParcel parcel;
    bool ret = ITypesUtil::Unmarshalling(output, parcel);
    EXPECT_FALSE(ret);
    LOG_INFO(UDMF_TEST, "Unmarshalling007 end.");
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
} // OHOS::Test