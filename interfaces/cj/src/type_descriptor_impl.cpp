
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


#include "type_descriptor_impl.h"
#include "cj_common_ffi.h"

#include <string>
#include <vector>

#include "ffi_remote_data.h"

#include "utils.h"

using namespace OHOS::FFI;
using namespace OHOS::UDMF;

namespace OHOS {
namespace UDMF {
    CTypeDescriptor::CTypeDescriptor(){
        typeDescriptor_=nullptr;
    }

    CTypeDescriptor::CTypeDescriptor(std::shared_ptr<UDMF::TypeDescriptor> typeDescriptor)
    {
        typeDescriptor_ = typeDescriptor;
    }

    char * CTypeDescriptor::GetTypeId(const char *type)
    {
        std::string ret = typeDescriptor_->GetTypeId();
        return Utils::MallocCString(ret);
    }

    CArrString CTypeDescriptor::GetBelongingToTypes()
    {
        std::vector<std::string> types = typeDescriptor_->GetBelongingToTypes();
        return Utils::StringVectorToArray(types);
    }

    char * CTypeDescriptor::GetDescription(const char *type)
    {
        std::string ret = typeDescriptor_->GetDescription();
        return Utils::MallocCString(ret);
    }

    char * CTypeDescriptor::GetIconFile(const char *type)
    {
        std::string ret = typeDescriptor_->GetIconFile();
        return Utils::MallocCString(ret);
    }

    char * CTypeDescriptor::GetReferenceURL(const char *type)
    {
        std::string ret = typeDescriptor_->GetReferenceURL();
        return Utils::MallocCString(ret);
    }

    CArrString CTypeDescriptor::GetFilenameExtensions()
    {
        std::vector<std::string> types = typeDescriptor_->GetFilenameExtensions();
        return Utils::StringVectorToArray(types);
    }

    CArrString CTypeDescriptor::GetMimeTypes()
    {
        std::vector<std::string> types = typeDescriptor_->GetMimeTypes();
        return Utils::StringVectorToArray(types);
    }


    bool CTypeDescriptor::BelongsTo(const char *type)
    {
        bool result = false;
        typeDescriptor_->BelongsTo(type, result);
        return result;
    }

    bool CTypeDescriptor::IsLowerLevelType(const char *type)
    {
        bool result = false;
        typeDescriptor_->IsLowerLevelType(type, result);
        return result;
    }

    bool CTypeDescriptor::IsHigherLevelType(const char *type)
    {
        bool result = false;
        typeDescriptor_->IsHigherLevelType(type, result);
        return result;
    }

    const std::shared_ptr<UDMF::TypeDescriptor> &CTypeDescriptor::GetTypeDescriptor() const
    {
        return typeDescriptor_;
    }

    bool CTypeDescriptor::Equals(CTypeDescriptor* thatCTypeDescriptor)
    {
        return typeDescriptor_->Equals(thatCTypeDescriptor->GetTypeDescriptor());
    }

}
}
