/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#define LOG_TAG "UnifiedRecordTest"

#include <unistd.h>
#include <thread>
#include <gtest/gtest.h>
#include <string>

#include "application_defined_record.h"
#include "file.h"
#include "html.h"
#include "image.h"
#include "logger.h"
#include "plain_text.h"
#include "udmf_capi_common.h"
#include "udmf_client.h"
#include "unified_record.h"

using namespace testing::ext;
using namespace OHOS::UDMF;
using namespace OHOS;
namespace OHOS::Test {
using namespace std;

class UnifiedRecordTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void UnifiedRecordTest::SetUpTestCase()
{
}

void UnifiedRecordTest::TearDownTestCase()
{
}

void UnifiedRecordTest::SetUp()
{
}

void UnifiedRecordTest::TearDown()
{
}

/**
* @tc.name: GetSize001
* @tc.desc: Normal testcase of GetSize
* @tc.type: FUNC
*/
HWTEST_F(UnifiedRecordTest, GetSize001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetSize001 begin.");
    UnifiedRecord unifiedRecord;
    int64_t ret = unifiedRecord.GetSize();
    EXPECT_EQ(ret, 0);
    LOG_INFO(UDMF_TEST, "GetSize001 end.");
}

/**
* @tc.name: GetValue001
* @tc.desc: Normal testcase of GetValue
* @tc.type: FUNC
*/
HWTEST_F(UnifiedRecordTest, GetValue001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetValue001 begin.");
    UnifiedRecord unifiedRecord;
    unifiedRecord.value_ = "value";
    ValueType ret = unifiedRecord.GetValue();
    EXPECT_EQ(ret, unifiedRecord.value_);
    LOG_INFO(UDMF_TEST, "GetValue001 end.");
}


/**
 * @tc.name: Constructor_001
 * @tc.desc: Verify the constructor.
 * @tc.type: FUNC
 */
HWTEST_F(UnifiedRecordTest, Constructor_001, TestSize.Level0)
{
    UnifiedRecord record;

    auto type = record.GetType();
    EXPECT_EQ(type, UD_BUTT);

    auto types = record.GetUtdIds();
    EXPECT_TRUE(types.empty());

    auto originValue = record.GetOriginValue();
    EXPECT_TRUE(std::holds_alternative<std::monostate>(originValue));

    auto entry = record.GetEntry("");
    EXPECT_TRUE(std::holds_alternative<std::monostate>(entry));

    auto entries = record.GetEntries();
    EXPECT_TRUE(entries->empty());
}

/**
 * @tc.name: Constructor_002
 * @tc.desc: Verify the constructor.
 * @tc.type: FUNC
 */
HWTEST_F(UnifiedRecordTest, Constructor_002, TestSize.Level0)
{
    auto utdId = UtdUtils::GetUtdIdFromUtdEnum(TEXT);

    UnifiedRecord record(TEXT);
    auto type = record.GetType();
    EXPECT_EQ(type, TEXT);
    auto types = record.GetUtdIds();
    EXPECT_TRUE(types.find(utdId) != types.end());

    auto originValue = record.GetOriginValue();
    EXPECT_TRUE(std::holds_alternative<std::monostate>(originValue));

    auto entry = record.GetEntry(utdId);
    EXPECT_TRUE(std::holds_alternative<std::monostate>(entry));

    auto entries = record.GetEntries();
    auto it = entries->find(utdId);
    ASSERT_TRUE(it != entries->end());
    EXPECT_FALSE(std::holds_alternative<std::monostate>(it->second));
    EXPECT_TRUE(std::holds_alternative<std::shared_ptr<Object>>(it->second));
}

/**
 * @tc.name: Constructor_003
 * @tc.desc: Verify the constructor.
 * @tc.type: FUNC
 */
HWTEST_F(UnifiedRecordTest, Constructor_003, TestSize.Level0)
{
    auto utdId = UtdUtils::GetUtdIdFromUtdEnum(TEXT);
    UnifiedRecord record(TEXT, "123456");
    auto type = record.GetType();
    EXPECT_EQ(type, TEXT);
    auto types = record.GetUtdIds();
    EXPECT_TRUE(types.find(utdId) != types.end());

    auto originValue = record.GetOriginValue();
    EXPECT_TRUE(std::holds_alternative<std::string>(originValue));
    auto originValueStr = std::get_if<std::string>(&originValue);
    EXPECT_EQ(*originValueStr, "123456");

    auto entry = record.GetEntry(utdId);
    EXPECT_TRUE(std::holds_alternative<std::shared_ptr<Object>>(entry));
    auto entryStr = std::get<std::shared_ptr<Object>>(entry);
    EXPECT_EQ(std::get<std::string>(entryStr->value_[VALUE_TYPE]), "123456");

    auto entries = record.GetEntries();
    auto it = entries->find(utdId);
    ASSERT_TRUE(it != entries->end());
    auto entry2 = it->second;
    EXPECT_TRUE(std::holds_alternative<std::shared_ptr<Object>>(entry2));
}

/**
 * @tc.name: AddEntry_001
 * @tc.desc: Normal testcase of AddEntry
 * @tc.type: FUNC
 */
HWTEST_F(UnifiedRecordTest, AddEntry_001, TestSize.Level0)
{
    std::string utdId = "utdId";
    ValueType value = "value";
    UnifiedRecord unifiedRecord;
    std::thread t1(&UnifiedRecord::AddEntry, std::ref(unifiedRecord), utdId, value);
    EXPECT_NO_FATAL_FAILURE(t1.join());

    std::string utdId1 = "utdId1";
    ValueType value1 = "value1";
    std::thread t2(&UnifiedRecord::AddEntry, std::ref(unifiedRecord), utdId1, value1);
    EXPECT_NO_FATAL_FAILURE(t2.join());

    std::string utdId2 = "utdId2";
    ValueType value2 = "value2";
    std::thread t3(&UnifiedRecord::AddEntry, std::ref(unifiedRecord), utdId2, value2);
    EXPECT_NO_FATAL_FAILURE(t3.join());

    std::string utdId3 = "utdId3";
    ValueType value3 = "value3";
    std::thread t4(&UnifiedRecord::AddEntry, std::ref(unifiedRecord), utdId3, value3);
    EXPECT_NO_FATAL_FAILURE(t4.join());

    std::string utdId4 = "utdId4";
    ValueType value4 = "value4";
    std::thread t5(&UnifiedRecord::AddEntry, std::ref(unifiedRecord), utdId4, value4);
    EXPECT_NO_FATAL_FAILURE(t5.join());

    std::string utdId5 = "utdId5";
    ValueType value5 = "value5";
    std::thread t6(&UnifiedRecord::AddEntry, std::ref(unifiedRecord), utdId5, value5);
    EXPECT_NO_FATAL_FAILURE(t6.join());

    std::string utdId6 = "utdId6";
    ValueType value6 = "value6";
    std::thread t7(&UnifiedRecord::AddEntry, std::ref(unifiedRecord), utdId6, value6);
    EXPECT_NO_FATAL_FAILURE(t7.join());

    std::string utdId7 = "utdId7";
    ValueType value7 = "value7";
    std::thread t8(&UnifiedRecord::AddEntry, std::ref(unifiedRecord), utdId7, value7);
    EXPECT_NO_FATAL_FAILURE(t8.join());

    std::string utdId8 = "utdId8";
    ValueType value8 = "value8";
    std::thread t9(&UnifiedRecord::AddEntry, std::ref(unifiedRecord), utdId8, value8);
    EXPECT_NO_FATAL_FAILURE(t9.join());

    std::string utdId9 = "utdId9";
    ValueType value9 = "value9";
    std::thread t10(&UnifiedRecord::AddEntry, std::ref(unifiedRecord), utdId9, value9);
    EXPECT_NO_FATAL_FAILURE(t10.join());
}

/**
* @tc.name: GetEntryTest001
* @tc.desc: Test set a UDC data, then get data with GetEntry function.
* @tc.type: FUNC
*/
HWTEST_F(UnifiedRecordTest, GetEntryTest001, TestSize.Level1)
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
HWTEST_F(UnifiedRecordTest, GetEntryTest002, TestSize.Level1)
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
HWTEST_F(UnifiedRecordTest, GetEntryTest003, TestSize.Level1)
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

/**
* @tc.name: SetFileUriTest001
* @tc.desc: Test set a base UnifiedRecord data, then get data with GetEntry function.
* @tc.type: FUNC
*/
HWTEST_F(UnifiedRecordTest, SetFileUriTest001, TestSize.Level1)
{
    std::string uri = "file://1111/a.jpeg";
    std::shared_ptr<Object> fileObj = std::make_shared<Object>();
    fileObj->value_[UNIFORM_DATA_TYPE] = "general.file-uri";
    fileObj->value_[FILE_TYPE] = "general.jpeg";
    std::shared_ptr<UnifiedRecord> fileRecord = std::make_shared<UnifiedRecord>(FILE_URI, fileObj);
    fileRecord->SetFileUri(uri);
    std::shared_ptr<Object> fileObj1 = std::get<std::shared_ptr<Object>>(fileRecord->GetValue());
    EXPECT_EQ(std::get<std::string>(fileObj1->value_[FILE_URI_PARAM]), uri);
}
} // OHOS::Test