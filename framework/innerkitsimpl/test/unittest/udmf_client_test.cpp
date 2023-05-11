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

#include "token_setproc.h"
#include "accesstoken_kit.h"
#include "nativetoken_kit.h"

#include "logger.h"
#include "udmf_client.h"
#include "application_defined_record.h"
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
#include "video.h"

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
    void SetHapToken1();
    void SetHapToken2();

    void AddPrivilege(QueryOption &option);
    void CompareDetails(const UDDetails &details);
    void GetEmptyData(QueryOption &option);

    static constexpr int USER_ID = 100;
    static constexpr int INST_INDEX = 0;
};

void UdmfClientTest::SetUpTestCase()
{
}

void UdmfClientTest::TearDownTestCase()
{
    auto tokenId = AccessTokenKit::GetHapTokenID(USER_ID, "ohos.test.demo1", INST_INDEX);
    AccessTokenKit::DeleteToken(tokenId);
}

void UdmfClientTest::SetUp()
{
    SetHapToken1();
}

void UdmfClientTest::TearDown()
{
}

void UdmfClientTest::SetNativeToken()
{
    auto tokenId = AccessTokenKit::GetNativeTokenId("msdp_sa");
    SetSelfTokenID(tokenId);
}

void UdmfClientTest::SetHapToken1()
{
    HapInfoParams info = {
        .userID = USER_ID,
        .bundleName = "ohos.test.demo1",
        .instIndex = INST_INDEX,
        .appIDDesc = "ohos.test.demo1"
    };

    HapPolicyParams policy = {
        .apl = APL_NORMAL,
        .domain = "test.domain",
        .permList = {
            {
                .permissionName = "ohos.permission.test",
                .bundleName = "ohos.test.demo1",
                .grantMode = 1,
                .availableLevel = APL_NORMAL,
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

void UdmfClientTest::SetHapToken2()
{
    HapInfoParams info = {
        .userID = USER_ID,
        .bundleName = "ohos.test.demo2",
        .instIndex = INST_INDEX,
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

void UdmfClientTest::AddPrivilege(QueryOption &option)
{
    Privilege privilege;
    privilege.pid = getpid();
    privilege.tokenId = AccessTokenKit::GetHapTokenID(USER_ID, "ohos.test.demo2", INST_INDEX);
    privilege.readPermission = "readPermission";
    privilege.writePermission = "writePermission";
    SetNativeToken();
    auto status = UdmfClient::GetInstance().AddPrivilege(option, privilege);
    ASSERT_EQ(status, E_OK);
}

void UdmfClientTest::CompareDetails(const UDDetails &details)
{
    for (auto &detail : details) {
        auto key = detail.first;
        EXPECT_EQ(key, "udmf_key");
        auto value = detail.second;
        auto str = std::get<std::string>(value);
        EXPECT_EQ(str, "udmf_value");
    }
}

void UdmfClientTest::GetEmptyData(QueryOption &option)
{
    UnifiedData data;
    auto status = UdmfClient::GetInstance().GetData(option, data);
    EXPECT_EQ(status, E_OK);
    EXPECT_TRUE(data.IsEmpty());
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
* @tc.desc: Set Text record with valid params and get data
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
    CompareDetails(text2->GetDetails());

    GetEmptyData(option2);

    LOG_INFO(UDMF_TEST, "SetData002 end.");
}

/**
* @tc.name: SetData003
* @tc.desc: Set PlainText record with valid params and get data
* @tc.type: FUNC
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
    ASSERT_EQ(type, UDType::PLAIN_TEXT);

    auto text2 = static_cast<Text *>(record2.get());
    ASSERT_NE(text2, nullptr);
    CompareDetails(text2->GetDetails());

    auto plainText2 = static_cast<PlainText *>(record2.get());
    ASSERT_NE(plainText2, nullptr);
    EXPECT_EQ(plainText1.GetContent(), plainText2->GetContent());
    EXPECT_EQ(plainText1.GetAbstract(), plainText2->GetAbstract());

    GetEmptyData(option2);

    LOG_INFO(UDMF_TEST, "SetData003 end.");
}

/**
* @tc.name: SetData004
* @tc.desc: Set Html record with valid params and get data
* @tc.type: FUNC
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
    ASSERT_EQ(type, UDType::HTML);

    auto text2 = static_cast<Text *>(record2.get());
    ASSERT_NE(text2, nullptr);
    CompareDetails(text2->GetDetails());

    auto html2 = static_cast<Html *>(record2.get());
    ASSERT_NE(html2, nullptr);
    EXPECT_EQ(html1.GetHtmlContent(), html2->GetHtmlContent());
    EXPECT_EQ(html1.GetPlainContent(), html2->GetPlainContent());

    GetEmptyData(option2);

    LOG_INFO(UDMF_TEST, "SetData004 end.");
}

/**
* @tc.name: SetData005
* @tc.desc: Set Link record with valid params and get data
* @tc.type: FUNC
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
    ASSERT_EQ(type, UDType::HYPER_LINK);

    auto text2 = static_cast<Text *>(record2.get());
    ASSERT_NE(text2, nullptr);
    CompareDetails(text2->GetDetails());

    auto link2 = static_cast<Link *>(record2.get());
    ASSERT_NE(link2, nullptr);
    EXPECT_EQ(link1.GetUrl(), link2->GetUrl());
    EXPECT_EQ(link1.GetDescription(), link2->GetDescription());

    GetEmptyData(option2);

    LOG_INFO(UDMF_TEST, "SetData005 end.");
}

/**
* @tc.name: SetData006
* @tc.desc: Set File record with valid params and get data
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientTest, SetData006, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetData006 begin.");

    CustomOption option1 = { .intention = Intention::UD_INTENTION_DRAG };
    UnifiedData data1;
    std::string key;
    File file1;
    file1.SetRemoteUri("remoteUri");
    UDDetails details1;
    details1.insert({ "udmf_key", "udmf_value" });
    file1.SetDetails(details1);
    std::shared_ptr<UnifiedRecord> record1 = std::make_shared<File>(file1);
    data1.AddRecord(record1);
    auto status = UdmfClient::GetInstance().SetData(option1, data1, key);
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
    ASSERT_EQ(type, UDType::FILE);

    auto file2 = static_cast<File *>(record2.get());
    ASSERT_NE(file2, nullptr);
    EXPECT_EQ(file1.GetRemoteUri(), file2->GetRemoteUri());
    CompareDetails(file2->GetDetails());

    GetEmptyData(option2);

    LOG_INFO(UDMF_TEST, "SetData006 end.");
}

/**
* @tc.name: SetData007
* @tc.desc: Set Image record with valid params and get data
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientTest, SetData007, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetData007 begin.");

    CustomOption option1 = { .intention = Intention::UD_INTENTION_DRAG };
    UnifiedData data1;
    std::string key;
    Image image1;
    UDDetails details1;
    details1.insert({ "udmf_key", "udmf_value" });
    image1.SetDetails(details1);
    image1.SetRemoteUri("remoteUri");
    std::shared_ptr<UnifiedRecord> record1 = std::make_shared<Image>(image1);
    data1.AddRecord(record1);
    auto status = UdmfClient::GetInstance().SetData(option1, data1, key);
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
    ASSERT_EQ(type, UDType::IMAGE);

    auto file2 = static_cast<File *>(record2.get());
    ASSERT_NE(file2, nullptr);
    CompareDetails(file2->GetDetails());

    auto image2 = static_cast<Image *>(record2.get());
    ASSERT_NE(image2, nullptr);
    EXPECT_EQ(image1.GetRemoteUri(), image2->GetRemoteUri());

    GetEmptyData(option2);

    LOG_INFO(UDMF_TEST, "SetData007 end.");
}

/**
* @tc.name: SetData008
* @tc.desc: Set Video record with valid params and get data
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientTest, SetData008, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetData008 begin.");

    CustomOption option1 = { .intention = Intention::UD_INTENTION_DRAG };
    UnifiedData data1;
    std::string key;
    Video video1;
    UDDetails details1;
    details1.insert({ "udmf_key", "udmf_value" });
    video1.SetDetails(details1);
    video1.SetRemoteUri("remoteUri");
    std::shared_ptr<UnifiedRecord> record1 = std::make_shared<Video>(video1);
    data1.AddRecord(record1);
    auto status = UdmfClient::GetInstance().SetData(option1, data1, key);
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
    EXPECT_EQ(type, UDType::VIDEO);

    auto file2 = static_cast<File *>(record2.get());
    ASSERT_NE(file2, nullptr);
    CompareDetails(file2->GetDetails());

    auto video2 = static_cast<Video *>(record2.get());
    ASSERT_NE(video2, nullptr);
    EXPECT_EQ(video1.GetRemoteUri(), video2->GetRemoteUri());

    GetEmptyData(option2);

    LOG_INFO(UDMF_TEST, "SetData008 end.");
}

/**
* @tc.name: SetData009
* @tc.desc: Set Folder record with valid params and get data
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientTest, SetData009, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetData009 begin.");

    CustomOption option1 = { .intention = Intention::UD_INTENTION_DRAG };
    UnifiedData data1;
    std::string key;
    Folder folder1;
    UDDetails details1;
    details1.insert({ "udmf_key", "udmf_value" });
    folder1.SetDetails(details1);
    folder1.SetRemoteUri("remoteUri");
    std::shared_ptr<UnifiedRecord> record1 = std::make_shared<Folder>(folder1);
    data1.AddRecord(record1);
    auto status = UdmfClient::GetInstance().SetData(option1, data1, key);
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
    EXPECT_EQ(type, UDType::FOLDER);

    auto file2 = static_cast<File *>(record2.get());
    ASSERT_NE(file2, nullptr);
    CompareDetails(file2->GetDetails());

    auto folder2 = static_cast<Folder *>(record2.get());
    ASSERT_NE(folder2, nullptr);
    EXPECT_EQ(folder1.GetRemoteUri(), folder2->GetRemoteUri());

    GetEmptyData(option2);

    LOG_INFO(UDMF_TEST, "SetData009 end.");
}

/**
* @tc.name: SetData010
* @tc.desc: Set SystemDefined record with valid params and get data
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientTest, SetData010, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetData010 begin.");

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
    ASSERT_EQ(type, UDType::SYSTEM_DEFINED_RECORD);

    auto systemDefinedRecord2 = static_cast<SystemDefinedRecord *>(record2.get());
    ASSERT_NE(systemDefinedRecord2, nullptr);
    CompareDetails(systemDefinedRecord2->GetDetails());

    GetEmptyData(option2);

    LOG_INFO(UDMF_TEST, "SetData010 end.");
}

/**
* @tc.name: SetData011
* @tc.desc: Set Form record with valid params and get data
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientTest, SetData011, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetData011 begin.");

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
    ASSERT_EQ(type, UDType::SYSTEM_DEFINED_FORM);

    auto systemDefinedRecord2 = static_cast<SystemDefinedRecord *>(record2.get());
    ASSERT_NE(systemDefinedRecord2, nullptr);
    CompareDetails(systemDefinedRecord2->GetDetails());

    auto systemDefinedForm2 = static_cast<SystemDefinedForm *>(record2.get());
    ASSERT_NE(systemDefinedForm2, nullptr);
    EXPECT_EQ(systemDefinedForm1.GetFormId(), systemDefinedForm2->GetFormId());
    EXPECT_EQ(systemDefinedForm1.GetFormName(), systemDefinedForm2->GetFormName());
    EXPECT_EQ(systemDefinedForm1.GetBundleName(), systemDefinedForm2->GetBundleName());
    EXPECT_EQ(systemDefinedForm1.GetAbilityName(), systemDefinedForm2->GetAbilityName());
    EXPECT_EQ(systemDefinedForm1.GetModule(), systemDefinedForm2->GetModule());

    GetEmptyData(option2);

    LOG_INFO(UDMF_TEST, "SetData011 end.");
}

/**
* @tc.name: SetData012
* @tc.desc: Set AppItem record with valid params and get data
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientTest, SetData012, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetData012 begin.");

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
    ASSERT_EQ(type, UDType::SYSTEM_DEFINED_APP_ITEM);

    auto systemDefinedRecord2 = static_cast<SystemDefinedRecord *>(record2.get());
    ASSERT_NE(systemDefinedRecord2, nullptr);
    CompareDetails(systemDefinedRecord2->GetDetails());

    auto systemDefinedAppItem2 = static_cast<SystemDefinedAppItem *>(record2.get());
    ASSERT_NE(systemDefinedAppItem2, nullptr);
    EXPECT_EQ(systemDefinedAppItem1.GetAppId(), systemDefinedAppItem2->GetAppId());
    EXPECT_EQ(systemDefinedAppItem1.GetAppName(), systemDefinedAppItem2->GetAppName());
    EXPECT_EQ(systemDefinedAppItem1.GetBundleName(), systemDefinedAppItem2->GetBundleName());
    EXPECT_EQ(systemDefinedAppItem1.GetAbilityName(), systemDefinedAppItem2->GetAbilityName());
    EXPECT_EQ(systemDefinedAppItem1.GetAppIconId(), systemDefinedAppItem2->GetAppIconId());
    EXPECT_EQ(systemDefinedAppItem1.GetAppLabelId(), systemDefinedAppItem2->GetAppLabelId());

    GetEmptyData(option2);

    LOG_INFO(UDMF_TEST, "SetData012 end.");
}

/**
* @tc.name: SetData013
* @tc.desc: Set PixelMap record with valid params and get data
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientTest, SetData013, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetData013 begin.");

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
    ASSERT_EQ(type, UDType::SYSTEM_DEFINED_PIXEL_MAP);

    auto systemDefinedRecord2 = static_cast<SystemDefinedRecord *>(record2.get());
    ASSERT_NE(systemDefinedRecord2, nullptr);
    CompareDetails(systemDefinedRecord2->GetDetails());

    auto systemDefinedPixelMap2 = static_cast<SystemDefinedPixelMap *>(record2.get());
    ASSERT_NE(systemDefinedPixelMap2, nullptr);
    auto rawData2 = systemDefinedPixelMap2->GetRawData();
    EXPECT_EQ(rawData1.size(), rawData2.size());
    for (int i = 0; i < rawData1.size(); ++i) {
        EXPECT_EQ(rawData1[i], rawData2[i]);
    }

    GetEmptyData(option2);

    LOG_INFO(UDMF_TEST, "SetData013 end.");
}

/**
* @tc.name: SetData014
* @tc.desc: Set Application Defined record with valid params and get data
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientTest, SetData014, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetData014 begin.");

    CustomOption option1 = { .intention = Intention::UD_INTENTION_DRAG };
    UnifiedData data1;
    std::string key;
    ApplicationDefinedRecord applicationDefinedRecord1;
    applicationDefinedRecord1.SetApplicationDefinedType("applicationDefinedType");
    std::vector<uint8_t> rawData1 = { 1, 2, 3, 4, 5 };
    applicationDefinedRecord1.SetRawData(rawData1);
    std::shared_ptr<UnifiedRecord> record1 = std::make_shared<ApplicationDefinedRecord>(applicationDefinedRecord1);
    data1.AddRecord(record1);
    auto status = UdmfClient::GetInstance().SetData(option1, data1, key);
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
    ASSERT_EQ(type, UDType::APPLICATION_DEFINED_RECORD);

    auto applicationDefinedRecord2 = static_cast<ApplicationDefinedRecord *>(record2.get());
    ASSERT_NE(applicationDefinedRecord2, nullptr);
    EXPECT_EQ(applicationDefinedRecord1.GetApplicationDefinedType(),
              applicationDefinedRecord2->GetApplicationDefinedType());
    auto rawData2 = applicationDefinedRecord2->GetRawData();
    EXPECT_EQ(rawData1.size(), rawData2.size());
    for (int i = 0; i < rawData1.size(); ++i) {
        EXPECT_EQ(rawData1[i], rawData2[i]);
    }

    GetEmptyData(option2);

    LOG_INFO(UDMF_TEST, "SetData014 end.");
}

/**
* @tc.name: GetData001
* @tc.desc: Get data with invalid key
* @tc.type: FUNC
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
    file.SetDetails(details);
    file.SetUri("uri");
    file.SetRemoteUri("remoteUri");
    std::shared_ptr<UnifiedRecord> record3 = std::make_shared<File>(file);
    data.AddRecord(record3);

    Image image;
    file.SetDetails(details);
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

    ApplicationDefinedRecord applicationDefinedRecord;
    applicationDefinedRecord.SetApplicationDefinedType("applicationDefinedType");
    std::vector<uint8_t> rawData = { 1, 2, 3, 4, 5 };
    applicationDefinedRecord.SetRawData(rawData);
    std::shared_ptr<UnifiedRecord> record7 = std::make_shared<ApplicationDefinedRecord>(applicationDefinedRecord);
    data.AddRecord(record7);

    auto status = UdmfClient::GetInstance().SetData(option1, data, key);
    ASSERT_EQ(status, E_OK);

    QueryOption option2 = { .key = key };
    Summary summary;
    status = UdmfClient::GetInstance().GetSummary(option2, summary);

    auto size = record1->GetSize();
    size += record2->GetSize();
    size += record3->GetSize();
    size += record4->GetSize();
    size += record5->GetSize();
    size += record6->GetSize();
    size += record7->GetSize();

    ASSERT_EQ(status, E_OK);
    ASSERT_EQ(summary.totalSize, size);
    ASSERT_EQ(summary.summary["Text"], record1->GetSize());
    ASSERT_EQ(summary.summary["Text.PlainText"], record2->GetSize());
    ASSERT_EQ(summary.summary["File"], record3->GetSize());
    ASSERT_EQ(summary.summary["File.Media.Image"], record4->GetSize());
    ASSERT_EQ(summary.summary["SystemDefinedType"], record5->GetSize());
    ASSERT_EQ(summary.summary["SystemDefinedType.Form"], record6->GetSize());

    LOG_INFO(UDMF_TEST, "GetSummary001 end.");
}


/**
* @tc.name: GetSummary002
* @tc.desc: Get summary with invalid key
* @tc.type: FUNC
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
    ASSERT_EQ(status, E_OK);

    QueryOption option2 = { .key = key };
    Privilege privilege;
    privilege.pid = getpid();
    SetHapToken2();
    privilege.tokenId = AccessTokenKit::GetHapTokenID(100, "ohos.test.demo2", 0);
    privilege.readPermission = "readPermission";
    privilege.writePermission = "writePermission";
    SetNativeToken();
    status = UdmfClient::GetInstance().AddPrivilege(option2, privilege);
    ASSERT_EQ(status, E_OK);

    LOG_INFO(UDMF_TEST, "AddPrivilege001 end.");
}

/**
* @tc.name: AddPrivilege002
* @tc.desc: Add Privilege with invalid params
* @tc.type: FUNC
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

/**
* @tc.name: GetSelfData001
* @tc.desc: Set File record with valid params and no add privilege and get data by self
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientTest, GetSelfData001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetSelfData001 begin.");

    CustomOption option1 = { .intention = Intention::UD_INTENTION_DRAG };
    UnifiedData data1;
    std::string key;
    File file1;
    file1.SetRemoteUri("remoteUri");
    UDDetails details1;
    details1.insert({ "udmf_key", "udmf_value" });
    file1.SetDetails(details1);
    std::shared_ptr<UnifiedRecord> record1 = std::make_shared<File>(file1);
    data1.AddRecord(record1);
    auto status = UdmfClient::GetInstance().SetData(option1, data1, key);
    ASSERT_EQ(status, E_OK);

    QueryOption option2 = { .key = key };
    UnifiedData data2;
    status = UdmfClient::GetInstance().GetData(option2, data2);
    ASSERT_EQ(status, E_OK);

    std::shared_ptr<UnifiedRecord> record2 = data2.GetRecordAt(0);
    ASSERT_NE(record2, nullptr);
    auto type = record2->GetType();
    ASSERT_EQ(type, UDType::FILE);

    auto file2 = static_cast<File *>(record2.get());
    ASSERT_NE(file2, nullptr);
    EXPECT_EQ(file1.GetRemoteUri(), file2->GetRemoteUri());
    CompareDetails(file2->GetDetails());

    GetEmptyData(option2);

    LOG_INFO(UDMF_TEST, "GetSelfData001 end.");
}

/**
* @tc.name: GetSelfData002
* @tc.desc: Set File record with valid params and add privilege and get data by self
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientTest, GetSelfData002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetSelfData002 begin.");

    CustomOption option1 = { .intention = Intention::UD_INTENTION_DRAG };
    UnifiedData data1;
    std::string key;
    File file1;
    file1.SetRemoteUri("remoteUri");
    UDDetails details1;
    details1.insert({ "udmf_key", "udmf_value" });
    file1.SetDetails(details1);
    std::shared_ptr<UnifiedRecord> record1 = std::make_shared<File>(file1);
    data1.AddRecord(record1);
    auto status = UdmfClient::GetInstance().SetData(option1, data1, key);
    ASSERT_EQ(status, E_OK);

    QueryOption option2 = { .key = key };
    AddPrivilege(option2);
    SetHapToken1();
    UnifiedData data2;
    status = UdmfClient::GetInstance().GetData(option2, data2);
    ASSERT_EQ(status, E_OK);

    std::shared_ptr<UnifiedRecord> record2 = data2.GetRecordAt(0);
    ASSERT_NE(record2, nullptr);
    auto type = record2->GetType();
    ASSERT_EQ(type, UDType::FILE);

    auto file2 = static_cast<File *>(record2.get());
    ASSERT_NE(file2, nullptr);
    EXPECT_EQ(file1.GetRemoteUri(), file2->GetRemoteUri());
    CompareDetails(file2->GetDetails());

    GetEmptyData(option2);

    LOG_INFO(UDMF_TEST, "GetSelfData002 end.");
}