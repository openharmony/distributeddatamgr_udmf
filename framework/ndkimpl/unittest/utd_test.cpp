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

#define LOG_TAG "UtdTest"

#include <gtest/gtest.h>
#include <unistd.h>

#include "token_setproc.h"
#include "accesstoken_kit.h"
#include "nativetoken_kit.h"

#include "logger.h"
#include "utd.h"
#include "udmf_ndk_common.h"
#include "udmf_meta.h"

using namespace testing::ext;
using namespace OHOS::Security::AccessToken;
using namespace OHOS::UDMF;
using namespace OHOS;

constexpr const char *REFERENCE_URL = "https://gitee.com/openharmony/docs/blob/master/en/application-dev/reference/"\
                                      "apis/js-apis-data-uniformTypeDescriptor.md#uniformdatatype";

namespace OHOS::Test {

OH_Utd* utd = nullptr;

class UtdTest : public testing::Test {
public:
    static void SetUpTestCase(void);
    static void TearDownTestCase(void);
    void SetUp();
    void TearDown();
};

void UtdTest::SetUpTestCase(void) {}

void UtdTest::TearDownTestCase(void) {}

void UtdTest::SetUp(void)
{
    LOG_INFO(UDMF_TEST, "test case will be start");
    utd = OH_Utd_Create(UDMF_META_PLAIN_TEXT);
}

void UtdTest::TearDown(void)
{
    OH_Utd_Destroy(utd);
    utd = nullptr;
    LOG_INFO(UDMF_TEST, "test case is complete");
}

/**
 * @tc.name: OH_Utd_Create_001
 * @tc.desc: Normal testcase of OH_Utd_Create
 * @tc.type: FUNC
 */
HWTEST_F(UtdTest, OH_Utd_Create_001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "OH_Utd_Create_001 begin.");
    EXPECT_EQ(utd->typeId, UDMF_META_PLAIN_TEXT);
    EXPECT_EQ(utd->belongingToTypesCount, 1);
    std::string belongingToType((utd->belongingToTypes)[0]);
    EXPECT_EQ(belongingToType, UDMF_META_TEXT);
    EXPECT_EQ(utd->description, "Text of unspecified encoding, with no markup.");

    char* typeId = nullptr;
    OH_Utd* utdNullptr = OH_Utd_Create(typeId);
    EXPECT_EQ(nullptr, utdNullptr);
    LOG_INFO(UDMF_TEST, "OH_Utd_Create_001 end.");
}

/**
 * @tc.name: OH_Utd_GetTypeId_001
 * @tc.desc: Normal testcase of OH_Utd_GetTypeId
 * @tc.type: FUNC
 */
HWTEST_F(UtdTest, OH_Utd_GetTypeId_001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "OH_Utd_GetTypeId_001 begin.");
    std::string actualTypeId(OH_Utd_GetTypeId(utd));
    EXPECT_EQ(UDMF_META_PLAIN_TEXT, actualTypeId);

    OH_Utd* utdNullptr = nullptr;
    const char* typeIdNullptr = OH_Utd_GetTypeId(utdNullptr);
    EXPECT_EQ(nullptr, typeIdNullptr);
    LOG_INFO(UDMF_TEST, "OH_Utd_GetTypeId_001 end.");
}

/**
 * @tc.name: OH_Utd_GetDescription_001
 * @tc.desc: Normal testcase of OH_Utd_GetDescription
 * @tc.type: FUNC
 */
HWTEST_F(UtdTest, OH_Utd_GetDescription_001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "OH_Utd_GetDescription_001 begin.");
    std::string description(OH_Utd_GetDescription(utd));
    EXPECT_EQ("Text of unspecified encoding, with no markup.", description);

    OH_Utd* utdNullptr = nullptr;
    const char* descriptionNullptr = OH_Utd_GetDescription(utdNullptr);
    EXPECT_EQ(nullptr, descriptionNullptr);
    LOG_INFO(UDMF_TEST, "OH_Utd_GetDescription_001 end.");
}

/**
 * @tc.name: OH_Utd_GetReferenceURL_001
 * @tc.desc: Normal testcase of OH_Utd_GetReferenceURL
 * @tc.type: FUNC
 */
HWTEST_F(UtdTest, OH_Utd_GetReferenceURL_001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "OH_Utd_GetReferenceURL_001 begin.");
    std::string url(OH_Utd_GetReferenceURL(utd));
    EXPECT_EQ(REFERENCE_URL, url);

    OH_Utd* utdNullptr = nullptr;
    const char* urlNullptr = OH_Utd_GetReferenceURL(utdNullptr);
    EXPECT_EQ(nullptr, urlNullptr);
    LOG_INFO(UDMF_TEST, "OH_Utd_GetReferenceURL_001 end.");
}

/**
 * @tc.name: OH_Utd_GetIconFile_001
 * @tc.desc: Normal testcase of OH_Utd_GetIconFile
 * @tc.type: FUNC
 */
HWTEST_F(UtdTest, OH_Utd_GetIconFile_001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "OH_Utd_GetIconFile_001 begin.");
    std::string iconFile(OH_Utd_GetIconFile(utd));
    EXPECT_EQ("sys.media.ohos_ic_normal_white_grid_txt", iconFile);

    OH_Utd* utdNullptr = nullptr;
    const char* iconFileNullptr = OH_Utd_GetIconFile(utdNullptr);
    EXPECT_EQ(nullptr, iconFileNullptr);
    LOG_INFO(UDMF_TEST, "OH_Utd_GetIconFile_001 end.");
}

/**
 * @tc.name: OH_Utd_GetBelongingToTypes_001
 * @tc.desc: Normal testcase of OH_Utd_GetBelongingToTypes
 * @tc.type: FUNC
 */
HWTEST_F(UtdTest, OH_Utd_GetBelongingToTypes_001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "OH_Utd_GetBelongingToTypes_001 begin.");
    unsigned int count = 0;
    auto belongingToTypes = OH_Utd_GetBelongingToTypes(utd, &count);
    std::string belongingToType(belongingToTypes[0]);
    EXPECT_EQ(UDMF_META_TEXT, belongingToType);
    EXPECT_EQ(1, count);

    OH_Utd* utdNullptr = nullptr;
    auto belongingToTypeNullptr = OH_Utd_GetBelongingToTypes(utdNullptr, &count);
    EXPECT_EQ(nullptr, belongingToTypeNullptr);

    unsigned int* countNullptr = nullptr;
    auto belongingToTypeNullptr2 = OH_Utd_GetBelongingToTypes(utd, countNullptr);
    EXPECT_EQ(nullptr, belongingToTypeNullptr2);
    LOG_INFO(UDMF_TEST, "OH_Utd_GetBelongingToTypes_001 end.");
}

/**
 * @tc.name: OH_Utd_GetFilenameExtensions_001
 * @tc.desc: Normal testcase of OH_Utd_GetFilenameExtensions
 * @tc.type: FUNC
 */
HWTEST_F(UtdTest, OH_Utd_GetFilenameExtensions_001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "OH_Utd_GetFilenameExtensions_001 begin.");
    unsigned int count = 0;
    auto filenameExtensions = OH_Utd_GetFilenameExtensions(utd, &count);
    std::string filenameExtension(filenameExtensions[0]);
    EXPECT_EQ(".txt", filenameExtension);
    EXPECT_EQ(2, count);

    OH_Utd* utdNullptr = nullptr;
    auto filenameExtensionsNullptr = OH_Utd_GetFilenameExtensions(utdNullptr, &count);
    EXPECT_EQ(nullptr, filenameExtensionsNullptr);

    unsigned int* countNullptr = nullptr;
    auto filenameExtensionsNullptr2 = OH_Utd_GetFilenameExtensions(utd, countNullptr);
    EXPECT_EQ(nullptr, filenameExtensionsNullptr2);
    LOG_INFO(UDMF_TEST, "OH_Utd_GetFilenameExtensions_001 end.");
}

/**
 * @tc.name: OH_Utd_GetMimeTypes_001
 * @tc.desc: Normal testcase of OH_Utd_GetMimeTypes
 * @tc.type: FUNC
 */
HWTEST_F(UtdTest, OH_Utd_GetMimeTypes_001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "OH_Utd_GetMimeTypes_001 begin.");
    unsigned int count = 0;
    auto mimeTypes = OH_Utd_GetMimeTypes(utd, &count);
    std::string mimeType(mimeTypes[0]);
    EXPECT_EQ("text/plain", mimeType);
    EXPECT_EQ(1, count);

    OH_Utd* utdNullptr = nullptr;
    auto mimeTypeNullptr = OH_Utd_GetMimeTypes(utdNullptr, &count);
    EXPECT_EQ(nullptr, mimeTypeNullptr);

    unsigned int* countNullptr = nullptr;
    auto mimeTypeNullptr2 = OH_Utd_GetMimeTypes(utd, countNullptr);
    EXPECT_EQ(nullptr, mimeTypeNullptr2);
    LOG_INFO(UDMF_TEST, "OH_Utd_GetMimeTypes_001 end.");
}

/**
 * @tc.name: OH_Utd_GetTypesByFilenameExtension_001
 * @tc.desc: Normal testcase of OH_Utd_GetTypesByFilenameExtension
 * @tc.type: FUNC
 */
HWTEST_F(UtdTest, OH_Utd_GetTypesByFilenameExtension_001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "OH_Utd_GetTypesByFilenameExtension_001 begin.");
    unsigned int count = 0;
    auto typeIds = OH_Utd_GetTypesByFilenameExtension(".txt", &count);
    std::string typeId(typeIds[0]);
    EXPECT_EQ(UDMF_META_PLAIN_TEXT, typeId);
    EXPECT_EQ(1, count);
    OH_Utd_DestroyStringList(typeIds, count);

    const char* extensionNullptr = nullptr;
    auto typeIdsNullptr = OH_Utd_GetTypesByFilenameExtension(extensionNullptr, &count);
    EXPECT_EQ(nullptr, typeIdsNullptr);

    unsigned int* countNullptr = nullptr;
    typeIds = OH_Utd_GetTypesByFilenameExtension(".txt", countNullptr);
    EXPECT_EQ(nullptr, typeIds);
    LOG_INFO(UDMF_TEST, "OH_Utd_GetTypesByFilenameExtension_001 end.");
}

/**
 * @tc.name: OH_Utd_GetTypesByMimeType_001
 * @tc.desc: Normal testcase of OH_Utd_GetTypesByMimeType
 * @tc.type: FUNC
 */
HWTEST_F(UtdTest, OH_Utd_GetTypesByMimeType_001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "OH_Utd_GetTypesByMimeType_001 begin.");
    unsigned int count = 0;
    auto typeIds = OH_Utd_GetTypesByMimeType("text/plain", &count);
    std::string typeId(typeIds[0]);
    EXPECT_EQ(UDMF_META_PLAIN_TEXT, typeId);
    EXPECT_EQ(1, count);
    OH_Utd_DestroyStringList(typeIds, count);

    const char* extensionNullptr = nullptr;
    auto typeIdsNullptr = OH_Utd_GetTypesByMimeType(extensionNullptr, &count);
    EXPECT_EQ(nullptr, typeIdsNullptr);

    unsigned int* countNullptr = nullptr;
    auto typeIdsNullptr2 = OH_Utd_GetTypesByMimeType("text/plain", countNullptr);
    EXPECT_EQ(nullptr, typeIdsNullptr2);
    LOG_INFO(UDMF_TEST, "OH_Utd_GetTypesByMimeType_001 end.");
}

/**
 * @tc.name: OH_Utd_IsBelongsTo_001
 * @tc.desc: test typeId1 belong to typeId2
 * @tc.type: FUNC
 */
HWTEST_F(UtdTest, OH_Utd_IsBelongsTo_001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "OH_Utd_IsBelongsTo_001 begin.");
    EXPECT_TRUE(OH_Utd_IsBelongsTo(UDMF_META_PLAIN_TEXT, UDMF_META_TEXT));
    LOG_INFO(UDMF_TEST, "OH_Utd_IsBelongsTo_001 end.");
}

/**
 * @tc.name: OH_Utd_IsBelongsTo_002
 * @tc.desc: test typeId1 don't belong to typeId2
 * @tc.type: FUNC
 */
HWTEST_F(UtdTest, OH_Utd_IsBelongsTo_002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "OH_Utd_IsBelongsTo_002 begin.");
    EXPECT_FALSE(OH_Utd_IsBelongsTo(UDMF_META_PLAIN_TEXT, UDMF_META_HTML));
    LOG_INFO(UDMF_TEST, "OH_Utd_IsBelongsTo_002 end.");
}

/**
 * @tc.name: OH_Utd_IsBelongsTo_003
 * @tc.desc: test param is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(UtdTest, OH_Utd_IsBelongsTo_003, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "OH_Utd_IsBelongsTo_003 begin.");
    EXPECT_FALSE(OH_Utd_IsBelongsTo(UDMF_META_PLAIN_TEXT, nullptr));
    EXPECT_FALSE(OH_Utd_IsBelongsTo(nullptr, UDMF_META_PLAIN_TEXT));
    LOG_INFO(UDMF_TEST, "OH_Utd_IsBelongsTo_003 end.");
}

/**
 * @tc.name: OH_Utd_IsLowerLevelType_001
 * @tc.desc: test typeId1 is lower level of typeId2
 * @tc.type: FUNC
 */
HWTEST_F(UtdTest, OH_Utd_IsLowerLevelType_001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "OH_Utd_IsLowerLevelType_001 begin.");
    EXPECT_TRUE(OH_Utd_IsLowerLevelType(UDMF_META_PLAIN_TEXT, UDMF_META_TEXT));
    LOG_INFO(UDMF_TEST, "OH_Utd_IsLowerLevelType_001 end.");
}

/**
 * @tc.name: OH_Utd_IsLowerLevelType_002
 * @tc.desc: test typeId1 isn't lower level of typeId2
 * @tc.type: FUNC
 */
HWTEST_F(UtdTest, OH_Utd_IsLowerLevelType_002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "OH_Utd_IsLowerLevelType_002 begin.");
    EXPECT_FALSE(OH_Utd_IsLowerLevelType(UDMF_META_PLAIN_TEXT, UDMF_META_HTML));
    LOG_INFO(UDMF_TEST, "OH_Utd_IsLowerLevelType_002 end.");
}

/**
 * @tc.name: OH_Utd_IsLowerLevelType_003
 * @tc.desc: test param is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(UtdTest, OH_Utd_IsLowerLevelType_003, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "OH_Utd_IsLowerLevelType_003 begin.");
    EXPECT_FALSE(OH_Utd_IsLowerLevelType(UDMF_META_PLAIN_TEXT, nullptr));
    EXPECT_FALSE(OH_Utd_IsLowerLevelType(nullptr, UDMF_META_PLAIN_TEXT));
    LOG_INFO(UDMF_TEST, "OH_Utd_IsLowerLevelType_003 end.");
}

/**
 * @tc.name: OH_Utd_IsHigherLevelType_001
 * @tc.desc: test typeId1 is higher level of typeId2
 * @tc.type: FUNC
 */
HWTEST_F(UtdTest, OH_Utd_IsHigherLevelType_001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "OH_Utd_IsHigherLevelType_001 begin.");
    EXPECT_TRUE(OH_Utd_IsHigherLevelType(UDMF_META_TEXT, UDMF_META_PLAIN_TEXT));
    LOG_INFO(UDMF_TEST, "OH_Utd_IsHigherLevelType_001 end.");
}

/**
 * @tc.name: OH_Utd_IsHigherLevelType_002
 * @tc.desc: test typeId1 isn't higher level of typeId2
 * @tc.type: FUNC
 */
HWTEST_F(UtdTest, OH_Utd_IsHigherLevelType_002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "OH_Utd_IsHigherLevelType_002 begin.");
    EXPECT_FALSE(OH_Utd_IsHigherLevelType(UDMF_META_PLAIN_TEXT, UDMF_META_HTML));
    LOG_INFO(UDMF_TEST, "OH_Utd_IsHigherLevelType_002 end.");
}

/**
 * @tc.name: OH_Utd_IsHigherLevelType_003
 * @tc.desc: test param is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(UtdTest, OH_Utd_IsHigherLevelType_003, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "OH_Utd_IsHigherLevelType_003 begin.");
    EXPECT_FALSE(OH_Utd_IsHigherLevelType(UDMF_META_PLAIN_TEXT, nullptr));
    EXPECT_FALSE(OH_Utd_IsHigherLevelType(nullptr, UDMF_META_PLAIN_TEXT));
    LOG_INFO(UDMF_TEST, "OH_Utd_IsHigherLevelType_003 end.");
}

/**
 * @tc.name: OH_Utd_IsEquals_001
 * @tc.desc: test case1 is equals case2
 * @tc.type: FUNC
 */
HWTEST_F(UtdTest, OH_Utd_IsEquals_001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "OH_Utd_IsEquals_001 begin.");
    auto utd2 = OH_Utd_Create(UDMF_META_PLAIN_TEXT);
    EXPECT_TRUE(OH_Utd_IsEquals(utd, utd2));
    OH_Utd_Destroy(utd2);
    utd2 = nullptr;
    LOG_INFO(UDMF_TEST, "OH_Utd_IsEquals_001 end.");
}

/**
 * @tc.name: OH_Utd_IsEquals_002
 * @tc.desc: test case1 is not equals case2
 * @tc.type: FUNC
 */
HWTEST_F(UtdTest, OH_Utd_IsEquals_002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "OH_Utd_IsEquals_002 begin.");
    auto utd2 = OH_Utd_Create(UDMF_META_TEXT);
    EXPECT_FALSE(OH_Utd_IsEquals(utd, utd2));
    OH_Utd_Destroy(utd2);
    utd2 = nullptr;
    LOG_INFO(UDMF_TEST, "OH_Utd_IsEquals_002 end.");
}

/**
 * @tc.name: OH_Utd_IsEquals_003
 * @tc.desc: test param is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(UtdTest, OH_Utd_IsEquals_003, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "OH_Utd_IsEquals_003 begin.");
    EXPECT_FALSE(OH_Utd_IsEquals(utd, nullptr));
    EXPECT_FALSE(OH_Utd_IsEquals(nullptr, utd));
    LOG_INFO(UDMF_TEST, "OH_Utd_IsEquals_003 end.");
}

}
