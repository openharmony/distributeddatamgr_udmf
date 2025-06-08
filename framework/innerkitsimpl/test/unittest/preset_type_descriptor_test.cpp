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
#define LOG_TAG "PlainTextTest"

#include <gtest/gtest.h>
#include "preset_type_descriptors.h"
#include "logger.h"

using namespace testing::ext;
using namespace OHOS::UDMF;
using namespace OHOS;
namespace OHOS::Test {
using namespace std;

class PresetTypeDescriptorsTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void PresetTypeDescriptorsTest::SetUpTestCase()
{
}

void PresetTypeDescriptorsTest::TearDownTestCase()
{
}

void PresetTypeDescriptorsTest::SetUp()
{
}

void PresetTypeDescriptorsTest::TearDown()
{
}

/**
* @tc.name: TestDoubleInit
* @tc.desc: Test double init utd list.
* @tc.type: FUNC
*/
HWTEST_F(PresetTypeDescriptorsTest, TestDoubleInit, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "TestDoubleInit begin.");
    PresetTypeDescriptors &instance = PresetTypeDescriptors::GetInstance();
    auto presetTypes = instance.GetPresetTypes();
    auto sizeFirst = presetTypes.size();
    EXPECT_GT(sizeFirst, 0);
    instance.InitDescriptors();
    presetTypes = instance.GetPresetTypes();
    auto sizeSecond = presetTypes.size();
    EXPECT_EQ(sizeSecond, sizeFirst);
    LOG_INFO(UDMF_TEST, "TestDoubleInit end.");
}

} // OHOS::Test