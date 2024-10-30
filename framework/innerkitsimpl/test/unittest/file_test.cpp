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
} // OHOS::Test