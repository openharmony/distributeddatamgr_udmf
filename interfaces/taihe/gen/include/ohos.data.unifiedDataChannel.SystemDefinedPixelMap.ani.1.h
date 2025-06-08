#pragma once
#include "ohos.data.unifiedDataChannel.SystemDefinedPixelMap.ani.0.h"
#include "ohos.data.unifiedDataChannel.SystemDefinedPixelMap.proj.2.hpp"
#include "ohos.data.unifiedDataChannel.ValueType.ani.1.h"
#include "ohos.data.unifiedDataChannel.DetailsValue.ani.1.h"
inline ::ohos::data::unifiedDataChannel::SystemDefinedPixelMap ohos_data_unifiedDataChannel_SystemDefinedPixelMap_fromANI(ani_env* env, ani_object ani_obj) {
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
            env->Object_CallMethod_Ref(static_cast<ani_object>(this->ref), TH_ANI_FIND_CLASS_METHOD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedPixelMap;", "getType", nullptr), reinterpret_cast<ani_ref*>(&ani_result));
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
            env->Object_CallMethod_Ref(static_cast<ani_object>(this->ref), TH_ANI_FIND_CLASS_METHOD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedPixelMap;", "getValue", nullptr), reinterpret_cast<ani_ref*>(&ani_result));
            ::ohos::data::unifiedDataChannel::ValueType cpp_result = ohos_data_unifiedDataChannel_ValueType_fromANI(env, ani_result);
            return cpp_result;
        }
        ::taihe::optional<::taihe::map<::taihe::string, ::ohos::data::unifiedDataChannel::DetailsValue>> GetDetails() {
            ::taihe::env_guard guard;
            ani_env *env = guard.get_env();
            ani_ref ani_result;
            env->Object_CallMethod_Ref(static_cast<ani_object>(this->ref), TH_ANI_FIND_CLASS_METHOD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedPixelMap;", "<get>details", nullptr), reinterpret_cast<ani_ref*>(&ani_result));
            ani_boolean cpp_result_flag;
            ::taihe::map<::taihe::string, ::ohos::data::unifiedDataChannel::DetailsValue>* cpp_result_ptr = nullptr;
            env->Reference_IsUndefined(ani_result, &cpp_result_flag);
            if (!cpp_result_flag) {
                ani_ref cpp_result_spec_iter;
                env->Object_CallMethod_Ref(static_cast<ani_object>(ani_result), TH_ANI_FIND_CLASS_METHOD(env, "Lescompat/Record;", "$_iterator", nullptr), &cpp_result_spec_iter);
                ::taihe::map<::taihe::string, ::ohos::data::unifiedDataChannel::DetailsValue> cpp_result_spec;
                while (true) {
                    ani_ref cpp_result_spec_next;
                    ani_boolean cpp_result_spec_done;
                    env->Object_CallMethod_Ref(static_cast<ani_object>(cpp_result_spec_iter), TH_ANI_FIND_CLASS_METHOD(env, "Lescompat/MapIterator;", "next", nullptr), &cpp_result_spec_next);
                    env->Object_GetField_Boolean(static_cast<ani_object>(cpp_result_spec_next), TH_ANI_FIND_CLASS_FIELD(env, "Lescompat/IteratorResult;", "done"), &cpp_result_spec_done);
                    if (cpp_result_spec_done) {;
                        break;
                    };
                    ani_ref cpp_result_spec_item;
                    env->Object_GetField_Ref(static_cast<ani_object>(cpp_result_spec_next),  TH_ANI_FIND_CLASS_FIELD(env, "Lescompat/IteratorResult;", "value"), &cpp_result_spec_item);
                    ani_ref cpp_result_spec_ani_key;
                    env->TupleValue_GetItem_Ref(static_cast<ani_tuple_value>(cpp_result_spec_item), 0, &cpp_result_spec_ani_key);
                    ani_ref cpp_result_spec_ani_val;
                    env->TupleValue_GetItem_Ref(static_cast<ani_tuple_value>(cpp_result_spec_item), 1, &cpp_result_spec_ani_val);
                    ani_size cpp_result_spec_cpp_key_len;
                    env->String_GetUTF8Size(static_cast<ani_string>(cpp_result_spec_ani_key), &cpp_result_spec_cpp_key_len);
                    TString cpp_result_spec_cpp_key_tstr;
                    char* cpp_result_spec_cpp_key_buf = tstr_initialize(&cpp_result_spec_cpp_key_tstr, cpp_result_spec_cpp_key_len + 1);
                    env->String_GetUTF8(static_cast<ani_string>(cpp_result_spec_ani_key), cpp_result_spec_cpp_key_buf, cpp_result_spec_cpp_key_len + 1, &cpp_result_spec_cpp_key_len);
                    cpp_result_spec_cpp_key_buf[cpp_result_spec_cpp_key_len] = '\0';
                    cpp_result_spec_cpp_key_tstr.length = cpp_result_spec_cpp_key_len;
                    ::taihe::string cpp_result_spec_cpp_key = ::taihe::string(cpp_result_spec_cpp_key_tstr);
                    ::ohos::data::unifiedDataChannel::DetailsValue cpp_result_spec_cpp_val = ohos_data_unifiedDataChannel_DetailsValue_fromANI(env, static_cast<ani_ref>(cpp_result_spec_ani_val));
                    cpp_result_spec.emplace(cpp_result_spec_cpp_key, cpp_result_spec_cpp_val);
                }
                cpp_result_ptr = new ::taihe::map<::taihe::string, ::ohos::data::unifiedDataChannel::DetailsValue>(std::move(cpp_result_spec));
            };
            ::taihe::optional<::taihe::map<::taihe::string, ::ohos::data::unifiedDataChannel::DetailsValue>> cpp_result(cpp_result_ptr);
            return cpp_result;
        }
        void SetDetails(::taihe::map_view<::taihe::string, ::ohos::data::unifiedDataChannel::DetailsValue> cpp_arg_details) {
            ::taihe::env_guard guard;
            ani_env *env = guard.get_env();
            ani_object ani_arg_details;
            env->Object_New(TH_ANI_FIND_CLASS(env, "Lescompat/Record;"), TH_ANI_FIND_CLASS_METHOD(env, "Lescompat/Record;", "<ctor>", nullptr), &ani_arg_details);
            for (const auto& [ani_arg_details_cpp_key, ani_arg_details_cpp_val] : cpp_arg_details) {
                ani_string ani_arg_details_ani_key;
                env->String_NewUTF8(ani_arg_details_cpp_key.c_str(), ani_arg_details_cpp_key.size(), &ani_arg_details_ani_key);
                ani_ref ani_arg_details_ani_val = ohos_data_unifiedDataChannel_DetailsValue_intoANI(env, ani_arg_details_cpp_val);
                env->Object_CallMethod_Void(ani_arg_details, TH_ANI_FIND_CLASS_METHOD(env, "Lescompat/Record;", "$_set", nullptr), ani_arg_details_ani_key, ani_arg_details_ani_val);
            }
            env->Object_CallMethod_Void(static_cast<ani_object>(this->ref), TH_ANI_FIND_CLASS_METHOD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedPixelMap;", "<set>details", nullptr), ani_arg_details);
        }
        ::taihe::optional<::taihe::array<uint8_t>> GetRawData() {
            ::taihe::env_guard guard;
            ani_env *env = guard.get_env();
            ani_ref ani_result;
            env->Object_CallMethod_Ref(static_cast<ani_object>(this->ref), TH_ANI_FIND_CLASS_METHOD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedPixelMap;", "<get>rawData", nullptr), reinterpret_cast<ani_ref*>(&ani_result));
            ani_boolean cpp_result_flag;
            ::taihe::array<uint8_t>* cpp_result_ptr = nullptr;
            env->Reference_IsUndefined(ani_result, &cpp_result_flag);
            if (!cpp_result_flag) {
                ani_double cpp_result_spec_bylen;
                ani_double cpp_result_spec_byoff;
                ani_arraybuffer cpp_result_spec_arrbuf;
                env->Object_GetPropertyByName_Double(static_cast<ani_object>(ani_result), "byteLength", &cpp_result_spec_bylen);
                env->Object_GetPropertyByName_Double(static_cast<ani_object>(ani_result), "byteOffset", &cpp_result_spec_byoff);
                env->Object_GetPropertyByName_Ref(static_cast<ani_object>(ani_result), "buffer", reinterpret_cast<ani_ref*>(&cpp_result_spec_arrbuf));
                char* cpp_result_spec_data = nullptr;
                size_t cpp_result_spec_length = 0;
                env->ArrayBuffer_GetInfo(cpp_result_spec_arrbuf, reinterpret_cast<void**>(&cpp_result_spec_data), &cpp_result_spec_length);
                ::taihe::array_view<uint8_t> cpp_result_spec(reinterpret_cast<uint8_t*>(cpp_result_spec_data + (size_t)cpp_result_spec_byoff), (size_t)cpp_result_spec_bylen / (sizeof(uint8_t) / sizeof(char)));
                cpp_result_ptr = new ::taihe::array<uint8_t>(std::move(cpp_result_spec));
            };
            ::taihe::optional<::taihe::array<uint8_t>> cpp_result(cpp_result_ptr);
            return cpp_result;
        }
        void SetRawData(::taihe::array_view<uint8_t> cpp_arg_rawData) {
            ::taihe::env_guard guard;
            ani_env *env = guard.get_env();
            char* ani_arg_rawData_data = nullptr;
            ani_arraybuffer ani_arg_rawData_arrbuf;
            env->CreateArrayBuffer(cpp_arg_rawData.size() * (sizeof(uint8_t) / sizeof(char)), reinterpret_cast<void**>(&ani_arg_rawData_data), &ani_arg_rawData_arrbuf);
            memcpy(ani_arg_rawData_data, cpp_arg_rawData.data(), cpp_arg_rawData.size() * (sizeof(uint8_t) / sizeof(char)));
            ani_ref ani_arg_rawData_bylen;
            env->GetUndefined(&ani_arg_rawData_bylen);
            ani_ref ani_arg_rawData_byoff;
            env->GetUndefined(&ani_arg_rawData_byoff);
            ani_object ani_arg_rawData;
            env->Object_New(TH_ANI_FIND_CLASS(env, "Lescompat/Uint8Array;"), TH_ANI_FIND_CLASS_METHOD(env, "Lescompat/Uint8Array;", "<ctor>", "Lescompat/Buffer;Lstd/core/Double;Lstd/core/Double;:V"), &ani_arg_rawData, ani_arg_rawData_arrbuf, ani_arg_rawData_bylen, ani_arg_rawData_byoff);
            env->Object_CallMethod_Void(static_cast<ani_object>(this->ref), TH_ANI_FIND_CLASS_METHOD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedPixelMap;", "<set>rawData", nullptr), ani_arg_rawData);
        }
        int64_t GetInner() {
            ::taihe::env_guard guard;
            ani_env *env = guard.get_env();
            ani_long ani_result;
            env->Object_CallMethod_Long(static_cast<ani_object>(this->ref), TH_ANI_FIND_CLASS_METHOD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedPixelMap;", "getInner", nullptr), reinterpret_cast<ani_long*>(&ani_result));
            int64_t cpp_result = (int64_t)ani_result;
            return cpp_result;
        }
    };
    return ::taihe::make_holder<cpp_impl_t, ::ohos::data::unifiedDataChannel::SystemDefinedPixelMap>(env, ani_obj);
}
inline ani_object ohos_data_unifiedDataChannel_SystemDefinedPixelMap_intoANI(ani_env* env, ::ohos::data::unifiedDataChannel::SystemDefinedPixelMap cpp_obj) {
    ani_long ani_vtbl_ptr = reinterpret_cast<ani_long>(cpp_obj.m_handle.vtbl_ptr);
    ani_long ani_data_ptr = reinterpret_cast<ani_long>(cpp_obj.m_handle.data_ptr);
    cpp_obj.m_handle.data_ptr = nullptr;
    ani_object ani_obj;
    env->Object_New(TH_ANI_FIND_CLASS(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedPixelMap;"), TH_ANI_FIND_CLASS_METHOD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedPixelMap;", "<ctor>", "JJ:V"), &ani_obj, ani_vtbl_ptr, ani_data_ptr);
    return ani_obj;
}
