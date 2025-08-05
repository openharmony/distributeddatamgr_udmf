/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define LOG_TAG "UdmfTypesUtilMockTest"

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
#include "message_parcel_mock.h"

using namespace testing;
using namespace testing::ext;
using namespace OHOS::UDMF;
using namespace OHOS;
namespace OHOS::Test {
using namespace std;
static constexpr int32_t NORMAL_MAX_PARCEL_SIZE = 128 * 1024 * 1024;
class UdmfTypesUtilMockTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
    static inline shared_ptr<MessageParcelMock> messageParcelMock_ = nullptr;
};

void UdmfTypesUtilMockTest::SetUpTestCase()
{
    messageParcelMock_ = make_shared<MessageParcelMock>();
    MessageParcelMock::messageParcel = messageParcelMock_;
}

void UdmfTypesUtilMockTest::TearDownTestCase()
{
}

void UdmfTypesUtilMockTest::SetUp()
{
}

void UdmfTypesUtilMockTest::TearDown()
{
}

/**
* @tc.name: Unmarshalling001
* @tc.desc: Unmarshalling UnifiedData
* @tc.type: FUNC
*/
HWTEST_F(UdmfTypesUtilMockTest, Unmarshalling001, TestSize.Level1)
{
    std::vector<UnifiedData> unifiedDataList;
    MessageParcel parcel;
    EXPECT_CALL(*messageParcelMock_, GetDataSize()).WillOnce(Return(10))
        .WillOnce(Return(10))
        .WillOnce(Return(NORMAL_MAX_PARCEL_SIZE + 1));
    EXPECT_CALL(*messageParcelMock_, ReadInt32()).WillOnce(Return(-1))
        .WillOnce(Return(UnifiedData::MAX_DATA_SIZE + 1))
        .WillOnce(Return(10));
    bool ret = ITypesUtil::Unmarshalling(unifiedDataList, parcel);
    EXPECT_FALSE(ret);
    ret = ITypesUtil::Unmarshalling(unifiedDataList, parcel);
    EXPECT_FALSE(ret);
    ret = ITypesUtil::Unmarshalling(unifiedDataList, parcel);
    EXPECT_FALSE(ret);
}

/**
* @tc.name: Unmarshalling002
* @tc.desc: Unmarshalling UnifiedData
* @tc.type: FUNC
*/
HWTEST_F(UdmfTypesUtilMockTest, Unmarshalling002, TestSize.Level1)
{
    UnifiedData unifiedData;
    MessageParcel parcel;
    EXPECT_CALL(*messageParcelMock_, GetDataSize()).WillOnce(Return(10))
        .WillOnce(Return(10))
        .WillOnce(Return(NORMAL_MAX_PARCEL_SIZE + 1));
    EXPECT_CALL(*messageParcelMock_, ReadInt32()).WillOnce(Return(-1))
        .WillOnce(Return(UnifiedData::MAX_DATA_SIZE + 1))
        .WillOnce(Return(10));
    bool ret = ITypesUtil::Unmarshalling(unifiedData, parcel);
    EXPECT_FALSE(ret);
    ret = ITypesUtil::Unmarshalling(unifiedData, parcel);
    EXPECT_FALSE(ret);
    ret = ITypesUtil::Unmarshalling(unifiedData, parcel);
    EXPECT_FALSE(ret);
}

/**
* @tc.name: Unmarshalling003
* @tc.desc: Unmarshalling summary
* @tc.type: FUNC
*/
HWTEST_F(UdmfTypesUtilMockTest, Unmarshalling003, TestSize.Level1)
{
    Summary summary;
    MessageParcel parcel;
    EXPECT_CALL(*messageParcelMock_, GetDataSize()).WillOnce(Return(-1))
        .WillOnce(Return(NORMAL_MAX_PARCEL_SIZE + 1));
    bool ret = ITypesUtil::Unmarshalling(summary, parcel);
    EXPECT_FALSE(ret);
    ret = ITypesUtil::Unmarshalling(summary, parcel);
    EXPECT_FALSE(ret);
}

/**
* @tc.name: Unmarshalling004
* @tc.desc: Unmarshalling privilege
* @tc.type: FUNC
*/
HWTEST_F(UdmfTypesUtilMockTest, Unmarshalling004, TestSize.Level1)
{
    Privilege privileges;
    MessageParcel parcel;
    EXPECT_CALL(*messageParcelMock_, GetDataSize()).WillOnce(Return(-1))
        .WillOnce(Return(NORMAL_MAX_PARCEL_SIZE + 1));
    bool ret = ITypesUtil::Unmarshalling(privileges, parcel);
    EXPECT_FALSE(ret);
    ret = ITypesUtil::Unmarshalling(privileges, parcel);
    EXPECT_FALSE(ret);
}


/**
* @tc.name: Unmarshalling005
* @tc.desc: Unmarshalling CustomOption
* @tc.type: FUNC
*/
HWTEST_F(UdmfTypesUtilMockTest, Unmarshalling005, TestSize.Level1)
{
    CustomOption option;
    MessageParcel parcel;
    EXPECT_CALL(*messageParcelMock_, GetDataSize()).WillOnce(Return(-1))
        .WillOnce(Return(NORMAL_MAX_PARCEL_SIZE + 1));
    bool ret = ITypesUtil::Unmarshalling(option, parcel);
    EXPECT_FALSE(ret);
    ret = ITypesUtil::Unmarshalling(option, parcel);
    EXPECT_FALSE(ret);
}

/**
* @tc.name: Unmarshalling006
* @tc.desc: Unmarshalling QueryOption
* @tc.type: FUNC
*/
HWTEST_F(UdmfTypesUtilMockTest, Unmarshalling006, TestSize.Level1)
{
    QueryOption queryOption;
    MessageParcel parcel;
    EXPECT_CALL(*messageParcelMock_, GetDataSize()).WillOnce(Return(-1))
        .WillOnce(Return(NORMAL_MAX_PARCEL_SIZE + 1));
    bool ret = ITypesUtil::Unmarshalling(queryOption, parcel);
    EXPECT_FALSE(ret);
    ret = ITypesUtil::Unmarshalling(queryOption, parcel);
    EXPECT_FALSE(ret);
}

/**
* @tc.name: Unmarshalling007
* @tc.desc: Unmarshalling UDType
* @tc.type: FUNC
*/
HWTEST_F(UdmfTypesUtilMockTest, Unmarshalling007, TestSize.Level1)
{
    UDType type;
    MessageParcel parcel;
    EXPECT_CALL(*messageParcelMock_, GetDataSize()).WillOnce(Return(-1))
        .WillOnce(Return(NORMAL_MAX_PARCEL_SIZE + 1));
    bool ret = ITypesUtil::Unmarshalling(type, parcel);
    EXPECT_FALSE(ret);
    ret = ITypesUtil::Unmarshalling(type, parcel);
    EXPECT_FALSE(ret);
}

/**
* @tc.name: Unmarshalling008
* @tc.desc: Unmarshalling Intention
* @tc.type: FUNC
*/
HWTEST_F(UdmfTypesUtilMockTest, Unmarshalling008, TestSize.Level1)
{
    Intention intention;
    MessageParcel parcel;
    EXPECT_CALL(*messageParcelMock_, GetDataSize()).WillOnce(Return(-1))
        .WillOnce(Return(NORMAL_MAX_PARCEL_SIZE + 1));
    bool ret = ITypesUtil::Unmarshalling(intention, parcel);
    EXPECT_FALSE(ret);
    ret = ITypesUtil::Unmarshalling(intention, parcel);
    EXPECT_FALSE(ret);
}

/**
* @tc.name: Unmarshalling009
* @tc.desc: Unmarshalling Visibility
* @tc.type: FUNC
*/
HWTEST_F(UdmfTypesUtilMockTest, Unmarshalling009, TestSize.Level1)
{
    Visibility visibility;
    MessageParcel parcel;
    EXPECT_CALL(*messageParcelMock_, GetDataSize()).WillOnce(Return(-1))
        .WillOnce(Return(NORMAL_MAX_PARCEL_SIZE + 1));
    bool ret = ITypesUtil::Unmarshalling(visibility, parcel);
    EXPECT_FALSE(ret);
    ret = ITypesUtil::Unmarshalling(visibility, parcel);
    EXPECT_FALSE(ret);
}

/**
* @tc.name: Unmarshalling010
* @tc.desc: Unmarshalling AsyncProcessInfo
* @tc.type: FUNC
*/
HWTEST_F(UdmfTypesUtilMockTest, Unmarshalling010, TestSize.Level1)
{
    AsyncProcessInfo asyncProcessInfo;
    MessageParcel parcel;
    EXPECT_CALL(*messageParcelMock_, GetDataSize()).WillOnce(Return(-1))
        .WillOnce(Return(NORMAL_MAX_PARCEL_SIZE + 1));
    bool ret = ITypesUtil::Unmarshalling(asyncProcessInfo, parcel);
    EXPECT_FALSE(ret);
    ret = ITypesUtil::Unmarshalling(asyncProcessInfo, parcel);
    EXPECT_FALSE(ret);
}

/**
* @tc.name: Unmarshalling011
* @tc.desc: Unmarshalling DataLoadInfo
* @tc.type: FUNC
*/
HWTEST_F(UdmfTypesUtilMockTest, Unmarshalling011, TestSize.Level1)
{
    DataLoadInfo dataLoadInfo;
    MessageParcel parcel;
    EXPECT_CALL(*messageParcelMock_, GetDataSize()).WillOnce(Return(10))
        .WillOnce(Return(10))
        .WillOnce(Return(NORMAL_MAX_PARCEL_SIZE + 1));
    EXPECT_CALL(*messageParcelMock_, ReadInt32()).WillOnce(Return(-1))
        .WillOnce(Return(NORMAL_MAX_PARCEL_SIZE + 1))
        .WillOnce(Return(10));
    bool ret = ITypesUtil::Unmarshalling(dataLoadInfo, parcel);
    EXPECT_FALSE(ret);
    ret = ITypesUtil::Unmarshalling(dataLoadInfo, parcel);
    EXPECT_FALSE(ret);
    ret = ITypesUtil::Unmarshalling(dataLoadInfo, parcel);
    EXPECT_FALSE(ret);
}
}