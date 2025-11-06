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

#include "tlv_util_fuzzer.h"

#include <unistd.h>
#include <fuzzer/FuzzedDataProvider.h>

#include "accesstoken_kit.h"
#include "nativetoken_kit.h"
#include "token_setproc.h"

#include "tlv_tag.h"
#include "tlv_util.h"
#include "udmf_async_client.h"
#include "udmf_executor.h"
#include "unified_data.h"
#include "unified_key.h"
#include "unified_meta.h"
#include "unified_record.h"
#include "unified_types.h"
#include "unified_data_helper.h"
#include "int_wrapper.h"
#include "pixelmap_native_impl.h"

using namespace OHOS;
using namespace OHOS::Security::AccessToken;
using namespace OHOS::UDMF;

namespace OHOS {
static constexpr int END_INTERVAL = 3;
static constexpr int ID_LEN = 7;
void SetUpTestCase()
{
}

void TearDown()
{
    std::this_thread::sleep_for(std::chrono::seconds(END_INTERVAL));
}

void ReadingNullptrFuzz(FuzzedDataProvider &provider)
{
    std::nullptr_t input = std::nullptr_t();
    std::nullptr_t output = std::nullptr_t();

    std::uint8_t data1 = provider.ConsumeIntegral<uint8_t>();
    std::uint8_t data2 = provider.ConsumeIntegral<uint8_t>();
    std::vector<std::uint8_t> buffer = { data1, data2 };
    TLVObject data(buffer);
    TLVHead head;
    TAG tag = TAG::TAG_VARIANT_ITEM;
    TLVUtil::Writing(input, data, tag);
    TLVUtil::CountBufferSize(input, data);
    TLVUtil::ReadTlv(output, data, tag);
    TLVUtil::Reading(output, data, head);
}

void ReadingMonostateFuzz(FuzzedDataProvider &provider)
{
    std::monostate input;
    std::monostate output;

    std::uint8_t data1 = provider.ConsumeIntegral<uint8_t>();
    std::uint8_t data2 = provider.ConsumeIntegral<uint8_t>();
    std::vector<std::uint8_t> buffer = { data1, data2 };
    TLVObject data(buffer);
    TLVHead head;
    TAG tag = TAG::TAG_VARIANT_ITEM;
    TLVUtil::Writing(input, data, tag);
    TLVUtil::CountBufferSize(input, data);
    TLVUtil::ReadTlv(output, data, tag);
    TLVUtil::Reading(output, data, head);
}

void ReadingStringFuzz(FuzzedDataProvider &provider)
{
    std::string input = provider.ConsumeRandomLengthString();
    std::string output;

    std::uint8_t data1 = provider.ConsumeIntegral<uint8_t>();
    std::uint8_t data2 = provider.ConsumeIntegral<uint8_t>();
    std::vector<std::uint8_t> buffer = { data1, data2 };
    TLVObject data(buffer);
    TLVHead head;
    TAG tag = TAG::TAG_VARIANT_ITEM;
    TLVUtil::Writing(input, data, tag);
    TLVUtil::CountBufferSize(input, data);
    TLVUtil::ReadTlv(output, data, tag);
    TLVUtil::Reading(output, data, head);
}

void ReadingVectorFuzz(FuzzedDataProvider &provider)
{
    std::uint8_t data1 = provider.ConsumeIntegral<uint8_t>();
    std::uint8_t data2 = provider.ConsumeIntegral<uint8_t>();
    std::vector<std::uint8_t> buffer = { data1, data2 };
    std::vector<std::uint8_t> input = { data1, data2 };
    std::vector<std::uint8_t> output;

    TLVObject data(buffer);
    TLVHead head;
    TAG tag = TAG::TAG_VARIANT_ITEM;
    TLVUtil::Writing(input, data, tag);
    TLVUtil::CountBufferSize(input, data);
    TLVUtil::ReadTlv(output, data, tag);
    TLVUtil::Reading(output, data, head);
}

void ReadingUDtypeFuzz(FuzzedDataProvider &provider)
{
    std::uint8_t data1 = provider.ConsumeIntegral<uint8_t>();
    std::uint8_t data2 = provider.ConsumeIntegral<uint8_t>();
    std::vector<std::uint8_t> buffer = { data1, data2 };
    UDType input = static_cast<UDType>(provider.ConsumeIntegralInRange<int32_t>(
        UDType::ENTITY + 1, UDType::UD_BUTT - 1));
    UDType output;

    TLVObject data(buffer);
    TLVHead head;
    TAG tag = TAG::TAG_VARIANT_ITEM;
    TLVUtil::Writing(input, data, tag);
    TLVUtil::CountBufferSize(input, data);
    TLVUtil::ReadTlv(output, data, tag);
    TLVUtil::Reading(output, data, head);
}

void ReadingDataStatusFuzz(FuzzedDataProvider &provider)
{
    std::uint8_t data1 = provider.ConsumeIntegral<uint8_t>();
    std::uint8_t data2 = provider.ConsumeIntegral<uint8_t>();
    std::vector<std::uint8_t> buffer = { data1, data2 };
    DataStatus input = static_cast<DataStatus>(provider.ConsumeIntegralInRange<int32_t>(
        DataStatus::WORKING, DataStatus::FADE));
    DataStatus output;

    TLVObject data(buffer);
    TLVHead head;
    TAG tag = TAG::TAG_VARIANT_ITEM;
    TLVUtil::Writing(input, data, tag);
    TLVUtil::CountBufferSize(input, data);
    TLVUtil::ReadTlv(output, data, tag);
    TLVUtil::Reading(output, data, head);
}

void ReadingObjectFuzz(FuzzedDataProvider &provider)
{
    std::uint8_t data1 = provider.ConsumeIntegral<uint8_t>();
    std::uint8_t data2 = provider.ConsumeIntegral<uint8_t>();
    std::vector<std::uint8_t> buffer = { data1, data2 };
    Object input;
    std::map<std::string, ValueType> map;
    map["keyString"] = provider.ConsumeRandomLengthString();
    double key = provider.ConsumeFloatingPoint<double>();
    map["keyName"] = key;
    input.value_ = map;
    Object output;

    TLVObject data(buffer);
    TLVHead head;
    TAG tag = static_cast<TAG>(provider.ConsumeIntegralInRange<uint16_t>(
        static_cast<uint16_t>(TAG::TAG_BUTT) + 1, static_cast<uint16_t>(TAG::TAG_SUMMARY_VERSION) - 1));
    TLVUtil::Writing(input, data, tag);
    TLVUtil::CountBufferSize(input, data);
    TLVUtil::ReadTlv(output, data, tag);
    TLVUtil::Reading(output, data, head);
}

void ReadingUnifiedKeyFuzz(FuzzedDataProvider &provider)
{
    std::uint8_t data1 = provider.ConsumeIntegral<uint8_t>();
    std::uint8_t data2 = provider.ConsumeIntegral<uint8_t>();
    std::vector<std::uint8_t> buffer = { data1, data2 };
    UnifiedKey input;
    input.key = provider.ConsumeRandomLengthString();
    input.intention = provider.ConsumeRandomLengthString();
    input.bundleName = provider.ConsumeRandomLengthString();
    UnifiedKey output;

    TLVObject data(buffer);
    TLVHead head;
    TAG tag = static_cast<TAG>(provider.ConsumeIntegralInRange<uint16_t>(
        static_cast<uint16_t>(TAG::TAG_BUTT) + 1, static_cast<uint16_t>(TAG::TAG_SUMMARY_VERSION) - 1));
    TLVUtil::Writing(input, data, tag);
    TLVUtil::CountBufferSize(input, data);
    TLVUtil::ReadTlv(output, data, tag);
    TLVUtil::Reading(output, data, head);
}

void ReadingUnifiedDataFuzz(FuzzedDataProvider &provider)
{
    std::uint8_t data1 = provider.ConsumeIntegral<uint8_t>();
    std::uint8_t data2 = provider.ConsumeIntegral<uint8_t>();
    std::vector<std::uint8_t> buffer = { data1, data2 };
    UnifiedData input;
    std::map<std::string, ValueType> value;
    value["fileType"] = provider.ConsumeRandomLengthString();
    value["fileUri"] = provider.ConsumeRandomLengthString();
    std::shared_ptr<Object> obj = std::make_shared<Object>();
    obj->value_ = value;
    std::shared_ptr<UnifiedRecord> fileUri = std::make_shared<UnifiedRecord>(UDType::FILE_URI, obj);
    std::vector<std::shared_ptr<UnifiedRecord>> records = { fileUri };

    input.SetRecords(records);
    UnifiedData output;

    TLVObject data(buffer);
    TLVHead head;
    TAG tag = static_cast<TAG>(provider.ConsumeIntegralInRange<uint16_t>(
        static_cast<uint16_t>(TAG::TAG_BUTT) + 1, static_cast<uint16_t>(TAG::TAG_SUMMARY_VERSION) - 1));
    TLVUtil::Writing(input, data, tag);
    TLVUtil::CountBufferSize(input, data);
    TLVUtil::ReadTlv(output, data, tag);
    TLVUtil::Reading(output, data, head);
}

void ReadingUnifiedRecordFuzz(FuzzedDataProvider &provider)
{
    std::uint8_t data1 = provider.ConsumeIntegral<uint8_t>();
    std::uint8_t data2 = provider.ConsumeIntegral<uint8_t>();
    std::vector<std::uint8_t> buffer = { data1, data2 };
    UnifiedRecord input;
    input.value_ = provider.ConsumeRandomLengthString();
    input.dataType_ = static_cast<UDType>(provider.ConsumeIntegralInRange<int32_t>(
        UDType::ENTITY + 1, UDType::UD_BUTT - 1));
    UnifiedRecord output;

    TLVObject data(buffer);
    TLVHead head;
    TAG tag = static_cast<TAG>(provider.ConsumeIntegralInRange<uint16_t>(
        static_cast<uint16_t>(TAG::TAG_BUTT) + 1, static_cast<uint16_t>(TAG::TAG_SUMMARY_VERSION) - 1));
    TLVUtil::Writing(input, data, tag);
    TLVUtil::CountBufferSize(input, data);
    TLVUtil::ReadTlv(output, data, tag);
    TLVUtil::Reading(output, data, head);
}

void ReadingRuntimeFuzz(FuzzedDataProvider &provider)
{
    std::uint8_t data1 = provider.ConsumeIntegral<uint8_t>();
    std::uint8_t data2 = provider.ConsumeIntegral<uint8_t>();
    std::vector<std::uint8_t> buffer = { data1, data2 };
    UnifiedKey key;
    key.key = provider.ConsumeRandomLengthString();
    Privilege privilege;
    privilege.readPermission = provider.ConsumeRandomLengthString();
    privilege.tokenId = provider.ConsumeIntegral<uint32_t>();
    Runtime input;
    input.dataStatus = static_cast<DataStatus>(provider.ConsumeIntegralInRange<int32_t>(
        static_cast<int32_t>(DataStatus::WORKING) + 1, static_cast<int32_t>(DataStatus::FADE) - 1));
    input.key = key;
    input.privileges.push_back(privilege);
    input.createTime = provider.ConsumeIntegral<time_t>();
    input.dataVersion = provider.ConsumeIntegral<int32_t>();
    input.createPackage = provider.ConsumeRandomLengthString();
    input.isPrivate = provider.ConsumeBool();
    input.appId = provider.ConsumeRandomLengthString();
    Runtime output;

    TLVObject data(buffer);
    TLVHead head;
    TAG tag = static_cast<TAG>(provider.ConsumeIntegralInRange<uint16_t>(
        static_cast<uint16_t>(TAG::TAG_BUTT) + 1, static_cast<uint16_t>(TAG::TAG_SUMMARY_VERSION) - 1));
    TLVUtil::Writing(input, data, tag);
    TLVUtil::CountBufferSize(input, data);
    TLVUtil::ReadTlv(output, data, tag);
    TLVUtil::Reading(output, data, head);
}

void ReadingPrivilegeFuzz(FuzzedDataProvider &provider)
{
    std::uint8_t data1 = provider.ConsumeIntegral<uint8_t>();
    std::uint8_t data2 = provider.ConsumeIntegral<uint8_t>();
    std::vector<std::uint8_t> buffer = { data1, data2 };
    Privilege input;
    input.readPermission = provider.ConsumeRandomLengthString();
    input.tokenId = provider.ConsumeIntegral<uint32_t>();
    Privilege output;

    TLVObject data(buffer);
    TLVHead head;
    TAG tag = static_cast<TAG>(provider.ConsumeIntegralInRange<uint16_t>(
        static_cast<uint16_t>(TAG::TAG_BUTT) + 1, static_cast<uint16_t>(TAG::TAG_SUMMARY_VERSION) - 1));
    TLVUtil::Writing(input, data, tag);
    TLVUtil::CountBufferSize(input, data);
    TLVUtil::ReadTlv(output, data, tag);
    TLVUtil::Reading(output, data, head);
}

void ReadingUriInfoFuzz(FuzzedDataProvider &provider)
{
    std::uint8_t data1 = provider.ConsumeIntegral<uint8_t>();
    std::uint8_t data2 = provider.ConsumeIntegral<uint8_t>();
    std::vector<std::uint8_t> buffer = { data1, data2 };
    UriInfo input;
    input.oriUri = provider.ConsumeRandomLengthString();
    input.authUri = provider.ConsumeRandomLengthString();
    input.dfsUri = provider.ConsumeRandomLengthString();
    input.permission = provider.ConsumeIntegralInRange<int32_t>(static_cast<int32_t>(PermissionPolicy::UNKNOW) + 1,
        static_cast<int32_t>(PermissionPolicy::PERMISSION_POLICY_BUTT) - 1);
    input.position = provider.ConsumeIntegral<uint32_t>();
    UriInfo output;

    TLVObject data(buffer);
    TLVHead head;
    TAG tag = static_cast<TAG>(provider.ConsumeIntegralInRange<uint16_t>(
        static_cast<uint16_t>(TAG::TAG_BUTT) + 1, static_cast<uint16_t>(TAG::TAG_SUMMARY_VERSION) - 1));
    TLVUtil::Writing(input, data, tag);
    TLVUtil::CountBufferSize(input, data);
    TLVUtil::ReadTlv(output, data, tag);
    TLVUtil::Reading(output, data, head);
}

void ReadingShareOptionsFuzz(FuzzedDataProvider &provider)
{
    std::uint8_t data1 = provider.ConsumeIntegral<uint8_t>();
    std::uint8_t data2 = provider.ConsumeIntegral<uint8_t>();
    std::vector<std::uint8_t> buffer = { data1, data2 };
    ShareOptions output;
    TLVObject data(buffer);
    TLVHead head;
    TLVUtil::Reading(output, data, head);
}

void ReadingUnifiedDataPropertiesFuzz(FuzzedDataProvider &provider)
{
    std::uint8_t data1 = provider.ConsumeIntegral<uint8_t>();
    std::uint8_t data2 = provider.ConsumeIntegral<uint8_t>();
    std::vector<std::uint8_t> buffer = { data1, data2 };
    UnifiedDataProperties input;
    input.tag = provider.ConsumeRandomLengthString();
    input.timestamp = provider.ConsumeIntegral<int64_t>();
    input.shareOptions = static_cast<ShareOptions>(provider.ConsumeIntegralInRange<int32_t>(
        static_cast<int32_t>(ShareOptions::CROSS_APP) + 1, static_cast<int32_t>(ShareOptions::SHARE_OPTIONS_BUTT) - 1));
    input.isRemote = provider.ConsumeBool();
    UnifiedDataProperties output;

    TLVObject data(buffer);
    TLVHead head;
    TAG tag = static_cast<TAG>(provider.ConsumeIntegralInRange<uint16_t>(
        static_cast<uint16_t>(TAG::TAG_BUTT) + 1, static_cast<uint16_t>(TAG::TAG_SUMMARY_VERSION) - 1));
    TLVUtil::Writing(input, data, tag);
    TLVUtil::CountBufferSize(input, data);
    TLVUtil::ReadTlv(output, data, tag);
    TLVUtil::Reading(output, data, head);
}

void ReadingWantParamsFuzz(FuzzedDataProvider &provider)
{
    std::uint8_t data1 = provider.ConsumeIntegral<uint8_t>();
    std::uint8_t data2 = provider.ConsumeIntegral<uint8_t>();
    std::vector<std::uint8_t> buffer = { data1, data2 };
    OHOS::AAFwk::WantParams input;

    std::string idKey = provider.ConsumeRandomLengthString();
    int32_t idValue = provider.ConsumeIntegral<int32_t>();
    input.SetParam(idKey, OHOS::AAFwk::Integer::Box(idValue));
    OHOS::AAFwk::WantParams output;

    TLVObject data(buffer);
    TLVHead head;
    TAG tag = static_cast<TAG>(provider.ConsumeIntegralInRange<uint16_t>(
        static_cast<uint16_t>(TAG::TAG_BUTT) + 1, static_cast<uint16_t>(TAG::TAG_SUMMARY_VERSION) - 1));
    TLVUtil::Writing(input, data, tag);
    TLVUtil::CountBufferSize(input, data);
    TLVUtil::ReadTlv(output, data, tag);
    TLVUtil::Reading(output, data, head);
}

void ReadingPixelMapFuzz(FuzzedDataProvider &provider)
{
    std::uint8_t data1 = provider.ConsumeIntegral<uint8_t>();
    std::uint8_t data2 = provider.ConsumeIntegral<uint8_t>();
    std::vector<std::uint8_t> buffer = { data1, data2 };
    uint32_t color[ID_LEN];
    for (size_t i = 0; i < ID_LEN; ++i) {
        color[i] = provider.ConsumeIntegral<uint8_t>();
    }
    OHOS::Media::InitializationOptions opts = { { provider.ConsumeIntegral<uint8_t>(),
        provider.ConsumeIntegral<uint8_t>() },  Media::PixelFormat::ARGB_8888, Media::PixelFormat::ARGB_8888 };
    std::unique_ptr<OHOS::Media::PixelMap> pixelMap =
        OHOS::Media::PixelMap::Create(color, sizeof(color) / sizeof(color[0]), opts);
    std::shared_ptr<OHOS::Media::PixelMap> input = move(pixelMap);
    std::shared_ptr<OHOS::Media::PixelMap> output;

    TLVObject data(buffer);
    TLVHead head;
    TAG tag = static_cast<TAG>(provider.ConsumeIntegralInRange<uint16_t>(
        static_cast<uint16_t>(TAG::TAG_BUTT) + 1, static_cast<uint16_t>(TAG::TAG_SUMMARY_VERSION) - 1));
    TLVUtil::Writing(input, data, tag);
    TLVUtil::CountBufferSize(input, data);
    TLVUtil::ReadTlv(output, data, tag);
    TLVUtil::Reading(output, data, head);
}

void ReadingMapFuzz(FuzzedDataProvider &provider)
{
    std::uint8_t data1 = provider.ConsumeIntegral<uint8_t>();
    std::uint8_t data2 = provider.ConsumeIntegral<uint8_t>();
    std::vector<std::uint8_t> buffer = { data1, data2 };
    std::shared_ptr<std::map<std::string, ValueType>> input = std::make_shared<std::map<std::string, ValueType>>();
    input->emplace(provider.ConsumeRandomLengthString(), provider.ConsumeRandomLengthString());
    std::shared_ptr<std::map<std::string, ValueType>> output;

    TLVObject data(buffer);
    TLVHead head;
    TAG tag = static_cast<TAG>(provider.ConsumeIntegralInRange<uint16_t>(
        static_cast<uint16_t>(TAG::TAG_BUTT) + 1, static_cast<uint16_t>(TAG::TAG_SUMMARY_VERSION) - 1));
    TLVUtil::Writing(input, data, tag);
    TLVUtil::CountBufferSize(input, data);
    TLVUtil::ReadTlv(output, data, tag);
    TLVUtil::Reading(output, data, head);
}

void ReadingWantPtrFuzz(FuzzedDataProvider &provider)
{
    std::uint8_t data1 = provider.ConsumeIntegral<uint8_t>();
    std::uint8_t data2 = provider.ConsumeIntegral<uint8_t>();
    std::vector<std::uint8_t> buffer = { data1, data2 };
    std::shared_ptr<OHOS::AAFwk::Want> input = std::make_shared<OHOS::AAFwk::Want>();
    input->SetAction(provider.ConsumeRandomLengthString());
    std::shared_ptr<OHOS::AAFwk::Want> output;

    TLVObject data(buffer);
    TLVHead head;
    TAG tag = static_cast<TAG>(provider.ConsumeIntegralInRange<uint16_t>(
        static_cast<uint16_t>(TAG::TAG_BUTT) + 1, static_cast<uint16_t>(TAG::TAG_SUMMARY_VERSION) - 1));
    TLVUtil::Writing(input, data, tag);
    TLVUtil::CountBufferSize(input, data);
    TLVUtil::ReadTlv(output, data, tag);
    TLVUtil::Reading(output, data, head);
}

void ReadingSummaryFuzz(FuzzedDataProvider &provider)
{
    std::uint8_t data1 = provider.ConsumeIntegral<uint8_t>();
    std::uint8_t data2 = provider.ConsumeIntegral<uint8_t>();
    std::vector<std::uint8_t> buffer = { data1, data2 };
    Summary input;
    input.tag = provider.ConsumeRandomLengthString();
    input.totalSize = provider.ConsumeIntegral<int64_t>();
    input.specificSummary.emplace(provider.ConsumeRandomLengthString(), provider.ConsumeIntegral<int64_t>());
    input.summary.emplace(provider.ConsumeRandomLengthString(), provider.ConsumeIntegral<int64_t>());
    input.summaryFormat.emplace(provider.ConsumeRandomLengthString(), std::vector<int32_t>());
    input.version = provider.ConsumeIntegral<int32_t>();
    Summary output;

    TLVObject data(buffer);
    TLVHead head;
    TAG tag = static_cast<TAG>(provider.ConsumeIntegralInRange<uint16_t>(
        static_cast<uint16_t>(TAG::TAG_BUTT) + 1, static_cast<uint16_t>(TAG::TAG_SUMMARY_VERSION) - 1));
    TLVUtil::Writing(input, data, tag);
    TLVUtil::CountBufferSize(input, data);
    TLVUtil::ReadTlv(output, data, tag);
    TLVUtil::Reading(output, data, head);
}

void ReadingDataLoadInfoFuzz(FuzzedDataProvider &provider)
{
    std::uint8_t data1 = provider.ConsumeIntegral<uint8_t>();
    std::uint8_t data2 = provider.ConsumeIntegral<uint8_t>();
    std::vector<std::uint8_t> buffer = { data1, data2 };
    DataLoadInfo input;
    input.deviceId = provider.ConsumeRandomLengthString();
    input.sequenceKey = provider.ConsumeRandomLengthString();
    input.recordCount = provider.ConsumeIntegral<uint32_t>();
    input.types.emplace(provider.ConsumeRandomLengthString());
    input.udKey = provider.ConsumeRandomLengthString();
    DataLoadInfo output;

    TLVObject data(buffer);
    TLVHead head;
    TAG tag = static_cast<TAG>(provider.ConsumeIntegralInRange<uint16_t>(
        static_cast<uint16_t>(TAG::TAG_BUTT) + 1, static_cast<uint16_t>(TAG::TAG_SUMMARY_VERSION) - 1));
    TLVUtil::Writing(input, data, tag);
    TLVUtil::CountBufferSize(input, data);
    TLVUtil::ReadTlv(output, data, tag);
    TLVUtil::Reading(output, data, head);
}

}

/* Fuzzer entry point */
extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
    /* Run your code on data */
    FuzzedDataProvider provider(data, size);
    OHOS::ReadingNullptrFuzz(provider);
    OHOS::ReadingMonostateFuzz(provider);
    OHOS::ReadingStringFuzz(provider);
    OHOS::ReadingVectorFuzz(provider);
    OHOS::ReadingUDtypeFuzz(provider);
    OHOS::ReadingDataStatusFuzz(provider);
    OHOS::ReadingObjectFuzz(provider);
    OHOS::ReadingUnifiedKeyFuzz(provider);
    OHOS::ReadingUnifiedDataFuzz(provider);
    OHOS::ReadingUnifiedRecordFuzz(provider);
    OHOS::ReadingRuntimeFuzz(provider);
    OHOS::ReadingPrivilegeFuzz(provider);
    OHOS::ReadingUriInfoFuzz(provider);
    OHOS::ReadingShareOptionsFuzz(provider);
    OHOS::ReadingUnifiedDataPropertiesFuzz(provider);
    OHOS::ReadingWantParamsFuzz(provider);
    OHOS::ReadingPixelMapFuzz(provider);
    OHOS::ReadingMapFuzz(provider);
    OHOS::ReadingWantPtrFuzz(provider);
    OHOS::ReadingSummaryFuzz(provider);
    OHOS::ReadingDataLoadInfoFuzz(provider);
    OHOS::TearDown();
    return 0;
}