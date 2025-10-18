/*
* Copyright (c) 2023 Huawei Device Co., Ltd.
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
#define LOG_TAG "UniformTypeDescriptorNapi"
#include "uniform_type_descriptor_napi.h"
#include "napi_data_utils.h"
#include "utd_client.h"

namespace OHOS {
namespace UDMF {

napi_value UniformTypeDescriptorNapi::UniformTypeDescriptorInit(napi_env env, napi_value exports)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "UniformTypeDescriptorNapi");
    napi_value uniformDataType = CreateUniformDataType(env);
    napi_property_descriptor desc[] = {
        DECLARE_NAPI_PROPERTY("UniformDataType", uniformDataType),
        DECLARE_NAPI_FUNCTION("getTypeDescriptor", GetTypeDescriptor),
        DECLARE_NAPI_FUNCTION("getUniformDataTypeByFilenameExtension", GetUniformDataTypeByFilenameExtension),
        DECLARE_NAPI_FUNCTION("getUniformDataTypeByMIMEType", GetUniformDataTypeByMIMEType),
        DECLARE_NAPI_FUNCTION("getUniformDataTypesByFilenameExtension", GetMultiUniformDataTypesByFilenameExtension),
        DECLARE_NAPI_FUNCTION("getUniformDataTypesByMIMEType", GetMultiUniformDataTypesByMIMEType),
        DECLARE_NAPI_FUNCTION("registerTypeDescriptors", RegisterTypeDescriptors),
        DECLARE_NAPI_FUNCTION("unregisterTypeDescriptors", UnregisterTypeDescriptors),
    };

    NAPI_CALL(env, napi_define_properties(env, exports, sizeof(desc) / sizeof(desc[0]), desc));
    return exports;
}

napi_value UniformTypeDescriptorNapi::CreateUniformDataType(napi_env env)
{
    napi_value uniformDataType = nullptr;
    napi_create_object(env, &uniformDataType);
    auto allUtdTypes = UtdUtils::GetUtdTypes();
    for (auto utdType : allUtdTypes) {
        SetNamedProperty(env, uniformDataType, utdType.UtdEnumName, utdType.UtdId);
    }
    napi_object_freeze(env, uniformDataType);
    return uniformDataType;
}

napi_status UniformTypeDescriptorNapi::SetNamedProperty(napi_env env, napi_value &obj, const std::string &name,
    const std::string &value)
{
    napi_value property = nullptr;
    napi_status status = NapiDataUtils::SetValue(env, value, property);
    ASSERT(status == napi_ok, "string to napi_value failed!", status);
    status = napi_set_named_property(env, obj, name.c_str(), property);
    ASSERT(status == napi_ok, "napi_set_named_property failed!", status);
    return status;
}

napi_value UniformTypeDescriptorNapi::GetTypeDescriptor(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "GetTypeDescriptor is called!");
    std::string typeId;
    auto ctxt = std::make_shared<ContextBase>();
    auto input = [env, ctxt, &typeId](size_t argc, napi_value* argv) {
        LOG_DEBUG(UDMF_KITS_NAPI, "GetTypeDescriptor, argc = %{public}zu !", argc);
        // required 1 arguments : typeId
        ASSERT_BUSINESS_ERR(ctxt, argc >= 1,
            Status::E_INVALID_PARAMETERS, "Parameter error: Mandatory parameters are left unspecified");
        ctxt->status = NapiDataUtils::GetValue(env, argv[0], typeId);
        ASSERT_BUSINESS_ERR(ctxt, ctxt->status == napi_ok, E_INVALID_PARAMETERS,
            "Parameter error: parameter type type must be string");
    };
    ctxt->GetCbInfoSync(env, info, input);
    ASSERT_NULL(!ctxt->isThrowError, "GetTypeDescriptor Exit");
    std::shared_ptr<TypeDescriptor> descriptor;
    auto status = UtdClient::GetInstance().GetTypeDescriptor(typeId, descriptor);
    ASSERT_ERR(ctxt->env, status == E_OK, status, "invalid arguments!");
    TypeDescriptorNapi::NewInstance(env, descriptor, ctxt->output);
    if (descriptor == nullptr) { // descriptor not found, not exception, need return null object.
        napi_get_null(env, &ctxt->output);
    }
    return ctxt->output;
}

napi_value UniformTypeDescriptorNapi::GetUniformDataTypeByFilenameExtension(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "GetUniformDataTypeByFilenameExtension is called!");
    std::string filenameExtension;
    std::string belongsTo;
    auto ctxt = std::make_shared<ContextBase>();
    auto input = [env, ctxt, &filenameExtension, &belongsTo](size_t argc, napi_value* argv) {
        LOG_DEBUG(UDMF_KITS_NAPI, "get utd type by fileExtention, argc = %{public}zu !", argc);
        // required 1 arguments : typeId
        ASSERT_BUSINESS_ERR(ctxt, argc >= 1,
            Status::E_INVALID_PARAMETERS, "Parameter error: Mandatory parameters are left unspecified");
        ctxt->status = NapiDataUtils::GetValue(env, argv[0], filenameExtension);
        ASSERT_BUSINESS_ERR(ctxt, ctxt->status == napi_ok, E_INVALID_PARAMETERS,
            "Parameter error: parameter filenameExtension type must be string");
        if (argc > 1) {
            ctxt->status = NapiDataUtils::GetValue(env, argv[1], belongsTo);
            ASSERT_BUSINESS_ERR(ctxt, ctxt->status == napi_ok && !belongsTo.empty(), E_INVALID_PARAMETERS,
                "Parameter error: parameter belongsTo type must be string");
        }
    };
    ctxt->GetCbInfoSync(env, info, input);
    ASSERT_NULL(!ctxt->isThrowError, "GetUniformDataTypeByFilenameExtension Exit");
    std::string typeId;
    auto status = E_OK;
    if (belongsTo.empty()) {
        status = UtdClient::GetInstance().GetUniformDataTypeByFilenameExtension(filenameExtension, typeId);
    } else {
        status = UtdClient::GetInstance().GetUniformDataTypeByFilenameExtension(filenameExtension, typeId, belongsTo);
    }
    ASSERT_ERR(ctxt->env, status == E_OK, status, "invalid arguments!");
    if (!typeId.empty()) {
        NapiDataUtils::SetValue(env, typeId, ctxt->output);
    } else {
        napi_get_null(env, &ctxt->output);
    }
    return ctxt->output;
}

napi_value UniformTypeDescriptorNapi::GetUniformDataTypeByMIMEType(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "GetUniformDataTypeByMIMEType is called!");
    std::string mimeType;
    std::string belongsTo;
    auto ctxt = std::make_shared<ContextBase>();
    auto input = [env, ctxt, &mimeType, &belongsTo](size_t argc, napi_value* argv) {
        LOG_DEBUG(UDMF_KITS_NAPI, "get utd type by MIMEType, argc = %{public}zu !", argc);
        // required 1 arguments : typeId
        ASSERT_BUSINESS_ERR(ctxt, argc >= 1,
            Status::E_INVALID_PARAMETERS, "Parameter error: Mandatory parameters are left unspecified");
        ctxt->status = NapiDataUtils::GetValue(env, argv[0], mimeType);
        ASSERT_BUSINESS_ERR(ctxt, ctxt->status == napi_ok, E_INVALID_PARAMETERS,
            "Parameter error: parameter mimeType type must be string");
        if (argc > 1) {
            ctxt->status = NapiDataUtils::GetValue(env, argv[1], belongsTo);
            ASSERT_BUSINESS_ERR(ctxt, ctxt->status == napi_ok && !belongsTo.empty(), E_INVALID_PARAMETERS,
                "Parameter error: parameter belongsTo type must be string");
        }
    };
    ctxt->GetCbInfoSync(env, info, input);
    ASSERT_NULL(!ctxt->isThrowError, "GetUniformDataTypeByMIMEType Exit");
    std::string typeId;
    auto status = E_OK;
    if (belongsTo.empty()) {
        status = UtdClient::GetInstance().GetUniformDataTypeByMIMEType(mimeType, typeId);
    } else {
        status = UtdClient::GetInstance().GetUniformDataTypeByMIMEType(mimeType, typeId, belongsTo);
    }
    ASSERT_ERR(ctxt->env, status == E_OK, status, "invalid arguments!");
    if (!typeId.empty()) {
        NapiDataUtils::SetValue(env, typeId, ctxt->output);
    } else {
        napi_get_null(env, &ctxt->output);
    }

    return ctxt->output;
}

napi_value UniformTypeDescriptorNapi::GetMultiUniformDataTypesByFilenameExtension(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "GetMultiUniformDataTypesByFilenameExtension is called!");
    std::string filenameExtension;
    std::string belongsTo;
    auto ctxt = std::make_shared<ContextBase>();
    auto input = [env, ctxt, &filenameExtension, &belongsTo](size_t argc, napi_value* argv) {
        LOG_DEBUG(UDMF_KITS_NAPI, "get utd types by fileExtention, argc = %{public}zu !", argc);
        // required 1 arguments : typeId
        ASSERT_BUSINESS_ERR(ctxt, argc >= 1,
            Status::E_INVALID_PARAMETERS, "Parameter error: Mandatory parameters are left unspecified");
        ctxt->status = NapiDataUtils::GetValue(env, argv[0], filenameExtension);
        ASSERT_BUSINESS_ERR(ctxt, ctxt->status == napi_ok, E_INVALID_PARAMETERS,
            "Parameter error: parameter filenameExtension type must be string");
        if (argc > 1) {
            ctxt->status = NapiDataUtils::GetValue(env, argv[1], belongsTo);
            ASSERT_BUSINESS_ERR(ctxt, ctxt->status == napi_ok && !belongsTo.empty(), E_INVALID_PARAMETERS,
                "Parameter error: parameter belongsTo type must be string");
        } else {
            belongsTo = DEFAULT_TYPE_ID;
        }
    };
    ctxt->GetCbInfoSync(env, info, input);
    ASSERT_NULL(!ctxt->isThrowError, "GetMultiUniformDataTypesByFilenameExtension Exit");
    std::vector<std::string> typeIds;
    auto status = E_OK;
    status = UtdClient::GetInstance().GetUniformDataTypesByFilenameExtension(filenameExtension, typeIds, belongsTo);
    ASSERT_ERR(ctxt->env, status == E_OK, status, "invalid arguments!");
    if (!typeIds.empty()) {
        NapiDataUtils::SetValue(env, typeIds, ctxt->output);
    } else {
        napi_get_null(env, &ctxt->output);
    }
    return ctxt->output;
}

napi_value UniformTypeDescriptorNapi::GetMultiUniformDataTypesByMIMEType(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "GetMultiUniformDataTypesByMIMEType is called!");
    std::string mimeType;
    std::string belongsTo;
    auto ctxt = std::make_shared<ContextBase>();
    auto input = [env, ctxt, &mimeType, &belongsTo](size_t argc, napi_value* argv) {
        LOG_DEBUG(UDMF_KITS_NAPI, "get utd types by MIMEType, argc = %{public}zu !", argc);
        // required 1 arguments : typeId
        ASSERT_BUSINESS_ERR(ctxt, argc >= 1,
            Status::E_INVALID_PARAMETERS, "Parameter error: Mandatory parameters are left unspecified");
        ctxt->status = NapiDataUtils::GetValue(env, argv[0], mimeType);
        ASSERT_BUSINESS_ERR(ctxt, ctxt->status == napi_ok, E_INVALID_PARAMETERS,
            "Parameter error: parameter mimeType type must be string");
        if (argc > 1) {
            ctxt->status = NapiDataUtils::GetValue(env, argv[1], belongsTo);
            ASSERT_BUSINESS_ERR(ctxt, ctxt->status == napi_ok && !belongsTo.empty(), E_INVALID_PARAMETERS,
                "Parameter error: parameter belongsTo type must be string");
        } else {
            belongsTo = DEFAULT_TYPE_ID;
        }
    };
    ctxt->GetCbInfoSync(env, info, input);
    ASSERT_NULL(!ctxt->isThrowError, "GetMultiUniformDataTypesByMIMEType Exit");
    std::vector<std::string> typeIds;
    auto status = E_OK;
    status = UtdClient::GetInstance().GetUniformDataTypesByMIMEType(mimeType, typeIds, belongsTo);
    ASSERT_ERR(ctxt->env, status == E_OK, status, "invalid arguments!");
    if (!typeIds.empty()) {
        NapiDataUtils::SetValue(env, typeIds, ctxt->output);
    } else {
        napi_get_null(env, &ctxt->output);
    }
    return ctxt->output;
}

napi_value UniformTypeDescriptorNapi::RegisterTypeDescriptors(napi_env env, napi_callback_info info)
{
    auto ctxt = std::make_shared<ContextBase>();
    auto descriptors = std::make_shared<std::vector<TypeDescriptorCfg>>();
    auto input = [env, ctxt, descriptors](size_t argc, napi_value *argv) {
        ASSERT_BUSINESS_ERR(ctxt, argc >= 1,
            E_INVALID_PARAMETERS, "Parameter error: Mandatory parameters are left unspecified");
        ctxt->status = NapiDataUtils::GetValue(env, argv[0], *descriptors);
        ASSERT_BUSINESS_ERR(ctxt, ctxt->status == napi_ok, E_INVALID_PARAMETERS,
            "Parameter error: parameter descriptors type must be array of TypeDescriptor");
    };
    ctxt->GetCbInfoSync(env, info, input);
    ASSERT_NULL(!ctxt->isThrowError, "RegisterTypeDescriptors Exit");
    auto execute = [env, ctxt, descriptors]() {
        auto status = UtdClient::GetInstance().RegisterTypeDescriptors(*descriptors);
        ASSERT_WITH_ERRCODE(ctxt, status != E_NO_SYSTEM_PERMISSION, status, "Permission denied!");
        ASSERT_WITH_ERRCODE(ctxt, status != E_NO_PERMISSION, status, "Permission denied!");
        ASSERT_WITH_ERRCODE(ctxt, status != E_FORMAT_ERROR, status, "Error typeDescriptors format!");
        ASSERT_WITH_ERRCODE(ctxt, status != E_CONTENT_ERROR, status, "Error typeDescriptors content!");
        ASSERT_WITH_ERRCODE(ctxt, status == E_OK, status, "RegisterTypeDescriptors failed!");
    };
    auto output = [env, ctxt](napi_value &result) {};
    return NapiQueue::AsyncWork(env, ctxt, std::string(__FUNCTION__), execute, output);
}

napi_value UniformTypeDescriptorNapi::UnregisterTypeDescriptors(napi_env env, napi_callback_info info)
{
    auto ctxt = std::make_shared<ContextBase>();
    auto typeIds = std::make_shared<std::vector<std::string>>();
    auto input = [env, ctxt, typeIds](size_t argc, napi_value *argv) {
        ASSERT_BUSINESS_ERR(ctxt, argc >= 1,
            E_INVALID_PARAMETERS, "Parameter error: Mandatory parameters are left unspecified");
        ctxt->status = NapiDataUtils::GetValue(env, argv[0], *typeIds);
        ASSERT_BUSINESS_ERR(ctxt, ctxt->status == napi_ok, E_INVALID_PARAMETERS,
            "Parameter error: parameter typeIds type must be array of string");
    };
    ctxt->GetCbInfoSync(env, info, input);
    ASSERT_NULL(!ctxt->isThrowError, "UnregisterTypeDescriptors Exit");
    auto execute = [env, ctxt, typeIds]() {
        auto status = UtdClient::GetInstance().UnregisterTypeDescriptors(*typeIds);
        ASSERT_WITH_ERRCODE(ctxt, status != E_NO_SYSTEM_PERMISSION, status, "Permission denied!");
        ASSERT_WITH_ERRCODE(ctxt, status != E_NO_PERMISSION, status, "Permission denied!");
        ASSERT_WITH_ERRCODE(ctxt, status != E_INVALID_TYPE_ID, status, "Error TypeId!");
        ASSERT_WITH_ERRCODE(ctxt, status == E_OK, status, "UnregisterTypeDescriptors failed!");
    };
    auto output = [env, ctxt](napi_value &result) {};
    return NapiQueue::AsyncWork(env, ctxt, std::string(__FUNCTION__), execute, output);
}
} // namespace UDMF
} // namespace OHOS