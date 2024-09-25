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
#define LOG_TAG "SystemDefinedRecordTest"

#include <unistd.h>
#include <gtest/gtest.h>
#include <string>

#include "logger.h"
#include "system_defined_record.h"

using namespace testing::ext;
using namespace OHOS::UDMF;
using namespace OHOS;
namespace OHOS::Test {
using namespace std;

class SystemDefinedRecordTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void SystemDefinedRecordTest::SetUpTestCase()
{
}

void SystemDefinedRecordTest::TearDownTestCase()
{
}

void SystemDefinedRecordTest::SetUp()
{
}

void SystemDefinedRecordTest::TearDown()
{
}

/**
* @tc.name: AddProperty001
* @tc.desc: Normal testcase of AddProperty
* @tc.type: FUNC
*/
HWTEST_F(SystemDefinedRecordTest, AddProperty001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "AddProperty001 begin.");
    const std::string property = "first";
    UDVariant value = 0;
    SystemDefinedRecord systemDefinedRecord;
    systemDefinedRecord.value_ = std::make_shared<Object>();
    systemDefinedRecord.AddProperty(property, value);
    auto object = std::get<std::shared_ptr<Object>>(systemDefinedRecord.value_);
    auto details = std::get<std::shared_ptr<Object>>(object->value_[DETAILS]);
    systemDefinedRecord.InitObject();
    EXPECT_EQ(systemDefinedRecord.details_.size(), 1);
    EXPECT_NE(details->value_.size(), 0);
    LOG_INFO(UDMF_TEST, "AddProperty001 end.");
}

/**
* @tc.name: AddProperty002
* @tc.desc: Normal testcase of AddProperty
* @tc.type: FUNC
*/
HWTEST_F(SystemDefinedRecordTest, AddProperty002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "AddProperty002 begin.");
    UDVariant value = 0;
    SystemDefinedRecord systemDefinedRecord;
    systemDefinedRecord.details_.insert({ "first", "second" });
    const std::string property = "first";
    systemDefinedRecord.value_ = std::make_shared<Object>();
    systemDefinedRecord.AddProperty(property, value);
    auto object = std::get<std::shared_ptr<Object>>(systemDefinedRecord.value_);
    auto details = std::get<std::shared_ptr<Object>>(object->value_[DETAILS]);
    EXPECT_EQ(systemDefinedRecord.details_[property], value);
    EXPECT_NE(details->value_.size(), 0);
    LOG_INFO(UDMF_TEST, "AddProperty002 end.");
}

/**
* @tc.name: GetPropertyByName001
* @tc.desc: Normal testcase of GetPropertyByName
* @tc.type: FUNC
*/
HWTEST_F(SystemDefinedRecordTest, GetPropertyByName001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetPropertyByName001 begin.");
    const std::string property = "first";
    SystemDefinedRecord systemDefinedRecord;
    systemDefinedRecord.details_.insert({ "first", "second" });
    const UDVariant ret = systemDefinedRecord.GetPropertyByName(property);
    EXPECT_EQ(std::get<std::string>(ret), "second");
    LOG_INFO(UDMF_TEST, "GetPropertyByName001 end.");
}

/**
* @tc.name: InitObject001
* @tc.desc: Normal testcase of InitObject
* @tc.type: FUNC
*/
HWTEST_F(SystemDefinedRecordTest, InitObject001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "InitObject001 begin.");
    SystemDefinedRecord systemDefinedRecord;
    systemDefinedRecord.details_.insert({ "first", "second" });
    systemDefinedRecord.InitObject();
    auto object = std::get<std::shared_ptr<Object>>(systemDefinedRecord.value_);
    auto details = std::get<std::shared_ptr<Object>>(object->value_[DETAILS]);
    EXPECT_NE(details->value_.size(), 0);
    LOG_INFO(UDMF_TEST, "InitObject001 end.");
}
} // OHOS::Test