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

#ifndef UDMF_TYPE_DESCRIPTOR_TAIHE_H
#define UDMF_TYPE_DESCRIPTOR_TAIHE_H

#include "type_descriptor.h"
#include "taihe_common_utils.h"
#include "taihe/runtime.hpp"
#include "ohos.data.uniformTypeDescriptor.impl.hpp"
#include "ohos.data.uniformTypeDescriptor.proj.hpp"

namespace OHOS {
namespace UDMF {
class TypeDescriptorImpl {
private:
    std::shared_ptr<TypeDescriptor> nativeDescriptor_;
public:
    TypeDescriptorImpl()
    {
        nativeDescriptor_ = std::make_shared<TypeDescriptor>();
    }

    explicit TypeDescriptorImpl(std::shared_ptr<TypeDescriptor> descriptor) : nativeDescriptor_(descriptor){}

    ::taihe::string GetTypeId() const;
    ::taihe::array<::taihe::string> GetBelongingToTypes() const;
    ::taihe::string GetDescription() const;
    ::taihe::string GetReferenceURL() const;
    ::taihe::string GetIconFile() const;
    ::taihe::array<::taihe::string> GetFilenameExtensions() const;
    ::taihe::array<::taihe::string> GetMimeTypes() const;
    bool BelongsTo(::taihe::string_view type) const;
    bool IsLowerLevelType(::taihe::string_view type) const;
    bool IsHigherLevelType(::taihe::string_view type) const;
    bool Equals(::ohos::data::uniformTypeDescriptor::weak::TypeDescriptor other) const;
    void SetTypeId(::taihe::string_view value);
    void SetBelongingToTypes(const ::taihe::array<::taihe::string>& value);
    void SetDescription(::taihe::string_view value);
    void SetReferenceURL(::taihe::string_view value);
    void SetIconFile(::taihe::string_view value);
    void SetFilenameExtensions(const ::taihe::array<::taihe::string>& value);
    void SetMimeTypes(const ::taihe::array<::taihe::string>& value);
};
} // namespace UDMF
} // namespace OHOS
#endif // UDMF_TYPE_DESCRIPTOR_TAIHE_H