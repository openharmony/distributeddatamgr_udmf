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

#include "image_embedding_napi.h"

#include <dlfcn.h>

#include "aip_log.h"
#include "aip_napi_error.h"
#include "aip_napi_utils.h"
#include "i_aip_core_manager_impl.h"

#undef LOG_TAG
#define LOG_TAG "ImageEmbeddingNapi"

namespace OHOS {
namespace DataIntelligence {
namespace {
const int32_t ERR_OK = 0;
static constexpr uint8_t ARG_0 = 0;
static constexpr uint8_t ARG_1 = 1;
static constexpr uint8_t NUM_0 = 0;
static constexpr uint8_t NUM_1 = 1;
static constexpr uint8_t LENGTH_1 = 2;
static constexpr uint8_t LENGTH_2 = 3;
static const std::string CLASS_NAME = "ImageEmbedding";
const std::vector<std::string> EXPECTED_GET_ARG_TYPES = { "string" };
const std::vector<std::string> EXPECTED_GET_IMG_MODEL_ARG_TYPES = { "object" };
const std::string AIP_MANAGER_PATH = "libaip_core.z.so";
} // namespace

AipCoreManagerHandle ImageEmbeddingNapi::imgAipCoreMgrHandle_{};
thread_local napi_ref ImageEmbeddingNapi::sConstructor_ = nullptr;
IAipCoreManager *ImageEmbeddingNapi::imageAipCoreManager_ = nullptr;

struct ImageEmbeddingConstructorInfo {
    std::string className;
    napi_ref *classRef;
    napi_callback constructor;
    const napi_property_descriptor *property;
    size_t propertyCount;
    const napi_property_descriptor *staticProperty;
    size_t staticPropertyCount;
};

struct LoadCallbackData {
    napi_async_work asyncWork;
    napi_deferred deferred;
    int32_t ret;
};

struct ReleaseCallbackData {
    napi_async_work asyncWork;
    napi_deferred deferred;
    int32_t ret;
};

struct ImageCallbackData {
    napi_async_work asyncWork;
    napi_deferred deferred;
    std::string strArg;
    int32_t dataRet;
    std::vector<float> ret;
};

ImageEmbeddingNapi::ImageEmbeddingNapi() : env_(nullptr) {}

ImageEmbeddingNapi::~ImageEmbeddingNapi()
{
    AipNapiUtils::UnLoadAlgoLibrary(imgAipCoreMgrHandle_);
    imageAipCoreManager_ = nullptr;
    delete imageAipCoreManager_;
}

static napi_value StartInit(napi_env env, napi_value exports, struct ImageEmbeddingConstructorInfo info)
{
    napi_value constructor = nullptr;
    napi_status status = napi_define_class(env, info.className.c_str(), NAPI_AUTO_LENGTH, info.constructor, nullptr,
        info.propertyCount, info.property, &constructor);
    if (status != napi_ok) {
        AIP_HILOGE("define class fail");
        return nullptr;
    }

    status = napi_create_reference(env, constructor, NUM_1, info.classRef);
    if (status != napi_ok) {
        AIP_HILOGE("create reference fail");
        return nullptr;
    }

    napi_value global = nullptr;
    status = napi_get_global(env, &global);
    if (status != napi_ok) {
        AIP_HILOGE("create global fail");
        return nullptr;
    }

    status = napi_set_named_property(env, global, info.className.c_str(), constructor);
    if (status != napi_ok) {
        AIP_HILOGE("Init::set global named property fail");
        return nullptr;
    }

    status = napi_define_properties(env, exports, info.staticPropertyCount, info.staticProperty);
    if (status != napi_ok) {
        AIP_HILOGE("define properties fail");
        return nullptr;
    }
    return exports;
}

napi_value ImageEmbeddingNapi::Init(napi_env env, napi_value exports)
{
    AIP_HILOGD("Enter");
    if (!AipNapiUtils::LoadAlgoLibrary(AIP_MANAGER_PATH, imgAipCoreMgrHandle_, true)) {
        AIP_HILOGE("LoadAlgoLibrary failed");
    }

    if (imgAipCoreMgrHandle_.pAipManager != nullptr) {
        imageAipCoreManager_ = AipNapiUtils::GetAlgoObj(imgAipCoreMgrHandle_);
    } else {
        imageAipCoreManager_ = new IAipCoreManagerImpl();
    }

    if (imageAipCoreManager_ == nullptr) {
        AIP_HILOGE("GetAlgoObj failed");
        return nullptr;
    }

    napi_property_descriptor properties[] = {
        DECLARE_NAPI_FUNCTION("loadModel", LoadModel),
        DECLARE_NAPI_FUNCTION("releaseModel", ReleaseModel),
        DECLARE_NAPI_FUNCTION("getEmbedding", GetEmbedding),
    };

    napi_property_descriptor static_prop[] = {
        DECLARE_NAPI_STATIC_FUNCTION("getImageEmbeddingModel", GetImageEmbeddingModel),
    };

    struct ImageEmbeddingConstructorInfo info = {
        .className = CLASS_NAME,
        .classRef = &sConstructor_,
        .constructor = Constructor,
        .property = properties,
        .propertyCount = sizeof(properties) / sizeof(properties[NUM_0]),
        .staticProperty = static_prop,
        .staticPropertyCount = sizeof(static_prop) / sizeof(static_prop[NUM_0]),
    };

    if (StartInit(env, exports, info)) {
        return nullptr;
    }
    return exports;
}

napi_value ImageEmbeddingNapi::Constructor(napi_env env, napi_callback_info info)
{
    napi_value undefineValue = nullptr;
    napi_get_undefined(env, &undefineValue);

    napi_status status;
    napi_value thisVar = nullptr;
    status = napi_get_cb_info(env, info, nullptr, nullptr, &thisVar, nullptr);
    if (status == napi_ok && thisVar != nullptr) {
        std::unique_ptr<ImageEmbeddingNapi> imgEmbNapi = std::make_unique<ImageEmbeddingNapi>();
        if (imgEmbNapi != nullptr) {
            imgEmbNapi->env_ = env;
            status = napi_wrap(env, thisVar, reinterpret_cast<void *>(imgEmbNapi.get()), ImageEmbeddingNapi::Destructor,
                nullptr, nullptr);
            if (status == napi_ok) {
                imgEmbNapi.release();
                return thisVar;
            } else {
                AIP_HILOGE("Failure wrapping js to native napi");
            }
        }
    }
    return undefineValue;
}

void ImageEmbeddingNapi::Destructor(napi_env env, void *nativeObject, void *finalize)
{
    AIP_HILOGD("TextEmbeddingNapi, Destructor");
}

napi_value ImageEmbeddingNapi::GetImageEmbeddingModel(napi_env env, napi_callback_info info)
{
    AIP_HILOGE("Enter");
    size_t argc = ARG_1;
    napi_value args[ARG_1] = { nullptr };
    napi_value jsThis = nullptr;

    napi_status status = napi_get_cb_info(env, info, &argc, args, &jsThis, nullptr);
    if (status != napi_ok) {
        AIP_HILOGE("napi_get_cb_info failed");
        ThrowIntelligenceErr(env, INNER_ERROR, "napi_get_cb_info failed.");
        return nullptr;
    }

    if (!AipNapiUtils::ValidateArgsType(env, args, argc, EXPECTED_GET_IMG_MODEL_ARG_TYPES)) {
        AIP_HILOGE("ValidateArgsType failed");
        ThrowIntelligenceErr(env, PARAM_EXCEPTION, "wrong params type.");
        return nullptr;
    }

    ModelConfigData imgModelConfig;
    if (!ParseModelConfig(env, args, argc, &imgModelConfig)) {
        AIP_HILOGE("ParseModelConfig failed");
        ThrowIntelligenceErr(env, PARAM_EXCEPTION, "wrong params type.");
        return nullptr;
    }

    napi_value promise = nullptr;
    napi_deferred deferred = nullptr;
    status = napi_create_promise(env, &deferred, &promise);
    if (status != napi_ok) {
        AIP_HILOGE("create promise failed");
        ThrowIntelligenceErr(env, INNER_ERROR, "create promise failed");
        return nullptr;
    }

    auto asyncGetImgEmbeddingModelData = new AsyncGetImageEmbeddingModelData{
        .asyncWork = nullptr,
        .deferred = deferred,
        .config = imgModelConfig,
    };

    if (!CreateAsyncImgModelExecution(env, asyncGetImgEmbeddingModelData)) {
        AIP_HILOGE("create AsyncTextModelExecution failed");
        ThrowIntelligenceErr(env, INNER_ERROR, "create AsyncTextModelExecution failed");
        delete asyncGetImgEmbeddingModelData;
        return nullptr;
    }

    return promise;
}

bool ImageEmbeddingNapi::ParseModelConfig(napi_env env, napi_value *args, size_t argc, ModelConfigData *modelConfig)
{
    AIP_HILOGI("Enter");
    if (modelConfig == nullptr) {
        AIP_HILOGE("The modelConfig is null");
        return false;
    }
    uint32_t length;
    if (!AipNapiUtils::CheckModelConfig(env, args[ARG_0], length)) {
        AIP_HILOGE("The modelConfig is failed");
        return false;
    }

    if (length != LENGTH_1 && length != LENGTH_2) {
        AIP_HILOGE("The modelConfig length is failed");
        return false;
    }

    napi_value version, isNPUAvailable, cachePath;
    napi_status status = napi_get_named_property(env, args[ARG_0], "version", &version);
    if (status != napi_ok) {
        AIP_HILOGE("napi get version property failed");
        return false;
    }

    if (!AipNapiUtils::TransJsToInt32(env, version, modelConfig->versionValue)) {
        AIP_HILOGE("Trans version failed");
        return false;
    }

    status = napi_get_named_property(env, args[ARG_0], "isNpuAvailable", &isNPUAvailable);
    if (status != napi_ok) {
        AIP_HILOGE("napi get isNpuAvailable property failed");
        return false;
    }

    if (!AipNapiUtils::TransJsToBool(env, isNPUAvailable, modelConfig->isNPUAvailableValue)) {
        AIP_HILOGE("Trans isNPUAvailable failed");
        return false;
    }

    if (modelConfig->isNPUAvailableValue) {
        status = napi_get_named_property(env, args[ARG_0], "cachePath", &cachePath);
        if (status != napi_ok) {
            AIP_HILOGE("napi get cachePath property failed");
            return false;
        }

        if (!AipNapiUtils::TransJsToStr(env, cachePath, modelConfig->cachePathValue)) {
            AIP_HILOGE("Trans cachePath failed");
            return false;
        }
    } else {
        modelConfig->cachePathValue = "";
    }
    return true;
}


bool ImageEmbeddingNapi::CreateAsyncImgModelExecution(napi_env env, AsyncGetImageEmbeddingModelData *asyncModelData)
{
    AIP_HILOGI("Enter");
    napi_value resourceName;
    napi_status status = napi_create_string_utf8(env, "GetIamgeEmbeddingModel", NAPI_AUTO_LENGTH, &resourceName);
    if (status != napi_ok) {
        AIP_HILOGE(" napi_create_string_utf8 failed");
        return false;
    }

    status = napi_create_async_work(env, nullptr, resourceName, GetImgEmbeddingModelExecutionCB,
        GetImgEmbeddingModelCompleteCB, static_cast<void *>(asyncModelData), &asyncModelData->asyncWork);
    if (status != napi_ok) {
        AIP_HILOGE("napi_create_async_work failed");
        return false;
    }

    status = napi_queue_async_work_with_qos(env, asyncModelData->asyncWork, napi_qos_default);
    if (status != napi_ok) {
        AIP_HILOGE("napi_queue_async_work_with_qos failed");
        return false;
    }
    return true;
}

void ImageEmbeddingNapi::GetImgEmbeddingModelExecutionCB(napi_env env, void *data)
{
    AIP_HILOGD("Enter");
    AsyncGetImageEmbeddingModelData *modelData = static_cast<AsyncGetImageEmbeddingModelData *>(data);
    if (imageAipCoreManager_ == nullptr) {
        AIP_HILOGE("pAipManager is nullptr");
        return;
    }
    auto config = modelData->config;
    int32_t result = imageAipCoreManager_->InitImageModel(config);
    modelData->ret = result;
}

void ImageEmbeddingNapi::GetImgEmbeddingModelCompleteCB(napi_env env, napi_status status, void *data)
{
    AIP_HILOGD("Enter");
    AsyncGetImageEmbeddingModelData *modelData = static_cast<AsyncGetImageEmbeddingModelData *>(data);
    auto ret = modelData->ret;
    napi_value result = nullptr;
    if (ret != ERR_OK) {
        if (ret == DEVICE_EXCEPTION) {
            ThrowIntelligenceErrByPromise(env, DEVICE_EXCEPTION, "GetImgEmbeddingModelCompleteCB failed", result);
        } else {
            ThrowIntelligenceErrByPromise(env, INNER_ERROR, "GetImgEmbeddingModelCompleteCB failed", result);
        }
        napi_reject_deferred(env, modelData->deferred, result);
    } else {
        napi_value constructor = nullptr;
        status = napi_get_reference_value(env, sConstructor_, &constructor);
        if (status != napi_ok) {
            AIP_HILOGE("napi_get_reference_value failed");
            napi_get_undefined(env, &result);
            delete modelData;
            return;
        }

        status = napi_new_instance(env, constructor, 0, nullptr, &result);
        if (status != napi_ok) {
            AIP_HILOGE("napi_new_instance failed");
            napi_get_undefined(env, &result);
            return;
        }

        status = napi_resolve_deferred(env, modelData->deferred, result);
        if (status != napi_ok) {
            AIP_HILOGE(" napi_resolve_deferred failed");
        }
    }

    status = napi_delete_async_work(env, modelData->asyncWork);
    if (status != napi_ok) {
        AIP_HILOGE("napi_delete_async_work failed");
    }
    delete modelData;
}

napi_value ImageEmbeddingNapi::GetEmbedding(napi_env env, napi_callback_info info)
{
    AIP_HILOGE("Enter");
    size_t argc = ARG_1;
    napi_value args[ARG_1] = { nullptr };
    napi_value jsThis = nullptr;

    napi_status status = napi_get_cb_info(env, info, &argc, args, &jsThis, nullptr);
    if (status != napi_ok) {
        ThrowIntelligenceErr(env, INNER_ERROR, "napi_get_cb_info failed");
        return nullptr;
    }

    if (!AipNapiUtils::ValidateArgsType(env, args, argc, EXPECTED_GET_ARG_TYPES)) {
        ThrowIntelligenceErr(env, PARAM_EXCEPTION, "napi_get_cb_info failed");
        return nullptr;
    }

    std::string strArg;
    if (!AipNapiUtils::TransJsToStr(env, args[ARG_0], strArg)) {
        ThrowIntelligenceErr(env, PARAM_EXCEPTION, "napi_get_cb_info failed");
        return nullptr;
    }

    napi_value promise = nullptr;
    napi_deferred deferred = nullptr;
    status = napi_create_promise(env, &deferred, &promise);
    if (status != napi_ok) {
        ThrowIntelligenceErr(env, INNER_ERROR, "napi_create_promise failed");
        return nullptr;
    }

    if (!GetEmbeddingAsyncExecution(env, deferred, strArg)) {
        ThrowIntelligenceErr(env, INNER_ERROR, "GetEmbeddingAsyncExecution failed");
        return nullptr;
    }

    return promise;
}

bool ImageEmbeddingNapi::GetEmbeddingAsyncExecution(napi_env env, napi_deferred deferred, std::string strArg)
{
    AIP_HILOGD("Enter");
    auto imageCallbackData = new ImageCallbackData{
        .asyncWork = nullptr,
        .deferred = deferred,
        .strArg = strArg,
    };

    napi_value resourceName;
    napi_status status = napi_create_string_utf8(env, "ImageGetEmbedding", NAPI_AUTO_LENGTH, &resourceName);
    if (status != napi_ok) {
        AIP_HILOGE("napi_create_string_utf8 failed");
        delete imageCallbackData;
        return false;
    }

    status = napi_create_async_work(env, nullptr, resourceName, GetEmbeddingExecuteCB, GetEmbeddingCompleteCB,
        static_cast<void *>(imageCallbackData), &imageCallbackData->asyncWork);
    if (status != napi_ok) {
        AIP_HILOGE("napi_create_async_work failed");
        delete imageCallbackData;
        return false;
    }

    status = napi_queue_async_work_with_qos(env, imageCallbackData->asyncWork, napi_qos_default);
    if (status != napi_ok) {
        AIP_HILOGE("napi_queue_async_work_with_qos failed");
        napi_delete_async_work(env, imageCallbackData->asyncWork);
        delete imageCallbackData;
        return false;
    }
    return true;
}

void ImageEmbeddingNapi::GetEmbeddingExecuteCB(napi_env env, void *data)
{
    AIP_HILOGD("Enter");
    ImageCallbackData *imageCallbackData = static_cast<ImageCallbackData *>(data);
    std::string strArg = imageCallbackData->strArg;
    std::vector<float> result;
    int32_t ret = imageAipCoreManager_->GetImageEmbedding(strArg, result);
    imageCallbackData->dataRet = ret;
    imageCallbackData->ret = result;
    AIP_HILOGD("Exit");
}

void ImageEmbeddingNapi::GetEmbeddingCompleteCB(napi_env env, napi_status status, void *data)
{
    AIP_HILOGD("Enter");
    ImageCallbackData *imageCallbackData = static_cast<ImageCallbackData *>(data);
    napi_value value;
    auto ret = imageCallbackData->ret;
    auto dataRet = imageCallbackData->dataRet;

    if (dataRet != ERR_OK) {
        if (dataRet == DEVICE_EXCEPTION) {
            ThrowIntelligenceErrByPromise(env, DEVICE_EXCEPTION, " GetEmbeddingCompleteCB failed", value);
        } else {
            ThrowIntelligenceErrByPromise(env, INNER_ERROR, "GetEmbeddingCompleteCB  failed", value);
        }
        napi_reject_deferred(env, imageCallbackData->deferred, value);
    } else {
        status = napi_create_array(env, &value);
        if (status != napi_ok) {
            AIP_HILOGE("napi_create_array failed");
        } else {
            for (size_t i = 0; i < ret.size(); i++) {
                napi_value jsDouble = nullptr;
                AipNapiUtils::CreateDoubleData(env, static_cast<double>(ret[i]), &jsDouble);
                napi_set_element(env, value, i, jsDouble);
            }
            status = napi_resolve_deferred(env, imageCallbackData->deferred, value);
            if (status != napi_ok) {
                AIP_HILOGE(" napi_resolve_deferred failed");
            }
        }
    }

    status = napi_delete_async_work(env, imageCallbackData->asyncWork);
    if (status != napi_ok) {
        AIP_HILOGE("napi_delete_async_work failed");
    }
    delete imageCallbackData;
}

napi_value ImageEmbeddingNapi::LoadModel(napi_env env, napi_callback_info info)
{
    AIP_HILOGD("Enter");
    size_t argc = ARG_0;
    napi_value args[ARG_1] = { nullptr };
    napi_value jsThis = nullptr;

    napi_status status = napi_get_cb_info(env, info, &argc, args, &jsThis, nullptr);
    if (status != napi_ok) {
        ThrowIntelligenceErr(env, INNER_ERROR, "napi_get_cb_info failed");
        return nullptr;
    }

    if (argc != ARG_0) {
        ThrowIntelligenceErr(env, PARAM_EXCEPTION, "param size error");
        return nullptr;
    }

    napi_value promise = nullptr;
    napi_deferred deferred = nullptr;
    status = napi_create_promise(env, &deferred, &promise);
    if (status != napi_ok) {
        AIP_HILOGE("create promise failed");
        ThrowIntelligenceErr(env, INNER_ERROR, "create promise failed");
        return nullptr;
    }

    if (!LoadAsyncExecution(env, deferred)) {
        ThrowIntelligenceErr(env, INNER_ERROR, "LoadAsyncExecution failed");
        return nullptr;
    }

    AIP_HILOGD("Exit");
    return promise;
}

bool ImageEmbeddingNapi::LoadAsyncExecution(napi_env env, napi_deferred deferred)
{
    AIP_HILOGD("Enter");
    auto loadCallbackData = new LoadCallbackData{
        .asyncWork = nullptr,
        .deferred = deferred,
    };

    napi_value resourceName;
    napi_status status = napi_create_string_utf8(env, "imageLoad", NAPI_AUTO_LENGTH, &resourceName);
    if (status != napi_ok) {
        AIP_HILOGE("napi_create_string_utf8 failed");
        delete loadCallbackData;
        return false;
    }

    status = napi_create_async_work(env, nullptr, resourceName, LoadExecuteCB, LoadCompleteCB,
        static_cast<void *>(loadCallbackData), &loadCallbackData->asyncWork);
    if (status != napi_ok) {
        AIP_HILOGE("napi_create_async_work failed");
        delete loadCallbackData;
        return false;
    }

    status = napi_queue_async_work_with_qos(env, loadCallbackData->asyncWork, napi_qos_default);
    if (status != napi_ok) {
        AIP_HILOGE("napi_queue_async_work_with_qos failed");
        napi_delete_async_work(env, loadCallbackData->asyncWork);
        delete loadCallbackData;
        return false;
    }
    return true;
}


void ImageEmbeddingNapi::LoadExecuteCB(napi_env env, void *data)
{
    AIP_HILOGD("Enter");
    LoadCallbackData *loadCallbackData = static_cast<LoadCallbackData *>(data);
    auto ret = imageAipCoreManager_->LoadImageModel();
    loadCallbackData->ret = ret;
    AIP_HILOGD("Exit");
}

void ImageEmbeddingNapi::LoadCompleteCB(napi_env env, napi_status status, void *data)
{
    AIP_HILOGD("Enter");
    LoadCallbackData *loadCallbackData = static_cast<LoadCallbackData *>(data);
    napi_value value = nullptr;
    auto ret = loadCallbackData->ret;
    if (ret != ERR_OK) {
        if (ret == DEVICE_EXCEPTION) {
            ThrowIntelligenceErrByPromise(env, DEVICE_EXCEPTION, "LoadCompleteCB failed", value);
        } else {
            ThrowIntelligenceErrByPromise(env, INNER_ERROR, "LoadCompleteCB failed", value);
        }
        napi_reject_deferred(env, loadCallbackData->deferred, value);
    } else {
        status = napi_get_undefined(env, &value);
        if (status != napi_ok) {
            AIP_HILOGE(" napi_get_undefined failed");
        }
        status = napi_resolve_deferred(env, loadCallbackData->deferred, value);
        if (status != napi_ok) {
            AIP_HILOGE(" napi_resolve_deferred failed");
        }
    }

    status = napi_delete_async_work(env, loadCallbackData->asyncWork);
    if (status != napi_ok) {
        AIP_HILOGE("napi_delete_async_work failed");
    }
    delete loadCallbackData;
}

napi_value ImageEmbeddingNapi::ReleaseModel(napi_env env, napi_callback_info info)
{
    AIP_HILOGD("Enter");
    size_t argc = ARG_0;
    napi_value args[ARG_1] = { nullptr };
    napi_value jsThis = nullptr;

    napi_status status = napi_get_cb_info(env, info, &argc, args, &jsThis, nullptr);
    if (status != napi_ok) {
        AIP_HILOGE("napi_get_cb_info failed");
        ThrowIntelligenceErr(env, INNER_ERROR, "napi_get_cb_info failed");
        return nullptr;
    }

    if (argc != ARG_0) {
        ThrowIntelligenceErr(env, PARAM_EXCEPTION, "param size error");
        return nullptr;
    }

    napi_value promise = nullptr;
    napi_deferred deferred = nullptr;
    status = napi_create_promise(env, &deferred, &promise);
    if (status != napi_ok) {
        ThrowIntelligenceErr(env, INNER_ERROR, "create promise failed");
        return nullptr;
    }

    if (!ReleaseAsyncExecution(env, deferred)) {
        ThrowIntelligenceErr(env, INNER_ERROR, "ReleaseAsyncExecution failed");
        return nullptr;
    }

    AIP_HILOGD("Exit");
    return promise;
}

bool ImageEmbeddingNapi::ReleaseAsyncExecution(napi_env env, napi_deferred deferred)
{
    AIP_HILOGD("Enter");
    auto releaseCallbackData = new ReleaseCallbackData{
        .asyncWork = nullptr,
        .deferred = deferred,
    };

    napi_value resourceName;
    napi_status status = napi_create_string_utf8(env, "textLoad", NAPI_AUTO_LENGTH, &resourceName);
    if (status != napi_ok) {
        AIP_HILOGE("napi_create_string_utf8 failed");
        delete releaseCallbackData;
        return false;
    }

    status = napi_create_async_work(env, nullptr, resourceName, ReleaseExecuteCB, ReleaseCompleteCB,
        static_cast<void *>(releaseCallbackData), &releaseCallbackData->asyncWork);
    if (status != napi_ok) {
        AIP_HILOGE("napi_create_async_work failed");
        delete releaseCallbackData;
        return false;
    }

    status = napi_queue_async_work_with_qos(env, releaseCallbackData->asyncWork, napi_qos_default);
    if (status != napi_ok) {
        AIP_HILOGE("napi_queue_async_work_with_qos failed");
        napi_delete_async_work(env, releaseCallbackData->asyncWork);
        delete releaseCallbackData;
        return false;
    }
    return true;
}
void ImageEmbeddingNapi::ReleaseExecuteCB(napi_env env, void *data)
{
    AIP_HILOGD("Enter");
    ReleaseCallbackData *releaseCallbackData = static_cast<ReleaseCallbackData *>(data);
    auto ret = imageAipCoreManager_->ReleaseImageModel();
    releaseCallbackData->ret = ret;
    AIP_HILOGD("Exit");
}

void ImageEmbeddingNapi::ReleaseCompleteCB(napi_env env, napi_status status, void *data)
{
    AIP_HILOGD("Enter");
    ReleaseCallbackData *releaseCallbackData = static_cast<ReleaseCallbackData *>(data);
    napi_value value = nullptr;
    auto ret = releaseCallbackData->ret;
    if (ret != ERR_OK) {
        if (ret == DEVICE_EXCEPTION) {
            ThrowIntelligenceErrByPromise(env, DEVICE_EXCEPTION, "ReleaseCompleteCB failed", value);
        } else {
            ThrowIntelligenceErrByPromise(env, INNER_ERROR, "ReleaseCompleteCB failed", value);
        }
        napi_reject_deferred(env, releaseCallbackData->deferred, value);
    } else {
        status = napi_get_undefined(env, &value);
        if (status != napi_ok) {
            AIP_HILOGE(" napi_get_undefined failed");
        }
        status = napi_resolve_deferred(env, releaseCallbackData->deferred, value);
        if (status != napi_ok) {
            AIP_HILOGE(" napi_resolve_deferred failed");
        }
    }

    status = napi_delete_async_work(env, releaseCallbackData->asyncWork);
    if (status != napi_ok) {
        AIP_HILOGE("napi_delete_async_work failed");
    }
    delete releaseCallbackData;
}
} // namespace DataIntelligence
} // namespace OHOS
