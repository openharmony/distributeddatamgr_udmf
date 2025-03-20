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
#define LOG_TAG "UnifiedDataTest"

#include <unistd.h>
#include <gtest/gtest.h>
#include <string>

#include "file.h"
#include "logger.h"
#include "plain_text.h"
#include "udmf_capi_common.h"
#include "udmf_utils.h"
#include "unified_data.h"

using namespace testing::ext;
using namespace OHOS::UDMF;
using namespace OHOS;
namespace OHOS::Test {
using namespace std;

class UnifiedDataTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
    void TransferToEntriesCompareEntries(UnifiedRecord* recordFirst);
};

void UnifiedDataTest::SetUpTestCase()
{
}

void UnifiedDataTest::TearDownTestCase()
{
}

void UnifiedDataTest::SetUp()
{
}

void UnifiedDataTest::TearDown()
{
}

void UnifiedDataTest::TransferToEntriesCompareEntries(UnifiedRecord* recordFirst)
{
    auto plainTextFirst = static_cast<PlainText*>(recordFirst);
    EXPECT_EQ(plainTextFirst->GetAbstract(), "abstract");
    EXPECT_EQ(plainTextFirst->GetContent(), "http://1111/a.img");

    std::set<std::string> utdIds = recordFirst->GetUtdIds();
    EXPECT_EQ(utdIds.size(), 4);
    EXPECT_TRUE(utdIds.find("general.plain-text") != utdIds.end());
    EXPECT_TRUE(utdIds.find("general.file") != utdIds.end());
    EXPECT_TRUE(utdIds.find("general.file-uri") != utdIds.end());
    EXPECT_TRUE(utdIds.find("general.img") == utdIds.end());
    EXPECT_TRUE(utdIds.find("general.media") != utdIds.end());

    auto fileEntry = recordFirst->GetEntry("general.file");
    std::shared_ptr<Object> fileEntryObj = std::get<std::shared_ptr<Object>>(fileEntry);
    std::string getUri;
    fileEntryObj->GetValue(ORI_URI, getUri);
    EXPECT_EQ(getUri, "http://1111/a.img");

    auto plainTextEntry = recordFirst->GetEntry("general.plain-text");
    EXPECT_TRUE(std::holds_alternative<std::monostate>(plainTextEntry));

    auto entries = recordFirst->GetEntries();
    EXPECT_NE(entries, nullptr);
    EXPECT_EQ(entries->size(), 3);
    auto fileEntry1 = (*entries)["general.file"];
    std::shared_ptr<Object> fileEntryObj1 = std::get<std::shared_ptr<Object>>(fileEntry1);
    std::string getUri1;
    fileEntryObj1->GetValue(ORI_URI, getUri1);
    EXPECT_EQ(getUri1, "http://1111/a.img");

    auto plainTextEntry1 = (*entries)["general.plain-text"];
    std::shared_ptr<Object> plainTextEntryObj1 = std::get<std::shared_ptr<Object>>(plainTextEntry1);
    std::string content;
    plainTextEntryObj1->GetValue(CONTENT, content);
    EXPECT_EQ(content, "http://1111/a.img");
    std::string abstract;
    plainTextEntryObj1->GetValue(ABSTRACT, abstract);
    EXPECT_EQ(abstract, "abstract");

    auto fileUriEntry1 = (*entries)["general.file-uri"];
    std::shared_ptr<Object> fileUriEntryObj1 = std::get<std::shared_ptr<Object>>(fileUriEntry1);
    std::string oriUri;
    fileUriEntryObj1->GetValue(FILE_URI_PARAM, oriUri);
    EXPECT_EQ(oriUri, "http://1111/a.img");
    std::string fileType;
    fileUriEntryObj1->GetValue(FILE_TYPE, fileType);
    EXPECT_EQ(fileType, "general.media");
}

/**
* @tc.name: UnifiedData001
* @tc.desc: Normal testcase of UnifiedData
* @tc.type: FUNC
*/
HWTEST_F(UnifiedDataTest, UnifiedData001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "UnifiedData001 begin.");
    std::shared_ptr<UnifiedDataProperties> properties = std::make_shared<UnifiedDataProperties>();
    UnifiedData unifiedData(properties);
    auto duration = std::chrono::system_clock::now().time_since_epoch();
    EXPECT_EQ(unifiedData.properties_, properties);
    EXPECT_EQ(unifiedData.properties_->timestamp,
        std::chrono::duration_cast<std::chrono::milliseconds>(duration).count());
    LOG_INFO(UDMF_TEST, "UnifiedData001 end.");
}

/**
* @tc.name: GetGroupId001
* @tc.desc: Normal testcase of GetGroupId
* @tc.type: FUNC
*/
HWTEST_F(UnifiedDataTest, GetGroupId001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetGroupId001 begin.");
    UnifiedData unifiedData;
    unifiedData.runtime_ = std::make_shared<Runtime>();
    std::string ret = unifiedData.GetGroupId();
    EXPECT_EQ(ret, unifiedData.runtime_->key.groupId);
    LOG_INFO(UDMF_TEST, "GetGroupId001 end.");
}

/**
* @tc.name: GetRuntime001
* @tc.desc: Normal testcase of GetRuntime
* @tc.type: FUNC
*/
HWTEST_F(UnifiedDataTest, GetRuntime001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetRuntime001 begin.");
    UnifiedData unifiedData;
    unifiedData.runtime_ = std::make_shared<Runtime>();
    std::shared_ptr<Runtime> ret = unifiedData.GetRuntime();
    EXPECT_EQ(ret, unifiedData.runtime_);
    LOG_INFO(UDMF_TEST, "GetRuntime001 end.");
}

/**
* @tc.name: SetRuntime001
* @tc.desc: Normal testcase of SetRuntime
* @tc.type: FUNC
*/
HWTEST_F(UnifiedDataTest, SetRuntime001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetRuntime001 begin.");
    UnifiedData unifiedData;
    Runtime runtime{};
    unifiedData.SetRuntime(runtime);
    EXPECT_NE(unifiedData.runtime_, nullptr);
    LOG_INFO(UDMF_TEST, "SetRuntime001 end.");
}

/**
* @tc.name: AddRecord001
* @tc.desc: Abnormal testcase of AddRecord, because record is nullptr
* @tc.type: FUNC
*/
HWTEST_F(UnifiedDataTest, AddRecord001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "AddRecord001 begin.");
    const std::shared_ptr<UnifiedRecord> record = nullptr;
    UnifiedData unifiedData;
    unifiedData.AddRecord(record);
    EXPECT_EQ(unifiedData.records_.size(), 0);
    LOG_INFO(UDMF_TEST, "AddRecord001 end.");
}

/**
* @tc.name: AddRecords001
* @tc.desc: Abnormal testcase of AddRecords, because record is nullptr
* @tc.type: FUNC
*/
HWTEST_F(UnifiedDataTest, AddRecords001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "AddRecords001 begin.");
    const std::vector<std::shared_ptr<UnifiedRecord>> record = {nullptr};
    UnifiedData unifiedData;
    unifiedData.AddRecords(record);
    EXPECT_EQ(unifiedData.records_.size(), 0);
    LOG_INFO(UDMF_TEST, "AddRecords001 end.");
}

/**
* @tc.name: GetRecordAt001
* @tc.desc: Abnormal testcase of GetRecordAt, because the length of records_ is equal to the length of index
* @tc.type: FUNC
*/
HWTEST_F(UnifiedDataTest, GetRecordAt001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetRecordAt001 begin.");
    UnifiedData unifiedData;
    unifiedData.records_ = std::vector<std::shared_ptr<UnifiedRecord>>();
    std::size_t index = unifiedData.records_.size();
    std::shared_ptr<UnifiedRecord> ret = unifiedData.GetRecordAt(index);
    EXPECT_EQ(ret, nullptr);
    LOG_INFO(UDMF_TEST, "GetRecordAt001 end.");
}

/**
* @tc.name: TransferToEntries001
* @tc.desc: Normal testcase of TransferToEntries
* @tc.type: FUNC
*/
HWTEST_F(UnifiedDataTest, TransferToEntries001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "TransferToEntries001 begin.");
    UnifiedData unifiedData;
    std::shared_ptr<PlainText> plainText = std::make_shared<PlainText>();
    plainText->SetContent("http://1111/a.img");
    plainText->SetAbstract("abstract");
    std::shared_ptr<File> file = std::make_shared<File>();
    file->SetUri("http://1111/a.img");
    unifiedData.AddRecord(plainText);
    unifiedData.AddRecord(file);
    unifiedData.TransferToEntries(unifiedData);
    auto records = unifiedData.GetRecords();
    EXPECT_EQ(records.size(), 1);
    auto recordFirst = records[0].get();
    auto plainTextFirst = static_cast<PlainText*>(recordFirst);
    EXPECT_EQ(plainTextFirst->GetAbstract(), "abstract");
    EXPECT_EQ(plainTextFirst->GetContent(), "http://1111/a.img");
    std::set<std::string> utdIds = recordFirst->GetUtdIds();
    EXPECT_EQ(utdIds.size(), 2);
    EXPECT_TRUE(utdIds.find("general.plain-text") != utdIds.end());
    EXPECT_TRUE(utdIds.find("general.file") != utdIds.end());
    auto fileEntry = recordFirst->GetEntry("general.file");
    std::shared_ptr<Object> fileEntryObj = std::get<std::shared_ptr<Object>>(fileEntry);
    std::string getUri;
    fileEntryObj->GetValue(ORI_URI, getUri);
    EXPECT_EQ(getUri, "http://1111/a.img");
    auto plainTextEntry = recordFirst->GetEntry("general.plain-text");
    EXPECT_TRUE(std::holds_alternative<std::monostate>(plainTextEntry));
    auto entries = recordFirst->GetEntries();
    EXPECT_NE(entries, nullptr);
    EXPECT_EQ(entries->size(), 2);
    auto fileEntry1 = (*entries)["general.file"];
    std::shared_ptr<Object> fileEntryObj1 = std::get<std::shared_ptr<Object>>(fileEntry1);
    std::string getUri1;
    fileEntryObj1->GetValue(ORI_URI, getUri1);
    EXPECT_EQ(getUri1, "http://1111/a.img");
    auto plainTextEntry1 = (*entries)["general.plain-text"];
    std::shared_ptr<Object> plainTextEntryObj1 = std::get<std::shared_ptr<Object>>(plainTextEntry1);
    std::string content;
    plainTextEntryObj1->GetValue(CONTENT, content);
    EXPECT_EQ(content, "http://1111/a.img");
    std::string abstract;
    plainTextEntryObj1->GetValue(ABSTRACT, abstract);
    EXPECT_EQ(abstract, "abstract");
    LOG_INFO(UDMF_TEST, "TransferToEntries001 end.");
}

/**
* @tc.name: TransferToEntries002
* @tc.desc: Normal testcase of TransferToEntries
* @tc.type: FUNC
*/
HWTEST_F(UnifiedDataTest, TransferToEntries002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "TransferToEntries002 begin.");
    UnifiedData unifiedData;
    std::shared_ptr<PlainText> plainText = std::make_shared<PlainText>();
    plainText->SetContent("http://1111/a.img");
    plainText->SetAbstract("abstract");

    std::shared_ptr<File> file = std::make_shared<File>();
    file->SetUri("http://1111/a.img");

    std::shared_ptr<Object> fileUriObj = std::make_shared<Object>();
    fileUriObj->value_[UNIFORM_DATA_TYPE] = "general.file-uri";
    fileUriObj->value_[FILE_URI_PARAM] = "http://1111/a.img";
    fileUriObj->value_[FILE_TYPE] = "general.img";
    std::shared_ptr<UnifiedRecord> fileUri = std::make_shared<UnifiedRecord>(FILE_URI, fileUriObj);

    std::shared_ptr<Object> fileUriObj1 = std::make_shared<Object>();
    fileUriObj1->value_[UNIFORM_DATA_TYPE] = "general.file-uri";
    fileUriObj1->value_[FILE_URI_PARAM] = "http://1111/a.img";
    fileUriObj1->value_[FILE_TYPE] = "general.media";
    std::shared_ptr<UnifiedRecord> fileUri1 = std::make_shared<UnifiedRecord>(FILE_URI, fileUriObj1);

    bool isNeed = unifiedData.IsNeedTransferToEntries();
    EXPECT_FALSE(isNeed);
    unifiedData.AddRecord(plainText);
    isNeed = unifiedData.IsNeedTransferToEntries();
    EXPECT_FALSE(isNeed);
    unifiedData.AddRecord(file);
    isNeed = unifiedData.IsNeedTransferToEntries();
    EXPECT_FALSE(isNeed);
    unifiedData.AddRecord(fileUri);
    unifiedData.AddRecord(fileUri1);
    std::shared_ptr<UnifiedDataProperties> properties = std::make_shared<UnifiedDataProperties>();
    properties->tag = "records_to_entries_data_format";
    unifiedData.SetProperties(properties);
    isNeed = unifiedData.IsNeedTransferToEntries();
    EXPECT_TRUE(isNeed);

    unifiedData.TransferToEntries(unifiedData);
    auto records = unifiedData.GetRecords();
    EXPECT_EQ(records.size(), 1);
    
    auto recordFirst = records[0].get();
    TransferToEntriesCompareEntries(recordFirst);
    LOG_INFO(UDMF_TEST, "TransferToEntries001 end.");
}
} // OHOS::Test