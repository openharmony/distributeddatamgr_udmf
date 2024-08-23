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
#define LOG_TAG "FlexibleTypeTest"

#include <unistd.h>
#include <gtest/gtest.h>
#include <string>

#include "logger.h"
#include "flexible_type.h"

using namespace testing::ext;
using namespace OHOS::UDMF;
using namespace OHOS;
namespace OHOS::Test {
using namespace std;

class FlexibleTypeTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void FlexibleTypeTest::SetUpTestCase()
{
}

void FlexibleTypeTest::TearDownTestCase()
{
}

void FlexibleTypeTest::SetUp()
{
}

void FlexibleTypeTest::TearDown()
{
}

/**
* @tc.name: EscapeStr001
* @tc.desc: Normal testcase of EscapeStr
* @tc.type: FUNC
*/
HWTEST_F(FlexibleTypeTest, EscapeStr001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "EscapeStr001 begin.");
    const std::string chs = "string?";
    string output = FlexibleType::EscapeStr(chs);
    EXPECT_EQ(output, "string\\?");
    LOG_INFO(UDMF_TEST, "EscapeStr001 end.");
}

/**
* @tc.name: EscapeStr002
* @tc.desc: Normal testcase of EscapeStr
* @tc.type: FUNC
*/
HWTEST_F(FlexibleTypeTest, EscapeStr002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "EscapeStr002 begin.");
    const std::string chs = "string:";
    string output = FlexibleType::EscapeStr(chs);
    EXPECT_EQ(output, "string\\:");
    LOG_INFO(UDMF_TEST, "EscapeStr002 end.");
}

/**
* @tc.name: EscapeStr003
* @tc.desc: Normal testcase of EscapeStr
* @tc.type: FUNC
*/
HWTEST_F(FlexibleTypeTest, EscapeStr003, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "EscapeStr003 begin.");
    const std::string chs = "string=";
    string output = FlexibleType::EscapeStr(chs);
    EXPECT_EQ(output, "string\\=");
    LOG_INFO(UDMF_TEST, "EscapeStr003 end.");
}

/**
* @tc.name: EscapeStr004
* @tc.desc: Normal testcase of EscapeStr
* @tc.type: FUNC
*/
HWTEST_F(FlexibleTypeTest, EscapeStr004, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "EscapeStr004 begin.");
    const std::string chs = "string,";
    string output = FlexibleType::EscapeStr(chs);
    EXPECT_EQ(output, "string\\,");
    LOG_INFO(UDMF_TEST, "EscapeStr004 end.");
}

/**
* @tc.name: EscapeStr005
* @tc.desc: Normal testcase of EscapeStr
* @tc.type: FUNC
*/
HWTEST_F(FlexibleTypeTest, EscapeStr005, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "EscapeStr005 begin.");
    const std::string chs = "string\\";
    string output = FlexibleType::EscapeStr(chs);
    EXPECT_EQ(output, "string\\\\");
    LOG_INFO(UDMF_TEST, "EscapeStr005 end.");
}

/**
* @tc.name: EscapeStr006
* @tc.desc: Abnormal testcase of EscapeStr, because chs doesn't include '?'、 ':'、 '='、',' and '\\'
* @tc.type: FUNC
*/
HWTEST_F(FlexibleTypeTest, EscapeStr006, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "EscapeStr006 begin.");
    const std::string chs = "string";
    string output = FlexibleType::EscapeStr(chs);
    EXPECT_EQ(output, "string");
    LOG_INFO(UDMF_TEST, "EscapeStr006 end.");
}

/**
* @tc.name: ParseFlexibleUtd007
* @tc.desc: Abnormal testcase of ParseFlexibleUtd, because typeId and FLEXIBLE_TYPE_FLAG are equal
* @tc.type: FUNC
*/
HWTEST_F(FlexibleTypeTest, ParseFlexibleUtd007, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "ParseFlexibleUtd007 begin.");
    const std::string typeId = "flex.z";
    TypeDescriptorCfg flexibleTypeDescriptorCfg;
    flexibleTypeDescriptorCfg.typeId = "com.example.utdtest.document";
    flexibleTypeDescriptorCfg.belongingToTypes = {"com.example.utdtest2.document"};
    flexibleTypeDescriptorCfg.filenameExtensions = {".mydocument"};
    flexibleTypeDescriptorCfg.mimeTypes = {"application/my-document"};
    flexibleTypeDescriptorCfg.description = "My document.";
    flexibleTypeDescriptorCfg.referenceURL = "http://www.mycompany.com/my-document.html";
    flexibleTypeDescriptorCfg.iconFile = "resources/my-document.png";
    flexibleTypeDescriptorCfg.ownerBundle = "com.example.utdtest";
    flexibleTypeDescriptorCfg.installerBundles = {"com.example.utdtest"};
    FlexibleType flexibleType;
    bool ret = flexibleType.ParseFlexibleUtd(typeId, flexibleTypeDescriptorCfg);
    EXPECT_FALSE(ret);
    LOG_INFO(UDMF_TEST, "ParseFlexibleUtd007 end.");
}

/**
* @tc.name: ParseFlexibleUtd008
* @tc.desc: Abnormal testcase of ParseFlexibleUtd, because flexibleUtdDecode[0] != '?'
* @tc.type: FUNC
*/
HWTEST_F(FlexibleTypeTest, ParseFlexibleUtd008, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "ParseFlexibleUtd008 begin.");
    const std::string typeId = "com.example.utdtest.document";
    TypeDescriptorCfg flexibleTypeDescriptorCfg;
    flexibleTypeDescriptorCfg.typeId = "com.example.utdtest.document";
    flexibleTypeDescriptorCfg.belongingToTypes = {"com.example.utdtest2.document"};
    flexibleTypeDescriptorCfg.filenameExtensions = {".mydocument"};
    flexibleTypeDescriptorCfg.mimeTypes = {"application/my-document"};
    flexibleTypeDescriptorCfg.description = "My document.";
    flexibleTypeDescriptorCfg.referenceURL = "http://www.mycompany.com/my-document.html";
    flexibleTypeDescriptorCfg.iconFile = "resources/my-document.png";
    flexibleTypeDescriptorCfg.ownerBundle = "com.example.utdtest";
    flexibleTypeDescriptorCfg.installerBundles = {"com.example.utdtest"};
    FlexibleType flexibleType;
    bool ret = flexibleType.ParseFlexibleUtd(typeId, flexibleTypeDescriptorCfg);
    EXPECT_FALSE(ret);
    LOG_INFO(UDMF_TEST, "ParseFlexibleUtd008 end.");
}

/**
* @tc.name: ParseFlexibleUtd009
* @tc.desc: Abnormal testcase of ParseFlexibleUtd, because flexibleUtdDecode contains "="
* @tc.type: FUNC
*/
HWTEST_F(FlexibleTypeTest, ParseFlexibleUtd009, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "ParseFlexibleUtd009 begin.");
    const std::string typeId = "flex.z=";
    TypeDescriptorCfg flexibleTypeDescriptorCfg;
    flexibleTypeDescriptorCfg.typeId = "com.example.utdtest.document";
    flexibleTypeDescriptorCfg.belongingToTypes = {"com.example.utdtest2.document"};
    flexibleTypeDescriptorCfg.filenameExtensions = {".mydocument"};
    flexibleTypeDescriptorCfg.mimeTypes = {"application/my-document"};
    flexibleTypeDescriptorCfg.description = "My document.";
    flexibleTypeDescriptorCfg.referenceURL = "http://www.mycompany.com/my-document.html";
    flexibleTypeDescriptorCfg.iconFile = "resources/my-document.png";
    flexibleTypeDescriptorCfg.ownerBundle = "com.example.utdtest";
    flexibleTypeDescriptorCfg.installerBundles = {"com.example.utdtest"};
    FlexibleType flexibleType;
    bool ret = flexibleType.ParseFlexibleUtd(typeId, flexibleTypeDescriptorCfg);
    EXPECT_FALSE(ret);
    LOG_INFO(UDMF_TEST, "ParseFlexibleUtd009 end.");
}
} // OHOS::Test