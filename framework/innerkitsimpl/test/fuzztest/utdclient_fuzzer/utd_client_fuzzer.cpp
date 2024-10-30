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

using namespace OHOS;
using namespace OHOS::UDMF;

namespace OHOS {
void SetUpTestCase()
{
}

void TearDown()
{
}

void GetTypeDescriptorFuzz(const uint8_t *data, size_t size)
{
    std::string typeId(data, data + size);
    std::shared_ptr<TypeDescriptor> typeDescriptor;
    UtdClient::GetInstance().GetTypeDescriptor(typeId, typeDescriptor);
}

void GetUniformDataTypeByFilenameExtensionDefaultBelongsFuzz(const uint8_t *data, size_t size)
{
    std::string fileExtension(data, data + size);
    std::string typeId;
    UtdClient::GetInstance().GetUniformDataTypeByFilenameExtension(fileExtension, typeId);
}

void GetUniformDataTypeByFilenameExtensionFuzz(const uint8_t *data, size_t size)
{
    std::string fileExtension(data, data + size);
    std::string typeId;
    std::string belongsTo(data, data + size);
    UtdClient::GetInstance().GetUniformDataTypeByFilenameExtension(fileExtension, typeId, belongsTo);
}

void GetUniformDataTypesByFilenameExtensionDefaultBelongsFuzz(const uint8_t *data, size_t size)
{
    std::string fileExtension(data, data + size);
    std::vector<std::string> typeIds;
    UtdClient::GetInstance().GetUniformDataTypesByFilenameExtension(fileExtension, typeIds);
}

void GetUniformDataTypesByFilenameExtensionFuzz(const uint8_t *data, size_t size)
{
    std::string fileExtension(data, data + size);
    std::vector<std::string> typeIds;
    std::string belongsTo(data, data + size);
    UtdClient::GetInstance().GetUniformDataTypesByFilenameExtension(fileExtension, typeIds, belongsTo);
}

void GetUniformDataTypeByMIMETypeDefaultBelongsFuzz(const uint8_t *data, size_t size)
{
    std::string mimeType(data, data + size);
    std::string typeId;
    UtdClient::GetInstance().GetUniformDataTypeByMIMEType(mimeType, typeId);
}

void GetUniformDataTypeByMIMETypeFuzz(const uint8_t *data, size_t size)
{
    std::string mimeType(data, data + size);
    std::string typeId;
    std::string belongsTo(data, data + size);
    UtdClient::GetInstance().GetUniformDataTypeByMIMEType(mimeType, typeId, belongsTo);
}

void GetUniformDataTypesByMIMETypeDefaultBelongsFuzz(const uint8_t *data, size_t size)
{
    std::string mimeType(data, data + size);
    std::vector<std::string> typeIds;
    UtdClient::GetInstance().GetUniformDataTypesByMIMEType(mimeType, typeIds);
}

void GetUniformDataTypesByMIMETypeFuzz(const uint8_t *data, size_t size)
{
    std::string mimeType(data, data + size);
    std::vector<std::string> typeIds;
    std::string belongsTo(data, data + size);
    UtdClient::GetInstance().GetUniformDataTypesByMIMEType(mimeType, typeIds, belongsTo);
}

void IsUtdFuzz(const uint8_t *data, size_t size)
{
    std::string typeId(data, data + size);
    bool result;
    UtdClient::GetInstance().IsUtd(typeId, result);
}

}
/* Fuzzer entry point */
extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size)
{
    /* Run your code on data */
    OHOS::SetUpTestCase();
    OHOS::GetTypeDescriptorFuzz(data, size);
    OHOS::GetUniformDataTypeByFilenameExtensionDefaultBelongsFuzz(data, size);
    OHOS::GetUniformDataTypeByFilenameExtensionFuzz(data, size);
    OHOS::GetUniformDataTypesByFilenameExtensionDefaultBelongsFuzz(data, size);
    OHOS::GetUniformDataTypesByFilenameExtensionFuzz(data, size);
    OHOS::GetUniformDataTypeByMIMETypeDefaultBelongsFuzz(data, size);
    OHOS::GetUniformDataTypeByMIMETypeFuzz(data, size);
    OHOS::GetUniformDataTypesByMIMETypeDefaultBelongsFuzz(data, size);
    OHOS::GetUniformDataTypesByMIMETypeFuzz(data, size);
    OHOS::IsUtdFuzz(data, size);
    return 0;
}