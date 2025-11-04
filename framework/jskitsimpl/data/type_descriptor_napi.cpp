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
#define LOG_TAG "TypeDescriptorNapi"
#include "type_descriptor_napi.h"
#include "napi_data_utils.h"

namespace OHOS {
namespace UDMF {
napi_value TypeDescriptorNapi::Constructor(napi_env env)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "typeDescriptorNapi");
    napi_property_descriptor properties[] = {
        /* TypeDescriptor properties */
        DECLARE_NAPI_FUNCTION("belongsTo", BelongsTo),
        DECLARE_NAPI_FUNCTION("isLowerLevelType", IsLowerLevelType),
        DECLARE_NAPI_FUNCTION("isHigherLevelType", IsHigherLevelType),
        DECLARE_NAPI_FUNCTION("equals", Equals),
        DECLARE_NAPI_GETTER_SETTER("typeId", GetTypeId, SetTypeId),
        DECLARE_NAPI_GETTER_SETTER("belongingToTypes", GetBelongingToTypes, SetBelongingToTypes),
        DECLARE_NAPI_GETTER_SETTER("description", GetDescription, SetDescription),
        DECLARE_NAPI_GETTER_SETTER("referenceURL", GetReferenceURL, SetReferenceURL),
        DECLARE_NAPI_GETTER_SETTER("iconFile", GetIconFile, SetIconFile),
        DECLARE_NAPI_GETTER_SETTER("filenameExtensions", GetFilenameExtensions, SetFilenameExtensions),
        DECLARE_NAPI_GETTER_SETTER("mimeTypes", GetMimeTypes, SetMimeTypes)
    };
    size_t count = sizeof(properties) / sizeof(properties[0]);
    return NapiDataUtils::DefineClass(env, "TypeDescriptor", properties, count, TypeDescriptorNapi::New);
}

napi_value TypeDescriptorNapi::New(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "TypeDescriptorNapi.");
    auto ctxt = std::make_shared<ContextBase>();
    ctxt->GetCbInfoSync(env, info);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_ERROR, ctxt->error);

    auto *descriptorNapi = new (std::nothrow) TypeDescriptorNapi();
    ASSERT_ERR(ctxt->env, descriptorNapi != nullptr, Status::E_ERROR, "no memory for descriptorNapi!");
    descriptorNapi->value_ = std::make_shared<TypeDescriptor>();
    ASSERT_CALL(ctxt->env, napi_wrap(env, ctxt->self, descriptorNapi, Destructor, nullptr, nullptr), descriptorNapi);
    return ctxt->self;
}

void TypeDescriptorNapi::Destructor(napi_env env, void *data, void *hint)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "TypeDescriptorNapi finalize.");
    auto *uData = static_cast<TypeDescriptorNapi *>(data);
    ASSERT_VOID(uData != nullptr, "finalize null!");
    delete uData;
}

void TypeDescriptorNapi::NewInstance(napi_env env, std::shared_ptr<TypeDescriptor> in, napi_value &out)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "TypeDescriptorNapi create NewInstance");
    ASSERT_CALL_VOID(env, napi_new_instance(env, Constructor(env), 0, nullptr, &out));
    TypeDescriptorNapi *descriptorNapi = new (std::nothrow) TypeDescriptorNapi();
    ASSERT_ERR_VOID(env, descriptorNapi != nullptr, Status::E_ERROR, "no memory for typeDescriptorNapi!");
    descriptorNapi->value_ = in;
    ASSERT_CALL_DELETE(env, napi_wrap(env, out, descriptorNapi, Destructor, nullptr, nullptr), descriptorNapi);
}

TypeDescriptorNapi *TypeDescriptorNapi::GetDescriptorNapi(napi_env env, napi_callback_info info,
                                                          std::shared_ptr<ContextBase> &ctxt)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "GetDescriptorNapi");
    ctxt->GetCbInfoSync(env, info);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_ERROR, ctxt->error);
    return static_cast<TypeDescriptorNapi *>(ctxt->native);
}

napi_value TypeDescriptorNapi::BelongsTo(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "TypeDescriptorNapi::BelongsTo()");
    auto ctxt = std::make_shared<ContextBase>();
    std::string typeId;
    auto input = [env, ctxt, &typeId](size_t argc, napi_value* argv) {
        // required 1 arguments : descriptor
        ASSERT_BUSINESS_ERR(ctxt, argc >= 1,
            Status::E_INVALID_PARAMETERS, "Parameter error: Mandatory parameters are left unspecified");
        ctxt->status = NapiDataUtils::GetValue(env, argv[0], typeId);
        ASSERT_BUSINESS_ERR(ctxt, ctxt->status == napi_ok,
            Status::E_INVALID_PARAMETERS, "Parameter error: parameter type type must be string");
    };

    ctxt->GetCbInfoSync(env, info, input);
    ASSERT_NULL(!ctxt->isThrowError, "BelongsTo Exit");
    bool checkRet = false;
    Status status = reinterpret_cast<TypeDescriptorNapi*>(ctxt->native)->value_->BelongsTo(typeId, checkRet);
    ASSERT_ERR(ctxt->env, status == E_OK, status, "invalid arguments!");
    napi_get_boolean(env, checkRet, &ctxt->output);
    return ctxt->output;
}

napi_value TypeDescriptorNapi::IsLowerLevelType(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "TypeDescriptorNapi::IsLowerLevelType()");
    auto ctxt = std::make_shared<ContextBase>();
    std::string typeId;
    auto input = [env, ctxt, &typeId](size_t argc, napi_value* argv) {
        // required 1 arguments : descriptor
        ASSERT_BUSINESS_ERR(ctxt, argc >= 1,
            Status::E_INVALID_PARAMETERS, "Parameter error: Mandatory parameters are left unspecified");
        ctxt->status = NapiDataUtils::GetValue(env, argv[0], typeId);
        ASSERT_BUSINESS_ERR(ctxt, ctxt->status == napi_ok,
            Status::E_INVALID_PARAMETERS, "Parameter error: parameter type type must be string");
    };

    ctxt->GetCbInfoSync(env, info, input);
    ASSERT_NULL(!ctxt->isThrowError, "IsLowerLevelType Exit");
    bool checkRet = false;
    Status status = reinterpret_cast<TypeDescriptorNapi*>(ctxt->native)->value_->IsLowerLevelType(typeId, checkRet);
    ASSERT_ERR(ctxt->env, status == E_OK, status, "invalid arguments!");
    napi_get_boolean(env, checkRet, &ctxt->output);
    return ctxt->output;
}

napi_value TypeDescriptorNapi::IsHigherLevelType(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "TypeDescriptorNapi::IsHigherLevelType()");
    auto ctxt = std::make_shared<ContextBase>();
    std::string typeId;
    auto input = [env, ctxt, &typeId](size_t argc, napi_value* argv) {
        // required 1 arguments : descriptor
        ASSERT_BUSINESS_ERR(ctxt, argc >= 1,
            Status::E_INVALID_PARAMETERS, "Parameter error: Mandatory parameters are left unspecified");
        ctxt->status = NapiDataUtils::GetValue(env, argv[0], typeId);
        ASSERT_BUSINESS_ERR(ctxt, ctxt->status == napi_ok,
            Status::E_INVALID_PARAMETERS, "Parameter error: parameter field type must be string");
    };

    ctxt->GetCbInfoSync(env, info, input);
    ASSERT_NULL(!ctxt->isThrowError, "IsHigherLevelType Exit");
    bool checkRet = false;
    Status status = reinterpret_cast<TypeDescriptorNapi*>(ctxt->native)->value_->IsHigherLevelType(typeId, checkRet);
    ASSERT_ERR(ctxt->env, status == E_OK, status, "invalid arguments!");
    napi_get_boolean(env, checkRet, &ctxt->output);
    return ctxt->output;
}

napi_value TypeDescriptorNapi::Equals(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "TypeDescriptorNapi::Equals()");
    auto ctxt = std::make_shared<ContextBase>();
    std::shared_ptr<TypeDescriptor> typeDescriptor;
    auto input = [env, ctxt, &typeDescriptor](size_t argc, napi_value* argv) {
        // required 1 arguments : descriptor
        ASSERT_BUSINESS_ERR(ctxt, argc >= 1,
            Status::E_INVALID_PARAMETERS, "Parameter error: Mandatory parameters are left unspecified");
        ctxt->status = NapiDataUtils::GetValue(env, argv[0], typeDescriptor);
        ASSERT_BUSINESS_ERR(ctxt, ctxt->status == napi_ok, Status::E_INVALID_PARAMETERS,
            "Parameter error: parameter typeDescriptor type must be TypeDescriptor");
    };

    ctxt->GetCbInfoSync(env, info, input);
    ASSERT_NULL(!ctxt->isThrowError, "Equals Exit");
    bool equalsRet = reinterpret_cast<TypeDescriptorNapi*>(ctxt->native)->value_->Equals(typeDescriptor);
    napi_get_boolean(env, equalsRet, &ctxt->output);
    return ctxt->output;
}

napi_value TypeDescriptorNapi::GetTypeId(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "GetTypeId");
    auto ctxt = std::make_shared<ContextBase>();
    auto descriptorNapi = GetDescriptorNapi(env, info, ctxt);
    ASSERT_ERR(ctxt->env, (descriptorNapi != nullptr && descriptorNapi->value_ != nullptr),
               Status::E_ERROR, "invalid object!");
    ctxt->status = NapiDataUtils::SetValue(env, descriptorNapi->value_->GetTypeId(), ctxt->output);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_ERROR, "set typeId value failed!");
    return ctxt->output;
}

napi_value TypeDescriptorNapi::GetBelongingToTypes(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "GetBelongingToTypes");
    auto ctxt = std::make_shared<ContextBase>();
    auto descriptorNapi = GetDescriptorNapi(env, info, ctxt);
    ASSERT_ERR(ctxt->env, (descriptorNapi != nullptr && descriptorNapi->value_ != nullptr),
               Status::E_ERROR, "invalid object!");
    std::vector<std::string> belongingTypes = descriptorNapi->value_->GetBelongingToTypes();
    ctxt->status = NapiDataUtils::SetValue(env, belongingTypes, ctxt->output);
    return ctxt->output;
}

napi_value TypeDescriptorNapi::GetDescription(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "GetDescription");
    auto ctxt = std::make_shared<ContextBase>();
    auto descriptorNapi = GetDescriptorNapi(env, info, ctxt);
    ASSERT_ERR(ctxt->env, (descriptorNapi != nullptr && descriptorNapi->value_ != nullptr),
               Status::E_ERROR, "invalid object!");
    ctxt->status = NapiDataUtils::SetValue(env, descriptorNapi->value_->GetDescription(), ctxt->output);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_ERROR, "set description value failed!");
    return ctxt->output;
}

napi_value TypeDescriptorNapi::GetReferenceURL(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "GetReferenceURL");
    auto ctxt = std::make_shared<ContextBase>();
    auto descriptorNapi = GetDescriptorNapi(env, info, ctxt);
    ASSERT_ERR(ctxt->env, (descriptorNapi != nullptr && descriptorNapi->value_ != nullptr),
               Status::E_ERROR, "invalid object!");
    ctxt->status = NapiDataUtils::SetValue(env, descriptorNapi->value_->GetReferenceURL(), ctxt->output);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_ERROR, "set referenceURL value failed!");
    return ctxt->output;
}

napi_value TypeDescriptorNapi::GetIconFile(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "GetIconFile");
    auto ctxt = std::make_shared<ContextBase>();
    auto descriptorNapi = GetDescriptorNapi(env, info, ctxt);
    ASSERT_ERR(ctxt->env, (descriptorNapi != nullptr && descriptorNapi->value_ != nullptr),
               Status::E_ERROR, "invalid object!");
    ctxt->status = NapiDataUtils::SetValue(env, descriptorNapi->value_->GetIconFile(), ctxt->output);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_ERROR, "set iconFile value failed!");
    return ctxt->output;
}

napi_value TypeDescriptorNapi::GetFilenameExtensions(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "GetFilenameExtensions");
    auto ctxt = std::make_shared<ContextBase>();
    auto descriptorNapi = GetDescriptorNapi(env, info, ctxt);
    ASSERT_ERR(ctxt->env, (descriptorNapi != nullptr && descriptorNapi->value_ != nullptr),
               Status::E_ERROR, "invalid object!");
    std::vector<std::string> filenameExtensions = descriptorNapi->value_->GetFilenameExtensions();
    ctxt->status = NapiDataUtils::SetValue(env, filenameExtensions, ctxt->output);
    return ctxt->output;
}

napi_value TypeDescriptorNapi::GetMimeTypes(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "GetMimeTypes");
    auto ctxt = std::make_shared<ContextBase>();
    auto descriptorNapi = GetDescriptorNapi(env, info, ctxt);
    ASSERT_ERR(ctxt->env, (descriptorNapi != nullptr && descriptorNapi->value_ != nullptr),
               Status::E_ERROR, "invalid object!");
    std::vector<std::string> mimeTypes = descriptorNapi->value_->GetMimeTypes();
    ctxt->status = NapiDataUtils::SetValue(env, mimeTypes, ctxt->output);
    return ctxt->output;
}

napi_value TypeDescriptorNapi::SetTypeId(napi_env env, napi_callback_info info)
{
    auto ctxt = std::make_shared<ContextBase>();
    std::string typeId;
    auto input = [env, ctxt, &typeId](size_t argc, napi_value *argv) {
        ASSERT_BUSINESS_ERR(ctxt, argc >= 1,
            Status::E_INVALID_PARAMETERS, "Parameter error: Mandatory parameters are left unspecified");
        ctxt->status = NapiDataUtils::GetValue(env, argv[0], typeId);
        ASSERT_BUSINESS_ERR(ctxt, ctxt->status == napi_ok,
            Status::E_INVALID_PARAMETERS, "Parameter error: parameter typeId type must be string");
    };
    ctxt->GetCbInfo(env, info, input);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_ERROR, ctxt->error);
    auto descriptorNapi = static_cast<TypeDescriptorNapi *>(ctxt->native);
    ASSERT_ERR(ctxt->env, (descriptorNapi != nullptr && descriptorNapi->value_ != nullptr),
               Status::E_ERROR, "invalid object!");
    descriptorNapi->value_->SetTypeId(typeId);
    return nullptr;
}

napi_value TypeDescriptorNapi::SetBelongingToTypes(napi_env env, napi_callback_info info)
{
    auto ctxt = std::make_shared<ContextBase>();
    std::vector<std::string> belongingTypes;
    auto input = [env, ctxt, &belongingTypes](size_t argc, napi_value *argv) {
        ASSERT_BUSINESS_ERR(ctxt, argc >= 1,
            Status::E_INVALID_PARAMETERS, "Parameter error: Mandatory parameters are left unspecified");
        ctxt->status = NapiDataUtils::GetValue(env, argv[0], belongingTypes);
        ASSERT_BUSINESS_ERR(ctxt, ctxt->status == napi_ok,
            Status::E_INVALID_PARAMETERS, "Parameter error: parameter belongingTypes type must be array");
    };
    ctxt->GetCbInfo(env, info, input);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_ERROR, ctxt->error);
    auto descriptorNapi = static_cast<TypeDescriptorNapi *>(ctxt->native);
    ASSERT_ERR(ctxt->env, (descriptorNapi != nullptr && descriptorNapi->value_ != nullptr),
               Status::E_ERROR, "invalid object!");
    descriptorNapi->value_->SetBelongingToTypes(belongingTypes);
    return nullptr;
}

napi_value TypeDescriptorNapi::SetDescription(napi_env env, napi_callback_info info)
{
    auto ctxt = std::make_shared<ContextBase>();
    std::string description;
    auto input = [env, ctxt, &description](size_t argc, napi_value *argv) {
        ASSERT_BUSINESS_ERR(ctxt, argc >= 1,
            Status::E_INVALID_PARAMETERS, "Parameter error: Mandatory parameters are left unspecified");
        ctxt->status = NapiDataUtils::GetValue(env, argv[0], description);
        ASSERT_BUSINESS_ERR(ctxt, ctxt->status == napi_ok,
            Status::E_INVALID_PARAMETERS, "Parameter error: parameter description type must be string");
    };
    ctxt->GetCbInfo(env, info, input);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_ERROR, ctxt->error);
    auto descriptorNapi = static_cast<TypeDescriptorNapi *>(ctxt->native);
    ASSERT_ERR(ctxt->env, (descriptorNapi != nullptr && descriptorNapi->value_ != nullptr),
               Status::E_ERROR, "invalid object!");
    descriptorNapi->value_->SetDescription(description);
    return nullptr;
}

napi_value TypeDescriptorNapi::SetReferenceURL(napi_env env, napi_callback_info info)
{
    auto ctxt = std::make_shared<ContextBase>();
    std::string referenceURL;
    auto input = [env, ctxt, &referenceURL](size_t argc, napi_value *argv) {
        ASSERT_BUSINESS_ERR(ctxt, argc >= 1,
            Status::E_INVALID_PARAMETERS, "Parameter error: Mandatory parameters are left unspecified");
        ctxt->status = NapiDataUtils::GetValue(env, argv[0], referenceURL);
        ASSERT_BUSINESS_ERR(ctxt, ctxt->status == napi_ok,
            Status::E_INVALID_PARAMETERS, "Parameter error: parameter referenceURL type must be string");
    };
    ctxt->GetCbInfo(env, info, input);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_ERROR, ctxt->error);
    auto descriptorNapi = static_cast<TypeDescriptorNapi *>(ctxt->native);
    ASSERT_ERR(ctxt->env, (descriptorNapi != nullptr && descriptorNapi->value_ != nullptr),
               Status::E_ERROR, "invalid object!");
    descriptorNapi->value_->SetReferenceURL(referenceURL);
    return nullptr;
}

napi_value TypeDescriptorNapi::SetIconFile(napi_env env, napi_callback_info info)
{
    auto ctxt = std::make_shared<ContextBase>();
    std::string iconFile;
    auto input = [env, ctxt, &iconFile](size_t argc, napi_value *argv) {
        ASSERT_BUSINESS_ERR(ctxt, argc >= 1,
            Status::E_INVALID_PARAMETERS, "Parameter error: Mandatory parameters are left unspecified");
        ctxt->status = NapiDataUtils::GetValue(env, argv[0], iconFile);
        ASSERT_BUSINESS_ERR(ctxt, ctxt->status == napi_ok,
            Status::E_INVALID_PARAMETERS, "Parameter error: parameter iconFile type must be string");
    };
    ctxt->GetCbInfo(env, info, input);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_ERROR, ctxt->error);
    auto descriptorNapi = static_cast<TypeDescriptorNapi *>(ctxt->native);
    ASSERT_ERR(ctxt->env, (descriptorNapi != nullptr && descriptorNapi->value_ != nullptr),
               Status::E_ERROR, "invalid object!");
    descriptorNapi->value_->SetIconFile(iconFile);
    return nullptr;
}

napi_value TypeDescriptorNapi::SetFilenameExtensions(napi_env env, napi_callback_info info)
{
    auto ctxt = std::make_shared<ContextBase>();
    std::vector<std::string> filenameExtensions;
    auto input = [env, ctxt, &filenameExtensions](size_t argc, napi_value *argv) {
        ASSERT_BUSINESS_ERR(ctxt, argc >= 1,
            Status::E_INVALID_PARAMETERS, "Parameter error: Mandatory parameters are left unspecified");
        ctxt->status = NapiDataUtils::GetValue(env, argv[0], filenameExtensions);
        ASSERT_BUSINESS_ERR(ctxt, ctxt->status == napi_ok,
            Status::E_INVALID_PARAMETERS, "Parameter error: parameter filenameExtensions type must be string array");
    };
    ctxt->GetCbInfo(env, info, input);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_ERROR, ctxt->error);
    auto descriptorNapi = static_cast<TypeDescriptorNapi *>(ctxt->native);
    ASSERT_ERR(ctxt->env, (descriptorNapi != nullptr && descriptorNapi->value_ != nullptr),
               Status::E_ERROR, "invalid object!");
    descriptorNapi->value_->SetFilenameExtensions(filenameExtensions);
    return nullptr;
}

napi_value TypeDescriptorNapi::SetMimeTypes(napi_env env, napi_callback_info info)
{
    auto ctxt = std::make_shared<ContextBase>();
    std::vector<std::string> mimeTypes;
    auto input = [env, ctxt, &mimeTypes](size_t argc, napi_value *argv) {
        ASSERT_BUSINESS_ERR(ctxt, argc >= 1,
            Status::E_INVALID_PARAMETERS, "Parameter error: Mandatory parameters are left unspecified");
        ctxt->status = NapiDataUtils::GetValue(env, argv[0], mimeTypes);
        ASSERT_BUSINESS_ERR(ctxt, ctxt->status == napi_ok,
            Status::E_INVALID_PARAMETERS, "Parameter error: parameter mimeTypes type must be string array");
    };
    ctxt->GetCbInfo(env, info, input);
    ASSERT_ERR(ctxt->env, ctxt->status == napi_ok, Status::E_ERROR, ctxt->error);
    auto descriptorNapi = static_cast<TypeDescriptorNapi *>(ctxt->native);
    ASSERT_ERR(ctxt->env, (descriptorNapi != nullptr && descriptorNapi->value_ != nullptr),
               Status::E_ERROR, "invalid object!");
    descriptorNapi->value_->SetMimeTypes(mimeTypes);
    return nullptr;
}
} // namespace UDMF
} // namespace OHOS