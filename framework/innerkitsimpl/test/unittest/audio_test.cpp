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
#define LOG_TAG "AudioTest"

#include <unistd.h>
#include <gtest/gtest.h>
#include <string>

#include "logger.h"
#include "audio.h"

using namespace testing::ext;
using namespace OHOS::UDMF;
using namespace OHOS;
namespace OHOS::Test {
using namespace std;

class AudioTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void AudioTest::SetUpTestCase()
{
}

void AudioTest::TearDownTestCase()
{
}

void AudioTest::SetUp()
{
}

void AudioTest::TearDown()
{
}

/**
* @tc.name: Audio001
* @tc.desc: Normal testcase of Audio
* @tc.type: FUNC
*/
HWTEST_F(AudioTest, Audio001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "Audio001 begin.");
    UDType type = UDType::ENTITY;
    ValueType value = 0;
    Audio audio(type, value);
    EXPECT_EQ(audio.dataType_, AUDIO);
    LOG_INFO(UDMF_TEST, "Audio001 end.");
}
} // OHOS::Test