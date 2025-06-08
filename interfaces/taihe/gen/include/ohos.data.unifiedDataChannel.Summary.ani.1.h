#pragma once
#include "ohos.data.unifiedDataChannel.Summary.ani.0.h"
#include "ohos.data.unifiedDataChannel.Summary.proj.1.hpp"
#pragma clang diagnostic ignored "-Wmissing-braces"
inline ::ohos::data::unifiedDataChannel::Summary ohos_data_unifiedDataChannel_Summary_fromANI(ani_env* env, ani_object ani_obj) {
    ani_object ani_field_summary;
    env->Object_GetField_Ref(ani_obj, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Summary;", "summary"), reinterpret_cast<ani_ref*>(&ani_field_summary));
    ani_ref cpp_field_summary_iter;
    env->Object_CallMethod_Ref(ani_field_summary, TH_ANI_FIND_CLASS_METHOD(env, "Lescompat/Record;", "$_iterator", nullptr), &cpp_field_summary_iter);
    ::taihe::map<::taihe::string, double> cpp_field_summary;
    while (true) {
        ani_ref cpp_field_summary_next;
        ani_boolean cpp_field_summary_done;
        env->Object_CallMethod_Ref(static_cast<ani_object>(cpp_field_summary_iter), TH_ANI_FIND_CLASS_METHOD(env, "Lescompat/MapIterator;", "next", nullptr), &cpp_field_summary_next);
        env->Object_GetField_Boolean(static_cast<ani_object>(cpp_field_summary_next), TH_ANI_FIND_CLASS_FIELD(env, "Lescompat/IteratorResult;", "done"), &cpp_field_summary_done);
        if (cpp_field_summary_done) {;
            break;
        };
        ani_ref cpp_field_summary_item;
        env->Object_GetField_Ref(static_cast<ani_object>(cpp_field_summary_next),  TH_ANI_FIND_CLASS_FIELD(env, "Lescompat/IteratorResult;", "value"), &cpp_field_summary_item);
        ani_ref cpp_field_summary_ani_key;
        env->TupleValue_GetItem_Ref(static_cast<ani_tuple_value>(cpp_field_summary_item), 0, &cpp_field_summary_ani_key);
        ani_ref cpp_field_summary_ani_val;
        env->TupleValue_GetItem_Ref(static_cast<ani_tuple_value>(cpp_field_summary_item), 1, &cpp_field_summary_ani_val);
        ani_size cpp_field_summary_cpp_key_len;
        env->String_GetUTF8Size(static_cast<ani_string>(cpp_field_summary_ani_key), &cpp_field_summary_cpp_key_len);
        TString cpp_field_summary_cpp_key_tstr;
        char* cpp_field_summary_cpp_key_buf = tstr_initialize(&cpp_field_summary_cpp_key_tstr, cpp_field_summary_cpp_key_len + 1);
        env->String_GetUTF8(static_cast<ani_string>(cpp_field_summary_ani_key), cpp_field_summary_cpp_key_buf, cpp_field_summary_cpp_key_len + 1, &cpp_field_summary_cpp_key_len);
        cpp_field_summary_cpp_key_buf[cpp_field_summary_cpp_key_len] = '\0';
        cpp_field_summary_cpp_key_tstr.length = cpp_field_summary_cpp_key_len;
        ::taihe::string cpp_field_summary_cpp_key = ::taihe::string(cpp_field_summary_cpp_key_tstr);
        ani_double cpp_field_summary_cpp_val_ani;
        env->Object_CallMethod_Double((ani_object)cpp_field_summary_ani_val, TH_ANI_FIND_CLASS_METHOD(env, "Lstd/core/Double;", "unboxed", ":D"), &cpp_field_summary_cpp_val_ani);
        double cpp_field_summary_cpp_val = (double)cpp_field_summary_cpp_val_ani;
        cpp_field_summary.emplace(cpp_field_summary_cpp_key, cpp_field_summary_cpp_val);
    }
    ani_double ani_field_totalSize;
    env->Object_GetField_Double(ani_obj, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Summary;", "totalSize"), reinterpret_cast<ani_double*>(&ani_field_totalSize));
    double cpp_field_totalSize = (double)ani_field_totalSize;
    return ::ohos::data::unifiedDataChannel::Summary{std::move(cpp_field_summary), std::move(cpp_field_totalSize)};
}
inline ani_object ohos_data_unifiedDataChannel_Summary_intoANI(ani_env* env, ::ohos::data::unifiedDataChannel::Summary const& cpp_obj) {
    ani_object ani_field_summary;
    env->Object_New(TH_ANI_FIND_CLASS(env, "Lescompat/Record;"), TH_ANI_FIND_CLASS_METHOD(env, "Lescompat/Record;", "<ctor>", nullptr), &ani_field_summary);
    for (const auto& [ani_field_summary_cpp_key, ani_field_summary_cpp_val] : cpp_obj.summary) {
        ani_string ani_field_summary_ani_key;
        env->String_NewUTF8(ani_field_summary_cpp_key.c_str(), ani_field_summary_cpp_key.size(), &ani_field_summary_ani_key);
        ani_object ani_field_summary_ani_val;
        ani_double ani_field_summary_ani_val_ani = (double)ani_field_summary_cpp_val;
        env->Object_New(TH_ANI_FIND_CLASS(env, "Lstd/core/Double;"), TH_ANI_FIND_CLASS_METHOD(env, "Lstd/core/Double;", "<ctor>", "D:V"), &ani_field_summary_ani_val, ani_field_summary_ani_val_ani);
        env->Object_CallMethod_Void(ani_field_summary, TH_ANI_FIND_CLASS_METHOD(env, "Lescompat/Record;", "$_set", nullptr), ani_field_summary_ani_key, ani_field_summary_ani_val);
    }
    ani_double ani_field_totalSize = (double)cpp_obj.totalSize;
    ani_object ani_obj;
    env->Object_New(TH_ANI_FIND_CLASS(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Summary;"), TH_ANI_FIND_CLASS_METHOD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Summary;", "<ctor>", nullptr), &ani_obj, ani_field_summary, ani_field_totalSize);
    return ani_obj;
}
