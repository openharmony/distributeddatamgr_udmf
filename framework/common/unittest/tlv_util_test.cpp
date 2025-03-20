/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


#define LOG_TAG "TlvUtilTest"

#include "tlv_util.h"
#include <gtest/gtest.h>
#include "unified_data.h"
#include "logger.h"
#include "plain_text.h"
#include "html.h"
#include "link.h"
#include "system_defined_appitem.h"
#include "application_defined_record.h"
#include "file.h"
#include "system_defined_form.h"
#include "system_defined_pixelmap.h"
#include "system_defined_record.h"
#include "udmf_conversion.h"
#include "unified_data_helper.h"
#include "unified_meta.h"
#include "unified_record.h"
#include "unified_types.h"

using namespace testing::ext;
using namespace OHOS::UDMF;
using namespace OHOS;

namespace OHOS::Test {
class TlvUtilTest : public testing::Test {
public:
    static void SetUpTestCase(void);

    static void TearDownTestCase(void);

    void SetUp();

    void TearDown();
};

void TlvUtilTest::SetUpTestCase(void) {}
void TlvUtilTest::TearDownTestCase(void) {}
void TlvUtilTest::SetUp(void) {}
void TlvUtilTest::TearDown(void) {}

/* *
 * @tc.name: CountBufferSize_001
 * @tc.desc: test fundamental for countBufferSize
 * @tc.type: FUNC
 */
HWTEST_F(TlvUtilTest, CountBufferSize_001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "CountBufferSize_001 begin.");
    std::vector<uint8_t> dataBytes;
    auto tlvObject = TLVObject(dataBytes);
    uint8_t num1 = 1;
    EXPECT_EQ(sizeof(TLVHead) + sizeof(num1), TLVUtil::CountBufferSize(num1, tlvObject)); // 7
    uint16_t num2 = 1;
    EXPECT_EQ(sizeof(TLVHead) + sizeof(num2), TLVUtil::CountBufferSize(num2, tlvObject)); // 8
    uint32_t num3 = 1;
    EXPECT_EQ(sizeof(TLVHead) + sizeof(num3), TLVUtil::CountBufferSize(num3, tlvObject)); // 10
    int16_t num4 = 1;
    EXPECT_EQ(sizeof(TLVHead) + sizeof(num4), TLVUtil::CountBufferSize(num4, tlvObject)); // 8
    int32_t num5 = 1;
    EXPECT_EQ(sizeof(TLVHead) + sizeof(num5), TLVUtil::CountBufferSize(num5, tlvObject)); // 10
    bool boolean = true;
    EXPECT_EQ(sizeof(TLVHead) + sizeof(boolean), TLVUtil::CountBufferSize(boolean, tlvObject)); // 7
    double doubleNum = 1;
    EXPECT_EQ(sizeof(TLVHead) + sizeof(doubleNum), TLVUtil::CountBufferSize(doubleNum, tlvObject)); // 14
    EXPECT_EQ(sizeof(TLVHead), TLVUtil::CountBufferSize(std::nullptr_t(), tlvObject));              // 6
    std::monostate monostate;
    EXPECT_EQ(sizeof(TLVHead), TLVUtil::CountBufferSize(monostate, tlvObject)); // 6
    std::string str = "abc";
    EXPECT_EQ(sizeof(TLVHead) + str.size(), TLVUtil::CountBufferSize(str, tlvObject)); // 9
    UDType type = XML;
    EXPECT_EQ(sizeof(TLVHead) + sizeof(type), TLVUtil::CountBufferSize(type, tlvObject)); // 10
    DataStatus status = HISTORY;
    EXPECT_EQ(sizeof(TLVHead) + sizeof(status), TLVUtil::CountBufferSize(status, tlvObject)); // 10
    std::vector<uint8_t> u8Vector = { 1, 1, 1 };
    EXPECT_EQ(sizeof(TLVHead) + u8Vector.size(), TLVUtil::CountBufferSize(u8Vector, tlvObject)); // 9
    std::shared_ptr<uint8_t> ptr;
    EXPECT_EQ(sizeof(TLVHead), TLVUtil::CountBufferSize(ptr, tlvObject)); // 6
    ptr = std::make_shared<uint8_t>(1);
    EXPECT_EQ(sizeof(TLVHead) + 1, TLVUtil::CountBufferSize(ptr, tlvObject)); // 7
    LOG_INFO(UDMF_TEST, "CountBufferSize_001 end.");
}

/* *
 * @tc.name: CountBufferSize_002
 * @tc.desc: test STL for countBufferSize
 * @tc.type: FUNC
 */
HWTEST_F(TlvUtilTest, CountBufferSize_002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "CountBufferSize_002 begin.");
    std::vector<uint8_t> dataBytes;
    auto tlvObject = TLVObject(dataBytes);
    Privilege privilege1;
    privilege1.readPermission = "111";
    Privilege privilege2;
    privilege2.readPermission = "111";
    privilege2.writePermission = "xx";
    std::vector<Privilege> privilegeVector{ privilege1, privilege2 };
    EXPECT_EQ(10 * sizeof(TLVHead) + 2 * sizeof(uint32_t) + sizeof(size_t) + 8,
        TLVUtil::CountBufferSize(privilegeVector, tlvObject)); // 80

    Object object;
    std::map<std::string, ValueType> map;
    map["keyString"] = "value";
    double key = 12;
    map["keyNum"] = key;
    object.value_ = map;
    EXPECT_EQ(12 * sizeof(TLVHead) + 36, TLVUtil::CountBufferSize(object, tlvObject)); // 108
    auto total = tlvObject.GetTotal();
    EXPECT_EQ(188, total);
    LOG_INFO(UDMF_TEST, "CountBufferSize_002 end.");
}

/* *
 * @tc.name: CountBufferSize_003
 * @tc.desc: test udmf for countBufferSize
 * @tc.type: FUNC
 */
HWTEST_F(TlvUtilTest, CountBufferSize_003, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "CountBufferSize_003 begin.");
    std::vector<uint8_t> dataBytes;
    auto tlvObject = TLVObject(dataBytes);

    std::shared_ptr<Object> object = std::make_shared<Object>();
    std::map<std::string, ValueType> map;
    map["uniformDataType"] = UtdUtils::GetUtdIdFromUtdEnum(UDType::PLAIN_TEXT);
    map["textContent"] = "content";
    map["abstract"] = "abstract";
    object->value_ = map;
    std::shared_ptr<UnifiedRecord> record = std::make_shared<PlainText>(PLAIN_TEXT, object);

    std::vector<std::shared_ptr<UnifiedRecord>> vector = { record };
    UnifiedData data;
    data.SetRecords(vector);
    std::vector<UnifiedData> unifiedData = { data };
    auto size = TLVUtil::CountBufferSize(unifiedData, tlvObject);
    EXPECT_EQ(tlvObject.GetTotal(), size); // 269
    LOG_INFO(UDMF_TEST, "CountBufferSize_003 end.");
}

/* *
 * @tc.name: CountBufferSize_004
 * @tc.desc: test other for countBufferSize
 * @tc.type: FUNC
 */
HWTEST_F(TlvUtilTest, CountBufferSize_004, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "CountBufferSize_004 begin.");
    std::vector<uint8_t> dataBytes;
    auto tlvObject = TLVObject(dataBytes);

    UnifiedKey key;
    key.key = "123456";
    key.intention = "DRAG";
    key.bundleName = "com.xxx";
    EXPECT_EQ(5 * sizeof(TLVHead) + 17, TLVUtil::CountBufferSize(key, tlvObject));

    Privilege privilege;
    EXPECT_EQ(4 * sizeof(TLVHead) + sizeof(int32_t), TLVUtil::CountBufferSize(privilege, tlvObject));

    Runtime runtime;
    EXPECT_EQ(19 * sizeof(TLVHead) + sizeof(bool) + sizeof(size_t) + 2 * sizeof(int64_t) + 2 * sizeof(int32_t) +
        2 * sizeof(uint32_t),
        TLVUtil::CountBufferSize(runtime, tlvObject));
    LOG_INFO(UDMF_TEST, "CountBufferSize_004 end.");
}

/* *
 * @tc.name: WritingAndReading_001
 * @tc.desc: test fundamental for Writing And Reading
 * @tc.type: FUNC
 */
HWTEST_F(TlvUtilTest, WritingAndReading_001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "WritingAndReading_001 begin.");
    std::vector<uint8_t> dataBytes;
    auto tlvObject = TLVObject(dataBytes);
    uint16_t num1 = 1;
    auto result = TLVUtil::Writing(num1, tlvObject, TAG::TAG_UINT16);
    int8_t num2 = 2;
    result = TLVUtil::Writing(num2, tlvObject, TAG::TAG_INT8) && result;
    uint32_t num3 = 3;
    result = TLVUtil::Writing(num3, tlvObject, TAG::TAG_UINT32) && result;
    int16_t num4 = 4;
    result = TLVUtil::Writing(num4, tlvObject, TAG::TAG_INT16) && result;
    int32_t num5 = 5;
    result = result = TLVUtil::Writing(num5, tlvObject, TAG::TAG_INT32) && result;
    bool boolean = true;
    result = TLVUtil::Writing(boolean, tlvObject, TAG::TAG_BOOL) && result;
    result = TLVUtil::Writing(std::nullptr_t(), tlvObject, TAG::TAG_NULL);
    std::monostate monostate;
    result = TLVUtil::Writing(monostate, tlvObject, TAG::TAG_MONOSTATE) && result;
    std::string str = "abc";
    result = TLVUtil::Writing(str, tlvObject, TAG::TAG_STRING) && result;
    UDType type = XML;
    result = TLVUtil::Writing(type, tlvObject, TAG::TAG_UD_TYPE) && result;
    DataStatus status = HISTORY;
    result = TLVUtil::Writing(status, tlvObject, TAG::TAG_DATA_STATUS) && result;
    std::vector<uint8_t> u8Vector = { 1, 2, 3 };
    result = TLVUtil::Writing(u8Vector, tlvObject, TAG::TAG_UINT8) && result;
    EXPECT_TRUE(result);

    uint16_t num1Result;
    int8_t num2Result;
    uint32_t num3Result;
    int16_t num4Result;
    int32_t num5Result;
    bool booleanResult;
    std::string strResult;
    UDType typeResult;
    DataStatus statusResult;
    std::vector<uint8_t> u8VectorResult;

    tlvObject.ResetCursor();
    TLVUtil::ReadTlv(statusResult, tlvObject, TAG::TAG_DATA_STATUS);
    tlvObject.ResetCursor();
    EXPECT_EQ(status, statusResult);

    tlvObject.ResetCursor();
    TLVUtil::ReadTlv(typeResult, tlvObject, TAG::TAG_UD_TYPE);
    EXPECT_EQ(type, typeResult);

    tlvObject.ResetCursor();
    TLVUtil::ReadTlv(strResult, tlvObject, TAG::TAG_STRING);
    EXPECT_EQ(str, strResult);

    tlvObject.ResetCursor();
    TLVUtil::ReadTlv(booleanResult, tlvObject, TAG::TAG_BOOL);
    EXPECT_EQ(boolean, booleanResult);

    tlvObject.ResetCursor();
    TLVUtil::ReadTlv(num5Result, tlvObject, TAG::TAG_INT32);
    EXPECT_EQ(num5, num5Result);

    tlvObject.ResetCursor();
    TLVUtil::ReadTlv(num4Result, tlvObject, TAG::TAG_INT16);
    EXPECT_EQ(num4, num4Result);

    tlvObject.ResetCursor();
    TLVUtil::ReadTlv(num3Result, tlvObject, TAG::TAG_UINT32);
    EXPECT_EQ(num3, num3Result);

    tlvObject.ResetCursor();
    TLVUtil::ReadTlv(num2Result, tlvObject, TAG::TAG_INT8);
    EXPECT_EQ(num2, num2Result);

    tlvObject.ResetCursor();
    TLVUtil::ReadTlv(num1Result, tlvObject, TAG::TAG_UINT16);
    EXPECT_EQ(num1, num1Result);

    tlvObject.ResetCursor();
    TLVUtil::ReadTlv(u8VectorResult, tlvObject, TAG::TAG_UINT8);
    for (int i = 0; i < 3; i++) {
        EXPECT_EQ(u8Vector[i], u8VectorResult[i]);
    }
    LOG_INFO(UDMF_TEST, "WritingAndReading_001 end.");
}

/* *
 * @tc.name: WritingAndReading_002
 * @tc.desc: test Runtime for Writing And Reading
 * @tc.type: FUNC
 */
HWTEST_F(TlvUtilTest, WritingAndReading_002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "WritingAndReading_002 begin.");
    UnifiedKey key;
    key.key = "123456";
    Privilege privilege;
    privilege.readPermission = "read";
    privilege.tokenId = 333;
    Privilege privilege2;
    privilege2.writePermission = "read";
    privilege2.tokenId = 444;
    Runtime runtime;
    runtime.dataStatus = DELETED;
    runtime.key = key;
    runtime.privileges.push_back(privilege);
    runtime.privileges.push_back(privilege2);
    runtime.createTime = 1;
    runtime.dataVersion = 3;
    runtime.createPackage = "package";
    runtime.isPrivate = true;

    std::vector<uint8_t> dataBytes;
    auto tlvObject = TLVObject(dataBytes);
    EXPECT_TRUE(TLVUtil::Writing(runtime, tlvObject, TAG::TAG_RUNTIME));

    tlvObject.ResetCursor();
    Runtime runtimeResult;
    EXPECT_TRUE(TLVUtil::ReadTlv(runtimeResult, tlvObject, TAG::TAG_RUNTIME));
    EXPECT_EQ(runtime.key.key, runtimeResult.key.key);
    EXPECT_EQ(runtime.key.key, runtimeResult.key.key);
    EXPECT_EQ(runtime.dataStatus, runtimeResult.dataStatus);
    EXPECT_EQ(runtime.createTime, runtimeResult.createTime);
    EXPECT_EQ(runtime.dataVersion, runtimeResult.dataVersion);
    EXPECT_EQ(runtime.createPackage, runtimeResult.createPackage);
    EXPECT_EQ(runtime.isPrivate, runtimeResult.isPrivate);
    EXPECT_EQ(runtime.privileges[0].readPermission, runtimeResult.privileges[0].readPermission);
    EXPECT_EQ(runtime.privileges[0].tokenId, runtimeResult.privileges[0].tokenId);
    EXPECT_EQ(runtime.privileges[1].writePermission, runtimeResult.privileges[1].writePermission);
    EXPECT_EQ(runtime.privileges[1].tokenId, runtimeResult.privileges[1].tokenId);

    LOG_INFO(UDMF_TEST, "WritingAndReading_002 end.");
}

/* *
 * @tc.name: WritingAndReading_003
 * @tc.desc: test UnifiedData for Writing And Reading
 * @tc.type: FUNC
 */
HWTEST_F(TlvUtilTest, WritingAndReading_003, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "WritingAndReading_003 begin.");

    std::map<std::string, ValueType> value;
    value["fileType"] = "File Type";
    value["fileUri"] = "File Uri";
    std::shared_ptr<Object> obj = std::make_shared<Object>();
    obj->value_ = value;
    std::shared_ptr<UnifiedRecord> fileUri = std::make_shared<UnifiedRecord>(UDType::FILE_URI, obj);

    std::shared_ptr<UnifiedRecord> plainText = std::make_shared<PlainText>(UDType::PLAIN_TEXT, "this is a content");
    std::shared_ptr<UnifiedRecord> html = std::make_shared<Html>(UDType::HTML, "this is a HTML content");

    std::vector<std::shared_ptr<UnifiedRecord>> records = { fileUri, plainText, html };

    UnifiedData data1;
    data1.SetRecords(records);

    std::shared_ptr<SystemDefinedAppItem> appItem =
        std::make_shared<SystemDefinedAppItem>(UDType::SYSTEM_DEFINED_APP_ITEM, "OTHER param");
    appItem->SetAppId("com.demo");
    std::shared_ptr<ApplicationDefinedRecord> defineRecord =
        std::make_shared<ApplicationDefinedRecord>(UDType::APPLICATION_DEFINED_RECORD, "OTHER param");
    std::vector<uint8_t> u8Vector = { 1, 2, 3, 4 };
    defineRecord->SetRawData(u8Vector);
    std::shared_ptr<UnifiedRecord> file = std::make_shared<File>(UDType::FILE, "this is a oriUri");

    std::vector<std::shared_ptr<UnifiedRecord>> records2 = { appItem, defineRecord, file };

    UnifiedData data2;
    data2.SetRecords(records2);

    std::vector<UnifiedData> datas = { data1, data2 };

    std::vector<uint8_t> dataBytes;
    auto tlvObject = TLVObject(dataBytes);

    UdmfConversion::InitValueObject(datas);
    EXPECT_TRUE(TLVUtil::Writing(datas, tlvObject, TAG::TAG_UNIFIED_DATA));

    tlvObject.ResetCursor();
    std::vector<UnifiedData> datasResult;

    EXPECT_TRUE(TLVUtil::ReadTlv(datasResult, tlvObject, TAG::TAG_UNIFIED_DATA));
    EXPECT_EQ(2, datasResult.size());
    UdmfConversion::ConvertRecordToSubclass(datasResult);

    auto recordsResult = datasResult[0].GetRecords();
    EXPECT_EQ(3, recordsResult.size());

    auto fileUriResult = recordsResult[0];
    EXPECT_EQ(UDType::FILE_URI, fileUriResult->GetType());
    auto fileUriValue = fileUriResult->GetValue();
    EXPECT_TRUE(std::holds_alternative<std::shared_ptr<Object>>(fileUriValue));
    auto fileUriObj = std::get<std::shared_ptr<Object>>(fileUriValue);
    EXPECT_EQ("File Uri", std::get<std::string>(fileUriObj->value_["fileUri"]));
    EXPECT_EQ("File Type", std::get<std::string>(fileUriObj->value_["fileType"]));

    auto plainTextResult = recordsResult[1];
    EXPECT_EQ(UDType::PLAIN_TEXT, plainTextResult->GetType());
    auto plainTextSubclass = std::static_pointer_cast<PlainText>(plainTextResult);
    EXPECT_EQ("this is a content", plainTextSubclass->GetContent());
    auto plainTextValue = plainTextSubclass->GetValue();
    EXPECT_TRUE(std::holds_alternative<std::string>(plainTextValue));

    auto htmlResult = recordsResult[2];
    EXPECT_EQ(UDType::HTML, htmlResult->GetType());
    auto htmlSubclass = std::static_pointer_cast<Html>(htmlResult);
    EXPECT_EQ("this is a HTML content", htmlSubclass->GetHtmlContent());
    auto htmlValue = htmlSubclass->GetValue();
    EXPECT_TRUE(std::holds_alternative<std::string>(htmlValue));

    auto recordsResult2 = datasResult[1].GetRecords();
    EXPECT_EQ(3, recordsResult2.size());
    auto appItemResult = recordsResult2[0];
    EXPECT_EQ(UDType::SYSTEM_DEFINED_APP_ITEM, appItemResult->GetType());
    auto appItemSubclass = std::static_pointer_cast<SystemDefinedAppItem>(appItemResult);
    EXPECT_EQ("com.demo", appItemSubclass->GetAppId());
    auto appItemValue = appItemSubclass->GetValue();
    EXPECT_TRUE(std::holds_alternative<std::string>(appItemValue));

    auto defineRecordResult = recordsResult2[1];
    EXPECT_EQ(UDType::APPLICATION_DEFINED_RECORD, defineRecordResult->GetType());
    auto adefineRecordSubclass = std::static_pointer_cast<ApplicationDefinedRecord>(defineRecordResult);
    auto u8VectorResult = adefineRecordSubclass->GetRawData();
    EXPECT_EQ(4, u8VectorResult.size());
    auto adefineRecordValue = adefineRecordSubclass->GetValue();
    EXPECT_TRUE(std::holds_alternative<std::string>(adefineRecordValue));

    auto fileResult = recordsResult2[2];
    EXPECT_EQ(UDType::FILE, fileResult->GetType());
    auto fileSubclass = std::static_pointer_cast<File>(fileResult);
    EXPECT_EQ(16, fileSubclass->GetSize());
    auto fileValue = fileSubclass->GetValue();
    EXPECT_TRUE(std::holds_alternative<std::string>(fileValue));

    LOG_INFO(UDMF_TEST, "WritingAndReading_003 end.");
}

/* *
 * @tc.name: WritingAndReading_004
 * @tc.desc: test UnifiedData for Writing And Reading
 * @tc.type: FUNC
 */
HWTEST_F(TlvUtilTest, WritingAndReading_004, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "WritingAndReading_004 begin.");

    uint32_t color[100] = { 3, 7, 9, 9, 7, 6 };
    OHOS::Media::InitializationOptions opts = { { 5, 7 },
        Media::PixelFormat::ARGB_8888,
        Media::PixelFormat::ARGB_8888 };
    std::unique_ptr<OHOS::Media::PixelMap> pixelMap =
        OHOS::Media::PixelMap::Create(color, sizeof(color) / sizeof(color[0]), opts);
    std::shared_ptr<OHOS::Media::PixelMap> pixelMapIn = move(pixelMap);
    std::map<std::string, ValueType> value;
    value["pixelMap"] = pixelMapIn;
    std::shared_ptr<Object> obj = std::make_shared<Object>();
    obj->value_ = value;
    std::shared_ptr<UnifiedRecord> pixelMapRecord =
        std::make_shared<SystemDefinedPixelMap>(UDType::SYSTEM_DEFINED_PIXEL_MAP, obj);

    std::shared_ptr<SystemDefinedForm> form =
        std::make_shared<SystemDefinedForm>(UDType::SYSTEM_DEFINED_FORM, "Other parm");
    form->SetFormName("HAPPY DAY");

    UDDetails details;
    details.emplace("name", "ZhangSan");
    details.emplace("age", 30);
    details.emplace("isFemal", true);
    std::shared_ptr<SystemDefinedRecord> definedRecord =
        std::make_shared<SystemDefinedRecord>(UDType::SYSTEM_DEFINED_RECORD, "Other parm");
    definedRecord->SetDetails(details);
    std::vector<std::shared_ptr<UnifiedRecord>> records = { pixelMapRecord, form, definedRecord };

    UnifiedData data;
    data.SetRecords(records);

    std::vector<UnifiedData> datas = { data };

    std::vector<uint8_t> dataBytes;
    auto tlvObject = TLVObject(dataBytes);

    UdmfConversion::InitValueObject(datas);
    EXPECT_TRUE(TLVUtil::Writing(datas, tlvObject, TAG::TAG_UNIFIED_DATA));

    tlvObject.ResetCursor();
    std::vector<UnifiedData> datasResult;

    EXPECT_TRUE(TLVUtil::ReadTlv(datasResult, tlvObject, TAG::TAG_UNIFIED_DATA));
    EXPECT_EQ(1, datasResult.size());
    UdmfConversion::ConvertRecordToSubclass(datasResult);

    auto recordsResult = datasResult[0].GetRecords();
    EXPECT_EQ(3, recordsResult.size());

    auto pixelMapRecordResult = recordsResult[0];
    EXPECT_EQ(UDType::SYSTEM_DEFINED_PIXEL_MAP, pixelMapRecordResult->GetType());
    auto pixelMapValue = pixelMapRecordResult->GetValue();
    EXPECT_TRUE(std::holds_alternative<std::shared_ptr<Object>>(pixelMapValue));
    auto pixelMapObj = std::get<std::shared_ptr<Object>>(pixelMapValue);
    EXPECT_TRUE(std::holds_alternative<std::shared_ptr<OHOS::Media::PixelMap>>(pixelMapObj->value_["pixelMap"]));
    auto piexelMapResult = std::get<std::shared_ptr<OHOS::Media::PixelMap>>(pixelMapObj->value_["pixelMap"]);
    EXPECT_EQ(7, piexelMapResult->GetHeight());

    auto formResult = recordsResult[1];
    EXPECT_EQ(UDType::SYSTEM_DEFINED_FORM, formResult->GetType());
    auto formSubclass = std::static_pointer_cast<SystemDefinedForm>(formResult);
    EXPECT_EQ("HAPPY DAY", formSubclass->GetFormName());
    auto formValue = formSubclass->GetValue();
    EXPECT_TRUE(std::holds_alternative<std::string>(formValue));

    auto definedRecordResult = recordsResult[2];
    EXPECT_EQ(UDType::SYSTEM_DEFINED_RECORD, definedRecordResult->GetType());
    auto definedRecordSubclass = std::static_pointer_cast<SystemDefinedRecord>(definedRecordResult);
    auto detailsRecord = definedRecordSubclass->GetDetails();
    EXPECT_EQ("ZhangSan", std::get<std::string>(detailsRecord["name"]));
    EXPECT_EQ(30, std::get<int32_t>(detailsRecord["age"]));
    EXPECT_TRUE(std::get<bool>(detailsRecord["isFemal"]));
    auto definedRecordValue = definedRecordSubclass->GetValue();
    EXPECT_TRUE(std::holds_alternative<std::string>(definedRecordValue));

    LOG_INFO(UDMF_TEST, "WritingAndReading_004 end.");
}

/* *
 * @tc.name: WritingAndReading_005
 * @tc.desc: test Want for Writing And Reading
 * @tc.type: FUNC
 */
HWTEST_F(TlvUtilTest, WritingAndReading_005, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "WritingAndReading_005 begin.");
    std::shared_ptr<OHOS::AAFwk::Want> want = std::make_shared<OHOS::AAFwk::Want>();
    std::string idKey = "id";
    int32_t idValue = 123;
    want->SetParam(idKey, idValue);
    std::map<std::string, ValueType> value;
    value["want"] = want;
    std::shared_ptr<Object> obj = std::make_shared<Object>();
    obj->value_ = value;

    std::vector<uint8_t> dataBytes;
    auto tlvObject = TLVObject(dataBytes);

    EXPECT_TRUE(TLVUtil::Writing(obj, tlvObject, TAG::TAG_OBJECT_VALUE));
    tlvObject.ResetCursor();
    std::shared_ptr<Object> objResult = std::make_shared<Object>();
    EXPECT_TRUE(TLVUtil::ReadTlv(objResult, tlvObject, TAG::TAG_OBJECT_VALUE));
    auto valueResult = objResult->value_;
    EXPECT_TRUE(std::holds_alternative<std::shared_ptr<OHOS::AAFwk::Want>>(valueResult["want"]));
    auto wantResult = std::get<std::shared_ptr<OHOS::AAFwk::Want>>(valueResult["want"]);
    EXPECT_EQ(idValue, wantResult->GetIntParam(idKey, 0));
    LOG_INFO(UDMF_TEST, "WritingAndReading_005 end.");
}

/* *
 * @tc.name: WritingAndReadingFile_001
 * @tc.desc: test Unified Data for Writing And Reading
 * @tc.type: FUNC
 */
HWTEST_F(TlvUtilTest, WritingAndReadingFile_001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "WritingAndReadingFile_001 begin.");
    std::map<std::string, ValueType> value;
    value["fileType"] = "File Type";
    value["fileUri"] = "File Uri";
    std::shared_ptr<Object> obj = std::make_shared<Object>();
    obj->value_ = value;
    std::shared_ptr<UnifiedRecord> fileUri = std::make_shared<UnifiedRecord>(UDType::FILE_URI, obj);

    std::shared_ptr<UnifiedRecord> plainText = std::make_shared<PlainText>(UDType::PLAIN_TEXT, "this is a content");
    std::shared_ptr<UnifiedRecord> html = std::make_shared<Html>(UDType::HTML, "this is a HTML content");

    std::vector<std::shared_ptr<UnifiedRecord>> records = { fileUri, plainText, html };

    UnifiedData data1;
    data1.SetRecords(records);

    std::shared_ptr<SystemDefinedAppItem> appItem =
        std::make_shared<SystemDefinedAppItem>(UDType::SYSTEM_DEFINED_APP_ITEM, "OTHER param");
    appItem->SetAppId("com.demo");
    std::shared_ptr<ApplicationDefinedRecord> defineRecord =
        std::make_shared<ApplicationDefinedRecord>(UDType::APPLICATION_DEFINED_RECORD, "OTHER param");
    std::vector<uint8_t> u8Vector = { 1, 2, 3, 4 };
    defineRecord->SetRawData(u8Vector);
    std::shared_ptr<UnifiedRecord> fileRecord = std::make_shared<File>(UDType::FILE, "this is a oriUri");

    std::vector<std::shared_ptr<UnifiedRecord>> records2 = { appItem, defineRecord, fileRecord };

    UnifiedData data2;
    data2.SetRecords(records2);

    std::vector<UnifiedData> datas = { data1, data2 };

    std::string dataFile = "demo1";
    std::vector<uint8_t> dataBytes;
    auto tlvObject = TLVObject(dataBytes);

    std::FILE *file = fopen(dataFile.c_str(), "w+");
    tlvObject.SetFile(file);
    UdmfConversion::InitValueObject(datas);
    EXPECT_TRUE(TLVUtil::Writing(datas, tlvObject, TAG::TAG_UNIFIED_DATA));

    tlvObject.ResetCursor();
    std::vector<UnifiedData> datasResult;

    EXPECT_TRUE(TLVUtil::ReadTlv(datasResult, tlvObject, TAG::TAG_UNIFIED_DATA));
    EXPECT_EQ(2, datasResult.size());
    UdmfConversion::ConvertRecordToSubclass(datasResult);

    auto recordsResult = datasResult[0].GetRecords();
    EXPECT_EQ(3, recordsResult.size());

    auto fileUriResult = recordsResult[0];
    EXPECT_EQ(UDType::FILE_URI, fileUriResult->GetType());
    auto fileUriValue = fileUriResult->GetValue();
    EXPECT_TRUE(std::holds_alternative<std::shared_ptr<Object>>(fileUriValue));
    auto fileUriObj = std::get<std::shared_ptr<Object>>(fileUriValue);
    EXPECT_EQ("File Uri", std::get<std::string>(fileUriObj->value_["fileUri"]));
    EXPECT_EQ("File Type", std::get<std::string>(fileUriObj->value_["fileType"]));

    auto plainTextResult = recordsResult[1];
    EXPECT_EQ(UDType::PLAIN_TEXT, plainTextResult->GetType());
    auto plainTextSubclass = std::static_pointer_cast<PlainText>(plainTextResult);
    EXPECT_EQ("this is a content", plainTextSubclass->GetContent());
    auto plainTextValue = plainTextSubclass->GetValue();
    EXPECT_TRUE(std::holds_alternative<std::string>(plainTextValue));

    auto htmlResult = recordsResult[2];
    EXPECT_EQ(UDType::HTML, htmlResult->GetType());
    auto htmlSubclass = std::static_pointer_cast<Html>(htmlResult);
    EXPECT_EQ("this is a HTML content", htmlSubclass->GetHtmlContent());
    auto htmlValue = htmlSubclass->GetValue();
    EXPECT_TRUE(std::holds_alternative<std::string>(htmlValue));

    auto recordsResult2 = datasResult[1].GetRecords();
    EXPECT_EQ(3, recordsResult2.size());
    auto appItemResult = recordsResult2[0];
    EXPECT_EQ(UDType::SYSTEM_DEFINED_APP_ITEM, appItemResult->GetType());
    auto appItemSubclass = std::static_pointer_cast<SystemDefinedAppItem>(appItemResult);
    EXPECT_EQ("com.demo", appItemSubclass->GetAppId());
    auto appItemValue = appItemSubclass->GetValue();
    EXPECT_TRUE(std::holds_alternative<std::string>(appItemValue));

    auto defineRecordResult = recordsResult2[1];
    EXPECT_EQ(UDType::APPLICATION_DEFINED_RECORD, defineRecordResult->GetType());
    auto adefineRecordSubclass = std::static_pointer_cast<ApplicationDefinedRecord>(defineRecordResult);
    auto u8VectorResult = adefineRecordSubclass->GetRawData();
    EXPECT_EQ(4, u8VectorResult.size());
    auto adefineRecordValue = adefineRecordSubclass->GetValue();
    EXPECT_TRUE(std::holds_alternative<std::string>(adefineRecordValue));

    auto fileResult = recordsResult2[2];
    EXPECT_EQ(UDType::FILE, fileResult->GetType());
    auto fileSubclass = std::static_pointer_cast<File>(fileResult);
    EXPECT_EQ(16, fileSubclass->GetSize());
    auto fileValue = fileSubclass->GetValue();
    EXPECT_TRUE(std::holds_alternative<std::string>(fileValue));

    fclose(file);
    LOG_INFO(UDMF_TEST, "WritingAndReadingFile_001 end.");
}

/* *
 * @tc.name: WritingAndReadingSummary_001
 * @tc.desc: test Summary for Writing And Reading
 * @tc.type: FUNC
 */
HWTEST_F(TlvUtilTest, WritingAndReadingSummary_001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "WritingAndReadingSummary_001 begin.");
    std::map<std::string, ValueType> value;
    value["fileType"] = "File Type";
    value["fileUri"] = "File Uri";
    std::shared_ptr<Object> obj = std::make_shared<Object>();
    obj->value_ = value;
    std::shared_ptr<UnifiedRecord> fileUri = std::make_shared<UnifiedRecord>(UDType::FILE_URI, obj);
    std::shared_ptr<UnifiedRecord> plainText = std::make_shared<PlainText>(UDType::PLAIN_TEXT, "this is a content");
    std::shared_ptr<UnifiedRecord> html = std::make_shared<Html>(UDType::HTML, "this is a HTML content");
    std::vector<std::shared_ptr<UnifiedRecord>> records = { fileUri, plainText, html };
    UnifiedData data1;
    data1.SetRecords(records);
    Summary summary;
    UnifiedDataHelper::GetSummary(data1, summary);
    EXPECT_EQ(summary.summary.size(), records.size());

    std::vector<uint8_t> dataBytes;
    auto tlvObject = TLVObject(dataBytes);
    EXPECT_TRUE(TLVUtil::Writing(summary, tlvObject, TAG::TAG_SUMMARY));

    tlvObject.ResetCursor();
    Summary summary2;
    TLVUtil::ReadTlv(summary2, tlvObject, TAG::TAG_SUMMARY);
    EXPECT_EQ(summary.totalSize, summary2.totalSize);
    EXPECT_EQ(summary.summary.size(), summary2.summary.size());
    for (const auto &[key, val  ] : summary.summary) {
        ASSERT_TRUE(summary2.summary.find(key) != summary2.summary.end());
        EXPECT_EQ(summary.summary[key], summary2.summary[key]);
    }
    LOG_INFO(UDMF_TEST, "WritingAndReadingSummary_001 end.");
}

/* *
 * @tc.name: WritingAndReadingVersion_001
 * @tc.desc: test Version for Writing And Reading
 * @tc.type: FUNC
 */
HWTEST_F(TlvUtilTest, WritingAndReadingVersion_001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "WritingAndReadingVersion_001 begin.");
    std::shared_ptr<UnifiedRecord> plainText = std::make_shared<PlainText>(UDType::PLAIN_TEXT, "this is a content");
    std::shared_ptr<UnifiedRecord> html = std::make_shared<Html>(UDType::HTML, "this is a HTML content");
    std::vector<std::shared_ptr<UnifiedRecord>> records = {plainText, html };
    UnifiedData data1;
    data1.SetRecords(records);
    auto version = data1.GetSdkVersion();

    std::vector<uint8_t> dataBytes;
    auto tlvObject = TLVObject(dataBytes);
    std::vector<UnifiedData> datas = {data1};
    EXPECT_TRUE(TLVUtil::Writing(datas, tlvObject, TAG::TAG_UNIFIED_DATA));

    tlvObject.ResetCursor();
    std::vector<UnifiedData> datas2;
    TLVUtil::ReadTlv(datas2, tlvObject, TAG::TAG_UNIFIED_DATA);
    EXPECT_EQ(datas2.size(), 1);
    EXPECT_EQ(datas2[0].GetSdkVersion(), version);
    LOG_INFO(UDMF_TEST, "WritingAndReadingVersion_001 end."); 
}
}
