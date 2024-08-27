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
    std::vector<UnifiedData> output = std::vector<UnifiedData>();
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
    const Summary input{};
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
    const Privilege input{};
    MessageParcel parcel;
    bool ret = ITypesUtil::Marshalling(input, parcel);
    EXPECT_EQ(ret, ITypesUtil::Marshal(parcel, input.tokenId, input.readPermission, input.writePermission));
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
    bool ret = ITypesUtil::Marshalling(output, parcel);
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
    bool ret = ITypesUtil::Marshalling(output, parcel);
    EXPECT_EQ(ret, ITypesUtil::Unmarshal(parcel, output.key, output.intention));
    LOG_INFO(UDMF_TEST, "Unmarshalling005 end.");
}
} // OHOS::Test