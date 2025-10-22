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
#define LOG_TAG "UdmfClientAbnormalTest"

#include <unistd.h>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>

#include "logger.h"
#include "udmf_capi_common.h"
#include "udmf_client.h"
#include "udmf_service_client_mock.h"

using namespace testing::ext;
using namespace OHOS::UDMF;
using namespace OHOS;
namespace OHOS::Test {
using namespace std;
using namespace testing;

class UdmfClientAbnormalTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;

    static inline shared_ptr<UdmfServiceClientMock> mock_ = nullptr;
};

void UdmfClientAbnormalTest::SetUpTestCase()
{
}

void UdmfClientAbnormalTest::TearDownTestCase()
{
}

void UdmfClientAbnormalTest::SetUp()
{
    mock_ = make_shared<UdmfServiceClientMock>();
    MUdmfServiceClient::udmfServiceClient = mock_;
}

void UdmfClientAbnormalTest::TearDown()
{
    mock_ = nullptr;
    MUdmfServiceClient::udmfServiceClient = nullptr;
}

/**
* @tc.name: SetData001
* @tc.desc: Abnrmal testcase of SetData, the return value of GetInstance() is nullptr
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientAbnormalTest, SetData001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetData001 begin.");
    EXPECT_CALL(*mock_, GetInstance()).WillOnce(Return(nullptr));

    UdmfClient client;
    UnifiedData unifiedData;
    CustomOption option;
    option.intention = Intention::UD_INTENTION_DATA_HUB;
    std::string key = "testKey";

    Status ret = client.SetData(option, unifiedData, key);
    EXPECT_EQ(ret, Status::E_IPC);
    LOG_INFO(UDMF_TEST, "SetData001 end.");
}

/**
* @tc.name: GetData001
* @tc.desc: Abnrmal testcase of GetData, the return value of GetInstance() is nullptr
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientAbnormalTest, GetData001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetData001 begin.");
    EXPECT_CALL(*mock_, GetInstance()).WillOnce(Return(nullptr));

    UdmfClient client;
    const QueryOption query;
    UnifiedData unifiedData;

    Status ret = client.GetData(query, unifiedData);
    EXPECT_EQ(ret, Status::E_IPC);
    LOG_INFO(UDMF_TEST, "GetData001 end.");
}

/**
* @tc.name: GetBatchData001
* @tc.desc: Abnrmal testcase of GetBatchData, the return value of GetInstance() is nullptr
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientAbnormalTest, GetBatchData001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetBatchData001 begin.");
    EXPECT_CALL(*mock_, GetInstance()).WillOnce(Return(nullptr));

    UdmfClient client;
    const QueryOption query;
    std::vector<UnifiedData> unifiedDataSet;

    Status ret = client.GetBatchData(query, unifiedDataSet);
    EXPECT_EQ(ret, Status::E_IPC);
    LOG_INFO(UDMF_TEST, "GetBatchData001 end.");
}

/**
* @tc.name: UpdateData001
* @tc.desc: Abnrmal testcase of UpdateData, the return value of GetInstance() is nullptr
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientAbnormalTest, UpdateData001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "UpdateData001 begin.");
    EXPECT_CALL(*mock_, GetInstance()).WillOnce(Return(nullptr));

    UdmfClient client;
    const QueryOption query;
    UnifiedData unifiedData;

    Status ret = client.UpdateData(query, unifiedData);
    EXPECT_EQ(ret, Status::E_IPC);
    LOG_INFO(UDMF_TEST, "UpdateData001 end.");
}

/**
* @tc.name: DeleteData001
* @tc.desc: Abnrmal testcase of DeleteData, the return value of GetInstance() is nullptr
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientAbnormalTest, DeleteData001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "DeleteData001 begin.");
    EXPECT_CALL(*mock_, GetInstance()).WillOnce(Return(nullptr));

    UdmfClient client;
    const QueryOption query;
    std::vector<UnifiedData> unifiedDataSet;

    Status ret = client.DeleteData(query, unifiedDataSet);
    EXPECT_EQ(ret, Status::E_IPC);
    LOG_INFO(UDMF_TEST, "DeleteData001 end.");
}

/**
* @tc.name: AddPrivilege001
* @tc.desc: Abnrmal testcase of AddPrivilege, the return value of GetInstance() is nullptr
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientAbnormalTest, AddPrivilege001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "AddPrivilege001 begin.");
    EXPECT_CALL(*mock_, GetInstance()).WillOnce(Return(nullptr));

    UdmfClient client;
    const QueryOption query;
    Privilege privilege;

    Status ret = client.AddPrivilege(query, privilege);
    EXPECT_EQ(ret, Status::E_IPC);
    LOG_INFO(UDMF_TEST, "AddPrivilege001 end.");
}

/**
* @tc.name: Sync001
* @tc.desc: Abnrmal testcase of Sync, the return value of GetInstance() is nullptr
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientAbnormalTest, Sync001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "Sync001 begin.");
    EXPECT_CALL(*mock_, GetInstance()).WillOnce(Return(nullptr));

    UdmfClient client;
    const QueryOption query;
    const std::vector<std::string> devices;

    Status ret = client.Sync(query, devices);
    EXPECT_EQ(ret, Status::E_IPC);
    LOG_INFO(UDMF_TEST, "Sync001 end.");
}

/**
* @tc.name: IsRemoteData001
* @tc.desc: Abnrmal testcase of IsRemoteData, the return value of GetInstance() is nullptr
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientAbnormalTest, IsRemoteData001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "IsRemoteData001 begin.");
    EXPECT_CALL(*mock_, GetInstance()).WillOnce(Return(nullptr));

    UdmfClient client;
    const QueryOption query;
    bool result = true;

    Status ret = client.IsRemoteData(query, result);
    EXPECT_EQ(ret, Status::E_IPC);
    LOG_INFO(UDMF_TEST, "IsRemoteData001 end.");
}

/**
* @tc.name: SetAppShareOption001
* @tc.desc: Abnrmal testcase of SetAppShareOption, the return value of GetInstance() is nullptr
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientAbnormalTest, SetAppShareOption001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetAppShareOption001 begin.");
    EXPECT_CALL(*mock_, GetInstance()).WillOnce(Return(nullptr));

    UdmfClient client;
    const std::string intention = "intention";
    enum ShareOptions shareOption = ShareOptions::IN_APP;

    Status ret = client.SetAppShareOption(intention, shareOption);
    EXPECT_EQ(ret, Status::E_IPC);
    LOG_INFO(UDMF_TEST, "SetAppShareOption001 end.");
}

/**
* @tc.name: GetAppShareOption001
* @tc.desc: Abnrmal testcase of GetAppShareOption, the return value of GetInstance() is nullptr
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientAbnormalTest, GetAppShareOption001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetAppShareOption001 begin.");
    EXPECT_CALL(*mock_, GetInstance()).WillOnce(Return(nullptr));

    UdmfClient client;
    const std::string intention = "intention";
    enum ShareOptions shareOption = ShareOptions::IN_APP;

    Status ret = client.SetAppShareOption(intention, shareOption);
    EXPECT_EQ(ret, Status::E_IPC);
    LOG_INFO(UDMF_TEST, "GetAppShareOption001 end.");
}

/**
* @tc.name: RemoveAppShareOption001
* @tc.desc: Abnrmal testcase of RemoveAppShareOption, the return value of GetInstance() is nullptr
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientAbnormalTest, RemoveAppShareOption001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "RemoveAppShareOption001 begin.");
    EXPECT_CALL(*mock_, GetInstance()).WillOnce(Return(nullptr));

    UdmfClient client;
    const std::string intention = "intention";

    Status ret = client.RemoveAppShareOption(intention);
    EXPECT_EQ(ret, Status::E_IPC);
    LOG_INFO(UDMF_TEST, "RemoveAppShareOption001 end.");
}

/**
* @tc.name: SaveAcceptableInfo001
* @tc.desc: Abnrmal testcase of SaveAcceptableInfo, the return value of GetInstance() is nullptr
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientAbnormalTest, SaveAcceptableInfo001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SaveAcceptableInfo001 begin.");
    EXPECT_CALL(*mock_, GetInstance()).WillOnce(Return(nullptr));

    UdmfClient client;
    std::string key = "udmf://ohos.test.demo1/drag/123456";
    DataLoadInfo info;

    Status ret = client.SaveAcceptableInfo(key, info);
    EXPECT_EQ(ret, Status::E_IPC);
    LOG_INFO(UDMF_TEST, "SaveAcceptableInfo001 end.");
}

/**
* @tc.name: PushAcceptableInfo001
* @tc.desc: Abnrmal testcase of PushAcceptableInfo, the return value of GetInstance() is nullptr
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientAbnormalTest, PushAcceptableInfo001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "PushAcceptableInfo001 begin.");
    EXPECT_CALL(*mock_, GetInstance()).WillOnce(Return(nullptr));

    UdmfClient client;
    QueryOption query = { .key = "udmf://ohos.test.demo1/drag/123456" };
    std::vector<std::string> devices = { "device1", "device2" };

    Status ret = client.PushAcceptableInfo(query, devices);
    EXPECT_EQ(ret, Status::E_IPC);
    LOG_INFO(UDMF_TEST, "PushAcceptableInfo001 end.");
}
} // OHOS::Test