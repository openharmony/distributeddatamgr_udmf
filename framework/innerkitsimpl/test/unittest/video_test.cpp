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
#define LOG_TAG "VideoTest"

#include <unistd.h>
#include <gtest/gtest.h>
#include <string>

#include "logger.h"
#include "udmf_capi_common.h"
#include "video.h"

using namespace testing::ext;
using namespace OHOS::UDMF;
using namespace OHOS;
namespace OHOS::Test {
using namespace std;

class VideoTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void VideoTest::SetUpTestCase()
{
}

void VideoTest::TearDownTestCase()
{
}

void VideoTest::SetUp()
{
}

void VideoTest::TearDown()
{
}

/**
* @tc.name: Video001
* @tc.desc: Normal testcase of Video
* @tc.type: FUNC
*/
HWTEST_F(VideoTest, Video001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "Video001 begin.");
    UDType type = UDType::ENTITY;
    ValueType value = 0;
    Video video(type, value);
    EXPECT_EQ(video.dataType_, VIDEO);
    LOG_INFO(UDMF_TEST, "Video001 end.");
}
} // OHOS::Test