/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
#define LOG_TAG "UdmfClientHapPermissionTest"
#include <gtest/gtest.h>

#include <unistd.h>
#include <thread>
#include <chrono>

#include "token_setproc.h"
#include "accesstoken_kit.h"
#include "directory_ex.h"
#include "nativetoken_kit.h"

#include "logger.h"
#include "udmf_client.h"
#include "application_defined_record.h"
#include "audio.h"
#include "file.h"
#include "folder.h"
#include "html.h"
#include "image.h"
#include "link.h"
#include "plain_text.h"
#include "system_defined_appitem.h"
#include "system_defined_form.h"
#include "system_defined_pixelmap.h"
#include "system_defined_record.h"
#include "text.h"
#include "unified_data_helper.h"
#include "video.h"

using namespace testing::ext;
using namespace OHOS::Security::AccessToken;
using namespace OHOS::UDMF;
using namespace OHOS;
namespace OHOS::Test {
static constexpr int USER_ID = 100;
static constexpr int INST_INDEX = 0;
class UdmfClientHapPermissionTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;

    void SetNativeToken(const std::string &processName);
    static void AllocHapToken1();
    static void AllocHapToken2();
    void SetHapToken1();
    void SetHapToken2();
    void AddPrivilege(QueryOption &option);
};

void UdmfClientHapPermissionTest::SetUpTestCase()
{
    AllocHapToken1();
    AllocHapToken2();
}

void UdmfClientHapPermissionTest::TearDownTestCase()
{
    auto tokenId = AccessTokenKit::GetHapTokenID(USER_ID, "ohos.test.demo11", INST_INDEX);
    AccessTokenKit::DeleteToken(tokenId);
    tokenId = AccessTokenKit::GetHapTokenID(USER_ID, "ohos.test.demo22", INST_INDEX);
    AccessTokenKit::DeleteToken(tokenId);
}

void UdmfClientHapPermissionTest::SetUp()
{
    SetHapToken1();
}

void UdmfClientHapPermissionTest::TearDown()
{
}

void UdmfClientHapPermissionTest::SetNativeToken(const std::string &processName)
{
    auto tokenId = AccessTokenKit::GetNativeTokenId(processName);
    SetSelfTokenID(tokenId);
}

void UdmfClientHapPermissionTest::AllocHapToken1()
{
    HapInfoParams info = {
        .userID = USER_ID,
        .bundleName = "ohos.test.demo11",
        .instIndex = INST_INDEX,
        .appIDDesc = "ohos.test.demo11",
        .isSystemApp = false,
    };

    HapPolicyParams policy = {
        .apl = APL_SYSTEM_BASIC,
        .domain = "test.domain",
        .permList = {
            {
                .permissionName = "ohos.permission.test",
                .bundleName = "ohos.test.demo11",
                .grantMode = 1,
                .availableLevel = APL_SYSTEM_BASIC,
                .label = "label",
                .labelId = 1,
                .description = "test1",
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

void UdmfClientHapPermissionTest::AllocHapToken2()
{
    HapInfoParams info = {
        .userID = USER_ID,
        .bundleName = "ohos.test.demo22",
        .instIndex = 0,
        .isSystemApp = false,
        .appIDDesc = "ohos.test.demo22"
    };
    HapPolicyParams policy = {
        .apl = APL_SYSTEM_BASIC,
        .domain = "test.domain",
        .permList = {
            {
                .permissionName = "ohos.permission.MANAGE_UDMF_APP_SHARE_OPTION",
                .bundleName = "ohos.test.demo22",
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

void UdmfClientHapPermissionTest::SetHapToken1()
{
    auto tokenId = AccessTokenKit::GetHapTokenID(USER_ID, "ohos.test.demo11", INST_INDEX);
    SetSelfTokenID(tokenId);
}

void UdmfClientHapPermissionTest::SetHapToken2()
{
    auto tokenId = AccessTokenKit::GetHapTokenID(USER_ID, "ohos.test.demo22", INST_INDEX);
    SetSelfTokenID(tokenId);
}

void UdmfClientHapPermissionTest::AddPrivilege(QueryOption &option)
{
    Privilege privilege;
    privilege.tokenId = AccessTokenKit::GetHapTokenID(USER_ID, "ohos.test.demo22", INST_INDEX);
    privilege.readPermission = "readPermission";
    privilege.writePermission = "writePermission";
    SetNativeToken("msdp_sa");
    auto status = UdmfClient::GetInstance().AddPrivilege(option, privilege);
    ASSERT_EQ(status, E_OK);
}

/**
* @tc.name: SetAppShareOption001
* @tc.desc: abnormal test, no permission
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientHapPermissionTest, SetAppShareOption001, TestSize.Level1)
{
    SetHapToken1();
    LOG_INFO(UDMF_TEST, "SetAppShareOption001 begin.");
    auto status = UdmfClient::GetInstance().SetAppShareOption("drag", ShareOptions::IN_APP);
    EXPECT_EQ(status, E_NO_PERMISSION);
    LOG_INFO(UDMF_TEST, "SetAppShareOption001 end.");
}

/**
* @tc.name: SetAppShareOption002
* @tc.desc: normal test, has permission
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientHapPermissionTest, SetAppShareOption002, TestSize.Level1)
{
    SetHapToken2();
    LOG_INFO(UDMF_TEST, "SetAppShareOption002 begin.");
    auto status = UdmfClient::GetInstance().SetAppShareOption("drag", ShareOptions::IN_APP);
    EXPECT_EQ(status, E_OK);

    ShareOptions appShareOptions;
    status = UdmfClient::GetInstance().GetAppShareOption("drag", appShareOptions);
    EXPECT_EQ(status, E_OK);
    EXPECT_EQ(appShareOptions, ShareOptions::IN_APP);

    status = UdmfClient::GetInstance().RemoveAppShareOption("drag");
    EXPECT_EQ(status, E_OK);

    status = UdmfClient::GetInstance().SetAppShareOption("drag", ShareOptions::CROSS_APP);
    EXPECT_EQ(status, E_OK);

    status = UdmfClient::GetInstance().GetAppShareOption("drag", appShareOptions);
    EXPECT_EQ(status, E_OK);
    EXPECT_EQ(appShareOptions, ShareOptions::CROSS_APP);

    status = UdmfClient::GetInstance().RemoveAppShareOption("drag");
    EXPECT_EQ(status, E_OK);

    status = UdmfClient::GetInstance().GetAppShareOption("drag", appShareOptions);
    EXPECT_EQ(status, E_NOT_FOUND);
    LOG_INFO(UDMF_TEST, "SetAppShareOption002 end.");
}

/**
* @tc.name: SetAppShareOption003
* @tc.desc: SetAppShareOption IN_APP, get data success when IN_APP
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientHapPermissionTest, SetAppShareOption003, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetAppShareOption003 begin.");
    SetHapToken2();
    auto status = UdmfClient::GetInstance().SetAppShareOption("drag", ShareOptions::IN_APP);
    EXPECT_EQ(status, E_OK);

    CustomOption option1 = { .intention = Intention::UD_INTENTION_DRAG };
    UnifiedData data1;
    Text text1;
    std::shared_ptr<UnifiedRecord> record1 = std::make_shared<Text>(text1);
    data1.AddRecord(record1);
    std::string key;
    status = UdmfClient::GetInstance().SetData(option1, data1, key);
    ASSERT_EQ(status, E_OK);

    QueryOption option2 = { .key = key };
    SetHapToken2();
    UnifiedData data2;
    status = UdmfClient::GetInstance().GetData(option2, data2);
    ASSERT_EQ(status, E_OK);

    std::shared_ptr<UnifiedRecord> record2 = data2.GetRecordAt(0);
    ASSERT_NE(record2, nullptr);
    auto type = record2->GetType();
    EXPECT_EQ(type, UDType::TEXT);

    auto text2 = static_cast<Text *>(record2.get());
    ASSERT_NE(text2, nullptr);

    status = UdmfClient::GetInstance().RemoveAppShareOption("drag");
    EXPECT_EQ(status, E_OK);
    LOG_INFO(UDMF_TEST, "SetAppShareOption003 end.");
}

/**
* @tc.name: SetAppShareOption004
* @tc.desc: SetAppShareOption CROSS_APP, get data success when CROSS_APP
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientHapPermissionTest, SetAppShareOption004, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetAppShareOption004 begin.");
    SetHapToken2();
    auto status = UdmfClient::GetInstance().SetAppShareOption("drag", ShareOptions::CROSS_APP);
    EXPECT_EQ(status, E_OK);

    CustomOption option1 = { .intention = Intention::UD_INTENTION_DRAG };
    UnifiedData data1;
    Text text1;
    std::shared_ptr<UnifiedRecord> record1 = std::make_shared<Text>(text1);
    data1.AddRecord(record1);
    std::string key;
    status = UdmfClient::GetInstance().SetData(option1, data1, key);
    ASSERT_EQ(status, E_OK);

    QueryOption option2 = { .key = key };
    AddPrivilege(option2);

    SetHapToken2();
    UnifiedData data2;
    status = UdmfClient::GetInstance().GetData(option2, data2);
    ASSERT_EQ(status, E_OK);
    std::shared_ptr<UnifiedRecord> record2 = data2.GetRecordAt(0);
    ASSERT_NE(record2, nullptr);
    auto type = record2->GetType();
    EXPECT_EQ(type, UDType::TEXT);
    auto text2 = static_cast<Text *>(record2.get());
    ASSERT_NE(text2, nullptr);

    SetHapToken2();
    status = UdmfClient::GetInstance().RemoveAppShareOption("drag");
    EXPECT_EQ(status, E_OK);
    LOG_INFO(UDMF_TEST, "SetAppShareOption004 end.");
}

/**
* @tc.name: RemoveAppShareOption001
* @tc.desc: abnormal test, no permission
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientHapPermissionTest, RemoveAppShareOption001, TestSize.Level1)
{
    SetHapToken1();
    LOG_INFO(UDMF_TEST, "RemoveAppShareOption001 begin.");
    auto status = UdmfClient::GetInstance().RemoveAppShareOption("drag");
    EXPECT_EQ(status, E_NO_PERMISSION);
    LOG_INFO(UDMF_TEST, "RemoveAppShareOption001 end.");
}

/**
* @tc.name: RemoveAppShareOption002
* @tc.desc: normal test, has permission
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientHapPermissionTest, RemoveAppShareOption002, TestSize.Level1)
{
    SetHapToken2();
    LOG_INFO(UDMF_TEST, "RemoveAppShareOption002 begin.");
    auto status = UdmfClient::GetInstance().RemoveAppShareOption("drag");
    EXPECT_EQ(status, E_OK);

    ShareOptions appShareOptions;
    status = UdmfClient::GetInstance().GetAppShareOption("drag", appShareOptions);
    EXPECT_EQ(status, E_NOT_FOUND);
    LOG_INFO(UDMF_TEST, "RemoveAppShareOption002 end.");
}
} // OHOS::Test