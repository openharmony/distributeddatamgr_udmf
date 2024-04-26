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
#define LOG_TAG "UnifiedDataChannelNapi"
#include "unified_data_channel_napi.h"

#include "napi_data_utils.h"
#include "napi_error_utils.h"
#include "napi_queue.h"
#include "udmf_client.h"
#include "unified_data_napi.h"
#include "unified_meta.h"

namespace OHOS {
namespace UDMF {
napi_value UnifiedDataChannelNapi::UnifiedDataChannelInit(napi_env env, napi_value exports)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "UnifiedDataChannelNapi");
    napi_value intention = CreateIntention(env);
    napi_property_descriptor desc[] = {
        DECLARE_NAPI_PROPERTY("Intention", intention),
        DECLARE_NAPI_FUNCTION("insertData", InsertData),
        DECLARE_NAPI_FUNCTION("updateData", UpdateData),
        DECLARE_NAPI_FUNCTION("queryData", QueryData),
        DECLARE_NAPI_FUNCTION("deleteData", DeleteData),
        DECLARE_NAPI_GETTER("ShareOptions", CreateShareOption),
    };

    NAPI_CALL(env, napi_define_properties(env, exports, sizeof(desc) / sizeof(desc[0]), desc));
    return exports;
}

napi_value UnifiedDataChannelNapi::CreateIntention(napi_env env)
{
    napi_value intention = nullptr;
    napi_create_object(env, &intention);
    SetNamedProperty(env, intention, JS_UD_INTENTION_NAME_MAP.at(UD_INTENTION_DATA_HUB),
        UD_INTENTION_MAP.at(UD_INTENTION_DATA_HUB));
    napi_object_freeze(env, intention);
    return intention;
}

napi_status UnifiedDataChannelNapi::SetNamedProperty(napi_env env, napi_value &obj, const std::string &name,
    const std::string &value)
{
    napi_value property = nullptr;
    napi_status status = NapiDataUtils::SetValue(env, value, property);
    ASSERT(status == napi_ok, "string to napi_value failed!", status);
    status = napi_set_named_property(env, obj, name.c_str(), property);
    ASSERT(status == napi_ok, "napi_set_named_property failed!", status);
    return status;
}

napi_value UnifiedDataChannelNapi::InsertData(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "InsertData is called!");
    struct InsertContext : public ContextBase {
        std::string key;
        Intention intention;
        std::shared_ptr<UnifiedData> unifiedData;
    };
    std::string intention;
    auto unifiedDataNapi = new (std::nothrow) UnifiedDataNapi();
    auto ctxt = std::make_shared<InsertContext>();
    auto input = [env, ctxt, &intention, &unifiedDataNapi](size_t argc, napi_value *argv) {
        // require 2 arguments <options, unifiedData>
        ASSERT_BUSINESS_ERR(ctxt, argc >= 2, E_INVALID_PARAMETERS, "invalid arguments!");
        ctxt->status = GetNamedProperty(env, argv[0], "intention", intention);
        ASSERT_BUSINESS_ERR(ctxt, ctxt->status == napi_ok && UnifiedDataUtils::IsPersist(intention),
            E_INVALID_PARAMETERS, "invalid arg[0], i.e. invalid intention!");
        ctxt->status = napi_unwrap(env, argv[1], reinterpret_cast<void **>(&unifiedDataNapi));
        ASSERT_BUSINESS_ERR(ctxt, ctxt->status == napi_ok, E_INVALID_PARAMETERS,
            "invalid arg[1], i.e. invalid unifiedData!");
    };
    ctxt->GetCbInfo(env, info, input);
    ASSERT_NULL(!ctxt->isThrowError, "Insert Exit");
    ctxt->unifiedData = unifiedDataNapi->value_;
    ctxt->intention = UnifiedDataUtils::GetIntentionByString(intention);
    auto execute = [ctxt]() {
        CustomOption option = { .intention = ctxt->intention };
        auto status = UdmfClient::GetInstance().SetData(option, *(ctxt->unifiedData), ctxt->key);
        ASSERT_WITH_ERRCODE(ctxt, status == E_OK, status, "InsertData failed!");
    };

    auto output = [env, ctxt](napi_value &result) {
        ctxt->status = NapiDataUtils::SetValue(env, ctxt->key, result);
        ASSERT_WITH_ERRCODE(ctxt, ctxt->status == napi_ok, E_ERROR, "output failed!");
    };
    return NapiQueue::AsyncWork(env, ctxt, std::string(__FUNCTION__), execute, output);
}

napi_value UnifiedDataChannelNapi::UpdateData(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "UpdateData is called!");
    struct UpdateContext : public ContextBase {
        std::string key;
        std::shared_ptr<UnifiedData> unifiedData;
    };
    std::string key;
    auto unifiedDataNapi = new (std::nothrow) UnifiedDataNapi();
    auto ctxt = std::make_shared<UpdateContext>();
    auto input = [env, ctxt, &unifiedDataNapi](size_t argc, napi_value *argv) {
        // require 2 arguments <options, unifiedData>
        ASSERT_BUSINESS_ERR(ctxt, argc >= 2, E_INVALID_PARAMETERS, "invalid arguments!");
        ctxt->status = GetNamedProperty(env, argv[0], "key", ctxt->key);
        UnifiedKey key(ctxt->key);
        ASSERT_BUSINESS_ERR(ctxt,
            ctxt->status == napi_ok && key.IsValid() && UnifiedDataUtils::IsPersist(key.intention),
            E_INVALID_PARAMETERS, "invalid arg[0], i.e. invalid key!");
        ctxt->status = napi_unwrap(env, argv[1], reinterpret_cast<void **>(&unifiedDataNapi));
        ASSERT_BUSINESS_ERR(ctxt, ctxt->status == napi_ok, E_INVALID_PARAMETERS,
            "invalid arg[1], i.e. invalid unifiedData!");
    };
    ctxt->GetCbInfo(env, info, input);
    ASSERT_NULL(!ctxt->isThrowError, "Update Exit");
    ctxt->unifiedData = unifiedDataNapi->value_;
    auto execute = [ctxt]() {
        QueryOption option = { .key = ctxt->key };
        auto status = UdmfClient::GetInstance().UpdateData(option, *(ctxt->unifiedData));
        ASSERT_WITH_ERRCODE(ctxt, status == E_OK, status, "UpdateData failed!");
    };
    return NapiQueue::AsyncWork(env, ctxt, std::string(__FUNCTION__), execute);
}

napi_value UnifiedDataChannelNapi::QueryData(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "QueryData is called!");
    struct QueryContext : public ContextBase {
        std::string key;
        Intention intention;
        std::vector<UnifiedData> unifiedDataSet;
    };
    std::string intention;
    auto ctxt = std::make_shared<QueryContext>();
    auto input = [env, ctxt, &intention](size_t argc, napi_value *argv) {
        // require 1 arguments <options>
        ASSERT_BUSINESS_ERR(ctxt, argc >= 1, E_INVALID_PARAMETERS, "invalid arguments!");
        napi_status keyStatus;
        napi_status intentionStatus;
        auto options = argv[0];
        keyStatus = GetNamedProperty(env, options, "key", ctxt->key);
        intentionStatus = GetNamedProperty(env, options, "intention", intention);
        ASSERT_BUSINESS_ERR(ctxt,
            (keyStatus == napi_ok || intentionStatus == napi_ok) &&
                UnifiedDataUtils::IsValidOptions(ctxt->key, intention),
            E_INVALID_PARAMETERS, "invalid arg[0], i.e. invalid options!");
    };
    ctxt->GetCbInfo(env, info, input);
    ASSERT_NULL(!ctxt->isThrowError, "Query Exit");
    ctxt->intention = UnifiedDataUtils::GetIntentionByString(intention);
    auto execute = [env, ctxt]() {
        QueryOption option = {
            .key = ctxt->key,
            .intention = ctxt->intention,
        };
        auto status = UdmfClient::GetInstance().GetBatchData(option, ctxt->unifiedDataSet);
        LOG_DEBUG(UDMF_SERVICE, "GetBatchData : status =  %{public}d!", status);
        ASSERT_WITH_ERRCODE(ctxt, status == E_OK, status, "QueryData failed!");
    };
    auto output = [env, ctxt](napi_value &result) {
        ASSERT_WITH_ERRCODE(ctxt, !ctxt->unifiedDataSet.empty(), E_ERROR, "unifiedDataSet is empty!");
        ctxt->status = napi_create_array_with_length(env, ctxt->unifiedDataSet.size(), &ctxt->output);
        ASSERT_WITH_ERRCODE(ctxt, ctxt->status == napi_ok, E_ERROR, "napi_create_array_with_length failed!");
        int index = 0;
        for (const UnifiedData &data : ctxt->unifiedDataSet) {
            std::shared_ptr<UnifiedData> unifiedData = std::make_shared<UnifiedData>();
            unifiedData->SetRecords(data.GetRecords());
            napi_value dataNapi = nullptr;
            UnifiedDataNapi::NewInstance(env, unifiedData, dataNapi);
            ctxt->status = napi_set_element(env, ctxt->output, index++, dataNapi);
            ASSERT_WITH_ERRCODE(ctxt, ctxt->status == napi_ok, E_ERROR, "napi_set_element failed!");
        }
        result = ctxt->output;
    };
    return NapiQueue::AsyncWork(env, ctxt, std::string(__FUNCTION__), execute, output);
}

napi_value UnifiedDataChannelNapi::DeleteData(napi_env env, napi_callback_info info)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "DeleteData is called!");
    struct DeleteContext : public ContextBase {
        std::string key;
        Intention intention;
        std::vector<UnifiedData> unifiedDataSet;
    };
    std::string intention;
    auto ctxt = std::make_shared<DeleteContext>();
    auto input = [env, ctxt, &intention](size_t argc, napi_value *argv) {
        // require 1 arguments <options>
        ASSERT_BUSINESS_ERR(ctxt, argc >= 1, E_INVALID_PARAMETERS, "invalid arguments!");
        napi_status keyStatus;
        napi_status intentionStatus;
        napi_value options = argv[0];
        keyStatus = GetNamedProperty(env, options, "key", ctxt->key);
        intentionStatus = GetNamedProperty(env, options, "intention", intention);
        ASSERT_BUSINESS_ERR(ctxt,
            (keyStatus == napi_ok || intentionStatus == napi_ok) &&
                UnifiedDataUtils::IsValidOptions(ctxt->key, intention),
            E_INVALID_PARAMETERS, "invalid arg[0], i.e. invalid options!");
    };
    ctxt->GetCbInfo(env, info, input);
    ASSERT_NULL(!ctxt->isThrowError, "Delete Exit");
    ctxt->intention = UnifiedDataUtils::GetIntentionByString(intention);
    auto execute = [env, ctxt]() {
        QueryOption option = {
            .key = ctxt->key,
            .intention = ctxt->intention,
        };
        auto status = UdmfClient::GetInstance().DeleteData(option, ctxt->unifiedDataSet);
        ASSERT_WITH_ERRCODE(ctxt, status == E_OK, status, "DeleteData failed!");
    };

    auto output = [env, ctxt](napi_value &result) {
        ASSERT_WITH_ERRCODE(ctxt, !ctxt->unifiedDataSet.empty(), E_ERROR, "unifiedDataSet is empty!");
        ctxt->status = napi_create_array_with_length(env, ctxt->unifiedDataSet.size(), &ctxt->output);
        ASSERT_WITH_ERRCODE(ctxt, ctxt->status == napi_ok, E_ERROR, "napi_create_array_with_length failed!");
        int index = 0;
        for (const UnifiedData &data : ctxt->unifiedDataSet) {
            std::shared_ptr<UnifiedData> unifiedData = std::make_shared<UnifiedData>();
            unifiedData->SetRecords(data.GetRecords());
            napi_value dataNapi = nullptr;
            UnifiedDataNapi::NewInstance(env, unifiedData, dataNapi);
            ctxt->status = napi_set_element(env, ctxt->output, index++, dataNapi);
            ASSERT_WITH_ERRCODE(ctxt, ctxt->status == napi_ok, E_ERROR, "napi_set_element failed!");
        }
        result = ctxt->output;
    };
    return NapiQueue::AsyncWork(env, ctxt, std::string(__FUNCTION__), execute, output);
}

napi_status UnifiedDataChannelNapi::GetNamedProperty(napi_env env, napi_value &obj, const std::string &key,
    std::string &value)
{
    bool hasKey = false;
    napi_status status = napi_has_named_property(env, obj, key.c_str(), &hasKey);
    if (status != napi_ok) {
        LOG_ERROR(UDMF_KITS_NAPI, "napi_has_named_property failed, name = %{public}s", key.c_str());
        return napi_generic_failure;
    }
    if (!hasKey) {
        LOG_ERROR(UDMF_KITS_NAPI, "The property name is non-existent, name: %{public}s", key.c_str());
        return napi_generic_failure;
    }
    napi_value napiValue = nullptr;
    status = napi_get_named_property(env, obj, key.c_str(), &napiValue);
    if (status != napi_ok || napiValue == nullptr) {
        LOG_ERROR(UDMF_KITS_NAPI, "napi_get_named_property failed, name = %{public}s", key.c_str());
        return napi_generic_failure;
    }
    if (NapiDataUtils::IsNull(env, napiValue)) {
        LOG_ERROR(UDMF_KITS_NAPI, "The property value is null, name = %{public}s", key.c_str());
        return napi_generic_failure;
    }
    status = NapiDataUtils::GetValue(env, napiValue, value);
    if (status != napi_ok) {
        LOG_ERROR(UDMF_KITS_NAPI, "NapiDataUtils::GetValue failed, name = %{public}s", key.c_str());
        return status;
    }
    LOG_DEBUG(UDMF_KITS_NAPI, "Param parse successful, Options.%{public}s = %{public}s", key.c_str(), value.c_str());
    return status;
}

napi_value UnifiedDataChannelNapi::CreateShareOption(napi_env env, napi_callback_info info)
{
    napi_value jsShareOption = nullptr;
    napi_create_object(env, &jsShareOption);

    napi_value jsInApp;
    NapiDataUtils::SetValue(env, static_cast<int32_t>(ShareOption::IN_APP), jsInApp);
    NAPI_CALL(env, napi_set_named_property(env, jsShareOption, "IN_APP", jsInApp));

    napi_value jsCrossDevice;
    NapiDataUtils::SetValue(env, static_cast<int32_t>(ShareOption::CROSS_APP), jsCrossDevice);
    NAPI_CALL(env, napi_set_named_property(env, jsShareOption, "CROSS_APP", jsCrossDevice));
    return jsShareOption;
}
} // namespace UDMF
} // namespace OHOS