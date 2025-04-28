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

#include "utd_client_fuzzer.h"
#include "utd_client.h"

#include <fuzzer/FuzzedDataProvider.h>

using namespace OHOS;
using namespace OHOS::UDMF;

namespace OHOS {
void SetUpTestCase()
{
}

void TearDown()
{
}

void GetTypeDescriptorFuzz(FuzzedDataProvider &provider)
{
    std::string typeId = provider.ConsumeRandomLengthString();
    std::shared_ptr<TypeDescriptor> typeDescriptor;
    UtdClient::GetInstance().GetTypeDescriptor(typeId, typeDescriptor);
}

void GetUniformDataTypeByFilenameExtensionDefaultBelongsFuzz(FuzzedDataProvider &provider)
{
    std::string fileExtension = provider.ConsumeRandomLengthString();
    std::string typeId;
    UtdClient::GetInstance().GetUniformDataTypeByFilenameExtension(fileExtension, typeId);
}

void GetUniformDataTypeByFilenameExtensionFuzz(FuzzedDataProvider &provider)
{
    std::string fileExtension = provider.ConsumeRandomLengthString();
    std::string typeId;
    std::string belongsTo = provider.ConsumeRandomLengthString();
    UtdClient::GetInstance().GetUniformDataTypeByFilenameExtension(fileExtension, typeId, belongsTo);
}

void GetUniformDataTypesByFilenameExtensionDefaultBelongsFuzz(FuzzedDataProvider &provider)
{
    std::string fileExtension = provider.ConsumeRandomLengthString();
    std::vector<std::string> typeIds;
    UtdClient::GetInstance().GetUniformDataTypesByFilenameExtension(fileExtension, typeIds);
}

void GetUniformDataTypesByFilenameExtensionFuzz(FuzzedDataProvider &provider)
{
    std::string fileExtension = provider.ConsumeRandomLengthString();
    std::vector<std::string> typeIds;
    std::string belongsTo = provider.ConsumeRandomLengthString();
    UtdClient::GetInstance().GetUniformDataTypesByFilenameExtension(fileExtension, typeIds, belongsTo);
}

void GetUniformDataTypeByMIMETypeDefaultBelongsFuzz(FuzzedDataProvider &provider)
{
    std::string mimeType = provider.ConsumeRandomLengthString();
    std::string typeId;
    UtdClient::GetInstance().GetUniformDataTypeByMIMEType(mimeType, typeId);
}

void GetUniformDataTypeByMIMETypeFuzz(FuzzedDataProvider &provider)
{
    std::string mimeType = provider.ConsumeRandomLengthString();
    std::string typeId;
    std::string belongsTo = provider.ConsumeRandomLengthString();
    UtdClient::GetInstance().GetUniformDataTypeByMIMEType(mimeType, typeId, belongsTo);
}

void GetUniformDataTypesByMIMETypeDefaultBelongsFuzz(FuzzedDataProvider &provider)
{
    std::string mimeType = provider.ConsumeRandomLengthString();
    std::vector<std::string> typeIds;
    UtdClient::GetInstance().GetUniformDataTypesByMIMEType(mimeType, typeIds);
}

void GetUniformDataTypesByMIMETypeFuzz(FuzzedDataProvider &provider)
{
    std::string mimeType = provider.ConsumeRandomLengthString();
    std::vector<std::string> typeIds;
    std::string belongsTo = provider.ConsumeRandomLengthString();
    UtdClient::GetInstance().GetUniformDataTypesByMIMEType(mimeType, typeIds, belongsTo);
}

void IsUtdFuzz(FuzzedDataProvider &provider)
{
    std::string typeId = provider.ConsumeRandomLengthString();
    bool result;
    UtdClient::GetInstance().IsUtd(typeId, result);
}

}
/* Fuzzer entry point */
extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
    /* Run your code on data */
    FuzzedDataProvider provider(data, size);
    OHOS::SetUpTestCase();
    OHOS::GetTypeDescriptorFuzz(provider);
    OHOS::GetUniformDataTypeByFilenameExtensionDefaultBelongsFuzz(provider);
    OHOS::GetUniformDataTypeByFilenameExtensionFuzz(provider);
    OHOS::GetUniformDataTypesByFilenameExtensionDefaultBelongsFuzz(provider);
    OHOS::GetUniformDataTypesByFilenameExtensionFuzz(provider);
    OHOS::GetUniformDataTypeByMIMETypeDefaultBelongsFuzz(provider);
    OHOS::GetUniformDataTypeByMIMETypeFuzz(provider);
    OHOS::GetUniformDataTypesByMIMETypeDefaultBelongsFuzz(provider);
    OHOS::GetUniformDataTypesByMIMETypeFuzz(provider);
    OHOS::IsUtdFuzz(provider);
    return 0;
}