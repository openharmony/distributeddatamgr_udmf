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
#define LOG_TAG "SystemDefinedFormTest"

#include <unistd.h>
#include <gtest/gtest.h>
#include <string>

#include "logger.h"
#include "system_defined_form.h"

using namespace testing::ext;
using namespace OHOS::UDMF;
using namespace OHOS;
namespace OHOS::Test {
using namespace std;

class SystemDefinedFormTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
};

void SystemDefinedFormTest::SetUpTestCase()
{
}

void SystemDefinedFormTest::TearDownTestCase()
{
}

void SystemDefinedFormTest::SetUp()
{
}

void SystemDefinedFormTest::TearDown()
{
}

/**
* @tc.name: SystemDefinedForm001
* @tc.desc: Normal testcase of SystemDefinedForm
* @tc.type: FUNC
*/
HWTEST_F(SystemDefinedFormTest, SystemDefinedForm001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SystemDefinedForm001 begin.");
    UDType type = UDType::ENTITY;
    ValueType value = 0;
    SystemDefinedForm systemDefinedForm(type, value);
    EXPECT_EQ(systemDefinedForm.dataType_, SYSTEM_DEFINED_FORM);
    LOG_INFO(UDMF_TEST, "SystemDefinedForm001 end.");
}

/**
* @tc.name: SystemDefinedFormSetItem001
* @tc.desc: Normal testcase of SystemDefinedForm
* @tc.type: FUNC
*/
HWTEST_F(SystemDefinedFormTest, SystemDefinedFormSetItem001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SystemDefinedFormSetItem001 begin.");
    std::shared_ptr<Object> obj = std::make_shared<Object>();
    obj->value_[FORMID] = 1;
    obj->value_[FORMNAME] = "formName";
    obj->value_[BUNDLE_NAME] = "bundleName";
    obj->value_[ABILITY_NAME] = "abilityName";
    obj->value_[MODULE] = "module";
    SystemDefinedForm systemDefinedForm(SYSTEM_DEFINED_FORM, obj);
    UDDetails details;
    details[FORMID] = 2;
    details[FORMNAME] = "formName1";
    details[BUNDLE_NAME] = "bundleName1";
    details[ABILITY_NAME] = "abilityName1";
    details[MODULE] = "module1";
    systemDefinedForm.SetItems(details);
    EXPECT_EQ(systemDefinedForm.GetFormId(), 2);
    EXPECT_EQ(systemDefinedForm.GetFormName(), "formName1");
    EXPECT_EQ(systemDefinedForm.GetBundleName(), "bundleName1");
    EXPECT_EQ(systemDefinedForm.GetAbilityName(), "abilityName1");
    EXPECT_EQ(systemDefinedForm.GetModule(), "module1");
    LOG_INFO(UDMF_TEST, "SystemDefinedFormSetItem001 end.");
}

/**
* @tc.name: SystemDefinedFormSetItem002
* @tc.desc: Abnormal testcase of SystemDefinedForm
* @tc.type: FUNC
*/
HWTEST_F(SystemDefinedFormTest, SystemDefinedFormSetItem002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SystemDefinedFormSetItem002 begin.");
    std::shared_ptr<Object> obj = std::make_shared<Object>();
    obj->value_[FORMID] = 1;
    obj->value_[FORMNAME] = "formName";
    obj->value_[BUNDLE_NAME] = "bundleName";
    obj->value_[ABILITY_NAME] = "abilityName";
    obj->value_[MODULE] = "module";
    SystemDefinedForm systemDefinedForm(SYSTEM_DEFINED_FORM, obj);
    UDDetails details;
    details[FORMID] = true;
    details[FORMNAME] = 2.1;
    details[BUNDLE_NAME] = false;
    details[ABILITY_NAME] = "abilityName1";
    details[MODULE] = "module1";
    systemDefinedForm.SetItems(details);
    EXPECT_EQ(systemDefinedForm.GetFormId(), 1);
    EXPECT_EQ(systemDefinedForm.GetFormName(), "formName");
    EXPECT_EQ(systemDefinedForm.GetBundleName(), "bundleName");
    EXPECT_EQ(systemDefinedForm.GetAbilityName(), "abilityName1");
    EXPECT_EQ(systemDefinedForm.GetModule(), "module1");
    LOG_INFO(UDMF_TEST, "SystemDefinedFormSetItem002 end.");
}

/**
* @tc.name: SystemDefinedFormGetItem001
* @tc.desc: Normal testcase of SystemDefinedForm GetItem
* @tc.type: FUNC
*/
HWTEST_F(SystemDefinedFormTest, SystemDefinedFormGetItem001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "SystemDefinedForm001 begin.");
    std::shared_ptr<Object> obj = std::make_shared<Object>();
    obj->value_[FORMID] = 1;
    obj->value_[FORMNAME] = "formName";
    obj->value_[BUNDLE_NAME] = "bundleName";
    obj->value_[ABILITY_NAME] = "abilityName";
    obj->value_[MODULE] = "module";
    SystemDefinedForm systemDefinedForm(SYSTEM_DEFINED_FORM, obj);
    UDDetails details = systemDefinedForm.GetItems();
    EXPECT_EQ(std::get<std::int32_t>(details[FORMID]), 1);
    EXPECT_EQ(std::get<std::string>(details[FORMNAME]), "formName");
    EXPECT_EQ(std::get<std::string>(details[BUNDLE_NAME]), "bundleName");
    EXPECT_EQ(std::get<std::string>(details[ABILITY_NAME]), "abilityName");
    EXPECT_EQ(std::get<std::string>(details[MODULE]), "module");
    LOG_INFO(UDMF_TEST, "SystemDefinedFormGetItem001 end.");
}

} // OHOS::Test