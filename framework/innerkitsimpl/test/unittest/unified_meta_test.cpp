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
#define LOG_TAG "UnifiedMetaTest"

#include <unistd.h>
#include <gtest/gtest.h>
#include <string>

#include "logger.h"
#include "udmf_capi_common.h"
#include "unified_meta.h"

using namespace testing::ext;
using namespace OHOS::UDMF;
using namespace OHOS;
namespace OHOS::Test {
using namespace std;

class UnifiedMetaTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void UnifiedMetaTest::SetUpTestCase()
{
}

void UnifiedMetaTest::TearDownTestCase()
{
}

void UnifiedMetaTest::SetUp()
{
}

void UnifiedMetaTest::TearDown()
{
}

/**
* @tc.name: IsValidType001
* @tc.desc: Normal testcase of IsValidType
* @tc.type: FUNC
*/
HWTEST_F(UnifiedMetaTest, IsValidType001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "IsValidType001 begin.");
    int32_t value = 0;
    bool ret = UnifiedDataUtils::IsValidType(value);
    EXPECT_EQ(ret, value >= ENTITY && value < UD_BUTT);
    LOG_INFO(UDMF_TEST, "IsValidType001 end.");
}

/**
* @tc.name: GetEnumNum001
* @tc.desc: Normal testcase of GetEnumNum
* @tc.type: FUNC
*/
HWTEST_F(UnifiedMetaTest, GetEnumNum001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetEnumNum001 begin.");
    const std::string shareOption = "";
    int32_t ret = ShareOptionsUtil::GetEnumNum(shareOption);
    EXPECT_EQ(ret, ShareOptions::SHARE_OPTIONS_BUTT);
    LOG_INFO(UDMF_TEST, "GetEnumNum001 end.");
}

/**
* @tc.name: GetEnumNum002
* @tc.desc: Abnormal testcase of GetEnumNum, shareOption is APP_SHARE_OPTIONS.enumNum
* @tc.type: FUNC
*/
HWTEST_F(UnifiedMetaTest, GetEnumNum002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetEnumNum002 begin.");
    const std::string shareOption = "CROSS_APP";
    int32_t ret = ShareOptionsUtil::GetEnumNum(shareOption);
    EXPECT_EQ(ret, 1);
    LOG_INFO(UDMF_TEST, "GetEnumNum002 end.");
}

/**
* @tc.name: GetEnumStr001
* @tc.desc: Normal testcase of GetEnumStr
* @tc.type: FUNC
*/
HWTEST_F(UnifiedMetaTest, GetEnumStr001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetEnumStr001 begin.");
    int32_t shareOption = 4;
    std::string ret = ShareOptionsUtil::GetEnumStr(shareOption);
    EXPECT_EQ(ret, "");
    LOG_INFO(UDMF_TEST, "GetEnumStr001 end.");
}

/**
* @tc.name: GetEnumStr002
* @tc.desc: Abnormal testcase of GetEnumStr, hareOption is APP_SHARE_OPTIONS.enumStr
* @tc.type: FUNC
*/
HWTEST_F(UnifiedMetaTest, GetEnumStr002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetEnumStr002 begin.");
    int32_t shareOption = 1;
    std::string ret = ShareOptionsUtil::GetEnumStr(shareOption);
    EXPECT_NE(ret, "");
    LOG_INFO(UDMF_TEST, "GetEnumStr002 end.");
}
} // OHOS::Test