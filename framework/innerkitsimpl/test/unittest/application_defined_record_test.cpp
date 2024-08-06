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
#define LOG_TAG "ApplicationUtdJsonParserTest"

#include <unistd.h>
#include <gtest/gtest.h>
#include <string>

#include "logger.h"
#include "application_defined_record.h"

using namespace testing::ext;
using namespace OHOS::UDMF;
using namespace OHOS;
namespace OHOS::Test {
using namespace std;

class ApplicationUtdJsonParserTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void ApplicationUtdJsonParserTest::SetUpTestCase()
{
}

void ApplicationUtdJsonParserTest::TearDownTestCase()
{
}

void ApplicationUtdJsonParserTest::SetUp()
{
}

void ApplicationUtdJsonParserTest::TearDown()
{
}

/**
* @tc.name: ApplicationDefinedRecord001
* @tc.desc: Normal testcase of ApplicationDefinedRecord
* @tc.type: FUNC
*/
HWTEST_F(ApplicationUtdJsonParserTest, ApplicationDefinedRecord001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "ApplicationDefinedRecord001 begin.");
    string type("record");
    ApplicationDefinedRecord application(type);
    EXPECT_EQ(application.applicationDefinedType, "record");
    LOG_INFO(UDMF_TEST, "ApplicationDefinedRecord001 end.");
}

/**
* @tc.name: ApplicationDefinedRecord002
* @tc.desc: Normal testcase of ApplicationDefinedRecord
* @tc.type: FUNC
*/
HWTEST_F(ApplicationUtdJsonParserTest, ApplicationDefinedRecord002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "ApplicationDefinedRecord002 begin.");
    string type("record");
    vector<uint8_t> data = vector<uint8_t>();
    ApplicationDefinedRecord application(type, data);
    EXPECT_EQ(application.applicationDefinedType, "record");
    EXPECT_EQ(application.rawData_, data);
    LOG_INFO(UDMF_TEST, "ApplicationDefinedRecord002 end.");
}

/**
* @tc.name: ApplicationDefinedRecord003
* @tc.desc: Normal testcase of ApplicationDefinedRecord
* @tc.type: FUNC
*/
HWTEST_F(ApplicationUtdJsonParserTest, ApplicationDefinedRecord003, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "ApplicationDefinedRecord003 begin.");
    UDType type = UDType::ENTITY;
    vector<uint8_t> vec = {1, 2};
    ApplicationDefinedRecord application(type, vec);
    EXPECT_EQ(application.rawData_.size(), vec.size());
    LOG_INFO(UDMF_TEST, "ApplicationDefinedRecord003 end.");
}

/**
* @tc.name: ApplicationDefinedRecord004
* @tc.desc: Normal testcase of ApplicationDefinedRecord
* @tc.type: FUNC
*/
HWTEST_F(ApplicationUtdJsonParserTest, ApplicationDefinedRecord004, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "ApplicationDefinedRecord004 begin.");
    UDType type = UDType::ENTITY;
    ValueType value = 0;
    ApplicationDefinedRecord application(type, value);
    EXPECT_EQ(application.rawData_.size(), 0);
    LOG_INFO(UDMF_TEST, "ApplicationDefinedRecord004 end.");
}
} // OHOS::Test