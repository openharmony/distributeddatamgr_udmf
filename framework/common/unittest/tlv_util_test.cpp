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
#include "udmf_utils.h"

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
    std::shared_ptr<UnifiedRecord> record = nullptr;
    bool res = TLVUtil::CountBufferSize(record, data);
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
    bool res = TLVUtil::CountBufferSize(record, data);
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
    std::vector<uint8_t> dataBytes;
    TLVObject data(dataBytes);

    int64_t num =  -1000;
    data.Count(num);
    data.UpdateSize();
    bool res = TLVUtil::Writing(num, data);
    EXPECT_EQ(res, true);

    data.cursor_ = 0;
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
    std::vector<uint8_t> dataBytes;
    TLVObject data(dataBytes);

    uint32_t num =  -1000;
    data.Count(num);
    data.UpdateSize();
    bool res = TLVUtil::Writing(num, data);
    EXPECT_EQ(res, true);

    data.cursor_ = 0;
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
    std::vector<uint8_t> dataBytes;
    TLVObject data(dataBytes);

    uint64_t num =  1000;
    data.Count(num);
    data.UpdateSize();
    bool res = TLVUtil::Writing(num, data);
    EXPECT_EQ(res, true);

    data.cursor_ = 0;
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
    std::vector<uint8_t> dataBytes;
    TLVObject data(dataBytes);

    bool num =  true;
    data.Count(num);
    data.UpdateSize();
    bool res = TLVUtil::Writing(num, data);
    EXPECT_EQ(res, true);

    data.cursor_ = 0;
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
    std::vector<uint8_t> dataBytes;
    TLVObject data(dataBytes);

    UDVariant value = "dataPakage";
    data.Count(value);
    data.UpdateSize();
    bool res = TLVUtil::Writing(value, data);
    EXPECT_EQ(res, true);

    data.cursor_ = 0;
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
    std::vector<uint8_t> dataBytes;
    TLVObject data(dataBytes);

    UDType type = UD_BUTT;
    data.Count(type);
    data.UpdateSize();
    bool res = TLVUtil::Writing(type, data);
    EXPECT_EQ(res, true);

    data.cursor_ = 0;
    UDType out;
    res = TLVUtil::Reading(out, data);
    EXPECT_EQ(res, false);
    LOG_INFO(UDMF_TEST, "Writing006 end.");
}

/**
* @tc.name: Writing007
* @tc.desc: Writing and Reading UDType, valid type
* @tc.type: FUNC
*/
HWTEST_F(TlvUtilTest, Writing007, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "Writing007 begin.");
    std::vector<uint8_t> dataBytes;
    TLVObject data(dataBytes);

    UDType type = PLAIN_TEXT;
    data.Count(type);
    data.UpdateSize();
    bool res = TLVUtil::Writing(type, data);
    EXPECT_EQ(res, true);

    data.cursor_ = 0;
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
    std::vector<uint8_t> dataBytes;
    TLVObject data(dataBytes);

    UnifiedData unifiedData;
    auto record = std::make_shared<PlainText>();
    unifiedData.AddRecord(record);
    std::vector<UnifiedData> unifiedDatas = {unifiedData};
    TLVUtil::CountBufferSize(unifiedDatas, data);
    data.UpdateSize();
    bool res = TLVUtil::Writing(unifiedDatas, data);
    EXPECT_EQ(res, true);

    data.cursor_ = 0;
    std::vector<UnifiedData> out;
    res = TLVUtil::Reading(out, data);
    EXPECT_EQ(res, true);
    EXPECT_FALSE(out.empty());
    EXPECT_EQ(out[0].GetTypes(), unifiedDatas[0].GetTypes());
    LOG_INFO(UDMF_TEST, "Writing008 end.");
}

/**
* @tc.name: Writing009
* @tc.desc: Writing and Reading UnifiedKey
* @tc.type: FUNC
*/
HWTEST_F(TlvUtilTest, Writing009, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "Writing009 begin.");
    std::vector<uint8_t> dataBytes;
    TLVObject data(dataBytes);

    UnifiedKey key("drag", bundleName, UTILS::GenerateId());
    data.Count(key);
    data.UpdateSize();
    bool res = TLVUtil::Writing(key, data);
    EXPECT_EQ(res, true);

    data.cursor_ = 0;
    UnifiedKey out;
    res = TLVUtil::Reading(out, data);
    EXPECT_EQ(res, true);
    EXPECT_EQ(out.groupId, key.groupId);
    LOG_INFO(UDMF_TEST, "Writing009 end.");
}

/**
* @tc.name: Writing010
* @tc.desc: Writing and Reading Privilege
* @tc.type: FUNC
*/
HWTEST_F(TlvUtilTest, Writing010, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "Writing010 begin.");
    std::vector<uint8_t> dataBytes;
    TLVObject data(dataBytes);

    Privilege privilege;
    privilege.readPermission = "readPermission";
    data.Count(privilege);
    data.UpdateSize();
    bool res = TLVUtil::Writing(privilege, data);
    EXPECT_EQ(res, true);

    data.cursor_ = 0;
    Privilege out;
    res = TLVUtil::Reading(out, data);
    EXPECT_EQ(res, true);
    EXPECT_EQ(out.readPermission, privilege.readPermission);
    LOG_INFO(UDMF_TEST, "Writing010 end.");
}

/**
* @tc.name: Writing011
* @tc.desc: Writing and Reading DataStatus
* @tc.type: FUNC
*/
HWTEST_F(TlvUtilTest, Writing011, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "Writing011 begin.");
    std::vector<uint8_t> dataBytes;
    TLVObject data(dataBytes);

    DataStatus dataStatus = DataStatus::WORKING;
    data.Count(dataStatus);
    data.UpdateSize();
    bool res = TLVUtil::Writing(dataStatus, data);
    EXPECT_EQ(res, true);

    data.cursor_ = 0;
    DataStatus out;
    res = TLVUtil::Reading(out, data);
    EXPECT_EQ(res, true);
    EXPECT_EQ(out, dataStatus);
    LOG_INFO(UDMF_TEST, "Writing011 end.");
}

/**
* @tc.name: Writing012
* @tc.desc: Writing and Reading RunTime
* @tc.type: FUNC
*/
HWTEST_F(TlvUtilTest, Writing012, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "Writing012 begin.");
    std::vector<uint8_t> dataBytes;
    TLVObject data(dataBytes);

    Runtime runtime;
    Privilege privilege;
    privilege.readPermission = "readPermission";
    privilege.writePermission = "writePermission";
    runtime.privileges.emplace_back(privilege);
    runtime.sourcePackage = bundleName;
    runtime.createPackage = bundleName;
    runtime.recordTotalNum = 5;
    TLVUtil::CountBufferSize(runtime, data);
    data.UpdateSize();
    bool res = TLVUtil::Writing(runtime, data);
    EXPECT_EQ(res, true);

    data.cursor_ = 0;
    Runtime out;
    res = TLVUtil::Reading(out, data);
    EXPECT_EQ(res, true);
    EXPECT_EQ(out.sourcePackage, runtime.sourcePackage);
    LOG_INFO(UDMF_TEST, "Writing012 end.");
}
} // OHOS::Test