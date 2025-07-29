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

#define LOG_TAG "UDMF_ANI_CONVERTER_UTILS"

#include "ani_common_utils.h"
#include "get_data_params_taihe.h"
#include "logger.h"
#include "ohos.data.unifiedDataChannel.proj.hpp"
#include "ohos.data.unifiedDataChannel.impl.hpp"
#include "udmf_ani_converter_utils.h"
#include "unified_data_taihe.h"
#include "unified_record_taihe.h"

namespace OHOS {
namespace UDMF {
static constexpr const char *GET_INNER_METHOED_NAME = "getInner";
std::shared_ptr<UnifiedData> AniConverter::UnwrapUnifiedData(ani_env *env, ani_object object)
{
    ani_long ptr;
    if (ANI_OK != env->Object_CallMethodByName_Long(object, GET_INNER_METHOED_NAME, nullptr, &ptr)) {
        LOG_ERROR(UDMF_ANI, "Call getInner method fail");
        return nullptr;
    }
    auto unifiedDataImplPtr = reinterpret_cast<UnifiedDataTaihe*>(ptr);
    if (unifiedDataImplPtr == nullptr) {
        LOG_ERROR(UDMF_ANI, "UnifiedDataImplPtr is null.");
        return nullptr;
    }
    return unifiedDataImplPtr->value_;
}

ani_object AniConverter::WrapUnifiedData(ani_env *env, std::shared_ptr<UnifiedData> unifiedData)
{
    ani_object obj = {};
    ani_class cls;
    if (ANI_OK!= env->FindClass("L@ohos/data/unifiedDataChannel/unifiedDataChannel/UnifiedData;", &cls)) {
        LOG_ERROR(UDMF_ANI, "Find class fail");
        return obj;
    }
    ani_method ctor;
    if (ANI_OK != env->Class_FindMethod(cls, "<ctor>", ":V", &ctor)) {
        LOG_ERROR(UDMF_ANI, "Find method fail");
        return obj;
    }
    if (ANI_OK != env->Object_New(cls, ctor, &obj)) {
        LOG_ERROR(UDMF_ANI, "Create object fail");
        return obj;
    }
    ani_long ptr;
    if (ANI_OK != env->Object_CallMethodByName_Long(obj, GET_INNER_METHOED_NAME, nullptr, &ptr)) {
        LOG_ERROR(UDMF_ANI, "Call getInner method fail");
        return obj;
    }
    auto unifiedDataImplPtr = reinterpret_cast<UnifiedDataTaihe*>(ptr);
    if (unifiedDataImplPtr == nullptr) {
        LOG_ERROR(UDMF_ANI, "UnifiedDataImplPtr is null.");
        return obj;
    }
    unifiedDataImplPtr->value_ = unifiedData;
    return obj;
}

ani_object AniConverter::WrapProgressInfo(ani_env *env, ProgressInfo info)
{
    ani_object obj = {};
    ani_double progress = (double)info.progress;
    ani_enum ani_field_status_cls;
    env->FindEnum("L@ohos/data/unifiedDataChannel/unifiedDataChannel/ListenerStatus;", &ani_field_status_cls);
    ani_enum_item status;
    env->Enum_GetEnumItemByIndex(ani_field_status_cls, (ani_size)info.progressStatus, &status);
    ani_class cls;
    if (ANI_OK!= env->FindClass("L@ohos/data/unifiedDataChannel/unifiedDataChannel/ProgressInfo_inner;", &cls)) {
        LOG_ERROR(UDMF_ANI, "Find class fail");
        return obj;
    }
    ani_method ctor;
    if (ANI_OK != env->Class_FindMethod(cls, "<ctor>", nullptr, &ctor)) {
        LOG_ERROR(UDMF_ANI, "Find method fail");
        return obj;
    }
    if (ANI_OK != env->Object_New(cls, ctor, &obj, progress, status)) {
        LOG_ERROR(UDMF_ANI, "Create object fail");
        return obj;
    }
    return obj;
}

std::shared_ptr<UnifiedRecord> AniConverter::UnwrapUnifiedRecord(ani_env *env, ani_object object)
{
    ani_long ptr;
    if (ANI_OK != env->Object_CallMethodByName_Long(object, GET_INNER_METHOED_NAME, nullptr, &ptr)) {
        LOG_ERROR(UDMF_ANI, "Call getInner method fail");
        return nullptr;
    }
    auto UnifiedRecordInnerImplPtr = reinterpret_cast<UnifiedRecordTaihe*>(ptr);
    if (UnifiedRecordInnerImplPtr == nullptr) {
        LOG_ERROR(UDMF_ANI, "UnifiedRecordInnerImplPtr is null.");
        return nullptr;
    }
    return UnifiedRecordInnerImplPtr->value_;
}

ani_object AniConverter::WrapUnifiedRecord(ani_env *env, std::shared_ptr<UnifiedRecord> unifiedRecord)
{
    ani_object obj = {};
    if (unifiedRecord == nullptr) {
        LOG_ERROR(UDMF_ANI, "UnifiedRecord is null.");
        return obj;
    }
    ani_class cls;
    if (ANI_OK!= env->FindClass("L@ohos/data/unifiedDataChannel/unifiedDataChannel/UnifiedRecord;", &cls)) {
        LOG_ERROR(UDMF_ANI, "Find class fail");
        return obj;
    }
    ani_method ctor;
    if (ANI_OK != env->Class_FindMethod(cls, "<ctor>", ":V", &ctor)) {
        LOG_ERROR(UDMF_ANI, "Find method fail");
        return obj;
    }
    if (ANI_OK != env->Object_New(cls, ctor, &obj)) {
        LOG_ERROR(UDMF_ANI, "Create object fail");
        return obj;
    }
    ani_long ptr;
    if (ANI_OK != env->Object_CallMethodByName_Long(obj, GET_INNER_METHOED_NAME, nullptr, &ptr)) {
        LOG_ERROR(UDMF_ANI, "Call getInner method fail");
        return obj;
    }
    auto UnifiedRecordInnerImplPtr = reinterpret_cast<UnifiedRecordTaihe*>(ptr);
    if (UnifiedRecordInnerImplPtr == nullptr) {
        LOG_ERROR(UDMF_ANI, "UnifiedRecordInnerImplPtr is null.");
        return obj;
    }
    UnifiedRecordInnerImplPtr->value_ = unifiedRecord;
    return obj;
}

ani_object AniConverter::WrapSummary(ani_env *env, std::shared_ptr<Summary> summary)
{
    ani_object obj = {};
    if (summary == nullptr) {
        LOG_ERROR(UDMF_ANI, "Summary is null.");
        return obj;
    }
    ani_class cls;
    if (ANI_OK!= env->FindClass("L@ohos/data/unifiedDataChannel/unifiedDataChannel/Summary;", &cls)) {
        LOG_ERROR(UDMF_ANI, "Find class fail");
        return obj;
    }
    ani_method ctor;
    if (ANI_OK != env->Class_FindMethod(cls, "<ctor>", ":V", &ctor)) {
        LOG_ERROR(UDMF_ANI, "Find method fail");
        return obj;
    }
    if (ANI_OK != env->Object_New(cls, ctor, &obj)) {
        LOG_ERROR(UDMF_ANI, "Create object fail");
        return obj;
    }

    env->Object_SetFieldByName_Ref(obj, "totalSize", CreateLong(env, summary->totalSize));
    InnerWrapMapParams(env, cls, obj, summary->summary);
    return obj;
}

GetDataParams AniConverter::UnwrapGetDataParams(ani_env *env, ani_object object, const std::string &key)
{
    GetDataParams params;
    GetDataParamsTaihe::Convert2NativeValue(env, object, params, key);
    return params;
}

} // namespace UDMF
} // namespace OHOS