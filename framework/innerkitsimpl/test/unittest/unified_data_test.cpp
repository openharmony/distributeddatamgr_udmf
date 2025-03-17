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
#define LOG_TAG "UnifiedDataTest"

#include <unistd.h>
#include <gtest/gtest.h>
#include <string>

#include "logger.h"
#include "udmf_capi_common.h"
#include "udmf_utils.h"
#include "unified_data.h"

using namespace testing::ext;
using namespace OHOS::UDMF;
using namespace OHOS;
namespace OHOS::Test {
using namespace std;

class UnifiedDataTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void UnifiedDataTest::SetUpTestCase()
{
}

void UnifiedDataTest::TearDownTestCase()
{
}

void UnifiedDataTest::SetUp()
{
}

void UnifiedDataTest::TearDown()
{
}

/**
* @tc.name: UnifiedData001
* @tc.desc: Normal testcase of UnifiedData
* @tc.type: FUNC
*/
HWTEST_F(UnifiedDataTest, UnifiedData001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "UnifiedData001 begin.");
    std::shared_ptr<UnifiedDataProperties> properties = std::make_shared<UnifiedDataProperties>();
    UnifiedData unifiedData(properties);
    auto duration = std::chrono::system_clock::now().time_since_epoch();
    EXPECT_EQ(unifiedData.properties_, properties);
    EXPECT_EQ(unifiedData.properties_->timestamp,
        std::chrono::duration_cast<std::chrono::milliseconds>(duration).count());
    LOG_INFO(UDMF_TEST, "UnifiedData001 end.");
}

/**
* @tc.name: GetGroupId001
* @tc.desc: Normal testcase of GetGroupId
* @tc.type: FUNC
*/
HWTEST_F(UnifiedDataTest, GetGroupId001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetGroupId001 begin.");
    UnifiedData unifiedData;
    unifiedData.runtime_ = std::make_shared<Runtime>();
    std::string ret = unifiedData.GetGroupId();
    EXPECT_EQ(ret, unifiedData.runtime_->key.groupId);
    LOG_INFO(UDMF_TEST, "GetGroupId001 end.");
}

/**
* @tc.name: GetRuntime001
* @tc.desc: Normal testcase of GetRuntime
* @tc.type: FUNC
*/
HWTEST_F(UnifiedDataTest, GetRuntime001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetRuntime001 begin.");
    UnifiedData unifiedData;
    unifiedData.runtime_ = std::make_shared<Runtime>();
    std::shared_ptr<Runtime> ret = unifiedData.GetRuntime();
    EXPECT_EQ(ret, unifiedData.runtime_);
    LOG_INFO(UDMF_TEST, "GetRuntime001 end.");
}

/**
* @tc.name: SetRuntime001
* @tc.desc: Normal testcase of SetRuntime
* @tc.type: FUNC
*/
HWTEST_F(UnifiedDataTest, SetRuntime001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetRuntime001 begin.");
    UnifiedData unifiedData;
    Runtime runtime{};
    unifiedData.SetRuntime(runtime);
    EXPECT_NE(unifiedData.runtime_, nullptr);
    LOG_INFO(UDMF_TEST, "SetRuntime001 end.");
}

/**
* @tc.name: AddRecord001
* @tc.desc: Abnormal testcase of AddRecord, because record is nullptr
* @tc.type: FUNC
*/
HWTEST_F(UnifiedDataTest, AddRecord001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "AddRecord001 begin.");
    const std::shared_ptr<UnifiedRecord> record = nullptr;
    UnifiedData unifiedData;
    unifiedData.AddRecord(record);
    EXPECT_EQ(unifiedData.records_.size(), 0);
    LOG_INFO(UDMF_TEST, "AddRecord001 end.");
}

/**
* @tc.name: AddRecords001
* @tc.desc: Abnormal testcase of AddRecords, because record is nullptr
* @tc.type: FUNC
*/
HWTEST_F(UnifiedDataTest, AddRecords001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "AddRecords001 begin.");
    const std::vector<std::shared_ptr<UnifiedRecord>> record = {nullptr};
    UnifiedData unifiedData;
    unifiedData.AddRecords(record);
    EXPECT_EQ(unifiedData.records_.size(), 0);
    LOG_INFO(UDMF_TEST, "AddRecords001 end.");
}

/**
* @tc.name: GetRecordAt001
* @tc.desc: Abnormal testcase of GetRecordAt, because the length of records_ is equal to the length of index
* @tc.type: FUNC
*/
HWTEST_F(UnifiedDataTest, GetRecordAt001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetRecordAt001 begin.");
    UnifiedData unifiedData;
    unifiedData.records_ = std::vector<std::shared_ptr<UnifiedRecord>>();
    std::size_t index = unifiedData.records_.size();
    std::shared_ptr<UnifiedRecord> ret = unifiedData.GetRecordAt(index);
    EXPECT_EQ(ret, nullptr);
    LOG_INFO(UDMF_TEST, "GetRecordAt001 end.");
}
} // OHOS::Test