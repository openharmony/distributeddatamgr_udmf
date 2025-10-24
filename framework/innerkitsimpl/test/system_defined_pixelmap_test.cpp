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
#include <sstream>

#include "logger.h"
#include "pixelmap_loader.h"
#include "system_defined_pixelmap.h"

using namespace testing::ext;
using namespace OHOS::UDMF;
using namespace OHOS;
namespace OHOS::Test {
using namespace std;
static constexpr const char* PIXEL_MAP_WIDTH = "width";
static constexpr const char* PIXEL_MAP_HEIGHT = "height";
static constexpr const char* PIXEL_MAP_FORMAT = "pixel-format";
static constexpr const char* PIXEL_MAP_ALPHA_TYPE = "alpha-type";
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
    auto ret = systemDefinedPixelMap.GetPixelMapFromRawData();
    EXPECT_EQ(ret, nullptr);
    LOG_INFO(UDMF_TEST, "GetPixelMapFromRawData001 end.");
}

/**
* @tc.name: GetPixelMapFromRawData002
* @tc.desc: Abnormal testcase of GetPixelMapFromRawData, rawData_ is wrong
* @tc.type: FUNC
*/
HWTEST_F(SystemDefinedPixelMapTest, GetPixelMapFromRawData002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetPixelMapFromRawData002 begin.");
    
    std::vector<uint8_t> rawData;
    for (int i = 0; i < 4 * 1024 * 1024; i++) {
        rawData.emplace_back(1);
    }
    SystemDefinedPixelMap systemDefinedPixelMap;
    UDDetails details = {
        {PIXEL_MAP_WIDTH, (int32_t)5},
        {PIXEL_MAP_HEIGHT, (int32_t)7},
        {PIXEL_MAP_FORMAT, (int32_t)Media::PixelFormat::ARGB_8888},
        {PIXEL_MAP_ALPHA_TYPE, (int32_t)Media::PixelFormat::ARGB_8888}
    };
    systemDefinedPixelMap.SetRawData(rawData);
    systemDefinedPixelMap.SetDetails(details);
    auto ret = systemDefinedPixelMap.GetPixelMapFromRawData();
    EXPECT_EQ(ret, nullptr);
    LOG_INFO(UDMF_TEST, "GetPixelMapFromRawData002 end.");
}

/**
* @tc.name: GetPixelMapFromRawData003
* @tc.desc: Abnormal testcase of GetPixelMapFromRawData, rawData_ is null
* @tc.type: FUNC
*/
HWTEST_F(SystemDefinedPixelMapTest, GetPixelMapFromRawData003, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetPixelMapFromRawData002 begin.");

    uint32_t color[35] = { 3, 7, 9, 9, 7, 6 };
    OHOS::Media::InitializationOptions opts = { { 5, 7 },
        Media::PixelFormat::ARGB_8888, Media::PixelFormat::ARGB_8888 };
    std::unique_ptr<OHOS::Media::PixelMap> pixelMap =
        OHOS::Media::PixelMap::Create(color, sizeof(color) / sizeof(color[0]), opts);
    auto length = pixelMap->GetByteCount();
    std::vector<uint8_t> rawData;
    rawData.resize(length);
    pixelMap->ReadPixels(length, rawData.data());
    SystemDefinedPixelMap systemDefinedPixelMap;
    UDDetails details = {
        {PIXEL_MAP_WIDTH, (int32_t)5},
        {PIXEL_MAP_HEIGHT, (int32_t)7},
        {PIXEL_MAP_FORMAT, (int32_t)Media::PixelFormat::ARGB_8888},
        {PIXEL_MAP_ALPHA_TYPE, (int32_t)Media::PixelFormat::ARGB_8888}
    };
    systemDefinedPixelMap.SetRawData(rawData);
    systemDefinedPixelMap.SetDetails(details);
    auto getPixelMap = systemDefinedPixelMap.GetPixelMapFromRawData();
    auto getLength = getPixelMap->GetByteCount();
    EXPECT_EQ(length, getLength);
    std::vector<uint8_t> getRawData(getLength);
    getPixelMap->ReadPixels(length, getRawData.data());
    for (int32_t i = 0; i < getLength; ++i) {
        EXPECT_EQ(getRawData[i], rawData[i]);
    }
    LOG_INFO(UDMF_TEST, "GetPixelMapFromRawData003 end.");
}

/**
* @tc.name: ParseInfoFromPixelMap001
* @tc.desc: Abnormal testcase of ParseInfoFromPixelMap001, pixelMap is null
* @tc.type: FUNC
*/
HWTEST_F(SystemDefinedPixelMapTest, ParseInfoFromPixelMap001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "ParseInfoFromPixelMap001 begin.");
    SystemDefinedPixelMap systemDefinedPixelMap;
    systemDefinedPixelMap.ParseInfoFromPixelMap(nullptr);
    EXPECT_TRUE(systemDefinedPixelMap.details_.empty());
    LOG_INFO(UDMF_TEST, "ParseInfoFromPixelMap001 end.");
}

/**
* @tc.name: PixelMapLoader001
* @tc.desc: Abnormal testcase of PixelMapLoader001
* @tc.type: FUNC
*/
HWTEST_F(SystemDefinedPixelMapTest, PixelMapLoader001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "PixelMapLoader001 begin.");
    PixelMapLoader loader;
    loader.handler_ = nullptr;
    std::vector<uint8_t> buff(10);
    auto ret = loader.DecodeTlv(buff);
    EXPECT_EQ(ret, nullptr);
    LOG_INFO(UDMF_TEST, "PixelMapLoader001 end.");
}

/**
* @tc.name: PixelMapLoader002
* @tc.desc: Abnormal testcase of PixelMapLoader002
* @tc.type: FUNC
*/
HWTEST_F(SystemDefinedPixelMapTest, PixelMapLoader002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "PixelMapLoader002 begin.");
    PixelMapLoader loader;
    loader.handler_ = nullptr;
    std::vector<uint8_t> buff;

    uint32_t color[35] = { 3, 7, 9, 9, 7, 6 };
    OHOS::Media::InitializationOptions opts = { { 5, 7 },
        Media::PixelFormat::ARGB_8888, Media::PixelFormat::ARGB_8888 };
    std::unique_ptr<OHOS::Media::PixelMap> pixelMap =
        OHOS::Media::PixelMap::Create(color, sizeof(color) / sizeof(color[0]), opts);
    std::shared_ptr<OHOS::Media::PixelMap> pixelMapIn = move(pixelMap);

    auto ret = loader.EncodeTlv(pixelMapIn, buff);
    EXPECT_EQ(ret, false);
    LOG_INFO(UDMF_TEST, "PixelMapLoader002 end.");
}

/**
* @tc.name: PixelMapLoader003
* @tc.desc: Abnormal testcase of PixelMapLoader003
* @tc.type: FUNC
*/
HWTEST_F(SystemDefinedPixelMapTest, PixelMapLoader003, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "PixelMapLoader003 begin.");
    PixelMapLoader loader;
    loader.handler_ = nullptr;
    
    PixelMapDetails details;
    auto buff = std::vector<uint8_t>(10);
    details.rawData = std::ref(buff);
    auto ret = loader.GetPixelMapFromRawData(details);
    EXPECT_EQ(ret, nullptr);
    LOG_INFO(UDMF_TEST, "PixelMapLoader003 end.");
}

/**
* @tc.name: PixelMapLoader004
* @tc.desc: Abnormal testcase of PixelMapLoader004
* @tc.type: FUNC
*/
HWTEST_F(SystemDefinedPixelMapTest, PixelMapLoader004, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "PixelMapLoader004 begin.");
    PixelMapLoader loader;
    loader.handler_ = nullptr;
    
    uint32_t color[35] = { 3, 7, 9, 9, 7, 6 };
    OHOS::Media::InitializationOptions opts = { { 5, 7 },
        Media::PixelFormat::ARGB_8888, Media::PixelFormat::ARGB_8888 };
    std::unique_ptr<OHOS::Media::PixelMap> pixelMap =
        OHOS::Media::PixelMap::Create(color, sizeof(color) / sizeof(color[0]), opts);
    std::shared_ptr<OHOS::Media::PixelMap> pixelMapIn = move(pixelMap);
    auto ret = loader.ParseInfoFromPixelMap(pixelMapIn);
    EXPECT_EQ(ret, nullptr);
    LOG_INFO(UDMF_TEST, "PixelMapLoader004 end.");
}

/**
* @tc.name: PixelMapLoader005
* @tc.desc: Abnormal testcase of PixelMapLoader005
* @tc.type: FUNC
*/
HWTEST_F(SystemDefinedPixelMapTest, PixelMapLoader005, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "PixelMapLoader005 begin.");
    PixelMapLoader loader;
    ASSERT_NE(loader.handler_, nullptr);

    std::vector<uint8_t> buff;
    auto ret = loader.DecodeTlv(buff);
    EXPECT_EQ(ret, nullptr);
    LOG_INFO(UDMF_TEST, "PixelMapLoader005 end.");
}

/**
* @tc.name: PixelMapLoader006
* @tc.desc: Abnormal testcase of PixelMapLoader006
* @tc.type: FUNC
*/
HWTEST_F(SystemDefinedPixelMapTest, PixelMapLoader006, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "PixelMapLoader006 begin.");
    PixelMapLoader loader;
    ASSERT_NE(loader.handler_, nullptr);
    std::vector<uint8_t> buff;
    std::shared_ptr<OHOS::Media::PixelMap> pixelMapIn = nullptr;

    auto ret = loader.EncodeTlv(pixelMapIn, buff);
    EXPECT_EQ(ret, false);
    LOG_INFO(UDMF_TEST, "PixelMapLoader006 end.");
}

/**
* @tc.name: PixelMapLoader007
* @tc.desc: Abnormal testcase of PixelMapLoader007
* @tc.type: FUNC
*/
HWTEST_F(SystemDefinedPixelMapTest, PixelMapLoader007, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "PixelMapLoader007 begin.");
    PixelMapLoader loader;
    ASSERT_NE(loader.handler_, nullptr);
    
    PixelMapDetails details;
    details.rawData = std::nullopt;
    auto ret = loader.GetPixelMapFromRawData(details);
    EXPECT_EQ(ret, nullptr);
    LOG_INFO(UDMF_TEST, "PixelMapLoader007 end.");
}

/**
* @tc.name: PixelMapLoader008
* @tc.desc: Abnormal testcase of PixelMapLoader008
* @tc.type: FUNC
*/
HWTEST_F(SystemDefinedPixelMapTest, PixelMapLoader008, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "PixelMapLoader008 begin.");
    PixelMapLoader loader;
    ASSERT_NE(loader.handler_, nullptr);

    auto ret = loader.ParseInfoFromPixelMap(nullptr);
    EXPECT_EQ(ret, nullptr);
    LOG_INFO(UDMF_TEST, "PixelMapLoader008 end.");
}
} // OHOS::Test