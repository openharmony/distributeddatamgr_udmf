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
#define LOG_TAG "UDMF_TYPE_DESCRIPTOR"

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
#include "type_descriptor_taihe.h"
#include "utd_client.h"
#include "utd_common.h"


using namespace taihe;
using namespace ohos::data::uniformTypeDescriptor;
constexpr size_t MAX_BELONGS_LEN = 1024;

namespace OHOS {
namespace UDMF {

::taihe::array<::taihe::string> GetUniformDataTypesByMIMEType(::taihe::string_view mimeType,
                                                              ::taihe::optional_view<::taihe::string> belongsTo)
{
    std::string isMime(mimeType);
    std::string isBelongs;
    std::vector<std::string> typeIds;
    if (belongsTo.has_value()) {
        auto val = belongsTo.value();
        if (val.size() > MAX_BELONGS_LEN) {
            set_business_error(PARAMETERSERROR, "Input string too long");
            return {};
        }
        isBelongs = std::string(val.data(), val.size());
    } else {
        isBelongs = std::string(DEFAULT_TYPE_ID);
    }
    Status status = UtdClient::GetInstance()
        .GetUniformDataTypesByMIMEType(isMime, typeIds, isBelongs);
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
        return {};
    }
    return ConvertStringVectorToTaiheArray(typeIds);
}

::taihe::array<::taihe::string> GetUniformDataTypesByFilenameExtension(
    ::taihe::string_view filenameExtension,
    ::taihe::optional_view<::taihe::string> belongsTo)
{
    std::string fileName(filenameExtension);
    std::string isBelongs;
    std::vector<std::string> typeIds;
    if (belongsTo.has_value()) {
        auto val = belongsTo.value();
        if (val.size() > MAX_BELONGS_LEN) {
            set_business_error(PARAMETERSERROR, "Input string too long");
            return {};
        }
        isBelongs = std::string(val.data(), val.size());
    } else {
        isBelongs = std::string(DEFAULT_TYPE_ID);
    }
    Status status = UtdClient::GetInstance()
        .GetUniformDataTypesByFilenameExtension(fileName, typeIds, isBelongs);
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
        return {};
    }
    return ConvertStringVectorToTaiheArray(typeIds);
}

::taihe::string GetUniformDataTypeByMIMEType(::taihe::string_view mimeType,
    ::taihe::optional_view<::taihe::string> belongsTo)
{
    std::string isMime(mimeType);
    std::string typeId;
    auto status = E_OK;
    if (belongsTo.has_value()) {
        if (belongsTo.value().empty()) {
            set_business_error(PARAMETERSERROR, "Parameter error: parameter belongsTo type must be string");   
        } else {
            std::string isBelongs(belongsTo.value());
            status = UtdClient::GetInstance().GetUniformDataTypeByMIMEType(isMime, typeId, isBelongs);
        }
    } else {
        status = UtdClient::GetInstance().GetUniformDataTypeByMIMEType(isMime, typeId);
    }
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
    if (belongsTo.has_value()) {
        if (belongsTo.value().empty()) {
            set_business_error(PARAMETERSERROR, "Parameter error: parameter belongsTo type must be string");   
        } else {
            std::string belongs(belongsTo.value());
            status = UtdClient::GetInstance().GetUniformDataTypeByFilenameExtension(fileName, typeId, belongs);
        }
    } else {
        status = UtdClient::GetInstance().GetUniformDataTypeByFilenameExtension(fileName, typeId);
    }
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
            napiError.message = "invalid arguments!";
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
