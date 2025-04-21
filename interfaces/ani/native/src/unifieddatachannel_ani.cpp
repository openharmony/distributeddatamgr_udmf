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
#define LOG_TAG "unifiedDataChannelANI"
#include "ani_utils.h"
#include "logger.h"
#include "ani_common_want.h"
#include "image_ani_utils.h"

#include "unified_data.h"
#include "unified_record.h"
#include "unified_types.h"
#include "unified_meta.h"

#include "plain_text.h"
#include "html.h"
#include "link.h"
#include "image.h"
#include "video.h"
#include "audio.h"
#include "folder.h"
#include "system_defined_appitem.h"
#include "system_defined_form.h"
#include "system_defined_pixelmap.h"
#include "application_defined_record.h"

using namespace OHOS;
using namespace OHOS::UDMF;

static UDMF::ValueType ParseANIRecordValueType(ani_env *env, const std::string type, ani_object unionValue)
{
    UnionAccessor unionAccessor(env, unionValue);

    double doubleValue = 0.0;
    if (unionAccessor.TryConvert<double>(doubleValue)) {
        return doubleValue;
    }

    std::string stringValue;
    if (unionAccessor.TryConvert<std::string>(stringValue)) {
        return stringValue;
    }

    bool boolValue = false;
    if (unionAccessor.TryConvert<bool>(boolValue)) {
        return boolValue;
    }

    int intValue = 0;
    if (unionAccessor.TryConvert<int>(intValue)) {
        return intValue;
    }

    std::vector<uint8_t> arrayVect;
    if (unionAccessor.TryConvertArray<uint8_t>(arrayVect)) {
        return arrayVect;
    }

    if (!unionAccessor.IsInstanceOf("Lstd/core/Object;")) {
        LOG_DEBUG(UDMF_KITS_NAPI, "ParseANIRecordValueType default std::monostate");
        return std::monostate();
    }

    if (type == "openharmony.pixel-map") {
        auto pixelMap = Media::ImageAniUtils::GetPixelMapFromEnv(env, unionValue);
        if (pixelMap == nullptr) {
            return std::shared_ptr<Media::PixelMap>(nullptr);
        }
        std::shared_ptr<Media::PixelMap> pixelMapSpr(pixelMap);
        return pixelMapSpr;
    } else if (type == "openharmony.want") {
        AAFwk::Want wantObj;
        AppExecFwk::UnwrapWant(env, unionValue, wantObj);
        return std::make_shared<AAFwk::Want>(wantObj);
    } else {
        return std::make_shared<Object>();
    }
}

class UnifiedRecordHolder {
public:
    explicit UnifiedRecordHolder(ani_env *env, const std::string type, ani_object unionValue)
        {
            if (type == "default") {
                object_ = std::make_shared<UnifiedRecord>();
                return;
            }

            UDType utdType = ENTITY;
            if (UtdUtils::IsValidUtdId(type)) {
                utdType = static_cast<UDType>(UtdUtils::GetUtdEnumFromUtdId(type));
            }

            UDMF::ValueType value = ParseANIRecordValueType(env, type, unionValue);

            std::map<UDType, std::function<std::shared_ptr<UnifiedRecord>(UDType, ValueType)>> constructors = {
                {TEXT, [](UDType type, ValueType value) { return std::make_shared<Text>(type, value); }},
                {PLAIN_TEXT, [](UDType type, ValueType value) { return std::make_shared<PlainText>(type, value); }},
                {HTML, [](UDType type, ValueType value) { return std::make_shared<Html>(type, value); }},
                {HYPERLINK, [](UDType type, ValueType value) { return std::make_shared<Link>(type, value); }},
                {UDType::FILE, [](UDType type, ValueType value) { return std::make_shared<File>(type, value); }},
                {IMAGE, [](UDType type, ValueType value) { return std::make_shared<Image>(type, value); }},
                {VIDEO, [](UDType type, ValueType value) { return std::make_shared<Video>(type, value); }},
                {AUDIO, [](UDType type, ValueType value) { return std::make_shared<Audio>(type, value); }},
                {FOLDER, [](UDType type, ValueType value) { return std::make_shared<Folder>(type, value); }},
                {SYSTEM_DEFINED_RECORD, [](UDType type, ValueType value)
                    { return std::make_shared<SystemDefinedRecord>(type, value); }},
                {SYSTEM_DEFINED_APP_ITEM, [](UDType type, ValueType value)
                    { return std::make_shared<SystemDefinedAppItem>(type, value); }},
                {SYSTEM_DEFINED_FORM, [](UDType type, ValueType value)
                    { return std::make_shared<SystemDefinedForm>(type, value); }},
                {SYSTEM_DEFINED_PIXEL_MAP, [](UDType type, ValueType value)
                    { return std::make_shared<SystemDefinedPixelMap>(type, value); }},
                {APPLICATION_DEFINED_RECORD, [](UDType type, ValueType value)
                    { return std::make_shared<ApplicationDefinedRecord>(type, value); }},
            };

            auto constructor = constructors.find(utdType);
            if (constructor == constructors.end()) {
                object_ = std::make_shared<UnifiedRecord>();
                return;
            }

            object_ = constructor->second(utdType, value);
            if (utdType == APPLICATION_DEFINED_RECORD) {
                std::shared_ptr<ApplicationDefinedRecord> applicationDefinedRecord =
                    std::static_pointer_cast<ApplicationDefinedRecord>(object_);
                applicationDefinedRecord->SetApplicationDefinedType(type);
            }
        }

        const std::shared_ptr<UnifiedRecord> Get()
        {
            if (object_ == nullptr) {
                object_ = std::make_shared<UnifiedRecord>();
            }
            return object_;
        }

        void Set(ani_ref saveRemote)
        {
            saveRemote_ = saveRemote;
        }

        ~UnifiedRecordHolder()
        {
            LOG_DEBUG(UDMF_KITS_NAPI, "[ANI] enter UnifiedRecordHolder dtor ");
        }

    private:
        ani_ref saveRemote_ = nullptr;
        std::shared_ptr<UnifiedRecord> object_;
};

class UnifiedDataHolder {
public:
        explicit UnifiedDataHolder(UnifiedRecordHolder* recordHolder)
        {
            object_ = std::make_shared<UnifiedData>();

            if (recordHolder != nullptr) {
                auto recordPtr = recordHolder->Get();
                if (recordPtr != nullptr) {
                    object_->AddRecord(recordPtr);
                }
            }
        }

        std::shared_ptr<UnifiedData> Get()
        {
            return object_;
        }

        void Set(ani_ref saveRemote)
        {
            saveRemote_ = saveRemote;
        }

        ~UnifiedDataHolder()
        {
            LOG_DEBUG(UDMF_KITS_NAPI, "[ANI] enter UnifiedDataHolder dtor ");
        }

    private:
        ani_ref saveRemote_ = nullptr;
        std::shared_ptr<UnifiedData> object_;
};

static void UnifiedRecodeValueTypeConstructor([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object,
    ani_string descriptor, ani_object unionValue)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "[ANI] enter UnifiedRecodeValueTypeConstructor");

    ani_ref saveRemote = nullptr;
    env->GlobalReference_Create(reinterpret_cast<ani_ref>(object), &saveRemote);

    auto type = AniStringUtils::ToStd(env, static_cast<ani_string>(descriptor));
    auto objectRemoteHolder = new UnifiedRecordHolder(env, type, unionValue);
    objectRemoteHolder->Set(saveRemote);
    AniObjectUtils::Wrap<UnifiedRecordHolder>(env, object, objectRemoteHolder);
}

static void UnifiedDataConstructor([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object,
    ani_object recordObj)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "[ANI] enter UnifiedDataConstructor ");
    auto recoderHolder = AniObjectUtils::Unwrap<UnifiedRecordHolder>(env, recordObj);

    ani_ref saveRemote = nullptr;
    env->GlobalReference_Create(reinterpret_cast<ani_ref>(object), &saveRemote);

    auto objectHolder = new UnifiedDataHolder(recoderHolder);
    objectHolder->Set(saveRemote);
    AniObjectUtils::Wrap<UnifiedDataHolder>(env, object, objectHolder);
}

static ani_object UnifiedRecordToObject(ani_env *env, std::shared_ptr<UnifiedRecord> record)
{
    ani_object aniObject = nullptr;

    static const char *nameSpaceName = "L@ohos/data/unifiedDataChannel/unifiedDataChannel;";
    ani_namespace ns;
    if (ANI_OK != env->FindNamespace(nameSpaceName, &ns)) {
        LOG_ERROR(UDMF_KITS_NAPI, "Not found namespace %{public}s", nameSpaceName);
        return aniObject;
    }

    static const char *recordclsName = "LUnifiedRecord;";
    ani_class aniClass;
    if (ANI_OK != env->Namespace_FindClass(ns, recordclsName, &aniClass)) {
        LOG_ERROR(UDMF_KITS_NAPI, "Not found class %{public}s", recordclsName);
        return aniObject;
    }

    ani_method personInfoCtor;
    if (ANI_OK != env->Class_FindMethod(aniClass, "setNativePtr", nullptr, &personInfoCtor)) {
        LOG_ERROR(UDMF_KITS_NAPI, "Not found func setNativePtr");
        return aniObject;
    }

    if (ANI_OK != env->Object_New(aniClass, personInfoCtor, &aniObject, reinterpret_cast<ani_long>(record.get()))) {
        LOG_ERROR(UDMF_KITS_NAPI, "Object_New Failed");
        return aniObject;
    }
    return aniObject;
}

static ani_object GetRecords([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object obj)
{
    ani_object arrayObj = nullptr;
    ani_class arrayCls = nullptr;
    if (ANI_OK != env->FindClass("Lescompat/Array;", &arrayCls)) {
        LOG_ERROR(UDMF_KITS_NAPI, "FindClass Lescompat/Array; Failed");
        return arrayObj;
    }

    ani_method arrayCtor;
    if (ANI_OK != env->Class_FindMethod(arrayCls, "<ctor>", "I:V", &arrayCtor)) {
        LOG_ERROR(UDMF_KITS_NAPI, "Class_FindMethod <ctor> Failed");
        return arrayObj;
    }

    auto dataHolder = AniObjectUtils::Unwrap<UnifiedDataHolder>(env, obj);
    if (dataHolder == nullptr) {
        LOG_ERROR(UDMF_KITS_NAPI, "UnifiedData unwrapp failed");
        return arrayObj;
    }

    auto dataObj = dataHolder->Get();
    if (dataObj == nullptr) {
        LOG_ERROR(UDMF_KITS_NAPI, "dataHolder get empty...");
        return arrayObj;
    }

    std::vector<std::shared_ptr<UnifiedRecord>> records = dataObj->GetRecords();
    if (ANI_OK != env->Object_New(arrayCls, arrayCtor, &arrayObj, records.size())) {
        LOG_ERROR(UDMF_KITS_NAPI, "Object_New Array Faild");
        return arrayObj;
    }

    ani_size index = 0;
    for (const std::shared_ptr<UnifiedRecord> &recordPtr : records) {
        auto aniRecord = UnifiedRecordToObject(env, recordPtr);
        if (ANI_OK != env->Object_CallMethodByName_Void(arrayObj, "$_set", "ILstd/core/Object;:V", index, aniRecord)) {
            LOG_ERROR(UDMF_KITS_NAPI, "Object_CallMethodByName_Void  $_set Faild");
            break;
        }
        index++;
    }

    LOG_DEBUG(UDMF_KITS_NAPI, "getRecords index:%{public}u", static_cast<uint32_t>(index));
    return arrayObj;
}

ANI_EXPORT ani_status ANI_Constructor(ani_vm *vm, uint32_t *result)
{
    LOG_DEBUG(UDMF_KITS_NAPI, "ANI_Constructor start...");

    ani_env *env;
    if (ANI_OK != vm->GetEnv(ANI_VERSION_1, &env)) {
        LOG_ERROR(UDMF_KITS_NAPI, "[ANI] Unsupported ANI_VERSION_1");
        return ANI_ERROR;
    }

    static const char *nameSpaceName = "L@ohos/data/unifiedDataChannel/unifiedDataChannel;";
    ani_namespace ns;
    if (ANI_OK != env->FindNamespace(nameSpaceName, &ns)) {
        LOG_ERROR(UDMF_KITS_NAPI, "Not found namespace %{public}s", nameSpaceName);
        return ANI_NOT_FOUND;
    }

    static const char *recordclsName = "LUnifiedRecord;";
    ani_class unifiedRecordClass;
    if (ANI_OK != env->Namespace_FindClass(ns, recordclsName, &unifiedRecordClass)) {
        LOG_ERROR(UDMF_KITS_NAPI, "Not found class %{public}s", recordclsName);
        return ANI_NOT_FOUND;
    }

    std::array methods = {
        ani_native_function {"init", nullptr, reinterpret_cast<void *>(UnifiedRecodeValueTypeConstructor)},
    };

    if (ANI_OK != env->Class_BindNativeMethods(unifiedRecordClass, methods.data(), methods.size())) {
        LOG_ERROR(UDMF_KITS_NAPI, "Cannot bind native methods to %{public}s", recordclsName);
        return ANI_ERROR;
    }

    static const char *dataclsName = "LUnifiedData;";
    ani_class unifiedDataClass;
    if (ANI_OK != env->Namespace_FindClass(ns, dataclsName, &unifiedDataClass)) {
        LOG_ERROR(UDMF_KITS_NAPI, "Cannot find class %{public}s", dataclsName);
        return ANI_NOT_FOUND;
    }

    std::array datamethods = {
        ani_native_function {"initData", nullptr, reinterpret_cast<void *>(UnifiedDataConstructor)},
        ani_native_function {"getRecords", nullptr, reinterpret_cast<void *>(GetRecords)},
    };

    if (ANI_OK != env->Class_BindNativeMethods(unifiedDataClass, datamethods.data(), datamethods.size())) {
        LOG_ERROR(UDMF_KITS_NAPI, "Cannot bind native methods to %{public}s", dataclsName);
        return ANI_ERROR;
    }

    if (result == nullptr) {
        LOG_ERROR(UDMF_KITS_NAPI, "param result is null");
        return ANI_ERROR;
    }

    *result = ANI_VERSION_1;
    LOG_DEBUG(UDMF_KITS_NAPI, "ANI_Constructor end...");
    return ANI_OK;
}
