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
* @tc.desc: getTypeDescriptor
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

    LOG_INFO(UDMF_TEST, "GetTypeDescriptor001 end.");
}

/**
* @tc.name: GetTypeDescriptor002
* @tc.desc: getTypeDescriptor
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
* @tc.name: GetUniformDataTypeByFilenameExtension001
* @tc.desc: GetUniformDataTypeByFilenameExtension
* @tc.type: FUNC
*/
HWTEST_F(UtdClientTest, GetUniformDataTypeByFilenameExtension001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetUniformDataTypeByFilenameExtension001 begin.");
    std::string filenameExtension = ".azw3";
    std::string blongsToType = "general.ebook";
    std::string currType;
    auto status = UtdClient::GetInstance().GetUniformDataTypeByFilenameExtension(filenameExtension, currType,
                                                                                 blongsToType);
    EXPECT_EQ(status, E_OK);
    EXPECT_EQ(currType, "com.amazon.azw3");
    LOG_INFO(UDMF_TEST, "GetUniformDataTypeByFilenameExtension001 end.");
}

/**
* @tc.name: GetUniformDataTypeByMIMEType001
* @tc.desc: GetUniformDataTypeByMIMEType
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
* @tc.name: BelongsTo001
* @tc.desc: BelongsTo
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
* @tc.desc: BelongsTo
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
* @tc.name: IsLowerLevelType001
* @tc.desc: IsLowerLevelType
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
* @tc.name: IsHigherLevelType001
* @tc.desc: IsHigherLevelType
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
* @tc.desc: IsHigherLevelType
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
* @tc.name: Equals001
* @tc.desc: Equals
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
* @tc.desc: Equals
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
* @tc.desc: TypeDescriptorGetAttr
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
} // OHOS::Test