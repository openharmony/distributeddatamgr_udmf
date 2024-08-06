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
#define LOG_TAG "FolderTest"

#include <unistd.h>
#include <gtest/gtest.h>
#include <string>

#include "logger.h"
#include "folder.h"

using namespace testing::ext;
using namespace OHOS::UDMF;
using namespace OHOS;
namespace OHOS::Test {
using namespace std;

class FolderTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void FolderTest::SetUpTestCase()
{
}

void FolderTest::TearDownTestCase()
{
}

void FolderTest::SetUp()
{
}

void FolderTest::TearDown()
{
}

/**
* @tc.name: Folder001
* @tc.desc: Normal testcase of Folder
* @tc.type: FUNC
*/
HWTEST_F(FolderTest, Folder001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "Folder001 begin.");
    UDType type = UDType::ENTITY;
    ValueType value = 0;
    Folder floder(type, value);
    EXPECT_EQ(floder.dataType_, FOLDER);
    LOG_INFO(UDMF_TEST, "Folder001 end.");
}
} // OHOS::Test
