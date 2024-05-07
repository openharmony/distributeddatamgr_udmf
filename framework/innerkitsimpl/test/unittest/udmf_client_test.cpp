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
#define LOG_TAG "UdmfClientTest"
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
constexpr int SLEEP_TIME = 50;   // 50 ms
class UdmfClientTest : public testing::Test {
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
    void CompareDetails(const UDDetails &details);
    void GetEmptyData(QueryOption &option);

    static constexpr int USER_ID = 100;
    static constexpr int INST_INDEX = 0;
};

void UdmfClientTest::SetUpTestCase()
{
    AllocHapToken1();
    AllocHapToken2();
}

void UdmfClientTest::TearDownTestCase()
{
    auto tokenId = AccessTokenKit::GetHapTokenID(USER_ID, "ohos.test.demo1", INST_INDEX);
    AccessTokenKit::DeleteToken(tokenId);
    tokenId = AccessTokenKit::GetHapTokenID(USER_ID, "ohos.test.demo2", INST_INDEX);
    AccessTokenKit::DeleteToken(tokenId);
}

void UdmfClientTest::SetUp()
{
    SetHapToken1();
}

void UdmfClientTest::TearDown()
{
}

void UdmfClientTest::SetNativeToken(const std::string &processName)
{
    auto tokenId = AccessTokenKit::GetNativeTokenId(processName);
    SetSelfTokenID(tokenId);
}

void UdmfClientTest::AllocHapToken1()
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

void UdmfClientTest::AllocHapToken2()
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

void UdmfClientTest::SetHapToken1()
{
    auto tokenId = AccessTokenKit::GetHapTokenID(USER_ID, "ohos.test.demo1", INST_INDEX);
    SetSelfTokenID(tokenId);
}

void UdmfClientTest::SetHapToken2()
{
    auto tokenId = AccessTokenKit::GetHapTokenID(USER_ID, "ohos.test.demo2", INST_INDEX);
    SetSelfTokenID(tokenId);
}

void UdmfClientTest::AddPrivilege(QueryOption &option)
{
    Privilege privilege;
    privilege.tokenId = AccessTokenKit::GetHapTokenID(USER_ID, "ohos.test.demo2", INST_INDEX);
    privilege.readPermission = "readPermission";
    privilege.writePermission = "writePermission";
    SetNativeToken("msdp_sa");
    auto status = UdmfClient::GetInstance().AddPrivilege(option, privilege);
    ASSERT_EQ(status, E_OK);
}

void UdmfClientTest::CompareDetails(const UDDetails &details)
{
    for (const auto &detail : details) {
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
    std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_TIME));
    auto status = UdmfClient::GetInstance().GetData(option, data);
    EXPECT_EQ(status, E_NOT_FOUND);
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
    EXPECT_EQ(status, E_INVALID_PARAMETERS);

    option = { .intention = Intention::UD_INTENTION_BUTT };
    Text text;
    UDDetails details;
    details.insert({ "udmf_key", "udmf_value" });
    text.SetDetails(details);
    std::shared_ptr<UnifiedRecord> record = std::make_shared<Text>(text);
    data.AddRecord(record);
    status = UdmfClient::GetInstance().SetData(option, data, key);
    EXPECT_EQ(status, E_INVALID_PARAMETERS);

    option = {};
    status = UdmfClient::GetInstance().SetData(option, data, key);
    EXPECT_EQ(status, E_INVALID_PARAMETERS);

    option = { .intention = Intention::UD_INTENTION_BASE };
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
    ASSERT_EQ(type, UDType::HYPERLINK);

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
* @tc.desc: Set Audio record with valid params and get data
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientTest, SetData009, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetData009 begin.");

    CustomOption option1 = { .intention = Intention::UD_INTENTION_DRAG };
    UnifiedData data1;
    std::string key;
    Audio audio1;
    UDDetails details1;
    details1.insert({ "udmf_key", "udmf_value" });
    audio1.SetDetails(details1);
    audio1.SetRemoteUri("remoteUri");
    std::shared_ptr<UnifiedRecord> record1 = std::make_shared<Audio>(audio1);
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
    EXPECT_EQ(type, UDType::AUDIO);

    auto file2 = static_cast<File *>(record2.get());
    ASSERT_NE(file2, nullptr);
    CompareDetails(file2->GetDetails());

    auto audio2 = static_cast<Audio *>(record2.get());
    ASSERT_NE(audio2, nullptr);
    EXPECT_EQ(audio1.GetRemoteUri(), audio2->GetRemoteUri());

    GetEmptyData(option2);

    LOG_INFO(UDMF_TEST, "SetData009 end.");
}

/**
* @tc.name: SetData010
* @tc.desc: Set Folder record with valid params and get data
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientTest, SetData010, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetData010 begin.");

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

    LOG_INFO(UDMF_TEST, "SetData010 end.");
}

/**
* @tc.name: SetData011
* @tc.desc: Set SystemDefined record with valid params and get data
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientTest, SetData011, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetData011 begin.");

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

    LOG_INFO(UDMF_TEST, "SetData011 end.");
}

/**
* @tc.name: SetData012
* @tc.desc: Set Form record with valid params and get data
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientTest, SetData012, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetData012 begin.");

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

    LOG_INFO(UDMF_TEST, "SetData012 end.");
}

/**
* @tc.name: SetData013
* @tc.desc: Set AppItem record with valid params and get data
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientTest, SetData013, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetData013 begin.");

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

    LOG_INFO(UDMF_TEST, "SetData013 end.");
}

/**
* @tc.name: SetData014
* @tc.desc: Set PixelMap record with valid params and get data
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientTest, SetData014, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetData014 begin.");

    CustomOption option1 = { .intention = Intention::UD_INTENTION_DRAG };
    UnifiedData data1;
    std::string key;
    SystemDefinedPixelMap systemDefinedPixelMap1;
    UDDetails details1;
    details1.insert({ "udmf_key", "udmf_value" });
    systemDefinedPixelMap1.SetDetails(details1);
    std::vector<uint8_t> rawData1 = { 1, 2, 3, 4, 5 };
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
    for (uint32_t i = 0; i < rawData1.size(); ++i) {
        EXPECT_EQ(rawData1[i], rawData2[i]);
    }

    GetEmptyData(option2);

    LOG_INFO(UDMF_TEST, "SetData014 end.");
}

/**
* @tc.name: SetData015
* @tc.desc: Set Application Defined record with valid params and get data
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientTest, SetData015, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetData015 begin.");

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
    for (uint32_t i = 0; i < rawData1.size(); ++i) {
        EXPECT_EQ(rawData1[i], rawData2[i]);
    }

    GetEmptyData(option2);

    LOG_INFO(UDMF_TEST, "SetData015 end.");
}

/**
* @tc.name: SetData016
* @tc.desc: Set multiple record with valid params and get data
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientTest, SetData016, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetData016 begin.");

    CustomOption customOption = {.intention = Intention::UD_INTENTION_DRAG};
    std::string key;
    UnifiedData inputData;
    std::vector<std::shared_ptr<UnifiedRecord>> inputRecords = {
        std::make_shared<Text>(),
        std::make_shared<PlainText>(),
        std::make_shared<File>(),
        std::make_shared<Image>(),
        std::make_shared<SystemDefinedRecord>(),
        std::make_shared<SystemDefinedForm>(),
        std::make_shared<ApplicationDefinedRecord>()
    };
    inputData.SetRecords(inputRecords);

    auto status = UdmfClient::GetInstance().SetData(customOption, inputData, key);
    ASSERT_EQ(status, E_OK);

    QueryOption queryOption = { .key = key };
    UnifiedData outputData;
    status = UdmfClient::GetInstance().GetData(queryOption, outputData);
    ASSERT_EQ(status, E_OK);
    auto outputRecords = outputData.GetRecords();
    ASSERT_EQ(inputRecords.size(), outputRecords.size());
    for (size_t i = 0; i < outputRecords.size(); ++i) {
        ASSERT_EQ(outputRecords[i]->GetType(), inputRecords[i]->GetType());
    }

    LOG_INFO(UDMF_TEST, "SetData016 end.");
}

/**
* @tc.name: SetData017
* @tc.desc: Set 512 records with valid params and get data
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientTest, SetData017, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetData017 begin.");

    CustomOption customOption = {.intention = Intention::UD_INTENTION_DRAG};
    std::string key;
    UnifiedData inputData;
    std::vector<std::shared_ptr<UnifiedRecord>> inputRecords;
    for (int32_t i = 0; i < 512; ++i) {
        inputRecords.emplace_back(std::make_shared<Text>());
    }
    inputData.SetRecords(inputRecords);

    auto status = UdmfClient::GetInstance().SetData(customOption, inputData, key);
    ASSERT_EQ(status, E_OK);

    QueryOption queryOption = { .key = key };
    UnifiedData outputData;
    status = UdmfClient::GetInstance().GetData(queryOption, outputData);
    ASSERT_EQ(status, E_OK);
    auto outputRecords = outputData.GetRecords();
    ASSERT_EQ(inputRecords.size(), outputRecords.size());

    LOG_INFO(UDMF_TEST, "SetData017 end.");
}

/**
* @tc.name: SetData018
* @tc.desc: Set one 2MB record of data with valid params and get data
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientTest, SetData018, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetData018 begin.");

    CustomOption customOption = { .intention = Intention::UD_INTENTION_DRAG };
    UnifiedData inputData;
    std::string key;
    UDDetails details;
    std::string value;
    int64_t maxSize = 512 * 1024;
    for (int64_t i = 0; i < maxSize; ++i) {
        value += "11";
    }
    details.insert({ value, value });
    Text text;
    text.SetDetails(details);
    std::shared_ptr<UnifiedRecord> record = std::make_shared<Text>(text);
    inputData.AddRecord(record);

    auto status = UdmfClient::GetInstance().SetData(customOption, inputData, key);
    ASSERT_EQ(status, E_OK);

    QueryOption queryOption = { .key = key };
    UnifiedData outputData;
    status = UdmfClient::GetInstance().GetData(queryOption, outputData);
    ASSERT_EQ(status, E_OK);

    LOG_INFO(UDMF_TEST, "SetData018 end.");
}

/**
* @tc.name: SetData019
* @tc.desc: Set one over 2MB record of data with valid params and get data
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientTest, SetData019, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetData019 begin.");

    CustomOption customOption = { .intention = Intention::UD_INTENTION_DRAG };
    UnifiedData inputData;
    std::string key;
    UDDetails details;
    std::string value;
    int64_t maxSize = 512 * 1024;
    for (int64_t i = 0; i < maxSize; ++i) {
        value += "11";
    }
    details.insert({ value, value });
    details.insert({ "udmf_key", "udmf_value" });
    Text text;
    text.SetDetails(details);
    std::shared_ptr<UnifiedRecord> record = std::make_shared<Text>(text);
    inputData.AddRecord(record);

    UnifiedDataHelper::SetRootPath("/data/udmf_test/");
    auto status = UdmfClient::GetInstance().SetData(customOption, inputData, key);
    ASSERT_EQ(status, E_OK);

    QueryOption queryOption = { .key = key };
    UnifiedData outputData;
    status = UdmfClient::GetInstance().GetData(queryOption, outputData);
    ASSERT_EQ(status, E_OK);
    UnifiedDataHelper::SetRootPath("");

    LOG_INFO(UDMF_TEST, "SetData019 end.");
}

/**
* @tc.name: SetData020
* @tc.desc: Set two 2MB record of data with valid params and get data
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientTest, SetData020, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetData020 begin.");

    CustomOption customOption = { .intention = Intention::UD_INTENTION_DRAG };
    UnifiedData inputData;
    std::string key;
    UDDetails details;
    std::string value;
    int64_t maxSize = 512 * 1024;
    for (int64_t i = 0; i < maxSize; ++i) {
        value += "11";
    }
    details.insert({ value, value });
    Text text;
    text.SetDetails(details);
    std::shared_ptr<UnifiedRecord> record = std::make_shared<Text>(text);
    for (int i = 0; i < 2; ++i) {
        inputData.AddRecord(record);
    }
    auto status = UdmfClient::GetInstance().SetData(customOption, inputData, key);
    ASSERT_EQ(status, E_OK);

    QueryOption queryOption = { .key = key };
    UnifiedData outputData;
    status = UdmfClient::GetInstance().GetData(queryOption, outputData);
    ASSERT_EQ(status, E_OK);

    LOG_INFO(UDMF_TEST, "SetData020 end.");
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
    ASSERT_EQ(summary.summary["general.text"], record1->GetSize());
    ASSERT_EQ(summary.summary["general.plain-text"], record2->GetSize());
    ASSERT_EQ(summary.summary["general.file"], record3->GetSize());
    ASSERT_EQ(summary.summary["general.image"], record4->GetSize());
    ASSERT_EQ(summary.summary["SystemDefinedType"], record5->GetSize());
    ASSERT_EQ(summary.summary["openharmony.form"], record6->GetSize());
    ASSERT_EQ(summary.summary["ApplicationDefinedType"], record7->GetSize());

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
    SetHapToken2();
    privilege.tokenId = AccessTokenKit::GetHapTokenID(100, "ohos.test.demo2", 0);
    privilege.readPermission = "readPermission";
    privilege.writePermission = "writePermission";
    SetNativeToken("msdp_sa");
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
* @tc.name: AddPrivilege003
* @tc.desc: Add privilege with invalid intention
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientTest, AddPrivilege003, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "AddPrivilege003 begin.");

    CustomOption option1 = { .intention = Intention::UD_INTENTION_DATA_HUB };
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
    SetHapToken2();
    privilege.tokenId = AccessTokenKit::GetHapTokenID(100, "ohos.test.demo2", 0);
    privilege.readPermission = "readPermission";
    privilege.writePermission = "writePermission";
    SetNativeToken("msdp_sa");
    status = UdmfClient::GetInstance().AddPrivilege(option2, privilege);
    ASSERT_EQ(status, E_NO_PERMISSION);
    LOG_INFO(UDMF_TEST, "AddPrivilege003 end.");
}

/**
* @tc.name: AddPrivilege004
* @tc.desc: Add privilege for unauthorized process with valid params
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientTest, AddPrivilege004, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "AddPrivilege004 begin.");

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
    SetHapToken2();
    privilege.tokenId = AccessTokenKit::GetHapTokenID(100, "ohos.test.demo2", 0);
    privilege.readPermission = "readPermission";
    privilege.writePermission = "writePermission";
    SetNativeToken("foundation");
    status = UdmfClient::GetInstance().AddPrivilege(option2, privilege);
    ASSERT_EQ(status, E_NO_PERMISSION);
    LOG_INFO(UDMF_TEST, "AddPrivilege004 end.");
}

/**
* @tc.name: AddPrivilege005
* @tc.desc: Add privilege with valid params
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientTest, AddPrivilege005, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "AddPrivilege005 begin.");

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
    SetHapToken2();
    privilege.tokenId = AccessTokenKit::GetHapTokenID(100, "ohos.test.demo2", 0);
    privilege.readPermission = "readAndKeep";
    privilege.writePermission = "writePermission";
    SetNativeToken("msdp_sa");
    status = UdmfClient::GetInstance().AddPrivilege(option2, privilege);
    ASSERT_EQ(status, E_OK);

    SetHapToken2();
    UnifiedData data1;
    status = UdmfClient::GetInstance().GetData(option2, data1);
    ASSERT_EQ(status, E_OK);
    
    std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_TIME));
    UnifiedData data2;
    status = UdmfClient::GetInstance().GetData(option2, data2);
    ASSERT_EQ(status, E_OK);
    std::shared_ptr<UnifiedRecord> record2 = data2.GetRecordAt(0);
    ASSERT_NE(record2, nullptr);
    auto type = record2->GetType();
    ASSERT_EQ(type, UDType::TEXT);
    auto text2 = static_cast<Text *>(record2.get());
    ASSERT_NE(text2, nullptr);
    CompareDetails(text2->GetDetails());   // Can be read repeatedly.
    LOG_INFO(UDMF_TEST, "AddPrivilege005 end.");
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

/**
* @tc.name: SetData021
* @tc.desc: Set datas with intention ${UD_INTENTION_DATA_HUB} and manually check db is cleared before set or not
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientTest, SetData021, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetData021 begin.");
    QueryOption query = { .intention = Intention::UD_INTENTION_DATA_HUB };
    std::vector<UnifiedData> unifiedDataSet;
    auto status = UdmfClient::GetInstance().DeleteData(query, unifiedDataSet);
    ASSERT_EQ(status, E_OK);
    unifiedDataSet.clear();
    status = UdmfClient::GetInstance().GetBatchData(query, unifiedDataSet);
    ASSERT_EQ(status, E_OK);
    ASSERT_TRUE(unifiedDataSet.empty());

    CustomOption customOption = { .intention = Intention::UD_INTENTION_DATA_HUB };
    UnifiedData data1;
    PlainText plainText1;
    plainText1.SetContent("content1");
    std::shared_ptr<UnifiedRecord> record1 = std::make_shared<PlainText>(plainText1);
    data1.AddRecord(record1);
    std::string key;
    status = UdmfClient::GetInstance().SetData(customOption, data1, key);
    ASSERT_EQ(status, E_OK);

    UnifiedData data2;
    PlainText plainText2;
    plainText1.SetContent("content2");
    std::shared_ptr<UnifiedRecord> record2 = std::make_shared<PlainText>(plainText1);
    data2.AddRecord(record2);
    status = UdmfClient::GetInstance().SetData(customOption, data2, key);
    ASSERT_EQ(status, E_OK);

    SetHapToken2();
    status = UdmfClient::GetInstance().GetBatchData(query, unifiedDataSet);
    ASSERT_EQ(status, E_OK);
    auto size = static_cast<int32_t>(unifiedDataSet.size());
    ASSERT_EQ(size, 2);
    LOG_INFO(UDMF_TEST, "SetData021 end.");
}

/**
* @tc.name: UpdateData001
* @tc.desc: Update data with invalid params
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientTest, UpdateData001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "UpdateData001 begin.");

    UnifiedData data;
    QueryOption queryOption = { .key = "" };
    auto status = UdmfClient::GetInstance().UpdateData(queryOption, data);
    ASSERT_EQ(status, E_INVALID_PARAMETERS);

    queryOption = { .key = "udmf://drag/ohos.test.demo1/abcde" };
    status = UdmfClient::GetInstance().UpdateData(queryOption, data);
    ASSERT_EQ(status, E_INVALID_PARAMETERS);

    CustomOption customOption = { .intention = Intention::UD_INTENTION_DATA_HUB };
    UnifiedData data1;
    PlainText plainText1;
    plainText1.SetContent("content1");
    std::shared_ptr<UnifiedRecord> record1 = std::make_shared<PlainText>(plainText1);
    data1.AddRecord(record1);
    std::string key;
    status = UdmfClient::GetInstance().SetData(customOption, data1, key);
    ASSERT_EQ(status, E_OK);

    queryOption = { .key = key };
    SetHapToken2();
    status = UdmfClient::GetInstance().UpdateData(queryOption, data);
    ASSERT_EQ(status, E_INVALID_PARAMETERS);
    LOG_INFO(UDMF_TEST, "UpdateData001 end.");
}

/**
* @tc.name: UpdateData002
* @tc.desc: Update data with valid params
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientTest, UpdateData002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "UpdateData002 begin.");

    UnifiedData data;
    PlainText plainText;
    plainText.SetContent("content");
    std::shared_ptr<UnifiedRecord> record = std::make_shared<PlainText>(plainText);
    data.AddRecord(record);

    CustomOption customOption = { .intention = Intention::UD_INTENTION_DATA_HUB };
    UnifiedData data1;
    PlainText plainText1;
    plainText1.SetContent("content1");
    std::shared_ptr<UnifiedRecord> record1 = std::make_shared<PlainText>(plainText1);
    data1.AddRecord(record1);
    std::string key;
    auto status = UdmfClient::GetInstance().SetData(customOption, data1, key);

    ASSERT_EQ(status, E_OK);
    QueryOption queryOption = { .key = key };
    SetHapToken2();
    status = UdmfClient::GetInstance().UpdateData(queryOption, data);
    ASSERT_EQ(status, E_OK);

    std::vector<UnifiedData> dataSet;
    status = UdmfClient::GetInstance().GetBatchData(queryOption, dataSet);
    std::shared_ptr<UnifiedRecord> record2 = dataSet[0].GetRecordAt(0);
    ASSERT_NE(record2, nullptr);
    auto type = record2->GetType();
    ASSERT_EQ(type, UDType::PLAIN_TEXT);
    auto plainText2 = static_cast<PlainText *>(record2.get());
    ASSERT_EQ(plainText2->GetContent(), "content");

    LOG_INFO(UDMF_TEST, "UpdateData002 end.");
}

/**
* @tc.name: QueryData001
* @tc.desc: Query data with invalid params
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientTest, QueryData001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "QueryData001 begin.");
    std::vector<UnifiedData> unifiedDataSet;
    QueryOption queryOption = {};
    auto status = UdmfClient::GetInstance().GetBatchData(queryOption, unifiedDataSet);
    ASSERT_EQ(status, E_INVALID_PARAMETERS);

    queryOption = { .key = "udmf://drag/ohos.test.demo1/abcde" };
    status = UdmfClient::GetInstance().GetBatchData(queryOption, unifiedDataSet);
    ASSERT_EQ(status, E_INVALID_PARAMETERS);

    queryOption = { .intention = UD_INTENTION_DRAG };
    status = UdmfClient::GetInstance().GetBatchData(queryOption, unifiedDataSet);
    ASSERT_EQ(status, E_INVALID_PARAMETERS);

    queryOption = { .key = "udmf://DataHub/ohos.test.demo1/abcde", .intention = UD_INTENTION_DRAG };
    status = UdmfClient::GetInstance().GetBatchData(queryOption, unifiedDataSet);
    ASSERT_EQ(status, E_INVALID_PARAMETERS);

    queryOption = { .key = "udmf://drag/ohos.test.demo1/abcde", .intention = UD_INTENTION_DATA_HUB };
    status = UdmfClient::GetInstance().GetBatchData(queryOption, unifiedDataSet);
    ASSERT_EQ(status, E_INVALID_PARAMETERS);
    LOG_INFO(UDMF_TEST, "QueryData001 end.");
}

/**
* @tc.name: QueryData002
* @tc.desc: Query data with valid params
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientTest, QueryData002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "QueryData002 begin.");

    QueryOption query = { .intention = Intention::UD_INTENTION_DATA_HUB };
    std::vector<UnifiedData> unifiedDataSet;
    auto status = UdmfClient::GetInstance().DeleteData(query, unifiedDataSet);
    ASSERT_EQ(status, E_OK);
    unifiedDataSet.clear();
    status = UdmfClient::GetInstance().GetBatchData(query, unifiedDataSet);
    ASSERT_EQ(status, E_OK);
    ASSERT_TRUE(unifiedDataSet.empty());

    CustomOption customOption = { .intention = Intention::UD_INTENTION_DATA_HUB };
    UnifiedData data;
    PlainText plainText;
    plainText.SetContent("content1");
    std::shared_ptr<UnifiedRecord> record = std::make_shared<PlainText>(plainText);
    data.AddRecord(record);
    std::string key;
    status = UdmfClient::GetInstance().SetData(customOption, data, key);
    ASSERT_EQ(status, E_OK);

    query = { .key = key };
    status = UdmfClient::GetInstance().GetBatchData(query, unifiedDataSet);
    ASSERT_EQ(status, E_OK);
    auto size = static_cast<int32_t>(unifiedDataSet.size());
    ASSERT_EQ(size, 1);
    std::shared_ptr<UnifiedRecord> record2 = unifiedDataSet[0].GetRecordAt(0);
    ASSERT_NE(record2, nullptr);
    auto type = record2->GetType();
    ASSERT_EQ(type, UDType::PLAIN_TEXT);
    auto plainText2 = static_cast<PlainText *>(record2.get());
    ASSERT_EQ(plainText2->GetContent(), "content1");

    UnifiedData data2;
    plainText.SetContent("content2");
    record = std::make_shared<PlainText>(plainText);
    data2.AddRecord(record);
    status = UdmfClient::GetInstance().SetData(customOption, data2, key);
    ASSERT_EQ(status, E_OK);

    unifiedDataSet.clear();
    query = { .key = key, .intention = UD_INTENTION_DATA_HUB };
    status = UdmfClient::GetInstance().GetBatchData(query, unifiedDataSet);
    ASSERT_EQ(status, E_OK);
    size = static_cast<int32_t>(unifiedDataSet.size());
    ASSERT_EQ(size, 1);
    record2 = unifiedDataSet[0].GetRecordAt(0);
    ASSERT_NE(record2, nullptr);
    type = record2->GetType();
    ASSERT_EQ(type, UDType::PLAIN_TEXT);
    plainText2 = static_cast<PlainText *>(record2.get());
    ASSERT_EQ(plainText2->GetContent(), "content2");

    unifiedDataSet.clear();
    query = { .intention = UD_INTENTION_DATA_HUB };
    status = UdmfClient::GetInstance().GetBatchData(query, unifiedDataSet);
    ASSERT_EQ(status, E_OK);
    size = static_cast<int32_t>(unifiedDataSet.size());
    ASSERT_EQ(size, 2);

    LOG_INFO(UDMF_TEST, "QueryData002 end.");
}

/**
* @tc.name: DeleteData001
* @tc.desc: Delete data with invalid params
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientTest, DeleteData001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "DeleteData001 begin.");
    std::vector<UnifiedData> unifiedDataSet;
    QueryOption queryOption = {};
    auto status = UdmfClient::GetInstance().DeleteData(queryOption, unifiedDataSet);
    ASSERT_EQ(status, E_INVALID_PARAMETERS);

    queryOption = { .key = "udmf://drag/ohos.test.demo1/abcde" };
    status = UdmfClient::GetInstance().DeleteData(queryOption, unifiedDataSet);
    ASSERT_EQ(status, E_INVALID_PARAMETERS);

    queryOption = { .intention = UD_INTENTION_DRAG };
    status = UdmfClient::GetInstance().DeleteData(queryOption, unifiedDataSet);
    ASSERT_EQ(status, E_INVALID_PARAMETERS);

    queryOption = { .key = "udmf://DataHub/ohos.test.demo1/abcde", .intention = UD_INTENTION_DRAG };
    status = UdmfClient::GetInstance().DeleteData(queryOption, unifiedDataSet);
    ASSERT_EQ(status, E_INVALID_PARAMETERS);

    queryOption = { .key = "udmf://drag/ohos.test.demo1/abcde", .intention = UD_INTENTION_DATA_HUB };
    status = UdmfClient::GetInstance().DeleteData(queryOption, unifiedDataSet);
    ASSERT_EQ(status, E_INVALID_PARAMETERS);
    LOG_INFO(UDMF_TEST, "DeleteData001 end.");
}

/**
* @tc.name: DeleteData002
* @tc.desc: Delete data with valid params
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientTest, DeleteData002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "DeleteData002 begin.");

    CustomOption customOption = { .intention = UD_INTENTION_DATA_HUB };
    UnifiedData data;
    PlainText plainText;
    plainText.SetContent("content1");
    std::shared_ptr<UnifiedRecord> record = std::make_shared<PlainText>(plainText);
    data.AddRecord(record);
    std::string key;
    auto status = UdmfClient::GetInstance().SetData(customOption, data, key);
    ASSERT_EQ(status, E_OK);
    status = UdmfClient::GetInstance().SetData(customOption, data, key);
    ASSERT_EQ(status, E_OK);
    status = UdmfClient::GetInstance().SetData(customOption, data, key);
    ASSERT_EQ(status, E_OK);

    QueryOption queryOption = { .key = key };
    SetHapToken2();

    std::vector<UnifiedData> unifiedDataSet;
    status = UdmfClient::GetInstance().DeleteData(queryOption, unifiedDataSet);
    ASSERT_EQ(status, E_OK);

    unifiedDataSet.clear();
    status = UdmfClient::GetInstance().GetBatchData(queryOption, unifiedDataSet);
    ASSERT_TRUE(unifiedDataSet.empty());

    queryOption = { .intention = UD_INTENTION_DATA_HUB };
    unifiedDataSet.clear();
    status = UdmfClient::GetInstance().GetBatchData(queryOption, unifiedDataSet);
    ASSERT_TRUE(!unifiedDataSet.empty());

    status = UdmfClient::GetInstance().DeleteData(queryOption, unifiedDataSet);
    ASSERT_EQ(status, E_OK);

    unifiedDataSet.clear();
    status = UdmfClient::GetInstance().GetBatchData(queryOption, unifiedDataSet);
    ASSERT_TRUE(unifiedDataSet.empty());
    LOG_INFO(UDMF_TEST, "DeleteData002 end.");
}

/**
* @tc.name: SetData022
* @tc.desc: Set two over 2MB record of data with valid params and get data
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientTest, SetData022, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetData022 begin.");

    CustomOption customOption = { .intention = Intention::UD_INTENTION_DRAG };
    UnifiedData inputData;
    std::string key;
    UDDetails details;
    std::string value;
    int64_t maxSize = 512 * 1024;
    for (int64_t i = 0; i < maxSize; ++i) {
        value += "11";
    }
    details.insert({ value, value });
    details.insert({ "udmf_key", "udmf_value" });
    Text text;
    text.SetDetails(details);
    std::shared_ptr<UnifiedRecord> record = std::make_shared<Text>(text);
    for (int i = 0; i < 2; ++i) {
        inputData.AddRecord(record);
    }
    UnifiedDataHelper::SetRootPath("/data/udmf_test/");
    auto status = UdmfClient::GetInstance().SetData(customOption, inputData, key);
    ASSERT_EQ(status, E_OK);

    QueryOption queryOption = { .key = key };
    UnifiedData outputData;
    status = UdmfClient::GetInstance().GetData(queryOption, outputData);
    ASSERT_EQ(status, E_OK);
    UnifiedDataHelper::SetRootPath("");

    LOG_INFO(UDMF_TEST, "SetData022 end.");
}

/**
* @tc.name: SetData023
* @tc.desc: Set 200MB record of data with valid params and get data
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientTest, SetData023, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetData023 begin.");

    CustomOption customOption = { .intention = Intention::UD_INTENTION_DRAG };
    UnifiedData inputData;
    std::string key;
    UDDetails details;
    std::string value;
    int64_t maxSize = 512 * 1024;
    for (int64_t i = 0; i < maxSize; ++i) {
        value += "11";
    }
    details.insert({ value, value });
    Text text;
    text.SetDetails(details);
    for (int64_t i = 0; i < 100; ++i) {
        auto record = std::make_shared<Text>(text);
        inputData.AddRecord(record);
    }
    auto records = inputData.GetRecords();
    LOG_INFO(UDMF_TEST, "SetData023 inputData.size() = %{public}zu", records.size());
    UnifiedDataHelper::SetRootPath("/data/udmf_test/");
    auto status = UdmfClient::GetInstance().SetData(customOption, inputData, key);
    ASSERT_EQ(status, E_OK);

    QueryOption queryOption = { .key = key };
    UnifiedData outputData;
    status = UdmfClient::GetInstance().GetData(queryOption, outputData);
    ASSERT_EQ(status, E_OK);
    UnifiedDataHelper::SetRootPath("");

    LOG_INFO(UDMF_TEST, "SetData023 end.");
}

/**
* @tc.name: SetData024
* @tc.desc: Set over 200MB record of data with valid params and get data
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientTest, SetData024, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetData024 begin.");

    CustomOption customOption = { .intention = Intention::UD_INTENTION_DRAG };
    UnifiedData inputData;
    std::string key;
    UDDetails details;
    std::string value;
    int64_t maxSize = 512 * 1024;
    for (int64_t i = 0; i < maxSize; ++i) {
        value += "11";
    }
    details.insert({ value, value });
    Text text;
    text.SetDetails(details);
    for (int64_t i = 0; i < 101; ++i) {
        auto record = std::make_shared<Text>(text);
        inputData.AddRecord(record);
    }
    auto records = inputData.GetRecords();
    LOG_INFO(UDMF_TEST, "SetData024 inputData.size() = %{public}zu", records.size());

    UnifiedDataHelper::SetRootPath("/data/udmf_test/");
    auto status = UdmfClient::GetInstance().SetData(customOption, inputData, key);
    ASSERT_EQ(status, E_INVALID_PARAMETERS);
    UnifiedDataHelper::SetRootPath("");

    LOG_INFO(UDMF_TEST, "SetData024 end.");
}

/**
* @tc.name: GetSummary003
* @tc.desc: Get summary data
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientTest, GetSummary003, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetSummary003 begin.");

    CustomOption option1 = { .intention = Intention::UD_INTENTION_DRAG };
    UnifiedData data;
    std::string key;

    UDDetails details;
    details.insert({ "udmf_key", "udmf_value" });
    std::string value;
    int64_t maxSize = 512 * 1024;
    for (int64_t i = 0; i < maxSize; ++i) {
        value += "11";
    }
    details.insert({ value, value });

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

    UnifiedDataHelper::SetRootPath("/data/udmf_test/");
    auto status = UdmfClient::GetInstance().SetData(option1, data, key);
    ASSERT_EQ(status, E_OK);
    UnifiedDataHelper::SetRootPath("");

    QueryOption option2 = { .key = key };
    Summary summary;
    status = UdmfClient::GetInstance().GetSummary(option2, summary);

    auto size = record1->GetSize();
    size += record2->GetSize();

    ASSERT_EQ(status, E_OK);
    ASSERT_EQ(summary.totalSize, size);
    ASSERT_EQ(summary.summary["general.text"], record1->GetSize());
    ASSERT_EQ(summary.summary["general.plain-text"], record2->GetSize());

    LOG_INFO(UDMF_TEST, "GetSummary003 end.");
}

/**
* @tc.name: IsRemoteData
* @tc.desc: is remote data, result false: not remote data, true: remote data.
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientTest, IsRemoteData001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "IsRemoteData001 begin.");

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

    auto status = UdmfClient::GetInstance().SetData(option1, data, key);
    ASSERT_EQ(status, E_OK);

    QueryOption option2 = { .key = key };
    bool result = true;
    status = UdmfClient::GetInstance().IsRemoteData(option2, result);

    ASSERT_EQ(status, E_OK);
    ASSERT_EQ(result, false);

    LOG_INFO(UDMF_TEST, "IsRemoteData001 end.");
}

/**
* @tc.name: GetTypesLabels001
* @tc.desc: test GetTypesLabels
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientTest, GetTypesLabels001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetTypesLabels001 begin.");
    UnifiedData data;
    UDDetails details;
    details.insert({ "udmf_key", "udmf_value" });
    Text text;
    text.SetDetails(details);
    std::shared_ptr<UnifiedRecord> record1 = std::make_shared<Text>(text);
    PlainText plainText;
    plainText.SetDetails(details);
    std::shared_ptr<UnifiedRecord> record2 = std::make_shared<PlainText>(plainText);
    std::vector<std::shared_ptr<UnifiedRecord>> records = {record1, record2};
    data.AddRecords(records);

    std::vector<std::string> types = {"general.text", "general.plain-text"};
    ASSERT_EQ(data.GetTypesLabels(), types);
    ASSERT_EQ(data.HasType("general.text"), true);
    ASSERT_EQ(data.HasType("general.plain-text"), true);
    ASSERT_EQ(data.HasType("general.html"), false);
}
} // OHOS::Test