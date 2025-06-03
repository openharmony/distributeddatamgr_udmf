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
#define LOG_TAG "SystemDefinedPixelMapTest"

#include <unistd.h>
#include <gtest/gtest.h>
#include <string>

#include "logger.h"
#include "system_defined_pixelmap.h"

using namespace testing::ext;
using namespace OHOS::UDMF;
using namespace OHOS;
namespace OHOS::Test {
using namespace std;

class SystemDefinedPixelMapTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void SystemDefinedPixelMapTest::SetUpTestCase()
{
}

void SystemDefinedPixelMapTest::TearDownTestCase()
{
}

void SystemDefinedPixelMapTest::SetUp()
{
}

void SystemDefinedPixelMapTest::TearDown()
{
}

/**
* @tc.name: SystemDefinedPixelMap001
* @tc.desc: Normal testcase of SystemDefinedPixelMap
* @tc.type: FUNC
*/
HWTEST_F(SystemDefinedPixelMapTest, SystemDefinedPixelMap001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SystemDefinedPixelMap001 begin.");
    std::vector<uint8_t> data = std::vector<uint8_t>();
    SystemDefinedPixelMap systemDefinedPixelMap(data);
    EXPECT_EQ(systemDefinedPixelMap.dataType_, SYSTEM_DEFINED_PIXEL_MAP);
    EXPECT_EQ(systemDefinedPixelMap.rawData_, data);
    LOG_INFO(UDMF_TEST, "SystemDefinedPixelMap001 end.");
}

/**
* @tc.name: SystemDefinedPixelMap002
* @tc.desc: Normal testcase of SystemDefinedPixelMap
* @tc.type: FUNC
*/
HWTEST_F(SystemDefinedPixelMapTest, SystemDefinedPixelMap002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SystemDefinedPixelMap002 begin.");
    UDType type = UDType::ENTITY;
    ValueType value = std::vector<uint8_t>();
    SystemDefinedPixelMap systemDefinedPixelMap(type, value);
    EXPECT_EQ(systemDefinedPixelMap.dataType_, SYSTEM_DEFINED_PIXEL_MAP);
    EXPECT_EQ(systemDefinedPixelMap.rawData_, std::get<std::vector<uint8_t>>(value));
    LOG_INFO(UDMF_TEST, "SystemDefinedPixelMap002 end.");
}

/**
* @tc.name: SystemDefinedPixelMap003
* @tc.desc: Abnormal testcase of SystemDefinedPixelMap, because value is not of type std::vector<uint8_t>
* @tc.type: FUNC
*/
HWTEST_F(SystemDefinedPixelMapTest, SystemDefinedPixelMap003, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SystemDefinedPixelMap003 begin.");
    UDType type = UDType::ENTITY;
    ValueType value = 0;
    SystemDefinedPixelMap systemDefinedPixelMap(type, value);
    EXPECT_EQ(systemDefinedPixelMap.dataType_, SYSTEM_DEFINED_PIXEL_MAP);
    EXPECT_EQ(systemDefinedPixelMap.rawData_.size(), 0);
    LOG_INFO(UDMF_TEST, "SystemDefinedPixelMap003 end.");
}

/**
* @tc.name: GetPixelMapFromRawData001
* @tc.desc: Abnormal testcase of GetPixelMapFromRawData, rawData_ is null
* @tc.type: FUNC
*/
HWTEST_F(SystemDefinedPixelMapTest, GetPixelMapFromRawData001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetPixelMapFromRawData001 begin.");
    SystemDefinedPixelMap systemDefinedPixelMap;
    const std::vector<uint8_t> rawData;
    systemDefinedPixelMap.SetRawData(rawData);
    std::unique_ptr<Media::PixelMap> ret = systemDefinedPixelMap.GetPixelMapFromRawData();
    EXPECT_EQ(ret, nullptr);
    LOG_INFO(UDMF_TEST, "GetPixelMapFromRawData001 end.");
}

/**
* @tc.name: SetRawDataFromPixels001
* @tc.desc: Abnormal testcase of SetRawDataFromPixels, rawData_ is null
* @tc.type: FUNC
*/
HWTEST_F(SystemDefinedPixelMapTest, SetRawDataFromPixels001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetRawDataFromPixels001 begin.");
    SystemDefinedPixelMap systemDefinedPixelMap;
    const std::shared_ptr<OHOS::Media::PixelMap> pixelMap = nullptr;
    bool ret = systemDefinedPixelMap.SetRawDataFromPixels(pixelMap);
    EXPECT_FALSE(ret);
    LOG_INFO(UDMF_TEST, "SetRawDataFromPixels001 end.");
}
} // OHOS::Test