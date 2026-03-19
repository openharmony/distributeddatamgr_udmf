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
} // OHOS::Test
