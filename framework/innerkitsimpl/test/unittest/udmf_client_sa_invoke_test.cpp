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
#define LOG_TAG "UdmfClientSaInvokeTest"
#include <gtest/gtest.h>

#include "token_setproc.h"
#include "accesstoken_kit.h"
#include "executor_pool.h"
#include "nativetoken_kit.h"

#include "logger.h"
#include "image.h"
#include "plain_text.h"
#include "system_defined_pixelmap.h"
#include "udmf_client.h"

using namespace testing::ext;
using namespace OHOS::Security::AccessToken;
using namespace OHOS::UDMF;
using namespace OHOS;
namespace OHOS::Test {
constexpr const int32_t FIVE = 5;
constexpr const int32_t TEN = 10;

class UdmfClientSaInvokeTest : public testing::Test {
public:

    void SetDataTest();

    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;

    static void SetHapToken();
};

void UdmfClientSaInvokeTest::SetUpTestCase()
{
    SetHapToken();
}

void UdmfClientSaInvokeTest::TearDownTestCase()
{
    auto tokenId = AccessTokenKit::GetNativeTokenId("msdp_sa");
    AccessTokenKit::DeleteToken(tokenId);
}

void UdmfClientSaInvokeTest::SetUp() {}

void UdmfClientSaInvokeTest::TearDown() {}


void UdmfClientSaInvokeTest::SetHapToken()
{
    auto tokenId = AccessTokenKit::GetNativeTokenId("msdp_sa");
    SetSelfTokenID(tokenId);
}

/**
* @tc.name: SetDataTest
* @tc.desc: Test set data success. Record size more than 4M and less than 15.5M.
* @tc.type: FUNC
*/
void UdmfClientSaInvokeTest::SetDataTest()
{
    LOG_INFO(UDMF_TEST, "SetDataTest begin.");
    CustomOption option = { .intention = Intention::UD_INTENTION_DRAG };
    std::vector<uint8_t> rawData;
    for (int i = 0; i < FIVE * 1024 * 1024; i++) {
        rawData.emplace_back(1);
    }
    auto pixelMap = std::make_shared<SystemDefinedPixelMap>(rawData);
    UnifiedData data;
    data.AddRecord(pixelMap);

    std::vector<uint8_t> rawData2;
    for (int i = 0; i < TEN * 1024 * 1024; i++) {
        rawData2.emplace_back(1);
    }
    auto pixelMap2 = std::make_shared<SystemDefinedPixelMap>(rawData2);
    data.AddRecord(pixelMap2);
    auto recordSize = data.GetRecords().size();
    
    std::string key;
    auto status = UdmfClient::GetInstance().SetData(option, data, key);
    ASSERT_EQ(E_OK, status);

    UnifiedData readData;
    QueryOption queryOption = {.key = key};
    status = UdmfClient::GetInstance().GetData(queryOption, readData);
    ASSERT_EQ(E_OK, status);
    ASSERT_EQ(recordSize, readData.GetRecords().size());
    auto readPixelMap = std::static_pointer_cast<SystemDefinedPixelMap>(readData.GetRecordAt(0));
    EXPECT_EQ(FIVE * 1024 * 1024, readPixelMap->GetRawData().size());

    auto readPixelMap2 = std::static_pointer_cast<SystemDefinedPixelMap>(readData.GetRecordAt(1));
    EXPECT_TRUE(readPixelMap2->GetRawData().size() == TEN * 1024 * 1024);
    EXPECT_EQ(TEN * 1024 * 1024, readPixelMap2->GetRawData().size());
    LOG_INFO(UDMF_TEST, "SetDataTest end.");
}

/**
* @tc.name: SetData001
* @tc.desc: Test set data success. Record size Less than 2M.
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientSaInvokeTest, SetData001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetData001 begin.");

    CustomOption option = { .intention = Intention::UD_INTENTION_DRAG };
    auto plainText = std::make_shared<PlainText>("something", "anything");
    UnifiedData data;
    data.AddRecord(plainText);
    std::string key;
    auto status = UdmfClient::GetInstance().SetData(option, data, key);
    ASSERT_EQ(E_OK, status);

    UnifiedData readData;
    QueryOption queryOption = {.key = key};
    status = UdmfClient::GetInstance().GetData(queryOption, readData);
    ASSERT_EQ(E_OK, status);
    ASSERT_EQ(1, readData.GetRecords().size());
    auto readPlainText = std::static_pointer_cast<PlainText>(readData.GetRecordAt(0));
    EXPECT_EQ("something", readPlainText->GetContent());
    EXPECT_EQ("anything", readPlainText->GetAbstract());
    LOG_INFO(UDMF_TEST, "SetData001 end.");
}

/**
* @tc.name: SetData002
* @tc.desc: Test set data success. Record size greater than 2M.
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientSaInvokeTest, SetData002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetData002 begin.");

    CustomOption option = { .intention = Intention::UD_INTENTION_DRAG };
    std::vector<uint8_t> rawData;
    for (int i = 0; i < 2 * 1024 * 1024 + 1; i++) {
        rawData.emplace_back(1);
    }
    auto pixelMap = std::make_shared<SystemDefinedPixelMap>(rawData);
    UnifiedData data;
    data.AddRecord(pixelMap);
    std::string key;
    auto status = UdmfClient::GetInstance().SetData(option, data, key);
    ASSERT_EQ(E_OK, status);

    UnifiedData readData;
    QueryOption queryOption = {.key = key};
    status = UdmfClient::GetInstance().GetData(queryOption, readData);
    ASSERT_EQ(E_OK, status);
    ASSERT_EQ(1, readData.GetRecords().size());
    auto readPixelMap = std::static_pointer_cast<SystemDefinedPixelMap>(readData.GetRecordAt(0));
    EXPECT_EQ(2 * 1024 * 1024 + 1, readPixelMap->GetRawData().size());
    LOG_INFO(UDMF_TEST, "SetData002 end.");
}

/**
* @tc.name: SetData003
* @tc.desc: Test set data success. Every record size greater than 2M, and data greater than 4M.
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientSaInvokeTest, SetData003, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetData003 begin.");

    CustomOption option = { .intention = Intention::UD_INTENTION_DRAG };
    std::vector<uint8_t> rawData1;
    for (int i = 0; i < 3 * 1024 * 1024; i++) {
        rawData1.emplace_back(1);
    }
    auto pixelMap1 = std::make_shared<SystemDefinedPixelMap>(rawData1);
    std::vector<uint8_t> rawData2;
    for (int i = 0; i < 3 * 1024 * 1024; i++) {
        rawData2.emplace_back(2);
    }
    auto pixelMap2 = std::make_shared<SystemDefinedPixelMap>(rawData2);
    std::vector<uint8_t> rawData3;
    for (int i = 0; i < 3 * 1024 * 1024; i++) {
        rawData3.emplace_back(3);
    }
    auto pixelMap3 = std::make_shared<SystemDefinedPixelMap>(rawData3);
    std::vector<uint8_t> rawData4;
    for (int i = 0; i < 3 * 1024 * 1024; i++) {
        rawData4.emplace_back(4);
    }
    auto pixelMap4 = std::make_shared<SystemDefinedPixelMap>(rawData4);

    UnifiedData data;
    data.AddRecord(pixelMap1);
    data.AddRecord(pixelMap2);
    data.AddRecord(pixelMap3);
    data.AddRecord(pixelMap4);
    LOG_ERROR(UDMF_TEST, "data size = %{public}lld.", data.GetSize());
    std::string key;
    auto status = UdmfClient::GetInstance().SetData(option, data, key);
    ASSERT_EQ(E_OK, status);

    UnifiedData readData;
    QueryOption queryOption = {.key = key};
    status = UdmfClient::GetInstance().GetData(queryOption, readData);
    ASSERT_EQ(E_OK, status);
    ASSERT_EQ(4, readData.GetRecords().size());
    auto readPixelMap1 = std::static_pointer_cast<SystemDefinedPixelMap>(readData.GetRecordAt(0));
    EXPECT_EQ(3 * 1024 * 1024, readPixelMap1->GetRawData().size());
    auto readPixelMap2 = std::static_pointer_cast<SystemDefinedPixelMap>(readData.GetRecordAt(1));
    EXPECT_EQ(3 * 1024 * 1024, readPixelMap2->GetRawData().size());
    auto readPixelMap3 = std::static_pointer_cast<SystemDefinedPixelMap>(readData.GetRecordAt(2));
    EXPECT_EQ(3 * 1024 * 1024, readPixelMap3->GetRawData().size());
    auto readPixelMap4 = std::static_pointer_cast<SystemDefinedPixelMap>(readData.GetRecordAt(3));
    EXPECT_EQ(3 * 1024 * 1024, readPixelMap4->GetRawData().size());
    LOG_INFO(UDMF_TEST, "SetData003 end.");
}

/**
* @tc.name: SetData004
* @tc.desc: Test set data error. Record size equals 4M.
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientSaInvokeTest, SetData004, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetData004 begin.");

    CustomOption option = { .intention = Intention::UD_INTENTION_DRAG };
    std::vector<uint8_t> rawData;
    for (int i = 0; i < 4 * 1024 * 1024; i++) {
        rawData.emplace_back(1);
    }
    auto pixelMap = std::make_shared<SystemDefinedPixelMap>(rawData);
    UnifiedData data;
    data.AddRecord(pixelMap);
    std::string key;
    auto status = UdmfClient::GetInstance().SetData(option, data, key);
    ASSERT_EQ(E_OK, status);

    UnifiedData readData;
    QueryOption queryOption = {.key = key};
    status = UdmfClient::GetInstance().GetData(queryOption, readData);
    ASSERT_EQ(E_OK, status);
    ASSERT_EQ(1, readData.GetRecords().size());
    auto readPixelMap1 = std::static_pointer_cast<SystemDefinedPixelMap>(readData.GetRecordAt(0));
    EXPECT_EQ(4 * 1024 * 1024, readPixelMap1->GetRawData().size());
    LOG_INFO(UDMF_TEST, "SetData004 end.");
}

/**
* @tc.name: SetData005
* @tc.desc: Test set data error. Record type is file.
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientSaInvokeTest, SetData005, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetData005 begin.");

    CustomOption option = { .intention = Intention::UD_INTENTION_DRAG };
    std::string uri = "https://image.jpg";
    auto image = std::make_shared<Image>(uri);
    UnifiedData data;
    data.AddRecord(image);
    std::string key;
    auto status = UdmfClient::GetInstance().SetData(option, data, key);
    ASSERT_EQ(E_INVALID_PARAMETERS, status);
    LOG_INFO(UDMF_TEST, "SetData005 end.");
}

/**
* @tc.name: SetData006
* @tc.desc: Test set data success. Record size more than 4M and less than 15.5M.
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientSaInvokeTest, SetData006, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetData006 begin.");
    SetDataTest();
    LOG_INFO(UDMF_TEST, "SetData006 end.");
}

/**
* @tc.name: SetData007
* @tc.desc: Test set data error. Record size Greater than 15.5M.
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientSaInvokeTest, SetData007, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetData007 begin.");

    CustomOption option = { .intention = Intention::UD_INTENTION_DRAG };
    std::vector<uint8_t> rawData;
    for (int i = 0; i < 15.5 * 1024 * 1024 + 1; i++) {
        rawData.emplace_back(1);
    }
    auto pixelMap = std::make_shared<SystemDefinedPixelMap>(rawData);
    UnifiedData data;
    data.AddRecord(pixelMap);
    std::string key;
    auto status = UdmfClient::GetInstance().SetData(option, data, key);
    ASSERT_EQ(E_INVALID_PARAMETERS, status);
    LOG_INFO(UDMF_TEST, "SetData007 end.");
}

/**
* @tc.name: SetData008
* @tc.desc: Test set data success. Record size equals 15.5M.
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientSaInvokeTest, SetData008, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetData008 begin.");

    CustomOption option = { .intention = Intention::UD_INTENTION_DRAG };
    std::vector<uint8_t> rawData;
    for (int i = 0; i < 15.5 * 1024 * 1024; i++) {
        rawData.emplace_back(1);
    }
    auto pixelMap = std::make_shared<SystemDefinedPixelMap>(rawData);
    UnifiedData data;
    data.AddRecord(pixelMap);

    std::vector<uint8_t> rawData2;
    for (int i = 0; i < 15 * 1024 * 1024; i++) {
        rawData2.emplace_back(1);
    }
    auto pixelMap2 = std::make_shared<SystemDefinedPixelMap>(rawData2);
    data.AddRecord(pixelMap2);

    std::string key;
    auto status = UdmfClient::GetInstance().SetData(option, data, key);
    ASSERT_EQ(E_OK, status);

    UnifiedData readData;
    QueryOption queryOption = {.key = key};
    status = UdmfClient::GetInstance().GetData(queryOption, readData);
    ASSERT_EQ(E_OK, status);
    ASSERT_EQ(2, readData.GetRecords().size());
    auto readPixelMap = std::static_pointer_cast<SystemDefinedPixelMap>(readData.GetRecordAt(0));
    EXPECT_EQ(5 * 1024 * 1024, readPixelMap->GetRawData().size());

    auto readPixelMap2 = std::static_pointer_cast<SystemDefinedPixelMap>(readData.GetRecordAt(1));
    EXPECT_TRUE(readPixelMap2->GetRawData().size() == 10 * 1024 * 1024);
    EXPECT_EQ(10 * 1024 * 1024, readPixelMap2->GetRawData().size());
    LOG_INFO(UDMF_TEST, "SetData006 end.");
}

/**
* @tc.name: SetData007
* @tc.desc: Test set data error. Record size Greater than 15.5M.
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientSaInvokeTest, SetData009, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetData009 begin.");

    CustomOption option = { .intention = Intention::UD_INTENTION_DRAG };
    std::vector<uint8_t> rawData;
    for (int i = 0; i < 15.5 * 1024 * 1024 + 1; i++) {
        rawData.emplace_back(1);
    }
    auto pixelMap = std::make_shared<SystemDefinedPixelMap>(rawData);
    UnifiedData data;
    data.AddRecord(pixelMap);

    std::string content;
    for (int i = 0; i < FIVE * 1024 * 1024; i++) {
        content.push_back('a');
    }

    auto plain_text = std::make_shared<PlainText>(content, "");
    data.AddRecord(plain_text);

    std::string key;
    auto status = UdmfClient::GetInstance().SetData(option, data, key);
    ASSERT_EQ(E_OK, status);

    UnifiedData readData;
    QueryOption queryOption = {.key = key};
    status = UdmfClient::GetInstance().GetData(queryOption, readData);
    ASSERT_EQ(E_OK, status);
    ASSERT_EQ(2, readData.GetRecords().size());
    auto readPixelMap1 = std::static_pointer_cast<SystemDefinedPixelMap>(readData.GetRecordAt(0));
    EXPECT_EQ(FIVE * 1024 * 1024, readPixelMap1->GetRawData().size());

    auto readPlainText = std::static_pointer_cast<PlainText>(readData.GetRecordAt(1));
    EXPECT_EQ(FIVE * 1024 * 1024, readPlainText->GetContent().size());
    LOG_INFO(UDMF_TEST, "SetData008 end.");
}

/**
 * @tc.name: SetData010
 * @tc.desc:  Test set data concurrently.
 * @tc.type: FUNC
 */
HWTEST_F(UdmfClientSaInvokeTest, SetData010, TestSize.Level0)
{
    LOG_INFO(UDMF_TEST, "SetData010 begin.");
    std::thread t1([&]() {
        SetDataTest();
    });
    EXPECT_NO_FATAL_FAILURE(t1.join());
    std::thread t2([&]() {
        SetDataTest();
    });
    EXPECT_NO_FATAL_FAILURE(t2.join());
    std::thread t3([&]() {
        SetDataTest();
    });
    EXPECT_NO_FATAL_FAILURE(t3.join());

    std::thread t4([&]() {
        SetDataTest();
    });
    EXPECT_NO_FATAL_FAILURE(t4.join());
    LOG_INFO(UDMF_TEST, "SetData010 end.");
}

/**
* @tc.name: SetData008
* @tc.desc: Test set data error. Record size equals 15.5M.
* @tc.type: FUNC
*/
HWTEST_F(UdmfClientSaInvokeTest, SetData008, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetData008 begin.");

    CustomOption option = { .intention = Intention::UD_INTENTION_DRAG };
    std::vector<uint8_t> rawData;
    for (int i = 0; i < 15.5 * 1024 * 1024; i++) {
        rawData.emplace_back(1);
    }
    auto pixelMap = std::make_shared<SystemDefinedPixelMap>(rawData);
    UnifiedData data;
    data.AddRecord(pixelMap);

    std::vector<uint8_t> rawData2;
    for (int i = 0; i < 15 * 1024 * 1024; i++) {
        rawData2.emplace_back(1);
    }
    auto pixelMap2 = std::make_shared<SystemDefinedPixelMap>(rawData2);
    data.AddRecord(pixelMap2);

    std::string key;
    auto status = UdmfClient::GetInstance().SetData(option, data, key);
    ASSERT_EQ(E_OK, status);

    UnifiedData readData;
    QueryOption queryOption = {.key = key};
    status = UdmfClient::GetInstance().GetData(queryOption, readData);
    ASSERT_EQ(E_OK, status);
    ASSERT_EQ(2, readData.GetRecords().size());
    auto readPixelMap1 = std::static_pointer_cast<SystemDefinedPixelMap>(readData.GetRecordAt(0));
    EXPECT_EQ(15.5 * 1024 * 1024, readPixelMap1->GetRawData().size());

    auto readPixelMap2 = std::static_pointer_cast<SystemDefinedPixelMap>(readData.GetRecordAt(1));
    EXPECT_EQ(15 * 1024 * 1024, readPixelMap2->GetRawData().size());
    LOG_INFO(UDMF_TEST, "SetData008 end.");
}

} // OHOS::Test