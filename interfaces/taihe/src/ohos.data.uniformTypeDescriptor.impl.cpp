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

#include "error_code.h"
#include "hilog_wrapper.h"
#include "logger.h"
#include "napi_error_utils.h"
#include "napi/native_node_api.h"
#include "ohos.data.uniformTypeDescriptor.impl.hpp"
#include "ohos.data.uniformTypeDescriptor.proj.hpp"
#include "stdexcept"
#include "taihe_common_utils.h"
#include "taihe/runtime.hpp"
#include "type_descriptor.h"
#include "utd_client.h"
#include "utd_common.h"


using namespace taihe;
using namespace ohos::data::uniformTypeDescriptor;

namespace OHOS {
namespace UDMF {

class TypeDescriptorImpl {
private:
    std::shared_ptr<TypeDescriptor> nativeDescriptor_;

public:
    TypeDescriptorImpl()
    {
        TypeDescriptorCfg config;
        nativeDescriptor_ = std::make_shared<TypeDescriptor>(config);
    }

    explicit TypeDescriptorImpl(std::shared_ptr<TypeDescriptor> descriptor) : nativeDescriptor_(descriptor)
    {
        if (nativeDescriptor_ == nullptr) {
            TypeDescriptorCfg config;
            nativeDescriptor_ = std::make_shared<TypeDescriptor>(config);
        }
    }

    ::taihe::string GetTypeId() const
{
    if (!nativeDescriptor_) {
        LOG_ERROR(UDMF_ANI, "nativeDescriptor_ is null in GetTypeId");
        return ::taihe::string("");
    }
    return ::taihe::string(nativeDescriptor_->GetTypeId().c_str());
}

    void SetTypeId(::taihe::string_view value)
    {
        std::string typeId = std::string(value);
        if (nativeDescriptor_) {
            nativeDescriptor_->SetTypeId(typeId);
        }
    }

    ::taihe::array<::taihe::string> GetBelongingToTypes() const
    {
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

    void SetBelongingToTypes(const ::taihe::array<::taihe::string>& value)
    {
        std::vector<std::string> belongingToTypes;
        belongingToTypes.clear();
        for (size_t i = 0; i < value.size(); ++i) {
            belongingToTypes.push_back(std::string(value[i]));
        }
        if (nativeDescriptor_) {
            nativeDescriptor_->SetBelongingToTypes(belongingToTypes);
        }
    }

    ::taihe::string GetDescription() const
    {
        if (!nativeDescriptor_) {
            LOG_ERROR(UDMF_ANI, "nativeDescriptor_ is null in GetDescription");
            return ::taihe::string("");
        }
        return ::taihe::string(nativeDescriptor_->GetDescription().c_str());
    }

    void SetDescription(::taihe::string_view value)
    {
        std::string description = std::string(value);
        if (nativeDescriptor_) {
            nativeDescriptor_->SetDescription(description);
        }
    }

    ::taihe::string GetReferenceURL() const
    {
        if (!nativeDescriptor_) {
            LOG_ERROR(UDMF_ANI, "nativeDescriptor_ is null in GetReferenceURL");
            return ::taihe::string("");
        }
        return ::taihe::string(nativeDescriptor_->GetReferenceURL().c_str());
    }

    void SetReferenceURL(::taihe::string_view value)
    {
        std::string referenceURL = std::string(value);
        if (nativeDescriptor_) {
            nativeDescriptor_->SetReferenceURL(referenceURL);
        }
    }

    ::taihe::string GetIconFile() const
    {
        if (!nativeDescriptor_) {
            LOG_ERROR(UDMF_ANI, "nativeDescriptor_ is null in GetIconFile");
            return ::taihe::string("");
        }
        return ::taihe::string(nativeDescriptor_->GetIconFile().c_str());
    }

    void SetIconFile(::taihe::string_view value)
    {
        std::string iconFile = std::string(value);
        if (nativeDescriptor_) {
            nativeDescriptor_->SetIconFile(iconFile);
        }
    }

    ::taihe::array<::taihe::string> GetFilenameExtensions() const
    {
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

    void SetFilenameExtensions(const ::taihe::array<::taihe::string>& value)
    {
        std::vector<std::string> filenameExtensions;
        filenameExtensions.clear();
        for (size_t i = 0; i < value.size(); ++i) {
            filenameExtensions.push_back(std::string(value[i]));
        }
        if (nativeDescriptor_) {
            nativeDescriptor_->SetFilenameExtensions(filenameExtensions);
        }
    }

    ::taihe::array<::taihe::string> GetMimeTypes() const
    {
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

    void SetMimeTypes(const ::taihe::array<::taihe::string>& value)
    {
        std::vector<std::string> mimeTypes;
        mimeTypes.clear();
        for (size_t i = 0; i < value.size(); ++i) {
            mimeTypes.push_back(std::string(value[i]));
        }
        if (nativeDescriptor_) {
            nativeDescriptor_->SetMimeTypes(mimeTypes);
        }
    }

    bool BelongsTo(::taihe::string_view type) const;
    bool IsLowerLevelType(::taihe::string_view type) const;
    bool IsHigherLevelType(::taihe::string_view type) const;
    bool Equals(::ohos::data::uniformTypeDescriptor::weak::TypeDescriptor other) const;
};

bool TypeDescriptorImpl::BelongsTo(::taihe::string_view type) const
{
    if (type.empty()) {
        LOG_ERROR(UDMF_ANI, "Type string is empty");
        taihe::set_business_error(E_INVALID_PARAMETERS, "type is empty");
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
    if (type.empty()) {
        LOG_ERROR(UDMF_ANI, "Type string is empty");
        taihe::set_business_error(E_INVALID_PARAMETERS, "type is empty");
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
    if (type.empty()) {
        LOG_ERROR(UDMF_ANI, "Type string is empty");
        taihe::set_business_error(E_INVALID_PARAMETERS, "type is empty");
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
    if (other.operator->() == nullptr || !nativeDescriptor_) {
        LOG_ERROR(UDMF_ANI, "[ERROR] TypeDescriptorImpl::Equals received nullptr for other parameter\n");
        return false;
    }
    std::string typeId = nativeDescriptor_->GetTypeId();
    bool ret = (typeId == other->GetTypeId());
    return ret;
}

::taihe::array<::taihe::string> GetUniformDataTypesByMIMEType(::taihe::string_view mimeType,
                                                              ::taihe::optional_view<::taihe::string> belongsTo)
{
    std::string isMime(mimeType);
    std::string isBelongs = belongsTo.has_value()
                                ? std::string(belongsTo.value().data(), belongsTo.value().size())
                                : std::string(DEFAULT_TYPE_ID);

    std::vector<std::string> typeIds;
    Status status = UtdClient::GetInstance()
        .GetUniformDataTypesByMIMEType(isMime, typeIds, isBelongs);
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
        return taihe::array<::taihe::string>(0, taihe::string(""));
    }
    taihe::array<::taihe::string> result(typeIds.size(), taihe::string(""));
    for (size_t i = 0; i < typeIds.size(); ++i) {
        result[i] = taihe::string(typeIds[i].c_str());
    }
    return result;
}

::taihe::array<::taihe::string> GetUniformDataTypesByFilenameExtension(
    ::taihe::string_view filenameExtension,
    ::taihe::optional_view<::taihe::string> belongsTo)
{
    std::string fileName(filenameExtension);
    std::string isBelongs = belongsTo.has_value()
                                ? std::string(belongsTo.value().data(), belongsTo.value().size())
                                : std::string(DEFAULT_TYPE_ID);
    std::vector<std::string> typeIds;
    Status status = UtdClient::GetInstance()
        .GetUniformDataTypesByFilenameExtension(fileName, typeIds, isBelongs);
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
        return taihe::array<::taihe::string>(0, taihe::string(""));
    }
    taihe::array<::taihe::string> result(typeIds.size(), taihe::string(""));
    for (size_t i = 0; i < typeIds.size(); ++i) {
        result[i] = taihe::string(typeIds[i].c_str());
    }
    return result;
}

::taihe::string GetUniformDataTypeByMIMEType(::taihe::string_view mimeType,
    ::taihe::optional_view<::taihe::string> belongsTo)
{
    std::string isMime(mimeType);
    std::string typeId;
    auto status = E_OK;
    if (!belongsTo.has_value() || belongsTo.value().empty()) {
        status = UtdClient::GetInstance().GetUniformDataTypeByMIMEType(isMime, typeId);
    } else {
        std::string isBelongs(belongsTo.value());
        status = UtdClient::GetInstance().GetUniformDataTypeByMIMEType(isMime, typeId, isBelongs);
    }
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
        return "";
    }
    return typeId;
}

::taihe::string GetUniformDataTypeByFilenameExtension(const ::taihe::string_view &filenameExtension,
    ::taihe::optional_view<::taihe::string> belongsTo)
{
    std::string fileName(filenameExtension);
    std::string typeId;
    auto status = E_OK;
    if (!belongsTo.has_value() || belongsTo.value().empty()) {
        status = UtdClient::GetInstance().GetUniformDataTypeByFilenameExtension(fileName, typeId);
    } else {
        std::string belongs(belongsTo.value());
        status = UtdClient::GetInstance().GetUniformDataTypeByFilenameExtension(fileName, typeId, belongs);
    }
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
        return "";
    }
    return typeId;
}

::ohos::data::uniformTypeDescriptor::TypeDescriptorUnion GetTypeDescriptor(::taihe::string_view typeId)
{
    std::string nativeTypeId(typeId);
    std::shared_ptr<TypeDescriptor> nativeDesc;
    Status status = UtdClient::GetInstance().GetTypeDescriptor(nativeTypeId, nativeDesc);
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
        return ::ohos::data::uniformTypeDescriptor::TypeDescriptorUnion::make_empty();
    }
    if (nativeDesc == nullptr) {
        set_business_error(PARAMETERSERROR, "Type descriptor not found for the specified nativeTypeId.");
        return ::ohos::data::uniformTypeDescriptor::TypeDescriptorUnion::make_empty();
    }
    auto holder = taihe::make_holder<TypeDescriptorImpl,
        ::ohos::data::uniformTypeDescriptor::TypeDescriptor>(nativeDesc);
    return ::ohos::data::uniformTypeDescriptor::TypeDescriptorUnion::make_desc(std::move(holder));
}
} // namespace UDMF
} // namespace OHOS

// NOLINTBEGIN
TH_EXPORT_CPP_API_GetUniformDataTypesByMIMEType(OHOS::UDMF::GetUniformDataTypesByMIMEType);
TH_EXPORT_CPP_API_GetUniformDataTypesByFilenameExtension(OHOS::UDMF::GetUniformDataTypesByFilenameExtension);
TH_EXPORT_CPP_API_GetUniformDataTypeByMIMEType(OHOS::UDMF::GetUniformDataTypeByMIMEType);
TH_EXPORT_CPP_API_getUniformDataTypeByFilenameExtension(OHOS::UDMF::GetUniformDataTypeByFilenameExtension);
TH_EXPORT_CPP_API_GetTypeDescriptor(OHOS::UDMF::GetTypeDescriptor);
// NOLINTEND
