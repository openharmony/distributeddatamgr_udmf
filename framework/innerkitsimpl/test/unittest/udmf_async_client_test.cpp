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
#define LOG_TAG "UdmfAsyncClientTest"
#include <gtest/gtest.h>

#include "token_setproc.h"
#include "accesstoken_kit.h"
#include "nativetoken_kit.h"

#include "image.h"
#include "logger.h"
#include "plain_text.h"
#include "udmf.h"
#include "udmf_async_client.h"
#include "udmf_client.h"
#include "udmf_executor.h"
#include "async_task_params.h"
#include "data_params_conversion.h"

using namespace testing::ext;
using namespace OHOS::Security::AccessToken;
using namespace OHOS::UDMF;
using namespace OHOS;
namespace OHOS::Test {
static constexpr int USER_ID = 100;
static constexpr int END_INTERVAL = 2;
class UdmfAsyncClientTest : public testing::Test {
public:
    Status SetDataTest(std::string key, ProgressIndicator progressIndicator);

    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;

    static void AllocHapToken();
};

void UdmfAsyncClientTest::SetUpTestCase()
{
    AllocHapToken();
}

void UdmfAsyncClientTest::TearDownTestCase()
{
    std::this_thread::sleep_for(std::chrono::seconds(END_INTERVAL));
    std::vector<UnifiedData> unifiedDataSet;
    QueryOption query = {
        .intention = UDMF::UD_INTENTION_DATA_HUB
    };
    auto status = UdmfClient::GetInstance().DeleteData(query, unifiedDataSet);
    EXPECT_EQ(E_OK, status);
    auto tokenId = AccessTokenKit::GetHapTokenID(USER_ID, "ohos.test.asyncdemo", 0);
    AccessTokenKit::DeleteToken(tokenId);
}

void UdmfAsyncClientTest::SetUp() {}

void UdmfAsyncClientTest::TearDown() {}


void UdmfAsyncClientTest::AllocHapToken()
{
    HapInfoParams info = {
        .userID = USER_ID,
        .bundleName = "ohos.test.asyncdemo",
        .instIndex = 0,
        .isSystemApp = false,
        .appIDDesc = "ohos.test.asyncdemo"
    };
    HapPolicyParams policy = {
        .apl = APL_SYSTEM_BASIC,
        .domain = "test.domain",
        .permList = {
            {
                .permissionName = "ohos.permission.MANAGE_UDMF_APP_SHARE_OPTION",
                .bundleName = "ohos.test.asyncdemo",
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

/* *
 * @tc.name: StartAsyncDataRetrieval001
 * @tc.desc: Test get data success.
 * @tc.type: FUNC
 */
HWTEST_F(UdmfAsyncClientTest, StartAsyncDataRetrieval001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "StartAsyncDataRetrieval001 begin.");

    CustomOption customOption = {
        .intention = UDMF::UD_INTENTION_DRAG
    };
    UnifiedData data;
    auto obj = std::make_shared<Object>();
    auto plainText = std::make_shared<PlainText>(UDType::PLAIN_TEXT, obj);
    plainText->SetContent("content1");
    data.AddRecord(plainText);
    std::string key;
    auto status = UdmfClient::GetInstance().SetData(customOption, data, key);
    ASSERT_EQ(E_OK, status);

    GetDataParams params;
    QueryOption query = {
        .intention = UD_INTENTION_DRAG,
        .key = key
    };
    auto callback = [this](ProgressInfo progress, std::shared_ptr<UnifiedData> data) {
        LOG_INFO(UDMF_TEST, "Callback begin status=%{public}d, progress=%{public}d, name=%{public}s.",
            progress.progressStatus, progress.progress, progress.srcDevName.c_str());
        if (data == nullptr) {
            ASSERT_TRUE(progress.progress != 0);
            return;
        }
        ASSERT_EQ(1, data->GetRecords().size());
        LOG_INFO(UDMF_TEST, "StartAsyncDataRetrieval001 callback end.");
    };
    params.query = query;
    params.progressIndicator = ProgressIndicator::NONE;
    params.progressListener = callback;
    status = UdmfAsyncClient::GetInstance().StartAsyncDataRetrieval(params);
    ASSERT_EQ(E_OK, status);
    LOG_INFO(UDMF_TEST, "StartAsyncDataRetrieval001 end.");
}

/* *
 * @tc.name: StartAsyncDataRetrieval002
 * @tc.desc: Test CAPI get data success.
 * @tc.type: FUNC
 */
HWTEST_F(UdmfAsyncClientTest, StartAsyncDataRetrieval002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "StartAsyncDataRetrieval002 begin.");

    CustomOption customOption = {
        .intention = UDMF::UD_INTENTION_DRAG
    };
    UnifiedData data;
    auto obj = std::make_shared<Object>();
    auto plainText = std::make_shared<PlainText>(UDType::PLAIN_TEXT, obj);
    plainText->SetContent("content1");
    data.AddRecord(plainText);
    std::string key;
    auto status = UdmfClient::GetInstance().SetData(customOption, data, key);
    ASSERT_EQ(E_OK, status);

    OH_UdmfGetDataParams param;
    OH_UdmfGetDataParams_SetProgressIndicator(&param, Udmf_ProgressIndicator::UDMF_DEFAULT);
    OH_UdmfGetDataParams_SetDestUri(&param, "/test/demo");
    OH_UdmfGetDataParams_SetFileConflictOptions(&param, Udmf_FileConflictOptions::UDMF_SKIP);
    OH_Udmf_DataProgressListener dataProgressListener = [](OH_Udmf_ProgressInfo *progressInfo, OH_UdmfData *data) {
        auto progress = OH_UdmfProgressInfo_GetProgress(progressInfo);
        auto status = OH_UdmfProgressInfo_GetStatus(progressInfo);
        LOG_INFO(UDMF_TEST, "Callback begin status=%{public}d, progress=%{public}d.", status, progress);
        if (data == nullptr) {
            ASSERT_TRUE(progress != 0);
            return;
        }
        unsigned int count = 0;
        OH_UdmfData_GetRecords(data, &count);
        ASSERT_EQ(1, count);
        LOG_INFO(UDMF_TEST, "StartAsyncDataRetrieval002 callback end.");
    };
    OH_UdmfGetDataParams_SetDataProgressListener(&param, dataProgressListener);
    QueryOption query = {
        .intention = UD_INTENTION_DRAG,
        .key = key
    };
    GetDataParams dataParams;
    status = DataParamsConversion::GetInnerDataParams(param, query, dataParams);
    ASSERT_EQ(E_OK, status);
    status = UdmfAsyncClient::GetInstance().StartAsyncDataRetrieval(dataParams);
    ASSERT_EQ(E_OK, status);
    LOG_INFO(UDMF_TEST, "StartAsyncDataRetrieval002 end.");
}

/* *
 * @tc.name: StartAsyncDataRetrieval003
 * @tc.desc: Test get cache data success.
 * @tc.type: FUNC
 */
HWTEST_F(UdmfAsyncClientTest, StartAsyncDataRetrieval003, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "StartAsyncDataRetrieval003 begin.");
    auto status = UdmfClient::GetInstance().SetAppShareOption("drag", ShareOptions::IN_APP);
    ASSERT_EQ(E_OK, status);

    CustomOption customOption = {
        .intention = UDMF::UD_INTENTION_DRAG
    };
    UnifiedData data;
    auto obj = std::make_shared<Object>();
    auto plainText = std::make_shared<PlainText>(UDType::PLAIN_TEXT, obj);
    plainText->SetContent("content1");
    data.AddRecord(plainText);
    std::string key;
    status = UdmfClient::GetInstance().SetData(customOption, data, key);
    ASSERT_EQ(E_OK, status);

    GetDataParams params;
    QueryOption query = {
        .intention = UD_INTENTION_DRAG,
        .key = key
    };
    auto callback = [this](ProgressInfo progress, std::shared_ptr<UnifiedData> data) {
        LOG_INFO(UDMF_TEST, "Callback begin status=%{public}d, progress=%{public}d, name=%{public}s.",
            progress.progressStatus, progress.progress, progress.srcDevName.c_str());
        if (data == nullptr) {
            ASSERT_TRUE(progress.progress != 0);
            return;
        }
        ASSERT_EQ(1, data->GetRecords().size());
        LOG_INFO(UDMF_TEST, "StartAsyncDataRetrieval003 callback end.");
    };
    params.query = query;
    params.progressIndicator = ProgressIndicator::DEFAULT;
    params.progressListener = callback;
    status = UdmfAsyncClient::GetInstance().StartAsyncDataRetrieval(params);
    ASSERT_EQ(E_OK, status);

    status = UdmfClient::GetInstance().RemoveAppShareOption("drag");
    ASSERT_EQ(E_OK, status);
    LOG_INFO(UDMF_TEST, "StartAsyncDataRetrieval003 end.");
}

/* *
 * @tc.name: StartAsyncDataRetrieval004
 * @tc.desc: Test get data cost 1s.
 * @tc.type: FUNC
 */
HWTEST_F(UdmfAsyncClientTest, StartAsyncDataRetrieval004, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "StartAsyncDataRetrieval004 begin.");

    CustomOption customOption = {
        .intention = UDMF::UD_INTENTION_DRAG
    };
    UnifiedData data;
    auto obj = std::make_shared<Object>();
    auto plainText = std::make_shared<PlainText>(UDType::PLAIN_TEXT, obj);
    plainText->SetContent("content1");
    data.AddRecord(plainText);
    std::string key;
    auto status = UdmfClient::GetInstance().SetData(customOption, data, key);
    ASSERT_EQ(E_OK, status);

    GetDataParams params;
    QueryOption query = {
        .intention = UD_INTENTION_DRAG,
        .key = key
    };
    auto callback = [this](ProgressInfo progress, std::shared_ptr<UnifiedData> data) {
        LOG_INFO(UDMF_TEST, "Callback begin status=%{public}d, progress=%{public}d, name=%{public}s.",
            progress.progressStatus, progress.progress, progress.srcDevName.c_str());
        if (data == nullptr) {
            ASSERT_TRUE(progress.progress != 0);
            return;
        }
        ASSERT_EQ(1, data->GetRecords().size());
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
        LOG_INFO(UDMF_TEST, "StartAsyncDataRetrieval003 callback end.");
    };
    params.query = query;
    params.progressIndicator = ProgressIndicator::NONE;
    params.progressListener = callback;
    status = UdmfAsyncClient::GetInstance().StartAsyncDataRetrieval(params);
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    ASSERT_EQ(E_OK, status);

    LOG_INFO(UDMF_TEST, "StartAsyncDataRetrieval004 end.");
}

/* *
 * @tc.name: StartAsyncDataRetrieval005
 * @tc.desc: Test get no data.
 * @tc.type: FUNC
 */
HWTEST_F(UdmfAsyncClientTest, StartAsyncDataRetrieval005, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "StartAsyncDataRetrieval005 begin.");

    GetDataParams params;
    QueryOption query = {
        .intention = UD_INTENTION_DRAG,
        .key = "udmf://drag/com.demo/NotFoundData"
    };
    auto callback = [this](ProgressInfo progress, std::shared_ptr<UnifiedData> data) {
        LOG_INFO(UDMF_TEST, "Callback begin status=%{public}d, progress=%{public}d, name=%{public}s.",
            progress.progressStatus, progress.progress, progress.srcDevName.c_str());
        if (progress.progressStatus == 4) {
            LOG_INFO(UDMF_TEST, "StartAsyncDataRetrieval005 demo1 callback end.");
            return;
        }
    };
    params.query = query;
    params.progressIndicator = ProgressIndicator::NONE;
    params.progressListener = callback;
    auto status = UdmfAsyncClient::GetInstance().StartAsyncDataRetrieval(params);
    ASSERT_EQ(E_OK, status);
    LOG_INFO(UDMF_TEST, "StartAsyncDataRetrieval005 end.");
}

/* *
 * @tc.name: StartAsyncDataRetrieval006
 * @tc.desc: Test invalid key.
 * @tc.type: FUNC
 */
HWTEST_F(UdmfAsyncClientTest, StartAsyncDataRetrieval006, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "StartAsyncDataRetrieval006 begin.");

    GetDataParams params;
    QueryOption query = {
        .intention = UD_INTENTION_DRAG,
        .key = "InvalidKey"
    };
    auto callback = [this](ProgressInfo progress, std::shared_ptr<UnifiedData> data) {
        LOG_INFO(UDMF_TEST, "Callback begin status=%{public}d, progress=%{public}d, name=%{public}s.",
            progress.progressStatus, progress.progress, progress.srcDevName.c_str());
        if (progress.progressStatus == 3) {
            LOG_INFO(UDMF_TEST, "StartAsyncDataRetrieval006 demo2 callback end.");
            return;
        }
    };
    params.query = query;
    params.progressIndicator = ProgressIndicator::DEFAULT;
    params.progressListener = callback;
    auto status = UdmfAsyncClient::GetInstance().StartAsyncDataRetrieval(params);
    ASSERT_EQ(E_OK, status);
    LOG_INFO(UDMF_TEST, "StartAsyncDataRetrieval006 end.");
}

Status UdmfAsyncClientTest::SetDataTest(std::string key, ProgressIndicator progressIndicator)
{
    GetDataParams params;
    QueryOption query = {
        .intention = UD_INTENTION_DRAG,
        .key = key
    };
    auto callback = [this](ProgressInfo progress, std::shared_ptr<UnifiedData> data) {
        LOG_INFO(UDMF_TEST, "Callback begin status=%{public}d, progress=%{public}d, name=%{public}s.",
            progress.progressStatus, progress.progress, progress.srcDevName.c_str());
        if (data == nullptr) {
            ASSERT_TRUE(progress.progress != 0);
            return;
        }
    };
    params.query = query;
    params.progressIndicator = progressIndicator;
    params.progressListener = callback;
    return UdmfAsyncClient::GetInstance().StartAsyncDataRetrieval(params);
}

/* *
 * @tc.name: StartAsyncDataRetrieval007
 * @tc.desc: Test multithreading different key.
 * @tc.type: FUNC
 */
HWTEST_F(UdmfAsyncClientTest, StartAsyncDataRetrieval007, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "StartAsyncDataRetrieval007 begin.");

    CustomOption customOption = {
        .intention = UDMF::UD_INTENTION_DRAG
    };
    UnifiedData data;
    auto obj = std::make_shared<Object>();
    auto plainText = std::make_shared<PlainText>(UDType::PLAIN_TEXT, obj);
    plainText->SetContent("content1");
    data.AddRecord(plainText);
    std::string key1;
    auto status = UdmfClient::GetInstance().SetData(customOption, data, key1);
    ASSERT_EQ(E_OK, status);

    std::string key2;
    customOption = {
        .intention = UDMF::UD_INTENTION_DRAG
    };
    plainText = std::make_shared<PlainText>(UDType::PLAIN_TEXT, obj);
    plainText->SetContent("content1");
    data.AddRecord(plainText);
    status = UdmfClient::GetInstance().SetData(customOption, data, key2);
    ASSERT_EQ(E_OK, status);

    std::string key3;
    customOption = {
        .intention = UDMF::UD_INTENTION_DRAG
    };
    plainText = std::make_shared<PlainText>(UDType::PLAIN_TEXT, obj);
    plainText->SetContent("content1");
    data.AddRecord(plainText);
    status = UdmfClient::GetInstance().SetData(customOption, data, key3);
    ASSERT_EQ(E_OK, status);

    std::thread t1([&]() {
        auto status = SetDataTest(key1, ProgressIndicator::DEFAULT);
        ASSERT_EQ(E_OK, status);
    });
    EXPECT_NO_FATAL_FAILURE(t1.join());
    std::thread t2([&]() {
        auto status = SetDataTest(key2, ProgressIndicator::NONE);
        ASSERT_EQ(E_OK, status);
    });
    EXPECT_NO_FATAL_FAILURE(t2.join());
    std::thread t3([&]() {
        auto status = SetDataTest(key3, ProgressIndicator::DEFAULT);
        ASSERT_EQ(E_OK, status);
    });
    EXPECT_NO_FATAL_FAILURE(t3.join());
    LOG_INFO(UDMF_TEST, "StartAsyncDataRetrieval007 end.");
}

/* *
 * @tc.name: StartAsyncDataRetrieval008
 * @tc.desc: Test multithreading same key.
 * @tc.type: FUNC
 */
HWTEST_F(UdmfAsyncClientTest, StartAsyncDataRetrieval008, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "StartAsyncDataRetrieval008 begin.");

    CustomOption customOption = {
        .intention = UDMF::UD_INTENTION_DRAG
    };
    UnifiedData data;
    auto obj = std::make_shared<Object>();
    auto plainText = std::make_shared<PlainText>(UDType::PLAIN_TEXT, obj);
    plainText->SetContent("content1");
    data.AddRecord(plainText);
    std::string key1;
    auto status = UdmfClient::GetInstance().SetData(customOption, data, key1);
    ASSERT_EQ(E_OK, status);

    std::thread t1([&]() {
        auto status = SetDataTest(key1, ProgressIndicator::DEFAULT);
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        ASSERT_EQ(E_OK, status);
    });
    EXPECT_NO_FATAL_FAILURE(t1.join());
    std::thread t2([&]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        auto status = SetDataTest(key1, ProgressIndicator::NONE);
        ASSERT_EQ(E_IDEMPOTENT_ERROR, status);
    });
    EXPECT_NO_FATAL_FAILURE(t2.join());
    std::thread t3([&]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        auto status = SetDataTest(key1, ProgressIndicator::DEFAULT);
        ASSERT_EQ(E_IDEMPOTENT_ERROR, status);
    });
    EXPECT_NO_FATAL_FAILURE(t3.join());
    LOG_INFO(UDMF_TEST, "StartAsyncDataRetrieval008 end.");
}

/* *
 * @tc.name: StartAsyncDataRetrieval009
 * @tc.desc: Test Get File type.
 * @tc.type: FUNC
 */
HWTEST_F(UdmfAsyncClientTest, StartAsyncDataRetrieval009, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "StartAsyncDataRetrieval009 begin.");

    CustomOption customOption = {
        .intention = UDMF::UD_INTENTION_DRAG
    };
    UnifiedData data;
    auto obj = std::make_shared<Object>();
    auto file = std::make_shared<Image>(UDType::IMAGE, obj);
    file->SetUri("uri");
    file->SetRemoteUri("remoteUri");
    data.AddRecord(file);
    std::string key;
    auto status = UdmfClient::GetInstance().SetData(customOption, data, key);
    ASSERT_EQ(E_OK, status);

    GetDataParams params;
    QueryOption query = {
        .intention = UD_INTENTION_DRAG,
        .key = key
    };
    auto callback = [this](ProgressInfo progress, std::shared_ptr<UnifiedData> data) {
        LOG_INFO(UDMF_TEST, "Callback begin status=%{public}d, progress=%{public}d, name=%{public}s.",
            progress.progressStatus, progress.progress, progress.srcDevName.c_str());
        if (data == nullptr) {
            ASSERT_TRUE(progress.progress != 0);
            return;
        }
        ASSERT_EQ(1, data->GetRecords().size());
        LOG_INFO(UDMF_TEST, "StartAsyncDataRetrieval009 callback end.");
    };
    params.query = query;
    params.progressIndicator = ProgressIndicator::DEFAULT;
    params.progressListener = callback;
    status = UdmfAsyncClient::GetInstance().StartAsyncDataRetrieval(params);
    ASSERT_EQ(E_OK, status);
    LOG_INFO(UDMF_TEST, "StartAsyncDataRetrieval009 end.");
}

/* *
 * @tc.name: StartAsyncDataRetrieval010
 * @tc.desc: Test Invalid params.
 * @tc.type: FUNC
 */
HWTEST_F(UdmfAsyncClientTest, StartAsyncDataRetrieval010, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "StartAsyncDataRetrieval010 begin.");

    GetDataParams params;
    QueryOption query = {
        .intention = UDMF::UD_INTENTION_DRAG
    };
    params.query = query;
    params.progressIndicator = ProgressIndicator::DEFAULT;
    auto callback = [this](ProgressInfo progress, std::shared_ptr<UnifiedData> data) {};
    params.progressListener = callback;
    auto status = UdmfAsyncClient::GetInstance().StartAsyncDataRetrieval(params);
    ASSERT_EQ(E_INVALID_PARAMETERS, status);

    query = {
        .intention = UDMF::UD_INTENTION_DATA_HUB,
        .key = "udmf://a/b/c"
    };
    params.query = query;
    params.progressIndicator = ProgressIndicator::DEFAULT;
    params.progressListener = callback;
    status = UdmfAsyncClient::GetInstance().StartAsyncDataRetrieval(params);
    ASSERT_EQ(E_INVALID_PARAMETERS, status);

    query = {
        .intention = UDMF::UD_INTENTION_DRAG,
        .key = "udmf://a/b/c"
    };
    params.query = query;
    params.progressIndicator = ProgressIndicator::DEFAULT;
    params.progressListener = nullptr;
    status = UdmfAsyncClient::GetInstance().StartAsyncDataRetrieval(params);
    ASSERT_EQ(E_INVALID_PARAMETERS, status);
    LOG_INFO(UDMF_TEST, "StartAsyncDataRetrieval010 end.");
}

/**
 * @tc.name: Cancel001
 * @tc.desc: Test Normal Cancel
 * @tc.type: FUNC
 */
HWTEST_F(UdmfAsyncClientTest, Cancel001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "Cancel001 begin.");
    CustomOption customOption = {
        .intention = UDMF::UD_INTENTION_DRAG
    };
    UnifiedData data;
    auto obj = std::make_shared<Object>();
    auto file = std::make_shared<Image>(UDType::IMAGE, obj);
    file->SetUri("uri");
    file->SetRemoteUri("remoteUri");
    data.AddRecord(file);
    std::string key;
    auto status = UdmfClient::GetInstance().SetData(customOption, data, key);
    ASSERT_EQ(E_OK, status);

    GetDataParams params;
    QueryOption query = {
        .intention = UD_INTENTION_DRAG,
        .key = key
    };
    auto callback = [this](ProgressInfo progress, std::shared_ptr<UnifiedData> data) {
        LOG_INFO(UDMF_TEST, "Callback begin status=%{public}d, progress=%{public}d, name=%{public}s.",
            progress.progressStatus, progress.progress, progress.srcDevName.c_str());
        if (data == nullptr) {
            ASSERT_TRUE(progress.progress != 0);
            return;
        }
        ASSERT_EQ(1, data->GetRecords().size());
        LOG_INFO(UDMF_TEST, "StartAsyncDataRetrieval009 callback end.");
    };
    params.query = query;
    params.progressIndicator = ProgressIndicator::DEFAULT;
    params.progressListener = callback;
    status = UdmfAsyncClient::GetInstance().StartAsyncDataRetrieval(params);
    ASSERT_EQ(E_OK, status);
    std::string businessUdKey = "udmf://a/b/c";
    status = UdmfAsyncClient::GetInstance().Cancel(params.query.key);
    ASSERT_EQ(E_OK, status);

    LOG_INFO(UDMF_TEST, "Cancel001 end.");
}

/**
 * @tc.name: Cancel002
 * @tc.desc: Test Invalid params.
 * @tc.type: FUNC
 */
HWTEST_F(UdmfAsyncClientTest, Cancel002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "Cancel002 begin.");
    CustomOption customOption = {
        .intention = UDMF::UD_INTENTION_DRAG
    };
    UnifiedData data;
    auto obj = std::make_shared<Object>();
    auto file = std::make_shared<Image>(UDType::IMAGE, obj);
    file->SetUri("uri");
    file->SetRemoteUri("remoteUri");
    data.AddRecord(file);
    std::string key;
    auto status = UdmfClient::GetInstance().SetData(customOption, data, key);
    ASSERT_EQ(E_OK, status);

    GetDataParams params;
    QueryOption query = {
        .intention = UD_INTENTION_DRAG,
        .key = key
    };
    auto callback = [this](ProgressInfo progress, std::shared_ptr<UnifiedData> data) {
        LOG_INFO(UDMF_TEST, "Callback begin status=%{public}d, progress=%{public}d, name=%{public}s.",
            progress.progressStatus, progress.progress, progress.srcDevName.c_str());
        if (data == nullptr) {
            ASSERT_TRUE(progress.progress != 0);
            return;
        }
        ASSERT_EQ(1, data->GetRecords().size());
        LOG_INFO(UDMF_TEST, "Cancel002 callback end.");
    };
    params.query = query;
    params.progressIndicator = ProgressIndicator::DEFAULT;
    params.progressListener = callback;
    status = UdmfAsyncClient::GetInstance().StartAsyncDataRetrieval(params);
    ASSERT_EQ(E_OK, status);
    std::string businessUdKey = "udmf";
    status = UdmfAsyncClient::GetInstance().Cancel(businessUdKey);
    ASSERT_EQ(E_ERROR, status);

    LOG_INFO(UDMF_TEST, "Cancel002 end.");
}

/* *
 * @tc.name: CancelOnSingleTask001
 * @tc.desc: Test one data
 * @tc.type: FUNC
 */
HWTEST_F(UdmfAsyncClientTest, CancelOnSingleTask001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "CancelOnSingleTask001 begin.");
    CustomOption customOption = {
        .intention = UDMF::UD_INTENTION_DRAG
    };
    UnifiedData data;
    auto obj = std::make_shared<Object>();
    auto file = std::make_shared<Image>(UDType::IMAGE, obj);
    file->SetUri("uri");
    file->SetRemoteUri("remoteUri");
    data.AddRecord(file);
    std::string key;
    auto status = UdmfClient::GetInstance().SetData(customOption, data, key);
    ASSERT_EQ(E_OK, status);

    GetDataParams params;
    QueryOption query = {
        .intention = UD_INTENTION_DRAG,
        .key = key
    };
    auto callback = [this](ProgressInfo progress, std::shared_ptr<UnifiedData> data) {
        LOG_INFO(UDMF_TEST, "Callback begin status=%{public}d, progress=%{public}d, name=%{public}s.",
            progress.progressStatus, progress.progress, progress.srcDevName.c_str());
        if (data == nullptr) {
            ASSERT_TRUE(progress.progress != 0);
            return;
        }
        ASSERT_EQ(1, data->GetRecords().size());
        LOG_INFO(UDMF_TEST, "CancelOnSingleTask001 callback end.");
    };
    params.query = query;
    params.progressIndicator = ProgressIndicator::DEFAULT;
    params.progressListener = callback;
    status = UdmfAsyncClient::GetInstance().StartAsyncDataRetrieval(params);
    ASSERT_EQ(E_OK, status);
    status = UdmfAsyncClient::GetInstance().CancelOnSingleTask();
    ASSERT_EQ(E_ERROR, status);

    LOG_INFO(UDMF_TEST, "CancelOnSingleTask001 end.");
}

/* *
 * @tc.name: CancelOnSingleTask002
 * @tc.desc: Test no data
 * @tc.type: FUNC
 */
HWTEST_F(UdmfAsyncClientTest, CancelOnSingleTask002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "CancelOnSingleTask002 begin.");
    auto status = UdmfAsyncClient::GetInstance().CancelOnSingleTask();
    ASSERT_EQ(E_ERROR, status);

    LOG_INFO(UDMF_TEST, "CancelOnSingleTask002 end.");
}

/* *
 * @tc.name: CancelOnSingleTask003
 * @tc.desc: Test two data
 * @tc.type: FUNC
 */
HWTEST_F(UdmfAsyncClientTest, CancelOnSingleTask003, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "CancelOnSingleTask003 begin.");
    CustomOption customOption = {
        .intention = UDMF::UD_INTENTION_DRAG
    };
    UnifiedData data;
    auto obj = std::make_shared<Object>();
    auto file = std::make_shared<Image>(UDType::IMAGE, obj);
    file->SetUri("uri");
    file->SetRemoteUri("remoteUri");
    data.AddRecord(file);
    std::string key;
    auto status = UdmfClient::GetInstance().SetData(customOption, data, key);
    ASSERT_EQ(E_OK, status);

    GetDataParams params;
    QueryOption query = {
        .intention = UD_INTENTION_DRAG,
        .key = key
    };
    auto callback = [this](ProgressInfo progress, std::shared_ptr<UnifiedData> data) {
        LOG_INFO(UDMF_TEST, "Callback begin status=%{public}d, progress=%{public}d, name=%{public}s.",
            progress.progressStatus, progress.progress, progress.srcDevName.c_str());
        if (data == nullptr) {
            ASSERT_TRUE(progress.progress != 0);
            return;
        }
        ASSERT_EQ(1, data->GetRecords().size());
        LOG_INFO(UDMF_TEST, "CancelOnSingleTask001 callback end.");
    };
    params.query = query;
    params.progressIndicator = ProgressIndicator::DEFAULT;
    params.progressListener = callback;
    status = UdmfAsyncClient::GetInstance().StartAsyncDataRetrieval(params);
    ASSERT_EQ(E_OK, status);
    query = {
        .intention = UD_INTENTION_DRAG,
        .key = "key"
    };
    params.query = query;
    status = UdmfAsyncClient::GetInstance().StartAsyncDataRetrieval(params);
    ASSERT_EQ(E_OK, status);
    status = UdmfAsyncClient::GetInstance().CancelOnSingleTask();
    ASSERT_EQ(E_ERROR, status);

    LOG_INFO(UDMF_TEST, "CancelOnSingleTask003 end.");
}

/* *
 * @tc.name: UpdateOnSameProgressAfterInterval001
 * @tc.desc: Test ProgressTask
 * @tc.type: FUNC
 */
HWTEST_F(UdmfAsyncClientTest, UpdateOnSameProgressAfterInterval001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "UpdateOnSameProgressAfterInterval001 begin.");
    std::string businessUdKey = "udmf://a/b/c";
    GetDataParams params;
    params.progressIndicator = ProgressIndicator::DEFAULT;
    params.query.key = businessUdKey;
    UdmfAsyncClient::GetInstance().RegisterAsyncHelper(params);
    std::thread pushThread([&]() {
        auto &asyncHelper = UdmfAsyncClient::GetInstance().asyncHelperMap_.at(businessUdKey);
        for (uint32_t i = 0; i < 10; ++i) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            ProgressInfo sameProgress;
            sameProgress.progress = 20;
            asyncHelper->progressQueue.PushBack(sameProgress);
        }
        auto processKey = asyncHelper->processKey;
        std::vector<UnifiedData> unifiedDataSet;
        QueryOption query;
        query.key = processKey;
        auto ret = UdmfClient::GetInstance().GetBatchData(query, unifiedDataSet);
        EXPECT_EQ(ret, E_OK);
        ASSERT_EQ(unifiedDataSet.size(), 1);
        auto record = unifiedDataSet[0].GetRecordAt(0);
        EXPECT_EQ(record->GetType(), UDType::PLAIN_TEXT);
        auto plainText = std::static_pointer_cast<PlainText>(record);
        auto ts1 = plainText->GetAbstract();
        for (uint32_t i = 0; i < 30; ++i) {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            ProgressInfo sameProgress;
            sameProgress.progress = 20;
            asyncHelper->progressQueue.PushBack(sameProgress);
        }
        unifiedDataSet.clear();
        ret = UdmfClient::GetInstance().GetBatchData(query, unifiedDataSet);
        EXPECT_EQ(ret, E_OK);
        ASSERT_EQ(unifiedDataSet.size(), 1);
        record = unifiedDataSet[0].GetRecordAt(0);
        EXPECT_EQ(record->GetType(), UDType::PLAIN_TEXT);
        plainText = std::static_pointer_cast<PlainText>(record);
        auto ts2 = plainText->GetAbstract();
        EXPECT_TRUE(ts2 > ts1);
        ProgressInfo sameProgress;
        sameProgress.progress = 100;
        asyncHelper->progressQueue.PushBack(sameProgress);
    });
    auto ret = UdmfAsyncClient::GetInstance().ProgressTask(businessUdKey);
    EXPECT_EQ(ret, E_OK);
    pushThread.join();
    LOG_INFO(UDMF_TEST, "UpdateOnSameProgressAfterInterval001 end.");
}

/* *
 * @tc.name: Clear001
 * @tc.desc: Test Cancel、ProgressTask、InvokeHapTask、Clear、SetProgressData、GetDataTask
 * @tc.type: FUNC
 */
HWTEST_F(UdmfAsyncClientTest, Clear001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "Clear001 begin.");
    std::string key = "businessUdKey";
    UdmfAsyncClient::GetInstance().asyncHelperMap_.insert_or_assign(key, nullptr);
    auto status = UdmfAsyncClient::GetInstance().Cancel("unKnow");
    EXPECT_EQ(status, E_ERROR);
    status = UdmfAsyncClient::GetInstance().Cancel(key);
    EXPECT_EQ(status, E_ERROR);
    status = UdmfAsyncClient::GetInstance().ProgressTask("unKnow");
    EXPECT_EQ(status, E_ERROR);
    status = UdmfAsyncClient::GetInstance().ProgressTask(key);
    EXPECT_EQ(status, E_ERROR);
    status = UdmfAsyncClient::GetInstance().InvokeHapTask("unKnow");
    EXPECT_EQ(status, E_ERROR);
    status = UdmfAsyncClient::GetInstance().InvokeHapTask(key);
    EXPECT_EQ(status, E_ERROR);
    status = UdmfAsyncClient::GetInstance().Clear("unKnow");
    EXPECT_EQ(status, E_ERROR);
    status = UdmfAsyncClient::GetInstance().Clear(key);
    EXPECT_EQ(status, E_ERROR);
    status = UdmfAsyncClient::GetInstance().SetProgressData("unKnow");
    EXPECT_EQ(status, E_ERROR);
    status = UdmfAsyncClient::GetInstance().SetProgressData(key);
    EXPECT_EQ(status, E_ERROR);
    QueryOption query;
    query.key = "unKnow";
    status = UdmfAsyncClient::GetInstance().GetDataTask(query);
    EXPECT_EQ(status, E_ERROR);
    query.key = key;
    status = UdmfAsyncClient::GetInstance().GetDataTask(query);
    EXPECT_EQ(status, E_ERROR);
    LOG_INFO(UDMF_TEST, "Clear001 end.");
}

/**
* @tc.name: PushAcceptableInfo001
* @tc.desc: Test PushAcceptableInfo function.
* @tc.type: FUNC
*/
HWTEST_F(UdmfAsyncClientTest, PushAcceptableInfo001, TestSize.Level1)
{
    UdmfAsyncClient::GetInstance().asyncHelperMap_.clear();
    QueryOption query = { .key = "invalid_key" };
    std::vector<std::string> devices = { "device1", "device2" };
    auto status = UdmfAsyncClient::GetInstance().PushAcceptableInfo(query, devices);
    EXPECT_EQ(status, E_INVALID_PARAMETERS);
    query.key = "udmf://ohos.test.demo1/invalid_intention/123456";
    status = UdmfAsyncClient::GetInstance().PushAcceptableInfo(query, devices);
    EXPECT_EQ(status, E_INVALID_PARAMETERS);
    query.key = "udmf://ohos.test.demo1/drag/123456";
    status = UdmfAsyncClient::GetInstance().PushAcceptableInfo(query, devices);
    EXPECT_EQ(status, E_ERROR);

    UdmfAsyncClient::GetInstance().asyncHelperMap_.insert_or_assign(query.key, std::make_unique<AsyncHelper>());
    status = UdmfAsyncClient::GetInstance().PushAcceptableInfo(query, devices);
    EXPECT_EQ(status, E_OK);
}
} // OHOS::Test