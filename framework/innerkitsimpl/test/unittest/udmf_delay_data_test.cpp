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
#define LOG_TAG "UdmfDelayDataTest"
#include <gtest/gtest.h>

#include "accesstoken_kit.h"
#include "nativetoken_kit.h"
#include "token_setproc.h"
#include "async_task_params.h"
#include "data_params_conversion.h"
#include "logger.h"
#include "plain_text.h"
#include "udmf.h"
#include "udmf_async_client.h"
#include "udmf_client.h"
#include "udmf_utils.h"

using namespace testing::ext;
using namespace OHOS::Security::AccessToken;
using namespace OHOS::UDMF;
using namespace OHOS;
namespace OHOS::Test {
static constexpr int USER_ID = 100;
static constexpr int END_INTERVAL = 3;
class UdmfDelayDataTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;

    static void AllocHapToken1();
    static void AllocHapToken2();
    static void SetHapToken1();
    static void SetHapToken2();
    static void AddPrivilege(QueryOption &option);
    static void SetNativeToken(const std::string &processName);
    static std::string SetDataInfoTest(const std::string &key);
    static void GetDelayDataTest(const std::string &key);
};

void UdmfDelayDataTest::SetUpTestCase()
{
    AllocHapToken1();
    AllocHapToken2();
}

void UdmfDelayDataTest::TearDownTestCase()
{
    std::this_thread::sleep_for(std::chrono::seconds(END_INTERVAL));
    std::vector<UnifiedData> unifiedDataSet;
    QueryOption query = {
        .intention = UDMF::UD_INTENTION_DATA_HUB
    };
    auto status = UdmfClient::GetInstance().DeleteData(query, unifiedDataSet);
    EXPECT_EQ(E_OK, status);

    auto tokenId = AccessTokenKit::GetHapTokenID(USER_ID, "ohos.test.demo1", 0);
    AccessTokenKit::DeleteToken(tokenId);
    auto tokenId2 = AccessTokenKit::GetHapTokenID(USER_ID, "ohos.test.demo2", 0);
    AccessTokenKit::DeleteToken(tokenId2);
}

void UdmfDelayDataTest::SetUp() {}

void UdmfDelayDataTest::TearDown()
{
    std::this_thread::sleep_for(std::chrono::seconds(END_INTERVAL));
}

void UdmfDelayDataTest::AllocHapToken1()
{
    HapInfoParams info = {
        .userID = USER_ID,
        .bundleName = "ohos.test.demo1",
        .instIndex = 0,
        .isSystemApp = false,
        .appIDDesc = "ohos.test.demo1"
    };
    HapPolicyParams policy = {
        .apl = APL_SYSTEM_BASIC,
        .domain = "test.domain",
        .permList = {
            {
                .permissionName = "ohos.permission.MANAGE_UDMF_APP_SHARE_OPTION",
                .bundleName = "ohos.test.demo1",
                .grantMode = 1,
                .availableLevel = APL_SYSTEM_BASIC,
                .label = "label",
                .labelId = 1,
                .description = "test2",
                .descriptionId = 1
            }
        },
        .permStateList = {
            {
                .permissionName = "ohos.permission.MANAGE_UDMF_APP_SHARE_OPTION",
                .isGeneral = true,
                .resDeviceID = { "local" },
                .grantStatus = { PermissionState::PERMISSION_GRANTED },
                .grantFlags = { 1 }
            }
        }
    };
    auto tokenID = AccessTokenKit::AllocHapToken(info, policy);
    SetSelfTokenID(tokenID.tokenIDEx);
}

void UdmfDelayDataTest::AllocHapToken2()
{
    HapInfoParams info = {
        .userID = USER_ID,
        .bundleName = "ohos.test.demo2",
        .instIndex = 0,
        .isSystemApp = false,
        .appIDDesc = "ohos.test.demo2"
    };

    HapPolicyParams policy = {
        .apl = APL_NORMAL,
        .domain = "test.domain",
        .permList = {
            {
                .permissionName = "ohos.permission.test",
                .bundleName = "ohos.test.demo2",
                .grantMode = 1,
                .availableLevel = APL_NORMAL,
                .label = "label",
                .labelId = 1,
                .description = "test2",
                .descriptionId = 1
            }
        },
        .permStateList = {
            {
                .permissionName = "ohos.permission.test",
                .isGeneral = true,
                .resDeviceID = { "local" },
                .grantStatus = { PermissionState::PERMISSION_GRANTED },
                .grantFlags = { 1 }
            }
        }
    };
    auto tokenID = AccessTokenKit::AllocHapToken(info, policy);
    SetSelfTokenID(tokenID.tokenIDEx);
}

void UdmfDelayDataTest::SetHapToken1()
{
    auto tokenId = AccessTokenKit::GetHapTokenID(USER_ID, "ohos.test.demo1", 0);
    SetSelfTokenID(tokenId);
}

void UdmfDelayDataTest::SetHapToken2()
{
    auto tokenId = AccessTokenKit::GetHapTokenID(USER_ID, "ohos.test.demo2", 0);
    SetSelfTokenID(tokenId);
}

void UdmfDelayDataTest::SetNativeToken(const std::string &processName)
{
    auto tokenId = AccessTokenKit::GetNativeTokenId(processName);
    SetSelfTokenID(tokenId);
}

void UdmfDelayDataTest::AddPrivilege(QueryOption &option)
{
    Privilege privilege;
    privilege.tokenId = AccessTokenKit::GetHapTokenID(USER_ID, "ohos.test.demo2", 0);
    privilege.readPermission = "readPermission";
    privilege.writePermission = "writePermission";
    SetNativeToken("msdp_sa");
    auto status = UdmfClient::GetInstance().AddPrivilege(option, privilege);
    ASSERT_EQ(status, E_OK);
}


/* *
 * @tc.name: UdmfDelayDataTest001
 * @tc.desc: Test get data success.
 * @tc.type: FUNC
 */
HWTEST_F(UdmfDelayDataTest, UdmfDelayDataTest001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "UdmfDelayDataTest001 begin.");

    DataLoadInfo dataLoadInfo1{
        .recordCount = 10,
        .types{"general.plain-text", "general.html"},
        .sequenceKey = UTILS::GenerateId()
    };
    DataLoadInfo dataLoadInfo2{
        .recordCount = 100,
        .types{"general.plain-text"},
    };

    SetHapToken1();
    auto loadHandler = [=] (const std::string &udKey, const DataLoadInfo &dataLoadInfo) {
        LOG_INFO(UDMF_TEST, "loadHandler begin udKey=%{public}s.", udKey.c_str());
        EXPECT_EQ(dataLoadInfo.recordCount, dataLoadInfo2.recordCount);
        EXPECT_EQ(dataLoadInfo.types, dataLoadInfo2.types);
        UnifiedData data;
        auto obj = std::make_shared<Object>();
        auto plainText = std::make_shared<PlainText>(UDType::PLAIN_TEXT, obj);
        plainText->SetContent("content1");
        data.AddRecord(plainText);
        auto ret = UdmfClient::GetInstance().PushDelayData(udKey, data);
        EXPECT_EQ(ret, E_OK);
    };
    DataLoadParams dataLoadParams = {
        .dataLoadInfo = dataLoadInfo1,
        .loadHandler = loadHandler
    };
    std::string key = "";
    auto status = UdmfClient::GetInstance().SetDelayInfo(dataLoadParams, key);
    EXPECT_EQ(status, E_OK);

    QueryOption option{
        .intention = UD_INTENTION_DRAG,
        .key = key
    };
    Summary summary;
    status = UdmfClient::GetInstance().GetSummary(option, summary);
    EXPECT_EQ(status, E_OK);
    EXPECT_EQ(summary.totalSize, dataLoadInfo1.recordCount);
    EXPECT_EQ(summary.summary.size(), dataLoadInfo1.types.size());
    for (auto item: summary.summary) {
        EXPECT_NE(summary.summary.find(item.first), summary.summary.end());
        EXPECT_EQ(item.second, 0);
    }

    QueryOption query = {
        .intention = UD_INTENTION_DRAG,
        .key = key
    };
    AddPrivilege(query);

    SetHapToken2();
    auto callback = [this](ProgressInfo progress, std::shared_ptr<UnifiedData> data) {
        LOG_INFO(UDMF_TEST, "Callback begin status=%{public}d, progress=%{public}d",
            progress.progressStatus, progress.progress);
        if (data == nullptr) {
            ASSERT_TRUE(progress.progress != 0);
            return;
        }
        ASSERT_EQ(1, data->GetRecords().size());
        LOG_INFO(UDMF_TEST, "UdmfDelayDataTest001 callback end.");
    };
    GetDataParams params{
        .query = query,
        .progressIndicator = ProgressIndicator::DEFAULT,
        .progressListener = callback,
        .acceptableInfo = dataLoadInfo2,
    };
    status = UdmfAsyncClient::GetInstance().StartAsyncDataRetrieval(params);
    EXPECT_EQ(status, E_OK);

    LOG_INFO(UDMF_TEST, "UdmfDelayDataTest001 end.");
}

/* *
 * @tc.name: UdmfDelayDataTest002
 * @tc.desc: Test after waiting for 500ms, get data success.
 * @tc.type: FUNC
 */
HWTEST_F(UdmfDelayDataTest, UdmfDelayDataTest002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "UdmfDelayDataTest002 begin.");

    DataLoadInfo dataLoadInfo1{
        .recordCount = 10,
        .types{"general.plain-text", "general.html"},
        .sequenceKey = UTILS::GenerateId()
    };
    DataLoadInfo dataLoadInfo2{
        .recordCount = 100,
        .types{"general.plain-text"},
    };

    SetHapToken1();
    auto loadHandler = [=] (const std::string &udKey, const DataLoadInfo &dataLoadInfo) {
        LOG_INFO(UDMF_TEST, "loadHandler begin udKey=%{public}s.", udKey.c_str());
        EXPECT_EQ(dataLoadInfo.recordCount, dataLoadInfo2.recordCount);
        EXPECT_EQ(dataLoadInfo.types, dataLoadInfo2.types);
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        UnifiedData data;
        auto obj = std::make_shared<Object>();
        auto plainText = std::make_shared<PlainText>(UDType::PLAIN_TEXT, obj);
        plainText->SetContent("content1");
        data.AddRecord(plainText);
        auto ret = UdmfClient::GetInstance().PushDelayData(udKey, data);
        EXPECT_EQ(ret, E_OK);
    };
    DataLoadParams dataLoadParams = {
        .dataLoadInfo = dataLoadInfo1,
        .loadHandler = loadHandler
    };
    std::string key = "";
    auto status = UdmfClient::GetInstance().SetDelayInfo(dataLoadParams, key);
    EXPECT_EQ(status, E_OK);

    QueryOption option{
        .intention = UD_INTENTION_DRAG,
        .key = key
    };
    Summary summary;
    status = UdmfClient::GetInstance().GetSummary(option, summary);
    EXPECT_EQ(status, E_OK);
    EXPECT_EQ(summary.totalSize, dataLoadInfo1.recordCount);
    EXPECT_EQ(summary.summary.size(), dataLoadInfo1.types.size());
    for (auto item: summary.summary) {
        EXPECT_NE(summary.summary.find(item.first), summary.summary.end());
        EXPECT_EQ(item.second, 0);
    }

    QueryOption query = {
        .intention = UD_INTENTION_DRAG,
        .key = key
    };
    AddPrivilege(query);

    SetHapToken2();
    auto callback = [this](ProgressInfo progress, std::shared_ptr<UnifiedData> data) {
        LOG_INFO(UDMF_TEST, "Callback begin status=%{public}d, progress=%{public}d",
            progress.progressStatus, progress.progress);
        if (data == nullptr) {
            ASSERT_TRUE(progress.progress != 0);
            return;
        }
        ASSERT_EQ(1, data->GetRecords().size());
        LOG_INFO(UDMF_TEST, "UdmfDelayDataTest002 callback end.");
    };
    GetDataParams params{
        .query = query,
        .progressIndicator = ProgressIndicator::DEFAULT,
        .progressListener = callback,
        .acceptableInfo = dataLoadInfo2,
    };
    status = UdmfAsyncClient::GetInstance().StartAsyncDataRetrieval(params);
    EXPECT_EQ(status, E_OK);

    LOG_INFO(UDMF_TEST, "UdmfDelayDataTest002 end.");
}

/* *
 * @tc.name: UdmfDelayDataTest003
 * @tc.desc: Test invalid parameters
 * @tc.type: FUNC
 */
HWTEST_F(UdmfDelayDataTest, UdmfDelayDataTest003, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "UdmfDelayDataTest003 begin.");

    DataLoadInfo dataLoadInfo1{
        .recordCount = 10,
        .types{"general.plain-text", "general.html"},
    };

    SetHapToken1();
    auto loadHandler = [=] (const std::string &udKey, const DataLoadInfo &dataLoadInfo) {
        LOG_INFO(UDMF_TEST, "loadHandler begin udKey=%{public}s.", udKey.c_str());
    };
    DataLoadParams dataLoadParams = {
        .dataLoadInfo = dataLoadInfo1,
        .loadHandler = loadHandler
    };
    std::string key = "";
    auto status = UdmfClient::GetInstance().SetDelayInfo(dataLoadParams, key);
    EXPECT_EQ(status, E_INVALID_PARAMETERS);
    LOG_INFO(UDMF_TEST, "UdmfDelayDataTest003 end.");
}

/* *
 * @tc.name: UdmfDelayDataTest004
 * @tc.desc: Test invalid parameters
 * @tc.type: FUNC
 */
HWTEST_F(UdmfDelayDataTest, UdmfDelayDataTest004, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "UdmfDelayDataTest004 begin.");
    SetHapToken1();
    UnifiedData data;
    auto obj = std::make_shared<Object>();
    auto plainText = std::make_shared<PlainText>(UDType::PLAIN_TEXT, obj);
    plainText->SetContent("content1");
    data.AddRecord(plainText);
    std::string udKey = "";
    auto ret = UdmfClient::GetInstance().PushDelayData(udKey, data);
    EXPECT_EQ(ret, E_INVALID_PARAMETERS);
    LOG_INFO(UDMF_TEST, "UdmfDelayDataTest004 end.");
}

std::string UdmfDelayDataTest::SetDataInfoTest(const std::string &key)
{
    DataLoadInfo dataLoadInfo1{
        .recordCount = 10,
        .types{"general.plain-text", "general.html"},
        .sequenceKey = key
    };
    DataLoadInfo dataLoadInfo2{
        .recordCount = 100,
        .types{"general.plain-text"},
    };
    auto loadHandler = [=] (const std::string &udKey, const DataLoadInfo &dataLoadInfo) {
        LOG_INFO(UDMF_TEST, "loadHandler begin udKey=%{public}s.", udKey.c_str());
        EXPECT_EQ(dataLoadInfo.recordCount, dataLoadInfo2.recordCount);
        EXPECT_EQ(dataLoadInfo.types, dataLoadInfo2.types);
        UnifiedData data;
        auto obj = std::make_shared<Object>();
        auto plainText = std::make_shared<PlainText>(UDType::PLAIN_TEXT, obj);
        plainText->SetContent("content1");
        data.AddRecord(plainText);
        auto ret = UdmfClient::GetInstance().PushDelayData(udKey, data);
        EXPECT_EQ(ret, E_OK);
    };
    DataLoadParams dataLoadParams = {
        .dataLoadInfo = dataLoadInfo1,
        .loadHandler = loadHandler
    };
    std::string udkey = "";
    auto status = UdmfClient::GetInstance().SetDelayInfo(dataLoadParams, udkey);
    EXPECT_EQ(status, E_OK);
    return udkey;
}

void UdmfDelayDataTest::GetDelayDataTest(const std::string &key)
{
    DataLoadInfo dataLoadInfo2{
        .recordCount = 100,
        .types{"general.plain-text"},
    };
    auto callback = [](ProgressInfo progress, std::shared_ptr<UnifiedData> data) {
        LOG_INFO(UDMF_TEST, "Callback begin status=%{public}d, progress=%{public}d",
            progress.progressStatus, progress.progress);
        if (data == nullptr) {
            ASSERT_TRUE(progress.progress != 0);
            return;
        }
        ASSERT_EQ(1, data->GetRecords().size());
        LOG_INFO(UDMF_TEST, "UdmfDelayDataTest002 callback end.");
    };
    QueryOption query = {
        .intention = UD_INTENTION_DRAG,
        .key = key
    };
    GetDataParams params{
        .query = query,
        .progressIndicator = ProgressIndicator::NONE,
        .progressListener = callback,
        .acceptableInfo = dataLoadInfo2,
    };
    auto status = UdmfAsyncClient::GetInstance().StartAsyncDataRetrieval(params);
    EXPECT_EQ(status, E_OK);
}

/* *
 * @tc.name: UdmfDelayDataTest005
 * @tc.desc: Test multi thread delay data
 * @tc.type: FUNC
 */
HWTEST_F(UdmfDelayDataTest, UdmfDelayDataTest005, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "UdmfDelayDataTest005 begin.");
    SetHapToken1();
    std::string key1 = UTILS::GenerateId();
    std::string key2 = UTILS::GenerateId();
    std::string key3 = UTILS::GenerateId();

    std::thread t1([&]() {
        key1 = SetDataInfoTest(key1);
        GetDelayDataTest(key1);
    });
    std::thread t2([&]() {
        key2 = SetDataInfoTest(key2);
        GetDelayDataTest(key2);
    });
    std::thread t3([&]() {
        key3 = SetDataInfoTest(key3);
        GetDelayDataTest(key3);
    });
    EXPECT_NO_FATAL_FAILURE(t1.join());
    EXPECT_NO_FATAL_FAILURE(t2.join());
    EXPECT_NO_FATAL_FAILURE(t3.join());
    
    LOG_INFO(UDMF_TEST, "UdmfDelayDataTest005 end.");
}
} // OHOS::Test