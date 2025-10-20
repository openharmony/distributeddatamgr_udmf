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

#include <unistd.h>
#include <thread>

#include "token_setproc.h"

#include "link.h"

#include "udmf_capi_common.h"
#include "utd_fuzzer.h"
#include "utd.h"

#include <fuzzer/FuzzedDataProvider.h>

using namespace OHOS;
using namespace OHOS::UDMF;

namespace OHOS {

void SetUpTestCase()
{}

void TearDown()
{}

void GetUtdTypeIdAndDescriptionFuzz(FuzzedDataProvider &provider)
{
    std::string typeId = provider.ConsumeRandomLengthString();
    OH_Utd *utd = OH_Utd_Create(typeId.c_str());
    OH_Utd_GetTypeId(utd);
    OH_Utd_GetDescription(utd);
    OH_Utd_Destroy(utd);
}

void GetUtdReferenceUrlAndIconFileFuzz(FuzzedDataProvider &provider)
{
    std::string typeId = provider.ConsumeRandomLengthString();
    OH_Utd *utd = OH_Utd_Create(typeId.c_str());
    OH_Utd_GetReferenceUrl(utd);
    OH_Utd_GetIconFile(utd);
    OH_Utd_Destroy(utd);
}

void GetUtdBelongingToTypesAndFilenameExtensionsFuzz(FuzzedDataProvider &provider)
{
    std::string typeId = provider.ConsumeRandomLengthString();
    OH_Utd *utd = OH_Utd_Create(typeId.c_str());
    unsigned int count = 0;
    OH_Utd_GetBelongingToTypes(utd, &count);
    OH_Utd_GetFilenameExtensions(utd, &count);
    OH_Utd_GetMimeTypes(utd, &count);
    OH_Utd_Destroy(utd);
}

void GetUtdTypesByFilenameExtensionFuzz(FuzzedDataProvider &provider)
{
    std::string typeId = provider.ConsumeRandomLengthString();
    OH_Utd *utd = OH_Utd_Create(typeId.c_str());
    unsigned int count = 0;
    std::string extension = provider.ConsumeRandomLengthString();
    auto typeIds = OH_Utd_GetTypesByFilenameExtension(extension.c_str(), &count);
    OH_Utd_DestroyStringList(typeIds, count);
    OH_Utd_Destroy(utd);
}

void GetUtdTypesByMimeTypeFuzz(FuzzedDataProvider &provider)
{
    std::string mimeType = provider.ConsumeRandomLengthString();
    std::string typeId = provider.ConsumeRandomLengthString();
    OH_Utd *utd = OH_Utd_Create(typeId.c_str());
    unsigned int count = 0;
    auto typeIds = OH_Utd_GetTypesByMimeType(mimeType.c_str(), &count);
    OH_Utd_DestroyStringList(typeIds, count);
    OH_Utd_Destroy(utd);
}

void UtdBelongsToFuzz(FuzzedDataProvider &provider)
{
    std::string srcTypeId = provider.ConsumeRandomLengthString();
    std::string destTypeId = provider.ConsumeRandomLengthString();
    OH_Utd_BelongsTo(srcTypeId.c_str(), destTypeId.c_str());
}

void UtdIsLowerFuzz(FuzzedDataProvider &provider)
{
    std::string srcTypeId = provider.ConsumeRandomLengthString();
    std::string destTypeId = provider.ConsumeRandomLengthString();
    OH_Utd_IsLower(srcTypeId.c_str(), destTypeId.c_str());
}

void UtdIsHigherFuzz(FuzzedDataProvider &provider)
{
    std::string srcTypeId = provider.ConsumeRandomLengthString();
    std::string destTypeId = provider.ConsumeRandomLengthString();
    OH_Utd_IsHigher(srcTypeId.c_str(), destTypeId.c_str());
}

void UtdEqualsFuzz(FuzzedDataProvider &provider)
{
    std::string typeId1 = provider.ConsumeRandomLengthString();
    OH_Utd *utd1 = OH_Utd_Create(typeId1.c_str());
    std::string typeId2 = provider.ConsumeRandomLengthString();
    OH_Utd *utd2 = OH_Utd_Create(typeId2.c_str());
    OH_Utd_Equals(utd1, utd2);
    OH_Utd_Destroy(utd1);
    OH_Utd_Destroy(utd2);
}

}

/* Fuzzer entry point */
extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
    /* Run your code on data */
    FuzzedDataProvider provider(data, size);
    OHOS::SetUpTestCase();
    OHOS::GetUtdTypeIdAndDescriptionFuzz(provider);
    OHOS::GetUtdReferenceUrlAndIconFileFuzz(provider);
    OHOS::GetUtdBelongingToTypesAndFilenameExtensionsFuzz(provider);
    OHOS::GetUtdTypesByFilenameExtensionFuzz(provider);
    OHOS::GetUtdTypesByMimeTypeFuzz(provider);
    OHOS::UtdBelongsToFuzz(provider);
    OHOS::UtdIsLowerFuzz(provider);
    OHOS::UtdIsHigherFuzz(provider);
    OHOS::UtdEqualsFuzz(provider);
    OHOS::TearDown();
    return 0;
}