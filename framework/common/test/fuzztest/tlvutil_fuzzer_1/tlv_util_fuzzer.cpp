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

using namespace OHOS;
using namespace OHOS::Security::AccessToken;
using namespace OHOS::UDMF;

namespace OHOS {
static constexpr int END_INTERVAL = 3;

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
    Runtime input;
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
    std::shared_ptr<OHOS::Media::PixelMap> input;
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
    std::shared_ptr<std::map<std::string, ValueType>> input;
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
    std::shared_ptr<OHOS::AAFwk::Want> input;
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
    OHOS::TearDown();
    return 0;
}