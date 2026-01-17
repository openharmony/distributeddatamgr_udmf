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

#include "udmf_client_fuzzer.h"

#include <unistd.h>
#include <fuzzer/FuzzedDataProvider.h>

#include "accesstoken_kit.h"
#include "nativetoken_kit.h"
#include "token_setproc.h"

#include "udmf_client.h"
#include "text.h"
#include "plain_text.h"
#include "html.h"
#include "link.h"
#include "file.h"
#include "image.h"
#include "video.h"
#include "system_defined_record.h"
#include "system_defined_form.h"
#include "system_defined_appitem.h"
#include "system_defined_pixelmap.h"
#include "udmf_async_client.h"
#include "udmf_executor.h"
#include "unified_types.h"

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
        .processName = "msdp",
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

void SetDataTextFuzz(FuzzedDataProvider &provider)
{
    std::string skey = provider.ConsumeRandomLengthString();
    std::string svalue = provider.ConsumeRandomLengthString();
    UnifiedData unifiedData;
    CustomOption option = {.intention = Intention::UD_INTENTION_BUTT};
    auto text = std::make_shared<Text>();
    UDDetails details;
    details.insert({skey, svalue});
    text->SetDetails(details);
    unifiedData.AddRecord(text);
    std::string key;
    UdmfClient::GetInstance().SetData(option, unifiedData, key);

    SetNativeToken();

    QueryOption option2 = {.key = key};
    Privilege privilege;
    privilege.readPermission = provider.ConsumeRandomLengthString();
    privilege.writePermission = provider.ConsumeRandomLengthString();
    UdmfClient::GetInstance().AddPrivilege(option2, privilege);

    SetHapToken();

    UnifiedData data2;
    UdmfClient::GetInstance().GetData(option2, data2);
}

void SetDataPlainTextFuzz(FuzzedDataProvider &provider)
{
    std::string skey = provider.ConsumeRandomLengthString();
    std::string svalue = provider.ConsumeRandomLengthString();
    CustomOption option1 = {.intention = Intention::UD_INTENTION_DRAG};
    UnifiedData data1;
    UDDetails details1;
    auto plainText1 = std::make_shared<PlainText>();
    details1.insert({skey, svalue});
    plainText1->SetDetails(details1);
    plainText1->SetContent(svalue + provider.ConsumeRandomLengthString());
    plainText1->SetAbstract(svalue + provider.ConsumeRandomLengthString());
    plainText1->GetContent();
    plainText1->GetAbstract();
    data1.AddRecord(plainText1);
    std::string key;
    UdmfClient::GetInstance().SetData(option1, data1, key);

    SetNativeToken();

    QueryOption option2 = {.key = key};
    Privilege privilege;
    privilege.readPermission = provider.ConsumeRandomLengthString();
    privilege.writePermission = provider.ConsumeRandomLengthString();
    UdmfClient::GetInstance().AddPrivilege(option2, privilege);

    SetHapToken();

    UnifiedData data2;
    UdmfClient::GetInstance().GetData(option2, data2);
}

void SetDataHtmlFuzz(FuzzedDataProvider &provider)
{
    std::string skey = provider.ConsumeRandomLengthString();
    std::string svalue = provider.ConsumeRandomLengthString();
    CustomOption option1 = {.intention = Intention::UD_INTENTION_DRAG};
    UnifiedData data1;
    std::string key;
    auto html1 = std::make_shared<Html>();
    UDDetails details1;
    details1.insert({skey, svalue});
    html1->SetDetails(details1);
    html1->SetHtmlContent(svalue + provider.ConsumeRandomLengthString());
    html1->SetPlainContent(svalue + provider.ConsumeRandomLengthString());
    html1->GetHtmlContent();
    html1->GetPlainContent();
    data1.AddRecord(html1);
    UdmfClient::GetInstance().SetData(option1, data1, key);

    SetNativeToken();

    QueryOption option2 = {.key = key};
    Privilege privilege;
    privilege.readPermission = provider.ConsumeRandomLengthString();
    privilege.writePermission = provider.ConsumeRandomLengthString();
    UdmfClient::GetInstance().AddPrivilege(option2, privilege);

    SetHapToken();

    UnifiedData data2;
    UdmfClient::GetInstance().GetData(option2, data2);
}

void SetDataLinkFuzz(FuzzedDataProvider &provider)
{
    std::string skey = provider.ConsumeRandomLengthString();
    std::string svalue = provider.ConsumeRandomLengthString();
    CustomOption option1 = {.intention = Intention::UD_INTENTION_DRAG};
    UnifiedData data1;
    std::string key;
    auto link1 = std::make_shared<Link>();
    UDDetails details1;
    details1.insert({skey, svalue});
    link1->SetDetails(details1);
    link1->SetUrl(svalue + provider.ConsumeRandomLengthString());
    link1->SetDescription(svalue + provider.ConsumeRandomLengthString());
    link1->GetUrl();
    link1->GetDescription();
    data1.AddRecord(link1);
    UdmfClient::GetInstance().SetData(option1, data1, key);

    SetNativeToken();

    QueryOption option2 = {.key = key};
    Privilege privilege;
    privilege.readPermission = provider.ConsumeRandomLengthString();
    privilege.writePermission = provider.ConsumeRandomLengthString();
    UdmfClient::GetInstance().AddPrivilege(option2, privilege);

    SetHapToken();

    UnifiedData data2;
    UdmfClient::GetInstance().GetData(option2, data2);
}

void SetDataFileFuzz(FuzzedDataProvider &provider)
{
    std::string svalue = provider.ConsumeRandomLengthString();
    CustomOption option1 = {.intention = Intention::UD_INTENTION_DRAG};
    UnifiedData data1;
    std::string key;
    auto file1 = std::make_shared<File>();
    file1->SetUri(svalue + provider.ConsumeRandomLengthString());
    file1->SetRemoteUri(svalue + provider.ConsumeRandomLengthString());
    file1->GetUri();
    file1->GetRemoteUri();
    file1->GetSize();
    data1.AddRecord(file1);
    UdmfClient::GetInstance().SetData(option1, data1, key);

    SetNativeToken();

    QueryOption option2 = {.key = key};
    Privilege privilege;
    privilege.readPermission = provider.ConsumeRandomLengthString();
    privilege.writePermission = provider.ConsumeRandomLengthString();
    UdmfClient::GetInstance().AddPrivilege(option2, privilege);

    SetHapToken();

    UnifiedData data2;
    UdmfClient::GetInstance().GetData(option2, data2);
}

void SetDataImageFuzz(FuzzedDataProvider &provider)
{
    std::string svalue = provider.ConsumeRandomLengthString();
    CustomOption option1 = {.intention = Intention::UD_INTENTION_DRAG};
    UnifiedData data1;
    std::string key;
    auto image1 = std::make_shared<Image>();
    image1->SetUri(svalue + provider.ConsumeRandomLengthString());
    image1->SetRemoteUri(svalue + provider.ConsumeRandomLengthString());
    data1.AddRecord(image1);
    UdmfClient::GetInstance().SetData(option1, data1, key);

    SetNativeToken();

    QueryOption option2 = {.key = key};
    Privilege privilege;
    privilege.readPermission = provider.ConsumeRandomLengthString();
    privilege.writePermission = provider.ConsumeRandomLengthString();
    UdmfClient::GetInstance().AddPrivilege(option2, privilege);

    SetHapToken();

    UnifiedData data2;
    UdmfClient::GetInstance().GetData(option2, data2);
}

void SetDataVideoFuzz(FuzzedDataProvider &provider)
{
    std::string svalue = provider.ConsumeRandomLengthString();
    CustomOption option1 = {.intention = Intention::UD_INTENTION_DRAG};
    UnifiedData data1;
    std::string key;
    auto video1 = std::make_shared<Video>();
    video1->SetUri(svalue + provider.ConsumeRandomLengthString());
    video1->SetRemoteUri(svalue + provider.ConsumeRandomLengthString());
    data1.AddRecord(video1);
    UdmfClient::GetInstance().SetData(option1, data1, key);

    SetNativeToken();

    QueryOption option2 = {.key = key};
    Privilege privilege;
    privilege.readPermission = provider.ConsumeRandomLengthString();
    privilege.writePermission = provider.ConsumeRandomLengthString();
    UdmfClient::GetInstance().AddPrivilege(option2, privilege);

    SetHapToken();

    UnifiedData data2;
    UdmfClient::GetInstance().GetData(option2, data2);
}

void SetDataSystemDefinedRecordFuzz(FuzzedDataProvider &provider)
{
    std::string skey = provider.ConsumeRandomLengthString();
    std::string svalue = provider.ConsumeRandomLengthString();
    CustomOption option1 = {.intention = Intention::UD_INTENTION_DRAG};
    UnifiedData data1;
    std::string key;
    auto systemDefinedRecord1 = std::make_shared<SystemDefinedRecord>();
    UDDetails details1;
    details1.insert({skey, svalue});
    systemDefinedRecord1->SetDetails(details1);
    data1.AddRecord(systemDefinedRecord1);
    UdmfClient::GetInstance().SetData(option1, data1, key);

    SetNativeToken();

    QueryOption option2 = {.key = key};
    Privilege privilege;
    privilege.readPermission = provider.ConsumeRandomLengthString();
    privilege.writePermission = provider.ConsumeRandomLengthString();
    UdmfClient::GetInstance().AddPrivilege(option2, privilege);

    SetHapToken();

    UnifiedData data2;
    UdmfClient::GetInstance().GetData(option2, data2);
}

void SetDataSystemDefinedFormFuzz(FuzzedDataProvider &provider)
{
    std::string skey = provider.ConsumeRandomLengthString();
    std::string svalue = provider.ConsumeRandomLengthString();
    CustomOption option1 = {.intention = Intention::UD_INTENTION_DRAG};
    UnifiedData data1;
    std::string key;
    auto systemDefinedForm1 = std::make_shared<SystemDefinedForm>();
    UDDetails details1;
    details1.insert({skey, svalue});
    systemDefinedForm1->SetDetails(details1);
    auto formId = 123;
    systemDefinedForm1->SetFormId(formId);
    systemDefinedForm1->SetFormName(svalue + provider.ConsumeRandomLengthString());
    systemDefinedForm1->SetModule(svalue + provider.ConsumeRandomLengthString());
    systemDefinedForm1->SetAbilityName(svalue + provider.ConsumeRandomLengthString());
    systemDefinedForm1->SetBundleName(svalue + provider.ConsumeRandomLengthString());
    systemDefinedForm1->GetFormId();
    systemDefinedForm1->GetFormName();
    systemDefinedForm1->GetBundleName();
    systemDefinedForm1->GetAbilityName();
    systemDefinedForm1->GetModule();
    data1.AddRecord(systemDefinedForm1);
    UdmfClient::GetInstance().SetData(option1, data1, key);

    SetNativeToken();

    QueryOption option2 = {.key = key};
    Privilege privilege;
    privilege.readPermission = provider.ConsumeRandomLengthString();
    privilege.writePermission = provider.ConsumeRandomLengthString();
    UdmfClient::GetInstance().AddPrivilege(option2, privilege);

    SetHapToken();

    UnifiedData data2;
    UdmfClient::GetInstance().GetData(option2, data2);
}

void SetDataSystemDefinedAppItemFuzz(FuzzedDataProvider &provider)
{
    std::string skey = provider.ConsumeRandomLengthString();
    std::string svalue = provider.ConsumeRandomLengthString();
    CustomOption option1 = {.intention = Intention::UD_INTENTION_DRAG};
    UnifiedData data1;
    std::string key;
    auto systemDefinedAppItem1 = std::make_shared<SystemDefinedAppItem>();
    UDDetails details1;
    details1.insert({skey, svalue});
    systemDefinedAppItem1->SetDetails(details1);
    systemDefinedAppItem1->SetAppId(svalue + provider.ConsumeRandomLengthString());
    systemDefinedAppItem1->SetAppName(svalue + provider.ConsumeRandomLengthString());
    systemDefinedAppItem1->SetAppIconId(svalue + provider.ConsumeRandomLengthString());
    systemDefinedAppItem1->SetAppLabelId(svalue + provider.ConsumeRandomLengthString());
    systemDefinedAppItem1->SetBundleName(svalue + provider.ConsumeRandomLengthString());
    systemDefinedAppItem1->SetAbilityName(svalue + provider.ConsumeRandomLengthString());
    systemDefinedAppItem1->GetAppId();
    systemDefinedAppItem1->GetAppName();
    systemDefinedAppItem1->GetBundleName();
    systemDefinedAppItem1->GetAbilityName();
    systemDefinedAppItem1->GetAppIconId();
    systemDefinedAppItem1->GetAppLabelId();
    data1.AddRecord(systemDefinedAppItem1);
    UdmfClient::GetInstance().SetData(option1, data1, key);

    SetNativeToken();

    QueryOption option2 = {.key = key};
    Privilege privilege;
    privilege.readPermission = provider.ConsumeRandomLengthString();
    privilege.writePermission = provider.ConsumeRandomLengthString();
    UdmfClient::GetInstance().AddPrivilege(option2, privilege);

    SetHapToken();

    UnifiedData data2;
    UdmfClient::GetInstance().GetData(option2, data2);
}

void SetDataSystemDefinedPixelMapFuzz(FuzzedDataProvider &provider)
{
    std::string skey = provider.ConsumeRandomLengthString();
    std::string svalue = provider.ConsumeRandomLengthString();
    CustomOption option1 = {.intention = Intention::UD_INTENTION_DRAG};
    UnifiedData data1;
    std::string key;
    auto systemDefinedPixelMap1 = std::make_shared<SystemDefinedPixelMap>();
    UDDetails details1;
    details1.insert({skey, svalue});
    systemDefinedPixelMap1->SetDetails(details1);
    std::vector<uint8_t> rawData1 = {1, 2, 3, 4, 5};
    systemDefinedPixelMap1->SetRawData(rawData1);
    data1.AddRecord(systemDefinedPixelMap1);
    UdmfClient::GetInstance().SetData(option1, data1, key);

    SetNativeToken();

    QueryOption option2 = {.key = key};
    Privilege privilege;
    privilege.readPermission = provider.ConsumeRandomLengthString();
    privilege.writePermission = provider.ConsumeRandomLengthString();
    UdmfClient::GetInstance().AddPrivilege(option2, privilege);

    SetHapToken();

    UnifiedData data2;
    UdmfClient::GetInstance().GetData(option2, data2);
}

void GetSummaryFuzz(FuzzedDataProvider &provider)
{
    std::string skey = provider.ConsumeRandomLengthString();
    std::string svalue = provider.ConsumeRandomLengthString();
    CustomOption option1 = {.intention = Intention::UD_INTENTION_DRAG};
    UnifiedData UData;
    std::string key;

    UDDetails details;
    details.insert({skey, svalue});

    auto text = std::make_shared<Text>();
    text->SetDetails(details);
    UData.AddRecord(text);

    auto plainText = std::make_shared<PlainText>();
    plainText->SetDetails(details);
    plainText->SetContent(svalue + provider.ConsumeRandomLengthString());
    plainText->SetAbstract(svalue + provider.ConsumeRandomLengthString());
    UData.AddRecord(plainText);

    auto file = std::make_shared<File>();
    file->SetUri(svalue + provider.ConsumeRandomLengthString());
    file->SetRemoteUri(svalue + provider.ConsumeRandomLengthString());
    UData.AddRecord(file);

    auto image = std::make_shared<Image>();
    image->SetUri(svalue + provider.ConsumeRandomLengthString());
    image->SetRemoteUri(svalue + provider.ConsumeRandomLengthString());
    UData.AddRecord(image);

    auto systemDefinedRecord = std::make_shared<SystemDefinedRecord>();
    systemDefinedRecord->SetDetails(details);
    UData.AddRecord(systemDefinedRecord);

    auto systemDefinedForm = std::make_shared<SystemDefinedForm>();
    systemDefinedForm->SetDetails(details);
    auto formId = 123;
    systemDefinedForm->SetFormId(formId);
    systemDefinedForm->SetFormName(svalue + provider.ConsumeRandomLengthString());
    systemDefinedForm->SetModule(svalue + provider.ConsumeRandomLengthString());
    systemDefinedForm->SetAbilityName(svalue + provider.ConsumeRandomLengthString());
    systemDefinedForm->SetBundleName(svalue + provider.ConsumeRandomLengthString());
    UData.AddRecord(systemDefinedForm);

    UdmfClient::GetInstance().SetData(option1, UData, key);

    QueryOption option2 = {.key = key};
    Summary summary;
    UdmfClient::GetInstance().GetSummary(option2, summary);
    UnifiedData data2;
    UdmfClient::GetInstance().GetData(option2, data2);
}

void GetBatchDataByKeyFuzz(FuzzedDataProvider &provider)
{
    std::string skey = provider.ConsumeRandomLengthString();
    CustomOption option1 = { .intention = UD_INTENTION_DATA_HUB };
    UnifiedData data1;
    std::string key;
    auto plainText = std::make_shared<PlainText>();
    data1.AddRecord(plainText);
    UdmfClient::GetInstance().SetData(option1, data1, key);

    SetHapToken();
    QueryOption option2 = { .key = key };
    std::vector<UnifiedData> dataSet2;
    UdmfClient::GetInstance().GetBatchData(option2, dataSet2);

    SetHapToken();
    QueryOption option3 = { .key = skey };
    std::vector<UnifiedData> dataSet3;
    UdmfClient::GetInstance().GetBatchData(option3, dataSet3);
}

void GetBatchDataByIntentionFuzz(FuzzedDataProvider &provider)
{
    std::string skey = provider.ConsumeRandomLengthString();
    CustomOption option1 = { .intention = UD_INTENTION_DATA_HUB };
    UnifiedData data1;
    std::string key;
    auto plainText = std::make_shared<PlainText>();
    data1.AddRecord(plainText);
    UdmfClient::GetInstance().SetData(option1, data1, key);

    SetHapToken();
    Intention intention = UnifiedDataUtils::GetIntentionByString(skey);
    QueryOption option2 = { .intention = intention };
    std::vector<UnifiedData> dataSet;
    UdmfClient::GetInstance().GetBatchData(option2, dataSet);
}

void DeleteDataByKeyFuzz(FuzzedDataProvider &provider)
{
    std::string skey = provider.ConsumeRandomLengthString();
    CustomOption option1 = { .intention = UD_INTENTION_DATA_HUB };
    UnifiedData data1;
    std::string key;
    auto plainText = std::make_shared<PlainText>();
    data1.AddRecord(plainText);
    UdmfClient::GetInstance().SetData(option1, data1, key);

    SetHapToken();
    QueryOption option2 = { .key = key };
    std::vector<UnifiedData> dataSet2;
    UdmfClient::GetInstance().DeleteData(option2, dataSet2);

    SetHapToken();
    QueryOption option3 = { .key = skey };
    std::vector<UnifiedData> dataSet3;
    UdmfClient::GetInstance().DeleteData(option3, dataSet3);
}

void DeleteDataByIntentionFuzz(FuzzedDataProvider &provider)
{
    std::string skey = provider.ConsumeRandomLengthString();
    CustomOption option1 = { .intention = UD_INTENTION_DATA_HUB };
    UnifiedData data1;
    std::string key;
    auto plainText = std::make_shared<PlainText>();
    data1.AddRecord(plainText);
    UdmfClient::GetInstance().SetData(option1, data1, key);

    SetHapToken();
    Intention intention = UnifiedDataUtils::GetIntentionByString(skey);
    QueryOption option2 = { .intention = intention };
    std::vector<UnifiedData> dataSet;
    UdmfClient::GetInstance().DeleteData(option2, dataSet);
}

void UpdateDataFuzz(FuzzedDataProvider &provider)
{
    std::string skey = provider.ConsumeRandomLengthString();
    CustomOption option1 = { .intention = UD_INTENTION_DATA_HUB };
    UnifiedData data1;
    std::string key;
    auto plainText = std::make_shared<PlainText>();
    data1.AddRecord(plainText);
    UdmfClient::GetInstance().SetData(option1, data1, key);

    SetHapToken();
    UnifiedData data2;
    data2.AddRecord(plainText);
    QueryOption option2 = { .key = key };
    UdmfClient::GetInstance().UpdateData(option2, data2);

    SetHapToken();
    UnifiedData data3;
    data3.AddRecord(plainText);
    QueryOption option3 = { .key = skey };
    UdmfClient::GetInstance().UpdateData(option3, data3);
}

void StartAsyncDataRetrievalFuzz(FuzzedDataProvider &provider)
{
    size_t dataSize = provider.ConsumeIntegralInRange<size_t>(1, 50);
    std::vector<uint8_t> data = provider.ConsumeBytes<uint8_t>(dataSize);
    CustomOption option1 = { .intention = UD_INTENTION_DATA_HUB };
    UnifiedData data1;
    std::string key;
    auto plainText = std::make_shared<PlainText>();
    std::string content = provider.ConsumeRandomLengthString();
    plainText->SetContent(content);
    data1.AddRecord(plainText);
    UdmfClient::GetInstance().SetData(option1, data1, key);

    QueryOption query = {.key = key, .intention = UDMF::UD_INTENTION_DRAG};
    GetDataParams params = {.query = query};
    params.progressIndicator = ProgressIndicator::DEFAULT;
    params.progressListener = [](ProgressInfo progressInfo, std::shared_ptr<UnifiedData> data) {};
    UdmfAsyncClient::GetInstance().StartAsyncDataRetrieval(params);
}

void CancelAsyncDataRetrievalFuzz(FuzzedDataProvider &provider)
{
    size_t dataSize = provider.ConsumeIntegralInRange<size_t>(1, 50);
    std::vector<uint8_t> data = provider.ConsumeBytes<uint8_t>(dataSize);
    CustomOption option1 = { .intention = UD_INTENTION_DATA_HUB };
    UnifiedData data1;
    std::string key;
    auto plainText = std::make_shared<PlainText>();
    std::string content = provider.ConsumeRandomLengthString();
    plainText->SetContent(content);
    data1.AddRecord(plainText);
    UdmfClient::GetInstance().SetData(option1, data1, key);

    QueryOption query = {.key = key, .intention = UDMF::UD_INTENTION_DRAG};
    GetDataParams params = {.query = query};
    params.progressIndicator = ProgressIndicator::NONE;
    params.progressListener = [](ProgressInfo progressInfo, std::shared_ptr<UnifiedData> data) {
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    };
    UdmfAsyncClient::GetInstance().StartAsyncDataRetrieval(params);
    UdmfAsyncClient::GetInstance().Cancel(key);
}

void SyncFuzz(FuzzedDataProvider &provider)
{
    QueryOption query;
    query.key = provider.ConsumeRandomLengthString();
    query.intention = static_cast<Intention>(
        provider.ConsumeIntegralInRange<int32_t>(UD_INTENTION_BASE + 1, UD_INTENTION_BUTT - 1));
    query.tokenId = provider.ConsumeIntegral<uint32_t>();

    std::vector<std::string> devices;
    size_t devicesSize = provider.ConsumeIntegralInRange<size_t>(0, 10);
    for (size_t i = 0; i < devicesSize; ++i) {
        devices.push_back(provider.ConsumeRandomLengthString());
    }
    UdmfClient::GetInstance().Sync(query, devices);
}

void IsRemoteDataFuzz(FuzzedDataProvider &provider)
{
    QueryOption query;
    query.key = provider.ConsumeRandomLengthString();
    query.intention = static_cast<Intention>(
        provider.ConsumeIntegralInRange<int32_t>(UD_INTENTION_BASE + 1, UD_INTENTION_BUTT - 1));
    query.tokenId = provider.ConsumeIntegral<uint32_t>();
    bool res = false;
    UdmfClient::GetInstance().IsRemoteData(query, res);
}

void SetAppShareOptionFuzz(FuzzedDataProvider &provider)
{
    Intention intention = static_cast<Intention>(
        provider.ConsumeIntegralInRange<int32_t>(UD_INTENTION_BASE + 1, UD_INTENTION_BUTT - 1));
    std::string intentionStr = UD_INTENTION_MAP.at(intention);

    ShareOptions shareOption = static_cast<ShareOptions>(
        provider.ConsumeIntegralInRange<int32_t>(IN_APP, SHARE_OPTIONS_BUTT));
    UdmfClient::GetInstance().SetAppShareOption(intentionStr, shareOption);
}

void GetAppShareOptionFuzz(FuzzedDataProvider &provider)
{
    Intention intention = static_cast<Intention>(
        provider.ConsumeIntegralInRange<int32_t>(UD_INTENTION_BASE + 1, UD_INTENTION_BUTT - 1));
    std::string intentionStr = UD_INTENTION_MAP.at(intention);

    ShareOptions shareOption;
    UdmfClient::GetInstance().GetAppShareOption(intentionStr, shareOption);
}

void RemoveAppShareOptionFuzz(FuzzedDataProvider &provider)
{
    Intention intention = static_cast<Intention>(
        provider.ConsumeIntegralInRange<int32_t>(UD_INTENTION_BASE + 1, UD_INTENTION_BUTT - 1));
    std::string intentionStr = UD_INTENTION_MAP.at(intention);
    UdmfClient::GetInstance().RemoveAppShareOption(intentionStr);
}

void GetParentTypeFuzz(FuzzedDataProvider &provider)
{
    Summary oldSummary;
    Summary newSummary;
 
    size_t summarySize = provider.ConsumeIntegralInRange<size_t>(0, 10);
    for (size_t i = 0; i < summarySize; ++i) {
        std::string key = provider.ConsumeRandomLengthString();
        int64_t value = provider.ConsumeIntegral<int64_t>();
        oldSummary.summary[key] = value;
    }
    oldSummary.totalSize = provider.ConsumeIntegral<int64_t>();
    UdmfClient::GetInstance().GetParentType(oldSummary, newSummary);
}

void SetDelayInfoFuzz(FuzzedDataProvider &provider)
{
    DataLoadInfo dataLoadInfo1 {
        .sequenceKey = provider.ConsumeBytesAsString(32),
        .types{ provider.ConsumeRandomLengthString() },
        .recordCount = provider.ConsumeIntegral<uint32_t>(),
    };
    auto loadHandler = [] (const std::string &udKey, const DataLoadInfo &dataLoadInfo) {};
    DataLoadParams dataLoadParams = {
        .loadHandler = loadHandler,
        .dataLoadInfo = dataLoadInfo1,
    };
    std::string key = provider.ConsumeRandomLengthString();
    UdmfClient::GetInstance().SetDelayInfo(dataLoadParams, key);
}

void PushDelayDataFuzz(FuzzedDataProvider &provider)
{
    DataLoadInfo dataLoadInfo1{
        .sequenceKey = provider.ConsumeRandomLengthString(),
        .types{provider.ConsumeRandomLengthString()},
        .recordCount = provider.ConsumeIntegral<uint32_t>(),
    };
    auto loadHandler = [] (const std::string &udKey, const DataLoadInfo &dataLoadInfo) {};
    DataLoadParams dataLoadParams = {
        .loadHandler = loadHandler,
        .dataLoadInfo = dataLoadInfo1,
    };
    std::string key = provider.ConsumeRandomLengthString();
    UdmfClient::GetInstance().SetDelayInfo(dataLoadParams, key);

    auto text = std::make_shared<Text>();
    UDDetails details;
    std::string skey = provider.ConsumeRandomLengthString();
    std::string svalue = provider.ConsumeRandomLengthString();
    details.insert({skey, svalue});
    text->SetDetails(details);
    UnifiedData unifiedData;
    unifiedData.AddRecord(text);
    UdmfClient::GetInstance().PushDelayData(key, unifiedData);
}

void GetBundleNameByUdKeyFuzz(FuzzedDataProvider &provider)
{
    std::string key = provider.ConsumeRandomLengthString();
    UdmfClient::GetInstance().GetBundleNameByUdKey(key);
}

void SetDataProcessDragInAppFuzz(FuzzedDataProvider &provider)
{
    std::string svalue = provider.ConsumeRandomLengthString();
    CustomOption option1 = {.intention = Intention::UD_INTENTION_DRAG};
    UnifiedData data1;
    std::string key;
    auto video1 = std::make_shared<Video>();
    video1->SetUri(svalue + provider.ConsumeRandomLengthString());
    video1->SetRemoteUri(svalue + provider.ConsumeRandomLengthString());
    data1.AddRecord(video1);
    auto intentionDrag = UD_INTENTION_MAP.at(option1.intention);
    UdmfClient::GetInstance().SetAppShareOption(intentionDrag, ShareOptions::IN_APP);
    UdmfClient::GetInstance().SetData(option1, data1, key);

    SetNativeToken();

    QueryOption option2 = {.key = key};
    Privilege privilege;
    privilege.readPermission = provider.ConsumeRandomLengthString();
    privilege.writePermission = provider.ConsumeRandomLengthString();
    UdmfClient::GetInstance().AddPrivilege(option2, privilege);

    SetHapToken();

    UnifiedData data2;
    UdmfClient::GetInstance().GetData(option2, data2);
}

void IsAppropriateTypeFuzz(FuzzedDataProvider &provider)
{
    std::string allowType = provider.ConsumeRandomLengthString();
    std::vector<std::string> allowTypes{allowType};
    Summary summary;
    summary.version = provider.ConsumeIntegral<uint32_t>();
    UdmfClient::GetInstance().IsAppropriateType(summary, allowTypes);
}
}

/* Fuzzer entry point */
extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
    /* Run your code on data */
    FuzzedDataProvider provider(data, size);
    OHOS::SetUpTestCase();
    OHOS::SetDataFileFuzz(provider);
    OHOS::SetDataHtmlFuzz(provider);
    OHOS::SetDataImageFuzz(provider);
    OHOS::SetDataLinkFuzz(provider);
    OHOS::SetDataPlainTextFuzz(provider);
    OHOS::SetDataSystemDefinedAppItemFuzz(provider);
    OHOS::SetDataSystemDefinedFormFuzz(provider);
    OHOS::SetDataSystemDefinedPixelMapFuzz(provider);
    OHOS::SetDataSystemDefinedRecordFuzz(provider);
    OHOS::SetDataTextFuzz(provider);
    OHOS::SetDataVideoFuzz(provider);
    OHOS::GetSummaryFuzz(provider);
    OHOS::GetBatchDataByKeyFuzz(provider);
    OHOS::GetBatchDataByIntentionFuzz(provider);
    OHOS::DeleteDataByKeyFuzz(provider);
    OHOS::DeleteDataByIntentionFuzz(provider);
    OHOS::UpdateDataFuzz(provider);
    OHOS::StartAsyncDataRetrievalFuzz(provider);
    OHOS::CancelAsyncDataRetrievalFuzz(provider);
    OHOS::SyncFuzz(provider);
    OHOS::IsRemoteDataFuzz(provider);
    OHOS::SetAppShareOptionFuzz(provider);
    OHOS::GetAppShareOptionFuzz(provider);
    OHOS::RemoveAppShareOptionFuzz(provider);
    OHOS::GetParentTypeFuzz(provider);
    OHOS::SetDelayInfoFuzz(provider);
    OHOS::PushDelayDataFuzz(provider);
    OHOS::GetBundleNameByUdKeyFuzz(provider);
    OHOS::SetDataProcessDragInAppFuzz(provider);
    OHOS::IsAppropriateTypeFuzz(provider);
    OHOS::TearDown();
    return 0;
}