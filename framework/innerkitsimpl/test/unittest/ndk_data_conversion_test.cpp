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

#define LOG_TAG "NdkDataConversionTest"

#include "ndk_data_conversion.h"
#include <gtest/gtest.h>
#include <memory>
#include "token_setproc.h"
#include "accesstoken_kit.h"
#include "nativetoken_kit.h"
#include "logger.h"
#include "application_defined_record.h"
#include "error_code.h"
#include "html.h"
#include "udmf.h"
#include "udmf_capi_common.h"
#include "udmf_client.h"
#include "udmf_meta.h"
#include "uds.h"
#include "unified_data.h"
#include "pixelmap_native_impl.h"
#include "system_defined_pixelmap.h"

using namespace testing::ext;
using namespace OHOS::Security::AccessToken;
using namespace OHOS::UDMF;
using namespace OHOS;

namespace OHOS::Test {
class NdkDataConversionTest : public testing::Test {
public:
    static void SetUpTestCase(void);
    static void TearDownTestCase(void);
    void SetUp();
    void TearDown();
    static void AllocHapToken1();
    static void AllocHapToken2();
    void SetHapToken1();
    static constexpr int USER_ID = 100;
    static constexpr int INST_INDEX = 0;
};

void NdkDataConversionTest::SetUpTestCase()
{
    AllocHapToken1();
    AllocHapToken2();
}

void NdkDataConversionTest::TearDownTestCase()
{
    auto tokenId = AccessTokenKit::GetHapTokenID(USER_ID, "ohos.test.demo1", INST_INDEX);
    AccessTokenKit::DeleteToken(tokenId);
    tokenId = AccessTokenKit::GetHapTokenID(USER_ID, "ohos.test.demo2", INST_INDEX);
    AccessTokenKit::DeleteToken(tokenId);
}

void NdkDataConversionTest::SetUp()
{
    SetHapToken1();
}

void NdkDataConversionTest::TearDown() {}

void NdkDataConversionTest::AllocHapToken1()
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
        .permList = { {
        .permissionName = "ohos.permission.test",
        .bundleName = "ohos.test.demo1",
        .grantMode = 1,
        .availableLevel = APL_NORMAL,
        .label = "label",
        .labelId = 1,
        .description = "test1",
        .descriptionId = 1 } },
        .permStateList = { {
        .permissionName = "ohos.permission.test",
        .isGeneral = true,
        .resDeviceID = { "local" },
        .grantStatus = { PermissionState::PERMISSION_GRANTED },
        .grantFlags = { 1 } } }
    };
    auto tokenID = AccessTokenKit::AllocHapToken(info, policy);
    SetSelfTokenID(tokenID.tokenIDEx);
}

void NdkDataConversionTest::AllocHapToken2()
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
        .permList = { {
        .permissionName = "ohos.permission.test",
        .bundleName = "ohos.test.demo2",
        .grantMode = 1,
        .availableLevel = APL_NORMAL,
        .label = "label",
        .labelId = 1,
        .description = "test2",
        .descriptionId = 1 } },
        .permStateList = { {
        .permissionName = "ohos.permission.test",
        .isGeneral = true,
        .resDeviceID = { "local" },
        .grantStatus = { PermissionState::PERMISSION_GRANTED },
        .grantFlags = { 1 } } }
    };
    auto tokenID = AccessTokenKit::AllocHapToken(info, policy);
    SetSelfTokenID(tokenID.tokenIDEx);
}

void NdkDataConversionTest::SetHapToken1()
{
    auto tokenId = AccessTokenKit::GetHapTokenID(USER_ID, "ohos.test.demo1", INST_INDEX);
    SetSelfTokenID(tokenId);
}

/* *
 * @tc.name: GetNativeUnifiedData_001
 * @tc.desc: Normal testcase of GetNativeUnifiedData
 * @tc.type: FUNC
 */
HWTEST_F(NdkDataConversionTest, GetNativeUnifiedData_001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetNativeUnifiedData_001 begin.");
    auto unifiedRecord = std::make_shared<UnifiedRecord>();
    const std::string uid("typeId");
    unifiedRecord->SetUid(uid);
    OH_UdmfData *ndkData = OH_UdmfData_Create();
    ndkData->unifiedData_->AddRecord(unifiedRecord);
    auto data = std::make_shared<UnifiedData>();

    Status status = NdkDataConversion::GetNativeUnifiedData(ndkData, data);
    ASSERT_EQ(E_OK, status);
    EXPECT_EQ("typeId", data->GetRecordAt(0)->GetUid());

    OH_UdmfData *ndkDataNull = nullptr;
    status = NdkDataConversion::GetNativeUnifiedData(ndkDataNull, data);
    ASSERT_EQ(E_INVALID_PARAMETERS, status);

    std::shared_ptr<UnifiedData> dataNull;
    status = NdkDataConversion::GetNativeUnifiedData(ndkData, dataNull);
    OH_UdmfData_Destroy(ndkData);
    ASSERT_EQ(E_INVALID_PARAMETERS, status);
    LOG_INFO(UDMF_TEST, "GetNativeUnifiedData_001 end.");
}

/* *
 * @tc.name: GetNativeUnifiedData_002
 * @tc.desc: Normal testcase of GetNativeUnifiedData
 * @tc.type: FUNC
 */
HWTEST_F(NdkDataConversionTest, GetNativeUnifiedData_002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetNativeUnifiedData_002 begin.");
    auto plainText = OH_UdsPlainText_Create();
    OH_UdmfData *fakeNdkData = reinterpret_cast<OH_UdmfData *>(plainText);
    auto data = std::make_shared<UnifiedData>();
    Status status = NdkDataConversion::GetNativeUnifiedData(fakeNdkData, data);
    OH_UdsPlainText_Destroy(plainText);
    ASSERT_EQ(E_INVALID_PARAMETERS, status);
    LOG_INFO(UDMF_TEST, "GetNativeUnifiedData_002 end.");
}

/* *
 * @tc.name: GetNdkUnifiedData_001
 * @tc.desc: Error testcase of GetNdkUnifiedData
 * @tc.type: FUNC
 */
HWTEST_F(NdkDataConversionTest, GetNdkUnifiedData_001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetNdkUnifiedData_001 begin.");
    auto unifiedRecord = std::make_shared<UnifiedRecord>();
    const std::string uid("typeId");
    unifiedRecord->SetUid(uid);
    auto data = std::make_shared<UnifiedData>();
    data->AddRecord(unifiedRecord);
    OH_UdmfData *ndkData = OH_UdmfData_Create();
    Status status = NdkDataConversion::GetNdkUnifiedData(data, ndkData);
    ASSERT_EQ(E_OK, status);
    EXPECT_EQ("typeId", ndkData->unifiedData_->GetRecordAt(0)->GetUid());

    OH_UdmfData *ndkDataNull = nullptr;
    status = NdkDataConversion::GetNdkUnifiedData(data, ndkDataNull);
    ASSERT_EQ(E_INVALID_PARAMETERS, status);

    std::shared_ptr<UnifiedData> dataNull;
    status = NdkDataConversion::GetNdkUnifiedData(dataNull, ndkData);
    OH_UdmfData_Destroy(ndkData);
    ASSERT_EQ(E_INVALID_PARAMETERS, status);
    LOG_INFO(UDMF_TEST, "GetNdkUnifiedData_001 end.");
}

/* *
 * @tc.name: GetNdkUnifiedData_002
 * @tc.desc: Error testcase of GetNdkUnifiedData
 * @tc.type: FUNC
 */
HWTEST_F(NdkDataConversionTest, GetNdkUnifiedData_002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetNdkUnifiedData_002 begin.");
    auto plainText = OH_UdsPlainText_Create();
    OH_UdmfData *fakeNdkData = reinterpret_cast<OH_UdmfData *>(plainText);
    auto data = std::make_shared<UnifiedData>();
    Status status = NdkDataConversion::GetNdkUnifiedData(data, fakeNdkData);
    OH_UdsPlainText_Destroy(plainText);
    ASSERT_EQ(E_INVALID_PARAMETERS, status);
    LOG_INFO(UDMF_TEST, "GetNdkUnifiedData_002 end.");
}

/* *
 * @tc.name: ConvertPixelMap_001
 * @tc.desc: test pixel-map conversion between JS and C-API
 * @tc.type: FUNC
 */
HWTEST_F(NdkDataConversionTest, ConvertPixelMap_001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "ConvertPixelMap_001 begin.");
    uint32_t color[100] = { 3, 7, 9, 9, 7, 6 };
    OHOS::Media::InitializationOptions opts = { { 5, 7 },
        Media::PixelFormat::ARGB_8888,
        Media::PixelFormat::ARGB_8888 };
    std::unique_ptr<OHOS::Media::PixelMap> pixelMap =
        OHOS::Media::PixelMap::Create(color, sizeof(color) / sizeof(color[0]), opts);
    std::shared_ptr<OHOS::Media::PixelMap> pixelMapIn = move(pixelMap);

    auto pixelMapUds = OH_UdsPixelMap_Create();
    OH_PixelmapNative *ohPixelmapNative = new OH_PixelmapNative(pixelMapIn);
    OH_UdsPixelMap_SetPixelMap(pixelMapUds, ohPixelmapNative);
    auto record = OH_UdmfRecord_Create();
    OH_UdmfRecord_AddPixelMap(record, pixelMapUds);
    auto data = OH_UdmfData_Create();
    OH_UdmfData_AddRecord(data, record);
    std::shared_ptr<UnifiedData> unifiedData = std::make_shared<UnifiedData>();
    auto conversionStatus = NdkDataConversion::GetNativeUnifiedData(data, unifiedData);
    EXPECT_EQ(conversionStatus, E_OK);
    std::string key;
    CustomOption option = {
        .intention = UD_INTENTION_DRAG
    };
    auto setRet = UdmfClient::GetInstance().SetData(option, *unifiedData, key);
    EXPECT_EQ(setRet, E_OK);

    std::shared_ptr<UnifiedData> readData = std::make_shared<UnifiedData>();
    QueryOption query = {
        .key = key
    };
    auto getRet = UdmfClient::GetInstance().GetData(query, *readData);
    EXPECT_EQ(getRet, E_OK);

    auto readRecord = readData->GetRecordAt(0);
    auto systemDefinedPixelMap = std::static_pointer_cast<SystemDefinedPixelMap>(readRecord);
    auto rawData = systemDefinedPixelMap->GetRawData();
    EXPECT_GT(rawData.size(), 0);

    OH_UdsPixelMap_Destroy(pixelMapUds);
    OH_UdmfRecord_Destroy(record);
    OH_UdmfData_Destroy(data);
    delete ohPixelmapNative;
    LOG_INFO(UDMF_TEST, "ConvertPixelMap_001 end.");
}

/* *
 * @tc.name: ConvertPixelMap_002
 * @tc.desc: test pixel-map conversion between JS and C-API
 * @tc.type: FUNC
 */
HWTEST_F(NdkDataConversionTest, ConvertPixelMap_002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "ConvertPixelMap_002 begin.");
    uint32_t color[100] = { 3, 7, 9, 9, 7, 6 };
    OHOS::Media::InitializationOptions opts = { { 5, 7 },
        Media::PixelFormat::ARGB_8888, Media::PixelFormat::ARGB_8888 };
    std::unique_ptr<OHOS::Media::PixelMap> pixelMap =
        OHOS::Media::PixelMap::Create(color, sizeof(color) / sizeof(color[0]), opts);
    std::shared_ptr<OHOS::Media::PixelMap> pixelMapIn = move(pixelMap);

    std::shared_ptr<SystemDefinedPixelMap> systemDefinedPixelMap =
        std::make_shared<SystemDefinedPixelMap>(UDType::SYSTEM_DEFINED_PIXEL_MAP, pixelMapIn);
    UnifiedData data;
    std::vector<std::shared_ptr<UnifiedRecord>> records = { systemDefinedPixelMap };
    data.SetRecords(records);

    std::string key;
    CustomOption option = { .intention = UD_INTENTION_DRAG };
    auto setRet = UdmfClient::GetInstance().SetData(option, data, key);
    EXPECT_EQ(setRet, E_OK);

    std::shared_ptr<UnifiedData> readData = std::make_shared<UnifiedData>();
    QueryOption query = { .key = key };
    auto getRet = UdmfClient::GetInstance().GetData(query, *readData);
    EXPECT_EQ(getRet, E_OK);

    auto ndkData = OH_UdmfData_Create();
    NdkDataConversion::GetNdkUnifiedData(readData, ndkData);
    unsigned int count;
    OH_UdmfData_GetRecords(ndkData, &count);
    EXPECT_EQ(1, count);
    auto record = OH_UdmfData_GetRecord(ndkData, 0);
    auto pixelMapUds = OH_UdsPixelMap_Create();
    OH_UdmfRecord_GetPixelMap(record, pixelMapUds);
    auto type = OH_UdsPixelMap_GetType(pixelMapUds);
    EXPECT_EQ(std::string(type), std::string(UDMF_META_OPENHARMONY_PIXEL_MAP));

    OHOS::Media::InitializationOptions opts2 = { { 10, 10 },
        Media::PixelFormat::ARGB_8888, Media::PixelFormat::ARGB_8888 };
    std::unique_ptr<OHOS::Media::PixelMap> pixelMap2 =
        OHOS::Media::PixelMap::Create(color, sizeof(color) / sizeof(color[0]), opts2);

    OH_PixelmapNative *ohPixelmapNative = new OH_PixelmapNative(std::move(pixelMap2));
    OH_UdsPixelMap_GetPixelMap(pixelMapUds, ohPixelmapNative);
    auto resultPixelMap = ohPixelmapNative->GetInnerPixelmap();
    auto height = resultPixelMap->GetHeight();
    EXPECT_EQ(height, 7);

    OH_UdsPixelMap_Destroy(pixelMapUds);
    OH_UdmfData_Destroy(ndkData);
    delete ohPixelmapNative;
    LOG_INFO(UDMF_TEST, "ConvertPixelMap_002 end.");
}

/* *
 * @tc.name: ConvertPixelMap_003
 * @tc.desc: test pixel-map conversion between JS and C-API
 * @tc.type: FUNC
 */
HWTEST_F(NdkDataConversionTest, ConvertPixelMap_003, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "ConvertPixelMap_003 begin.");
    uint32_t color[35] = { 3, 7, 9, 9, 7, 6 };
    OHOS::Media::InitializationOptions opts = { { 5, 7 },
        Media::PixelFormat::ARGB_8888, Media::PixelFormat::ARGB_8888 };
    auto pixelMap = OHOS::Media::PixelMap::Create(color, sizeof(color) / sizeof(color[0]), opts);
    std::vector<uint8_t> buff;
    buff.resize(pixelMap->GetByteCount());
    auto status = pixelMap->ReadPixels(pixelMap->GetByteCount(), buff.data());
    ASSERT_EQ(status, E_OK);
    auto systemDefinedPixelMap = std::make_shared<SystemDefinedPixelMap>(UDType::SYSTEM_DEFINED_PIXEL_MAP, buff);
    UDDetails uDetails = {
        { "width", pixelMap->GetWidth() },
        { "height", pixelMap->GetHeight() },
        { "pixel-format", static_cast<int32_t>(pixelMap->GetPixelFormat()) },
        { "alpha-type", static_cast<int32_t>(pixelMap->GetAlphaType()) } };
    systemDefinedPixelMap->SetDetails(uDetails);
    UnifiedData data;
    data.AddRecord(systemDefinedPixelMap);

    std::string key;
    CustomOption option = { .intention = UD_INTENTION_DRAG };
    auto setRet = UdmfClient::GetInstance().SetData(option, data, key);
    EXPECT_EQ(setRet, E_OK);
    std::shared_ptr<UnifiedData> readData = std::make_shared<UnifiedData>();
    QueryOption query = { .key = key };
    auto getRet = UdmfClient::GetInstance().GetData(query, *readData);
    EXPECT_EQ(getRet, E_OK);

    auto ndkData = OH_UdmfData_Create();
    NdkDataConversion::GetNdkUnifiedData(readData, ndkData);
    unsigned int count;
    OH_UdmfData_GetRecords(ndkData, &count);
    EXPECT_EQ(1, count);
    auto record = OH_UdmfData_GetRecord(ndkData, 0);
    auto pixelMapUds = OH_UdsPixelMap_Create();
    OH_UdmfRecord_GetPixelMap(record, pixelMapUds);
    auto type = OH_UdsPixelMap_GetType(pixelMapUds);
    EXPECT_EQ(std::string(type), std::string(UDMF_META_OPENHARMONY_PIXEL_MAP));

    uint32_t color2[100] = { 3, 7, 9, 9, 7, 6 };
    OHOS::Media::InitializationOptions opts2 = { { 10, 10 },
        Media::PixelFormat::ARGB_8888, Media::PixelFormat::ARGB_8888 };
    auto pixelMap2 = OHOS::Media::PixelMap::Create(color2, sizeof(color) / sizeof(color[0]), opts2);
    OH_PixelmapNative *ohPixelmapNative = new OH_PixelmapNative(std::move(pixelMap2));
    OH_UdsPixelMap_GetPixelMap(pixelMapUds, ohPixelmapNative);
    auto resultPixelMap = ohPixelmapNative->GetInnerPixelmap();
    EXPECT_EQ(resultPixelMap->GetHeight(), 7);

    OH_UdsPixelMap_Destroy(pixelMapUds);
    OH_UdmfData_Destroy(ndkData);
    delete ohPixelmapNative;
    LOG_INFO(UDMF_TEST, "ConvertPixelMap_003 end.");
}

/* *
 * @tc.name: ConvertPixelMap_004
 * @tc.desc: test pixel-map conversion between UDS and C-API
 * @tc.type: FUNC
 */
HWTEST_F(NdkDataConversionTest, ConvertPixelMap_004, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "ConvertPixelMap_004 begin.");
    uint32_t color[35] = { 3, 7, 9, 9, 7, 6 };
    OHOS::Media::InitializationOptions opts = { { 5, 7 },
        Media::PixelFormat::ARGB_8888, Media::PixelFormat::ARGB_8888 };
    std::unique_ptr<OHOS::Media::PixelMap> pixelMap =
        OHOS::Media::PixelMap::Create(color, sizeof(color) / sizeof(color[0]), opts);
    std::shared_ptr<OHOS::Media::PixelMap> pixelMapIn = move(pixelMap);

    auto pixelMapUds = OH_UdsPixelMap_Create();
    OH_PixelmapNative *ohPixelmapNative = new OH_PixelmapNative(pixelMapIn);
    OH_UdsPixelMap_SetPixelMap(pixelMapUds, ohPixelmapNative);
    auto record = OH_UdmfRecord_Create();
    OH_UdmfRecord_AddPixelMap(record, pixelMapUds);
    auto data = OH_UdmfData_Create();
    OH_UdmfData_AddRecord(data, record);
    std::shared_ptr<UnifiedData> unifiedData = std::make_shared<UnifiedData>();
    auto conversionStatus = NdkDataConversion::GetNativeUnifiedData(data, unifiedData);
    EXPECT_EQ(conversionStatus, E_OK);
    std::string key;
    CustomOption option = {.intention = UD_INTENTION_DRAG};
    auto setRet = UdmfClient::GetInstance().SetData(option, *unifiedData, key);
    EXPECT_EQ(setRet, E_OK);
    std::shared_ptr<UnifiedData> readData = std::make_shared<UnifiedData>();
    QueryOption query = {.key = key};
    auto getRet = UdmfClient::GetInstance().GetData(query, *readData);
    EXPECT_EQ(getRet, E_OK);

    auto readRecord = readData->GetRecordAt(0);
    auto value = readRecord->GetEntry(UDMF_META_OPENHARMONY_PIXEL_MAP);
    ASSERT_TRUE(std::holds_alternative<std::shared_ptr<Object>>(value));
    auto obj = std::get<std::shared_ptr<Object>>(value);
    std::shared_ptr<Media::PixelMap> getPixelMap = nullptr;
    ASSERT_TRUE(obj->GetValue(PIXEL_MAP, getPixelMap));
    ASSERT_NE(getPixelMap, nullptr);
    ASSERT_EQ(getPixelMap->GetHeight(), pixelMapIn->GetHeight());
    ASSERT_EQ(getPixelMap->GetByteCount(), pixelMapIn->GetByteCount());
    OH_UdsPixelMap_Destroy(pixelMapUds);
    OH_UdmfRecord_Destroy(record);
    OH_UdmfData_Destroy(data);
    delete ohPixelmapNative;
    LOG_INFO(UDMF_TEST, "ConvertPixelMap_004 end.");
}

/* *
 * @tc.name: ConvertApplicationDefined_001
 * @tc.desc: test application defined record conversion between JS and C-API
 * @tc.type: FUNC
 */
HWTEST_F(NdkDataConversionTest, ConvertApplicationDefined_001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "ConvertApplicationDefined_001 begin.");
    std::vector<uint8_t> dataBytes = { '1', '2', '3', '4', '5', '6' };
    std::string definedTypeId = "person_app_demo";
    std::shared_ptr<ApplicationDefinedRecord> systemDefinedPixelMap =
        std::make_shared<ApplicationDefinedRecord>(definedTypeId, dataBytes);
    UnifiedData data;
    std::vector<std::shared_ptr<UnifiedRecord>> records = { systemDefinedPixelMap };
    data.SetRecords(records);

    std::string key;
    CustomOption option = {
        .intention = UD_INTENTION_DRAG
    };
    auto setRet = UdmfClient::GetInstance().SetData(option, data, key);
    EXPECT_EQ(setRet, E_OK);

    std::shared_ptr<UnifiedData> readData = std::make_shared<UnifiedData>();
    QueryOption query = {
        .key = key
    };
    auto getRet = UdmfClient::GetInstance().GetData(query, *readData);
    EXPECT_EQ(getRet, E_OK);

    auto ndkData = OH_UdmfData_Create();
    NdkDataConversion::GetNdkUnifiedData(readData, ndkData);
    unsigned int count;
    OH_UdmfData_GetRecords(ndkData, &count);
    EXPECT_EQ(1, count);
    auto record = OH_UdmfData_GetRecord(ndkData, 0);
    unsigned int getCount = 0;
    unsigned char *getEntry;
    auto result = OH_UdmfRecord_GetGeneralEntry(record, definedTypeId.c_str(), &getEntry, &getCount);
    EXPECT_EQ(0, result);
    EXPECT_EQ(6, getCount);
    dataBytes = { '1', '2', '3', '4', '5', '6' };
    EXPECT_EQ(std::string(dataBytes.begin(), dataBytes.end()), std::string(reinterpret_cast<const char *>(getEntry)));

    OH_UdmfData_Destroy(ndkData);
    LOG_INFO(UDMF_TEST, "ConvertApplicationDefined_001 end.");
}

/* *
 * @tc.name: ConvertApplicationDefined_002
 * @tc.desc: test application defined record conversion between JS and C-API
 * @tc.type: FUNC
 */
HWTEST_F(NdkDataConversionTest, ConvertApplicationDefined_002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "ConvertApplicationDefined_002 begin.");
    std::vector<uint8_t> dataBytes = { '1', '2', '3', '4', '5', '6' };
    std::string definedTypeId = "person_app_demo";
    std::shared_ptr<ApplicationDefinedRecord> systemDefinedPixelMap =
        std::make_shared<ApplicationDefinedRecord>(definedTypeId, dataBytes);
    UnifiedData data;
    std::vector<std::shared_ptr<UnifiedRecord>> records = { systemDefinedPixelMap };
    data.SetRecords(records);

    std::string key;
    CustomOption option = {
        .intention = UD_INTENTION_DRAG
    };
    auto setRet = UdmfClient::GetInstance().SetData(option, data, key);
    EXPECT_EQ(setRet, E_OK);

    std::shared_ptr<UnifiedData> readData = std::make_shared<UnifiedData>();
    QueryOption query = {
        .key = key
    };
    auto getRet = UdmfClient::GetInstance().GetData(query, *readData);
    EXPECT_EQ(getRet, E_OK);

    auto ndkData = OH_UdmfData_Create();
    NdkDataConversion::GetNdkUnifiedData(readData, ndkData);
    unsigned int count;
    OH_UdmfData_GetRecords(ndkData, &count);
    EXPECT_EQ(1, count);
    auto record = OH_UdmfData_GetRecord(ndkData, 0);
    auto arrayBuffer = OH_UdsArrayBuffer_Create();
    auto result = OH_UdmfRecord_GetArrayBuffer(record, definedTypeId.c_str(), arrayBuffer);
    EXPECT_EQ(0, result);
    unsigned int getCount = 0;
    unsigned char *getEntry;
    OH_UdsArrayBuffer_GetData(arrayBuffer, &getEntry, &getCount);
    EXPECT_EQ(6, getCount);
    dataBytes = { '1', '2', '3', '4', '5', '6' };
    EXPECT_EQ(std::string(dataBytes.begin(), dataBytes.end()), std::string(reinterpret_cast<const char *>(getEntry)));

    OH_UdsArrayBuffer_Destroy(arrayBuffer);
    OH_UdmfData_Destroy(ndkData);
    LOG_INFO(UDMF_TEST, "ConvertApplicationDefined_002 end.");
}

/* *
 * @tc.name: ConvertApplicationDefined_003
 * @tc.desc: test application defined record conversion between JS and C-API
 * @tc.type: FUNC
 */
HWTEST_F(NdkDataConversionTest, ConvertApplicationDefined_003, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "ConvertApplicationDefined_003 begin.");
    auto arrayBuffer = OH_UdsArrayBuffer_Create();
    unsigned char data[] = {'1', '2', '3', '4', '5', '6'};
    OH_UdsArrayBuffer_SetData(arrayBuffer, data, 6);
    auto record = OH_UdmfRecord_Create();
    OH_UdmfRecord_AddArrayBuffer(record, "person_demo", arrayBuffer);
    auto ndkData = OH_UdmfData_Create();
    OH_UdmfData_AddRecord(ndkData, record);
    std::shared_ptr<UnifiedData> unifiedData = std::make_shared<UnifiedData>();
    auto conversionStatus = NdkDataConversion::GetNativeUnifiedData(ndkData, unifiedData);
    EXPECT_EQ(conversionStatus, E_OK);
    std::string key;
    CustomOption option = {
        .intention = UD_INTENTION_DRAG
    };
    auto setRet = UdmfClient::GetInstance().SetData(option, *unifiedData, key);
    EXPECT_EQ(setRet, E_OK);

    std::shared_ptr<UnifiedData> readData = std::make_shared<UnifiedData>();
    QueryOption query = {
        .key = key
    };
    auto getRet = UdmfClient::GetInstance().GetData(query, *readData);
    EXPECT_EQ(getRet, E_OK);

    auto readRecord = readData->GetRecordAt(0);
    auto definedRecord = std::static_pointer_cast<ApplicationDefinedRecord>(readRecord);
    auto type = definedRecord->GetApplicationDefinedType();
    EXPECT_EQ("person_demo", type);
    auto rawData = definedRecord->GetRawData();
    std::vector<uint8_t> dataBytes = { '1', '2', '3', '4', '5', '6' };
    EXPECT_EQ(std::string(dataBytes.begin(), dataBytes.end()), std::string(rawData.begin(), rawData.end()));

    OH_UdsArrayBuffer_Destroy(arrayBuffer);
    OH_UdmfRecord_Destroy(record);
    OH_UdmfData_Destroy(ndkData);
    LOG_INFO(UDMF_TEST, "ConvertApplicationDefined_003 end.");
}

/* *
 * @tc.name: ConvertApplicationDefined_004
 * @tc.desc: test application defined record conversion between JS and C-API
 * @tc.type: FUNC
 */
HWTEST_F(NdkDataConversionTest, ConvertApplicationDefined_004, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "ConvertApplicationDefined_004 begin.");
    unsigned char data[] = {'1', '2', '3', '4', '5', '6'};
    auto record = OH_UdmfRecord_Create();
    OH_UdmfRecord_AddGeneralEntry(record, "person_demo", data, 6);
    auto ndkData = OH_UdmfData_Create();
    OH_UdmfData_AddRecord(ndkData, record);
    std::shared_ptr<UnifiedData> unifiedData = std::make_shared<UnifiedData>();
    auto conversionStatus = NdkDataConversion::GetNativeUnifiedData(ndkData, unifiedData);
    EXPECT_EQ(conversionStatus, E_OK);
    std::string key;
    CustomOption option = {
        .intention = UD_INTENTION_DRAG
    };
    auto setRet = UdmfClient::GetInstance().SetData(option, *unifiedData, key);
    EXPECT_EQ(setRet, E_OK);

    std::shared_ptr<UnifiedData> readData = std::make_shared<UnifiedData>();
    QueryOption query = {
        .key = key
    };
    auto getRet = UdmfClient::GetInstance().GetData(query, *readData);
    EXPECT_EQ(getRet, E_OK);

    auto readRecord = readData->GetRecordAt(0);
    auto definedRecord = std::static_pointer_cast<ApplicationDefinedRecord>(readRecord);
    auto type = definedRecord->GetApplicationDefinedType();
    EXPECT_EQ("person_demo", type);
    auto rawData = definedRecord->GetRawData();
    std::vector<uint8_t> dataBytes = { '1', '2', '3', '4', '5', '6' };
    EXPECT_EQ(std::string(dataBytes.begin(), dataBytes.end()), std::string(rawData.begin(), rawData.end()));

    OH_UdmfRecord_Destroy(record);
    OH_UdmfData_Destroy(ndkData);
    LOG_INFO(UDMF_TEST, "ConvertApplicationDefined_004 end.");
}

/* *
 * @tc.name: ConvertOhtherUds_001
 * @tc.desc: test other conversion between JS and C-API
 * @tc.type: FUNC
 */
HWTEST_F(NdkDataConversionTest, ConvertOhtherUds_001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "ConvertOhtherUds_001 begin.");
    std::string definedTypeId = "person_app_demo";
    std::shared_ptr<Html> html = std::make_shared<Html>("htmlContent", "plainContent");
    std::map<std::string, ValueType> value;
    std::vector<uint8_t> thumbData = {1, 2, 3, 4, 5};
    auto obj = std::make_shared<Object>();
    obj->value_.emplace(UNIFORM_DATA_TYPE, "general.content-form");
    obj->value_.emplace(TITLE, "title");
    obj->value_.emplace(THUMB_DATA, thumbData);
    std::shared_ptr<UnifiedRecord> contentForm = std::make_shared<UnifiedRecord>(UDType::CONTENT_FORM, obj);
    UnifiedData data;
    std::vector<std::shared_ptr<UnifiedRecord>> records = { html, contentForm };
    data.SetRecords(records);

    std::string key;
    CustomOption option = { .intention = UD_INTENTION_DRAG };
    auto setRet = UdmfClient::GetInstance().SetData(option, data, key);
    EXPECT_EQ(setRet, E_OK);

    std::shared_ptr<UnifiedData> readData = std::make_shared<UnifiedData>();
    QueryOption query = { .key = key };
    auto getRet = UdmfClient::GetInstance().GetData(query, *readData);
    EXPECT_EQ(getRet, E_OK);

    auto ndkData = OH_UdmfData_Create();
    NdkDataConversion::GetNdkUnifiedData(readData, ndkData);
    unsigned int count;
    OH_UdmfData_GetRecords(ndkData, &count);
    EXPECT_EQ(2, count);
    auto record = OH_UdmfData_GetRecord(ndkData, 0);
    auto htmlNdk = OH_UdsHtml_Create();
    auto result = OH_UdmfRecord_GetHtml(record, htmlNdk);
    EXPECT_EQ(0, result);
    EXPECT_EQ("general.html", std::string(OH_UdsHtml_GetType(htmlNdk)));
    EXPECT_EQ("htmlContent", std::string(OH_UdsHtml_GetContent(htmlNdk)));
    EXPECT_EQ("plainContent", std::string(OH_UdsHtml_GetPlainContent(htmlNdk)));

    auto contentFormRecord = OH_UdmfData_GetRecord(ndkData, 1);
    auto contentFormNdk = OH_UdsContentForm_Create();
    result = OH_UdmfRecord_GetContentForm(contentFormRecord, contentFormNdk);
    EXPECT_EQ(0, result);
    EXPECT_EQ("general.content-form", std::string(OH_UdsContentForm_GetType(contentFormNdk)));
    EXPECT_EQ("title", std::string(OH_UdsContentForm_GetTitle(contentFormNdk)));
    unsigned char *readThumbData;
    unsigned int thumbDataLen = 0;
    EXPECT_EQ(0, OH_UdsContentForm_GetThumbData(contentFormNdk, &readThumbData, &thumbDataLen));
    EXPECT_EQ(5, thumbDataLen);
    OH_UdsHtml_Destroy(htmlNdk);
    OH_UdsContentForm_Destroy(contentFormNdk);
    OH_UdmfData_Destroy(ndkData);
    LOG_INFO(UDMF_TEST, "ConvertOhtherUds_001 end.");
}

/* *
 * @tc.name: ConvertOhtherUds_002
 * @tc.desc: test html conversion between JS and C-API
 * @tc.type: FUNC
 */
HWTEST_F(NdkDataConversionTest, ConvertOhtherUds_002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "ConvertOhtherUds_002 begin.");
    auto htmlNdk = OH_UdsHtml_Create();
    OH_UdsHtml_SetContent(htmlNdk, "htmlContent");
    OH_UdsHtml_SetPlainContent(htmlNdk, "plainContent");
    auto record = OH_UdmfRecord_Create();
    OH_UdmfRecord_AddHtml(record, htmlNdk);
    auto ndkData = OH_UdmfData_Create();
    OH_UdmfData_AddRecord(ndkData, record);
    auto record2 = OH_UdmfRecord_Create();
    auto contentFormNdk = OH_UdsContentForm_Create();
    OH_UdsContentForm_SetTitle(contentFormNdk, "title");
    unsigned char thumbData[] = {0, 1, 2, 3, 4};
    OH_UdsContentForm_SetThumbData(contentFormNdk, thumbData, 5);
    OH_UdmfRecord_AddContentForm(record2, contentFormNdk);
    OH_UdmfData_AddRecord(ndkData, record2);

    std::shared_ptr<UnifiedData> unifiedData = std::make_shared<UnifiedData>();
    auto conversionStatus = NdkDataConversion::GetNativeUnifiedData(ndkData, unifiedData);
    EXPECT_EQ(conversionStatus, E_OK);
    std::string key;
    CustomOption option = { .intention = UD_INTENTION_DRAG };
    auto setRet = UdmfClient::GetInstance().SetData(option, *unifiedData, key);
    EXPECT_EQ(setRet, E_OK);

    std::shared_ptr<UnifiedData> readData = std::make_shared<UnifiedData>();
    QueryOption query = { .key = key };
    auto getRet = UdmfClient::GetInstance().GetData(query, *readData);
    EXPECT_EQ(getRet, E_OK);

    auto readRecord = readData->GetRecordAt(0);
    auto html = std::static_pointer_cast<Html>(readRecord);
    EXPECT_EQ("htmlContent", html->GetHtmlContent());
    EXPECT_EQ("plainContent", html->GetPlainContent());

    auto contentForm = readData->GetRecordAt(1);
    auto value = contentForm->GetValue();
    auto obj = std::get<std::shared_ptr<Object>>(value);
    EXPECT_EQ("general.content-form", std::get<std::string>(obj->value_[UNIFORM_DATA_TYPE]));
    EXPECT_EQ(5, std::get<int>(obj->value_[THUMB_DATA_LENGTH]));
    auto readThumbData = std::get<std::vector<uint8_t>>(obj->value_[THUMB_DATA]);
    EXPECT_EQ(4, readThumbData.at(4));

    OH_UdsHtml_Destroy(htmlNdk);
    OH_UdsContentForm_Destroy(contentFormNdk);
    OH_UdmfRecord_Destroy(record);
    OH_UdmfRecord_Destroy(record2);
    OH_UdmfData_Destroy(ndkData);
    LOG_INFO(UDMF_TEST, "ConvertOhtherUds_002 end.");
}
}
