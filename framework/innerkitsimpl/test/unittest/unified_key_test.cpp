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
#define LOG_TAG "unifiedKeyTest"

#include <unistd.h>
#include <gtest/gtest.h>
#include <string>
#include "unified_key.h"

using namespace testing::ext;
using namespace OHOS::UDMF;
using namespace OHOS;
namespace OHOS::Test {
using namespace std;

class UnifiedKeyTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void UnifiedKeyTest::SetUpTestCase()
{
}

void UnifiedKeyTest::TearDownTestCase()
{
}

void UnifiedKeyTest::SetUp()
{
}

void UnifiedKeyTest::TearDown()
{
}

/**
* @tc.name: UnifiedKey001
* @tc.desc: Normal testcase of UnifiedKey
* @tc.type: FUNC
*/
HWTEST_F(UnifiedKeyTest, UnifiedKey001, TestSize.Level1)
{
    std::string key = "general.text";
    UnifiedKey unifiedKey(key);
    EXPECT_FALSE(unifiedKey.key.empty());
}

/**
* @tc.name: UnifiedKey002
* @tc.desc: Normal testcase of UnifiedKey
* @tc.type: FUNC
*/
HWTEST_F(UnifiedKeyTest, UnifiedKey002, TestSize.Level1)
{
    std::string intention = "general.text";
    std::string bundle = "com.ohos.test";
    std::string groupId = "test";

    UnifiedKey unifiedKey(intention, bundle, groupId);
    EXPECT_FALSE(unifiedKey.intention.empty());
    EXPECT_FALSE(unifiedKey.bundleName.empty());
    EXPECT_FALSE(unifiedKey.groupId.empty());
}

/**
* @tc.name: GetUnifiedKey001
* @tc.desc: Normal testcase of GetUnifiedKey, this->key is empty
* @tc.type: FUNC
*/
HWTEST_F(UnifiedKeyTest, GetUnifiedKey001, TestSize.Level1)
{
    std::string intention = "general.text";
    std::string bundle = "com.ohos.test";
    std::string groupId = "test";

    UnifiedKey unifiedKey(intention, bundle, groupId);
    EXPECT_NO_FATAL_FAILURE(unifiedKey.GetUnifiedKey());
}

/**
* @tc.name: GetUnifiedKey002
* @tc.desc: Normal testcase of GetUnifiedKey
* @tc.type: FUNC
*/
HWTEST_F(UnifiedKeyTest, GetUnifiedKey002, TestSize.Level1)
{
    std::string key = "general.text";
    UnifiedKey unifiedKey(key);
    std::string ret = unifiedKey.GetUnifiedKey();
    EXPECT_EQ(ret, key);
}

/**
* @tc.name: GetUnifiedKey003
* @tc.desc: Abnormal testcase of GetUnifiedKey, this->intention is empty
* @tc.type: FUNC
*/
HWTEST_F(UnifiedKeyTest, GetUnifiedKey003, TestSize.Level1)
{
    std::string intention;
    std::string bundle = "com.ohos.test";
    std::string groupId = "group1";

    UnifiedKey unifiedKey(intention, bundle, groupId);
    std::string ret = unifiedKey.GetUnifiedKey();
    EXPECT_EQ(ret, "");
}

/**
* @tc.name: GetUnifiedKey004
* @tc.desc: Abnormal testcase of GetUnifiedKey, this->groupId is empty
* @tc.type: FUNC
*/
HWTEST_F(UnifiedKeyTest, GetUnifiedKey004, TestSize.Level1)
{
    std::string intention = "intention1";
    std::string bundle;
    std::string groupId;

    UnifiedKey unifiedKey(intention, bundle, groupId);
    std::string ret = unifiedKey.GetUnifiedKey();
    EXPECT_EQ(ret, "");
}

/**
* @tc.name: GetUnifiedKey005
* @tc.desc: Abnormal testcase of GetUnifiedKey, this->groupId and this->intention is empty
* @tc.type: FUNC
*/
HWTEST_F(UnifiedKeyTest, GetUnifiedKey005, TestSize.Level1)
{
    std::string intention;
    std::string bundle;
    std::string groupId;

    UnifiedKey unifiedKey(intention, bundle, groupId);
    std::string ret = unifiedKey.GetUnifiedKey();
    EXPECT_EQ(ret, "");
}

/**
* @tc.name: GetKeyCommonPrefix001
* @tc.desc: Abnormal testcase of GetKeyCommonPrefix, size of this->key is 33
* @tc.type: FUNC
*/
HWTEST_F(UnifiedKeyTest, GetKeyCommonPrefix001, TestSize.Level1)
{
    std::string key('A', 33);
    UnifiedKey unifiedKey(key);

    std::string ret = unifiedKey.GetKeyCommonPrefix();
    EXPECT_FALSE(ret.empty());
}

/**
* @tc.name: GetKeyCommonPrefix002
* @tc.desc: Abnormal testcase of GetKeyCommonPrefix, size of this->key is 31, this->intention is empty
* @tc.type: FUNC
*/
HWTEST_F(UnifiedKeyTest, GetKeyCommonPrefix002, TestSize.Level1)
{
    std::string intention;
    std::string bundle = "com.ohos.test";
    std::string groupId('A', 31);
    UnifiedKey unifiedKey(intention, bundle, groupId);

    std::string ret = unifiedKey.GetKeyCommonPrefix();
    EXPECT_EQ(ret, "");
}

/**
* @tc.name: GetKeyCommonPrefix003
* @tc.desc: Abnormal testcase of GetKeyCommonPrefix, this->groupId size < INDEX_LEN
* @tc.type: FUNC
*/
HWTEST_F(UnifiedKeyTest, GetKeyCommonPrefix003, TestSize.Level1)
{
    std::string intention = "general.text";
    std::string bundle = "com.ohos.test";
    std::string groupId = "test";

    UnifiedKey unifiedKey(intention, bundle, groupId);
    std::string ret = unifiedKey.GetKeyCommonPrefix();
    EXPECT_EQ(ret, "");
}

/**
* @tc.name: GetKeyCommonPrefix004
* @tc.desc: Abnormal testcase of GetKeyCommonPrefix, this->groupId size < INDEX_LEN
* @tc.type: FUNC
*/
HWTEST_F(UnifiedKeyTest, GetKeyCommonPrefix004, TestSize.Level1)
{
    std::string intention = "general.text";
    std::string bundle = "com.ohos.test";
    std::string groupId('A', 33);

    UnifiedKey unifiedKey(intention, bundle, groupId);
    std::string ret = unifiedKey.GetKeyCommonPrefix();
    EXPECT_FALSE(ret.empty());
}

/**
* @tc.name: IsValid001
* @tc.desc: Normal testcase of IsValid, key is invalid
* @tc.type: FUNC
*/
HWTEST_F(UnifiedKeyTest, IsValid001, TestSize.Level1)
{
    std::string intention = "general.text";
    std::string bundle = "com.ohos.test";
    std::string groupId('A', 33);

    UnifiedKey unifiedKey(intention, bundle, groupId);
    bool ret = unifiedKey.IsValid();
    EXPECT_FALSE(ret);
}

/**
* @tc.name: IsValid002
* @tc.desc: Abnormal testcase of IsValid, key is invalid
* @tc.type: FUNC
*/
HWTEST_F(UnifiedKeyTest, IsValid002, TestSize.Level1)
{
    std::string key('A', 33);
    UnifiedKey unifiedKey(key);

    bool ret = unifiedKey.IsValid();
    EXPECT_FALSE(ret);
}

/**
* @tc.name: IsValid003
* @tc.desc: Abnormal testcase of IsValid, key is invalid
* @tc.type: FUNC
*/
HWTEST_F(UnifiedKeyTest, IsValid003, TestSize.Level1)
{
    std::string key = "udmf://";
    UnifiedKey unifiedKey(key);

    bool ret = unifiedKey.IsValid();
    EXPECT_FALSE(ret);
}

/**
* @tc.name: PreliminaryWork002
* @tc.desc: Normal testcase of PreliminaryWork
* @tc.type: FUNC
*/
HWTEST_F(UnifiedKeyTest, PreliminaryWork002, TestSize.Level1)
{
    std::string key = "udmf://";
    UnifiedKey unifiedKey(key);

    EXPECT_NO_FATAL_FAILURE(unifiedKey.PreliminaryWork());
}

/**
* @tc.name: CheckCharacter001
* @tc.desc: Abnormal testcase of CheckCharacter, data is invalid
* @tc.type: FUNC
*/
HWTEST_F(UnifiedKeyTest, CheckCharacter001, TestSize.Level1)
{
    std::string key = "udmf://";
    UnifiedKey unifiedKey(key);
    std::string_view data;
    std::bitset<MAX_BIT_SIZE> rule;

    EXPECT_FALSE(unifiedKey.CheckCharacter(data, rule));
}

/**
* @tc.name: CheckCharacter002
* @tc.desc: Abnormal testcase of CheckCharacter, data is invalid
* @tc.type: FUNC
*/
HWTEST_F(UnifiedKeyTest, CheckCharacter002, TestSize.Level1)
{
    std::string key = "udmf://";
    UnifiedKey unifiedKey(key);
    std::string_view data = "data";
    std::bitset<MAX_BIT_SIZE> rule;

    EXPECT_FALSE(unifiedKey.CheckCharacter(data, rule));
}

/**
* @tc.name: ExtractAndValidateSegment001
* @tc.desc: Abnormal testcase of ExtractAndValidateSegment, data is invalid
* @tc.type: FUNC
*/
HWTEST_F(UnifiedKeyTest, ExtractAndValidateSegment001, TestSize.Level1)
{
    std::string key = "udmf://";
    UnifiedKey unifiedKey(key);
    std::string_view data = "data";
    std::string field;
    std::bitset<MAX_BIT_SIZE> rule;
    std::string name;

    EXPECT_FALSE(unifiedKey.ExtractAndValidateSegment(data, field, rule, name));
}

/**
* @tc.name: ExtractAndValidateSegment002
* @tc.desc: Abnormal testcase of ExtractAndValidateSegment, data is invalid
* @tc.type: FUNC
*/
HWTEST_F(UnifiedKeyTest, ExtractAndValidateSegment002, TestSize.Level1)
{
    std::string key = "udmf://";
    UnifiedKey unifiedKey(key);
    std::string_view data = "udmf://";
    std::string field = "udmf://";
    std::bitset<MAX_BIT_SIZE> rule;
    std::string name;

    EXPECT_FALSE(unifiedKey.ExtractAndValidateSegment(data, field, rule, name));
}
} // OHOS::Test