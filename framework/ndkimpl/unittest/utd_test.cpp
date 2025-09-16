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
#include <map>

#include "token_setproc.h"
#include "accesstoken_kit.h"
#include "nativetoken_kit.h"

#include "logger.h"
#include "utd.h"
#include "udmf_capi_common.h"
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
 * @tc.name: OH_Utd_GetReferenceUrl_001
 * @tc.desc: Normal testcase of OH_Utd_GetReferenceUrl
 * @tc.type: FUNC
 */
HWTEST_F(UtdTest, OH_Utd_GetReferenceUrl_001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "OH_Utd_GetReferenceUrl_001 begin.");
    std::string url(OH_Utd_GetReferenceUrl(utd));
    EXPECT_EQ(REFERENCE_URL, url);

    OH_Utd* utdNullptr = nullptr;
    const char* urlNullptr = OH_Utd_GetReferenceUrl(utdNullptr);
    EXPECT_EQ(nullptr, urlNullptr);
    LOG_INFO(UDMF_TEST, "OH_Utd_GetReferenceUrl_001 end.");
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
 * @tc.name: OH_Utd_GetTypesByFilenameExtension_002
 * @tc.desc: Normal testcase of OH_Utd_GetTypesByFilenameExtension
 * @tc.type: FUNC
 */
HWTEST_F(UtdTest, OH_Utd_GetTypesByFilenameExtension_002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "OH_Utd_GetTypesByFilenameExtension_002 begin.");
    unsigned int count = 0;
    auto typeIds = OH_Utd_GetTypesByFilenameExtension(".ts", &count);
    ASSERT_GE(count, 2);
    std::vector<std::string> typeIdsVec;
    for (size_t i = 0; i < count; ++i) {
        typeIdsVec.emplace_back(typeIds[i]);
    }
    EXPECT_TRUE(std::find(typeIdsVec.begin(), typeIdsVec.end(), "general.type-script") != typeIdsVec.end());
    EXPECT_TRUE(std::find(typeIdsVec.begin(), typeIdsVec.end(), "general.ts") != typeIdsVec.end());
    OH_Utd_DestroyStringList(typeIds, count);
    LOG_INFO(UDMF_TEST, "OH_Utd_GetTypesByFilenameExtension_002 end.");
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
    ASSERT_GE(count, 6);
    std::vector<std::string> typeIdsVec;
    for (size_t i = 0; i < count; ++i) {
        typeIdsVec.emplace_back(typeIds[i]);
    }
    EXPECT_TRUE(std::find(typeIdsVec.begin(), typeIdsVec.end(), "general.plain-text") != typeIdsVec.end());
    EXPECT_TRUE(std::find(typeIdsVec.begin(), typeIdsVec.end(), "general.asc-text") != typeIdsVec.end());
    EXPECT_TRUE(std::find(typeIdsVec.begin(), typeIdsVec.end(), "general.portable-object") != typeIdsVec.end());
    EXPECT_TRUE(std::find(typeIdsVec.begin(), typeIdsVec.end(), "general.diff") != typeIdsVec.end());
    EXPECT_TRUE(std::find(typeIdsVec.begin(), typeIdsVec.end(), "general.log") != typeIdsVec.end());
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
 * @tc.name: OH_Utd_GetTypesByMimeType_002
 * @tc.desc: Normal testcase of OH_Utd_GetTypesByMimeType
 * @tc.type: FUNC
 */
HWTEST_F(UtdTest, OH_Utd_GetTypesByMimeType_002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "OH_Utd_GetTypesByMimeType_002 begin.");
    unsigned int count = 0;
    auto typeIds = OH_Utd_GetTypesByMimeType("video/mp2ts", &count);
    ASSERT_GE(count, 1);
    std::vector<std::string> typeIdsVec;
    for (size_t i = 0; i < count; ++i) {
        typeIdsVec.emplace_back(typeIds[i]);
    }
    EXPECT_TRUE(std::find(typeIdsVec.begin(), typeIdsVec.end(), "general.ts") != typeIdsVec.end());
    OH_Utd_DestroyStringList(typeIds, count);
    LOG_INFO(UDMF_TEST, "OH_Utd_GetTypesByMimeType_002 end.");
}

/**
 * @tc.name: OH_Utd_BelongsTo_001
 * @tc.desc: test typeId1 belong to typeId2
 * @tc.type: FUNC
 */
HWTEST_F(UtdTest, OH_Utd_BelongsTo_001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "OH_Utd_BelongsTo_001 begin.");
    EXPECT_TRUE(OH_Utd_BelongsTo(UDMF_META_PLAIN_TEXT, UDMF_META_TEXT));
    LOG_INFO(UDMF_TEST, "OH_Utd_BelongsTo_001 end.");
}

/**
 * @tc.name: OH_Utd_BelongsTo_002
 * @tc.desc: test typeId1 don't belong to typeId2
 * @tc.type: FUNC
 */
HWTEST_F(UtdTest, OH_Utd_BelongsTo_002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "OH_Utd_BelongsTo_002 begin.");
    EXPECT_FALSE(OH_Utd_BelongsTo(UDMF_META_PLAIN_TEXT, UDMF_META_HTML));
    LOG_INFO(UDMF_TEST, "OH_Utd_BelongsTo_002 end.");
}

/**
 * @tc.name: OH_Utd_BelongsTo_003
 * @tc.desc: test param is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(UtdTest, OH_Utd_BelongsTo_003, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "OH_Utd_BelongsTo_003 begin.");
    EXPECT_FALSE(OH_Utd_BelongsTo(UDMF_META_PLAIN_TEXT, nullptr));
    EXPECT_FALSE(OH_Utd_BelongsTo(nullptr, UDMF_META_PLAIN_TEXT));
    LOG_INFO(UDMF_TEST, "OH_Utd_BelongsTo_003 end.");
}

/**
 * @tc.name: OH_Utd_IsLower_001
 * @tc.desc: test typeId1 is lower level of typeId2
 * @tc.type: FUNC
 */
HWTEST_F(UtdTest, OH_Utd_IsLower_001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "OH_Utd_IsLower_001 begin.");
    EXPECT_TRUE(OH_Utd_IsLower(UDMF_META_PLAIN_TEXT, UDMF_META_TEXT));
    LOG_INFO(UDMF_TEST, "OH_Utd_IsLower_001 end.");
}

/**
 * @tc.name: OH_Utd_IsLower_002
 * @tc.desc: test typeId1 isn't lower level of typeId2
 * @tc.type: FUNC
 */
HWTEST_F(UtdTest, OH_Utd_IsLower_002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "OH_Utd_IsLower_002 begin.");
    EXPECT_FALSE(OH_Utd_IsLower(UDMF_META_PLAIN_TEXT, UDMF_META_HTML));
    LOG_INFO(UDMF_TEST, "OH_Utd_IsLower_002 end.");
}

/**
 * @tc.name: OH_Utd_IsLower_003
 * @tc.desc: test param is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(UtdTest, OH_Utd_IsLower_003, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "OH_Utd_IsLower_003 begin.");
    EXPECT_FALSE(OH_Utd_IsLower(UDMF_META_PLAIN_TEXT, nullptr));
    EXPECT_FALSE(OH_Utd_IsLower(nullptr, UDMF_META_PLAIN_TEXT));
    LOG_INFO(UDMF_TEST, "OH_Utd_IsLower_003 end.");
}

/**
 * @tc.name: OH_Utd_IsHigher_001
 * @tc.desc: test typeId1 is higher level of typeId2
 * @tc.type: FUNC
 */
HWTEST_F(UtdTest, OH_Utd_IsHigher_001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "OH_Utd_IsHigher_001 begin.");
    EXPECT_TRUE(OH_Utd_IsHigher(UDMF_META_TEXT, UDMF_META_PLAIN_TEXT));
    LOG_INFO(UDMF_TEST, "OH_Utd_IsHigher_001 end.");
}

/**
 * @tc.name: OH_Utd_IsHigher_002
 * @tc.desc: test typeId1 isn't higher level of typeId2
 * @tc.type: FUNC
 */
HWTEST_F(UtdTest, OH_Utd_IsHigher_002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "OH_Utd_IsHigher_002 begin.");
    EXPECT_FALSE(OH_Utd_IsHigher(UDMF_META_PLAIN_TEXT, UDMF_META_HTML));
    LOG_INFO(UDMF_TEST, "OH_Utd_IsHigher_002 end.");
}

/**
 * @tc.name: OH_Utd_IsHigher_003
 * @tc.desc: test param is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(UtdTest, OH_Utd_IsHigher_003, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "OH_Utd_IsHigher_003 begin.");
    EXPECT_FALSE(OH_Utd_IsHigher(UDMF_META_PLAIN_TEXT, nullptr));
    EXPECT_FALSE(OH_Utd_IsHigher(nullptr, UDMF_META_PLAIN_TEXT));
    LOG_INFO(UDMF_TEST, "OH_Utd_IsHigher_003 end.");
}

/**
 * @tc.name: OH_Utd_Equals_001
 * @tc.desc: test case1 is equals case2
 * @tc.type: FUNC
 */
HWTEST_F(UtdTest, OH_Utd_Equals_001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "OH_Utd_Equals_001 begin.");
    auto utd2 = OH_Utd_Create(UDMF_META_PLAIN_TEXT);
    EXPECT_TRUE(OH_Utd_Equals(utd, utd2));
    OH_Utd_Destroy(utd2);
    utd2 = nullptr;
    LOG_INFO(UDMF_TEST, "OH_Utd_Equals_001 end.");
}

/**
 * @tc.name: OH_Utd_Equals_002
 * @tc.desc: test case1 is not equals case2
 * @tc.type: FUNC
 */
HWTEST_F(UtdTest, OH_Utd_Equals_002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "OH_Utd_Equals_002 begin.");
    auto utd2 = OH_Utd_Create(UDMF_META_TEXT);
    EXPECT_FALSE(OH_Utd_Equals(utd, utd2));
    OH_Utd_Destroy(utd2);
    utd2 = nullptr;
    LOG_INFO(UDMF_TEST, "OH_Utd_Equals_002 end.");
}

/**
 * @tc.name: OH_Utd_Equals_003
 * @tc.desc: test param is nullptr
 * @tc.type: FUNC
 */
HWTEST_F(UtdTest, OH_Utd_Equals_003, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "OH_Utd_Equals_003 begin.");
    EXPECT_FALSE(OH_Utd_Equals(utd, nullptr));
    EXPECT_FALSE(OH_Utd_Equals(nullptr, utd));
    LOG_INFO(UDMF_TEST, "OH_Utd_Equals_003 end.");
}

std::map<std::string, std::string> typeIdMap = {
    {UDMF_META_ENTITY, "general.entity"},
    {UDMF_META_OBJECT, "general.object"},
    {UDMF_META_COMPOSITE_OBJECT, "general.composite-object"},
    {UDMF_META_TEXT, "general.text"},
    {UDMF_META_PLAIN_TEXT, "general.plain-text"},
    {UDMF_META_HTML, "general.html"},
    {UDMF_META_HYPERLINK, "general.hyperlink"},
    {UDMF_META_XML, "general.xml"},
    {UDMF_META_SOURCE_CODE, "general.source-code"},
    {UDMF_META_SCRIPT, "general.script"},
    {UDMF_META_SHELL_SCRIPT, "general.shell-script"},
    {UDMF_META_CSH_SCRIPT, "general.csh-script"},
    {UDMF_META_PERL_SCRIPT, "general.perl-script"},
    {UDMF_META_PHP_SCRIPT, "general.php-script"},
    {UDMF_META_PYTHON_SCRIPT, "general.python-script"},
    {UDMF_META_RUBY_SCRIPT, "general.ruby-script"},
    {UDMF_META_TYPE_SCRIPT, "general.type-script"},
    {UDMF_META_JAVA_SCRIPT, "general.java-script"},
    {UDMF_META_C_HEADER, "general.c-header"},
    {UDMF_META_C_SOURCE, "general.c-source"},
    {UDMF_META_C_PLUS_PLUS_HEADER, "general.c-plus-plus-header"},
    {UDMF_META_C_PLUS_PLUS_SOURCE, "general.c-plus-plus-source"},
    {UDMF_META_JAVA_SOURCE, "general.java-source"},
    {UDMF_META_EBOOK, "general.ebook"},
    {UDMF_META_EPUB, "general.epub"},
    {UDMF_META_AZW, "com.amazon.azw"},
    {UDMF_META_AZW3, "com.amazon.azw3"},
    {UDMF_META_KFX, "com.amazon.kfx"},
    {UDMF_META_MOBI, "com.amazon.mobi"},
    {UDMF_META_MEDIA, "general.media"},
    {UDMF_META_IMAGE, "general.image"},
    {UDMF_META_JPEG, "general.jpeg"},
    {UDMF_META_PNG, "general.png"},
    {UDMF_META_RAW_IMAGE, "general.raw-image"},
    {UDMF_META_TIFF, "general.tiff"},
    {UDMF_META_BMP, "com.microsoft.bmp"},
    {UDMF_META_ICO, "com.microsoft.ico"},
    {UDMF_META_PHOTOSHOP_IMAGE, "com.adobe.photoshop-image"},
    {UDMF_META_AI_IMAGE, "com.adobe.illustrator.ai-image"},
    {UDMF_META_WORD_DOC, "com.microsoft.word.doc"},
    {UDMF_META_EXCEL, "com.microsoft.excel.xls"},
    {UDMF_META_PPT, "com.microsoft.powerpoint.ppt"},
    {UDMF_META_PDF, "com.adobe.pdf"},
    {UDMF_META_POSTSCRIPT, "com.adobe.postscript"},
    {UDMF_META_ENCAPSULATED_POSTSCRIPT, "com.adobe.encapsulated-postscript"},
    {UDMF_META_VIDEO, "general.video"},
    {UDMF_META_AVI, "general.avi"},
    {UDMF_META_MPEG, "general.mpeg"},
    {UDMF_META_MPEG4, "general.mpeg-4"},
    {UDMF_META_VIDEO_3GPP, "general.3gpp"},
    {UDMF_META_VIDEO_3GPP2, "general.3gpp2"},
    {UDMF_META_WINDOWS_MEDIA_WM, "com.microsoft.windows-media-wm"},
    {UDMF_META_WINDOWS_MEDIA_WMV, "com.microsoft.windows-media-wmv"},
    {UDMF_META_WINDOWS_MEDIA_WMP, "com.microsoft.windows-media-wmp"},
    {UDMF_META_AUDIO, "general.audio"},
    {UDMF_META_AAC, "general.aac"},
    {UDMF_META_AIFF, "general.aiff"},
    {UDMF_META_ALAC, "general.alac"},
    {UDMF_META_FLAC, "general.flac"},
    {UDMF_META_MP3, "general.mp3"},
    {UDMF_META_OGG, "general.ogg"},
    {UDMF_META_PCM, "general.pcm"},
    {UDMF_META_WINDOWS_MEDIA_WMA, "com.microsoft.windows-media-wma"},
    {UDMF_META_WAVEFORM_AUDIO, "com.microsoft.waveform-audio"},
    {UDMF_META_WINDOWS_MEDIA_WMX, "com.microsoft.windows-media-wmx"},
    {UDMF_META_WINDOWS_MEDIA_WVX, "com.microsoft.windows-media-wvx"},
    {UDMF_META_WINDOWS_MEDIA_WAX, "com.microsoft.windows-media-wax"},
    {UDMF_META_GENERAL_FILE, "general.file"},
    {UDMF_META_DIRECTORY, "general.directory"},
    {UDMF_META_FOLDER, "general.folder"},
    {UDMF_META_SYMLINK, "general.symlink"},
    {UDMF_META_ARCHIVE, "general.archive"},
    {UDMF_META_BZ2_ARCHIVE, "general.bz2-archive"},
    {UDMF_META_DISK_IMAGE, "general.disk-image"},
    {UDMF_META_TAR_ARCHIVE, "general.tar-archive"},
    {UDMF_META_ZIP_ARCHIVE, "general.zip-archive"},
    {UDMF_META_JAVA_ARCHIVE, "com.sun.java-archive"},
    {UDMF_META_GNU_TAR_ARCHIVE, "org.gnu.gnu-tar-archive"},
    {UDMF_META_GNU_ZIP_ARCHIVE, "org.gnu.gnu-zip-archive"},
    {UDMF_META_GNU_ZIP_TAR_ARCHIVE, "org.gnu.gnu-zip-tar-archive"},
    {UDMF_META_CALENDAR, "general.calendar"},
    {UDMF_META_CONTACT, "general.contact"},
    {UDMF_META_DATABASE, "general.database"},
    {UDMF_META_MESSAGE, "general.message"},
    {UDMF_META_VCARD, "general.vcard"},
    {UDMF_META_NAVIGATION, "general.navigation"},
    {UDMF_META_LOCATION, "general.location"},
    {UDMF_META_OPENHARMONY_FORM, "openharmony.form"},
    {UDMF_META_OPENHARMONY_APP_ITEM, "openharmony.app-item"},
    {UDMF_META_OPENHARMONY_PIXEL_MAP, "openharmony.pixel-map"},
    {UDMF_META_OPENHARMONY_ATOMIC_SERVICE, "openharmony.atomic-service"},
    {UDMF_META_OPENHARMONY_PACKAGE, "openharmony.package"},
    {UDMF_META_OPENHARMONY_HAP, "openharmony.hap"},
    {UDMF_META_SMIL, "com.real.smil"},
    {UDMF_META_MARKDOWN, "general.markdown"},
    {UDMF_META_FAX, "general.fax"},
    {UDMF_META_JFX_FAX, "com.j2.jfx-fax"},
    {UDMF_META_EFX_FAX, "com.js.efx-fax"},
    {UDMF_META_XBITMAP_IMAGE, "general.xbitmap-image"},
    {UDMF_META_TGA_IMAGE, "com.truevision.tga-image"},
    {UDMF_META_SGI_IMAGE, "com.sgi.sgi-image"},
    {UDMF_META_OPENEXR_IMAGE, "com.ilm.openexr-image"},
    {UDMF_META_FLASHPIX_IMAGE, "com.kodak.flashpix.image"},
    {UDMF_META_REALMEDIA, "com.real.realmedia"},
    {UDMF_META_AU_AUDIO, "general.au-audio"},
    {UDMF_META_AIFC_AUDIO, "general.aifc-audio"},
    {UDMF_META_SD2_AUDIO, "com.digidesign.sd2-audio"},
    {UDMF_META_REALAUDIO, "com.real.realaudio"},
    {UDMF_META_OPENXML, "org.openxmlformats.openxml"},
    {UDMF_META_WORDPROCESSINGML_DOCUMENT, "org.openxmlformats.wordprocessingml.document"},
    {UDMF_META_SPREADSHEETML_SHEET, "org.openxmlformats.spreadsheetml.sheet"},
    {UDMF_META_PRESENTATIONML_PRESENTATION, "org.openxmlformats.presentationml.presentation"},
    {UDMF_META_OPENDOCUMENT, "org.oasis.opendocument"},
    {UDMF_META_OPENDOCUMENT_TEXT, "org.oasis.opendocument.text"},
    {UDMF_META_OPENDOCUMENT_SPREADSHEET, "org.oasis.opendocument.spreadsheet"},
    {UDMF_META_OPENDOCUMENT_PRESENTATION, "org.oasis.opendocument.presentation"},
    {UDMF_META_OPENDOCUMENT_GRAPHICS, "org.oasis.opendocument.graphics"},
    {UDMF_META_OPENDOCUMENT_FORMULA, "org.oasis.opendocument.formula"},
    {UDMF_META_STUFFIT_ARCHIVE, "com.allume.stuffit-archive"},
    {UDMF_META_VCS, "general.vcs"},
    {UDMF_META_ICS, "general.ics"},
    {UDMF_META_EXECUTABLE, "general.executable"},
    {UDMF_META_PORTABLE_EXECUTABLE, "com.microsoft.portable-executable"},
    {UDMF_META_SUN_JAVA_CLASS, "com.sun.java-class"},
    {UDMF_META_FONT, "general.font"},
    {UDMF_META_TRUETYPE_FONT, "general.truetype-font"},
    {UDMF_META_TRUETYPE_COLLECTION_FONT, "general.truetype-collection-font"},
    {UDMF_META_OPENTYPE_FONT, "general.opentype-font"},
    {UDMF_META_POSTSCRIPT_FONT, "com.adobe.postscript-font"},
    {UDMF_META_POSTSCRIPT_PFB_FONT, "com.adobe.postscript-pfb-font"},
    {UDMF_META_POSTSCRIPT_PFA_FONT, "com.adobe.postscript-pfa-font"},
    {UDMF_META_OPENHARMONY_HDOC, "openharmony.hdoc"},
    {UDMF_META_OPENHARMONY_HINOTE, "openharmony.hinote"},
    {UDMF_META_OPENHARMONY_STYLED_STRING, "openharmony.styled-string"},
    {UDMF_META_OPENHARMONY_WANT, "openharmony.want"}
};

/**
 * @tc.name: OH_Utd_Create_002
 * @tc.desc: traverse enum for UTD
 * @tc.type: FUNC
 */
HWTEST_F(UtdTest, OH_Utd_Create_002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "OH_Utd_Create_002 begin.");
    OH_Utd* utd1;
    for (const auto& pair : typeIdMap) {
        utd1 = OH_Utd_Create(pair.first.c_str());
        std::string typeId(OH_Utd_GetTypeId(utd1));
        EXPECT_EQ(pair.second, typeId);
        OH_Utd_Destroy(utd1);
    }
    LOG_INFO(UDMF_TEST, "OH_Utd_Create_002 end.");
}

}
