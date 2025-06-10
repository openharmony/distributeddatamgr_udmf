#pragma once
#include "ohos.data.unifiedDataChannel.DetailsValue.ani.0.h"
#include "ohos.data.unifiedDataChannel.DetailsValue.proj.1.hpp"
inline ::ohos::data::unifiedDataChannel::DetailsValue ohos_data_unifiedDataChannel_DetailsValue_fromANI(ani_env* env, ani_ref ani_value) {
    ani_boolean ani_is_number;
    env->Object_InstanceOf(static_cast<ani_object>(ani_value), TH_ANI_FIND_CLASS(env, "Lstd/core/Double;"), &ani_is_number);
    if (ani_is_number) {
        ani_double cpp_field_number_ani;
        env->Object_CallMethod_Double((ani_object)ani_value, TH_ANI_FIND_CLASS_METHOD(env, "Lstd/core/Double;", "unboxed", ":D"), &cpp_field_number_ani);
        double cpp_field_number = (double)cpp_field_number_ani;
        return ::ohos::data::unifiedDataChannel::DetailsValue(::taihe::static_tag<::ohos::data::unifiedDataChannel::DetailsValue::tag_t::number>, std::move(cpp_field_number));
    }
    ani_boolean ani_is_string;
    env->Object_InstanceOf(static_cast<ani_object>(ani_value), TH_ANI_FIND_CLASS(env, "Lstd/core/String;"), &ani_is_string);
    if (ani_is_string) {
        ani_size cpp_field_string_len;
        env->String_GetUTF8Size(static_cast<ani_string>(ani_value), &cpp_field_string_len);
        TString cpp_field_string_tstr;
        char* cpp_field_string_buf = tstr_initialize(&cpp_field_string_tstr, cpp_field_string_len + 1);
        env->String_GetUTF8(static_cast<ani_string>(ani_value), cpp_field_string_buf, cpp_field_string_len + 1, &cpp_field_string_len);
        cpp_field_string_buf[cpp_field_string_len] = '\0';
        cpp_field_string_tstr.length = cpp_field_string_len;
        ::taihe::string cpp_field_string = ::taihe::string(cpp_field_string_tstr);
        return ::ohos::data::unifiedDataChannel::DetailsValue(::taihe::static_tag<::ohos::data::unifiedDataChannel::DetailsValue::tag_t::string>, std::move(cpp_field_string));
    }
    ani_boolean ani_is_Uint8Array;
    env->Object_InstanceOf(static_cast<ani_object>(ani_value), TH_ANI_FIND_CLASS(env, "Lescompat/Uint8Array;"), &ani_is_Uint8Array);
    if (ani_is_Uint8Array) {
        ani_double cpp_field_Uint8Array_bylen;
        ani_double cpp_field_Uint8Array_byoff;
        ani_arraybuffer cpp_field_Uint8Array_arrbuf;
        env->Object_GetPropertyByName_Double(static_cast<ani_object>(ani_value), "byteLength", &cpp_field_Uint8Array_bylen);
        env->Object_GetPropertyByName_Double(static_cast<ani_object>(ani_value), "byteOffset", &cpp_field_Uint8Array_byoff);
        env->Object_GetPropertyByName_Ref(static_cast<ani_object>(ani_value), "buffer", reinterpret_cast<ani_ref*>(&cpp_field_Uint8Array_arrbuf));
        char* cpp_field_Uint8Array_data = nullptr;
        size_t cpp_field_Uint8Array_length = 0;
        env->ArrayBuffer_GetInfo(cpp_field_Uint8Array_arrbuf, reinterpret_cast<void**>(&cpp_field_Uint8Array_data), &cpp_field_Uint8Array_length);
        ::taihe::array_view<uint8_t> cpp_field_Uint8Array(reinterpret_cast<uint8_t*>(cpp_field_Uint8Array_data + (size_t)cpp_field_Uint8Array_byoff), (size_t)cpp_field_Uint8Array_bylen / (sizeof(uint8_t) / sizeof(char)));
        return ::ohos::data::unifiedDataChannel::DetailsValue(::taihe::static_tag<::ohos::data::unifiedDataChannel::DetailsValue::tag_t::Uint8Array>, std::move(cpp_field_Uint8Array));
    }
    __builtin_unreachable();
}
inline ani_ref ohos_data_unifiedDataChannel_DetailsValue_intoANI(ani_env* env, ::ohos::data::unifiedDataChannel::DetailsValue const& cpp_value) {
    ani_ref ani_value;
    switch (cpp_value.get_tag()) {
    case ::ohos::data::unifiedDataChannel::DetailsValue::tag_t::number: {
        ani_object ani_field_number;
        ani_double ani_field_number_ani = (double)cpp_value.get_number_ref();
        env->Object_New(TH_ANI_FIND_CLASS(env, "Lstd/core/Double;"), TH_ANI_FIND_CLASS_METHOD(env, "Lstd/core/Double;", "<ctor>", "D:V"), &ani_field_number, ani_field_number_ani);
        ani_value = ani_field_number;
        break;
    }
    case ::ohos::data::unifiedDataChannel::DetailsValue::tag_t::string: {
        ani_string ani_field_string;
        env->String_NewUTF8(cpp_value.get_string_ref().c_str(), cpp_value.get_string_ref().size(), &ani_field_string);
        ani_value = ani_field_string;
        break;
    }
    case ::ohos::data::unifiedDataChannel::DetailsValue::tag_t::Uint8Array: {
        char* ani_field_Uint8Array_data = nullptr;
        ani_arraybuffer ani_field_Uint8Array_arrbuf;
        env->CreateArrayBuffer(cpp_value.get_Uint8Array_ref().size() * (sizeof(uint8_t) / sizeof(char)), reinterpret_cast<void**>(&ani_field_Uint8Array_data), &ani_field_Uint8Array_arrbuf);
        memcpy(ani_field_Uint8Array_data, cpp_value.get_Uint8Array_ref().data(), cpp_value.get_Uint8Array_ref().size() * (sizeof(uint8_t) / sizeof(char)));
        ani_ref ani_field_Uint8Array_bylen;
        env->GetUndefined(&ani_field_Uint8Array_bylen);
        ani_ref ani_field_Uint8Array_byoff;
        env->GetUndefined(&ani_field_Uint8Array_byoff);
        ani_object ani_field_Uint8Array;
        env->Object_New(TH_ANI_FIND_CLASS(env, "Lescompat/Uint8Array;"), TH_ANI_FIND_CLASS_METHOD(env, "Lescompat/Uint8Array;", "<ctor>", "Lescompat/Buffer;Lstd/core/Double;Lstd/core/Double;:V"), &ani_field_Uint8Array, ani_field_Uint8Array_arrbuf, ani_field_Uint8Array_bylen, ani_field_Uint8Array_byoff);
        ani_value = ani_field_Uint8Array;
        break;
    }
    }
    return ani_value;
}
