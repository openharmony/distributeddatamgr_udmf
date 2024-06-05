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
#define LOG_TAG "UdmfClientSystemHapTest"
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
class UdmfClientSystemHapTest : public testing::Test {
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

void UdmfClientSystemHapTest::SetUpTestCase()
{
    AllocHapToken1();
    AllocHapToken2();
}

void UdmfClientSystemHapTest::TearDownTestCase()
{
    auto tokenId = AccessTokenKit::GetHapTokenID(USER_ID, "ohos.test.demo1", INST_INDEX);
    AccessTokenKit::DeleteToken(tokenId);
    tokenId = AccessTokenKit::GetHapTokenID(USER_ID, "ohos.test.demo2", INST_INDEX);
    AccessTokenKit::DeleteToken(tokenId);
}

void UdmfClientSystemHapTest::SetUp()
{
    SetHapToken1();
}

void UdmfClientSystemHapTest::TearDown()
{
}

void UdmfClientSystemHapTest::SetNativeToken(const std::string &processName)
{
    auto tokenId = AccessTokenKit::GetNativeTokenId(processName);
    SetSelfTokenID(tokenId);
}

void UdmfClientSystemHapTest::AllocHapToken1()
{
    HapInfoParams info = {
        .userID = USER_ID,
        .bundleName = "ohos.test.demo1",
        .instIndex = INST_INDEX,
        .appIDDesc = "ohos.test.demo1",
        .isSystemApp = true,
    };

    HapPolicyParams policy = {
        .apl = APL_SYSTEM_BASIC,
        .domain = "test.domain",
        .permList = {
            {
                .permissionName = "ohos.permission.test",
                .bundleName = "ohos.test.demo1",
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

void UdmfClientSystemHapTest::AllocHapToken2()
{
    HapInfoParams info = {
        .userID = USER_ID,
        .bundleName = "ohos.test.demo2",
        .instIndex = INST_INDEX,
        .appIDDesc = "ohos.test.demo2",
        .isSystemApp = true,
    };

    HapPolicyParams policy = {
        .apl = APL_SYSTEM_BASIC,
        .domain = "test.domain",
        .permList = {
            {
                .permissionName = "ohos.permission.test",
                .bundleName = "ohos.test.demo2",
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

void UdmfClientSystemHapTest::SetHapToken1()
{
    auto tokenId = AccessTokenKit::GetHapTokenID(USER_ID, "ohos.test.demo1", INST_INDEX);
    SetSelfTokenID(tokenId);
}

void UdmfClientSystemHapTest::SetHapToken2()
{
    auto tokenId = AccessTokenKit::GetHapTokenID(USER_ID, "ohos.test.demo2", INST_INDEX);
    SetSelfTokenID(tokenId);
}

void UdmfClientSystemHapTest::AddPrivilege(QueryOption &option)
{
    Privilege privilege;
    privilege.tokenId = AccessTokenKit::GetHapTokenID(USER_ID, "ohos.test.demo2", INST_INDEX);
    privilege.readPermission = "readPermission";
    privilege.writePermission = "writePermission";
    SetNativeToken("msdp_sa");
    auto status = UdmfClient::GetInstance().AddPrivilege(option, privilege);
    ASSERT_EQ(status, E_OK);
}

/**
* @tc.name: SetAppShareOption001
* @tc.desc: SetAppShareOption
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientSystemHapTest, SetAppShareOption001, TestSize.Level1)
{
    AllocHapToken1();
    auto status = UdmfClient::GetInstance().RemoveAppShareOption("drag");
    LOG_INFO(UDMF_TEST, "SetAppShareOption001 begin.");
    status = UdmfClient::GetInstance().SetAppShareOption("drag", ShareOptions::IN_APP);
    EXPECT_EQ(status, E_OK);
    status = UdmfClient::GetInstance().RemoveAppShareOption("drag");
    EXPECT_EQ(status, E_OK);
    LOG_INFO(UDMF_TEST, "SetAppShareOption001 end.");
}

/**
* @tc.name: SetAppShareOption002
* @tc.desc: SetAppShareOption
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientSystemHapTest, SetAppShareOption002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetAppShareOption002 begin.");
    AllocHapToken1();
    auto status = UdmfClient::GetInstance().RemoveAppShareOption("drag");
    status = UdmfClient::GetInstance().SetAppShareOption("drag", ShareOptions::IN_APP);
    EXPECT_EQ(status, E_OK);
    ShareOptions appShareOptions;
    status = UdmfClient::GetInstance().GetAppShareOption("drag", appShareOptions);
    EXPECT_EQ(status, E_OK);
    EXPECT_EQ(appShareOptions, ShareOptions::IN_APP);
    status = UdmfClient::GetInstance().SetAppShareOption("drag", ShareOptions::IN_APP);
    EXPECT_EQ(status, E_SETTINGS_EXISTED);
    status = UdmfClient::GetInstance().RemoveAppShareOption("drag");
    EXPECT_EQ(status, E_OK);
    LOG_INFO(UDMF_TEST, "SetAppShareOption002 end.");
}

/**
* @tc.name: RemoveAppShareOption001
* @tc.desc: RemoveAppShareOption
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientSystemHapTest, RemoveAppShareOption001, TestSize.Level1)
{
    AllocHapToken1();
    LOG_INFO(UDMF_TEST, "RemoveAppShareOption001 begin.");
    auto status = UdmfClient::GetInstance().RemoveAppShareOption("drag");
    EXPECT_EQ(status, E_OK);
    LOG_INFO(UDMF_TEST, "RemoveAppShareOption001 end.");
}

/**
* @tc.name: DeleteData002
* @tc.desc: Delete data with valid params
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientSystemHapTest, systemAppSetData001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "systemAppSetData001 begin.");
    AllocHapToken1();
    auto status = UdmfClient::GetInstance().RemoveAppShareOption("drag");
    status = UdmfClient::GetInstance().SetAppShareOption("drag", ShareOptions::IN_APP);
    EXPECT_EQ(status, E_OK);
    LOG_INFO(UDMF_TEST, "systemAppSetData001 SetAppShareOption success.");

    CustomOption customOption = { .intention = UD_INTENTION_DRAG };
    UnifiedData data;
    PlainText plainText;
    plainText.SetContent("systemApptestcontent1");
    std::shared_ptr<UnifiedRecord> record = std::make_shared<PlainText>(plainText);
    data.AddRecord(record);
    std::string key;
    status = UdmfClient::GetInstance().SetData(customOption, data, key);
    ASSERT_EQ(status, E_OK);

    QueryOption queryOption = { .key = key };
    LOG_INFO(UDMF_TEST, "systemAppSetData001 SetData success, key:%{public}s.", key.c_str());

    UnifiedData outputData;
    status = UdmfClient::GetInstance().GetData(queryOption, outputData);
    ASSERT_EQ(status, E_OK);
    std::shared_ptr<UnifiedRecord> record2 = outputData.GetRecordAt(0);
    ASSERT_NE(record2, nullptr);
    auto type = record2->GetType();
    ASSERT_EQ(type, UDType::PLAIN_TEXT);
    auto text2 = static_cast<Text *>(record2.get());
    ASSERT_NE(text2, nullptr);
    auto plainText2 = static_cast<PlainText *>(record2.get());
    ASSERT_EQ(plainText2->GetContent(), "systemApptestcontent1");

    LOG_INFO(UDMF_TEST, "systemAppSetData001 end.");
}

/**
* @tc.name: systemAppSetData002
* @tc.desc: systemAppSetData CROSS_APP
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientSystemHapTest, systemAppSetData002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "systemAppSetData002 begin.");
    AllocHapToken1();
    auto status = UdmfClient::GetInstance().RemoveAppShareOption("drag");
    status = UdmfClient::GetInstance().SetAppShareOption("drag", ShareOptions::IN_APP);
    EXPECT_EQ(status, E_OK);
    LOG_INFO(UDMF_TEST, "systemAppSetData002 SetAppShareOption success.");
    CustomOption customOption = { .intention = UD_INTENTION_DRAG };
    UnifiedData data;
    PlainText plainText;
    plainText.SetContent("systemApptestcontent1");
    std::shared_ptr<UnifiedRecord> record = std::make_shared<PlainText>(plainText);
    data.AddRecord(record);
    std::string key;
    status = UdmfClient::GetInstance().SetData(customOption, data, key);
    ASSERT_EQ(status, E_OK);

    SetHapToken2();

    QueryOption queryOption = { .key = key };
    UnifiedData outputData;
    status = UdmfClient::GetInstance().GetData(queryOption, outputData);
    ASSERT_EQ(status, E_NOT_FOUND);

    LOG_INFO(UDMF_TEST, "systemAppSetData002 end.");
}
} // OHOS::Test