
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

#include "type_descriptor_ffi.h"
#include "type_descriptor_impl.h"
#include "cj_common_ffi.h"

using namespace OHOS::FFI;
using namespace OHOS::UDMF;

namespace OHOS {
namespace UDMF {
extern "C" {

    char * FfiUDMFUniformTypeDescriptorGetTypeId(int64_t typeDescriptorID)
    {
        auto data = FFIData::GetData<CTypeDescriptor>(typeDescriptorID);
        if (data == nullptr) {
            return nullptr;
        }

        return data->GetTypeId();
    }

    CArrString FfiUDMFUniformTypeDescriptorGetBelongingToTypes(int64_t typeDescriptorID)
    {
        auto data = FFIData::GetData<CTypeDescriptor>(typeDescriptorID);
        if (data == nullptr) {
            return CArrString{};
        }

        return data->GetBelongingToTypes();
    }

    char * FfiUDMFUniformTypeDescriptorGetDescription(int64_t typeDescriptorID)
    {
        auto data = FFIData::GetData<CTypeDescriptor>(typeDescriptorID);
        if (data == nullptr) {
            return nullptr;
        }

        return data->GetDescription();
    }

    char * FfiUDMFUniformTypeDescriptorGetReferenceURL(int64_t typeDescriptorID)
    {
        auto data = FFIData::GetData<CTypeDescriptor>(typeDescriptorID);
        if (data == nullptr) {
            return nullptr;
        }

        return data->GetReferenceURL();
    }

    char * FfiUDMFUniformTypeDescriptorGetIconFile(int64_t typeDescriptorID)
    {
        auto data = FFIData::GetData<CTypeDescriptor>(typeDescriptorID);
        if (data == nullptr) {
            return nullptr;
        }

        return data->GetIconFile();
    }

    CArrString FfiUDMFUniformTypeDescriptorGetFilenameExtensions(int64_t typeDescriptorID)
    {
        auto data = FFIData::GetData<CTypeDescriptor>(typeDescriptorID);
        if (data == nullptr) {
            return CArrString{};
        }

        return data->GetFilenameExtensions();
    }

    CArrString FfiUDMFUniformTypeDescriptorGetMimeTypes(int64_t typeDescriptorID)
    {
        auto data = FFIData::GetData<CTypeDescriptor>(typeDescriptorID);
        if (data == nullptr) {
            return CArrString{};
        }

        return data->GetMimeTypes();
    }

    bool FfiUDMFUniformTypeDescriptorBelongsTo(int64_t typeDescriptorID, const char *type)
    {
        auto data = FFIData::GetData<CTypeDescriptor>(typeDescriptorID);
        if (data == nullptr) {
            return false;
        }

        return data->BelongsTo(type);
    }

    bool FfiUDMFUniformTypeDescriptorIsLowerLevelType(int64_t typeDescriptorID, const char *type)
    {
        auto data = FFIData::GetData<CTypeDescriptor>(typeDescriptorID);
        if (data == nullptr) {
            return false;
        }

        return data->IsLowerLevelType(type);
    }

    bool FfiUDMFUniformTypeDescriptorIsHigherLevelType(int64_t typeDescriptorID, const char *type)
    {
        auto data = FFIData::GetData<CTypeDescriptor>(typeDescriptorID);
        if (data == nullptr) {
            return false;
        }

        return data->IsHigherLevelType(type);
    }

    bool FfiUDMFUniformTypeDescriptorEquals(int64_t thisTypeDescriptorID, int64_t thatTypeDescriptorID)
    {
        auto thisTypeDescriptor = FFIData::GetData<CTypeDescriptor>(thisTypeDescriptorID);
        if (thisTypeDescriptor == nullptr) {
            return false;
        }

        auto thatTypeDescriptor = FFIData::GetData<CTypeDescriptor>(thatTypeDescriptorID);
        if (thatTypeDescriptor == nullptr) {
            return false;
        }

        return thisTypeDescriptor->Equals(thatTypeDescriptor);
    }
    
}
}
}
