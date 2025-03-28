/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#include "retrieval_napi.h"

#include <dlfcn.h>
#include <memory>
#include <node_api.h>
#include <string>

#include "aip_log.h"
#include "aip_napi_error.h"
#include "aip_napi_utils.h"
#include "i_aip_core_manager_impl.h"

#undef LOG_TAG
#define LOG_TAG "RetrievalNapi"

namespace OHOS {
namespace DataIntelligence {
namespace {
const int32_t ERR_OK = 0;
const std::string AIP_MANAGER_PATH = "libaip_core.z.so";
} // namespace

AipCoreManagerHandle RetrievalNapi::retrievalAipCoreMgrHandle_{};

RetrievalNapi::RetrievalNapi() : env_(nullptr) {}

RetrievalNapi::~RetrievalNapi()
{
    AipNapiUtils::UnLoadAlgoLibrary(retrievalAipCoreMgrHandle_);
}

napi_value RetrievalNapi::Init(napi_env env, napi_value exports)
{
    AIP_HILOGI("Init retrieval start.");
    napi_property_descriptor desc[] = {
        DECLARE_NAPI_FUNCTION("getRetriever", GetRetriever),
    };
    napi_status status = napi_define_properties(env, exports, sizeof(desc) / sizeof(desc[0]), desc);
    if (status != napi_ok) {
        AIP_HILOGE("define properties fail, status = %{public}d", status);
        return nullptr;
    }
    return exports;
}

napi_value RetrievalNapi::GetRetriever(napi_env env, napi_callback_info info)
{
    AIP_HILOGD("Enter");
    napi_value args[1] = { nullptr };
    size_t argc = 1;
    napi_status status = napi_get_cb_info(env, info, &argc, args, nullptr, nullptr);
    if (status != napi_ok) {
        ThrowIntelligenceErr(env, INNER_ERROR, "napi_get_cb_info failed.");
        return nullptr;
    }
    RetrievalConfigStruct retrievalConfig;
    status = AipNapiUtils::Convert2Value(env, args[0], retrievalConfig);
    if (status != napi_ok) {
        ThrowIntelligenceErr(env, PARAM_EXCEPTION, "Parse RetrievalConfig type failed.");
        return nullptr;
    }
    napi_value promise = nullptr;
    napi_deferred deferred = nullptr;
    status = napi_create_promise(env, &deferred, &promise);
    if (status != napi_ok) {
        ThrowIntelligenceErr(env, INNER_ERROR, "create promise failed");
        return nullptr;
    }
    auto asyncGetRetriever = new AsyncGetRetriever{
        .asyncWork = nullptr,
        .deferred = deferred,
        .config = retrievalConfig,
    };
    if (!CreateAsyncGetRetrieverExecution(env, asyncGetRetriever)) {
        ThrowIntelligenceErr(env, INNER_ERROR, "create AsyncGetRetrieverExecution failed");
        delete asyncGetRetriever;
        return nullptr;
    }
    return promise;
}

bool RetrievalNapi::CreateAsyncGetRetrieverExecution(napi_env env, AsyncGetRetriever *asyncGetRetriever)
{
    AIP_HILOGD("Enter");
    napi_value resourceName;
    napi_status status = napi_create_string_utf8(env, "GetRetriever", NAPI_AUTO_LENGTH, &resourceName);
    if (status != napi_ok) {
        AIP_HILOGE(" napi_create_string_utf8 failed.");
        return false;
    }
    status = napi_create_async_work(env, nullptr, resourceName, GetRetrieverExecutionCB, GetRetrieverCompleteCB,
        static_cast<void *>(asyncGetRetriever), &asyncGetRetriever->asyncWork);
    if (status != napi_ok) {
        AIP_HILOGE("napi_create_async_work failed.");
        return false;
    }
    status = napi_queue_async_work_with_qos(env, asyncGetRetriever->asyncWork, napi_qos_default);
    if (status != napi_ok) {
        AIP_HILOGE("napi_queue_async_work_with_qos failed");
        return false;
    }
    return true;
}

napi_value RetrievalNapi::WrapAipCoreManager(napi_env env, IAipCoreManager *retrievalAipCoreManager)
{
    napi_value result;
    napi_status status = napi_create_object(env, &result);
    if (status != napi_ok) {
        return nullptr;
    }
    status = napi_wrap(
        env, result, static_cast<void *>(retrievalAipCoreManager),
        [](napi_env env, void *data, void *hint) { delete static_cast<IAipCoreManager *>(data); }, nullptr, nullptr);
    if (status != napi_ok) {
        AIP_HILOGE("napi_wrap aipCoreMangager failed, erroCode is %{public}d", status);
        delete retrievalAipCoreManager;
        return nullptr;
    }
    // 为 Retriever 对象添加 retrieve 方法
    napi_value retrieveFn;
    status = napi_create_function(env, nullptr, NAPI_AUTO_LENGTH, Retrieve, nullptr, &retrieveFn);
    if (status != napi_ok) {
        return nullptr;
    }
    status = napi_set_named_property(env, result, "retrieveRdb", retrieveFn);
    if (status != napi_ok) {
        return nullptr;
    }
    return result;
}

void RetrievalNapi::GetRetrieverExecutionCB(napi_env env, void *data)
{
    AIP_HILOGD("Enter");
    AsyncGetRetriever *asyncGetRetrieverdata = static_cast<AsyncGetRetriever *>(data);
    auto config = asyncGetRetrieverdata->config;
    IAipCoreManager *retrievalAipCoreManager = nullptr;
    if (retrievalAipCoreMgrHandle_.create == nullptr) {
        AipNapiUtils::LoadAlgoLibrary(AIP_MANAGER_PATH, retrievalAipCoreMgrHandle_, false);
    }
    if (retrievalAipCoreMgrHandle_.create != nullptr) {
        AIP_HILOGI("Init retrieval by dlopen.");
        retrievalAipCoreManager = retrievalAipCoreMgrHandle_.create();
    }
    if (retrievalAipCoreManager == nullptr) {
        AIP_HILOGI("Init retrieval by new.");
        retrievalAipCoreManager = new IAipCoreManagerImpl();
    }
    int32_t ret = retrievalAipCoreManager->InitRetriever(config);
    asyncGetRetrieverdata->ret = ret;
    if (ret != ERR_OK) {
        AIP_HILOGE("init Retriever failed, erroCode is %{public}d", ret);
        delete retrievalAipCoreManager;
        return;
    }
    asyncGetRetrieverdata->retrievalAipCoreManagerPtr = retrievalAipCoreManager;
}

void RetrievalNapi::GetRetrieverCompleteCB(napi_env env, napi_status status, void *data)
{
    AIP_HILOGD("Enter");
    AsyncGetRetriever *asyncGetRetrieverdata = static_cast<AsyncGetRetriever *>(data);
    auto ret = asyncGetRetrieverdata->ret;
    napi_value result = nullptr;
    if (ret != ERR_OK) {
        if (ret == DEVICE_EXCEPTION) {
            ThrowIntelligenceErrByPromise(env, DEVICE_EXCEPTION, "GetRetrieverCompleteCB failed", result);
        } else {
            ThrowIntelligenceErrByPromise(env, INNER_ERROR, "GetRetrieverCompleteCB failed", result);
        }
        napi_reject_deferred(env, asyncGetRetrieverdata->deferred, result);
    } else {
        result = WrapAipCoreManager(env, asyncGetRetrieverdata->retrievalAipCoreManagerPtr);
        if (result == nullptr) {
            ThrowIntelligenceErrByPromise(env, INNER_ERROR, "GetRetrieverCompleteCB failed", result);
            napi_reject_deferred(env, asyncGetRetrieverdata->deferred, result);
        }
        status = napi_resolve_deferred(env, asyncGetRetrieverdata->deferred, result);
        if (status != napi_ok) {
            AIP_HILOGE(" napi_resolve_deferred failed");
        }
    }
    // todo 释放动态申请的RetrievalConfigStruct的内存
    status = napi_delete_async_work(env, asyncGetRetrieverdata->asyncWork);
    if (status != napi_ok) {
        AIP_HILOGE("napi_delete_async_work failed");
    }
    delete asyncGetRetrieverdata;
}

bool RetrievalNapi::CreateAsyncRetrieveExecution(napi_env env, AsyncRetrieve *asyncRetrieve)
{
    AIP_HILOGD("Enter");
    napi_value resourceName;
    napi_status status = napi_create_string_utf8(env, "Retrieve", NAPI_AUTO_LENGTH, &resourceName);
    if (status != napi_ok) {
        AIP_HILOGE(" napi_create_string_utf8 failed.");
        return false;
    }

    status = napi_create_async_work(env, nullptr, resourceName, RetrieveExecutionCB, RetrieveCompleteCB,
        static_cast<void *>(asyncRetrieve), &asyncRetrieve->asyncWork);
    if (status != napi_ok) {
        AIP_HILOGE("napi_create_async_work failed");
        return false;
    }

    status = napi_queue_async_work_with_qos(env, asyncRetrieve->asyncWork, napi_qos_default);
    if (status != napi_ok) {
        AIP_HILOGE("napi_queue_async_work_with_qos failed");
        return false;
    }
    return true;
}

void RetrievalNapi::RetrieveExecutionCB(napi_env env, void *data)
{
    AIP_HILOGD("Enter");
    AsyncRetrieve *asyncRetrieve = static_cast<AsyncRetrieve *>(data);
    auto retrievalCondition = asyncRetrieve->retrievalCondition;
    auto retrievalAipCoreManagerPtr = asyncRetrieve->retrievalAipCoreManagerPtr;
    RetrievalResponseStruct retrievalResponse;
    int32_t result = retrievalAipCoreManagerPtr->Retrieve(retrievalCondition, retrievalResponse);
    AIP_HILOGI("execute retrieve.");
    asyncRetrieve->ret = result;
    asyncRetrieve->retrievalResponse = retrievalResponse;
}

void RetrievalNapi::RetrieveCompleteCB(napi_env env, napi_status status, void *data)
{
    AIP_HILOGD("Enter");
    AsyncRetrieve *asyncRetrieve = static_cast<AsyncRetrieve *>(data);
    auto ret = asyncRetrieve->ret;
    napi_value result = nullptr;
    if (ret != ERR_OK) {
        if (ret == DEVICE_EXCEPTION) {
            ThrowIntelligenceErrByPromise(env, DEVICE_EXCEPTION, "GetRetrieverCompleteCB failed", result);
        } else {
            int32_t errCode = ConvertErrCodeNative2Ts(ret);
            // todo 这里不能只返回INNER_ERROR,应该返回返回具体的错误码
            ThrowIntelligenceErrByPromise(env, errCode, "GetRetrieverCompleteCB failed", result);
        }
        napi_reject_deferred(env, asyncRetrieve->deferred, result);
    } else {
        status = AipNapiUtils::Convert2JSValue(env, asyncRetrieve->retrievalResponse, result);
        if (status != napi_ok) {
            ThrowIntelligenceErrByPromise(env, INNER_ERROR, "convert RetrievalResponse to js value failed.", result);
            napi_reject_deferred(env, asyncRetrieve->deferred, result);
        } else {
            napi_resolve_deferred(env, asyncRetrieve->deferred, result);
        }
    }
    status = napi_delete_async_work(env, asyncRetrieve->asyncWork);
    if (status != napi_ok) {
        AIP_HILOGE("napi_delete_async_work failed.");
    }
    delete asyncRetrieve;
}


napi_value RetrievalNapi::Retrieve(napi_env env, napi_callback_info info)
{
    AIP_HILOGI("Retrieve being call.");
    napi_value args[1] = { nullptr };
    size_t argc = 1;
    napi_value jsThis = nullptr;
    napi_status status = napi_get_cb_info(env, info, &argc, args, &jsThis, nullptr);
    if (status != napi_ok) {
        ThrowIntelligenceErr(env, INNER_ERROR, "napi_get_cb_info failed.");
        return nullptr;
    }
    RetrievalConditionStruct retrievalCondition;
    status = AipNapiUtils::Convert2Value(env, args[0], retrievalCondition);
    if (status != napi_ok) {
        ThrowIntelligenceErr(env, PARAM_EXCEPTION, "Parse RetrievalCondition failed.");
        return nullptr;
    }
    napi_value promise = nullptr;
    napi_deferred deferred = nullptr;
    status = napi_create_promise(env, &deferred, &promise);
    if (status != napi_ok) {
        ThrowIntelligenceErr(env, INNER_ERROR, "create promise failed.");
        return nullptr;
    }
    IAipCoreManager *retrievalAipCoreManagerPtr;
    status = napi_unwrap(env, jsThis, reinterpret_cast<void **>(&retrievalAipCoreManagerPtr));
    if (status != napi_ok) {
        return nullptr;
    }
    auto asyncRetrieve = new AsyncRetrieve{
        .asyncWork = nullptr,
        .deferred = deferred,
        .retrievalCondition = retrievalCondition,
        .retrievalAipCoreManagerPtr = retrievalAipCoreManagerPtr
    };
    if (!CreateAsyncRetrieveExecution(env, asyncRetrieve)) {
        // napi函数错误为INNER_ERROR
        ThrowIntelligenceErr(env, INNER_ERROR, "CreateAsyncRetrieveExecution failed");
        delete asyncRetrieve;
    }
    return promise;
}
} // namespace DataIntelligence
} // namespace OHOS
