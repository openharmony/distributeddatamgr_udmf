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
#define LOG_TAG "SystemDefinedFormTest"

#include <unistd.h>
#include <gtest/gtest.h>
#include <string>

#include "logger.h"
#include "system_defined_form.h"

using namespace testing::ext;
using namespace OHOS::UDMF;
using namespace OHOS;
namespace OHOS::Test {
using namespace std;

class SystemDefinedFormTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void SystemDefinedFormTest::SetUpTestCase()
{
}

void SystemDefinedFormTest::TearDownTestCase()
{
}

void SystemDefinedFormTest::SetUp()
{
}

void SystemDefinedFormTest::TearDown()
{
}

/**
* @tc.name: SystemDefinedForm001
* @tc.desc: Normal testcase of SystemDefinedForm
* @tc.type: FUNC
*/
HWTEST_F(SystemDefinedFormTest, SystemDefinedForm001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SystemDefinedForm001 begin.");
    UDType type = UDType::ENTITY;
    ValueType value = 0;
    SystemDefinedForm systemDefinedForm(type, value);
    EXPECT_EQ(systemDefinedForm.dataType_, SYSTEM_DEFINED_FORM);
    LOG_INFO(UDMF_TEST, "SystemDefinedForm001 end.");
}
} // OHOS::Test