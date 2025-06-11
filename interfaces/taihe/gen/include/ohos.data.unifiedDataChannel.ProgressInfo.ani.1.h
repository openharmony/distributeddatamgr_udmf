#pragma once
#include "ohos.data.unifiedDataChannel.ProgressInfo.ani.0.h"
#include "ohos.data.unifiedDataChannel.ProgressInfo.proj.1.hpp"
#pragma clang diagnostic ignored "-Wmissing-braces"
inline ::ohos::data::unifiedDataChannel::ProgressInfo ohos_data_unifiedDataChannel_ProgressInfo_fromANI(ani_env* env, ani_object ani_obj) {
    ani_double ani_field_progress;
    env->Object_CallMethod_Double(ani_obj, TH_ANI_FIND_CLASS_METHOD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/ProgressInfo_inner;", "<get>progress", nullptr), reinterpret_cast<ani_double*>(&ani_field_progress));
    double cpp_field_progress = (double)ani_field_progress;
    ani_enum_item ani_field_status;
    env->Object_CallMethod_Ref(ani_obj, TH_ANI_FIND_CLASS_METHOD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/ProgressInfo_inner;", "<get>status", nullptr), reinterpret_cast<ani_ref*>(&ani_field_status));
    ani_size cpp_field_status_idx;
    env->EnumItem_GetIndex(ani_field_status, &cpp_field_status_idx);
    ::ohos::data::unifiedDataChannel::ListenerStatus cpp_field_status((::ohos::data::unifiedDataChannel::ListenerStatus::key_t)cpp_field_status_idx);
    return ::ohos::data::unifiedDataChannel::ProgressInfo{std::move(cpp_field_progress), std::move(cpp_field_status)};
}
inline ani_object ohos_data_unifiedDataChannel_ProgressInfo_intoANI(ani_env* env, ::ohos::data::unifiedDataChannel::ProgressInfo const& cpp_obj) {
    ani_double ani_field_progress = (double)cpp_obj.progress;
    ani_enum ani_field_status_cls;
    env->FindEnum("L@ohos/data/unifiedDataChannel/unifiedDataChannel/ListenerStatus;", &ani_field_status_cls);
    ani_enum_item ani_field_status;
    env->Enum_GetEnumItemByIndex(ani_field_status_cls, (ani_size)cpp_obj.status.get_key(), &ani_field_status);
    ani_object ani_obj;
    env->Object_New(TH_ANI_FIND_CLASS(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/ProgressInfo_inner;"), TH_ANI_FIND_CLASS_METHOD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/ProgressInfo_inner;", "<ctor>", nullptr), &ani_obj, ani_field_progress, ani_field_status);
    return ani_obj;
}
