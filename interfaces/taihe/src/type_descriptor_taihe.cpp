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
#include <mutex>
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

namespace OHOS {
namespace UDMF {

    ::taihe::string TypeDescriptorImpl::GetTypeId() const
    {
        std::lock_guard<std::mutex> lock(mtx_);
        if (!nativeDescriptor_) {
            LOG_ERROR(UDMF_ANI, "nativeDescriptor_ is null in GetTypeId");
            return ::taihe::string("");
        }
        return ::taihe::string(nativeDescriptor_->GetTypeId().c_str());
    }

    void TypeDescriptorImpl::SetTypeId(::taihe::string_view value)
    {
        std::lock_guard<std::mutex> lock(mtx_);
        std::string typeId = std::string(value);
        if (nativeDescriptor_) {
            nativeDescriptor_->SetTypeId(typeId);
        }
    }

    ::taihe::array<::taihe::string> TypeDescriptorImpl::GetBelongingToTypes() const
    {
        std::lock_guard<std::mutex> lock(mtx_);
        if (!nativeDescriptor_) {
            LOG_ERROR(UDMF_ANI, "nativeDescriptor_ is null in GetBelongingToTypes");
            return ::taihe::array<::taihe::string>(0, ::taihe::string(""));
        }
        std::vector<std::string> belongingToTypes = nativeDescriptor_->GetBelongingToTypes();
        ::taihe::array<::taihe::string> result(belongingToTypes.size(), ::taihe::string(""));
        for (size_t i = 0; i < belongingToTypes.size(); ++i) {
            result[i] = ::taihe::string(belongingToTypes[i].c_str());
        }
        return result;
    }

    void TypeDescriptorImpl::SetBelongingToTypes(const ::taihe::array<::taihe::string>& value)
    {
        std::lock_guard<std::mutex> lock(mtx_);
        std::vector<std::string> belongingToTypes;
        belongingToTypes.clear();
        for (size_t i = 0; i < value.size(); ++i) {
            belongingToTypes.push_back(std::string(value[i]));
        }
        if (nativeDescriptor_) {
            nativeDescriptor_->SetBelongingToTypes(belongingToTypes);
        }
    }

    ::taihe::string TypeDescriptorImpl::GetDescription() const
    {
        std::lock_guard<std::mutex> lock(mtx_);
        if (!nativeDescriptor_) {
            LOG_ERROR(UDMF_ANI, "nativeDescriptor_ is null in GetDescription");
            return ::taihe::string("");
        }
        return ::taihe::string(nativeDescriptor_->GetDescription().c_str());
    }

    void TypeDescriptorImpl::SetDescription(::taihe::string_view value)
    {
        std::lock_guard<std::mutex> lock(mtx_);
        std::string description = std::string(value);
        if (nativeDescriptor_) {
            nativeDescriptor_->SetDescription(description);
        }
    }

    ::taihe::string TypeDescriptorImpl::GetReferenceURL() const
    {
        std::lock_guard<std::mutex> lock(mtx_);
        if (!nativeDescriptor_) {
            LOG_ERROR(UDMF_ANI, "nativeDescriptor_ is null in GetReferenceURL");
            return ::taihe::string("");
        }
        return ::taihe::string(nativeDescriptor_->GetReferenceURL().c_str());
    }

    void TypeDescriptorImpl::SetReferenceURL(::taihe::string_view value)
    {
        std::lock_guard<std::mutex> lock(mtx_);
        std::string referenceURL = std::string(value);
        if (nativeDescriptor_) {
            nativeDescriptor_->SetReferenceURL(referenceURL);
        }
    }

    ::taihe::string TypeDescriptorImpl::GetIconFile() const
    {
        std::lock_guard<std::mutex> lock(mtx_);
        if (!nativeDescriptor_) {
            LOG_ERROR(UDMF_ANI, "nativeDescriptor_ is null in GetIconFile");
            return ::taihe::string("");
        }
        return ::taihe::string(nativeDescriptor_->GetIconFile().c_str());
    }

    void TypeDescriptorImpl::SetIconFile(::taihe::string_view value)
    {
        std::lock_guard<std::mutex> lock(mtx_);
        std::string iconFile = std::string(value);
        if (nativeDescriptor_) {
            nativeDescriptor_->SetIconFile(iconFile);
        }
    }

    ::taihe::array<::taihe::string> TypeDescriptorImpl::GetFilenameExtensions() const
    {
        std::lock_guard<std::mutex> lock(mtx_);
        if (!nativeDescriptor_) {
            LOG_ERROR(UDMF_ANI, "nativeDescriptor_ is null in GetFilenameExtensions");
            return ::taihe::array<::taihe::string>(0, ::taihe::string(""));
        }
        std::vector<std::string> filenameExtensions = nativeDescriptor_->GetFilenameExtensions();
        ::taihe::array<::taihe::string> result(filenameExtensions.size(), ::taihe::string(""));
        for (size_t i = 0; i < filenameExtensions.size(); ++i) {
            result[i] = ::taihe::string(filenameExtensions[i].c_str());
        }
        return result;
    }

    void TypeDescriptorImpl::SetFilenameExtensions(const ::taihe::array<::taihe::string>& value)
    {
        std::lock_guard<std::mutex> lock(mtx_);
        std::vector<std::string> filenameExtensions;
        filenameExtensions.clear();
        for (size_t i = 0; i < value.size(); ++i) {
            filenameExtensions.push_back(std::string(value[i]));
        }
        if (nativeDescriptor_) {
            nativeDescriptor_->SetFilenameExtensions(filenameExtensions);
        }
    }

    ::taihe::array<::taihe::string> TypeDescriptorImpl::GetMimeTypes() const
    {
        std::lock_guard<std::mutex> lock(mtx_);
        if (!nativeDescriptor_) {
            LOG_ERROR(UDMF_ANI, "nativeDescriptor_ is null in GetMimeTypes");
            return ::taihe::array<::taihe::string>(0, ::taihe::string(""));
        }
        std::vector<std::string> mimeTypes = nativeDescriptor_->GetMimeTypes();
        ::taihe::array<::taihe::string> result(mimeTypes.size(), ::taihe::string(""));
        for (size_t i = 0; i < mimeTypes.size(); ++i) {
            result[i] = ::taihe::string(mimeTypes[i].c_str());
        }
        return result;
    }

    void TypeDescriptorImpl::SetMimeTypes(const ::taihe::array<::taihe::string>& value)
    {
        std::lock_guard<std::mutex> lock(mtx_);
        std::vector<std::string> mimeTypes;
        mimeTypes.clear();
        for (size_t i = 0; i < value.size(); ++i) {
            mimeTypes.push_back(std::string(value[i]));
        }
        if (nativeDescriptor_) {
            nativeDescriptor_->SetMimeTypes(mimeTypes);
        }
    }

    bool TypeDescriptorImpl::BelongsTo(::taihe::string_view type) const
    {
        std::lock_guard<std::mutex> lock(mtx_);
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
                napiError.message = "Parameter error.";
            }
            set_business_error(napiError.jsCode, napiError.message);
            return false;
        }
        return checkRet;
    }

    bool TypeDescriptorImpl::IsLowerLevelType(::taihe::string_view type) const
    {
        std::lock_guard<std::mutex> lock(mtx_);
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
                napiError.message = "Parameter error.";
            }
            set_business_error(napiError.jsCode, napiError.message);
            return false;
        }
        return checkRet;
    }

    bool TypeDescriptorImpl::IsHigherLevelType(::taihe::string_view type) const
    {
        std::lock_guard<std::mutex> lock(mtx_);
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
                napiError.message = "Parameter error.";
            }
            set_business_error(napiError.jsCode, napiError.message);
            return false;
        }
        return checkRet;
    }

    bool TypeDescriptorImpl::Equals(::ohos::data::uniformTypeDescriptor::weak::TypeDescriptor other) const
    {
        std::lock_guard<std::mutex> lock(mtx_);
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