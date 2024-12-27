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
#include "error_code.h"
#include "udmf.h"
#include "udmf_capi_common.h"
#include "uds.h"

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
    uint32_t color[100] = { 3, 7, 9, 9, 7, 6 };
    OHOS::Media::InitializationOptions opts = { { 5, 7 },
        Media::PixelFormat::ARGB_8888, Media::PixelFormat::ARGB_8888 };
    std::unique_ptr<OHOS::Media::PixelMap> pixelMap =
        OHOS::Media::PixelMap::Create(color, sizeof(color) / sizeof(color[0]), opts);
    std::shared_ptr<OHOS::Media::PixelMap> pixelMapIn = move(pixelMap);
    std::vector<uint8_t> buff;
    pixelMapIn->EncodeTlv(buff);

    std::shared_ptr<SystemDefinedPixelMap> systemDefinedPixelMap =
        std::make_shared<SystemDefinedPixelMap>(UDType::SYSTEM_DEFINED_PIXEL_MAP, buff);
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
    LOG_INFO(UDMF_TEST, "ConvertPixelMap_003 end.");
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

    void NdkDataConversionTest::SetUpTestCase(void) {}

    void NdkDataConversionTest::TearDownTestCase(void) {}

    void NdkDataConversionTest::SetUp(void) {}

    void NdkDataConversionTest::TearDown(void) {}

    /**
     * @tc.name: GetNativeUnifiedData_001
     * @tc.desc: Normal testcase of GetNativeUnifiedData
     * @tc.type: FUNC
     */
    HWTEST_F(NdkDataConversionTest, GetNativeUnifiedData_001, TestSize.Level1) {
        LOG_INFO(UDMF_TEST, "GetNativeUnifiedData_001 begin.");
        UnifiedRecord unifiedRecord;
        const std::string uid("typeId");
        unifiedRecord.SetUid(uid);
        OH_UdmfData* ndkData = OH_UdmfData_Create();
        const std::shared_ptr<UnifiedRecord> recordPtr = std::make_shared<UnifiedRecord>(unifiedRecord);
        ndkData->unifiedData_->AddRecord(recordPtr);
        auto data = std::make_shared<UnifiedData>();

        Status status = NdkDataConversion::GetNativeUnifiedData(ndkData, data);
        ASSERT_EQ(E_OK, status);
        EXPECT_EQ("typeId", data->GetRecordAt(0)->GetUid());

        OH_UdmfData* ndkDataNull = nullptr;
        status = NdkDataConversion::GetNativeUnifiedData(ndkDataNull, data);
        ASSERT_EQ(E_INVALID_PARAMETERS, status);

        std::shared_ptr<UnifiedData> dataNull;
        status = NdkDataConversion::GetNativeUnifiedData(ndkData, dataNull);
        OH_UdmfData_Destroy(ndkData);
        ASSERT_EQ(E_INVALID_PARAMETERS, status);
        LOG_INFO(UDMF_TEST, "GetNativeUnifiedData_001 end.");
    }

    /**
     * @tc.name: GetNativeUnifiedData_002
     * @tc.desc: Normal testcase of GetNativeUnifiedData
     * @tc.type: FUNC
     */
    HWTEST_F(NdkDataConversionTest, GetNativeUnifiedData_002, TestSize.Level1) {
        LOG_INFO(UDMF_TEST, "GetNativeUnifiedData_002 begin.");
        auto plainText = OH_UdsPlainText_Create();
        OH_UdmfData* fakeNdkData = reinterpret_cast<OH_UdmfData*>(plainText);
        auto data = std::make_shared<UnifiedData>();
        Status status = NdkDataConversion::GetNativeUnifiedData(fakeNdkData, data);
        OH_UdsPlainText_Destroy(plainText);
        ASSERT_EQ(E_INVALID_PARAMETERS, status);
        LOG_INFO(UDMF_TEST, "GetNativeUnifiedData_002 end.");
    }

    /**
     * @tc.name: GetNdkUnifiedData_001
     * @tc.desc: Error testcase of GetNdkUnifiedData
     * @tc.type: FUNC
     */
    HWTEST_F(NdkDataConversionTest, GetNdkUnifiedData_001, TestSize.Level1) {
        LOG_INFO(UDMF_TEST, "GetNdkUnifiedData_001 begin.");
        UnifiedRecord unifiedRecord;
        const std::string uid("typeId");
        unifiedRecord.SetUid(uid);
        const std::shared_ptr<UnifiedRecord> recordPtr = std::make_shared<UnifiedRecord>(unifiedRecord);
        auto data= std::make_shared<UnifiedData>();
        data->AddRecord(recordPtr);
        OH_UdmfData* ndkData = OH_UdmfData_Create();
        Status status = NdkDataConversion::GetNdkUnifiedData(data, ndkData);
        ASSERT_EQ(E_OK, status);
        EXPECT_EQ("typeId", ndkData->unifiedData_->GetRecordAt(0)->GetUid());

        OH_UdmfData* ndkDataNull = nullptr;
        status = NdkDataConversion::GetNdkUnifiedData(data, ndkDataNull);
        ASSERT_EQ(E_INVALID_PARAMETERS, status);

        std::shared_ptr<UnifiedData> dataNull;
        status = NdkDataConversion::GetNdkUnifiedData(dataNull, ndkData);
        OH_UdmfData_Destroy(ndkData);
        ASSERT_EQ(E_INVALID_PARAMETERS, status);
        LOG_INFO(UDMF_TEST, "GetNdkUnifiedData_001 end.");
    }

    /**
     * @tc.name: GetNdkUnifiedData_002
     * @tc.desc: Error testcase of GetNdkUnifiedData
     * @tc.type: FUNC
     */
    HWTEST_F(NdkDataConversionTest, GetNdkUnifiedData_002, TestSize.Level1) {
        LOG_INFO(UDMF_TEST, "GetNdkUnifiedData_002 begin.");
        auto plainText = OH_UdsPlainText_Create();
        OH_UdmfData* fakeNdkData = reinterpret_cast<OH_UdmfData*>(plainText);
        auto data = std::make_shared<UnifiedData>();
        Status status = NdkDataConversion::GetNdkUnifiedData(data, fakeNdkData);
        OH_UdsPlainText_Destroy(plainText);
        ASSERT_EQ(E_INVALID_PARAMETERS, status);
        LOG_INFO(UDMF_TEST, "GetNdkUnifiedData_002 end.");
    }
}