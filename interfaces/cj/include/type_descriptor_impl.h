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

#ifndef UDMF_TYPE_DESCRIPTOR_IMPL_H
#define UDMF_TYPE_DESCRIPTOR_IMPL_H

#include <memory>

#include "type_descriptor.h"
#include "cj_common_ffi.h"
#include "udmf_log.h"

namespace OHOS {
namespace UDMF {
    using namespace OHOS::UDMF;

    class CTypeDescriptor : public OHOS::FFI::FFIData {
        DECL_TYPE(CTypeDescriptor, OHOS::FFI::FFIData)
        public:
            CTypeDescriptor(std::shared_ptr<UDMF::TypeDescriptor> typeDescriptor);

            char *GetTypeId();
            CArrString GetBelongingToTypes();
            char *GetDescription();
            char *GetIconFile();
            char *GetReferenceURL();
            CArrString GetFilenameExtensions();
            CArrString GetMimeTypes();

            bool BelongsTo(const char *type);
            bool IsLowerLevelType(const char *type);
            bool IsHigherLevelType(const char *type);
            bool Equals(CTypeDescriptor* thatCTypeDescriptor);

            const std::shared_ptr<UDMF::TypeDescriptor> &GetTypeDescriptor() const;
    
        private:
            std::shared_ptr<UDMF::TypeDescriptor> typeDescriptor_;
    };

}
} // namespace OHOS::UDMF

#endif