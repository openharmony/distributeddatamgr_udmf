/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
#define LOG_TAG "UdmfConversionTest"

#include <gtest/gtest.h>

#include "logger.h"
#include "udmf_conversion.h"

using namespace testing::ext;
using namespace OHOS::UDMF;
using namespace OHOS;
namespace OHOS::Test {
using namespace std;

class UdmfConversionTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void UdmfConversionTest::SetUpTestCase()
{
}

void UdmfConversionTest::TearDownTestCase()
{
}

void UdmfConversionTest::SetUp()
{
}

void UdmfConversionTest::TearDown()
{
}

/**
* @tc.name: ConvertRecordToSubclass001
* @tc.desc: Normal testcase of ConvertRecordToSubclass
* @tc.type: FUNC
*/
HWTEST_F(UdmfConversionTest, ConvertRecordToSubclass001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "ConvertRecordToSubclass001 begin.");
    std::shared_ptr<UnifiedRecord> record = std::make_shared<UnifiedRecord>();
    UdmfConversion udmfConversion;
    EXPECT_NO_FATAL_FAILURE(udmfConversion.ConvertRecordToSubclass(record));
    LOG_INFO(UDMF_TEST, "ConvertRecordToSubclass001 end.");
}

/**
* @tc.name: ConvertRecordToSubclass002
* @tc.desc: Normal testcase of ConvertRecordToSubclass
* @tc.type: FUNC
*/
HWTEST_F(UdmfConversionTest, ConvertRecordToSubclass002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "ConvertRecordToSubclass002 begin.");
    std::shared_ptr<UnifiedRecord> record = nullptr;
    UdmfConversion udmfConversion;
    EXPECT_NO_FATAL_FAILURE(udmfConversion.ConvertRecordToSubclass(record));
    LOG_INFO(UDMF_TEST, "ConvertRecordToSubclass002 end.");
}
} // OHOS::Test