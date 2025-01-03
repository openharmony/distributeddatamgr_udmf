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
#define LOG_TAG "SystemDefinedAppitemTest"

#include <unistd.h>
#include <gtest/gtest.h>
#include <string>

#include "logger.h"
#include "system_defined_appitem.h"
#include "udmf_capi_common.h"

using namespace testing::ext;
using namespace OHOS::UDMF;
using namespace OHOS;
namespace OHOS::Test {
using namespace std;

class SystemDefinedAppitemTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void SystemDefinedAppitemTest::SetUpTestCase()
{
}

void SystemDefinedAppitemTest::TearDownTestCase()
{
}

void SystemDefinedAppitemTest::SetUp()
{
}

void SystemDefinedAppitemTest::TearDown()
{
}

/**
* @tc.name: SetItems001
* @tc.desc: Normal testcase of SetItems
* @tc.type: FUNC
*/
HWTEST_F(SystemDefinedAppitemTest, SetItems001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetItems001 begin.");
    SystemDefinedAppItem systemDefinedAppItem;
    UDDetails details;
    details.insert({ "string", "" });
    systemDefinedAppItem.SetItems(details);
    systemDefinedAppItem.InitObject();
    auto object = std::get<std::shared_ptr<Object>>(systemDefinedAppItem.value_);
    EXPECT_EQ(std::get<std::string>(object->value_[UNIFORM_DATA_TYPE]), "openharmony.app-item");
    LOG_INFO(UDMF_TEST, "SetItems001 end.");
}

/**
* @tc.name: SetItems002
* @tc.desc: Normal testcase of SetItems
* @tc.type: FUNC
*/
HWTEST_F(SystemDefinedAppitemTest, SetItems002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetItems002 begin.");
    UDDetails details;
    details.insert({ APP_ID, "SetItems002" });
    SystemDefinedAppItem systemDefinedAppItem;
    systemDefinedAppItem.SetItems(details);
    EXPECT_EQ(systemDefinedAppItem.appId_, "SetItems002");
    LOG_INFO(UDMF_TEST, "SetItems002 end.");
}

/**
* @tc.name: SetItems003
* @tc.desc: Normal testcase of SetItems
* @tc.type: FUNC
*/
HWTEST_F(SystemDefinedAppitemTest, SetItems003, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetItems003 begin.");
    UDDetails details;
    details.insert({ APP_NAME, "SetItems003" });
    SystemDefinedAppItem systemDefinedAppItem;
    systemDefinedAppItem.SetItems(details);
    EXPECT_EQ(systemDefinedAppItem.appName_, "SetItems003");
    LOG_INFO(UDMF_TEST, "SetItems003 end.");
}

/**
* @tc.name: SetItems004
* @tc.desc: Normal testcase of SetItems
* @tc.type: FUNC
*/
HWTEST_F(SystemDefinedAppitemTest, SetItems004, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetItems004 begin.");
    UDDetails details;
    details.insert({ APP_ICON_ID, "SetItems004" });
    SystemDefinedAppItem systemDefinedAppItem;
    systemDefinedAppItem.SetItems(details);
    EXPECT_EQ(systemDefinedAppItem.appIconId_, "SetItems004");
    LOG_INFO(UDMF_TEST, "SetItems004 end.");
}

/**
* @tc.name: SetItems005
* @tc.desc: Normal testcase of SetItems
* @tc.type: FUNC
*/
HWTEST_F(SystemDefinedAppitemTest, SetItems005, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetItems005 begin.");
    UDDetails details;
    details.insert({APP_LABEL_ID, "SetItems005" });
    SystemDefinedAppItem systemDefinedAppItem;
    systemDefinedAppItem.SetItems(details);
    EXPECT_EQ(systemDefinedAppItem.appLabelId_, "SetItems005");
    LOG_INFO(UDMF_TEST, "SetItems005 end.");
}

/**
* @tc.name: SetItems006
* @tc.desc: Normal testcase of SetItems
* @tc.type: FUNC
*/
HWTEST_F(SystemDefinedAppitemTest, SetItems006, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetItems006 begin.");
    UDDetails details;
    details.insert({ BUNDLE_NAME, "SetItems006" });
    SystemDefinedAppItem systemDefinedAppItem;
    systemDefinedAppItem.SetItems(details);
    EXPECT_EQ(systemDefinedAppItem.bundleName_, "SetItems006");
    LOG_INFO(UDMF_TEST, "SetItems006 end.");
}

/**
* @tc.name: SetItems007
* @tc.desc: Normal testcase of SetItems
* @tc.type: FUNC
*/
HWTEST_F(SystemDefinedAppitemTest, SetItems007, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SetItems007 begin.");
    UDDetails details;
    details.insert({ ABILITY_NAME, "SetItems007" });
    SystemDefinedAppItem systemDefinedAppItem;
    systemDefinedAppItem.SetItems(details);
    EXPECT_EQ(systemDefinedAppItem.abilityName_, "SetItems007");
    LOG_INFO(UDMF_TEST, "SetItems007 end.");
}

/**
* @tc.name: GetItems001
* @tc.desc: Normal testcase of GetItems
* @tc.type: FUNC
*/
HWTEST_F(SystemDefinedAppitemTest, GetItems001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetItems001 begin.");
    SystemDefinedAppItem valueType;
    valueType.appId_ = "appId";
    valueType.appName_ = "appName_";
    valueType.appIconId_ = "appIconId";
    valueType.appLabelId_ = "appLabelId";
    valueType.bundleName_ = "bundleName";
    valueType.abilityName_ = "abilityName";
    UDDetails items = valueType.GetItems();
    EXPECT_EQ(std::get<std::string>(items[APP_ID]), valueType.appId_);
    EXPECT_EQ(std::get<std::string>(items[APP_NAME]), valueType.appName_);
    EXPECT_EQ(std::get<std::string>(items[APP_ICON_ID]), valueType.appIconId_);
    EXPECT_EQ(std::get<std::string>(items[APP_LABEL_ID]), valueType.appLabelId_);
    EXPECT_EQ(std::get<std::string>(items[BUNDLE_NAME]), valueType.bundleName_);
    EXPECT_EQ(std::get<std::string>(items[ABILITY_NAME]), valueType.abilityName_);
    LOG_INFO(UDMF_TEST, "GetItems001 end.");
}

/**
* @tc.name: GetValue001
* @tc.desc: Normal testcase of GetValue
* @tc.type: FUNC
*/
HWTEST_F(SystemDefinedAppitemTest, GetValue001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "GetValue001 begin.");
    SystemDefinedAppItem valueType;
    valueType.value_ = std::monostate{};
    valueType.appId_ = "appId";
    valueType.appName_ = "appName_";
    valueType.appIconId_ = "appIconId";
    valueType.appLabelId_ = "appLabelId";
    valueType.bundleName_ = "bundleName";
    valueType.abilityName_ = "abilityName";
    valueType.InitObject();
    auto object = std::get<std::shared_ptr<Object>>(valueType.value_);
    auto details = std::get<std::shared_ptr<Object>>(object->value_[DETAILS]);
    EXPECT_EQ(std::get<std::string>(object->value_[UNIFORM_DATA_TYPE]), "openharmony.app-item");
    EXPECT_EQ(std::get<std::string>(object->value_[APP_ID]), valueType.appId_);
    EXPECT_EQ(std::get<std::string>(object->value_[APP_NAME]), valueType.appName_);
    EXPECT_EQ(std::get<std::string>(object->value_[APP_ICON_ID]), valueType.appIconId_);
    EXPECT_EQ(std::get<std::string>(object->value_[APP_LABEL_ID]), valueType.appLabelId_);
    EXPECT_EQ(std::get<std::string>(object->value_[BUNDLE_NAME]), valueType.bundleName_);
    EXPECT_EQ(std::get<std::string>(object->value_[ABILITY_NAME]), valueType.abilityName_);
    EXPECT_EQ(details->value_.size(), 0);
    LOG_INFO(UDMF_TEST, "GetValue001 end.");
}
} // OHOS::Test