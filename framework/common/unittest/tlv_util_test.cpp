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
#define LOG_TAG "TlvUtilTest"

#include <unistd.h>
#include <gtest/gtest.h>
#include <string>

#include "logger.h"
#include "tlv_util.h"

using namespace testing::ext;
using namespace OHOS::UDMF;
using namespace OHOS;
namespace OHOS::Test {
using namespace std;

class TlvUtilTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;

    std::string bundleName = "ohos.test.demo1";
};

void TlvUtilTest::SetUpTestCase()
{
}

void TlvUtilTest::TearDownTestCase()
{
}

void TlvUtilTest::SetUp()
{
}

void TlvUtilTest::TearDown()
{
}

/**
* @tc.name: CountBufferSize001
* @tc.desc: CountBufferSize, parameter is nullptr
* @tc.type: FUNC
*/
HWTEST_F(TlvUtilTest, CountBufferSize001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "CountBufferSize001 begin.");
    TLVObject data;
    bool res = TLVUtil::CountBufferSize(nullptr, data);
    EXPECT_EQ(res, false);
    LOG_INFO(UDMF_TEST, "CountBufferSize001 end.");
}

/**
* @tc.name: CountBufferSize002
* @tc.desc: CountBufferSize, unifiedRecord has error type
* @tc.type: FUNC
*/
HWTEST_F(TlvUtilTest, CountBufferSize002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "CountBufferSize002 begin.");
    TLVObject data;
    auto record = std::make_shared<UnifiedRecord>();
    record->SetType(UD_BUTT);
    bool res = TLVUtil::CountBufferSize(nullptr, data);
    EXPECT_EQ(res, false);
    LOG_INFO(UDMF_TEST, "CountBufferSize002 end.");
}

/**
* @tc.name: CountBufferSize003
* @tc.desc: CountBufferSize, unifiedData contains error unifiedRecord
* @tc.type: FUNC
*/
HWTEST_F(TlvUtilTest, CountBufferSize003, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "CountBufferSize003 begin.");
    TLVObject data;
    UnifiedData unifiedData;
    auto record = std::make_shared<UnifiedRecord>();
    record->SetType(UD_BUTT);
    unifiedData.AddRecord(record);
    bool res = TLVUtil::CountBufferSize(unifiedData, data);
    EXPECT_EQ(res, false);
    LOG_INFO(UDMF_TEST, "CountBufferSize003 end.");
}

/**
* @tc.name: CountBufferSize004
* @tc.desc: CountBufferSize, vector<unifiedData> contains error unifiedData
* @tc.type: FUNC
*/
HWTEST_F(TlvUtilTest, CountBufferSize004, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "CountBufferSize004 begin.");
    TLVObject data;
    UnifiedData unifiedData;
    auto record = std::make_shared<UnifiedRecord>();
    record->SetType(UD_BUTT);
    unifiedData.AddRecord(record);
    std::vector<UnifiedData> unifiedDatas = {unifiedData};
    bool res = TLVUtil::CountBufferSize(unifiedDatas, data);
    EXPECT_EQ(res, false);
    LOG_INFO(UDMF_TEST, "CountBufferSize004 end.");
}

/**
* @tc.name: CountBufferSize005
* @tc.desc: CountBufferSize Runtime
* @tc.type: FUNC
*/
HWTEST_F(TlvUtilTest, CountBufferSize005, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "CountBufferSize005 begin.");
    TLVObject data;
    Runtime runtime;
    UnifiedKey key;
    runtime.key = key;
    Privilege privilege;
    privilege.readPermission = "readPermission";
    privilege.writePermission = "writePermission";
    runtime.privileges.emplace_back(privilege);
    runtime.sourcePackage = bundleName;
    runtime.createPackage = bundleName;
    runtime.recordTotalNum = 5;
    bool res = TLVUtil::CountBufferSize(runtime, data);
    EXPECT_EQ(res, true);
    LOG_INFO(UDMF_TEST, "CountBufferSize005 end.");
}

/**
* @tc.name: Writing001
* @tc.desc: Writing and Reading int64_t
* @tc.type: FUNC
*/
HWTEST_F(TlvUtilTest, Writing001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "Writing001 begin.");
    TLVObject data;
    int64_t num =  -1000;
    bool res = TLVUtil::Writing(num, data);
    EXPECT_EQ(res, true);

    int64_t out;
    res = TLVUtil::Reading(out, data);
    EXPECT_EQ(res, true);
    EXPECT_EQ(num, out);
    LOG_INFO(UDMF_TEST, "Writing001 end.");
}

/**
* @tc.name: Writing002
* @tc.desc: Writing and Reading uint32_t
* @tc.type: FUNC
*/
HWTEST_F(TlvUtilTest, Writing002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "Writing002 begin.");
    TLVObject data;
    uint32_t num =  -1000;
    bool res = TLVUtil::Writing(num, data);
    EXPECT_EQ(res, true);

    uint32_t out;
    res = TLVUtil::Reading(out, data);
    EXPECT_EQ(res, true);
    EXPECT_EQ(num, out);
    LOG_INFO(UDMF_TEST, "Writing002 end.");
}

/**
* @tc.name: Writing003
* @tc.desc: Writing and Reading uint64_t
* @tc.type: FUNC
*/
HWTEST_F(TlvUtilTest, Writing003, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "Writing003 begin.");
    TLVObject data;
    uint64_t num =  1000;
    bool res = TLVUtil::Writing(num, data);
    EXPECT_EQ(res, true);

    uint64_t out;
    res = TLVUtil::Reading(out, data);
    EXPECT_EQ(res, true);
    EXPECT_EQ(num, out);
    LOG_INFO(UDMF_TEST, "Writing003 end.");
}

/**
* @tc.name: Writing004
* @tc.desc: Writing and Reading bool
* @tc.type: FUNC
*/
HWTEST_F(TlvUtilTest, Writing004, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "Writing004 begin.");
    TLVObject data;
    bool num =  true;
    bool res = TLVUtil::Writing(num, data);
    EXPECT_EQ(res, true);

    bool out;
    res = TLVUtil::Reading(out, data);
    EXPECT_EQ(res, true);
    EXPECT_EQ(num, out);
    LOG_INFO(UDMF_TEST, "Writing004 end.");
}

/**
* @tc.name: Writing005
* @tc.desc: Writing and Reading UDVariant
* @tc.type: FUNC
*/
HWTEST_F(TlvUtilTest, Writing005, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "Writing005 begin.");
    TLVObject data;
    UDVariant value = "dataPakage";
    bool res = TLVUtil::Writing(value, data);
    EXPECT_EQ(res, true);

    UDVariant out;
    res = TLVUtil::Reading(out, data);
    EXPECT_EQ(res, true);
    EXPECT_EQ(std::get<std::string>(value), std::get<std::string>(out));
    LOG_INFO(UDMF_TEST, "Writing005 end.");
}

/**
* @tc.name: Writing006
* @tc.desc: Writing and Reading UDType, invalid type
* @tc.type: FUNC
*/
HWTEST_F(TlvUtilTest, Writing006, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "Writing006 begin.");
    TLVObject data;
    UDType type = UD_BUTT;
    bool res = TLVUtil::Writing(type, data);
    EXPECT_EQ(res, true);

    UDType out;
    res = TLVUtil::Reading(out, data);
    EXPECT_EQ(res, false);
    LOG_INFO(UDMF_TEST, "Writing006 end.");
}

/**
* @tc.name: Writing007
* @tc.desc: Writing and Reading UDType
* @tc.type: FUNC
*/
HWTEST_F(TlvUtilTest, Writing007, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "Writing007 begin.");
    TLVObject data;
    UDType type = PLAIN_TEXT;
    bool res = TLVUtil::Writing(type, data);
    EXPECT_EQ(res, true);

    UDType out;
    res = TLVUtil::Reading(out, data);
    EXPECT_EQ(res, true);
    EXPECT_EQ(type, out);
    LOG_INFO(UDMF_TEST, "Writing007 end.");
}

/**
* @tc.name: Writing008
* @tc.desc: Writing and Reading vector<UnifiedData>
* @tc.type: FUNC
*/
HWTEST_F(TlvUtilTest, Writing008, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "Writing008 begin.");
    TLVObject data;
    UnifiedData unifiedData;
    auto record = std::make_shared<PlainText>();
    unifiedData.AddRecord(record);
    std::vector<UnifiedData> unifiedDatas = {unifiedData};
    bool res = TLVUtil::Writing(unifiedDatas, data);
    EXPECT_EQ(res, true);

    std::vector<UnifiedData> out;
    res = TLVUtil::Reading(out, data);
    EXPECT_EQ(res, true);
    EXPECT_FALSE(out.empty());
    EXPECT_EQ(out[0].GetTypes(), unifiedDatas[0].GetTypes());
    LOG_INFO(UDMF_TEST, "Writing008 end.");
}
} // OHOS::Test