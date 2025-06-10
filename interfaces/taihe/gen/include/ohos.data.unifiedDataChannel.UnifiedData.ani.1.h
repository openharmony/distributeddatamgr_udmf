#pragma once
#include "ohos.data.unifiedDataChannel.UnifiedData.ani.0.h"
#include "ohos.data.unifiedDataChannel.UnifiedData.proj.2.hpp"
#include "ohos.data.unifiedDataChannel.AllRecords.ani.1.h"
inline ::ohos::data::unifiedDataChannel::UnifiedData ohos_data_unifiedDataChannel_UnifiedData_fromANI(ani_env* env, ani_object ani_obj) {
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
        void AddRecord(::ohos::data::unifiedDataChannel::AllRecords const& cpp_arg_unifiedRecord) {
            ::taihe::env_guard guard;
            ani_env *env = guard.get_env();
            ani_ref ani_arg_unifiedRecord = ohos_data_unifiedDataChannel_AllRecords_intoANI(env, cpp_arg_unifiedRecord);
            env->Object_CallMethod_Void(static_cast<ani_object>(this->ref), TH_ANI_FIND_CLASS_METHOD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/UnifiedData;", "addRecord", nullptr), ani_arg_unifiedRecord);
        }
        ::taihe::array<::ohos::data::unifiedDataChannel::AllRecords> GetRecords() {
            ::taihe::env_guard guard;
            ani_env *env = guard.get_env();
            ani_array_ref ani_result;
            env->Object_CallMethod_Ref(static_cast<ani_object>(this->ref), TH_ANI_FIND_CLASS_METHOD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/UnifiedData;", "getRecords", nullptr), reinterpret_cast<ani_ref*>(&ani_result));
            size_t cpp_result_size;
            env->Array_GetLength(ani_result, &cpp_result_size);
            ::ohos::data::unifiedDataChannel::AllRecords* cpp_result_buffer = reinterpret_cast<::ohos::data::unifiedDataChannel::AllRecords*>(malloc(cpp_result_size * sizeof(::ohos::data::unifiedDataChannel::AllRecords)));
            for (size_t cpp_result_buffer_i = 0; cpp_result_buffer_i < cpp_result_size; cpp_result_buffer_i++) {
                ani_ref cpp_result_buffer_ani_item;
                env->Array_Get_Ref(ani_result, cpp_result_buffer_i, reinterpret_cast<ani_ref*>(&cpp_result_buffer_ani_item));
                ::ohos::data::unifiedDataChannel::AllRecords cpp_result_buffer_cpp_item = ohos_data_unifiedDataChannel_AllRecords_fromANI(env, cpp_result_buffer_ani_item);
                new (&cpp_result_buffer[cpp_result_buffer_i]) ::ohos::data::unifiedDataChannel::AllRecords(std::move(cpp_result_buffer_cpp_item));
            }
            ::taihe::array<::ohos::data::unifiedDataChannel::AllRecords> cpp_result(cpp_result_buffer, cpp_result_size);
            return cpp_result;
        }
        int64_t GetInner() {
            ::taihe::env_guard guard;
            ani_env *env = guard.get_env();
            ani_long ani_result;
            env->Object_CallMethod_Long(static_cast<ani_object>(this->ref), TH_ANI_FIND_CLASS_METHOD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/UnifiedData;", "getInner", nullptr), reinterpret_cast<ani_long*>(&ani_result));
            int64_t cpp_result = (int64_t)ani_result;
            return cpp_result;
        }
    };
    return ::taihe::make_holder<cpp_impl_t, ::ohos::data::unifiedDataChannel::UnifiedData>(env, ani_obj);
}
inline ani_object ohos_data_unifiedDataChannel_UnifiedData_intoANI(ani_env* env, ::ohos::data::unifiedDataChannel::UnifiedData cpp_obj) {
    ani_long ani_vtbl_ptr = reinterpret_cast<ani_long>(cpp_obj.m_handle.vtbl_ptr);
    ani_long ani_data_ptr = reinterpret_cast<ani_long>(cpp_obj.m_handle.data_ptr);
    cpp_obj.m_handle.data_ptr = nullptr;
    ani_object ani_obj;
    env->Object_New(TH_ANI_FIND_CLASS(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/UnifiedData;"), TH_ANI_FIND_CLASS_METHOD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/UnifiedData;", "<ctor>", "JJ:V"), &ani_obj, ani_vtbl_ptr, ani_data_ptr);
    return ani_obj;
}
