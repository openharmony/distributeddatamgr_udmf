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

#include "securec.h"
#include "logger.h"
#include "utd_client.h"
#include "udmf_capi_common.h"
#include "udmf_err_code.h"

using namespace OHOS::UDMF;

static constexpr const int32_t MAX_UTD_SIZE = 50;

typedef Status (UtdClient::*GetUtdByConditionPtr)(const std::string&, std::string&, std::string);

static void DestroyArrayPtr(const char** &arrayPtr, unsigned int& count)
{
    if (arrayPtr == nullptr) {
        LOG_ERROR(UDMF_CAPI, "Cannot delete arrayPtr because it's a nullptr.");
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
    LOG_INFO(UDMF_CAPI, "delete arrayPtr finish.");
}

static const char** CreateStrArrByVector(const std::vector<std::string>& paramVector, unsigned int* count)
{
    unsigned int size = paramVector.size();
    if (size <= 0 || size > MAX_UTD_SIZE) {
        LOG_ERROR(UDMF_CAPI, "Cannot create array, because size is illegal or exceeds the max value of UTD.");
        *count = 0;
        return nullptr;
    }
    auto charPtr = new (std::nothrow) char* [size];
    if (charPtr == nullptr) {
        *count = 0;
        return nullptr;
    }
    for (unsigned int i = 0; i < size; i++) {
        charPtr[i] = new (std::nothrow) char[paramVector[i].size() + 1];
        if (charPtr[i] == nullptr ||
            strcpy_s(charPtr[i], paramVector[i].size() + 1, paramVector[i].c_str()) != UDMF_E_OK) {
            LOG_ERROR(UDMF_CAPI, "obtain the memory error, or str copy error!");
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
    return pThis == nullptr || pThis->cid != NdkStructId::UTD_STRUCT_ID;
}

static const char** GetTypesByCondition(const char* condition, unsigned int* count, GetUtdByConditionPtr funcPtr)
{
    if (condition == nullptr || count == nullptr || funcPtr == nullptr) {
        return nullptr;
    }
    std::string typeIdStr;
    Status result = (UtdClient::GetInstance().*funcPtr)(condition, typeIdStr, DEFAULT_TYPE_ID);
    if (result != Status::E_OK || typeIdStr.empty()) {
        LOG_ERROR(UDMF_CAPI, "Failed to obtain typeId by invoking the native function.");
        return nullptr;
    }
    auto typeId = new (std::nothrow) char[typeIdStr.size() + 1];
    if (typeId == nullptr) {
        LOG_ERROR(UDMF_CAPI, "obtain typeId's memory error!");
        return nullptr;
    }
    if (strcpy_s(typeId, typeIdStr.size() + 1, typeIdStr.c_str()) != UDMF_E_OK) {
        LOG_ERROR(UDMF_CAPI, "str copy error!");
        delete[] typeId;
        return nullptr;
    }
    *count = 1;
    auto typeIds = new char* [*count];
    typeIds[0] = typeId;
    return const_cast<const char**>(typeIds);
}

OH_Utd* OH_Utd_Create(const char* typeId)
{
    if (typeId == nullptr) {
        return nullptr;
    }
    auto pThis = new (std::nothrow) OH_Utd();
    if (pThis == nullptr) {
        LOG_ERROR(UDMF_CAPI, "Failed to apply for memory.");
        return nullptr;
    }
    auto typeDescriptor = GetTypeDescriptorByUtdClient(typeId);
    if (typeDescriptor == nullptr) {
        LOG_ERROR(UDMF_CAPI, "Failed to create by invoking the native function.");
        return nullptr;
    }
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
        LOG_ERROR(UDMF_CAPI, "Failed to Destroy UTD, because pThis maybe nullptr or non-UTD struct ptr.");
        return;
    }
    DestroyArrayPtr(pThis->belongingToTypes, pThis->belongingToTypesCount);
    DestroyArrayPtr(pThis->filenameExtensions, pThis->filenameExtensionsCount);
    DestroyArrayPtr(pThis->mimeTypes, pThis->mimeTypeCount);
    delete pThis;
    LOG_INFO(UDMF_CAPI, "OH_Utd ptr already be delete");
}

const char* OH_Utd_GetTypeId(OH_Utd* pThis)
{
    return IsUtdInvalid(pThis) ? nullptr : pThis->typeId.c_str();
}

const char* OH_Utd_GetDescription(OH_Utd* pThis)
{
    return IsUtdInvalid(pThis) ? nullptr : pThis->description.c_str();
}

const char* OH_Utd_GetReferenceUrl(OH_Utd* pThis)
{
    return IsUtdInvalid(pThis) ? nullptr : pThis->referenceURL.c_str();
}

const char* OH_Utd_GetIconFile(OH_Utd* pThis)
{
    return IsUtdInvalid(pThis) ? nullptr : pThis->iconFile.c_str();
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

bool OH_Utd_BelongsTo(const char* srcTypeId, const char* destTypeId)
{
    if (srcTypeId == nullptr || destTypeId == nullptr) {
        LOG_ERROR(UDMF_CAPI, "The input parameter is nullptr");
        return false;
    }
    auto typeDescriptor = GetTypeDescriptorByUtdClient(srcTypeId);
    if (typeDescriptor == nullptr) {
        LOG_ERROR(UDMF_CAPI, "Failed to create by invoking the native function.");
        return false;
    }
    bool checkResult{false};
    if (typeDescriptor->BelongsTo(destTypeId, checkResult) != Status::E_OK) {
        LOG_ERROR(UDMF_CAPI, "invoke the native function error.");
    }
    return checkResult;
}

bool OH_Utd_IsLower(const char* srcTypeId, const char* destTypeId)
{
    if (srcTypeId == nullptr || destTypeId == nullptr) {
        LOG_ERROR(UDMF_CAPI, "The input parameter is nullptr");
        return false;
    }
    auto typeDescriptor = GetTypeDescriptorByUtdClient(srcTypeId);
    if (typeDescriptor == nullptr) {
        LOG_ERROR(UDMF_CAPI, "Failed to create by invoking the native function.");
        return false;
    }
    bool checkResult{false};
    if (typeDescriptor->IsLowerLevelType(destTypeId, checkResult) != Status::E_OK) {
        LOG_ERROR(UDMF_CAPI, "Failed to create by invoking the native function.");
    }
    return checkResult;
}

bool OH_Utd_IsHigher(const char* srcTypeId, const char* destTypeId)
{
    if (srcTypeId == nullptr || destTypeId == nullptr) {
        LOG_ERROR(UDMF_CAPI, "The input parameter is nullptr");
        return false;
    }
    auto typeDescriptor = GetTypeDescriptorByUtdClient(srcTypeId);
    if (typeDescriptor == nullptr) {
        LOG_ERROR(UDMF_CAPI, "Failed to create by invoking the native function.");
        return false;
    }
    bool checkResult{false};
    if (typeDescriptor->IsHigherLevelType(destTypeId, checkResult) != Status::E_OK) {
        LOG_ERROR(UDMF_CAPI, "Failed to create by invoking the native function.");
    }
    return checkResult;
}

bool OH_Utd_Equals(OH_Utd* utd1, OH_Utd* utd2)
{
    if (IsUtdInvalid(utd1) || IsUtdInvalid(utd2)) {
        LOG_ERROR(UDMF_CAPI, "The input parameter is invalid");
        return false;
    }
    auto typeDescriptor1 = GetTypeDescriptorByUtdClient(utd1->typeId.c_str());
    if (typeDescriptor1 == nullptr) {
        LOG_ERROR(UDMF_CAPI, "utd1 failed to create by invoking the native function.");
        return false;
    }
    auto typeDescriptor2 = GetTypeDescriptorByUtdClient(utd2->typeId.c_str());
    if (typeDescriptor2 == nullptr) {
        LOG_ERROR(UDMF_CAPI, "utd2 failed to create by invoking the native function.");
        return false;
    }
    return typeDescriptor1->Equals(typeDescriptor2);
}

void OH_Utd_DestroyStringList(const char** list, unsigned int count)
{
    DestroyArrayPtr(list, count);
}
