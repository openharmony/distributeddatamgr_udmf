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

#define LOG_TAG "UDMFTEST"
#include <gtest/gtest.h>
#include "token_setproc.h"
#include "accesstoken_kit.h"
#include "directory_ex.h"
#include "nativetoken_kit.h"
#include <unistd.h>
#include <memory>
#include "udmf.h"
#include "uds.h"
#include "udmf_err_code.h"
#include "unified_data.h"
#include "unified_record.h"
#include "udmf_capi_common.h"
#include "udmf_client.h"
#include "plain_text.h"
#include "udmf_meta.h"
#include "data_provider_impl.h"
#include "image.h"
#include "audio.h"
#include "file.h"
#include "folder.h"
#include "video.h"
#include "logger.h"

using namespace testing::ext;
using namespace OHOS::Security::AccessToken;
using namespace OHOS::UDMF;

namespace OHOS::Test {
class UDMFTest : public testing::Test {
public:
    static void SetUpTestCase(void);
    static void TearDownTestCase(void);
    void SetUp();
    void TearDown();
    static void AllocHapToken1();
    static void AllocHapToken2();
    void SetHapToken1();
    bool CheckUnsignedChar(unsigned char* dst, unsigned char* src, int size);
    static void FinalizeFunc(void* context);
    static void* GetDataCallbackFunc(void* context, const char* type);
    static constexpr int USER_ID = 100;
    static constexpr int INST_INDEX = 0;
};

void UDMFTest::SetUpTestCase()
{
    AllocHapToken1();
    AllocHapToken2();
}

void UDMFTest::TearDownTestCase()
{
    auto tokenId = AccessTokenKit::GetHapTokenID(USER_ID, "ohos.test.demo1", INST_INDEX);
    AccessTokenKit::DeleteToken(tokenId);
    tokenId = AccessTokenKit::GetHapTokenID(USER_ID, "ohos.test.demo2", INST_INDEX);
    AccessTokenKit::DeleteToken(tokenId);
}

void UDMFTest::SetUp()
{
    SetHapToken1();
}

void UDMFTest::TearDown()
{
}

void UDMFTest::AllocHapToken1()
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

void UDMFTest::AllocHapToken2()
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

void UDMFTest::SetHapToken1()
{
    auto tokenId = AccessTokenKit::GetHapTokenID(USER_ID, "ohos.test.demo1", INST_INDEX);
    SetSelfTokenID(tokenId);
}

bool UDMFTest::CheckUnsignedChar(unsigned char* dst, unsigned char* src, int size)
{
    EXPECT_NE(dst, nullptr);
    EXPECT_NE(src, nullptr);
    for (int i = 0; i < size; ++i) {
        if (dst[i] != src[i]) {
            return false;
        }
    }
    return true;
}

void UDMFTest::FinalizeFunc(void* context) {}

void* UDMFTest::GetDataCallbackFunc(void* context, const char* type)
{
    auto plainText = OH_UdsPlainText_Create();
    OH_UdsPlainText_SetAbstract(plainText, "doing something");
    OH_UdsPlainText_SetContent(plainText, "doing something");
    return plainText;
}

/**
 * @tc.name: OH_Udmf_CreateUnifiedData001
 * @tc.desc: test OH_UdmfData_Create
 * @tc.type: FUNC
 * @tc.require: AROOOH5R5G
 */
HWTEST_F(UDMFTest, OH_Udmf_CreateUnifiedData001, TestSize.Level0)
{
    OH_UdmfData *unifiedData = OH_UdmfData_Create();
    EXPECT_NE(unifiedData, nullptr);
    EXPECT_NE(unifiedData->unifiedData_, nullptr);
    OH_UdmfData_Destroy(unifiedData);
}

/**
 * @tc.name: OH_Udmf_AddRecordToUnifiedData001
 * @tc.desc: OH_UdmfData_AddRecord with return UDMF_E_INVALID_PARAM
 * @tc.type: FUNC
 * @tc.require: AROOOH5R5G
 */
HWTEST_F(UDMFTest, OH_Udmf_AddRecordToUnifiedData001, TestSize.Level0)
{
    OH_UdmfRecord *record = OH_UdmfRecord_Create();
    OH_UdmfData *unifiedData = OH_UdmfData_Create();

    int invalidRes1 = OH_UdmfData_AddRecord(nullptr, record);
    EXPECT_EQ(invalidRes1, UDMF_E_INVALID_PARAM);

    OH_UdmfData unifiedData1;
    int invalidRes2 = OH_UdmfData_AddRecord(&unifiedData1, record);
    EXPECT_EQ(invalidRes2, UDMF_E_INVALID_PARAM);

    int invalidRes3 = OH_UdmfData_AddRecord(unifiedData, nullptr);
    EXPECT_EQ(invalidRes3, UDMF_E_INVALID_PARAM);

    OH_UdmfRecord unifiedRecord1;
    int invalidRes4 = OH_UdmfData_AddRecord(unifiedData, nullptr);
    EXPECT_EQ(invalidRes4, UDMF_E_INVALID_PARAM);
    OH_UdmfRecord_Destroy(record);
    OH_UdmfData_Destroy(unifiedData);
}

/**
 * @tc.name: OH_Udmf_AddRecordToUnifiedData002
 * @tc.desc: OH_UdmfData_AddRecord with return UDMF_E_OK
 * @tc.type: FUNC
 * @tc.require: AROOOH5R5G
 */
HWTEST_F(UDMFTest, OH_Udmf_AddRecordToUnifiedData002, TestSize.Level0)
{
    OH_UdmfRecord *record = OH_UdmfRecord_Create();
    OH_UdmfData *unifiedData = OH_UdmfData_Create();
    int status = OH_UdmfData_AddRecord(unifiedData, record);
    EXPECT_EQ(status, UDMF_E_OK);

    OH_UdmfRecord_Destroy(record);
    OH_UdmfData_Destroy(unifiedData);
}

/**
 * @tc.name: OH_Udmf_HasUnifiedDataType001
 * @tc.desc: OH_UdmfData_HasType with return UDMF_E_INVALID_PARAM
 * @tc.type: FUNC
 * @tc.require: AROOOH5R5G
 */
HWTEST_F(UDMFTest, OH_Udmf_HasUnifiedDataType001, TestSize.Level0)
{
    OH_UdmfData *unifiedData = OH_UdmfData_Create();
    char type[] = "general.plain-text";

    bool status1 = OH_UdmfData_HasType(nullptr, type);
    EXPECT_FALSE(status1);

    bool status2 = OH_UdmfData_HasType(unifiedData, nullptr);
    EXPECT_FALSE(status2);

    OH_UdmfData unifiedData1;
    bool status3 = OH_UdmfData_HasType(&unifiedData1, nullptr);
    EXPECT_FALSE(status3);

    bool status4 = OH_UdmfData_HasType(nullptr, nullptr);
    EXPECT_FALSE(status4);

    OH_UdmfData_Destroy(unifiedData);
}

/**
 * @tc.name: OH_Udmf_HasUnifiedDataType002
 * @tc.desc: OH_UdmfData_HasType with return whether has type, number 1 represent true, number 0 represent false
 * @tc.type: FUNC
 * @tc.require: AROOOH5R5G
 */
HWTEST_F(UDMFTest, OH_Udmf_HasUnifiedDataType002, TestSize.Level0)
{
    OH_UdmfData *unifiedData = OH_UdmfData_Create();
    OH_UdmfRecord *record = OH_UdmfRecord_Create();
    OH_UdsPlainText *plainText = OH_UdsPlainText_Create();
    OH_UdmfRecord_AddPlainText(record, plainText);
    OH_UdmfData_AddRecord(unifiedData, record);

    char type1[] = "general.plain-text";
    int hasType1 = OH_UdmfData_HasType(unifiedData, type1);
    EXPECT_EQ(hasType1, 1);

    char type2[] = "general.html";
    int hasType2 = OH_UdmfData_HasType(unifiedData, type2);
    EXPECT_EQ(hasType2, 0);

    OH_UdsPlainText_Destroy(plainText);
    OH_UdmfRecord_Destroy(record);
    OH_UdmfData_Destroy(unifiedData);
}

/**
 * @tc.name: OH_Udmf_GetUnifiedDataTypes001
 * @tc.desc: OH_UdmfData_GetTypes with invalid params
 * @tc.type: FUNC
 * @tc.require: AROOOH5R5G
 */
HWTEST_F(UDMFTest, OH_Udmf_GetUnifiedDataTypes001, TestSize.Level0)
{
    OH_UdmfData *unifiedData = OH_UdmfData_Create();

    unsigned int count1 = 0;
    char **types1 = OH_UdmfData_GetTypes(nullptr, &count1);
    EXPECT_EQ(types1, nullptr);

    OH_UdmfData data;
    char **types2 = OH_UdmfData_GetTypes(&data, &count1);
    EXPECT_EQ(types2, nullptr);

    char **types3 = OH_UdmfData_GetTypes(unifiedData, nullptr);
    EXPECT_EQ(types3, nullptr);

    OH_UdmfData_Destroy(unifiedData);
}

/**
 * @tc.name: OH_Udmf_GetUnifiedDataTypes002
 * @tc.desc: OH_UdmfData_GetTypes with valid params
 * @tc.type: FUNC
 * @tc.require: AROOOH5R5G
 */
HWTEST_F(UDMFTest, OH_Udmf_GetUnifiedDataTypes002, TestSize.Level0)
{
    OH_UdmfData *unifiedData = OH_UdmfData_Create();
    OH_UdmfRecord *record = OH_UdmfRecord_Create();
    OH_UdsPlainText *plainText = OH_UdsPlainText_Create();
    OH_UdmfRecord_AddPlainText(record, plainText);
    OH_UdmfData_AddRecord(unifiedData, record);
    OH_UdmfRecord *record1 = OH_UdmfRecord_Create();
    OH_UdsHyperlink *hyperlink = OH_UdsHyperlink_Create();
    OH_UdmfRecord_AddHyperlink(record1, hyperlink);
    OH_UdmfData_AddRecord(unifiedData, record1);

    unsigned int count1 = 0;
    char **types1 = OH_UdmfData_GetTypes(unifiedData, &count1);
    EXPECT_NE(types1, nullptr);
    EXPECT_EQ(count1, 2);

    char **types2 = OH_UdmfData_GetTypes(unifiedData, &count1);
    EXPECT_EQ(types1, types2);

    OH_UdsPlainText_Destroy(plainText);
    OH_UdsHyperlink_Destroy(hyperlink);
    OH_UdmfRecord_Destroy(record);
    OH_UdmfData_Destroy(unifiedData);
}

/**
 * @tc.name: OH_Udmf_GetUnifiedRecordTypes001
 * @tc.desc: OH_UdmfRecord_GetTypes with invalid params
 * @tc.type: FUNC
 * @tc.require: AROOOH5R5G
 */
HWTEST_F(UDMFTest, OH_Udmf_GetUnifiedRecordTypes001, TestSize.Level0)
{
    OH_UdmfRecord *record = OH_UdmfRecord_Create();
    unsigned int count = 0;
    char **types1 = OH_UdmfRecord_GetTypes(nullptr, &count);
    EXPECT_EQ(types1, nullptr);

    char **types2 = OH_UdmfRecord_GetTypes(record, nullptr);
    EXPECT_EQ(types2, nullptr);

    OH_UdmfRecord recordCp;
    char **types3 = OH_UdmfRecord_GetTypes(&recordCp, nullptr);
    EXPECT_EQ(types3, nullptr);

    OH_UdmfRecord_Destroy(record);
}

/**
 * @tc.name: OH_Udmf_GetUnifiedRecordTypes002
 * @tc.desc: OH_UdmfRecord_GetTypes with valid params
 * @tc.type: FUNC
 * @tc.require: AROOOH5R5G
 */
HWTEST_F(UDMFTest, OH_Udmf_GetUnifiedRecordTypes002, TestSize.Level0)
{
    OH_UdmfRecord *record = OH_UdmfRecord_Create();
    OH_UdsPlainText *plaintext = OH_UdsPlainText_Create();
    OH_UdmfRecord_AddPlainText(record, plaintext);
    unsigned int count = 0;
    char **types1 = OH_UdmfRecord_GetTypes(record, &count);
    EXPECT_NE(types1, nullptr);
    EXPECT_EQ(count, 1);

    char **types2 = OH_UdmfRecord_GetTypes(record, &count);
    EXPECT_NE(types2, nullptr);
    EXPECT_EQ(count, 1);
    EXPECT_EQ(types2, types1);

    OH_UdsPlainText_Destroy(plaintext);
    OH_UdmfRecord_Destroy(record);
}

/**
 * @tc.name: OH_Udmf_GetRecords001
 * @tc.desc: OH_UdmfRecord_GetTypes with invalid params
 * @tc.type: FUNC
 * @tc.require: AROOOH5R5G
 */
HWTEST_F(UDMFTest, OH_Udmf_GetRecords001, TestSize.Level0)
{
    OH_UdmfData *unifiedData = OH_UdmfData_Create();

    unsigned int count1 = 0;
    OH_UdmfRecord **records1 = OH_UdmfData_GetRecords(nullptr, &count1);
    EXPECT_EQ(records1, nullptr);

    OH_UdmfData data;
    OH_UdmfRecord **records2 = OH_UdmfData_GetRecords(&data, &count1);
    EXPECT_EQ(records2, nullptr);

    OH_UdmfRecord **records3 = OH_UdmfData_GetRecords(unifiedData, nullptr);
    EXPECT_EQ(records3, nullptr);

    OH_UdmfData_Destroy(unifiedData);
}

/**
 * @tc.name: OH_Udmf_GetRecords002
 * @tc.desc: OH_UdmfRecord_GetTypes with valid params
 * @tc.type: FUNC
 * @tc.require: AROOOH5R5G
 */
HWTEST_F(UDMFTest, OH_Udmf_GetRecords002, TestSize.Level0)
{
    OH_UdmfData *unifiedData = OH_UdmfData_Create();
    OH_UdmfRecord *record = OH_UdmfRecord_Create();
    OH_UdsPlainText *plainText = OH_UdsPlainText_Create();
    OH_UdmfRecord_AddPlainText(record, plainText);
    OH_UdmfData_AddRecord(unifiedData, record);
    OH_UdmfRecord *record1 = OH_UdmfRecord_Create();
    OH_UdsHyperlink *hyperlink = OH_UdsHyperlink_Create();
    OH_UdmfRecord_AddHyperlink(record1, hyperlink);
    OH_UdmfData_AddRecord(unifiedData, record1);

    unsigned int count = 0;
    OH_UdmfRecord **records1 = OH_UdmfData_GetRecords(unifiedData, &count);
    EXPECT_EQ(count, 2);
    EXPECT_NE(records1, nullptr);

    OH_UdmfRecord **records2 = OH_UdmfData_GetRecords(unifiedData, &count);
    EXPECT_EQ(count, 2);
    EXPECT_NE(records2, nullptr);
    EXPECT_EQ(records2, records1);

    OH_UdsPlainText_Destroy(plainText);
    OH_UdsHyperlink_Destroy(hyperlink);
    OH_UdmfRecord_Destroy(record);
    OH_UdmfRecord_Destroy(record1);
    OH_UdmfData_Destroy(unifiedData);
}

/**
 * @tc.name: OH_Udmf_SetUnifiedData001
 * @tc.desc: OH_Udmf_SetUnifiedData with invalid param
 * @tc.type: FUNC
 * @tc.require: AROOOH5R5G
 */
HWTEST_F(UDMFTest, UdmfTest006, TestSize.Level0)
{
    Udmf_Intention intention = UDMF_INTENTION_DRAG;
    int setRes1 = OH_Udmf_SetUnifiedData(intention, nullptr, nullptr, 0);
    EXPECT_EQ(setRes1, UDMF_E_INVALID_PARAM);

    OH_UdmfData unifiedData;
    int setRes2 = OH_Udmf_SetUnifiedData(intention, &unifiedData, nullptr, 0);
    EXPECT_EQ(setRes2, UDMF_E_INVALID_PARAM);

    OH_UdmfData *unifiedData1 = OH_UdmfData_Create();
    int setRes3 = OH_Udmf_SetUnifiedData(intention, unifiedData1, nullptr, 0);
    EXPECT_EQ(setRes3, UDMF_E_INVALID_PARAM);

    char key[] = "key";
    int setRes4 = OH_Udmf_SetUnifiedData(intention, unifiedData1, key, 0);
    EXPECT_EQ(setRes4, UDMF_E_INVALID_PARAM);

    intention = static_cast<Udmf_Intention>(10);
    int setRes5 = OH_Udmf_SetUnifiedData(intention, unifiedData1, key, UDMF_KEY_BUFFER_LEN);
    EXPECT_EQ(setRes5, UDMF_E_INVALID_PARAM);

    OH_UdmfData_Destroy(unifiedData1);
}

/**
 * @tc.name: OH_Udmf_GetUnifiedData001
 * @tc.desc: OH_Udmf_GetUnifiedData with invalid param
 * @tc.type: FUNC
 * @tc.require: AROOOH5R5G
 */
HWTEST_F(UDMFTest, OH_Udmf_GetUnifiedData001, TestSize.Level0)
{
    Udmf_Intention intention = UDMF_INTENTION_DRAG;
    int getRes1 = OH_Udmf_GetUnifiedData(nullptr, intention, nullptr);
    EXPECT_EQ(getRes1, UDMF_E_INVALID_PARAM);

    OH_UdmfData unifiedData;
    int getRes2 = OH_Udmf_GetUnifiedData(nullptr, intention, &unifiedData);
    EXPECT_EQ(getRes2, UDMF_E_INVALID_PARAM);

    OH_UdmfData *unifiedData1 = OH_UdmfData_Create();
    int getRes3 = OH_Udmf_GetUnifiedData(nullptr, intention, unifiedData1);
    EXPECT_EQ(getRes3, UDMF_E_INVALID_PARAM);

    int getRes4 = OH_Udmf_GetUnifiedData("KEY", UDMF_INTENTION_PASTEBOARD, unifiedData1);
    EXPECT_EQ(getRes4, UDMF_E_INVALID_PARAM);

    OH_UdmfData_Destroy(unifiedData1);
}

/**
 * @tc.name: OH_Udmf_SetAndGetUnifiedData001
 * @tc.desc: OH_Udmf_SetUnifiedData and OH_Udmf_GetUnifiedData with valid param
 * @tc.type: FUNC
 * @tc.require: AROOOH5R5G
 */
HWTEST_F(UDMFTest, OH_Udmf_SetAndGetUnifiedData001, TestSize.Level0)
{
    OH_UdmfData *udmfUnifiedData = OH_UdmfData_Create();
    OH_UdmfRecord *record = OH_UdmfRecord_Create();
    OH_UdsPlainText *plainText = OH_UdsPlainText_Create();
    char content[] = "hello world";
    OH_UdsPlainText_SetContent(plainText, content);
    OH_UdmfRecord_AddPlainText(record, plainText);
    OH_UdmfData_AddRecord(udmfUnifiedData, record);
    Udmf_Intention intention = UDMF_INTENTION_DRAG;
    char key[UDMF_KEY_BUFFER_LEN];

    int setRes = OH_Udmf_SetUnifiedData(intention, udmfUnifiedData, key, UDMF_KEY_BUFFER_LEN);
    EXPECT_EQ(setRes, UDMF_E_OK);
    EXPECT_NE(key[0], '\0');
    OH_UdmfData *readUnifiedData = OH_UdmfData_Create();
    int getRes = OH_Udmf_GetUnifiedData(key, intention, readUnifiedData);
    EXPECT_EQ(getRes, UDMF_E_OK);
    unsigned int count = 0;
    OH_UdmfRecord **getRecords = OH_UdmfData_GetRecords(readUnifiedData, &count);
    EXPECT_EQ(count, 1);
    OH_UdsPlainText *getPlainText = OH_UdsPlainText_Create();
    OH_UdmfRecord_GetPlainText(getRecords[0], getPlainText);
    const char *getContent = OH_UdsPlainText_GetContent(getPlainText);
    EXPECT_EQ(strcmp(getContent, content), 0);

    OH_UdsPlainText_Destroy(plainText);
    OH_UdmfRecord_Destroy(record);
    OH_UdmfData_Destroy(udmfUnifiedData);

    OH_UdsPlainText_Destroy(getPlainText);
    OH_UdmfData_Destroy(readUnifiedData);
}

/**
 * @tc.name: OH_Udmf_SetAndGetUnifiedData002
 * @tc.desc: OH_Udmf_SetUnifiedData and OH_Udmf_GetUnifiedData with valid param
 * @tc.type: FUNC
 * @tc.require: AROOOH5R5G
 */
HWTEST_F(UDMFTest, OH_Udmf_SetAndGetUnifiedData002, TestSize.Level0)
{
    OH_UdmfData *udmfUnifiedData = OH_UdmfData_Create();
    char typeId[] = "ApplicationDefined-myType";
    unsigned char entry[] = "CreateGeneralRecord";
    unsigned int count = sizeof(entry);
    OH_UdmfRecord *record = OH_UdmfRecord_Create();
    int setRes = OH_UdmfRecord_AddGeneralEntry(record, typeId, entry, count);
    EXPECT_EQ(setRes, UDMF_E_OK);
    setRes = OH_UdmfData_AddRecord(udmfUnifiedData, record);
    EXPECT_EQ(setRes, UDMF_E_OK);
    Udmf_Intention intention = UDMF_INTENTION_DRAG;
    char key[UDMF_KEY_BUFFER_LEN];

    setRes = OH_Udmf_SetUnifiedData(intention, udmfUnifiedData, key, UDMF_KEY_BUFFER_LEN);
    EXPECT_EQ(setRes, UDMF_E_OK);
    EXPECT_NE(key[0], '\0');
    OH_UdmfData *readUnifiedData = OH_UdmfData_Create();
    int getUnifiedDataRes = OH_Udmf_GetUnifiedData(key, intention, readUnifiedData);
    EXPECT_EQ(getUnifiedDataRes, UDMF_E_OK);
    unsigned int getRecordsCount = 0;
    OH_UdmfRecord **getRecords = OH_UdmfData_GetRecords(readUnifiedData, &getRecordsCount);
    EXPECT_EQ(getRecordsCount, 1);
    EXPECT_NE(getRecords, nullptr);

    OH_UdmfRecord_Destroy(record);
    OH_UdmfData_Destroy(readUnifiedData);
    OH_UdmfData_Destroy(udmfUnifiedData);
}

/**
 * @tc.name: OH_Udmf_CreateUnifiedRecord001
 * @tc.desc: OH_Udmf_CreateUnifiedRecord001
 * @tc.type: FUNC
 * @tc.require: AROOOH5R5G
 */
HWTEST_F(UDMFTest, OH_Udmf_CreateUnifiedRecord001, TestSize.Level0)
{
    OH_UdmfRecord *record = OH_UdmfRecord_Create();
    EXPECT_NE(record, nullptr);
    EXPECT_NE(record->record_, nullptr);
    OH_UdmfRecord_Destroy(record);
}

/**
 * @tc.name: OH_Udmf_AddGeneralEntry001
 * @tc.desc: test OH_UdmfRecord_AddGeneralEntry with invalid param
 * @tc.type: FUNC
 * @tc.require: AROOOH5R5G
 */
HWTEST_F(UDMFTest, OH_Udmf_AddGeneralEntry001, TestSize.Level0)
{
    int addRes1 = OH_UdmfRecord_AddGeneralEntry(nullptr, nullptr, nullptr, 0);
    EXPECT_EQ(addRes1, UDMF_E_INVALID_PARAM);

    OH_UdmfRecord record1;
    int addRes2 = OH_UdmfRecord_AddGeneralEntry(&record1, nullptr, nullptr, 0);
    EXPECT_EQ(addRes2, UDMF_E_INVALID_PARAM);

    OH_UdmfRecord *record2 = OH_UdmfRecord_Create();
    int addRes3 = OH_UdmfRecord_AddGeneralEntry(record2, nullptr, nullptr, 0);
    EXPECT_EQ(addRes3, UDMF_E_INVALID_PARAM);

    char typeId[] = "general.plain-text";
    int addRes4 = OH_UdmfRecord_AddGeneralEntry(record2, typeId, nullptr, 0);
    EXPECT_EQ(addRes4, UDMF_E_INVALID_PARAM);

    OH_UdmfRecord_Destroy(record2);
}

/**
 * @tc.name: OH_Udmf_GetGeneralEntry001
 * @tc.desc: test OH_UdmfRecord_GetGeneralEntry with invalid param
 * @tc.type: FUNC
 * @tc.require: AROOOH5R5G
 */
HWTEST_F(UDMFTest, OH_Udmf_GetGeneralEntry001, TestSize.Level0)
{
    int addRes1 = OH_UdmfRecord_GetGeneralEntry(nullptr, nullptr, nullptr, 0);
    EXPECT_EQ(addRes1, UDMF_E_INVALID_PARAM);

    OH_UdmfRecord record1;
    int addRes2 = OH_UdmfRecord_GetGeneralEntry(&record1, nullptr, nullptr, 0);
    EXPECT_EQ(addRes2, UDMF_E_INVALID_PARAM);

    OH_UdmfRecord *record2 = OH_UdmfRecord_Create();
    int addRes3 = OH_UdmfRecord_GetGeneralEntry(record2, nullptr, nullptr, 0);
    EXPECT_EQ(addRes3, UDMF_E_INVALID_PARAM);

    char typeId[] = "general.plain-text";
    int addRes4 = OH_UdmfRecord_GetGeneralEntry(record2, typeId, nullptr, 0);
    EXPECT_EQ(addRes4, UDMF_E_INVALID_PARAM);
    OH_UdmfRecord_Destroy(record2);
}

/**
 * @tc.name: OH_Udmf_AddAndGetGeneralEntry002
 * @tc.desc: test OH_UdmfRecord_AddGeneralEntry and OH_UdmfRecord_GetGeneralEntry with valid param
 * @tc.type: FUNC
 * @tc.require: AROOOH5R5G
 */
HWTEST_F(UDMFTest, OH_Udmf_AddAndGetGeneralEntry002, TestSize.Level0)
{
    char typeId[] = "general.plain-text-1";
    unsigned char entry[] = "CreateGeneralRecord";
    unsigned int count = sizeof(entry);
    OH_UdmfRecord *record = OH_UdmfRecord_Create();
    int addRes1 = OH_UdmfRecord_AddGeneralEntry(record, typeId, entry, count);
    EXPECT_EQ(addRes1, UDMF_E_OK);
}

/**
 * @tc.name: OH_Udmf_AddAndGetGeneralEntry003
 * @tc.desc: test OH_UdmfRecord_AddGeneralEntry and OH_UdmfRecord_GetGeneralEntry with appdefined type
 * @tc.type: FUNC
 * @tc.require:
 */
HWTEST_F(UDMFTest, OH_Udmf_AddAndGetGeneralEntry003, TestSize.Level0)
{
    char typeId[] = "ApplicationDefined-myType";
    unsigned char entry[] = "CreateGeneralRecord1";
    unsigned int count = sizeof(entry);
    OH_UdmfRecord *record = OH_UdmfRecord_Create();
    int addRes1 = OH_UdmfRecord_AddGeneralEntry(record, typeId, entry, count);
    EXPECT_EQ(addRes1, UDMF_E_OK);

    unsigned int getCount = 0;
    unsigned char *getEntry;
    int getRes = OH_UdmfRecord_GetGeneralEntry(record, typeId, &getEntry, &getCount);
    EXPECT_EQ(getRes, UDMF_E_OK);
    EXPECT_EQ(getCount, count);
    ASSERT_TRUE(CheckUnsignedChar(entry, getEntry, getCount));
    OH_UdmfRecord_Destroy(record);
}

/**
 * @tc.name: OH_Udmf_AddAndGetGeneralEntry004
 * @tc.desc: test OH_UdmfRecord_AddGeneralEntry and OH_UdmfRecord_GetGeneralEntry with appdefined diff types
 * @tc.type: FUNC
 * @tc.require:
 */
HWTEST_F(UDMFTest, OH_Udmf_AddAndGetGeneralEntry004, TestSize.Level0)
{
    char typeId1[] = "ApplicationDefined-myType1";
    unsigned char entry1[] = "CreateGeneralRecord1";
    unsigned int count1 = sizeof(entry1);
    char typeId2[] = "ApplicationDefined-myType2";
    unsigned char entry2[] = "CreateGeneralRecord2";
    unsigned int count2 = sizeof(entry2);
    OH_UdmfRecord *record = OH_UdmfRecord_Create();
    int addRes1 = OH_UdmfRecord_AddGeneralEntry(record, typeId1, entry1, count1);
    EXPECT_EQ(addRes1, UDMF_E_OK);
    addRes1 = OH_UdmfRecord_AddGeneralEntry(record, typeId2, entry2, count2);
    EXPECT_EQ(addRes1, UDMF_E_OK);

    unsigned int getCount1 = 0;
    unsigned char *getEntry1;
    int getRes = OH_UdmfRecord_GetGeneralEntry(record, typeId1, &getEntry1, &getCount1);
    EXPECT_EQ(getRes, UDMF_E_OK);
    EXPECT_EQ(getCount1, count1);
    ASSERT_TRUE(CheckUnsignedChar(entry1, getEntry1, getCount1));

    unsigned int getCount2 = 0;
    unsigned char *getEntry2;
    getRes = OH_UdmfRecord_GetGeneralEntry(record, typeId2, &getEntry2, &getCount2);
    EXPECT_EQ(getRes, UDMF_E_OK);
    EXPECT_EQ(getCount2, count2);
    ASSERT_TRUE(CheckUnsignedChar(entry2, getEntry2, getCount2));

    OH_UdmfRecord_Destroy(record);
}

/**
 * @tc.name: OH_Udmf_BuildRecordByPlainText001
 * @tc.desc: test OH_UdmfRecord_AddPlainText with invalid param
 * @tc.type: FUNC
 * @tc.require: AROOOH5R5G
 */
HWTEST_F(UDMFTest, OH_Udmf_BuildRecordByPlainText001, TestSize.Level0)
{
    int buildRes1 = OH_UdmfRecord_AddPlainText(nullptr, nullptr);
    EXPECT_EQ(buildRes1, UDMF_E_INVALID_PARAM);

    OH_UdmfRecord record1;
    int buildRes2 = OH_UdmfRecord_AddPlainText(&record1, nullptr);
    EXPECT_EQ(buildRes2, UDMF_E_INVALID_PARAM);

    OH_UdmfRecord *record2 = OH_UdmfRecord_Create();
    int buildRes3 = OH_UdmfRecord_AddPlainText(record2, nullptr);
    EXPECT_EQ(buildRes3, UDMF_E_INVALID_PARAM);

    OH_UdsPlainText plainText;
    int buildRes4 = OH_UdmfRecord_AddPlainText(record2, &plainText);
    EXPECT_EQ(buildRes4, UDMF_E_INVALID_PARAM);

    OH_UdmfRecord_Destroy(record2);
}

/**
 * @tc.name: OH_Udmf_GetPlainTextFromRecord001
 * @tc.desc: test OH_UdmfRecord_GetPlainText with invalid param
 * @tc.type: FUNC
 * @tc.require: AROOOH5R5G
 */
HWTEST_F(UDMFTest, OH_Udmf_GetPlainTextFromRecord001, TestSize.Level0)
{
    int buildRes1 = OH_UdmfRecord_GetPlainText(nullptr, nullptr);
    EXPECT_EQ(buildRes1, UDMF_E_INVALID_PARAM);

    OH_UdmfRecord record1;
    int buildRes2 = OH_UdmfRecord_GetPlainText(&record1, nullptr);
    EXPECT_EQ(buildRes2, UDMF_E_INVALID_PARAM);

    OH_UdmfRecord *record2 = OH_UdmfRecord_Create();
    int buildRes3 = OH_UdmfRecord_GetPlainText(record2, nullptr);
    EXPECT_EQ(buildRes3, UDMF_E_INVALID_PARAM);

    OH_UdsPlainText plainText;
    int buildRes4 = OH_UdmfRecord_GetPlainText(record2, &plainText);
    EXPECT_EQ(buildRes4, UDMF_E_INVALID_PARAM);

    OH_UdmfRecord_Destroy(record2);
}

/**
 * @tc.name: OH_Udmf_BuildAndGetPlainTextFromRecord001
 * @tc.desc: test OH_UdmfRecord_GetPlainText and OH_Udmf_BuildPlainTextFromRecord with invalid param
 * @tc.type: FUNC
 * @tc.require: AROOOH5R5G
 */
HWTEST_F(UDMFTest, OH_Udmf_BuildAndGetPlainTextFromRecord001, TestSize.Level0)
{
    OH_UdmfRecord *record1 = OH_UdmfRecord_Create();
    OH_UdsPlainText *plainText1 = OH_UdsPlainText_Create();
    char content[] = "hello world";
    OH_UdsPlainText_SetContent(plainText1, content);
    int buildRes = OH_UdmfRecord_AddPlainText(record1, plainText1);
    EXPECT_EQ(buildRes, UDMF_E_OK);

    OH_UdsPlainText *plainText2 = OH_UdsPlainText_Create();
    int getRes = OH_UdmfRecord_GetPlainText(record1, plainText2);
    EXPECT_EQ(getRes, UDMF_E_OK);

    const char *getContent = OH_UdsPlainText_GetContent(plainText2);
    EXPECT_EQ(strcmp(content, getContent), 0);

    OH_UdmfRecord_Destroy(record1);
    OH_UdsPlainText_Destroy(plainText1);
    OH_UdsPlainText_Destroy(plainText2);
}

/**
 * @tc.name: OH_Udmf_BuildRecordByHyperlink001
 * @tc.desc: test OH_UdmfRecord_AddHyperlink with invalid param
 * @tc.type: FUNC
 * @tc.require: AROOOH5R5G
 */
HWTEST_F(UDMFTest, OH_Udmf_BuildRecordByHyperlink001, TestSize.Level0)
{
    int buildRes1 = OH_UdmfRecord_AddHyperlink(nullptr, nullptr);
    EXPECT_EQ(buildRes1, UDMF_E_INVALID_PARAM);

    OH_UdmfRecord record1;
    int buildRes2 = OH_UdmfRecord_AddHyperlink(&record1, nullptr);
    EXPECT_EQ(buildRes2, UDMF_E_INVALID_PARAM);

    OH_UdmfRecord *record2 = OH_UdmfRecord_Create();
    int buildRes3 = OH_UdmfRecord_AddHyperlink(record2, nullptr);
    EXPECT_EQ(buildRes3, UDMF_E_INVALID_PARAM);

    OH_UdsHyperlink hyperlink;
    int buildRes4 = OH_UdmfRecord_AddHyperlink(record2, &hyperlink);
    EXPECT_EQ(buildRes4, UDMF_E_INVALID_PARAM);

    OH_UdmfRecord_Destroy(record2);
}

/**
 * @tc.name: OH_Udmf_GetHyperlinkFromRecord001
 * @tc.desc: test OH_UdmfRecord_GetHyperlink with invalid param
 * @tc.type: FUNC
 * @tc.require: AROOOH5R5G
 */
HWTEST_F(UDMFTest, OH_Udmf_GetHyperlinkFromRecord001, TestSize.Level0)
{
    int buildRes1 = OH_UdmfRecord_GetHyperlink(nullptr, nullptr);
    EXPECT_EQ(buildRes1, UDMF_E_INVALID_PARAM);

    OH_UdmfRecord record1;
    int buildRes2 = OH_UdmfRecord_GetHyperlink(&record1, nullptr);
    EXPECT_EQ(buildRes2, UDMF_E_INVALID_PARAM);

    OH_UdmfRecord *record2 = OH_UdmfRecord_Create();
    int buildRes3 = OH_UdmfRecord_GetHyperlink(record2, nullptr);
    EXPECT_EQ(buildRes3, UDMF_E_INVALID_PARAM);

    OH_UdsHyperlink hyperlink;
    int buildRes4 = OH_UdmfRecord_GetHyperlink(record2, &hyperlink);
    EXPECT_EQ(buildRes4, UDMF_E_INVALID_PARAM);

    OH_UdmfRecord_Destroy(record2);
}

/**
 * @tc.name: OH_Udmf_BuildAndGetHyperlinkFromRecord001
 * @tc.desc: test OH_Udmf_BuildAndGetHyperlinkFromRecord with invalid param
 * @tc.type: FUNC
 * @tc.require: AROOOH5R5G
 */
HWTEST_F(UDMFTest, OH_Udmf_BuildAndGetHyperlinkFromRecord001, TestSize.Level0)
{
    OH_UdmfRecord *record1 = OH_UdmfRecord_Create();
    OH_UdsHyperlink *hyperlink1 = OH_UdsHyperlink_Create();
    char url[] = "https://gitee.com/openharmony/distributeddatamgr_udmf/members";
    OH_UdsHyperlink_SetUrl(hyperlink1, url);
    int buildRes = OH_UdmfRecord_AddHyperlink(record1, hyperlink1);
    EXPECT_EQ(buildRes, UDMF_E_OK);

    OH_UdsHyperlink *hyperlink2 = OH_UdsHyperlink_Create();
    int getRes = OH_UdmfRecord_GetHyperlink(record1, hyperlink2);
    EXPECT_EQ(getRes, UDMF_E_OK);

    const char *getUrl = OH_UdsHyperlink_GetUrl(hyperlink2);
    EXPECT_EQ(strcmp(url, getUrl), 0);

    OH_UdmfRecord_Destroy(record1);
    OH_UdsHyperlink_Destroy(hyperlink1);
    OH_UdsHyperlink_Destroy(hyperlink2);
}

/**
 * @tc.name: OH_Udmf_BuildRecordByHtml001
 * @tc.desc: test OH_UdmfRecord_AddHtml with invalid param
 * @tc.type: FUNC
 * @tc.require: AROOOH5R5G
 */
HWTEST_F(UDMFTest, OH_Udmf_BuildRecordByHtml001, TestSize.Level0)
{
    int buildRes1 = OH_UdmfRecord_AddHtml(nullptr, nullptr);
    EXPECT_EQ(buildRes1, UDMF_E_INVALID_PARAM);

    OH_UdmfRecord record1;
    int buildRes2 = OH_UdmfRecord_AddHtml(&record1, nullptr);
    EXPECT_EQ(buildRes2, UDMF_E_INVALID_PARAM);

    OH_UdmfRecord *record2 = OH_UdmfRecord_Create();
    int buildRes3 = OH_UdmfRecord_AddHtml(record2, nullptr);
    EXPECT_EQ(buildRes3, UDMF_E_INVALID_PARAM);

    OH_UdsHtml html;
    int buildRes4 = OH_UdmfRecord_AddHtml(record2, &html);
    EXPECT_EQ(buildRes4, UDMF_E_INVALID_PARAM);

    OH_UdmfRecord_Destroy(record2);
}

/**
 * @tc.name: OH_Udmf_GetHtmlFromRecord001
 * @tc.desc: test OH_UdmfRecord_GetHtml with invalid param
 * @tc.type: FUNC
 * @tc.require: AROOOH5R5G
 */
HWTEST_F(UDMFTest, OH_Udmf_GetHtmlFromRecord001, TestSize.Level0)
{
    int buildRes1 = OH_UdmfRecord_GetHtml(nullptr, nullptr);
    EXPECT_EQ(buildRes1, UDMF_E_INVALID_PARAM);

    OH_UdmfRecord record1;
    int buildRes2 = OH_UdmfRecord_GetHtml(&record1, nullptr);
    EXPECT_EQ(buildRes2, UDMF_E_INVALID_PARAM);

    OH_UdmfRecord *record2 = OH_UdmfRecord_Create();
    int buildRes3 = OH_UdmfRecord_GetHtml(record2, nullptr);
    EXPECT_EQ(buildRes3, UDMF_E_INVALID_PARAM);

    OH_UdsHtml html;
    int buildRes4 = OH_UdmfRecord_GetHtml(record2, &html);
    EXPECT_EQ(buildRes4, UDMF_E_INVALID_PARAM);

    OH_UdmfRecord_Destroy(record2);
}

/**
 * @tc.name: OH_Udmf_BuildAndGetHtmlFromRecord001
 * @tc.desc: test OH_Udmf_BuildAndGetHtmlFromRecord with invalid param
 * @tc.type: FUNC
 * @tc.require: AROOOH5R5G
 */
HWTEST_F(UDMFTest, OH_Udmf_BuildAndGetHtmlFromRecord001, TestSize.Level0)
{
    OH_UdmfRecord *record1 = OH_UdmfRecord_Create();
    OH_UdsHtml *html1 = OH_UdsHtml_Create();
    char content[] = "hello world";
    OH_UdsHtml_SetContent(html1, content);
    int buildRes = OH_UdmfRecord_AddHtml(record1, html1);
    EXPECT_EQ(buildRes, UDMF_E_OK);

    OH_UdsHtml *html2 = OH_UdsHtml_Create();
    int getRes = OH_UdmfRecord_GetHtml(record1, html2);
    EXPECT_EQ(getRes, UDMF_E_OK);

    const char *getContent = OH_UdsHtml_GetContent(html2);
    EXPECT_EQ(strcmp(content, getContent), 0);

    OH_UdmfRecord_Destroy(record1);
    OH_UdsHtml_Destroy(html1);
    OH_UdsHtml_Destroy(html2);
}

/**
 * @tc.name: OH_Udmf_BuildRecordByOpenHarmonyAppItem001
 * @tc.desc: test OH_UdmfRecord_AddAppItem with invalid param
 * @tc.type: FUNC
 * @tc.require: AROOOH5R5G
 */
HWTEST_F(UDMFTest, OH_Udmf_BuildRecordByOpenHarmonyAppItem001, TestSize.Level0)
{
    int buildRes1 = OH_UdmfRecord_AddAppItem(nullptr, nullptr);
    EXPECT_EQ(buildRes1, UDMF_E_INVALID_PARAM);

    OH_UdmfRecord record1;
    int buildRes2 = OH_UdmfRecord_AddAppItem(&record1, nullptr);
    EXPECT_EQ(buildRes2, UDMF_E_INVALID_PARAM);

    OH_UdmfRecord *record2 = OH_UdmfRecord_Create();
    int buildRes3 = OH_UdmfRecord_AddAppItem(record2, nullptr);
    EXPECT_EQ(buildRes3, UDMF_E_INVALID_PARAM);

    OH_UdsAppItem appItem;
    int buildRes4 = OH_UdmfRecord_AddAppItem(record2, &appItem);
    EXPECT_EQ(buildRes4, UDMF_E_INVALID_PARAM);

    OH_UdmfRecord_Destroy(record2);
}

/**
 * @tc.name: OH_Udmf_GetOpenHarmonyAppItemFromRecord001
 * @tc.desc: test OH_UdmfRecord_GetAppItem with invalid param
 * @tc.type: FUNC
 * @tc.require: AROOOH5R5G
 */
HWTEST_F(UDMFTest, OH_Udmf_GetOpenHarmonyAppItemFromRecord001, TestSize.Level0)
{
    int buildRes1 = OH_UdmfRecord_GetAppItem(nullptr, nullptr);
    EXPECT_EQ(buildRes1, UDMF_E_INVALID_PARAM);

    OH_UdmfRecord record1;
    int buildRes2 = OH_UdmfRecord_GetAppItem(&record1, nullptr);
    EXPECT_EQ(buildRes2, UDMF_E_INVALID_PARAM);

    OH_UdmfRecord *record2 = OH_UdmfRecord_Create();
    int buildRes3 = OH_UdmfRecord_GetAppItem(record2, nullptr);
    EXPECT_EQ(buildRes3, UDMF_E_INVALID_PARAM);

    OH_UdsAppItem appItem;
    int buildRes4 = OH_UdmfRecord_GetAppItem(record2, &appItem);
    EXPECT_EQ(buildRes4, UDMF_E_INVALID_PARAM);

    OH_UdmfRecord_Destroy(record2);
}

/**
 * @tc.name: OH_Udmf_BuildAndGetAppItemFromRecord001
 * @tc.desc: test OH_Udmf_BuildAndGetAppItemFromRecord with invalid param
 * @tc.type: FUNC
 * @tc.require: AROOOH5R5G
 */
HWTEST_F(UDMFTest, OH_Udmf_BuildAndGetAppItemFromRecord001, TestSize.Level0)
{
    OH_UdmfRecord *record1 = OH_UdmfRecord_Create();
    OH_UdsAppItem *appItem1 = OH_UdsAppItem_Create();
    char name[] = "appItem";
    OH_UdsAppItem_SetName(appItem1, name);
    int buildRes = OH_UdmfRecord_AddAppItem(record1, appItem1);
    EXPECT_EQ(buildRes, UDMF_E_OK);

    OH_UdsAppItem *appItem2 = OH_UdsAppItem_Create();
    int getRes = OH_UdmfRecord_GetAppItem(record1, appItem2);
    EXPECT_EQ(getRes, UDMF_E_OK);

    const char *getName = OH_UdsAppItem_GetName(appItem2);
    EXPECT_EQ(strcmp(name, getName), 0);

    OH_UdmfRecord_Destroy(record1);
    OH_UdsAppItem_Destroy(appItem1);
    OH_UdsAppItem_Destroy(appItem2);
}

/**
 * @tc.name: OH_Udmf_CreatePropertiesFromUnifiedData001
 * @tc.desc: Normal testcase of OH_UdmfProperty_Create
 * @tc.type: FUNC
 */
HWTEST_F(UDMFTest, OH_Udmf_CreatePropertiesFromUnifiedData001, TestSize.Level1)
{
    OH_UdmfData *data = OH_UdmfData_Create();
    OH_UdmfProperty *properties = OH_UdmfProperty_Create(data);
    auto duration = std::chrono::system_clock::now().time_since_epoch();
    EXPECT_LE(properties->properties_->timestamp,
        std::chrono::duration_cast<std::chrono::milliseconds>(duration).count());
    OH_UdmfData_Destroy(data);
    OH_UdmfProperty_Destroy(properties);
}

/**
 * @tc.name: OH_Udmf_SetPropertiesTag001
 * @tc.desc: Normal testcase of OH_Udmf_SetPropertiesTag001
 * @tc.type: FUNC
 */
HWTEST_F(UDMFTest, OH_Udmf_SetPropertiesTag001, TestSize.Level1)
{
    OH_UdmfData *data = OH_UdmfData_Create();
    OH_UdmfProperty *properties = OH_UdmfProperty_Create(data);
    std::string tag("tag");
    int result = OH_UdmfProperty_SetTag(properties, tag.c_str());
    EXPECT_EQ(UDMF_E_OK, result);
    EXPECT_EQ(tag, OH_UdmfProperty_GetTag(properties));
    OH_UdmfProperty_Destroy(properties);
    OH_UdmfData_Destroy(data);
}

/**
 * @tc.name: OH_Udmf_SetPropertiesShareOption001
 * @tc.desc: set properties IN_APP
 * @tc.type: FUNC
 */
HWTEST_F(UDMFTest, OH_Udmf_SetPropertiesShareOption001, TestSize.Level1)
{
    OH_UdmfData *data = OH_UdmfData_Create();
    OH_UdmfProperty *properties = OH_UdmfProperty_Create(data);
    int result = OH_UdmfProperty_SetShareOption(properties, Udmf_ShareOption::SHARE_OPTIONS_IN_APP);
    EXPECT_EQ(UDMF_E_OK, result);
    EXPECT_EQ(Udmf_ShareOption::SHARE_OPTIONS_IN_APP, OH_UdmfProperty_GetShareOption(properties));
    OH_UdmfData_Destroy(data);
    OH_UdmfProperty_Destroy(properties);
}

/**
 * @tc.name: OH_Udmf_SetPropertiesShareOption002
 * @tc.desc: set properties CROSS_APP
 * @tc.type: FUNC
 */
HWTEST_F(UDMFTest, OH_Udmf_SetPropertiesShareOption002, TestSize.Level1)
{
    OH_UdmfData *data = OH_UdmfData_Create();
    OH_UdmfProperty *properties = OH_UdmfProperty_Create(data);
    int result = OH_UdmfProperty_SetShareOption(properties, Udmf_ShareOption::SHARE_OPTIONS_CROSS_APP);
    EXPECT_EQ(UDMF_E_OK, result);
    EXPECT_EQ(Udmf_ShareOption::SHARE_OPTIONS_CROSS_APP, OH_UdmfProperty_GetShareOption(properties));
    OH_UdmfData_Destroy(data);
    OH_UdmfProperty_Destroy(properties);
}

/**
 * @tc.name: OH_Udmf_SetPropertiesShareOption003
 * @tc.desc: set invalid properties
 * @tc.type: FUNC
 */
HWTEST_F(UDMFTest, OH_Udmf_SetPropertiesShareOption003, TestSize.Level1)
{
    OH_UdmfProperty *property = nullptr;
    EXPECT_EQ(Udmf_ShareOption::SHARE_OPTIONS_INVALID, OH_UdmfProperty_GetShareOption(property));
}

/**
 * @tc.name: OH_Udmf_SetPropertiesExtrasIntParam001
 * @tc.desc: Normal testcase of OH_UdmfProperty_SetExtrasIntParam
 * @tc.type: FUNC
 */
HWTEST_F(UDMFTest, OH_Udmf_SetPropertiesExtrasIntParam001, TestSize.Level1)
{
    OH_UdmfData *data = OH_UdmfData_Create();
    OH_UdmfProperty *properties = OH_UdmfProperty_Create(data);
    int result = OH_UdmfProperty_SetExtrasIntParam(properties, "keyInt", 0);
    EXPECT_EQ(UDMF_E_OK, result);
    EXPECT_EQ(0, OH_UdmfProperty_GetExtrasIntParam(properties, "keyInt", -1));
    OH_UdmfData_Destroy(data);
    OH_UdmfProperty_Destroy(properties);
}

/**
 * @tc.name: OH_Udmf_SetPropertiesExtrasStringParam001
 * @tc.desc: Normal testcase of OH_UdmfProperty_SetExtrasStringParam
 * @tc.type: FUNC
 */
HWTEST_F(UDMFTest, OH_Udmf_SetPropertiesExtrasStringParam001, TestSize.Level1)
{
    OH_UdmfData *data = OH_UdmfData_Create();
    OH_UdmfProperty *properties = OH_UdmfProperty_Create(data);
    std::string str("str");
    int result = OH_UdmfProperty_SetExtrasStringParam(properties, "keyStr", str.c_str());
    EXPECT_EQ(UDMF_E_OK, result);
    std::string actualStr(OH_UdmfProperty_GetExtrasStringParam(properties, "keyStr"));
    EXPECT_EQ(str, actualStr);
    OH_UdmfData_Destroy(data);
    OH_UdmfProperty_Destroy(properties);
}

/**
 * @tc.name: OH_Udmf_MultiStyleRecord001
 * @tc.desc: Normal testcase of OH_UdmfProperty_SetExtrasStringParam
 * @tc.type: FUNC
 */
HWTEST_F(UDMFTest, OH_Udmf_MultiStyleRecord001, TestSize.Level1)
{
    OH_UdsPlainText* plainText = OH_UdsPlainText_Create();
    char plainTextContent[] = "plain text";
    OH_UdsPlainText_SetContent(plainText, plainTextContent);

    OH_UdsHyperlink* hyperlink = OH_UdsHyperlink_Create();
    char url[] = "hyper link";
    OH_UdsHyperlink_SetUrl(hyperlink, url);

    OH_UdsHtml* html = OH_UdsHtml_Create();
    char htmlContent[] = "html";
    OH_UdsHtml_SetContent(html, htmlContent);

    OH_UdsAppItem* appItem = OH_UdsAppItem_Create();
    char name[] = "appItem";
    OH_UdsAppItem_SetName(appItem, name);

    OH_UdmfRecord *record = OH_UdmfRecord_Create();

    OH_UdmfRecord_AddPlainText(record, plainText);
    OH_UdmfRecord_AddHyperlink(record, hyperlink);
    OH_UdmfRecord_AddHtml(record, html);
    OH_UdmfRecord_AddAppItem(record, appItem);

    unsigned int count = 0;
    char** types = OH_UdmfRecord_GetTypes(record, &count);
    EXPECT_NE(types, nullptr);
    EXPECT_EQ(count, 4);

    OH_UdsPlainText *getPlainText = OH_UdsPlainText_Create();
    OH_UdmfRecord_GetPlainText(record, getPlainText);
    const char *getPlainTextContent = OH_UdsPlainText_GetContent(getPlainText);
    EXPECT_EQ(strcmp(getPlainTextContent, plainTextContent), 0);

    OH_UdsHyperlink *getHyperLink = OH_UdsHyperlink_Create();
    OH_UdmfRecord_GetHyperlink(record, getHyperLink);
    const char *getUrl = OH_UdsHyperlink_GetUrl(getHyperLink);
    EXPECT_EQ(strcmp(getUrl, url), 0);

    OH_UdsHtml *getHtml = OH_UdsHtml_Create();
    OH_UdmfRecord_GetHtml(record, getHtml);
    const char *getHtmlContent = OH_UdsHtml_GetContent(getHtml);
    EXPECT_EQ(strcmp(getHtmlContent, htmlContent), 0);

    OH_UdsAppItem *getAppItem = OH_UdsAppItem_Create();
    OH_UdmfRecord_GetAppItem(record, getAppItem);
    const char *getName = OH_UdsAppItem_GetName(getAppItem);
    EXPECT_EQ(strcmp(getName, name), 0);

    OH_UdmfData* data = OH_UdmfData_Create();
    OH_UdmfData_AddRecord(data, record);

    unsigned int count2 = 0;
    char** types2 = OH_UdmfData_GetTypes(data, &count2);
    EXPECT_NE(types2, nullptr);
    EXPECT_EQ(count2, 4);

    char plianTextType[] = "general.plain-text";
    char hyperLinkType[] = "general.hyperlink";
    char htmlType[] = "general.html";
    char appItemType[] = "openharmony.app-item";

    EXPECT_TRUE(OH_UdmfData_HasType(data, plianTextType));
    EXPECT_TRUE(OH_UdmfData_HasType(data, hyperLinkType));
    EXPECT_TRUE(OH_UdmfData_HasType(data, htmlType));
    EXPECT_TRUE(OH_UdmfData_HasType(data, appItemType));

    OH_UdsPlainText_Destroy(plainText);
    OH_UdsPlainText_Destroy(getPlainText);
    OH_UdsHyperlink_Destroy(hyperlink);
    OH_UdsHyperlink_Destroy(getHyperLink);
    OH_UdsHtml_Destroy(html);
    OH_UdsHtml_Destroy(getHtml);
    OH_UdsAppItem_Destroy(appItem);
    OH_UdsAppItem_Destroy(getAppItem);
    OH_UdmfRecord_Destroy(record);
    OH_UdmfData_Destroy(data);
}

/**
 * @tc.name: OH_Udmf_MultiStyleRecord002
 * @tc.desc: Normal testcase of OH_UdmfProperty_SetExtrasStringParam
 * @tc.type: FUNC
 */
HWTEST_F(UDMFTest, OH_Udmf_MultiStyleRecord002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetSummary005 begin.");

    CustomOption option1 = { .intention = Intention::UD_INTENTION_DRAG };
    UnifiedData data;
    std::string key;
    auto object = std::make_shared<Object>();
    object->value_[UNIFORM_DATA_TYPE] = UtdUtils::GetUtdIdFromUtdEnum(UDType::PLAIN_TEXT);
    object->value_[CONTENT] = "content_";
    object->value_[ABSTRACT] = "abstract_";
    auto record = std::make_shared<UnifiedRecord>(UDType::PLAIN_TEXT, object);

    std::vector<uint8_t> raw = {1, 2, 3, 4, 5};
    std::shared_ptr<Object> obj = std::make_shared<Object>();
    obj->value_[UNIFORM_DATA_TYPE] = "general.content-form";
    obj->value_[THUMB_DATA] = raw;
    obj->value_[THUMB_DATA_LENGTH] = 5;
    obj->value_[DESCRIPTION] = "descritpion";
    obj->value_[TITLE] = "title";
    obj->value_[APP_ICON_LENGTH] = 5;
    obj->value_[APP_NAME] = "appName";
    obj->value_[LINK_URL] = "linkUri";
    auto contentForm = UnifiedRecord(CONTENT_FORM, obj);
    record->AddEntry(contentForm.GetUtdId(), contentForm.GetOriginValue());

    data.AddRecord(record);

    auto status = UdmfClient::GetInstance().SetData(option1, data, key);
    ASSERT_EQ(status, E_OK);

    ASSERT_EQ(status, E_OK);
    OH_UdmfData *readUnifiedData = OH_UdmfData_Create();
    int getRes = OH_Udmf_GetUnifiedData(key.c_str(), UDMF_INTENTION_DRAG, readUnifiedData);
    ASSERT_EQ(getRes, E_OK);
    unsigned int count = 0;
    OH_UdmfRecord** readRecords = OH_UdmfData_GetRecords(readUnifiedData, &count);
    ASSERT_EQ(count, 1);
    for (int i = 0; i < count; i++) {
        OH_UdsContentForm *contentForm = OH_UdsContentForm_Create();
        OH_UdmfRecord_GetContentForm(readRecords[i], contentForm);
        const char* desc = OH_UdsContentForm_GetDescription(contentForm);
        EXPECT_EQ(std::string(desc), "descritpion");
        OH_UdsPlainText *plainText = OH_UdsPlainText_Create();
        OH_UdmfRecord_GetPlainText(readRecords[i], plainText);
        const char* text = OH_UdsPlainText_GetContent(plainText);
        EXPECT_EQ(std::string(text), "content_");
    }
}

/**
 * @tc.name: OH_UdmfRecordProvider_Create001
 * @tc.desc: Normal testcase of OH_UdmfRecordProvider_Create
 * @tc.type: FUNC
 */
HWTEST_F(UDMFTest, OH_UdmfRecordProvider_Create001, TestSize.Level1)
{
    OH_UdmfRecordProvider* provider = OH_UdmfRecordProvider_Create();
    EXPECT_NE(provider, nullptr);
    OH_UdmfRecordProvider_Destroy(provider);
}

/**
 * @tc.name: OH_UdmfRecordProvider_Destroy001
 * @tc.desc: Normal testcase of OH_UdmfRecordProvider_Destroy
 * @tc.type: FUNC
 */
HWTEST_F(UDMFTest, OH_UdmfRecordProvider_Destroy001, TestSize.Level1)
{
    OH_UdmfRecordProvider* provider = OH_UdmfRecordProvider_Create();
    EXPECT_NE(provider, nullptr);
    int num = 1;
    void* context = &num;
    OH_UdmfRecordProvider_SetData(provider, context, GetDataCallbackFunc, FinalizeFunc);
    int res1 = OH_UdmfRecordProvider_Destroy(provider);
    EXPECT_EQ(res1, UDMF_E_OK);
}

/**
 * @tc.name: OH_UdmfRecordProvider_Destroy002
 * @tc.desc: invalid parameters testcase of OH_UdmfRecordProvider_Destroy
 * @tc.type: FUNC
 */
HWTEST_F(UDMFTest, OH_UdmfRecordProvider_Destroy002, TestSize.Level1)
{
    OH_UdmfRecordProvider* provider = OH_UdmfRecordProvider_Create();
    EXPECT_NE(provider, nullptr);
    int num = 1;
    void* context = &num;
    OH_UdmfRecordProvider_SetData(provider, context, GetDataCallbackFunc, nullptr);
    int res1 = OH_UdmfRecordProvider_Destroy(provider);
    EXPECT_EQ(res1, UDMF_E_OK);
}

/**
 * @tc.name: OH_UdmfRecordProvider_SetData001
 * @tc.desc: Normal testcase of OH_UdmfRecordProvider_SetData
 * @tc.type: FUNC
 */
HWTEST_F(UDMFTest, OH_UdmfRecordProvider_SetData001, TestSize.Level1)
{
    OH_UdmfRecordProvider* provider = OH_UdmfRecordProvider_Create();
    EXPECT_NE(provider, nullptr);
    int num = 1;
    void* context = &num;
    int res = OH_UdmfRecordProvider_SetData(provider, context, GetDataCallbackFunc, FinalizeFunc);
    EXPECT_NE(provider->context, nullptr);
    EXPECT_NE(provider->callback, nullptr);
    EXPECT_NE(provider->finalize, nullptr);
    EXPECT_EQ(res, UDMF_E_OK);
    OH_UdmfRecordProvider_Destroy(provider);
}

/**
 * @tc.name: OH_UdmfRecordProvider_SetData002
 * @tc.desc: invalid parameters testcase of OH_UdmfRecordProvider_SetData
 * @tc.type: FUNC
 */
HWTEST_F(UDMFTest, OH_UdmfRecordProvider_SetData002, TestSize.Level1)
{
    OH_UdmfRecordProvider* provider = OH_UdmfRecordProvider_Create();
    EXPECT_NE(provider, nullptr);
    int num = 1;
    void* context = &num;
    int res1 = OH_UdmfRecordProvider_SetData(provider, context, GetDataCallbackFunc, nullptr);
    EXPECT_EQ(provider->context, nullptr);
    EXPECT_EQ(provider->finalize, nullptr);
    EXPECT_EQ(res1, UDMF_E_INVALID_PARAM);

    int res2 = OH_UdmfRecordProvider_SetData(nullptr, context, GetDataCallbackFunc, nullptr);
    EXPECT_EQ(res2, UDMF_E_INVALID_PARAM);

    int res3 = OH_UdmfRecordProvider_SetData(provider, context, nullptr, nullptr);
    EXPECT_EQ(res3, UDMF_E_INVALID_PARAM);
    OH_UdmfRecordProvider_Destroy(provider);
}

/**
 * @tc.name: OH_UdmfRecord_SetProvider001
 * @tc.desc: Normal testcase of OH_UdmfRecord_SetProvider
 * @tc.type: FUNC
 */
HWTEST_F(UDMFTest, OH_UdmfRecord_SetProvider001, TestSize.Level1)
{
    OH_UdmfRecord *record = OH_UdmfRecord_Create();
    OH_UdsPlainText *plainText = OH_UdsPlainText_Create();
    char content[] = "hello world";
    OH_UdsPlainText_SetContent(plainText, content);
    OH_UdmfRecord_AddPlainText(record, plainText);
    OH_UdmfRecordProvider* provider = OH_UdmfRecordProvider_Create();
    EXPECT_NE(provider, nullptr);
    int num = 1;
    void* context = &num;
    OH_UdmfRecordProvider_SetData(provider, context, GetDataCallbackFunc, FinalizeFunc);
    const char* types[3] = { "general.plain-text", "general.hyperlink", "general.html" };

    int res = OH_UdmfRecord_SetProvider(record, types, 3, provider);
    EXPECT_EQ(res, UDMF_E_OK);
    OH_UdmfRecordProvider_Destroy(provider);
}

/**
 * @tc.name: OH_UdmfRecord_SetProvider002
 * @tc.desc: invalid parameters testcase of OH_UdmfRecord_SetProvider
 * @tc.type: FUNC
 */
HWTEST_F(UDMFTest, OH_UdmfRecord_SetProvider002, TestSize.Level1)
{
    OH_UdmfRecord *record = OH_UdmfRecord_Create();
    OH_UdsPlainText *plainText = OH_UdsPlainText_Create();
    char content[] = "hello world";
    OH_UdsPlainText_SetContent(plainText, content);
    OH_UdmfRecord_AddPlainText(record, plainText);
    OH_UdmfRecordProvider* provider = OH_UdmfRecordProvider_Create();
    EXPECT_NE(provider, nullptr);
    int num = 1;
    void* context = &num;
    OH_UdmfRecordProvider_SetData(provider, context, GetDataCallbackFunc, FinalizeFunc);
    const char* types[3] = { "general.plain-text", "general.hyperlink", "general.html" };

    int res = OH_UdmfRecord_SetProvider(record, types, 3, provider);
    EXPECT_EQ(res, UDMF_E_OK);
    OH_UdmfRecordProvider_Destroy(provider);
}

/**
 * @tc.name: OH_Udmf_BuildRecordByOpenHarmonyArrayBuffer001
 * @tc.desc: test OH_UdmfRecord_AddArrayBuffer with invalid param
 * @tc.type: FUNC
 */
HWTEST_F(UDMFTest, OH_Udmf_BuildRecordByOpenHarmonyArrayBuffer001, TestSize.Level0)
{
    int buildRes1 = OH_UdmfRecord_AddArrayBuffer(nullptr, nullptr, nullptr);
    EXPECT_EQ(buildRes1, UDMF_E_INVALID_PARAM);

    OH_UdmfRecord record1;
    int buildRes2 = OH_UdmfRecord_AddArrayBuffer(&record1, nullptr, nullptr);
    EXPECT_EQ(buildRes2, UDMF_E_INVALID_PARAM);

    OH_UdmfRecord *record2 = OH_UdmfRecord_Create();
    int buildRes3 = OH_UdmfRecord_AddArrayBuffer(record2, nullptr, nullptr);
    EXPECT_EQ(buildRes3, UDMF_E_INVALID_PARAM);

    OH_UdsArrayBuffer buffer;
    int buildRes4 = OH_UdmfRecord_AddArrayBuffer(record2, nullptr, &buffer);
    EXPECT_EQ(buildRes4, UDMF_E_INVALID_PARAM);

    OH_UdsArrayBuffer *buffer2 = OH_UdsArrayBuffer_Create();
    int buildRes5 = OH_UdmfRecord_AddArrayBuffer(record2, nullptr, buffer2);
    EXPECT_EQ(buildRes5, UDMF_E_INVALID_PARAM);

    char type[] = "general.plain-text";
    int buildRes6 = OH_UdmfRecord_AddArrayBuffer(record2, type, buffer2);
    EXPECT_EQ(buildRes6, UDMF_E_INVALID_PARAM);

    char type2[] = "ApplicationDefined-myType1";
    int buildRes7 = OH_UdmfRecord_AddArrayBuffer(record2, type2, buffer2);
    EXPECT_EQ(buildRes7, UDMF_E_INVALID_PARAM);

    OH_UdmfRecord_Destroy(record2);
    OH_UdsArrayBuffer_Destroy(buffer2);
}

/**
 * @tc.name: OH_Udmf_BuildRecordByOpenHarmonyArrayBuffer002
 * @tc.desc: test OH_UdmfRecord_AddArrayBuffer with invalid param
 * @tc.type: FUNC
 */
HWTEST_F(UDMFTest, OH_Udmf_BuildRecordByOpenHarmonyArrayBuffer002, TestSize.Level0)
{
    int buildRes1 = OH_UdmfRecord_GetArrayBuffer(nullptr, nullptr, nullptr);
    EXPECT_EQ(buildRes1, UDMF_E_INVALID_PARAM);

    OH_UdmfRecord record1;
    int buildRes2 = OH_UdmfRecord_GetArrayBuffer(&record1, nullptr, nullptr);
    EXPECT_EQ(buildRes2, UDMF_E_INVALID_PARAM);

    OH_UdmfRecord *record2 = OH_UdmfRecord_Create();
    int buildRes3 = OH_UdmfRecord_GetArrayBuffer(record2, nullptr, nullptr);
    EXPECT_EQ(buildRes3, UDMF_E_INVALID_PARAM);

    OH_UdsArrayBuffer buffer;
    int buildRes4 = OH_UdmfRecord_GetArrayBuffer(record2, nullptr, &buffer);
    EXPECT_EQ(buildRes4, UDMF_E_INVALID_PARAM);

    OH_UdsArrayBuffer *buffer2 = OH_UdsArrayBuffer_Create();
    int buildRes5 = OH_UdmfRecord_GetArrayBuffer(record2, nullptr, buffer2);
    EXPECT_EQ(buildRes5, UDMF_E_INVALID_PARAM);

    char type[] = "general.plain-text";
    int buildRes6 = OH_UdmfRecord_GetArrayBuffer(record2, type, buffer2);
    EXPECT_EQ(buildRes6, UDMF_E_INVALID_PARAM);

    char type2[] = "ApplicationDefined-myType1";
    int buildRes7 = OH_UdmfRecord_GetArrayBuffer(record2, type2, buffer2);
    EXPECT_EQ(buildRes7, UDMF_E_INVALID_PARAM);

    OH_UdmfRecord_Destroy(record2);
    OH_UdsArrayBuffer_Destroy(buffer2);
}

/**
 * @tc.name: OH_Udmf_GetArrayBufferFromRecord001
 * @tc.desc: test OH_UdmfRecord_AddArrayBuffer with invalid param
 * @tc.type: FUNC
 */
HWTEST_F(UDMFTest, OH_Udmf_GetArrayBufferFromRecord001, TestSize.Level0)
{
    unsigned char data1[] = "Hello world";
    unsigned int len1 = sizeof(data1);
    OH_UdsArrayBuffer *buffer1 = OH_UdsArrayBuffer_Create();
    OH_UdsArrayBuffer_SetData(buffer1, data1, len1);

    char type1[] = "ApplicationDefined-myType1";
    OH_UdmfRecord *record1 = OH_UdmfRecord_Create();
    int buildRes = OH_UdmfRecord_AddArrayBuffer(record1, type1, buffer1);
    ASSERT_EQ(buildRes, UDMF_E_OK);

    char type2[] = "ApplicationDefined-myType2";
    OH_UdsArrayBuffer *buffer2 = OH_UdsArrayBuffer_Create();
    int getRes = OH_UdmfRecord_GetArrayBuffer(record1, type2, buffer2);
    EXPECT_EQ(getRes, UDMF_E_INVALID_PARAM);

    int getRes2 = OH_UdmfRecord_GetArrayBuffer(record1, type1, buffer2);
    ASSERT_EQ(getRes2, UDMF_E_OK);

    unsigned int getLen = 0;
    unsigned char *getData;
    int getRes3 = OH_UdsArrayBuffer_GetData(buffer2, &getData, &getLen);
    ASSERT_EQ(getRes3, UDMF_E_OK);
    ASSERT_EQ(len1, getLen);
    ASSERT_TRUE(CheckUnsignedChar(data1, getData, getLen));

    OH_UdmfRecord_Destroy(record1);
    OH_UdsArrayBuffer_Destroy(buffer1);
    OH_UdsArrayBuffer_Destroy(buffer2);
}

/**
 * @tc.name: OH_UdmfData_GetPrimaryPlainText001
 * @tc.desc: Normal testcase of OH_UdmfData_GetPrimaryPlainText
 * @tc.type: FUNC
 */
HWTEST_F(UDMFTest, OH_UdmfData_GetPrimaryPlainText001, TestSize.Level1)
{
    int result = OH_UdmfData_GetPrimaryPlainText(nullptr, nullptr);
    EXPECT_EQ(result, UDMF_E_INVALID_PARAM);

    OH_UdmfData data;
    int result2 = OH_UdmfData_GetPrimaryPlainText(&data, nullptr);
    EXPECT_EQ(result2, UDMF_E_INVALID_PARAM);

    OH_UdmfData *data2 = OH_UdmfData_Create();
    int result3 = OH_UdmfData_GetPrimaryPlainText(data2, nullptr);
    EXPECT_EQ(result3, UDMF_E_INVALID_PARAM);

    OH_UdsPlainText plainText;
    int result4 = OH_UdmfData_GetPrimaryPlainText(data2, &plainText);
    EXPECT_EQ(result4, UDMF_E_INVALID_PARAM);

    OH_UdsPlainText *plainText2 = OH_UdsPlainText_Create();
    int result5 = OH_UdmfData_GetPrimaryPlainText(data2, plainText2);
    EXPECT_EQ(result5, UDMF_ERR);

    OH_UdsPlainText_Destroy(plainText2);
    OH_UdmfData_Destroy(data2);
}

/**
 * @tc.name: OH_UdmfData_GetPrimaryPlainText002
 * @tc.desc: Normal testcase of OH_UdmfData_GetPrimaryPlainText
 * @tc.type: FUNC
 */
HWTEST_F(UDMFTest, OH_UdmfData_GetPrimaryPlainText002, TestSize.Level1)
{
    const char *helloWorld = "Hello world";

    OH_UdmfData *data = OH_UdmfData_Create();
    OH_UdsPlainText *plainTextOutput = OH_UdsPlainText_Create();
    int result = OH_UdmfData_GetPrimaryPlainText(data, plainTextOutput);
    EXPECT_EQ(result, UDMF_ERR);

    OH_UdmfData *data2 = OH_UdmfData_Create();
    OH_UdsHtml *html = OH_UdsHtml_Create();
    OH_UdsHtml_SetContent(html, "<p>Hello world</p>");
    OH_UdmfRecord *record = OH_UdmfRecord_Create();
    OH_UdmfRecord_AddHtml(record, html);
    OH_UdmfData_AddRecord(data2, record);
    int result2 = OH_UdmfData_GetPrimaryPlainText(data2, plainTextOutput);
    EXPECT_EQ(result2, UDMF_ERR);

    OH_UdmfData *data3 = OH_UdmfData_Create();
    OH_UdsPlainText *plainText = OH_UdsPlainText_Create();
    OH_UdsPlainText_SetContent(plainText, helloWorld);
    OH_UdmfRecord *record2 = OH_UdmfRecord_Create();
    OH_UdmfRecord_AddPlainText(record2, plainText);
    OH_UdmfData_AddRecord(data3, record);
    OH_UdmfData_AddRecord(data3, record2);
    int result3 = OH_UdmfData_GetPrimaryPlainText(data3, plainTextOutput);
    ASSERT_EQ(result3, UDMF_E_OK);
    auto *content = OH_UdsPlainText_GetContent(plainTextOutput);
    EXPECT_EQ(strcmp(content, helloWorld), 0);

    OH_UdsHtml_Destroy(html);
    OH_UdsPlainText_Destroy(plainTextOutput);
    OH_UdsPlainText_Destroy(plainText);
    OH_UdmfRecord_Destroy(record);
    OH_UdmfRecord_Destroy(record2);
    OH_UdmfData_Destroy(data);
    OH_UdmfData_Destroy(data2);
    OH_UdmfData_Destroy(data3);
}

/**
 * @tc.name: OH_UdmfData_GetPrimaryPlainText003
 * @tc.desc: Normal testcase of OH_UdmfData_GetPrimaryPlainText
 * @tc.type: FUNC
 */
HWTEST_F(UDMFTest, OH_UdmfData_GetPrimaryPlainText003, TestSize.Level1)
{
    const char *helloWorld = "Hello world";
    const char *helloWorld2 = "Hello world2";

    OH_UdsHtml *html = OH_UdsHtml_Create();
    OH_UdsHtml_SetContent(html, "<p>Hello world</p>");
    OH_UdmfRecord *record = OH_UdmfRecord_Create();
    OH_UdmfRecord_AddHtml(record, html);

    OH_UdsPlainText *plainText = OH_UdsPlainText_Create();
    OH_UdsPlainText_SetContent(plainText, helloWorld);
    OH_UdmfRecord *record2 = OH_UdmfRecord_Create();
    OH_UdmfRecord_AddPlainText(record2, plainText);


    OH_UdsPlainText *plainText2 = OH_UdsPlainText_Create();
    OH_UdsPlainText_SetContent(plainText2, helloWorld2);
    OH_UdmfRecord* record3 = OH_UdmfRecord_Create();
    OH_UdmfRecord_AddPlainText(record3, plainText2);

    OH_UdmfData *data = OH_UdmfData_Create();
    OH_UdmfData_AddRecord(data, record3);
    OH_UdmfData_AddRecord(data, record2);
    OH_UdmfData_AddRecord(data, record);
    OH_UdsPlainText *plainTextOutput = OH_UdsPlainText_Create();
    int result4 = OH_UdmfData_GetPrimaryPlainText(data, plainTextOutput);
    ASSERT_EQ(result4, UDMF_E_OK);
    auto *content2 = OH_UdsPlainText_GetContent(plainTextOutput);
    EXPECT_EQ(strcmp(content2, helloWorld2), 0);

    OH_UdsHtml_Destroy(html);
    OH_UdsPlainText_Destroy(plainTextOutput);
    OH_UdsPlainText_Destroy(plainText);
    OH_UdsPlainText_Destroy(plainText2);
    OH_UdmfRecord_Destroy(record);
    OH_UdmfRecord_Destroy(record2);
    OH_UdmfRecord_Destroy(record3);
    OH_UdmfData_Destroy(data);
}

/**
 * @tc.name: OH_UdmfData_GetPrimaryHtml001
 * @tc.desc: Normal testcase of OH_UdmfData_GetPrimaryHtml
 * @tc.type: FUNC
 */
HWTEST_F(UDMFTest, OH_UdmfData_GetPrimaryHtml001, TestSize.Level1)
{
    int result1 = OH_UdmfData_GetPrimaryHtml(nullptr, nullptr);
    EXPECT_EQ(result1, UDMF_E_INVALID_PARAM);

    OH_UdmfData data;
    int result2 = OH_UdmfData_GetPrimaryHtml(&data, nullptr);
    EXPECT_EQ(result2, UDMF_E_INVALID_PARAM);

    OH_UdmfData *data2 = OH_UdmfData_Create();
    int result3 = OH_UdmfData_GetPrimaryHtml(data2, nullptr);
    EXPECT_EQ(result3, UDMF_E_INVALID_PARAM);

    OH_UdsHtml html;
    int result4 = OH_UdmfData_GetPrimaryHtml(data2, &html);
    EXPECT_EQ(result4, UDMF_E_INVALID_PARAM);

    OH_UdsHtml *html2 = OH_UdsHtml_Create();
    int result5 = OH_UdmfData_GetPrimaryHtml(data2, html2);
    EXPECT_EQ(result5, UDMF_ERR);

    OH_UdsHtml_Destroy(html2);
    OH_UdmfData_Destroy(data2);
}

/**
 * @tc.name: OH_UdmfData_GetPrimaryHtml002
 * @tc.desc: Normal testcase of OH_UdmfData_GetPrimaryHtml
 * @tc.type: FUNC
 */
HWTEST_F(UDMFTest, OH_UdmfData_GetPrimaryHtml002, TestSize.Level1)
{
    const char *helloWorld = "<p>Hello world</p>";

    OH_UdmfData *data = OH_UdmfData_Create();
    OH_UdsHtml *htmlOutput = OH_UdsHtml_Create();
    int result = OH_UdmfData_GetPrimaryHtml(data, htmlOutput);
    EXPECT_EQ(result, UDMF_ERR);

    OH_UdmfData *data2 = OH_UdmfData_Create();
    OH_UdsPlainText *plainText = OH_UdsPlainText_Create();
    OH_UdsPlainText_SetContent(plainText, "Hello world");
    OH_UdmfRecord* record = OH_UdmfRecord_Create();
    OH_UdmfRecord_AddPlainText(record, plainText);
    OH_UdmfData_AddRecord(data2, record);
    int result2 = OH_UdmfData_GetPrimaryHtml(data2, htmlOutput);
    EXPECT_EQ(result2, UDMF_ERR);

    OH_UdmfData *data3 = OH_UdmfData_Create();
    OH_UdsHtml *html = OH_UdsHtml_Create();
    OH_UdsHtml_SetContent(html, helloWorld);
    OH_UdmfRecord* record2 = OH_UdmfRecord_Create();
    OH_UdmfRecord_AddHtml(record2, html);
    OH_UdmfData_AddRecord(data3, record);
    OH_UdmfData_AddRecord(data3, record2);
    int result3 = OH_UdmfData_GetPrimaryHtml(data3, htmlOutput);
    ASSERT_EQ(result3, UDMF_E_OK);
    auto content = OH_UdsHtml_GetContent(htmlOutput);
    EXPECT_EQ(strcmp(content, helloWorld), 0);

    OH_UdsHtml_Destroy(html);
    OH_UdsHtml_Destroy(htmlOutput);
    OH_UdsPlainText_Destroy(plainText);
    OH_UdmfRecord_Destroy(record);
    OH_UdmfRecord_Destroy(record2);
    OH_UdmfData_Destroy(data);
    OH_UdmfData_Destroy(data2);
    OH_UdmfData_Destroy(data3);
}

/**
 * @tc.name: OH_UdmfData_GetPrimaryHtml003
 * @tc.desc: Normal testcase of OH_UdmfData_GetPrimaryHtml
 * @tc.type: FUNC
 */
HWTEST_F(UDMFTest, OH_UdmfData_GetPrimaryHtml003, TestSize.Level1)
{
    const char *helloWorld = "<p>Hello world</p>";
    const char *helloWorld2 = "<p>Hello world2</p>";

    OH_UdsPlainText *plainText = OH_UdsPlainText_Create();
    OH_UdsPlainText_SetContent(plainText, "Hello world");
    OH_UdmfRecord* record = OH_UdmfRecord_Create();
    OH_UdmfRecord_AddPlainText(record, plainText);

    OH_UdsHtml *html = OH_UdsHtml_Create();
    OH_UdsHtml_SetContent(html, helloWorld);
    OH_UdmfRecord* record2 = OH_UdmfRecord_Create();
    OH_UdmfRecord_AddHtml(record2, html);

    OH_UdsHtml *html2 = OH_UdsHtml_Create();
    OH_UdsHtml_SetContent(html2, helloWorld2);
    OH_UdmfRecord* record3 = OH_UdmfRecord_Create();
    OH_UdmfRecord_AddHtml(record3, html2);

    OH_UdmfData *data = OH_UdmfData_Create();
    OH_UdmfData_AddRecord(data, record3);
    OH_UdmfData_AddRecord(data, record2);
    OH_UdmfData_AddRecord(data, record);
    OH_UdsHtml *htmlOutput = OH_UdsHtml_Create();
    int result4 = OH_UdmfData_GetPrimaryHtml(data, htmlOutput);
    ASSERT_EQ(result4, UDMF_E_OK);
    auto content2 = OH_UdsHtml_GetContent(htmlOutput);
    EXPECT_EQ(strcmp(content2, helloWorld2), 0);

    OH_UdsHtml_Destroy(html);
    OH_UdsHtml_Destroy(html2);
    OH_UdsHtml_Destroy(htmlOutput);
    OH_UdsPlainText_Destroy(plainText);
    OH_UdmfRecord_Destroy(record);
    OH_UdmfRecord_Destroy(record2);
    OH_UdmfRecord_Destroy(record3);
    OH_UdmfData_Destroy(data);
}

/**
 * @tc.name: OH_UdmfData_GetRecordCount001
 * @tc.desc: Normal testcase of OH_UdmfData_GetRecordCount
 * @tc.type: FUNC
 */
HWTEST_F(UDMFTest, OH_UdmfData_GetRecordCount001, TestSize.Level1)
{
    int result = OH_UdmfData_GetRecordCount(nullptr);
    EXPECT_EQ(result, 0);

    OH_UdmfData data;
    int result2 = OH_UdmfData_GetRecordCount(&data);
    EXPECT_EQ(result2, 0);

    OH_UdmfData *data2 = OH_UdmfData_Create();
    int result3 = OH_UdmfData_GetRecordCount(data2);
    EXPECT_EQ(result3, 0);

    OH_UdmfData *data3 = OH_UdmfData_Create();
    OH_UdmfRecord *record = OH_UdmfRecord_Create();
    OH_UdmfData_AddRecord(data3, record);
    int result4 = OH_UdmfData_GetRecordCount(data3);
    EXPECT_EQ(result4, 1);

    OH_UdmfData *data4 = OH_UdmfData_Create();
    OH_UdmfRecord *record2 = OH_UdmfRecord_Create();
    OH_UdmfData_AddRecord(data4, record);
    OH_UdmfData_AddRecord(data4, record2);
    int result5 = OH_UdmfData_GetRecordCount(data4);
    EXPECT_EQ(result5, 2);

    OH_UdmfRecord_Destroy(record);
    OH_UdmfRecord_Destroy(record2);
    OH_UdmfData_Destroy(data2);
    OH_UdmfData_Destroy(data3);
    OH_UdmfData_Destroy(data4);
}

/**
 * @tc.name: OH_UdmfData_GetRecord001
 * @tc.desc: Normal testcase of OH_UdmfData_GetRecord
 * @tc.type: FUNC
 */
HWTEST_F(UDMFTest, OH_UdmfData_GetRecord001, TestSize.Level1)
{
    OH_UdmfRecord *result = OH_UdmfData_GetRecord(nullptr, -1);
    EXPECT_EQ(result, nullptr);

    OH_UdmfData data;
    OH_UdmfRecord *result2 = OH_UdmfData_GetRecord(&data, -1);
    EXPECT_EQ(result2, nullptr);

    OH_UdmfRecord *result3 = OH_UdmfData_GetRecord(&data, 0);
    EXPECT_EQ(result3, nullptr);

    OH_UdmfData *data2 = OH_UdmfData_Create();
    OH_UdmfRecord *result4 = OH_UdmfData_GetRecord(data2, -1);
    EXPECT_EQ(result4, nullptr);

    OH_UdmfRecord *result5 = OH_UdmfData_GetRecord(data2, 0);
    EXPECT_EQ(result5, nullptr);

    OH_UdmfRecord *result6 = OH_UdmfData_GetRecord(data2, 1);
    EXPECT_EQ(result6, nullptr);

    OH_UdmfData *data3 = OH_UdmfData_Create();
    OH_UdmfRecord* record = OH_UdmfRecord_Create();
    OH_UdmfData_AddRecord(data3, record);
    EXPECT_EQ(OH_UdmfData_GetRecordCount(data3), 1);
    OH_UdmfRecord *result7 = OH_UdmfData_GetRecord(data3, -1);
    EXPECT_EQ(result7, nullptr);
    OH_UdmfRecord *result8 = OH_UdmfData_GetRecord(data3, 1);
    EXPECT_EQ(result8, nullptr);
    OH_UdmfRecord *result9 = OH_UdmfData_GetRecord(data3, 0);
    EXPECT_NE(result9, nullptr);

    OH_UdmfRecord_Destroy(record);
    OH_UdmfData_Destroy(data2);
    OH_UdmfData_Destroy(data3);
}

/**
 * @tc.name: OH_UdmfData_GetRecord002
 * @tc.desc: Normal testcase of OH_UdmfData_GetRecord
 * @tc.type: FUNC
 */
HWTEST_F(UDMFTest, OH_UdmfData_GetRecord002, TestSize.Level1)
{
    const char *helloWorld = "Hello world";
    const char *helloWorld2 = "Hello world2";

    OH_UdmfData *data3 = OH_UdmfData_Create();
    OH_UdsPlainText *plainText = OH_UdsPlainText_Create();
    OH_UdsPlainText_SetContent(plainText, helloWorld);
    OH_UdmfRecord* record = OH_UdmfRecord_Create();
    OH_UdmfRecord_AddPlainText(record, plainText);
    OH_UdmfData_AddRecord(data3, record);
    OH_UdmfRecord *result9 = OH_UdmfData_GetRecord(data3, 0);
    EXPECT_NE(result9, nullptr);
    OH_UdsPlainText *plainText2 = OH_UdsPlainText_Create();
    OH_UdmfRecord_GetPlainText(result9, plainText2);
    auto content = OH_UdsPlainText_GetContent(plainText2);
    EXPECT_EQ(strcmp(content, helloWorld), 0);

    OH_UdmfData *data4 = OH_UdmfData_Create();
    OH_UdsPlainText *plainText3 = OH_UdsPlainText_Create();
    OH_UdsPlainText_SetContent(plainText3, helloWorld2);
    OH_UdmfRecord* record2 = OH_UdmfRecord_Create();
    OH_UdmfRecord_AddPlainText(record2, plainText3);
    OH_UdmfData_AddRecord(data4, record);
    OH_UdmfData_AddRecord(data4, record2);
    OH_UdmfRecord *result10 = OH_UdmfData_GetRecord(data4, -1);
    EXPECT_EQ(result10, nullptr);
    OH_UdmfRecord *result11 = OH_UdmfData_GetRecord(data4, 2);
    EXPECT_EQ(result11, nullptr);
    OH_UdmfRecord *result12 = OH_UdmfData_GetRecord(data4, 0);
    ASSERT_NE(result12, nullptr);
    OH_UdsPlainText *plainText4 = OH_UdsPlainText_Create();
    OH_UdmfRecord_GetPlainText(result12, plainText4);
    auto content2 = OH_UdsPlainText_GetContent(plainText4);
    EXPECT_EQ(strcmp(content2, helloWorld), 0);
    OH_UdmfRecord *result13 = OH_UdmfData_GetRecord(data4, 1);
    ASSERT_NE(result13, nullptr);
    OH_UdsPlainText *plainText5 = OH_UdsPlainText_Create();
    OH_UdmfRecord_GetPlainText(result13, plainText5);
    auto content3 = OH_UdsPlainText_GetContent(plainText5);
    EXPECT_EQ(strcmp(content3, helloWorld2), 0);

    OH_UdsPlainText_Destroy(plainText);
    OH_UdsPlainText_Destroy(plainText2);
    OH_UdmfRecord_Destroy(record);
    OH_UdmfRecord_Destroy(record2);
    OH_UdmfData_Destroy(data3);
    OH_UdmfData_Destroy(data4);
}

/**
 * @tc.name: OH_UdmfData_IsLocal001
 * @tc.desc: Normal testcase of OH_UdmfData_IsLocal
 * @tc.type: FUNC
 */
HWTEST_F(UDMFTest, OH_UdmfData_IsLocal001, TestSize.Level1)
{
    bool result = OH_UdmfData_IsLocal(nullptr);
    EXPECT_EQ(result, true);

    OH_UdmfData data;
    bool result2 = OH_UdmfData_IsLocal(&data);
    EXPECT_EQ(result2, true);

    OH_UdmfData *data2 = OH_UdmfData_Create();
    bool result3 = OH_UdmfData_IsLocal(data2);
    EXPECT_EQ(result3, true);

    OH_UdmfData_Destroy(data2);
}

/**
 * @tc.name: FileUriTest001
 * @tc.desc: test fileUri between js and capi
 * @tc.type: FUNC
 */
HWTEST_F(UDMFTest, FileUriTest001, TestSize.Level1)
{
    std::string uri = "https://xxx/xx/xx.jpg";
    std::shared_ptr<Image> image = std::make_shared<Image>();
    image->SetUri(uri);
    std::shared_ptr<UnifiedData> unifiedData = std::make_shared<UnifiedData>();
    unifiedData->AddRecord(image);
    std::string key;
    CustomOption option = {
        .intention = UD_INTENTION_DRAG
    };
    int setRet = UdmfClient::GetInstance().SetData(option, *unifiedData, key);
    EXPECT_EQ(setRet, E_OK);

    OH_UdmfData* udmfData = OH_UdmfData_Create();
    OH_Udmf_GetUnifiedData(key.c_str(), UDMF_INTENTION_DRAG, udmfData);

    unsigned int dataTypeCount;
    char** dataTypes = OH_UdmfData_GetTypes(udmfData, &dataTypeCount);
    EXPECT_EQ(dataTypeCount, 2);
    EXPECT_NE(dataTypes, nullptr);
    EXPECT_EQ(strcmp(dataTypes[0], UDMF_META_IMAGE), 0);
    EXPECT_EQ(strcmp(dataTypes[1], UDMF_META_GENERAL_FILE_URI), 0);

    unsigned int recordCount;
    OH_UdmfRecord** records = OH_UdmfData_GetRecords(udmfData, &recordCount);
    EXPECT_EQ(recordCount, 1);
    EXPECT_NE(records, nullptr);

    for (unsigned int idx = 0; idx < recordCount; ++idx) {
        unsigned int recordTypeCount;
        char** recordTypes = OH_UdmfRecord_GetTypes(records[idx], &recordTypeCount);
        EXPECT_EQ(recordTypeCount, 1);
        EXPECT_NE(recordTypes, nullptr);
        EXPECT_EQ(strcmp(recordTypes[0], UDMF_META_GENERAL_FILE_URI), 0);
        for (unsigned int recordIdx = 0; recordIdx < recordTypeCount; ++recordIdx) {
            if (strcmp(recordTypes[recordIdx], UDMF_META_GENERAL_FILE_URI) == 0) {
                OH_UdsFileUri* fileUri = OH_UdsFileUri_Create();
                int getFileUriRet = OH_UdmfRecord_GetFileUri(records[idx], fileUri);
                EXPECT_EQ(getFileUriRet, UDMF_E_OK);
                const char* getFileUri = OH_UdsFileUri_GetFileUri(fileUri);
                EXPECT_EQ(strcmp(getFileUri, uri.c_str()), 0);
            }
        }
    }
}

/**
 * @tc.name: FileUriTest002
 * @tc.desc: test fileUri between js and capi
 * @tc.type: FUNC
 */
HWTEST_F(UDMFTest, FileUriTest002, TestSize.Level1)
{
    std::string uri = "https://xxx/xx/xx.jpg";
    std::string content = "content";
    std::shared_ptr<Image> image = std::make_shared<Image>();
    image->SetUri(uri);
    std::shared_ptr<PlainText> plaintext = std::make_shared<PlainText>();
    plaintext->SetContent(content);
    std::shared_ptr<UnifiedData> unifiedData = std::make_shared<UnifiedData>();
    unifiedData->AddRecord(image);
    unifiedData->AddRecord(plaintext);
    std::string key;
    CustomOption option = {
        .intention = UD_INTENTION_DRAG
    };
    int setRet = UdmfClient::GetInstance().SetData(option, *unifiedData, key);
    EXPECT_EQ(setRet, E_OK);

    OH_UdmfData* udmfData = OH_UdmfData_Create();
    OH_Udmf_GetUnifiedData(key.c_str(), UDMF_INTENTION_DRAG, udmfData);

    unsigned int dataTypeCount;
    char** dataTypes = OH_UdmfData_GetTypes(udmfData, &dataTypeCount);
    EXPECT_EQ(dataTypeCount, 3);
    EXPECT_NE(dataTypes, nullptr);
    EXPECT_EQ(strcmp(dataTypes[0], UDMF_META_IMAGE), 0);
    EXPECT_EQ(strcmp(dataTypes[1], UDMF_META_PLAIN_TEXT), 0);
    EXPECT_EQ(strcmp(dataTypes[2], UDMF_META_GENERAL_FILE_URI), 0);

    unsigned int recordCount;
    OH_UdmfRecord** records = OH_UdmfData_GetRecords(udmfData, &recordCount);
    EXPECT_EQ(recordCount, 2);
    EXPECT_NE(records, nullptr);

    unsigned int recordTypeCount;
    char** recordTypes = OH_UdmfRecord_GetTypes(records[0], &recordTypeCount);
    EXPECT_EQ(strcmp(recordTypes[0], UDMF_META_GENERAL_FILE_URI), 0);
    EXPECT_EQ(recordTypeCount, 1);
    OH_UdsFileUri* fileUri = OH_UdsFileUri_Create();
    int getFileUriRet = OH_UdmfRecord_GetFileUri(records[0], fileUri);
    EXPECT_EQ(getFileUriRet, UDMF_E_OK);
    const char* getFileUri = OH_UdsFileUri_GetFileUri(fileUri);
    EXPECT_EQ(strcmp(getFileUri, uri.c_str()), 0);

    recordTypes = OH_UdmfRecord_GetTypes(records[1], &recordTypeCount);
    EXPECT_EQ(strcmp(recordTypes[0], UDMF_META_PLAIN_TEXT), 0);
    EXPECT_EQ(recordTypeCount, 1);
    OH_UdsPlainText* text = OH_UdsPlainText_Create();
    int getPlaintextRet = OH_UdmfRecord_GetPlainText(records[1], text);
    EXPECT_EQ(getPlaintextRet, UDMF_E_OK);
    const char* getContent = OH_UdsPlainText_GetContent(text);
    EXPECT_EQ(strcmp(getContent, content.c_str()), 0);
}

/**
 * @tc.name: FileUriTest003
 * @tc.desc: test fileUri between js and capi
 * @tc.type: FUNC
 */
HWTEST_F(UDMFTest, FileUriTest003, TestSize.Level1)
{
    std::string uri = "https://xxx/xx/xx.jpg";
    std::shared_ptr<Audio> audio = std::make_shared<Audio>();
    audio->SetUri(uri);
    std::shared_ptr<UnifiedData> unifiedData = std::make_shared<UnifiedData>();
    unifiedData->AddRecord(audio);
    std::string key;
    CustomOption option = {
        .intention = UD_INTENTION_DRAG
    };
    int setRet = UdmfClient::GetInstance().SetData(option, *unifiedData, key);
    EXPECT_EQ(setRet, E_OK);

    OH_UdmfData* udmfData = OH_UdmfData_Create();
    OH_Udmf_GetUnifiedData(key.c_str(), UDMF_INTENTION_DRAG, udmfData);

    unsigned int dataTypeCount;
    char** dataTypes = OH_UdmfData_GetTypes(udmfData, &dataTypeCount);
    EXPECT_EQ(dataTypeCount, 2);
    EXPECT_NE(dataTypes, nullptr);
    EXPECT_EQ(strcmp(dataTypes[0], UDMF_META_AUDIO), 0);
    EXPECT_EQ(strcmp(dataTypes[1], UDMF_META_GENERAL_FILE_URI), 0);

    unsigned int recordCount;
    OH_UdmfRecord** records = OH_UdmfData_GetRecords(udmfData, &recordCount);
    EXPECT_EQ(recordCount, 1);
    EXPECT_NE(records, nullptr);

    for (unsigned int idx = 0; idx < recordCount; ++idx) {
        unsigned int recordTypeCount;
        char** recordTypes = OH_UdmfRecord_GetTypes(records[idx], &recordTypeCount);
        EXPECT_EQ(recordTypeCount, 1);
        EXPECT_NE(recordTypes, nullptr);
        EXPECT_EQ(strcmp(recordTypes[0], UDMF_META_GENERAL_FILE_URI), 0);
        for (unsigned int recordIdx = 0; recordIdx < recordTypeCount; ++recordIdx) {
            if (strcmp(recordTypes[recordIdx], UDMF_META_GENERAL_FILE_URI) == 0) {
                OH_UdsFileUri* fileUri = OH_UdsFileUri_Create();
                int getFileUriRet = OH_UdmfRecord_GetFileUri(records[idx], fileUri);
                EXPECT_EQ(getFileUriRet, UDMF_E_OK);
                const char* getFileUri = OH_UdsFileUri_GetFileUri(fileUri);
                EXPECT_EQ(strcmp(getFileUri, uri.c_str()), 0);
            }
        }
    }
}

/**
 * @tc.name: FileUriTest004
 * @tc.desc: test fileUri between js and capi
 * @tc.type: FUNC
 */
HWTEST_F(UDMFTest, FileUriTest004, TestSize.Level1)
{
    std::string uri = "https://xxx/xx/xx.jpg";
    std::shared_ptr<File> file = std::make_shared<File>();
    file->SetUri(uri);
    std::shared_ptr<UnifiedData> unifiedData = std::make_shared<UnifiedData>();
    unifiedData->AddRecord(file);
    std::string key;
    CustomOption option = {
        .intention = UD_INTENTION_DRAG
    };
    int setRet = UdmfClient::GetInstance().SetData(option, *unifiedData, key);
    EXPECT_EQ(setRet, E_OK);

    OH_UdmfData* udmfData = OH_UdmfData_Create();
    OH_Udmf_GetUnifiedData(key.c_str(), UDMF_INTENTION_DRAG, udmfData);

    unsigned int dataTypeCount;
    char** dataTypes = OH_UdmfData_GetTypes(udmfData, &dataTypeCount);
    EXPECT_EQ(dataTypeCount, 2);
    EXPECT_NE(dataTypes, nullptr);
    EXPECT_EQ(strcmp(dataTypes[0], UDMF_META_GENERAL_FILE), 0);
    EXPECT_EQ(strcmp(dataTypes[1], UDMF_META_GENERAL_FILE_URI), 0);

    unsigned int recordCount;
    OH_UdmfRecord** records = OH_UdmfData_GetRecords(udmfData, &recordCount);
    EXPECT_EQ(recordCount, 1);
    EXPECT_NE(records, nullptr);

    for (unsigned int idx = 0; idx < recordCount; ++idx) {
        unsigned int recordTypeCount;
        char** recordTypes = OH_UdmfRecord_GetTypes(records[idx], &recordTypeCount);
        EXPECT_EQ(recordTypeCount, 1);
        EXPECT_NE(recordTypes, nullptr);
        EXPECT_EQ(strcmp(recordTypes[0], UDMF_META_GENERAL_FILE_URI), 0);
        for (unsigned int recordIdx = 0; recordIdx < recordTypeCount; ++recordIdx) {
            if (strcmp(recordTypes[recordIdx], UDMF_META_GENERAL_FILE_URI) == 0) {
                OH_UdsFileUri* fileUri = OH_UdsFileUri_Create();
                int getFileUriRet = OH_UdmfRecord_GetFileUri(records[idx], fileUri);
                EXPECT_EQ(getFileUriRet, UDMF_E_OK);
                const char* getFileUri = OH_UdsFileUri_GetFileUri(fileUri);
                EXPECT_EQ(strcmp(getFileUri, uri.c_str()), 0);
            }
        }
    }
}

/**
 * @tc.name: FileUriTest005
 * @tc.desc: test fileUri between js and capi
 * @tc.type: FUNC
 */
HWTEST_F(UDMFTest, FileUriTest005, TestSize.Level1)
{
    std::string uri = "https://xxx/xx/xx.jpg";
    std::shared_ptr<Object> obj = std::make_shared<Object>();
    obj->value_[UNIFORM_DATA_TYPE] = "general.file-uri";
    obj->value_[FILE_URI_PARAM] = uri;
    obj->value_[FILE_TYPE] = "general.img";
    auto record = std::make_shared<UnifiedRecord>(UDType::FOLDER, obj);
    std::shared_ptr<UnifiedData> unifiedData = std::make_shared<UnifiedData>();
    unifiedData->AddRecord(record);
    std::string key;
    CustomOption option = {
        .intention = UD_INTENTION_DRAG
    };
    int setRet = UdmfClient::GetInstance().SetData(option, *unifiedData, key);
    EXPECT_EQ(setRet, E_OK);

    OH_UdmfData* udmfData = OH_UdmfData_Create();
    OH_Udmf_GetUnifiedData(key.c_str(), UDMF_INTENTION_DRAG, udmfData);

    unsigned int dataTypeCount;
    char** dataTypes = OH_UdmfData_GetTypes(udmfData, &dataTypeCount);
    EXPECT_EQ(dataTypeCount, 2);
    EXPECT_NE(dataTypes, nullptr);
    EXPECT_EQ(strcmp(dataTypes[0], UDMF_META_FOLDER), 0);
    EXPECT_EQ(strcmp(dataTypes[1], UDMF_META_GENERAL_FILE_URI), 0);

    unsigned int recordCount;
    OH_UdmfRecord** records = OH_UdmfData_GetRecords(udmfData, &recordCount);
    EXPECT_EQ(recordCount, 1);
    EXPECT_NE(records, nullptr);

    for (unsigned int idx = 0; idx < recordCount; ++idx) {
        unsigned int recordTypeCount;
        char** recordTypes = OH_UdmfRecord_GetTypes(records[idx], &recordTypeCount); 
        EXPECT_EQ(recordTypeCount, 2);
        EXPECT_NE(recordTypes, nullptr);
        EXPECT_EQ(strcmp(recordTypes[0], UDMF_META_FOLDER), 0);
        EXPECT_EQ(strcmp(recordTypes[1], UDMF_META_GENERAL_FILE_URI), 0);
        for (unsigned int recordIdx = 0; recordIdx < recordTypeCount; ++recordIdx) {
            if (strcmp(recordTypes[recordIdx], UDMF_META_GENERAL_FILE_URI) == 0) {
                OH_UdsFileUri* fileUri = OH_UdsFileUri_Create();
                int getFileUriRet = OH_UdmfRecord_GetFileUri(records[idx], fileUri);
                EXPECT_EQ(getFileUriRet, UDMF_E_OK);
                const char* getFileUri = OH_UdsFileUri_GetFileUri(fileUri);
                EXPECT_EQ(strcmp(getFileUri, uri.c_str()), 0);
            }
        }
    }
}

/**
 * @tc.name: FileUriTest006
 * @tc.desc: test fileUri between js and capi
 * @tc.type: FUNC
 */
HWTEST_F(UDMFTest, FileUriTest006, TestSize.Level1)
{
    std::string uri = "https://xxx/xx/xx.jpg";
    std::shared_ptr<Video> video = std::make_shared<Video>();
    video->SetUri(uri);
    std::shared_ptr<UnifiedData> unifiedData = std::make_shared<UnifiedData>();
    unifiedData->AddRecord(video);
    std::string key;
    CustomOption option = {
        .intention = UD_INTENTION_DRAG
    };
    int setRet = UdmfClient::GetInstance().SetData(option, *unifiedData, key);
    EXPECT_EQ(setRet, E_OK);

    OH_UdmfData* udmfData = OH_UdmfData_Create();
    OH_Udmf_GetUnifiedData(key.c_str(), UDMF_INTENTION_DRAG, udmfData);

    unsigned int dataTypeCount;
    char** dataTypes = OH_UdmfData_GetTypes(udmfData, &dataTypeCount);
    EXPECT_EQ(dataTypeCount, 2);
    EXPECT_NE(dataTypes, nullptr);
    EXPECT_EQ(strcmp(dataTypes[0], UDMF_META_VIDEO), 0);
    EXPECT_EQ(strcmp(dataTypes[1], UDMF_META_GENERAL_FILE_URI), 0);

    unsigned int recordCount;
    OH_UdmfRecord** records = OH_UdmfData_GetRecords(udmfData, &recordCount);
    EXPECT_EQ(recordCount, 1);
    EXPECT_NE(records, nullptr);

    for (unsigned int idx = 0; idx < recordCount; ++idx) {
        unsigned int recordTypeCount;
        char** recordTypes = OH_UdmfRecord_GetTypes(records[idx], &recordTypeCount);
        EXPECT_EQ(recordTypeCount, 1);
        EXPECT_NE(recordTypes, nullptr);
        EXPECT_EQ(strcmp(recordTypes[0], UDMF_META_GENERAL_FILE_URI), 0);
        for (unsigned int recordIdx = 0; recordIdx < recordTypeCount; ++recordIdx) {
            if (strcmp(recordTypes[recordIdx], UDMF_META_GENERAL_FILE_URI) == 0) {
                OH_UdsFileUri* fileUri = OH_UdsFileUri_Create();
                int getFileUriRet = OH_UdmfRecord_GetFileUri(records[idx], fileUri);
                EXPECT_EQ(getFileUriRet, UDMF_E_OK);
                const char* getFileUri = OH_UdsFileUri_GetFileUri(fileUri);
                EXPECT_EQ(strcmp(getFileUri, uri.c_str()), 0);
            }
        }
    }
}

/**
 * @tc.name: FileUriTest007
 * @tc.desc: test fileUri between js and capi
 * @tc.type: FUNC
 */
HWTEST_F(UDMFTest, FileUriTest007, TestSize.Level1)
{
    std::string uri = "https://xxx/xx/xx.jpg";

    std::shared_ptr<Object> obj = std::make_shared<Object>();
    obj->value_[UNIFORM_DATA_TYPE] = "general.file-uri";
    obj->value_[FILE_URI_PARAM] = uri;
    obj->value_[FILE_TYPE] = "general.img";
    auto record = std::make_shared<UnifiedRecord>(UDType::VIDEO, obj);
    std::shared_ptr<UnifiedData> unifiedData = std::make_shared<UnifiedData>();
    unifiedData->AddRecord(record);
    std::string key;
    CustomOption option = {
        .intention = UD_INTENTION_DRAG
    };
    int setRet = UdmfClient::GetInstance().SetData(option, *unifiedData, key);
    EXPECT_EQ(setRet, E_OK);

    OH_UdmfData* udmfData = OH_UdmfData_Create();
    OH_Udmf_GetUnifiedData(key.c_str(), UDMF_INTENTION_DRAG, udmfData);

    unsigned int dataTypeCount;
    char** dataTypes = OH_UdmfData_GetTypes(udmfData, &dataTypeCount);
    EXPECT_EQ(dataTypeCount, 2);
    EXPECT_NE(dataTypes, nullptr);
    EXPECT_EQ(strcmp(dataTypes[0], UDMF_META_VIDEO), 0);
    EXPECT_EQ(strcmp(dataTypes[1], UDMF_META_GENERAL_FILE_URI), 0);

    unsigned int recordCount;
    OH_UdmfRecord** records = OH_UdmfData_GetRecords(udmfData, &recordCount);
    EXPECT_EQ(recordCount, 1);
    EXPECT_NE(records, nullptr);

    for (unsigned int idx = 0; idx < recordCount; ++idx) {
        unsigned int recordTypeCount;
        char** recordTypes = OH_UdmfRecord_GetTypes(records[idx], &recordTypeCount);
        EXPECT_EQ(recordTypeCount, 2);
        EXPECT_NE(recordTypes, nullptr);
        EXPECT_EQ(strcmp(recordTypes[0], UDMF_META_VIDEO), 0);
        EXPECT_EQ(strcmp(recordTypes[1], UDMF_META_GENERAL_FILE_URI), 0);
        for (unsigned int recordIdx = 0; recordIdx < recordTypeCount; ++recordIdx) {
            if (strcmp(recordTypes[recordIdx], UDMF_META_GENERAL_FILE_URI) == 0) {
                OH_UdsFileUri* fileUri = OH_UdsFileUri_Create();
                int getFileUriRet = OH_UdmfRecord_GetFileUri(records[idx], fileUri);
                EXPECT_EQ(getFileUriRet, UDMF_E_OK);
                const char* getFileUri = OH_UdsFileUri_GetFileUri(fileUri);
                EXPECT_EQ(strcmp(getFileUri, uri.c_str()), 0);
            }
        }
    }
}

/**
 * @tc.name: OH_Udmf_SetAndGetUnifiedData003
 * @tc.desc: OH_Udmf_SetUnifiedData and OH_Udmf_GetUnifiedData with file uri
 * @tc.type: FUNC
 * @tc.require: AROOOH5R5G
 */
HWTEST_F(UDMFTest, OH_Udmf_SetAndGetUnifiedData003, TestSize.Level1)
{
    std::string uri = "https://xxx/xx/xx.jpg";
    OH_UdmfData *udmfUnifiedData = OH_UdmfData_Create();
    OH_UdmfRecord *record = OH_UdmfRecord_Create();
    OH_UdsFileUri *fileUri = OH_UdsFileUri_Create();
    OH_UdsFileUri_SetFileUri(fileUri, uri.c_str());
    OH_UdsFileUri_SetFileType(fileUri, UDMF_META_IMAGE);
    OH_UdmfRecord_AddFileUri(record, fileUri);
    OH_UdmfData_AddRecord(udmfUnifiedData, record);
    Udmf_Intention intention = UDMF_INTENTION_DRAG;
    char key[UDMF_KEY_BUFFER_LEN];

    int setRes = OH_Udmf_SetUnifiedData(intention, udmfUnifiedData, key, UDMF_KEY_BUFFER_LEN);
    EXPECT_EQ(setRes, UDMF_E_OK);
    EXPECT_NE(key[0], '\0');
    OH_UdmfData *readUnifiedData = OH_UdmfData_Create();
    int getRes = OH_Udmf_GetUnifiedData(key, intention, readUnifiedData);
    EXPECT_EQ(getRes, UDMF_E_OK);
    unsigned int count = 0;
    OH_UdmfRecord **getRecords = OH_UdmfData_GetRecords(readUnifiedData, &count);
    EXPECT_EQ(count, 1);
    OH_UdsFileUri *getFileUri = OH_UdsFileUri_Create();
    OH_UdmfRecord_GetFileUri(getRecords[0], getFileUri);
    const char *getUri = OH_UdsFileUri_GetFileUri(getFileUri);
    EXPECT_EQ(strcmp(getUri, uri.c_str()), 0);

    OH_UdsFileUri_Destroy(fileUri);
    OH_UdmfRecord_Destroy(record);
    OH_UdmfData_Destroy(udmfUnifiedData);

    OH_UdsFileUri_Destroy(getFileUri);
    OH_UdmfData_Destroy(readUnifiedData);
}

/**
 * @tc.name: OH_Udmf_SetAndGetUnifiedData004
 * @tc.desc: OH_Udmf_SetUnifiedData and OH_Udmf_GetUnifiedData with file uri
 * @tc.type: FUNC
 * @tc.require: AROOOH5R5G
 */
HWTEST_F(UDMFTest, OH_Udmf_SetAndGetUnifiedData004, TestSize.Level1)
{
    std::string uri = "https://xxx/xx/xx.jpg";
    OH_UdmfData *udmfUnifiedData = OH_UdmfData_Create();
    OH_UdmfRecord *record = OH_UdmfRecord_Create();
    OH_UdsFileUri *fileUri = OH_UdsFileUri_Create();
    OH_UdsFileUri_SetFileUri(fileUri, uri.c_str());
    OH_UdmfRecord_AddFileUri(record, fileUri);
    OH_UdmfData_AddRecord(udmfUnifiedData, record);
    Udmf_Intention intention = UDMF_INTENTION_DRAG;
    char key[UDMF_KEY_BUFFER_LEN];

    int setRes = OH_Udmf_SetUnifiedData(intention, udmfUnifiedData, key, UDMF_KEY_BUFFER_LEN);
    EXPECT_EQ(setRes, UDMF_E_OK);
    EXPECT_NE(key[0], '\0');
    OH_UdmfData *readUnifiedData = OH_UdmfData_Create();
    int getRes = OH_Udmf_GetUnifiedData(key, intention, readUnifiedData);
    EXPECT_EQ(getRes, UDMF_E_OK);
    unsigned int count = 0;
    OH_UdmfRecord **getRecords = OH_UdmfData_GetRecords(readUnifiedData, &count);
    EXPECT_EQ(count, 1);
    OH_UdsFileUri *getFileUri = OH_UdsFileUri_Create();
    OH_UdmfRecord_GetFileUri(getRecords[0], getFileUri);
    const char *getUri = OH_UdsFileUri_GetFileUri(getFileUri);
    EXPECT_EQ(strcmp(getUri, uri.c_str()), 0);

    OH_UdsFileUri_Destroy(fileUri);
    OH_UdmfRecord_Destroy(record);
    OH_UdmfData_Destroy(udmfUnifiedData);

    OH_UdsFileUri_Destroy(getFileUri);
    OH_UdmfData_Destroy(readUnifiedData);
}

/**
 * @tc.name: OH_Udmf_SetAndGetUnifiedData005
 * @tc.desc: OH_Udmf_SetUnifiedData and OH_Udmf_GetUnifiedData with file uri
 * @tc.type: FUNC
 * @tc.require: AROOOH5R5G
 */
HWTEST_F(UDMFTest, OH_Udmf_SetAndGetUnifiedData005, TestSize.Level1)
{
    std::string uri = "https://xxx/xx/xx.jpg";
    OH_UdmfData *udmfUnifiedData = OH_UdmfData_Create();
    OH_UdmfRecord *record = OH_UdmfRecord_Create();
    OH_UdsFileUri *fileUri = OH_UdsFileUri_Create();
    OH_UdsFileUri_SetFileUri(fileUri, uri.c_str());
    OH_UdsFileUri_SetFileType(fileUri, UDMF_META_FOLDER);
    OH_UdmfRecord_AddFileUri(record, fileUri);
    OH_UdmfData_AddRecord(udmfUnifiedData, record);
    Udmf_Intention intention = UDMF_INTENTION_DRAG;
    char key[UDMF_KEY_BUFFER_LEN];

    int setRes = OH_Udmf_SetUnifiedData(intention, udmfUnifiedData, key, UDMF_KEY_BUFFER_LEN);
    EXPECT_EQ(setRes, UDMF_E_OK);
    EXPECT_NE(key[0], '\0');
    OH_UdmfData *readUnifiedData = OH_UdmfData_Create();
    int getRes = OH_Udmf_GetUnifiedData(key, intention, readUnifiedData);
    EXPECT_EQ(getRes, UDMF_E_OK);
    unsigned int count = 0;
    OH_UdmfRecord **getRecords = OH_UdmfData_GetRecords(readUnifiedData, &count);
    EXPECT_EQ(count, 1);
    OH_UdsFileUri *getFileUri = OH_UdsFileUri_Create();
    OH_UdmfRecord_GetFileUri(getRecords[0], getFileUri);
    const char *getUri = OH_UdsFileUri_GetFileUri(getFileUri);
    EXPECT_EQ(strcmp(getUri, uri.c_str()), 0);

    OH_UdsFileUri_Destroy(fileUri);
    OH_UdmfRecord_Destroy(record);
    OH_UdmfData_Destroy(udmfUnifiedData);

    OH_UdsFileUri_Destroy(getFileUri);
    OH_UdmfData_Destroy(readUnifiedData);
}

/**
 * @tc.name: OH_Udmf_SetAndGetUnifiedData006
 * @tc.desc: OH_Udmf_SetUnifiedData and OH_Udmf_GetUnifiedData with content form
 * @tc.type: FUNC
 */
HWTEST_F(UDMFTest, OH_Udmf_SetAndGetUnifiedData006, TestSize.Level1)
{
    OH_UdmfData *udmfUnifiedData = OH_UdmfData_Create();
    OH_UdmfRecord *record = OH_UdmfRecord_Create();
    OH_UdsContentForm *contentForm = OH_UdsContentForm_Create();
    unsigned char thumbData[] = {0, 1, 2, 3, 4};
    OH_UdsContentForm_SetThumbData(contentForm, thumbData, 5);
    OH_UdsContentForm_SetDescription(contentForm, "description");
    OH_UdmfRecord_AddContentForm(record, contentForm);
    OH_UdmfData_AddRecord(udmfUnifiedData, record);
    Udmf_Intention intention = UDMF_INTENTION_DRAG;
    char key[UDMF_KEY_BUFFER_LEN];

    int setRes = OH_Udmf_SetUnifiedData(intention, udmfUnifiedData, key, UDMF_KEY_BUFFER_LEN);
    EXPECT_EQ(setRes, UDMF_E_OK);
    EXPECT_NE(key[0], '\0');
    OH_UdmfData *readUnifiedData = OH_UdmfData_Create();
    int getRes = OH_Udmf_GetUnifiedData(key, intention, readUnifiedData);
    EXPECT_EQ(getRes, UDMF_E_OK);
    unsigned int count = 0;
    OH_UdmfRecord **getRecords = OH_UdmfData_GetRecords(readUnifiedData, &count);
    EXPECT_EQ(count, 1);
    OH_UdsContentForm *getContentForm = OH_UdsContentForm_Create();
    OH_UdmfRecord_GetContentForm(getRecords[0], getContentForm);
    EXPECT_EQ("description", std::string(OH_UdsContentForm_GetDescription(getContentForm)));

    unsigned char *readThumbData;
    unsigned int thumbDataLen = 0;
    OH_UdsContentForm_GetThumbData(getContentForm, &readThumbData, &thumbDataLen);
    ASSERT_EQ(5, thumbDataLen);
    ASSERT_TRUE(CheckUnsignedChar(thumbData, readThumbData, thumbDataLen));

    OH_UdsContentForm_Destroy(contentForm);
    OH_UdmfRecord_Destroy(record);
    OH_UdmfData_Destroy(udmfUnifiedData);

    OH_UdsContentForm_Destroy(getContentForm);
    OH_UdmfData_Destroy(readUnifiedData);
}
}
