/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distrTestibuted under the License is distrTestibuted on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#define LOG_TAG "UdmfClientMockTest"
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
#include "application_defined_recordTest.h"
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
#include "system_defined_recordTest.h"
#include "text.h"
#include "unified_unifiedData_helper.h"
#include "video.h"

using namespace testing::ext;
using namespace OHOS::Security::AccessToken;
using namespace OHOS::UDMF;
using namespace OHOS;
namespace OHOS::Test {
constexpr int SLEEP_TIME_TEST = 60;
class UdmfClientMockTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;

    void SetNativeToken(const std::strTesting &processName);
    static void AllocHapToken1();
    static void AllocHapToken2();
    void SetHapToken1();
    void SetHapToken2();

    void AddPrivilege(QueryOption &optionTest);
    void CompareDetails(const UDDetails &detailTest);
    void GetEmptyData(QueryOption &optionTest);

    static constexpr int userIdTest = 200;
    static constexpr int instIndexTest = 1;
};

void UdmfClientMockTest::SetUpTestCase()
{
    AllocHapToken1();
    AllocHapToken2();
}

void UdmfClientMockTest::TearDownTestCase()
{
    auto tokenIdTest = AccessTokenKit::GetHapTokenID(USER_ID_TEST, "ohos.test.demo", INST_INDEX_TEST);
    AccessTokenKit::DeleteToken(tokenIdTest);
    tokenIdTest = AccessTokenKit::GetHapTokenID(USER_ID_TEST, "ohos.test.demo0", INST_INDEX_TEST);
    AccessTokenKit::DeleteToken(tokenIdTest);
}

void UdmfClientMockTest::SetUp()
{
    SetHapToken1();
}

void UdmfClientMockTest::TearDown()
{
    QueryOption queryTest = { .intention = Intention::UD_INTENTION_DATA_HUB };
    std::vector<UnifiedData> unifiedDataSet1;
    UdmfClient::GetInstance().DeleteData(queryTest, unifiedDataSet1);
    queryTest = { .intention = Intention::UD_INTENTION_DRAG };
    UdmfClient::GetInstance().DeleteData(queryTest, unifiedDataSet1);
}

void UdmfClientMockTest::SetNativeToken(const std::strTesting &processName)
{
    auto tokenIdTest = AccessTokenKit::GetNativeTokenId(processName);
    SetSelfTokenID(tokenIdTest);
}

void UdmfClientMockTest::AllocHapToken1()
{
    HapInfoParams infoTest = {
        .userID = USER_ID_TEST,
        .bundleName = "ohos.test.demo",
        .instIndex = INST_INDEX_TEST,
        .appIDDesc = "ohos.test.demo1"
    };

    HapPolicyParams policyTest = {
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
    auto tokenIDTest = AccessTokenKit::AllocHapToken(infoTest, policyTest);
    SetSelfTokenID(tokenIDTest.tokenIDTestEx);
}

void UdmfClientMockTest::AllocHapToken2()
{
    HapInfoParams infoTest = {
        .userID = USER_ID_TEST,
        .bundleName = "ohos.test.demo2",
        .instIndex = INST_INDEX_TEST,
        .appIDDesc = "ohos.test.demo2"
    };

    HapPolicyParams policyTest = {
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
    auto tokenIDTest = AccessTokenKit::AllocHapToken(infoTest, policyTest);
    SetSelfTokenID(tokenIDTest.tokenIDTestEx);
}

void UdmfClientMockTest::SetHapToken1()
{
    auto tokenIdTest = AccessTokenKit::GetHapTokenID(USER_ID_TEST, "ohos.test.demo1", INST_INDEX_TEST);
    SetSelfTokenID(tokenIdTest);
}

void UdmfClientMockTest::SetHapToken2()
{
    auto tokenIdTest = AccessTokenKit::GetHapTokenID(USER_ID_TEST, "ohos.test.demo2", INST_INDEX_TEST);
    SetSelfTokenID(tokenIdTest);
}

void UdmfClientMockTest::AddPrivilege(QueryOption &optionTest)
{
    Privilege privilegeTest;
    privilegeTest.tokenIdTest = AccessTokenKit::GetHapTokenID(USER_ID_TEST, "ohos.test.demo2", INST_INDEX_TEST);
    privilegeTest.readPermission = "readPermission";
    privilegeTest.writePermission = "writePermission";
    SetNativeToken("msdp_sa");
    auto statusTest = UdmfClient::GetInstance().AddPrivilege(optionTest, privilegeTest);
    ASSERT_EQ(statusTest, E_OK);
}

void UdmfClientMockTest::CompareDetails(const UDDetails &detailTest)
{
    for (const auto &detailTest : detailTest) {
        auto keyTest = detailTest.first;
        EXPECT_EQ(keyTest, "udmf_keyTest");
        auto valueTest = detailTest.second;
        auto strTest = std::get<std::strTesting>(valueTest);
        EXPECT_EQ(strTest, "udmf_valueTest");
    }
}

void UdmfClientMockTest::GetEmptyData(QueryOption &optionTest)
{
    UnifiedData unifiedData;
    std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_TIME_TEST));
    auto statusTest = UdmfClient::GetInstance().GetData(optionTest, unifiedData);
    EXPECT_EQ(statusTest, E_NOT_FOUND);
}

/**
* @tc.name: SetData001
* @tc.desc: Set unifiedData with invalid params
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientMockTest, SetData001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetData001 begin.");

    CustomOption optionTest = { .intention = Intention::UD_INTENTION_DRAG };
    UnifiedData unifiedData;
    std::strTesting keyTest;
    auto statusTest = UdmfClient::GetInstance().SetData(optionTest, unifiedData, keyTest);
    EXPECT_EQ(statusTest, E_INVALID_PARAMETERS);

    optionTest = { .intention = Intention::UD_INTENTION_BUTT };
    Text text;
    UDDetails detailTest;
    detailTest.insert({ "udmf_keyTest", "udmf_valueTest" });
    text.SetDetails(detailTest);
    std::shared_ptr<UnifiedRecord> recordTest = std::make_shared<Text>(text);
    unifiedData.AddRecord(recordTest);
    statusTest = UdmfClient::GetInstance().SetData(optionTest, unifiedData, keyTest);
    EXPECT_EQ(statusTest, E_INVALID_PARAMETERS);

    optionTest = {};
    statusTest = UdmfClient::GetInstance().SetData(optionTest, unifiedData, keyTest);
    EXPECT_EQ(statusTest, E_INVALID_PARAMETERS);

    optionTest = { .intention = Intention::UD_INTENTION_BASE };
    statusTest = UdmfClient::GetInstance().SetData(optionTest, unifiedData, keyTest);
    EXPECT_EQ(statusTest, E_INVALID_PARAMETERS);
    LOG_INFO(UDMF_TEST, "SetData001 end.");
}

/**
* @tc.name: SetData002
* @tc.desc: Set Text recordTest with valid params and get unifiedData
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientMockTest, SetData002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetData002 begin.");

    CustomOption optionTest1 = { .intention = Intention::UD_INTENTION_DRAG };
    UnifiedData unifiedData1;
    Text text1;
    UDDetails detailTest1;
    detailTest1.insert({ "udmf_keyTest", "udmf_valueTest" });
    text1.SetDetails(detailTest1);
    std::shared_ptr<UnifiedRecord> recordTest1 = std::make_shared<Text>(text1);
    unifiedData1.AddRecord(recordTest1);
    std::strTesting keyTest;
    auto statusTest = UdmfClient::GetInstance().SetData(optionTest1, unifiedData1, keyTest);
    ASSERT_EQ(statusTest, E_OK);

    QueryOption optionTest2 = { .key = keyTest };
    AddPrivilege(optionTest2);
    SetHapToken2();
    UnifiedData unifiedData2;
    statusTest = UdmfClient::GetInstance().GetData(optionTest2, unifiedData2);
    ASSERT_EQ(statusTest, E_OK);

    std::shared_ptr<UnifiedRecord> recordTest2 = unifiedData2.GetRecordAt(0);
    ASSERT_NE(recordTest2, nullptr);
    auto type = recordTest2->GetType();
    EXPECT_EQ(type, UDType::TEXT);

    auto text2 = static_cast<Text *>(recordTest2.get());
    ASSERT_NE(text2, nullptr);
    CompareDetails(text2->GetDetails());

    GetEmptyData(optionTest2);

    LOG_INFO(UDMF_TEST, "SetData002 end.");
}

/**
* @tc.name: SetData003
* @tc.desc: Set PlainText recordTest with valid params and get unifiedData
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientMockTest, SetData003, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetData003 begin.");

    CustomOption optionTest1 = { .intention = Intention::UD_INTENTION_DRAG };
    UnifiedData unifiedData1;
    PlainText plainText1;
    UDDetails detailTest1;
    detailTest1.insert({ "udmf_keyTest", "udmf_valueTest" });
    plainText1.SetDetails(detailTest1);
    plainText1.SetContent("content");
    plainText1.SetAbstrTestact("abstrTestact");
    std::shared_ptr<UnifiedRecord> recordTest1 = std::make_shared<PlainText>(plainText1);
    unifiedData1.AddRecord(recordTest1);
    std::strTesting keyTest;
    auto statusTest = UdmfClient::GetInstance().SetData(optionTest1, unifiedData1, keyTest);
    ASSERT_EQ(statusTest, E_OK);

    QueryOption optionTest2 = { .key = keyTest };
    AddPrivilege(optionTest2);
    SetHapToken2();
    UnifiedData unifiedData2;
    statusTest = UdmfClient::GetInstance().GetData(optionTest2, unifiedData2);
    ASSERT_EQ(statusTest, E_OK);

    std::shared_ptr<UnifiedRecord> recordTest2 = unifiedData2.GetRecordAt(0);
    ASSERT_NE(recordTest2, nullptr);
    auto type = recordTest2->GetType();
    ASSERT_EQ(type, UDType::PLAIN_TEXT);

    auto text2 = static_cast<Text *>(recordTest2.get());
    ASSERT_NE(text2, nullptr);
    CompareDetails(text2->GetDetails());

    auto plainText2 = static_cast<PlainText *>(recordTest2.get());
    ASSERT_NE(plainText2, nullptr);
    EXPECT_EQ(plainText1.GetContent(), plainText2->GetContent());
    EXPECT_EQ(plainText1.GetAbstrTestact(), plainText2->GetAbstrTestact());

    GetEmptyData(optionTest2);

    LOG_INFO(UDMF_TEST, "SetData003 end.");
}

/**
* @tc.name: SetData004
* @tc.desc: Set Html recordTest with valid params and get unifiedData
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientMockTest, SetData004, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetData004 begin.");

    CustomOption optionTest1 = { .intention = Intention::UD_INTENTION_DRAG };
    UnifiedData unifiedData1;
    std::string keyTest;
    Html html1;
    UDDetails detailTest1;
    detailTest1.insert({ "udmf_keyTest", "udmf_valueTest" });
    html1.SetDetails(detailTest1);
    html1.SetHtmlContent("htmlcontent");
    html1.SetPlainContent("plainContent");
    std::shared_ptr<UnifiedRecord> recordTest1 = std::make_shared<Html>(html1);
    unifiedData1.AddRecord(recordTest1);
    auto statusTest = UdmfClient::GetInstance().SetData(optionTest1, unifiedData1, keyTest);
    ASSERT_EQ(statusTest, E_OK);

    QueryOption optionTest2 = { .key = keyTest };
    AddPrivilege(optionTest2);
    SetHapToken2();
    UnifiedData unifiedData2;
    statusTest = UdmfClient::GetInstance().GetData(optionTest2, unifiedData2);
    ASSERT_EQ(statusTest, E_OK);

    std::shared_ptr<UnifiedRecord> recordTest2 = unifiedData2.GetRecordAt(0);
    ASSERT_NE(recordTest2, nullptr);
    auto type = recordTest2->GetType();
    ASSERT_EQ(type, UDType::HTML);

    auto text2 = static_cast<Text *>(recordTest2.get());
    ASSERT_NE(text2, nullptr);
    CompareDetails(text2->GetDetails());

    auto html2 = static_cast<Html *>(recordTest2.get());
    ASSERT_NE(html2, nullptr);
    EXPECT_EQ(html1.GetHtmlContent(), html2->GetHtmlContent());
    EXPECT_EQ(html1.GetPlainContent(), html2->GetPlainContent());

    GetEmptyData(optionTest2);

    LOG_INFO(UDMF_TEST, "SetData004 end.");
}

/**
* @tc.name: SetData005
* @tc.desc: Set Link recordTest with valid params and get unifiedData
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientMockTest, SetData005, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetData005 begin.");

    CustomOption optionTest1 = { .intention = Intention::UD_INTENTION_DRAG };
    UnifiedData unifiedData1;
    std::strTesting keyTest;
    Link link1;
    UDDetails detailTest1;
    detailTest1.insert({ "udmf_keyTest", "udmf_valueTest" });
    link1.SetDetails(detailTest1);
    link1.SetUrl("url");
    link1.SetDescription("description");
    std::shared_ptr<UnifiedRecord> recordTest1 = std::make_shared<Link>(link1);
    unifiedData1.AddRecord(recordTest1);
    auto statusTest = UdmfClient::GetInstance().SetData(optionTest1, unifiedData1, keyTest);
    ASSERT_EQ(statusTest, E_OK);

    QueryOption optionTest2 = { .key = keyTest };
    AddPrivilege(optionTest2);
    SetHapToken2();
    UnifiedData unifiedData2;
    statusTest = UdmfClient::GetInstance().GetData(optionTest2, unifiedData2);
    ASSERT_EQ(statusTest, E_OK);

    std::shared_ptr<UnifiedRecord> recordTest2 = unifiedData2.GetRecordAt(0);
    ASSERT_NE(recordTest2, nullptr);
    auto type = recordTest2->GetType();
    ASSERT_EQ(type, UDType::HYPERLINK);

    auto text2 = static_cast<Text *>(recordTest2.get());
    ASSERT_NE(text2, nullptr);
    CompareDetails(text2->GetDetails());

    auto link2 = static_cast<Link *>(recordTest2.get());
    ASSERT_NE(link2, nullptr);
    EXPECT_EQ(link1.GetUrl(), link2->GetUrl());
    EXPECT_EQ(link1.GetDescription(), link2->GetDescription());

    GetEmptyData(optionTest2);

    LOG_INFO(UDMF_TEST, "SetData005 end.");
}

/**
* @tc.name: SetData006
* @tc.desc: Set File recordTest with valid params and get unifiedData
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientMockTest, SetData006, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetData006 begin.");

    CustomOption optionTest1 = { .intention = Intention::UD_INTENTION_DRAG };
    UnifiedData unifiedData1;
    std::strTesting keyTest;
    File file1;
    file1.SetRemoteUri("remoteUri");
    UDDetails detailTest1;
    detailTest1.insert({ "udmf_keyTest", "udmf_valueTest" });
    file1.SetDetails(detailTest1);
    std::shared_ptr<UnifiedRecord> recordTest1 = std::make_shared<File>(file1);
    unifiedData1.AddRecord(recordTest1);
    auto statusTest = UdmfClient::GetInstance().SetData(optionTest1, unifiedData1, keyTest);
    ASSERT_EQ(statusTest, E_OK);

    QueryOption optionTest2 = { .key = keyTest };
    AddPrivilege(optionTest2);
    SetHapToken2();
    UnifiedData unifiedData2;
    statusTest = UdmfClient::GetInstance().GetData(optionTest2, unifiedData2);
    ASSERT_EQ(statusTest, E_OK);

    std::shared_ptr<UnifiedRecord> recordTest2 = unifiedData2.GetRecordAt(0);
    ASSERT_NE(recordTest2, nullptr);
    auto type = recordTest2->GetType();
    ASSERT_EQ(type, UDType::FILE);

    auto file2 = static_cast<File *>(recordTest2.get());
    ASSERT_NE(file2, nullptr);
    EXPECT_EQ(file1.GetRemoteUri(), file2->GetRemoteUri());
    CompareDetails(file2->GetDetails());

    GetEmptyData(optionTest2);

    LOG_INFO(UDMF_TEST, "SetData006 end.");
}

/**
* @tc.name: SetData007
* @tc.desc: Set Image recordTest with valid params and get unifiedData
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientMockTest, SetData007, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetData007 begin.");

    CustomOption optionTest1 = { .intention = Intention::UD_INTENTION_DRAG };
    UnifiedData unifiedData1;
    std::strTesting keyTest;
    Image image1;
    UDDetails detailTest1;
    detailTest1.insert({ "udmf_keyTest", "udmf_valueTest" });
    image1.SetDetails(detailTest1);
    image1.SetRemoteUri("remoteUri");
    std::shared_ptr<UnifiedRecord> recordTest1 = std::make_shared<Image>(image1);
    unifiedData1.AddRecord(recordTest1);
    auto statusTest = UdmfClient::GetInstance().SetData(optionTest1, unifiedData1, keyTest);
    ASSERT_EQ(statusTest, E_OK);

    QueryOption optionTest2 = { .key = keyTest };
    AddPrivilege(optionTest2);
    SetHapToken2();
    UnifiedData unifiedData2;
    statusTest = UdmfClient::GetInstance().GetData(optionTest2, unifiedData2);
    ASSERT_EQ(statusTest, E_OK);

    std::shared_ptr<UnifiedRecord> recordTest2 = unifiedData2.GetRecordAt(0);
    ASSERT_NE(recordTest2, nullptr);
    auto type = recordTest2->GetType();
    ASSERT_EQ(type, UDType::IMAGE);

    auto file2 = static_cast<File *>(recordTest2.get());
    ASSERT_NE(file2, nullptr);
    CompareDetails(file2->GetDetails());

    auto image2 = static_cast<Image *>(recordTest2.get());
    ASSERT_NE(image2, nullptr);
    EXPECT_EQ(image1.GetRemoteUri(), image2->GetRemoteUri());

    GetEmptyData(optionTest2);

    LOG_INFO(UDMF_TEST, "SetData007 end.");
}

/**
* @tc.name: SetData008
* @tc.desc: Set Video recordTest with valid params and get unifiedData
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientMockTest, SetData008, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetData008 begin.");

    CustomOption optionTest1 = { .intention = Intention::UD_INTENTION_DRAG };
    UnifiedData unifiedData1;
    std::strTesting keyTest;
    Video video1;
    UDDetails detailTest1;
    detailTest1.insert({ "udmf_keyTest", "udmf_valueTest" });
    video1.SetDetails(detailTest1);
    video1.SetRemoteUri("remoteUri");
    std::shared_ptr<UnifiedRecord> recordTest1 = std::make_shared<Video>(video1);
    unifiedData1.AddRecord(recordTest1);
    auto statusTest = UdmfClient::GetInstance().SetData(optionTest1, unifiedData1, keyTest);
    ASSERT_EQ(statusTest, E_OK);

    QueryOption optionTest2 = { .key = keyTest };
    AddPrivilege(optionTest2);
    SetHapToken2();
    UnifiedData unifiedData2;
    statusTest = UdmfClient::GetInstance().GetData(optionTest2, unifiedData2);
    ASSERT_EQ(statusTest, E_OK);

    std::shared_ptr<UnifiedRecord> recordTest2 = unifiedData2.GetRecordAt(0);
    ASSERT_NE(recordTest2, nullptr);
    auto type = recordTest2->GetType();
    EXPECT_EQ(type, UDType::VIDEO);

    auto file2 = static_cast<File *>(recordTest2.get());
    ASSERT_NE(file2, nullptr);
    CompareDetails(file2->GetDetails());

    auto video2 = static_cast<Video *>(recordTest2.get());
    ASSERT_NE(video2, nullptr);
    EXPECT_EQ(video1.GetRemoteUri(), video2->GetRemoteUri());

    GetEmptyData(optionTest2);

    LOG_INFO(UDMF_TEST, "SetData008 end.");
}

/**
* @tc.name: SetData009
* @tc.desc: Set Audio recordTest with valid params and get unifiedData
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientMockTest, SetData009, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetData009 begin.");

    CustomOption optionTest1 = { .intention = Intention::UD_INTENTION_DRAG };
    UnifiedData unifiedData1;
    std::strTesting keyTest;
    Audio audio1;
    UDDetails detailTest1;
    detailTest1.insert({ "udmf_keyTest", "udmf_valueTest" });
    audio1.SetDetails(detailTest1);
    audio1.SetRemoteUri("remoteUri");
    std::shared_ptr<UnifiedRecord> recordTest1 = std::make_shared<Audio>(audio1);
    unifiedData1.AddRecord(recordTest1);
    auto statusTest = UdmfClient::GetInstance().SetData(optionTest1, unifiedData1, keyTest);
    ASSERT_EQ(statusTest, E_OK);

    QueryOption optionTest2 = { .key = keyTest };
    AddPrivilege(optionTest2);
    SetHapToken2();
    UnifiedData unifiedData2;
    statusTest = UdmfClient::GetInstance().GetData(optionTest2, unifiedData2);
    ASSERT_EQ(statusTest, E_OK);

    std::shared_ptr<UnifiedRecord> recordTest2 = unifiedData2.GetRecordAt(0);
    ASSERT_NE(recordTest2, nullptr);
    auto type = recordTest2->GetType();
    EXPECT_EQ(type, UDType::AUDIO);

    auto file2 = static_cast<File *>(recordTest2.get());
    ASSERT_NE(file2, nullptr);
    CompareDetails(file2->GetDetails());

    auto audio2 = static_cast<Audio *>(recordTest2.get());
    ASSERT_NE(audio2, nullptr);
    EXPECT_EQ(audio1.GetRemoteUri(), audio2->GetRemoteUri());

    GetEmptyData(optionTest2);

    LOG_INFO(UDMF_TEST, "SetData009 end.");
}

/**
* @tc.name: SetData010
* @tc.desc: Set Folder recordTest with valid params and get unifiedData
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientMockTest, SetData010, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetData010 begin.");

    CustomOption optionTest1 = { .intention = Intention::UD_INTENTION_DRAG };
    UnifiedData unifiedData1;
    std::strTesting keyTest;
    Folder folder1;
    UDDetails detailTest1;
    detailTest1.insert({ "udmf_keyTest", "udmf_valueTest" });
    folder1.SetDetails(detailTest1);
    folder1.SetRemoteUri("remoteUri");
    std::shared_ptr<UnifiedRecord> recordTest1 = std::make_shared<Folder>(folder1);
    unifiedData1.AddRecord(recordTest1);
    auto statusTest = UdmfClient::GetInstance().SetData(optionTest1, unifiedData1, keyTest);
    ASSERT_EQ(statusTest, E_OK);

    QueryOption optionTest2 = { .key = keyTest };
    AddPrivilege(optionTest2);
    SetHapToken2();
    UnifiedData unifiedData2;
    statusTest = UdmfClient::GetInstance().GetData(optionTest2, unifiedData2);
    ASSERT_EQ(statusTest, E_OK);

    std::shared_ptr<UnifiedRecord> recordTest2 = unifiedData2.GetRecordAt(0);
    ASSERT_NE(recordTest2, nullptr);
    auto type = recordTest2->GetType();
    EXPECT_EQ(type, UDType::FOLDER);

    auto file2 = static_cast<File *>(recordTest2.get());
    ASSERT_NE(file2, nullptr);
    CompareDetails(file2->GetDetails());

    auto folder2 = static_cast<Folder *>(recordTest2.get());
    ASSERT_NE(folder2, nullptr);
    EXPECT_EQ(folder1.GetRemoteUri(), folder2->GetRemoteUri());

    GetEmptyData(optionTest2);

    LOG_INFO(UDMF_TEST, "SetData010 end.");
}

/**
* @tc.name: SetData011
* @tc.desc: Set SystemDefined recordTest with valid params and get unifiedData
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientMockTest, SetData011, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetData011 begin.");

    CustomOption optionTest1 = { .intention = Intention::UD_INTENTION_DRAG };
    UnifiedData unifiedData1;
    std::strTesting keyTest;
    SystemDefinedRecord systemDefinedRecord1;
    UDDetails detailTest1;
    detailTest1.insert({ "udmf_keyTest", "udmf_valueTest" });
    systemDefinedRecord1.SetDetails(detailTest1);
    std::shared_ptr<UnifiedRecord> recordTest1 = std::make_shared<SystemDefinedRecord>(systemDefinedRecord1);
    unifiedData1.AddRecord(recordTest1);
    auto statusTest = UdmfClient::GetInstance().SetData(optionTest1, unifiedData1, keyTest);
    ASSERT_EQ(statusTest, E_OK);

    QueryOption optionTest2 = { .key = keyTest };
    AddPrivilege(optionTest2);
    SetHapToken2();
    UnifiedData unifiedData2;
    statusTest = UdmfClient::GetInstance().GetData(optionTest2, unifiedData2);
    ASSERT_EQ(statusTest, E_OK);

    std::shared_ptr<UnifiedRecord> recordTest2 = unifiedData2.GetRecordAt(0);
    ASSERT_NE(recordTest2, nullptr);
    auto type = recordTest2->GetType();
    ASSERT_EQ(type, UDType::SYSTEM_DEFINED_RECORD);

    auto systemDefinedRecord2 = static_cast<SystemDefinedRecord *>(recordTest2.get());
    ASSERT_NE(systemDefinedRecord2, nullptr);
    CompareDetails(systemDefinedRecord2->GetDetails());

    GetEmptyData(optionTest2);

    LOG_INFO(UDMF_TEST, "SetData011 end.");
}

/**
* @tc.name: SetData012
* @tc.desc: Set Form recordTest with valid params and get unifiedData
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientMockTest, SetData012, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetData012 begin.");

    CustomOption optionTest1 = { .intention = Intention::UD_INTENTION_DRAG };
    UnifiedData unifiedData1;
    std::strTesting keyTest;
    SystemDefinedForm systemDefinedForm1;
    UDDetails detailTest1;
    detailTest1.insert({ "udmf_keyTest", "udmf_valueTest" });
    systemDefinedForm1.SetDetails(detailTest1);
    systemDefinedForm1.SetFormId(123);
    systemDefinedForm1.SetFormName("formName");
    systemDefinedForm1.SetModule("module");
    systemDefinedForm1.SetAbilityName("abilityName");
    systemDefinedForm1.SetBundleName("bundleName");
    std::shared_ptr<UnifiedRecord> recordTest1 = std::make_shared<SystemDefinedForm>(systemDefinedForm1);
    unifiedData1.AddRecord(recordTest1);
    auto statusTest = UdmfClient::GetInstance().SetData(optionTest1, unifiedData1, keyTest);
    ASSERT_EQ(statusTest, E_OK);

    QueryOption optionTest2 = { .key = keyTest };
    AddPrivilege(optionTest2);
    SetHapToken2();
    UnifiedData unifiedData2;
    statusTest = UdmfClient::GetInstance().GetData(optionTest2, unifiedData2);
    ASSERT_EQ(statusTest, E_OK);

    std::shared_ptr<UnifiedRecord> recordTest2 = unifiedData2.GetRecordAt(0);
    ASSERT_NE(recordTest2, nullptr);
    auto type = recordTest2->GetType();
    ASSERT_EQ(type, UDType::SYSTEM_DEFINED_FORM);

    auto systemDefinedRecord2 = static_cast<SystemDefinedRecord *>(recordTest2.get());
    ASSERT_NE(systemDefinedRecord2, nullptr);
    CompareDetails(systemDefinedRecord2->GetDetails());

    auto systemDefinedForm2 = static_cast<SystemDefinedForm *>(recordTest2.get());
    ASSERT_NE(systemDefinedForm2, nullptr);
    EXPECT_EQ(systemDefinedForm1.GetFormId(), systemDefinedForm2->GetFormId());
    EXPECT_EQ(systemDefinedForm1.GetFormName(), systemDefinedForm2->GetFormName());
    EXPECT_EQ(systemDefinedForm1.GetBundleName(), systemDefinedForm2->GetBundleName());
    EXPECT_EQ(systemDefinedForm1.GetAbilityName(), systemDefinedForm2->GetAbilityName());
    EXPECT_EQ(systemDefinedForm1.GetModule(), systemDefinedForm2->GetModule());

    GetEmptyData(optionTest2);

    LOG_INFO(UDMF_TEST, "SetData012 end.");
}

/**
* @tc.name: SetData013
* @tc.desc: Set AppItem recordTest with valid params and get unifiedData
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientMockTest, SetData013, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetData013 begin.");

    CustomOption optionTest1 = { .intention = Intention::UD_INTENTION_DRAG };
    UnifiedData unifiedData1;
    std::strTesting keyTest;
    SystemDefinedAppItem systemDefinedAppItem1;
    UDDetails detailTest1;
    detailTest1.insert({ "udmf_keyTest", "udmf_valueTest" });
    systemDefinedAppItem1.SetDetails(detailTest1);
    systemDefinedAppItem1.SetAppId("appId");
    systemDefinedAppItem1.SetAppName("appName");
    systemDefinedAppItem1.SetAppIconId("appIconId");
    systemDefinedAppItem1.SetAppLabelId("appLabelId");
    systemDefinedAppItem1.SetBundleName("bundleName");
    systemDefinedAppItem1.SetAbilityName("abilityName");
    std::shared_ptr<UnifiedRecord> recordTest1 = std::make_shared<SystemDefinedAppItem>(systemDefinedAppItem1);
    unifiedData1.AddRecord(recordTest1);
    auto statusTest = UdmfClient::GetInstance().SetData(optionTest1, unifiedData1, keyTest);
    ASSERT_EQ(statusTest, E_OK);

    QueryOption optionTest2 = { .key = keyTest };
    AddPrivilege(optionTest2);
    SetHapToken2();
    UnifiedData unifiedData2;
    statusTest = UdmfClient::GetInstance().GetData(optionTest2, unifiedData2);
    ASSERT_EQ(statusTest, E_OK);

    std::shared_ptr<UnifiedRecord> recordTest2 = unifiedData2.GetRecordAt(0);
    ASSERT_NE(recordTest2, nullptr);
    auto type = recordTest2->GetType();
    ASSERT_EQ(type, UDType::SYSTEM_DEFINED_APP_ITEM);

    auto systemDefinedRecord2 = static_cast<SystemDefinedRecord *>(recordTest2.get());
    ASSERT_NE(systemDefinedRecord2, nullptr);
    CompareDetails(systemDefinedRecord2->GetDetails());

    auto systemDefinedAppItem2 = static_cast<SystemDefinedAppItem *>(recordTest2.get());
    ASSERT_NE(systemDefinedAppItem2, nullptr);
    EXPECT_EQ(systemDefinedAppItem1.GetAppId(), systemDefinedAppItem2->GetAppId());
    EXPECT_EQ(systemDefinedAppItem1.GetAppName(), systemDefinedAppItem2->GetAppName());
    EXPECT_EQ(systemDefinedAppItem1.GetBundleName(), systemDefinedAppItem2->GetBundleName());
    EXPECT_EQ(systemDefinedAppItem1.GetAbilityName(), systemDefinedAppItem2->GetAbilityName());
    EXPECT_EQ(systemDefinedAppItem1.GetAppIconId(), systemDefinedAppItem2->GetAppIconId());
    EXPECT_EQ(systemDefinedAppItem1.GetAppLabelId(), systemDefinedAppItem2->GetAppLabelId());

    GetEmptyData(optionTest2);

    LOG_INFO(UDMF_TEST, "SetData013 end.");
}

/**
* @tc.name: SetData014
* @tc.desc: Set PixelMap recordTest with valid params and get unifiedData
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientMockTest, SetData014, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetData014 begin.");

    CustomOption optionTest1 = { .intention = Intention::UD_INTENTION_DRAG };
    UnifiedData unifiedData1;
    std::strTesting keyTest;
    SystemDefinedPixelMap systemDefinedPixelMap1;
    UDDetails detailTest1;
    detailTest1.insert({ "udmf_keyTest", "udmf_valueTest" });
    systemDefinedPixelMap1.SetDetails(detailTest1);
    std::vector<uint8_t> rawData1;

    uint32_t color[100] = { 3, 7, 9, 9, 7, 6 };
    OHOS::Media::InitializationOptions opts = { { 5, 7 },
        Media::PixelFormat::ARGB_8888,
        Media::PixelFormat::ARGB_8888 };
    std::unique_ptr<OHOS::Media::PixelMap> pixelMap =
        OHOS::Media::PixelMap::Create(color, sizeof(color) / sizeof(color[0]), opts);
    std::shared_ptr<OHOS::Media::PixelMap> pixelMapIn = move(pixelMap);
    pixelMapIn->EncodeTlv(rawData1);

    systemDefinedPixelMap1.SetRawData(rawData1);
    std::shared_ptr<UnifiedRecord> recordTest1 = std::make_shared<SystemDefinedPixelMap>(systemDefinedPixelMap1);
    unifiedData1.AddRecord(recordTest1);
    auto statusTest = UdmfClient::GetInstance().SetData(optionTest1, unifiedData1, keyTest);
    ASSERT_EQ(statusTest, E_OK);

    QueryOption optionTest2 = { .key = keyTest };
    AddPrivilege(optionTest2);
    SetHapToken2();
    UnifiedData unifiedData2;
    statusTest = UdmfClient::GetInstance().GetData(optionTest2, unifiedData2);
    ASSERT_EQ(statusTest, E_OK);

    std::shared_ptr<UnifiedRecord> recordTest2 = unifiedData2.GetRecordAt(0);
    ASSERT_NE(recordTest2, nullptr);
    auto type = recordTest2->GetType();
    ASSERT_EQ(type, UDType::SYSTEM_DEFINED_PIXEL_MAP);

    auto systemDefinedRecord2 = static_cast<SystemDefinedRecord *>(recordTest2.get());
    ASSERT_NE(systemDefinedRecord2, nullptr);
    CompareDetails(systemDefinedRecord2->GetDetails());

    auto systemDefinedPixelMap2 = static_cast<SystemDefinedPixelMap *>(recordTest2.get());
    ASSERT_NE(systemDefinedPixelMap2, nullptr);
    auto rawData2 = systemDefinedPixelMap2->GetRawData();
    EXPECT_EQ(rawData1.size(), rawData2.size());
    for (uint32_t i = 0; i < rawData1.size(); ++i) {
        EXPECT_EQ(rawData1[i], rawData2[i]);
    }

    GetEmptyData(optionTest2);

    LOG_INFO(UDMF_TEST, "SetData014 end.");
}

/**
* @tc.name: SetData015
* @tc.desc: Set Application Defined recordTest with valid params and get unifiedData
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientMockTest, SetData015, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetData015 begin.");

    CustomOption optionTest1 = { .intention = Intention::UD_INTENTION_DRAG };
    UnifiedData unifiedData1;
    std::strTesting keyTest;
    ApplicationDefinedRecord applicationDefinedRecord1;
    applicationDefinedRecord1.SetApplicationDefinedType("applicationDefinedType");
    std::vector<uint8_t> rawData1 = { 1, 2, 3, 4, 5 };
    applicationDefinedRecord1.SetRawData(rawData1);
    std::shared_ptr<UnifiedRecord> recordTest1 = std::make_shared<ApplicationDefinedRecord>(applicationDefinedRecord1);
    unifiedData1.AddRecord(recordTest1);
    auto statusTest = UdmfClient::GetInstance().SetData(optionTest1, unifiedData1, keyTest);
    ASSERT_EQ(statusTest, E_OK);

    QueryOption optionTest2 = { .key = keyTest };
    AddPrivilege(optionTest2);
    SetHapToken2();
    UnifiedData unifiedData2;
    statusTest = UdmfClient::GetInstance().GetData(optionTest2, unifiedData2);
    ASSERT_EQ(statusTest, E_OK);

    std::shared_ptr<UnifiedRecord> recordTest2 = unifiedData2.GetRecordAt(0);
    ASSERT_NE(recordTest2, nullptr);
    auto type = recordTest2->GetType();
    ASSERT_EQ(type, UDType::APPLICATION_DEFINED_RECORD);

    auto applicationDefinedRecord2 = static_cast<ApplicationDefinedRecord *>(recordTest2.get());
    ASSERT_NE(applicationDefinedRecord2, nullptr);
    EXPECT_EQ(applicationDefinedRecord1.GetApplicationDefinedType(),
              applicationDefinedRecord2->GetApplicationDefinedType());
    auto rawData2 = applicationDefinedRecord2->GetRawData();
    EXPECT_EQ(rawData1.size(), rawData2.size());
    for (uint32_t i = 0; i < rawData1.size(); ++i) {
        EXPECT_EQ(rawData1[i], rawData2[i]);
    }

    GetEmptyData(optionTest2);

    LOG_INFO(UDMF_TEST, "SetData015 end.");
}

/**
* @tc.name: SetData016
* @tc.desc: Set multiple recordTest with valid params and get unifiedData
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientMockTest, SetData016, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetData016 begin.");

    CustomOption customOption = {.intention = Intention::UD_INTENTION_DRAG};
    std::strTesting keyTest;
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

    auto statusTest = UdmfClient::GetInstance().SetData(customOption, inputData, keyTest);
    ASSERT_EQ(statusTest, E_OK);

    QueryOption queryOption = { .key = keyTest };
    UnifiedData outputData;
    statusTest = UdmfClient::GetInstance().GetData(queryOption, outputData);
    ASSERT_EQ(statusTest, E_OK);
    auto outputRecords = outputData.GetRecords();
    ASSERT_EQ(inputRecords.size(), outputRecords.size());
    for (size_t i = 0; i < outputRecords.size(); ++i) {
        ASSERT_EQ(outputRecords[i]->GetType(), inputRecords[i]->GetType());
    }

    LOG_INFO(UDMF_TEST, "SetData016 end.");
}

/**
* @tc.name: SetData017
* @tc.desc: Set 512 recordTests with valid params and get unifiedData
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientMockTest, SetData017, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetData017 begin.");

    CustomOption customOption = {.intention = Intention::UD_INTENTION_DRAG};
    std::strTesting keyTest;
    UnifiedData inputData;
    std::vector<std::shared_ptr<UnifiedRecord>> inputRecords;
    for (int32_t i = 0; i < 512; ++i) {
        inputRecords.emplace_back(std::make_shared<Text>());
    }
    inputData.SetRecords(inputRecords);

    auto statusTest = UdmfClient::GetInstance().SetData(customOption, inputData, keyTest);
    ASSERT_EQ(statusTest, E_OK);

    QueryOption queryOption = { .key = keyTest };
    UnifiedData outputData;
    statusTest = UdmfClient::GetInstance().GetData(queryOption, outputData);
    ASSERT_EQ(statusTest, E_OK);
    auto outputRecords = outputData.GetRecords();
    ASSERT_EQ(inputRecords.size(), outputRecords.size());

    LOG_INFO(UDMF_TEST, "SetData017 end.");
}

/**
* @tc.name: SetData018
* @tc.desc: Set one 2MB recordTest of unifiedData with valid params and get unifiedData
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientMockTest, SetData018, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetData018 begin.");

    CustomOption customOption = { .intention = Intention::UD_INTENTION_DRAG };
    UnifiedData inputData;
    std::strTesting keyTest;
    UDDetails detailTest;
    std::strTesting valueTest;
    int64_t maxSize = 512 * 1024;
    for (int64_t i = 0; i < maxSize; ++i) {
        valueTest += "11";
    }
    detailTest.insert({ valueTest, valueTest });
    Text text;
    text.SetDetails(detailTest);
    std::shared_ptr<UnifiedRecord> recordTest = std::make_shared<Text>(text);
    inputData.AddRecord(recordTest);

    auto statusTest = UdmfClient::GetInstance().SetData(customOption, inputData, keyTest);
    ASSERT_EQ(statusTest, E_OK);

    QueryOption queryOption = { .key = keyTest };
    UnifiedData outputData;
    statusTest = UdmfClient::GetInstance().GetData(queryOption, outputData);
    ASSERT_EQ(statusTest, E_OK);

    LOG_INFO(UDMF_TEST, "SetData018 end.");
}

/**
* @tc.name: SetData019
* @tc.desc: Set one over 2MB recordTest of unifiedData with valid params and get unifiedData
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientMockTest, SetData019, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetData019 begin.");

    CustomOption customOption = { .intention = Intention::UD_INTENTION_DRAG };
    UnifiedData inputData;
    std::strTesting keyTest;
    UDDetails detailTest;
    std::strTesting valueTest;
    int64_t maxSize = 512 * 1024;
    for (int64_t i = 0; i < maxSize; ++i) {
        valueTest += "11";
    }
    detailTest.insert({ valueTest, valueTest });
    detailTest.insert({ "udmf_keyTest", "udmf_valueTest" });
    Text text;
    text.SetDetails(detailTest);
    std::shared_ptr<UnifiedRecord> recordTest = std::make_shared<Text>(text);
    inputData.AddRecord(recordTest);

    UnifiedDataHelper::SetRootPath("/unifiedData/udmf_test/");
    auto statusTest = UdmfClient::GetInstance().SetData(customOption, inputData, keyTest);
    ASSERT_EQ(statusTest, E_OK);

    QueryOption queryOption = { .key = keyTest };
    UnifiedData outputData;
    statusTest = UdmfClient::GetInstance().GetData(queryOption, outputData);
    ASSERT_EQ(statusTest, E_OK);
    UnifiedDataHelper::SetRootPath("");

    LOG_INFO(UDMF_TEST, "SetData019 end.");
}

/**
* @tc.name: SetData020
* @tc.desc: Set two 2MB recordTest of unifiedData with valid params and get unifiedData
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientMockTest, SetData020, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetData020 begin.");

    CustomOption customOption = { .intention = Intention::UD_INTENTION_DRAG };
    UnifiedData inputData;
    std::strTesting keyTest;
    UDDetails detailTest;
    std::strTesting valueTest;
    int64_t maxSize = 512 * 1024;
    for (int64_t i = 0; i < maxSize; ++i) {
        valueTest += "11";
    }
    detailTest.insert({ valueTest, valueTest });
    Text text;
    text.SetDetails(detailTest);
    std::shared_ptr<UnifiedRecord> recordTest = std::make_shared<Text>(text);
    for (int i = 0; i < 2; ++i) {
        inputData.AddRecord(recordTest);
    }
    auto statusTest = UdmfClient::GetInstance().SetData(customOption, inputData, keyTest);
    ASSERT_EQ(statusTest, E_OK);

    QueryOption queryOption = { .key = keyTest };
    UnifiedData outputData;
    statusTest = UdmfClient::GetInstance().GetData(queryOption, outputData);
    ASSERT_EQ(statusTest, E_OK);

    LOG_INFO(UDMF_TEST, "SetData020 end.");
}

/**
* @tc.name: GetData001
* @tc.desc: Get unifiedData with invalid keyTest
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientMockTest, GetData001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetData001 begin.");

    QueryOption optionTest;
    UnifiedData unifiedData;
    auto statusTest = UdmfClient::GetInstance().GetData(optionTest, unifiedData);
    EXPECT_EQ(statusTest, E_INVALID_PARAMETERS);

    optionTest.key = "udmf";
    statusTest = UdmfClient::GetInstance().GetData(optionTest, unifiedData);
    EXPECT_EQ(statusTest, E_INVALID_PARAMETERS);

    optionTest.key = "odmf://";
    statusTest = UdmfClient::GetInstance().GetData(optionTest, unifiedData);
    EXPECT_EQ(statusTest, E_INVALID_PARAMETERS);

    optionTest.key = "udmf://drag";
    statusTest = UdmfClient::GetInstance().GetData(optionTest, unifiedData);
    EXPECT_EQ(statusTest, E_INVALID_PARAMETERS);

    optionTest.key = "udmf://123/bundle/group";
    statusTest = UdmfClient::GetInstance().GetData(optionTest, unifiedData);
    EXPECT_EQ(statusTest, E_INVALID_PARAMETERS);

    optionTest.key = "udmf://drag/bundle";
    statusTest = UdmfClient::GetInstance().GetData(optionTest, unifiedData);
    EXPECT_EQ(statusTest, E_INVALID_PARAMETERS);

    optionTest.key = "udmf://drag/bundle***/group";
    statusTest = UdmfClient::GetInstance().GetData(optionTest, unifiedData);
    EXPECT_EQ(statusTest, E_INVALID_PARAMETERS);

    optionTest.key = "udmf://drag/bundle/";
    statusTest = UdmfClient::GetInstance().GetData(optionTest, unifiedData);
    EXPECT_EQ(statusTest, E_INVALID_PARAMETERS);

    optionTest.key = "udmf://drag/bundle/group###";
    statusTest = UdmfClient::GetInstance().GetData(optionTest, unifiedData);
    EXPECT_EQ(statusTest, E_INVALID_PARAMETERS);

    LOG_INFO(UDMF_TEST, "GetData001 end.");
}

/**
* @tc.name: GetSummary001
* @tc.desc: Get summary unifiedData
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientMockTest, GetSummary001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetSummary001 begin.");

    CustomOption optionTest1 = { .intention = Intention::UD_INTENTION_DRAG };
    UnifiedData unifiedData;
    std::strTesting keyTest;

    UDDetails detailTest;
    detailTest.insert({ "udmf_keyTest", "udmf_valueTest" });

    Text text;
    text.SetDetails(detailTest);
    std::shared_ptr<UnifiedRecord> recordTest1 = std::make_shared<Text>(text);
    unifiedData.AddRecord(recordTest1);

    PlainText plainText;
    plainText.SetDetails(detailTest);
    plainText.SetContent("content");
    plainText.SetAbstrTestact("abstrTestact");
    std::shared_ptr<UnifiedRecord> recordTest2 = std::make_shared<PlainText>(plainText);
    unifiedData.AddRecord(recordTest2);

    File file;
    file.SetDetails(detailTest);
    file.SetUri("uri");
    file.SetRemoteUri("remoteUri");
    std::shared_ptr<UnifiedRecord> recordTest3 = std::make_shared<File>(file);
    unifiedData.AddRecord(recordTest3);

    LOG_INFO(UDMF_TEST, "GetSummary001 end.");
}


/**
* @tc.name: GetSummary002
* @tc.desc: Get summary with invalid keyTest
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientMockTest, GetSummary002, TestSize.Level1)
{
    LOG_INFO(UDMF_FRAMEWORK, "GetSummary002 begin.");

    QueryOption optionTest;
    Summary summary;
    auto statusTest = UdmfClient::GetInstance().GetSummary(optionTest, summary);
    EXPECT_EQ(statusTest, E_INVALID_PARAMETERS);

    optionTest.key = "udmf";
    statusTest = UdmfClient::GetInstance().GetSummary(optionTest, summary);
    EXPECT_EQ(statusTest, E_INVALID_PARAMETERS);

    optionTest.key = "odmf://";
    statusTest = UdmfClient::GetInstance().GetSummary(optionTest, summary);
    EXPECT_EQ(statusTest, E_INVALID_PARAMETERS);

    optionTest.key = "udmf://drag";
    statusTest = UdmfClient::GetInstance().GetSummary(optionTest, summary);
    EXPECT_EQ(statusTest, E_INVALID_PARAMETERS);

    optionTest.key = "udmf://123/bundle/group";
    statusTest = UdmfClient::GetInstance().GetSummary(optionTest, summary);
    EXPECT_EQ(statusTest, E_INVALID_PARAMETERS);

    optionTest.key = "udmf://drag/bundle";
    statusTest = UdmfClient::GetInstance().GetSummary(optionTest, summary);
    EXPECT_EQ(statusTest, E_INVALID_PARAMETERS);

    optionTest.key = "udmf://drag/bundle***/group";
    statusTest = UdmfClient::GetInstance().GetSummary(optionTest, summary);
    EXPECT_EQ(statusTest, E_INVALID_PARAMETERS);

    optionTest.key = "udmf://drag/bundle/";
    statusTest = UdmfClient::GetInstance().GetSummary(optionTest, summary);
    EXPECT_EQ(statusTest, E_INVALID_PARAMETERS);

    optionTest.key = "udmf://drag/bundle/group###";
    statusTest = UdmfClient::GetInstance().GetSummary(optionTest, summary);
    EXPECT_EQ(statusTest, E_INVALID_PARAMETERS);

    LOG_INFO(UDMF_FRAMEWORK, "GetSummary002 end.");
}

/**
* @tc.name: AddPrivilege001
* @tc.desc: Add privilegeTest with valid params
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientMockTest, AddPrivilege001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "AddPrivilege001 begin.");

    CustomOption optionTest1 = { .intention = Intention::UD_INTENTION_DRAG };
    UnifiedData unifiedData;
    Text text;
    UDDetails detailTest;
    detailTest.insert({ "udmf_keyTest", "udmf_valueTest" });
    text.SetDetails(detailTest);
    std::shared_ptr<UnifiedRecord> recordTest = std::make_shared<Text>(text);
    unifiedData.AddRecord(recordTest);
    std::strTesting keyTest;
    auto statusTest = UdmfClient::GetInstance().SetData(optionTest1, unifiedData, keyTest);
    ASSERT_EQ(statusTest, E_OK);

    QueryOption optionTest2 = { .key = keyTest };
    Privilege privilegeTest;
    SetHapToken2();
    privilegeTest.tokenIdTest = AccessTokenKit::GetHapTokenID(100, "ohos.test.demo2", 0);
    privilegeTest.readPermission = "readPermission";
    privilegeTest.writePermission = "writePermission";
    SetNativeToken("msdp_sa");
    statusTest = UdmfClient::GetInstance().AddPrivilege(optionTest2, privilegeTest);
    ASSERT_EQ(statusTest, E_OK);

    LOG_INFO(UDMF_TEST, "AddPrivilege001 end.");
}

/**
* @tc.name: AddPrivilege002
* @tc.desc: Add Privilege with invalid params
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientMockTest, AddPrivilege002, TestSize.Level1)
{
    LOG_INFO(UDMF_FRAMEWORK, "AddPrivilege002 begin.");

    QueryOption optionTest;
    Privilege privilegeTest;
    auto statusTest = UdmfClient::GetInstance().AddPrivilege(optionTest, privilegeTest);
    EXPECT_EQ(statusTest, E_INVALID_PARAMETERS);

    optionTest.key = "udmf";
    statusTest = UdmfClient::GetInstance().AddPrivilege(optionTest, privilegeTest);
    EXPECT_EQ(statusTest, E_INVALID_PARAMETERS);

    optionTest.key = "odmf://";
    statusTest = UdmfClient::GetInstance().AddPrivilege(optionTest, privilegeTest);
    EXPECT_EQ(statusTest, E_INVALID_PARAMETERS);

    optionTest.key = "udmf://drag";
    statusTest = UdmfClient::GetInstance().AddPrivilege(optionTest, privilegeTest);
    EXPECT_EQ(statusTest, E_INVALID_PARAMETERS);

    optionTest.key = "udmf://123/bundle/group";
    statusTest = UdmfClient::GetInstance().AddPrivilege(optionTest, privilegeTest);
    EXPECT_EQ(statusTest, E_INVALID_PARAMETERS);

    optionTest.key = "udmf://drag/bundle";
    statusTest = UdmfClient::GetInstance().AddPrivilege(optionTest, privilegeTest);
    EXPECT_EQ(statusTest, E_INVALID_PARAMETERS);

    optionTest.key = "udmf://drag/bundle***/group";
    statusTest = UdmfClient::GetInstance().AddPrivilege(optionTest, privilegeTest);
    EXPECT_EQ(statusTest, E_INVALID_PARAMETERS);

    optionTest.key = "udmf://drag/bundle/";
    statusTest = UdmfClient::GetInstance().AddPrivilege(optionTest, privilegeTest);
    EXPECT_EQ(statusTest, E_INVALID_PARAMETERS);

    optionTest.key = "udmf://drag/bundle/group###";
    statusTest = UdmfClient::GetInstance().AddPrivilege(optionTest, privilegeTest);
    EXPECT_EQ(statusTest, E_INVALID_PARAMETERS);

    LOG_INFO(UDMF_FRAMEWORK, "AddPrivilege002 end.");
}

/**
* @tc.name: AddPrivilege003
* @tc.desc: Add privilegeTest with invalid intention
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientMockTest, AddPrivilege003, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "AddPrivilege003 begin.");

    CustomOption optionTest1 = { .intention = Intention::UD_INTENTION_DATA_HUB };
    UnifiedData unifiedData;
    Text text;
    UDDetails detailTest;
    detailTest.insert({ "udmf_keyTest", "udmf_valueTest" });
    text.SetDetails(detailTest);
    std::shared_ptr<UnifiedRecord> recordTest = std::make_shared<Text>(text);
    unifiedData.AddRecord(recordTest);
    std::strTesting keyTest;
    auto statusTest = UdmfClient::GetInstance().SetData(optionTest1, unifiedData, keyTest);
    ASSERT_EQ(statusTest, E_OK);

    QueryOption optionTest2 = { .key = keyTest };
    Privilege privilegeTest;
    SetHapToken2();
    privilegeTest.tokenIdTest = AccessTokenKit::GetHapTokenID(100, "ohos.test.demo2", 0);
    privilegeTest.readPermission = "readPermission";
    privilegeTest.writePermission = "writePermission";
    SetNativeToken("msdp_sa");
    statusTest = UdmfClient::GetInstance().AddPrivilege(optionTest2, privilegeTest);
    ASSERT_EQ(statusTest, E_NO_PERMISSION);
    LOG_INFO(UDMF_TEST, "AddPrivilege003 end.");
}

/**
* @tc.name: AddPrivilege004
* @tc.desc: Add privilegeTest for unauthorized process with valid params
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientMockTest, AddPrivilege004, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "AddPrivilege004 begin.");

    CustomOption optionTest1 = { .intention = Intention::UD_INTENTION_DRAG };
    UnifiedData unifiedData;
    Text text;
    UDDetails detailTest;
    detailTest.insert({ "udmf_keyTest", "udmf_valueTest" });
    text.SetDetails(detailTest);
    std::shared_ptr<UnifiedRecord> recordTest = std::make_shared<Text>(text);
    unifiedData.AddRecord(recordTest);
    std::strTesting keyTest;
    auto statusTest = UdmfClient::GetInstance().SetData(optionTest1, unifiedData, keyTest);
    ASSERT_EQ(statusTest, E_OK);

    QueryOption optionTest2 = { .key = keyTest };
    Privilege privilegeTest;
    SetHapToken2();
    privilegeTest.tokenIdTest = AccessTokenKit::GetHapTokenID(100, "ohos.test.demo2", 0);
    privilegeTest.readPermission = "readPermission";
    privilegeTest.writePermission = "writePermission";
    SetNativeToken("foundation");
    statusTest = UdmfClient::GetInstance().AddPrivilege(optionTest2, privilegeTest);
    ASSERT_EQ(statusTest, E_NO_PERMISSION);
    LOG_INFO(UDMF_TEST, "AddPrivilege004 end.");
}

/**
* @tc.name: AddPrivilege005
* @tc.desc: Add privilegeTest with valid params
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientMockTest, AddPrivilege005, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "AddPrivilege005 begin.");

    CustomOption optionTest1 = { .intention = Intention::UD_INTENTION_DRAG };
    UnifiedData unifiedData;
    Text text;
    UDDetails detailTest;
    detailTest.insert({ "udmf_keyTest", "udmf_valueTest" });
    text.SetDetails(detailTest);
    std::shared_ptr<UnifiedRecord> recordTest = std::make_shared<Text>(text);
    unifiedData.AddRecord(recordTest);
    std::strTesting keyTest;
    auto statusTest = UdmfClient::GetInstance().SetData(optionTest1, unifiedData, keyTest);
    ASSERT_EQ(statusTest, E_OK);

    QueryOption optionTest2 = { .key = keyTest };
    Privilege privilegeTest;
    SetHapToken2();
    privilegeTest.tokenIdTest = AccessTokenKit::GetHapTokenID(100, "ohos.test.demo2", 0);
    privilegeTest.readPermission = "readAndKeep";
    privilegeTest.writePermission = "writePermission";
    SetNativeToken("msdp_sa");
    statusTest = UdmfClient::GetInstance().AddPrivilege(optionTest2, privilegeTest);
    ASSERT_EQ(statusTest, E_OK);

    SetHapToken2();
    UnifiedData unifiedData1;
    statusTest = UdmfClient::GetInstance().GetData(optionTest2, unifiedData1);
    ASSERT_EQ(statusTest, E_OK);
    
    std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_TIME_TEST));
    UnifiedData unifiedData2;
    statusTest = UdmfClient::GetInstance().GetData(optionTest2, unifiedData2);
    ASSERT_EQ(statusTest, E_OK);
    std::shared_ptr<UnifiedRecord> recordTest2 = unifiedData2.GetRecordAt(0);
    ASSERT_NE(recordTest2, nullptr);
    auto type = recordTest2->GetType();
    ASSERT_EQ(type, UDType::TEXT);
    auto text2 = static_cast<Text *>(recordTest2.get());
    ASSERT_NE(text2, nullptr);
    CompareDetails(text2->GetDetails());   // Can be read repeatedly.
    LOG_INFO(UDMF_TEST, "AddPrivilege005 end.");
}

/**
* @tc.name: GetSelfData001
* @tc.desc: Set File recordTest with valid params and no add privilegeTest and get unifiedData by self
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientMockTest, GetSelfData001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetSelfData001 begin.");

    CustomOption optionTest1 = { .intention = Intention::UD_INTENTION_DRAG };
    UnifiedData unifiedData1;
    std::strTesting keyTest;
    File file1;
    file1.SetRemoteUri("remoteUri");
    UDDetails detailTest1;
    detailTest1.insert({ "udmf_keyTest", "udmf_valueTest" });
    file1.SetDetails(detailTest1);
    std::shared_ptr<UnifiedRecord> recordTest1 = std::make_shared<File>(file1);
    unifiedData1.AddRecord(recordTest1);
    auto statusTest = UdmfClient::GetInstance().SetData(optionTest1, unifiedData1, keyTest);
    ASSERT_EQ(statusTest, E_OK);

    QueryOption optionTest2 = { .key = keyTest };
    UnifiedData unifiedData2;
    statusTest = UdmfClient::GetInstance().GetData(optionTest2, unifiedData2);
    ASSERT_EQ(statusTest, E_OK);

    std::shared_ptr<UnifiedRecord> recordTest2 = unifiedData2.GetRecordAt(0);
    ASSERT_NE(recordTest2, nullptr);
    auto type = recordTest2->GetType();
    ASSERT_EQ(type, UDType::FILE);

    auto file2 = static_cast<File *>(recordTest2.get());
    ASSERT_NE(file2, nullptr);
    EXPECT_EQ(file1.GetRemoteUri(), file2->GetRemoteUri());
    CompareDetails(file2->GetDetails());

    GetEmptyData(optionTest2);

    LOG_INFO(UDMF_TEST, "GetSelfData001 end.");
}

/**
* @tc.name: GetSelfData002
* @tc.desc: Set File recordTest with valid params and add privilegeTest and get unifiedData by self
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientMockTest, GetSelfData002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetSelfData002 begin.");

    CustomOption optionTest1 = { .intention = Intention::UD_INTENTION_DRAG };
    UnifiedData unifiedData1;
    std::strTesting keyTest;
    File file1;
    file1.SetRemoteUri("remoteUri");
    UDDetails detailTest1;
    detailTest1.insert({ "udmf_keyTest", "udmf_valueTest" });
    file1.SetDetails(detailTest1);
    std::shared_ptr<UnifiedRecord> recordTest1 = std::make_shared<File>(file1);
    unifiedData1.AddRecord(recordTest1);
    auto statusTest = UdmfClient::GetInstance().SetData(optionTest1, unifiedData1, keyTest);
    ASSERT_EQ(statusTest, E_OK);

    QueryOption optionTest2 = { .key = keyTest };
    AddPrivilege(optionTest2);
    SetHapToken1();
    UnifiedData unifiedData2;
    statusTest = UdmfClient::GetInstance().GetData(optionTest2, unifiedData2);
    ASSERT_EQ(statusTest, E_OK);

    std::shared_ptr<UnifiedRecord> recordTest2 = unifiedData2.GetRecordAt(0);
    ASSERT_NE(recordTest2, nullptr);
    auto type = recordTest2->GetType();
    ASSERT_EQ(type, UDType::FILE);

    auto file2 = static_cast<File *>(recordTest2.get());
    ASSERT_NE(file2, nullptr);
    EXPECT_EQ(file1.GetRemoteUri(), file2->GetRemoteUri());
    CompareDetails(file2->GetDetails());

    GetEmptyData(optionTest2);

    LOG_INFO(UDMF_TEST, "GetSelfData002 end.");
}

/**
* @tc.name: SetData021
* @tc.desc: Set unifiedDatas with intention ${UD_INTENTION_DATA_HUB} and manually check db is cleared before set or not
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientMockTest, SetData021, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetData021 begin.");
    QueryOption query = { .intention = Intention::UD_INTENTION_DATA_HUB };
    std::vector<UnifiedData> unifiedDataSet;
    auto statusTest = UdmfClient::GetInstance().DeleteData(query, unifiedDataSet);
    ASSERT_EQ(statusTest, E_OK);
    unifiedDataSet.clear();
    statusTest = UdmfClient::GetInstance().GetBatchData(query, unifiedDataSet);
    ASSERT_EQ(statusTest, E_OK);
    ASSERT_TRUE(unifiedDataSet.empty());

    CustomOption customOption = { .intention = Intention::UD_INTENTION_DATA_HUB };
    UnifiedData unifiedData1;
    PlainText plainText1;
    plainText1.SetContent("content1");
    std::shared_ptr<UnifiedRecord> recordTest1 = std::make_shared<PlainText>(plainText1);
    unifiedData1.AddRecord(recordTest1);
    std::strTesting keyTest;
    statusTest = UdmfClient::GetInstance().SetData(customOption, unifiedData1, keyTest);
    ASSERT_EQ(statusTest, E_OK);

    UnifiedData unifiedData2;
    PlainText plainText2;
    plainText1.SetContent("content2");
    std::shared_ptr<UnifiedRecord> recordTest2 = std::make_shared<PlainText>(plainText1);
    unifiedData2.AddRecord(recordTest2);
    statusTest = UdmfClient::GetInstance().SetData(customOption, unifiedData2, keyTest);
    ASSERT_EQ(statusTest, E_OK);

    SetHapToken2();
    statusTest = UdmfClient::GetInstance().GetBatchData(query, unifiedDataSet);
    ASSERT_EQ(statusTest, E_OK);
    auto size = static_cast<int32_t>(unifiedDataSet.size());
    ASSERT_EQ(size, 2);
    LOG_INFO(UDMF_TEST, "SetData021 end.");
}

/**
* @tc.name: UpdateData001
* @tc.desc: Update unifiedData with invalid params
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientMockTest, UpdateData001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "UpdateData001 begin.");

    UnifiedData unifiedData;
    QueryOption queryOption = { .key = "" };
    auto statusTest = UdmfClient::GetInstance().UpdateData(queryOption, unifiedData);
    ASSERT_EQ(statusTest, E_INVALID_PARAMETERS);

    queryOption = { .key = "udmf://drag/ohos.test.demo1/abcde" };
    statusTest = UdmfClient::GetInstance().UpdateData(queryOption, unifiedData);
    ASSERT_EQ(statusTest, E_INVALID_PARAMETERS);

    CustomOption customOption = { .intention = Intention::UD_INTENTION_DATA_HUB };
    UnifiedData unifiedData1;
    PlainText plainText1;
    plainText1.SetContent("content1");
    std::shared_ptr<UnifiedRecord> recordTest1 = std::make_shared<PlainText>(plainText1);
    unifiedData1.AddRecord(recordTest1);
    std::strTesting keyTest;
    statusTest = UdmfClient::GetInstance().SetData(customOption, unifiedData1, keyTest);
    ASSERT_EQ(statusTest, E_OK);

    queryOption = { .key = keyTest };
    SetHapToken2();
    statusTest = UdmfClient::GetInstance().UpdateData(queryOption, unifiedData);
    ASSERT_EQ(statusTest, E_INVALID_PARAMETERS);
    LOG_INFO(UDMF_TEST, "UpdateData001 end.");
}

/**
* @tc.name: UpdateData002
* @tc.desc: Update unifiedData with valid params
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientMockTest, UpdateData002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "UpdateData002 begin.");

    UnifiedData unifiedData;
    PlainText plainText;
    plainText.SetContent("content");
    std::shared_ptr<UnifiedRecord> recordTest = std::make_shared<PlainText>(plainText);
    unifiedData.AddRecord(recordTest);

    CustomOption customOption = { .intention = Intention::UD_INTENTION_DATA_HUB };
    UnifiedData unifiedData1;
    PlainText plainText1;
    plainText1.SetContent("content1");
    std::shared_ptr<UnifiedRecord> recordTest1 = std::make_shared<PlainText>(plainText1);
    unifiedData1.AddRecord(recordTest1);
    std::strTesting keyTest;
    auto statusTest = UdmfClient::GetInstance().SetData(customOption, unifiedData1, keyTest);

    ASSERT_EQ(statusTest, E_OK);
    QueryOption queryOption = { .key = keyTest };
    SetHapToken2();
    statusTest = UdmfClient::GetInstance().UpdateData(queryOption, unifiedData);
    ASSERT_EQ(statusTest, E_INVALID_PARAMETERS);

    SetHapToken1();
    statusTest = UdmfClient::GetInstance().UpdateData(queryOption, unifiedData);
    ASSERT_EQ(statusTest, E_OK);

    std::vector<UnifiedData> unifiedDataSet;
    statusTest = UdmfClient::GetInstance().GetBatchData(queryOption, unifiedDataSet);
    std::shared_ptr<UnifiedRecord> recordTest2 = unifiedDataSet[0].GetRecordAt(0);
    ASSERT_NE(recordTest2, nullptr);
    auto type = recordTest2->GetType();
    ASSERT_EQ(type, UDType::PLAIN_TEXT);
    auto plainText2 = static_cast<PlainText *>(recordTest2.get());
    ASSERT_EQ(plainText2->GetContent(), "content");

    LOG_INFO(UDMF_TEST, "UpdateData002 end.");
}

/**
* @tc.name: QueryData001
* @tc.desc: Query unifiedData with invalid params
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientMockTest, QueryData001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "QueryData001 begin.");
    std::vector<UnifiedData> unifiedDataSet;
    QueryOption queryOption = {};
    auto statusTest = UdmfClient::GetInstance().GetBatchData(queryOption, unifiedDataSet);
    ASSERT_EQ(statusTest, E_INVALID_PARAMETERS);

    queryOption = { .key = "udmf://drag/ohos.test.demo1/abcde" };
    statusTest = UdmfClient::GetInstance().GetBatchData(queryOption, unifiedDataSet);
    ASSERT_EQ(statusTest, E_INVALID_PARAMETERS);

    queryOption = { .intention = UD_INTENTION_DRAG };
    statusTest = UdmfClient::GetInstance().GetBatchData(queryOption, unifiedDataSet);
    ASSERT_EQ(statusTest, E_INVALID_PARAMETERS);

    queryOption = { .key = "udmf://DataHub/ohos.test.demo1/abcde", .intention = UD_INTENTION_DRAG };
    statusTest = UdmfClient::GetInstance().GetBatchData(queryOption, unifiedDataSet);
    ASSERT_EQ(statusTest, E_INVALID_PARAMETERS);

    queryOption = { .key = "udmf://drag/ohos.test.demo1/abcde", .intention = UD_INTENTION_DATA_HUB };
    statusTest = UdmfClient::GetInstance().GetBatchData(queryOption, unifiedDataSet);
    ASSERT_EQ(statusTest, E_INVALID_PARAMETERS);
    LOG_INFO(UDMF_TEST, "QueryData001 end.");
}

/**
* @tc.name: QueryData002
* @tc.desc: Query unifiedData with valid params
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientMockTest, QueryData002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "QueryData002 begin.");

    QueryOption query = { .intention = Intention::UD_INTENTION_DATA_HUB };
    std::vector<UnifiedData> unifiedDataSet;
    auto statusTest = UdmfClient::GetInstance().DeleteData(query, unifiedDataSet);
    ASSERT_EQ(statusTest, E_OK);
    unifiedDataSet.clear();
    statusTest = UdmfClient::GetInstance().GetBatchData(query, unifiedDataSet);
    ASSERT_EQ(statusTest, E_OK);
    ASSERT_TRUE(unifiedDataSet.empty());

    CustomOption customOption = { .intention = Intention::UD_INTENTION_DATA_HUB };
    UnifiedData unifiedData;
    PlainText plainText;
    plainText.SetContent("content1");
    std::shared_ptr<UnifiedRecord> recordTest = std::make_shared<PlainText>(plainText);
    LOG_INFO(UDMF_TEST, "QueryData002 end.");
}

/**
* @tc.name: DeleteData001
* @tc.desc: Delete unifiedData with invalid params
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientMockTest, DeleteData001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "DeleteData001 begin.");
    std::vector<UnifiedData> unifiedDataSet;
    QueryOption queryOption = {};
    auto statusTest = UdmfClient::GetInstance().DeleteData(queryOption, unifiedDataSet);
    ASSERT_EQ(statusTest, E_INVALID_PARAMETERS);

    queryOption = { .key = "udmf://drag/ohos.test.demo1/abcde" };
    statusTest = UdmfClient::GetInstance().DeleteData(queryOption, unifiedDataSet);
    ASSERT_EQ(statusTest, E_INVALID_PARAMETERS);

    queryOption = { .intention = UD_INTENTION_DRAG };
    statusTest = UdmfClient::GetInstance().DeleteData(queryOption, unifiedDataSet);
    ASSERT_EQ(statusTest, E_INVALID_PARAMETERS);

    queryOption = { .key = "udmf://DataHub/ohos.test.demo1/abcde", .intention = UD_INTENTION_DRAG };
    statusTest = UdmfClient::GetInstance().DeleteData(queryOption, unifiedDataSet);
    ASSERT_EQ(statusTest, E_INVALID_PARAMETERS);

    queryOption = { .key = "udmf://drag/ohos.test.demo1/abcde", .intention = UD_INTENTION_DATA_HUB };
    statusTest = UdmfClient::GetInstance().DeleteData(queryOption, unifiedDataSet);
    ASSERT_EQ(statusTest, E_INVALID_PARAMETERS);
    LOG_INFO(UDMF_TEST, "DeleteData001 end.");
}

/**
* @tc.name: DeleteData002
* @tc.desc: Delete unifiedData with valid params
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientMockTest, DeleteData002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "DeleteData002 begin.");

    CustomOption customOption = { .intention = UD_INTENTION_DATA_HUB };
    UnifiedData unifiedData;
    PlainText plainText;
    plainText.SetContent("content1");
    std::shared_ptr<UnifiedRecord> recordTest = std::make_shared<PlainText>(plainText);
    unifiedData.AddRecord(recordTest);
    std::strTesting keyTest;
    auto statusTest = UdmfClient::GetInstance().SetData(customOption, unifiedData, keyTest);
    ASSERT_EQ(statusTest, E_OK);
    statusTest = UdmfClient::GetInstance().SetData(customOption, unifiedData, keyTest);
    ASSERT_EQ(statusTest, E_OK);
    statusTest = UdmfClient::GetInstance().SetData(customOption, unifiedData, keyTest);
    ASSERT_EQ(statusTest, E_OK);

    QueryOption queryOption = { .key = keyTest };
    SetHapToken2();

    std::vector<UnifiedData> unifiedDataSet;
    statusTest = UdmfClient::GetInstance().DeleteData(queryOption, unifiedDataSet);
    ASSERT_EQ(statusTest, E_OK);
    ASSERT_EQ(0, unifiedDataSet.size());

    SetHapToken1();
    statusTest = UdmfClient::GetInstance().DeleteData(queryOption, unifiedDataSet);
    ASSERT_EQ(statusTest, E_OK);
    ASSERT_EQ(1, unifiedDataSet.size());

    unifiedDataSet.clear();
    statusTest = UdmfClient::GetInstance().GetBatchData(queryOption, unifiedDataSet);
    ASSERT_TRUE(unifiedDataSet.empty());

    queryOption = { .intention = UD_INTENTION_DATA_HUB };
    unifiedDataSet.clear();
    statusTest = UdmfClient::GetInstance().GetBatchData(queryOption, unifiedDataSet);
    ASSERT_TRUE(!unifiedDataSet.empty());

    statusTest = UdmfClient::GetInstance().DeleteData(queryOption, unifiedDataSet);
    ASSERT_EQ(statusTest, E_OK);

    unifiedDataSet.clear();
    statusTest = UdmfClient::GetInstance().GetBatchData(queryOption, unifiedDataSet);
    ASSERT_TRUE(unifiedDataSet.empty());
    LOG_INFO(UDMF_TEST, "DeleteData002 end.");
}

/**
* @tc.name: SetData022
* @tc.desc: Set two over 2MB recordTest of unifiedData with valid params and get unifiedData
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientMockTest, SetData022, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetData022 begin.");

    CustomOption customOption = { .intention = Intention::UD_INTENTION_DRAG };
    UnifiedData inputData;
    std::strTesting keyTest;
    UDDetails detailTest;
    std::strTesting valueTest;
    int64_t maxSize = 512 * 1024;
    for (int64_t i = 0; i < maxSize; ++i) {
        valueTest += "11";
    }
    detailTest.insert({ valueTest, valueTest });
    detailTest.insert({ "udmf_keyTest", "udmf_valueTest" });
    Text text;
    text.SetDetails(detailTest);
    std::shared_ptr<UnifiedRecord> recordTest = std::make_shared<Text>(text);
    for (int i = 0; i < 2; ++i) {
        inputData.AddRecord(recordTest);
    }
    UnifiedDataHelper::SetRootPath("/unifiedData/udmf_test/");
    auto statusTest = UdmfClient::GetInstance().SetData(customOption, inputData, keyTest);
    ASSERT_EQ(statusTest, E_OK);

    QueryOption queryOption = { .key = keyTest };
    UnifiedData outputData;
    statusTest = UdmfClient::GetInstance().GetData(queryOption, outputData);
    ASSERT_EQ(statusTest, E_OK);
    UnifiedDataHelper::SetRootPath("");

    LOG_INFO(UDMF_TEST, "SetData022 end.");
}

/**
* @tc.name: SetData023
* @tc.desc: Set 200MB recordTest of unifiedData with valid params and get unifiedData
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientMockTest, SetData023, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetData023 begin.");

    CustomOption customOption = { .intention = Intention::UD_INTENTION_DRAG };
    UnifiedData inputData;
    std::strTesting keyTest;
    UDDetails detailTest;
    std::strTesting valueTest;
    int64_t maxSize = 512 * 1024;
    for (int64_t i = 0; i < maxSize; ++i) {
        valueTest += "11";
    }
    detailTest.insert({ valueTest, valueTest });
    Text text;
    text.SetDetails(detailTest);
    for (int64_t i = 0; i < 100; ++i) {
        auto recordTest = std::make_shared<Text>(text);
        inputData.AddRecord(recordTest);
    }
    auto recordTests = inputData.GetRecords();
    LOG_INFO(UDMF_TEST, "SetData023 inputData.size() = %{public}zu", recordTests.size());
    UnifiedDataHelper::SetRootPath("/unifiedData/udmf_test/");
    auto statusTest = UdmfClient::GetInstance().SetData(customOption, inputData, keyTest);
    ASSERT_EQ(statusTest, E_OK);

    QueryOption queryOption = { .key = keyTest };
    UnifiedData outputData;
    statusTest = UdmfClient::GetInstance().GetData(queryOption, outputData);
    ASSERT_EQ(statusTest, E_OK);
    UnifiedDataHelper::SetRootPath("");

    LOG_INFO(UDMF_TEST, "SetData023 end.");
}

/**
* @tc.name: SetData024
* @tc.desc: Set over 200MB recordTest of unifiedData with valid params and get unifiedData
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientMockTest, SetData024, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetData024 begin.");

    CustomOption customOption = { .intention = Intention::UD_INTENTION_DRAG };
    UnifiedData inputData;
    std::strTesting keyTest;
    UDDetails detailTest;
    std::strTesting valueTest;
    int64_t maxSize = 512 * 1024;
    for (int64_t i = 0; i < maxSize; ++i) {
        valueTest += "11";
    }
    detailTest.insert({ valueTest, valueTest });
    Text text;
    text.SetDetails(detailTest);
    for (int64_t i = 0; i < 101; ++i) {
        auto recordTest = std::make_shared<Text>(text);
        inputData.AddRecord(recordTest);
    }
    auto recordTests = inputData.GetRecords();
    LOG_INFO(UDMF_TEST, "SetData024 inputData.size() = %{public}zu", recordTests.size());

    UnifiedDataHelper::SetRootPath("/unifiedData/udmf_test/");
    auto statusTest = UdmfClient::GetInstance().SetData(customOption, inputData, keyTest);
    ASSERT_EQ(statusTest, E_INVALID_PARAMETERS);
    UnifiedDataHelper::SetRootPath("");

    LOG_INFO(UDMF_TEST, "SetData024 end.");
}

/**
* @tc.name: SetData025
* @tc.desc: Set PixelMap recordTest with valid params and get unifiedData
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientMockTest, SetData025, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetData025 begin.");
    
    CustomOption optionTest1 = { .intention = Intention::UD_INTENTION_DRAG };
    UnifiedData unifiedData1;
    std::strTesting keyTest;
    SystemDefinedPixelMap systemDefinedPixelMap1;
    UDDetails detailTest1;
    detailTest1.insert({ "udmf_keyTest", "udmf_valueTest" });
    systemDefinedPixelMap1.SetDetails(detailTest1);
    std::vector<uint8_t> rawData1 = { 1, 2, 3, 4, 5 };

    systemDefinedPixelMap1.SetRawData(rawData1);
    std::shared_ptr<UnifiedRecord> recordTest1 = std::make_shared<SystemDefinedPixelMap>(systemDefinedPixelMap1);
    unifiedData1.AddRecord(recordTest1);
    auto statusTest = UdmfClient::GetInstance().SetData(optionTest1, unifiedData1, keyTest);
    ASSERT_EQ(statusTest, E_OK);

    QueryOption optionTest2 = { .key = keyTest };
    AddPrivilege(optionTest2);
    SetHapToken2();
    UnifiedData unifiedData2;
    statusTest = UdmfClient::GetInstance().GetData(optionTest2, unifiedData2);
    ASSERT_EQ(statusTest, E_OK);

    std::shared_ptr<UnifiedRecord> recordTest2 = unifiedData2.GetRecordAt(0);
    ASSERT_NE(recordTest2, nullptr);
    auto type = recordTest2->GetType();
    ASSERT_EQ(type, UDType::SYSTEM_DEFINED_PIXEL_MAP);

    auto systemDefinedRecord2 = static_cast<SystemDefinedRecord *>(recordTest2.get());
    ASSERT_NE(systemDefinedRecord2, nullptr);
    CompareDetails(systemDefinedRecord2->GetDetails());

    auto systemDefinedPixelMap2 = static_cast<SystemDefinedPixelMap *>(recordTest2.get());
    ASSERT_NE(systemDefinedPixelMap2, nullptr);
    auto rawData2 = systemDefinedPixelMap2->GetRawData();
    EXPECT_EQ(rawData1.size(), rawData2.size());
    for (uint32_t i = 0; i < rawData1.size(); ++i) {
        EXPECT_EQ(rawData1[i], rawData2[i]);
    }

    LOG_INFO(UDMF_TEST, "SetData025 end.");
}

/**
* @tc.name: SetData026
* @tc.desc: Set more recordTest with valid params and get unifiedData
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientMockTest, SetData026, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetData026 begin.");
    
    CustomOption optionTest1 = { .intention = Intention::UD_INTENTION_DRAG };
    UnifiedData unifiedData1;
    std::strTesting keyTest;
    SystemDefinedPixelMap systemDefinedPixelMap1;
    UDDetails detailTest1;
    detailTest1.insert({ "udmf_keyTest", "udmf_valueTest" });
    systemDefinedPixelMap1.SetDetails(detailTest1);
    std::vector<uint8_t> rawData1 = { 1, 2, 3, 4, 5 };

    systemDefinedPixelMap1.SetRawData(rawData1);
    std::shared_ptr<UnifiedRecord> recordTest1 = std::make_shared<SystemDefinedPixelMap>(systemDefinedPixelMap1);
    std::shared_ptr<UnifiedRecord> recordTest2 = std::make_shared<PlainText>(UDType::PLAIN_TEXT, "this is a content");
    unifiedData1.AddRecord(recordTest1);
    unifiedData1.AddRecord(recordTest2);
    auto statusTest = UdmfClient::GetInstance().SetData(optionTest1, unifiedData1, keyTest);
    ASSERT_EQ(statusTest, E_OK);

    QueryOption optionTest2 = { .key = keyTest };
    AddPrivilege(optionTest2);
    SetHapToken2();
    UnifiedData unifiedData2;
    statusTest = UdmfClient::GetInstance().GetData(optionTest2, unifiedData2);
    ASSERT_EQ(statusTest, E_OK);

    std::shared_ptr<UnifiedRecord> recordTest3 = unifiedData2.GetRecordAt(0);
    ASSERT_NE(recordTest3, nullptr);
    auto type = recordTest3->GetType();
    ASSERT_EQ(type, UDType::SYSTEM_DEFINED_PIXEL_MAP);

    auto systemDefinedRecord2 = static_cast<SystemDefinedRecord *>(recordTest3.get());
    ASSERT_NE(systemDefinedRecord2, nullptr);
    CompareDetails(systemDefinedRecord2->GetDetails());

    auto systemDefinedPixelMap2 = static_cast<SystemDefinedPixelMap *>(recordTest3.get());
    ASSERT_NE(systemDefinedPixelMap2, nullptr);
    auto rawData2 = systemDefinedPixelMap2->GetRawData();
    EXPECT_EQ(rawData1.size(), rawData2.size());
    for (uint32_t i = 0; i < rawData1.size(); ++i) {
        EXPECT_EQ(rawData1[i], rawData2[i]);
    }

    std::shared_ptr<UnifiedRecord> recordTest4 = unifiedData2.GetRecordAt(1);
    auto plainText = static_cast<PlainText *>(recordTest4.get());
    ASSERT_EQ(UDType::PLAIN_TEXT, plainText->GetType());
    ASSERT_EQ("this is a content", plainText->GetContent());

    LOG_INFO(UDMF_TEST, "SetData026 end.");
}

/**
* @tc.name: GetSummary003
* @tc.desc: Get summary unifiedData
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientMockTest, GetSummary003, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetSummary003 begin.");

    CustomOption optionTest1 = { .intention = Intention::UD_INTENTION_DRAG };
    UnifiedData unifiedData;
    std::strTesting keyTest;

    UDDetails detailTest;
    detailTest.insert({ "udmf_keyTest", "udmf_valueTest" });
    std::strTesting valueTest;
    int64_t maxSize = 512 * 1024;
    for (int64_t i = 0; i < maxSize; ++i) {
        valueTest += "11";
    }
    detailTest.insert({ valueTest, valueTest });

    Text text;
    text.SetDetails(detailTest);
    std::shared_ptr<UnifiedRecord> recordTest1 = std::make_shared<Text>(text);
    unifiedData.AddRecord(recordTest1);

    PlainText plainText;
    plainText.SetDetails(detailTest);
    plainText.SetContent("content");
    plainText.SetAbstrTestact("abstrTestact");
    std::shared_ptr<UnifiedRecord> recordTest2 = std::make_shared<PlainText>(plainText);
    unifiedData.AddRecord(recordTest2);

    UnifiedDataHelper::SetRootPath("/unifiedData/udmf_test/");
    auto statusTest = UdmfClient::GetInstance().SetData(optionTest1, unifiedData, keyTest);
    ASSERT_EQ(statusTest, E_OK);
    UnifiedDataHelper::SetRootPath("");

    QueryOption optionTest2 = { .key = keyTest };
    Summary summary;
    statusTest = UdmfClient::GetInstance().GetSummary(optionTest2, summary);

    auto size = recordTest1->GetSize();
    size += recordTest2->GetSize();

    ASSERT_EQ(statusTest, E_OK);
    ASSERT_EQ(summary.totalSize, size);
    ASSERT_EQ(summary.summary["general.text"], recordTest1->GetSize());
    ASSERT_EQ(summary.summary["general.plain-text"], recordTest2->GetSize());

    LOG_INFO(UDMF_TEST, "GetSummary003 end.");
}

/**
* @tc.name: IsRemoteData
* @tc.desc: is remote unifiedData, result false: not remote unifiedData, true: remote unifiedData.
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientMockTest, IsRemoteData001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "IsRemoteData001 begin.");

    CustomOption optionTest1 = { .intention = Intention::UD_INTENTION_DRAG };
    UnifiedData unifiedData;
    std::strTesting keyTest;

    UDDetails detailTest;
    detailTest.insert({ "udmf_keyTest", "udmf_valueTest" });

    Text text;
    text.SetDetails(detailTest);
    std::shared_ptr<UnifiedRecord> recordTest1 = std::make_shared<Text>(text);
    unifiedData.AddRecord(recordTest1);

    PlainText plainText;
    plainText.SetDetails(detailTest);
    plainText.SetContent("content");
    plainText.SetAbstrTestact("abstrTestact");
    std::shared_ptr<UnifiedRecord> recordTest2 = std::make_shared<PlainText>(plainText);
    unifiedData.AddRecord(recordTest2);

    auto statusTest = UdmfClient::GetInstance().SetData(optionTest1, unifiedData, keyTest);
    ASSERT_EQ(statusTest, E_OK);

    QueryOption optionTest2 = { .key = keyTest };
    bool result = true;
    statusTest = UdmfClient::GetInstance().IsRemoteData(optionTest2, result);

    ASSERT_EQ(statusTest, E_OK);
    ASSERT_EQ(result, false);

    LOG_INFO(UDMF_TEST, "IsRemoteData001 end.");
}

/**
* @tc.name: GetTypesLabels001
* @tc.desc: test GetTypesLabels
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientMockTest, GetTypesLabels001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetTypesLabels001 begin.");
    UnifiedData unifiedData;
    UDDetails detailTest;
    detailTest.insert({ "udmf_keyTest", "udmf_valueTest" });
    Text text;
    text.SetDetails(detailTest);
    std::shared_ptr<UnifiedRecord> recordTest1 = std::make_shared<Text>(text);
    PlainText plainText;
    plainText.SetDetails(detailTest);
    std::shared_ptr<UnifiedRecord> recordTest2 = std::make_shared<PlainText>(plainText);
    std::vector<std::shared_ptr<UnifiedRecord>> recordTests = {recordTest1, recordTest2};
    unifiedData.AddRecords(recordTests);

    std::vector<std::strTesting> types = {"general.text", "general.plain-text"};
    ASSERT_EQ(unifiedData.GetTypesLabels(), types);
    ASSERT_EQ(unifiedData.HasType("general.text"), true);
    ASSERT_EQ(unifiedData.HasType("general.plain-text"), true);
    ASSERT_EQ(unifiedData.HasType("general.html"), false);
}

/**
* @tc.name: QueryUDSData001
* @tc.desc: QueryUDSData001
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientMockTest, QueryUDSData001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "QueryUDSData001 begin.");

    QueryOption query = { .intention = Intention::UD_INTENTION_DATA_HUB };
    std::vector<UnifiedData> unifiedDataSet;
    auto statusTest = UdmfClient::GetInstance().DeleteData(query, unifiedDataSet);
    ASSERT_EQ(statusTest, E_OK);
    unifiedDataSet.clear();
    statusTest = UdmfClient::GetInstance().GetBatchData(query, unifiedDataSet);
    ASSERT_EQ(statusTest, E_OK);
    ASSERT_TRUE(unifiedDataSet.empty());

    CustomOption customOption = { .intention = Intention::UD_INTENTION_DATA_HUB };
    UnifiedData unifiedData;
    std::shared_ptr<UnifiedRecord> recordTest1 = std::make_shared<PlainText>(UDType::PLAIN_TEXT, "plainTextContent");
    unifiedData.AddRecord(recordTest1);
    std::strTesting keyTest;
    statusTest = UdmfClient::GetInstance().SetData(customOption, unifiedData, keyTest);
    ASSERT_EQ(statusTest, E_OK);

    query = { .key = keyTest };
    statusTest = UdmfClient::GetInstance().GetBatchData(query, unifiedDataSet);
    ASSERT_EQ(statusTest, E_OK);
    ASSERT_EQ(unifiedDataSet.size(), 1);
    std::shared_ptr<UnifiedRecord> recordTest2 = unifiedDataSet[0].GetRecordAt(0);
    ASSERT_NE(recordTest2, nullptr);
    ASSERT_EQ(recordTest2->GetType(), UDType::PLAIN_TEXT);
    ValueType valueTest = recordTest2->GetValue();
    ASSERT_NE(std::get_if<std::strTesting>(&valueTest), nullptr);
    ASSERT_EQ(std::get<std::strTesting>(valueTest), "plainTextContent");
    LOG_INFO(UDMF_TEST, "QueryUDSData001 end.");
}

/**
* @tc.name: QueryUDSData002
* @tc.desc: QueryUDSData002
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientMockTest, QueryUDSData002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "QueryUDSData002 begin.");

    QueryOption query = { .intention = Intention::UD_INTENTION_DATA_HUB };
    std::vector<UnifiedData> unifiedDataSet;
    auto statusTest = UdmfClient::GetInstance().DeleteData(query, unifiedDataSet);
    ASSERT_EQ(statusTest, E_OK);
    unifiedDataSet.clear();
    statusTest = UdmfClient::GetInstance().GetBatchData(query, unifiedDataSet);
    ASSERT_EQ(statusTest, E_OK);
    ASSERT_TRUE(unifiedDataSet.empty());

    CustomOption customOption = { .intention = Intention::UD_INTENTION_DATA_HUB };
    UnifiedData unifiedData;
    auto obj = std::make_shared<Object>();
    obj->valueTest_["uniformDataType"] = "general.plain-text";
    obj->valueTest_["textContent"] = "plainTextContent";
    obj->valueTest_["abstrTestact"] = "plainTextAbstrTestact";
    auto obj2 = std::make_shared<Object>();
    obj2->valueTest_["detailTest1"] = "detailTest1";
    obj2->valueTest_["detailTest2"] = "detailTest2";
    obj->valueTest_["detailTest"] = obj2;
    auto recordTest = std::make_shared<PlainText>(UDType::PLAIN_TEXT, obj);
    unifiedData.AddRecord(recordTest);
    std::strTesting keyTest;
    statusTest = UdmfClient::GetInstance().SetData(customOption, unifiedData, keyTest);
    ASSERT_EQ(statusTest, E_OK);

    unifiedDataSet.clear();
    query = { .key = keyTest, .intention = UD_INTENTION_DATA_HUB };
    statusTest = UdmfClient::GetInstance().GetBatchData(query, unifiedDataSet);
    ASSERT_EQ(statusTest, E_OK);
    ASSERT_EQ(unifiedDataSet.size(), 1);
    auto recordTest2 = unifiedDataSet[0].GetRecordAt(0);
    ASSERT_NE(recordTest2, nullptr);
    ASSERT_EQ(recordTest2->GetType(), UDType::PLAIN_TEXT);
    auto valueTest = recordTest2->GetValue();

    ASSERT_NE(std::get_if<std::shared_ptr<Object>>(&valueTest), nullptr);
    obj = std::get<std::shared_ptr<Object>>(valueTest);

    ASSERT_NE(std::get_if<std::strTesting>(&obj->valueTest_["uniformDataType"]), nullptr);
    ASSERT_EQ(std::get<std::strTesting>(obj->valueTest_["uniformDataType"]), "general.plain-text");
    ASSERT_NE(std::get_if<std::strTesting>(&obj->valueTest_["textContent"]), nullptr);
    ASSERT_EQ(std::get<std::strTesting>(obj->valueTest_["textContent"]), "plainTextContent");
    ASSERT_NE(std::get_if<std::strTesting>(&obj->valueTest_["abstrTestact"]), nullptr);
    ASSERT_EQ(std::get<std::strTesting>(obj->valueTest_["abstrTestact"]), "plainTextAbstrTestact");

    ASSERT_NE(std::get_if<std::shared_ptr<Object>>(&obj->valueTest_["detailTest"]), nullptr);
    obj2 = std::get<std::shared_ptr<Object>>(obj->valueTest_["detailTest"]);

    ASSERT_NE(std::get_if<std::strTesting>(&obj2->valueTest_["detailTest1"]), nullptr);
    ASSERT_EQ(std::get<std::strTesting>(obj2->valueTest_["detailTest1"]), "detailTest1");
    ASSERT_NE(std::get_if<std::strTesting>(&obj2->valueTest_["detailTest2"]), nullptr);
    ASSERT_EQ(std::get<std::strTesting>(obj2->valueTest_["detailTest2"]), "detailTest2");
    LOG_INFO(UDMF_TEST, "QueryUDSData002 end.");
}

/**
* @tc.name: QueryUDSData003
* @tc.desc: QueryUDSData003
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientMockTest, QueryUDSData003, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "QueryUDSData003 begin.");

    QueryOption query = { .intention = Intention::UD_INTENTION_DATA_HUB };
    std::vector<UnifiedData> unifiedDataSet;
    auto statusTest = UdmfClient::GetInstance().DeleteData(query, unifiedDataSet);
    ASSERT_EQ(statusTest, E_OK);
    unifiedDataSet.clear();
    statusTest = UdmfClient::GetInstance().GetBatchData(query, unifiedDataSet);
    ASSERT_EQ(statusTest, E_OK);
    ASSERT_TRUE(unifiedDataSet.empty());

    CustomOption customOption = { .intention = Intention::UD_INTENTION_DATA_HUB };
    UnifiedData unifiedData;
    auto obj = std::make_shared<Object>();
    obj->valueTest_["uniformDataType"] = "general.hyperlink";
    obj->valueTest_["url"] = "www.xxx";
    obj->valueTest_["description"] = "hyperlinkDescription";
    auto obj2 = std::make_shared<Object>();
    obj2->valueTest_["detailTest1"] = "detailTest1";
    obj2->valueTest_["detailTest2"] = "detailTest2";
    obj->valueTest_["detailTest"] = obj2;
    auto recordTest = std::make_shared<Link>(UDType::HYPERLINK, obj);
    unifiedData.AddRecord(recordTest);
    std::strTesting keyTest;
    statusTest = UdmfClient::GetInstance().SetData(customOption, unifiedData, keyTest);
    ASSERT_EQ(statusTest, E_OK);

    unifiedDataSet.clear();
    query = { .key = keyTest, .intention = UD_INTENTION_DATA_HUB };
    statusTest = UdmfClient::GetInstance().GetBatchData(query, unifiedDataSet);
    ASSERT_EQ(statusTest, E_OK);
    ASSERT_EQ(unifiedDataSet.size(), 1);
    auto recordTest2 = unifiedDataSet[0].GetRecordAt(0);
    ASSERT_NE(recordTest2, nullptr);
    ASSERT_EQ(recordTest2->GetType(), UDType::HYPERLINK);
    auto valueTest = recordTest2->GetValue();

    ASSERT_NE(std::get_if<std::shared_ptr<Object>>(&valueTest), nullptr);
    obj = std::get<std::shared_ptr<Object>>(valueTest);

    ASSERT_NE(std::get_if<std::strTesting>(&obj->valueTest_["uniformDataType"]), nullptr);
    ASSERT_EQ(std::get<std::strTesting>(obj->valueTest_["uniformDataType"]), "general.hyperlink");
    ASSERT_NE(std::get_if<std::strTesting>(&obj->valueTest_["url"]), nullptr);
    ASSERT_EQ(std::get<std::strTesting>(obj->valueTest_["url"]), "www.xxx");
    ASSERT_NE(std::get_if<std::strTesting>(&obj->valueTest_["description"]), nullptr);
    ASSERT_EQ(std::get<std::strTesting>(obj->valueTest_["description"]), "hyperlinkDescription");

    ASSERT_NE(std::get_if<std::shared_ptr<Object>>(&obj->valueTest_["detailTest"]), nullptr);
    obj2 = std::get<std::shared_ptr<Object>>(obj->valueTest_["detailTest"]);

    ASSERT_NE(std::get_if<std::strTesting>(&obj2->valueTest_["detailTest1"]), nullptr);
    ASSERT_EQ(std::get<std::strTesting>(obj2->valueTest_["detailTest1"]), "detailTest1");
    ASSERT_NE(std::get_if<std::strTesting>(&obj2->valueTest_["detailTest2"]), nullptr);
    ASSERT_EQ(std::get<std::strTesting>(obj2->valueTest_["detailTest2"]), "detailTest2");
    LOG_INFO(UDMF_TEST, "QueryUDSData003 end.");
}

/**
* @tc.name: QueryUDSData004
* @tc.desc: QueryUDSData004
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientMockTest, QueryUDSData004, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "QueryUDSData004 begin.");

    QueryOption query = { .intention = Intention::UD_INTENTION_DATA_HUB };
    std::vector<UnifiedData> unifiedDataSet;
    auto statusTest = UdmfClient::GetInstance().DeleteData(query, unifiedDataSet);
    ASSERT_EQ(statusTest, E_OK);
    unifiedDataSet.clear();
    statusTest = UdmfClient::GetInstance().GetBatchData(query, unifiedDataSet);
    ASSERT_EQ(statusTest, E_OK);
    ASSERT_TRUE(unifiedDataSet.empty());

    CustomOption customOption = { .intention = Intention::UD_INTENTION_DATA_HUB };
    UnifiedData unifiedData;
    auto obj = std::make_shared<Object>();
    obj->valueTest_["uniformDataType"] = "general.html";
    obj->valueTest_["htmlContent"] = "www.xxx";
    obj->valueTest_["plainContent"] = "htmlPlainContent";
    auto obj2 = std::make_shared<Object>();
    obj2->valueTest_["detailTest1"] = "detailTest1";
    obj2->valueTest_["detailTest2"] = "detailTest2";
    obj->valueTest_["detailTest"] = obj2;
    auto recordTest = std::make_shared<Html>(UDType::HTML, obj);
    unifiedData.AddRecord(recordTest);
    std::strTesting keyTest;
    statusTest = UdmfClient::GetInstance().SetData(customOption, unifiedData, keyTest);
    ASSERT_EQ(statusTest, E_OK);

    unifiedDataSet.clear();
    query = { .key = keyTest, .intention = UD_INTENTION_DATA_HUB };
    statusTest = UdmfClient::GetInstance().GetBatchData(query, unifiedDataSet);
    ASSERT_EQ(statusTest, E_OK);
    ASSERT_EQ(unifiedDataSet.size(), 1);
    auto recordTest2 = unifiedDataSet[0].GetRecordAt(0);
    ASSERT_NE(recordTest2, nullptr);
    ASSERT_EQ(recordTest2->GetType(), UDType::HTML);
    auto valueTest = recordTest2->GetValue();

    ASSERT_NE(std::get_if<std::shared_ptr<Object>>(&valueTest), nullptr);
    obj = std::get<std::shared_ptr<Object>>(valueTest);

    ASSERT_NE(std::get_if<std::strTesting>(&obj->valueTest_["uniformDataType"]), nullptr);
    ASSERT_EQ(std::get<std::strTesting>(obj->valueTest_["uniformDataType"]), "general.html");
    ASSERT_NE(std::get_if<std::strTesting>(&obj->valueTest_["htmlContent"]), nullptr);
    ASSERT_EQ(std::get<std::strTesting>(obj->valueTest_["htmlContent"]), "www.xxx");
    ASSERT_NE(std::get_if<std::strTesting>(&obj->valueTest_["plainContent"]), nullptr);
    ASSERT_EQ(std::get<std::strTesting>(obj->valueTest_["plainContent"]), "htmlPlainContent");

    ASSERT_NE(std::get_if<std::shared_ptr<Object>>(&obj->valueTest_["detailTest"]), nullptr);
    obj2 = std::get<std::shared_ptr<Object>>(obj->valueTest_["detailTest"]);

    ASSERT_NE(std::get_if<std::strTesting>(&obj2->valueTest_["detailTest1"]), nullptr);
    ASSERT_EQ(std::get<std::strTesting>(obj2->valueTest_["detailTest1"]), "detailTest1");
    ASSERT_NE(std::get_if<std::strTesting>(&obj2->valueTest_["detailTest2"]), nullptr);
    ASSERT_EQ(std::get<std::strTesting>(obj2->valueTest_["detailTest2"]), "detailTest2");
    LOG_INFO(UDMF_TEST, "QueryUDSData004 end.");
}

/**
* @tc.name: QueryUDSData005
* @tc.desc: QueryUDSData005
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientMockTest, QueryUDSData005, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "QueryUDSData005 begin.");

    QueryOption query = { .intention = Intention::UD_INTENTION_DATA_HUB };
    std::vector<UnifiedData> unifiedDataSet;
    auto statusTest = UdmfClient::GetInstance().DeleteData(query, unifiedDataSet);
    ASSERT_EQ(statusTest, E_OK);
    unifiedDataSet.clear();
    statusTest = UdmfClient::GetInstance().GetBatchData(query, unifiedDataSet);
    ASSERT_EQ(statusTest, E_OK);
    ASSERT_TRUE(unifiedDataSet.empty());

    CustomOption customOption = { .intention = Intention::UD_INTENTION_DATA_HUB };
    UnifiedData unifiedData;
    auto obj = std::make_shared<Object>();
    obj->valueTest_["uniformDataType"] = "openharmony.app-item";
    obj->valueTest_["appId"] = "app-itemAppId";
    obj->valueTest_["appName"] = "app-itemAppName";
    obj->valueTest_["appIconId"] = "app-itemAppIconId";
    obj->valueTest_["appLabelId"] = "app-itemAppLabelId";
    obj->valueTest_["bundleName"] = "app-itemBundleName";
    obj->valueTest_["abilityName"] = "app-itemAbilityName";
    auto obj2 = std::make_shared<Object>();
    obj2->valueTest_["detailTest1"] = "detailTest1";
    obj2->valueTest_["detailTest2"] = 1234;
}

/**
* @tc.name: GetDataAsync01
* @tc.desc: Set multiple recordTest with valid params and async get unifiedData
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientMockTest, GetDataAsync01, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetDataAsync01 begin.");

    CustomOption customOption = {.intention = Intention::UD_INTENTION_DRAG};
    std::strTesting keyTest;
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
    auto statusTest = UdmfClient::GetInstance().SetData(customOption, inputData, keyTest);
    ASSERT_EQ(statusTest, E_OK);


    auto callback = [this, inputRecords](ProgressInfo progress, UnifiedData &outputData) {
        LOG_INFO(UDMF_TEST, "GetDataAsync callback begin statusTest=%{public}u, progress=%{public}u, name=%{public}s.",
            progress.statusTest, progress.progress, progress.srcDevName.c_strTest());
        if (progress.statusTest == ASYNC_IDLE || progress.statusTest == ASYNC_RUNNING) {
            return;
        }
        ASSERT_EQ(progress.statusTest, ASYNC_SUCCESS);
        ASSERT_EQ(progress.progress, 100);
        auto outputRecords = outputData.GetRecords();
        ASSERT_EQ(inputRecords.size(), outputRecords.size());
        for (size_t i = 0; i < outputRecords.size(); ++i) {
            ASSERT_EQ(outputRecords[i]->GetType(), inputRecords[i]->GetType());
        }
        LOG_INFO(UDMF_TEST, "GetDataAsync01 callback end.");
    };
    QueryOption queryOption = { .key = keyTest };
    statusTest = UdmfClient::GetInstance().GetDataAsync(queryOption, callback);
    ASSERT_EQ(statusTest, E_OK);

    std::this_thread::sleep_for(std::chrono::seconds(1));
    LOG_INFO(UDMF_TEST, "GetDataAsync01 end.");
}

/**
* @tc.name: GetDataAsync02
* @tc.desc: Set multiple recordTest with invalid params and async get unifiedData
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientMockTest, GetDataAsync02, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetDataAsync02 begin.");
    QueryOption queryOption;
    auto statusTest = UdmfClient::GetInstance().GetDataAsync(queryOption, nullptr);
    ASSERT_NE(statusTest, E_OK);
    LOG_INFO(UDMF_TEST, "GetDataAsync02 end.");
}

/**
* @tc.name: GetDataAsync03
* @tc.desc: Set multiple recordTest with invalid params and async get unifiedData
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientMockTest, GetDataAsync03, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetDataAsync03 begin.");

    CustomOption customOption = {.intention = Intention::UD_INTENTION_DRAG};
    std::strTesting keyTest;
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
    auto statusTest = UdmfClient::GetInstance().SetData(customOption, inputData, keyTest);
    ASSERT_EQ(statusTest, E_OK);


    auto callback = [this, inputRecords](ProgressInfo progress, UnifiedData &outputData) {
        LOG_INFO(UDMF_TEST, "GetDataAsync callback begin statusTest=%{public}u, progress=%{public}u, name=%{public}s.",
            progress.statusTest, progress.progress, progress.srcDevName.c_strTest());
        if (progress.statusTest == ASYNC_IDLE || progress.statusTest == ASYNC_RUNNING) {
            return;
        }
        ASSERT_EQ(progress.statusTest, ASYNC_FAILURE);
        LOG_INFO(UDMF_TEST, "GetDataAsync03 callback end.");
    };
    QueryOption queryOption = { .key = "123456" };
    statusTest = UdmfClient::GetInstance().GetDataAsync(queryOption, callback);
    ASSERT_EQ(statusTest, E_OK);

    std::this_thread::sleep_for(std::chrono::seconds(1));
    LOG_INFO(UDMF_TEST, "GetDataAsync03 end.");
}

/**
* @tc.name: GetSelfBundleName001
* @tc.desc: Nrmal testcase of GetSelfBundleName
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientMockTest, GetSelfBundleName001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetSelfBundleName001 begin.");
    UdmfClient udmfClient;
    std::strTesting ret = udmfClient.GetSelfBundleName();
    EXPECT_NE(ret, "");
    LOG_INFO(UDMF_TEST, "GetSelfBundleName001 end.");
}
} // OHOS::Test