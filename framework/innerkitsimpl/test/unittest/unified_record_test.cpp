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
#define LOG_TAG "UnifiedRecordTest"

#include <unistd.h>
#include <gtest/gtest.h>
#include <string>

#include "logger.h"
#include "udmf_capi_common.h"
#include "unified_record.h"

using namespace testing::ext;
using namespace OHOS::UDMF;
using namespace OHOS;
namespace OHOS::Test {
using namespace std;

class UnifiedRecordTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void UnifiedRecordTest::SetUpTestCase()
{
}

void UnifiedRecordTest::TearDownTestCase()
{
}

void UnifiedRecordTest::SetUp()
{
}

void UnifiedRecordTest::TearDown()
{
}

/**
* @tc.name: GetSize001
* @tc.desc: Normal testcase of GetSize
* @tc.type: FUNC
*/
HWTEST_F(UnifiedRecordTest, GetSize001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetSize001 begin.");
    UnifiedRecord unifiedRecord;
    int64_t ret = unifiedRecord.GetSize();
    EXPECT_EQ(ret, 0);
    LOG_INFO(UDMF_TEST, "GetSize001 end.");
}

/**
* @tc.name: GetValue001
* @tc.desc: Normal testcase of GetValue
* @tc.type: FUNC
*/
HWTEST_F(UnifiedRecordTest, GetValue001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetValue001 begin.");
    UnifiedRecord unifiedRecord;
    unifiedRecord.value_ = "value";
    ValueType ret = unifiedRecord.GetValue();
    EXPECT_EQ(ret, unifiedRecord.value_);
    LOG_INFO(UDMF_TEST, "GetValue001 end.");
}


/**
 * @tc.name: Constructor_001
 * @tc.desc: Verify the constructor.
 * @tc.type: FUNC
 */
HWTEST_F(UnifiedRecordTest, Constructor_001, TestSize.Level0)
{
    UnifiedRecord record;

    auto type = record.GetType();
    EXPECT_EQ(type, UD_BUTT);

    auto types = record.GetUtdIds();
    EXPECT_TRUE(types.empty());

    auto originValue = record.GetOriginValue();
    EXPECT_TRUE(std::holds_alternative<std::monostate>(originValue));

    auto entry = record.GetEntry("");
    EXPECT_TRUE(std::holds_alternative<std::monostate>(entry));

    auto entries = record.GetEntries();
    EXPECT_TRUE(entries->empty());
}

/**
 * @tc.name: Constructor_002
 * @tc.desc: Verify the constructor.
 * @tc.type: FUNC
 */
HWTEST_F(UnifiedRecordTest, Constructor_002, TestSize.Level0)
{
    auto utdId = UtdUtils::GetUtdIdFromUtdEnum(TEXT);

    UnifiedRecord record(TEXT);
    auto type = record.GetType();
    EXPECT_EQ(type, TEXT);
    auto types = record.GetUtdIds();
    EXPECT_TRUE(types.find(utdId) != types.end());

    auto originValue = record.GetOriginValue();
    EXPECT_TRUE(std::holds_alternative<std::monostate>(originValue));

    auto entry = record.GetEntry(utdId);
    EXPECT_TRUE(std::holds_alternative<std::monostate>(entry));

    auto entries = record.GetEntries();
    auto it = entries->find(utdId);
    ASSERT_TRUE(it != entries->end());
    EXPECT_TRUE(std::holds_alternative<std::monostate>(it->second));
}

/**
 * @tc.name: Constructor_003
 * @tc.desc: Verify the constructor.
 * @tc.type: FUNC
 */
HWTEST_F(UnifiedRecordTest, Constructor_003, TestSize.Level0)
{
    auto utdId = UtdUtils::GetUtdIdFromUtdEnum(TEXT);
    UnifiedRecord record(TEXT, "123456");
    auto type = record.GetType();
    EXPECT_EQ(type, TEXT);
    auto types = record.GetUtdIds();
    EXPECT_TRUE(types.find(utdId) != types.end());

    auto originValue = record.GetOriginValue();
    EXPECT_TRUE(std::holds_alternative<std::string>(originValue));
    auto originValueStr = std::get_if<std::string>(&originValue);
    EXPECT_EQ(*originValueStr, "123456");

    auto entry = record.GetEntry(utdId);
    EXPECT_TRUE(std::holds_alternative<std::string>(entry));
    auto entryStr = std::get_if<std::string>(&entry);
    EXPECT_EQ(*entryStr, "123456");

    auto entries = record.GetEntries();
    auto it = entries->find(utdId);
    ASSERT_TRUE(it != entries->end());
    auto entry2 = it->second;
    EXPECT_TRUE(std::holds_alternative<std::string>(entry2));
    auto entryStr2 = std::get_if<std::string>(&entry2);
    EXPECT_EQ(*entryStr2, "123456");
}
} // OHOS::Test