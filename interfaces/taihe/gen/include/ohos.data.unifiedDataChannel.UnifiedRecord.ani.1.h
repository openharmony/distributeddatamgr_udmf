#pragma once
#include "ohos.data.unifiedDataChannel.UnifiedRecord.ani.0.h"
#include "ohos.data.unifiedDataChannel.UnifiedRecord.proj.2.hpp"
#include "ohos.data.unifiedDataChannel.ValueType.ani.1.h"
inline ::ohos::data::unifiedDataChannel::UnifiedRecord ohos_data_unifiedDataChannel_UnifiedRecord_fromANI(ani_env* env, ani_object ani_obj) {
    struct cpp_impl_t {
        ani_ref ref;
        cpp_impl_t(ani_env* env, ani_object obj) {
            env->GlobalReference_Create(obj, &this->ref);
        }
        ~cpp_impl_t() {
            ::taihe::env_guard guard;
            ani_env *env = guard.get_env();
            env->GlobalReference_Delete(this->ref);
        }
        ::taihe::string GetType() {
            ::taihe::env_guard guard;
            ani_env *env = guard.get_env();
            ani_string ani_result;
            env->Object_CallMethod_Ref(static_cast<ani_object>(this->ref), TH_ANI_FIND_CLASS_METHOD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/UnifiedRecord;", "getType", nullptr), reinterpret_cast<ani_ref*>(&ani_result));
            ani_size cpp_result_len;
            env->String_GetUTF8Size(ani_result, &cpp_result_len);
            TString cpp_result_tstr;
            char* cpp_result_buf = tstr_initialize(&cpp_result_tstr, cpp_result_len + 1);
            env->String_GetUTF8(ani_result, cpp_result_buf, cpp_result_len + 1, &cpp_result_len);
            cpp_result_buf[cpp_result_len] = '\0';
            cpp_result_tstr.length = cpp_result_len;
            ::taihe::string cpp_result = ::taihe::string(cpp_result_tstr);
            return cpp_result;
        }
        ::ohos::data::unifiedDataChannel::ValueType GetValue() {
            ::taihe::env_guard guard;
            ani_env *env = guard.get_env();
            ani_ref ani_result;
            env->Object_CallMethod_Ref(static_cast<ani_object>(this->ref), TH_ANI_FIND_CLASS_METHOD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/UnifiedRecord;", "getValue", nullptr), reinterpret_cast<ani_ref*>(&ani_result));
            ::ohos::data::unifiedDataChannel::ValueType cpp_result = ohos_data_unifiedDataChannel_ValueType_fromANI(env, ani_result);
            return cpp_result;
        }
        int64_t GetInner() {
            ::taihe::env_guard guard;
            ani_env *env = guard.get_env();
            ani_long ani_result;
            env->Object_CallMethod_Long(static_cast<ani_object>(this->ref), TH_ANI_FIND_CLASS_METHOD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/UnifiedRecord;", "getInner", nullptr), reinterpret_cast<ani_long*>(&ani_result));
            int64_t cpp_result = (int64_t)ani_result;
            return cpp_result;
        }
    };
    return ::taihe::make_holder<cpp_impl_t, ::ohos::data::unifiedDataChannel::UnifiedRecord>(env, ani_obj);
}
inline ani_object ohos_data_unifiedDataChannel_UnifiedRecord_intoANI(ani_env* env, ::ohos::data::unifiedDataChannel::UnifiedRecord cpp_obj) {
    ani_long ani_vtbl_ptr = reinterpret_cast<ani_long>(cpp_obj.m_handle.vtbl_ptr);
    ani_long ani_data_ptr = reinterpret_cast<ani_long>(cpp_obj.m_handle.data_ptr);
    cpp_obj.m_handle.data_ptr = nullptr;
    ani_object ani_obj;
    env->Object_New(TH_ANI_FIND_CLASS(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/UnifiedRecord;"), TH_ANI_FIND_CLASS_METHOD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/UnifiedRecord;", "<ctor>", "JJ:V"), &ani_obj, ani_vtbl_ptr, ani_data_ptr);
    return ani_obj;
}
