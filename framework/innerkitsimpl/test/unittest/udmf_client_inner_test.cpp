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
#define LOG_TAG "UdmfClientInnerTest"
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
#include "file_uri.h"
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
using namespace std;

class UdmfClientInnerTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
    static void AllocHapToken1();
    void SetHapToken1();

    static constexpr int userId = 100;
    static constexpr int instIndex = 0;
};

void UdmfClientInnerTest::SetUpTestCase()
{
    AllocHapToken1();
}

void UdmfClientInnerTest::TearDownTestCase()
{
    auto tokenId = AccessTokenKit::GetHapTokenID(userId, "ohos.test.demo1", instIndex);
    AccessTokenKit::DeleteToken(tokenId);
}

void UdmfClientInnerTest::SetUp()
{
    SetHapToken1();
}

void UdmfClientInnerTest::TearDown()
{
    QueryOption query = { .intention = Intention::UD_INTENTION_DATA_HUB };
    std::vector<UnifiedData> unifiedDataSet;
    UdmfClient::GetInstance().DeleteData(query, unifiedDataSet);
    query = { .intention = Intention::UD_INTENTION_DRAG };
    UdmfClient::GetInstance().DeleteData(query, unifiedDataSet);
}

void UdmfClientInnerTest::AllocHapToken1()
{
    HapInfoParams info = {
        .userID = userId,
        .bundleName = "ohos.test.demo1",
        .instIndex = instIndex,
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

void UdmfClientInnerTest::SetHapToken1()
{
    auto tokenId = AccessTokenKit::GetHapTokenID(userId, "ohos.test.demo1", instIndex);
    SetSelfTokenID(tokenId);
}

/**
* @tc.name: GetEntryTest001
* @tc.desc: Test set a UDC data, then get data with GetEntry function.
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientInnerTest, GetEntryTest001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetEntryTest001 begin.");
    UnifiedData data;
    std::shared_ptr<File> file = std::make_shared<File>();
    file->SetUri("https://file/txt.txt");
    data.AddRecord(file);
    auto image = std::make_shared<Image>();
    image->SetUri("https://file/txt.txt");
    data.AddRecord(image);
    auto applicationDefinedRecord = std::make_shared<ApplicationDefinedRecord>();
    applicationDefinedRecord->SetRawData({ 'a', 'b' });
    data.AddRecord(applicationDefinedRecord);
    auto html = std::make_shared<Html>();
    html->SetHtmlContent("content");
    data.AddRecord(html);
    auto plainText = std::make_shared<PlainText>();
    plainText->SetContent("content");
    data.AddRecord(plainText);
    CustomOption option1 = { .intention = Intention::UD_INTENTION_DRAG };
    std::string key;
    auto status = UdmfClient::GetInstance().SetData(option1, data, key);
    ASSERT_EQ(status, E_OK);
    QueryOption option2 = { .key = key };
    UnifiedData readData;
    status = UdmfClient::GetInstance().GetData(option2, readData);
    auto recordFile = readData.GetRecordAt(0);
    auto udsValue = recordFile->GetEntry("general.file-uri");
    EXPECT_TRUE(std::holds_alternative<std::shared_ptr<Object>>(udsValue));
    std::shared_ptr<Object> fileUds = std::get<std::shared_ptr<Object>>(udsValue);
    EXPECT_EQ(std::get<std::string>(fileUds->value_[ORI_URI]), "https://file/txt.txt");
    auto recordImage = readData.GetRecordAt(1);
    auto imageValue = recordImage->GetEntry("general.file-uri");
    EXPECT_TRUE(std::holds_alternative<std::shared_ptr<Object>>(imageValue));
    std::shared_ptr<Object> imageUds = std::get<std::shared_ptr<Object>>(imageValue);
    EXPECT_EQ(std::get<std::string>(imageUds->value_[ORI_URI]), "https://file/txt.txt");
    auto recordAppDefined = readData.GetRecordAt(2);
    auto appDefinedValue = recordAppDefined->GetEntry("ApplicationDefinedType");
    EXPECT_TRUE(std::holds_alternative<std::shared_ptr<Object>>(appDefinedValue));
    std::shared_ptr<Object> appDefinedUds = std::get<std::shared_ptr<Object>>(appDefinedValue);
    EXPECT_EQ(std::get<std::vector<uint8_t>>(appDefinedUds->value_[ARRAY_BUFFER])[0], 'a');
    LOG_INFO(UDMF_TEST, "GetEntryTest001 end.");
}

/**
* @tc.name: GetEntryTest002
* @tc.desc: Test set a UDC data, then get data with GetEntry function.
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientInnerTest, GetEntryTest002, TestSize.Level1)
{
    UnifiedData data;
    std::shared_ptr<File> file = std::make_shared<File>("https://file/txt.txt");
    data.AddRecord(file);
    auto image = std::make_shared<Image>("https://file/txt.txt");
    data.AddRecord(image);
    std::vector<uint8_t> value =  { 'a', 'b' };
    auto applicationDefinedRecord = std::make_shared<ApplicationDefinedRecord>("test", value);
    data.AddRecord(applicationDefinedRecord);
    auto html = std::make_shared<Html>("content", "plaintext content");
    data.AddRecord(html);
    auto plainText = std::make_shared<PlainText>("content", "abstract");
    data.AddRecord(plainText);
    CustomOption option1 = { .intention = Intention::UD_INTENTION_DRAG };
    std::string key;
    auto status = UdmfClient::GetInstance().SetData(option1, data, key);
    QueryOption option2 = { .key = key };
    UnifiedData readData;
    status = UdmfClient::GetInstance().GetData(option2, readData);
    auto recordFile = readData.GetRecordAt(0);
    auto udsValue = recordFile->GetEntry("general.file-uri");
    EXPECT_TRUE(std::holds_alternative<std::shared_ptr<Object>>(udsValue));
    std::shared_ptr<Object> fileUds = std::get<std::shared_ptr<Object>>(udsValue);
    EXPECT_EQ(std::get<std::string>(fileUds->value_[ORI_URI]), "https://file/txt.txt");
    auto recordImage = readData.GetRecordAt(1);
    auto imageValue = recordImage->GetEntry("general.file-uri");
    EXPECT_TRUE(std::holds_alternative<std::shared_ptr<Object>>(imageValue));
    std::shared_ptr<Object> imageUds = std::get<std::shared_ptr<Object>>(imageValue);
    EXPECT_EQ(std::get<std::string>(imageUds->value_[ORI_URI]), "https://file/txt.txt");
    auto recordAppDefined = readData.GetRecordAt(2);
    auto appDefinedValue = recordAppDefined->GetEntry("test");
    EXPECT_TRUE(std::holds_alternative<std::shared_ptr<Object>>(appDefinedValue));
    std::shared_ptr<Object> appDefinedUds = std::get<std::shared_ptr<Object>>(appDefinedValue);
    EXPECT_EQ(std::get<std::vector<uint8_t>>(appDefinedUds->value_[ARRAY_BUFFER])[0], 'a');
    auto recordHtml = readData.GetRecordAt(3);
    auto htmlValue = recordHtml->GetEntry("general.html");
    EXPECT_TRUE(std::holds_alternative<std::shared_ptr<Object>>(htmlValue));
    std::shared_ptr<Object> htmlUds = std::get<std::shared_ptr<Object>>(htmlValue);
    EXPECT_EQ(std::get<std::string>(htmlUds->value_[HTML_CONTENT]), "content");
    EXPECT_EQ(std::get<std::string>(htmlUds->value_[PLAIN_CONTENT]), "plaintext content");
    auto recordPlainText = readData.GetRecordAt(4);
    auto plainTextValue = recordPlainText->GetEntry("general.plain-text");
    EXPECT_TRUE(std::holds_alternative<std::shared_ptr<Object>>(plainTextValue));
    std::shared_ptr<Object> plainTextUds = std::get<std::shared_ptr<Object>>(plainTextValue);
    EXPECT_EQ(std::get<std::string>(plainTextUds->value_[CONTENT]), "content");
    EXPECT_EQ(std::get<std::string>(plainTextUds->value_[ABSTRACT]), "abstract");
}

/**
* @tc.name: GetEntryTest003
* @tc.desc: Test set a base UnifiedRecord data, then get data with GetEntry function.
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientInnerTest, GetEntryTest003, TestSize.Level1)
{
    UnifiedData data;
    std::shared_ptr<UnifiedRecord> record1 = std::make_shared<UnifiedRecord>(VIDEO, "video");
    data.AddRecord(record1);
    std::shared_ptr<UnifiedRecord> record2 = std::make_shared<UnifiedRecord>(HTML, "html");
    data.AddRecord(record2);
    std::shared_ptr<UnifiedRecord> record3 = std::make_shared<UnifiedRecord>(KINGSOFT_WRITER_WPT, "abc");
    data.AddRecord(record3);
    auto obj = std::make_shared<Object>();
    obj->value_["uniformDataType"] = "general.plain-text";
    obj->value_["textContent"] = "plainTextContent";
    std::shared_ptr<UnifiedRecord> record4 = std::make_shared<UnifiedRecord>(PLAIN_TEXT, obj);
    data.AddRecord(record4);
    std::shared_ptr<UnifiedRecord> record5 = std::make_shared<UnifiedRecord>(HYPERLINK);
    data.AddRecord(record5);
    CustomOption option1 = { .intention = Intention::UD_INTENTION_DRAG };
    std::string key;
    auto status = UdmfClient::GetInstance().SetData(option1, data, key);
    QueryOption option2 = { .key = key };
    UnifiedData readData;
    status = UdmfClient::GetInstance().GetData(option2, readData);
    auto recordFirst = readData.GetRecordAt(0);
    auto firstValue = recordFirst->GetEntry("general.video");
    EXPECT_TRUE(std::holds_alternative<std::shared_ptr<Object>>(firstValue));
    std::shared_ptr<Object> firstUds = std::get<std::shared_ptr<Object>>(firstValue);
    EXPECT_EQ(std::get<std::string>(firstUds->value_[VALUE_TYPE]), "video");
    auto recordSecond = readData.GetRecordAt(1);
    auto secondValue = recordSecond->GetEntry("general.html");
    EXPECT_TRUE(std::holds_alternative<std::shared_ptr<Object>>(secondValue));
    std::shared_ptr<Object> secondUds = std::get<std::shared_ptr<Object>>(secondValue);
    EXPECT_EQ(std::get<std::string>(secondUds->value_[VALUE_TYPE]), "html");
    auto recordThird = readData.GetRecordAt(2);
    auto thirdValue = recordThird->GetEntry("com.kingsoft.office.writer.wpt");
    EXPECT_TRUE(std::holds_alternative<std::string>(thirdValue));
    EXPECT_EQ(std::get<std::string>(thirdValue), "abc");
    auto recordFourth = readData.GetRecordAt(3);
    auto fourthValue = recordFourth->GetEntry("general.plain-text");
    EXPECT_TRUE(std::holds_alternative<std::shared_ptr<Object>>(fourthValue));
    std::shared_ptr<Object> fourthUds = std::get<std::shared_ptr<Object>>(fourthValue);
    EXPECT_EQ(std::get<std::string>(fourthUds->value_["textContent"]), "plainTextContent");
    auto recordFifth = readData.GetRecordAt(4);
    auto fifthValue = recordFifth->GetEntry("general.hyperlink");
    EXPECT_TRUE(std::holds_alternative<std::monostate>(
        std::get<std::shared_ptr<Object>>(fifthValue)->value_[VALUE_TYPE]));
}
} // OHOS::Test