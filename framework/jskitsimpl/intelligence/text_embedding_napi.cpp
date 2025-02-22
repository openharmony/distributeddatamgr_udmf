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

#include "text_embedding_napi.h"

#include <dlfcn.h>

#include "aip_log.h"
#include "aip_napi_error.h"
#include "aip_napi_utils.h"
#include "i_aip_core_manager_impl.h"

#undef LOG_TAG
#define LOG_TAG "TextEmbeddingNapi"

namespace OHOS {
namespace DataIntelligence {
namespace {
const int32_t ERR_OK = 0;
static constexpr uint8_t ARG_0 = 0;
static constexpr uint8_t ARG_1 = 1;
static constexpr uint8_t ARG_2 = 2;

static constexpr uint8_t NUM_0 = 0;
static constexpr uint8_t NUM_1 = 1;
static constexpr uint8_t BASIC_MODEL = 0;
static constexpr uint8_t LENGTH_1 = 2;
static constexpr uint8_t LENGTH_2 = 3;
static constexpr uint32_t MAX_STR_PARAM_LEN = 512;
static const std::string CLASS_NAME = "TextEmbedding";
const std::vector<std::string> EXPECTED_SPLITTEXT_ARG_TYPES = { "string", "object" };
const std::vector<std::string> EXPECTED_GET_TEXT_MODEL_ARG_TYPES = { "object" };
const std::string AIP_MANAGER_PATH = "/system/lib64/platformsdk/libaip_core.z.so";
} // namespace
AipCoreManagerHandle TextEmbeddingNapi::textAipCoreMgrHandle_{};
thread_local napi_ref TextEmbeddingNapi::sConstructor_ = nullptr;
IAipCoreManager *TextEmbeddingNapi::textAipCoreManager_ = nullptr;

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

struct TextStringCallbackData {
    napi_async_work asyncWork;
    napi_deferred deferred;
    std::string strArg;
    int32_t dataRet;
    std::vector<float> ret;
};

struct TextArrayCallbackData {
    napi_async_work asyncWork;
    napi_deferred deferred;
    std::vector<std::string> text;
    int32_t dataRet;
    std::vector<std::vector<float>> ret;
};


struct SplitTextCallbackData {
    napi_async_work asyncWork;
    napi_deferred deferred;
    std::string strArg;
    int32_t configSize;
    double configOverlap;
    int32_t dataRet;
    std::vector<std::string> ret;
};

struct TextEmbeddingConstructorInfo {
    std::string className;
    napi_ref *classRef;
    napi_callback constructor;
    const napi_property_descriptor *property;
    size_t propertyCount;
    const napi_property_descriptor *staticProperty;
    size_t staticPropertyCount;
};

TextEmbeddingNapi::TextEmbeddingNapi() : env_(nullptr) {}

TextEmbeddingNapi::~TextEmbeddingNapi()
{
    AIP_HILOGI("Enter");
    AipNapiUtils::UnLoadAlgoLibrary(textAipCoreMgrHandle_);
    delete textAipCoreManager_;
}

static napi_value StartInit(napi_env env, napi_value exports, struct TextEmbeddingConstructorInfo info)
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

napi_value TextEmbeddingNapi::Init(napi_env env, napi_value exports)
{
    AIP_HILOGD("Enter");
    if (!AipNapiUtils::LoadAlgoLibrary(AIP_MANAGER_PATH, textAipCoreMgrHandle_)) {
        AIP_HILOGE("LoadAlgoLibrary failed");
    }

    if (textAipCoreMgrHandle_.pAipManager != nullptr) {
        textAipCoreManager_ = AipNapiUtils::GetAlgoObj(textAipCoreMgrHandle_);
    } else {
        textAipCoreManager_ = new IAipCoreManagerImpl();
    }

    if (textAipCoreManager_ == nullptr) {
        AIP_HILOGE("GetAlgoObj failed");
        return nullptr;
    }

    napi_property_descriptor properties[] = {
        DECLARE_NAPI_FUNCTION("loadModel", LoadModel),
        DECLARE_NAPI_FUNCTION("releaseModel", ReleaseModel),
        DECLARE_NAPI_FUNCTION("getEmbedding", GetEmbedding),
    };

    napi_property_descriptor static_prop[] = {
        DECLARE_NAPI_STATIC_FUNCTION("getTextEmbeddingModel", GetTextEmbeddingModel),
        DECLARE_NAPI_STATIC_FUNCTION("splitText", SplitText),
    };

    napi_value modelVersion;
    napi_status status = napi_create_object(env, &modelVersion);
    if (status != napi_ok) {
        AIP_HILOGE("Failed create object");
        return nullptr;
    }

    AipNapiUtils::SetInt32Property(env, modelVersion, BASIC_MODEL, "BASIC_MODEL");
    AipNapiUtils::SetPropertyName(env, exports, "ModelVersion", modelVersion);

    struct TextEmbeddingConstructorInfo info = {
        .className = CLASS_NAME,
        .classRef = &sConstructor_,
        .constructor = TextConstructor,
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

napi_value TextEmbeddingNapi::TextConstructor(napi_env env, napi_callback_info info)
{
    napi_value undefineValue = nullptr;
    napi_get_undefined(env, &undefineValue);

    napi_status status;
    napi_value thisVar = nullptr;
    status = napi_get_cb_info(env, info, nullptr, nullptr, &thisVar, nullptr);
    if (status == napi_ok && thisVar != nullptr) {
        std::unique_ptr<TextEmbeddingNapi> txtEmbNapi = std::make_unique<TextEmbeddingNapi>();
        if (txtEmbNapi != nullptr) {
            txtEmbNapi->env_ = env;
            status = napi_wrap(env, thisVar, reinterpret_cast<void *>(txtEmbNapi.get()), TextEmbeddingNapi::Destructor,
                nullptr, nullptr);
            if (status == napi_ok) {
                txtEmbNapi.release();
                return thisVar;
            } else {
                AIP_HILOGE("Failure wrapping js to native napi");
            }
        }
    }
    return undefineValue;
}

void TextEmbeddingNapi::Destructor(napi_env env, void *nativeObject, void *finalize)
{
    AIP_HILOGD("TextEmbeddingNapi, Destructor");
}

napi_value TextEmbeddingNapi::GetTextEmbeddingModel(napi_env env, napi_callback_info info)
{
    AIP_HILOGE("Enter");
    size_t argc = ARG_1;
    napi_value args[ARG_1] = { nullptr };
    napi_value jsThis = nullptr;

    napi_status status = napi_get_cb_info(env, info, &argc, args, &jsThis, nullptr);
    if (status != napi_ok) {
        ThrowIntelligenceErr(env, PARAM_EXCEPTION, "napi_get_cb_info failed");
        return nullptr;
    }

    if (!AipNapiUtils::ValidateArgsType(env, args, argc, EXPECTED_GET_TEXT_MODEL_ARG_TYPES)) {
        ThrowIntelligenceErr(env, PARAM_EXCEPTION, "ValidateArgsType failed");
        return nullptr;
    }

    ModelConfigData textModelConfig;
    if (!ParseModelConfig(env, args, argc, &textModelConfig)) {
        ThrowIntelligenceErr(env, PARAM_EXCEPTION, "ParseModelConfig failed");
        return nullptr;
    }

    napi_value promise = nullptr;
    napi_deferred deferred = nullptr;
    status = napi_create_promise(env, &deferred, &promise);
    if (status != napi_ok) {
        ThrowIntelligenceErr(env, PARAM_EXCEPTION, "create promise failed");
        return nullptr;
    }

    auto asyncGetTextEmbeddingModelData = new AsyncGetTextEmbeddingModelData{
        .asyncWork = nullptr,
        .deferred = deferred,
        .config = textModelConfig,
    };

    if (!CreateAsyncTextModelExecution(env, asyncGetTextEmbeddingModelData)) {
        ThrowIntelligenceErr(env, PARAM_EXCEPTION, "create AsyncTextModelExecution failed");
        delete asyncGetTextEmbeddingModelData;
        return nullptr;
    }

    return promise;
}

bool TextEmbeddingNapi::ParseModelConfig(napi_env env, napi_value *args, size_t argc, ModelConfigData *textModelConfig)
{
    AIP_HILOGI("Enter");
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

    if (!AipNapiUtils::TransJsToInt32(env, version, textModelConfig->versionValue)) {
        AIP_HILOGE("Trans version failed");
        return false;
    }

    status = napi_get_named_property(env, args[ARG_0], "isNpuAvailable", &isNPUAvailable);
    if (status != napi_ok) {
        AIP_HILOGE("napi get isNpuAvailable property failed");
        return false;
    }

    if (!AipNapiUtils::TransJsToBool(env, isNPUAvailable, textModelConfig->isNPUAvailableValue)) {
        AIP_HILOGE("Trans isNPUAvailable failed");
        return false;
    }

    if (textModelConfig->isNPUAvailableValue) {
        status = napi_get_named_property(env, args[ARG_0], "cachePath", &cachePath);
        if (status != napi_ok) {
            AIP_HILOGE("napi get cachePath property failed");
            return false;
        }

        if (!AipNapiUtils::TransJsToStr(env, cachePath, textModelConfig->cachePathValue)) {
            AIP_HILOGE("Trans cachePath failed");
            return false;
        }
    } else {
        textModelConfig->cachePathValue = "";
    }
    return true;
}

bool TextEmbeddingNapi::CreateAsyncTextModelExecution(napi_env env, AsyncGetTextEmbeddingModelData *asyncModelData)
{
    AIP_HILOGI("Enter");
    napi_value resourceName;
    napi_status status = napi_create_string_utf8(env, "GetTextEmbeddingModel", NAPI_AUTO_LENGTH, &resourceName);
    if (status != napi_ok) {
        AIP_HILOGE(" napi_create_string_utf8 failed");
        return false;
    }

    status = napi_create_async_work(env, nullptr, resourceName, GetTextEmbeddingModelExecutionCB,
        GetTextEmbeddingModelCompleteCB, static_cast<void *>(asyncModelData), &asyncModelData->asyncWork);
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


void TextEmbeddingNapi::GetTextEmbeddingModelExecutionCB(napi_env env, void *data)
{
    AIP_HILOGD("Enter");
    AsyncGetTextEmbeddingModelData *modelData = static_cast<AsyncGetTextEmbeddingModelData *>(data);
    if (textAipCoreManager_ == nullptr) {
        AIP_HILOGE("pAipManager is nullptr");
        return;
    }
    auto config = modelData->config;
    int32_t result = textAipCoreManager_->InitTextModel(config);
    modelData->ret = result;
    AIP_HILOGD("Exit");
}

void TextEmbeddingNapi::GetTextEmbeddingModelCompleteCB(napi_env env, napi_status status, void *data)
{
    AIP_HILOGD("Enter");
    AsyncGetTextEmbeddingModelData *modelData = static_cast<AsyncGetTextEmbeddingModelData *>(data);
    auto ret = modelData->ret;
    napi_value result = nullptr;
    napi_value constructor = nullptr;
    if (ret != ERR_OK) {
        if (ret == DEVICE_EXCEPTION) {
            ThrowIntelligenceErrByPromise(env, DEVICE_EXCEPTION, "GetTextEmbeddingModelCompleteCB failed", result);
        } else {
            ThrowIntelligenceErrByPromise(env, INNER_ERROR, "GetTextEmbeddingModelCompleteCB failed", result);
        }
        napi_reject_deferred(env, modelData->deferred, result);
    } else {
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


napi_value TextEmbeddingNapi::SplitText(napi_env env, napi_callback_info info)
{
    AIP_HILOGI("Enter");
    size_t argc = ARG_2;
    napi_value args[ARG_2] = { nullptr };
    napi_value jsThis = nullptr;

    napi_status status = napi_get_cb_info(env, info, &argc, args, &jsThis, nullptr);
    if (status != napi_ok) {
        ThrowIntelligenceErr(env, PARAM_EXCEPTION, "napi_get_cb_info failed");
        return nullptr;
    }

    if (!AipNapiUtils::ValidateArgsType(env, args, argc, EXPECTED_SPLITTEXT_ARG_TYPES)) {
        ThrowIntelligenceErr(env, PARAM_EXCEPTION, "ValidateArgsType failed");
        return nullptr;
    }

    std::string strArg;
    if (!AipNapiUtils::TransJsToStrUnlimited(env, args[ARG_0], strArg)) {
        ThrowIntelligenceErr(env, PARAM_EXCEPTION, "TransJsToStrUnlimited failed");
        return nullptr;
    }
    AIP_HILOGI("string strArg: %{public}s", strArg.c_str());

    napi_value cfgSize;
    napi_value cfgOverlap;
    if (!GetProperties(env, args[ARG_1], cfgSize, cfgOverlap)) {
        AIP_HILOGE("content property failed");
        ThrowIntelligenceErr(env, PARAM_EXCEPTION, "content property failed");
        return nullptr;
    }
    int32_t configSize;
    double configOverlap;
    AipNapiUtils::TransJsToInt32(env, cfgSize, configSize);
    AipNapiUtils::TransJsToDouble(env, cfgOverlap, configOverlap);
    AIP_HILOGI("string strArg: %{public}d", configSize);
    AIP_HILOGI("string strArg: %{public}f", configOverlap);

    napi_value promise = nullptr;
    napi_deferred deferred = nullptr;
    status = napi_create_promise(env, &deferred, &promise);
    if (status != napi_ok) {
        ThrowIntelligenceErr(env, PARAM_EXCEPTION, "create promise failed");
        return nullptr;
    }

    if (!SplitTextAsyncExecution(env, deferred, strArg, configSize, configOverlap)) {
        ThrowIntelligenceErr(env, PARAM_EXCEPTION, "create split text async execution failed");
        return nullptr;
    }
    AIP_HILOGD("Exit");
    return promise;
}

bool TextEmbeddingNapi::SplitTextAsyncExecution(napi_env env, napi_deferred deferred, std::string strArg,
    int32_t configSize, double configOverlap)
{
    AIP_HILOGD("Enter");
    auto splitTextCallbackData = new SplitTextCallbackData{
        .asyncWork = nullptr,
        .deferred = deferred,
        .strArg = strArg,
        .configSize = configSize,
        .configOverlap = configOverlap,
    };

    napi_value resourceName;
    napi_status status = napi_create_string_utf8(env, "SplitText", NAPI_AUTO_LENGTH, &resourceName);
    if (status != napi_ok) {
        AIP_HILOGE("napi_create_string_utf8 failed");
        delete splitTextCallbackData;
        return false;
    }

    status = napi_create_async_work(env, nullptr, resourceName, SplitTextExecuteCB, SplitTextCompleteCB,
        static_cast<void *>(splitTextCallbackData), &splitTextCallbackData->asyncWork);
    if (status != napi_ok) {
        AIP_HILOGE("napi_create_async_work failed");
        delete splitTextCallbackData;
        return false;
    }

    status = napi_queue_async_work_with_qos(env, splitTextCallbackData->asyncWork, napi_qos_default);
    if (status != napi_ok) {
        AIP_HILOGE("napi_queue_async_work_with_qos failed");
        napi_delete_async_work(env, splitTextCallbackData->asyncWork);
        delete splitTextCallbackData;
        return false;
    }
    return true;
}

void TextEmbeddingNapi::SplitTextExecuteCB(napi_env env, void *data)
{
    AIP_HILOGD("Enter");
    SplitTextCallbackData *splitTextCallbackData = static_cast<SplitTextCallbackData *>(data);
    std::string strArg = splitTextCallbackData->strArg;
    int32_t configSize = splitTextCallbackData->configSize;
    double configOverlap = splitTextCallbackData->configOverlap;
    std::vector<std::string> result;
    int32_t ret = textAipCoreManager_->SplitText(strArg, configSize, static_cast<float>(configOverlap), result);
    if (ret != ERR_OK) {
        AIP_HILOGE("SplitText failed");
        result = {};
    }
    splitTextCallbackData->ret = result;
    splitTextCallbackData->dataRet = ret;
    AIP_HILOGD("Exit");
}
void TextEmbeddingNapi::SplitTextCompleteCB(napi_env env, napi_status status, void *data)
{
    AIP_HILOGD("Enter");
    SplitTextCallbackData *splitTextCallbackData = static_cast<SplitTextCallbackData *>(data);
    napi_value value = nullptr;
    std::vector<std::string> ret = splitTextCallbackData->ret;
    int32_t dataRet = splitTextCallbackData->dataRet;
    if (dataRet != ERR_OK) {
        if (dataRet == DEVICE_EXCEPTION) {
            ThrowIntelligenceErrByPromise(env, DEVICE_EXCEPTION, "SplitTextCompleteCB failed", value);
        } else {
            ThrowIntelligenceErrByPromise(env, INNER_ERROR, "SplitTextCompleteCB failed", value);
        }
        napi_reject_deferred(env, splitTextCallbackData->deferred, value);
    } else {
        status = napi_create_array(env, &value);
        if (status != napi_ok) {
            AIP_HILOGE("napi_create_array failed");
        } else {
            for (size_t i = 0; i < ret.size(); i++) {
                napi_value jsStr = nullptr;
                napi_create_string_utf8(env, ret[i].c_str(), NAPI_AUTO_LENGTH, &jsStr);
                napi_set_element(env, value, i, jsStr);
            }
            status = napi_resolve_deferred(env, splitTextCallbackData->deferred, value);
            if (status != napi_ok) {
                AIP_HILOGE("napi_resolve_deferred failed");
            }
        }
    }

    status = napi_delete_async_work(env, splitTextCallbackData->asyncWork);
    if (status != napi_ok) {
        AIP_HILOGE("napi_delete_async_work failed");
    }
    delete splitTextCallbackData;
}


bool TextEmbeddingNapi::GetProperties(napi_env env, napi_value args, napi_value &cfgSize, napi_value &cfgOverlap)
{
    napi_status status = napi_get_named_property(env, args, "size", &cfgSize);
    if (status != napi_ok) {
        AIP_HILOGE("napi get size property failed");
        return false;
    }

    status = napi_get_named_property(env, args, "overlapRatio", &cfgOverlap);
    if (status != napi_ok) {
        AIP_HILOGE("napi get overlapRatio property failed");
        return false;
    }
    return true;
}

napi_value TextEmbeddingNapi::GetEmbedding(napi_env env, napi_callback_info info)
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

    if (argc != ARG_1) {
        AIP_HILOGE("param size error");
        ThrowIntelligenceErr(env, PARAM_EXCEPTION, "param size error");
        return nullptr;
    }

    napi_valuetype valueType = napi_undefined;
    status = napi_typeof(env, args[ARG_0], &valueType);
    napi_value promise = nullptr;
    napi_deferred deferred = nullptr;
    status = napi_create_promise(env, &deferred, &promise);
    if (status != napi_ok) {
        ThrowIntelligenceErr(env, INNER_ERROR, "napi_get_cb_info failed");
        return nullptr;
    }
    if (valueType == napi_string) {
        StringType(env, args[ARG_0], promise, deferred);
    }
    if (valueType == napi_object) {
        ArrayType(env, args[ARG_0], promise, deferred);
    }

    return promise;
}

napi_value TextEmbeddingNapi::StringType(napi_env env, napi_value args, napi_value promise, napi_deferred deferred)
{
    std::string strArg;
    if (!AipNapiUtils::TransJsToStr(env, args, strArg)) {
        ThrowIntelligenceErr(env, PARAM_EXCEPTION, "TransJsToStr failed");
        return nullptr;
    }

    AIP_HILOGI("string Arg: %{public}s", strArg.c_str());
    if (!GetEmbeddingStringAsyncExecution(env, deferred, strArg)) {
        ThrowIntelligenceErr(env, INNER_ERROR, "GetEmbeddingStringAsyncExecution failed");
        return nullptr;
    }
    AIP_HILOGD("Exit");
    return promise;
}

bool TextEmbeddingNapi::GetEmbeddingStringAsyncExecution(napi_env env, napi_deferred deferred, std::string strArg)
{
    AIP_HILOGD("Enter");
    auto textStringCallbackData = new TextStringCallbackData{
        .asyncWork = nullptr,
        .deferred = deferred,
        .strArg = strArg,
    };

    napi_value resourceName;
    napi_status status = napi_create_string_utf8(env, "textStringEmbedding", NAPI_AUTO_LENGTH, &resourceName);
    if (status != napi_ok) {
        AIP_HILOGE("napi_create_string_utf8 failed");
        delete textStringCallbackData;
        return false;
    }

    status = napi_create_async_work(env, nullptr, resourceName, GetEmbeddingStringExecuteCB,
        GetEmbeddingStringCompleteCB, static_cast<void *>(textStringCallbackData), &textStringCallbackData->asyncWork);
    if (status != napi_ok) {
        AIP_HILOGE("napi_create_async_work failed");
        delete textStringCallbackData;
        return false;
    }

    status = napi_queue_async_work_with_qos(env, textStringCallbackData->asyncWork, napi_qos_default);
    if (status != napi_ok) {
        AIP_HILOGE("napi_queue_async_work_with_qos failed");
        napi_delete_async_work(env, textStringCallbackData->asyncWork);
        delete textStringCallbackData;
        return false;
    }
    return true;
}

void TextEmbeddingNapi::GetEmbeddingStringExecuteCB(napi_env env, void *data)
{
    AIP_HILOGD("Enter");
    TextStringCallbackData *textStringCallbackData = static_cast<TextStringCallbackData *>(data);
    std::string strArg = textStringCallbackData->strArg;
    std::vector<float> result;
    int32_t ret = textAipCoreManager_->GetTextEmbedding(strArg, result);
    textStringCallbackData->ret = result;
    textStringCallbackData->dataRet = ret;
    AIP_HILOGD("Exit");
}

void TextEmbeddingNapi::GetEmbeddingStringCompleteCB(napi_env env, napi_status status, void *data)
{
    AIP_HILOGD("Enter");
    TextStringCallbackData *textStringCallbackData = static_cast<TextStringCallbackData *>(data);
    napi_value value;
    auto ret = textStringCallbackData->ret;
    auto dataRet = textStringCallbackData->dataRet;
    if (dataRet != ERR_OK) {
        if (dataRet == DEVICE_EXCEPTION) {
            ThrowIntelligenceErrByPromise(env, DEVICE_EXCEPTION, "GetEmbeddingStringCompleteCB failed", value);
        } else {
            ThrowIntelligenceErrByPromise(env, INNER_ERROR, "GetEmbeddingStringCompleteCB failed", value);
        }
        napi_reject_deferred(env, textStringCallbackData->deferred, value);
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
            status = napi_resolve_deferred(env, textStringCallbackData->deferred, value);
            if (status != napi_ok) {
                AIP_HILOGE(" napi_resolve_deferred failed");
            }
        }
    }

    status = napi_delete_async_work(env, textStringCallbackData->asyncWork);
    if (status != napi_ok) {
        AIP_HILOGE("napi_delete_async_work failed");
    }
    delete textStringCallbackData;
}

bool TextEmbeddingNapi::ValidateAndDealArrayArgs(napi_env env, napi_value args, std::vector<std::string> &strArr)
{
    AIP_HILOGD("Enter");
    bool isArray = false;
    napi_status status = napi_is_array(env, args, &isArray);
    if (status != napi_ok) {
        AIP_HILOGE("check napi is array failed");
        return false;
    }

    if (!isArray) {
        AIP_HILOGE("argument is not array");
        return false;
    }

    uint32_t arrayLen = 0;
    status = napi_get_array_length(env, args, &arrayLen);
    if (status != napi_ok) {
        AIP_HILOGE("argument is not array");
        return false;
    }
    if (arrayLen > MAX_STR_PARAM_LEN) {
        AIP_HILOGE("argument size is too big");
        return false;
    }

    for (uint32_t i = 0; i < arrayLen; ++i) {
        napi_value element = nullptr;
        status = napi_get_element(env, args, i, &element);
        if (status != napi_ok) {
            AIP_HILOGE("argument get array element failed");
            return false;
        }
        std::string text;
        if (!AipNapiUtils::TransJsToStr(env, element, text)) {
            AIP_HILOGE("napi get array element error");
            strArr.clear();
            return false;
        }
        strArr.push_back(text);
    }
    return true;
}

napi_value TextEmbeddingNapi::ArrayType(napi_env env, napi_value args, napi_value promise, napi_deferred deferred)
{
    std::vector<std::string> text;
    if (!ValidateAndDealArrayArgs(env, args, text)) {
        ThrowIntelligenceErr(env, PARAM_EXCEPTION, "Validate ArrayArgs error!");
        return nullptr;
    }
    if (!GetEmbeddingArrayAsyncExecution(env, deferred, text)) {
        ThrowIntelligenceErr(env, INNER_ERROR, "GetEmbeddingArrayAsyncExecution failed!");
        return nullptr;
    }

    AIP_HILOGD("exit");
    return promise;
}

bool TextEmbeddingNapi::GetEmbeddingArrayAsyncExecution(napi_env env, napi_deferred deferred,
    std::vector<std::string> text)
{
    AIP_HILOGD("Enter");
    auto textArrayCallbackData = new TextArrayCallbackData{
        .asyncWork = nullptr,
        .deferred = deferred,
        .text = text,
    };

    napi_value resourceName;
    napi_status status = napi_create_string_utf8(env, "textArrayEmbedding", NAPI_AUTO_LENGTH, &resourceName);
    if (status != napi_ok) {
        AIP_HILOGE("napi_create_string_utf8 failed");
        delete textArrayCallbackData;
        return false;
    }

    status = napi_create_async_work(env, nullptr, resourceName, GetEmbeddingArrayExecuteCB, GetEmbeddingArrayCompleteCB,
        static_cast<void *>(textArrayCallbackData), &textArrayCallbackData->asyncWork);
    if (status != napi_ok) {
        AIP_HILOGE("napi_create_async_work failed");
        delete textArrayCallbackData;
        return false;
    }

    status = napi_queue_async_work_with_qos(env, textArrayCallbackData->asyncWork, napi_qos_default);
    if (status != napi_ok) {
        AIP_HILOGE("napi_queue_async_work_with_qos failed");
        napi_delete_async_work(env, textArrayCallbackData->asyncWork);
        delete textArrayCallbackData;
        return false;
    }
    return true;
}


void TextEmbeddingNapi::GetEmbeddingArrayExecuteCB(napi_env env, void *data)
{
    AIP_HILOGD("Enter");
    TextArrayCallbackData *textArrayCallbackData = static_cast<TextArrayCallbackData *>(data);
    auto text = textArrayCallbackData->text;
    std::vector<std::vector<float>> result;
    int32_t ret = textAipCoreManager_->GetTextEmbedding(text, result);
    textArrayCallbackData->ret = result;
    textArrayCallbackData->dataRet = ret;
}

void TextEmbeddingNapi::GetEmbeddingArrayCompleteCB(napi_env env, napi_status status, void *data)
{
    AIP_HILOGD("Enter");
    TextArrayCallbackData *textArrayCallbackData = static_cast<TextArrayCallbackData *>(data);
    napi_value value = nullptr;
    std::vector<std::vector<float>> ret = textArrayCallbackData->ret;
    auto dataRet = textArrayCallbackData->dataRet;
    if (dataRet != ERR_OK) {
        if (dataRet == DEVICE_EXCEPTION) {
            ThrowIntelligenceErrByPromise(env, DEVICE_EXCEPTION, "GetEmbeddingArrayCompleteCB failed", value);
        } else {
            ThrowIntelligenceErrByPromise(env, INNER_ERROR, "GetEmbeddingArrayCompleteCB failed", value);
        }
        napi_reject_deferred(env, textArrayCallbackData->deferred, value);
        status = napi_delete_async_work(env, textArrayCallbackData->asyncWork);
        if (status != napi_ok) {
            AIP_HILOGE("napi_delete_async_work failed");
        }
        delete textArrayCallbackData;
        return;
    }

    status = napi_create_array(env, &value);
    if (status != napi_ok) {
        AIP_HILOGE("napi_create_array failed");
    } else {
        for (size_t i = 0; i < ret.size(); ++i) {
            napi_value res = nullptr;
            napi_create_array(env, &res);
            for (size_t j = 0; j < ret[i].size(); ++j) {
                napi_value jsDouble = nullptr;
                napi_create_double(env, static_cast<double>(ret[i][j]), &jsDouble);
                napi_set_element(env, res, j, jsDouble);
            }
            napi_set_element(env, value, i, res);
        }
        status = napi_resolve_deferred(env, textArrayCallbackData->deferred, value);
        if (status != napi_ok) {
            AIP_HILOGE(" napi_resolve_deferred failed");
        }
    }

    status = napi_delete_async_work(env, textArrayCallbackData->asyncWork);
    if (status != napi_ok) {
        AIP_HILOGE("napi_delete_async_work failed");
    }
    delete textArrayCallbackData;
}


napi_value TextEmbeddingNapi::LoadModel(napi_env env, napi_callback_info info)
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
        AIP_HILOGE("param size error");
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

    if (!LoadAsyncExecution(env, deferred)) {
        ThrowIntelligenceErr(env, INNER_ERROR, "create promise failed");
        return nullptr;
    }
    AIP_HILOGD("Exit");
    return promise;
}

bool TextEmbeddingNapi::LoadAsyncExecution(napi_env env, napi_deferred deferred)
{
    AIP_HILOGD("Enter");
    auto loadCallbackData = new LoadCallbackData{
        .asyncWork = nullptr,
        .deferred = deferred,
    };

    napi_value resourceName;
    napi_status status = napi_create_string_utf8(env, "textLoad", NAPI_AUTO_LENGTH, &resourceName);
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

void TextEmbeddingNapi::LoadExecuteCB(napi_env env, void *data)
{
    AIP_HILOGD("Enter");
    LoadCallbackData *loadCallbackData = static_cast<LoadCallbackData *>(data);
    auto ret = textAipCoreManager_->LoadTextModel();
    loadCallbackData->ret = ret;
    AIP_HILOGD("Exit");
}

void TextEmbeddingNapi::LoadCompleteCB(napi_env env, napi_status status, void *data)
{
    AIP_HILOGD("Enter");
    LoadCallbackData *loadCallbackData = static_cast<LoadCallbackData *>(data);
    napi_value value = nullptr;
    auto ret = loadCallbackData->ret;
    if (ret != ERR_OK) {
        if (ret == DEVICE_EXCEPTION) {
            ThrowIntelligenceErrByPromise(env, DEVICE_EXCEPTION, "loadCallbackData failed", value);
        } else {
            ThrowIntelligenceErrByPromise(env, INNER_ERROR, "loadCallbackData failed", value);
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


napi_value TextEmbeddingNapi::ReleaseModel(napi_env env, napi_callback_info info)
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
        ThrowIntelligenceErr(env, INNER_ERROR, "releaseAsyncExecution failed");
        return nullptr;
    }

    AIP_HILOGD("Exit");
    return promise;
}

bool TextEmbeddingNapi::ReleaseAsyncExecution(napi_env env, napi_deferred deferred)
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
void TextEmbeddingNapi::ReleaseExecuteCB(napi_env env, void *data)
{
    AIP_HILOGD("Enter");
    ReleaseCallbackData *releaseCallbackData = static_cast<ReleaseCallbackData *>(data);
    auto ret = textAipCoreManager_->ReleaseTextModel();
    releaseCallbackData->ret = ret;
    AIP_HILOGD("Exit");
}

void TextEmbeddingNapi::ReleaseCompleteCB(napi_env env, napi_status status, void *data)
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
