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
#define LOG_TAG "UdmfClientFileMangerTest"
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
#include "unified_html_record_process.h"
#include "video.h"

using namespace testing::ext;
using namespace OHOS::Security::AccessToken;
using namespace OHOS::UDMF;
using namespace OHOS;
namespace OHOS::Test {
class UdmfClientFileMangerTest : public testing::Test {
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
    void AddPrivilege1(QueryOption &option);
    int64_t CountTime();

    static constexpr int userId = 100;
    static constexpr int instIndex = 0;
};

void UdmfClientFileMangerTest::SetUpTestCase()
{
    AllocHapToken1();
    AllocHapToken2();
}

void UdmfClientFileMangerTest::TearDownTestCase()
{
    auto tokenId = AccessTokenKit::GetHapTokenID(userId, "ohos.file.manger.test.demo1", instIndex);
    AccessTokenKit::DeleteToken(tokenId);
    tokenId = AccessTokenKit::GetHapTokenID(userId, "ohos.file.manger.test.demo2", instIndex);
    AccessTokenKit::DeleteToken(tokenId);
}

void UdmfClientFileMangerTest::SetUp()
{
    SetHapToken1();
}

void UdmfClientFileMangerTest::TearDown()
{
    QueryOption query = { .intention = Intention::UD_INTENTION_PICKER };
    std::vector<UnifiedData> unifiedDataSet;
    UdmfClient::GetInstance().DeleteData(query, unifiedDataSet);
    query = { .intention = Intention::UD_INTENTION_MENU };
    UdmfClient::GetInstance().DeleteData(query, unifiedDataSet);
    query = { .intention = Intention::UD_INTENTION_SYSTEM_SHARE };
    UdmfClient::GetInstance().DeleteData(query, unifiedDataSet);
}

void UdmfClientFileMangerTest::SetNativeToken(const std::string &processName)
{
    auto tokenId = AccessTokenKit::GetNativeTokenId(processName);
    SetSelfTokenID(tokenId);
}

void UdmfClientFileMangerTest::AllocHapToken1()
{
    HapInfoParams info = {
        .userID = userId,
        .bundleName = "ohos.file.manger.test.demo1",
        .instIndex = instIndex,
        .appIDDesc = "ohos.file.manger.test.demo1"
    };

    HapPolicyParams policy = {
        .apl = APL_NORMAL,
        .domain = "test.domain",
        .permList = {
            {
                .permissionName = "ohos.permission.test",
                .bundleName = "ohos.file.manger.test.demo1",
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

void UdmfClientFileMangerTest::AllocHapToken2()
{
    HapInfoParams info = {
        .userID = userId,
        .bundleName = "ohos.file.manger.test.demo2",
        .instIndex = instIndex,
        .appIDDesc = "ohos.file.manger.test.demo2"
    };

    HapPolicyParams policy = {
        .apl = APL_NORMAL,
        .domain = "test.domain",
        .permList = {
            {
                .permissionName = "ohos.permission.test",
                .bundleName = "ohos.file.manger.test.demo2",
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

void UdmfClientFileMangerTest::SetHapToken1()
{
    auto tokenId = AccessTokenKit::GetHapTokenID(userId, "ohos.file.manger.test.demo1", instIndex);
    SetSelfTokenID(tokenId);
}

void UdmfClientFileMangerTest::SetHapToken2()
{
    auto tokenId = AccessTokenKit::GetHapTokenID(userId, "ohos.file.manger.test.demo2", instIndex);
    SetSelfTokenID(tokenId);
}

void UdmfClientFileMangerTest::AddPrivilege(QueryOption &option)
{
    Privilege privilege;
    privilege.tokenId = AccessTokenKit::GetHapTokenID(userId, "ohos.file.manger.test.demo2", instIndex);
    privilege.readPermission = "readAndKeep";
    privilege.writePermission = "writePermission";
    SetNativeToken("foundation");

    auto status = UdmfClient::GetInstance().AddPrivilege(option, privilege);
    ASSERT_EQ(status, E_OK);
}

void UdmfClientFileMangerTest::AddPrivilege1(QueryOption &option)
{
    Privilege privilege;
    privilege.tokenId = AccessTokenKit::GetHapTokenID(userId, "ohos.file.manger.test.demo1", instIndex);
    privilege.readPermission = "readpermission";
    privilege.writePermission = "writePermission";
    SetNativeToken("foundation");
    auto status = UdmfClient::GetInstance().AddPrivilege(option, privilege);
    ASSERT_EQ(status, E_OK);
}

int64_t UdmfClientFileMangerTest::CountTime()
{
    return std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch()).count();
}

/**
* @tc.name: SetData001
* @tc.desc: Set data with invalid params
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientFileMangerTest, SetData001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetData001 begin.");

    CustomOption option = { .intention = Intention::UD_INTENTION_PICKER };
    UnifiedData data;
    std::string key;
    auto status = UdmfClient::GetInstance().SetData(option, data, key);
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
* @tc.desc: Set data with valid params UD_INTENTION_PICKER
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientFileMangerTest, SetData002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetData002 begin.");
    CustomOption customOption = { .intention = Intention::UD_INTENTION_PICKER };
    UnifiedData inputData;
    std::string keyTest;
    std::vector<std::shared_ptr<UnifiedRecord>> inputRecords;

    std::string uri = "file://file_11.txt";
    inputRecords.emplace_back(std::make_shared<File>(UDType::FILE, "this is a oriUri"+uri));
    inputData.SetRecords(inputRecords);
    auto status = UdmfClient::GetInstance().SetData(customOption, inputData, keyTest);
    ASSERT_EQ(status, E_OK);

    QueryOption query = { .key = keyTest };
    std::vector<UnifiedData> unifiedDataSet;
    SetHapToken2();
    status = UdmfClient::GetInstance().GetBatchData(query, unifiedDataSet);
    EXPECT_EQ(status, E_NO_PERMISSION);

    AddPrivilege(query);
    SetHapToken2();
    status = UdmfClient::GetInstance().GetBatchData(query, unifiedDataSet);
    EXPECT_EQ(status, E_OK);
    query.intention = Intention::UD_INTENTION_PICKER;
    status = UdmfClient::GetInstance().GetBatchData(query, unifiedDataSet);
    EXPECT_EQ(status, E_OK);
    status = UdmfClient::GetInstance().DeleteData(query, unifiedDataSet);
    ASSERT_EQ(status, E_OK);
    LOG_INFO(UDMF_TEST, "SetData002 end.");
}

/**
* @tc.name: SetData003
* @tc.desc: Set data with invalid params UD_INTENTION_PICKER
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientFileMangerTest, SetData003, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetData003 begin.");
    CustomOption customOption = { .intention = Intention::UD_INTENTION_PICKER };
    UnifiedData inputData;
    std::string keyTest;
    std::vector<std::shared_ptr<UnifiedRecord>> inputRecords;
    std::string uri = "file://file_11.txt";
    inputRecords.emplace_back(std::make_shared<File>(UDType::FILE, "this is a oriUri"+uri));
    inputData.SetRecords(inputRecords);
    auto status = UdmfClient::GetInstance().SetData(customOption, inputData, keyTest);
    ASSERT_EQ(status, E_OK);

    QueryOption query = { .key = keyTest };
    std::vector<UnifiedData> unifiedDataSet;
    SetHapToken2();
    status = UdmfClient::GetInstance().GetBatchData(query, unifiedDataSet);
    EXPECT_EQ(status, E_NO_PERMISSION);
    AddPrivilege(query);
    SetHapToken2();
    query.intention = Intention::UD_INTENTION_DATA_HUB;
    status = UdmfClient::GetInstance().GetBatchData(query, unifiedDataSet);
    ASSERT_EQ(status, E_INVALID_PARAMETERS);

    QueryOption query1;
    status = UdmfClient::GetInstance().GetBatchData(query1, unifiedDataSet);
    ASSERT_EQ(status, E_INVALID_PARAMETERS);
    query1.intention = Intention::UD_INTENTION_SYSTEM_SHARE;
    status = UdmfClient::GetInstance().GetBatchData(query1, unifiedDataSet);
    ASSERT_EQ(status, E_INVALID_PARAMETERS);
    query1.intention = Intention::UD_INTENTION_PICKER;
    status = UdmfClient::GetInstance().GetBatchData(query1, unifiedDataSet);
    ASSERT_EQ(status, E_INVALID_PARAMETERS);

    query.intention = Intention::UD_INTENTION_PICKER;
    status = UdmfClient::GetInstance().DeleteData(query, unifiedDataSet);
    ASSERT_EQ(status, E_OK);
    LOG_INFO(UDMF_TEST, "SetData003 end.");
}

/**
* @tc.name: SetData004
* @tc.desc: Set data with invalid params UD_INTENTION_PICKER
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientFileMangerTest, SetData004, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetData004 begin.");
    CustomOption customOption = { .intention = Intention::UD_INTENTION_PICKER };
    UnifiedData inputData;
    std::string keyTest;
    std::vector<std::shared_ptr<UnifiedRecord>> inputRecords;
    std::string uri = "file://file_11.txt";
    inputRecords.emplace_back(std::make_shared<File>(UDType::FILE, "this is a oriUri"+uri));
    inputData.SetRecords(inputRecords);
    auto status = UdmfClient::GetInstance().SetData(customOption, inputData, keyTest);
    ASSERT_EQ(status, E_OK);

    QueryOption query = { .key = keyTest };
    std::vector<UnifiedData> unifiedDataSet;
    SetHapToken2();
    status = UdmfClient::GetInstance().GetBatchData(query, unifiedDataSet);
    EXPECT_EQ(status, E_NO_PERMISSION);
    AddPrivilege(query);
    SetHapToken2();

    QueryOption query1;
    query1.key = "udmf://aaabbbccc/com.hmos.test/CSl;cdcGFcmdkasaccCSCAAScscdc";
    status = UdmfClient::GetInstance().GetBatchData(query1, unifiedDataSet);
    ASSERT_EQ(status, E_INVALID_PARAMETERS);
    query1.intention = Intention::UD_INTENTION_DATA_HUB;
    status = UdmfClient::GetInstance().GetBatchData(query1, unifiedDataSet);
    ASSERT_EQ(status, E_INVALID_PARAMETERS);
    query1.intention = Intention::UD_INTENTION_PICKER;
    status = UdmfClient::GetInstance().GetBatchData(query1, unifiedDataSet);
    ASSERT_EQ(status, E_INVALID_PARAMETERS);

    status = UdmfClient::GetInstance().DeleteData(query, unifiedDataSet);
    ASSERT_EQ(status, E_OK);
    LOG_INFO(UDMF_TEST, "SetData003 end.");
}

/**
* @tc.name: SetData005
* @tc.desc: one over 2MB record UD_INTENTION_PICKER
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientFileMangerTest, SetData005, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetData005 begin.");
    CustomOption customOption = { .intention = Intention::UD_INTENTION_PICKER };
    UnifiedData inputData;
    std::string key;
    UDDetails details;
    std::string value;
    int64_t maxSize = 512 * 1024;
    for (int64_t i = 0; i < maxSize; ++i) {
        value += "11";
    }
    std::vector<std::shared_ptr<UnifiedRecord>> inputRecords;
    std::string fileName = "file_" + value + ".txt";
    std::string uri = "file://" + fileName;
    inputRecords.emplace_back(std::make_shared<File>(UDType::FILE, "this is a oriUri"+uri));
    inputData.SetRecords(inputRecords);
    int64_t start = CountTime();
    auto status = UdmfClient::GetInstance().SetData(customOption, inputData, key);
    int64_t end = CountTime();
    LOG_INFO(UDMF_TEST, "picker setdata 1000 cost timet:%{public}" PRIi64, (end - start));
    ASSERT_EQ(status, E_OK);

    QueryOption query = { .key = key };
    std::vector<UnifiedData> unifiedDataSet;
    SetHapToken2();
    status = UdmfClient::GetInstance().GetBatchData(query, unifiedDataSet);
    EXPECT_EQ(status, E_NO_PERMISSION);

    AddPrivilege(query);
    SetHapToken2();
    start = CountTime();
    status = UdmfClient::GetInstance().GetBatchData(query, unifiedDataSet);
    end = CountTime();
    LOG_INFO(UDMF_TEST, "picker getdata 2MB record cost timet:%{public}" PRIi64, (end - start));
    ASSERT_EQ(status, E_OK);
    status = UdmfClient::GetInstance().DeleteData(query, unifiedDataSet);
    ASSERT_EQ(status, E_OK);
    LOG_INFO(UDMF_TEST, "SetData005 end.");
}

/**
* @tc.name: SetData006
* @tc.desc: two 2MB record UD_INTENTION_PICKER
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientFileMangerTest, SetData006, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetData006 begin.");

    CustomOption customOption = { .intention = Intention::UD_INTENTION_PICKER };
    std::string key;
    std::string value;
    UnifiedData inputData;
    int64_t maxSize = 512 * 1024;
    for (int64_t i = 0; i < maxSize; ++i) {
        value += "11";
    }
    std::vector<std::shared_ptr<UnifiedRecord>> inputRecords;
    std::string uri = "file://file_" + value + ".txt";
    for (int i = 0; i < 2; ++i) {
        inputRecords.emplace_back(std::make_shared<File>(UDType::FILE, "this is a oriUri"+uri));
    }
    inputData.SetRecords(inputRecords);

    int64_t start = CountTime();
    auto status = UdmfClient::GetInstance().SetData(customOption, inputData, key);
    int64_t end = CountTime();
    LOG_INFO(UDMF_TEST, "picker setdata two 2MB record cost timet:%{public}" PRIi64, (end - start));
    ASSERT_EQ(status, E_OK);

    QueryOption query = { .key = key };
    std::vector<UnifiedData> unifiedDataSet;
    SetHapToken2();
    status = UdmfClient::GetInstance().GetBatchData(query, unifiedDataSet);
    EXPECT_EQ(status, E_NO_PERMISSION);

    AddPrivilege(query);
    SetHapToken2();
    start = CountTime();
    status = UdmfClient::GetInstance().GetBatchData(query, unifiedDataSet);
    end = CountTime();
    LOG_INFO(UDMF_TEST, "picker getdata two 2MB record cost timet:%{public}" PRIi64, (end - start));
    ASSERT_EQ(status, E_OK);
    status = UdmfClient::GetInstance().DeleteData(query, unifiedDataSet);
    ASSERT_EQ(status, E_OK);
    LOG_INFO(UDMF_TEST, "SetData006 end.");
}

/**
* @tc.name: SetData007
* @tc.desc: Set multiple record with valid params and get data
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientFileMangerTest, SetData007, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetData007 begin.");

    CustomOption customOption = {.intention = Intention::UD_INTENTION_PICKER};
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

    QueryOption query = { .key = key };
    std::vector<UnifiedData> unifiedDataSet;
    SetHapToken2();
    status = UdmfClient::GetInstance().GetBatchData(query, unifiedDataSet);
    EXPECT_EQ(status, E_NO_PERMISSION);

    AddPrivilege(query);
    SetHapToken2();

    status = UdmfClient::GetInstance().GetBatchData(query, unifiedDataSet);
    ASSERT_EQ(status, E_OK);
    auto outputRecords = unifiedDataSet[0].GetRecords();
    ASSERT_EQ(inputRecords.size(), outputRecords.size());
    for (size_t i = 0; i < outputRecords.size(); ++i) {
        ASSERT_EQ(outputRecords[i]->GetType(), inputRecords[i]->GetType());
    }
    status = UdmfClient::GetInstance().DeleteData(query, unifiedDataSet);
    ASSERT_EQ(status, E_OK);
    LOG_INFO(UDMF_TEST, "SetData007 end.");
}

/**
* @tc.name: SetData008
* @tc.desc: Set data with invalid params
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientFileMangerTest, SetData008, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetData008 begin.");
    CustomOption option = { .intention = Intention::UD_INTENTION_MENU };
    UnifiedData data;
    std::string key;
    auto status = UdmfClient::GetInstance().SetData(option, data, key);
    EXPECT_EQ(status, E_INVALID_PARAMETERS);

    option = {};
    status = UdmfClient::GetInstance().SetData(option, data, key);
    EXPECT_EQ(status, E_INVALID_PARAMETERS);

    option = { .intention = Intention::UD_INTENTION_BASE };
    status = UdmfClient::GetInstance().SetData(option, data, key);
    EXPECT_EQ(status, E_INVALID_PARAMETERS);
    LOG_INFO(UDMF_TEST, "SetData008 end.");
}

/**
* @tc.name: SetData009
* @tc.desc: Set data with valid params UD_INTENTION_MENU
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientFileMangerTest, SetData009, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetData009 begin.");
    CustomOption customOption = { .intention = Intention::UD_INTENTION_MENU };
    UnifiedData inputData;
    std::string keyTest;
    std::vector<std::shared_ptr<UnifiedRecord>> inputRecords;

    std::string uri = "file://file_11.txt";
    inputRecords.emplace_back(std::make_shared<File>(UDType::FILE, "this is a oriUri"+uri));
    inputData.SetRecords(inputRecords);
    auto status = UdmfClient::GetInstance().SetData(customOption, inputData, keyTest);
    ASSERT_EQ(status, E_OK);

    QueryOption query = { .key = keyTest };
    std::vector<UnifiedData> unifiedDataSet;
    SetHapToken2();
    status = UdmfClient::GetInstance().GetBatchData(query, unifiedDataSet);
    EXPECT_EQ(status, E_NO_PERMISSION);

    AddPrivilege(query);
    SetHapToken2();

    status = UdmfClient::GetInstance().GetBatchData(query, unifiedDataSet);
    EXPECT_EQ(status, E_OK);

    query.intention = Intention::UD_INTENTION_MENU;
    status = UdmfClient::GetInstance().GetBatchData(query, unifiedDataSet);
    EXPECT_EQ(status, E_OK);
    status = UdmfClient::GetInstance().DeleteData(query, unifiedDataSet);
    ASSERT_EQ(status, E_OK);
    LOG_INFO(UDMF_TEST, "SetData009 end.");
}

/**
* @tc.name: SetData010
* @tc.desc: Set data with invalid params UD_INTENTION_MENU
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientFileMangerTest, SetData010, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetData010 begin.");
    CustomOption customOption = { .intention = Intention::UD_INTENTION_MENU };
    UnifiedData inputData;
    std::string keyTest;
    std::vector<std::shared_ptr<UnifiedRecord>> inputRecords;
    std::string uri = "file://file_11.txt";
    inputRecords.emplace_back(std::make_shared<File>(UDType::FILE, "this is a oriUri"+uri));
    inputData.SetRecords(inputRecords);
    auto status = UdmfClient::GetInstance().SetData(customOption, inputData, keyTest);
    ASSERT_EQ(status, E_OK);

    QueryOption query = { .key = keyTest };
    std::vector<UnifiedData> unifiedDataSet;
    SetHapToken2();
    status = UdmfClient::GetInstance().GetBatchData(query, unifiedDataSet);
    EXPECT_EQ(status, E_NO_PERMISSION);
    AddPrivilege(query);
    SetHapToken2();
    query.intention = Intention::UD_INTENTION_DATA_HUB;
    status = UdmfClient::GetInstance().GetBatchData(query, unifiedDataSet);
    ASSERT_EQ(status, E_INVALID_PARAMETERS);

    QueryOption query1;
    status = UdmfClient::GetInstance().GetBatchData(query1, unifiedDataSet);
    ASSERT_EQ(status, E_INVALID_PARAMETERS);
    query1.intention = Intention::UD_INTENTION_SYSTEM_SHARE;
    status = UdmfClient::GetInstance().GetBatchData(query1, unifiedDataSet);
    ASSERT_EQ(status, E_INVALID_PARAMETERS);
    query1.intention = Intention::UD_INTENTION_MENU;
    status = UdmfClient::GetInstance().GetBatchData(query1, unifiedDataSet);
    ASSERT_EQ(status, E_INVALID_PARAMETERS);

    query.intention = Intention::UD_INTENTION_MENU;
    status = UdmfClient::GetInstance().DeleteData(query, unifiedDataSet);
    ASSERT_EQ(status, E_OK);
    LOG_INFO(UDMF_TEST, "SetData010 end.");
}

/**
* @tc.name: SetData011
* @tc.desc: Set data with invalid params UD_INTENTION_MENU
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientFileMangerTest, SetData011, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetData011 begin.");
    CustomOption customOption = { .intention = Intention::UD_INTENTION_MENU };
    UnifiedData inputData;
    std::string keyTest;
    std::vector<std::shared_ptr<UnifiedRecord>> inputRecords;
    std::string uri = "file://file_11.txt";
    inputRecords.emplace_back(std::make_shared<File>(UDType::FILE, "this is a oriUri"+uri));
    inputData.SetRecords(inputRecords);
    auto status = UdmfClient::GetInstance().SetData(customOption, inputData, keyTest);
    ASSERT_EQ(status, E_OK);

    QueryOption query = { .key = keyTest };
    std::vector<UnifiedData> unifiedDataSet;
    SetHapToken2();
    status = UdmfClient::GetInstance().GetBatchData(query, unifiedDataSet);
    EXPECT_EQ(status, E_NO_PERMISSION);
    AddPrivilege(query);
    SetHapToken2();

    QueryOption query1;
    query1.key = "udmf://aaabbbccc/com.hmos.test/CSl;cdcGFcmdkasaccCSCAAScscdc";
    status = UdmfClient::GetInstance().GetBatchData(query1, unifiedDataSet);
    ASSERT_EQ(status, E_INVALID_PARAMETERS);
    query1.intention = Intention::UD_INTENTION_DATA_HUB;
    status = UdmfClient::GetInstance().GetBatchData(query1, unifiedDataSet);
    ASSERT_EQ(status, E_INVALID_PARAMETERS);
    query1.intention = Intention::UD_INTENTION_MENU;
    status = UdmfClient::GetInstance().GetBatchData(query1, unifiedDataSet);
    ASSERT_EQ(status, E_INVALID_PARAMETERS);

    status = UdmfClient::GetInstance().DeleteData(query, unifiedDataSet);
    ASSERT_EQ(status, E_OK);
    LOG_INFO(UDMF_TEST, "SetData011 end.");
}

/**
* @tc.name: SetData012
* @tc.desc: one over 2MB record UD_INTENTION_MENU
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientFileMangerTest, SetData012, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetData012 begin.");

    CustomOption customOption = { .intention = Intention::UD_INTENTION_MENU };
    UnifiedData inputData;
    std::string key;
    UDDetails details;
    std::string value;
    int64_t maxSize = 512 * 1024;
    for (int64_t i = 0; i < maxSize; ++i) {
        value += "11";
    }
    std::vector<std::shared_ptr<UnifiedRecord>> inputRecords;
    std::string fileName = "file_" + value + ".txt";
    std::string uri = "file://" + fileName;
    inputRecords.emplace_back(std::make_shared<File>(UDType::FILE, "this is a oriUri"+uri));
    inputData.SetRecords(inputRecords);

    int64_t start = CountTime();
    auto status = UdmfClient::GetInstance().SetData(customOption, inputData, key);
    int64_t end = CountTime();
    LOG_INFO(UDMF_TEST, "rightclick setdata 2MB record cost timet:%{public}" PRIi64, (end - start));
    ASSERT_EQ(status, E_OK);

    QueryOption query = { .key = key };
    std::vector<UnifiedData> unifiedDataSet;
    SetHapToken2();
    status = UdmfClient::GetInstance().GetBatchData(query, unifiedDataSet);
    EXPECT_EQ(status, E_NO_PERMISSION);

    AddPrivilege(query);
    SetHapToken2();

    start = CountTime();
    status = UdmfClient::GetInstance().GetBatchData(query, unifiedDataSet);
    end = CountTime();
    LOG_INFO(UDMF_TEST, "rightclick getdata 2MB record cost timet:%{public}" PRIi64, (end - start));
    ASSERT_EQ(status, E_OK);
    UnifiedDataHelper::SetRootPath("");
    status = UdmfClient::GetInstance().DeleteData(query, unifiedDataSet);
    ASSERT_EQ(status, E_OK);
    LOG_INFO(UDMF_TEST, "SetData012 end.");
}

/**
* @tc.name: SetData013
* @tc.desc: two 2MB record UD_INTENTION_MENU
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientFileMangerTest, SetData013, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetData013 begin.");

    CustomOption customOption = { .intention = Intention::UD_INTENTION_MENU };
    UnifiedData inputData;
    std::string key;
    UDDetails details;
    std::string value;
    int64_t maxSize = 512 * 1024;
    for (int64_t i = 0; i < maxSize; ++i) {
        value += "11";
    }
    std::vector<std::shared_ptr<UnifiedRecord>> inputRecords;
    std::string uri = "file://file_" + value + ".txt";
    for (int i = 0; i < 2; ++i) {
        inputRecords.emplace_back(std::make_shared<File>(UDType::FILE, "this is a oriUri"+uri));
    }
    inputData.SetRecords(inputRecords);

    int64_t start = CountTime();
    auto status = UdmfClient::GetInstance().SetData(customOption, inputData, key);
    int64_t end = CountTime();
    LOG_INFO(UDMF_TEST, "setdata 4MB cost timet:%{public}" PRIi64, (end - start));
    ASSERT_EQ(status, E_OK);

    QueryOption query = { .key = key };
    std::vector<UnifiedData> unifiedDataSet;
    SetHapToken2();
    status = UdmfClient::GetInstance().GetBatchData(query, unifiedDataSet);
    EXPECT_EQ(status, E_NO_PERMISSION);

    AddPrivilege(query);
    SetHapToken2();

    start = CountTime();
    status = UdmfClient::GetInstance().GetBatchData(query, unifiedDataSet);
    end = CountTime();
    LOG_INFO(UDMF_TEST, "getdata 4MB cost timet:%{public}" PRIi64, (end - start));
    ASSERT_EQ(status, E_OK);
    status = UdmfClient::GetInstance().DeleteData(query, unifiedDataSet);
    ASSERT_EQ(status, E_OK);
    LOG_INFO(UDMF_TEST, "SetData013 end.");
}

/**
* @tc.name: SetData014
* @tc.desc: Set multiple record with valid params and get data
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientFileMangerTest, SetData014, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetData014 begin.");

    CustomOption customOption = {.intention = Intention::UD_INTENTION_MENU};
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

    QueryOption query = { .key = key };
    std::vector<UnifiedData> unifiedDataSet;
    SetHapToken2();
    status = UdmfClient::GetInstance().GetBatchData(query, unifiedDataSet);
    EXPECT_EQ(status, E_NO_PERMISSION);

    AddPrivilege(query);
    SetHapToken2();

    status = UdmfClient::GetInstance().GetBatchData(query, unifiedDataSet);
    ASSERT_EQ(status, E_OK);
    auto outputRecords = unifiedDataSet[0].GetRecords();
    ASSERT_EQ(inputRecords.size(), outputRecords.size());
    for (size_t i = 0; i < outputRecords.size(); ++i) {
        ASSERT_EQ(outputRecords[i]->GetType(), inputRecords[i]->GetType());
    }
    status = UdmfClient::GetInstance().DeleteData(query, unifiedDataSet);
    ASSERT_EQ(status, E_OK);
    LOG_INFO(UDMF_TEST, "SetData014 end.");
}

/**
* @tc.name: SetData015
* @tc.desc: Set data with invalid params
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientFileMangerTest, SetData015, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetData015 begin.");

    CustomOption option = { .intention = Intention::UD_INTENTION_SYSTEM_SHARE };
    UnifiedData data;
    std::string key;
    auto status = UdmfClient::GetInstance().SetData(option, data, key);
    EXPECT_EQ(status, E_INVALID_PARAMETERS);

    option = {};
    status = UdmfClient::GetInstance().SetData(option, data, key);
    EXPECT_EQ(status, E_INVALID_PARAMETERS);

    option = { .intention = Intention::UD_INTENTION_BASE };
    status = UdmfClient::GetInstance().SetData(option, data, key);
    EXPECT_EQ(status, E_INVALID_PARAMETERS);
    LOG_INFO(UDMF_TEST, "SetData015 end.");
}

/**
* @tc.name: SetData016
* @tc.desc: Set data with valid params UD_INTENTION_SYSTEM_SHARE
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientFileMangerTest, SetData016, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetData016 begin.");
    CustomOption customOption = { .intention = Intention::UD_INTENTION_SYSTEM_SHARE };
    UnifiedData inputData;
    std::string keyTest;
    std::vector<std::shared_ptr<UnifiedRecord>> inputRecords;

    std::string uri = "file://file_11.txt";
    inputRecords.emplace_back(std::make_shared<File>(UDType::FILE, "this is a oriUri"+uri));
    inputData.SetRecords(inputRecords);
    auto status = UdmfClient::GetInstance().SetData(customOption, inputData, keyTest);
    ASSERT_EQ(status, E_OK);

    QueryOption query = { .key = keyTest };
    std::vector<UnifiedData> unifiedDataSet;
    SetHapToken2();
    status = UdmfClient::GetInstance().GetBatchData(query, unifiedDataSet);
    EXPECT_EQ(status, E_NO_PERMISSION);

    AddPrivilege(query);
    SetHapToken2();

    status = UdmfClient::GetInstance().GetBatchData(query, unifiedDataSet);
    EXPECT_EQ(status, E_OK);

    query.intention = Intention::UD_INTENTION_SYSTEM_SHARE;
    status = UdmfClient::GetInstance().GetBatchData(query, unifiedDataSet);
    EXPECT_EQ(status, E_OK);
    status = UdmfClient::GetInstance().DeleteData(query, unifiedDataSet);
    ASSERT_EQ(status, E_OK);
    LOG_INFO(UDMF_TEST, "SetData016 end.");
}

/**
* @tc.name: SetData017
* @tc.desc: Set data with invalid params UD_INTENTION_SYSTEM_SHARE
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientFileMangerTest, SetData017, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetData017 begin.");
    CustomOption customOption = { .intention = Intention::UD_INTENTION_SYSTEM_SHARE };
    UnifiedData inputData;
    std::string keyTest;
    std::vector<std::shared_ptr<UnifiedRecord>> inputRecords;
    std::string uri = "file://file_11.txt";
    inputRecords.emplace_back(std::make_shared<File>(UDType::FILE, "this is a oriUri"+uri));
    inputData.SetRecords(inputRecords);
    auto status = UdmfClient::GetInstance().SetData(customOption, inputData, keyTest);
    ASSERT_EQ(status, E_OK);

    QueryOption query = { .key = keyTest };
    std::vector<UnifiedData> unifiedDataSet;
    SetHapToken2();
    status = UdmfClient::GetInstance().GetBatchData(query, unifiedDataSet);
    EXPECT_EQ(status, E_NO_PERMISSION);
    AddPrivilege(query);
    SetHapToken2();
    query.intention = Intention::UD_INTENTION_DATA_HUB;
    status = UdmfClient::GetInstance().GetBatchData(query, unifiedDataSet);
    ASSERT_EQ(status, E_INVALID_PARAMETERS);

    QueryOption query1;
    status = UdmfClient::GetInstance().GetBatchData(query1, unifiedDataSet);
    ASSERT_EQ(status, E_INVALID_PARAMETERS);
    query1.intention = Intention::UD_INTENTION_MENU;
    status = UdmfClient::GetInstance().GetBatchData(query1, unifiedDataSet);
    ASSERT_EQ(status, E_INVALID_PARAMETERS);
    query1.intention = Intention::UD_INTENTION_SYSTEM_SHARE;
    status = UdmfClient::GetInstance().GetBatchData(query1, unifiedDataSet);
    ASSERT_EQ(status, E_INVALID_PARAMETERS);

    query.intention = Intention::UD_INTENTION_SYSTEM_SHARE;
    status = UdmfClient::GetInstance().DeleteData(query, unifiedDataSet);
    ASSERT_EQ(status, E_OK);
    LOG_INFO(UDMF_TEST, "SetData017 end.");
}

/**
* @tc.name: SetData018
* @tc.desc: Set data with invalid params UD_INTENTION_SYSTEM_SHARE
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientFileMangerTest, SetData018, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetData018 begin.");
    CustomOption customOption = { .intention = Intention::UD_INTENTION_SYSTEM_SHARE };
    UnifiedData inputData;
    std::string keyTest;
    std::vector<std::shared_ptr<UnifiedRecord>> inputRecords;
    std::string uri = "file://file_11.txt";
    inputRecords.emplace_back(std::make_shared<File>(UDType::FILE, "this is a oriUri"+uri));
    inputData.SetRecords(inputRecords);
    auto status = UdmfClient::GetInstance().SetData(customOption, inputData, keyTest);
    ASSERT_EQ(status, E_OK);

    QueryOption query = { .key = keyTest };
    std::vector<UnifiedData> unifiedDataSet;
    SetHapToken2();
    status = UdmfClient::GetInstance().GetBatchData(query, unifiedDataSet);
    EXPECT_EQ(status, E_NO_PERMISSION);
    AddPrivilege(query);
    SetHapToken2();

    QueryOption query1;
    query1.key = "udmf://aaabbbccc/com.hmos.test/CSl;cdcGFcmdkasaccCSCAAScscdc";
    status = UdmfClient::GetInstance().GetBatchData(query1, unifiedDataSet);
    ASSERT_EQ(status, E_INVALID_PARAMETERS);
    query1.intention = Intention::UD_INTENTION_DATA_HUB;
    status = UdmfClient::GetInstance().GetBatchData(query1, unifiedDataSet);
    ASSERT_EQ(status, E_INVALID_PARAMETERS);
    query1.intention = Intention::UD_INTENTION_SYSTEM_SHARE;
    status = UdmfClient::GetInstance().GetBatchData(query1, unifiedDataSet);
    ASSERT_EQ(status, E_INVALID_PARAMETERS);
    status = UdmfClient::GetInstance().DeleteData(query, unifiedDataSet);
    ASSERT_EQ(status, E_OK);
    LOG_INFO(UDMF_TEST, "SetData018 end.");
}

/**
* @tc.name: SetData019
* @tc.desc: one over 2MB record UD_INTENTION_SYSTEM_SHARE
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientFileMangerTest, SetData019, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetData019 begin.");

    CustomOption customOption = { .intention = Intention::UD_INTENTION_SYSTEM_SHARE };
    UnifiedData inputData;
    std::string key;
    UDDetails details;
    std::string value;
    int64_t maxSize = 512 * 1024;
    for (int64_t i = 0; i < maxSize; ++i) {
        value += "11";
    }
    std::vector<std::shared_ptr<UnifiedRecord>> inputRecords;
    std::string fileName = "file_" + value + ".txt";
    std::string uri = "file://" + fileName;
    inputRecords.emplace_back(std::make_shared<File>(UDType::FILE, "this is a oriUri"+uri));
    inputData.SetRecords(inputRecords);

    int64_t start = CountTime();
    auto status = UdmfClient::GetInstance().SetData(customOption, inputData, key);
    int64_t end = CountTime();
    LOG_INFO(UDMF_TEST, "systemshare setdata one over 2MB record cost timet:%{public}" PRIi64, (end - start));
    ASSERT_EQ(status, E_OK);

    QueryOption query = { .key = key };
    std::vector<UnifiedData> unifiedDataSet;
    SetHapToken2();
    status = UdmfClient::GetInstance().GetBatchData(query, unifiedDataSet);
    EXPECT_EQ(status, E_NO_PERMISSION);

    AddPrivilege(query);
    SetHapToken2();

    start = CountTime();
    status = UdmfClient::GetInstance().GetBatchData(query, unifiedDataSet);
    end = CountTime();
    LOG_INFO(UDMF_TEST, "systemshare getdata one over 2MB record cost timet:%{public}" PRIi64, (end - start));
    ASSERT_EQ(status, E_OK);
    UnifiedDataHelper::SetRootPath("");
    status = UdmfClient::GetInstance().DeleteData(query, unifiedDataSet);
    ASSERT_EQ(status, E_OK);
    LOG_INFO(UDMF_TEST, "SetData019 end.");
}

/**
* @tc.name: SetData020
* @tc.desc: two 2MB record UD_INTENTION_SYSTEM_SHARE
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientFileMangerTest, SetData020, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetData020 begin.");

    CustomOption customOption = { .intention = Intention::UD_INTENTION_SYSTEM_SHARE };
    UnifiedData inputData;
    std::string key;
    UDDetails details;
    std::string value;
    int64_t maxSize = 512 * 1024;
    for (int64_t i = 0; i < maxSize; ++i) {
        value += "11";
    }
    std::vector<std::shared_ptr<UnifiedRecord>> inputRecords;
    std::string uri = "file://file_" + value + ".txt";
    for (int i = 0; i < 2; ++i) {
        inputRecords.emplace_back(std::make_shared<File>(UDType::FILE, "this is a oriUri"+uri));
    }
    inputData.SetRecords(inputRecords);

    int64_t start = CountTime();
    auto status = UdmfClient::GetInstance().SetData(customOption, inputData, key);
    int64_t end = CountTime();
    LOG_INFO(UDMF_TEST, "getdata 1 cost timet:%{public}" PRIi64, (end - start));
    ASSERT_EQ(status, E_OK);

    QueryOption query = { .key = key };
    std::vector<UnifiedData> unifiedDataSet;
    SetHapToken2();
    status = UdmfClient::GetInstance().GetBatchData(query, unifiedDataSet);
    EXPECT_EQ(status, E_NO_PERMISSION);

    AddPrivilege(query);
    SetHapToken2();

    start = CountTime();
    status = UdmfClient::GetInstance().GetBatchData(query, unifiedDataSet);
    end = CountTime();
    LOG_INFO(UDMF_TEST, "getdata 1 cost timet:%{public}" PRIi64, (end - start));
    ASSERT_EQ(status, E_OK);
    status = UdmfClient::GetInstance().DeleteData(query, unifiedDataSet);
    ASSERT_EQ(status, E_OK);

    LOG_INFO(UDMF_TEST, "SetData020 end.");
}

/**
* @tc.name: SetData021
* @tc.desc: Set multiple record with valid params and get data
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientFileMangerTest, SetData021, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetData021 begin.");

    CustomOption customOption = {.intention = Intention::UD_INTENTION_SYSTEM_SHARE};
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

    QueryOption query = { .key = key };
    std::vector<UnifiedData> unifiedDataSet;
    SetHapToken2();
    status = UdmfClient::GetInstance().GetBatchData(query, unifiedDataSet);
    EXPECT_EQ(status, E_NO_PERMISSION);

    AddPrivilege(query);
    SetHapToken2();

    status = UdmfClient::GetInstance().GetBatchData(query, unifiedDataSet);
    ASSERT_EQ(status, E_OK);
    auto outputRecords = unifiedDataSet[0].GetRecords();
    ASSERT_EQ(inputRecords.size(), outputRecords.size());
    for (size_t i = 0; i < outputRecords.size(); ++i) {
        ASSERT_EQ(outputRecords[i]->GetType(), inputRecords[i]->GetType());
    }
    status = UdmfClient::GetInstance().DeleteData(query, unifiedDataSet);
    ASSERT_EQ(status, E_OK);
    LOG_INFO(UDMF_TEST, "SetData018 end.");
}

/**
* @tc.name: AddPrivilege001
* @tc.desc: Add privilege with valid params
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientFileMangerTest, AddPrivilege001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "AddPrivilege001 begin.");
    CustomOption option1 = { .intention = Intention::UD_INTENTION_PICKER };
    UnifiedData data;
    auto text = std::make_shared<Text>();
    UDDetails details;
    details.insert({ "udmf_key", "udmf_value" });
    text->SetDetails(details);
    data.AddRecord(text);
    std::string key;
    auto status = UdmfClient::GetInstance().SetData(option1, data, key);
    ASSERT_EQ(status, E_OK);

    QueryOption query = { .key = key };
    Privilege privilege;
    privilege.tokenId = AccessTokenKit::GetHapTokenID(userId, "ohos.file.manger.test.demo2", instIndex);
    privilege.readPermission = "readandkeep";
    privilege.writePermission = "writePermission";
    SetNativeToken("foundation");
    status = UdmfClient::GetInstance().AddPrivilege(query, privilege);
    ASSERT_EQ(status, E_OK);
    query.intention = Intention::UD_INTENTION_SYSTEM_SHARE;
    SetNativeToken("foundation");
    status = UdmfClient::GetInstance().AddPrivilege(query, privilege);
    ASSERT_EQ(status, E_NO_PERMISSION);
    privilege.readPermission = "readpermission";
    query.intention = Intention::UD_INTENTION_PICKER;
    status = UdmfClient::GetInstance().AddPrivilege(query, privilege);
    ASSERT_EQ(status, E_OK);
    LOG_INFO(UDMF_TEST, "AddPrivilege001 end.");
}

/**
* @tc.name: AddPrivilege002
* @tc.desc: Add privilege with valid params
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientFileMangerTest, AddPrivilege002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "AddPrivilege002 begin.");
    CustomOption option1 = { .intention = Intention::UD_INTENTION_MENU };
    UnifiedData data;
    auto text = std::make_shared<Text>();
    UDDetails details;
    details.insert({ "udmf_key", "udmf_value" });
    text->SetDetails(details);
    data.AddRecord(text);
    std::string key;
    auto status = UdmfClient::GetInstance().SetData(option1, data, key);
    ASSERT_EQ(status, E_OK);

    QueryOption query = { .key = key };
    Privilege privilege;
    privilege.tokenId = AccessTokenKit::GetHapTokenID(userId, "ohos.file.manger.test.demo2", instIndex);
    privilege.readPermission = "readandkeep";
    privilege.writePermission = "writePermission";
    SetNativeToken("foundation");

    status = UdmfClient::GetInstance().AddPrivilege(query, privilege);
    ASSERT_EQ(status, E_OK);
    query.intention = Intention::UD_INTENTION_SYSTEM_SHARE;
    SetNativeToken("foundation");
    status = UdmfClient::GetInstance().AddPrivilege(query, privilege);
    ASSERT_EQ(status, E_NO_PERMISSION);
    privilege.readPermission = "readpermission";
    query.intention = Intention::UD_INTENTION_MENU;
    status = UdmfClient::GetInstance().AddPrivilege(query, privilege);
    ASSERT_EQ(status, E_OK);
    LOG_INFO(UDMF_TEST, "AddPrivilege002 end.");
}

/**
* @tc.name: AddPrivilege003
* @tc.desc: Add privilege with valid params
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientFileMangerTest, AddPrivilege003, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "AddPrivilege003 begin.");

    CustomOption option1 = { .intention = Intention::UD_INTENTION_SYSTEM_SHARE };
    UnifiedData data;
    auto text = std::make_shared<Text>();
    UDDetails details;
    details.insert({ "udmf_key", "udmf_value" });
    text->SetDetails(details);
    data.AddRecord(text);
    std::string key;
    auto status = UdmfClient::GetInstance().SetData(option1, data, key);
    ASSERT_EQ(status, E_OK);

    QueryOption query = { .key = key };
    Privilege privilege;
    privilege.tokenId = AccessTokenKit::GetHapTokenID(userId, "ohos.file.manger.test.demo2", instIndex);
    privilege.readPermission = "readandkeep";
    privilege.writePermission = "writePermission";
    SetNativeToken("foundation");
    status = UdmfClient::GetInstance().AddPrivilege(query, privilege);
    ASSERT_EQ(status, E_OK);
    query.intention = Intention::UD_INTENTION_MENU;
    status = UdmfClient::GetInstance().AddPrivilege(query, privilege);
    ASSERT_EQ(status, E_NO_PERMISSION);
    privilege.readPermission = "readpermission";
    query.intention = Intention::UD_INTENTION_SYSTEM_SHARE;
    status = UdmfClient::GetInstance().AddPrivilege(query, privilege);
    ASSERT_EQ(status, E_OK);
    LOG_INFO(UDMF_TEST, "AddPrivilege003 end.");
}

/**
* @tc.name: AddPrivilege004
* @tc.desc: Add privilege with invalid params
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientFileMangerTest, AddPrivilege004, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "AddPrivilege004 begin.");

    CustomOption option1 = { .intention = Intention::UD_INTENTION_PICKER };
    UnifiedData data;
    auto text = std::make_shared<Text>();
    UDDetails details;
    details.insert({ "udmf_key", "udmf_value" });
    text->SetDetails(details);
    data.AddRecord(text);
    std::string key;
    auto status = UdmfClient::GetInstance().SetData(option1, data, key);
    ASSERT_EQ(status, E_OK);

    QueryOption query;
    Privilege privilege;
    privilege.tokenId = AccessTokenKit::GetHapTokenID(userId, "ohos.file.manger.test.demo2", instIndex);
    privilege.readPermission = "readandkeep";
    privilege.writePermission = "writePermission";
    SetNativeToken("foundation");

    status = UdmfClient::GetInstance().AddPrivilege(query, privilege);
    ASSERT_EQ(status, E_INVALID_PARAMETERS);
    query.intention = Intention::UD_INTENTION_MENU;
    status = UdmfClient::GetInstance().AddPrivilege(query, privilege);
    ASSERT_EQ(status, E_INVALID_PARAMETERS);
    query.intention = Intention::UD_INTENTION_PICKER;
    status = UdmfClient::GetInstance().AddPrivilege(query, privilege);
    ASSERT_EQ(status, E_INVALID_PARAMETERS);

    query.key = key;
    query.intention = Intention::UD_INTENTION_SYSTEM_SHARE;
    status = UdmfClient::GetInstance().AddPrivilege(query, privilege);
    ASSERT_EQ(status, E_NO_PERMISSION);
    query.intention = Intention::UD_INTENTION_PICKER;
    std::vector<UnifiedData> unifiedDataSet;
    SetHapToken2();
    status = UdmfClient::GetInstance().DeleteData(query, unifiedDataSet);
    ASSERT_EQ(status, E_OK);
    LOG_INFO(UDMF_TEST, "AddPrivilege004 end.");
}

/**
* @tc.name: AddPrivilege005
* @tc.desc: Add privilege with invalid params
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientFileMangerTest, AddPrivilege005, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "AddPrivilege005 begin.");

    CustomOption option1 = { .intention = Intention::UD_INTENTION_MENU };
    UnifiedData data;
    auto text = std::make_shared<Text>();
    UDDetails details;
    details.insert({ "udmf_key", "udmf_value" });
    text->SetDetails(details);
    data.AddRecord(text);
    std::string key;
    auto status = UdmfClient::GetInstance().SetData(option1, data, key);
    ASSERT_EQ(status, E_OK);

    QueryOption query;
    Privilege privilege;
    privilege.tokenId = AccessTokenKit::GetHapTokenID(userId, "ohos.file.manger.test.demo2", instIndex);
    privilege.readPermission = "readandkeep";
    privilege.writePermission = "writePermission";
    SetNativeToken("foundation");
    status = UdmfClient::GetInstance().AddPrivilege(query, privilege);
    ASSERT_EQ(status, E_INVALID_PARAMETERS);
    query.intention = Intention::UD_INTENTION_PICKER;
    status = UdmfClient::GetInstance().AddPrivilege(query, privilege);
    ASSERT_EQ(status, E_INVALID_PARAMETERS);
    query.intention = Intention::UD_INTENTION_MENU;
    status = UdmfClient::GetInstance().AddPrivilege(query, privilege);
    ASSERT_EQ(status, E_INVALID_PARAMETERS);
    query.key = key;
    query.intention = Intention::UD_INTENTION_PICKER;
    status = UdmfClient::GetInstance().AddPrivilege(query, privilege);
    ASSERT_EQ(status, E_NO_PERMISSION);
    query.intention = Intention::UD_INTENTION_MENU;
    std::vector<UnifiedData> unifiedDataSet;
    SetHapToken2();
    status = UdmfClient::GetInstance().DeleteData(query, unifiedDataSet);
    ASSERT_EQ(status, E_OK);
    LOG_INFO(UDMF_TEST, "AddPrivilege005 end.");
}

/**
* @tc.name: AddPrivilege006
* @tc.desc: Add privilege with invalid params
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientFileMangerTest, AddPrivilege006, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "AddPrivilege006 begin.");

    CustomOption option1 = { .intention = Intention::UD_INTENTION_SYSTEM_SHARE };
    UnifiedData data;
    auto text = std::make_shared<Text>();
    UDDetails details;
    details.insert({ "udmf_key", "udmf_value" });
    text->SetDetails(details);
    data.AddRecord(text);
    std::string key;
    auto status = UdmfClient::GetInstance().SetData(option1, data, key);
    ASSERT_EQ(status, E_OK);

    QueryOption query;
    Privilege privilege;
    privilege.tokenId = AccessTokenKit::GetHapTokenID(userId, "ohos.file.manger.test.demo2", instIndex);
    privilege.readPermission = "readandkeep";
    privilege.writePermission = "writePermission";
    SetNativeToken("foundation");
    status = UdmfClient::GetInstance().AddPrivilege(query, privilege);
    ASSERT_EQ(status, E_INVALID_PARAMETERS);
    query.intention = Intention::UD_INTENTION_MENU;
    status = UdmfClient::GetInstance().AddPrivilege(query, privilege);
    ASSERT_EQ(status, E_INVALID_PARAMETERS);
    query.intention = Intention::UD_INTENTION_SYSTEM_SHARE;
    status = UdmfClient::GetInstance().AddPrivilege(query, privilege);
    ASSERT_EQ(status, E_INVALID_PARAMETERS);
    query.key = key;
    query.intention = Intention::UD_INTENTION_MENU;
    status = UdmfClient::GetInstance().AddPrivilege(query, privilege);
    ASSERT_EQ(status, E_NO_PERMISSION);
    query.intention = Intention::UD_INTENTION_SYSTEM_SHARE;
    std::vector<UnifiedData> unifiedDataSet;
    SetHapToken2();
    status = UdmfClient::GetInstance().DeleteData(query, unifiedDataSet);
    ASSERT_EQ(status, E_OK);
    LOG_INFO(UDMF_TEST, "AddPrivilege006 end.");
}

/**
* @tc.name: AddPrivilege007
* @tc.desc: Add privilege with invalid params
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientFileMangerTest, AddPrivilege007, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "AddPrivilege007 begin.");

    CustomOption option1 = { .intention = Intention::UD_INTENTION_SYSTEM_SHARE };
    UnifiedData data;
    auto text = std::make_shared<Text>();
    UDDetails details;
    details.insert({ "udmf_key", "udmf_value" });
    text->SetDetails(details);
    data.AddRecord(text);
    std::string key;
    auto status = UdmfClient::GetInstance().SetData(option1, data, key);
    ASSERT_EQ(status, E_OK);

    QueryOption query;
    Privilege privilege;
    privilege.tokenId = AccessTokenKit::GetHapTokenID(userId, "ohos.file.manger.test.demo2", instIndex);
    privilege.readPermission = "readandkeep";
    privilege.writePermission = "writePermission";
    SetNativeToken("foundation");

    query.key = "udmf://aaabbbccc/com.hmos.test/CSl;cdcGFcmdkasaccCSCAAScscdc";
    status = UdmfClient::GetInstance().AddPrivilege(query, privilege);
    ASSERT_EQ(status, E_NO_PERMISSION);
    query.intention = Intention::UD_INTENTION_MENU;
    status = UdmfClient::GetInstance().AddPrivilege(query, privilege);
    ASSERT_EQ(status, E_NO_PERMISSION);
    query.intention = Intention::UD_INTENTION_SYSTEM_SHARE;
    status = UdmfClient::GetInstance().AddPrivilege(query, privilege);
    ASSERT_EQ(status, E_NO_PERMISSION);
    LOG_INFO(UDMF_TEST, "AddPrivilege007 end.");
}

/**
* @tc.name: AddPrivilege008
* @tc.desc: Add privilege with invalid params
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientFileMangerTest, AddPrivilege008, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "AddPrivilege008 begin.");

    CustomOption option1 = { .intention = Intention::UD_INTENTION_SYSTEM_SHARE };
    UnifiedData data;
    auto text = std::make_shared<Text>();
    UDDetails details;
    details.insert({ "udmf_key", "udmf_value" });
    text->SetDetails(details);
    data.AddRecord(text);
    std::string key;
    auto status = UdmfClient::GetInstance().SetData(option1, data, key);
    ASSERT_EQ(status, E_OK);

    QueryOption query;
    Privilege privilege;
    privilege.tokenId = AccessTokenKit::GetHapTokenID(userId, "ohos.file.manger.test.demo2", instIndex);
    privilege.readPermission = "readandkeep";
    privilege.writePermission = "writePermission";
    SetNativeToken("foundation");
    query.key = "udmf://aaabbbccc/com.hmos.test/CSl;cdcGFcmdkasaccCSCAAScscdc";
    status = UdmfClient::GetInstance().AddPrivilege(query, privilege);
    ASSERT_EQ(status, E_NO_PERMISSION);
    query.intention = Intention::UD_INTENTION_MENU;
    status = UdmfClient::GetInstance().AddPrivilege(query, privilege);
    ASSERT_EQ(status, E_NO_PERMISSION);
    query.intention = Intention::UD_INTENTION_SYSTEM_SHARE;
    status = UdmfClient::GetInstance().AddPrivilege(query, privilege);
    ASSERT_EQ(status, E_NO_PERMISSION);
    LOG_INFO(UDMF_TEST, "AddPrivilege008 end.");
}

/**
* @tc.name: AddPrivilege009
* @tc.desc: Add privilege with invalid params
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientFileMangerTest, AddPrivilege009, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "AddPrivilege009 begin.");

    CustomOption option1 = { .intention = Intention::UD_INTENTION_SYSTEM_SHARE };
    UnifiedData data;
    auto text = std::make_shared<Text>();
    UDDetails details;
    details.insert({ "udmf_key", "udmf_value" });
    text->SetDetails(details);
    data.AddRecord(text);
    std::string key;
    auto status = UdmfClient::GetInstance().SetData(option1, data, key);
    ASSERT_EQ(status, E_OK);

    QueryOption query;
    Privilege privilege;
    privilege.tokenId = AccessTokenKit::GetHapTokenID(userId, "ohos.file.manger.test.demo2", instIndex);
    privilege.readPermission = "readandkeep";
    privilege.writePermission = "writePermission";
    SetNativeToken("foundation");
    query.key = "udmf://aaabbbccc/com.hmos.test/CSl;cdcGFcmdkasaccCSCAAScscdc";
    status = UdmfClient::GetInstance().AddPrivilege(query, privilege);
    ASSERT_EQ(status, E_NO_PERMISSION);
    query.intention = Intention::UD_INTENTION_MENU;
    status = UdmfClient::GetInstance().AddPrivilege(query, privilege);
    ASSERT_EQ(status, E_NO_PERMISSION);
    query.intention = Intention::UD_INTENTION_SYSTEM_SHARE;
    status = UdmfClient::GetInstance().AddPrivilege(query, privilege);
    ASSERT_EQ(status, E_NO_PERMISSION);
    LOG_INFO(UDMF_TEST, "AddPrivilege009 end.");
}

/**
* @tc.name: DeleteData001
* @tc.desc: Delete data with UD_INTENTION_PICKER
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientFileMangerTest, DeleteData001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "DeleteData001 begin.");
    CustomOption customOption = { .intention = UD_INTENTION_PICKER };
    UnifiedData data;
    auto plainText = std::make_shared<PlainText>();
    plainText->SetContent("content1");
    data.AddRecord(plainText);
    std::string key;
    auto status = UdmfClient::GetInstance().SetData(customOption, data, key);
    ASSERT_EQ(status, E_OK);

    QueryOption queryOption;
    std::vector<UnifiedData> unifiedDataSet;
    queryOption.key = key;
    queryOption.intention = UD_INTENTION_SYSTEM_SHARE;
    status = UdmfClient::GetInstance().DeleteData(queryOption, unifiedDataSet);
    ASSERT_EQ(status, E_INVALID_PARAMETERS);
    queryOption.intention = UD_INTENTION_PICKER;
    status = UdmfClient::GetInstance().DeleteData(queryOption, unifiedDataSet);
    ASSERT_EQ(status, E_OK);
    LOG_INFO(UDMF_TEST, "DeleteData001 end.");
}

/**
* @tc.name: DeleteData002
* @tc.desc: Delete data with UD_INTENTION_PICKER
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientFileMangerTest, DeleteData002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "DeleteData002 begin.");
    CustomOption customOption = { .intention = UD_INTENTION_PICKER };
    UnifiedData data;
    auto plainText = std::make_shared<PlainText>();
    plainText->SetContent("content1");
    data.AddRecord(plainText);
    std::string key;
    auto status = UdmfClient::GetInstance().SetData(customOption, data, key);
    ASSERT_EQ(status, E_OK);

    QueryOption queryOption;
    std::vector<UnifiedData> unifiedDataSet;
    status = UdmfClient::GetInstance().DeleteData(queryOption, unifiedDataSet);
    ASSERT_EQ(status, E_INVALID_PARAMETERS);
    queryOption.intention = UD_INTENTION_PICKER;
    status = UdmfClient::GetInstance().DeleteData(queryOption, unifiedDataSet);
    ASSERT_EQ(status, E_INVALID_PARAMETERS);
    queryOption.intention = UD_INTENTION_SYSTEM_SHARE;
    status = UdmfClient::GetInstance().DeleteData(queryOption, unifiedDataSet);
    ASSERT_EQ(status, E_INVALID_PARAMETERS);

    QueryOption queryOption1 = { .key = key };
    status = UdmfClient::GetInstance().DeleteData(queryOption1, unifiedDataSet);
    ASSERT_EQ(status, E_OK);
    LOG_INFO(UDMF_TEST, "DeleteData002 end.");
}

/**
* @tc.name: DeleteData003
* @tc.desc: Delete data with UD_INTENTION_PICKER
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientFileMangerTest, DeleteData003, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "DeleteData003 begin.");
    CustomOption customOption = { .intention = UD_INTENTION_PICKER };
    UnifiedData data;
    auto plainText = std::make_shared<PlainText>();
    plainText->SetContent("content1");
    data.AddRecord(plainText);
    std::string key;
    auto status = UdmfClient::GetInstance().SetData(customOption, data, key);
    ASSERT_EQ(status, E_OK);

    QueryOption queryOption;
    std::vector<UnifiedData> unifiedDataSet;
    queryOption.key = "udmf://aaabbbccc/com.hmos.test/CSl;cdcGFcmdkasaccCSCAAScscdc";
    status = UdmfClient::GetInstance().DeleteData(queryOption, unifiedDataSet);
    ASSERT_EQ(status, E_INVALID_PARAMETERS);
    queryOption.intention = UD_INTENTION_SYSTEM_SHARE;
    status = UdmfClient::GetInstance().DeleteData(queryOption, unifiedDataSet);
    ASSERT_EQ(status, E_INVALID_PARAMETERS);
    queryOption.intention = UD_INTENTION_PICKER;
    status = UdmfClient::GetInstance().DeleteData(queryOption, unifiedDataSet);
    ASSERT_EQ(status, E_INVALID_PARAMETERS);

    QueryOption queryOption1 = { .key = key };
    status = UdmfClient::GetInstance().DeleteData(queryOption1, unifiedDataSet);
    ASSERT_EQ(status, E_OK);
    LOG_INFO(UDMF_TEST, "DeleteData003 end.");
}

/**
* @tc.name: DeleteData004
* @tc.desc: Delete data with UD_INTENTION_SYSTEM_SHARE
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientFileMangerTest, DeleteData004, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "DeleteData004 begin.");
    CustomOption customOption = { .intention = UD_INTENTION_SYSTEM_SHARE };
    UnifiedData data;
    auto plainText = std::make_shared<PlainText>();
    plainText->SetContent("content1");
    data.AddRecord(plainText);
    std::string key;
    auto status = UdmfClient::GetInstance().SetData(customOption, data, key);
    ASSERT_EQ(status, E_OK);

    QueryOption queryOption;
    std::vector<UnifiedData> unifiedDataSet;
    queryOption.key = key;
    queryOption.intention = UD_INTENTION_PICKER;
    status = UdmfClient::GetInstance().DeleteData(queryOption, unifiedDataSet);
    ASSERT_EQ(status, E_INVALID_PARAMETERS);
    queryOption.intention = UD_INTENTION_SYSTEM_SHARE;
    status = UdmfClient::GetInstance().DeleteData(queryOption, unifiedDataSet);
    ASSERT_EQ(status, E_OK);
    LOG_INFO(UDMF_TEST, "DeleteData004 end.");
}

/**
* @tc.name: DeleteData005
* @tc.desc: Delete data with UD_INTENTION_SYSTEM_SHARE
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientFileMangerTest, DeleteData005, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "DeleteData005 begin.");
    CustomOption customOption = { .intention = UD_INTENTION_SYSTEM_SHARE };
    UnifiedData data;
    auto plainText = std::make_shared<PlainText>();
    plainText->SetContent("content1");
    data.AddRecord(plainText);
    std::string key;
    auto status = UdmfClient::GetInstance().SetData(customOption, data, key);
    ASSERT_EQ(status, E_OK);

    QueryOption queryOption;
    std::vector<UnifiedData> unifiedDataSet;
    status = UdmfClient::GetInstance().DeleteData(queryOption, unifiedDataSet);
    ASSERT_EQ(status, E_INVALID_PARAMETERS);
    queryOption.intention = UD_INTENTION_PICKER;
    status = UdmfClient::GetInstance().DeleteData(queryOption, unifiedDataSet);
    ASSERT_EQ(status, E_INVALID_PARAMETERS);
    queryOption.intention = UD_INTENTION_SYSTEM_SHARE;
    status = UdmfClient::GetInstance().DeleteData(queryOption, unifiedDataSet);
    ASSERT_EQ(status, E_INVALID_PARAMETERS);

    QueryOption queryOption1 = { .key = key };
    status = UdmfClient::GetInstance().DeleteData(queryOption1, unifiedDataSet);
    ASSERT_EQ(status, E_OK);
    LOG_INFO(UDMF_TEST, "DeleteData005 end.");
}

/**
* @tc.name: DeleteData006
* @tc.desc: Delete data with UD_INTENTION_SYSTEM_SHARE
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientFileMangerTest, DeleteData006, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "DeleteData006 begin.");
    CustomOption customOption = { .intention = UD_INTENTION_SYSTEM_SHARE };
    UnifiedData data;
    auto plainText = std::make_shared<PlainText>();
    plainText->SetContent("content1");
    data.AddRecord(plainText);
    std::string key;
    auto status = UdmfClient::GetInstance().SetData(customOption, data, key);
    ASSERT_EQ(status, E_OK);

    QueryOption queryOption;
    std::vector<UnifiedData> unifiedDataSet;
    queryOption.key = "udmf://aaabbbccc/com.hmos.test/CSl;cdcGFcmdkasaccCSCAAScscdc";
    status = UdmfClient::GetInstance().DeleteData(queryOption, unifiedDataSet);
    ASSERT_EQ(status, E_INVALID_PARAMETERS);
    queryOption.intention = UD_INTENTION_PICKER;
    status = UdmfClient::GetInstance().DeleteData(queryOption, unifiedDataSet);
    ASSERT_EQ(status, E_INVALID_PARAMETERS);
    queryOption.intention = UD_INTENTION_SYSTEM_SHARE;
    status = UdmfClient::GetInstance().DeleteData(queryOption, unifiedDataSet);
    ASSERT_EQ(status, E_INVALID_PARAMETERS);

    QueryOption queryOption1 = { .key = key };
    status = UdmfClient::GetInstance().DeleteData(queryOption1, unifiedDataSet);
    ASSERT_EQ(status, E_OK);
    LOG_INFO(UDMF_TEST, "DeleteData006 end.");
}

/**
* @tc.name: DeleteData007
* @tc.desc: Delete data with UD_INTENTION_MENU
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientFileMangerTest, DeleteData007, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "DeleteData007 begin.");
    CustomOption customOption = { .intention = UD_INTENTION_MENU };
    UnifiedData data;
    auto plainText = std::make_shared<PlainText>();
    plainText->SetContent("content1");
    data.AddRecord(plainText);
    std::string key;
    auto status = UdmfClient::GetInstance().SetData(customOption, data, key);
    ASSERT_EQ(status, E_OK);

    QueryOption queryOption;
    std::vector<UnifiedData> unifiedDataSet;
    queryOption.key = key;
    queryOption.intention = UD_INTENTION_SYSTEM_SHARE;
    status = UdmfClient::GetInstance().DeleteData(queryOption, unifiedDataSet);
    ASSERT_EQ(status, E_INVALID_PARAMETERS);
    queryOption.intention = UD_INTENTION_MENU;
    status = UdmfClient::GetInstance().DeleteData(queryOption, unifiedDataSet);
    ASSERT_EQ(status, E_OK);
    LOG_INFO(UDMF_TEST, "DeleteData007 end.");
}

/**
* @tc.name: DeleteData008
* @tc.desc: Delete data with UD_INTENTION_MENU
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientFileMangerTest, DeleteData008, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "DeleteData008 begin.");
    CustomOption customOption = { .intention = UD_INTENTION_MENU };
    UnifiedData data;
    auto plainText = std::make_shared<PlainText>();
    plainText->SetContent("content1");
    data.AddRecord(plainText);
    std::string key;
    auto status = UdmfClient::GetInstance().SetData(customOption, data, key);
    ASSERT_EQ(status, E_OK);

    QueryOption queryOption;
    std::vector<UnifiedData> unifiedDataSet;
    status = UdmfClient::GetInstance().DeleteData(queryOption, unifiedDataSet);
    ASSERT_EQ(status, E_INVALID_PARAMETERS);
    queryOption.intention = UD_INTENTION_SYSTEM_SHARE;
    status = UdmfClient::GetInstance().DeleteData(queryOption, unifiedDataSet);
    ASSERT_EQ(status, E_INVALID_PARAMETERS);
    queryOption.intention = UD_INTENTION_MENU;
    status = UdmfClient::GetInstance().DeleteData(queryOption, unifiedDataSet);
    ASSERT_EQ(status, E_INVALID_PARAMETERS);

    QueryOption queryOption1 = { .key = key };
    status = UdmfClient::GetInstance().DeleteData(queryOption1, unifiedDataSet);
    ASSERT_EQ(status, E_OK);
    LOG_INFO(UDMF_TEST, "DeleteData008 end.");
}

/**
* @tc.name: DeleteData009
* @tc.desc: Delete data with UD_INTENTION_MENU
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientFileMangerTest, DeleteData009, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "DeleteData009 begin.");
    CustomOption customOption = { .intention = UD_INTENTION_MENU };
    UnifiedData data;
    auto plainText = std::make_shared<PlainText>();
    plainText->SetContent("content1");
    data.AddRecord(plainText);
    std::string key;
    auto status = UdmfClient::GetInstance().SetData(customOption, data, key);
    ASSERT_EQ(status, E_OK);

    QueryOption queryOption;
    std::vector<UnifiedData> unifiedDataSet;
    queryOption.key = "udmf://aaabbbccc/com.hmos.test/CSl;cdcGFcmdkasaccCSCAAScscdc";
    status = UdmfClient::GetInstance().DeleteData(queryOption, unifiedDataSet);
    ASSERT_EQ(status, E_INVALID_PARAMETERS);
    queryOption.intention = UD_INTENTION_SYSTEM_SHARE;
    status = UdmfClient::GetInstance().DeleteData(queryOption, unifiedDataSet);
    ASSERT_EQ(status, E_INVALID_PARAMETERS);
    queryOption.intention = UD_INTENTION_MENU;
    status = UdmfClient::GetInstance().DeleteData(queryOption, unifiedDataSet);
    ASSERT_EQ(status, E_INVALID_PARAMETERS);

    QueryOption queryOption1 = { .key = key };
    status = UdmfClient::GetInstance().DeleteData(queryOption1, unifiedDataSet);
    ASSERT_EQ(status, E_OK);
    LOG_INFO(UDMF_TEST, "DeleteData009 end.");
}

/**
* @tc.name: UpdateData001
* @tc.desc: test picker update data
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientFileMangerTest, UpdateData001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "UpdateData001 begin.");
    CustomOption customOption = { .intention = Intention::UD_INTENTION_PICKER };
    UnifiedData data;
    std::shared_ptr<UnifiedRecord> record = std::make_shared<PlainText>(UDType::PLAIN_TEXT, "plainTextContent");
    data.AddRecord(record);
    std::shared_ptr<UnifiedDataProperties> properties = std::make_shared<UnifiedDataProperties>();
    std::string tag = "this is a tag of test UpdateData001";
    properties->tag = tag;
    data.SetProperties(std::move(properties));
    std::string key;
    auto status = UdmfClient::GetInstance().SetData(customOption, data, key);
    ASSERT_EQ(status, E_OK);

    QueryOption query;
    std::vector<UnifiedData> unifiedDataSet;
    status = UdmfClient::GetInstance().UpdateData(query, data);
    ASSERT_EQ(status, E_INVALID_PARAMETERS);
    query.intention = Intention::UD_INTENTION_SYSTEM_SHARE;
    status = UdmfClient::GetInstance().UpdateData(query, data);
    ASSERT_EQ(status, E_INVALID_PARAMETERS);
    query.intention = Intention::UD_INTENTION_PICKER;
    status = UdmfClient::GetInstance().UpdateData(query, data);
    ASSERT_EQ(status, E_INVALID_PARAMETERS);

    query.key = key;
    status = UdmfClient::GetInstance().UpdateData(query, data);
    ASSERT_EQ(status, E_INVALID_PARAMETERS);
    status = UdmfClient::GetInstance().DeleteData(query, unifiedDataSet);
    ASSERT_EQ(status, E_OK);
    LOG_INFO(UDMF_TEST, "UpdateData001 end.");
}

/**
* @tc.name: UpdateData002
* @tc.desc: test picker update data
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientFileMangerTest, UpdateData002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "UpdateData002 begin.");
    CustomOption customOption = { .intention = Intention::UD_INTENTION_PICKER };
    UnifiedData data;
    std::shared_ptr<UnifiedRecord> record = std::make_shared<PlainText>(UDType::PLAIN_TEXT, "plainTextContent");
    data.AddRecord(record);
    std::shared_ptr<UnifiedDataProperties> properties = std::make_shared<UnifiedDataProperties>();
    std::string tag = "this is a tag of test UpdateData001";
    properties->tag = tag;
    data.SetProperties(std::move(properties));
    std::string key;
    auto status = UdmfClient::GetInstance().SetData(customOption, data, key);
    ASSERT_EQ(status, E_OK);

    QueryOption query;
    query.key = "udmf://aaabbbccc/com.hmos.test/CSl;cdcGFcmdkasaccCSCAAScscdc";
    std::vector<UnifiedData> unifiedDataSet;
    status = UdmfClient::GetInstance().UpdateData(query, data);
    ASSERT_EQ(status, E_INVALID_PARAMETERS);
    query.intention = Intention::UD_INTENTION_SYSTEM_SHARE;
    status = UdmfClient::GetInstance().UpdateData(query, data);
    ASSERT_EQ(status, E_INVALID_PARAMETERS);
    query.intention = Intention::UD_INTENTION_PICKER;
    status = UdmfClient::GetInstance().UpdateData(query, data);
    ASSERT_EQ(status, E_INVALID_PARAMETERS);

    query.key = key;
    status = UdmfClient::GetInstance().UpdateData(query, data);
    ASSERT_EQ(status, E_INVALID_PARAMETERS);
    status = UdmfClient::GetInstance().DeleteData(query, unifiedDataSet);
    ASSERT_EQ(status, E_OK);
    LOG_INFO(UDMF_TEST, "UpdateData002 end.");
}

/**
* @tc.name: UpdateData003
* @tc.desc: test picker update data
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientFileMangerTest, UpdateData003, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "UpdateData003 begin.");
    CustomOption customOption = { .intention = Intention::UD_INTENTION_PICKER };
    UnifiedData data;
    std::shared_ptr<UnifiedRecord> record = std::make_shared<PlainText>(UDType::PLAIN_TEXT, "plainTextContent");
    data.AddRecord(record);
    std::shared_ptr<UnifiedDataProperties> properties = std::make_shared<UnifiedDataProperties>();
    std::string tag = "this is a tag of test UpdateData001";
    properties->tag = tag;
    data.SetProperties(std::move(properties));
    std::string key;
    auto status = UdmfClient::GetInstance().SetData(customOption, data, key);
    ASSERT_EQ(status, E_OK);

    QueryOption query;
    query.key = key;
    std::vector<UnifiedData> unifiedDataSet;
    status = UdmfClient::GetInstance().UpdateData(query, data);
    ASSERT_EQ(status, E_INVALID_PARAMETERS);
    query.intention = Intention::UD_INTENTION_SYSTEM_SHARE;
    status = UdmfClient::GetInstance().UpdateData(query, data);
    ASSERT_EQ(status, E_INVALID_PARAMETERS);
    query.intention = Intention::UD_INTENTION_PICKER;
    status = UdmfClient::GetInstance().UpdateData(query, data);
    ASSERT_EQ(status, E_INVALID_PARAMETERS);

    status = UdmfClient::GetInstance().DeleteData(query, unifiedDataSet);
    ASSERT_EQ(status, E_OK);
    LOG_INFO(UDMF_TEST, "UpdateData003 end.");
}

/**
* @tc.name: UpdateData004
* @tc.desc: test picker update data
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientFileMangerTest, UpdateData004, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "UpdateData004 begin.");
    CustomOption customOption = { .intention = Intention::UD_INTENTION_PICKER };
    UnifiedData data;
    std::shared_ptr<UnifiedRecord> record = std::make_shared<PlainText>(UDType::PLAIN_TEXT, "plainTextContent");
    data.AddRecord(record);
    std::shared_ptr<UnifiedDataProperties> properties = std::make_shared<UnifiedDataProperties>();
    std::string tag = "this is a tag of test UpdateData001";
    properties->tag = tag;
    data.SetProperties(std::move(properties));
    std::string key;
    auto status = UdmfClient::GetInstance().SetData(customOption, data, key);
    ASSERT_EQ(status, E_OK);

    QueryOption query;
    std::vector<UnifiedData> unifiedDataSet;
    status = UdmfClient::GetInstance().UpdateData(query, data);
    ASSERT_EQ(status, E_INVALID_PARAMETERS);
    query.intention = Intention::UD_INTENTION_SYSTEM_SHARE;
    status = UdmfClient::GetInstance().UpdateData(query, data);
    ASSERT_EQ(status, E_INVALID_PARAMETERS);
    query.intention = Intention::UD_INTENTION_PICKER;
    status = UdmfClient::GetInstance().UpdateData(query, data);
    ASSERT_EQ(status, E_INVALID_PARAMETERS);

    query.key = key;
    status = UdmfClient::GetInstance().UpdateData(query, data);
    ASSERT_EQ(status, E_INVALID_PARAMETERS);
    status = UdmfClient::GetInstance().DeleteData(query, unifiedDataSet);
    ASSERT_EQ(status, E_OK);
    LOG_INFO(UDMF_TEST, "UpdateData004 end.");
}

/**
* @tc.name: UpdateData005
* @tc.desc: test picker update data
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientFileMangerTest, UpdateData005, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "UpdateData005 begin.");
    CustomOption customOption = { .intention = Intention::UD_INTENTION_SYSTEM_SHARE };
    UnifiedData data;
    std::shared_ptr<UnifiedRecord> record = std::make_shared<PlainText>(UDType::PLAIN_TEXT, "plainTextContent");
    data.AddRecord(record);
    std::shared_ptr<UnifiedDataProperties> properties = std::make_shared<UnifiedDataProperties>();
    std::string tag = "this is a tag of test UpdateData001";
    properties->tag = tag;
    data.SetProperties(std::move(properties));
    std::string key;
    auto status = UdmfClient::GetInstance().SetData(customOption, data, key);
    ASSERT_EQ(status, E_OK);

    QueryOption query;
    query.key = key;
    std::vector<UnifiedData> unifiedDataSet;
    status = UdmfClient::GetInstance().UpdateData(query, data);
    ASSERT_EQ(status, E_INVALID_PARAMETERS);
    query.intention = Intention::UD_INTENTION_PICKER;
    status = UdmfClient::GetInstance().UpdateData(query, data);
    ASSERT_EQ(status, E_INVALID_PARAMETERS);
    query.intention = Intention::UD_INTENTION_SYSTEM_SHARE;
    status = UdmfClient::GetInstance().UpdateData(query, data);
    ASSERT_EQ(status, E_INVALID_PARAMETERS);

    status = UdmfClient::GetInstance().DeleteData(query, unifiedDataSet);
    ASSERT_EQ(status, E_OK);
    LOG_INFO(UDMF_TEST, "UpdateData005 end.");
}
}