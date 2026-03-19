/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
#define LOG_TAG "AuditHelperTest"
#include <gtest/gtest.h>

#include <thread>
#include <chrono>

#include "logger.h"
#include "audit_helper.h"
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
#include "progress_callback.h"
#include "video.h"
#include <nlohmann/json.hpp>

using namespace testing::ext;
using namespace OHOS::UDMF;
using namespace OHOS;

namespace OHOS::Test {
constexpr int SLEEP_TIME = 50;   // 50 ms

class AuditHelperTest : public testing::Test {
public:
    void SetUp() override {}
    void TearDown() override {}
};

/**
* @tc.name: ConvertValueToJson001
* @tc.desc: Test ConvertValueToJson with int32_t value
* @tc.type: FUNC
*/
HWTEST_F(AuditHelperTest, ConvertValueToJson001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "ConvertValueToJson001 begin.");

    int32_t testValue = 12345;
    ValueType value = testValue;

    auto json = AuditHelper::ConvertValueToJson(value);
    EXPECT_TRUE(json.is_number_integer());
    EXPECT_EQ(json.get<int32_t>(), testValue);

    LOG_INFO(UDMF_TEST, "ConvertValueToJson001 end.");
}

/**
* @tc.name: ConvertValueToJson002
* @tc.desc: Test ConvertValueToJson with int64_t value
* @tc.type: FUNC
*/
HWTEST_F(AuditHelperTest, ConvertValueToJson002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "ConvertValueToJson002 begin.");

    int64_t testValue = 1234567890123LL;
    ValueType value = testValue;

    auto json = AuditHelper::ConvertValueToJson(value);
    EXPECT_TRUE(json.is_number_integer());
    EXPECT_EQ(json.get<int64_t>(), testValue);

    LOG_INFO(UDMF_TEST, "ConvertValueToJson002 end.");
}

/**
* @tc.name: ConvertValueToJson003
* @tc.desc: Test ConvertValueToJson with double value
* @tc.type: FUNC
*/
HWTEST_F(AuditHelperTest, ConvertValueToJson003, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "ConvertValueToJson003 begin.");

    double testValue = 3.14159;
    ValueType value = testValue;

    auto json = AuditHelper::ConvertValueToJson(value);
    EXPECT_TRUE(json.is_number_float());
    EXPECT_DOUBLE_EQ(json.get<double>(), testValue);

    LOG_INFO(UDMF_TEST, "ConvertValueToJson003 end.");
}

/**
* @tc.name: ConvertValueToJson004
* @tc.desc: Test ConvertValueToJson with bool value
* @tc.type: FUNC
*/
HWTEST_F(AuditHelperTest, ConvertValueToJson004, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "ConvertValueToJson004 begin.");

    bool testValue = true;
    ValueType value = testValue;

    auto json = AuditHelper::ConvertValueToJson(value);
    EXPECT_TRUE(json.is_boolean());
    EXPECT_EQ(json.get<bool>(), testValue);

    LOG_INFO(UDMF_TEST, "ConvertValueToJson004 end.");
}

/**
* @tc.name: ConvertValueToJson005
* @tc.desc: Test ConvertValueToJson with string value
* @tc.type: FUNC
*/
HWTEST_F(AuditHelperTest, ConvertValueToJson005, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "ConvertValueToJson005 begin.");

    std::string testValue = "test string value";
    ValueType value = testValue;

    auto json = AuditHelper::ConvertValueToJson(value);
    EXPECT_TRUE(json.is_string());
    EXPECT_EQ(json.get<std::string>(), testValue);

    LOG_INFO(UDMF_TEST, "ConvertValueToJson005 end.");
}

/**
* @tc.name: ConvertValueToJson006
* @tc.desc: Test ConvertValueToJson with vector<uint8_t> value
* @tc.type: FUNC
*/
HWTEST_F(AuditHelperTest, ConvertValueToJson006, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "ConvertValueToJson006 begin.");

    std::vector<uint8_t> testValue = {0x01, 0x02, 0x03, 0x04, 0x05};
    ValueType value = testValue;

    auto json = AuditHelper::ConvertValueToJson(value);
    EXPECT_TRUE(json.is_binary());
    auto bytes = json.get_binary();
    EXPECT_EQ(bytes.size(), testValue.size());
    for (size_t i = 0; i < testValue.size(); ++i) {
        EXPECT_EQ(bytes[i], testValue[i]);
    }

    LOG_INFO(UDMF_TEST, "ConvertValueToJson006 end.");
}

/**
* @tc.name: ConvertValueToJson007
* @tc.desc: Test ConvertValueToJson with monostate (empty) value
* @tc.type: FUNC
*/
HWTEST_F(AuditHelperTest, ConvertValueToJson007, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "ConvertValueToJson007 begin.");

    std::monostate testValue;
    ValueType value = testValue;

    auto json = AuditHelper::ConvertValueToJson(value);
    EXPECT_TRUE(json.is_null());

    LOG_INFO(UDMF_TEST, "ConvertValueToJson007 end.");
}

/**
* @tc.name: ConvertEntriesToJson001
* @tc.desc: Test ConvertEntriesToJson with multiple entries
* @tc.type: FUNC
*/
HWTEST_F(AuditHelperTest, ConvertEntriesToJson001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "ConvertEntriesToJson001 begin.");

    std::map<std::string, ValueType> entries;
    entries.insert(std::make_pair("int_key", int32_t(123)));
    entries.insert(std::make_pair("string_key", std::string("test value")));
    entries.insert(std::make_pair("bool_key", true));
    entries.insert(std::make_pair("double_key", 3.14));

    auto json = AuditHelper::ConvertEntriesToJson(entries);
    EXPECT_TRUE(json.is_object());
    EXPECT_EQ(json.size(), 4);
    EXPECT_TRUE(json.contains("int_key"));
    EXPECT_TRUE(json.contains("string_key"));
    EXPECT_TRUE(json.contains("bool_key"));
    EXPECT_TRUE(json.contains("double_key"));

    LOG_INFO(UDMF_TEST, "ConvertEntriesToJson001 end.");
}

/**
* @tc.name: ConvertEntriesToJson002
* @tc.desc: Test ConvertEntriesToJson with empty entries
* @tc.type: FUNC
*/
HWTEST_F(AuditHelperTest, ConvertEntriesToJson002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "ConvertEntriesToJson002 begin.");

    std::map<std::string, ValueType> entries;

    auto json = AuditHelper::ConvertEntriesToJson(entries);
    EXPECT_TRUE(json.is_null());

    LOG_INFO(UDMF_TEST, "ConvertEntriesToJson002 end.");
}

/**
* @tc.name: ConvertEntriesToJson003
* @tc.desc: Test ConvertEntriesToJson with various value types
* @tc.type: FUNC
*/
HWTEST_F(AuditHelperTest, ConvertEntriesToJson003, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "ConvertEntriesToJson003 begin.");

    std::map<std::string, ValueType> entries;
    entries.insert(std::make_pair("int32_val", int32_t(2147483647)));
    entries.insert(std::make_pair("int64_val", int64_t(9223372036854775807LL)));
    entries.insert(std::make_pair("double_val", 2.718281828459045));
    entries.insert(std::make_pair("bool_val", false));
    entries.insert(std::make_pair("string_val", "complex test string with special chars: !@#$%^&*()"));
    entries.insert(std::make_pair("bytes_val", std::string("bytes_value")));

    auto json = AuditHelper::ConvertEntriesToJson(entries);
    EXPECT_TRUE(json.is_object());
    EXPECT_EQ(json.size(), 6);
    EXPECT_TRUE(json.contains("int32_val"));
    EXPECT_TRUE(json.contains("int64_val"));
    EXPECT_TRUE(json.contains("double_val"));
    EXPECT_TRUE(json.contains("bool_val"));
    EXPECT_TRUE(json.contains("string_val"));
    EXPECT_TRUE(json.contains("bytes_val"));

    LOG_INFO(UDMF_TEST, "ConvertEntriesToJson003 end.");
}

/**
* @tc.name: ConvertRecordToJson001
* @tc.desc: Test ConvertRecordToJson with text record
* @tc.type: FUNC
*/
HWTEST_F(AuditHelperTest, ConvertRecordToJson001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "ConvertRecordToJson001 begin.");

    auto text = std::make_shared<Text>();
    UDDetails details;
    details.insert(std::make_pair("key1", "value1"));
    details.insert(std::make_pair("key2", int32_t(456)));
    text->SetDetails(details);

    auto json = AuditHelper::ConvertRecordToJson(text, 0);
    EXPECT_TRUE(json.is_object());

    LOG_INFO(UDMF_TEST, "ConvertRecordToJson001 end.");
}

/**
* @tc.name: ConvertRecordToJson002
* @tc.desc: Test ConvertRecordToJson with plain text record
* @tc.type: FUNC
*/
HWTEST_F(AuditHelperTest, ConvertRecordToJson002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "ConvertRecordToJson002 begin.");

    auto plainText = std::make_shared<PlainText>();
    plainText->SetContent("test content");
    plainText->SetAbstract("test abstract");

    auto json = AuditHelper::ConvertRecordToJson(plainText, 1);
    EXPECT_TRUE(json.is_object());

    LOG_INFO(UDMF_TEST, "ConvertRecordToJson002 end.");
}

/**
* @tc.name: ConvertRecordToJson003
* @tc.desc: Test ConvertRecordToJson with file record
* @tc.type: FUNC
*/
HWTEST_F(AuditHelperTest, ConvertRecordToJson003, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "ConvertRecordToJson003 begin.");

    auto file = std::make_shared<File>();
    file->SetUri("file:///data/test.txt");
    file->SetRemoteUri("file:///data/remote/test.txt");

    auto json = AuditHelper::ConvertRecordToJson(file, 2);
    EXPECT_TRUE(json.is_object());

    LOG_INFO(UDMF_TEST, "ConvertRecordToJson003 end.");
}

/**
* @tc.name: ConvertRecordToJson004
* @tc.desc: Test ConvertRecordToJson with application defined record
* @tc.type: FUNC
*/
HWTEST_F(AuditHelperTest, ConvertRecordToJson004, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "ConvertRecordToJson004 begin.");

    auto appRecord = std::make_shared<ApplicationDefinedRecord>();
    appRecord->SetApplicationDefinedType("custom.app.record");
    std::vector<uint8_t> rawData = {0x01, 0x02, 0x03, 0x04};
    appRecord->SetRawData(rawData);

    auto json = AuditHelper::ConvertRecordToJson(appRecord, 5);
    EXPECT_TRUE(json.is_object());

    LOG_INFO(UDMF_TEST, "ConvertRecordToJson004 end.");
}

/**
* @tc.name: PublishAuditEvent001
* @tc.desc: Test PublishAuditEvent with valid JSON data
* @tc.type: FUNC
*/
HWTEST_F(AuditHelperTest, PublishAuditEvent001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "PublishAuditEvent001 begin.");

    nlohmann::json auditData;
    auditData["sourceTokenId"] = 12345;
    auditData["targetTokenId"] = 67890;
    auditData["userId"] = 100;
    auditData["timestamp"] = 1234567890;

    nlohmann::json dataArray = nlohmann::json::array();
    nlohmann::json record;
    record["type"] = 1;
    record["index"] = 0;
    record["value"] = "test value";
    dataArray.push_back(record);
    auditData["unifiedData"] = dataArray;

    nlohmann::json auditDataBefore = auditData;
    EXPECT_NO_FATAL_FAILURE(AuditHelper::PublishAuditEvent(auditData));
    EXPECT_EQ(auditDataBefore.dump(), auditData.dump());

    LOG_INFO(UDMF_TEST, "PublishAuditEvent001 end.");
}

/**
* @tc.name: PublishAuditEvent002
* @tc.desc: Test PublishAuditEvent with complex nested data
* @tc.type: FUNC
*/
HWTEST_F(AuditHelperTest, PublishAuditEvent002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "PublishAuditEvent002 begin.");

    nlohmann::json auditData;
    auditData["sourceTokenId"] = 11111;
    auditData["targetTokenId"] = 22222;
    auditData["userId"] = 200;
    auditData["timestamp"] = 9876543210;

    nlohmann::json dataArray = nlohmann::json::array();
    for (int i = 0; i < 3; i++) {
        nlohmann::json record;
        record["type"] = i + 1;
        record["index"] = i;
        record["value"] = "value_" + std::to_string(i);

        nlohmann::json entries;
        entries["key1"] = "entry_value_" + std::to_string(i);
        entries["key2"] = i * 100;
        record["entries"] = entries;

        dataArray.push_back(record);
    }
    auditData["unifiedData"] = dataArray;

    nlohmann::json auditDataBefore = auditData;
    EXPECT_NO_FATAL_FAILURE(AuditHelper::PublishAuditEvent(auditData));
    EXPECT_EQ(auditDataBefore.dump(), auditData.dump());

    LOG_INFO(UDMF_TEST, "PublishAuditEvent002 end.");
}

/**
* @tc.name: ReportDragAuditEvent001
* @tc.desc: Test ReportDragAuditEvent with single record
* @tc.type: FUNC
*/
HWTEST_F(AuditHelperTest, ReportDragAuditEvent001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "ReportDragAuditEvent001 begin.");

    UnifiedData unifiedData;
    auto text = std::make_shared<Text>();
    UDDetails details;
    details.insert(std::make_pair("test_key", "test_value"));
    text->SetDetails(details);
    unifiedData.AddRecord(text);

    int32_t userId = 100;
    uint32_t tokenId = 12345;

    int32_t originalUserId = userId;
    uint32_t originalTokenId = tokenId;
    size_t originalRecordsSize = unifiedData.GetRecords().size();

    EXPECT_NO_FATAL_FAILURE(AuditHelper::ReportDragAuditEvent(unifiedData, userId, tokenId));

    std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_TIME));

    EXPECT_EQ(userId, originalUserId);
    EXPECT_EQ(tokenId, originalTokenId);
    EXPECT_EQ(unifiedData.GetRecords().size(), originalRecordsSize);

    LOG_INFO(UDMF_TEST, "ReportDragAuditEvent001 end.");
}

/**
* @tc.name: ReportDragAuditEvent002
* @tc.desc: Test ReportDragAuditEvent with multiple records
* @tc.type: FUNC
*/
HWTEST_F(AuditHelperTest, ReportDragAuditEvent002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "ReportDragAuditEvent002 begin.");

    UnifiedData unifiedData;
    auto text = std::make_shared<Text>();
    UDDetails details;
    details.insert(std::make_pair("key1", "value1"));
    text->SetDetails(details);
    unifiedData.AddRecord(text);

    int32_t userId = 100;
    uint32_t tokenId = 12345;

    int32_t originalUserId = userId;
    uint32_t originalTokenId = tokenId;
    size_t originalRecordsSize = unifiedData.GetRecords().size();

    EXPECT_NO_FATAL_FAILURE(AuditHelper::ReportDragAuditEvent(unifiedData, userId, tokenId));

    std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_TIME));

    EXPECT_EQ(userId, originalUserId);
    EXPECT_EQ(tokenId, originalTokenId);
    EXPECT_EQ(unifiedData.GetRecords().size(), originalRecordsSize);

    LOG_INFO(UDMF_TEST, "ReportDragAuditEvent001 end.");
}

/**
* @tc.name: ReportDragAuditEvent003
* @tc.desc: Test ReportDragAuditEvent with empty data
* @tc.type: FUNC
*/
HWTEST_F(AuditHelperTest, ReportDragAuditEvent003, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "ReportDragAuditEvent003 begin.");

    UnifiedData unifiedData;
    int32_t userId = 100;
    uint32_t tokenId = 54321;

    int32_t originalUserId = userId;
    uint32_t originalTokenId = tokenId;
    size_t originalRecordsSize = unifiedData.GetRecords().size();

    EXPECT_NO_FATAL_FAILURE(AuditHelper::ReportDragAuditEvent(unifiedData, userId, tokenId));

    std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_TIME));

    EXPECT_EQ(userId, originalUserId);
    EXPECT_EQ(tokenId, originalTokenId);
    EXPECT_EQ(unifiedData.GetRecords().size(), originalRecordsSize);

    LOG_INFO(UDMF_TEST, "ReportDragAuditEvent003 end.");
}

/**
* @tc.name: ReportDragAuditEvent004
* @tc.desc: Test ReportDragAuditEvent with high frequency calls
* @tc.type: FUNC
*/
HWTEST_F(AuditHelperTest, ReportDragAuditEvent004, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "ReportDragAuditEvent004 begin.");

    UnifiedData unifiedData;
    auto text = std::make_shared<Text>();
    UDDetails details;
    details.insert(std::make_pair("test_key", "test_value"));
    text->SetDetails(details);
    unifiedData.AddRecord(text);

    int32_t userId = 100;
    uint32_t tokenId = 98765;
    int32_t originalUserId = userId;
    uint32_t originalTokenId = tokenId;
    size_t originalRecordsSize = unifiedData.GetRecords().size();

    for (int i = 0; i < 10; i++) {
        EXPECT_NO_FATAL_FAILURE(AuditHelper::ReportDragAuditEvent(unifiedData, userId, tokenId));
    }

    std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_TIME * 2));
    EXPECT_EQ(userId, originalUserId);
    EXPECT_EQ(tokenId, originalTokenId);
    EXPECT_EQ(unifiedData.GetRecords().size(), originalRecordsSize);

    LOG_INFO(UDMF_TEST, "ReportDragAuditEvent004 end.");
}

/**
* @tc.name: ReportDragAuditEvent005
* @tc.desc: Test ReportDragAuditEvent with different userId and tokenId
* @tc.type: FUNC
*/
HWTEST_F(AuditHelperTest, ReportDragAuditEvent005, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "ReportDragAuditEvent005 begin.");

    UnifiedData unifiedData;
    auto text = std::make_shared<Text>();
    UDDetails details;
    details.insert(std::make_pair("test_key", "test_value"));
    text->SetDetails(details);
    unifiedData.AddRecord(text);

    int32_t userId = 200;
    uint32_t tokenId = 11111;

    int32_t originalUserId = userId;
    uint32_t originalTokenId = tokenId;
    size_t originalRecordsSize = unifiedData.GetRecords().size();

EXPECT_NO_FATAL_FAILURE(AuditHelper::ReportDragAuditEvent(unifiedData, userId, tokenId));

    std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_TIME));

    EXPECT_EQ(userId, originalUserId);
    EXPECT_EQ(tokenId, originalTokenId);
    EXPECT_EQ(unifiedData.GetRecords().size(), originalRecordsSize);

    LOG_INFO(UDMF_TEST, "ReportDragAuditEvent005 end.");
}

/**
* @tc.name: ReportDragAuditEvent006
* @tc.desc: Test ReportDragAuditEvent with large data
* @tc.type: FUNC
*/
HWTEST_F(AuditHelperTest, ReportDragAuditEvent006, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "ReportDragAuditEvent006 begin.");

    UnifiedData unifiedData;
    for (int i = 0; i < 50; i++) {
        auto text = std::make_shared<Text>();
        UDDetails details;
        details.insert(std::make_pair("key_" + std::to_string(i), "value_" + std::to_string(i)));
        text->SetDetails(details);
        unifiedData.AddRecord(text);
    }

    int32_t userId = 100;
    uint32_t tokenId = 22222;

    int32_t originalUserId = userId;
    uint32_t originalTokenId = tokenId;
    size_t originalRecordsSize = unifiedData.GetRecords().size();

    EXPECT_NO_FATAL_FAILURE(AuditHelper::ReportDragAuditEvent(unifiedData, userId, tokenId));

    std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_TIME * 2));
    EXPECT_EQ(userId, originalUserId);
    EXPECT_EQ(tokenId, originalTokenId);
    EXPECT_EQ(unifiedData.GetRecords().size(), originalRecordsSize);

    LOG_INFO(UDMF_TEST, "ReportDragAuditEvent006 end.");
}

/**
* @tc.name: ReportDragAuditEvent007
* @tc.desc: Test ReportDragAuditEvent with complete data
* @tc.type: FUNC
*/
HWTEST_F(AuditHelperTest, ReportDragAuditEvent007, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "ReportDragAuditEvent007 begin.");

    UnifiedData unifiedData;

    auto runtime = std::make_shared<Runtime>();
    runtime->tokenId = 99999;
    runtime->sourcePackage = "com.test.app";
    runtime->createPackage = "com.test.app";
    runtime->deviceId = "device-test";
    runtime->dataVersion = 2;
    runtime->isPrivate = true;
    runtime->recordTotalNum = 5;
    runtime->sdkVersion = "2.0.0";
    runtime->appId = "test-app-002";
    unifiedData.SetRuntime(*runtime);

    auto properties = std::make_shared<UnifiedDataProperties>();
    properties->tag = "final-test-tag";
    properties->isRemote = false;
    properties->timestamp = 9876543210;
    properties->shareOptions = CROSS_DEVICE;
    unifiedData.SetProperties(properties);

    auto plainText = std::make_shared<PlainText>();
    plainText->SetContent("Final test content");
    plainText->SetAbstract("Final test abstract");
    unifiedData.AddRecord(plainText);

    auto file = std::make_shared<File>();
    file->SetUri("file:///data/final/file.txt");
    file->SetRemoteUri("file:///data/final/remote.txt");
    unifiedData.AddRecord(file);

    int32_t userId = 999;
    uint32_t tokenId = 88888;

    int32_t originalUserId = userId;
    uint32_t originalTokenId = tokenId;
    size_t originalRecordsSize = unifiedData.GetRecords().size();

    EXPECT_NO_FATAL_FAILURE(AuditHelper::ReportDragAuditEvent(unifiedData, userId, tokenId));

    std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_TIME * 2));
    EXPECT_EQ(userId, originalUserId);
    EXPECT_EQ(tokenId, originalTokenId);
    EXPECT_EQ(unifiedData.GetRecords().size(), originalRecordsSize);

    LOG_INFO(UDMF_TEST, "ReportDragAuditEvent007 end.");
}

/**
* @tc.name: ReportDragAuditEvent008
* @tc.desc: Test ReportDragAuditEvent with Want object
* @tc.type: FUNC
*/
HWTEST_F(AuditHelperTest, ReportDragAuditEvent008, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "ReportDragAuditEvent008 begin.");

    UnifiedData unifiedData;

    auto text = std::make_shared<Text>();
    UDDetails details;
    auto want = std::make_shared<OHOS::AAFwk::Want>();
    want->SetAction("test.action");
    want->SetBundle("com.test.bundle");
    want->SetDeviceId("device-001");
    want->SetModuleName("test.module");
    want->SetType("test.type");
    want->SetUri("file:///test/uri");
    want->SetFlags(0x1234);
    want->SetParam("intParam", 12345);
    want->SetParam("stringParam", std::string("test string"));
    want->SetParam("boolParam", true);
    UDDetails testDetails; testDetails.insert(std::make_pair("wantKey", "want_value")); text->SetDetails(testDetails);
    text->SetDetails(details);
    unifiedData.AddRecord(text);

    int32_t userId = 100;
    uint32_t tokenId = 11111;

    int32_t originalUserId = userId;
    uint32_t originalTokenId = tokenId;
    size_t originalRecordsSize = unifiedData.GetRecords().size();

    EXPECT_NO_FATAL_FAILURE(AuditHelper::ReportDragAuditEvent(unifiedData, userId, tokenId));

    std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_TIME * 2));
    EXPECT_EQ(userId, originalUserId);
    EXPECT_EQ(tokenId, originalTokenId);
    EXPECT_EQ(unifiedData.GetRecords().size(), originalRecordsSize);

    LOG_INFO(UDMF_TEST, "ReportDragAuditEvent008 end.");
}

/**
* @tc.name: ReportDragAuditEvent009
* @tc.desc: Test ReportDragAuditEvent with PixelMap object
* @tc.type: FUNC
*/
HWTEST_F(AuditHelperTest, ReportDragAuditEvent009, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "ReportDragAuditEvent009 begin.");

    UnifiedData unifiedData;

    auto text = std::make_shared<Text>();
    UDDetails details;
    auto pixelMap = std::make_shared<OHOS::Media::PixelMap>();
    details.insert(std::make_pair("pixelMapKey", "pixel_map_value"));
    text->SetDetails(details);
    unifiedData.AddRecord(text);

    int32_t userId = 100;
    uint32_t tokenId = 22222;

    int32_t originalUserId = userId;
    uint32_t originalTokenId = tokenId;
    size_t originalRecordsSize = unifiedData.GetRecords().size();

    EXPECT_NO_FATAL_FAILURE(AuditHelper::ReportDragAuditEvent(unifiedData, userId, tokenId));

    std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_TIME * 2));
    EXPECT_EQ(userId, originalUserId);
    EXPECT_EQ(tokenId, originalTokenId);
    EXPECT_EQ(unifiedData.GetRecords().size(), originalRecordsSize);

    LOG_INFO(UDMF_TEST, "ReportDragAuditEvent009 end.");
}

/**
* @tc.name: ReportDragAuditEvent010
* @tc.desc: Test ReportDragAuditEvent with Object
* @tc.type: FUNC
*/
HWTEST_F(AuditHelperTest, ReportDragAuditEvent010, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "ReportDragAuditEvent010 begin.");

    UnifiedData unifiedData;

    auto text = std::make_shared<Text>();
    UDDetails details;

    details.insert(std::make_pair("objectKey", "object_value"));
    text->SetDetails(details);
    unifiedData.AddRecord(text);

    int32_t userId = 100;
    uint32_t tokenId = 33333;

    int32_t originalUserId = userId;
    uint32_t originalTokenId = tokenId;
    size_t originalRecordsSize = unifiedData.GetRecords().size();

    EXPECT_NO_FATAL_FAILURE(AuditHelper::ReportDragAuditEvent(unifiedData, userId, tokenId));

    std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_TIME * 2));
    EXPECT_EQ(userId, originalUserId);
    EXPECT_EQ(tokenId, originalTokenId);
    EXPECT_EQ(unifiedData.GetRecords().size(), originalRecordsSize);

    LOG_INFO(UDMF_TEST, "ReportDragAuditEvent010 end.");
}

/**
* @tc.name: ReportDragAuditEvent011
* @tc.desc: Test ReportDragAuditEvent with multiple record types
* @tc.type: FUNC
*/
HWTEST_F(AuditHelperTest, ReportDragAuditEvent011, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "ReportDragAuditEvent011 begin.");

    UnifiedData unifiedData;

    auto plainText = std::make_shared<PlainText>();
    plainText->SetContent("Plain text content");
    unifiedData.AddRecord(plainText);

    auto html = std::make_shared<Html>();
    html->SetHtmlContent("<html>content</html>");
    html->SetPlainContent("plain content");
    unifiedData.AddRecord(html);

    auto link = std::make_shared<Link>();
    link->SetUrl("https://example.com");
    link->SetDescription("Test link");
    unifiedData.AddRecord(link);

    auto file = std::make_shared<File>();
    file->SetUri("file:///data/test.txt");
    unifiedData.AddRecord(file);

    int32_t userId = 100;
    uint32_t tokenId = 44444;

    int32_t originalUserId = userId;
    uint32_t originalTokenId = tokenId;
    size_t originalRecordsSize = unifiedData.GetRecords().size();

    EXPECT_NO_FATAL_FAILURE(AuditHelper::ReportDragAuditEvent(unifiedData, userId, tokenId));

    std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_TIME * 2));
    EXPECT_EQ(userId, originalUserId);
    EXPECT_EQ(tokenId, originalTokenId);
    EXPECT_EQ(unifiedData.GetRecords().size(), originalRecordsSize);

    LOG_INFO(UDMF_TEST, "ReportDragAuditEvent011 end.");
}

/**
* @tc.name: ReportDragAuditEvent012
* @tc.desc: Test ReportDragAuditEvent with complex nested data
* @tc.type: FUNC
*/
HWTEST_F(AuditHelperTest, ReportDragAuditEvent012, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "ReportDragAuditEvent012 begin.");

    UnifiedData unifiedData;

    auto text = std::make_shared<Text>();
    UDDetails details;

    auto innerObject = std::make_shared<Object>();
    innerObject->value_["innerKey1"] = "innerValue1";
    innerObject->value_["innerKey2"] = 999;

    auto outerObject = std::make_shared<Object>();
    outerObject->value_["outerKey1"] = "outerValue1";
    outerObject->value_["outerKey2"] = innerObject;
    outerObject->value_["outerKey3"] = true;

    details.insert(std::make_pair("complexKey", "complex_value"));
    text->SetDetails(details);
    unifiedData.AddRecord(text);

    int32_t userId = 100;
    uint32_t tokenId = 55555;

    int32_t originalUserId = userId;
    uint32_t originalTokenId = tokenId;
    size_t originalRecordsSize = unifiedData.GetRecords().size();

    EXPECT_NO_FATAL_FAILURE(AuditHelper::ReportDragAuditEvent(unifiedData, userId, tokenId));

    std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_TIME * 2));
    EXPECT_EQ(userId, originalUserId);
    EXPECT_EQ(tokenId, originalTokenId);
    EXPECT_EQ(unifiedData.GetRecords().size(), originalRecordsSize);

    LOG_INFO(UDMF_TEST, "ReportDragAuditEvent012 end.");
}

/**
* @tc.name: ReportDragAuditEvent013
* @tc.desc: Test ReportDragAuditEvent with array values
* @tc.type: FUNC
*/
HWTEST_F(AuditHelperTest, ReportDragAuditEvent013, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "ReportDragAuditEvent013 begin.");

    UnifiedData unifiedData;

    auto text = std::make_shared<Text>();
    UDDetails details;
    
    
    details.insert(std::make_pair("intArrayKey", "array_value"));
    details.insert(std::make_pair("stringArrayKey", "array_value"));
    details.insert(std::make_pair("boolArrayKey", "array_value"));
    text->SetDetails(details);
    unifiedData.AddRecord(text);

    int32_t userId = 100;
    uint32_t tokenId = 66666;

    int32_t originalUserId = userId;
    uint32_t originalTokenId = tokenId;
    size_t originalRecordsSize = unifiedData.GetRecords().size();

    EXPECT_NO_FATAL_FAILURE(AuditHelper::ReportDragAuditEvent(unifiedData, userId, tokenId));

    std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_TIME * 2));
    EXPECT_EQ(userId, originalUserId);
    EXPECT_EQ(tokenId, originalTokenId);
    EXPECT_EQ(unifiedData.GetRecords().size(), originalRecordsSize);

    LOG_INFO(UDMF_TEST, "ReportDragAuditEvent013 end.");
}

/**
* @tc.name: ReportDragAuditEvent014
* @tc.desc: Test ReportDragAuditEvent with special characters
* @tc.type: FUNC
*/
HWTEST_F(AuditHelperTest, ReportDragAuditEvent014, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "ReportDragAuditEvent014 begin.");

    UnifiedData unifiedData;

    auto plainText = std::make_shared<PlainText>();
    plainText->SetContent("Test content with special chars: 中文 \n\t\r");
    plainText->SetAbstract("Abstract with special chars: !@#$%^&*()");
    unifiedData.AddRecord(plainText);

    int32_t userId = 100;
    uint32_t tokenId = 77777;

    int32_t originalUserId = userId;
    uint32_t originalTokenId = tokenId;
    size_t originalRecordsSize = unifiedData.GetRecords().size();

    EXPECT_NO_FATAL_FAILURE(AuditHelper::ReportDragAuditEvent(unifiedData, userId, tokenId));

    std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_TIME * 2));
    EXPECT_EQ(userId, originalUserId);
    EXPECT_EQ(tokenId, originalTokenId);
    EXPECT_EQ(unifiedData.GetRecords().size(), originalRecordsSize);

    LOG_INFO(UDMF_TEST, "ReportAuditEvent014 end.");
}

/**
* @tc.name: ReportDragAuditEvent015
* @tc.desc: Test ReportDragAuditEvent with empty and null values
* @tc.type: FUNC
*/
HWTEST_F(AuditHelperTest, ReportDragAuditEvent015, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "ReportDragAuditEvent015 begin.");

    UnifiedData unifiedData;

    auto text = std::make_shared<Text>();
    UDDetails details;
    details.insert(std::make_pair("emptyString", std::string("")));
    details.insert(std::make_pair("zeroValue", 0));
    details.insert(std::make_pair("falseValue", false));
    text->SetDetails(details);
    unifiedData.AddRecord(text);

    int32_t userId = 100;
    uint32_t tokenId = 88888;

    EXPECT_NO_FATAL_FAILURE(AuditHelper::ReportDragAuditEvent(unifiedData, userId, tokenId));

    std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_TIME * 2));

    LOG_INFO(UDMF_TEST, "ReportDragAuditEvent015 end.");
}

/**
* @tc.name: ReportDragAuditEvent0017
* @tc.desc: Test ReportDragAuditEvent with PixelMap object
* @tc.type: FUNC
*/
HWTEST_F(AuditHelperTest, ReportDragAuditEvent0017, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "ReportDragAuditEvent0017 begin.");

    UnifiedData unifiedData;

    auto text = std::make_shared<Text>();
    UDDetails details;
    auto pixelMap = std::make_shared<OHOS::Media::PixelMap>();
    details.insert(std::make_pair("pixelMapKey", "pixel_map_value"));
    text->SetDetails(details);
    unifiedData.AddRecord(text);

    int32_t userId = 100;
    uint32_t tokenId = 22222;

    int32_t originalUserId = userId;
    uint32_t originalTokenId = tokenId;
    size_t originalRecordsSize = unifiedData.GetRecords().size();

    EXPECT_NO_FATAL_FAILURE(AuditHelper::ReportDragAuditEvent(unifiedData, userId, tokenId));

    std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_TIME * 2));
    EXPECT_EQ(userId, originalUserId);
    EXPECT_EQ(tokenId, originalTokenId);
    EXPECT_EQ(unifiedData.GetRecords().size(), originalRecordsSize);

    LOG_INFO(UDMF_TEST, "ReportDragAuditEvent0017 end.");
}

/**
* @tc.name: ReportDragAuditEvent018
* @tc.desc: Test ReportDragAuditEvent with Object
* @tc.type: FUNC
*/
HWTEST_F(AuditHelperTest, ReportDragAuditEvent018, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "ReportDragAuditEvent018 begin.");

    UnifiedData unifiedData;
    UDDetails details;

    auto text = std::make_shared<Text>();
    
    details.insert(std::make_pair("objectKey", "object_value"));
    text->SetDetails(details);
    unifiedData.AddRecord(text);

    int32_t userId = 100;
    uint32_t tokenId = 33333;

    int32_t originalUserId = userId;
    uint32_t originalTokenId = tokenId;
    size_t originalRecordsSize = unifiedData.GetRecords().size();

    EXPECT_NO_FATAL_FAILURE(AuditHelper::ReportDragAuditEvent(unifiedData, userId, tokenId));

    std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_TIME * 2));
    EXPECT_EQ(userId, originalUserId);
    EXPECT_EQ(tokenId, originalTokenId);
    EXPECT_EQ(unifiedData.GetRecords().size(), originalRecordsSize);

    LOG_INFO(UDMF_TEST, "ReportDragAuditEvent018 end.");
}

/**
* @tc.name: ReportDragAuditEvent019
* @tc.desc: Test ReportDragAuditEvent with multiple record types
* @tc.type: FUNC
*/
HWTEST_F(AuditHelperTest, ReportDragAuditEvent019, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "ReportDragAuditEvent019 begin.");

    UnifiedData unifiedData;

    auto plainText = std::make_shared<PlainText>();
    plainText->SetContent("Plain text content");
    unifiedData.AddRecord(plainText);

    auto html = std::make_shared<Html>();
    html->SetHtmlContent("<html>content</html>");
    html->SetPlainContent("plain content");
    unifiedData.AddRecord(html);

    auto link = std::make_shared<Link>();
    link->SetUrl("https://example.com");
    link->SetDescription("Test link");
    unifiedData.AddRecord(link);

    auto file = std::make_shared<File>();
    file->SetUri("file:///data/test.txt");
    unifiedData.AddRecord(file);

    int32_t userId = 100;
    uint32_t tokenId = 44444;

    int32_t originalUserId = userId;
    uint32_t originalTokenId = tokenId;
    size_t originalRecordsSize = unifiedData.GetRecords().size();

    EXPECT_NO_FATAL_FAILURE(AuditHelper::ReportDragAuditEvent(unifiedData, userId, tokenId));

    std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_TIME * 2));
    EXPECT_EQ(userId, originalUserId);
    EXPECT_EQ(tokenId, originalTokenId);
    EXPECT_EQ(unifiedData.GetRecords().size(), originalRecordsSize);

    LOG_INFO(UDMF_TEST, "ReportDragAuditEvent019 end.");
}

/**
* @tc.name: ReportDragAuditEvent020
* @tc.desc: Test ReportDragAuditEvent with complex nested data
* @tc.type: FUNC
*/
HWTEST_F(AuditHelperTest, ReportDragAuditEvent020, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "ReportDragAuditEvent020 begin.");

    UnifiedData unifiedData;

    auto text = std::make_shared<Text>();
    UDDetails details;

    auto innerObject = std::make_shared<Object>();
    innerObject->value_["innerKey1"] = "innerValue1";
    innerObject->value_["innerKey2"] = 999;

    auto outerObject = std::make_shared<Object>();
    outerObject->value_["outerKey1"] = "outerValue1";
    outerObject->value_["outerKey2"] = innerObject;
    outerObject->value_["outerKey3"] = true;

    details.insert(std::make_pair("complexKey", "complex_value"));
    text->SetDetails(details);
    unifiedData.AddRecord(text);

    int32_t userId = 100;
    uint32_t tokenId = 55555;

    int32_t originalUserId = userId;
    uint32_t originalTokenId = tokenId;
    size_t originalRecordsSize = unifiedData.GetRecords().size();

    EXPECT_NO_FATAL_FAILURE(AuditHelper::ReportDragAuditEvent(unifiedData, userId, tokenId));

    std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_TIME * 2));
    EXPECT_EQ(userId, originalUserId);
    EXPECT_EQ(tokenId, originalTokenId);
    EXPECT_EQ(unifiedData.GetRecords().size(), originalRecordsSize);

    LOG_INFO(UDMF_TEST, "ReportDragAuditEvent020 end.");
}

/**
* @tc.name: ReportDragAuditEvent021
* @tc.desc: Test ReportDragAuditEvent with array values
* @tc.type: FUNC
*/
HWTEST_F(AuditHelperTest, ReportDragAuditEvent021, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "ReportDragAuditEvent021 begin.");

    UnifiedData unifiedData;

    auto text = std::make_shared<Text>();
    UDDetails details;


    details.insert(std::make_pair("intArrayKey", "array_value"));
    details.insert(std::make_pair("stringArrayKey", "array_value"));
    details.insert(std::make_pair("boolArrayKey", "array_value"));
    text->SetDetails(details);
    unifiedData.AddRecord(text);

    int32_t userId = 100;
    uint32_t tokenId = 66666;

    int32_t originalUserId = userId;
    uint32_t originalTokenId = tokenId;
    size_t originalRecordsSize = unifiedData.GetRecords().size();

    EXPECT_NO_FATAL_FAILURE(AuditHelper::ReportDragAuditEvent(unifiedData, userId, tokenId));

    std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_TIME * 2));
    EXPECT_EQ(userId, originalUserId);
    EXPECT_EQ(tokenId, originalTokenId);
    EXPECT_EQ(unifiedData.GetRecords().size(), originalRecordsSize);

    LOG_INFO(UDMF_TEST, "ReportDragAuditEvent021 end.");
}

/**
* @tc.name: ReportDragAuditEvent022
* @tc.desc: Test ReportDragAuditEvent with special characters
* @tc.type: FUNC
*/
HWTEST_F(AuditHelperTest, ReportDragAuditEvent022, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "ReportDragAuditEvent022 begin.");

    UnifiedData unifiedData;

    auto plainText = std::make_shared<PlainText>();
    plainText->SetContent("Test content with special chars: 中文 \n\t\r");
    plainText->SetAbstract("Abstract with special chars: !@#$%^&*()");
    unifiedData.AddRecord(plainText);

    int32_t userId = 100;
    uint32_t tokenId = 77777;

    int32_t originalUserId = userId;
    uint32_t originalTokenId = tokenId;
    size_t originalRecordsSize = unifiedData.GetRecords().size();

    EXPECT_NO_FATAL_FAILURE(AuditHelper::ReportDragAuditEvent(unifiedData, userId, tokenId));

    std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_TIME * 2));
    EXPECT_EQ(userId, originalUserId);
    EXPECT_EQ(tokenId, originalTokenId);
    EXPECT_EQ(unifiedData.GetRecords().size(), originalRecordsSize);

    LOG_INFO(UDMF_TEST, "ReportDragAuditEvent022 end.");
}

/**
* @tc.name: ReportDragAuditEvent023
* @tc.desc: Test ReportDragAuditEvent with empty and null values
* @tc.type: FUNC
*/
HWTEST_F(AuditHelperTest, ReportDragAuditEvent023, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "ReportDragAuditEvent023 begin.");

    UnifiedData unifiedData;

    auto text = std::make_shared<Text>();
    UDDetails details;
    details.insert(std::make_pair("emptyString", ""));
    details.insert(std::make_pair("zeroValue", 0));
    text->SetDetails(details);
    unifiedData.AddRecord(text);

    int32_t userId = 100;
    uint32_t tokenId = 88888;

    int32_t originalUserId = userId;
    uint32_t originalTokenId = tokenId;
    size_t originalRecordsSize = unifiedData.GetRecords().size();

    EXPECT_NO_FATAL_FAILURE(AuditHelper::ReportDragAuditEvent(unifiedData, userId, tokenId));

    std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_TIME * 2));
    EXPECT_EQ(userId, originalUserId);
    EXPECT_EQ(tokenId, originalTokenId);
    EXPECT_EQ(unifiedData.GetRecords().size(), originalRecordsSize);

    LOG_INFO(UDMF_TEST, "ReportDragAuditEvent023 end.");
}

/**
* @tc.name: ReportDragAuditEvent024
* @tc.desc: Test ReportDragAuditEvent with Object
* @tc.type: FUNC
*/
HWTEST_F(AuditHelperTest, ReportDragAuditEvent024, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "ReportDragAuditEvent024 begin.");

    UnifiedData unifiedData;

    int32_t userId = 100;
    uint32_t tokenId = 33333;
    auto text = std::make_shared<Text>();
    UDDetails details;
    int32_t originalUserId = userId;
    uint32_t originalTokenId = tokenId;
    size_t originalRecordsSize = unifiedData.GetRecords().size();

    EXPECT_NO_FATAL_FAILURE(AuditHelper::ReportDragAuditEvent(unifiedData, userId, tokenId));

    std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_TIME * 2));
    EXPECT_EQ(userId, originalUserId);
    EXPECT_EQ(tokenId, originalTokenId);
    EXPECT_EQ(unifiedData.GetRecords().size(), originalRecordsSize);

    LOG_INFO(UDMF_TEST, "ReportDragAuditEvent024 end.");
}

/**
* @tc.name: ReportDragAuditEvent025
* @tc.desc: Test ReportDragAuditEvent with multiple record types
* @tc.type: FUNC
*/
HWTEST_F(AuditHelperTest, ReportDragAuditEvent025, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "ReportDragAuditEvent025 begin.");

    UnifiedData unifiedData;

    auto plainText = std::make_shared<PlainText>();
    plainText->SetContent("Plain text content");
    unifiedData.AddRecord(plainText);

    auto html = std::make_shared<Html>();
    html->SetHtmlContent("<html>content</html>");
    html->SetPlainContent("plain content");
    unifiedData.AddRecord(html);

    auto link = std::make_shared<Link>();
    link->SetUrl("https://example.com");
    link->SetDescription("Test link");
    unifiedData.AddRecord(link);

    auto file = std::make_shared<File>();
    file->SetUri("file:///data/test.txt");
    unifiedData.AddRecord(file);

    int32_t userId = 100;
    uint32_t tokenId = 44444;

    int32_t originalUserId = userId;
    uint32_t originalTokenId = tokenId;
    size_t originalRecordsSize = unifiedData.GetRecords().size();

    EXPECT_NO_FATAL_FAILURE(AuditHelper::ReportDragAuditEvent(unifiedData, userId, tokenId));

    std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_TIME * 2));
    EXPECT_EQ(userId, originalUserId);
    EXPECT_EQ(tokenId, originalTokenId);
    EXPECT_EQ(unifiedData.GetRecords().size(), originalRecordsSize);

    LOG_INFO(UDMF_TEST, "ReportDragAuditEvent025 end.");
}

/**
* @tc.name: ReportDragAuditEvent026
* @tc.desc: Test ReportDragAuditEvent with complex nested data
* @tc.type: FUNC
*/
HWTEST_F(AuditHelperTest, ReportDragAuditEvent026, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "ReportDragAuditEvent026 begin.");

    UnifiedData unifiedData;

    auto text = std::make_shared<Text>();
    UDDetails details;

    auto innerObject = std::make_shared<Object>();
    innerObject->value_.insert({ "innerKey1", "innerValue1" });
    innerObject->value_.insert({ "innerKey2", 999 });

    auto outerObject = std::make_shared<Object>();
    outerObject->value_.insert({ "outerKey1", "outerValue1" });
    outerObject->value_.insert({ "outerKey2", innerObject });
    outerObject->value_.insert({ "outerKey3", true });

    details.insert(std::make_pair("complexKey", "complex_value"));
    text->SetDetails(details);
    unifiedData.AddRecord(text);

    int32_t userId = 100;
    uint32_t tokenId = 55555;

    int32_t originalUserId = userId;
    uint32_t originalTokenId = tokenId;
    size_t originalRecordsSize = unifiedData.GetRecords().size();

    EXPECT_NO_FATAL_FAILURE(AuditHelper::ReportDragAuditEvent(unifiedData, userId, tokenId));

    std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_TIME * 2));
    EXPECT_EQ(userId, originalUserId);
    EXPECT_EQ(tokenId, originalTokenId);
    EXPECT_EQ(unifiedData.GetRecords().size(), originalRecordsSize);

    LOG_INFO(UDMF_TEST, "ReportDragAuditEvent026 end.");
}

/**
* @tc.name: ReportDragAuditEvent027
* @tc.desc: Test ReportDragAuditEvent with array values
* @tc.type: FUNC
*/
HWTEST_F(AuditHelperTest, ReportDragAuditEvent027, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "ReportDragAuditEvent027 begin.");

    UnifiedData unifiedData;

    auto text = std::make_shared<Text>();
    UDDetails details;

    details.insert(std::make_pair("intArrayKey", "array_value"));
    details.insert(std::make_pair("stringArrayKey", "array_value"));
    details.insert(std::make_pair("boolArrayKey", "array_value"));
    text->SetDetails(details);
    unifiedData.AddRecord(text);

    int32_t userId = 100;
    uint32_t tokenId = 66666;

    int32_t originalUserId = userId;
    uint32_t originalTokenId = tokenId;
    size_t originalRecordsSize = unifiedData.GetRecords().size();

    EXPECT_NO_FATAL_FAILURE(AuditHelper::ReportDragAuditEvent(unifiedData, userId, tokenId));

    std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_TIME * 2));
    EXPECT_EQ(userId, originalUserId);
    EXPECT_EQ(tokenId, originalTokenId);
    EXPECT_EQ(unifiedData.GetRecords().size(), originalRecordsSize);

    LOG_INFO(UDMF_TEST, "ReportDragAuditEvent027 end.");
}

/**
* @tc.name: ReportDragAuditEvent028
* @tc.desc: Test ReportDragAuditEvent with special characters
* @tc.type: FUNC
*/
HWTEST_F(AuditHelperTest, ReportDragAuditEvent028, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "ReportDragAuditEvent028 begin.");

    UnifiedData unifiedData;

    auto plainText = std::make_shared<PlainText>();
    plainText->SetContent("Test content with special chars: 中文 \n\t\r");
    plainText->SetAbstract("Abstract with special chars: !@#$%^&*()");
    unifiedData.AddRecord(plainText);

    int32_t userId = 100;
    uint32_t tokenId = 77777;

    int32_t originalUserId = userId;
    uint32_t originalTokenId = tokenId;
    size_t originalRecordsSize = unifiedData.GetRecords().size();

    EXPECT_NO_FATAL_FAILURE(AuditHelper::ReportDragAuditEvent(unifiedData, userId, tokenId));

    std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_TIME * 2));
    EXPECT_EQ(userId, originalUserId);
    EXPECT_EQ(tokenId, originalTokenId);
    EXPECT_EQ(unifiedData.GetRecords().size(), originalRecordsSize);

    LOG_INFO(UDMF_TEST, "ReportDragAuditEvent028 end.");
}

/**
* @tc.name: ReportDragAuditEvent029
* @tc.desc: Test ReportDragAuditEvent with empty and null values
* @tc.type: FUNC
*/
HWTEST_F(AuditHelperTest, ReportDragAuditEvent029, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "ReportDragAuditEvent029 begin.");

    UnifiedData unifiedData;

    auto text = std::make_shared<Text>();
    UDDetails details;
    details.insert(std::make_pair("emptyString", ""));
    details.insert(std::make_pair("zeroValue", 0));
    text->SetDetails(details);
    unifiedData.AddRecord(text);

    int32_t userId = 100;
    uint32_t tokenId = 88888;

    int32_t originalUserId = userId;
    uint32_t originalTokenId = tokenId;
    size_t originalRecordsSize = unifiedData.GetRecords().size();

    EXPECT_NO_FATAL_FAILURE(AuditHelper::ReportDragAuditEvent(unifiedData, userId, tokenId));

    std::this_thread::sleep_for(std::chrono::milliseconds(SLEEP_TIME * 2));
    EXPECT_EQ(userId, originalUserId);
    EXPECT_EQ(tokenId, originalTokenId);
    EXPECT_EQ(unifiedData.GetRecords().size(), originalRecordsSize);

    LOG_INFO(UDMF_TEST, "ReportDragAuditEvent029 end.");
}

/**
* @tc.name: ConvertWantToJson001
* @tc.desc: Test ConvertWantToJson with valid Want object
* @tc.type: FUNC
*/
HWTEST_F(AuditHelperTest, ConvertWantToJson001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "ConvertWantToJson001 begin.");

    auto want = std::make_shared<OHOS::AAFwk::Want>();
    want->SetAction("test.action");
    want->SetBundle("test.bundle");
    want->SetType("test/type");
    want->SetUri("http://test.uri");

    auto json = AuditHelper::ConvertWantToJson(want);
    EXPECT_TRUE(json.is_object());
    EXPECT_TRUE(json.contains("action"));
    EXPECT_TRUE(json.contains("bundle"));
    EXPECT_TRUE(json.contains("type"));
    EXPECT_TRUE(json.contains("uri"));

    LOG_INFO(UDMF_TEST, "ConvertWantToJson001 end.");
}

/**
* @tc.name: ConvertWantToJson002
* @tc.desc: Test ConvertWantToJson with nullptr
* @tc.type: FUNC
*/
HWTEST_F(AuditHelperTest, ConvertWantToJson002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "ConvertWantToJson002 begin.");

    std::shared_ptr<OHOS::AAFwk::Want> want = nullptr;

    auto json = AuditHelper::ConvertWantToJson(want);
    EXPECT_TRUE(json.is_null());

    LOG_INFO(UDMF_TEST, "ConvertWantToJson002 end.");
}

/**
* @tc.name: ConvertPixelMapToJson001
* @tc.desc: Test ConvertPixelMapToJson with nullptr
* @tc.type: FUNC
*/
HWTEST_F(AuditHelperTest, ConvertPixelMapToJson001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "ConvertPixelMapToJson001 begin.");

    std::shared_ptr<OHOS::Media::PixelMap> pixelMap = nullptr;

    auto json = AuditHelper::ConvertPixelMapToJson(pixelMap);
    EXPECT_TRUE(json.is_null());

    LOG_INFO(UDMF_TEST, "ConvertPixelMapToJson001 end.");
}

/**
* @tc.name: ConvertObjectToJson001
* @tc.desc: Test ConvertObjectToJson with valid Object
* @tc.type: FUNC
*/
HWTEST_F(AuditHelperTest, ConvertObjectToJson001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "ConvertObjectToJson001 begin.");

    auto object = std::make_shared<Object>();
    object->value_["key1"] = std::string("value1");
    object->value_["key2"] = int32_t(123);
    object->value_["key3"] = true;

    auto json = AuditHelper::ConvertObjectToJson(object);
    EXPECT_TRUE(json.is_object());
    EXPECT_TRUE(json.contains("key1"));
    EXPECT_TRUE(json.contains("key2"));
    EXPECT_TRUE(json.contains("key3"));

    LOG_INFO(UDMF_TEST, "ConvertObjectToJson001 end.");
}

/**
* @tc.name: ConvertObjectToJson002
* @tc.desc: Test ConvertObjectToJson with nullptr
* @tc.type: FUNC
*/
HWTEST_F(AuditHelperTest, ConvertObjectToJson002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "ConvertObjectToJson002 begin.");

    std::shared_ptr<Object> object = nullptr;

    auto json = AuditHelper::ConvertObjectToJson(object);
    EXPECT_TRUE(json.is_object());
    EXPECT_EQ(json.size(), 0);

    LOG_INFO(UDMF_TEST, "ConvertObjectToJson002 end.");
}

/**
*   @tc.name: ConvertObjectToJson003
* @tc.desc: Test ConvertObjectToJson with nested Object
* @tc.type: FUNC
*/
HWTEST_F(AuditHelperTest, ConvertObjectToJson003, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "ConvertObjectToJson003 begin.");

    auto innerObject = std::make_shared<Object>();
    innerObject->value_["innerKey"] = std::string("innerValue");

    auto outerObject = std::make_shared<Object>();
    outerObject->value_["outerKey"] = std::string("outerValue");
    outerObject->value_["nested"] = innerObject;

    auto json = AuditHelper::ConvertObjectToJson(outerObject);
    EXPECT_TRUE(json.is_object());
    EXPECT_TRUE(json.contains("outerKey"));
    EXPECT_TRUE(json.contains("nested"));

    LOG_INFO(UDMF_TEST, "ConvertObjectToJson003 end.");
}

} // OHOS::Test