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
#define LOG_TAG "UDMF_TYPE_DESCRIPTOR_TAIHE"

#include "type_descriptor_taihe.h"
#include <string>
#include <vector>
#include <set>
#include "hilog_wrapper.h"
#include "logger.h"
#include "napi_error_utils.h"
#include "taihe_common_utils.h"
#include "taihe/runtime.hpp"
#include "utd_client.h"
#include "utd_common.h"
#include "ohos.data.uniformTypeDescriptor.impl.hpp"
#include "ohos.data.uniformTypeDescriptor.proj.hpp"
#include "stdexcept"

using namespace taihe;
using namespace ohos::data::uniformTypeDescriptor;
constexpr size_t MAX_BELONGS_LEN = 1024;

namespace OHOS {
namespace UDMF {

    ::taihe::string TypeDescriptorImpl::GetTypeId() const
    {
        if (!nativeDescriptor_) {
            LOG_ERROR(UDMF_ANI, "nativeDescriptor_ is null in GetTypeId");
            return ::taihe::string("");
        }
        return ::taihe::string(nativeDescriptor_->GetTypeId());
    }

    void TypeDescriptorImpl::SetTypeId(::taihe::string_view value)
    {
        std::string typeId = std::string(value);
        if (nativeDescriptor_) {
            nativeDescriptor_->SetTypeId(typeId);
        }
    }

    ::taihe::array<::taihe::string> TypeDescriptorImpl::GetBelongingToTypes() const
    {
        if (!nativeDescriptor_) {
            LOG_ERROR(UDMF_ANI, "nativeDescriptor_ is null in GetBelongingToTypes");
            return {};
        }
        const std::vector<std::string>& belongingToTypes = nativeDescriptor_->GetBelongingToTypes();
        return ConvertStringVectorToTaiheArray(belongingToTypes);
    }

    void TypeDescriptorImpl::SetBelongingToTypes(const ::taihe::array<::taihe::string>& value)
    {
        if (value.size() > MAX_BELONGS_LEN) {
            LOG_ERROR(UDMF_ANI, "SetBelongingToTypes: array size %zu exceeds maximum limit %zu",
                value.size(), MAX_BELONGS_LEN);
            taihe::set_business_error(E_INVALID_PARAMETERS, "array size exceeds maximum limit");
            return;
        }
        std::vector<std::string> belongingToTypes;
        belongingToTypes.clear();
        for (size_t i = 0; i < value.size(); ++i) {
            belongingToTypes.emplace_back(std::string(value[i]));
        }
        if (nativeDescriptor_) {
            nativeDescriptor_->SetBelongingToTypes(belongingToTypes);
        }
    }

    ::taihe::string TypeDescriptorImpl::GetDescription() const
    {
        if (!nativeDescriptor_) {
            LOG_ERROR(UDMF_ANI, "nativeDescriptor_ is null in GetDescription");
            return ::taihe::string("");
        }
        return ::taihe::string(nativeDescriptor_->GetDescription());
    }

    void TypeDescriptorImpl::SetDescription(::taihe::string_view value)
    {
        std::string description = std::string(value);
        if (nativeDescriptor_) {
            nativeDescriptor_->SetDescription(description);
        }
    }

    ::taihe::string TypeDescriptorImpl::GetReferenceURL() const
    {
        if (!nativeDescriptor_) {
            LOG_ERROR(UDMF_ANI, "nativeDescriptor_ is null in GetReferenceURL");
            return ::taihe::string("");
        }
        return ::taihe::string(nativeDescriptor_->GetReferenceURL());
    }

    void TypeDescriptorImpl::SetReferenceURL(::taihe::string_view value)
    {
        std::string referenceURL = std::string(value);
        if (nativeDescriptor_) {
            nativeDescriptor_->SetReferenceURL(referenceURL);
        }
    }

    ::taihe::string TypeDescriptorImpl::GetIconFile() const
    {
        if (!nativeDescriptor_) {
            LOG_ERROR(UDMF_ANI, "nativeDescriptor_ is null in GetIconFile");
            return ::taihe::string("");
        }
        return ::taihe::string(nativeDescriptor_->GetIconFile());
    }

    void TypeDescriptorImpl::SetIconFile(::taihe::string_view value)
    {
        std::string iconFile = std::string(value);
        if (nativeDescriptor_) {
            nativeDescriptor_->SetIconFile(iconFile);
        }
    }

    ::taihe::array<::taihe::string> TypeDescriptorImpl::GetFilenameExtensions() const
    {
        if (!nativeDescriptor_) {
            LOG_ERROR(UDMF_ANI, "nativeDescriptor_ is null in GetFilenameExtensions");
            return {};
        }
        const std::vector<std::string>& filenameExtensions = nativeDescriptor_->GetFilenameExtensions();
        return ConvertStringVectorToTaiheArray(filenameExtensions);
    }

    void TypeDescriptorImpl::SetFilenameExtensions(const ::taihe::array<::taihe::string>& value)
    {
        if (value.size() > MAX_BELONGS_LEN) {
            LOG_ERROR(UDMF_ANI, "SetFilenameExtensions: array size %zu exceeds maximum limit %zu",
                value.size(), MAX_BELONGS_LEN);
            taihe::set_business_error(E_INVALID_PARAMETERS, "array size exceeds maximum limit");
            return;
        }
        std::vector<std::string> filenameExtensions;
        filenameExtensions.clear();
        for (size_t i = 0; i < value.size(); ++i) {
            filenameExtensions.emplace_back(std::string(value[i]));
        }
        if (nativeDescriptor_) {
            nativeDescriptor_->SetFilenameExtensions(filenameExtensions);
        }
    }

    ::taihe::array<::taihe::string> TypeDescriptorImpl::GetMimeTypes() const
    {
        if (!nativeDescriptor_) {
            LOG_ERROR(UDMF_ANI, "nativeDescriptor_ is null in GetMimeTypes");
            return {};
        }
        const std::vector<std::string>& mimeTypes = nativeDescriptor_->GetMimeTypes();
        return ConvertStringVectorToTaiheArray(mimeTypes);
    }

    void TypeDescriptorImpl::SetMimeTypes(const ::taihe::array<::taihe::string>& value)
    {
        if (value.size() > MAX_BELONGS_LEN) {
            LOG_ERROR(UDMF_ANI, "SetMimeTypes: array size %zu exceeds maximum limit %zu",
                value.size(), MAX_BELONGS_LEN);
            taihe::set_business_error(E_INVALID_PARAMETERS, "array size exceeds maximum limit");
            return;
        }
        std::vector<std::string> mimeTypes;
        mimeTypes.clear();
        for (size_t i = 0; i < value.size(); ++i) {
            mimeTypes.emplace_back(std::string(value[i]));
        }
        if (nativeDescriptor_) {
            nativeDescriptor_->SetMimeTypes(mimeTypes);
        }
    }

    bool TypeDescriptorImpl::BelongsTo(::taihe::string_view type) const
    {
        if (type.empty()) {
            LOG_ERROR(UDMF_ANI, "Type string is empty");
            taihe::set_business_error(E_INVALID_PARAMETERS, "type is empty");
            return false;
        }
        if (!nativeDescriptor_) {
            LOG_ERROR(UDMF_ANI, "nativeDescriptor_ is null in BelongsTo");
            taihe::set_business_error(E_INVALID_PARAMETERS, "nativeDescriptor_ is null");
            return false;
        }
        bool checkRet = false;
        Status status = nativeDescriptor_->BelongsTo(std::string(type), checkRet);
        if (status != E_OK) {
            auto errorMsg = GetErrorCode(status);
            NapiErrorCode napiError;
            if (errorMsg.has_value()) {
                napiError = errorMsg.value();
            } else {
                napiError.jsCode = PARAMETERSERROR;
                napiError.message = "invalid arguments!";
            }
            set_business_error(napiError.jsCode, napiError.message);
            return false;
        }
        return checkRet;
    }

    bool TypeDescriptorImpl::IsLowerLevelType(::taihe::string_view type) const
    {
        if (type.empty()) {
            LOG_ERROR(UDMF_ANI, "Type string is empty");
            taihe::set_business_error(E_INVALID_PARAMETERS, "type is empty");
            return false;
        }
        if (!nativeDescriptor_) {
            LOG_ERROR(UDMF_ANI, "nativeDescriptor_ is null in IsLowerLevelType");
            taihe::set_business_error(E_INVALID_PARAMETERS, "nativeDescriptor_ is null");
            return false;
        }
        bool checkRet = false;
        Status status = nativeDescriptor_->IsLowerLevelType(std::string(type), checkRet);
        if (status != E_OK) {
            auto errorMsg = GetErrorCode(status);
            NapiErrorCode napiError;
            if (errorMsg.has_value()) {
                napiError = errorMsg.value();
            } else {
                napiError.jsCode = PARAMETERSERROR;
                napiError.message = "invalid arguments!";
            }
            set_business_error(napiError.jsCode, napiError.message);
            return false;
        }
        return checkRet;
    }

    bool TypeDescriptorImpl::IsHigherLevelType(::taihe::string_view type) const
    {
        if (type.empty()) {
            LOG_ERROR(UDMF_ANI, "Type string is empty");
            taihe::set_business_error(E_INVALID_PARAMETERS, "type is empty");
            return false;
        }
        if (!nativeDescriptor_) {
            LOG_ERROR(UDMF_ANI, "nativeDescriptor_ is null in IsHigherLevelType");
            taihe::set_business_error(E_INVALID_PARAMETERS, "nativeDescriptor_ is null");
            return false;
        }
        bool checkRet = false;
        Status status = nativeDescriptor_->IsHigherLevelType(std::string(type), checkRet);
        if (status != E_OK) {
            auto errorMsg = GetErrorCode(status);
            NapiErrorCode napiError;
            if (errorMsg.has_value()) {
                napiError = errorMsg.value();
            } else {
                napiError.jsCode = PARAMETERSERROR;
                napiError.message = "invalid arguments!";
            }
            set_business_error(napiError.jsCode, napiError.message);
            return false;
        }
        return checkRet;
    }

    bool TypeDescriptorImpl::Equals(::ohos::data::uniformTypeDescriptor::weak::TypeDescriptor other) const
    {
        if (other.operator->() == nullptr || !nativeDescriptor_) {
            LOG_ERROR(UDMF_ANI, "[ERROR] TypeDescriptorImpl::Equals received nullptr for other parameter\n");
            return false;
        }
        std::string typeId = nativeDescriptor_->GetTypeId();
        bool ret = (typeId == other->GetTypeId());
        return ret;
    }
};

} // namespace OHOS