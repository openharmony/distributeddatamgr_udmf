/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
#define LOG_TAG "UtdDynamicUpdateTest"
#include <gtest/gtest.h>

#include <unistd.h>
#include <thread>

#include "token_setproc.h"
#include "accesstoken_kit.h"
#include "nativetoken_kit.h"

#include "logger.h"
#include "utd_client.h"
#include "type_descriptor.h"
#include "preset_type_descriptors.h"
#include "utd_graph.h"
#include "custom_utd_store.h"

using namespace testing::ext;
using namespace OHOS::Security::AccessToken;
using namespace OHOS::UDMF;
using namespace OHOS;

namespace OHOS::Test {
constexpr const int32_t USER_ID = 100;
constexpr const char *HAP_BUNDLE_NAME = "ohos.test.utddemo999";
constexpr const char *SYS_HAP_BUNDLE_NAME = "ohos.test.utddemo998";

class UtdDynamicUpdateTest : public testing::Test {
public:
    static void SetUpTestCase();
    static void TearDownTestCase();
    void SetUp() override;
    void TearDown() override;
    static void AllocHapToken1();
    static void AllocSysHapToken();
    static void AllocFoundationToken();
};

void UtdDynamicUpdateTest::SetUpTestCase()
{
}

void UtdDynamicUpdateTest::TearDownTestCase()
{
    auto tokenId = AccessTokenKit::GetHapTokenID(USER_ID, HAP_BUNDLE_NAME, 0);
    AccessTokenKit::DeleteToken(tokenId);
    tokenId = AccessTokenKit::GetHapTokenID(USER_ID, SYS_HAP_BUNDLE_NAME, 0);
    AccessTokenKit::DeleteToken(tokenId);
}

void UtdDynamicUpdateTest::SetUp()
{
}

void UtdDynamicUpdateTest::TearDown()
{
}

void UtdDynamicUpdateTest::AllocHapToken1()
{
    HapInfoParams info = {
        .userID = USER_ID,
        .bundleName = HAP_BUNDLE_NAME,
        .instIndex = 0,
        .appIDDesc = HAP_BUNDLE_NAME
    };

    HapPolicyParams policy = {
        .apl = APL_NORMAL,
        .domain = "test.domain",
        .permList = {
            {
                .permissionName = "ohos.permission.test",
                .bundleName = HAP_BUNDLE_NAME,
                .grantMode = 1,
                .availableLevel = APL_NORMAL,
                .label = "label",
                .labelId = 1,
                .description = "test1",
                .descriptionId = 1
            }
        },
        .permStateList = {
            {
                .permissionName = "ohos.permission.test",
                .isGeneral = true,
                .resDeviceID = { "local" },
                .grantStatus = { PermissionState::PERMISSION_GRANTED },
                .grantFlags = { 1 }
            }
        }
    };
    auto tokenID = AccessTokenKit::AllocHapToken(info, policy);
    SetSelfTokenID(tokenID.tokenIDEx);
}

void UtdDynamicUpdateTest::AllocSysHapToken()
{
    HapInfoParams info = {
        .userID = USER_ID,
        .bundleName = SYS_HAP_BUNDLE_NAME,
        .instIndex = 0,
        .appIDDesc = SYS_HAP_BUNDLE_NAME,
        .isSystemApp = true,
    };

    HapPolicyParams policy = {
        .apl = APL_SYSTEM_BASIC,
        .domain = "test.domain",
        .permList = {
            {
                .permissionName = "ohos.permission.MANAGE_DYNAMIC_UTD_TYPE",
                .bundleName = SYS_HAP_BUNDLE_NAME,
                .grantMode = 1,
                .availableLevel = APL_SYSTEM_BASIC,
                .label = "label",
                .labelId = 1,
                .description = "test1",
                .descriptionId = 1
            }
        },
        .permStateList = {
            {
                .permissionName = "ohos.permission.MANAGE_DYNAMIC_UTD_TYPE",
                .isGeneral = true,
                .resDeviceID = { "local" },
                .grantStatus = { PermissionState::PERMISSION_GRANTED },
                .grantFlags = { 1 }
            }
        }
    };
    auto tokenID = AccessTokenKit::AllocHapToken(info, policy);
    SetSelfTokenID(tokenID.tokenIDEx);
}

void UtdDynamicUpdateTest::AllocFoundationToken()
{
    auto tokenId = AccessTokenKit::GetNativeTokenId("foundation");
    SetSelfTokenID(tokenId);
}

/**
* @tc.name: RegisterTypeDescriptors001
* @tc.desc: Normal test case
* @tc.type: FUNC
*/
HWTEST_F(UtdDynamicUpdateTest, RegisterTypeDescriptors001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "RegisterTypeDescriptors001 begin.");
    AllocSysHapToken();
    std::vector<TypeDescriptorCfg> descriptors(50);
    for (size_t i = 0; i < 50; ++i) {
        descriptors[i] = {
            .typeId = std::string(SYS_HAP_BUNDLE_NAME) + std::string(".ppp") + std::to_string(i),
            .belongingToTypes = {"general.file"},
            .filenameExtensions = {".ppp"},
            .mimeTypes = {},
        };
    }
    auto status = UtdClient::GetInstance().RegisterTypeDescriptors(descriptors);
    ASSERT_EQ(status, E_OK);
    for (size_t j = 0; j < 50; ++j) {
        AllocFoundationToken();
        UtdClient::GetInstance().InitializeUtdTypes();
        std::shared_ptr<TypeDescriptor> descriptor;
        status = UtdClient::GetInstance().GetTypeDescriptor(descriptors[j].typeId, descriptor);
        ASSERT_EQ(status, E_OK);
        ASSERT_NE(descriptor, nullptr);

        EXPECT_EQ(descriptor->typeId_, descriptors[j].typeId);
        EXPECT_EQ(descriptor->belongingToTypes_, descriptors[j].belongingToTypes);
        EXPECT_EQ(descriptor->filenameExtensions_, descriptors[j].filenameExtensions);
        EXPECT_EQ(descriptor->mimeTypes_, descriptors[j].mimeTypes);
        AllocSysHapToken();
        std::vector<std::string> typeIds = {std::string(SYS_HAP_BUNDLE_NAME) + ".ppp" + std::to_string(j)};
        status = UtdClient::GetInstance().UnregisterTypeDescriptors(typeIds);
        ASSERT_EQ(status, E_OK);

        AllocFoundationToken();
        UtdClient::GetInstance().InitializeUtdTypes();
        descriptor = nullptr;
        status = UtdClient::GetInstance().GetTypeDescriptor(descriptors[j].typeId, descriptor);
        ASSERT_EQ(status, E_OK);
        ASSERT_EQ(descriptor, nullptr);
    }
    LOG_INFO(UDMF_TEST, "RegisterTypeDescriptors001 end.");
};

/**
* @tc.name: RegisterTypeDescriptors002
* @tc.desc: Abnormal test case, format error: invalid typeId
* @tc.type: FUNC
*/
HWTEST_F(UtdDynamicUpdateTest, RegisterTypeDescriptors002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "RegisterTypeDescriptors002 begin.");
    AllocSysHapToken();
    std::vector<TypeDescriptorCfg> descriptors(1);
    descriptors[0] = {
        .typeId = "",
        .belongingToTypes = {"general.file"},
        .filenameExtensions = {".ppp"},
        .mimeTypes = {},
    };
    auto status = UtdClient::GetInstance().RegisterTypeDescriptors(descriptors);
    EXPECT_NE(status, E_OK);

    descriptors[0] = {
        .typeId = std::string(SYS_HAP_BUNDLE_NAME),
        .belongingToTypes = {"general.file"},
        .filenameExtensions = {".ppp"},
        .mimeTypes = {},
    };
    status = UtdClient::GetInstance().RegisterTypeDescriptors(descriptors);
    EXPECT_NE(status, E_OK);

    descriptors[0] = {
        .typeId = std::string(SYS_HAP_BUNDLE_NAME) + "?",
        .belongingToTypes = {"general.file"},
        .filenameExtensions = {".ppp"},
        .mimeTypes = {},
    };
    status = UtdClient::GetInstance().RegisterTypeDescriptors(descriptors);
    EXPECT_EQ(status, E_FORMAT_ERROR);
    LOG_INFO(UDMF_TEST, "RegisterTypeDescriptors002 end.");
};

/**
* @tc.name: RegisterTypeDescriptors003
* @tc.desc: Abnormal test case, format error: invalid belongingToTypes
* @tc.type: FUNC
*/
HWTEST_F(UtdDynamicUpdateTest, RegisterTypeDescriptors003, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "RegisterTypeDescriptors003 begin.");
    AllocSysHapToken();
    std::vector<TypeDescriptorCfg> descriptors(1);
    descriptors[0] = {
        .typeId = std::string(SYS_HAP_BUNDLE_NAME) + ".ppp",
        .belongingToTypes = {},
        .filenameExtensions = {".ppp"},
        .mimeTypes = {},
    };
    auto status = UtdClient::GetInstance().RegisterTypeDescriptors(descriptors);
    EXPECT_EQ(status, E_FORMAT_ERROR);

    descriptors[0] = {
        .typeId = std::string(SYS_HAP_BUNDLE_NAME) + ".ppp",
        .belongingToTypes = {"none-exist-type"},
        .filenameExtensions = {".ppp"},
        .mimeTypes = {},
    };
    status = UtdClient::GetInstance().RegisterTypeDescriptors(descriptors);
    EXPECT_EQ(status, E_CONTENT_ERROR);
    LOG_INFO(UDMF_TEST, "RegisterTypeDescriptors003 end.");
};

/**
* @tc.name: RegisterTypeDescriptors004
* @tc.desc: Abnormal test case, format error: invalid filenameExtensions
* @tc.type: FUNC
*/
HWTEST_F(UtdDynamicUpdateTest, RegisterTypeDescriptors004, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "RegisterTypeDescriptors004 begin.");
    AllocSysHapToken();
    std::vector<TypeDescriptorCfg> descriptors(1);
    descriptors[0] = {
        .typeId = std::string(SYS_HAP_BUNDLE_NAME) + ".ppp",
        .belongingToTypes = {"general.file"},
        .filenameExtensions = {"."},
        .mimeTypes = {},
    };
    auto status = UtdClient::GetInstance().RegisterTypeDescriptors(descriptors);
    EXPECT_EQ(status, E_FORMAT_ERROR);

    descriptors[0] = {
        .typeId = std::string(SYS_HAP_BUNDLE_NAME) + ".ppp",
        .belongingToTypes = {"general.file"},
        .filenameExtensions = {"ppp"},
        .mimeTypes = {},
    };
    status = UtdClient::GetInstance().RegisterTypeDescriptors(descriptors);
    EXPECT_EQ(status, E_FORMAT_ERROR);

    std::string str(127, 'a');
    descriptors[0] = {
        .typeId = std::string(SYS_HAP_BUNDLE_NAME) + ".ppp",
        .belongingToTypes = {"general.file"},
        .filenameExtensions = {"." + str},
        .mimeTypes = {},
    };
    status = UtdClient::GetInstance().RegisterTypeDescriptors(descriptors);
    EXPECT_EQ(status, E_FORMAT_ERROR);
    LOG_INFO(UDMF_TEST, "RegisterTypeDescriptors004 end.");
};

/**
* @tc.name: RegisterTypeDescriptors005
* @tc.desc: Abnormal test case, format error: invalid mimeTypes
* @tc.type: FUNC
*/
HWTEST_F(UtdDynamicUpdateTest, RegisterTypeDescriptors005, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "RegisterTypeDescriptors005 begin.");
    AllocSysHapToken();
    std::vector<TypeDescriptorCfg> descriptors(1);
    std::string str(128, 'a');
    descriptors[0] = {
        .typeId = std::string(SYS_HAP_BUNDLE_NAME) + ".ppp",
        .belongingToTypes = {"general.file"},
        .filenameExtensions = {".ppp"},
        .mimeTypes = {str},
    };
    auto status = UtdClient::GetInstance().RegisterTypeDescriptors(descriptors);
    EXPECT_EQ(status, E_FORMAT_ERROR);
    LOG_INFO(UDMF_TEST, "RegisterTypeDescriptors005 end.");
};

/**
* @tc.name: RegisterTypeDescriptors006
* @tc.desc: Abnormal test case, violate rule: not unique typeId
* @tc.type: FUNC
*/
HWTEST_F(UtdDynamicUpdateTest, RegisterTypeDescriptors006, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "RegisterTypeDescriptors006 begin.");
    AllocSysHapToken();
    std::vector<TypeDescriptorCfg> descriptors(1);
    descriptors[0] = {
        .typeId = std::string(SYS_HAP_BUNDLE_NAME) + ".ppp",
        .belongingToTypes = {"general.file"},
        .filenameExtensions = {".ppp"},
        .mimeTypes = {},
    };
    auto status = UtdClient::GetInstance().RegisterTypeDescriptors(descriptors);
    ASSERT_EQ(status, E_OK);

    status = UtdClient::GetInstance().RegisterTypeDescriptors(descriptors);
    ASSERT_EQ(status, E_CONTENT_ERROR);

    std::vector<std::string> typeIds = {std::string(SYS_HAP_BUNDLE_NAME) + ".ppp"};
    status = UtdClient::GetInstance().UnregisterTypeDescriptors(typeIds);
    ASSERT_EQ(status, E_OK);

    status = UtdClient::GetInstance().UnregisterTypeDescriptors(typeIds);
    ASSERT_EQ(status, E_INVALID_TYPE_ID);
    LOG_INFO(UDMF_TEST, "RegisterTypeDescriptors006 end.");
};

/**
* @tc.name: RegisterTypeDescriptors007
* @tc.desc: Normal test case
* @tc.type: FUNC
*/
HWTEST_F(UtdDynamicUpdateTest, RegisterTypeDescriptors007, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "RegisterTypeDescriptors007 begin.");
    AllocSysHapToken();
    std::vector<TypeDescriptorCfg> descriptors(200);
    for (size_t i = 0; i < 200; i++) {
        descriptors[i] = {
            .typeId = std::string(SYS_HAP_BUNDLE_NAME) + std::string(".ppp") + std::to_string(i),
            .belongingToTypes = {"general.file"},
            .filenameExtensions = {std::string(".ppp")},
            .mimeTypes = {},
        };
    }
    auto status = UtdClient::GetInstance().RegisterTypeDescriptors(descriptors);
    ASSERT_EQ(status, E_FORMAT_ERROR);
    LOG_INFO(UDMF_TEST, "RegisterTypeDescriptors007 end.");
};

/**
* @tc.name: UnregisterTypeDescriptors001
* @tc.desc: Abnormal test case, format error: invalid typeIds
* @tc.type: FUNC
*/
HWTEST_F(UtdDynamicUpdateTest, UnregisterTypeDescriptors001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "UnregisterTypeDescriptors001 begin.");
    AllocSysHapToken();
    std::vector<std::string> typeIds(1);
    typeIds[0] = "";
    auto status = UtdClient::GetInstance().UnregisterTypeDescriptors(typeIds);
    EXPECT_EQ(status, E_INVALID_TYPE_ID);

    typeIds[0] = std::string(SYS_HAP_BUNDLE_NAME) + ".nonexist";
    status = UtdClient::GetInstance().UnregisterTypeDescriptors(typeIds);
    EXPECT_EQ(status, E_INVALID_TYPE_ID);

    typeIds[0] = "general.file";
    status = UtdClient::GetInstance().UnregisterTypeDescriptors(typeIds);
    EXPECT_EQ(status, E_INVALID_TYPE_ID);
    LOG_INFO(UDMF_TEST, "UnregisterTypeDescriptors001 end.");
};

/**
* @tc.name: permissiontest001
* @tc.desc: Abnormal test case, permission error: not sys hap token
* @tc.type: FUNC
*/
HWTEST_F(UtdDynamicUpdateTest, permissiontest001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "permissiontest001 begin.");
    AllocHapToken1();
    std::vector<TypeDescriptorCfg> descriptors(1);
    descriptors[0] = {
        .typeId = std::string(SYS_HAP_BUNDLE_NAME) + ".ppp",
        .belongingToTypes = {"general.file"},
        .filenameExtensions = {".ppp"},
        .mimeTypes = {},
    };
    auto status = UtdClient::GetInstance().RegisterTypeDescriptors(descriptors);
    ASSERT_TRUE(status == E_NO_SYSTEM_PERMISSION);
    
    std::vector<std::string> typeIds = {std::string(SYS_HAP_BUNDLE_NAME) + ".ppp"};
    status = UtdClient::GetInstance().UnregisterTypeDescriptors(typeIds);
    ASSERT_TRUE(status == E_NO_SYSTEM_PERMISSION);
    LOG_INFO(UDMF_TEST, "permissiontest001 end.");
};

/**
* @tc.name: TypeDescriptor001
* @tc.desc: Normal test case
* @tc.type: FUNC
*/
HWTEST_F(UtdDynamicUpdateTest, TypeDescriptor001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "TypeDescriptor001 begin.");
    TypeDescriptor typeDescriptor;
    std::string typeId = std::string(HAP_BUNDLE_NAME) + ".ppp";
    typeDescriptor.SetTypeId(typeId);
    EXPECT_EQ(typeDescriptor.GetTypeId(), typeId);

    std::vector<std::string> belongingToTypes = {"general.file"};
    typeDescriptor.SetBelongingToTypes(belongingToTypes);
    EXPECT_EQ(typeDescriptor.GetBelongingToTypes(), belongingToTypes);

    std::vector<std::string> filenameExtensions = {".ppp"};
    typeDescriptor.SetFilenameExtensions(filenameExtensions);
    EXPECT_EQ(typeDescriptor.GetFilenameExtensions(), filenameExtensions);

    std::vector<std::string> mimeTypes = {"application/ppp"};
    typeDescriptor.SetMimeTypes(mimeTypes);
    EXPECT_EQ(typeDescriptor.GetMimeTypes(), mimeTypes);

    std::string description = "ppp file";
    typeDescriptor.SetDescription(description);
    EXPECT_EQ(typeDescriptor.GetDescription(), description);

    std::string icon = "icon.ppp";
    typeDescriptor.SetIconFile(icon);
    EXPECT_EQ(typeDescriptor.GetIconFile(), icon);

    std::string launchUri = "ppp://launch";
    typeDescriptor.SetReferenceURL(launchUri);
    EXPECT_EQ(typeDescriptor.GetReferenceURL(), launchUri);
    LOG_INFO(UDMF_TEST, "TypeDescriptor001 end.");
}

/**
 @tc.name: InstallDynamicUtds001
 @tc.desc: Abnormal test, error process
 @tc.type: FUNC
*/
HWTEST_F(UtdDynamicUpdateTest, InstallDynamicUtds001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "InstallDynamicUtds001 begin.");
    AllocHapToken1();
    std::string bundleName = HAP_BUNDLE_NAME;
    std::vector<TypeDescriptorCfg> customTypeCfgs(1);
    customTypeCfgs[0].typeId = std::string(HAP_BUNDLE_NAME) + ".ppp";
    customTypeCfgs[0].belongingToTypes = {"general.file"};
    auto status = UtdClient::GetInstance().InstallDynamicUtds(bundleName, customTypeCfgs);
    EXPECT_EQ(status, E_ERROR);

    std::vector<std::string> typeIds = {std::string(HAP_BUNDLE_NAME) + ".ppp"};
    status = UtdClient::GetInstance().UninstallDynamicUtds(bundleName, typeIds);
    EXPECT_EQ(status, E_ERROR);
    LOG_INFO(UDMF_TEST, "InstallDynamicUtds001 end.");
}

/**
 @tc.name: InstallDynamicUtds002
 @tc.desc: Normal test
 @tc.type: FUNC
*/
HWTEST_F(UtdDynamicUpdateTest, InstallDynamicUtds002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "InstallDynamicUtds002 begin.");
    AllocFoundationToken();
    std::string bundleName = HAP_BUNDLE_NAME;
    std::vector<TypeDescriptorCfg> customTypeCfgs(1);
    customTypeCfgs[0].typeId = bundleName + ".ppp";
    customTypeCfgs[0].belongingToTypes = {"general.file"};
    auto status = UtdClient::GetInstance().InstallDynamicUtds(bundleName, customTypeCfgs);
    EXPECT_EQ(status, E_OK);
    
    std::vector<std::string> typeIds = {bundleName + ".ppp"};
    status = UtdClient::GetInstance().UninstallDynamicUtds(bundleName, typeIds);
    EXPECT_EQ(status, E_OK);
    LOG_INFO(UDMF_TEST, "InstallDynamicUtds002 end.");
};

/**
 @tc.name: InstallDynamicUtds003
 @tc.desc: Abnormal test, customTypeCfgs is empty
 @tc.type: FUNC
*/
HWTEST_F(UtdDynamicUpdateTest, InstallDynamicUtds003, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "InstallDynamicUtds003 begin.");
    AllocFoundationToken();
    std::string bundleName = HAP_BUNDLE_NAME;
    std::vector<TypeDescriptorCfg> customTypeCfgs;
    auto status = UtdClient::GetInstance().InstallDynamicUtds(bundleName, customTypeCfgs);
    EXPECT_EQ(status, E_FORMAT_ERROR);
    
    std::vector<std::string> typeIds;
    status = UtdClient::GetInstance().UninstallDynamicUtds(bundleName, typeIds);
    EXPECT_EQ(status, E_INVALID_TYPE_ID);
    LOG_INFO(UDMF_TEST, "InstallDynamicUtds003 end.");
}

/**
 @tc.name: InstallDynamicUtds004
 @tc.desc: Abnormal test, error typeId
 @tc.type: FUNC
*/
HWTEST_F(UtdDynamicUpdateTest, InstallDynamicUtds004, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "InstallDynamicUtds004 begin.");
    AllocFoundationToken();
    std::string bundleName = HAP_BUNDLE_NAME;
    std::vector<TypeDescriptorCfg> customTypeCfgs(1);
    customTypeCfgs[0].belongingToTypes = {"general.file"};
    auto status = UtdClient::GetInstance().InstallDynamicUtds(bundleName, customTypeCfgs);
    EXPECT_EQ(status, E_FORMAT_ERROR);

    status = UtdClient::GetInstance().UninstallDynamicUtds(bundleName, {""});
    EXPECT_EQ(status, E_INVALID_TYPE_ID);
    LOG_INFO(UDMF_TEST, "InstallDynamicUtds004 end.");
}

/**
 @tc.name: InstallDynamicUtds005
 @tc.desc: Abnormal test, error belongingToTypes
 @tc.type: FUNC
*/
HWTEST_F(UtdDynamicUpdateTest, InstallDynamicUtds005, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "InstallDynamicUtds005 begin.");
    AllocFoundationToken();
    std::string bundleName = HAP_BUNDLE_NAME;
    std::vector<TypeDescriptorCfg> customTypeCfgs(1);
    customTypeCfgs[0].typeId = bundleName + ".ppp";
    auto status = UtdClient::GetInstance().InstallDynamicUtds(bundleName, customTypeCfgs);
    EXPECT_EQ(status, E_FORMAT_ERROR);

    customTypeCfgs[0].belongingToTypes = {""};
    status = UtdClient::GetInstance().InstallDynamicUtds(bundleName, customTypeCfgs);
    EXPECT_EQ(status, E_FORMAT_ERROR);
    LOG_INFO(UDMF_TEST, "InstallDynamicUtds005 end.");
}

/**
 @tc.name: InstallDynamicUtds006
 @tc.desc: Abnormal test, error typeId bundleName
 @tc.type: FUNC
*/
HWTEST_F(UtdDynamicUpdateTest, InstallDynamicUtds006, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "InstallDynamicUtds006 begin.");
    AllocFoundationToken();
    std::string bundleName = HAP_BUNDLE_NAME;
    std::vector<TypeDescriptorCfg> customTypeCfgs(1);
    customTypeCfgs[0].typeId = bundleName + ".ppp";
    customTypeCfgs[0].belongingToTypes = {"general.file"};
    auto status = UtdClient::GetInstance().InstallDynamicUtds(SYS_HAP_BUNDLE_NAME, customTypeCfgs);
    EXPECT_EQ(status, E_CONTENT_ERROR);

    status = UtdClient::GetInstance().UninstallDynamicUtds(SYS_HAP_BUNDLE_NAME, {customTypeCfgs[0].typeId});
    EXPECT_EQ(status, E_INVALID_TYPE_ID);
    LOG_INFO(UDMF_TEST, "InstallDynamicUtds006 end.");
}

/**
 @tc.name: InstallDynamicUtds007
 @tc.desc: Abnormal test, duplicate typeId
 @tc.type: FUNC
*/
HWTEST_F(UtdDynamicUpdateTest, InstallDynamicUtds007, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "InstallDynamicUtds007 begin.");
    AllocFoundationToken();
    std::string bundleName = HAP_BUNDLE_NAME;
    std::vector<TypeDescriptorCfg> customTypeCfgs(2);
    customTypeCfgs[0].typeId = bundleName + ".ppp";
    customTypeCfgs[0].belongingToTypes = {"general.file"};

    customTypeCfgs[1].typeId = bundleName + ".ppp";
    customTypeCfgs[1].belongingToTypes = {"general.file"};
    auto status = UtdClient::GetInstance().InstallDynamicUtds(bundleName, customTypeCfgs);
    EXPECT_EQ(status, E_CONTENT_ERROR);
    LOG_INFO(UDMF_TEST, "InstallDynamicUtds007 end.");
}

/**
 @tc.name: InstallDynamicUtds008
 @tc.desc: Abnormal test, error typeId regex
 @tc.type: FUNC
*/
HWTEST_F(UtdDynamicUpdateTest, InstallDynamicUtds008, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "InstallDynamicUtds008 begin.");
    AllocFoundationToken();
    std::string bundleName = HAP_BUNDLE_NAME;
    std::vector<TypeDescriptorCfg> customTypeCfgs(1);
    customTypeCfgs[0].typeId = bundleName + ".ppp?";
    customTypeCfgs[0].belongingToTypes = {"general.file"};
    auto status = UtdClient::GetInstance().InstallDynamicUtds(bundleName, customTypeCfgs);
    EXPECT_EQ(status, E_FORMAT_ERROR);
    LOG_INFO(UDMF_TEST, "InstallDynamicUtds008 end.");
}

/**
 @tc.name: InstallDynamicUtds009
 @tc.desc: Abnormal test, error typeId size
 @tc.type: FUNC
*/
HWTEST_F(UtdDynamicUpdateTest, InstallDynamicUtds009, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "InstallDynamicUtds009 begin.");
    AllocFoundationToken();
    std::string bundleName = HAP_BUNDLE_NAME;
    std::vector<TypeDescriptorCfg> customTypeCfgs(1);
    customTypeCfgs[0].typeId = bundleName + std::string(128, 'a');
    customTypeCfgs[0].belongingToTypes = {"general.file"};
    auto status = UtdClient::GetInstance().InstallDynamicUtds(bundleName, customTypeCfgs);
    EXPECT_EQ(status, E_FORMAT_ERROR);

    status = UtdClient::GetInstance().UninstallDynamicUtds(bundleName, {customTypeCfgs[0].typeId});
    EXPECT_EQ(status, E_INVALID_TYPE_ID);
    LOG_INFO(UDMF_TEST, "InstallDynamicUtds009 end.");
};

/**
 @tc.name: InstallDynamicUtds010
 @tc.desc: Abnormal test, error fileExtention size
 @tc.type: FUNC
*/
HWTEST_F(UtdDynamicUpdateTest, InstallDynamicUtds010, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "InstallDynamicUtds010 begin.");
    AllocFoundationToken();
    std::string bundleName = HAP_BUNDLE_NAME;
    std::vector<TypeDescriptorCfg> customTypeCfgs(1);
    customTypeCfgs[0].typeId = bundleName + ".ppp";
    customTypeCfgs[0].belongingToTypes = {"general.file"};
    customTypeCfgs[0].filenameExtensions = {"." + std::string(128, 'p')};
    auto status = UtdClient::GetInstance().InstallDynamicUtds(bundleName, customTypeCfgs);
    EXPECT_EQ(status, E_FORMAT_ERROR);
    LOG_INFO(UDMF_TEST, "InstallDynamicUtds010 end.");
};

/**
 @tc.name: InstallDynamicUtds011
 @tc.desc: Abnormal test, error mimetype size
 @tc.type: FUNC
*/
HWTEST_F(UtdDynamicUpdateTest, InstallDynamicUtds011, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "InstallDynamicUtds011 begin.");
    AllocFoundationToken();
    std::string bundleName = HAP_BUNDLE_NAME;
    std::vector<TypeDescriptorCfg> customTypeCfgs(1);
    customTypeCfgs[0].typeId = bundleName + ".ppp";
    customTypeCfgs[0].belongingToTypes = {"general.file"};
    customTypeCfgs[0].mimeTypes = std::vector<std::string>(51, "text/ppp");
    auto status = UtdClient::GetInstance().InstallDynamicUtds(bundleName, customTypeCfgs);
    EXPECT_EQ(status, E_FORMAT_ERROR);
    LOG_INFO(UDMF_TEST, "InstallDynamicUtds011 end.");
};

/**
 @tc.name: InstallDynamicUtds012
 @tc.desc: Abnormal test, error description size
 @tc.type: FUNC
*/
HWTEST_F(UtdDynamicUpdateTest, InstallDynamicUtds012, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "InstallDynamicUtds012 begin.");
    AllocFoundationToken();
    std::string bundleName = HAP_BUNDLE_NAME;
    std::vector<TypeDescriptorCfg> customTypeCfgs(1);
    customTypeCfgs[0].typeId = bundleName + ".ppp";
    customTypeCfgs[0].belongingToTypes = {"general.file"};
    customTypeCfgs[0].description = std::string(256, 'a');
    auto status = UtdClient::GetInstance().InstallDynamicUtds(bundleName, customTypeCfgs);
    EXPECT_EQ(status, E_FORMAT_ERROR);

    customTypeCfgs[0].typeId = bundleName + ".ppp";
    customTypeCfgs[0].belongingToTypes = {"general.file"};
    customTypeCfgs[0].iconFile = std::string(256, 'a');
    status = UtdClient::GetInstance().InstallDynamicUtds(bundleName, customTypeCfgs);
    EXPECT_EQ(status, E_FORMAT_ERROR);

    customTypeCfgs[0].typeId = bundleName + ".ppp";
    customTypeCfgs[0].belongingToTypes = {"general.file"};
    customTypeCfgs[0].referenceURL = std::string(256, 'a');
    status = UtdClient::GetInstance().InstallDynamicUtds(bundleName, customTypeCfgs);
    EXPECT_EQ(status, E_FORMAT_ERROR);
    LOG_INFO(UDMF_TEST, "InstallDynamicUtds012 end.");
};

/**
 @tc.name: UninstallDynamicUtds001
 @tc.desc: Abnormal test, typeId not exist
 @tc.type: FUNC
*/
HWTEST_F(UtdDynamicUpdateTest, UninstallDynamicUtds001, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "UninstallDynamicUtds001 begin.");
    AllocFoundationToken();

    std::vector<std::string> typeIds = {std::string(HAP_BUNDLE_NAME) + ".sss"};
    auto status = UtdClient::GetInstance().UninstallDynamicUtds(HAP_BUNDLE_NAME, typeIds);
    EXPECT_EQ(status, E_INVALID_TYPE_ID);
    LOG_INFO(UDMF_TEST, "UninstallDynamicUtds001 end.");
}

/**
 @tc.name: UninstallDynamicUtds002
 @tc.desc: Abnormal test, typeId bundle not match
 @tc.type: FUNC
*/
HWTEST_F(UtdDynamicUpdateTest, UninstallDynamicUtds002, TestSize.Level1)
{
    LOG_INFO(UDMF_TEST, "UninstallDynamicUtds002 begin.");
    AllocFoundationToken();
    std::string bundleName = HAP_BUNDLE_NAME;
    std::vector<TypeDescriptorCfg> customTypeCfgs(1);
    customTypeCfgs[0].typeId = bundleName + ".sss";
    customTypeCfgs[0].belongingToTypes = {"general.file"};
    auto status = UtdClient::GetInstance().InstallDynamicUtds(bundleName, customTypeCfgs);
    EXPECT_EQ(status, E_OK);
    
    status = UtdClient::GetInstance().UninstallDynamicUtds(SYS_HAP_BUNDLE_NAME, {customTypeCfgs[0].typeId});
    EXPECT_EQ(status, E_INVALID_TYPE_ID);

    status = UtdClient::GetInstance().UninstallDynamicUtds(bundleName, {customTypeCfgs[0].typeId});
    EXPECT_EQ(status, E_OK);
    LOG_INFO(UDMF_TEST, "UninstallDynamicUtds002 end.");
}
} // namespace OHOS::Test