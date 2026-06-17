/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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
#define LOG_TAG "GetterSystemTest"

#include <unistd.h>
#include <gtest/gtest.h>
#include <string>

#include "logger.h"
#include "getter_system.h"
#include "udmf_capi_common.h"

using namespace testing::ext;
using namespace OHOS::UDMF;
using namespace OHOS;
namespace OHOS::Test {
using namespace std;

class GetterSystemTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void GetterSystemTest::SetUpTestCase()
{
}

void GetterSystemTest::TearDownTestCase()
{
}

void GetterSystemTest::SetUp()
{
}

void GetterSystemTest::TearDown()
{
}

/**
* @tc.name: GetValueByType001
* @tc.desc: Normal testcase of GetValueByType, base class returns empty ValueType
* @tc.type: FUNC
*/
HWTEST_F(GetterSystemTest, GetValueByType001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetValueByType001 begin.");
    GetterSystem::GeneralGetter getter;
    uint32_t dataId = 0;
    uint32_t recordId = 0;
    std::string utdId = "";
    ValueType value = getter.GetValueByType(dataId, recordId, utdId);
    EXPECT_TRUE(std::holds_alternative<std::monostate>(value));
    LOG_INFO(UDMF_TEST, "GetValueByType001 end.");
}

/**
* @tc.name: GetValueByType002
* @tc.desc: Normal testcase of GetValueByType, with valid parameters
* @tc.type: FUNC
*/
HWTEST_F(GetterSystemTest, GetValueByType002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetValueByType002 begin.");
    GetterSystem::GeneralGetter getter;
    uint32_t dataId = 100;
    uint32_t recordId = 200;
    std::string utdId = "general.file-uri";
    ValueType value = getter.GetValueByType(dataId, recordId, utdId);
    EXPECT_TRUE(std::holds_alternative<std::monostate>(value));
    LOG_INFO(UDMF_TEST, "GetValueByType002 end.");
}

/**
* @tc.name: GetInstance001
* @tc.desc: Normal testcase of GetInstance, singleton pattern
* @tc.type: FUNC
*/
HWTEST_F(GetterSystemTest, GetInstance001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetInstance001 begin.");
    GetterSystem& instance1 = GetterSystem::GetInstance();
    GetterSystem& instance2 = GetterSystem::GetInstance();
    EXPECT_EQ(&instance1, &instance2);
    LOG_INFO(UDMF_TEST, "GetInstance001 end.");
}

/**
* @tc.name: GetGetter001
* @tc.desc: Abnormal testcase of GetGetter, nonexistent creator
* @tc.type: FUNC
*/
HWTEST_F(GetterSystemTest, GetGetter001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetGetter001 begin.");
    GetterSystem::Getter getter = GetterSystem::GetInstance().GetGetter("test");
    EXPECT_EQ(getter, nullptr);
    LOG_INFO(UDMF_TEST, "GetGetter001 end.");
}
} // OHOS::Test
