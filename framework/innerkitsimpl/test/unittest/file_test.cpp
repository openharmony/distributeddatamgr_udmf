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
#define LOG_TAG "FileTest"

#include <unistd.h>
#include <gtest/gtest.h>
#include <string>
#include <cstring>

#include "logger.h"
#include "file.h"
#include "unified_meta.h"

using namespace testing::ext;
using namespace OHOS::UDMF;
using namespace OHOS;
namespace OHOS::Test {
using namespace std;

class FileTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void FileTest::SetUpTestCase()
{
}

void FileTest::TearDownTestCase()
{
}

void FileTest::SetUp()
{
}

void FileTest::TearDown()
{
}

/**
* @tc.name: File001
* @tc.desc: Normal testcase of File
* @tc.type: FUNC
*/
HWTEST_F(FileTest, File001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "File001 begin.");
    UDType type = UDType::ENTITY;
    ValueType value = "string";
    OHOS::UDMF::File file(type, value);
    EXPECT_EQ(file.dataType_, UDType::FILE);
    EXPECT_EQ(file.oriUri_.length(), std::get<std::string>(value).length());
    LOG_INFO(UDMF_TEST, "File001 end.");
}

/**
* @tc.name: File002
* @tc.desc: Normal testcase of File
* @tc.type: FUNC
*/
HWTEST_F(FileTest, File002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "File002 begin.");
    UDType type = UDType::ENTITY;
    ValueType value = 0;
    OHOS::UDMF::File file(type, value);
    EXPECT_EQ(file.dataType_, UDType::FILE);
    EXPECT_EQ(file.oriUri_.length(), 0);
    LOG_INFO(UDMF_TEST, "File002 end.");
}

/**
* @tc.name: File003
* @tc.desc: Verify URI_AUTHORIZATION_POLICIES is absent when not explicitly set
* @tc.type: FUNC
*/
HWTEST_F(FileTest, File003, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "File003 begin.");
    File file("file://com.example.test/data.txt");
    file.InitObject();
    auto value = file.GetValue();
    ASSERT_TRUE(std::holds_alternative<std::shared_ptr<Object>>(value));
    auto object = std::get<std::shared_ptr<Object>>(value);
    ASSERT_NE(object, nullptr);
    EXPECT_EQ(object->value_.find(URI_AUTHORIZATION_POLICIES), object->value_.end());
    LOG_INFO(UDMF_TEST, "File003 end.");
}

/**
* @tc.name: File004
* @tc.desc: Verify explicit NONE policy is preserved as 0
* @tc.type: FUNC
*/
HWTEST_F(FileTest, File004, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "File004 begin.");
    File file("file://com.example.test/data.txt");
    file.SetUriAuthorizationPolicyMask(0);
    file.InitObject();
    auto value = file.GetValue();
    ASSERT_TRUE(std::holds_alternative<std::shared_ptr<Object>>(value));
    auto object = std::get<std::shared_ptr<Object>>(value);
    ASSERT_NE(object, nullptr);
    auto iter = object->value_.find(URI_AUTHORIZATION_POLICIES);
    ASSERT_NE(iter, object->value_.end());
    ASSERT_TRUE(std::holds_alternative<int32_t>(iter->second));
    EXPECT_EQ(std::get<int32_t>(iter->second), 0);

    File fileFromObject(UDType::FILE, value);
    EXPECT_EQ(fileFromObject.GetUriAuthorizationPolicyMask(), 0);
    LOG_INFO(UDMF_TEST, "File004 end.");
}


/**
* @tc.name: File005
* @tc.desc: Test various permission mask combinations
* @tc.type: FUNC
*/
HWTEST_F(FileTest, File005, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "File005 begin.");
    File file("file://com.example.test/data.txt");

    file.SetUriAuthorizationPolicyMask(1);
    EXPECT_EQ(file.GetUriAuthorizationPolicyMask(), 1);

    file.SetUriAuthorizationPolicyMask(2);
    EXPECT_EQ(file.GetUriAuthorizationPolicyMask(), 2);

    file.SetUriAuthorizationPolicyMask(3);
    EXPECT_EQ(file.GetUriAuthorizationPolicyMask(), 3);

    file.SetUriAuthorizationPolicyMask(5);
    EXPECT_EQ(file.GetUriAuthorizationPolicyMask(), 5);

    file.SetUriAuthorizationPolicyMask(7);
    EXPECT_EQ(file.GetUriAuthorizationPolicyMask(), 7);
    LOG_INFO(UDMF_TEST, "File005 end.");
}

/**
* @tc.name: File006
* @tc.desc: Test PERSIST flag normalization (removed when no READ/WRITE)
* @tc.type: FUNC
*/
HWTEST_F(FileTest, File006, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "File006 begin.");
    File file("file://com.example.test/data.txt");

    file.SetUriAuthorizationPolicyMask(4);
    EXPECT_EQ(file.GetUriAuthorizationPolicyMask(), 0);

    file.SetUriAuthorizationPolicyMask(6);
    EXPECT_EQ(file.GetUriAuthorizationPolicyMask(), 6);
    LOG_INFO(UDMF_TEST, "File006 end.");
}

/**
* @tc.name: File007
* @tc.desc: Test File constructor with Object containing negative permission mask
* @tc.type: FUNC
*/
HWTEST_F(FileTest, File007, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "File007 begin.");
    auto object = std::make_shared<Object>();
    object->value_[ORI_URI] = "file://com.example.test/data.txt";
    object->value_[URI_AUTHORIZATION_POLICIES] = -1;

    File file(UDType::FILE, object);
    EXPECT_EQ(file.GetUriAuthorizationPolicyMask(), 0);
    EXPECT_FALSE(file.hasUriAuthorizationPolicyMask_);
    LOG_INFO(UDMF_TEST, "File007 end.");
}

/**
* @tc.name: File008
* @tc.desc: Test File constructor with Object containing valid permission mask
* @tc.type: FUNC
*/
HWTEST_F(FileTest, File008, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "File008 begin.");
    auto object = std::make_shared<Object>();
    object->value_[ORI_URI] = "file://com.example.test/data.txt";
    object->value_[URI_AUTHORIZATION_POLICIES] = 3;

    File file(UDType::FILE, object);
    EXPECT_EQ(file.GetUriAuthorizationPolicyMask(), 3);
    EXPECT_TRUE(file.hasUriAuthorizationPolicyMask_);
    LOG_INFO(UDMF_TEST, "File008 end.");
}

/**
* @tc.name: File009
* @tc.desc: Test SetUriAuthorizationPolicyMask with null Object
* @tc.type: FUNC
*/
HWTEST_F(FileTest, File009, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "File009 begin.");
    File file("file://com.example.test/data.txt");
    file.SetUriAuthorizationPolicyMask(5);

    file.SetUriAuthorizationPolicyMask(7);
    EXPECT_EQ(file.GetUriAuthorizationPolicyMask(), 7);
    LOG_INFO(UDMF_TEST, "File009 end.");
}

/**
* @tc.name: File010
* @tc.desc: Test File constructor with Object containing valid permission mask
* @tc.type: FUNC
*/
HWTEST_F(FileTest, File010, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "File010 begin.");
    auto object = std::make_shared<Object>();
    object->value_[ORI_URI] = "file://com.example.test/data.txt";
    object->value_[URI_AUTHORIZATION_POLICIES] = 5;

    File file(UDType::FILE, object);
    EXPECT_EQ(file.GetUriAuthorizationPolicyMask(), 5);
    EXPECT_TRUE(file.hasUriAuthorizationPolicyMask_);
    LOG_INFO(UDMF_TEST, "File010 end.");
}

/**
* @tc.name: File011
* @tc.desc: Test SetUriAuthorizationPolicyMask with various mask values
* @tc.type: FUNC
*/
HWTEST_F(FileTest, File011, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "File011 begin.");
    File file("file://com.example.test/data.txt");

    file.SetUriAuthorizationPolicyMask(1);
    EXPECT_EQ(file.GetUriAuthorizationPolicyMask(), 1);

    file.SetUriAuthorizationPolicyMask(2);
    EXPECT_EQ(file.GetUriAuthorizationPolicyMask(), 2);

    file.SetUriAuthorizationPolicyMask(3);
    EXPECT_EQ(file.GetUriAuthorizationPolicyMask(), 3);

    file.SetUriAuthorizationPolicyMask(5);
    EXPECT_EQ(file.GetUriAuthorizationPolicyMask(), 5);

    file.SetUriAuthorizationPolicyMask(7);
    EXPECT_EQ(file.GetUriAuthorizationPolicyMask(), 7);

    file.SetUriAuthorizationPolicyMask(0);
    EXPECT_EQ(file.GetUriAuthorizationPolicyMask(), 0);

    LOG_INFO(UDMF_TEST, "File011 end.");
}

/**
* @tc.name: File012
* @tc.desc: Test SetUriAuthorizationPolicyMask with PERSIST normalization
* @tc.type: FUNC
*/
HWTEST_F(FileTest, File012, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "File012 begin.");
    File file("file://com.example.test/data.txt");

    file.SetUriAuthorizationPolicyMask(4);
    EXPECT_EQ(file.GetUriAuthorizationPolicyMask(), 0);

    file.SetUriAuthorizationPolicyMask(6);
    EXPECT_EQ(file.GetUriAuthorizationPolicyMask(), 6);

    LOG_INFO(UDMF_TEST, "File012 end.");
}

/**
* @tc.name: File013
* @tc.desc: Test SetUriAuthorizationPolicyMask with string value
* @tc.type: FUNC
*/
HWTEST_F(FileTest, File013, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "File013 begin.");
    File file("file://com.example.test/data.txt");

    file.SetUriAuthorizationPolicyMask(3);
    file.SetUri("file://com.example.test/data2.txt");
    EXPECT_EQ(file.GetUri(), "file://com.example.test/data2.txt");
    EXPECT_EQ(file.GetUriAuthorizationPolicyMask(), 3);

    LOG_INFO(UDMF_TEST, "File013 end.");
}

/**
* @tc.name: File014
* @tc.desc: Test InitObject with permission mask serialization
* @tc.type: FUNC
*/
HWTEST_F(FileTest, File014, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "File014 begin.");
    File file("file://com.example.test/data.txt");
    file.SetUriAuthorizationPolicyMask(5);
    file.InitObject();

    auto value = file.GetValue();
    ASSERT_TRUE(std::holds_alternative<std::shared_ptr<Object>>(value));
    auto object = std::get<std::shared_ptr<Object>>(value);
    ASSERT_NE(object, nullptr);

    auto iter = object->value_.find(URI_AUTHORIZATION_POLICIES);
    ASSERT_NE(iter, object->value_.end());
    ASSERT_TRUE(std::holds_alternative<int32_t>(iter->second));
    EXPECT_EQ(std::get<int32_t>(iter->second), 5);

    LOG_INFO(UDMF_TEST, "File014 end.");
}

/**
* @tc.name: File015
* @tc.desc: Test InitObject without permission mask
* @tc.type: FUNC
*/
HWTEST_F(FileTest, File015, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "File015 begin.");
    File file("file://com.example.test/data.txt");
    file.InitObject();

    auto value = file.GetValue();
    ASSERT_TRUE(std::holds_alternative<std::shared_ptr<Object>>(value));
    auto object = std::get<std::shared_ptr<Object>>(value);
    ASSERT_NE(object, nullptr);

    auto iter = object->value_.find(URI_AUTHORIZATION_POLICIES);
    EXPECT_EQ(iter, object->value_.end());

    LOG_INFO(UDMF_TEST, "File015 end.");
}
} // OHOS::Test