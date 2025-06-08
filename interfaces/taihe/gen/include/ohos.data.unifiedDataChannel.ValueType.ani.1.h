#pragma once
#include "ohos.data.unifiedDataChannel.ValueType.ani.0.h"
#include "ohos.data.unifiedDataChannel.ValueType.proj.1.hpp"
inline ::ohos::data::unifiedDataChannel::ValueType ohos_data_unifiedDataChannel_ValueType_fromANI(ani_env* env, ani_ref ani_value) {
    ani_boolean ani_is_nullType;
    env->Reference_IsNull(ani_value, &ani_is_nullType);
    if (ani_is_nullType) {
        return ::ohos::data::unifiedDataChannel::ValueType(::taihe::static_tag<::ohos::data::unifiedDataChannel::ValueType::tag_t::nullType>);
    }
    ani_boolean ani_is_undefinedType;
    env->Reference_IsUndefined(ani_value, &ani_is_undefinedType);
    if (ani_is_undefinedType) {
        return ::ohos::data::unifiedDataChannel::ValueType(::taihe::static_tag<::ohos::data::unifiedDataChannel::ValueType::tag_t::undefinedType>);
    }
    ani_boolean ani_is_number;
    env->Object_InstanceOf(static_cast<ani_object>(ani_value), TH_ANI_FIND_CLASS(env, "Lstd/core/Double;"), &ani_is_number);
    if (ani_is_number) {
        ani_double cpp_field_number_ani;
        env->Object_CallMethod_Double((ani_object)ani_value, TH_ANI_FIND_CLASS_METHOD(env, "Lstd/core/Double;", "unboxed", ":D"), &cpp_field_number_ani);
        double cpp_field_number = (double)cpp_field_number_ani;
        return ::ohos::data::unifiedDataChannel::ValueType(::taihe::static_tag<::ohos::data::unifiedDataChannel::ValueType::tag_t::number>, std::move(cpp_field_number));
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
        return ::ohos::data::unifiedDataChannel::ValueType(::taihe::static_tag<::ohos::data::unifiedDataChannel::ValueType::tag_t::string>, std::move(cpp_field_string));
    }
    ani_boolean ani_is_boolean;
    env->Object_InstanceOf(static_cast<ani_object>(ani_value), TH_ANI_FIND_CLASS(env, "Lstd/core/Boolean;"), &ani_is_boolean);
    if (ani_is_boolean) {
        ani_boolean cpp_field_boolean_ani;
        env->Object_CallMethod_Boolean((ani_object)ani_value, TH_ANI_FIND_CLASS_METHOD(env, "Lstd/core/Boolean;", "unboxed", ":Z"), &cpp_field_boolean_ani);
        bool cpp_field_boolean = (bool)cpp_field_boolean_ani;
        return ::ohos::data::unifiedDataChannel::ValueType(::taihe::static_tag<::ohos::data::unifiedDataChannel::ValueType::tag_t::boolean>, std::move(cpp_field_boolean));
    }
    ani_boolean ani_is_ArrayBuffer;
    env->Object_InstanceOf(static_cast<ani_object>(ani_value), TH_ANI_FIND_CLASS(env, "Lescompat/ArrayBuffer;"), &ani_is_ArrayBuffer);
    if (ani_is_ArrayBuffer) {
        char* cpp_field_ArrayBuffer_data = nullptr;
        size_t cpp_field_ArrayBuffer_length = 0;
        env->ArrayBuffer_GetInfo(static_cast<ani_arraybuffer>(ani_value), reinterpret_cast<void**>(&cpp_field_ArrayBuffer_data), &cpp_field_ArrayBuffer_length);
        ::taihe::array_view<uint8_t> cpp_field_ArrayBuffer(reinterpret_cast<uint8_t*>(cpp_field_ArrayBuffer_data), cpp_field_ArrayBuffer_length);
        return ::ohos::data::unifiedDataChannel::ValueType(::taihe::static_tag<::ohos::data::unifiedDataChannel::ValueType::tag_t::ArrayBuffer>, std::move(cpp_field_ArrayBuffer));
    }
    ani_boolean ani_is_object;
    env->Object_InstanceOf(static_cast<ani_object>(ani_value), TH_ANI_FIND_CLASS(env, "Lstd/core/Object;"), &ani_is_object);
    if (ani_is_object) {
        uintptr_t cpp_field_object = (uintptr_t)static_cast<ani_object>(ani_value);
        return ::ohos::data::unifiedDataChannel::ValueType(::taihe::static_tag<::ohos::data::unifiedDataChannel::ValueType::tag_t::object>, std::move(cpp_field_object));
    }
    __builtin_unreachable();
}
inline ani_ref ohos_data_unifiedDataChannel_ValueType_intoANI(ani_env* env, ::ohos::data::unifiedDataChannel::ValueType const& cpp_value) {
    ani_ref ani_value;
    switch (cpp_value.get_tag()) {
    case ::ohos::data::unifiedDataChannel::ValueType::tag_t::number: {
        ani_object ani_field_number;
        ani_double ani_field_number_ani = (double)cpp_value.get_number_ref();
        env->Object_New(TH_ANI_FIND_CLASS(env, "Lstd/core/Double;"), TH_ANI_FIND_CLASS_METHOD(env, "Lstd/core/Double;", "<ctor>", "D:V"), &ani_field_number, ani_field_number_ani);
        ani_value = ani_field_number;
        break;
    }
    case ::ohos::data::unifiedDataChannel::ValueType::tag_t::string: {
        ani_string ani_field_string;
        env->String_NewUTF8(cpp_value.get_string_ref().c_str(), cpp_value.get_string_ref().size(), &ani_field_string);
        ani_value = ani_field_string;
        break;
    }
    case ::ohos::data::unifiedDataChannel::ValueType::tag_t::boolean: {
        ani_object ani_field_boolean;
        ani_boolean ani_field_boolean_ani = (bool)cpp_value.get_boolean_ref();
        env->Object_New(TH_ANI_FIND_CLASS(env, "Lstd/core/Boolean;"), TH_ANI_FIND_CLASS_METHOD(env, "Lstd/core/Boolean;", "<ctor>", "Z:V"), &ani_field_boolean, ani_field_boolean_ani);
        ani_value = ani_field_boolean;
        break;
    }
    case ::ohos::data::unifiedDataChannel::ValueType::tag_t::ArrayBuffer: {
        char* ani_field_ArrayBuffer_data = nullptr;
        ani_arraybuffer ani_field_ArrayBuffer;
        env->CreateArrayBuffer(cpp_value.get_ArrayBuffer_ref().size(), reinterpret_cast<void**>(&ani_field_ArrayBuffer_data), &ani_field_ArrayBuffer);
        memcpy(ani_field_ArrayBuffer_data, cpp_value.get_ArrayBuffer_ref().data(), cpp_value.get_ArrayBuffer_ref().size());
        ani_value = ani_field_ArrayBuffer;
        break;
    }
    case ::ohos::data::unifiedDataChannel::ValueType::tag_t::nullType: {
        env->GetNull(&ani_value);
        break;
    }
    case ::ohos::data::unifiedDataChannel::ValueType::tag_t::undefinedType: {
        env->GetUndefined(&ani_value);
        break;
    }
    case ::ohos::data::unifiedDataChannel::ValueType::tag_t::object: {
        ani_object ani_field_object = (ani_object)cpp_value.get_object_ref();
        ani_value = ani_field_object;
        break;
    }
    }
    return ani_value;
}
