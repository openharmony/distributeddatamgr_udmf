/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include <unistd.h>
#include <thread>

#include "accesstoken_kit.h"
#include "nativetoken_kit.h"
#include "token_setproc.h"

#include "link.h"

#include "udmf_fuzzer.h"
#include "udmf.h"
#include "udmf_capi_common.h"
#include "udmf_meta.h"

#include <fuzzer/FuzzedDataProvider.h>

using namespace OHOS;
using namespace OHOS::Security::AccessToken;
using namespace OHOS::UDMF;

namespace OHOS {
static constexpr int END_INTERVAL = 3;

void AllocHapToken()
{
    HapInfoParams info = {
        .userID = 100,
        .bundleName = "ohos.test.demo",
        .instIndex = 0,
        .appIDDesc = "ohos.test.demo"
    };

    HapPolicyParams policy = {
        .apl = APL_NORMAL,
        .domain = "test.domain",
        .permList = {
            {
                .permissionName = "ohos.permission.test",
                .bundleName = "ohos.test.demo",
                .grantMode = 1,
                .availableLevel = APL_NORMAL,
                .label = "label",
                .labelId = 1,
                .description = "test",
                .descriptionId = 1
            }
        },
        .permStateList = {
            {
                .permissionName = "ohos.permission.test",
                .isGeneral = true,
                .resDeviceID = {"local"},
                .grantStatus = {PermissionState::PERMISSION_GRANTED},
                .grantFlags = {1}
            }
        }
    };
    auto tokenID = AccessTokenKit::AllocHapToken(info, policy);
    SetSelfTokenID(tokenID.tokenIDEx);
}

void SetUpTestCase()
{
    AllocHapToken();
}

void TearDown()
{
    std::this_thread::sleep_for(std::chrono::seconds(END_INTERVAL));
}

void SetNativeToken()
{
    NativeTokenInfoParams infoInstance = {
        .dcapsNum = 0,
        .permsNum = 0,
        .aclsNum = 0,
        .dcaps = nullptr,
        .perms = nullptr,
        .acls = nullptr,
        .processName = "msdp_sa",
        .aplStr = "system_core",
    };
    auto tokenId = GetAccessTokenId(&infoInstance);
    SetSelfTokenID(tokenId);
    AccessTokenKit::ReloadNativeTokenInfo();
}

void SetHapToken()
{
    auto tokenId = AccessTokenKit::GetHapTokenID(100, "ohos.test.demo", 0);
    SetSelfTokenID(tokenId);
}

void SetUnifiedDataFuzz(FuzzedDataProvider &provider)
{
    std::string skey = provider.ConsumeRandomLengthString();
    OH_UdmfData *udmfUnifiedData = OH_UdmfData_Create();
    OH_UdmfRecord *record = OH_UdmfRecord_Create();
    OH_UdsFileUri *fileUri = OH_UdsFileUri_Create();
    OH_UdsFileUri_SetFileUri(fileUri, skey.c_str());
    OH_UdsFileUri_SetFileType(fileUri, UDMF_META_IMAGE);
    OH_UdmfRecord_AddFileUri(record, fileUri);
    OH_UdmfData_AddRecord(udmfUnifiedData, record);
    OH_UdmfOptions* options = OH_UdmfOptions_Create();
    options->intention = UDMF_INTENTION_DATA_HUB;
    char key[UDMF_KEY_BUFFER_LEN];
    OH_Udmf_SetUnifiedDataByOptions(options, udmfUnifiedData, key, UDMF_KEY_BUFFER_LEN);
    OH_UdmfOptions_Destroy(options);
    OH_UdsFileUri_Destroy(fileUri);
    OH_UdmfRecord_Destroy(record);
    OH_UdmfData_Destroy(udmfUnifiedData);
}

void GetUnifiedDataFuzz(FuzzedDataProvider &provider)
{
    std::string skey = provider.ConsumeRandomLengthString();
    OH_UdmfData *udmfUnifiedData = OH_UdmfData_Create();
    OH_UdmfRecord *record = OH_UdmfRecord_Create();
    OH_UdsFileUri *fileUri = OH_UdsFileUri_Create();
    OH_UdsFileUri_SetFileUri(fileUri, skey.c_str());
    OH_UdsFileUri_SetFileType(fileUri, UDMF_META_IMAGE);
    OH_UdmfRecord_AddFileUri(record, fileUri);
    OH_UdmfData_AddRecord(udmfUnifiedData, record);
    OH_UdmfOptions* options = OH_UdmfOptions_Create();
    options->intention = UDMF_INTENTION_DATA_HUB;
    char key[UDMF_KEY_BUFFER_LEN];
    OH_Udmf_SetUnifiedDataByOptions(options, udmfUnifiedData, key, UDMF_KEY_BUFFER_LEN);

    unsigned int dataSize = 0;
    OH_UdmfData* dataArray = nullptr;
    OH_Udmf_GetUnifiedDataByOptions(options, &dataArray, &dataSize);
    OH_UdmfOptions_Destroy(options);
    OH_UdsFileUri_Destroy(fileUri);
    OH_UdmfRecord_Destroy(record);
    OH_UdmfData_Destroy(udmfUnifiedData);
    OH_Udmf_DestroyDataArray(&dataArray, dataSize);
}

void UpdataUnifiedDataFuzz(FuzzedDataProvider &provider)
{
    std::string skey = provider.ConsumeRandomLengthString();
    OH_UdmfData *udmfUnifiedData = OH_UdmfData_Create();
    OH_UdmfRecord *record = OH_UdmfRecord_Create();
    OH_UdsFileUri *fileUri = OH_UdsFileUri_Create();
    OH_UdsFileUri_SetFileUri(fileUri, skey.c_str());
    OH_UdsFileUri_SetFileType(fileUri, UDMF_META_IMAGE);
    OH_UdmfRecord_AddFileUri(record, fileUri);
    OH_UdmfData_AddRecord(udmfUnifiedData, record);
    OH_UdmfOptions* options = OH_UdmfOptions_Create();
    options->intention = UDMF_INTENTION_DATA_HUB;
    char key[UDMF_KEY_BUFFER_LEN];
    OH_Udmf_SetUnifiedDataByOptions(options, udmfUnifiedData, key, UDMF_KEY_BUFFER_LEN);

    std::string svalue = provider.ConsumeRandomLengthString();
    OH_UdmfData *udmfUnifiedData2 = OH_UdmfData_Create();
    OH_UdmfRecord *record2 = OH_UdmfRecord_Create();
    OH_UdsFileUri *fileUri2 = OH_UdsFileUri_Create();
    OH_UdsFileUri_SetFileUri(fileUri2, svalue.c_str());
    OH_UdsFileUri_SetFileType(fileUri2, UDMF_META_IMAGE);
    OH_UdmfRecord_AddFileUri(record2, fileUri2);
    OH_UdmfData_AddRecord(udmfUnifiedData2, record2);
    OH_UdmfOptions* options2 = OH_UdmfOptions_Create();
    options2->intention = UDMF_INTENTION_DATA_HUB;
    options2->key = key;
    OH_Udmf_UpdateUnifiedData(options2, udmfUnifiedData2);
    OH_UdmfOptions_Destroy(options);
    OH_UdmfOptions_Destroy(options2);
    OH_UdsFileUri_Destroy(fileUri);
    OH_UdsFileUri_Destroy(fileUri2);
    OH_UdmfRecord_Destroy(record);
    OH_UdmfRecord_Destroy(record2);
    OH_UdmfData_Destroy(udmfUnifiedData);
    OH_UdmfData_Destroy(udmfUnifiedData2);
}

void DeleteUnifiedDataFuzz(FuzzedDataProvider &provider)
{
    std::string skey = provider.ConsumeRandomLengthString();
    OH_UdmfData *udmfUnifiedData = OH_UdmfData_Create();
    OH_UdmfRecord *record = OH_UdmfRecord_Create();
    OH_UdsFileUri *fileUri = OH_UdsFileUri_Create();
    OH_UdsFileUri_SetFileUri(fileUri, skey.c_str());
    OH_UdsFileUri_SetFileType(fileUri, UDMF_META_IMAGE);
    OH_UdmfRecord_AddFileUri(record, fileUri);
    OH_UdmfData_AddRecord(udmfUnifiedData, record);
    OH_UdmfOptions* options = OH_UdmfOptions_Create();
    options->intention = UDMF_INTENTION_DATA_HUB;
    char key[UDMF_KEY_BUFFER_LEN];
    OH_Udmf_SetUnifiedDataByOptions(options, udmfUnifiedData, key, UDMF_KEY_BUFFER_LEN);

    unsigned int dataSize = 0;
    OH_UdmfData* dataArray = nullptr;
    OH_Udmf_DeleteUnifiedData(options, &dataArray, &dataSize);
    OH_UdmfOptions_Destroy(options);
    OH_UdsFileUri_Destroy(fileUri);
    OH_UdmfRecord_Destroy(record);
    OH_UdmfData_Destroy(udmfUnifiedData);
    OH_Udmf_DestroyDataArray(&dataArray, dataSize);
}

void SetAndGetVisibilityFuzz(FuzzedDataProvider &provider)
{
    OH_UdmfOptions* options = OH_UdmfOptions_Create();
    Udmf_Visibility testVisibility = Udmf_Visibility::UDMF_ALL;
    OH_UdmfOptions_SetVisibility(options, testVisibility);
    OH_UdmfOptions_GetVisibility(options);
    OH_UdmfOptions_Destroy(options);
    OH_UdmfOptions* options1 = OH_UdmfOptions_Create();
    testVisibility = Udmf_Visibility::UDMF_OWN_PROCESS;
    OH_UdmfOptions_SetVisibility(options1, testVisibility);
    OH_UdmfOptions_GetVisibility(options1);
    OH_UdmfOptions_Destroy(options1);
}
}

/* Fuzzer entry point */
extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
    /* Run your code on data */
    FuzzedDataProvider provider(data, size);
    OHOS::SetUpTestCase();
    OHOS::SetUnifiedDataFuzz(provider);
    OHOS::GetUnifiedDataFuzz(provider);
    OHOS::UpdataUnifiedDataFuzz(provider);
    OHOS::DeleteUnifiedDataFuzz(provider);
    OHOS::SetAndGetVisibilityFuzz(provider);
    OHOS::TearDown();
    return 0;
}