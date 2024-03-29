/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
#define LOG_TAG "UtdClientTest"
#include <gtest/gtest.h>

#include <unistd.h>

#include "token_setproc.h"
#include "accesstoken_kit.h"
#include "nativetoken_kit.h"

#include "logger.h"
#include "utd_client.h"
#include "type_descriptor.h"


using namespace testing::ext;
using namespace OHOS::Security::AccessToken;
using namespace OHOS::UDMF;
using namespace OHOS;
namespace OHOS::Test {
class UtdClientTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void UtdClientTest::SetUpTestCase()
{
}

void UtdClientTest::TearDownTestCase()
{
}

void UtdClientTest::SetUp()
{
}

void UtdClientTest::TearDown()
{
}

/**
* @tc.name: GetTypeDescriptor001
* @tc.desc: Normal testcase of GetTypeDescriptor
* @tc.type: FUNC
*/
HWTEST_F(UtdClientTest, GetTypeDescriptor001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetTypeDescriptor001 begin.");

    std::shared_ptr<TypeDescriptor> descriptor;
    std::string typeId = "com.amazon.azw3";
    auto status = UtdClient::GetInstance().GetTypeDescriptor(typeId, descriptor);
    EXPECT_EQ(status, E_OK);
    EXPECT_EQ(descriptor->GetTypeId(), typeId);
    EXPECT_EQ(*(descriptor->GetBelongingToTypes().begin()), "general.ebook");
    EXPECT_EQ(descriptor->GetDescription(), "AZW3 ebook.");
    EXPECT_EQ(descriptor->GetIconFile(), "");
    EXPECT_EQ(*(descriptor->GetFilenameExtensions().begin()), ".azw3");
    EXPECT_EQ(*(descriptor->GetMimeTypes().begin()), "application/vnd.amazon.mobi8-ebook");
    LOG_INFO(UDMF_TEST, "GetTypeDescriptor001 end.");
}

/**
* @tc.name: GetTypeDescriptor002
* @tc.desc: Negative test case, invalid typeId argument, returns nullptr
* @tc.type: FUNC
*/
HWTEST_F(UtdClientTest, GetTypeDescriptor002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetTypeDescriptor002 begin.");

    std::shared_ptr<TypeDescriptor> descriptor;
    std::string typeId = "";
    auto status = UtdClient::GetInstance().GetTypeDescriptor(typeId, descriptor);
    EXPECT_EQ(status, E_OK);
    EXPECT_EQ(descriptor, nullptr);
    LOG_INFO(UDMF_TEST, "GetTypeDescriptor002 end.");
}

/**
* @tc.name: GetTypeDescriptor003
* @tc.desc: Negative test case, invalid typeId argument, returns nullptr
* @tc.type: FUNC
*/
HWTEST_F(UtdClientTest, GetTypeDescriptor003, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetTypeDescriptor003 begin.");

    std::shared_ptr<TypeDescriptor> descriptor;
    std::string typeId = "12345";
    auto status = UtdClient::GetInstance().GetTypeDescriptor(typeId, descriptor);
    EXPECT_EQ(status, E_OK);
    EXPECT_EQ(descriptor, nullptr);
    LOG_INFO(UDMF_TEST, "GetTypeDescriptor003 end.");
}

/**
* @tc.name: GetTypeDescriptor004
* @tc.desc: Normal testcase of GetTypeDescriptor
* @tc.type: FUNC
*/
HWTEST_F(UtdClientTest, GetTypeDescriptor004, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetTypeDescriptor004 begin.");

    std::shared_ptr<TypeDescriptor> descriptor;
    std::string typeId = "org.gnu.gnu-zip-archive";
    auto status = UtdClient::GetInstance().GetTypeDescriptor(typeId, descriptor);
    EXPECT_EQ(status, E_OK);
    EXPECT_EQ(descriptor->GetTypeId(), typeId);
    EXPECT_EQ(*(descriptor->GetBelongingToTypes().begin()), "general.archive");
    EXPECT_EQ(descriptor->GetDescription(), "Gzip archive.");
    EXPECT_EQ(descriptor->GetIconFile(), "sys.media.ohos_ic_normal_white_grid_compress");
    LOG_INFO(UDMF_TEST, "GetTypeDescriptor004 end.");
}

/**
* @tc.name: GetTypeDescriptor005
* @tc.desc: Negative test case, invalid typeId argument, returns nullptr
* @tc.type: FUNC
*/
HWTEST_F(UtdClientTest, GetTypeDescriptor005, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetTypeDescriptor005 begin.");

    std::shared_ptr<TypeDescriptor> descriptor;
    std::string typeId = "...";
    auto status = UtdClient::GetInstance().GetTypeDescriptor(typeId, descriptor);
    EXPECT_EQ(status, E_OK);
    EXPECT_EQ(descriptor, nullptr);
    LOG_INFO(UDMF_TEST, "GetTypeDescriptor005 end.");
}

/**
* @tc.name: GetTypeDescriptor006
* @tc.desc: Normal testcase of GetTypeDescriptor
* @tc.type: FUNC
*/
HWTEST_F(UtdClientTest, GetTypeDescriptor006, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetTypeDescriptor006 begin.");

    std::shared_ptr<TypeDescriptor> descriptor;
    std::string typeId = "general.fax";
    auto status = UtdClient::GetInstance().GetTypeDescriptor(typeId, descriptor);
    EXPECT_EQ(status, E_OK);
    EXPECT_EQ(descriptor->GetTypeId(), typeId);
    EXPECT_EQ(*(descriptor->GetBelongingToTypes().begin()), "general.image");
    EXPECT_EQ(descriptor->GetDescription(), "Base type for fax images.");
    EXPECT_EQ(descriptor->GetIconFile(), "");
    EXPECT_EQ(descriptor->GetFilenameExtensions().empty(), true);
    EXPECT_EQ(descriptor->GetMimeTypes().empty(), true);
    LOG_INFO(UDMF_TEST, "GetTypeDescriptor006 end.");
}

/**
* @tc.name: GetUniformDataTypeByFilenameExtension001
* @tc.desc: Normal testcase of GetUniformDataTypeByFilenameExtension
* @tc.type: FUNC
*/
HWTEST_F(UtdClientTest, GetUniformDataTypeByFilenameExtension001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetUniformDataTypeByFilenameExtension001 begin.");
    std::string filenameExtension = ".azw3";
    std::string blongsToType = "general.ebook";
    std::string currType;
    auto status =
        UtdClient::GetInstance().GetUniformDataTypeByFilenameExtension(filenameExtension, currType, blongsToType);
    EXPECT_EQ(status, E_OK);
    EXPECT_EQ(currType, "com.amazon.azw3");
    LOG_INFO(UDMF_TEST, "GetUniformDataTypeByFilenameExtension001 end.");
}

/**
* @tc.name: GetUniformDataTypeByFilenameExtension002
* @tc.desc: Normal testcase of GetUniformDataTypeByFilenameExtension
* @tc.type: FUNC
*/
HWTEST_F(UtdClientTest, GetUniformDataTypeByFilenameExtension002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetUniformDataTypeByFilenameExtension002 begin.");
    std::string filenameExtension = ".png";
    std::string blongsToType = "general.image";
    std::string currType;
    auto status =
        UtdClient::GetInstance().GetUniformDataTypeByFilenameExtension(filenameExtension, currType, blongsToType);
    EXPECT_EQ(status, E_OK);
    EXPECT_EQ(currType, "general.png");
    LOG_INFO(UDMF_TEST, "GetUniformDataTypeByFilenameExtension002 end.");
}

/**
* @tc.name: GetUniformDataTypeByFilenameExtension003
* @tc.desc: Normal testcase of GetUniformDataTypeByFilenameExtension
* @tc.type: FUNC
*/
HWTEST_F(UtdClientTest, GetUniformDataTypeByFilenameExtension003, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetUniformDataTypeByFilenameExtension003 begin.");
    std::string filenameExtension = ".cpp";
    std::string blongsToType = "general.source-code";
    std::string currType;
    auto status =
        UtdClient::GetInstance().GetUniformDataTypeByFilenameExtension(filenameExtension, currType, blongsToType);
    EXPECT_EQ(status, E_OK);
    EXPECT_EQ(currType, "general.c-plus-plus-source");
    LOG_INFO(UDMF_TEST, "GetUniformDataTypeByFilenameExtension003 end.");
}

/**
* @tc.name: GetUniformDataTypeByFilenameExtension004
* @tc.desc: Abnormal testcase of GetUniformDataTypeByFilenameExtension,
* para empty string, return E_INVALID_PARAMETERS
* @tc.type: FUNC
*/
HWTEST_F(UtdClientTest, GetUniformDataTypeByFilenameExtension004, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetUniformDataTypeByFilenameExtension004 begin.");
    std::string filenameExtension = "";
    std::string blongsToType = "general.plain-text";
    std::string currType;
    auto status =
        UtdClient::GetInstance().GetUniformDataTypeByFilenameExtension(filenameExtension, currType, blongsToType);
    EXPECT_EQ(status, E_INVALID_PARAMETERS);
    LOG_INFO(UDMF_TEST, "GetUniformDataTypeByFilenameExtension004 end.");
}

/**
* @tc.name: GetUniformDataTypeByFilenameExtension005
* @tc.desc: Abnormal testcase of GetUniformDataTypeByFilenameExtension, return invalid parameter
* @tc.type: FUNC
*/
HWTEST_F(UtdClientTest, GetUniformDataTypeByFilenameExtension005, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetUniformDataTypeByFilenameExtension005 begin.");
    std::string filenameExtension = ".test";
    std::string blongsToType = "general.test";
    std::string currType;
    auto status =
        UtdClient::GetInstance().GetUniformDataTypeByFilenameExtension(filenameExtension, currType, blongsToType);
    EXPECT_EQ(status, E_INVALID_PARAMETERS);
    LOG_INFO(UDMF_TEST, "GetUniformDataTypeByFilenameExtension005 end.");
}

/**
* @tc.name: GetUniformDataTypeByFilenameExtension006
* @tc.desc: Normal testcase of GetUniformDataTypeByFilenameExtension
* @tc.type: FUNC
*/
HWTEST_F(UtdClientTest, GetUniformDataTypeByFilenameExtension006, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetUniformDataTypeByFilenameExtension006 begin.");
    std::string filenameExtension = ".mp3";
    std::string blongsToType = "general.object";
    std::string currType;
    auto status =
        UtdClient::GetInstance().GetUniformDataTypeByFilenameExtension(filenameExtension, currType, blongsToType);
    EXPECT_EQ(status, E_OK);
    EXPECT_EQ(currType, "general.mp3");
    LOG_INFO(UDMF_TEST, "GetUniformDataTypeByFilenameExtension006 end.");
}

/**
* @tc.name: GetUniformDataTypeByFilenameExtension007
* @tc.desc: Abnormal testcase of GetUniformDataTypeByFilenameExtension, return invalid parameter
* @tc.type: FUNC
*/
HWTEST_F(UtdClientTest, GetUniformDataTypeByFilenameExtension007, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetUniformDataTypeByFilenameExtension007 begin.");
    std::string filenameExtension = ".mp3";
    std::string blongsToType = "test";
    std::string currType;
    auto status =
        UtdClient::GetInstance().GetUniformDataTypeByFilenameExtension(filenameExtension, currType, blongsToType);
    EXPECT_EQ(status, E_INVALID_PARAMETERS);
    LOG_INFO(UDMF_TEST, "GetUniformDataTypeByFilenameExtension007 end.");
}


/**
* @tc.name: GetUniformDataTypeByFilenameExtension008
* @tc.desc: Abnormal testcase of GetUniformDataTypeByFilenameExtension, return flexible type.
* @tc.type: FUNC
*/
HWTEST_F(UtdClientTest, GetUniformDataTypeByFilenameExtension008, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetUniformDataTypeByFilenameExtension008 begin.");
    std::string filenameExtension = ".auto-image";
    std::string blongsToType = "general.image";
    std::string currType;
    auto status =
        UtdClient::GetInstance().GetUniformDataTypeByFilenameExtension(filenameExtension, currType, blongsToType);
    EXPECT_EQ(status, E_OK);
    std::shared_ptr<TypeDescriptor> descriptor;
    status = UtdClient::GetInstance().GetTypeDescriptor(currType, descriptor);
    EXPECT_EQ(status, E_OK);
    EXPECT_EQ(descriptor->GetTypeId(), currType);
    EXPECT_EQ(*(descriptor->GetBelongingToTypes().begin()), "general.image");
    EXPECT_EQ(descriptor->GetDescription().empty(), true);
    EXPECT_EQ(descriptor->GetIconFile().empty(), true);
    EXPECT_EQ(*(descriptor->GetFilenameExtensions().begin()), ".auto-image");
    EXPECT_EQ(descriptor->GetMimeTypes().empty(), true);
    LOG_INFO(UDMF_TEST, "GetUniformDataTypeByFilenameExtension008 end.");
}

/**
* @tc.name: GetUniformDataTypeByMIMEType001
* @tc.desc: Normal testcase of GetUniformDataTypeByMIMEType
* @tc.type: FUNC
*/
HWTEST_F(UtdClientTest, GetUniformDataTypeByMIMEType001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetUniformDataTypeByMIMEType001 begin.");
    std::string mimeType = "application/x-mobi8-ebook";
    std::string blongsToType = "general.ebook";
    std::string currType;
    auto status = UtdClient::GetInstance().GetUniformDataTypeByMIMEType(mimeType, currType, blongsToType);
    EXPECT_EQ(status, E_OK);
    EXPECT_EQ(currType, "com.amazon.azw3");
    LOG_INFO(UDMF_TEST, "GetUniformDataTypeByMIMEType001 end.");
}

/**
* @tc.name: GetUniformDataTypeByMIMEType002
* @tc.desc: Normal testcase of GetUniformDataTypeByMIMEType
* @tc.type: FUNC
*/
HWTEST_F(UtdClientTest, GetUniformDataTypeByMIMEType002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetUniformDataTypeByMIMEType002 begin.");
    std::string mimeType = "application/mspowerpoint";
    std::string blongsToType = "general.composite-object";
    std::string currType;
    auto status = UtdClient::GetInstance().GetUniformDataTypeByMIMEType(mimeType, currType, blongsToType);
    EXPECT_EQ(status, E_OK);
    EXPECT_EQ(currType, "com.microsoft.powerpoint.ppt");
    LOG_INFO(UDMF_TEST, "GetUniformDataTypeByMIMEType002 end.");
}

/**
* @tc.name: GetUniformDataTypeByMIMEType003
* @tc.desc: Abnormal testcase of GetUniformDataTypeByMIMEType, return invalid parameter
* @tc.type: FUNC
*/
HWTEST_F(UtdClientTest, GetUniformDataTypeByMIMEType003, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetUniformDataTypeByMIMEType003 begin.");
    std::string mimeType = "test01";
    std::string blongsToType = "";
    std::string currType;
    auto status = UtdClient::GetInstance().GetUniformDataTypeByMIMEType(mimeType, currType, blongsToType);
    EXPECT_EQ(status, E_INVALID_PARAMETERS);
    LOG_INFO(UDMF_TEST, "GetUniformDataTypeByMIMEType003 end.");
}

/**
* @tc.name: GetUniformDataTypeByMIMEType004
* @tc.desc: BelongsTo is invalid, return invalid parameter
* @tc.type: FUNC
*/
HWTEST_F(UtdClientTest, GetUniformDataTypeByMIMEType004, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetUniformDataTypeByMIMEType004 begin.");
    std::string mimeType = "";
    std::string blongsToType = "test02";
    std::string currType;
    auto status = UtdClient::GetInstance().GetUniformDataTypeByMIMEType(mimeType, currType, blongsToType);
    EXPECT_EQ(status, E_INVALID_PARAMETERS);
    LOG_INFO(UDMF_TEST, "GetUniformDataTypeByMIMEType004 end.");
}

/**
* @tc.name: GetUniformDataTypeByMIMEType005
* @tc.desc: BelongsTo is invalid, return invalid parameter
* @tc.type: FUNC
*/
HWTEST_F(UtdClientTest, GetUniformDataTypeByMIMEType005, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetUniformDataTypeByMIMEType005 begin.");
    std::string mimeType = ".pm";
    std::string blongsToType = "test03";
    std::string currType;
    auto status = UtdClient::GetInstance().GetUniformDataTypeByMIMEType(mimeType, currType, blongsToType);
    EXPECT_EQ(status, E_INVALID_PARAMETERS);
    LOG_INFO(UDMF_TEST, "GetUniformDataTypeByMIMEType005 end.");
}

/**
* @tc.name: GetUniformDataTypeByMIMEType006
* @tc.desc: Abnormal testcase of GetUniformDataTypeByMIMEType,
* para empty string, return E_INVALID_PARAMETERS
* @tc.type: FUNC
*/
HWTEST_F(UtdClientTest, GetUniformDataTypeByMIMEType006, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetUniformDataTypeByMIMEType006 begin.");
    std::string mimeType = "";
    std::string blongsToType = "general.entity";
    std::string currType;
    auto status = UtdClient::GetInstance().GetUniformDataTypeByMIMEType(mimeType, currType, blongsToType);
    EXPECT_EQ(status, E_INVALID_PARAMETERS);
    LOG_INFO(UDMF_TEST, "GetUniformDataTypeByMIMEType006 end.");
}

/**
* @tc.name: GetUniformDataTypeByMIMEType007
* @tc.desc: Abnormal testcase of GetUniformDataTypeByMIMEType, return flexible type.
* @tc.type: FUNC
*/
HWTEST_F(UtdClientTest, GetUniformDataTypeByMIMEType007, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetUniformDataTypeByMIMEType007 begin.");
    std::string mimeType = "image/auto-image";
    std::string blongsToType = "general.image";
    std::string currType;
    auto status = UtdClient::GetInstance().GetUniformDataTypeByMIMEType(mimeType, currType, blongsToType);
    EXPECT_EQ(status, E_OK);
    std::shared_ptr<TypeDescriptor> descriptor;
    status = UtdClient::GetInstance().GetTypeDescriptor(currType, descriptor);
    EXPECT_EQ(status, E_OK);
    EXPECT_EQ(descriptor->GetTypeId(), currType);
    EXPECT_EQ(*(descriptor->GetBelongingToTypes().begin()), "general.image");
    EXPECT_EQ(descriptor->GetDescription().empty(), true);
    EXPECT_EQ(descriptor->GetIconFile().empty(), true);
    EXPECT_EQ(descriptor->GetFilenameExtensions().empty(), true);
    EXPECT_EQ(*(descriptor->GetMimeTypes().begin()), "image/auto-image");
    LOG_INFO(UDMF_TEST, "GetUniformDataTypeByMIMEType007 end.");
}


/**
* @tc.name: BelongsTo001
* @tc.desc: Normal testcase of BelongsTo
* @tc.type: FUNC
*/
HWTEST_F(UtdClientTest, BelongsTo001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "BelongsTo001 begin.");
    std::shared_ptr<TypeDescriptor> descriptor;
    std::string typeId = "com.amazon.azw3";
    auto status = UtdClient::GetInstance().GetTypeDescriptor(typeId, descriptor);
    EXPECT_EQ(status, E_OK);
    bool checkRet = false;
    ASSERT_NE(descriptor, nullptr);
    status = descriptor->BelongsTo("general.composite-object", checkRet);
    EXPECT_EQ(status, E_OK);
    EXPECT_EQ(checkRet, true);
    LOG_INFO(UDMF_TEST, "BelongsTo001 end.");
}

/**
* @tc.name: BelongsTo002
* @tc.desc: Normal testcase of BelongsTo
* @tc.type: FUNC
*/
HWTEST_F(UtdClientTest, BelongsTo002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "BelongsTo002 begin.");
    std::shared_ptr<TypeDescriptor> descriptor;
    std::string typeId = "com.amazon.azw3";
    auto status = UtdClient::GetInstance().GetTypeDescriptor(typeId, descriptor);
    EXPECT_EQ(status, E_OK);
    bool checkRet = false;
    ASSERT_NE(descriptor, nullptr);
    status = descriptor->BelongsTo(typeId, checkRet);
    EXPECT_EQ(status, E_OK);
    EXPECT_EQ(checkRet, true);
    LOG_INFO(UDMF_TEST, "BelongsTo002 end.");
}

/**
* @tc.name: BelongsTo003
* @tc.desc: Normal testcase of BelongsTo
* @tc.type: FUNC
*/
HWTEST_F(UtdClientTest, BelongsTo003, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "BelongsTo003 begin.");
    std::shared_ptr<TypeDescriptor> descriptor;
    std::string typeId = "general.tiff";
    auto status = UtdClient::GetInstance().GetTypeDescriptor(typeId, descriptor);
    EXPECT_EQ(status, E_OK);
    bool checkRet = false;
    ASSERT_NE(descriptor, nullptr);
    status = descriptor->BelongsTo("general.media", checkRet);
    EXPECT_EQ(status, E_OK);
    EXPECT_EQ(checkRet, true);
    LOG_INFO(UDMF_TEST, "BelongsTo003 end.");
}

/**
* @tc.name: BelongsTo004
* @tc.desc: Normal testcase of BelongsTo
* @tc.type: FUNC
*/
HWTEST_F(UtdClientTest, BelongsTo004, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "BelongsTo004 begin.");
    std::shared_ptr<TypeDescriptor> descriptor;
    std::string typeId = "general.tiff";
    auto status = UtdClient::GetInstance().GetTypeDescriptor(typeId, descriptor);
    EXPECT_EQ(status, E_OK);
    bool checkRet = false;
    ASSERT_NE(descriptor, nullptr);
    status = descriptor->BelongsTo("general.object", checkRet);
    EXPECT_EQ(status, E_OK);
    EXPECT_EQ(checkRet, true);
    LOG_INFO(UDMF_TEST, "BelongsTo004 end.");
}

/**
* @tc.name: BelongsTo005
* @tc.desc: Abnormal testcase of BelongsTo
* @tc.type: FUNC
*/
HWTEST_F(UtdClientTest, BelongsTo005, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "BelongsTo005 begin.");
    std::shared_ptr<TypeDescriptor> descriptor;
    std::string typeId = "general.c-header";
    auto status = UtdClient::GetInstance().GetTypeDescriptor(typeId, descriptor);
    EXPECT_EQ(status, E_OK);
    bool checkRet = false;
    ASSERT_NE(descriptor, nullptr);
    status = descriptor->BelongsTo("general.script", checkRet);
    EXPECT_EQ(status, E_OK);
    EXPECT_EQ(checkRet, false);
    LOG_INFO(UDMF_TEST, "BelongsTo005 end.");
}

/**
* @tc.name: BelongsTo006
* @tc.desc: BelongsTo is invalid, return invalid parameter
* @tc.type: FUNC
*/
HWTEST_F(UtdClientTest, BelongsTo006, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "BelongsTo006 begin.");
    std::shared_ptr<TypeDescriptor> descriptor;
    std::string typeId = "general.mpeg";
    auto status = UtdClient::GetInstance().GetTypeDescriptor(typeId, descriptor);
    EXPECT_EQ(status, E_OK);
    bool checkRet = false;
    ASSERT_NE(descriptor, nullptr);
    status = descriptor->BelongsTo("test04", checkRet);
    EXPECT_EQ(status, E_INVALID_PARAMETERS);
    EXPECT_EQ(checkRet, false);
    LOG_INFO(UDMF_TEST, "BelongsTo006 end.");
}

/**
* @tc.name: IsLowerLevelType001
* @tc.desc: Normal testcase of IsLowerLevelType
* @tc.type: FUNC
*/
HWTEST_F(UtdClientTest, IsLowerLevelType001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "IsLowerLevelType001 begin.");
    std::shared_ptr<TypeDescriptor> descriptor;
    std::string typeId = "com.amazon.azw3";
    auto status = UtdClient::GetInstance().GetTypeDescriptor(typeId, descriptor);
    EXPECT_EQ(status, E_OK);
    bool checkRet = false;
    ASSERT_NE(descriptor, nullptr);
    status = descriptor->IsLowerLevelType("general.composite-object", checkRet);
    EXPECT_EQ(status, E_OK);
    EXPECT_EQ(checkRet, true);
    LOG_INFO(UDMF_TEST, "IsLowerLevelType001 end.");
}

/**
* @tc.name: IsLowerLevelType002
* @tc.desc: TypeId is "', return invalid parameter
* @tc.type: FUNC
*/
HWTEST_F(UtdClientTest, IsLowerLevelType002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "IsLowerLevelType002 begin.");
    std::shared_ptr<TypeDescriptor> descriptor;
    std::string typeId = "general.object";
    auto status = UtdClient::GetInstance().GetTypeDescriptor(typeId, descriptor);
    EXPECT_EQ(status, E_OK);
    bool checkRet = false;
    ASSERT_NE(descriptor, nullptr);
    status = descriptor->IsLowerLevelType("", checkRet);
    EXPECT_EQ(status, Status::E_INVALID_PARAMETERS);
    EXPECT_EQ(checkRet, false);
    LOG_INFO(UDMF_TEST, "IsLowerLevelType002 end.");
}

/**
* @tc.name: IsLowerLevelType003
* @tc.desc: Normal testcase of IsLowerLevelType
* @tc.type: FUNC
*/
HWTEST_F(UtdClientTest, IsLowerLevelType003, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "IsLowerLevelType003 begin.");
    std::shared_ptr<TypeDescriptor> descriptor;
    std::string typeId = "com.microsoft.bmp";
    auto status = UtdClient::GetInstance().GetTypeDescriptor(typeId, descriptor);
    EXPECT_EQ(status, E_OK);
    bool checkRet = false;
    ASSERT_NE(descriptor, nullptr);
    status = descriptor->IsLowerLevelType("general.object", checkRet);
    EXPECT_EQ(status, E_OK);
    EXPECT_EQ(checkRet, true);
    LOG_INFO(UDMF_TEST, "IsLowerLevelType003 end.");
}

/**
* @tc.name: IsLowerLevelType004
* @tc.desc: Abnormal testcase of IsLowerLevelType, the two values are equal
* @tc.type: FUNC
*/
HWTEST_F(UtdClientTest, IsLowerLevelType004, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "IsLowerLevelType004 begin.");
    std::shared_ptr<TypeDescriptor> descriptor;
    std::string typeId = "com.amazon.azw3";
    auto status = UtdClient::GetInstance().GetTypeDescriptor(typeId, descriptor);
    EXPECT_EQ(status, E_OK);
    bool checkRet = false;
    ASSERT_NE(descriptor, nullptr);
    status = descriptor->IsLowerLevelType("com.amazon.azw3", checkRet);
    EXPECT_EQ(status, E_OK);
    EXPECT_EQ(checkRet, false);
    LOG_INFO(UDMF_TEST, "IsLowerLevelType004 end.");
}

/**
* @tc.name: IsHigherLevelType001
* @tc.desc: Normal testcase of IsHigherLevelType
* @tc.type: FUNC
*/
HWTEST_F(UtdClientTest, IsHigherLevelType001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "IsHigherLevelType001 begin.");
    std::shared_ptr<TypeDescriptor> descriptor;
    std::string typeId = "general.composite-object";
    auto status = UtdClient::GetInstance().GetTypeDescriptor(typeId, descriptor);
    EXPECT_EQ(status, E_OK);
    bool checkRet = false;
    ASSERT_NE(descriptor, nullptr);
    status = descriptor->IsHigherLevelType("com.amazon.azw3", checkRet);
    EXPECT_EQ(status, E_OK);
    EXPECT_EQ(checkRet, true);
    LOG_INFO(UDMF_TEST, "IsHigherLevelType001 end.");
}

/**
* @tc.name: IsHigherLevelType002
* @tc.desc: Abnormal testcase of IsHigherLevelType, the two values are equal
* @tc.type: FUNC
*/
HWTEST_F(UtdClientTest, IsHigherLevelType002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "IsHigherLevelType002 begin.");
    std::shared_ptr<TypeDescriptor> descriptor;
    std::string typeId = "com.amazon.azw3";
    auto status = UtdClient::GetInstance().GetTypeDescriptor(typeId, descriptor);
    EXPECT_EQ(status, E_OK);
    bool checkRet = false;
    ASSERT_NE(descriptor, nullptr);
    status = descriptor->IsHigherLevelType("com.amazon.azw3", checkRet);
    EXPECT_EQ(status, E_OK);
    EXPECT_EQ(checkRet, false);
    LOG_INFO(UDMF_TEST, "IsHigherLevelType002 end.");
}

/**
* @tc.name: IsHigherLevelType003
* @tc.desc: Abnormal testcase of IsHigherLevelType
* @tc.type: FUNC
*/
HWTEST_F(UtdClientTest, IsHigherLevelType003, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "IsHigherLevelType003 begin.");
    std::shared_ptr<TypeDescriptor> descriptor;
    std::string typeId = "general.image";
    auto status = UtdClient::GetInstance().GetTypeDescriptor(typeId, descriptor);
    EXPECT_EQ(status, E_OK);
    bool checkRet = false;
    ASSERT_NE(descriptor, nullptr);
    status = descriptor->IsHigherLevelType("general.object", checkRet);
    EXPECT_EQ(status, E_OK);
    EXPECT_EQ(checkRet, false);
    LOG_INFO(UDMF_TEST, "IsHigherLevelType003 end.");
}

/**
* @tc.name: Equals001
* @tc.desc: Abnormal testcase of Equals, two values are different
* @tc.type: FUNC
*/
HWTEST_F(UtdClientTest, Equals001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "Equals001 begin.");
    std::shared_ptr<TypeDescriptor> descriptor1;
    std::string typeId1 =  "com.amazon.azw3";
    auto status = UtdClient::GetInstance().GetTypeDescriptor(typeId1, descriptor1);
    EXPECT_EQ(status, E_OK);
    std::string typeId2 = "general.composite-object";
    std::shared_ptr<TypeDescriptor> descriptor2;
    status = UtdClient::GetInstance().GetTypeDescriptor(typeId2, descriptor2);
    EXPECT_EQ(status, E_OK);
    bool ret = descriptor1->Equals(descriptor2);
    EXPECT_EQ(ret, false);
    LOG_INFO(UDMF_TEST, "Equals001 end.");
}

/**
* @tc.name: Equals002
* @tc.desc: Normal testcase of Equals
* @tc.type: FUNC
*/
HWTEST_F(UtdClientTest, Equals002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "Equals002 begin.");
    std::shared_ptr<TypeDescriptor> descriptor1;
    std::string typeId1 =  "com.amazon.azw3";
    auto status = UtdClient::GetInstance().GetTypeDescriptor(typeId1, descriptor1);
    EXPECT_EQ(status, E_OK);
    std::string typeId2 =  "com.amazon.azw3";
    std::shared_ptr<TypeDescriptor> descriptor2;
    status = UtdClient::GetInstance().GetTypeDescriptor(typeId2, descriptor2);
    EXPECT_EQ(status, E_OK);
    bool ret = descriptor1->Equals(descriptor2);
    EXPECT_EQ(ret, true);
    LOG_INFO(UDMF_TEST, "Equals002 end.");
}

/**
* @tc.name: TypeDescriptorGetAttr001
* @tc.desc: Normal testcase of TypeDescriptorGetAttr
* @tc.type: FUNC
*/
HWTEST_F(UtdClientTest, TypeDescriptorGetAttr001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "TypeDescriptorGetAttr001 begin.");
    std::shared_ptr<TypeDescriptor> descriptor;
    std::string typeId = "com.amazon.azw3";
    auto status = UtdClient::GetInstance().GetTypeDescriptor(typeId, descriptor);
    EXPECT_EQ(status, E_OK);
    EXPECT_EQ(descriptor->GetTypeId(), typeId);
    EXPECT_EQ(*(descriptor->GetBelongingToTypes().begin()), "general.ebook");
    EXPECT_EQ(descriptor->GetDescription(), "AZW3 ebook.");
    EXPECT_EQ(descriptor->GetIconFile(), "");
    EXPECT_EQ(*(descriptor->GetFilenameExtensions().begin()), ".azw3");
    EXPECT_EQ(*(descriptor->GetMimeTypes().begin()), "application/vnd.amazon.mobi8-ebook");

    LOG_INFO(UDMF_TEST, "TypeDescriptorGetAttr001 end.");
}

/**
* @tc.name: TypeDescriptorGetAttr002
* @tc.desc: Normal testcase of TypeDescriptorGetAttr
* @tc.type: FUNC
*/
HWTEST_F(UtdClientTest, TypeDescriptorGetAttr002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "TypeDescriptorGetAttr002 begin.");
    std::shared_ptr<TypeDescriptor> descriptor;
    std::string typeId = "general.text";
    auto status = UtdClient::GetInstance().GetTypeDescriptor(typeId, descriptor);
    EXPECT_EQ(status, E_OK);
    EXPECT_EQ(descriptor->GetTypeId(), typeId);
    EXPECT_EQ(*(descriptor->GetBelongingToTypes().begin()), "general.object");
    EXPECT_EQ(descriptor->GetDescription(), "Base type for all text.");
    EXPECT_EQ(descriptor->GetIconFile(), "");
    EXPECT_EQ(descriptor->GetFilenameExtensions().empty(), true);
    EXPECT_EQ(*(descriptor->GetMimeTypes().begin()), "text/*");

    LOG_INFO(UDMF_TEST, "TypeDescriptorGetAttr002 end.");
}

/**
* @tc.name: TypeDescriptorGetAttr003
* @tc.desc: Normal testcase of TypeDescriptorGetAttr
* @tc.type: FUNC
*/
HWTEST_F(UtdClientTest, TypeDescriptorGetAttr003, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "TypeDescriptorGetAttr003 begin.");
    std::shared_ptr<TypeDescriptor> descriptor;
    std::string typeId = "general.image";
    auto status = UtdClient::GetInstance().GetTypeDescriptor(typeId, descriptor);
    EXPECT_EQ(status, E_OK);
    EXPECT_EQ(descriptor->GetTypeId(), typeId);
    EXPECT_EQ(*(descriptor->GetBelongingToTypes().begin()), "general.media");
    EXPECT_EQ(descriptor->GetDescription(), "Base type for images.");
    EXPECT_EQ(descriptor->GetIconFile(), "sys.media.ohos_ic_normal_white_grid_image");
    EXPECT_EQ(descriptor->GetFilenameExtensions().empty(), true);
    EXPECT_EQ(*(descriptor->GetMimeTypes().begin()), "image/*");

    LOG_INFO(UDMF_TEST, "TypeDescriptorGetAttr003 end.");
}

/**
* @tc.name: TypeDescriptorGetAttr004
* @tc.desc: Normal testcase of TypeDescriptorGetAttr
* @tc.type: FUNC
*/
HWTEST_F(UtdClientTest, TypeDescriptorGetAttr004, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "TypeDescriptorGetAttr004 begin.");
    std::shared_ptr<TypeDescriptor> descriptor;
    std::string typeId = "general.video";
    auto status = UtdClient::GetInstance().GetTypeDescriptor(typeId, descriptor);
    EXPECT_EQ(status, E_OK);
    EXPECT_EQ(descriptor->GetTypeId(), typeId);
    EXPECT_EQ(*(descriptor->GetBelongingToTypes().begin()), "general.media");
    EXPECT_EQ(descriptor->GetDescription(), "Base type for video.");
    EXPECT_EQ(descriptor->GetIconFile(), "sys.media.ohos_ic_normal_white_grid_video");
    EXPECT_EQ(descriptor->GetFilenameExtensions().empty(), true);
    EXPECT_EQ(*(descriptor->GetMimeTypes().begin()), "video/*");

    LOG_INFO(UDMF_TEST, "TypeDescriptorGetAttr004 end.");
}

/**
* @tc.name: TypeDescriptorGetAttr005
* @tc.desc: Normal testcase of TypeDescriptorGetAttr
* @tc.type: FUNC
*/
HWTEST_F(UtdClientTest, TypeDescriptorGetAttr005, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "TypeDescriptorGetAttr005 begin.");
    std::shared_ptr<TypeDescriptor> descriptor;
    std::string typeId = "general.audio";
    auto status = UtdClient::GetInstance().GetTypeDescriptor(typeId, descriptor);
    EXPECT_EQ(status, E_OK);
    EXPECT_EQ(descriptor->GetTypeId(), typeId);
    EXPECT_EQ(*(descriptor->GetBelongingToTypes().begin()), "general.media");
    EXPECT_EQ(descriptor->GetDescription(), "Base type for audio.");
    EXPECT_EQ(descriptor->GetIconFile(), "sys.media.ohos_ic_normal_white_grid_audio");
    EXPECT_EQ(descriptor->GetFilenameExtensions().empty(), true);
    EXPECT_EQ(*(descriptor->GetMimeTypes().begin()), "audio/*");

    LOG_INFO(UDMF_TEST, "TypeDescriptorGetAttr005 end.");
}

/**
* @tc.name: FlexibleType001
* @tc.desc: Normal testcase of flexibleType, flexibleType cmp with preset UTD.
* @tc.type: FUNC
*/
HWTEST_F(UtdClientTest, FlexibleType001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "FlexibleType001 begin.");
    std::string filenameExtension = ".mytext";
    std::string blongsToType = "general.plain-text";
    std::string flexTypeId;
    auto status =
        UtdClient::GetInstance().GetUniformDataTypeByFilenameExtension(filenameExtension, flexTypeId, blongsToType);
    EXPECT_EQ(status, E_OK);
    LOG_INFO(UDMF_TEST, "FlexibleType001, flexTypeId = %{public}s.", flexTypeId.c_str());
    std::shared_ptr<TypeDescriptor> descriptor;
    status = UtdClient::GetInstance().GetTypeDescriptor(flexTypeId, descriptor);
    EXPECT_EQ(status, E_OK);
    EXPECT_EQ(descriptor->GetTypeId(), flexTypeId);
    EXPECT_EQ(*(descriptor->GetBelongingToTypes().begin()), "general.plain-text");
    EXPECT_EQ(descriptor->GetDescription().empty(), true);
    EXPECT_EQ(descriptor->GetIconFile().empty(), true);
    EXPECT_EQ(descriptor->GetMimeTypes().empty(), true);
    EXPECT_EQ(*(descriptor->GetFilenameExtensions().begin()), ".mytext");
    bool checkRet = false;
    ASSERT_NE(descriptor, nullptr);
    status = descriptor->IsHigherLevelType("general.object", checkRet);    //  cmp with gengral type.
    EXPECT_EQ(status, E_OK);
    EXPECT_EQ(checkRet, false);
    LOG_INFO(UDMF_TEST, "FlexibleType001 end.");
}

/**
* @tc.name: FlexibleType002
* @tc.desc: Normal testcase of flexibleType, flexibleType cmp with preset UTD.
* @tc.type: FUNC
*/
HWTEST_F(UtdClientTest, FlexibleType002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "FlexibleType002 begin.");
    std::string filenameExtension = ".mytext";
    std::string blongsToType = "general.plain-text";
    std::string flexTypeId1;
    auto status =
        UtdClient::GetInstance().GetUniformDataTypeByFilenameExtension(filenameExtension, flexTypeId1, blongsToType);
    EXPECT_EQ(status, E_OK);
    LOG_INFO(UDMF_TEST, "FlexibleType002, flexTypeId1 = %{public}s.", flexTypeId1.c_str());
    std::shared_ptr<TypeDescriptor> descriptor1;
    status = UtdClient::GetInstance().GetTypeDescriptor(flexTypeId1, descriptor1);
    EXPECT_EQ(status, E_OK);
    
    std::string filenameExtension2 = ".myvideo";
    std::string blongsToType2 = "general.video";
    std::string flexTypeId2;
    status =
        UtdClient::GetInstance().GetUniformDataTypeByFilenameExtension(filenameExtension2, flexTypeId2, blongsToType2);
    EXPECT_EQ(status, E_OK);
    LOG_INFO(UDMF_TEST, "FlexibleType002, flexTypeId2 = %{public}s.", flexTypeId2.c_str());
    std::shared_ptr<TypeDescriptor> descriptor2;
    status = UtdClient::GetInstance().GetTypeDescriptor(flexTypeId2, descriptor2);
    EXPECT_EQ(status, E_OK);
    EXPECT_EQ(descriptor2->GetTypeId(), flexTypeId2);
    EXPECT_EQ(*(descriptor2->GetBelongingToTypes().begin()), "general.video");
    EXPECT_EQ(descriptor2->GetDescription().empty(), true);
    EXPECT_EQ(descriptor2->GetIconFile().empty(), true);
    EXPECT_EQ(descriptor2->GetMimeTypes().empty(), true);
    EXPECT_EQ(*(descriptor2->GetFilenameExtensions().begin()), ".myvideo");
    bool checkRet = false;
    ASSERT_NE(descriptor2, nullptr);
    status = descriptor2->IsHigherLevelType(flexTypeId2, checkRet);   //  cmp with flexbile type.
    EXPECT_EQ(status, E_OK);
    EXPECT_EQ(checkRet, false);
    LOG_INFO(UDMF_TEST, "FlexibleType002 end.");
}

/**
* @tc.name: FlexibleType001
* @tc.desc: Normal testcase of flexibleType, flexibleType cmp with preset UTD.
* @tc.type: FUNC
*/
HWTEST_F(UtdClientTest, FlexibleType003, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "FlexibleType003 begin.");
    std::string filenameExtension = ".mytext";
    std::string blongsToType = "general.plain-text";
    std::string flexTypeId;
    auto status =
        UtdClient::GetInstance().GetUniformDataTypeByFilenameExtension(filenameExtension, flexTypeId, blongsToType);
    EXPECT_EQ(status, E_OK);
    LOG_INFO(UDMF_TEST, "FlexibleType003, flexTypeId = %{public}s.", flexTypeId.c_str());
    std::shared_ptr<TypeDescriptor> descriptor;
    status = UtdClient::GetInstance().GetTypeDescriptor(flexTypeId, descriptor);
    EXPECT_EQ(status, E_OK);
    EXPECT_EQ(descriptor->GetTypeId(), flexTypeId);
    EXPECT_EQ(*(descriptor->GetBelongingToTypes().begin()), "general.plain-text");
    EXPECT_EQ(descriptor->GetDescription().empty(), true);
    EXPECT_EQ(descriptor->GetIconFile().empty(), true);
    EXPECT_EQ(descriptor->GetMimeTypes().empty(), true);
    EXPECT_EQ(*(descriptor->GetFilenameExtensions().begin()), ".mytext");
    bool checkRet = false;
    ASSERT_NE(descriptor, nullptr);
    status = descriptor->IsHigherLevelType("general.invildType", checkRet);    //  cmp with invildType type.
    EXPECT_EQ(status, E_INVALID_PARAMETERS);
    EXPECT_EQ(checkRet, false);
    LOG_INFO(UDMF_TEST, "FlexibleType003 end.");
}


/**
* @tc.name: FlexibleType011
* @tc.desc: Normal testcase of flexibleType, flexibleType cmp with preset UTD.
* @tc.type: FUNC
*/
HWTEST_F(UtdClientTest, FlexibleType011, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "FlexibleType011 begin.");
    std::string filenameExtension = ".mytext";
    std::string blongsToType = "general.plain-text";
    std::string flexTypeId;
    auto status =
        UtdClient::GetInstance().GetUniformDataTypeByFilenameExtension(filenameExtension, flexTypeId, blongsToType);
    EXPECT_EQ(status, E_OK);
    LOG_INFO(UDMF_TEST, "FlexibleType011, flexTypeId = %{public}s.", flexTypeId.c_str());
    std::shared_ptr<TypeDescriptor> descriptor;
    status = UtdClient::GetInstance().GetTypeDescriptor(flexTypeId, descriptor);
    EXPECT_EQ(status, E_OK);
    EXPECT_EQ(descriptor->GetTypeId(), flexTypeId);
    EXPECT_EQ(*(descriptor->GetBelongingToTypes().begin()), "general.plain-text");
    EXPECT_EQ(descriptor->GetDescription().empty(), true);
    EXPECT_EQ(descriptor->GetIconFile().empty(), true);
    EXPECT_EQ(descriptor->GetMimeTypes().empty(), true);
    EXPECT_EQ(*(descriptor->GetFilenameExtensions().begin()), ".mytext");
    bool checkRet = false;
    ASSERT_NE(descriptor, nullptr);
    status = descriptor->IsLowerLevelType("general.object", checkRet);
    EXPECT_EQ(status, E_OK);
    EXPECT_EQ(checkRet, true);
    LOG_INFO(UDMF_TEST, "FlexibleType011 end.");
}

/**
* @tc.name: FlexibleType012
* @tc.desc: Normal testcase of flexibleType, flexibleType cmp with preset UTD.
* @tc.type: FUNC
*/
HWTEST_F(UtdClientTest, FlexibleType012, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "FlexibleType012 begin.");
    std::string filenameExtension = ".mytext";
    std::string blongsToType = "general.plain-text";
    std::string flexTypeId;
    auto status =
        UtdClient::GetInstance().GetUniformDataTypeByFilenameExtension(filenameExtension, flexTypeId, blongsToType);
    EXPECT_EQ(status, E_OK);
    LOG_INFO(UDMF_TEST, "FlexibleType012, flexTypeId = %{public}s.", flexTypeId.c_str());
    std::shared_ptr<TypeDescriptor> descriptor;
    status = UtdClient::GetInstance().GetTypeDescriptor(flexTypeId, descriptor);
    EXPECT_EQ(status, E_OK);
    EXPECT_EQ(descriptor->GetTypeId(), flexTypeId);
    EXPECT_EQ(*(descriptor->GetBelongingToTypes().begin()), "general.plain-text");
    EXPECT_EQ(descriptor->GetDescription().empty(), true);
    EXPECT_EQ(descriptor->GetIconFile().empty(), true);
    EXPECT_EQ(descriptor->GetMimeTypes().empty(), true);
    EXPECT_EQ(*(descriptor->GetFilenameExtensions().begin()), ".mytext");
    bool checkRet = false;
    ASSERT_NE(descriptor, nullptr);
    status = descriptor->IsLowerLevelType("general.video", checkRet);
    EXPECT_EQ(status, E_OK);
    EXPECT_EQ(checkRet, false);
    LOG_INFO(UDMF_TEST, "FlexibleType012 end.");
}

/**
* @tc.name: FlexibleType013
* @tc.desc: Normal testcase of flexibleType, flexibleType cmp with preset UTD.
* @tc.type: FUNC
*/
HWTEST_F(UtdClientTest, FlexibleType013, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "FlexibleType013 begin.");
    std::string filenameExtension = ".mytext";
    std::string blongsToType = "general.plain-text";
    std::string flexTypeId1;
    auto status =
        UtdClient::GetInstance().GetUniformDataTypeByFilenameExtension(filenameExtension, flexTypeId1, blongsToType);
    EXPECT_EQ(status, E_OK);
    LOG_INFO(UDMF_TEST, "FlexibleType013, flexTypeId1 = %{public}s.", flexTypeId1.c_str());
    std::shared_ptr<TypeDescriptor> descriptor1;
    status = UtdClient::GetInstance().GetTypeDescriptor(flexTypeId1, descriptor1);
    EXPECT_EQ(status, E_OK);
    
    std::string filenameExtension2 = ".myvideo";
    std::string blongsToType2 = "general.video";
    std::string flexTypeId2;
    status =
        UtdClient::GetInstance().GetUniformDataTypeByFilenameExtension(filenameExtension2, flexTypeId2, blongsToType2);
    EXPECT_EQ(status, E_OK);
    LOG_INFO(UDMF_TEST, "FlexibleType013, flexTypeId2 = %{public}s.", flexTypeId2.c_str());
    bool checkRet = false;
    ASSERT_NE(descriptor1, nullptr);
    status = descriptor1->IsLowerLevelType(flexTypeId2, checkRet);   //  cmp with flexbile type.
    EXPECT_EQ(status, E_OK);
    EXPECT_EQ(checkRet, false);
    LOG_INFO(UDMF_TEST, "FlexibleType013 end.");
}

/**
* @tc.name: FlexibleType014
* @tc.desc: Normal testcase of flexibleType, flexibleType cmp with preset UTD.
* @tc.type: FUNC
*/
HWTEST_F(UtdClientTest, FlexibleType014, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "FlexibleType014 begin.");
    std::string filenameExtension = ".mytext";
    std::string blongsToType = "general.plain-text";
    std::string flexTypeId;
    auto status =
        UtdClient::GetInstance().GetUniformDataTypeByFilenameExtension(filenameExtension, flexTypeId, blongsToType);
    EXPECT_EQ(status, E_OK);
    LOG_INFO(UDMF_TEST, "FlexibleType014, flexTypeId = %{public}s.", flexTypeId.c_str());
    std::shared_ptr<TypeDescriptor> descriptor;
    status = UtdClient::GetInstance().GetTypeDescriptor(flexTypeId, descriptor);
    EXPECT_EQ(status, E_OK);
    EXPECT_EQ(descriptor->GetTypeId(), flexTypeId);
    EXPECT_EQ(*(descriptor->GetBelongingToTypes().begin()), "general.plain-text");
    EXPECT_EQ(descriptor->GetDescription().empty(), true);
    EXPECT_EQ(descriptor->GetIconFile().empty(), true);
    EXPECT_EQ(descriptor->GetMimeTypes().empty(), true);
    EXPECT_EQ(*(descriptor->GetFilenameExtensions().begin()), ".mytext");
    bool checkRet = false;
    ASSERT_NE(descriptor, nullptr);
    status = descriptor->IsLowerLevelType("general.invaildType", checkRet);   // cmp with invaild type.
    EXPECT_EQ(status, E_INVALID_PARAMETERS);
    EXPECT_EQ(checkRet, false);
    LOG_INFO(UDMF_TEST, "FlexibleType014 end.");
}

/**
* @tc.name: FlexibleType021
* @tc.desc: Normal testcase of flexibleType, flexibleType cmp with preset UTD.
* @tc.type: FUNC
*/
HWTEST_F(UtdClientTest, FlexibleType021, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "FlexibleType021 begin.");
    std::string filenameExtension = ".mytext";
    std::string blongsToType = "general.plain-text";
    std::string flexTypeId;
    auto status =
        UtdClient::GetInstance().GetUniformDataTypeByFilenameExtension(filenameExtension, flexTypeId, blongsToType);
    EXPECT_EQ(status, E_OK);
    LOG_INFO(UDMF_TEST, "FlexibleType021, flexTypeId = %{public}s.", flexTypeId.c_str());
    std::shared_ptr<TypeDescriptor> descriptor;
    status = UtdClient::GetInstance().GetTypeDescriptor(flexTypeId, descriptor);
    EXPECT_EQ(status, E_OK);
    EXPECT_EQ(descriptor->GetTypeId(), flexTypeId);
    EXPECT_EQ(*(descriptor->GetBelongingToTypes().begin()), "general.plain-text");
    EXPECT_EQ(descriptor->GetDescription().empty(), true);
    EXPECT_EQ(descriptor->GetIconFile().empty(), true);
    EXPECT_EQ(descriptor->GetMimeTypes().empty(), true);
    EXPECT_EQ(*(descriptor->GetFilenameExtensions().begin()), ".mytext");
    bool checkRet = false;
    ASSERT_NE(descriptor, nullptr);
    status = descriptor->BelongsTo("general.object", checkRet);
    EXPECT_EQ(status, E_OK);
    EXPECT_EQ(checkRet, true);
    LOG_INFO(UDMF_TEST, "FlexibleType021 end.");
}

/**
* @tc.name: FlexibleType022
* @tc.desc: Normal testcase of flexibleType, flexibleType cmp with preset UTD.
* @tc.type: FUNC
*/
HWTEST_F(UtdClientTest, FlexibleType022, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "FlexibleType022 begin.");
    std::string filenameExtension = ".mytext";
    std::string blongsToType = "general.plain-text";
    std::string flexTypeId;
    auto status =
        UtdClient::GetInstance().GetUniformDataTypeByFilenameExtension(filenameExtension, flexTypeId, blongsToType);
    EXPECT_EQ(status, E_OK);
    LOG_INFO(UDMF_TEST, "FlexibleType022, flexTypeId = %{public}s.", flexTypeId.c_str());
    std::shared_ptr<TypeDescriptor> descriptor;
    status = UtdClient::GetInstance().GetTypeDescriptor(flexTypeId, descriptor);
    EXPECT_EQ(status, E_OK);
    EXPECT_EQ(descriptor->GetTypeId(), flexTypeId);
    EXPECT_EQ(*(descriptor->GetBelongingToTypes().begin()), "general.plain-text");
    EXPECT_EQ(descriptor->GetDescription().empty(), true);
    EXPECT_EQ(descriptor->GetIconFile().empty(), true);
    EXPECT_EQ(descriptor->GetMimeTypes().empty(), true);
    EXPECT_EQ(*(descriptor->GetFilenameExtensions().begin()), ".mytext");
    bool checkRet = false;
    ASSERT_NE(descriptor, nullptr);
    status = descriptor->BelongsTo(flexTypeId, checkRet);   // cmp with self.
    EXPECT_EQ(status, E_OK);
    EXPECT_EQ(checkRet, true);
    LOG_INFO(UDMF_TEST, "FlexibleType022 end.");
}

/**
* @tc.name: FlexibleType023
* @tc.desc: Normal testcase of flexibleType, flexibleType cmp with preset UTD.
* @tc.type: FUNC
*/
HWTEST_F(UtdClientTest, FlexibleType023, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "FlexibleType023 begin.");
    std::string filenameExtension = ".mytext";
    std::string blongsToType = "general.plain-text";
    std::string flexTypeId1;
    auto status =
        UtdClient::GetInstance().GetUniformDataTypeByFilenameExtension(filenameExtension, flexTypeId1, blongsToType);
    EXPECT_EQ(status, E_OK);
    LOG_INFO(UDMF_TEST, "FlexibleType023, flexTypeId1 = %{public}s.", flexTypeId1.c_str());
    std::shared_ptr<TypeDescriptor> descriptor1;
    status = UtdClient::GetInstance().GetTypeDescriptor(flexTypeId1, descriptor1);
    EXPECT_EQ(status, E_OK);
    
    std::string filenameExtension2 = ".myvideo";
    std::string blongsToType2 = "general.video";
    std::string flexTypeId2;
    status =
        UtdClient::GetInstance().GetUniformDataTypeByFilenameExtension(filenameExtension2, flexTypeId2, blongsToType2);
    EXPECT_EQ(status, E_OK);
    LOG_INFO(UDMF_TEST, "FlexibleType023, flexTypeId2 = %{public}s.", flexTypeId2.c_str());
    bool checkRet = false;
    ASSERT_NE(descriptor1, nullptr);
    status = descriptor1->BelongsTo(flexTypeId2, checkRet);   //  cmp with flexbile type.
    EXPECT_EQ(status, E_OK);
    EXPECT_EQ(checkRet, false);
    LOG_INFO(UDMF_TEST, "FlexibleType023 end.");
}


/**
* @tc.name: FlexibleType024
* @tc.desc: Normal testcase of flexibleType, flexibleType cmp with preset UTD.
* @tc.type: FUNC
*/
HWTEST_F(UtdClientTest, FlexibleType024, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "FlexibleType024 begin.");
    std::string filenameExtension = ".mytext";
    std::string blongsToType = "general.plain-text";
    std::string flexTypeId;
    auto status =
        UtdClient::GetInstance().GetUniformDataTypeByFilenameExtension(filenameExtension, flexTypeId, blongsToType);
    EXPECT_EQ(status, E_OK);
    LOG_INFO(UDMF_TEST, "FlexibleType024, flexTypeId = %{public}s.", flexTypeId.c_str());
    std::shared_ptr<TypeDescriptor> descriptor;
    status = UtdClient::GetInstance().GetTypeDescriptor(flexTypeId, descriptor);
    EXPECT_EQ(status, E_OK);
    EXPECT_EQ(descriptor->GetTypeId(), flexTypeId);
    EXPECT_EQ(*(descriptor->GetBelongingToTypes().begin()), "general.plain-text");
    EXPECT_EQ(descriptor->GetDescription().empty(), true);
    EXPECT_EQ(descriptor->GetIconFile().empty(), true);
    EXPECT_EQ(descriptor->GetMimeTypes().empty(), true);
    EXPECT_EQ(*(descriptor->GetFilenameExtensions().begin()), ".mytext");
    bool checkRet = false;
    ASSERT_NE(descriptor, nullptr);
    status = descriptor->BelongsTo("general.invaildType", checkRet);   // cmp with invaild type.
    EXPECT_EQ(status, E_INVALID_PARAMETERS);
    LOG_INFO(UDMF_TEST, "FlexibleType024 end.");
}
} // OHOS::Test