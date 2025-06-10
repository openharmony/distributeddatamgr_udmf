#pragma once
#include "ohos.data.unifiedDataChannel.GetDataParams.ani.0.h"
#include "ohos.data.unifiedDataChannel.GetDataParams.proj.1.hpp"
#include "ohos.data.unifiedDataChannel.ProgressInfo.ani.1.h"
#include "ohos.data.unifiedDataChannel.UnifiedDataOrNull.ani.1.h"
#pragma clang diagnostic ignored "-Wmissing-braces"
inline ::ohos::data::unifiedDataChannel::GetDataParams ohos_data_unifiedDataChannel_GetDataParams_fromANI(ani_env* env, ani_object ani_obj) {
    ani_enum_item ani_field_progressIndicator;
    env->Object_CallMethod_Ref(ani_obj, TH_ANI_FIND_CLASS_METHOD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/GetDataParams_inner;", "<get>progressIndicator", nullptr), reinterpret_cast<ani_ref*>(&ani_field_progressIndicator));
    ani_size cpp_field_progressIndicator_idx;
    env->EnumItem_GetIndex(ani_field_progressIndicator, &cpp_field_progressIndicator_idx);
    ::ohos::data::unifiedDataChannel::ProgressIndicator cpp_field_progressIndicator((::ohos::data::unifiedDataChannel::ProgressIndicator::key_t)cpp_field_progressIndicator_idx);
    ani_fn_object ani_field_dataProgressListener;
    env->Object_CallMethod_Ref(ani_obj, TH_ANI_FIND_CLASS_METHOD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/GetDataParams_inner;", "<get>dataProgressListener", nullptr), reinterpret_cast<ani_ref*>(&ani_field_dataProgressListener));
    struct cpp_field_dataProgressListener_cpp_impl_t {
        ani_ref ref;
        cpp_field_dataProgressListener_cpp_impl_t(ani_env* env, ani_fn_object obj) {
            env->GlobalReference_Create(obj, &this->ref);
        }
        ~cpp_field_dataProgressListener_cpp_impl_t() {
            ::taihe::env_guard guard;
            ani_env *env = guard.get_env();
            env->GlobalReference_Delete(this->ref);
        }
        void operator()(::ohos::data::unifiedDataChannel::ProgressInfo const& cpp_arg_0, ::ohos::data::unifiedDataChannel::UnifiedDataOrNull const& cpp_arg_1) {
            ::taihe::env_guard guard;
            ani_env *env = guard.get_env();
            ani_object ani_arg_0 = ohos_data_unifiedDataChannel_ProgressInfo_intoANI(env, cpp_arg_0);
            ani_ref ani_arg_1 = ohos_data_unifiedDataChannel_UnifiedDataOrNull_intoANI(env, cpp_arg_1);
            ani_ref ani_argv[] = {ani_arg_0, ani_arg_1};
            ani_ref ani_result;
            env->FunctionalObject_Call(static_cast<ani_fn_object>(this->ref), 2, ani_argv, &ani_result);
            return;
        }
    };
    ::taihe::callback<void(::ohos::data::unifiedDataChannel::ProgressInfo const&, ::ohos::data::unifiedDataChannel::UnifiedDataOrNull const&)> cpp_field_dataProgressListener = ::taihe::callback<void(::ohos::data::unifiedDataChannel::ProgressInfo const&, ::ohos::data::unifiedDataChannel::UnifiedDataOrNull const&)>::from<cpp_field_dataProgressListener_cpp_impl_t>(env, ani_field_dataProgressListener);
    ani_ref ani_field_destUri;
    env->Object_CallMethod_Ref(ani_obj, TH_ANI_FIND_CLASS_METHOD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/GetDataParams_inner;", "<get>destUri", nullptr), reinterpret_cast<ani_ref*>(&ani_field_destUri));
    ani_boolean cpp_field_destUri_flag;
    ::taihe::string* cpp_field_destUri_ptr = nullptr;
    env->Reference_IsUndefined(ani_field_destUri, &cpp_field_destUri_flag);
    if (!cpp_field_destUri_flag) {
        ani_size cpp_field_destUri_spec_len;
        env->String_GetUTF8Size(static_cast<ani_string>(ani_field_destUri), &cpp_field_destUri_spec_len);
        TString cpp_field_destUri_spec_tstr;
        char* cpp_field_destUri_spec_buf = tstr_initialize(&cpp_field_destUri_spec_tstr, cpp_field_destUri_spec_len + 1);
        env->String_GetUTF8(static_cast<ani_string>(ani_field_destUri), cpp_field_destUri_spec_buf, cpp_field_destUri_spec_len + 1, &cpp_field_destUri_spec_len);
        cpp_field_destUri_spec_buf[cpp_field_destUri_spec_len] = '\0';
        cpp_field_destUri_spec_tstr.length = cpp_field_destUri_spec_len;
        ::taihe::string cpp_field_destUri_spec = ::taihe::string(cpp_field_destUri_spec_tstr);
        cpp_field_destUri_ptr = new ::taihe::string(std::move(cpp_field_destUri_spec));
    };
    ::taihe::optional<::taihe::string> cpp_field_destUri(cpp_field_destUri_ptr);
    ani_ref ani_field_fileConflictOptions;
    env->Object_CallMethod_Ref(ani_obj, TH_ANI_FIND_CLASS_METHOD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/GetDataParams_inner;", "<get>fileConflictOptions", nullptr), reinterpret_cast<ani_ref*>(&ani_field_fileConflictOptions));
    ani_boolean cpp_field_fileConflictOptions_flag;
    ::ohos::data::unifiedDataChannel::FileConflictOptions* cpp_field_fileConflictOptions_ptr = nullptr;
    env->Reference_IsUndefined(ani_field_fileConflictOptions, &cpp_field_fileConflictOptions_flag);
    if (!cpp_field_fileConflictOptions_flag) {
        ani_size cpp_field_fileConflictOptions_spec_idx;
        env->EnumItem_GetIndex(static_cast<ani_enum_item>(ani_field_fileConflictOptions), &cpp_field_fileConflictOptions_spec_idx);
        ::ohos::data::unifiedDataChannel::FileConflictOptions cpp_field_fileConflictOptions_spec((::ohos::data::unifiedDataChannel::FileConflictOptions::key_t)cpp_field_fileConflictOptions_spec_idx);
        cpp_field_fileConflictOptions_ptr = new ::ohos::data::unifiedDataChannel::FileConflictOptions(std::move(cpp_field_fileConflictOptions_spec));
    };
    ::taihe::optional<::ohos::data::unifiedDataChannel::FileConflictOptions> cpp_field_fileConflictOptions(cpp_field_fileConflictOptions_ptr);
    return ::ohos::data::unifiedDataChannel::GetDataParams{std::move(cpp_field_progressIndicator), std::move(cpp_field_dataProgressListener), std::move(cpp_field_destUri), std::move(cpp_field_fileConflictOptions)};
}
inline ani_object ohos_data_unifiedDataChannel_GetDataParams_intoANI(ani_env* env, ::ohos::data::unifiedDataChannel::GetDataParams const& cpp_obj) {
    ani_enum ani_field_progressIndicator_cls;
    env->FindEnum("L@ohos/data/unifiedDataChannel/unifiedDataChannel/ProgressIndicator;", &ani_field_progressIndicator_cls);
    ani_enum_item ani_field_progressIndicator;
    env->Enum_GetEnumItemByIndex(ani_field_progressIndicator_cls, (ani_size)cpp_obj.progressIndicator.get_key(), &ani_field_progressIndicator);
    ani_fn_object ani_field_dataProgressListener = {};
    ani_ref ani_field_destUri;
    if (!cpp_obj.destUri) {
        env->GetUndefined(&ani_field_destUri);
    }
    else {
        ani_string ani_field_destUri_spec;
        env->String_NewUTF8((*cpp_obj.destUri).c_str(), (*cpp_obj.destUri).size(), &ani_field_destUri_spec);
        ani_field_destUri = ani_field_destUri_spec;
    }
    ani_ref ani_field_fileConflictOptions;
    if (!cpp_obj.fileConflictOptions) {
        env->GetUndefined(&ani_field_fileConflictOptions);
    }
    else {
        ani_enum ani_field_fileConflictOptions_spec_cls;
        env->FindEnum("L@ohos/data/unifiedDataChannel/unifiedDataChannel/FileConflictOptions;", &ani_field_fileConflictOptions_spec_cls);
        ani_enum_item ani_field_fileConflictOptions_spec;
        env->Enum_GetEnumItemByIndex(ani_field_fileConflictOptions_spec_cls, (ani_size)(*cpp_obj.fileConflictOptions).get_key(), &ani_field_fileConflictOptions_spec);
        ani_field_fileConflictOptions = ani_field_fileConflictOptions_spec;
    }
    ani_object ani_obj;
    env->Object_New(TH_ANI_FIND_CLASS(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/GetDataParams_inner;"), TH_ANI_FIND_CLASS_METHOD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/GetDataParams_inner;", "<ctor>", nullptr), &ani_obj, ani_field_progressIndicator, ani_field_dataProgressListener, ani_field_destUri, ani_field_fileConflictOptions);
    return ani_obj;
}
