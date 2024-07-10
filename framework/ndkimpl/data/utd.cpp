/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define LOG_TAG "Utd"

#include "utd.h"
#include <cstring>
#include <vector>
#include "securec.h"
#include "logger.h"
#include "utd_client.h"
#include "udmf_ndk_common.h"
#include "udmf_err_code.h"

using namespace OHOS::UDMF;

static constexpr const int32_t MAX_UTD_SIZE = 50;

typedef Status (UtdClient::*GetUtdByConditionPtr)(const std::string&, std::string&, std::string);

static void DestroyArrayPtr(const char** &arrayPtr, unsigned int& count)
{
    if (arrayPtr == nullptr) {
        LOG_ERROR(UDMF_NDK, "Cannot delete arrayPtr because it's a nullptr.");
        return;
    }
    for (unsigned int i = 0; i < count; i++) {
        if (arrayPtr[i] != nullptr) {
            delete[] arrayPtr[i];
            arrayPtr[i] = nullptr;
        }
    }
    delete[] arrayPtr;
    arrayPtr = nullptr;
    count = 0;
    LOG_INFO(UDMF_NDK, "END TO DELETE arrayPtr.");
}

static const char** CreateStrArrByVector(const std::vector<std::string>& paramVector, unsigned int* count)
{
    unsigned int size = paramVector.size();
    if (size <= 0 || size > MAX_UTD_SIZE) {
        *count = 0;
        return nullptr;
    }
    auto charPtr = new (std::nothrow) char* [size];
    if (charPtr == nullptr) {
        *count = 0;
        return nullptr;
    }
    for (unsigned int i = 0; i < size; i++) {
        charPtr[i] = new char[paramVector[i].size() + 1];
        if (charPtr[i] == nullptr ||
            strcpy_s(charPtr[i], paramVector[i].size() + 1, paramVector[i].c_str()) != UDMF_E_OK) {
            LOG_ERROR(UDMF_NDK, "str copy error!");
            const char** arrayPtr = const_cast<const char**>(charPtr);
            DestroyArrayPtr(arrayPtr, size);
            *count = 0;
            return nullptr;
        }
    }
    *count = size;
    return const_cast<const char**>(charPtr);
}

static std::shared_ptr<TypeDescriptor> GetTypeDescriptorByUtdClient(const char* typeId)
{
    std::shared_ptr<TypeDescriptor> typeDescriptor;
    UtdClient::GetInstance().GetTypeDescriptor(typeId, typeDescriptor);
    return typeDescriptor;
}

static bool IsUtdInvalid(OH_Utd* pThis)
{
    return pThis == nullptr || pThis->id != UTD_STRUCT_ID;
}

static const char** GetTypesByCondition(const char* condition, unsigned int* count, GetUtdByConditionPtr funcPtr)
{
    if (condition == nullptr || count == nullptr) {
        return nullptr;
    }
    std::string typeIdStr;
    (UtdClient::GetInstance().*funcPtr)(condition, typeIdStr, DEFAULT_TYPE_ID);
    if (typeIdStr.empty()) {
        return nullptr;
    }
    char* typeId = new char[typeIdStr.size() + 1];
    if (strcpy_s(typeId, typeIdStr.size() + 1, typeIdStr.c_str()) != UDMF_E_OK) {
        LOG_ERROR(UDMF_NDK, "str copy error!");
        delete[] typeId;
        return nullptr;
    }
    *count = 1;
    char **typeIds = new char *[*count];
    typeIds[0] = typeId;
    return const_cast<const char**>(typeIds);
}

OH_Utd* OH_Utd_Create(const char* typeId)
{
    if (typeId == nullptr) {
        return nullptr;
    }
    OH_Utd* pThis = new (std::nothrow) OH_Utd();
    if (pThis == nullptr) {
        LOG_ERROR(UDMF_NDK, "Failed to apply for memory.");
        return nullptr;
    }
    auto typeDescriptor = GetTypeDescriptorByUtdClient(typeId);
    pThis->typeId = typeDescriptor->GetTypeId();
    pThis->description = typeDescriptor->GetDescription();
    pThis->referenceURL = typeDescriptor->GetReferenceURL();
    pThis->iconFile = typeDescriptor->GetIconFile();
    pThis->belongingToTypes =
        CreateStrArrByVector(typeDescriptor->GetBelongingToTypes(), &(pThis->belongingToTypesCount));
    pThis->filenameExtensions =
        CreateStrArrByVector(typeDescriptor->GetFilenameExtensions(), &(pThis->filenameExtensionsCount));
    pThis->mimeTypes = CreateStrArrByVector(typeDescriptor->GetMimeTypes(), &(pThis->mimeTypeCount));
    return pThis;
}

void OH_Utd_Destroy(OH_Utd* pThis)
{
    if (IsUtdInvalid(pThis)) {
        LOG_ERROR(UDMF_NDK, "Failed to Destroy UTD, because pThis maybe nullptr or non-UTD struct ptr.");
        return;
    }
    DestroyArrayPtr(pThis->belongingToTypes, pThis->belongingToTypesCount);
    DestroyArrayPtr(pThis->filenameExtensions, pThis->filenameExtensionsCount);
    DestroyArrayPtr(pThis->mimeTypes, pThis->mimeTypeCount);
    delete pThis;
    LOG_INFO(UDMF_NDK, "OH_Utd ptr already be delete");
}

const char* OH_Utd_GetTypeId(OH_Utd* pThis)
{
    if (IsUtdInvalid(pThis)) {
        return nullptr;
    }
    return pThis->typeId.c_str();
}

const char* OH_Utd_GetDescription(OH_Utd* pThis)
{
    if (IsUtdInvalid(pThis)) {
        return nullptr;
    }
    return pThis->description.c_str();
}

const char* OH_Utd_GetReferenceURL(OH_Utd* pThis)
{
    if (IsUtdInvalid(pThis)) {
        return nullptr;
    }
    return pThis->referenceURL.c_str();
}

const char* OH_Utd_GetIconFile(OH_Utd* pThis)
{
    if (IsUtdInvalid(pThis)) {
        return nullptr;
    }
    return pThis->iconFile.c_str();
}

const char** OH_Utd_GetBelongingToTypes(OH_Utd* pThis, unsigned int* count)
{
    if (IsUtdInvalid(pThis) || count == nullptr) {
        return nullptr;
    }
    *count = pThis->belongingToTypesCount;
    return pThis->belongingToTypes;
}

const char** OH_Utd_GetFilenameExtensions(OH_Utd* pThis, unsigned int* count)
{
    if (IsUtdInvalid(pThis) || count == nullptr) {
        return nullptr;
    }
    *count = pThis->filenameExtensionsCount;
    return pThis->filenameExtensions;
}

const char** OH_Utd_GetMimeTypes(OH_Utd* pThis, unsigned int* count)
{
    if (IsUtdInvalid(pThis) || count == nullptr) {
        return nullptr;
    }
    *count = pThis->mimeTypeCount;
    return pThis->mimeTypes;
}

const char** OH_Utd_GetTypesByFilenameExtension(const char* extension, unsigned int* count)
{
    return GetTypesByCondition(extension, count, &UtdClient::GetUniformDataTypeByFilenameExtension);
}

const char** OH_Utd_GetTypesByMimeType(const char* mimeType, unsigned int* count)
{
    return GetTypesByCondition(mimeType, count, &UtdClient::GetUniformDataTypeByMIMEType);
}

bool OH_Utd_IsBelongsTo(const char* srcTypeId, const char* destTypeId)
{
    if (srcTypeId == nullptr || destTypeId == nullptr) {
        return false;
    }
    auto typeDescriptor = GetTypeDescriptorByUtdClient(srcTypeId);
    bool checkResult = false;
    typeDescriptor->BelongsTo(destTypeId, checkResult);
    return checkResult;
}

bool OH_Utd_IsLowerLevelType(const char* srcTypeId, const char* destTypeId)
{
    if (srcTypeId == nullptr || destTypeId == nullptr) {
        return false;
    }
    auto typeDescriptor = GetTypeDescriptorByUtdClient(srcTypeId);
    bool checkResult = false;
    typeDescriptor->IsLowerLevelType(destTypeId, checkResult);
    return checkResult;
}

bool OH_Utd_IsHigherLevelType(const char* srcTypeId, const char* destTypeId)
{
    if (srcTypeId == nullptr || destTypeId == nullptr) {
        return false;
    }
    auto typeDescriptor = GetTypeDescriptorByUtdClient(srcTypeId);
    bool checkResult = false;
    typeDescriptor->IsHigherLevelType(destTypeId, checkResult);
    return checkResult;
}

bool OH_Utd_IsEquals(OH_Utd* utd1, OH_Utd* utd2)
{
    if (IsUtdInvalid(utd1) || IsUtdInvalid(utd2)) {
        return false;
    }
    return GetTypeDescriptorByUtdClient(utd1->typeId.c_str())
        ->Equals(GetTypeDescriptorByUtdClient(utd2->typeId.c_str()));
}

void OH_Utd_DestroyStringList(const char** list, unsigned int count)
{
    DestroyArrayPtr(list, count);
}
