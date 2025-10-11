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
#define LOG_TAG "DataProviderImplTest"

#include <unistd.h>
#include <gtest/gtest.h>
#include <string>

#include "logger.h"
#include "data_provider_impl.h"

using namespace testing::ext;
using namespace OHOS::UDMF;
using namespace OHOS;
namespace OHOS::Test {
using namespace std;

class DataProviderImplTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void DataProviderImplTest::SetUpTestCase()
{
}

void DataProviderImplTest::TearDownTestCase()
{
}

void DataProviderImplTest::SetUp()
{
}

void DataProviderImplTest::TearDown()
{
}

/**
* @tc.name: GetInnerProvider001
* @tc.desc: Normal testcase of GetInnerProvider
* @tc.type: FUNC
*/
HWTEST_F(DataProviderImplTest, GetInnerProvider001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetInnerProvider001 begin.");
    DataProviderImpl dataProviderImpl;
    dataProviderImpl.innerProvider_ = OH_UdmfRecordProvider_Create();
    OH_UdmfRecordProvider* ret = dataProviderImpl.GetInnerProvider();
    EXPECT_EQ(ret, dataProviderImpl.innerProvider_);
    LOG_INFO(UDMF_TEST, "GetInnerProvider001 end.");
}

/**
* @tc.name: GetValueByType001
* @tc.desc: Normal testcase of GetValueByType
* @tc.type: FUNC
*/
HWTEST_F(DataProviderImplTest, GetValueByType001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetValueByType001 begin.");
    const std::string utdId;
    DataProviderImpl dataProviderImpl;
    ValueType ret = dataProviderImpl.GetValueByType(utdId);
    EXPECT_TRUE(std::holds_alternative<std::monostate>(ret));
    LOG_INFO(UDMF_TEST, "GetValueByType001 end.");
}
} // OHOS::Test