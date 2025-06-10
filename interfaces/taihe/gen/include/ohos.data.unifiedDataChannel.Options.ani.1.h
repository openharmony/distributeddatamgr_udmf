#pragma once
#include "ohos.data.unifiedDataChannel.Options.ani.0.h"
#include "ohos.data.unifiedDataChannel.Options.proj.1.hpp"
#pragma clang diagnostic ignored "-Wmissing-braces"
inline ::ohos::data::unifiedDataChannel::Options ohos_data_unifiedDataChannel_Options_fromANI(ani_env* env, ani_object ani_obj) {
    ani_ref ani_field_intention;
    env->Object_CallMethod_Ref(ani_obj, TH_ANI_FIND_CLASS_METHOD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Options_inner;", "<get>intention", nullptr), reinterpret_cast<ani_ref*>(&ani_field_intention));
    ani_boolean cpp_field_intention_flag;
    ::ohos::data::unifiedDataChannel::Intention* cpp_field_intention_ptr = nullptr;
    env->Reference_IsUndefined(ani_field_intention, &cpp_field_intention_flag);
    if (!cpp_field_intention_flag) {
        ani_size cpp_field_intention_spec_idx;
        env->EnumItem_GetIndex(static_cast<ani_enum_item>(ani_field_intention), &cpp_field_intention_spec_idx);
        ::ohos::data::unifiedDataChannel::Intention cpp_field_intention_spec((::ohos::data::unifiedDataChannel::Intention::key_t)cpp_field_intention_spec_idx);
        cpp_field_intention_ptr = new ::ohos::data::unifiedDataChannel::Intention(std::move(cpp_field_intention_spec));
    };
    ::taihe::optional<::ohos::data::unifiedDataChannel::Intention> cpp_field_intention(cpp_field_intention_ptr);
    ani_ref ani_field_key;
    env->Object_CallMethod_Ref(ani_obj, TH_ANI_FIND_CLASS_METHOD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Options_inner;", "<get>key", nullptr), reinterpret_cast<ani_ref*>(&ani_field_key));
    ani_boolean cpp_field_key_flag;
    ::taihe::string* cpp_field_key_ptr = nullptr;
    env->Reference_IsUndefined(ani_field_key, &cpp_field_key_flag);
    if (!cpp_field_key_flag) {
        ani_size cpp_field_key_spec_len;
        env->String_GetUTF8Size(static_cast<ani_string>(ani_field_key), &cpp_field_key_spec_len);
        TString cpp_field_key_spec_tstr;
        char* cpp_field_key_spec_buf = tstr_initialize(&cpp_field_key_spec_tstr, cpp_field_key_spec_len + 1);
        env->String_GetUTF8(static_cast<ani_string>(ani_field_key), cpp_field_key_spec_buf, cpp_field_key_spec_len + 1, &cpp_field_key_spec_len);
        cpp_field_key_spec_buf[cpp_field_key_spec_len] = '\0';
        cpp_field_key_spec_tstr.length = cpp_field_key_spec_len;
        ::taihe::string cpp_field_key_spec = ::taihe::string(cpp_field_key_spec_tstr);
        cpp_field_key_ptr = new ::taihe::string(std::move(cpp_field_key_spec));
    };
    ::taihe::optional<::taihe::string> cpp_field_key(cpp_field_key_ptr);
    return ::ohos::data::unifiedDataChannel::Options{std::move(cpp_field_intention), std::move(cpp_field_key)};
}
inline ani_object ohos_data_unifiedDataChannel_Options_intoANI(ani_env* env, ::ohos::data::unifiedDataChannel::Options const& cpp_obj) {
    ani_ref ani_field_intention;
    if (!cpp_obj.intention) {
        env->GetUndefined(&ani_field_intention);
    }
    else {
        ani_enum ani_field_intention_spec_cls;
        env->FindEnum("L@ohos/data/unifiedDataChannel/unifiedDataChannel/Intention;", &ani_field_intention_spec_cls);
        ani_enum_item ani_field_intention_spec;
        env->Enum_GetEnumItemByIndex(ani_field_intention_spec_cls, (ani_size)(*cpp_obj.intention).get_key(), &ani_field_intention_spec);
        ani_field_intention = ani_field_intention_spec;
    }
    ani_ref ani_field_key;
    if (!cpp_obj.key) {
        env->GetUndefined(&ani_field_key);
    }
    else {
        ani_string ani_field_key_spec;
        env->String_NewUTF8((*cpp_obj.key).c_str(), (*cpp_obj.key).size(), &ani_field_key_spec);
        ani_field_key = ani_field_key_spec;
    }
    ani_object ani_obj;
    env->Object_New(TH_ANI_FIND_CLASS(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Options_inner;"), TH_ANI_FIND_CLASS_METHOD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Options_inner;", "<ctor>", nullptr), &ani_obj, ani_field_intention, ani_field_key);
    return ani_obj;
}
