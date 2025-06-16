#include "ohos.data.unifiedDataChannel.ani.hpp"
#include "ohos.data.unifiedDataChannel.user.hpp"
#include "ohos.data.unifiedDataChannel.Summary.ani.1.h"
#include "ohos.data.unifiedDataChannel.UnifiedDataInner.ani.1.h"
#include "ohos.data.unifiedDataChannel.AllRecords.ani.1.h"
#include "ohos.data.unifiedDataChannel.UnifiedRecordInner.ani.1.h"
#include "ohos.data.unifiedDataChannel.ValueType.ani.1.h"
#include "ohos.data.unifiedDataChannel.FileInner.ani.1.h"
#include "ohos.data.unifiedDataChannel.FolderInner.ani.1.h"
#include "ohos.data.unifiedDataChannel.AudioInner.ani.1.h"
#include "ohos.data.unifiedDataChannel.VideoInner.ani.1.h"
#include "ohos.data.unifiedDataChannel.ImageInner.ani.1.h"
#include "ohos.data.unifiedDataChannel.TextInner.ani.1.h"
#include "ohos.data.unifiedDataChannel.HTMLInner.ani.1.h"
#include "ohos.data.unifiedDataChannel.HyperlinkInner.ani.1.h"
#include "ohos.data.unifiedDataChannel.PlainTextInner.ani.1.h"
#include "ohos.data.unifiedDataChannel.SystemDefinedRecordInner.ani.1.h"
#include "ohos.data.unifiedDataChannel.SystemDefinedFormInner.ani.1.h"
#include "ohos.data.unifiedDataChannel.SystemDefinedAppItemInner.ani.1.h"
#include "ohos.data.unifiedDataChannel.SystemDefinedPixelMapInner.ani.1.h"
#include "ohos.data.unifiedDataChannel.Options.ani.1.h"
#include "taihe/object.hpp"
#include "ohos.data.unifiedDataChannel.DetailsValue.ani.1.h"
static ani_object ohos_data_unifiedDataChannel_CreateSummary_ANIFunc([[maybe_unused]] ani_env *env) {
    ::ohos::data::unifiedDataChannel::Summary cpp_result = ::ohos::data::unifiedDataChannel::CreateSummary();
    if (::taihe::has_error()) { return ani_object{}; }
    ani_object ani_result = ohos_data_unifiedDataChannel_Summary_intoANI(env, cpp_result);
    return ani_result;
}
static ani_object ohos_data_unifiedDataChannel_CreateUnifiedData_ANIFunc([[maybe_unused]] ani_env *env) {
    ::ohos::data::unifiedDataChannel::UnifiedDataInner cpp_result = ::ohos::data::unifiedDataChannel::CreateUnifiedData();
    if (::taihe::has_error()) { return ani_object{}; }
    ani_object ani_result = ohos_data_unifiedDataChannel_UnifiedDataInner_intoANI(env, cpp_result);
    return ani_result;
}
static ani_object ohos_data_unifiedDataChannel_CreateUnifiedDataWithParams_ANIFunc([[maybe_unused]] ani_env *env, ani_ref ani_arg_unifiedRecord) {
    ::ohos::data::unifiedDataChannel::AllRecords cpp_arg_unifiedRecord = ohos_data_unifiedDataChannel_AllRecords_fromANI(env, ani_arg_unifiedRecord);
    ::ohos::data::unifiedDataChannel::UnifiedDataInner cpp_result = ::ohos::data::unifiedDataChannel::CreateUnifiedDataWithParams(cpp_arg_unifiedRecord);
    if (::taihe::has_error()) { return ani_object{}; }
    ani_object ani_result = ohos_data_unifiedDataChannel_UnifiedDataInner_intoANI(env, cpp_result);
    return ani_result;
}
static ani_object ohos_data_unifiedDataChannel_CreateUnifiedRecord_ANIFunc([[maybe_unused]] ani_env *env) {
    ::ohos::data::unifiedDataChannel::UnifiedRecordInner cpp_result = ::ohos::data::unifiedDataChannel::CreateUnifiedRecord();
    if (::taihe::has_error()) { return ani_object{}; }
    ani_object ani_result = ohos_data_unifiedDataChannel_UnifiedRecordInner_intoANI(env, cpp_result);
    return ani_result;
}
static ani_object ohos_data_unifiedDataChannel_CreateUnifiedRecordWithParams_ANIFunc([[maybe_unused]] ani_env *env, ani_string ani_arg_type, ani_ref ani_arg_value) {
    ani_size cpp_arg_type_len;
    env->String_GetUTF8Size(ani_arg_type, &cpp_arg_type_len);
    TString cpp_arg_type_tstr;
    char* cpp_arg_type_buf = tstr_initialize(&cpp_arg_type_tstr, cpp_arg_type_len + 1);
    env->String_GetUTF8(ani_arg_type, cpp_arg_type_buf, cpp_arg_type_len + 1, &cpp_arg_type_len);
    cpp_arg_type_buf[cpp_arg_type_len] = '\0';
    cpp_arg_type_tstr.length = cpp_arg_type_len;
    ::taihe::string cpp_arg_type = ::taihe::string(cpp_arg_type_tstr);
    ::ohos::data::unifiedDataChannel::ValueType cpp_arg_value = ohos_data_unifiedDataChannel_ValueType_fromANI(env, ani_arg_value);
    ::ohos::data::unifiedDataChannel::UnifiedRecordInner cpp_result = ::ohos::data::unifiedDataChannel::CreateUnifiedRecordWithParams(cpp_arg_type, cpp_arg_value);
    if (::taihe::has_error()) { return ani_object{}; }
    ani_object ani_result = ohos_data_unifiedDataChannel_UnifiedRecordInner_intoANI(env, cpp_result);
    return ani_result;
}
static ani_object ohos_data_unifiedDataChannel_CreateUnifiedFile_ANIFunc([[maybe_unused]] ani_env *env) {
    ::ohos::data::unifiedDataChannel::FileInner cpp_result = ::ohos::data::unifiedDataChannel::CreateUnifiedFile();
    if (::taihe::has_error()) { return ani_object{}; }
    ani_object ani_result = ohos_data_unifiedDataChannel_FileInner_intoANI(env, cpp_result);
    return ani_result;
}
static ani_object ohos_data_unifiedDataChannel_CreateUnifiedFolder_ANIFunc([[maybe_unused]] ani_env *env) {
    ::ohos::data::unifiedDataChannel::FolderInner cpp_result = ::ohos::data::unifiedDataChannel::CreateUnifiedFolder();
    if (::taihe::has_error()) { return ani_object{}; }
    ani_object ani_result = ohos_data_unifiedDataChannel_FolderInner_intoANI(env, cpp_result);
    return ani_result;
}
static ani_object ohos_data_unifiedDataChannel_CreateUnifiedAudio_ANIFunc([[maybe_unused]] ani_env *env) {
    ::ohos::data::unifiedDataChannel::AudioInner cpp_result = ::ohos::data::unifiedDataChannel::CreateUnifiedAudio();
    if (::taihe::has_error()) { return ani_object{}; }
    ani_object ani_result = ohos_data_unifiedDataChannel_AudioInner_intoANI(env, cpp_result);
    return ani_result;
}
static ani_object ohos_data_unifiedDataChannel_CreateUnifiedVideo_ANIFunc([[maybe_unused]] ani_env *env) {
    ::ohos::data::unifiedDataChannel::VideoInner cpp_result = ::ohos::data::unifiedDataChannel::CreateUnifiedVideo();
    if (::taihe::has_error()) { return ani_object{}; }
    ani_object ani_result = ohos_data_unifiedDataChannel_VideoInner_intoANI(env, cpp_result);
    return ani_result;
}
static ani_object ohos_data_unifiedDataChannel_CreateUnifiedImage_ANIFunc([[maybe_unused]] ani_env *env) {
    ::ohos::data::unifiedDataChannel::ImageInner cpp_result = ::ohos::data::unifiedDataChannel::CreateUnifiedImage();
    if (::taihe::has_error()) { return ani_object{}; }
    ani_object ani_result = ohos_data_unifiedDataChannel_ImageInner_intoANI(env, cpp_result);
    return ani_result;
}
static ani_object ohos_data_unifiedDataChannel_CreateText_ANIFunc([[maybe_unused]] ani_env *env) {
    ::ohos::data::unifiedDataChannel::TextInner cpp_result = ::ohos::data::unifiedDataChannel::CreateText();
    if (::taihe::has_error()) { return ani_object{}; }
    ani_object ani_result = ohos_data_unifiedDataChannel_TextInner_intoANI(env, cpp_result);
    return ani_result;
}
static ani_object ohos_data_unifiedDataChannel_CreateHtml_ANIFunc([[maybe_unused]] ani_env *env) {
    ::ohos::data::unifiedDataChannel::HTMLInner cpp_result = ::ohos::data::unifiedDataChannel::CreateHtml();
    if (::taihe::has_error()) { return ani_object{}; }
    ani_object ani_result = ohos_data_unifiedDataChannel_HTMLInner_intoANI(env, cpp_result);
    return ani_result;
}
static ani_object ohos_data_unifiedDataChannel_CreateHyperlink_ANIFunc([[maybe_unused]] ani_env *env) {
    ::ohos::data::unifiedDataChannel::HyperlinkInner cpp_result = ::ohos::data::unifiedDataChannel::CreateHyperlink();
    if (::taihe::has_error()) { return ani_object{}; }
    ani_object ani_result = ohos_data_unifiedDataChannel_HyperlinkInner_intoANI(env, cpp_result);
    return ani_result;
}
static ani_object ohos_data_unifiedDataChannel_CreatePlainText_ANIFunc([[maybe_unused]] ani_env *env) {
    ::ohos::data::unifiedDataChannel::PlainTextInner cpp_result = ::ohos::data::unifiedDataChannel::CreatePlainText();
    if (::taihe::has_error()) { return ani_object{}; }
    ani_object ani_result = ohos_data_unifiedDataChannel_PlainTextInner_intoANI(env, cpp_result);
    return ani_result;
}
static ani_object ohos_data_unifiedDataChannel_CreateSystemDefinedRecord_ANIFunc([[maybe_unused]] ani_env *env) {
    ::ohos::data::unifiedDataChannel::SystemDefinedRecordInner cpp_result = ::ohos::data::unifiedDataChannel::CreateSystemDefinedRecord();
    if (::taihe::has_error()) { return ani_object{}; }
    ani_object ani_result = ohos_data_unifiedDataChannel_SystemDefinedRecordInner_intoANI(env, cpp_result);
    return ani_result;
}
static ani_object ohos_data_unifiedDataChannel_CreateSystemDefinedForm_ANIFunc([[maybe_unused]] ani_env *env) {
    ::ohos::data::unifiedDataChannel::SystemDefinedFormInner cpp_result = ::ohos::data::unifiedDataChannel::CreateSystemDefinedForm();
    if (::taihe::has_error()) { return ani_object{}; }
    ani_object ani_result = ohos_data_unifiedDataChannel_SystemDefinedFormInner_intoANI(env, cpp_result);
    return ani_result;
}
static ani_object ohos_data_unifiedDataChannel_CreateSystemDefinedAppItem_ANIFunc([[maybe_unused]] ani_env *env) {
    ::ohos::data::unifiedDataChannel::SystemDefinedAppItemInner cpp_result = ::ohos::data::unifiedDataChannel::CreateSystemDefinedAppItem();
    if (::taihe::has_error()) { return ani_object{}; }
    ani_object ani_result = ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_intoANI(env, cpp_result);
    return ani_result;
}
static ani_object ohos_data_unifiedDataChannel_CreateSystemDefinedPixelMap_ANIFunc([[maybe_unused]] ani_env *env) {
    ::ohos::data::unifiedDataChannel::SystemDefinedPixelMapInner cpp_result = ::ohos::data::unifiedDataChannel::CreateSystemDefinedPixelMap();
    if (::taihe::has_error()) { return ani_object{}; }
    ani_object ani_result = ohos_data_unifiedDataChannel_SystemDefinedPixelMapInner_intoANI(env, cpp_result);
    return ani_result;
}
static ani_string ohos_data_unifiedDataChannel_InsertDataSync_ANIFunc([[maybe_unused]] ani_env *env, ani_object ani_arg_options, ani_object ani_arg_data) {
    ::ohos::data::unifiedDataChannel::Options cpp_arg_options = ohos_data_unifiedDataChannel_Options_fromANI(env, ani_arg_options);
    ::ohos::data::unifiedDataChannel::UnifiedDataInner cpp_arg_data = ohos_data_unifiedDataChannel_UnifiedDataInner_fromANI(env, ani_arg_data);
    ::taihe::string cpp_result = ::ohos::data::unifiedDataChannel::InsertDataSync(cpp_arg_options, cpp_arg_data);
    if (::taihe::has_error()) { return ani_string{}; }
    ani_string ani_result;
    env->String_NewUTF8(cpp_result.c_str(), cpp_result.size(), &ani_result);
    return ani_result;
}
static ani_array_ref ohos_data_unifiedDataChannel_QueryDataSync_ANIFunc([[maybe_unused]] ani_env *env, ani_object ani_arg_options) {
    ::ohos::data::unifiedDataChannel::Options cpp_arg_options = ohos_data_unifiedDataChannel_Options_fromANI(env, ani_arg_options);
    ::taihe::array<::ohos::data::unifiedDataChannel::UnifiedDataInner> cpp_result = ::ohos::data::unifiedDataChannel::QueryDataSync(cpp_arg_options);
    if (::taihe::has_error()) { return ani_array_ref{}; }
    size_t ani_result_size = cpp_result.size();
    ani_array_ref ani_result;
    ani_class ani_result_cls;
    env->FindClass("L@ohos/data/unifiedDataChannel/unifiedDataChannel/UnifiedDataInner;", &ani_result_cls);
    ani_ref ani_result_undef;
    env->GetUndefined(&ani_result_undef);
    env->Array_New_Ref(ani_result_cls, ani_result_size, ani_result_undef, &ani_result);
    for (size_t ani_result_i = 0; ani_result_i < ani_result_size; ani_result_i++) {
        ani_object ani_result_item = ohos_data_unifiedDataChannel_UnifiedDataInner_intoANI(env, cpp_result.data()[ani_result_i]);
        env->Array_Set_Ref(ani_result, ani_result_i, ani_result_item);
    }
    return ani_result;
}
static void ohos_data_unifiedDataChannel_UnifiedDataInner_AddRecord_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object, ani_ref ani_arg_unifiedRecord) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/UnifiedDataInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/UnifiedDataInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_UnifiedDataInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_UnifiedDataInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::UnifiedDataInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::UnifiedDataInner({cpp_vtbl_ptr, cpp_data_ptr});
    ::ohos::data::unifiedDataChannel::AllRecords cpp_arg_unifiedRecord = ohos_data_unifiedDataChannel_AllRecords_fromANI(env, ani_arg_unifiedRecord);
    ::ohos::data::unifiedDataChannel::weak::UnifiedDataInner(cpp_iface)->AddRecord(cpp_arg_unifiedRecord);
}
static ani_array_ref ohos_data_unifiedDataChannel_UnifiedDataInner_GetRecords_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/UnifiedDataInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/UnifiedDataInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_UnifiedDataInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_UnifiedDataInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::UnifiedDataInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::UnifiedDataInner({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::array<::ohos::data::unifiedDataChannel::AllRecords> cpp_result = ::ohos::data::unifiedDataChannel::weak::UnifiedDataInner(cpp_iface)->GetRecords();
    if (::taihe::has_error()) { return ani_array_ref{}; }
    size_t ani_result_size = cpp_result.size();
    ani_array_ref ani_result;
    ani_class ani_result_cls;
    env->FindClass("Lstd/core/Object;", &ani_result_cls);
    ani_ref ani_result_undef;
    env->GetUndefined(&ani_result_undef);
    env->Array_New_Ref(ani_result_cls, ani_result_size, ani_result_undef, &ani_result);
    for (size_t ani_result_i = 0; ani_result_i < ani_result_size; ani_result_i++) {
        ani_ref ani_result_item = ohos_data_unifiedDataChannel_AllRecords_intoANI(env, cpp_result.data()[ani_result_i]);
        env->Array_Set_Ref(ani_result, ani_result_i, ani_result_item);
    }
    return ani_result;
}
static ani_long ohos_data_unifiedDataChannel_UnifiedDataInner_GetInner_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/UnifiedDataInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/UnifiedDataInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_UnifiedDataInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_UnifiedDataInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::UnifiedDataInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::UnifiedDataInner({cpp_vtbl_ptr, cpp_data_ptr});
    int64_t cpp_result = ::ohos::data::unifiedDataChannel::weak::UnifiedDataInner(cpp_iface)->GetInner();
    if (::taihe::has_error()) { return ani_long{}; }
    ani_long ani_result = (int64_t)cpp_result;
    return ani_result;
}
static void ohos_data_unifiedDataChannel_UnifiedDataInner_static_finalize_ANIFunc4([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_class clazz, ani_long data_ptr) {
    ::taihe::data_holder(reinterpret_cast<DataBlockHead*>(data_ptr));
}
static ani_string ohos_data_unifiedDataChannel_UnifiedRecordInner_GetType_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/UnifiedRecordInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/UnifiedRecordInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_UnifiedRecordInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_UnifiedRecordInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::UnifiedRecordInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::UnifiedRecordInner({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::string cpp_result = ::ohos::data::unifiedDataChannel::weak::UnifiedRecordInner(cpp_iface)->GetType();
    if (::taihe::has_error()) { return ani_string{}; }
    ani_string ani_result;
    env->String_NewUTF8(cpp_result.c_str(), cpp_result.size(), &ani_result);
    return ani_result;
}
static ani_ref ohos_data_unifiedDataChannel_UnifiedRecordInner_GetValue_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/UnifiedRecordInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/UnifiedRecordInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_UnifiedRecordInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_UnifiedRecordInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::UnifiedRecordInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::UnifiedRecordInner({cpp_vtbl_ptr, cpp_data_ptr});
    ::ohos::data::unifiedDataChannel::ValueType cpp_result = ::ohos::data::unifiedDataChannel::weak::UnifiedRecordInner(cpp_iface)->GetValue();
    if (::taihe::has_error()) { return ani_ref{}; }
    ani_ref ani_result = ohos_data_unifiedDataChannel_ValueType_intoANI(env, cpp_result);
    return ani_result;
}
static ani_long ohos_data_unifiedDataChannel_UnifiedRecordInner_GetInner_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/UnifiedRecordInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/UnifiedRecordInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_UnifiedRecordInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_UnifiedRecordInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::UnifiedRecordInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::UnifiedRecordInner({cpp_vtbl_ptr, cpp_data_ptr});
    int64_t cpp_result = ::ohos::data::unifiedDataChannel::weak::UnifiedRecordInner(cpp_iface)->GetInner();
    if (::taihe::has_error()) { return ani_long{}; }
    ani_long ani_result = (int64_t)cpp_result;
    return ani_result;
}
static void ohos_data_unifiedDataChannel_UnifiedRecordInner_static_finalize_ANIFunc4([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_class clazz, ani_long data_ptr) {
    ::taihe::data_holder(reinterpret_cast<DataBlockHead*>(data_ptr));
}
static ani_string ohos_data_unifiedDataChannel_FileInner_GetType_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/FileInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/FileInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_FileInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_FileInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::FileInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::FileInner({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::string cpp_result = ::ohos::data::unifiedDataChannel::weak::FileInner(cpp_iface)->GetType();
    if (::taihe::has_error()) { return ani_string{}; }
    ani_string ani_result;
    env->String_NewUTF8(cpp_result.c_str(), cpp_result.size(), &ani_result);
    return ani_result;
}
static ani_ref ohos_data_unifiedDataChannel_FileInner_GetValue_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/FileInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/FileInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_FileInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_FileInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::FileInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::FileInner({cpp_vtbl_ptr, cpp_data_ptr});
    ::ohos::data::unifiedDataChannel::ValueType cpp_result = ::ohos::data::unifiedDataChannel::weak::FileInner(cpp_iface)->GetValue();
    if (::taihe::has_error()) { return ani_ref{}; }
    ani_ref ani_result = ohos_data_unifiedDataChannel_ValueType_intoANI(env, cpp_result);
    return ani_result;
}
static ani_string ohos_data_unifiedDataChannel_FileInner_GetUri_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/FileInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/FileInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_FileInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_FileInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::FileInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::FileInner({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::string cpp_result = ::ohos::data::unifiedDataChannel::weak::FileInner(cpp_iface)->GetUri();
    if (::taihe::has_error()) { return ani_string{}; }
    ani_string ani_result;
    env->String_NewUTF8(cpp_result.c_str(), cpp_result.size(), &ani_result);
    return ani_result;
}
static void ohos_data_unifiedDataChannel_FileInner_SetUri_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object, ani_string ani_arg_uri) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/FileInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/FileInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_FileInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_FileInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::FileInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::FileInner({cpp_vtbl_ptr, cpp_data_ptr});
    ani_size cpp_arg_uri_len;
    env->String_GetUTF8Size(ani_arg_uri, &cpp_arg_uri_len);
    TString cpp_arg_uri_tstr;
    char* cpp_arg_uri_buf = tstr_initialize(&cpp_arg_uri_tstr, cpp_arg_uri_len + 1);
    env->String_GetUTF8(ani_arg_uri, cpp_arg_uri_buf, cpp_arg_uri_len + 1, &cpp_arg_uri_len);
    cpp_arg_uri_buf[cpp_arg_uri_len] = '\0';
    cpp_arg_uri_tstr.length = cpp_arg_uri_len;
    ::taihe::string cpp_arg_uri = ::taihe::string(cpp_arg_uri_tstr);
    ::ohos::data::unifiedDataChannel::weak::FileInner(cpp_iface)->SetUri(cpp_arg_uri);
}
static ani_ref ohos_data_unifiedDataChannel_FileInner_GetDetails_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/FileInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/FileInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_FileInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_FileInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::FileInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::FileInner({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::optional<::taihe::map<::taihe::string, ::taihe::string>> cpp_result = ::ohos::data::unifiedDataChannel::weak::FileInner(cpp_iface)->GetDetails();
    if (::taihe::has_error()) { return ani_ref{}; }
    ani_ref ani_result;
    if (!cpp_result) {
        env->GetUndefined(&ani_result);
    }
    else {
        ani_object ani_result_spec;
        env->Object_New(TH_ANI_FIND_CLASS(env, "Lescompat/Record;"), TH_ANI_FIND_CLASS_METHOD(env, "Lescompat/Record;", "<ctor>", nullptr), &ani_result_spec);
        for (const auto& [ani_result_spec_cpp_key, ani_result_spec_cpp_val] : (*cpp_result)) {
            ani_string ani_result_spec_ani_key;
            env->String_NewUTF8(ani_result_spec_cpp_key.c_str(), ani_result_spec_cpp_key.size(), &ani_result_spec_ani_key);
            ani_string ani_result_spec_ani_val;
            env->String_NewUTF8(ani_result_spec_cpp_val.c_str(), ani_result_spec_cpp_val.size(), &ani_result_spec_ani_val);
            env->Object_CallMethod_Void(ani_result_spec, TH_ANI_FIND_CLASS_METHOD(env, "Lescompat/Record;", "$_set", nullptr), ani_result_spec_ani_key, ani_result_spec_ani_val);
        }
        ani_result = ani_result_spec;
    }
    return ani_result;
}
static void ohos_data_unifiedDataChannel_FileInner_SetDetails_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object, ani_object ani_arg_details) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/FileInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/FileInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_FileInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_FileInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::FileInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::FileInner({cpp_vtbl_ptr, cpp_data_ptr});
    ani_ref cpp_arg_details_iter;
    env->Object_CallMethod_Ref(ani_arg_details, TH_ANI_FIND_CLASS_METHOD(env, "Lescompat/Record;", "$_iterator", nullptr), &cpp_arg_details_iter);
    ::taihe::map<::taihe::string, ::taihe::string> cpp_arg_details;
    while (true) {
        ani_ref cpp_arg_details_next;
        ani_boolean cpp_arg_details_done;
        env->Object_CallMethod_Ref(static_cast<ani_object>(cpp_arg_details_iter), TH_ANI_FIND_CLASS_METHOD(env, "Lescompat/MapIterator;", "next", nullptr), &cpp_arg_details_next);
        env->Object_GetField_Boolean(static_cast<ani_object>(cpp_arg_details_next), TH_ANI_FIND_CLASS_FIELD(env, "Lescompat/IteratorResult;", "done"), &cpp_arg_details_done);
        if (cpp_arg_details_done) {;
            break;
        };
        ani_ref cpp_arg_details_item;
        env->Object_GetField_Ref(static_cast<ani_object>(cpp_arg_details_next),  TH_ANI_FIND_CLASS_FIELD(env, "Lescompat/IteratorResult;", "value"), &cpp_arg_details_item);
        ani_ref cpp_arg_details_ani_key;
        env->TupleValue_GetItem_Ref(static_cast<ani_tuple_value>(cpp_arg_details_item), 0, &cpp_arg_details_ani_key);
        ani_ref cpp_arg_details_ani_val;
        env->TupleValue_GetItem_Ref(static_cast<ani_tuple_value>(cpp_arg_details_item), 1, &cpp_arg_details_ani_val);
        ani_size cpp_arg_details_cpp_key_len;
        env->String_GetUTF8Size(static_cast<ani_string>(cpp_arg_details_ani_key), &cpp_arg_details_cpp_key_len);
        TString cpp_arg_details_cpp_key_tstr;
        char* cpp_arg_details_cpp_key_buf = tstr_initialize(&cpp_arg_details_cpp_key_tstr, cpp_arg_details_cpp_key_len + 1);
        env->String_GetUTF8(static_cast<ani_string>(cpp_arg_details_ani_key), cpp_arg_details_cpp_key_buf, cpp_arg_details_cpp_key_len + 1, &cpp_arg_details_cpp_key_len);
        cpp_arg_details_cpp_key_buf[cpp_arg_details_cpp_key_len] = '\0';
        cpp_arg_details_cpp_key_tstr.length = cpp_arg_details_cpp_key_len;
        ::taihe::string cpp_arg_details_cpp_key = ::taihe::string(cpp_arg_details_cpp_key_tstr);
        ani_size cpp_arg_details_cpp_val_len;
        env->String_GetUTF8Size(static_cast<ani_string>(cpp_arg_details_ani_val), &cpp_arg_details_cpp_val_len);
        TString cpp_arg_details_cpp_val_tstr;
        char* cpp_arg_details_cpp_val_buf = tstr_initialize(&cpp_arg_details_cpp_val_tstr, cpp_arg_details_cpp_val_len + 1);
        env->String_GetUTF8(static_cast<ani_string>(cpp_arg_details_ani_val), cpp_arg_details_cpp_val_buf, cpp_arg_details_cpp_val_len + 1, &cpp_arg_details_cpp_val_len);
        cpp_arg_details_cpp_val_buf[cpp_arg_details_cpp_val_len] = '\0';
        cpp_arg_details_cpp_val_tstr.length = cpp_arg_details_cpp_val_len;
        ::taihe::string cpp_arg_details_cpp_val = ::taihe::string(cpp_arg_details_cpp_val_tstr);
        cpp_arg_details.emplace(cpp_arg_details_cpp_key, cpp_arg_details_cpp_val);
    }
    ::ohos::data::unifiedDataChannel::weak::FileInner(cpp_iface)->SetDetails(cpp_arg_details);
}
static ani_long ohos_data_unifiedDataChannel_FileInner_GetInner_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/FileInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/FileInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_FileInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_FileInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::FileInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::FileInner({cpp_vtbl_ptr, cpp_data_ptr});
    int64_t cpp_result = ::ohos::data::unifiedDataChannel::weak::FileInner(cpp_iface)->GetInner();
    if (::taihe::has_error()) { return ani_long{}; }
    ani_long ani_result = (int64_t)cpp_result;
    return ani_result;
}
static void ohos_data_unifiedDataChannel_FileInner_static_finalize_ANIFunc4([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_class clazz, ani_long data_ptr) {
    ::taihe::data_holder(reinterpret_cast<DataBlockHead*>(data_ptr));
}
static ani_string ohos_data_unifiedDataChannel_FolderInner_GetType_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/FolderInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/FolderInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_FolderInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_FolderInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::FolderInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::FolderInner({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::string cpp_result = ::ohos::data::unifiedDataChannel::weak::FolderInner(cpp_iface)->GetType();
    if (::taihe::has_error()) { return ani_string{}; }
    ani_string ani_result;
    env->String_NewUTF8(cpp_result.c_str(), cpp_result.size(), &ani_result);
    return ani_result;
}
static ani_ref ohos_data_unifiedDataChannel_FolderInner_GetValue_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/FolderInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/FolderInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_FolderInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_FolderInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::FolderInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::FolderInner({cpp_vtbl_ptr, cpp_data_ptr});
    ::ohos::data::unifiedDataChannel::ValueType cpp_result = ::ohos::data::unifiedDataChannel::weak::FolderInner(cpp_iface)->GetValue();
    if (::taihe::has_error()) { return ani_ref{}; }
    ani_ref ani_result = ohos_data_unifiedDataChannel_ValueType_intoANI(env, cpp_result);
    return ani_result;
}
static ani_string ohos_data_unifiedDataChannel_FolderInner_GetUri_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/FolderInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/FolderInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_FolderInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_FolderInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::FolderInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::FolderInner({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::string cpp_result = ::ohos::data::unifiedDataChannel::weak::FolderInner(cpp_iface)->GetUri();
    if (::taihe::has_error()) { return ani_string{}; }
    ani_string ani_result;
    env->String_NewUTF8(cpp_result.c_str(), cpp_result.size(), &ani_result);
    return ani_result;
}
static void ohos_data_unifiedDataChannel_FolderInner_SetUri_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object, ani_string ani_arg_uri) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/FolderInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/FolderInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_FolderInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_FolderInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::FolderInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::FolderInner({cpp_vtbl_ptr, cpp_data_ptr});
    ani_size cpp_arg_uri_len;
    env->String_GetUTF8Size(ani_arg_uri, &cpp_arg_uri_len);
    TString cpp_arg_uri_tstr;
    char* cpp_arg_uri_buf = tstr_initialize(&cpp_arg_uri_tstr, cpp_arg_uri_len + 1);
    env->String_GetUTF8(ani_arg_uri, cpp_arg_uri_buf, cpp_arg_uri_len + 1, &cpp_arg_uri_len);
    cpp_arg_uri_buf[cpp_arg_uri_len] = '\0';
    cpp_arg_uri_tstr.length = cpp_arg_uri_len;
    ::taihe::string cpp_arg_uri = ::taihe::string(cpp_arg_uri_tstr);
    ::ohos::data::unifiedDataChannel::weak::FolderInner(cpp_iface)->SetUri(cpp_arg_uri);
}
static ani_ref ohos_data_unifiedDataChannel_FolderInner_GetDetails_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/FolderInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/FolderInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_FolderInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_FolderInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::FolderInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::FolderInner({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::optional<::taihe::map<::taihe::string, ::taihe::string>> cpp_result = ::ohos::data::unifiedDataChannel::weak::FolderInner(cpp_iface)->GetDetails();
    if (::taihe::has_error()) { return ani_ref{}; }
    ani_ref ani_result;
    if (!cpp_result) {
        env->GetUndefined(&ani_result);
    }
    else {
        ani_object ani_result_spec;
        env->Object_New(TH_ANI_FIND_CLASS(env, "Lescompat/Record;"), TH_ANI_FIND_CLASS_METHOD(env, "Lescompat/Record;", "<ctor>", nullptr), &ani_result_spec);
        for (const auto& [ani_result_spec_cpp_key, ani_result_spec_cpp_val] : (*cpp_result)) {
            ani_string ani_result_spec_ani_key;
            env->String_NewUTF8(ani_result_spec_cpp_key.c_str(), ani_result_spec_cpp_key.size(), &ani_result_spec_ani_key);
            ani_string ani_result_spec_ani_val;
            env->String_NewUTF8(ani_result_spec_cpp_val.c_str(), ani_result_spec_cpp_val.size(), &ani_result_spec_ani_val);
            env->Object_CallMethod_Void(ani_result_spec, TH_ANI_FIND_CLASS_METHOD(env, "Lescompat/Record;", "$_set", nullptr), ani_result_spec_ani_key, ani_result_spec_ani_val);
        }
        ani_result = ani_result_spec;
    }
    return ani_result;
}
static void ohos_data_unifiedDataChannel_FolderInner_SetDetails_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object, ani_object ani_arg_details) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/FolderInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/FolderInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_FolderInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_FolderInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::FolderInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::FolderInner({cpp_vtbl_ptr, cpp_data_ptr});
    ani_ref cpp_arg_details_iter;
    env->Object_CallMethod_Ref(ani_arg_details, TH_ANI_FIND_CLASS_METHOD(env, "Lescompat/Record;", "$_iterator", nullptr), &cpp_arg_details_iter);
    ::taihe::map<::taihe::string, ::taihe::string> cpp_arg_details;
    while (true) {
        ani_ref cpp_arg_details_next;
        ani_boolean cpp_arg_details_done;
        env->Object_CallMethod_Ref(static_cast<ani_object>(cpp_arg_details_iter), TH_ANI_FIND_CLASS_METHOD(env, "Lescompat/MapIterator;", "next", nullptr), &cpp_arg_details_next);
        env->Object_GetField_Boolean(static_cast<ani_object>(cpp_arg_details_next), TH_ANI_FIND_CLASS_FIELD(env, "Lescompat/IteratorResult;", "done"), &cpp_arg_details_done);
        if (cpp_arg_details_done) {;
            break;
        };
        ani_ref cpp_arg_details_item;
        env->Object_GetField_Ref(static_cast<ani_object>(cpp_arg_details_next),  TH_ANI_FIND_CLASS_FIELD(env, "Lescompat/IteratorResult;", "value"), &cpp_arg_details_item);
        ani_ref cpp_arg_details_ani_key;
        env->TupleValue_GetItem_Ref(static_cast<ani_tuple_value>(cpp_arg_details_item), 0, &cpp_arg_details_ani_key);
        ani_ref cpp_arg_details_ani_val;
        env->TupleValue_GetItem_Ref(static_cast<ani_tuple_value>(cpp_arg_details_item), 1, &cpp_arg_details_ani_val);
        ani_size cpp_arg_details_cpp_key_len;
        env->String_GetUTF8Size(static_cast<ani_string>(cpp_arg_details_ani_key), &cpp_arg_details_cpp_key_len);
        TString cpp_arg_details_cpp_key_tstr;
        char* cpp_arg_details_cpp_key_buf = tstr_initialize(&cpp_arg_details_cpp_key_tstr, cpp_arg_details_cpp_key_len + 1);
        env->String_GetUTF8(static_cast<ani_string>(cpp_arg_details_ani_key), cpp_arg_details_cpp_key_buf, cpp_arg_details_cpp_key_len + 1, &cpp_arg_details_cpp_key_len);
        cpp_arg_details_cpp_key_buf[cpp_arg_details_cpp_key_len] = '\0';
        cpp_arg_details_cpp_key_tstr.length = cpp_arg_details_cpp_key_len;
        ::taihe::string cpp_arg_details_cpp_key = ::taihe::string(cpp_arg_details_cpp_key_tstr);
        ani_size cpp_arg_details_cpp_val_len;
        env->String_GetUTF8Size(static_cast<ani_string>(cpp_arg_details_ani_val), &cpp_arg_details_cpp_val_len);
        TString cpp_arg_details_cpp_val_tstr;
        char* cpp_arg_details_cpp_val_buf = tstr_initialize(&cpp_arg_details_cpp_val_tstr, cpp_arg_details_cpp_val_len + 1);
        env->String_GetUTF8(static_cast<ani_string>(cpp_arg_details_ani_val), cpp_arg_details_cpp_val_buf, cpp_arg_details_cpp_val_len + 1, &cpp_arg_details_cpp_val_len);
        cpp_arg_details_cpp_val_buf[cpp_arg_details_cpp_val_len] = '\0';
        cpp_arg_details_cpp_val_tstr.length = cpp_arg_details_cpp_val_len;
        ::taihe::string cpp_arg_details_cpp_val = ::taihe::string(cpp_arg_details_cpp_val_tstr);
        cpp_arg_details.emplace(cpp_arg_details_cpp_key, cpp_arg_details_cpp_val);
    }
    ::ohos::data::unifiedDataChannel::weak::FolderInner(cpp_iface)->SetDetails(cpp_arg_details);
}
static ani_string ohos_data_unifiedDataChannel_FolderInner_GetFolderUri_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/FolderInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/FolderInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_FolderInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_FolderInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::FolderInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::FolderInner({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::string cpp_result = ::ohos::data::unifiedDataChannel::weak::FolderInner(cpp_iface)->GetFolderUri();
    if (::taihe::has_error()) { return ani_string{}; }
    ani_string ani_result;
    env->String_NewUTF8(cpp_result.c_str(), cpp_result.size(), &ani_result);
    return ani_result;
}
static void ohos_data_unifiedDataChannel_FolderInner_SetFolderUri_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object, ani_string ani_arg_folderUri) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/FolderInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/FolderInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_FolderInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_FolderInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::FolderInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::FolderInner({cpp_vtbl_ptr, cpp_data_ptr});
    ani_size cpp_arg_folderUri_len;
    env->String_GetUTF8Size(ani_arg_folderUri, &cpp_arg_folderUri_len);
    TString cpp_arg_folderUri_tstr;
    char* cpp_arg_folderUri_buf = tstr_initialize(&cpp_arg_folderUri_tstr, cpp_arg_folderUri_len + 1);
    env->String_GetUTF8(ani_arg_folderUri, cpp_arg_folderUri_buf, cpp_arg_folderUri_len + 1, &cpp_arg_folderUri_len);
    cpp_arg_folderUri_buf[cpp_arg_folderUri_len] = '\0';
    cpp_arg_folderUri_tstr.length = cpp_arg_folderUri_len;
    ::taihe::string cpp_arg_folderUri = ::taihe::string(cpp_arg_folderUri_tstr);
    ::ohos::data::unifiedDataChannel::weak::FolderInner(cpp_iface)->SetFolderUri(cpp_arg_folderUri);
}
static ani_long ohos_data_unifiedDataChannel_FolderInner_GetInner_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/FolderInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/FolderInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_FolderInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_FolderInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::FolderInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::FolderInner({cpp_vtbl_ptr, cpp_data_ptr});
    int64_t cpp_result = ::ohos::data::unifiedDataChannel::weak::FolderInner(cpp_iface)->GetInner();
    if (::taihe::has_error()) { return ani_long{}; }
    ani_long ani_result = (int64_t)cpp_result;
    return ani_result;
}
static void ohos_data_unifiedDataChannel_FolderInner_static_finalize_ANIFunc4([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_class clazz, ani_long data_ptr) {
    ::taihe::data_holder(reinterpret_cast<DataBlockHead*>(data_ptr));
}
static ani_string ohos_data_unifiedDataChannel_AudioInner_GetType_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/AudioInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/AudioInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_AudioInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_AudioInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::AudioInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::AudioInner({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::string cpp_result = ::ohos::data::unifiedDataChannel::weak::AudioInner(cpp_iface)->GetType();
    if (::taihe::has_error()) { return ani_string{}; }
    ani_string ani_result;
    env->String_NewUTF8(cpp_result.c_str(), cpp_result.size(), &ani_result);
    return ani_result;
}
static ani_ref ohos_data_unifiedDataChannel_AudioInner_GetValue_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/AudioInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/AudioInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_AudioInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_AudioInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::AudioInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::AudioInner({cpp_vtbl_ptr, cpp_data_ptr});
    ::ohos::data::unifiedDataChannel::ValueType cpp_result = ::ohos::data::unifiedDataChannel::weak::AudioInner(cpp_iface)->GetValue();
    if (::taihe::has_error()) { return ani_ref{}; }
    ani_ref ani_result = ohos_data_unifiedDataChannel_ValueType_intoANI(env, cpp_result);
    return ani_result;
}
static ani_string ohos_data_unifiedDataChannel_AudioInner_GetUri_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/AudioInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/AudioInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_AudioInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_AudioInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::AudioInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::AudioInner({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::string cpp_result = ::ohos::data::unifiedDataChannel::weak::AudioInner(cpp_iface)->GetUri();
    if (::taihe::has_error()) { return ani_string{}; }
    ani_string ani_result;
    env->String_NewUTF8(cpp_result.c_str(), cpp_result.size(), &ani_result);
    return ani_result;
}
static void ohos_data_unifiedDataChannel_AudioInner_SetUri_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object, ani_string ani_arg_uri) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/AudioInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/AudioInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_AudioInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_AudioInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::AudioInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::AudioInner({cpp_vtbl_ptr, cpp_data_ptr});
    ani_size cpp_arg_uri_len;
    env->String_GetUTF8Size(ani_arg_uri, &cpp_arg_uri_len);
    TString cpp_arg_uri_tstr;
    char* cpp_arg_uri_buf = tstr_initialize(&cpp_arg_uri_tstr, cpp_arg_uri_len + 1);
    env->String_GetUTF8(ani_arg_uri, cpp_arg_uri_buf, cpp_arg_uri_len + 1, &cpp_arg_uri_len);
    cpp_arg_uri_buf[cpp_arg_uri_len] = '\0';
    cpp_arg_uri_tstr.length = cpp_arg_uri_len;
    ::taihe::string cpp_arg_uri = ::taihe::string(cpp_arg_uri_tstr);
    ::ohos::data::unifiedDataChannel::weak::AudioInner(cpp_iface)->SetUri(cpp_arg_uri);
}
static ani_ref ohos_data_unifiedDataChannel_AudioInner_GetDetails_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/AudioInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/AudioInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_AudioInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_AudioInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::AudioInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::AudioInner({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::optional<::taihe::map<::taihe::string, ::taihe::string>> cpp_result = ::ohos::data::unifiedDataChannel::weak::AudioInner(cpp_iface)->GetDetails();
    if (::taihe::has_error()) { return ani_ref{}; }
    ani_ref ani_result;
    if (!cpp_result) {
        env->GetUndefined(&ani_result);
    }
    else {
        ani_object ani_result_spec;
        env->Object_New(TH_ANI_FIND_CLASS(env, "Lescompat/Record;"), TH_ANI_FIND_CLASS_METHOD(env, "Lescompat/Record;", "<ctor>", nullptr), &ani_result_spec);
        for (const auto& [ani_result_spec_cpp_key, ani_result_spec_cpp_val] : (*cpp_result)) {
            ani_string ani_result_spec_ani_key;
            env->String_NewUTF8(ani_result_spec_cpp_key.c_str(), ani_result_spec_cpp_key.size(), &ani_result_spec_ani_key);
            ani_string ani_result_spec_ani_val;
            env->String_NewUTF8(ani_result_spec_cpp_val.c_str(), ani_result_spec_cpp_val.size(), &ani_result_spec_ani_val);
            env->Object_CallMethod_Void(ani_result_spec, TH_ANI_FIND_CLASS_METHOD(env, "Lescompat/Record;", "$_set", nullptr), ani_result_spec_ani_key, ani_result_spec_ani_val);
        }
        ani_result = ani_result_spec;
    }
    return ani_result;
}
static void ohos_data_unifiedDataChannel_AudioInner_SetDetails_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object, ani_object ani_arg_details) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/AudioInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/AudioInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_AudioInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_AudioInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::AudioInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::AudioInner({cpp_vtbl_ptr, cpp_data_ptr});
    ani_ref cpp_arg_details_iter;
    env->Object_CallMethod_Ref(ani_arg_details, TH_ANI_FIND_CLASS_METHOD(env, "Lescompat/Record;", "$_iterator", nullptr), &cpp_arg_details_iter);
    ::taihe::map<::taihe::string, ::taihe::string> cpp_arg_details;
    while (true) {
        ani_ref cpp_arg_details_next;
        ani_boolean cpp_arg_details_done;
        env->Object_CallMethod_Ref(static_cast<ani_object>(cpp_arg_details_iter), TH_ANI_FIND_CLASS_METHOD(env, "Lescompat/MapIterator;", "next", nullptr), &cpp_arg_details_next);
        env->Object_GetField_Boolean(static_cast<ani_object>(cpp_arg_details_next), TH_ANI_FIND_CLASS_FIELD(env, "Lescompat/IteratorResult;", "done"), &cpp_arg_details_done);
        if (cpp_arg_details_done) {;
            break;
        };
        ani_ref cpp_arg_details_item;
        env->Object_GetField_Ref(static_cast<ani_object>(cpp_arg_details_next),  TH_ANI_FIND_CLASS_FIELD(env, "Lescompat/IteratorResult;", "value"), &cpp_arg_details_item);
        ani_ref cpp_arg_details_ani_key;
        env->TupleValue_GetItem_Ref(static_cast<ani_tuple_value>(cpp_arg_details_item), 0, &cpp_arg_details_ani_key);
        ani_ref cpp_arg_details_ani_val;
        env->TupleValue_GetItem_Ref(static_cast<ani_tuple_value>(cpp_arg_details_item), 1, &cpp_arg_details_ani_val);
        ani_size cpp_arg_details_cpp_key_len;
        env->String_GetUTF8Size(static_cast<ani_string>(cpp_arg_details_ani_key), &cpp_arg_details_cpp_key_len);
        TString cpp_arg_details_cpp_key_tstr;
        char* cpp_arg_details_cpp_key_buf = tstr_initialize(&cpp_arg_details_cpp_key_tstr, cpp_arg_details_cpp_key_len + 1);
        env->String_GetUTF8(static_cast<ani_string>(cpp_arg_details_ani_key), cpp_arg_details_cpp_key_buf, cpp_arg_details_cpp_key_len + 1, &cpp_arg_details_cpp_key_len);
        cpp_arg_details_cpp_key_buf[cpp_arg_details_cpp_key_len] = '\0';
        cpp_arg_details_cpp_key_tstr.length = cpp_arg_details_cpp_key_len;
        ::taihe::string cpp_arg_details_cpp_key = ::taihe::string(cpp_arg_details_cpp_key_tstr);
        ani_size cpp_arg_details_cpp_val_len;
        env->String_GetUTF8Size(static_cast<ani_string>(cpp_arg_details_ani_val), &cpp_arg_details_cpp_val_len);
        TString cpp_arg_details_cpp_val_tstr;
        char* cpp_arg_details_cpp_val_buf = tstr_initialize(&cpp_arg_details_cpp_val_tstr, cpp_arg_details_cpp_val_len + 1);
        env->String_GetUTF8(static_cast<ani_string>(cpp_arg_details_ani_val), cpp_arg_details_cpp_val_buf, cpp_arg_details_cpp_val_len + 1, &cpp_arg_details_cpp_val_len);
        cpp_arg_details_cpp_val_buf[cpp_arg_details_cpp_val_len] = '\0';
        cpp_arg_details_cpp_val_tstr.length = cpp_arg_details_cpp_val_len;
        ::taihe::string cpp_arg_details_cpp_val = ::taihe::string(cpp_arg_details_cpp_val_tstr);
        cpp_arg_details.emplace(cpp_arg_details_cpp_key, cpp_arg_details_cpp_val);
    }
    ::ohos::data::unifiedDataChannel::weak::AudioInner(cpp_iface)->SetDetails(cpp_arg_details);
}
static ani_string ohos_data_unifiedDataChannel_AudioInner_GetAudioUri_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/AudioInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/AudioInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_AudioInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_AudioInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::AudioInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::AudioInner({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::string cpp_result = ::ohos::data::unifiedDataChannel::weak::AudioInner(cpp_iface)->GetAudioUri();
    if (::taihe::has_error()) { return ani_string{}; }
    ani_string ani_result;
    env->String_NewUTF8(cpp_result.c_str(), cpp_result.size(), &ani_result);
    return ani_result;
}
static void ohos_data_unifiedDataChannel_AudioInner_SetAudioUri_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object, ani_string ani_arg_audioUri) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/AudioInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/AudioInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_AudioInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_AudioInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::AudioInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::AudioInner({cpp_vtbl_ptr, cpp_data_ptr});
    ani_size cpp_arg_audioUri_len;
    env->String_GetUTF8Size(ani_arg_audioUri, &cpp_arg_audioUri_len);
    TString cpp_arg_audioUri_tstr;
    char* cpp_arg_audioUri_buf = tstr_initialize(&cpp_arg_audioUri_tstr, cpp_arg_audioUri_len + 1);
    env->String_GetUTF8(ani_arg_audioUri, cpp_arg_audioUri_buf, cpp_arg_audioUri_len + 1, &cpp_arg_audioUri_len);
    cpp_arg_audioUri_buf[cpp_arg_audioUri_len] = '\0';
    cpp_arg_audioUri_tstr.length = cpp_arg_audioUri_len;
    ::taihe::string cpp_arg_audioUri = ::taihe::string(cpp_arg_audioUri_tstr);
    ::ohos::data::unifiedDataChannel::weak::AudioInner(cpp_iface)->SetAudioUri(cpp_arg_audioUri);
}
static ani_long ohos_data_unifiedDataChannel_AudioInner_GetInner_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/AudioInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/AudioInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_AudioInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_AudioInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::AudioInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::AudioInner({cpp_vtbl_ptr, cpp_data_ptr});
    int64_t cpp_result = ::ohos::data::unifiedDataChannel::weak::AudioInner(cpp_iface)->GetInner();
    if (::taihe::has_error()) { return ani_long{}; }
    ani_long ani_result = (int64_t)cpp_result;
    return ani_result;
}
static void ohos_data_unifiedDataChannel_AudioInner_static_finalize_ANIFunc4([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_class clazz, ani_long data_ptr) {
    ::taihe::data_holder(reinterpret_cast<DataBlockHead*>(data_ptr));
}
static ani_string ohos_data_unifiedDataChannel_VideoInner_GetType_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/VideoInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/VideoInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_VideoInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_VideoInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::VideoInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::VideoInner({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::string cpp_result = ::ohos::data::unifiedDataChannel::weak::VideoInner(cpp_iface)->GetType();
    if (::taihe::has_error()) { return ani_string{}; }
    ani_string ani_result;
    env->String_NewUTF8(cpp_result.c_str(), cpp_result.size(), &ani_result);
    return ani_result;
}
static ani_ref ohos_data_unifiedDataChannel_VideoInner_GetValue_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/VideoInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/VideoInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_VideoInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_VideoInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::VideoInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::VideoInner({cpp_vtbl_ptr, cpp_data_ptr});
    ::ohos::data::unifiedDataChannel::ValueType cpp_result = ::ohos::data::unifiedDataChannel::weak::VideoInner(cpp_iface)->GetValue();
    if (::taihe::has_error()) { return ani_ref{}; }
    ani_ref ani_result = ohos_data_unifiedDataChannel_ValueType_intoANI(env, cpp_result);
    return ani_result;
}
static ani_string ohos_data_unifiedDataChannel_VideoInner_GetUri_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/VideoInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/VideoInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_VideoInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_VideoInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::VideoInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::VideoInner({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::string cpp_result = ::ohos::data::unifiedDataChannel::weak::VideoInner(cpp_iface)->GetUri();
    if (::taihe::has_error()) { return ani_string{}; }
    ani_string ani_result;
    env->String_NewUTF8(cpp_result.c_str(), cpp_result.size(), &ani_result);
    return ani_result;
}
static void ohos_data_unifiedDataChannel_VideoInner_SetUri_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object, ani_string ani_arg_uri) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/VideoInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/VideoInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_VideoInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_VideoInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::VideoInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::VideoInner({cpp_vtbl_ptr, cpp_data_ptr});
    ani_size cpp_arg_uri_len;
    env->String_GetUTF8Size(ani_arg_uri, &cpp_arg_uri_len);
    TString cpp_arg_uri_tstr;
    char* cpp_arg_uri_buf = tstr_initialize(&cpp_arg_uri_tstr, cpp_arg_uri_len + 1);
    env->String_GetUTF8(ani_arg_uri, cpp_arg_uri_buf, cpp_arg_uri_len + 1, &cpp_arg_uri_len);
    cpp_arg_uri_buf[cpp_arg_uri_len] = '\0';
    cpp_arg_uri_tstr.length = cpp_arg_uri_len;
    ::taihe::string cpp_arg_uri = ::taihe::string(cpp_arg_uri_tstr);
    ::ohos::data::unifiedDataChannel::weak::VideoInner(cpp_iface)->SetUri(cpp_arg_uri);
}
static ani_ref ohos_data_unifiedDataChannel_VideoInner_GetDetails_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/VideoInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/VideoInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_VideoInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_VideoInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::VideoInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::VideoInner({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::optional<::taihe::map<::taihe::string, ::taihe::string>> cpp_result = ::ohos::data::unifiedDataChannel::weak::VideoInner(cpp_iface)->GetDetails();
    if (::taihe::has_error()) { return ani_ref{}; }
    ani_ref ani_result;
    if (!cpp_result) {
        env->GetUndefined(&ani_result);
    }
    else {
        ani_object ani_result_spec;
        env->Object_New(TH_ANI_FIND_CLASS(env, "Lescompat/Record;"), TH_ANI_FIND_CLASS_METHOD(env, "Lescompat/Record;", "<ctor>", nullptr), &ani_result_spec);
        for (const auto& [ani_result_spec_cpp_key, ani_result_spec_cpp_val] : (*cpp_result)) {
            ani_string ani_result_spec_ani_key;
            env->String_NewUTF8(ani_result_spec_cpp_key.c_str(), ani_result_spec_cpp_key.size(), &ani_result_spec_ani_key);
            ani_string ani_result_spec_ani_val;
            env->String_NewUTF8(ani_result_spec_cpp_val.c_str(), ani_result_spec_cpp_val.size(), &ani_result_spec_ani_val);
            env->Object_CallMethod_Void(ani_result_spec, TH_ANI_FIND_CLASS_METHOD(env, "Lescompat/Record;", "$_set", nullptr), ani_result_spec_ani_key, ani_result_spec_ani_val);
        }
        ani_result = ani_result_spec;
    }
    return ani_result;
}
static void ohos_data_unifiedDataChannel_VideoInner_SetDetails_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object, ani_object ani_arg_details) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/VideoInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/VideoInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_VideoInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_VideoInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::VideoInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::VideoInner({cpp_vtbl_ptr, cpp_data_ptr});
    ani_ref cpp_arg_details_iter;
    env->Object_CallMethod_Ref(ani_arg_details, TH_ANI_FIND_CLASS_METHOD(env, "Lescompat/Record;", "$_iterator", nullptr), &cpp_arg_details_iter);
    ::taihe::map<::taihe::string, ::taihe::string> cpp_arg_details;
    while (true) {
        ani_ref cpp_arg_details_next;
        ani_boolean cpp_arg_details_done;
        env->Object_CallMethod_Ref(static_cast<ani_object>(cpp_arg_details_iter), TH_ANI_FIND_CLASS_METHOD(env, "Lescompat/MapIterator;", "next", nullptr), &cpp_arg_details_next);
        env->Object_GetField_Boolean(static_cast<ani_object>(cpp_arg_details_next), TH_ANI_FIND_CLASS_FIELD(env, "Lescompat/IteratorResult;", "done"), &cpp_arg_details_done);
        if (cpp_arg_details_done) {;
            break;
        };
        ani_ref cpp_arg_details_item;
        env->Object_GetField_Ref(static_cast<ani_object>(cpp_arg_details_next),  TH_ANI_FIND_CLASS_FIELD(env, "Lescompat/IteratorResult;", "value"), &cpp_arg_details_item);
        ani_ref cpp_arg_details_ani_key;
        env->TupleValue_GetItem_Ref(static_cast<ani_tuple_value>(cpp_arg_details_item), 0, &cpp_arg_details_ani_key);
        ani_ref cpp_arg_details_ani_val;
        env->TupleValue_GetItem_Ref(static_cast<ani_tuple_value>(cpp_arg_details_item), 1, &cpp_arg_details_ani_val);
        ani_size cpp_arg_details_cpp_key_len;
        env->String_GetUTF8Size(static_cast<ani_string>(cpp_arg_details_ani_key), &cpp_arg_details_cpp_key_len);
        TString cpp_arg_details_cpp_key_tstr;
        char* cpp_arg_details_cpp_key_buf = tstr_initialize(&cpp_arg_details_cpp_key_tstr, cpp_arg_details_cpp_key_len + 1);
        env->String_GetUTF8(static_cast<ani_string>(cpp_arg_details_ani_key), cpp_arg_details_cpp_key_buf, cpp_arg_details_cpp_key_len + 1, &cpp_arg_details_cpp_key_len);
        cpp_arg_details_cpp_key_buf[cpp_arg_details_cpp_key_len] = '\0';
        cpp_arg_details_cpp_key_tstr.length = cpp_arg_details_cpp_key_len;
        ::taihe::string cpp_arg_details_cpp_key = ::taihe::string(cpp_arg_details_cpp_key_tstr);
        ani_size cpp_arg_details_cpp_val_len;
        env->String_GetUTF8Size(static_cast<ani_string>(cpp_arg_details_ani_val), &cpp_arg_details_cpp_val_len);
        TString cpp_arg_details_cpp_val_tstr;
        char* cpp_arg_details_cpp_val_buf = tstr_initialize(&cpp_arg_details_cpp_val_tstr, cpp_arg_details_cpp_val_len + 1);
        env->String_GetUTF8(static_cast<ani_string>(cpp_arg_details_ani_val), cpp_arg_details_cpp_val_buf, cpp_arg_details_cpp_val_len + 1, &cpp_arg_details_cpp_val_len);
        cpp_arg_details_cpp_val_buf[cpp_arg_details_cpp_val_len] = '\0';
        cpp_arg_details_cpp_val_tstr.length = cpp_arg_details_cpp_val_len;
        ::taihe::string cpp_arg_details_cpp_val = ::taihe::string(cpp_arg_details_cpp_val_tstr);
        cpp_arg_details.emplace(cpp_arg_details_cpp_key, cpp_arg_details_cpp_val);
    }
    ::ohos::data::unifiedDataChannel::weak::VideoInner(cpp_iface)->SetDetails(cpp_arg_details);
}
static ani_string ohos_data_unifiedDataChannel_VideoInner_GetVideoUri_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/VideoInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/VideoInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_VideoInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_VideoInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::VideoInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::VideoInner({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::string cpp_result = ::ohos::data::unifiedDataChannel::weak::VideoInner(cpp_iface)->GetVideoUri();
    if (::taihe::has_error()) { return ani_string{}; }
    ani_string ani_result;
    env->String_NewUTF8(cpp_result.c_str(), cpp_result.size(), &ani_result);
    return ani_result;
}
static void ohos_data_unifiedDataChannel_VideoInner_SetVideoUri_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object, ani_string ani_arg_videoUri) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/VideoInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/VideoInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_VideoInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_VideoInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::VideoInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::VideoInner({cpp_vtbl_ptr, cpp_data_ptr});
    ani_size cpp_arg_videoUri_len;
    env->String_GetUTF8Size(ani_arg_videoUri, &cpp_arg_videoUri_len);
    TString cpp_arg_videoUri_tstr;
    char* cpp_arg_videoUri_buf = tstr_initialize(&cpp_arg_videoUri_tstr, cpp_arg_videoUri_len + 1);
    env->String_GetUTF8(ani_arg_videoUri, cpp_arg_videoUri_buf, cpp_arg_videoUri_len + 1, &cpp_arg_videoUri_len);
    cpp_arg_videoUri_buf[cpp_arg_videoUri_len] = '\0';
    cpp_arg_videoUri_tstr.length = cpp_arg_videoUri_len;
    ::taihe::string cpp_arg_videoUri = ::taihe::string(cpp_arg_videoUri_tstr);
    ::ohos::data::unifiedDataChannel::weak::VideoInner(cpp_iface)->SetVideoUri(cpp_arg_videoUri);
}
static ani_long ohos_data_unifiedDataChannel_VideoInner_GetInner_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/VideoInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/VideoInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_VideoInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_VideoInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::VideoInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::VideoInner({cpp_vtbl_ptr, cpp_data_ptr});
    int64_t cpp_result = ::ohos::data::unifiedDataChannel::weak::VideoInner(cpp_iface)->GetInner();
    if (::taihe::has_error()) { return ani_long{}; }
    ani_long ani_result = (int64_t)cpp_result;
    return ani_result;
}
static void ohos_data_unifiedDataChannel_VideoInner_static_finalize_ANIFunc4([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_class clazz, ani_long data_ptr) {
    ::taihe::data_holder(reinterpret_cast<DataBlockHead*>(data_ptr));
}
static ani_string ohos_data_unifiedDataChannel_ImageInner_GetType_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/ImageInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/ImageInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_ImageInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_ImageInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::ImageInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::ImageInner({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::string cpp_result = ::ohos::data::unifiedDataChannel::weak::ImageInner(cpp_iface)->GetType();
    if (::taihe::has_error()) { return ani_string{}; }
    ani_string ani_result;
    env->String_NewUTF8(cpp_result.c_str(), cpp_result.size(), &ani_result);
    return ani_result;
}
static ani_ref ohos_data_unifiedDataChannel_ImageInner_GetValue_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/ImageInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/ImageInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_ImageInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_ImageInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::ImageInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::ImageInner({cpp_vtbl_ptr, cpp_data_ptr});
    ::ohos::data::unifiedDataChannel::ValueType cpp_result = ::ohos::data::unifiedDataChannel::weak::ImageInner(cpp_iface)->GetValue();
    if (::taihe::has_error()) { return ani_ref{}; }
    ani_ref ani_result = ohos_data_unifiedDataChannel_ValueType_intoANI(env, cpp_result);
    return ani_result;
}
static ani_string ohos_data_unifiedDataChannel_ImageInner_GetUri_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/ImageInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/ImageInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_ImageInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_ImageInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::ImageInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::ImageInner({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::string cpp_result = ::ohos::data::unifiedDataChannel::weak::ImageInner(cpp_iface)->GetUri();
    if (::taihe::has_error()) { return ani_string{}; }
    ani_string ani_result;
    env->String_NewUTF8(cpp_result.c_str(), cpp_result.size(), &ani_result);
    return ani_result;
}
static void ohos_data_unifiedDataChannel_ImageInner_SetUri_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object, ani_string ani_arg_uri) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/ImageInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/ImageInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_ImageInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_ImageInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::ImageInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::ImageInner({cpp_vtbl_ptr, cpp_data_ptr});
    ani_size cpp_arg_uri_len;
    env->String_GetUTF8Size(ani_arg_uri, &cpp_arg_uri_len);
    TString cpp_arg_uri_tstr;
    char* cpp_arg_uri_buf = tstr_initialize(&cpp_arg_uri_tstr, cpp_arg_uri_len + 1);
    env->String_GetUTF8(ani_arg_uri, cpp_arg_uri_buf, cpp_arg_uri_len + 1, &cpp_arg_uri_len);
    cpp_arg_uri_buf[cpp_arg_uri_len] = '\0';
    cpp_arg_uri_tstr.length = cpp_arg_uri_len;
    ::taihe::string cpp_arg_uri = ::taihe::string(cpp_arg_uri_tstr);
    ::ohos::data::unifiedDataChannel::weak::ImageInner(cpp_iface)->SetUri(cpp_arg_uri);
}
static ani_ref ohos_data_unifiedDataChannel_ImageInner_GetDetails_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/ImageInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/ImageInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_ImageInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_ImageInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::ImageInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::ImageInner({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::optional<::taihe::map<::taihe::string, ::taihe::string>> cpp_result = ::ohos::data::unifiedDataChannel::weak::ImageInner(cpp_iface)->GetDetails();
    if (::taihe::has_error()) { return ani_ref{}; }
    ani_ref ani_result;
    if (!cpp_result) {
        env->GetUndefined(&ani_result);
    }
    else {
        ani_object ani_result_spec;
        env->Object_New(TH_ANI_FIND_CLASS(env, "Lescompat/Record;"), TH_ANI_FIND_CLASS_METHOD(env, "Lescompat/Record;", "<ctor>", nullptr), &ani_result_spec);
        for (const auto& [ani_result_spec_cpp_key, ani_result_spec_cpp_val] : (*cpp_result)) {
            ani_string ani_result_spec_ani_key;
            env->String_NewUTF8(ani_result_spec_cpp_key.c_str(), ani_result_spec_cpp_key.size(), &ani_result_spec_ani_key);
            ani_string ani_result_spec_ani_val;
            env->String_NewUTF8(ani_result_spec_cpp_val.c_str(), ani_result_spec_cpp_val.size(), &ani_result_spec_ani_val);
            env->Object_CallMethod_Void(ani_result_spec, TH_ANI_FIND_CLASS_METHOD(env, "Lescompat/Record;", "$_set", nullptr), ani_result_spec_ani_key, ani_result_spec_ani_val);
        }
        ani_result = ani_result_spec;
    }
    return ani_result;
}
static void ohos_data_unifiedDataChannel_ImageInner_SetDetails_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object, ani_object ani_arg_details) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/ImageInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/ImageInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_ImageInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_ImageInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::ImageInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::ImageInner({cpp_vtbl_ptr, cpp_data_ptr});
    ani_ref cpp_arg_details_iter;
    env->Object_CallMethod_Ref(ani_arg_details, TH_ANI_FIND_CLASS_METHOD(env, "Lescompat/Record;", "$_iterator", nullptr), &cpp_arg_details_iter);
    ::taihe::map<::taihe::string, ::taihe::string> cpp_arg_details;
    while (true) {
        ani_ref cpp_arg_details_next;
        ani_boolean cpp_arg_details_done;
        env->Object_CallMethod_Ref(static_cast<ani_object>(cpp_arg_details_iter), TH_ANI_FIND_CLASS_METHOD(env, "Lescompat/MapIterator;", "next", nullptr), &cpp_arg_details_next);
        env->Object_GetField_Boolean(static_cast<ani_object>(cpp_arg_details_next), TH_ANI_FIND_CLASS_FIELD(env, "Lescompat/IteratorResult;", "done"), &cpp_arg_details_done);
        if (cpp_arg_details_done) {;
            break;
        };
        ani_ref cpp_arg_details_item;
        env->Object_GetField_Ref(static_cast<ani_object>(cpp_arg_details_next),  TH_ANI_FIND_CLASS_FIELD(env, "Lescompat/IteratorResult;", "value"), &cpp_arg_details_item);
        ani_ref cpp_arg_details_ani_key;
        env->TupleValue_GetItem_Ref(static_cast<ani_tuple_value>(cpp_arg_details_item), 0, &cpp_arg_details_ani_key);
        ani_ref cpp_arg_details_ani_val;
        env->TupleValue_GetItem_Ref(static_cast<ani_tuple_value>(cpp_arg_details_item), 1, &cpp_arg_details_ani_val);
        ani_size cpp_arg_details_cpp_key_len;
        env->String_GetUTF8Size(static_cast<ani_string>(cpp_arg_details_ani_key), &cpp_arg_details_cpp_key_len);
        TString cpp_arg_details_cpp_key_tstr;
        char* cpp_arg_details_cpp_key_buf = tstr_initialize(&cpp_arg_details_cpp_key_tstr, cpp_arg_details_cpp_key_len + 1);
        env->String_GetUTF8(static_cast<ani_string>(cpp_arg_details_ani_key), cpp_arg_details_cpp_key_buf, cpp_arg_details_cpp_key_len + 1, &cpp_arg_details_cpp_key_len);
        cpp_arg_details_cpp_key_buf[cpp_arg_details_cpp_key_len] = '\0';
        cpp_arg_details_cpp_key_tstr.length = cpp_arg_details_cpp_key_len;
        ::taihe::string cpp_arg_details_cpp_key = ::taihe::string(cpp_arg_details_cpp_key_tstr);
        ani_size cpp_arg_details_cpp_val_len;
        env->String_GetUTF8Size(static_cast<ani_string>(cpp_arg_details_ani_val), &cpp_arg_details_cpp_val_len);
        TString cpp_arg_details_cpp_val_tstr;
        char* cpp_arg_details_cpp_val_buf = tstr_initialize(&cpp_arg_details_cpp_val_tstr, cpp_arg_details_cpp_val_len + 1);
        env->String_GetUTF8(static_cast<ani_string>(cpp_arg_details_ani_val), cpp_arg_details_cpp_val_buf, cpp_arg_details_cpp_val_len + 1, &cpp_arg_details_cpp_val_len);
        cpp_arg_details_cpp_val_buf[cpp_arg_details_cpp_val_len] = '\0';
        cpp_arg_details_cpp_val_tstr.length = cpp_arg_details_cpp_val_len;
        ::taihe::string cpp_arg_details_cpp_val = ::taihe::string(cpp_arg_details_cpp_val_tstr);
        cpp_arg_details.emplace(cpp_arg_details_cpp_key, cpp_arg_details_cpp_val);
    }
    ::ohos::data::unifiedDataChannel::weak::ImageInner(cpp_iface)->SetDetails(cpp_arg_details);
}
static ani_string ohos_data_unifiedDataChannel_ImageInner_GetImageUri_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/ImageInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/ImageInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_ImageInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_ImageInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::ImageInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::ImageInner({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::string cpp_result = ::ohos::data::unifiedDataChannel::weak::ImageInner(cpp_iface)->GetImageUri();
    if (::taihe::has_error()) { return ani_string{}; }
    ani_string ani_result;
    env->String_NewUTF8(cpp_result.c_str(), cpp_result.size(), &ani_result);
    return ani_result;
}
static void ohos_data_unifiedDataChannel_ImageInner_SetImageUri_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object, ani_string ani_arg_imageUri) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/ImageInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/ImageInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_ImageInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_ImageInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::ImageInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::ImageInner({cpp_vtbl_ptr, cpp_data_ptr});
    ani_size cpp_arg_imageUri_len;
    env->String_GetUTF8Size(ani_arg_imageUri, &cpp_arg_imageUri_len);
    TString cpp_arg_imageUri_tstr;
    char* cpp_arg_imageUri_buf = tstr_initialize(&cpp_arg_imageUri_tstr, cpp_arg_imageUri_len + 1);
    env->String_GetUTF8(ani_arg_imageUri, cpp_arg_imageUri_buf, cpp_arg_imageUri_len + 1, &cpp_arg_imageUri_len);
    cpp_arg_imageUri_buf[cpp_arg_imageUri_len] = '\0';
    cpp_arg_imageUri_tstr.length = cpp_arg_imageUri_len;
    ::taihe::string cpp_arg_imageUri = ::taihe::string(cpp_arg_imageUri_tstr);
    ::ohos::data::unifiedDataChannel::weak::ImageInner(cpp_iface)->SetImageUri(cpp_arg_imageUri);
}
static ani_long ohos_data_unifiedDataChannel_ImageInner_GetInner_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/ImageInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/ImageInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_ImageInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_ImageInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::ImageInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::ImageInner({cpp_vtbl_ptr, cpp_data_ptr});
    int64_t cpp_result = ::ohos::data::unifiedDataChannel::weak::ImageInner(cpp_iface)->GetInner();
    if (::taihe::has_error()) { return ani_long{}; }
    ani_long ani_result = (int64_t)cpp_result;
    return ani_result;
}
static void ohos_data_unifiedDataChannel_ImageInner_static_finalize_ANIFunc4([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_class clazz, ani_long data_ptr) {
    ::taihe::data_holder(reinterpret_cast<DataBlockHead*>(data_ptr));
}
static ani_string ohos_data_unifiedDataChannel_TextInner_GetType_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/TextInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/TextInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_TextInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_TextInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::TextInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::TextInner({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::string cpp_result = ::ohos::data::unifiedDataChannel::weak::TextInner(cpp_iface)->GetType();
    if (::taihe::has_error()) { return ani_string{}; }
    ani_string ani_result;
    env->String_NewUTF8(cpp_result.c_str(), cpp_result.size(), &ani_result);
    return ani_result;
}
static ani_ref ohos_data_unifiedDataChannel_TextInner_GetValue_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/TextInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/TextInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_TextInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_TextInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::TextInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::TextInner({cpp_vtbl_ptr, cpp_data_ptr});
    ::ohos::data::unifiedDataChannel::ValueType cpp_result = ::ohos::data::unifiedDataChannel::weak::TextInner(cpp_iface)->GetValue();
    if (::taihe::has_error()) { return ani_ref{}; }
    ani_ref ani_result = ohos_data_unifiedDataChannel_ValueType_intoANI(env, cpp_result);
    return ani_result;
}
static ani_ref ohos_data_unifiedDataChannel_TextInner_GetDetails_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/TextInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/TextInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_TextInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_TextInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::TextInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::TextInner({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::optional<::taihe::map<::taihe::string, ::taihe::string>> cpp_result = ::ohos::data::unifiedDataChannel::weak::TextInner(cpp_iface)->GetDetails();
    if (::taihe::has_error()) { return ani_ref{}; }
    ani_ref ani_result;
    if (!cpp_result) {
        env->GetUndefined(&ani_result);
    }
    else {
        ani_object ani_result_spec;
        env->Object_New(TH_ANI_FIND_CLASS(env, "Lescompat/Record;"), TH_ANI_FIND_CLASS_METHOD(env, "Lescompat/Record;", "<ctor>", nullptr), &ani_result_spec);
        for (const auto& [ani_result_spec_cpp_key, ani_result_spec_cpp_val] : (*cpp_result)) {
            ani_string ani_result_spec_ani_key;
            env->String_NewUTF8(ani_result_spec_cpp_key.c_str(), ani_result_spec_cpp_key.size(), &ani_result_spec_ani_key);
            ani_string ani_result_spec_ani_val;
            env->String_NewUTF8(ani_result_spec_cpp_val.c_str(), ani_result_spec_cpp_val.size(), &ani_result_spec_ani_val);
            env->Object_CallMethod_Void(ani_result_spec, TH_ANI_FIND_CLASS_METHOD(env, "Lescompat/Record;", "$_set", nullptr), ani_result_spec_ani_key, ani_result_spec_ani_val);
        }
        ani_result = ani_result_spec;
    }
    return ani_result;
}
static void ohos_data_unifiedDataChannel_TextInner_SetDetails_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object, ani_object ani_arg_details) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/TextInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/TextInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_TextInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_TextInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::TextInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::TextInner({cpp_vtbl_ptr, cpp_data_ptr});
    ani_ref cpp_arg_details_iter;
    env->Object_CallMethod_Ref(ani_arg_details, TH_ANI_FIND_CLASS_METHOD(env, "Lescompat/Record;", "$_iterator", nullptr), &cpp_arg_details_iter);
    ::taihe::map<::taihe::string, ::taihe::string> cpp_arg_details;
    while (true) {
        ani_ref cpp_arg_details_next;
        ani_boolean cpp_arg_details_done;
        env->Object_CallMethod_Ref(static_cast<ani_object>(cpp_arg_details_iter), TH_ANI_FIND_CLASS_METHOD(env, "Lescompat/MapIterator;", "next", nullptr), &cpp_arg_details_next);
        env->Object_GetField_Boolean(static_cast<ani_object>(cpp_arg_details_next), TH_ANI_FIND_CLASS_FIELD(env, "Lescompat/IteratorResult;", "done"), &cpp_arg_details_done);
        if (cpp_arg_details_done) {;
            break;
        };
        ani_ref cpp_arg_details_item;
        env->Object_GetField_Ref(static_cast<ani_object>(cpp_arg_details_next),  TH_ANI_FIND_CLASS_FIELD(env, "Lescompat/IteratorResult;", "value"), &cpp_arg_details_item);
        ani_ref cpp_arg_details_ani_key;
        env->TupleValue_GetItem_Ref(static_cast<ani_tuple_value>(cpp_arg_details_item), 0, &cpp_arg_details_ani_key);
        ani_ref cpp_arg_details_ani_val;
        env->TupleValue_GetItem_Ref(static_cast<ani_tuple_value>(cpp_arg_details_item), 1, &cpp_arg_details_ani_val);
        ani_size cpp_arg_details_cpp_key_len;
        env->String_GetUTF8Size(static_cast<ani_string>(cpp_arg_details_ani_key), &cpp_arg_details_cpp_key_len);
        TString cpp_arg_details_cpp_key_tstr;
        char* cpp_arg_details_cpp_key_buf = tstr_initialize(&cpp_arg_details_cpp_key_tstr, cpp_arg_details_cpp_key_len + 1);
        env->String_GetUTF8(static_cast<ani_string>(cpp_arg_details_ani_key), cpp_arg_details_cpp_key_buf, cpp_arg_details_cpp_key_len + 1, &cpp_arg_details_cpp_key_len);
        cpp_arg_details_cpp_key_buf[cpp_arg_details_cpp_key_len] = '\0';
        cpp_arg_details_cpp_key_tstr.length = cpp_arg_details_cpp_key_len;
        ::taihe::string cpp_arg_details_cpp_key = ::taihe::string(cpp_arg_details_cpp_key_tstr);
        ani_size cpp_arg_details_cpp_val_len;
        env->String_GetUTF8Size(static_cast<ani_string>(cpp_arg_details_ani_val), &cpp_arg_details_cpp_val_len);
        TString cpp_arg_details_cpp_val_tstr;
        char* cpp_arg_details_cpp_val_buf = tstr_initialize(&cpp_arg_details_cpp_val_tstr, cpp_arg_details_cpp_val_len + 1);
        env->String_GetUTF8(static_cast<ani_string>(cpp_arg_details_ani_val), cpp_arg_details_cpp_val_buf, cpp_arg_details_cpp_val_len + 1, &cpp_arg_details_cpp_val_len);
        cpp_arg_details_cpp_val_buf[cpp_arg_details_cpp_val_len] = '\0';
        cpp_arg_details_cpp_val_tstr.length = cpp_arg_details_cpp_val_len;
        ::taihe::string cpp_arg_details_cpp_val = ::taihe::string(cpp_arg_details_cpp_val_tstr);
        cpp_arg_details.emplace(cpp_arg_details_cpp_key, cpp_arg_details_cpp_val);
    }
    ::ohos::data::unifiedDataChannel::weak::TextInner(cpp_iface)->SetDetails(cpp_arg_details);
}
static ani_long ohos_data_unifiedDataChannel_TextInner_GetInner_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/TextInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/TextInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_TextInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_TextInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::TextInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::TextInner({cpp_vtbl_ptr, cpp_data_ptr});
    int64_t cpp_result = ::ohos::data::unifiedDataChannel::weak::TextInner(cpp_iface)->GetInner();
    if (::taihe::has_error()) { return ani_long{}; }
    ani_long ani_result = (int64_t)cpp_result;
    return ani_result;
}
static void ohos_data_unifiedDataChannel_TextInner_static_finalize_ANIFunc4([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_class clazz, ani_long data_ptr) {
    ::taihe::data_holder(reinterpret_cast<DataBlockHead*>(data_ptr));
}
static ani_string ohos_data_unifiedDataChannel_HTMLInner_GetType_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/HTMLInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/HTMLInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_HTMLInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_HTMLInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::HTMLInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::HTMLInner({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::string cpp_result = ::ohos::data::unifiedDataChannel::weak::HTMLInner(cpp_iface)->GetType();
    if (::taihe::has_error()) { return ani_string{}; }
    ani_string ani_result;
    env->String_NewUTF8(cpp_result.c_str(), cpp_result.size(), &ani_result);
    return ani_result;
}
static ani_ref ohos_data_unifiedDataChannel_HTMLInner_GetValue_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/HTMLInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/HTMLInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_HTMLInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_HTMLInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::HTMLInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::HTMLInner({cpp_vtbl_ptr, cpp_data_ptr});
    ::ohos::data::unifiedDataChannel::ValueType cpp_result = ::ohos::data::unifiedDataChannel::weak::HTMLInner(cpp_iface)->GetValue();
    if (::taihe::has_error()) { return ani_ref{}; }
    ani_ref ani_result = ohos_data_unifiedDataChannel_ValueType_intoANI(env, cpp_result);
    return ani_result;
}
static ani_ref ohos_data_unifiedDataChannel_HTMLInner_GetDetails_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/HTMLInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/HTMLInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_HTMLInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_HTMLInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::HTMLInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::HTMLInner({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::optional<::taihe::map<::taihe::string, ::taihe::string>> cpp_result = ::ohos::data::unifiedDataChannel::weak::HTMLInner(cpp_iface)->GetDetails();
    if (::taihe::has_error()) { return ani_ref{}; }
    ani_ref ani_result;
    if (!cpp_result) {
        env->GetUndefined(&ani_result);
    }
    else {
        ani_object ani_result_spec;
        env->Object_New(TH_ANI_FIND_CLASS(env, "Lescompat/Record;"), TH_ANI_FIND_CLASS_METHOD(env, "Lescompat/Record;", "<ctor>", nullptr), &ani_result_spec);
        for (const auto& [ani_result_spec_cpp_key, ani_result_spec_cpp_val] : (*cpp_result)) {
            ani_string ani_result_spec_ani_key;
            env->String_NewUTF8(ani_result_spec_cpp_key.c_str(), ani_result_spec_cpp_key.size(), &ani_result_spec_ani_key);
            ani_string ani_result_spec_ani_val;
            env->String_NewUTF8(ani_result_spec_cpp_val.c_str(), ani_result_spec_cpp_val.size(), &ani_result_spec_ani_val);
            env->Object_CallMethod_Void(ani_result_spec, TH_ANI_FIND_CLASS_METHOD(env, "Lescompat/Record;", "$_set", nullptr), ani_result_spec_ani_key, ani_result_spec_ani_val);
        }
        ani_result = ani_result_spec;
    }
    return ani_result;
}
static void ohos_data_unifiedDataChannel_HTMLInner_SetDetails_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object, ani_object ani_arg_details) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/HTMLInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/HTMLInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_HTMLInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_HTMLInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::HTMLInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::HTMLInner({cpp_vtbl_ptr, cpp_data_ptr});
    ani_ref cpp_arg_details_iter;
    env->Object_CallMethod_Ref(ani_arg_details, TH_ANI_FIND_CLASS_METHOD(env, "Lescompat/Record;", "$_iterator", nullptr), &cpp_arg_details_iter);
    ::taihe::map<::taihe::string, ::taihe::string> cpp_arg_details;
    while (true) {
        ani_ref cpp_arg_details_next;
        ani_boolean cpp_arg_details_done;
        env->Object_CallMethod_Ref(static_cast<ani_object>(cpp_arg_details_iter), TH_ANI_FIND_CLASS_METHOD(env, "Lescompat/MapIterator;", "next", nullptr), &cpp_arg_details_next);
        env->Object_GetField_Boolean(static_cast<ani_object>(cpp_arg_details_next), TH_ANI_FIND_CLASS_FIELD(env, "Lescompat/IteratorResult;", "done"), &cpp_arg_details_done);
        if (cpp_arg_details_done) {;
            break;
        };
        ani_ref cpp_arg_details_item;
        env->Object_GetField_Ref(static_cast<ani_object>(cpp_arg_details_next),  TH_ANI_FIND_CLASS_FIELD(env, "Lescompat/IteratorResult;", "value"), &cpp_arg_details_item);
        ani_ref cpp_arg_details_ani_key;
        env->TupleValue_GetItem_Ref(static_cast<ani_tuple_value>(cpp_arg_details_item), 0, &cpp_arg_details_ani_key);
        ani_ref cpp_arg_details_ani_val;
        env->TupleValue_GetItem_Ref(static_cast<ani_tuple_value>(cpp_arg_details_item), 1, &cpp_arg_details_ani_val);
        ani_size cpp_arg_details_cpp_key_len;
        env->String_GetUTF8Size(static_cast<ani_string>(cpp_arg_details_ani_key), &cpp_arg_details_cpp_key_len);
        TString cpp_arg_details_cpp_key_tstr;
        char* cpp_arg_details_cpp_key_buf = tstr_initialize(&cpp_arg_details_cpp_key_tstr, cpp_arg_details_cpp_key_len + 1);
        env->String_GetUTF8(static_cast<ani_string>(cpp_arg_details_ani_key), cpp_arg_details_cpp_key_buf, cpp_arg_details_cpp_key_len + 1, &cpp_arg_details_cpp_key_len);
        cpp_arg_details_cpp_key_buf[cpp_arg_details_cpp_key_len] = '\0';
        cpp_arg_details_cpp_key_tstr.length = cpp_arg_details_cpp_key_len;
        ::taihe::string cpp_arg_details_cpp_key = ::taihe::string(cpp_arg_details_cpp_key_tstr);
        ani_size cpp_arg_details_cpp_val_len;
        env->String_GetUTF8Size(static_cast<ani_string>(cpp_arg_details_ani_val), &cpp_arg_details_cpp_val_len);
        TString cpp_arg_details_cpp_val_tstr;
        char* cpp_arg_details_cpp_val_buf = tstr_initialize(&cpp_arg_details_cpp_val_tstr, cpp_arg_details_cpp_val_len + 1);
        env->String_GetUTF8(static_cast<ani_string>(cpp_arg_details_ani_val), cpp_arg_details_cpp_val_buf, cpp_arg_details_cpp_val_len + 1, &cpp_arg_details_cpp_val_len);
        cpp_arg_details_cpp_val_buf[cpp_arg_details_cpp_val_len] = '\0';
        cpp_arg_details_cpp_val_tstr.length = cpp_arg_details_cpp_val_len;
        ::taihe::string cpp_arg_details_cpp_val = ::taihe::string(cpp_arg_details_cpp_val_tstr);
        cpp_arg_details.emplace(cpp_arg_details_cpp_key, cpp_arg_details_cpp_val);
    }
    ::ohos::data::unifiedDataChannel::weak::HTMLInner(cpp_iface)->SetDetails(cpp_arg_details);
}
static void ohos_data_unifiedDataChannel_HTMLInner_SetHtmlContent_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object, ani_string ani_arg_htmlContent) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/HTMLInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/HTMLInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_HTMLInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_HTMLInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::HTMLInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::HTMLInner({cpp_vtbl_ptr, cpp_data_ptr});
    ani_size cpp_arg_htmlContent_len;
    env->String_GetUTF8Size(ani_arg_htmlContent, &cpp_arg_htmlContent_len);
    TString cpp_arg_htmlContent_tstr;
    char* cpp_arg_htmlContent_buf = tstr_initialize(&cpp_arg_htmlContent_tstr, cpp_arg_htmlContent_len + 1);
    env->String_GetUTF8(ani_arg_htmlContent, cpp_arg_htmlContent_buf, cpp_arg_htmlContent_len + 1, &cpp_arg_htmlContent_len);
    cpp_arg_htmlContent_buf[cpp_arg_htmlContent_len] = '\0';
    cpp_arg_htmlContent_tstr.length = cpp_arg_htmlContent_len;
    ::taihe::string cpp_arg_htmlContent = ::taihe::string(cpp_arg_htmlContent_tstr);
    ::ohos::data::unifiedDataChannel::weak::HTMLInner(cpp_iface)->SetHtmlContent(cpp_arg_htmlContent);
}
static ani_string ohos_data_unifiedDataChannel_HTMLInner_GetHtmlContent_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/HTMLInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/HTMLInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_HTMLInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_HTMLInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::HTMLInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::HTMLInner({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::string cpp_result = ::ohos::data::unifiedDataChannel::weak::HTMLInner(cpp_iface)->GetHtmlContent();
    if (::taihe::has_error()) { return ani_string{}; }
    ani_string ani_result;
    env->String_NewUTF8(cpp_result.c_str(), cpp_result.size(), &ani_result);
    return ani_result;
}
static void ohos_data_unifiedDataChannel_HTMLInner_SetPlainContent_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object, ani_string ani_arg_plainContent) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/HTMLInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/HTMLInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_HTMLInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_HTMLInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::HTMLInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::HTMLInner({cpp_vtbl_ptr, cpp_data_ptr});
    ani_size cpp_arg_plainContent_len;
    env->String_GetUTF8Size(ani_arg_plainContent, &cpp_arg_plainContent_len);
    TString cpp_arg_plainContent_tstr;
    char* cpp_arg_plainContent_buf = tstr_initialize(&cpp_arg_plainContent_tstr, cpp_arg_plainContent_len + 1);
    env->String_GetUTF8(ani_arg_plainContent, cpp_arg_plainContent_buf, cpp_arg_plainContent_len + 1, &cpp_arg_plainContent_len);
    cpp_arg_plainContent_buf[cpp_arg_plainContent_len] = '\0';
    cpp_arg_plainContent_tstr.length = cpp_arg_plainContent_len;
    ::taihe::string cpp_arg_plainContent = ::taihe::string(cpp_arg_plainContent_tstr);
    ::ohos::data::unifiedDataChannel::weak::HTMLInner(cpp_iface)->SetPlainContent(cpp_arg_plainContent);
}
static ani_string ohos_data_unifiedDataChannel_HTMLInner_GetPlainContent_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/HTMLInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/HTMLInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_HTMLInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_HTMLInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::HTMLInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::HTMLInner({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::string cpp_result = ::ohos::data::unifiedDataChannel::weak::HTMLInner(cpp_iface)->GetPlainContent();
    if (::taihe::has_error()) { return ani_string{}; }
    ani_string ani_result;
    env->String_NewUTF8(cpp_result.c_str(), cpp_result.size(), &ani_result);
    return ani_result;
}
static ani_long ohos_data_unifiedDataChannel_HTMLInner_GetInner_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/HTMLInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/HTMLInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_HTMLInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_HTMLInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::HTMLInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::HTMLInner({cpp_vtbl_ptr, cpp_data_ptr});
    int64_t cpp_result = ::ohos::data::unifiedDataChannel::weak::HTMLInner(cpp_iface)->GetInner();
    if (::taihe::has_error()) { return ani_long{}; }
    ani_long ani_result = (int64_t)cpp_result;
    return ani_result;
}
static void ohos_data_unifiedDataChannel_HTMLInner_static_finalize_ANIFunc4([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_class clazz, ani_long data_ptr) {
    ::taihe::data_holder(reinterpret_cast<DataBlockHead*>(data_ptr));
}
static ani_string ohos_data_unifiedDataChannel_HyperlinkInner_GetType_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/HyperlinkInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/HyperlinkInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_HyperlinkInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_HyperlinkInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::HyperlinkInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::HyperlinkInner({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::string cpp_result = ::ohos::data::unifiedDataChannel::weak::HyperlinkInner(cpp_iface)->GetType();
    if (::taihe::has_error()) { return ani_string{}; }
    ani_string ani_result;
    env->String_NewUTF8(cpp_result.c_str(), cpp_result.size(), &ani_result);
    return ani_result;
}
static ani_ref ohos_data_unifiedDataChannel_HyperlinkInner_GetValue_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/HyperlinkInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/HyperlinkInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_HyperlinkInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_HyperlinkInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::HyperlinkInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::HyperlinkInner({cpp_vtbl_ptr, cpp_data_ptr});
    ::ohos::data::unifiedDataChannel::ValueType cpp_result = ::ohos::data::unifiedDataChannel::weak::HyperlinkInner(cpp_iface)->GetValue();
    if (::taihe::has_error()) { return ani_ref{}; }
    ani_ref ani_result = ohos_data_unifiedDataChannel_ValueType_intoANI(env, cpp_result);
    return ani_result;
}
static ani_ref ohos_data_unifiedDataChannel_HyperlinkInner_GetDetails_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/HyperlinkInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/HyperlinkInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_HyperlinkInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_HyperlinkInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::HyperlinkInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::HyperlinkInner({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::optional<::taihe::map<::taihe::string, ::taihe::string>> cpp_result = ::ohos::data::unifiedDataChannel::weak::HyperlinkInner(cpp_iface)->GetDetails();
    if (::taihe::has_error()) { return ani_ref{}; }
    ani_ref ani_result;
    if (!cpp_result) {
        env->GetUndefined(&ani_result);
    }
    else {
        ani_object ani_result_spec;
        env->Object_New(TH_ANI_FIND_CLASS(env, "Lescompat/Record;"), TH_ANI_FIND_CLASS_METHOD(env, "Lescompat/Record;", "<ctor>", nullptr), &ani_result_spec);
        for (const auto& [ani_result_spec_cpp_key, ani_result_spec_cpp_val] : (*cpp_result)) {
            ani_string ani_result_spec_ani_key;
            env->String_NewUTF8(ani_result_spec_cpp_key.c_str(), ani_result_spec_cpp_key.size(), &ani_result_spec_ani_key);
            ani_string ani_result_spec_ani_val;
            env->String_NewUTF8(ani_result_spec_cpp_val.c_str(), ani_result_spec_cpp_val.size(), &ani_result_spec_ani_val);
            env->Object_CallMethod_Void(ani_result_spec, TH_ANI_FIND_CLASS_METHOD(env, "Lescompat/Record;", "$_set", nullptr), ani_result_spec_ani_key, ani_result_spec_ani_val);
        }
        ani_result = ani_result_spec;
    }
    return ani_result;
}
static void ohos_data_unifiedDataChannel_HyperlinkInner_SetDetails_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object, ani_object ani_arg_details) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/HyperlinkInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/HyperlinkInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_HyperlinkInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_HyperlinkInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::HyperlinkInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::HyperlinkInner({cpp_vtbl_ptr, cpp_data_ptr});
    ani_ref cpp_arg_details_iter;
    env->Object_CallMethod_Ref(ani_arg_details, TH_ANI_FIND_CLASS_METHOD(env, "Lescompat/Record;", "$_iterator", nullptr), &cpp_arg_details_iter);
    ::taihe::map<::taihe::string, ::taihe::string> cpp_arg_details;
    while (true) {
        ani_ref cpp_arg_details_next;
        ani_boolean cpp_arg_details_done;
        env->Object_CallMethod_Ref(static_cast<ani_object>(cpp_arg_details_iter), TH_ANI_FIND_CLASS_METHOD(env, "Lescompat/MapIterator;", "next", nullptr), &cpp_arg_details_next);
        env->Object_GetField_Boolean(static_cast<ani_object>(cpp_arg_details_next), TH_ANI_FIND_CLASS_FIELD(env, "Lescompat/IteratorResult;", "done"), &cpp_arg_details_done);
        if (cpp_arg_details_done) {;
            break;
        };
        ani_ref cpp_arg_details_item;
        env->Object_GetField_Ref(static_cast<ani_object>(cpp_arg_details_next),  TH_ANI_FIND_CLASS_FIELD(env, "Lescompat/IteratorResult;", "value"), &cpp_arg_details_item);
        ani_ref cpp_arg_details_ani_key;
        env->TupleValue_GetItem_Ref(static_cast<ani_tuple_value>(cpp_arg_details_item), 0, &cpp_arg_details_ani_key);
        ani_ref cpp_arg_details_ani_val;
        env->TupleValue_GetItem_Ref(static_cast<ani_tuple_value>(cpp_arg_details_item), 1, &cpp_arg_details_ani_val);
        ani_size cpp_arg_details_cpp_key_len;
        env->String_GetUTF8Size(static_cast<ani_string>(cpp_arg_details_ani_key), &cpp_arg_details_cpp_key_len);
        TString cpp_arg_details_cpp_key_tstr;
        char* cpp_arg_details_cpp_key_buf = tstr_initialize(&cpp_arg_details_cpp_key_tstr, cpp_arg_details_cpp_key_len + 1);
        env->String_GetUTF8(static_cast<ani_string>(cpp_arg_details_ani_key), cpp_arg_details_cpp_key_buf, cpp_arg_details_cpp_key_len + 1, &cpp_arg_details_cpp_key_len);
        cpp_arg_details_cpp_key_buf[cpp_arg_details_cpp_key_len] = '\0';
        cpp_arg_details_cpp_key_tstr.length = cpp_arg_details_cpp_key_len;
        ::taihe::string cpp_arg_details_cpp_key = ::taihe::string(cpp_arg_details_cpp_key_tstr);
        ani_size cpp_arg_details_cpp_val_len;
        env->String_GetUTF8Size(static_cast<ani_string>(cpp_arg_details_ani_val), &cpp_arg_details_cpp_val_len);
        TString cpp_arg_details_cpp_val_tstr;
        char* cpp_arg_details_cpp_val_buf = tstr_initialize(&cpp_arg_details_cpp_val_tstr, cpp_arg_details_cpp_val_len + 1);
        env->String_GetUTF8(static_cast<ani_string>(cpp_arg_details_ani_val), cpp_arg_details_cpp_val_buf, cpp_arg_details_cpp_val_len + 1, &cpp_arg_details_cpp_val_len);
        cpp_arg_details_cpp_val_buf[cpp_arg_details_cpp_val_len] = '\0';
        cpp_arg_details_cpp_val_tstr.length = cpp_arg_details_cpp_val_len;
        ::taihe::string cpp_arg_details_cpp_val = ::taihe::string(cpp_arg_details_cpp_val_tstr);
        cpp_arg_details.emplace(cpp_arg_details_cpp_key, cpp_arg_details_cpp_val);
    }
    ::ohos::data::unifiedDataChannel::weak::HyperlinkInner(cpp_iface)->SetDetails(cpp_arg_details);
}
static void ohos_data_unifiedDataChannel_HyperlinkInner_SetUrl_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object, ani_string ani_arg_url) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/HyperlinkInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/HyperlinkInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_HyperlinkInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_HyperlinkInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::HyperlinkInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::HyperlinkInner({cpp_vtbl_ptr, cpp_data_ptr});
    ani_size cpp_arg_url_len;
    env->String_GetUTF8Size(ani_arg_url, &cpp_arg_url_len);
    TString cpp_arg_url_tstr;
    char* cpp_arg_url_buf = tstr_initialize(&cpp_arg_url_tstr, cpp_arg_url_len + 1);
    env->String_GetUTF8(ani_arg_url, cpp_arg_url_buf, cpp_arg_url_len + 1, &cpp_arg_url_len);
    cpp_arg_url_buf[cpp_arg_url_len] = '\0';
    cpp_arg_url_tstr.length = cpp_arg_url_len;
    ::taihe::string cpp_arg_url = ::taihe::string(cpp_arg_url_tstr);
    ::ohos::data::unifiedDataChannel::weak::HyperlinkInner(cpp_iface)->SetUrl(cpp_arg_url);
}
static ani_string ohos_data_unifiedDataChannel_HyperlinkInner_GetUrl_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/HyperlinkInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/HyperlinkInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_HyperlinkInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_HyperlinkInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::HyperlinkInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::HyperlinkInner({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::string cpp_result = ::ohos::data::unifiedDataChannel::weak::HyperlinkInner(cpp_iface)->GetUrl();
    if (::taihe::has_error()) { return ani_string{}; }
    ani_string ani_result;
    env->String_NewUTF8(cpp_result.c_str(), cpp_result.size(), &ani_result);
    return ani_result;
}
static void ohos_data_unifiedDataChannel_HyperlinkInner_SetDescription_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object, ani_string ani_arg_description) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/HyperlinkInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/HyperlinkInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_HyperlinkInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_HyperlinkInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::HyperlinkInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::HyperlinkInner({cpp_vtbl_ptr, cpp_data_ptr});
    ani_size cpp_arg_description_len;
    env->String_GetUTF8Size(ani_arg_description, &cpp_arg_description_len);
    TString cpp_arg_description_tstr;
    char* cpp_arg_description_buf = tstr_initialize(&cpp_arg_description_tstr, cpp_arg_description_len + 1);
    env->String_GetUTF8(ani_arg_description, cpp_arg_description_buf, cpp_arg_description_len + 1, &cpp_arg_description_len);
    cpp_arg_description_buf[cpp_arg_description_len] = '\0';
    cpp_arg_description_tstr.length = cpp_arg_description_len;
    ::taihe::string cpp_arg_description = ::taihe::string(cpp_arg_description_tstr);
    ::ohos::data::unifiedDataChannel::weak::HyperlinkInner(cpp_iface)->SetDescription(cpp_arg_description);
}
static ani_string ohos_data_unifiedDataChannel_HyperlinkInner_GetDescription_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/HyperlinkInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/HyperlinkInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_HyperlinkInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_HyperlinkInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::HyperlinkInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::HyperlinkInner({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::string cpp_result = ::ohos::data::unifiedDataChannel::weak::HyperlinkInner(cpp_iface)->GetDescription();
    if (::taihe::has_error()) { return ani_string{}; }
    ani_string ani_result;
    env->String_NewUTF8(cpp_result.c_str(), cpp_result.size(), &ani_result);
    return ani_result;
}
static ani_long ohos_data_unifiedDataChannel_HyperlinkInner_GetInner_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/HyperlinkInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/HyperlinkInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_HyperlinkInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_HyperlinkInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::HyperlinkInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::HyperlinkInner({cpp_vtbl_ptr, cpp_data_ptr});
    int64_t cpp_result = ::ohos::data::unifiedDataChannel::weak::HyperlinkInner(cpp_iface)->GetInner();
    if (::taihe::has_error()) { return ani_long{}; }
    ani_long ani_result = (int64_t)cpp_result;
    return ani_result;
}
static void ohos_data_unifiedDataChannel_HyperlinkInner_static_finalize_ANIFunc4([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_class clazz, ani_long data_ptr) {
    ::taihe::data_holder(reinterpret_cast<DataBlockHead*>(data_ptr));
}
static ani_string ohos_data_unifiedDataChannel_PlainTextInner_GetType_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/PlainTextInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/PlainTextInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_PlainTextInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_PlainTextInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::PlainTextInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::PlainTextInner({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::string cpp_result = ::ohos::data::unifiedDataChannel::weak::PlainTextInner(cpp_iface)->GetType();
    if (::taihe::has_error()) { return ani_string{}; }
    ani_string ani_result;
    env->String_NewUTF8(cpp_result.c_str(), cpp_result.size(), &ani_result);
    return ani_result;
}
static ani_ref ohos_data_unifiedDataChannel_PlainTextInner_GetValue_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/PlainTextInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/PlainTextInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_PlainTextInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_PlainTextInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::PlainTextInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::PlainTextInner({cpp_vtbl_ptr, cpp_data_ptr});
    ::ohos::data::unifiedDataChannel::ValueType cpp_result = ::ohos::data::unifiedDataChannel::weak::PlainTextInner(cpp_iface)->GetValue();
    if (::taihe::has_error()) { return ani_ref{}; }
    ani_ref ani_result = ohos_data_unifiedDataChannel_ValueType_intoANI(env, cpp_result);
    return ani_result;
}
static ani_ref ohos_data_unifiedDataChannel_PlainTextInner_GetDetails_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/PlainTextInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/PlainTextInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_PlainTextInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_PlainTextInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::PlainTextInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::PlainTextInner({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::optional<::taihe::map<::taihe::string, ::taihe::string>> cpp_result = ::ohos::data::unifiedDataChannel::weak::PlainTextInner(cpp_iface)->GetDetails();
    if (::taihe::has_error()) { return ani_ref{}; }
    ani_ref ani_result;
    if (!cpp_result) {
        env->GetUndefined(&ani_result);
    }
    else {
        ani_object ani_result_spec;
        env->Object_New(TH_ANI_FIND_CLASS(env, "Lescompat/Record;"), TH_ANI_FIND_CLASS_METHOD(env, "Lescompat/Record;", "<ctor>", nullptr), &ani_result_spec);
        for (const auto& [ani_result_spec_cpp_key, ani_result_spec_cpp_val] : (*cpp_result)) {
            ani_string ani_result_spec_ani_key;
            env->String_NewUTF8(ani_result_spec_cpp_key.c_str(), ani_result_spec_cpp_key.size(), &ani_result_spec_ani_key);
            ani_string ani_result_spec_ani_val;
            env->String_NewUTF8(ani_result_spec_cpp_val.c_str(), ani_result_spec_cpp_val.size(), &ani_result_spec_ani_val);
            env->Object_CallMethod_Void(ani_result_spec, TH_ANI_FIND_CLASS_METHOD(env, "Lescompat/Record;", "$_set", nullptr), ani_result_spec_ani_key, ani_result_spec_ani_val);
        }
        ani_result = ani_result_spec;
    }
    return ani_result;
}
static void ohos_data_unifiedDataChannel_PlainTextInner_SetDetails_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object, ani_object ani_arg_details) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/PlainTextInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/PlainTextInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_PlainTextInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_PlainTextInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::PlainTextInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::PlainTextInner({cpp_vtbl_ptr, cpp_data_ptr});
    ani_ref cpp_arg_details_iter;
    env->Object_CallMethod_Ref(ani_arg_details, TH_ANI_FIND_CLASS_METHOD(env, "Lescompat/Record;", "$_iterator", nullptr), &cpp_arg_details_iter);
    ::taihe::map<::taihe::string, ::taihe::string> cpp_arg_details;
    while (true) {
        ani_ref cpp_arg_details_next;
        ani_boolean cpp_arg_details_done;
        env->Object_CallMethod_Ref(static_cast<ani_object>(cpp_arg_details_iter), TH_ANI_FIND_CLASS_METHOD(env, "Lescompat/MapIterator;", "next", nullptr), &cpp_arg_details_next);
        env->Object_GetField_Boolean(static_cast<ani_object>(cpp_arg_details_next), TH_ANI_FIND_CLASS_FIELD(env, "Lescompat/IteratorResult;", "done"), &cpp_arg_details_done);
        if (cpp_arg_details_done) {;
            break;
        };
        ani_ref cpp_arg_details_item;
        env->Object_GetField_Ref(static_cast<ani_object>(cpp_arg_details_next),  TH_ANI_FIND_CLASS_FIELD(env, "Lescompat/IteratorResult;", "value"), &cpp_arg_details_item);
        ani_ref cpp_arg_details_ani_key;
        env->TupleValue_GetItem_Ref(static_cast<ani_tuple_value>(cpp_arg_details_item), 0, &cpp_arg_details_ani_key);
        ani_ref cpp_arg_details_ani_val;
        env->TupleValue_GetItem_Ref(static_cast<ani_tuple_value>(cpp_arg_details_item), 1, &cpp_arg_details_ani_val);
        ani_size cpp_arg_details_cpp_key_len;
        env->String_GetUTF8Size(static_cast<ani_string>(cpp_arg_details_ani_key), &cpp_arg_details_cpp_key_len);
        TString cpp_arg_details_cpp_key_tstr;
        char* cpp_arg_details_cpp_key_buf = tstr_initialize(&cpp_arg_details_cpp_key_tstr, cpp_arg_details_cpp_key_len + 1);
        env->String_GetUTF8(static_cast<ani_string>(cpp_arg_details_ani_key), cpp_arg_details_cpp_key_buf, cpp_arg_details_cpp_key_len + 1, &cpp_arg_details_cpp_key_len);
        cpp_arg_details_cpp_key_buf[cpp_arg_details_cpp_key_len] = '\0';
        cpp_arg_details_cpp_key_tstr.length = cpp_arg_details_cpp_key_len;
        ::taihe::string cpp_arg_details_cpp_key = ::taihe::string(cpp_arg_details_cpp_key_tstr);
        ani_size cpp_arg_details_cpp_val_len;
        env->String_GetUTF8Size(static_cast<ani_string>(cpp_arg_details_ani_val), &cpp_arg_details_cpp_val_len);
        TString cpp_arg_details_cpp_val_tstr;
        char* cpp_arg_details_cpp_val_buf = tstr_initialize(&cpp_arg_details_cpp_val_tstr, cpp_arg_details_cpp_val_len + 1);
        env->String_GetUTF8(static_cast<ani_string>(cpp_arg_details_ani_val), cpp_arg_details_cpp_val_buf, cpp_arg_details_cpp_val_len + 1, &cpp_arg_details_cpp_val_len);
        cpp_arg_details_cpp_val_buf[cpp_arg_details_cpp_val_len] = '\0';
        cpp_arg_details_cpp_val_tstr.length = cpp_arg_details_cpp_val_len;
        ::taihe::string cpp_arg_details_cpp_val = ::taihe::string(cpp_arg_details_cpp_val_tstr);
        cpp_arg_details.emplace(cpp_arg_details_cpp_key, cpp_arg_details_cpp_val);
    }
    ::ohos::data::unifiedDataChannel::weak::PlainTextInner(cpp_iface)->SetDetails(cpp_arg_details);
}
static void ohos_data_unifiedDataChannel_PlainTextInner_SetTextContent_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object, ani_string ani_arg_textContent) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/PlainTextInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/PlainTextInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_PlainTextInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_PlainTextInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::PlainTextInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::PlainTextInner({cpp_vtbl_ptr, cpp_data_ptr});
    ani_size cpp_arg_textContent_len;
    env->String_GetUTF8Size(ani_arg_textContent, &cpp_arg_textContent_len);
    TString cpp_arg_textContent_tstr;
    char* cpp_arg_textContent_buf = tstr_initialize(&cpp_arg_textContent_tstr, cpp_arg_textContent_len + 1);
    env->String_GetUTF8(ani_arg_textContent, cpp_arg_textContent_buf, cpp_arg_textContent_len + 1, &cpp_arg_textContent_len);
    cpp_arg_textContent_buf[cpp_arg_textContent_len] = '\0';
    cpp_arg_textContent_tstr.length = cpp_arg_textContent_len;
    ::taihe::string cpp_arg_textContent = ::taihe::string(cpp_arg_textContent_tstr);
    ::ohos::data::unifiedDataChannel::weak::PlainTextInner(cpp_iface)->SetTextContent(cpp_arg_textContent);
}
static ani_string ohos_data_unifiedDataChannel_PlainTextInner_GetTextContent_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/PlainTextInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/PlainTextInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_PlainTextInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_PlainTextInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::PlainTextInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::PlainTextInner({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::string cpp_result = ::ohos::data::unifiedDataChannel::weak::PlainTextInner(cpp_iface)->GetTextContent();
    if (::taihe::has_error()) { return ani_string{}; }
    ani_string ani_result;
    env->String_NewUTF8(cpp_result.c_str(), cpp_result.size(), &ani_result);
    return ani_result;
}
static ani_long ohos_data_unifiedDataChannel_PlainTextInner_GetInner_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/PlainTextInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/PlainTextInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_PlainTextInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_PlainTextInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::PlainTextInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::PlainTextInner({cpp_vtbl_ptr, cpp_data_ptr});
    int64_t cpp_result = ::ohos::data::unifiedDataChannel::weak::PlainTextInner(cpp_iface)->GetInner();
    if (::taihe::has_error()) { return ani_long{}; }
    ani_long ani_result = (int64_t)cpp_result;
    return ani_result;
}
static void ohos_data_unifiedDataChannel_PlainTextInner_static_finalize_ANIFunc4([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_class clazz, ani_long data_ptr) {
    ::taihe::data_holder(reinterpret_cast<DataBlockHead*>(data_ptr));
}
static ani_string ohos_data_unifiedDataChannel_SystemDefinedRecordInner_GetType_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedRecordInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedRecordInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_SystemDefinedRecordInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedRecordInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedRecordInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::SystemDefinedRecordInner({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::string cpp_result = ::ohos::data::unifiedDataChannel::weak::SystemDefinedRecordInner(cpp_iface)->GetType();
    if (::taihe::has_error()) { return ani_string{}; }
    ani_string ani_result;
    env->String_NewUTF8(cpp_result.c_str(), cpp_result.size(), &ani_result);
    return ani_result;
}
static ani_ref ohos_data_unifiedDataChannel_SystemDefinedRecordInner_GetValue_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedRecordInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedRecordInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_SystemDefinedRecordInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedRecordInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedRecordInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::SystemDefinedRecordInner({cpp_vtbl_ptr, cpp_data_ptr});
    ::ohos::data::unifiedDataChannel::ValueType cpp_result = ::ohos::data::unifiedDataChannel::weak::SystemDefinedRecordInner(cpp_iface)->GetValue();
    if (::taihe::has_error()) { return ani_ref{}; }
    ani_ref ani_result = ohos_data_unifiedDataChannel_ValueType_intoANI(env, cpp_result);
    return ani_result;
}
static ani_ref ohos_data_unifiedDataChannel_SystemDefinedRecordInner_GetDetails_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedRecordInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedRecordInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_SystemDefinedRecordInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedRecordInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedRecordInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::SystemDefinedRecordInner({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::optional<::taihe::map<::taihe::string, ::ohos::data::unifiedDataChannel::DetailsValue>> cpp_result = ::ohos::data::unifiedDataChannel::weak::SystemDefinedRecordInner(cpp_iface)->GetDetails();
    if (::taihe::has_error()) { return ani_ref{}; }
    ani_ref ani_result;
    if (!cpp_result) {
        env->GetUndefined(&ani_result);
    }
    else {
        ani_object ani_result_spec;
        env->Object_New(TH_ANI_FIND_CLASS(env, "Lescompat/Record;"), TH_ANI_FIND_CLASS_METHOD(env, "Lescompat/Record;", "<ctor>", nullptr), &ani_result_spec);
        for (const auto& [ani_result_spec_cpp_key, ani_result_spec_cpp_val] : (*cpp_result)) {
            ani_string ani_result_spec_ani_key;
            env->String_NewUTF8(ani_result_spec_cpp_key.c_str(), ani_result_spec_cpp_key.size(), &ani_result_spec_ani_key);
            ani_ref ani_result_spec_ani_val = ohos_data_unifiedDataChannel_DetailsValue_intoANI(env, ani_result_spec_cpp_val);
            env->Object_CallMethod_Void(ani_result_spec, TH_ANI_FIND_CLASS_METHOD(env, "Lescompat/Record;", "$_set", nullptr), ani_result_spec_ani_key, ani_result_spec_ani_val);
        }
        ani_result = ani_result_spec;
    }
    return ani_result;
}
static void ohos_data_unifiedDataChannel_SystemDefinedRecordInner_SetDetails_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object, ani_object ani_arg_details) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedRecordInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedRecordInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_SystemDefinedRecordInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedRecordInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedRecordInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::SystemDefinedRecordInner({cpp_vtbl_ptr, cpp_data_ptr});
    ani_ref cpp_arg_details_iter;
    env->Object_CallMethod_Ref(ani_arg_details, TH_ANI_FIND_CLASS_METHOD(env, "Lescompat/Record;", "$_iterator", nullptr), &cpp_arg_details_iter);
    ::taihe::map<::taihe::string, ::ohos::data::unifiedDataChannel::DetailsValue> cpp_arg_details;
    while (true) {
        ani_ref cpp_arg_details_next;
        ani_boolean cpp_arg_details_done;
        env->Object_CallMethod_Ref(static_cast<ani_object>(cpp_arg_details_iter), TH_ANI_FIND_CLASS_METHOD(env, "Lescompat/MapIterator;", "next", nullptr), &cpp_arg_details_next);
        env->Object_GetField_Boolean(static_cast<ani_object>(cpp_arg_details_next), TH_ANI_FIND_CLASS_FIELD(env, "Lescompat/IteratorResult;", "done"), &cpp_arg_details_done);
        if (cpp_arg_details_done) {;
            break;
        };
        ani_ref cpp_arg_details_item;
        env->Object_GetField_Ref(static_cast<ani_object>(cpp_arg_details_next),  TH_ANI_FIND_CLASS_FIELD(env, "Lescompat/IteratorResult;", "value"), &cpp_arg_details_item);
        ani_ref cpp_arg_details_ani_key;
        env->TupleValue_GetItem_Ref(static_cast<ani_tuple_value>(cpp_arg_details_item), 0, &cpp_arg_details_ani_key);
        ani_ref cpp_arg_details_ani_val;
        env->TupleValue_GetItem_Ref(static_cast<ani_tuple_value>(cpp_arg_details_item), 1, &cpp_arg_details_ani_val);
        ani_size cpp_arg_details_cpp_key_len;
        env->String_GetUTF8Size(static_cast<ani_string>(cpp_arg_details_ani_key), &cpp_arg_details_cpp_key_len);
        TString cpp_arg_details_cpp_key_tstr;
        char* cpp_arg_details_cpp_key_buf = tstr_initialize(&cpp_arg_details_cpp_key_tstr, cpp_arg_details_cpp_key_len + 1);
        env->String_GetUTF8(static_cast<ani_string>(cpp_arg_details_ani_key), cpp_arg_details_cpp_key_buf, cpp_arg_details_cpp_key_len + 1, &cpp_arg_details_cpp_key_len);
        cpp_arg_details_cpp_key_buf[cpp_arg_details_cpp_key_len] = '\0';
        cpp_arg_details_cpp_key_tstr.length = cpp_arg_details_cpp_key_len;
        ::taihe::string cpp_arg_details_cpp_key = ::taihe::string(cpp_arg_details_cpp_key_tstr);
        ::ohos::data::unifiedDataChannel::DetailsValue cpp_arg_details_cpp_val = ohos_data_unifiedDataChannel_DetailsValue_fromANI(env, static_cast<ani_ref>(cpp_arg_details_ani_val));
        cpp_arg_details.emplace(cpp_arg_details_cpp_key, cpp_arg_details_cpp_val);
    }
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedRecordInner(cpp_iface)->SetDetails(cpp_arg_details);
}
static ani_long ohos_data_unifiedDataChannel_SystemDefinedRecordInner_GetInner_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedRecordInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedRecordInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_SystemDefinedRecordInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedRecordInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedRecordInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::SystemDefinedRecordInner({cpp_vtbl_ptr, cpp_data_ptr});
    int64_t cpp_result = ::ohos::data::unifiedDataChannel::weak::SystemDefinedRecordInner(cpp_iface)->GetInner();
    if (::taihe::has_error()) { return ani_long{}; }
    ani_long ani_result = (int64_t)cpp_result;
    return ani_result;
}
static void ohos_data_unifiedDataChannel_SystemDefinedRecordInner_static_finalize_ANIFunc4([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_class clazz, ani_long data_ptr) {
    ::taihe::data_holder(reinterpret_cast<DataBlockHead*>(data_ptr));
}
static ani_string ohos_data_unifiedDataChannel_SystemDefinedFormInner_GetType_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedFormInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedFormInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_SystemDefinedFormInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedFormInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedFormInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::SystemDefinedFormInner({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::string cpp_result = ::ohos::data::unifiedDataChannel::weak::SystemDefinedFormInner(cpp_iface)->GetType();
    if (::taihe::has_error()) { return ani_string{}; }
    ani_string ani_result;
    env->String_NewUTF8(cpp_result.c_str(), cpp_result.size(), &ani_result);
    return ani_result;
}
static ani_ref ohos_data_unifiedDataChannel_SystemDefinedFormInner_GetValue_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedFormInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedFormInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_SystemDefinedFormInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedFormInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedFormInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::SystemDefinedFormInner({cpp_vtbl_ptr, cpp_data_ptr});
    ::ohos::data::unifiedDataChannel::ValueType cpp_result = ::ohos::data::unifiedDataChannel::weak::SystemDefinedFormInner(cpp_iface)->GetValue();
    if (::taihe::has_error()) { return ani_ref{}; }
    ani_ref ani_result = ohos_data_unifiedDataChannel_ValueType_intoANI(env, cpp_result);
    return ani_result;
}
static ani_ref ohos_data_unifiedDataChannel_SystemDefinedFormInner_GetDetails_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedFormInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedFormInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_SystemDefinedFormInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedFormInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedFormInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::SystemDefinedFormInner({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::optional<::taihe::map<::taihe::string, ::ohos::data::unifiedDataChannel::DetailsValue>> cpp_result = ::ohos::data::unifiedDataChannel::weak::SystemDefinedFormInner(cpp_iface)->GetDetails();
    if (::taihe::has_error()) { return ani_ref{}; }
    ani_ref ani_result;
    if (!cpp_result) {
        env->GetUndefined(&ani_result);
    }
    else {
        ani_object ani_result_spec;
        env->Object_New(TH_ANI_FIND_CLASS(env, "Lescompat/Record;"), TH_ANI_FIND_CLASS_METHOD(env, "Lescompat/Record;", "<ctor>", nullptr), &ani_result_spec);
        for (const auto& [ani_result_spec_cpp_key, ani_result_spec_cpp_val] : (*cpp_result)) {
            ani_string ani_result_spec_ani_key;
            env->String_NewUTF8(ani_result_spec_cpp_key.c_str(), ani_result_spec_cpp_key.size(), &ani_result_spec_ani_key);
            ani_ref ani_result_spec_ani_val = ohos_data_unifiedDataChannel_DetailsValue_intoANI(env, ani_result_spec_cpp_val);
            env->Object_CallMethod_Void(ani_result_spec, TH_ANI_FIND_CLASS_METHOD(env, "Lescompat/Record;", "$_set", nullptr), ani_result_spec_ani_key, ani_result_spec_ani_val);
        }
        ani_result = ani_result_spec;
    }
    return ani_result;
}
static void ohos_data_unifiedDataChannel_SystemDefinedFormInner_SetDetails_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object, ani_object ani_arg_details) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedFormInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedFormInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_SystemDefinedFormInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedFormInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedFormInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::SystemDefinedFormInner({cpp_vtbl_ptr, cpp_data_ptr});
    ani_ref cpp_arg_details_iter;
    env->Object_CallMethod_Ref(ani_arg_details, TH_ANI_FIND_CLASS_METHOD(env, "Lescompat/Record;", "$_iterator", nullptr), &cpp_arg_details_iter);
    ::taihe::map<::taihe::string, ::ohos::data::unifiedDataChannel::DetailsValue> cpp_arg_details;
    while (true) {
        ani_ref cpp_arg_details_next;
        ani_boolean cpp_arg_details_done;
        env->Object_CallMethod_Ref(static_cast<ani_object>(cpp_arg_details_iter), TH_ANI_FIND_CLASS_METHOD(env, "Lescompat/MapIterator;", "next", nullptr), &cpp_arg_details_next);
        env->Object_GetField_Boolean(static_cast<ani_object>(cpp_arg_details_next), TH_ANI_FIND_CLASS_FIELD(env, "Lescompat/IteratorResult;", "done"), &cpp_arg_details_done);
        if (cpp_arg_details_done) {;
            break;
        };
        ani_ref cpp_arg_details_item;
        env->Object_GetField_Ref(static_cast<ani_object>(cpp_arg_details_next),  TH_ANI_FIND_CLASS_FIELD(env, "Lescompat/IteratorResult;", "value"), &cpp_arg_details_item);
        ani_ref cpp_arg_details_ani_key;
        env->TupleValue_GetItem_Ref(static_cast<ani_tuple_value>(cpp_arg_details_item), 0, &cpp_arg_details_ani_key);
        ani_ref cpp_arg_details_ani_val;
        env->TupleValue_GetItem_Ref(static_cast<ani_tuple_value>(cpp_arg_details_item), 1, &cpp_arg_details_ani_val);
        ani_size cpp_arg_details_cpp_key_len;
        env->String_GetUTF8Size(static_cast<ani_string>(cpp_arg_details_ani_key), &cpp_arg_details_cpp_key_len);
        TString cpp_arg_details_cpp_key_tstr;
        char* cpp_arg_details_cpp_key_buf = tstr_initialize(&cpp_arg_details_cpp_key_tstr, cpp_arg_details_cpp_key_len + 1);
        env->String_GetUTF8(static_cast<ani_string>(cpp_arg_details_ani_key), cpp_arg_details_cpp_key_buf, cpp_arg_details_cpp_key_len + 1, &cpp_arg_details_cpp_key_len);
        cpp_arg_details_cpp_key_buf[cpp_arg_details_cpp_key_len] = '\0';
        cpp_arg_details_cpp_key_tstr.length = cpp_arg_details_cpp_key_len;
        ::taihe::string cpp_arg_details_cpp_key = ::taihe::string(cpp_arg_details_cpp_key_tstr);
        ::ohos::data::unifiedDataChannel::DetailsValue cpp_arg_details_cpp_val = ohos_data_unifiedDataChannel_DetailsValue_fromANI(env, static_cast<ani_ref>(cpp_arg_details_ani_val));
        cpp_arg_details.emplace(cpp_arg_details_cpp_key, cpp_arg_details_cpp_val);
    }
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedFormInner(cpp_iface)->SetDetails(cpp_arg_details);
}
static ani_double ohos_data_unifiedDataChannel_SystemDefinedFormInner_GetFormId_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedFormInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedFormInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_SystemDefinedFormInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedFormInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedFormInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::SystemDefinedFormInner({cpp_vtbl_ptr, cpp_data_ptr});
    double cpp_result = ::ohos::data::unifiedDataChannel::weak::SystemDefinedFormInner(cpp_iface)->GetFormId();
    if (::taihe::has_error()) { return ani_double{}; }
    ani_double ani_result = (double)cpp_result;
    return ani_result;
}
static void ohos_data_unifiedDataChannel_SystemDefinedFormInner_SetFormId_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object, ani_double ani_arg_formId) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedFormInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedFormInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_SystemDefinedFormInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedFormInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedFormInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::SystemDefinedFormInner({cpp_vtbl_ptr, cpp_data_ptr});
    double cpp_arg_formId = (double)ani_arg_formId;
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedFormInner(cpp_iface)->SetFormId(cpp_arg_formId);
}
static ani_string ohos_data_unifiedDataChannel_SystemDefinedFormInner_GetFormName_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedFormInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedFormInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_SystemDefinedFormInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedFormInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedFormInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::SystemDefinedFormInner({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::string cpp_result = ::ohos::data::unifiedDataChannel::weak::SystemDefinedFormInner(cpp_iface)->GetFormName();
    if (::taihe::has_error()) { return ani_string{}; }
    ani_string ani_result;
    env->String_NewUTF8(cpp_result.c_str(), cpp_result.size(), &ani_result);
    return ani_result;
}
static void ohos_data_unifiedDataChannel_SystemDefinedFormInner_SetFormName_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object, ani_string ani_arg_formName) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedFormInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedFormInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_SystemDefinedFormInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedFormInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedFormInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::SystemDefinedFormInner({cpp_vtbl_ptr, cpp_data_ptr});
    ani_size cpp_arg_formName_len;
    env->String_GetUTF8Size(ani_arg_formName, &cpp_arg_formName_len);
    TString cpp_arg_formName_tstr;
    char* cpp_arg_formName_buf = tstr_initialize(&cpp_arg_formName_tstr, cpp_arg_formName_len + 1);
    env->String_GetUTF8(ani_arg_formName, cpp_arg_formName_buf, cpp_arg_formName_len + 1, &cpp_arg_formName_len);
    cpp_arg_formName_buf[cpp_arg_formName_len] = '\0';
    cpp_arg_formName_tstr.length = cpp_arg_formName_len;
    ::taihe::string cpp_arg_formName = ::taihe::string(cpp_arg_formName_tstr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedFormInner(cpp_iface)->SetFormName(cpp_arg_formName);
}
static ani_string ohos_data_unifiedDataChannel_SystemDefinedFormInner_GetBundleName_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedFormInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedFormInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_SystemDefinedFormInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedFormInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedFormInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::SystemDefinedFormInner({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::string cpp_result = ::ohos::data::unifiedDataChannel::weak::SystemDefinedFormInner(cpp_iface)->GetBundleName();
    if (::taihe::has_error()) { return ani_string{}; }
    ani_string ani_result;
    env->String_NewUTF8(cpp_result.c_str(), cpp_result.size(), &ani_result);
    return ani_result;
}
static void ohos_data_unifiedDataChannel_SystemDefinedFormInner_SetBundleName_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object, ani_string ani_arg_bundleName) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedFormInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedFormInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_SystemDefinedFormInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedFormInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedFormInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::SystemDefinedFormInner({cpp_vtbl_ptr, cpp_data_ptr});
    ani_size cpp_arg_bundleName_len;
    env->String_GetUTF8Size(ani_arg_bundleName, &cpp_arg_bundleName_len);
    TString cpp_arg_bundleName_tstr;
    char* cpp_arg_bundleName_buf = tstr_initialize(&cpp_arg_bundleName_tstr, cpp_arg_bundleName_len + 1);
    env->String_GetUTF8(ani_arg_bundleName, cpp_arg_bundleName_buf, cpp_arg_bundleName_len + 1, &cpp_arg_bundleName_len);
    cpp_arg_bundleName_buf[cpp_arg_bundleName_len] = '\0';
    cpp_arg_bundleName_tstr.length = cpp_arg_bundleName_len;
    ::taihe::string cpp_arg_bundleName = ::taihe::string(cpp_arg_bundleName_tstr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedFormInner(cpp_iface)->SetBundleName(cpp_arg_bundleName);
}
static ani_string ohos_data_unifiedDataChannel_SystemDefinedFormInner_GetAbilityName_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedFormInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedFormInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_SystemDefinedFormInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedFormInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedFormInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::SystemDefinedFormInner({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::string cpp_result = ::ohos::data::unifiedDataChannel::weak::SystemDefinedFormInner(cpp_iface)->GetAbilityName();
    if (::taihe::has_error()) { return ani_string{}; }
    ani_string ani_result;
    env->String_NewUTF8(cpp_result.c_str(), cpp_result.size(), &ani_result);
    return ani_result;
}
static void ohos_data_unifiedDataChannel_SystemDefinedFormInner_SetAbilityName_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object, ani_string ani_arg_abilityName) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedFormInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedFormInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_SystemDefinedFormInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedFormInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedFormInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::SystemDefinedFormInner({cpp_vtbl_ptr, cpp_data_ptr});
    ani_size cpp_arg_abilityName_len;
    env->String_GetUTF8Size(ani_arg_abilityName, &cpp_arg_abilityName_len);
    TString cpp_arg_abilityName_tstr;
    char* cpp_arg_abilityName_buf = tstr_initialize(&cpp_arg_abilityName_tstr, cpp_arg_abilityName_len + 1);
    env->String_GetUTF8(ani_arg_abilityName, cpp_arg_abilityName_buf, cpp_arg_abilityName_len + 1, &cpp_arg_abilityName_len);
    cpp_arg_abilityName_buf[cpp_arg_abilityName_len] = '\0';
    cpp_arg_abilityName_tstr.length = cpp_arg_abilityName_len;
    ::taihe::string cpp_arg_abilityName = ::taihe::string(cpp_arg_abilityName_tstr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedFormInner(cpp_iface)->SetAbilityName(cpp_arg_abilityName);
}
static ani_string ohos_data_unifiedDataChannel_SystemDefinedFormInner_GetModule_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedFormInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedFormInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_SystemDefinedFormInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedFormInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedFormInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::SystemDefinedFormInner({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::string cpp_result = ::ohos::data::unifiedDataChannel::weak::SystemDefinedFormInner(cpp_iface)->GetModule();
    if (::taihe::has_error()) { return ani_string{}; }
    ani_string ani_result;
    env->String_NewUTF8(cpp_result.c_str(), cpp_result.size(), &ani_result);
    return ani_result;
}
static void ohos_data_unifiedDataChannel_SystemDefinedFormInner_SetModule_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object, ani_string ani_arg_module) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedFormInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedFormInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_SystemDefinedFormInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedFormInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedFormInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::SystemDefinedFormInner({cpp_vtbl_ptr, cpp_data_ptr});
    ani_size cpp_arg_module_len;
    env->String_GetUTF8Size(ani_arg_module, &cpp_arg_module_len);
    TString cpp_arg_module_tstr;
    char* cpp_arg_module_buf = tstr_initialize(&cpp_arg_module_tstr, cpp_arg_module_len + 1);
    env->String_GetUTF8(ani_arg_module, cpp_arg_module_buf, cpp_arg_module_len + 1, &cpp_arg_module_len);
    cpp_arg_module_buf[cpp_arg_module_len] = '\0';
    cpp_arg_module_tstr.length = cpp_arg_module_len;
    ::taihe::string cpp_arg_module = ::taihe::string(cpp_arg_module_tstr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedFormInner(cpp_iface)->SetModule(cpp_arg_module);
}
static ani_long ohos_data_unifiedDataChannel_SystemDefinedFormInner_GetInner_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedFormInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedFormInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_SystemDefinedFormInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedFormInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedFormInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::SystemDefinedFormInner({cpp_vtbl_ptr, cpp_data_ptr});
    int64_t cpp_result = ::ohos::data::unifiedDataChannel::weak::SystemDefinedFormInner(cpp_iface)->GetInner();
    if (::taihe::has_error()) { return ani_long{}; }
    ani_long ani_result = (int64_t)cpp_result;
    return ani_result;
}
static void ohos_data_unifiedDataChannel_SystemDefinedFormInner_static_finalize_ANIFunc4([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_class clazz, ani_long data_ptr) {
    ::taihe::data_holder(reinterpret_cast<DataBlockHead*>(data_ptr));
}
static ani_string ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_GetType_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedAppItemInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedAppItemInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItemInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItemInner({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::string cpp_result = ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItemInner(cpp_iface)->GetType();
    if (::taihe::has_error()) { return ani_string{}; }
    ani_string ani_result;
    env->String_NewUTF8(cpp_result.c_str(), cpp_result.size(), &ani_result);
    return ani_result;
}
static ani_ref ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_GetValue_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedAppItemInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedAppItemInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItemInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItemInner({cpp_vtbl_ptr, cpp_data_ptr});
    ::ohos::data::unifiedDataChannel::ValueType cpp_result = ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItemInner(cpp_iface)->GetValue();
    if (::taihe::has_error()) { return ani_ref{}; }
    ani_ref ani_result = ohos_data_unifiedDataChannel_ValueType_intoANI(env, cpp_result);
    return ani_result;
}
static ani_ref ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_GetDetails_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedAppItemInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedAppItemInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItemInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItemInner({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::optional<::taihe::map<::taihe::string, ::ohos::data::unifiedDataChannel::DetailsValue>> cpp_result = ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItemInner(cpp_iface)->GetDetails();
    if (::taihe::has_error()) { return ani_ref{}; }
    ani_ref ani_result;
    if (!cpp_result) {
        env->GetUndefined(&ani_result);
    }
    else {
        ani_object ani_result_spec;
        env->Object_New(TH_ANI_FIND_CLASS(env, "Lescompat/Record;"), TH_ANI_FIND_CLASS_METHOD(env, "Lescompat/Record;", "<ctor>", nullptr), &ani_result_spec);
        for (const auto& [ani_result_spec_cpp_key, ani_result_spec_cpp_val] : (*cpp_result)) {
            ani_string ani_result_spec_ani_key;
            env->String_NewUTF8(ani_result_spec_cpp_key.c_str(), ani_result_spec_cpp_key.size(), &ani_result_spec_ani_key);
            ani_ref ani_result_spec_ani_val = ohos_data_unifiedDataChannel_DetailsValue_intoANI(env, ani_result_spec_cpp_val);
            env->Object_CallMethod_Void(ani_result_spec, TH_ANI_FIND_CLASS_METHOD(env, "Lescompat/Record;", "$_set", nullptr), ani_result_spec_ani_key, ani_result_spec_ani_val);
        }
        ani_result = ani_result_spec;
    }
    return ani_result;
}
static void ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_SetDetails_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object, ani_object ani_arg_details) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedAppItemInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedAppItemInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItemInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItemInner({cpp_vtbl_ptr, cpp_data_ptr});
    ani_ref cpp_arg_details_iter;
    env->Object_CallMethod_Ref(ani_arg_details, TH_ANI_FIND_CLASS_METHOD(env, "Lescompat/Record;", "$_iterator", nullptr), &cpp_arg_details_iter);
    ::taihe::map<::taihe::string, ::ohos::data::unifiedDataChannel::DetailsValue> cpp_arg_details;
    while (true) {
        ani_ref cpp_arg_details_next;
        ani_boolean cpp_arg_details_done;
        env->Object_CallMethod_Ref(static_cast<ani_object>(cpp_arg_details_iter), TH_ANI_FIND_CLASS_METHOD(env, "Lescompat/MapIterator;", "next", nullptr), &cpp_arg_details_next);
        env->Object_GetField_Boolean(static_cast<ani_object>(cpp_arg_details_next), TH_ANI_FIND_CLASS_FIELD(env, "Lescompat/IteratorResult;", "done"), &cpp_arg_details_done);
        if (cpp_arg_details_done) {;
            break;
        };
        ani_ref cpp_arg_details_item;
        env->Object_GetField_Ref(static_cast<ani_object>(cpp_arg_details_next),  TH_ANI_FIND_CLASS_FIELD(env, "Lescompat/IteratorResult;", "value"), &cpp_arg_details_item);
        ani_ref cpp_arg_details_ani_key;
        env->TupleValue_GetItem_Ref(static_cast<ani_tuple_value>(cpp_arg_details_item), 0, &cpp_arg_details_ani_key);
        ani_ref cpp_arg_details_ani_val;
        env->TupleValue_GetItem_Ref(static_cast<ani_tuple_value>(cpp_arg_details_item), 1, &cpp_arg_details_ani_val);
        ani_size cpp_arg_details_cpp_key_len;
        env->String_GetUTF8Size(static_cast<ani_string>(cpp_arg_details_ani_key), &cpp_arg_details_cpp_key_len);
        TString cpp_arg_details_cpp_key_tstr;
        char* cpp_arg_details_cpp_key_buf = tstr_initialize(&cpp_arg_details_cpp_key_tstr, cpp_arg_details_cpp_key_len + 1);
        env->String_GetUTF8(static_cast<ani_string>(cpp_arg_details_ani_key), cpp_arg_details_cpp_key_buf, cpp_arg_details_cpp_key_len + 1, &cpp_arg_details_cpp_key_len);
        cpp_arg_details_cpp_key_buf[cpp_arg_details_cpp_key_len] = '\0';
        cpp_arg_details_cpp_key_tstr.length = cpp_arg_details_cpp_key_len;
        ::taihe::string cpp_arg_details_cpp_key = ::taihe::string(cpp_arg_details_cpp_key_tstr);
        ::ohos::data::unifiedDataChannel::DetailsValue cpp_arg_details_cpp_val = ohos_data_unifiedDataChannel_DetailsValue_fromANI(env, static_cast<ani_ref>(cpp_arg_details_ani_val));
        cpp_arg_details.emplace(cpp_arg_details_cpp_key, cpp_arg_details_cpp_val);
    }
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItemInner(cpp_iface)->SetDetails(cpp_arg_details);
}
static ani_string ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_GetAppId_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedAppItemInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedAppItemInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItemInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItemInner({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::string cpp_result = ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItemInner(cpp_iface)->GetAppId();
    if (::taihe::has_error()) { return ani_string{}; }
    ani_string ani_result;
    env->String_NewUTF8(cpp_result.c_str(), cpp_result.size(), &ani_result);
    return ani_result;
}
static void ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_SetAppId_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object, ani_string ani_arg_appId) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedAppItemInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedAppItemInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItemInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItemInner({cpp_vtbl_ptr, cpp_data_ptr});
    ani_size cpp_arg_appId_len;
    env->String_GetUTF8Size(ani_arg_appId, &cpp_arg_appId_len);
    TString cpp_arg_appId_tstr;
    char* cpp_arg_appId_buf = tstr_initialize(&cpp_arg_appId_tstr, cpp_arg_appId_len + 1);
    env->String_GetUTF8(ani_arg_appId, cpp_arg_appId_buf, cpp_arg_appId_len + 1, &cpp_arg_appId_len);
    cpp_arg_appId_buf[cpp_arg_appId_len] = '\0';
    cpp_arg_appId_tstr.length = cpp_arg_appId_len;
    ::taihe::string cpp_arg_appId = ::taihe::string(cpp_arg_appId_tstr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItemInner(cpp_iface)->SetAppId(cpp_arg_appId);
}
static ani_string ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_GetAppName_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedAppItemInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedAppItemInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItemInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItemInner({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::string cpp_result = ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItemInner(cpp_iface)->GetAppName();
    if (::taihe::has_error()) { return ani_string{}; }
    ani_string ani_result;
    env->String_NewUTF8(cpp_result.c_str(), cpp_result.size(), &ani_result);
    return ani_result;
}
static void ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_SetAppName_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object, ani_string ani_arg_appName) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedAppItemInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedAppItemInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItemInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItemInner({cpp_vtbl_ptr, cpp_data_ptr});
    ani_size cpp_arg_appName_len;
    env->String_GetUTF8Size(ani_arg_appName, &cpp_arg_appName_len);
    TString cpp_arg_appName_tstr;
    char* cpp_arg_appName_buf = tstr_initialize(&cpp_arg_appName_tstr, cpp_arg_appName_len + 1);
    env->String_GetUTF8(ani_arg_appName, cpp_arg_appName_buf, cpp_arg_appName_len + 1, &cpp_arg_appName_len);
    cpp_arg_appName_buf[cpp_arg_appName_len] = '\0';
    cpp_arg_appName_tstr.length = cpp_arg_appName_len;
    ::taihe::string cpp_arg_appName = ::taihe::string(cpp_arg_appName_tstr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItemInner(cpp_iface)->SetAppName(cpp_arg_appName);
}
static ani_string ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_GetAppIconId_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedAppItemInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedAppItemInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItemInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItemInner({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::string cpp_result = ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItemInner(cpp_iface)->GetAppIconId();
    if (::taihe::has_error()) { return ani_string{}; }
    ani_string ani_result;
    env->String_NewUTF8(cpp_result.c_str(), cpp_result.size(), &ani_result);
    return ani_result;
}
static void ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_SetAppIconId_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object, ani_string ani_arg_appIconId) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedAppItemInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedAppItemInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItemInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItemInner({cpp_vtbl_ptr, cpp_data_ptr});
    ani_size cpp_arg_appIconId_len;
    env->String_GetUTF8Size(ani_arg_appIconId, &cpp_arg_appIconId_len);
    TString cpp_arg_appIconId_tstr;
    char* cpp_arg_appIconId_buf = tstr_initialize(&cpp_arg_appIconId_tstr, cpp_arg_appIconId_len + 1);
    env->String_GetUTF8(ani_arg_appIconId, cpp_arg_appIconId_buf, cpp_arg_appIconId_len + 1, &cpp_arg_appIconId_len);
    cpp_arg_appIconId_buf[cpp_arg_appIconId_len] = '\0';
    cpp_arg_appIconId_tstr.length = cpp_arg_appIconId_len;
    ::taihe::string cpp_arg_appIconId = ::taihe::string(cpp_arg_appIconId_tstr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItemInner(cpp_iface)->SetAppIconId(cpp_arg_appIconId);
}
static ani_string ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_GetAppLabelId_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedAppItemInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedAppItemInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItemInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItemInner({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::string cpp_result = ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItemInner(cpp_iface)->GetAppLabelId();
    if (::taihe::has_error()) { return ani_string{}; }
    ani_string ani_result;
    env->String_NewUTF8(cpp_result.c_str(), cpp_result.size(), &ani_result);
    return ani_result;
}
static void ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_SetAppLabelId_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object, ani_string ani_arg_appLabelId) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedAppItemInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedAppItemInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItemInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItemInner({cpp_vtbl_ptr, cpp_data_ptr});
    ani_size cpp_arg_appLabelId_len;
    env->String_GetUTF8Size(ani_arg_appLabelId, &cpp_arg_appLabelId_len);
    TString cpp_arg_appLabelId_tstr;
    char* cpp_arg_appLabelId_buf = tstr_initialize(&cpp_arg_appLabelId_tstr, cpp_arg_appLabelId_len + 1);
    env->String_GetUTF8(ani_arg_appLabelId, cpp_arg_appLabelId_buf, cpp_arg_appLabelId_len + 1, &cpp_arg_appLabelId_len);
    cpp_arg_appLabelId_buf[cpp_arg_appLabelId_len] = '\0';
    cpp_arg_appLabelId_tstr.length = cpp_arg_appLabelId_len;
    ::taihe::string cpp_arg_appLabelId = ::taihe::string(cpp_arg_appLabelId_tstr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItemInner(cpp_iface)->SetAppLabelId(cpp_arg_appLabelId);
}
static ani_string ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_GetBundleName_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedAppItemInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedAppItemInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItemInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItemInner({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::string cpp_result = ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItemInner(cpp_iface)->GetBundleName();
    if (::taihe::has_error()) { return ani_string{}; }
    ani_string ani_result;
    env->String_NewUTF8(cpp_result.c_str(), cpp_result.size(), &ani_result);
    return ani_result;
}
static void ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_SetBundleName_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object, ani_string ani_arg_bundleName) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedAppItemInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedAppItemInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItemInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItemInner({cpp_vtbl_ptr, cpp_data_ptr});
    ani_size cpp_arg_bundleName_len;
    env->String_GetUTF8Size(ani_arg_bundleName, &cpp_arg_bundleName_len);
    TString cpp_arg_bundleName_tstr;
    char* cpp_arg_bundleName_buf = tstr_initialize(&cpp_arg_bundleName_tstr, cpp_arg_bundleName_len + 1);
    env->String_GetUTF8(ani_arg_bundleName, cpp_arg_bundleName_buf, cpp_arg_bundleName_len + 1, &cpp_arg_bundleName_len);
    cpp_arg_bundleName_buf[cpp_arg_bundleName_len] = '\0';
    cpp_arg_bundleName_tstr.length = cpp_arg_bundleName_len;
    ::taihe::string cpp_arg_bundleName = ::taihe::string(cpp_arg_bundleName_tstr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItemInner(cpp_iface)->SetBundleName(cpp_arg_bundleName);
}
static ani_string ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_GetAbilityName_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedAppItemInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedAppItemInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItemInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItemInner({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::string cpp_result = ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItemInner(cpp_iface)->GetAbilityName();
    if (::taihe::has_error()) { return ani_string{}; }
    ani_string ani_result;
    env->String_NewUTF8(cpp_result.c_str(), cpp_result.size(), &ani_result);
    return ani_result;
}
static void ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_SetAbilityName_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object, ani_string ani_arg_abilityName) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedAppItemInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedAppItemInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItemInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItemInner({cpp_vtbl_ptr, cpp_data_ptr});
    ani_size cpp_arg_abilityName_len;
    env->String_GetUTF8Size(ani_arg_abilityName, &cpp_arg_abilityName_len);
    TString cpp_arg_abilityName_tstr;
    char* cpp_arg_abilityName_buf = tstr_initialize(&cpp_arg_abilityName_tstr, cpp_arg_abilityName_len + 1);
    env->String_GetUTF8(ani_arg_abilityName, cpp_arg_abilityName_buf, cpp_arg_abilityName_len + 1, &cpp_arg_abilityName_len);
    cpp_arg_abilityName_buf[cpp_arg_abilityName_len] = '\0';
    cpp_arg_abilityName_tstr.length = cpp_arg_abilityName_len;
    ::taihe::string cpp_arg_abilityName = ::taihe::string(cpp_arg_abilityName_tstr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItemInner(cpp_iface)->SetAbilityName(cpp_arg_abilityName);
}
static ani_long ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_GetInner_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedAppItemInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedAppItemInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItemInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItemInner({cpp_vtbl_ptr, cpp_data_ptr});
    int64_t cpp_result = ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItemInner(cpp_iface)->GetInner();
    if (::taihe::has_error()) { return ani_long{}; }
    ani_long ani_result = (int64_t)cpp_result;
    return ani_result;
}
static void ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_static_finalize_ANIFunc4([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_class clazz, ani_long data_ptr) {
    ::taihe::data_holder(reinterpret_cast<DataBlockHead*>(data_ptr));
}
static ani_string ohos_data_unifiedDataChannel_SystemDefinedPixelMapInner_GetType_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedPixelMapInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedPixelMapInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_SystemDefinedPixelMapInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedPixelMapInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedPixelMapInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::SystemDefinedPixelMapInner({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::string cpp_result = ::ohos::data::unifiedDataChannel::weak::SystemDefinedPixelMapInner(cpp_iface)->GetType();
    if (::taihe::has_error()) { return ani_string{}; }
    ani_string ani_result;
    env->String_NewUTF8(cpp_result.c_str(), cpp_result.size(), &ani_result);
    return ani_result;
}
static ani_ref ohos_data_unifiedDataChannel_SystemDefinedPixelMapInner_GetValue_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedPixelMapInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedPixelMapInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_SystemDefinedPixelMapInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedPixelMapInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedPixelMapInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::SystemDefinedPixelMapInner({cpp_vtbl_ptr, cpp_data_ptr});
    ::ohos::data::unifiedDataChannel::ValueType cpp_result = ::ohos::data::unifiedDataChannel::weak::SystemDefinedPixelMapInner(cpp_iface)->GetValue();
    if (::taihe::has_error()) { return ani_ref{}; }
    ani_ref ani_result = ohos_data_unifiedDataChannel_ValueType_intoANI(env, cpp_result);
    return ani_result;
}
static ani_ref ohos_data_unifiedDataChannel_SystemDefinedPixelMapInner_GetDetails_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedPixelMapInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedPixelMapInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_SystemDefinedPixelMapInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedPixelMapInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedPixelMapInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::SystemDefinedPixelMapInner({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::optional<::taihe::map<::taihe::string, ::ohos::data::unifiedDataChannel::DetailsValue>> cpp_result = ::ohos::data::unifiedDataChannel::weak::SystemDefinedPixelMapInner(cpp_iface)->GetDetails();
    if (::taihe::has_error()) { return ani_ref{}; }
    ani_ref ani_result;
    if (!cpp_result) {
        env->GetUndefined(&ani_result);
    }
    else {
        ani_object ani_result_spec;
        env->Object_New(TH_ANI_FIND_CLASS(env, "Lescompat/Record;"), TH_ANI_FIND_CLASS_METHOD(env, "Lescompat/Record;", "<ctor>", nullptr), &ani_result_spec);
        for (const auto& [ani_result_spec_cpp_key, ani_result_spec_cpp_val] : (*cpp_result)) {
            ani_string ani_result_spec_ani_key;
            env->String_NewUTF8(ani_result_spec_cpp_key.c_str(), ani_result_spec_cpp_key.size(), &ani_result_spec_ani_key);
            ani_ref ani_result_spec_ani_val = ohos_data_unifiedDataChannel_DetailsValue_intoANI(env, ani_result_spec_cpp_val);
            env->Object_CallMethod_Void(ani_result_spec, TH_ANI_FIND_CLASS_METHOD(env, "Lescompat/Record;", "$_set", nullptr), ani_result_spec_ani_key, ani_result_spec_ani_val);
        }
        ani_result = ani_result_spec;
    }
    return ani_result;
}
static void ohos_data_unifiedDataChannel_SystemDefinedPixelMapInner_SetDetails_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object, ani_object ani_arg_details) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedPixelMapInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedPixelMapInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_SystemDefinedPixelMapInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedPixelMapInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedPixelMapInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::SystemDefinedPixelMapInner({cpp_vtbl_ptr, cpp_data_ptr});
    ani_ref cpp_arg_details_iter;
    env->Object_CallMethod_Ref(ani_arg_details, TH_ANI_FIND_CLASS_METHOD(env, "Lescompat/Record;", "$_iterator", nullptr), &cpp_arg_details_iter);
    ::taihe::map<::taihe::string, ::ohos::data::unifiedDataChannel::DetailsValue> cpp_arg_details;
    while (true) {
        ani_ref cpp_arg_details_next;
        ani_boolean cpp_arg_details_done;
        env->Object_CallMethod_Ref(static_cast<ani_object>(cpp_arg_details_iter), TH_ANI_FIND_CLASS_METHOD(env, "Lescompat/MapIterator;", "next", nullptr), &cpp_arg_details_next);
        env->Object_GetField_Boolean(static_cast<ani_object>(cpp_arg_details_next), TH_ANI_FIND_CLASS_FIELD(env, "Lescompat/IteratorResult;", "done"), &cpp_arg_details_done);
        if (cpp_arg_details_done) {;
            break;
        };
        ani_ref cpp_arg_details_item;
        env->Object_GetField_Ref(static_cast<ani_object>(cpp_arg_details_next),  TH_ANI_FIND_CLASS_FIELD(env, "Lescompat/IteratorResult;", "value"), &cpp_arg_details_item);
        ani_ref cpp_arg_details_ani_key;
        env->TupleValue_GetItem_Ref(static_cast<ani_tuple_value>(cpp_arg_details_item), 0, &cpp_arg_details_ani_key);
        ani_ref cpp_arg_details_ani_val;
        env->TupleValue_GetItem_Ref(static_cast<ani_tuple_value>(cpp_arg_details_item), 1, &cpp_arg_details_ani_val);
        ani_size cpp_arg_details_cpp_key_len;
        env->String_GetUTF8Size(static_cast<ani_string>(cpp_arg_details_ani_key), &cpp_arg_details_cpp_key_len);
        TString cpp_arg_details_cpp_key_tstr;
        char* cpp_arg_details_cpp_key_buf = tstr_initialize(&cpp_arg_details_cpp_key_tstr, cpp_arg_details_cpp_key_len + 1);
        env->String_GetUTF8(static_cast<ani_string>(cpp_arg_details_ani_key), cpp_arg_details_cpp_key_buf, cpp_arg_details_cpp_key_len + 1, &cpp_arg_details_cpp_key_len);
        cpp_arg_details_cpp_key_buf[cpp_arg_details_cpp_key_len] = '\0';
        cpp_arg_details_cpp_key_tstr.length = cpp_arg_details_cpp_key_len;
        ::taihe::string cpp_arg_details_cpp_key = ::taihe::string(cpp_arg_details_cpp_key_tstr);
        ::ohos::data::unifiedDataChannel::DetailsValue cpp_arg_details_cpp_val = ohos_data_unifiedDataChannel_DetailsValue_fromANI(env, static_cast<ani_ref>(cpp_arg_details_ani_val));
        cpp_arg_details.emplace(cpp_arg_details_cpp_key, cpp_arg_details_cpp_val);
    }
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedPixelMapInner(cpp_iface)->SetDetails(cpp_arg_details);
}
static ani_ref ohos_data_unifiedDataChannel_SystemDefinedPixelMapInner_GetRawData_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedPixelMapInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedPixelMapInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_SystemDefinedPixelMapInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedPixelMapInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedPixelMapInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::SystemDefinedPixelMapInner({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::optional<::taihe::array<uint8_t>> cpp_result = ::ohos::data::unifiedDataChannel::weak::SystemDefinedPixelMapInner(cpp_iface)->GetRawData();
    if (::taihe::has_error()) { return ani_ref{}; }
    ani_ref ani_result;
    if (!cpp_result) {
        env->GetUndefined(&ani_result);
    }
    else {
        char* ani_result_spec_data = nullptr;
        ani_arraybuffer ani_result_spec_arrbuf;
        env->CreateArrayBuffer((*cpp_result).size() * (sizeof(uint8_t) / sizeof(char)), reinterpret_cast<void**>(&ani_result_spec_data), &ani_result_spec_arrbuf);
        memcpy(ani_result_spec_data, (*cpp_result).data(), (*cpp_result).size() * (sizeof(uint8_t) / sizeof(char)));
        ani_ref ani_result_spec_bylen;
        env->GetUndefined(&ani_result_spec_bylen);
        ani_ref ani_result_spec_byoff;
        env->GetUndefined(&ani_result_spec_byoff);
        ani_object ani_result_spec;
        env->Object_New(TH_ANI_FIND_CLASS(env, "Lescompat/Uint8Array;"), TH_ANI_FIND_CLASS_METHOD(env, "Lescompat/Uint8Array;", "<ctor>", "Lescompat/Buffer;Lstd/core/Double;Lstd/core/Double;:V"), &ani_result_spec, ani_result_spec_arrbuf, ani_result_spec_bylen, ani_result_spec_byoff);
        ani_result = ani_result_spec;
    }
    return ani_result;
}
static void ohos_data_unifiedDataChannel_SystemDefinedPixelMapInner_SetRawData_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object, ani_object ani_arg_rawData) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedPixelMapInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedPixelMapInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_SystemDefinedPixelMapInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedPixelMapInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedPixelMapInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::SystemDefinedPixelMapInner({cpp_vtbl_ptr, cpp_data_ptr});
    ani_double cpp_arg_rawData_bylen;
    ani_double cpp_arg_rawData_byoff;
    ani_arraybuffer cpp_arg_rawData_arrbuf;
    env->Object_GetPropertyByName_Double(ani_arg_rawData, "byteLength", &cpp_arg_rawData_bylen);
    env->Object_GetPropertyByName_Double(ani_arg_rawData, "byteOffset", &cpp_arg_rawData_byoff);
    env->Object_GetPropertyByName_Ref(ani_arg_rawData, "buffer", reinterpret_cast<ani_ref*>(&cpp_arg_rawData_arrbuf));
    char* cpp_arg_rawData_data = nullptr;
    size_t cpp_arg_rawData_length = 0;
    env->ArrayBuffer_GetInfo(cpp_arg_rawData_arrbuf, reinterpret_cast<void**>(&cpp_arg_rawData_data), &cpp_arg_rawData_length);
    ::taihe::array_view<uint8_t> cpp_arg_rawData(reinterpret_cast<uint8_t*>(cpp_arg_rawData_data + (size_t)cpp_arg_rawData_byoff), (size_t)cpp_arg_rawData_bylen / (sizeof(uint8_t) / sizeof(char)));
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedPixelMapInner(cpp_iface)->SetRawData(cpp_arg_rawData);
}
static ani_long ohos_data_unifiedDataChannel_SystemDefinedPixelMapInner_GetInner_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedPixelMapInner;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedPixelMapInner;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_SystemDefinedPixelMapInner_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedPixelMapInner_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedPixelMapInner cpp_iface = ::ohos::data::unifiedDataChannel::weak::SystemDefinedPixelMapInner({cpp_vtbl_ptr, cpp_data_ptr});
    int64_t cpp_result = ::ohos::data::unifiedDataChannel::weak::SystemDefinedPixelMapInner(cpp_iface)->GetInner();
    if (::taihe::has_error()) { return ani_long{}; }
    ani_long ani_result = (int64_t)cpp_result;
    return ani_result;
}
static void ohos_data_unifiedDataChannel_SystemDefinedPixelMapInner_static_finalize_ANIFunc4([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_class clazz, ani_long data_ptr) {
    ::taihe::data_holder(reinterpret_cast<DataBlockHead*>(data_ptr));
}
namespace ohos::data::unifiedDataChannel {
ani_status ANIRegister(ani_env *env) {
    if (::taihe::get_vm() == nullptr) {
        ani_vm *vm;
        if (ANI_OK != env->GetVM(&vm)) {
            return ANI_ERROR;
        }
        ::taihe::set_vm(vm);
    }
    {
        ani_namespace ani_env;
        if (ANI_OK != env->FindNamespace("L@ohos/data/unifiedDataChannel/unifiedDataChannel;", &ani_env)) {
            return ANI_ERROR;
        }
        ani_native_function methods[] = {
            {"CreateSummary_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_CreateSummary_ANIFunc)},
            {"CreateUnifiedData_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_CreateUnifiedData_ANIFunc)},
            {"CreateUnifiedDataWithParams_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_CreateUnifiedDataWithParams_ANIFunc)},
            {"CreateUnifiedRecord_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_CreateUnifiedRecord_ANIFunc)},
            {"CreateUnifiedRecordWithParams_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_CreateUnifiedRecordWithParams_ANIFunc)},
            {"CreateUnifiedFile_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_CreateUnifiedFile_ANIFunc)},
            {"CreateUnifiedFolder_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_CreateUnifiedFolder_ANIFunc)},
            {"CreateUnifiedAudio_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_CreateUnifiedAudio_ANIFunc)},
            {"CreateUnifiedVideo_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_CreateUnifiedVideo_ANIFunc)},
            {"CreateUnifiedImage_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_CreateUnifiedImage_ANIFunc)},
            {"CreateText_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_CreateText_ANIFunc)},
            {"CreateHtml_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_CreateHtml_ANIFunc)},
            {"CreateHyperlink_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_CreateHyperlink_ANIFunc)},
            {"CreatePlainText_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_CreatePlainText_ANIFunc)},
            {"CreateSystemDefinedRecord_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_CreateSystemDefinedRecord_ANIFunc)},
            {"CreateSystemDefinedForm_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_CreateSystemDefinedForm_ANIFunc)},
            {"CreateSystemDefinedAppItem_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_CreateSystemDefinedAppItem_ANIFunc)},
            {"CreateSystemDefinedPixelMap_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_CreateSystemDefinedPixelMap_ANIFunc)},
            {"InsertDataSync_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_InsertDataSync_ANIFunc)},
            {"QueryDataSync_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_QueryDataSync_ANIFunc)},
        };
        if (ANI_OK != env->Namespace_BindNativeFunctions(ani_env, methods, sizeof(methods) / sizeof(ani_native_function))) {
            return ANI_ERROR;
        }
    }
    {
        ani_class ani_env;
        if (ANI_OK != env->FindClass("L@ohos/data/unifiedDataChannel/unifiedDataChannel/UnifiedDataInner;", &ani_env)) {
            return ANI_ERROR;
        }
        ani_native_function methods[] = {
            {"AddRecord_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_UnifiedDataInner_AddRecord_ANIFunc)},
            {"GetRecords_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_UnifiedDataInner_GetRecords_ANIFunc)},
            {"GetInner_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_UnifiedDataInner_GetInner_ANIFunc)},
            {"_finalize", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_UnifiedDataInner_static_finalize_ANIFunc4)},
        };
        if (ANI_OK != env->Class_BindNativeMethods(ani_env, methods, sizeof(methods) / sizeof(ani_native_function))) {
            return ANI_ERROR;
        }
    }
    {
        ani_class ani_env;
        if (ANI_OK != env->FindClass("L@ohos/data/unifiedDataChannel/unifiedDataChannel/UnifiedRecordInner;", &ani_env)) {
            return ANI_ERROR;
        }
        ani_native_function methods[] = {
            {"GetType_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_UnifiedRecordInner_GetType_ANIFunc)},
            {"GetValue_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_UnifiedRecordInner_GetValue_ANIFunc)},
            {"GetInner_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_UnifiedRecordInner_GetInner_ANIFunc)},
            {"_finalize", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_UnifiedRecordInner_static_finalize_ANIFunc4)},
        };
        if (ANI_OK != env->Class_BindNativeMethods(ani_env, methods, sizeof(methods) / sizeof(ani_native_function))) {
            return ANI_ERROR;
        }
    }
    {
        ani_class ani_env;
        if (ANI_OK != env->FindClass("L@ohos/data/unifiedDataChannel/unifiedDataChannel/FileInner;", &ani_env)) {
            return ANI_ERROR;
        }
        ani_native_function methods[] = {
            {"GetType_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_FileInner_GetType_ANIFunc)},
            {"GetValue_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_FileInner_GetValue_ANIFunc)},
            {"GetUri_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_FileInner_GetUri_ANIFunc)},
            {"SetUri_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_FileInner_SetUri_ANIFunc)},
            {"GetDetails_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_FileInner_GetDetails_ANIFunc)},
            {"SetDetails_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_FileInner_SetDetails_ANIFunc)},
            {"GetInner_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_FileInner_GetInner_ANIFunc)},
            {"_finalize", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_FileInner_static_finalize_ANIFunc4)},
        };
        if (ANI_OK != env->Class_BindNativeMethods(ani_env, methods, sizeof(methods) / sizeof(ani_native_function))) {
            return ANI_ERROR;
        }
    }
    {
        ani_class ani_env;
        if (ANI_OK != env->FindClass("L@ohos/data/unifiedDataChannel/unifiedDataChannel/FolderInner;", &ani_env)) {
            return ANI_ERROR;
        }
        ani_native_function methods[] = {
            {"GetType_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_FolderInner_GetType_ANIFunc)},
            {"GetValue_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_FolderInner_GetValue_ANIFunc)},
            {"GetUri_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_FolderInner_GetUri_ANIFunc)},
            {"SetUri_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_FolderInner_SetUri_ANIFunc)},
            {"GetDetails_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_FolderInner_GetDetails_ANIFunc)},
            {"SetDetails_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_FolderInner_SetDetails_ANIFunc)},
            {"GetFolderUri_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_FolderInner_GetFolderUri_ANIFunc)},
            {"SetFolderUri_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_FolderInner_SetFolderUri_ANIFunc)},
            {"GetInner_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_FolderInner_GetInner_ANIFunc)},
            {"_finalize", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_FolderInner_static_finalize_ANIFunc4)},
        };
        if (ANI_OK != env->Class_BindNativeMethods(ani_env, methods, sizeof(methods) / sizeof(ani_native_function))) {
            return ANI_ERROR;
        }
    }
    {
        ani_class ani_env;
        if (ANI_OK != env->FindClass("L@ohos/data/unifiedDataChannel/unifiedDataChannel/AudioInner;", &ani_env)) {
            return ANI_ERROR;
        }
        ani_native_function methods[] = {
            {"GetType_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_AudioInner_GetType_ANIFunc)},
            {"GetValue_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_AudioInner_GetValue_ANIFunc)},
            {"GetUri_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_AudioInner_GetUri_ANIFunc)},
            {"SetUri_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_AudioInner_SetUri_ANIFunc)},
            {"GetDetails_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_AudioInner_GetDetails_ANIFunc)},
            {"SetDetails_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_AudioInner_SetDetails_ANIFunc)},
            {"GetAudioUri_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_AudioInner_GetAudioUri_ANIFunc)},
            {"SetAudioUri_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_AudioInner_SetAudioUri_ANIFunc)},
            {"GetInner_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_AudioInner_GetInner_ANIFunc)},
            {"_finalize", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_AudioInner_static_finalize_ANIFunc4)},
        };
        if (ANI_OK != env->Class_BindNativeMethods(ani_env, methods, sizeof(methods) / sizeof(ani_native_function))) {
            return ANI_ERROR;
        }
    }
    {
        ani_class ani_env;
        if (ANI_OK != env->FindClass("L@ohos/data/unifiedDataChannel/unifiedDataChannel/VideoInner;", &ani_env)) {
            return ANI_ERROR;
        }
        ani_native_function methods[] = {
            {"GetType_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_VideoInner_GetType_ANIFunc)},
            {"GetValue_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_VideoInner_GetValue_ANIFunc)},
            {"GetUri_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_VideoInner_GetUri_ANIFunc)},
            {"SetUri_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_VideoInner_SetUri_ANIFunc)},
            {"GetDetails_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_VideoInner_GetDetails_ANIFunc)},
            {"SetDetails_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_VideoInner_SetDetails_ANIFunc)},
            {"GetVideoUri_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_VideoInner_GetVideoUri_ANIFunc)},
            {"SetVideoUri_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_VideoInner_SetVideoUri_ANIFunc)},
            {"GetInner_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_VideoInner_GetInner_ANIFunc)},
            {"_finalize", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_VideoInner_static_finalize_ANIFunc4)},
        };
        if (ANI_OK != env->Class_BindNativeMethods(ani_env, methods, sizeof(methods) / sizeof(ani_native_function))) {
            return ANI_ERROR;
        }
    }
    {
        ani_class ani_env;
        if (ANI_OK != env->FindClass("L@ohos/data/unifiedDataChannel/unifiedDataChannel/ImageInner;", &ani_env)) {
            return ANI_ERROR;
        }
        ani_native_function methods[] = {
            {"GetType_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_ImageInner_GetType_ANIFunc)},
            {"GetValue_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_ImageInner_GetValue_ANIFunc)},
            {"GetUri_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_ImageInner_GetUri_ANIFunc)},
            {"SetUri_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_ImageInner_SetUri_ANIFunc)},
            {"GetDetails_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_ImageInner_GetDetails_ANIFunc)},
            {"SetDetails_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_ImageInner_SetDetails_ANIFunc)},
            {"GetImageUri_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_ImageInner_GetImageUri_ANIFunc)},
            {"SetImageUri_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_ImageInner_SetImageUri_ANIFunc)},
            {"GetInner_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_ImageInner_GetInner_ANIFunc)},
            {"_finalize", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_ImageInner_static_finalize_ANIFunc4)},
        };
        if (ANI_OK != env->Class_BindNativeMethods(ani_env, methods, sizeof(methods) / sizeof(ani_native_function))) {
            return ANI_ERROR;
        }
    }
    {
        ani_class ani_env;
        if (ANI_OK != env->FindClass("L@ohos/data/unifiedDataChannel/unifiedDataChannel/TextInner;", &ani_env)) {
            return ANI_ERROR;
        }
        ani_native_function methods[] = {
            {"GetType_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_TextInner_GetType_ANIFunc)},
            {"GetValue_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_TextInner_GetValue_ANIFunc)},
            {"GetDetails_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_TextInner_GetDetails_ANIFunc)},
            {"SetDetails_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_TextInner_SetDetails_ANIFunc)},
            {"GetInner_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_TextInner_GetInner_ANIFunc)},
            {"_finalize", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_TextInner_static_finalize_ANIFunc4)},
        };
        if (ANI_OK != env->Class_BindNativeMethods(ani_env, methods, sizeof(methods) / sizeof(ani_native_function))) {
            return ANI_ERROR;
        }
    }
    {
        ani_class ani_env;
        if (ANI_OK != env->FindClass("L@ohos/data/unifiedDataChannel/unifiedDataChannel/HTMLInner;", &ani_env)) {
            return ANI_ERROR;
        }
        ani_native_function methods[] = {
            {"GetType_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_HTMLInner_GetType_ANIFunc)},
            {"GetValue_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_HTMLInner_GetValue_ANIFunc)},
            {"GetDetails_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_HTMLInner_GetDetails_ANIFunc)},
            {"SetDetails_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_HTMLInner_SetDetails_ANIFunc)},
            {"SetHtmlContent_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_HTMLInner_SetHtmlContent_ANIFunc)},
            {"GetHtmlContent_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_HTMLInner_GetHtmlContent_ANIFunc)},
            {"SetPlainContent_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_HTMLInner_SetPlainContent_ANIFunc)},
            {"GetPlainContent_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_HTMLInner_GetPlainContent_ANIFunc)},
            {"GetInner_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_HTMLInner_GetInner_ANIFunc)},
            {"_finalize", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_HTMLInner_static_finalize_ANIFunc4)},
        };
        if (ANI_OK != env->Class_BindNativeMethods(ani_env, methods, sizeof(methods) / sizeof(ani_native_function))) {
            return ANI_ERROR;
        }
    }
    {
        ani_class ani_env;
        if (ANI_OK != env->FindClass("L@ohos/data/unifiedDataChannel/unifiedDataChannel/HyperlinkInner;", &ani_env)) {
            return ANI_ERROR;
        }
        ani_native_function methods[] = {
            {"GetType_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_HyperlinkInner_GetType_ANIFunc)},
            {"GetValue_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_HyperlinkInner_GetValue_ANIFunc)},
            {"GetDetails_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_HyperlinkInner_GetDetails_ANIFunc)},
            {"SetDetails_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_HyperlinkInner_SetDetails_ANIFunc)},
            {"SetUrl_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_HyperlinkInner_SetUrl_ANIFunc)},
            {"GetUrl_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_HyperlinkInner_GetUrl_ANIFunc)},
            {"SetDescription_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_HyperlinkInner_SetDescription_ANIFunc)},
            {"GetDescription_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_HyperlinkInner_GetDescription_ANIFunc)},
            {"GetInner_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_HyperlinkInner_GetInner_ANIFunc)},
            {"_finalize", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_HyperlinkInner_static_finalize_ANIFunc4)},
        };
        if (ANI_OK != env->Class_BindNativeMethods(ani_env, methods, sizeof(methods) / sizeof(ani_native_function))) {
            return ANI_ERROR;
        }
    }
    {
        ani_class ani_env;
        if (ANI_OK != env->FindClass("L@ohos/data/unifiedDataChannel/unifiedDataChannel/PlainTextInner;", &ani_env)) {
            return ANI_ERROR;
        }
        ani_native_function methods[] = {
            {"GetType_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_PlainTextInner_GetType_ANIFunc)},
            {"GetValue_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_PlainTextInner_GetValue_ANIFunc)},
            {"GetDetails_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_PlainTextInner_GetDetails_ANIFunc)},
            {"SetDetails_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_PlainTextInner_SetDetails_ANIFunc)},
            {"SetTextContent_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_PlainTextInner_SetTextContent_ANIFunc)},
            {"GetTextContent_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_PlainTextInner_GetTextContent_ANIFunc)},
            {"GetInner_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_PlainTextInner_GetInner_ANIFunc)},
            {"_finalize", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_PlainTextInner_static_finalize_ANIFunc4)},
        };
        if (ANI_OK != env->Class_BindNativeMethods(ani_env, methods, sizeof(methods) / sizeof(ani_native_function))) {
            return ANI_ERROR;
        }
    }
    {
        ani_class ani_env;
        if (ANI_OK != env->FindClass("L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedRecordInner;", &ani_env)) {
            return ANI_ERROR;
        }
        ani_native_function methods[] = {
            {"GetType_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_SystemDefinedRecordInner_GetType_ANIFunc)},
            {"GetValue_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_SystemDefinedRecordInner_GetValue_ANIFunc)},
            {"GetDetails_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_SystemDefinedRecordInner_GetDetails_ANIFunc)},
            {"SetDetails_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_SystemDefinedRecordInner_SetDetails_ANIFunc)},
            {"GetInner_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_SystemDefinedRecordInner_GetInner_ANIFunc)},
            {"_finalize", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_SystemDefinedRecordInner_static_finalize_ANIFunc4)},
        };
        if (ANI_OK != env->Class_BindNativeMethods(ani_env, methods, sizeof(methods) / sizeof(ani_native_function))) {
            return ANI_ERROR;
        }
    }
    {
        ani_class ani_env;
        if (ANI_OK != env->FindClass("L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedFormInner;", &ani_env)) {
            return ANI_ERROR;
        }
        ani_native_function methods[] = {
            {"GetType_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_SystemDefinedFormInner_GetType_ANIFunc)},
            {"GetValue_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_SystemDefinedFormInner_GetValue_ANIFunc)},
            {"GetDetails_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_SystemDefinedFormInner_GetDetails_ANIFunc)},
            {"SetDetails_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_SystemDefinedFormInner_SetDetails_ANIFunc)},
            {"GetFormId_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_SystemDefinedFormInner_GetFormId_ANIFunc)},
            {"SetFormId_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_SystemDefinedFormInner_SetFormId_ANIFunc)},
            {"GetFormName_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_SystemDefinedFormInner_GetFormName_ANIFunc)},
            {"SetFormName_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_SystemDefinedFormInner_SetFormName_ANIFunc)},
            {"GetBundleName_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_SystemDefinedFormInner_GetBundleName_ANIFunc)},
            {"SetBundleName_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_SystemDefinedFormInner_SetBundleName_ANIFunc)},
            {"GetAbilityName_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_SystemDefinedFormInner_GetAbilityName_ANIFunc)},
            {"SetAbilityName_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_SystemDefinedFormInner_SetAbilityName_ANIFunc)},
            {"GetModule_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_SystemDefinedFormInner_GetModule_ANIFunc)},
            {"SetModule_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_SystemDefinedFormInner_SetModule_ANIFunc)},
            {"GetInner_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_SystemDefinedFormInner_GetInner_ANIFunc)},
            {"_finalize", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_SystemDefinedFormInner_static_finalize_ANIFunc4)},
        };
        if (ANI_OK != env->Class_BindNativeMethods(ani_env, methods, sizeof(methods) / sizeof(ani_native_function))) {
            return ANI_ERROR;
        }
    }
    {
        ani_class ani_env;
        if (ANI_OK != env->FindClass("L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedAppItemInner;", &ani_env)) {
            return ANI_ERROR;
        }
        ani_native_function methods[] = {
            {"GetType_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_GetType_ANIFunc)},
            {"GetValue_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_GetValue_ANIFunc)},
            {"GetDetails_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_GetDetails_ANIFunc)},
            {"SetDetails_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_SetDetails_ANIFunc)},
            {"GetAppId_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_GetAppId_ANIFunc)},
            {"SetAppId_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_SetAppId_ANIFunc)},
            {"GetAppName_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_GetAppName_ANIFunc)},
            {"SetAppName_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_SetAppName_ANIFunc)},
            {"GetAppIconId_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_GetAppIconId_ANIFunc)},
            {"SetAppIconId_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_SetAppIconId_ANIFunc)},
            {"GetAppLabelId_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_GetAppLabelId_ANIFunc)},
            {"SetAppLabelId_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_SetAppLabelId_ANIFunc)},
            {"GetBundleName_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_GetBundleName_ANIFunc)},
            {"SetBundleName_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_SetBundleName_ANIFunc)},
            {"GetAbilityName_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_GetAbilityName_ANIFunc)},
            {"SetAbilityName_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_SetAbilityName_ANIFunc)},
            {"GetInner_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_GetInner_ANIFunc)},
            {"_finalize", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_static_finalize_ANIFunc4)},
        };
        if (ANI_OK != env->Class_BindNativeMethods(ani_env, methods, sizeof(methods) / sizeof(ani_native_function))) {
            return ANI_ERROR;
        }
    }
    {
        ani_class ani_env;
        if (ANI_OK != env->FindClass("L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedPixelMapInner;", &ani_env)) {
            return ANI_ERROR;
        }
        ani_native_function methods[] = {
            {"GetType_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_SystemDefinedPixelMapInner_GetType_ANIFunc)},
            {"GetValue_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_SystemDefinedPixelMapInner_GetValue_ANIFunc)},
            {"GetDetails_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_SystemDefinedPixelMapInner_GetDetails_ANIFunc)},
            {"SetDetails_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_SystemDefinedPixelMapInner_SetDetails_ANIFunc)},
            {"GetRawData_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_SystemDefinedPixelMapInner_GetRawData_ANIFunc)},
            {"SetRawData_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_SystemDefinedPixelMapInner_SetRawData_ANIFunc)},
            {"GetInner_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_SystemDefinedPixelMapInner_GetInner_ANIFunc)},
            {"_finalize", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_SystemDefinedPixelMapInner_static_finalize_ANIFunc4)},
        };
        if (ANI_OK != env->Class_BindNativeMethods(ani_env, methods, sizeof(methods) / sizeof(ani_native_function))) {
            return ANI_ERROR;
        }
    }
    return ANI_OK;
}
}
