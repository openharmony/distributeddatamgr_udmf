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

#include <gtest/gtest.h>

#include <unistd.h>

#include "accesstoken_kit.h"
#include "nativetoken_kit.h"
#include "token_setproc.h"

#include "logger.h"
#include "udmf_client.h"
#include "text.h"
#include "plain_text.h"
#include "html.h"
#include "link.h"
#include "file.h"
#include "image.h"
#include "video.h"
#include "system_defined_record.h"
#include "system_defined_form.h"
#include "system_defined_appitem.h"
#include "system_defined_pixelmap.h"

using namespace testing::ext;
using namespace OHOS::Security::AccessToken;
using namespace OHOS::UDMF;
using namespace OHOS;

class UdmfClientTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;

    void SetNativeToken();
    void SetHapToken();
};

void UdmfClientTest::SetUpTestCase()
{
}

void UdmfClientTest::TearDownTestCase()
{
}

void UdmfClientTest::SetUp()
{
    SetHapToken();
}

void UdmfClientTest::TearDown()
{
}

void UdmfClientTest::SetNativeToken()
{
    NativeTokenInfoParams infoInstance = {
        .dcapsNum = 0,
        .permsNum = 0,
        .aclsNum = 0,
        .dcaps = nullptr,
        .perms = nullptr,
        .acls = nullptr,
        .processName = "msdp_sa",
        .aplStr = "system_core",
    };
    auto tokenId = GetAccessTokenId(&infoInstance);
    SetSelfTokenID(tokenId);
    AccessTokenKit::ReloadNativeTokenInfo();
}

void UdmfClientTest::SetHapToken()
{
    HapInfoParams info = {
        .userID = 100,
        .bundleName = "ohos.test.demo",
        .instIndex = 0,
        .appIDDesc = "ohos.test.demo"
    };

    HapPolicyParams policy = {
        .apl = APL_NORMAL,
        .domain = "test.domain",
        .permList = {
            {
                .permissionName = "ohos.permission.test",
                .bundleName = "ohos.test.demo",
                .grantMode = 1,
                .availableLevel = APL_NORMAL,
                .label = "label",
                .labelId = 1,
                .description = "test",
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

/**
* @tc.name: SetData001
* @tc.desc: Set data with invalid params
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientTest, SetData001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetData001 begin.");

    CustomOption option = { .intention = Intention::UD_INTENTION_DRAG };
    UnifiedData data;
    std::string key;
    auto status = UdmfClient::GetInstance().SetData(option, data, key);
    EXPECT_EQ(status, E_INVALID_VALUE);

    option = { .intention = Intention::UD_INTENTION_BUTT };
    Text text;
    UDDetails details;
    details.insert({ "udmf_key", "udmf_value" });
    text.SetDetails(details);
    std::shared_ptr<UnifiedRecord> record = std::make_shared<Text>(text);
    data.AddRecord(record);
    status = UdmfClient::GetInstance().SetData(option, data, key);
    EXPECT_EQ(status, E_INVALID_PARAMETERS);

    LOG_INFO(UDMF_TEST, "SetData001 end.");
}

/**
* @tc.name: SetData002
* @tc.desc: Set text data with valid params and get text data
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientTest, SetData002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetData002 begin.");

    CustomOption option1 = { .intention = Intention::UD_INTENTION_DRAG };
    UnifiedData data1;
    Text text1;
    UDDetails details1;
    details1.insert({ "udmf_key", "udmf_value" });
    text1.SetDetails(details1);
    std::shared_ptr<UnifiedRecord> record1 = std::make_shared<Text>(text1);
    data1.AddRecord(record1);
    std::string key;
    auto status = UdmfClient::GetInstance().SetData(option1, data1, key);
    EXPECT_EQ(status, E_OK);

    SetNativeToken();

    QueryOption option2 = { .key = key };
    Privilege privilege;
    privilege.pid = getpid();
    privilege.readPermission = "readPermission";
    privilege.writePermission = "writePermission";
    status = UdmfClient::GetInstance().AddPrivilege(option2, privilege);
    EXPECT_EQ(status, E_OK);

    SetHapToken();

    UnifiedData data2;
    status = UdmfClient::GetInstance().GetData(option2, data2);
    EXPECT_EQ(status, E_OK);

    std::shared_ptr<UnifiedRecord> record2 = data2.GetRecordAt(0);
    auto type = record2->GetType();
    EXPECT_EQ(type, UDType::TEXT);

    auto text2 = static_cast<Text *>(record2.get());
    EXPECT_NE(text2, nullptr);

    auto details2 = text2->GetDetails();
    for (auto &detail : details2) {
        auto key = detail.first;
        EXPECT_EQ(key, "udmf_key");
        auto value = detail.second;
        auto str = std::get<std::string>(value);
        EXPECT_EQ(str, "udmf_value");
    }

    UnifiedData data3;
    status = UdmfClient::GetInstance().GetData(option2, data3);
    EXPECT_EQ(status, E_OK);
    EXPECT_TRUE(data3.IsEmpty());

    LOG_INFO(UDMF_TEST, "SetData002 end.");
}

/**
* @tc.name: SetData003
* @tc.desc: Set data with valid params and get data
* @tc.type: FUNC
* @tc.require:
*/
HWTEST_F(UdmfClientTest, SetData003, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetData003 begin.");

    CustomOption option1 = { .intention = Intention::UD_INTENTION_DRAG };
    UnifiedData data1;
    PlainText plainText1;
    UDDetails details1;
    details1.insert({ "udmf_key", "udmf_value" });
    plainText1.SetDetails(details1);
    plainText1.SetContent("content");
    plainText1.SetAbstract("abstract");
    std::shared_ptr<UnifiedRecord> record1 = std::make_shared<PlainText>(plainText1);
    data1.AddRecord(record1);
    std::string key;
    auto status = UdmfClient::GetInstance().SetData(option1, data1, key);
    EXPECT_EQ(status, E_OK);

    SetNativeToken();

    QueryOption option2 = { .key = key };
    Privilege privilege;
    privilege.pid = getpid();
    privilege.readPermission = "readPermission";
    privilege.writePermission = "writePermission";
    status = UdmfClient::GetInstance().AddPrivilege(option2, privilege);
    EXPECT_EQ(status, E_OK);

    SetHapToken();

    UnifiedData data2;
    status = UdmfClient::GetInstance().GetData(option2, data2);
    EXPECT_EQ(status, E_OK);

    std::shared_ptr<UnifiedRecord> record2 = data2.GetRecordAt(0);
    auto type = record2->GetType();
    EXPECT_EQ(type, UDType::PLAIN_TEXT);

    auto text2 = static_cast<Text *>(record2.get());
    EXPECT_NE(text2, nullptr);

    auto details2 = text2->GetDetails();
    for (auto &detail : details2) {
        auto key = detail.first;
        EXPECT_EQ(key, "udmf_key");
        auto value = detail.second;
        auto str = std::get<std::string>(value);
        EXPECT_EQ(str, "udmf_value");
    }

    auto plainText2 = static_cast<PlainText *>(record2.get());
    EXPECT_NE(plainText2, nullptr);
    EXPECT_EQ(plainText1.GetContent(), plainText2->GetContent());
    EXPECT_EQ(plainText1.GetAbstract(), plainText2->GetAbstract());

    UnifiedData data3;
    status = UdmfClient::GetInstance().GetData(option2, data3);
    EXPECT_EQ(status, E_OK);
    EXPECT_TRUE(data3.IsEmpty());

    LOG_INFO(UDMF_TEST, "SetData003 end.");
}

/**
* @tc.name: SetData004
* @tc.desc: Set data with valid params and get data
* @tc.type: FUNC
* @tc.require:
*/
HWTEST_F(UdmfClientTest, SetData004, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetData004 begin.");

    CustomOption option1 = { .intention = Intention::UD_INTENTION_DRAG };
    UnifiedData data1;
    std::string key;
    Html html1;
    UDDetails details1;
    details1.insert({ "udmf_key", "udmf_value" });
    html1.SetDetails(details1);
    html1.SetHtmlContent("htmlcontent");
    html1.SetPlainContent("plainContent");
    std::shared_ptr<UnifiedRecord> record1 = std::make_shared<Html>(html1);
    data1.AddRecord(record1);
    auto status = UdmfClient::GetInstance().SetData(option1, data1, key);
    EXPECT_EQ(status, E_OK);

    SetNativeToken();

    QueryOption option2 = { .key = key };
    Privilege privilege;
    privilege.pid = getpid();
    privilege.readPermission = "readPermission";
    privilege.writePermission = "writePermission";
    status = UdmfClient::GetInstance().AddPrivilege(option2, privilege);
    EXPECT_EQ(status, E_OK);

    SetHapToken();

    UnifiedData data2;
    status = UdmfClient::GetInstance().GetData(option2, data2);
    EXPECT_EQ(status, E_OK);

    std::shared_ptr<UnifiedRecord> record2 = data2.GetRecordAt(0);
    auto type = record2->GetType();
    EXPECT_EQ(type, UDType::HTML);

    auto text2 = static_cast<Text *>(record2.get());
    EXPECT_NE(text2, nullptr);

    auto details2 = text2->GetDetails();
    for (auto &detail : details2) {
        auto key = detail.first;
        EXPECT_EQ(key, "udmf_key");
        auto value = detail.second;
        auto str = std::get<std::string>(value);
        EXPECT_EQ(str, "udmf_value");
    }

    auto html2 = static_cast<Html *>(record2.get());
    EXPECT_NE(html2, nullptr);
    EXPECT_EQ(html1.GetHtmlContent(), html2->GetHtmlContent());
    EXPECT_EQ(html1.GetPlainContent(), html2->GetPlainContent());

    UnifiedData data3;
    status = UdmfClient::GetInstance().GetData(option2, data3);
    EXPECT_EQ(status, E_OK);
    EXPECT_TRUE(data3.IsEmpty());

    LOG_INFO(UDMF_TEST, "SetData004 end.");
}

/**
* @tc.name: SetData005
* @tc.desc: Set data with valid params and get data
* @tc.type: FUNC
* @tc.require:
*/
HWTEST_F(UdmfClientTest, SetData005, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetData005 begin.");

    CustomOption option1 = { .intention = Intention::UD_INTENTION_DRAG };
    UnifiedData data1;
    std::string key;
    Link link1;
    UDDetails details1;
    details1.insert({ "udmf_key", "udmf_value" });
    link1.SetDetails(details1);
    link1.SetUrl("url");
    link1.SetDescription("description");
    std::shared_ptr<UnifiedRecord> record1 = std::make_shared<Link>(link1);
    data1.AddRecord(record1);
    auto status = UdmfClient::GetInstance().SetData(option1, data1, key);
    EXPECT_EQ(status, E_OK);

    SetNativeToken();

    QueryOption option2 = { .key = key };
    Privilege privilege;
    privilege.pid = getpid();
    privilege.readPermission = "readPermission";
    privilege.writePermission = "writePermission";
    status = UdmfClient::GetInstance().AddPrivilege(option2, privilege);
    EXPECT_EQ(status, E_OK);

    SetHapToken();

    UnifiedData data2;
    status = UdmfClient::GetInstance().GetData(option2, data2);
    EXPECT_EQ(status, E_OK);

    std::shared_ptr<UnifiedRecord> record2 = data2.GetRecordAt(0);
    auto type = record2->GetType();
    EXPECT_EQ(type, UDType::HYPER_LINK);

    auto text2 = static_cast<Text *>(record2.get());
    EXPECT_NE(text2, nullptr);

    auto details2 = text2->GetDetails();
    for (auto &detail : details2) {
        auto key = detail.first;
        EXPECT_EQ(key, "udmf_key");
        auto value = detail.second;
        auto str = std::get<std::string>(value);
        EXPECT_EQ(str, "udmf_value");
    }

    auto link2 = static_cast<Link *>(record2.get());
    EXPECT_NE(link2, nullptr);
    EXPECT_EQ(link1.GetUrl(), link2->GetUrl());
    EXPECT_EQ(link1.GetDescription(), link2->GetDescription());

    UnifiedData data3;
    status = UdmfClient::GetInstance().GetData(option2, data3);
    EXPECT_EQ(status, E_OK);
    EXPECT_TRUE(data3.IsEmpty());

    LOG_INFO(UDMF_TEST, "SetData005 end.");
}

/**
* @tc.name: SetData006
* @tc.desc: Set data with valid params and get data
* @tc.type: FUNC
* @tc.require:
*/
HWTEST_F(UdmfClientTest, SetData006, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetData006 begin.");

    CustomOption option1 = { .intention = Intention::UD_INTENTION_DRAG };
    UnifiedData data1;
    std::string key;
    File file1;
    file1.SetUri("uri");
    file1.SetRemoteUri("remoteUri");
    std::shared_ptr<UnifiedRecord> record1 = std::make_shared<File>(file1);
    data1.AddRecord(record1);
    auto status = UdmfClient::GetInstance().SetData(option1, data1, key);
    EXPECT_EQ(status, E_OK);

    SetNativeToken();

    QueryOption option2 = { .key = key };
    Privilege privilege;
    privilege.pid = getpid();
    privilege.readPermission = "readPermission";
    privilege.writePermission = "writePermission";
    status = UdmfClient::GetInstance().AddPrivilege(option2, privilege);
    EXPECT_EQ(status, E_OK);

    SetHapToken();

    UnifiedData data2;
    status = UdmfClient::GetInstance().GetData(option2, data2);
    EXPECT_EQ(status, E_OK);

    std::shared_ptr<UnifiedRecord> record2 = data2.GetRecordAt(0);
    auto type = record2->GetType();
    EXPECT_EQ(type, UDType::FILE);

    auto file2 = static_cast<File *>(record2.get());
    EXPECT_NE(file2, nullptr);
    EXPECT_EQ(file1.GetUri(), file2->GetUri());
    EXPECT_EQ(file1.GetRemoteUri(), file2->GetRemoteUri());

    UnifiedData data3;
    status = UdmfClient::GetInstance().GetData(option2, data3);
    EXPECT_EQ(status, E_OK);
    EXPECT_TRUE(data3.IsEmpty());

    LOG_INFO(UDMF_TEST, "SetData006 end.");
}

/**
* @tc.name: SetData007
* @tc.desc: Set data with valid params and get data
* @tc.type: FUNC
* @tc.require:
*/
HWTEST_F(UdmfClientTest, SetData007, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetData007 begin.");

    CustomOption option1 = { .intention = Intention::UD_INTENTION_DRAG };
    UnifiedData data1;
    std::string key;
    Image image1;
    image1.SetUri("uri");
    image1.SetRemoteUri("remoteUri");
    std::shared_ptr<UnifiedRecord> record1 = std::make_shared<Image>(image1);
    data1.AddRecord(record1);
    auto status = UdmfClient::GetInstance().SetData(option1, data1, key);
    EXPECT_EQ(status, E_OK);

    SetNativeToken();

    QueryOption option2 = { .key = key };
    Privilege privilege;
    privilege.pid = getpid();
    privilege.readPermission = "readPermission";
    privilege.writePermission = "writePermission";
    status = UdmfClient::GetInstance().AddPrivilege(option2, privilege);
    EXPECT_EQ(status, E_OK);

    SetHapToken();

    UnifiedData data2;
    status = UdmfClient::GetInstance().GetData(option2, data2);
    EXPECT_EQ(status, E_OK);

    std::shared_ptr<UnifiedRecord> record2 = data2.GetRecordAt(0);
    auto type = record2->GetType();
    EXPECT_EQ(type, UDType::IMAGE);

    auto image2 = static_cast<Image *>(record2.get());
    EXPECT_NE(image2, nullptr);
    EXPECT_EQ(image1.GetUri(), image2->GetUri());
    EXPECT_EQ(image1.GetRemoteUri(), image2->GetRemoteUri());

    UnifiedData data3;
    status = UdmfClient::GetInstance().GetData(option2, data3);
    EXPECT_EQ(status, E_OK);
    EXPECT_TRUE(data3.IsEmpty());

    LOG_INFO(UDMF_TEST, "SetData007 end.");
}

/**
* @tc.name: SetData008
* @tc.desc: Set data with valid params and get data
* @tc.type: FUNC
* @tc.require:
*/
HWTEST_F(UdmfClientTest, SetData008, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetData008 begin.");

    CustomOption option1 = { .intention = Intention::UD_INTENTION_DRAG };
    UnifiedData data1;
    std::string key;
    Video video1;
    video1.SetUri("uri");
    video1.SetRemoteUri("remoteUri");
    std::shared_ptr<UnifiedRecord> record1 = std::make_shared<Video>(video1);
    data1.AddRecord(record1);
    auto status = UdmfClient::GetInstance().SetData(option1, data1, key);
    EXPECT_EQ(status, E_OK);

    SetNativeToken();

    QueryOption option2 = { .key = key };
    Privilege privilege;
    privilege.pid = getpid();
    privilege.readPermission = "readPermission";
    privilege.writePermission = "writePermission";
    status = UdmfClient::GetInstance().AddPrivilege(option2, privilege);
    EXPECT_EQ(status, E_OK);

    SetHapToken();

    UnifiedData data2;
    status = UdmfClient::GetInstance().GetData(option2, data2);
    EXPECT_EQ(status, E_OK);

    std::shared_ptr<UnifiedRecord> record2 = data2.GetRecordAt(0);
    auto type = record2->GetType();
    EXPECT_EQ(type, UDType::VIDEO);

    auto video2 = static_cast<Video *>(record2.get());
    EXPECT_NE(video2, nullptr);
    EXPECT_EQ(video1.GetUri(), video2->GetUri());
    EXPECT_EQ(video1.GetRemoteUri(), video2->GetRemoteUri());

    UnifiedData data3;
    status = UdmfClient::GetInstance().GetData(option2, data3);
    EXPECT_EQ(status, E_OK);
    EXPECT_TRUE(data3.IsEmpty());

    LOG_INFO(UDMF_TEST, "SetData008 end.");
}

/**
* @tc.name: SetData009
* @tc.desc: Set data with valid params and get data
* @tc.type: FUNC
* @tc.require:
*/
HWTEST_F(UdmfClientTest, SetData009, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetData009 begin.");

    CustomOption option1 = { .intention = Intention::UD_INTENTION_DRAG };
    UnifiedData data1;
    std::string key;
    SystemDefinedRecord systemDefinedRecord1;
    UDDetails details1;
    details1.insert({ "udmf_key", "udmf_value" });
    systemDefinedRecord1.SetDetails(details1);
    std::shared_ptr<UnifiedRecord> record1 = std::make_shared<SystemDefinedRecord>(systemDefinedRecord1);
    data1.AddRecord(record1);
    auto status = UdmfClient::GetInstance().SetData(option1, data1, key);
    EXPECT_EQ(status, E_OK);

    SetNativeToken();

    QueryOption option2 = { .key = key };
    Privilege privilege;
    privilege.pid = getpid();
    privilege.readPermission = "readPermission";
    privilege.writePermission = "writePermission";
    status = UdmfClient::GetInstance().AddPrivilege(option2, privilege);
    EXPECT_EQ(status, E_OK);

    SetHapToken();

    UnifiedData data2;
    status = UdmfClient::GetInstance().GetData(option2, data2);
    EXPECT_EQ(status, E_OK);

    std::shared_ptr<UnifiedRecord> record2 = data2.GetRecordAt(0);
    auto type = record2->GetType();
    EXPECT_EQ(type, UDType::SYSTEM_DEFINED_RECORD);

    auto systemDefinedRecord2 = static_cast<SystemDefinedRecord *>(record2.get());
    EXPECT_NE(systemDefinedRecord2, nullptr);

    auto details2 = systemDefinedRecord2->GetDetails();
    for (auto &detail : details2) {
        auto key = detail.first;
        EXPECT_EQ(key, "udmf_key");
        auto value = detail.second;
        auto str = std::get<std::string>(value);
        EXPECT_EQ(str, "udmf_value");
    }

    UnifiedData data3;
    status = UdmfClient::GetInstance().GetData(option2, data3);
    EXPECT_EQ(status, E_OK);
    EXPECT_TRUE(data3.IsEmpty());

    LOG_INFO(UDMF_TEST, "SetData009 end.");
}

/**
* @tc.name: SetData010
* @tc.desc: Set data with valid params and get data
* @tc.type: FUNC
* @tc.require:
*/
HWTEST_F(UdmfClientTest, SetData010, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetData010 begin.");

    CustomOption option1 = { .intention = Intention::UD_INTENTION_DRAG };
    UnifiedData data1;
    std::string key;
    SystemDefinedForm systemDefinedForm1;
    UDDetails details1;
    details1.insert({ "udmf_key", "udmf_value" });
    systemDefinedForm1.SetDetails(details1);
    systemDefinedForm1.SetFormId(123);
    systemDefinedForm1.SetFormName("formName");
    systemDefinedForm1.SetModule("module");
    systemDefinedForm1.SetAbilityName("abilityName");
    systemDefinedForm1.SetBundleName("bundleName");
    std::shared_ptr<UnifiedRecord> record1 = std::make_shared<SystemDefinedForm>(systemDefinedForm1);
    data1.AddRecord(record1);
    auto status = UdmfClient::GetInstance().SetData(option1, data1, key);
    EXPECT_EQ(status, E_OK);

    SetNativeToken();

    QueryOption option2 = { .key = key };
    Privilege privilege;
    privilege.pid = getpid();
    privilege.readPermission = "readPermission";
    privilege.writePermission = "writePermission";
    status = UdmfClient::GetInstance().AddPrivilege(option2, privilege);
    EXPECT_EQ(status, E_OK);

    SetHapToken();

    UnifiedData data2;
    status = UdmfClient::GetInstance().GetData(option2, data2);
    EXPECT_EQ(status, E_OK);

    std::shared_ptr<UnifiedRecord> record2 = data2.GetRecordAt(0);
    auto type = record2->GetType();
    EXPECT_EQ(type, UDType::SYSTEM_DEFINED_FORM);

    auto systemDefinedRecord2 = static_cast<SystemDefinedRecord *>(record2.get());
    EXPECT_NE(systemDefinedRecord2, nullptr);

    auto details2 = systemDefinedRecord2->GetDetails();
    for (auto &detail : details2) {
        auto key = detail.first;
        EXPECT_EQ(key, "udmf_key");
        auto value = detail.second;
        auto str = std::get<std::string>(value);
        EXPECT_EQ(str, "udmf_value");
    }

    auto systemDefinedForm2 = static_cast<SystemDefinedForm *>(record2.get());
    EXPECT_NE(systemDefinedForm2, nullptr);
    EXPECT_EQ(systemDefinedForm1.GetFormId(), systemDefinedForm2->GetFormId());
    EXPECT_EQ(systemDefinedForm1.GetFormName(), systemDefinedForm2->GetFormName());
    EXPECT_EQ(systemDefinedForm1.GetBundleName(), systemDefinedForm2->GetBundleName());
    EXPECT_EQ(systemDefinedForm1.GetAbilityName(), systemDefinedForm2->GetAbilityName());
    EXPECT_EQ(systemDefinedForm1.GetModule(), systemDefinedForm2->GetModule());

    UnifiedData data3;
    status = UdmfClient::GetInstance().GetData(option2, data3);
    EXPECT_EQ(status, E_OK);
    EXPECT_TRUE(data3.IsEmpty());

    LOG_INFO(UDMF_TEST, "SetData010 end.");
}

/**
* @tc.name: SetData011
* @tc.desc: Set data with valid params and get data
* @tc.type: FUNC
* @tc.require:
*/
HWTEST_F(UdmfClientTest, SetData011, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetData011 begin.");

    CustomOption option1 = { .intention = Intention::UD_INTENTION_DRAG };
    UnifiedData data1;
    std::string key;
    SystemDefinedAppItem systemDefinedAppItem1;
    UDDetails details1;
    details1.insert({ "udmf_key", "udmf_value" });
    systemDefinedAppItem1.SetDetails(details1);
    systemDefinedAppItem1.SetAppId("appId");
    systemDefinedAppItem1.SetAppName("appName");
    systemDefinedAppItem1.SetAppIconId("appIconId");
    systemDefinedAppItem1.SetAppLabelId("appLabelId");
    systemDefinedAppItem1.SetBundleName("bundleName");
    systemDefinedAppItem1.SetAbilityName("abilityName");
    std::shared_ptr<UnifiedRecord> record1 = std::make_shared<SystemDefinedAppItem>(systemDefinedAppItem1);
    data1.AddRecord(record1);
    auto status = UdmfClient::GetInstance().SetData(option1, data1, key);
    EXPECT_EQ(status, E_OK);

    SetNativeToken();

    QueryOption option2 = { .key = key };
    Privilege privilege;
    privilege.pid = getpid();
    privilege.readPermission = "readPermission";
    privilege.writePermission = "writePermission";
    status = UdmfClient::GetInstance().AddPrivilege(option2, privilege);
    EXPECT_EQ(status, E_OK);

    SetHapToken();

    UnifiedData data2;
    status = UdmfClient::GetInstance().GetData(option2, data2);
    EXPECT_EQ(status, E_OK);

    std::shared_ptr<UnifiedRecord> record2 = data2.GetRecordAt(0);
    auto type = record2->GetType();
    EXPECT_EQ(type, UDType::SYSTEM_DEFINED_APP_ITEM);

    auto systemDefinedRecord2 = static_cast<SystemDefinedRecord *>(record2.get());
    EXPECT_NE(systemDefinedRecord2, nullptr);

    auto details2 = systemDefinedRecord2->GetDetails();
    for (auto &detail : details2) {
        auto key = detail.first;
        EXPECT_EQ(key, "udmf_key");
        auto value = detail.second;
        auto str = std::get<std::string>(value);
        EXPECT_EQ(str, "udmf_value");
    }

    auto systemDefinedAppItem2 = static_cast<SystemDefinedAppItem *>(record2.get());
    EXPECT_NE(systemDefinedAppItem2, nullptr);
    EXPECT_EQ(systemDefinedAppItem1.GetAppId(), systemDefinedAppItem2->GetAppId());
    EXPECT_EQ(systemDefinedAppItem1.GetAppName(), systemDefinedAppItem2->GetAppName());
    EXPECT_EQ(systemDefinedAppItem1.GetBundleName(), systemDefinedAppItem2->GetBundleName());
    EXPECT_EQ(systemDefinedAppItem1.GetAbilityName(), systemDefinedAppItem2->GetAbilityName());
    EXPECT_EQ(systemDefinedAppItem1.GetAppIconId(), systemDefinedAppItem2->GetAppIconId());
    EXPECT_EQ(systemDefinedAppItem1.GetAppLabelId(), systemDefinedAppItem2->GetAppLabelId());

    UnifiedData data3;
    status = UdmfClient::GetInstance().GetData(option2, data3);
    EXPECT_EQ(status, E_OK);
    EXPECT_TRUE(data3.IsEmpty());

    LOG_INFO(UDMF_TEST, "SetData011 end.");
}

/**
* @tc.name: SetData012
* @tc.desc: Set data with valid params and get data
* @tc.type: FUNC
* @tc.require:
*/
HWTEST_F(UdmfClientTest, SetData012, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetData012 begin.");

    CustomOption option1 = { .intention = Intention::UD_INTENTION_DRAG };
    UnifiedData data1;
    std::string key;
    SystemDefinedPixelMap systemDefinedPixelMap1;
    UDDetails details1;
    details1.insert({ "udmf_key", "udmf_value" });
    systemDefinedPixelMap1.SetDetails(details1);
    std::vector<uint8_t> rawData1 ={ 1, 2, 3, 4, 5 };
    systemDefinedPixelMap1.SetRawData(rawData1);
    std::shared_ptr<UnifiedRecord> record1 = std::make_shared<SystemDefinedPixelMap>(systemDefinedPixelMap1);
    data1.AddRecord(record1);
    auto status = UdmfClient::GetInstance().SetData(option1, data1, key);
    EXPECT_EQ(status, E_OK);

    SetNativeToken();

    QueryOption option2 = { .key = key };
    Privilege privilege;
    privilege.pid = getpid();
    privilege.readPermission = "readPermission";
    privilege.writePermission = "writePermission";
    status = UdmfClient::GetInstance().AddPrivilege(option2, privilege);
    EXPECT_EQ(status, E_OK);

    SetHapToken();

    UnifiedData data2;
    status = UdmfClient::GetInstance().GetData(option2, data2);
    EXPECT_EQ(status, E_OK);

    std::shared_ptr<UnifiedRecord> record2 = data2.GetRecordAt(0);
    auto type = record2->GetType();
    EXPECT_EQ(type, UDType::SYSTEM_DEFINED_PIXEL_MAP);

    auto systemDefinedRecord2 = static_cast<SystemDefinedRecord *>(record2.get());
    EXPECT_NE(systemDefinedRecord2, nullptr);

    auto details2 = systemDefinedRecord2->GetDetails();
    for (auto &detail : details2) {
        auto key = detail.first;
        EXPECT_EQ(key, "udmf_key");
        auto value = detail.second;
        auto str = std::get<std::string>(value);
        EXPECT_EQ(str, "udmf_value");
    }

    auto systemDefinedPixelMap2 = static_cast<SystemDefinedPixelMap *>(record2.get());
    EXPECT_NE(systemDefinedPixelMap2, nullptr);
    auto rawData2 = systemDefinedPixelMap2->GetRawData();
    EXPECT_EQ(rawData1.size(), rawData2.size());
    for (int i = 0; i < rawData1.size(); ++i) {
        EXPECT_EQ(rawData1[i], rawData2[i]);
    }

    UnifiedData data3;
    status = UdmfClient::GetInstance().GetData(option2, data3);
    EXPECT_EQ(status, E_OK);
    EXPECT_TRUE(data3.IsEmpty());

    LOG_INFO(UDMF_TEST, "SetData012 end.");
}

/**
* @tc.name: GetData001
* @tc.desc: Get data with invalid params
* @tc.type: FUNC
* @tc.require:
*/
HWTEST_F(UdmfClientTest, GetData001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetData001 begin.");

    QueryOption option;
    UnifiedData data;
    auto status = UdmfClient::GetInstance().GetData(option, data);
    EXPECT_EQ(status, E_INVALID_PARAMETERS);

    option.key = "udmf";
    status = UdmfClient::GetInstance().GetData(option, data);
    EXPECT_EQ(status, E_INVALID_PARAMETERS);

    option.key = "odmf://";
    status = UdmfClient::GetInstance().GetData(option, data);
    EXPECT_EQ(status, E_INVALID_PARAMETERS);

    option.key = "udmf://drag";
    status = UdmfClient::GetInstance().GetData(option, data);
    EXPECT_EQ(status, E_INVALID_PARAMETERS);

    option.key = "udmf://123/bundle/group";
    status = UdmfClient::GetInstance().GetData(option, data);
    EXPECT_EQ(status, E_INVALID_PARAMETERS);

    option.key = "udmf://drag/bundle";
    status = UdmfClient::GetInstance().GetData(option, data);
    EXPECT_EQ(status, E_INVALID_PARAMETERS);

    option.key = "udmf://drag/bundle***/group";
    status = UdmfClient::GetInstance().GetData(option, data);
    EXPECT_EQ(status, E_INVALID_PARAMETERS);

    option.key = "udmf://drag/bundle/";
    status = UdmfClient::GetInstance().GetData(option, data);
    EXPECT_EQ(status, E_INVALID_PARAMETERS);

    option.key = "udmf://drag/bundle/group###";
    status = UdmfClient::GetInstance().GetData(option, data);
    EXPECT_EQ(status, E_INVALID_PARAMETERS);
    LOG_INFO(UDMF_TEST, "GetData001 end.");
}

/**
* @tc.name: GetSummary001
* @tc.desc: Get summary data
* @tc.type: FUNC
* @tc.require:
*/
HWTEST_F(UdmfClientTest, GetSummary001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetSummary001 begin.");

    CustomOption option1 = { .intention = Intention::UD_INTENTION_DRAG };
    UnifiedData data;
    std::string key;

    UDDetails details;
    details.insert({ "udmf_key", "udmf_value" });

    Text text;
    text.SetDetails(details);
    std::shared_ptr<UnifiedRecord> record1 = std::make_shared<Text>(text);
    data.AddRecord(record1);

    PlainText plainText;
    plainText.SetDetails(details);
    plainText.SetContent("content");
    plainText.SetAbstract("abstract");
    std::shared_ptr<UnifiedRecord> record2 = std::make_shared<PlainText>(plainText);
    data.AddRecord(record2);

    File file;
    file.SetUri("uri");
    file.SetRemoteUri("remoteUri");
    std::shared_ptr<UnifiedRecord> record3 = std::make_shared<File>(file);
    data.AddRecord(record3);

    Image image;
    image.SetUri("uri");
    image.SetRemoteUri("remoteUri");
    std::shared_ptr<UnifiedRecord> record4 = std::make_shared<Image>(image);
    data.AddRecord(record4);

    SystemDefinedRecord systemDefinedRecord;
    systemDefinedRecord.SetDetails(details);
    std::shared_ptr<UnifiedRecord> record5 = std::make_shared<SystemDefinedRecord>(systemDefinedRecord);
    data.AddRecord(record5);

    SystemDefinedForm systemDefinedForm;
    systemDefinedForm.SetDetails(details);
    systemDefinedForm.SetFormId(123);
    systemDefinedForm.SetFormName("formName");
    systemDefinedForm.SetModule("module");
    systemDefinedForm.SetAbilityName("abilityName");
    systemDefinedForm.SetBundleName("bundleName");
    std::shared_ptr<UnifiedRecord> record6 = std::make_shared<SystemDefinedForm>(systemDefinedForm);
    data.AddRecord(record6);

    auto status = UdmfClient::GetInstance().SetData(option1, data, key);
    EXPECT_EQ(status, E_OK);

    QueryOption option2 = { .key = key };
    Summary summary;
    status = UdmfClient::GetInstance().GetSummary(option2, summary);

    auto size = record1->GetSize();
    size += record2->GetSize();
    size += record3->GetSize();
    size += record4->GetSize();
    size += record5->GetSize();
    size += record6->GetSize();

    EXPECT_EQ(status, E_OK);
    EXPECT_EQ(summary.totalSize, size);
    EXPECT_EQ(summary.summary["Text"], record1->GetSize());
    EXPECT_EQ(summary.summary["Text.PlainText"], record2->GetSize());
    EXPECT_EQ(summary.summary["File"], record3->GetSize());
    EXPECT_EQ(summary.summary["File.Media.Image"], record4->GetSize());
    EXPECT_EQ(summary.summary["SystemDefinedType"], record5->GetSize());
    EXPECT_EQ(summary.summary["SystemDefinedType.Form"], record6->GetSize());

    LOG_INFO(UDMF_TEST, "GetSummary001 end.");
}


/**
* @tc.name: GetSummary002
* @tc.desc: Get summary with invalid params
* @tc.type: FUNC
* @tc.require:
*/
HWTEST_F(UdmfClientTest, GetSummary002, TestSize.Level1)
{
    LOG_INFO(UDMF_FRAMEWORK, "GetSummary002 begin.");

    QueryOption option;
    Summary summary;
    auto status = UdmfClient::GetInstance().GetSummary(option, summary);
    EXPECT_EQ(status, E_INVALID_PARAMETERS);

    option.key = "udmf";
    status = UdmfClient::GetInstance().GetSummary(option, summary);
    EXPECT_EQ(status, E_INVALID_PARAMETERS);

    option.key = "odmf://";
    status = UdmfClient::GetInstance().GetSummary(option, summary);
    EXPECT_EQ(status, E_INVALID_PARAMETERS);

    option.key = "udmf://drag";
    status = UdmfClient::GetInstance().GetSummary(option, summary);
    EXPECT_EQ(status, E_INVALID_PARAMETERS);

    option.key = "udmf://123/bundle/group";
    status = UdmfClient::GetInstance().GetSummary(option, summary);
    EXPECT_EQ(status, E_INVALID_PARAMETERS);

    option.key = "udmf://drag/bundle";
    status = UdmfClient::GetInstance().GetSummary(option, summary);
    EXPECT_EQ(status, E_INVALID_PARAMETERS);

    option.key = "udmf://drag/bundle***/group";
    status = UdmfClient::GetInstance().GetSummary(option, summary);
    EXPECT_EQ(status, E_INVALID_PARAMETERS);

    option.key = "udmf://drag/bundle/";
    status = UdmfClient::GetInstance().GetSummary(option, summary);
    EXPECT_EQ(status, E_INVALID_PARAMETERS);

    option.key = "udmf://drag/bundle/group###";
    status = UdmfClient::GetInstance().GetSummary(option, summary);
    EXPECT_EQ(status, E_INVALID_PARAMETERS);
    LOG_INFO(UDMF_FRAMEWORK, "GetSummary002 end.");
}

/**
* @tc.name: AddPrivilege001
* @tc.desc: Add privilege with valid params
* @tc.type: FUNC
* @tc.require:
*/
HWTEST_F(UdmfClientTest, AddPrivilege001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "AddPrivilege001 begin.");

    CustomOption option1 = { .intention = Intention::UD_INTENTION_DRAG };
    UnifiedData data;
    Text text;
    UDDetails details;
    details.insert({ "udmf_key", "udmf_value" });
    text.SetDetails(details);
    std::shared_ptr<UnifiedRecord> record = std::make_shared<Text>(text);
    data.AddRecord(record);
    std::string key;
    auto status = UdmfClient::GetInstance().SetData(option1, data, key);
    EXPECT_EQ(status, E_OK);

    SetNativeToken();

    QueryOption option2 = { .key = key };
    Privilege privilege;
    privilege.pid = getpid();
    privilege.readPermission = "readPermission";
    privilege.writePermission = "writePermission";
    status = UdmfClient::GetInstance().AddPrivilege(option2, privilege);
    EXPECT_EQ(status, E_OK);

    LOG_INFO(UDMF_TEST, "AddPrivilege001 end.");
}

/**
* @tc.name: AddPrivilege002
* @tc.desc: Add Privilege with invalid params
* @tc.type: FUNC
* @tc.require:
*/
HWTEST_F(UdmfClientTest, AddPrivilege002, TestSize.Level1)
{
    LOG_INFO(UDMF_FRAMEWORK, "AddPrivilege002 begin.");

    QueryOption option;
    Privilege privilege;
    auto status = UdmfClient::GetInstance().AddPrivilege(option, privilege);
    EXPECT_EQ(status, E_INVALID_PARAMETERS);

    option.key = "udmf";
    status = UdmfClient::GetInstance().AddPrivilege(option, privilege);
    EXPECT_EQ(status, E_INVALID_PARAMETERS);

    option.key = "odmf://";
    status = UdmfClient::GetInstance().AddPrivilege(option, privilege);
    EXPECT_EQ(status, E_INVALID_PARAMETERS);

    option.key = "udmf://drag";
    status = UdmfClient::GetInstance().AddPrivilege(option, privilege);
    EXPECT_EQ(status, E_INVALID_PARAMETERS);

    option.key = "udmf://123/bundle/group";
    status = UdmfClient::GetInstance().AddPrivilege(option, privilege);
    EXPECT_EQ(status, E_INVALID_PARAMETERS);

    option.key = "udmf://drag/bundle";
    status = UdmfClient::GetInstance().AddPrivilege(option, privilege);
    EXPECT_EQ(status, E_INVALID_PARAMETERS);

    option.key = "udmf://drag/bundle***/group";
    status = UdmfClient::GetInstance().AddPrivilege(option, privilege);
    EXPECT_EQ(status, E_INVALID_PARAMETERS);

    option.key = "udmf://drag/bundle/";
    status = UdmfClient::GetInstance().AddPrivilege(option, privilege);
    EXPECT_EQ(status, E_INVALID_PARAMETERS);

    option.key = "udmf://drag/bundle/group###";
    status = UdmfClient::GetInstance().AddPrivilege(option, privilege);
    EXPECT_EQ(status, E_INVALID_PARAMETERS);
    LOG_INFO(UDMF_FRAMEWORK, "AddPrivilege002 end.");
}