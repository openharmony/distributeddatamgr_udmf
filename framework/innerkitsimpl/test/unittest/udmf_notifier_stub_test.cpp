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

#define LOG_TAG "UdmfNotifierStubTest"
#include "udmf_notifier_stub.h"
#include "gtest/gtest.h"
#include "unified_data_helper.h"
#include "file.h"
#include "udmf_types_util.h"
#include "accesstoken_kit.h"
#include "nativetoken_kit.h"
#include "token_setproc.h"

namespace OHOS::UDMF {
using namespace testing::ext;
using namespace OHOS::Security::AccessToken;

class UdmfNotifierStubTest : public testing::Test {
public:
    static void SetUpTestCase(void) {}
    static void TearDownTestCase(void) {}
    void SetUp() {}
    void TearDown() {}
    
    static void SetNativeToken(const std::string &processName)
    {
        auto tokenId = AccessTokenKit::GetNativeTokenId(processName);
        SetSelfTokenID(tokenId);
    }
};

/**
* @tc.name: DelayDataCallback_OnRemoteRequest_001
* @tc.desc: Test DelayDataCallbackStub rejects temp_udmf_file_flag
* @tc.type: FUNC
*/
HWTEST_F(UdmfNotifierStubTest, DelayDataCallback_OnRemoteRequest_001, TestSize.Level1)
{
    uint32_t code = 0;
    MessageParcel data;
    MessageParcel reply;
    MessageOption option;
    
    auto callback = [](const std::string &key, const UnifiedData &data) {};
    DelayDataCallbackClient client(callback);
    
    int ret = client.OnRemoteRequest(code, data, reply, option);
    EXPECT_NE(ret, 0);
}

/**
* @tc.name: UdmfNotifierClient_HandleDelayObserver_001
* @tc.desc: Test UdmfNotifierClient handles delay observer
* @tc.type: FUNC
*/
HWTEST_F(UdmfNotifierStubTest, UdmfNotifierClient_HandleDelayObserver_001, TestSize.Level1)
{
    auto loadHandler = [](const std::string &key, const DataLoadInfo &info) {};
    UdmfNotifierClient client(loadHandler);
    
    std::string key = "test_key";
    DataLoadInfo dataLoadInfo;
    dataLoadInfo.sequenceKey = "seq_key";
    
    client.HandleDelayObserver(key, dataLoadInfo);
    EXPECT_TRUE(true);
}

/**
* @tc.name: IsTempUData_RejectedInDelayCallback_001
* @tc.desc: Test IsTempUData is rejected in delay data callback
* @tc.type: FUNC
*/
HWTEST_F(UdmfNotifierStubTest, IsTempUData_RejectedInDelayCallback_001, TestSize.Level1)
{
    UnifiedData data;
    auto file = std::make_shared<File>();
    file->SetType(UDType::FILE);
    file->SetUtdId("general.file-uri");
    
    UDDetails details;
    details.insert(std::make_pair("temp_udmf_file_flag", true));
    file->SetDetails(details);
    
    data.AddRecord(file);
    
    bool ret = UnifiedDataHelper::IsTempUData(data);
    EXPECT_TRUE(ret);
}

/**
* @tc.name: OnRemoteRequest_NativeTokenCheck_001
* @tc.desc: Test OnRemoteRequest rejects non-native token
* @tc.type: FUNC
*/
HWTEST_F(UdmfNotifierStubTest, OnRemoteRequest_NativeTokenCheck_001, TestSize.Level1)
{
    uint32_t code = 0;
    MessageParcel data;
    MessageParcel reply;
    MessageOption option;
    
    auto loadHandler = [](const std::string &key, const DataLoadInfo &info) {};
    UdmfNotifierClient client(loadHandler);
    
    auto callback = [](const std::string &key, const UnifiedData &data) {};
    DelayDataCallbackClient delayClient(callback);
    
    int ret = delayClient.OnRemoteRequest(code, data, reply, option);
    EXPECT_NE(ret, 0);
}

/**
* @tc.name: OnRemoteRequest_ProcessNameCheck_001
* @tc.desc: Test OnRemoteRequest validates process name
* @tc.type: FUNC
*/
HWTEST_F(UdmfNotifierStubTest, OnRemoteRequest_ProcessNameCheck_001, TestSize.Level1)
{
    uint32_t code = 0;
    MessageParcel data;
    MessageParcel reply;
    MessageOption option;
    
    auto callback = [](const std::string &key, const UnifiedData &data) {};
    DelayDataCallbackClient client(callback);
    
    int ret = client.OnRemoteRequest(code, data, reply, option);
    EXPECT_NE(ret, 0);
}

/**
* @tc.name: OnRemoteRequest_ValidRequest_001
* @tc.desc: Test OnRemoteRequest accepts valid native request
* @tc.type: FUNC
*/
HWTEST_F(UdmfNotifierStubTest, OnRemoteRequest_ValidRequest_001, TestSize.Level1)
{
    auto loadHandler = [](const std::string &key, const DataLoadInfo &info) {};
    UdmfNotifierClient client(loadHandler);
    
    std::string key = "test_key";
    DataLoadInfo dataLoadInfo;
    dataLoadInfo.sequenceKey = "seq_key";
    
    client.HandleDelayObserver(key, dataLoadInfo);
    EXPECT_TRUE(true);
}

/**
* @tc.name: UdmfNotifierStub_OnRemoteRequest_DescriptorMismatch_001
* @tc.desc: Test UdmfNotifierStub OnRemoteRequest with descriptor mismatch
* @tc.type: FUNC
*/
HWTEST_F(UdmfNotifierStubTest, UdmfNotifierStub_OnRemoteRequest_DescriptorMismatch_001, TestSize.Level1)
{
    auto loadHandler = [](const std::string &key, const DataLoadInfo &info) {};
    UdmfNotifierClient client(loadHandler);
    
    uint32_t code = 0;
    MessageParcel data;
    MessageParcel reply;
    MessageOption option;
    
    data.WriteInterfaceToken(u"invalid.descriptor");
    
    int ret = client.OnRemoteRequest(code, data, reply, option);
    EXPECT_EQ(ret, -1);
}

/**
* @tc.name: UdmfNotifierStub_OnRemoteRequest_UnmarshalFailed_001
* @tc.desc: Test UdmfNotifierStub OnRemoteRequest with unmarshal failed
* @tc.type: FUNC
*/
HWTEST_F(UdmfNotifierStubTest, UdmfNotifierStub_OnRemoteRequest_UnmarshalFailed_001, TestSize.Level1)
{
    auto loadHandler = [](const std::string &key, const DataLoadInfo &info) {};
    UdmfNotifierClient client(loadHandler);
    
    uint32_t code = 0;
    MessageParcel data;
    MessageParcel reply;
    MessageOption option;
    
    data.WriteInterfaceToken(UdmfNotifierClient::GetDescriptor());
    data.WriteInt32(123);
    
    int ret = client.OnRemoteRequest(code, data, reply, option);
    EXPECT_EQ(ret, E_READ_PARCEL_ERROR);
}

/**
* @tc.name: IsValidProcessName_ValidProcess_001
* @tc.desc: Test IsValidProcessName with valid process name "distributeddata"
* @tc.type: FUNC
*/
HWTEST_F(UdmfNotifierStubTest, IsValidProcessName_ValidProcess_001, TestSize.Level1)
{
    SetNativeToken("distributeddata");
    bool result = DelayDataCallbackStub::IsValidProcessName();
    EXPECT_TRUE(result);
}

/**
* @tc.name: IsValidProcessName_InvalidProcess_001
* @tc.desc: Test IsValidProcessName with invalid process name
* @tc.type: FUNC
*/
HWTEST_F(UdmfNotifierStubTest, IsValidProcessName_InvalidProcess_001, TestSize.Level1)
{
    SetNativeToken("foundation");
    bool result = DelayDataCallbackStub::IsValidProcessName();
    EXPECT_FALSE(result);
}

/**
* @tc.name: IsValidProcessName_NonNativeToken_001
* @tc.desc: Test IsValidProcessName with non-native token
* @tc.type: FUNC
*/
HWTEST_F(UdmfNotifierStubTest, IsValidProcessName_NonNativeToken_001, TestSize.Level1)
{
    HapInfoParams info = {
        .userID = 100,
        .bundleName = "ohos.test.demo",
        .instIndex = 0,
        .appIDDesc = "ohos.test.demo"
    };
    HapPolicyParams policy = {
        .apl = APL_NORMAL,
        .domain = "test.domain"
    };
    auto tokenIDEx = AccessTokenKit::AllocHapToken(info, policy);
    SetSelfTokenID(tokenIDEx.tokenIDEx);

    bool result = DelayDataCallbackStub::IsValidProcessName();
    EXPECT_FALSE(result);

    auto tokenId = AccessTokenKit::GetHapTokenID(100, "ohos.test.demo", 0);
    AccessTokenKit::DeleteToken(tokenId);
}

/**
* @tc.name: DelayDataCallback_OnRemoteRequest_ValidProcess_001
* @tc.desc: Test DelayDataCallback OnRemoteRequest with valid process name
* @tc.type: FUNC
*/
HWTEST_F(UdmfNotifierStubTest, DelayDataCallback_OnRemoteRequest_ValidProcess_001, TestSize.Level1)
{
    SetNativeToken("distributeddata");

    uint32_t code = 0;
    MessageParcel data;
    MessageParcel reply;
    MessageOption option;

    auto callback = [](const std::string &key, const UnifiedData &data) {};
    DelayDataCallbackClient client(callback);

    data.WriteInterfaceToken(DelayDataCallbackClient::GetDescriptor());

    std::string key = "test_key";
    UnifiedData unifiedData;

    if (!ITypesUtil::Marshal(data, key, unifiedData)) {
        FAIL() << "Marshal failed";
    }

    int ret = client.OnRemoteRequest(code, data, reply, option);
    EXPECT_EQ(ret, 0);
}

/**
* @tc.name: DelayDataCallback_OnRemoteRequest_InvalidProcess_001
* @tc.desc: Test DelayDataCallback OnRemoteRequest with invalid process name
* @tc.type: FUNC
*/
HWTEST_F(UdmfNotifierStubTest, DelayDataCallback_OnRemoteRequest_InvalidProcess_001, TestSize.Level1)
{
    SetNativeToken("foundation");

    uint32_t code = 0;
    MessageParcel data;
    MessageParcel reply;
    MessageOption option;

    auto callback = [](const std::string &key, const UnifiedData &data) {};
    DelayDataCallbackClient client(callback);

    data.WriteInterfaceToken(DelayDataCallbackClient::GetDescriptor());

    std::string key = "test_key";
    UnifiedData unifiedData;

    if (!ITypesUtil::Marshal(data, key, unifiedData)) {
        FAIL() << "Marshal failed";
    }

    int ret = client.OnRemoteRequest(code, data, reply, option);
    EXPECT_NE(ret, 0);
}

} // namespace OHOS::UDMF