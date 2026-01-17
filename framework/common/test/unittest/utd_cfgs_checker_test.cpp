/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define LOG_TAG "UtdCfgsCheckerTest"

#include "utd_cfgs_checker.h"
#include <gtest/gtest.h>
#include "logger.h"

using namespace testing::ext;
using namespace OHOS::UDMF;
using namespace OHOS;

namespace OHOS::Test {
class UtdCfgsCheckerTest : public testing::Test {
public:
    static void SetUpTestCase(void);
    static void TearDownTestCase(void);
    void SetUp();
    void TearDown();
};

void UtdCfgsCheckerTest::SetUpTestCase(void) {}
void UtdCfgsCheckerTest::TearDownTestCase(void) {}
void UtdCfgsCheckerTest::SetUp(void) {}
void UtdCfgsCheckerTest::TearDown(void) {}

/**
 * @tc.name: CheckTypeDescriptors_001
 * @tc.desc: Normal testcase of CheckTypeDescriptors
 * @tc.type: FUNC
 */
HWTEST_F(UtdCfgsCheckerTest, CheckTypeDescriptors_001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "CheckTypeDescriptors_001 begin.");
    CustomUtdCfgs typeCfgs;
    TypeDescriptorCfg tdc1;
    tdc1.typeId = "com.demo.test.type";
    tdc1.filenameExtensions = {".abc"};
    tdc1.belongingToTypes = {"com.demo.test.parent"};
    tdc1.mimeTypes = {"parent/abc"};
    std::vector<TypeDescriptorCfg> first = {tdc1};
    TypeDescriptorCfg tdc2;
    tdc2.typeId = "com.demo.test.type2";
    tdc2.filenameExtensions = {".abc2"};
    tdc2.belongingToTypes = {"com.demo.test.parent2"};
    tdc2.mimeTypes = {"parent2/abc"};
    std::vector<TypeDescriptorCfg> second = {tdc2};
    CustomUtdCfgs customUtdCfgs = {first, second};

    TypeDescriptorCfg preTdc1;
    preTdc1.typeId = "com.demo.test.parent";
    TypeDescriptorCfg preTdc2;
    preTdc2.typeId = "com.demo.test.parent2";

    UtdUpdateContext context = {
        .bundleName = "com.demo.test",
        .userId = 100,
        .presetCfgs = {preTdc1, preTdc2},
        .installedCustomUtdCfgs = {},
        .installedDynamicUtdCfgs = {},
    };

    auto result = UtdCfgsChecker::GetInstance().CheckTypeDescriptors(
        customUtdCfgs, UtdTypeCategory::STATIC_TYPE, context);
    EXPECT_EQ(result, E_OK);
    LOG_INFO(UDMF_TEST, "CheckTypeDescriptors_001 end.");
}

/**
 * @tc.name: CheckTypeDescriptors_002
 * @tc.desc: testcase of CheckTypeDescriptors: failed to match the regular expression
 * @tc.type: FUNC
 */
HWTEST_F(UtdCfgsCheckerTest, CheckTypeDescriptors_002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "CheckTypeDescriptors_002 begin.");
    CustomUtdCfgs typeCfgs;
    TypeDescriptorCfg tdc1;
    tdc1.typeId = "com.demo.test.type";
    std::vector<TypeDescriptorCfg> first = {tdc1};
    TypeDescriptorCfg tdc2;
    tdc2.typeId = "errorTypeId";
    std::vector<TypeDescriptorCfg> second = {tdc2};
    CustomUtdCfgs customUtdCfgs1 = {first, second};

    TypeDescriptorCfg preTdc1;
    preTdc1.typeId = "com.demo.test.parent";
    TypeDescriptorCfg preTdc2;
    preTdc2.typeId = "com.demo.test.parent2";

    UtdUpdateContext context = {
        .bundleName = "com.demo.test",
        .userId = 100,
        .presetCfgs = {preTdc1, preTdc2},
        .installedCustomUtdCfgs = {},
        .installedDynamicUtdCfgs = {},
    };

    auto result = UtdCfgsChecker::GetInstance().CheckTypeDescriptors(
        customUtdCfgs1, UtdTypeCategory::STATIC_TYPE, context);
    EXPECT_EQ(result, E_FORMAT_ERROR);

    CustomUtdCfgs customUtdCfgs2 = {second, first};
    result = UtdCfgsChecker::GetInstance().CheckTypeDescriptors(customUtdCfgs2, UtdTypeCategory::STATIC_TYPE, context);
    EXPECT_EQ(result, E_FORMAT_ERROR);
    LOG_INFO(UDMF_TEST, "CheckTypeDescriptors_002 end.");
}

/**
 * @tc.name: CheckTypeDescriptors_003
 * @tc.desc: testcase of CheckTypeDescriptors: empty testcase
 * @tc.type: FUNC
 */
HWTEST_F(UtdCfgsCheckerTest, CheckTypeDescriptors_003, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "CheckTypeDescriptors_003 begin.");
    CustomUtdCfgs typeCfgs;
    std::vector<TypeDescriptorCfg> first = {};
    std::vector<TypeDescriptorCfg> second = {};
    CustomUtdCfgs customUtdCfgs = {first, second};

    UtdUpdateContext context = {
        .bundleName = "com.demo.test",
        .userId = 100,
        .presetCfgs = {},
        .installedCustomUtdCfgs = {},
        .installedDynamicUtdCfgs = {},
    };

    auto result = UtdCfgsChecker::GetInstance().CheckTypeDescriptors(
        customUtdCfgs, UtdTypeCategory::STATIC_TYPE, context);
    EXPECT_EQ(result, E_FORMAT_ERROR);
    LOG_INFO(UDMF_TEST, "CheckTypeDescriptors_003 end.");
}

/**
 * @tc.name: CheckTypeDescriptors_004
 * @tc.desc: testcase of CheckTypeDescriptors: filename, belongingToType or mimeType not match
 * @tc.type: FUNC
 */
HWTEST_F(UtdCfgsCheckerTest, CheckTypeDescriptors_004, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "CheckTypeDescriptors_004 begin.");
    CustomUtdCfgs typeCfgs;
    TypeDescriptorCfg tdc1;
    tdc1.typeId = "com.demo.test.type";
    std::vector<TypeDescriptorCfg> first = {tdc1};
    TypeDescriptorCfg tdc2;
    tdc2.typeId = "com.demo.test.type2";
    tdc2.filenameExtensions = {".abc2"};
    tdc2.belongingToTypes = {"com.demo.test.parent2"};
    tdc2.mimeTypes = {"parent2/abc"};
    std::vector<TypeDescriptorCfg> second = {tdc2};
    CustomUtdCfgs customUtdCfgs = {first, second};

    TypeDescriptorCfg preTdc1;
    preTdc1.typeId = "com.demo.test.parent";
    TypeDescriptorCfg preTdc2;
    preTdc2.typeId = "com.demo.test.parent2";
    std::vector<TypeDescriptorCfg> presetCfgs = {preTdc1, preTdc2};

    UtdUpdateContext context = {
        .bundleName = "com.demo.test",
        .userId = 100,
        .presetCfgs = {preTdc1, preTdc2},
        .installedCustomUtdCfgs = {},
        .installedDynamicUtdCfgs = {},
    };

    auto result = UtdCfgsChecker::GetInstance().CheckTypeDescriptors(
        customUtdCfgs, UtdTypeCategory::STATIC_TYPE, context);
    EXPECT_EQ(result, E_FORMAT_ERROR);

    tdc1.filenameExtensions = {".abc"};
    first = {tdc1};
    customUtdCfgs = {first, second};
    result = UtdCfgsChecker::GetInstance().CheckTypeDescriptors(
        customUtdCfgs, UtdTypeCategory::STATIC_TYPE, context);
    EXPECT_EQ(result, E_FORMAT_ERROR);

    tdc1.belongingToTypes = {"com.demo.test.parent"};
    tdc1.mimeTypes = {""};
    first = {tdc1};
    customUtdCfgs = {first, second};
    result = UtdCfgsChecker::GetInstance().CheckTypeDescriptors(customUtdCfgs, UtdTypeCategory::STATIC_TYPE, context);
    EXPECT_EQ(result, E_FORMAT_ERROR);

    tdc1.mimeTypes = {"parent/abc"};
    first = {tdc1};
    customUtdCfgs = {first, second};
    result = UtdCfgsChecker::GetInstance().CheckTypeDescriptors(customUtdCfgs, UtdTypeCategory::STATIC_TYPE, context);
    EXPECT_EQ(result, E_OK);
    LOG_INFO(UDMF_TEST, "CheckTypeDescriptors_004 end.");
}

/**
 * @tc.name: CheckBelongingToTypes_001
 * @tc.desc: Normal testcase of CheckTypeDescriptors
 * @tc.type: FUNC
 */
HWTEST_F(UtdCfgsCheckerTest, CheckBelongingToTypes_001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "CheckBelongingToTypes_001 begin.");
    TypeDescriptorCfg tdc1;
    tdc1.typeId = "com.demo.test.type";
    tdc1.filenameExtensions = {".abc"};
    tdc1.belongingToTypes = {""};
    tdc1.mimeTypes = {"parent/abc"};
    std::vector<TypeDescriptorCfg> typeCfgs = {tdc1};

    TypeDescriptorCfg preTdc1;
    preTdc1.typeId = "com.demo.test.parent";
    TypeDescriptorCfg preTdc2;
    preTdc2.typeId = "com.demo.test.parent2";
    std::vector<TypeDescriptorCfg> presetCfgs = {preTdc1, preTdc2};

    bool result = UtdCfgsChecker::GetInstance().CheckBelongingToTypes(typeCfgs, presetCfgs);
    EXPECT_FALSE(result);

    tdc1.belongingToTypes = {"com.demo.test.type"};
    typeCfgs = {tdc1};
    result = UtdCfgsChecker::GetInstance().CheckBelongingToTypes(typeCfgs, presetCfgs);
    EXPECT_FALSE(result);

    tdc1.belongingToTypes = {"com.demo.test.parent3"};
    typeCfgs = {tdc1};
    result = UtdCfgsChecker::GetInstance().CheckBelongingToTypes(typeCfgs, presetCfgs);
    EXPECT_FALSE(result);

    tdc1.belongingToTypes = {"com.demo.test.parent"};
    typeCfgs = {tdc1};
    result = UtdCfgsChecker::GetInstance().CheckBelongingToTypes(typeCfgs, presetCfgs);
    EXPECT_TRUE(result);

    LOG_INFO(UDMF_TEST, "CheckBelongingToTypes_001 end.");
}

/**
 * @tc.name: CheckTypeDescriptors_005
 * @tc.desc: Normal testcase of CheckTypeDescriptors
 * @tc.type: FUNC
 */
HWTEST_F(UtdCfgsCheckerTest, CheckTypeDescriptors_005, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "CheckTypeDescriptors_005 begin.");
    TypeDescriptorCfg tdc1;
    tdc1.typeId = "com.demo.test.type";
    tdc1.filenameExtensions = {".abc"};
    tdc1.belongingToTypes = {"com.demo.test.parent"};
    tdc1.mimeTypes = {"parent/abc"};
    TypeDescriptorCfg tdc2;
    tdc2.typeId = "com.demo.test.type2";
    tdc2.filenameExtensions = {".abc2"};
    tdc2.belongingToTypes = {"com.demo.test.parent2"};
    tdc2.mimeTypes = {"parent2/abc"};
    std::vector<TypeDescriptorCfg> first = {tdc1, tdc2};
    TypeDescriptorCfg tdc3;
    tdc3.typeId = "com.demo.test.parent";
    tdc3.filenameExtensions = {".abc3"};
    tdc3.belongingToTypes = {"com.demo.test.parent3"};
    tdc3.mimeTypes = {"parent3/abc"};
    TypeDescriptorCfg tdc4;
    tdc4.typeId = "com.demo.test.parent2";
    tdc4.filenameExtensions = {".abc4"};
    tdc4.belongingToTypes = {"com.demo.test.parent4"};
    tdc4.mimeTypes = {"parent4/abc"};
    std::vector<TypeDescriptorCfg> second = {tdc3, tdc4};
    CustomUtdCfgs customUtdCfgs = {first, second};

    TypeDescriptorCfg presetCfg1;
    presetCfg1.typeId = "com.demo.test.parent3";
    presetCfg1.filenameExtensions = {".abca3"};
    presetCfg1.belongingToTypes = {"com.demo.test.parent5"};
    presetCfg1.mimeTypes = {"parent3/abc"};
    TypeDescriptorCfg presetCfg2;
    presetCfg2.typeId = "com.demo.test.parent4";
    presetCfg2.filenameExtensions = {".abca3"};
    presetCfg2.belongingToTypes = {"com.demo.test.parent6"};
    presetCfg2.mimeTypes = {"parent3/abc"};
    UtdUpdateContext context = {
        .bundleName = "com.demo.test",
        .userId = 100,
        .presetCfgs = {presetCfg1, presetCfg2},
        .installedCustomUtdCfgs = {},
        .installedDynamicUtdCfgs = {},
    };
    auto result = UtdCfgsChecker::GetInstance().CheckTypeDescriptors(
        customUtdCfgs, UtdTypeCategory::STATIC_TYPE, context);
    EXPECT_EQ(result, E_OK);
    LOG_INFO(UDMF_TEST, "CheckTypeDescriptors_005 end.");
}

/**
 * @tc.name: CheckTypeIdUniqueness_001
 * @tc.desc: Normal testcase of CheckTypeIdUniqueness
 * @tc.type: FUNC
 */
HWTEST_F(UtdCfgsCheckerTest, CheckTypeIdUniqueness_001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "CheckTypeIdUniqueness_001 begin.");
    TypeDescriptorCfg type1;
    type1.typeId = "general.type1";
    std::vector<TypeDescriptorCfg> presetCfgs = {type1};

    TypeDescriptorCfg type2;
    type2.typeId = "com.demo.test.type2";
    type2.ownerBundle = "com.demo.test";

    TypeDescriptorCfg type3;
    type3.typeId = "com.demo.test.type3";
    type3.ownerBundle = "com.demo.test";
    
    UtdUpdateContext ctx = {
        .presetCfgs = {type1}
    };
    ctx.installedDynamicUtdCfgs = { type2 };
    ctx.installedCustomUtdCfgs = { type3 };

    TypeDescriptorCfg type4;
    type4.typeId = "com.demo.test.type4";
    type4.ownerBundle = "com.demo.test";

    CustomUtdCfgs installing = {{type4}, {}};
    EXPECT_TRUE(UtdCfgsChecker::GetInstance().CheckTypeIdUniqueness(installing, UtdTypeCategory::DYNAMIC_TYPE, ctx));
    EXPECT_TRUE(UtdCfgsChecker::GetInstance().CheckTypeIdUniqueness(installing, UtdTypeCategory::STATIC_TYPE, ctx));

    installing = {{}, {type4}};
    EXPECT_TRUE(UtdCfgsChecker::GetInstance().CheckTypeIdUniqueness(installing, UtdTypeCategory::DYNAMIC_TYPE, ctx));
    EXPECT_TRUE(UtdCfgsChecker::GetInstance().CheckTypeIdUniqueness(installing, UtdTypeCategory::STATIC_TYPE, ctx));
}

/**
 * @tc.name: CheckTypeIdUniqueness_002
 * @tc.desc: Normal testcase of CheckTypeIdUniqueness
 * @tc.type: FUNC
 */
HWTEST_F(UtdCfgsCheckerTest, CheckTypeIdUniqueness_002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "CheckTypeIdUniqueness_002 begin.");
    TypeDescriptorCfg type1;
    type1.typeId = "general.type1";
    std::vector<TypeDescriptorCfg> presetCfgs = {type1};

    TypeDescriptorCfg type2;
    type2.typeId = "com.demo.test.type2";
    type2.ownerBundle = "com.demo.test";

    TypeDescriptorCfg type3;
    type3.typeId = "com.demo.test.type3";
    type3.ownerBundle = "com.demo.test";
    
    UtdUpdateContext ctx = {
        .presetCfgs = {type1}
    };
    ctx.installedDynamicUtdCfgs = { type2 };
    ctx.installedCustomUtdCfgs = { type3 };

    TypeDescriptorCfg type4;
    type4.typeId = "com.demo.test.type3";
    type4.ownerBundle = "";

    CustomUtdCfgs installing = {{}, {type4}};
    EXPECT_TRUE(UtdCfgsChecker::GetInstance().CheckTypeIdUniqueness(installing, UtdTypeCategory::STATIC_TYPE, ctx));
}

/**
 * @tc.name: CheckTypeIdUniqueness_003
 * @tc.desc: Normal testcase of CheckTypeIdUniqueness
 * @tc.type: FUNC
 */
HWTEST_F(UtdCfgsCheckerTest, CheckTypeIdUniqueness_003, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "CheckTypeIdUniqueness_003 begin.");
    TypeDescriptorCfg type1;
    type1.typeId = "general.type1";
    std::vector<TypeDescriptorCfg> presetCfgs = {type1};

    TypeDescriptorCfg type2;
    type2.typeId = "com.demo.test.type2";
    type2.ownerBundle = "com.demo.test";

    TypeDescriptorCfg type3;
    type3.typeId = "com.demo.test.type3";
    type3.ownerBundle = "";
    
    UtdUpdateContext ctx = {
        .presetCfgs = {type1}
    };
    ctx.installedDynamicUtdCfgs = { type2 };
    ctx.installedCustomUtdCfgs = { type3 };

    TypeDescriptorCfg type4;
    type4.typeId = "com.demo.test.type3";
    type4.ownerBundle = "com.demo.test";
    CustomUtdCfgs installing = {{}, {type4}};
    EXPECT_TRUE(UtdCfgsChecker::GetInstance().CheckTypeIdUniqueness(installing, UtdTypeCategory::STATIC_TYPE, ctx));

    type4.ownerBundle = "";
    installing = {{}, {type4}};
    EXPECT_TRUE(UtdCfgsChecker::GetInstance().CheckTypeIdUniqueness(installing, UtdTypeCategory::STATIC_TYPE, ctx));
}

/**
 * @tc.name: CheckTypeIdUniqueness_004
 * @tc.desc: Abnormal testcase of CheckTypeIdUniqueness
 * @tc.type: FUNC
 */
HWTEST_F(UtdCfgsCheckerTest, CheckTypeIdUniqueness_004, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "CheckTypeIdUniqueness_004 begin.");
    TypeDescriptorCfg type1;
    type1.typeId = "general.type1";
    std::vector<TypeDescriptorCfg> presetCfgs = {type1};

    TypeDescriptorCfg type2;
    type2.typeId = "com.demo.test.type2";
    type2.ownerBundle = "com.demo.test";

    TypeDescriptorCfg type3;
    type3.typeId = "com.demo.test.type3";
    type3.ownerBundle = "com.demo.test";
    
    UtdUpdateContext ctx = {
        .presetCfgs = {type1}
    };
    ctx.installedDynamicUtdCfgs = { type2 };
    ctx.installedCustomUtdCfgs = { type3 };

    TypeDescriptorCfg type4;
    type4.typeId = "general.type1";
    CustomUtdCfgs installing = {{}, {type4}};
    EXPECT_FALSE(UtdCfgsChecker::GetInstance().CheckTypeIdUniqueness(installing, UtdTypeCategory::STATIC_TYPE, ctx));

    type4.typeId = "com.demo.test.type2";
    installing = {{}, {type4}};
    EXPECT_FALSE(UtdCfgsChecker::GetInstance().CheckTypeIdUniqueness(installing, UtdTypeCategory::STATIC_TYPE, ctx));
}

/**
 * @tc.name: CheckTypeIdUniqueness_005
 * @tc.desc: Abnormal testcase of CheckTypeIdUniqueness
 * @tc.type: FUNC
 */
HWTEST_F(UtdCfgsCheckerTest, CheckTypeIdUniqueness_005, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "CheckTypeIdUniqueness_005 begin.");
    TypeDescriptorCfg type1;
    type1.typeId = "general.type1";
    std::vector<TypeDescriptorCfg> presetCfgs = {type1};

    TypeDescriptorCfg type2;
    type2.typeId = "com.demo.test.type2";
    type2.ownerBundle = "com.demo.test";

    TypeDescriptorCfg type3;
    type3.typeId = "com.demo.test.type3";
    type3.ownerBundle = "com.demo.test";
    
    UtdUpdateContext ctx = {
        .presetCfgs = {type1}
    };
    ctx.installedDynamicUtdCfgs = { type2 };
    ctx.installedCustomUtdCfgs = { type3 };

    TypeDescriptorCfg type4;
    type4.typeId = "general.type1";
    CustomUtdCfgs installing = {{type4}, {}};
    EXPECT_FALSE(UtdCfgsChecker::GetInstance().CheckTypeIdUniqueness(installing, UtdTypeCategory::STATIC_TYPE, ctx));
    EXPECT_FALSE(UtdCfgsChecker::GetInstance().CheckTypeIdUniqueness(installing, UtdTypeCategory::DYNAMIC_TYPE, ctx));

    type4.typeId = "com.demo.test.type2";
    installing = {{type4}, {}};
    EXPECT_FALSE(UtdCfgsChecker::GetInstance().CheckTypeIdUniqueness(installing, UtdTypeCategory::STATIC_TYPE, ctx));
    EXPECT_FALSE(UtdCfgsChecker::GetInstance().CheckTypeIdUniqueness(installing, UtdTypeCategory::DYNAMIC_TYPE, ctx));

    type4.typeId = "com.demo.test.type3";
    installing = {{type4}, {}};
    EXPECT_FALSE(UtdCfgsChecker::GetInstance().CheckTypeIdUniqueness(installing, UtdTypeCategory::STATIC_TYPE, ctx));
    EXPECT_FALSE(UtdCfgsChecker::GetInstance().CheckTypeIdUniqueness(installing, UtdTypeCategory::DYNAMIC_TYPE, ctx));
}
}