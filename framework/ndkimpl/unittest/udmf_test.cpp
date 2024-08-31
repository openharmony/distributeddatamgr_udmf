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
    ASSERT_EQ(setRes, UDMF_E_OK);
    EXPECT_NE(key[0], '\0');
    OH_UdmfData *readUnifiedData = OH_UdmfData_Create();
    int getRes = OH_Udmf_GetUnifiedData(key, intention, readUnifiedData);
    ASSERT_EQ(getRes, UDMF_E_OK);
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
    char typeId[] = "general.plain-text";
    unsigned char entry[] = "CreateGeneralRecord";
    unsigned int count = sizeof(entry);
    OH_UdmfRecord *record = OH_UdmfRecord_Create();
    OH_UdmfRecord_AddGeneralEntry(record, typeId, entry, count);
    OH_UdmfData_AddRecord(udmfUnifiedData, record);
    Udmf_Intention intention = UDMF_INTENTION_DRAG;
    char key[UDMF_KEY_BUFFER_LEN];

    int setRes = OH_Udmf_SetUnifiedData(intention, udmfUnifiedData, key, UDMF_KEY_BUFFER_LEN);
    EXPECT_EQ(setRes, UDMF_E_OK);
    EXPECT_NE(key[0], '\0');
    OH_UdmfData *readUnifiedData = OH_UdmfData_Create();
    int getUnifiedDataRes = OH_Udmf_GetUnifiedData(key, intention, readUnifiedData);
    EXPECT_EQ(getUnifiedDataRes, UDMF_E_OK);
    unsigned int getRecordsCount = 0;
    OH_UdmfRecord **getRecords = OH_UdmfData_GetRecords(readUnifiedData, &getRecordsCount);
    EXPECT_EQ(getRecordsCount, 1);

    unsigned char *getEntry;
    unsigned int getCount = 0;
    int getRes = OH_UdmfRecord_GetGeneralEntry(getRecords[0], typeId, &getEntry, &getCount);
    EXPECT_EQ(getRes, UDMF_E_OK);
    EXPECT_EQ(getCount, count);
    EXPECT_EQ(std::memcmp(getEntry, entry, getCount), 0);

    unsigned int getCount1 = 0;
    unsigned char *getEntry1;
    int getRes1 = OH_UdmfRecord_GetGeneralEntry(getRecords[0], typeId, &getEntry1, &getCount1);
    EXPECT_EQ(getEntry1, getEntry);
    EXPECT_EQ(getRes1, UDMF_E_OK);

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
    char typeId[] = "general.plain-text";
    unsigned char entry[] = "CreateGeneralRecord";
    unsigned int count = sizeof(entry);
    OH_UdmfRecord *record = OH_UdmfRecord_Create();
    int addRes1 = OH_UdmfRecord_AddGeneralEntry(record, typeId, entry, count);
    EXPECT_EQ(addRes1, UDMF_E_OK);

    unsigned int getCount = 0;
    unsigned char *getEntry;
    int getRes = OH_UdmfRecord_GetGeneralEntry(record, typeId, &getEntry, &getCount);
    EXPECT_EQ(getRes, UDMF_E_OK);
    EXPECT_EQ(getCount, count);
    EXPECT_EQ(std::memcmp(getEntry, entry, getCount), 0);

    unsigned int getCount1 = 0;
    unsigned char *getEntry1;
    int getRes1 = OH_UdmfRecord_GetGeneralEntry(record, typeId, &getEntry1, &getCount1);
    EXPECT_EQ(getEntry1, getEntry);
    EXPECT_EQ(getRes1, UDMF_E_OK);

    OH_UdmfRecord_Destroy(record);
}

/**
 * @tc.name: OH_Udmf_AddAndGetGeneralEntry003
 * @tc.desc: test OH_UdmfRecord_AddGeneralEntry and OH_UdmfRecord_GetGeneralEntry with return error
 * @tc.type: FUNC
 * @tc.require: AROOOH5R5G
 */
HWTEST_F(UDMFTest, OH_Udmf_AddAndGetGeneralEntry003, TestSize.Level0)
{
    char typeId[] = "general.plain-text";
    unsigned char entry[] = "CreateGeneralRecord";
    unsigned int count = sizeof(entry);
    OH_UdmfRecord *record = OH_UdmfRecord_Create();
    int addRes1 = OH_UdmfRecord_AddGeneralEntry(record, typeId, entry, count);
    EXPECT_EQ(addRes1, UDMF_E_OK);

    OH_UdmfRecord *getRecord = OH_UdmfRecord_Create();
    unsigned int getCount = 0;
    unsigned char *getEntry;
    char typeId1[] = "general.text";
    OH_UdmfRecord_AddGeneralEntry(record, typeId, entry, count);
    
    int getRes = OH_UdmfRecord_GetGeneralEntry(getRecord, typeId1, &getEntry, &getCount);
    EXPECT_EQ(getRes, UDMF_E_INVALID_PARAM);

    OH_UdmfRecord_Destroy(record);
    OH_UdmfRecord_Destroy(getRecord);
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
 * @tc.name: OH_Udmf_BuildRecordByOpenHarmonyArrayBuffer001
 * @tc.desc: test OH_UdmfRecord_AddArrayBuffer with invalid param
 * @tc.type: FUNC
 * @tc.require: AROOOH5R5G
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
 * @tc.require: AROOOH5R5G
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
 * @tc.name: OH_Udmf_BuildAndGetArrayBufferFromRecord001
 * @tc.desc: test OH_UdmfRecord_AddArrayBuffer with invalid param
 * @tc.type: FUNC
 * @tc.require: AROOOH5R5G
 */
HWTEST_F(UDMFTest, OH_Udmf_BuildAndGetArrayBufferFromRecord001, TestSize.Level0)
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
}
