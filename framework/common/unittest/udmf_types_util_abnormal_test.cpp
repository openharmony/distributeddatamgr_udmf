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
#define LOG_TAG "UdmfTypesUtilAbnormalTest"

#include <unistd.h>
#include <string>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "logger.h"
#include "udmf_types_util.h"
#include "unified_meta.h"
#include "text.h"
#include "plain_text.h"
#include "file.h"
#include "image.h"
#include "system_defined_record.h"
#include "system_defined_form.h"
#include "application_defined_record.h"
#include "unified_types.h"
#include "udmf_client.h"

using namespace testing::ext;
using namespace OHOS::UDMF;
using namespace OHOS;
namespace OHOS::Test {
using namespace std;
using namespace testing;

class UdmfTypesUtilAbnormalTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void UdmfTypesUtilAbnormalTest::SetUpTestCase()
{
}

void UdmfTypesUtilAbnormalTest::TearDownTestCase()
{
}

void UdmfTypesUtilAbnormalTest::SetUp()
{
}

void UdmfTypesUtilAbnormalTest::TearDown()
{
}

/**
* @tc.name: Marshalling001
* @tc.desc: Abnrmal testcase of Marshalling, the return value of Writing() is nullptr
* @tc.type: FUNC
*/
HWTEST_F(UdmfTypesUtilAbnormalTest, Marshalling001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "Marshalling001 begin.");
    UnifiedData input;
    std::vector<std::shared_ptr<UnifiedRecord>> inputRecords = {
        std::make_shared<Text>(),
        std::make_shared<PlainText>(),
        std::make_shared<File>(),
        std::make_shared<Image>(),
        std::make_shared<SystemDefinedRecord>(),
        std::make_shared<SystemDefinedForm>(),
        std::make_shared<ApplicationDefinedRecord>()
    };
    input.SetRecords(inputRecords);
    MessageParcel parcel;
    bool ret = ITypesUtil::Marshalling(input, parcel);
    EXPECT_FALSE(ret);
    LOG_INFO(UDMF_TEST, "Marshalling001 end.");
}

/**
* @tc.name: Marshalling002
* @tc.desc: Abnrmal testcase of Marshalling, the return value of Writing() is nullptr
* @tc.type: FUNC
*/
HWTEST_F(UdmfTypesUtilAbnormalTest, Marshalling002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "Marshalling002 begin.");
    UnifiedData unifiedData;
    std::vector<UnifiedData> input = {unifiedData};
    MessageParcel parcel;
    bool ret = ITypesUtil::Marshalling(input, parcel);
    EXPECT_FALSE(ret);
    LOG_INFO(UDMF_TEST, "Marshalling002 end.");
}

/**
* @tc.name: Marshalling003
* @tc.desc: Abnrmal testcase of Marshalling, the return value of Reading() is nullptr
* @tc.type: FUNC
*/
HWTEST_F(UdmfTypesUtilAbnormalTest, Marshalling003, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "Marshalling003 begin.");
    UnifiedData unifiedData;
    std::vector<UnifiedData> input = {unifiedData};
    MessageParcel parcel;
    bool ret = ITypesUtil::Marshalling(input, parcel);
    EXPECT_FALSE(ret);
    LOG_INFO(UDMF_TEST, "Marshalling003 end.");
}

/**
* @tc.name: Unmarshalling001
* @tc.desc: Abnrmal testcase of Unmarshalling, the return value of Reading() is nullptr
* @tc.type: FUNC
*/
HWTEST_F(UdmfTypesUtilAbnormalTest, Unmarshalling001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "Unmarshalling001 begin.");
    UnifiedData unifiedData;
    std::vector<UnifiedData> output = {unifiedData};
    MessageParcel parcel;
    bool ret = ITypesUtil::Unmarshalling(output, parcel);
    EXPECT_FALSE(ret);
    LOG_INFO(UDMF_TEST, "Unmarshalling001 end.");
}
} // OHOS::Test