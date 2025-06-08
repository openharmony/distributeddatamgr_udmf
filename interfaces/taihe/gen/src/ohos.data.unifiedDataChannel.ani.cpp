#include "ohos.data.unifiedDataChannel.ani.hpp"
#include "ohos.data.unifiedDataChannel.user.hpp"
#include "ohos.data.unifiedDataChannel.Summary.ani.1.h"
#include "ohos.data.unifiedDataChannel.UnifiedData.ani.1.h"
#include "ohos.data.unifiedDataChannel.UnifiedRecord.ani.1.h"
#include "ohos.data.unifiedDataChannel.ValueType.ani.1.h"
#include "ohos.data.unifiedDataChannel.File.ani.1.h"
#include "ohos.data.unifiedDataChannel.Folder.ani.1.h"
#include "ohos.data.unifiedDataChannel.Audio.ani.1.h"
#include "ohos.data.unifiedDataChannel.Video.ani.1.h"
#include "ohos.data.unifiedDataChannel.Image.ani.1.h"
#include "ohos.data.unifiedDataChannel.Text.ani.1.h"
#include "ohos.data.unifiedDataChannel.HTML.ani.1.h"
#include "ohos.data.unifiedDataChannel.Hyperlink.ani.1.h"
#include "ohos.data.unifiedDataChannel.PlainText.ani.1.h"
#include "ohos.data.unifiedDataChannel.SystemDefinedRecord.ani.1.h"
#include "ohos.data.unifiedDataChannel.SystemDefinedForm.ani.1.h"
#include "ohos.data.unifiedDataChannel.SystemDefinedAppItem.ani.1.h"
#include "ohos.data.unifiedDataChannel.SystemDefinedPixelMap.ani.1.h"
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
    ::ohos::data::unifiedDataChannel::UnifiedData cpp_result = ::ohos::data::unifiedDataChannel::CreateUnifiedData();
    if (::taihe::has_error()) { return ani_object{}; }
    ani_object ani_result = ohos_data_unifiedDataChannel_UnifiedData_intoANI(env, cpp_result);
    return ani_result;
}
static ani_object ohos_data_unifiedDataChannel_CreateUnifiedDataWithParams_ANIFunc([[maybe_unused]] ani_env *env, ani_object ani_arg_unifiedRecord) {
    ::ohos::data::unifiedDataChannel::UnifiedRecord cpp_arg_unifiedRecord = ohos_data_unifiedDataChannel_UnifiedRecord_fromANI(env, ani_arg_unifiedRecord);
    ::ohos::data::unifiedDataChannel::UnifiedData cpp_result = ::ohos::data::unifiedDataChannel::CreateUnifiedDataWithParams(cpp_arg_unifiedRecord);
    if (::taihe::has_error()) { return ani_object{}; }
    ani_object ani_result = ohos_data_unifiedDataChannel_UnifiedData_intoANI(env, cpp_result);
    return ani_result;
}
static ani_object ohos_data_unifiedDataChannel_CreateUnifiedRecord_ANIFunc([[maybe_unused]] ani_env *env) {
    ::ohos::data::unifiedDataChannel::UnifiedRecord cpp_result = ::ohos::data::unifiedDataChannel::CreateUnifiedRecord();
    if (::taihe::has_error()) { return ani_object{}; }
    ani_object ani_result = ohos_data_unifiedDataChannel_UnifiedRecord_intoANI(env, cpp_result);
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
    ::ohos::data::unifiedDataChannel::UnifiedRecord cpp_result = ::ohos::data::unifiedDataChannel::CreateUnifiedRecordWithParams(cpp_arg_type, cpp_arg_value);
    if (::taihe::has_error()) { return ani_object{}; }
    ani_object ani_result = ohos_data_unifiedDataChannel_UnifiedRecord_intoANI(env, cpp_result);
    return ani_result;
}
static ani_object ohos_data_unifiedDataChannel_CreateUnifiedFile_ANIFunc([[maybe_unused]] ani_env *env) {
    ::ohos::data::unifiedDataChannel::File cpp_result = ::ohos::data::unifiedDataChannel::CreateUnifiedFile();
    if (::taihe::has_error()) { return ani_object{}; }
    ani_object ani_result = ohos_data_unifiedDataChannel_File_intoANI(env, cpp_result);
    return ani_result;
}
static ani_object ohos_data_unifiedDataChannel_CreateFolder_ANIFunc([[maybe_unused]] ani_env *env) {
    ::ohos::data::unifiedDataChannel::Folder cpp_result = ::ohos::data::unifiedDataChannel::CreateFolder();
    if (::taihe::has_error()) { return ani_object{}; }
    ani_object ani_result = ohos_data_unifiedDataChannel_Folder_intoANI(env, cpp_result);
    return ani_result;
}
static ani_object ohos_data_unifiedDataChannel_CreateAudio_ANIFunc([[maybe_unused]] ani_env *env) {
    ::ohos::data::unifiedDataChannel::Audio cpp_result = ::ohos::data::unifiedDataChannel::CreateAudio();
    if (::taihe::has_error()) { return ani_object{}; }
    ani_object ani_result = ohos_data_unifiedDataChannel_Audio_intoANI(env, cpp_result);
    return ani_result;
}
static ani_object ohos_data_unifiedDataChannel_CreateVideo_ANIFunc([[maybe_unused]] ani_env *env) {
    ::ohos::data::unifiedDataChannel::Video cpp_result = ::ohos::data::unifiedDataChannel::CreateVideo();
    if (::taihe::has_error()) { return ani_object{}; }
    ani_object ani_result = ohos_data_unifiedDataChannel_Video_intoANI(env, cpp_result);
    return ani_result;
}
static ani_object ohos_data_unifiedDataChannel_CreateImage_ANIFunc([[maybe_unused]] ani_env *env) {
    ::ohos::data::unifiedDataChannel::Image cpp_result = ::ohos::data::unifiedDataChannel::CreateImage();
    if (::taihe::has_error()) { return ani_object{}; }
    ani_object ani_result = ohos_data_unifiedDataChannel_Image_intoANI(env, cpp_result);
    return ani_result;
}
static ani_object ohos_data_unifiedDataChannel_CreateText_ANIFunc([[maybe_unused]] ani_env *env) {
    ::ohos::data::unifiedDataChannel::Text cpp_result = ::ohos::data::unifiedDataChannel::CreateText();
    if (::taihe::has_error()) { return ani_object{}; }
    ani_object ani_result = ohos_data_unifiedDataChannel_Text_intoANI(env, cpp_result);
    return ani_result;
}
static ani_object ohos_data_unifiedDataChannel_CreateHtml_ANIFunc([[maybe_unused]] ani_env *env) {
    ::ohos::data::unifiedDataChannel::HTML cpp_result = ::ohos::data::unifiedDataChannel::CreateHtml();
    if (::taihe::has_error()) { return ani_object{}; }
    ani_object ani_result = ohos_data_unifiedDataChannel_HTML_intoANI(env, cpp_result);
    return ani_result;
}
static ani_object ohos_data_unifiedDataChannel_CreateHyperlink_ANIFunc([[maybe_unused]] ani_env *env) {
    ::ohos::data::unifiedDataChannel::Hyperlink cpp_result = ::ohos::data::unifiedDataChannel::CreateHyperlink();
    if (::taihe::has_error()) { return ani_object{}; }
    ani_object ani_result = ohos_data_unifiedDataChannel_Hyperlink_intoANI(env, cpp_result);
    return ani_result;
}
static ani_object ohos_data_unifiedDataChannel_CreatePlainText_ANIFunc([[maybe_unused]] ani_env *env) {
    ::ohos::data::unifiedDataChannel::PlainText cpp_result = ::ohos::data::unifiedDataChannel::CreatePlainText();
    if (::taihe::has_error()) { return ani_object{}; }
    ani_object ani_result = ohos_data_unifiedDataChannel_PlainText_intoANI(env, cpp_result);
    return ani_result;
}
static ani_object ohos_data_unifiedDataChannel_CreateSystemDefinedRecord_ANIFunc([[maybe_unused]] ani_env *env) {
    ::ohos::data::unifiedDataChannel::SystemDefinedRecord cpp_result = ::ohos::data::unifiedDataChannel::CreateSystemDefinedRecord();
    if (::taihe::has_error()) { return ani_object{}; }
    ani_object ani_result = ohos_data_unifiedDataChannel_SystemDefinedRecord_intoANI(env, cpp_result);
    return ani_result;
}
static ani_object ohos_data_unifiedDataChannel_CreateSystemDefinedForm_ANIFunc([[maybe_unused]] ani_env *env) {
    ::ohos::data::unifiedDataChannel::SystemDefinedForm cpp_result = ::ohos::data::unifiedDataChannel::CreateSystemDefinedForm();
    if (::taihe::has_error()) { return ani_object{}; }
    ani_object ani_result = ohos_data_unifiedDataChannel_SystemDefinedForm_intoANI(env, cpp_result);
    return ani_result;
}
static ani_object ohos_data_unifiedDataChannel_CreateSystemDefinedAppItem_ANIFunc([[maybe_unused]] ani_env *env) {
    ::ohos::data::unifiedDataChannel::SystemDefinedAppItem cpp_result = ::ohos::data::unifiedDataChannel::CreateSystemDefinedAppItem();
    if (::taihe::has_error()) { return ani_object{}; }
    ani_object ani_result = ohos_data_unifiedDataChannel_SystemDefinedAppItem_intoANI(env, cpp_result);
    return ani_result;
}
static ani_object ohos_data_unifiedDataChannel_CreateSystemDefinedPixelMap_ANIFunc([[maybe_unused]] ani_env *env) {
    ::ohos::data::unifiedDataChannel::SystemDefinedPixelMap cpp_result = ::ohos::data::unifiedDataChannel::CreateSystemDefinedPixelMap();
    if (::taihe::has_error()) { return ani_object{}; }
    ani_object ani_result = ohos_data_unifiedDataChannel_SystemDefinedPixelMap_intoANI(env, cpp_result);
    return ani_result;
}
static void ohos_data_unifiedDataChannel_InsertDataSync_ANIFunc([[maybe_unused]] ani_env *env, ani_object ani_arg_options, ani_object ani_arg_data) {
    ::ohos::data::unifiedDataChannel::Options cpp_arg_options = ohos_data_unifiedDataChannel_Options_fromANI(env, ani_arg_options);
    ::ohos::data::unifiedDataChannel::UnifiedData cpp_arg_data = ohos_data_unifiedDataChannel_UnifiedData_fromANI(env, ani_arg_data);
    ::ohos::data::unifiedDataChannel::InsertDataSync(cpp_arg_options, cpp_arg_data);
}
static ani_array_ref ohos_data_unifiedDataChannel_QueryDataSync_ANIFunc([[maybe_unused]] ani_env *env, ani_object ani_arg_options) {
    ::ohos::data::unifiedDataChannel::Options cpp_arg_options = ohos_data_unifiedDataChannel_Options_fromANI(env, ani_arg_options);
    ::taihe::array<::ohos::data::unifiedDataChannel::UnifiedData> cpp_result = ::ohos::data::unifiedDataChannel::QueryDataSync(cpp_arg_options);
    if (::taihe::has_error()) { return ani_array_ref{}; }
    size_t ani_result_size = cpp_result.size();
    ani_array_ref ani_result;
    ani_class ani_result_cls;
    env->FindClass("L@ohos/data/unifiedDataChannel/unifiedDataChannel/UnifiedData;", &ani_result_cls);
    ani_ref ani_result_undef;
    env->GetUndefined(&ani_result_undef);
    env->Array_New_Ref(ani_result_cls, ani_result_size, ani_result_undef, &ani_result);
    for (size_t ani_result_i = 0; ani_result_i < ani_result_size; ani_result_i++) {
        ani_object ani_result_item = ohos_data_unifiedDataChannel_UnifiedData_intoANI(env, cpp_result.data()[ani_result_i]);
        env->Array_Set_Ref(ani_result, ani_result_i, ani_result_item);
    }
    return ani_result;
}
static void ohos_data_unifiedDataChannel_UnifiedData_AddRecord_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object, ani_object ani_arg_unifiedRecord) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/UnifiedData;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/UnifiedData;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_UnifiedData_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_UnifiedData_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::UnifiedData cpp_iface = ::ohos::data::unifiedDataChannel::weak::UnifiedData({cpp_vtbl_ptr, cpp_data_ptr});
    ::ohos::data::unifiedDataChannel::UnifiedRecord cpp_arg_unifiedRecord = ohos_data_unifiedDataChannel_UnifiedRecord_fromANI(env, ani_arg_unifiedRecord);
    ::ohos::data::unifiedDataChannel::weak::UnifiedData(cpp_iface)->AddRecord(cpp_arg_unifiedRecord);
}
static ani_array_ref ohos_data_unifiedDataChannel_UnifiedData_GetRecords_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/UnifiedData;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/UnifiedData;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_UnifiedData_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_UnifiedData_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::UnifiedData cpp_iface = ::ohos::data::unifiedDataChannel::weak::UnifiedData({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::array<::ohos::data::unifiedDataChannel::UnifiedRecord> cpp_result = ::ohos::data::unifiedDataChannel::weak::UnifiedData(cpp_iface)->GetRecords();
    if (::taihe::has_error()) { return ani_array_ref{}; }
    size_t ani_result_size = cpp_result.size();
    ani_array_ref ani_result;
    ani_class ani_result_cls;
    env->FindClass("L@ohos/data/unifiedDataChannel/unifiedDataChannel/UnifiedRecord;", &ani_result_cls);
    ani_ref ani_result_undef;
    env->GetUndefined(&ani_result_undef);
    env->Array_New_Ref(ani_result_cls, ani_result_size, ani_result_undef, &ani_result);
    for (size_t ani_result_i = 0; ani_result_i < ani_result_size; ani_result_i++) {
        ani_object ani_result_item = ohos_data_unifiedDataChannel_UnifiedRecord_intoANI(env, cpp_result.data()[ani_result_i]);
        env->Array_Set_Ref(ani_result, ani_result_i, ani_result_item);
    }
    return ani_result;
}
static ani_long ohos_data_unifiedDataChannel_UnifiedData_GetInner_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/UnifiedData;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/UnifiedData;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_UnifiedData_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_UnifiedData_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::UnifiedData cpp_iface = ::ohos::data::unifiedDataChannel::weak::UnifiedData({cpp_vtbl_ptr, cpp_data_ptr});
    int64_t cpp_result = ::ohos::data::unifiedDataChannel::weak::UnifiedData(cpp_iface)->GetInner();
    if (::taihe::has_error()) { return ani_long{}; }
    ani_long ani_result = (int64_t)cpp_result;
    return ani_result;
}
static void ohos_data_unifiedDataChannel_UnifiedData_static_finalize_ANIFunc4([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_class clazz, ani_long data_ptr) {
    ::taihe::data_holder(reinterpret_cast<DataBlockHead*>(data_ptr));
}
static ani_string ohos_data_unifiedDataChannel_UnifiedRecord_GetType_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/UnifiedRecord;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/UnifiedRecord;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_UnifiedRecord_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_UnifiedRecord_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::UnifiedRecord cpp_iface = ::ohos::data::unifiedDataChannel::weak::UnifiedRecord({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::string cpp_result = ::ohos::data::unifiedDataChannel::weak::UnifiedRecord(cpp_iface)->GetType();
    if (::taihe::has_error()) { return ani_string{}; }
    ani_string ani_result;
    env->String_NewUTF8(cpp_result.c_str(), cpp_result.size(), &ani_result);
    return ani_result;
}
static ani_ref ohos_data_unifiedDataChannel_UnifiedRecord_GetValue_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/UnifiedRecord;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/UnifiedRecord;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_UnifiedRecord_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_UnifiedRecord_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::UnifiedRecord cpp_iface = ::ohos::data::unifiedDataChannel::weak::UnifiedRecord({cpp_vtbl_ptr, cpp_data_ptr});
    ::ohos::data::unifiedDataChannel::ValueType cpp_result = ::ohos::data::unifiedDataChannel::weak::UnifiedRecord(cpp_iface)->GetValue();
    if (::taihe::has_error()) { return ani_ref{}; }
    ani_ref ani_result = ohos_data_unifiedDataChannel_ValueType_intoANI(env, cpp_result);
    return ani_result;
}
static ani_long ohos_data_unifiedDataChannel_UnifiedRecord_GetInner_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/UnifiedRecord;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/UnifiedRecord;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_UnifiedRecord_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_UnifiedRecord_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::UnifiedRecord cpp_iface = ::ohos::data::unifiedDataChannel::weak::UnifiedRecord({cpp_vtbl_ptr, cpp_data_ptr});
    int64_t cpp_result = ::ohos::data::unifiedDataChannel::weak::UnifiedRecord(cpp_iface)->GetInner();
    if (::taihe::has_error()) { return ani_long{}; }
    ani_long ani_result = (int64_t)cpp_result;
    return ani_result;
}
static void ohos_data_unifiedDataChannel_UnifiedRecord_static_finalize_ANIFunc4([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_class clazz, ani_long data_ptr) {
    ::taihe::data_holder(reinterpret_cast<DataBlockHead*>(data_ptr));
}
static ani_string ohos_data_unifiedDataChannel_File_GetType_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/File;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/File;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_File_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_File_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::File cpp_iface = ::ohos::data::unifiedDataChannel::weak::File({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::string cpp_result = ::ohos::data::unifiedDataChannel::weak::File(cpp_iface)->GetType();
    if (::taihe::has_error()) { return ani_string{}; }
    ani_string ani_result;
    env->String_NewUTF8(cpp_result.c_str(), cpp_result.size(), &ani_result);
    return ani_result;
}
static ani_ref ohos_data_unifiedDataChannel_File_GetValue_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/File;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/File;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_File_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_File_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::File cpp_iface = ::ohos::data::unifiedDataChannel::weak::File({cpp_vtbl_ptr, cpp_data_ptr});
    ::ohos::data::unifiedDataChannel::ValueType cpp_result = ::ohos::data::unifiedDataChannel::weak::File(cpp_iface)->GetValue();
    if (::taihe::has_error()) { return ani_ref{}; }
    ani_ref ani_result = ohos_data_unifiedDataChannel_ValueType_intoANI(env, cpp_result);
    return ani_result;
}
static ani_string ohos_data_unifiedDataChannel_File_GetUri_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/File;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/File;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_File_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_File_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::File cpp_iface = ::ohos::data::unifiedDataChannel::weak::File({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::string cpp_result = ::ohos::data::unifiedDataChannel::weak::File(cpp_iface)->GetUri();
    if (::taihe::has_error()) { return ani_string{}; }
    ani_string ani_result;
    env->String_NewUTF8(cpp_result.c_str(), cpp_result.size(), &ani_result);
    return ani_result;
}
static void ohos_data_unifiedDataChannel_File_SetUri_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object, ani_string ani_arg_uri) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/File;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/File;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_File_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_File_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::File cpp_iface = ::ohos::data::unifiedDataChannel::weak::File({cpp_vtbl_ptr, cpp_data_ptr});
    ani_size cpp_arg_uri_len;
    env->String_GetUTF8Size(ani_arg_uri, &cpp_arg_uri_len);
    TString cpp_arg_uri_tstr;
    char* cpp_arg_uri_buf = tstr_initialize(&cpp_arg_uri_tstr, cpp_arg_uri_len + 1);
    env->String_GetUTF8(ani_arg_uri, cpp_arg_uri_buf, cpp_arg_uri_len + 1, &cpp_arg_uri_len);
    cpp_arg_uri_buf[cpp_arg_uri_len] = '\0';
    cpp_arg_uri_tstr.length = cpp_arg_uri_len;
    ::taihe::string cpp_arg_uri = ::taihe::string(cpp_arg_uri_tstr);
    ::ohos::data::unifiedDataChannel::weak::File(cpp_iface)->SetUri(cpp_arg_uri);
}
static ani_ref ohos_data_unifiedDataChannel_File_GetDetails_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/File;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/File;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_File_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_File_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::File cpp_iface = ::ohos::data::unifiedDataChannel::weak::File({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::optional<::taihe::map<::taihe::string, ::taihe::string>> cpp_result = ::ohos::data::unifiedDataChannel::weak::File(cpp_iface)->GetDetails();
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
static void ohos_data_unifiedDataChannel_File_SetDetails_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object, ani_object ani_arg_details) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/File;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/File;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_File_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_File_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::File cpp_iface = ::ohos::data::unifiedDataChannel::weak::File({cpp_vtbl_ptr, cpp_data_ptr});
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
    ::ohos::data::unifiedDataChannel::weak::File(cpp_iface)->SetDetails(cpp_arg_details);
}
static ani_long ohos_data_unifiedDataChannel_File_GetInner_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/File;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/File;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_File_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_File_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::File cpp_iface = ::ohos::data::unifiedDataChannel::weak::File({cpp_vtbl_ptr, cpp_data_ptr});
    int64_t cpp_result = ::ohos::data::unifiedDataChannel::weak::File(cpp_iface)->GetInner();
    if (::taihe::has_error()) { return ani_long{}; }
    ani_long ani_result = (int64_t)cpp_result;
    return ani_result;
}
static void ohos_data_unifiedDataChannel_File_static_finalize_ANIFunc4([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_class clazz, ani_long data_ptr) {
    ::taihe::data_holder(reinterpret_cast<DataBlockHead*>(data_ptr));
}
static ani_string ohos_data_unifiedDataChannel_Folder_GetType_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Folder;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Folder;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_Folder_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_Folder_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::Folder cpp_iface = ::ohos::data::unifiedDataChannel::weak::Folder({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::string cpp_result = ::ohos::data::unifiedDataChannel::weak::Folder(cpp_iface)->GetType();
    if (::taihe::has_error()) { return ani_string{}; }
    ani_string ani_result;
    env->String_NewUTF8(cpp_result.c_str(), cpp_result.size(), &ani_result);
    return ani_result;
}
static ani_ref ohos_data_unifiedDataChannel_Folder_GetValue_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Folder;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Folder;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_Folder_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_Folder_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::Folder cpp_iface = ::ohos::data::unifiedDataChannel::weak::Folder({cpp_vtbl_ptr, cpp_data_ptr});
    ::ohos::data::unifiedDataChannel::ValueType cpp_result = ::ohos::data::unifiedDataChannel::weak::Folder(cpp_iface)->GetValue();
    if (::taihe::has_error()) { return ani_ref{}; }
    ani_ref ani_result = ohos_data_unifiedDataChannel_ValueType_intoANI(env, cpp_result);
    return ani_result;
}
static ani_string ohos_data_unifiedDataChannel_Folder_GetUri_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Folder;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Folder;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_Folder_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_Folder_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::Folder cpp_iface = ::ohos::data::unifiedDataChannel::weak::Folder({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::string cpp_result = ::ohos::data::unifiedDataChannel::weak::Folder(cpp_iface)->GetUri();
    if (::taihe::has_error()) { return ani_string{}; }
    ani_string ani_result;
    env->String_NewUTF8(cpp_result.c_str(), cpp_result.size(), &ani_result);
    return ani_result;
}
static void ohos_data_unifiedDataChannel_Folder_SetUri_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object, ani_string ani_arg_uri) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Folder;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Folder;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_Folder_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_Folder_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::Folder cpp_iface = ::ohos::data::unifiedDataChannel::weak::Folder({cpp_vtbl_ptr, cpp_data_ptr});
    ani_size cpp_arg_uri_len;
    env->String_GetUTF8Size(ani_arg_uri, &cpp_arg_uri_len);
    TString cpp_arg_uri_tstr;
    char* cpp_arg_uri_buf = tstr_initialize(&cpp_arg_uri_tstr, cpp_arg_uri_len + 1);
    env->String_GetUTF8(ani_arg_uri, cpp_arg_uri_buf, cpp_arg_uri_len + 1, &cpp_arg_uri_len);
    cpp_arg_uri_buf[cpp_arg_uri_len] = '\0';
    cpp_arg_uri_tstr.length = cpp_arg_uri_len;
    ::taihe::string cpp_arg_uri = ::taihe::string(cpp_arg_uri_tstr);
    ::ohos::data::unifiedDataChannel::weak::Folder(cpp_iface)->SetUri(cpp_arg_uri);
}
static ani_ref ohos_data_unifiedDataChannel_Folder_GetDetails_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Folder;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Folder;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_Folder_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_Folder_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::Folder cpp_iface = ::ohos::data::unifiedDataChannel::weak::Folder({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::optional<::taihe::map<::taihe::string, ::taihe::string>> cpp_result = ::ohos::data::unifiedDataChannel::weak::Folder(cpp_iface)->GetDetails();
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
static void ohos_data_unifiedDataChannel_Folder_SetDetails_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object, ani_object ani_arg_details) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Folder;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Folder;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_Folder_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_Folder_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::Folder cpp_iface = ::ohos::data::unifiedDataChannel::weak::Folder({cpp_vtbl_ptr, cpp_data_ptr});
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
    ::ohos::data::unifiedDataChannel::weak::Folder(cpp_iface)->SetDetails(cpp_arg_details);
}
static ani_string ohos_data_unifiedDataChannel_Folder_GetFolderUri_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Folder;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Folder;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_Folder_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_Folder_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::Folder cpp_iface = ::ohos::data::unifiedDataChannel::weak::Folder({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::string cpp_result = ::ohos::data::unifiedDataChannel::weak::Folder(cpp_iface)->GetFolderUri();
    if (::taihe::has_error()) { return ani_string{}; }
    ani_string ani_result;
    env->String_NewUTF8(cpp_result.c_str(), cpp_result.size(), &ani_result);
    return ani_result;
}
static void ohos_data_unifiedDataChannel_Folder_SetFolderUri_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object, ani_string ani_arg_folderUri) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Folder;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Folder;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_Folder_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_Folder_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::Folder cpp_iface = ::ohos::data::unifiedDataChannel::weak::Folder({cpp_vtbl_ptr, cpp_data_ptr});
    ani_size cpp_arg_folderUri_len;
    env->String_GetUTF8Size(ani_arg_folderUri, &cpp_arg_folderUri_len);
    TString cpp_arg_folderUri_tstr;
    char* cpp_arg_folderUri_buf = tstr_initialize(&cpp_arg_folderUri_tstr, cpp_arg_folderUri_len + 1);
    env->String_GetUTF8(ani_arg_folderUri, cpp_arg_folderUri_buf, cpp_arg_folderUri_len + 1, &cpp_arg_folderUri_len);
    cpp_arg_folderUri_buf[cpp_arg_folderUri_len] = '\0';
    cpp_arg_folderUri_tstr.length = cpp_arg_folderUri_len;
    ::taihe::string cpp_arg_folderUri = ::taihe::string(cpp_arg_folderUri_tstr);
    ::ohos::data::unifiedDataChannel::weak::Folder(cpp_iface)->SetFolderUri(cpp_arg_folderUri);
}
static ani_long ohos_data_unifiedDataChannel_Folder_GetInner_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Folder;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Folder;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_Folder_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_Folder_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::Folder cpp_iface = ::ohos::data::unifiedDataChannel::weak::Folder({cpp_vtbl_ptr, cpp_data_ptr});
    int64_t cpp_result = ::ohos::data::unifiedDataChannel::weak::Folder(cpp_iface)->GetInner();
    if (::taihe::has_error()) { return ani_long{}; }
    ani_long ani_result = (int64_t)cpp_result;
    return ani_result;
}
static void ohos_data_unifiedDataChannel_Folder_static_finalize_ANIFunc4([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_class clazz, ani_long data_ptr) {
    ::taihe::data_holder(reinterpret_cast<DataBlockHead*>(data_ptr));
}
static ani_string ohos_data_unifiedDataChannel_Audio_GetType_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Audio;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Audio;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_Audio_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_Audio_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::Audio cpp_iface = ::ohos::data::unifiedDataChannel::weak::Audio({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::string cpp_result = ::ohos::data::unifiedDataChannel::weak::Audio(cpp_iface)->GetType();
    if (::taihe::has_error()) { return ani_string{}; }
    ani_string ani_result;
    env->String_NewUTF8(cpp_result.c_str(), cpp_result.size(), &ani_result);
    return ani_result;
}
static ani_ref ohos_data_unifiedDataChannel_Audio_GetValue_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Audio;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Audio;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_Audio_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_Audio_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::Audio cpp_iface = ::ohos::data::unifiedDataChannel::weak::Audio({cpp_vtbl_ptr, cpp_data_ptr});
    ::ohos::data::unifiedDataChannel::ValueType cpp_result = ::ohos::data::unifiedDataChannel::weak::Audio(cpp_iface)->GetValue();
    if (::taihe::has_error()) { return ani_ref{}; }
    ani_ref ani_result = ohos_data_unifiedDataChannel_ValueType_intoANI(env, cpp_result);
    return ani_result;
}
static ani_string ohos_data_unifiedDataChannel_Audio_GetUri_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Audio;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Audio;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_Audio_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_Audio_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::Audio cpp_iface = ::ohos::data::unifiedDataChannel::weak::Audio({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::string cpp_result = ::ohos::data::unifiedDataChannel::weak::Audio(cpp_iface)->GetUri();
    if (::taihe::has_error()) { return ani_string{}; }
    ani_string ani_result;
    env->String_NewUTF8(cpp_result.c_str(), cpp_result.size(), &ani_result);
    return ani_result;
}
static void ohos_data_unifiedDataChannel_Audio_SetUri_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object, ani_string ani_arg_uri) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Audio;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Audio;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_Audio_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_Audio_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::Audio cpp_iface = ::ohos::data::unifiedDataChannel::weak::Audio({cpp_vtbl_ptr, cpp_data_ptr});
    ani_size cpp_arg_uri_len;
    env->String_GetUTF8Size(ani_arg_uri, &cpp_arg_uri_len);
    TString cpp_arg_uri_tstr;
    char* cpp_arg_uri_buf = tstr_initialize(&cpp_arg_uri_tstr, cpp_arg_uri_len + 1);
    env->String_GetUTF8(ani_arg_uri, cpp_arg_uri_buf, cpp_arg_uri_len + 1, &cpp_arg_uri_len);
    cpp_arg_uri_buf[cpp_arg_uri_len] = '\0';
    cpp_arg_uri_tstr.length = cpp_arg_uri_len;
    ::taihe::string cpp_arg_uri = ::taihe::string(cpp_arg_uri_tstr);
    ::ohos::data::unifiedDataChannel::weak::Audio(cpp_iface)->SetUri(cpp_arg_uri);
}
static ani_ref ohos_data_unifiedDataChannel_Audio_GetDetails_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Audio;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Audio;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_Audio_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_Audio_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::Audio cpp_iface = ::ohos::data::unifiedDataChannel::weak::Audio({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::optional<::taihe::map<::taihe::string, ::taihe::string>> cpp_result = ::ohos::data::unifiedDataChannel::weak::Audio(cpp_iface)->GetDetails();
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
static void ohos_data_unifiedDataChannel_Audio_SetDetails_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object, ani_object ani_arg_details) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Audio;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Audio;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_Audio_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_Audio_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::Audio cpp_iface = ::ohos::data::unifiedDataChannel::weak::Audio({cpp_vtbl_ptr, cpp_data_ptr});
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
    ::ohos::data::unifiedDataChannel::weak::Audio(cpp_iface)->SetDetails(cpp_arg_details);
}
static ani_string ohos_data_unifiedDataChannel_Audio_GetAudioUri_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Audio;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Audio;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_Audio_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_Audio_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::Audio cpp_iface = ::ohos::data::unifiedDataChannel::weak::Audio({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::string cpp_result = ::ohos::data::unifiedDataChannel::weak::Audio(cpp_iface)->GetAudioUri();
    if (::taihe::has_error()) { return ani_string{}; }
    ani_string ani_result;
    env->String_NewUTF8(cpp_result.c_str(), cpp_result.size(), &ani_result);
    return ani_result;
}
static void ohos_data_unifiedDataChannel_Audio_SetAudioUri_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object, ani_string ani_arg_audioUri) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Audio;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Audio;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_Audio_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_Audio_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::Audio cpp_iface = ::ohos::data::unifiedDataChannel::weak::Audio({cpp_vtbl_ptr, cpp_data_ptr});
    ani_size cpp_arg_audioUri_len;
    env->String_GetUTF8Size(ani_arg_audioUri, &cpp_arg_audioUri_len);
    TString cpp_arg_audioUri_tstr;
    char* cpp_arg_audioUri_buf = tstr_initialize(&cpp_arg_audioUri_tstr, cpp_arg_audioUri_len + 1);
    env->String_GetUTF8(ani_arg_audioUri, cpp_arg_audioUri_buf, cpp_arg_audioUri_len + 1, &cpp_arg_audioUri_len);
    cpp_arg_audioUri_buf[cpp_arg_audioUri_len] = '\0';
    cpp_arg_audioUri_tstr.length = cpp_arg_audioUri_len;
    ::taihe::string cpp_arg_audioUri = ::taihe::string(cpp_arg_audioUri_tstr);
    ::ohos::data::unifiedDataChannel::weak::Audio(cpp_iface)->SetAudioUri(cpp_arg_audioUri);
}
static ani_long ohos_data_unifiedDataChannel_Audio_GetInner_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Audio;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Audio;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_Audio_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_Audio_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::Audio cpp_iface = ::ohos::data::unifiedDataChannel::weak::Audio({cpp_vtbl_ptr, cpp_data_ptr});
    int64_t cpp_result = ::ohos::data::unifiedDataChannel::weak::Audio(cpp_iface)->GetInner();
    if (::taihe::has_error()) { return ani_long{}; }
    ani_long ani_result = (int64_t)cpp_result;
    return ani_result;
}
static void ohos_data_unifiedDataChannel_Audio_static_finalize_ANIFunc4([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_class clazz, ani_long data_ptr) {
    ::taihe::data_holder(reinterpret_cast<DataBlockHead*>(data_ptr));
}
static ani_string ohos_data_unifiedDataChannel_Video_GetType_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Video;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Video;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_Video_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_Video_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::Video cpp_iface = ::ohos::data::unifiedDataChannel::weak::Video({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::string cpp_result = ::ohos::data::unifiedDataChannel::weak::Video(cpp_iface)->GetType();
    if (::taihe::has_error()) { return ani_string{}; }
    ani_string ani_result;
    env->String_NewUTF8(cpp_result.c_str(), cpp_result.size(), &ani_result);
    return ani_result;
}
static ani_ref ohos_data_unifiedDataChannel_Video_GetValue_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Video;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Video;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_Video_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_Video_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::Video cpp_iface = ::ohos::data::unifiedDataChannel::weak::Video({cpp_vtbl_ptr, cpp_data_ptr});
    ::ohos::data::unifiedDataChannel::ValueType cpp_result = ::ohos::data::unifiedDataChannel::weak::Video(cpp_iface)->GetValue();
    if (::taihe::has_error()) { return ani_ref{}; }
    ani_ref ani_result = ohos_data_unifiedDataChannel_ValueType_intoANI(env, cpp_result);
    return ani_result;
}
static ani_string ohos_data_unifiedDataChannel_Video_GetUri_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Video;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Video;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_Video_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_Video_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::Video cpp_iface = ::ohos::data::unifiedDataChannel::weak::Video({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::string cpp_result = ::ohos::data::unifiedDataChannel::weak::Video(cpp_iface)->GetUri();
    if (::taihe::has_error()) { return ani_string{}; }
    ani_string ani_result;
    env->String_NewUTF8(cpp_result.c_str(), cpp_result.size(), &ani_result);
    return ani_result;
}
static void ohos_data_unifiedDataChannel_Video_SetUri_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object, ani_string ani_arg_uri) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Video;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Video;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_Video_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_Video_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::Video cpp_iface = ::ohos::data::unifiedDataChannel::weak::Video({cpp_vtbl_ptr, cpp_data_ptr});
    ani_size cpp_arg_uri_len;
    env->String_GetUTF8Size(ani_arg_uri, &cpp_arg_uri_len);
    TString cpp_arg_uri_tstr;
    char* cpp_arg_uri_buf = tstr_initialize(&cpp_arg_uri_tstr, cpp_arg_uri_len + 1);
    env->String_GetUTF8(ani_arg_uri, cpp_arg_uri_buf, cpp_arg_uri_len + 1, &cpp_arg_uri_len);
    cpp_arg_uri_buf[cpp_arg_uri_len] = '\0';
    cpp_arg_uri_tstr.length = cpp_arg_uri_len;
    ::taihe::string cpp_arg_uri = ::taihe::string(cpp_arg_uri_tstr);
    ::ohos::data::unifiedDataChannel::weak::Video(cpp_iface)->SetUri(cpp_arg_uri);
}
static ani_ref ohos_data_unifiedDataChannel_Video_GetDetails_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Video;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Video;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_Video_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_Video_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::Video cpp_iface = ::ohos::data::unifiedDataChannel::weak::Video({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::optional<::taihe::map<::taihe::string, ::taihe::string>> cpp_result = ::ohos::data::unifiedDataChannel::weak::Video(cpp_iface)->GetDetails();
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
static void ohos_data_unifiedDataChannel_Video_SetDetails_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object, ani_object ani_arg_details) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Video;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Video;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_Video_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_Video_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::Video cpp_iface = ::ohos::data::unifiedDataChannel::weak::Video({cpp_vtbl_ptr, cpp_data_ptr});
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
    ::ohos::data::unifiedDataChannel::weak::Video(cpp_iface)->SetDetails(cpp_arg_details);
}
static ani_string ohos_data_unifiedDataChannel_Video_GetVideoUri_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Video;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Video;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_Video_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_Video_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::Video cpp_iface = ::ohos::data::unifiedDataChannel::weak::Video({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::string cpp_result = ::ohos::data::unifiedDataChannel::weak::Video(cpp_iface)->GetVideoUri();
    if (::taihe::has_error()) { return ani_string{}; }
    ani_string ani_result;
    env->String_NewUTF8(cpp_result.c_str(), cpp_result.size(), &ani_result);
    return ani_result;
}
static void ohos_data_unifiedDataChannel_Video_SetVideoUri_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object, ani_string ani_arg_videoUri) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Video;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Video;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_Video_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_Video_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::Video cpp_iface = ::ohos::data::unifiedDataChannel::weak::Video({cpp_vtbl_ptr, cpp_data_ptr});
    ani_size cpp_arg_videoUri_len;
    env->String_GetUTF8Size(ani_arg_videoUri, &cpp_arg_videoUri_len);
    TString cpp_arg_videoUri_tstr;
    char* cpp_arg_videoUri_buf = tstr_initialize(&cpp_arg_videoUri_tstr, cpp_arg_videoUri_len + 1);
    env->String_GetUTF8(ani_arg_videoUri, cpp_arg_videoUri_buf, cpp_arg_videoUri_len + 1, &cpp_arg_videoUri_len);
    cpp_arg_videoUri_buf[cpp_arg_videoUri_len] = '\0';
    cpp_arg_videoUri_tstr.length = cpp_arg_videoUri_len;
    ::taihe::string cpp_arg_videoUri = ::taihe::string(cpp_arg_videoUri_tstr);
    ::ohos::data::unifiedDataChannel::weak::Video(cpp_iface)->SetVideoUri(cpp_arg_videoUri);
}
static ani_long ohos_data_unifiedDataChannel_Video_GetInner_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Video;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Video;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_Video_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_Video_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::Video cpp_iface = ::ohos::data::unifiedDataChannel::weak::Video({cpp_vtbl_ptr, cpp_data_ptr});
    int64_t cpp_result = ::ohos::data::unifiedDataChannel::weak::Video(cpp_iface)->GetInner();
    if (::taihe::has_error()) { return ani_long{}; }
    ani_long ani_result = (int64_t)cpp_result;
    return ani_result;
}
static void ohos_data_unifiedDataChannel_Video_static_finalize_ANIFunc4([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_class clazz, ani_long data_ptr) {
    ::taihe::data_holder(reinterpret_cast<DataBlockHead*>(data_ptr));
}
static ani_string ohos_data_unifiedDataChannel_Image_GetType_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Image;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Image;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_Image_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_Image_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::Image cpp_iface = ::ohos::data::unifiedDataChannel::weak::Image({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::string cpp_result = ::ohos::data::unifiedDataChannel::weak::Image(cpp_iface)->GetType();
    if (::taihe::has_error()) { return ani_string{}; }
    ani_string ani_result;
    env->String_NewUTF8(cpp_result.c_str(), cpp_result.size(), &ani_result);
    return ani_result;
}
static ani_ref ohos_data_unifiedDataChannel_Image_GetValue_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Image;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Image;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_Image_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_Image_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::Image cpp_iface = ::ohos::data::unifiedDataChannel::weak::Image({cpp_vtbl_ptr, cpp_data_ptr});
    ::ohos::data::unifiedDataChannel::ValueType cpp_result = ::ohos::data::unifiedDataChannel::weak::Image(cpp_iface)->GetValue();
    if (::taihe::has_error()) { return ani_ref{}; }
    ani_ref ani_result = ohos_data_unifiedDataChannel_ValueType_intoANI(env, cpp_result);
    return ani_result;
}
static ani_string ohos_data_unifiedDataChannel_Image_GetUri_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Image;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Image;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_Image_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_Image_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::Image cpp_iface = ::ohos::data::unifiedDataChannel::weak::Image({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::string cpp_result = ::ohos::data::unifiedDataChannel::weak::Image(cpp_iface)->GetUri();
    if (::taihe::has_error()) { return ani_string{}; }
    ani_string ani_result;
    env->String_NewUTF8(cpp_result.c_str(), cpp_result.size(), &ani_result);
    return ani_result;
}
static void ohos_data_unifiedDataChannel_Image_SetUri_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object, ani_string ani_arg_uri) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Image;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Image;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_Image_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_Image_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::Image cpp_iface = ::ohos::data::unifiedDataChannel::weak::Image({cpp_vtbl_ptr, cpp_data_ptr});
    ani_size cpp_arg_uri_len;
    env->String_GetUTF8Size(ani_arg_uri, &cpp_arg_uri_len);
    TString cpp_arg_uri_tstr;
    char* cpp_arg_uri_buf = tstr_initialize(&cpp_arg_uri_tstr, cpp_arg_uri_len + 1);
    env->String_GetUTF8(ani_arg_uri, cpp_arg_uri_buf, cpp_arg_uri_len + 1, &cpp_arg_uri_len);
    cpp_arg_uri_buf[cpp_arg_uri_len] = '\0';
    cpp_arg_uri_tstr.length = cpp_arg_uri_len;
    ::taihe::string cpp_arg_uri = ::taihe::string(cpp_arg_uri_tstr);
    ::ohos::data::unifiedDataChannel::weak::Image(cpp_iface)->SetUri(cpp_arg_uri);
}
static ani_ref ohos_data_unifiedDataChannel_Image_GetDetails_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Image;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Image;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_Image_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_Image_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::Image cpp_iface = ::ohos::data::unifiedDataChannel::weak::Image({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::optional<::taihe::map<::taihe::string, ::taihe::string>> cpp_result = ::ohos::data::unifiedDataChannel::weak::Image(cpp_iface)->GetDetails();
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
static void ohos_data_unifiedDataChannel_Image_SetDetails_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object, ani_object ani_arg_details) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Image;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Image;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_Image_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_Image_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::Image cpp_iface = ::ohos::data::unifiedDataChannel::weak::Image({cpp_vtbl_ptr, cpp_data_ptr});
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
    ::ohos::data::unifiedDataChannel::weak::Image(cpp_iface)->SetDetails(cpp_arg_details);
}
static ani_string ohos_data_unifiedDataChannel_Image_GetImageUri_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Image;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Image;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_Image_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_Image_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::Image cpp_iface = ::ohos::data::unifiedDataChannel::weak::Image({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::string cpp_result = ::ohos::data::unifiedDataChannel::weak::Image(cpp_iface)->GetImageUri();
    if (::taihe::has_error()) { return ani_string{}; }
    ani_string ani_result;
    env->String_NewUTF8(cpp_result.c_str(), cpp_result.size(), &ani_result);
    return ani_result;
}
static void ohos_data_unifiedDataChannel_Image_SetImageUri_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object, ani_string ani_arg_imageUri) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Image;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Image;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_Image_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_Image_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::Image cpp_iface = ::ohos::data::unifiedDataChannel::weak::Image({cpp_vtbl_ptr, cpp_data_ptr});
    ani_size cpp_arg_imageUri_len;
    env->String_GetUTF8Size(ani_arg_imageUri, &cpp_arg_imageUri_len);
    TString cpp_arg_imageUri_tstr;
    char* cpp_arg_imageUri_buf = tstr_initialize(&cpp_arg_imageUri_tstr, cpp_arg_imageUri_len + 1);
    env->String_GetUTF8(ani_arg_imageUri, cpp_arg_imageUri_buf, cpp_arg_imageUri_len + 1, &cpp_arg_imageUri_len);
    cpp_arg_imageUri_buf[cpp_arg_imageUri_len] = '\0';
    cpp_arg_imageUri_tstr.length = cpp_arg_imageUri_len;
    ::taihe::string cpp_arg_imageUri = ::taihe::string(cpp_arg_imageUri_tstr);
    ::ohos::data::unifiedDataChannel::weak::Image(cpp_iface)->SetImageUri(cpp_arg_imageUri);
}
static ani_long ohos_data_unifiedDataChannel_Image_GetInner_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Image;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Image;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_Image_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_Image_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::Image cpp_iface = ::ohos::data::unifiedDataChannel::weak::Image({cpp_vtbl_ptr, cpp_data_ptr});
    int64_t cpp_result = ::ohos::data::unifiedDataChannel::weak::Image(cpp_iface)->GetInner();
    if (::taihe::has_error()) { return ani_long{}; }
    ani_long ani_result = (int64_t)cpp_result;
    return ani_result;
}
static void ohos_data_unifiedDataChannel_Image_static_finalize_ANIFunc4([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_class clazz, ani_long data_ptr) {
    ::taihe::data_holder(reinterpret_cast<DataBlockHead*>(data_ptr));
}
static ani_string ohos_data_unifiedDataChannel_Text_GetType_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Text;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Text;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_Text_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_Text_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::Text cpp_iface = ::ohos::data::unifiedDataChannel::weak::Text({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::string cpp_result = ::ohos::data::unifiedDataChannel::weak::Text(cpp_iface)->GetType();
    if (::taihe::has_error()) { return ani_string{}; }
    ani_string ani_result;
    env->String_NewUTF8(cpp_result.c_str(), cpp_result.size(), &ani_result);
    return ani_result;
}
static ani_ref ohos_data_unifiedDataChannel_Text_GetValue_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Text;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Text;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_Text_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_Text_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::Text cpp_iface = ::ohos::data::unifiedDataChannel::weak::Text({cpp_vtbl_ptr, cpp_data_ptr});
    ::ohos::data::unifiedDataChannel::ValueType cpp_result = ::ohos::data::unifiedDataChannel::weak::Text(cpp_iface)->GetValue();
    if (::taihe::has_error()) { return ani_ref{}; }
    ani_ref ani_result = ohos_data_unifiedDataChannel_ValueType_intoANI(env, cpp_result);
    return ani_result;
}
static ani_ref ohos_data_unifiedDataChannel_Text_GetDetails_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Text;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Text;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_Text_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_Text_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::Text cpp_iface = ::ohos::data::unifiedDataChannel::weak::Text({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::optional<::taihe::map<::taihe::string, ::taihe::string>> cpp_result = ::ohos::data::unifiedDataChannel::weak::Text(cpp_iface)->GetDetails();
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
static void ohos_data_unifiedDataChannel_Text_SetDetails_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object, ani_object ani_arg_details) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Text;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Text;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_Text_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_Text_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::Text cpp_iface = ::ohos::data::unifiedDataChannel::weak::Text({cpp_vtbl_ptr, cpp_data_ptr});
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
    ::ohos::data::unifiedDataChannel::weak::Text(cpp_iface)->SetDetails(cpp_arg_details);
}
static ani_long ohos_data_unifiedDataChannel_Text_GetInner_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Text;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Text;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_Text_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_Text_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::Text cpp_iface = ::ohos::data::unifiedDataChannel::weak::Text({cpp_vtbl_ptr, cpp_data_ptr});
    int64_t cpp_result = ::ohos::data::unifiedDataChannel::weak::Text(cpp_iface)->GetInner();
    if (::taihe::has_error()) { return ani_long{}; }
    ani_long ani_result = (int64_t)cpp_result;
    return ani_result;
}
static void ohos_data_unifiedDataChannel_Text_static_finalize_ANIFunc4([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_class clazz, ani_long data_ptr) {
    ::taihe::data_holder(reinterpret_cast<DataBlockHead*>(data_ptr));
}
static ani_string ohos_data_unifiedDataChannel_HTML_GetType_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/HTML;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/HTML;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_HTML_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_HTML_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::HTML cpp_iface = ::ohos::data::unifiedDataChannel::weak::HTML({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::string cpp_result = ::ohos::data::unifiedDataChannel::weak::HTML(cpp_iface)->GetType();
    if (::taihe::has_error()) { return ani_string{}; }
    ani_string ani_result;
    env->String_NewUTF8(cpp_result.c_str(), cpp_result.size(), &ani_result);
    return ani_result;
}
static ani_ref ohos_data_unifiedDataChannel_HTML_GetValue_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/HTML;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/HTML;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_HTML_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_HTML_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::HTML cpp_iface = ::ohos::data::unifiedDataChannel::weak::HTML({cpp_vtbl_ptr, cpp_data_ptr});
    ::ohos::data::unifiedDataChannel::ValueType cpp_result = ::ohos::data::unifiedDataChannel::weak::HTML(cpp_iface)->GetValue();
    if (::taihe::has_error()) { return ani_ref{}; }
    ani_ref ani_result = ohos_data_unifiedDataChannel_ValueType_intoANI(env, cpp_result);
    return ani_result;
}
static ani_ref ohos_data_unifiedDataChannel_HTML_GetDetails_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/HTML;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/HTML;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_HTML_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_HTML_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::HTML cpp_iface = ::ohos::data::unifiedDataChannel::weak::HTML({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::optional<::taihe::map<::taihe::string, ::taihe::string>> cpp_result = ::ohos::data::unifiedDataChannel::weak::HTML(cpp_iface)->GetDetails();
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
static void ohos_data_unifiedDataChannel_HTML_SetDetails_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object, ani_object ani_arg_details) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/HTML;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/HTML;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_HTML_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_HTML_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::HTML cpp_iface = ::ohos::data::unifiedDataChannel::weak::HTML({cpp_vtbl_ptr, cpp_data_ptr});
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
    ::ohos::data::unifiedDataChannel::weak::HTML(cpp_iface)->SetDetails(cpp_arg_details);
}
static void ohos_data_unifiedDataChannel_HTML_SetHtmlContent_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object, ani_string ani_arg_htmlContent) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/HTML;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/HTML;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_HTML_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_HTML_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::HTML cpp_iface = ::ohos::data::unifiedDataChannel::weak::HTML({cpp_vtbl_ptr, cpp_data_ptr});
    ani_size cpp_arg_htmlContent_len;
    env->String_GetUTF8Size(ani_arg_htmlContent, &cpp_arg_htmlContent_len);
    TString cpp_arg_htmlContent_tstr;
    char* cpp_arg_htmlContent_buf = tstr_initialize(&cpp_arg_htmlContent_tstr, cpp_arg_htmlContent_len + 1);
    env->String_GetUTF8(ani_arg_htmlContent, cpp_arg_htmlContent_buf, cpp_arg_htmlContent_len + 1, &cpp_arg_htmlContent_len);
    cpp_arg_htmlContent_buf[cpp_arg_htmlContent_len] = '\0';
    cpp_arg_htmlContent_tstr.length = cpp_arg_htmlContent_len;
    ::taihe::string cpp_arg_htmlContent = ::taihe::string(cpp_arg_htmlContent_tstr);
    ::ohos::data::unifiedDataChannel::weak::HTML(cpp_iface)->SetHtmlContent(cpp_arg_htmlContent);
}
static ani_string ohos_data_unifiedDataChannel_HTML_GetHtmlContent_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/HTML;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/HTML;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_HTML_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_HTML_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::HTML cpp_iface = ::ohos::data::unifiedDataChannel::weak::HTML({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::string cpp_result = ::ohos::data::unifiedDataChannel::weak::HTML(cpp_iface)->GetHtmlContent();
    if (::taihe::has_error()) { return ani_string{}; }
    ani_string ani_result;
    env->String_NewUTF8(cpp_result.c_str(), cpp_result.size(), &ani_result);
    return ani_result;
}
static void ohos_data_unifiedDataChannel_HTML_SetPlainContent_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object, ani_string ani_arg_plainContent) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/HTML;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/HTML;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_HTML_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_HTML_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::HTML cpp_iface = ::ohos::data::unifiedDataChannel::weak::HTML({cpp_vtbl_ptr, cpp_data_ptr});
    ani_size cpp_arg_plainContent_len;
    env->String_GetUTF8Size(ani_arg_plainContent, &cpp_arg_plainContent_len);
    TString cpp_arg_plainContent_tstr;
    char* cpp_arg_plainContent_buf = tstr_initialize(&cpp_arg_plainContent_tstr, cpp_arg_plainContent_len + 1);
    env->String_GetUTF8(ani_arg_plainContent, cpp_arg_plainContent_buf, cpp_arg_plainContent_len + 1, &cpp_arg_plainContent_len);
    cpp_arg_plainContent_buf[cpp_arg_plainContent_len] = '\0';
    cpp_arg_plainContent_tstr.length = cpp_arg_plainContent_len;
    ::taihe::string cpp_arg_plainContent = ::taihe::string(cpp_arg_plainContent_tstr);
    ::ohos::data::unifiedDataChannel::weak::HTML(cpp_iface)->SetPlainContent(cpp_arg_plainContent);
}
static ani_string ohos_data_unifiedDataChannel_HTML_GetPlainContent_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/HTML;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/HTML;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_HTML_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_HTML_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::HTML cpp_iface = ::ohos::data::unifiedDataChannel::weak::HTML({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::string cpp_result = ::ohos::data::unifiedDataChannel::weak::HTML(cpp_iface)->GetPlainContent();
    if (::taihe::has_error()) { return ani_string{}; }
    ani_string ani_result;
    env->String_NewUTF8(cpp_result.c_str(), cpp_result.size(), &ani_result);
    return ani_result;
}
static ani_long ohos_data_unifiedDataChannel_HTML_GetInner_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/HTML;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/HTML;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_HTML_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_HTML_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::HTML cpp_iface = ::ohos::data::unifiedDataChannel::weak::HTML({cpp_vtbl_ptr, cpp_data_ptr});
    int64_t cpp_result = ::ohos::data::unifiedDataChannel::weak::HTML(cpp_iface)->GetInner();
    if (::taihe::has_error()) { return ani_long{}; }
    ani_long ani_result = (int64_t)cpp_result;
    return ani_result;
}
static void ohos_data_unifiedDataChannel_HTML_static_finalize_ANIFunc4([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_class clazz, ani_long data_ptr) {
    ::taihe::data_holder(reinterpret_cast<DataBlockHead*>(data_ptr));
}
static ani_string ohos_data_unifiedDataChannel_Hyperlink_GetType_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Hyperlink;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Hyperlink;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_Hyperlink_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_Hyperlink_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::Hyperlink cpp_iface = ::ohos::data::unifiedDataChannel::weak::Hyperlink({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::string cpp_result = ::ohos::data::unifiedDataChannel::weak::Hyperlink(cpp_iface)->GetType();
    if (::taihe::has_error()) { return ani_string{}; }
    ani_string ani_result;
    env->String_NewUTF8(cpp_result.c_str(), cpp_result.size(), &ani_result);
    return ani_result;
}
static ani_ref ohos_data_unifiedDataChannel_Hyperlink_GetValue_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Hyperlink;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Hyperlink;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_Hyperlink_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_Hyperlink_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::Hyperlink cpp_iface = ::ohos::data::unifiedDataChannel::weak::Hyperlink({cpp_vtbl_ptr, cpp_data_ptr});
    ::ohos::data::unifiedDataChannel::ValueType cpp_result = ::ohos::data::unifiedDataChannel::weak::Hyperlink(cpp_iface)->GetValue();
    if (::taihe::has_error()) { return ani_ref{}; }
    ani_ref ani_result = ohos_data_unifiedDataChannel_ValueType_intoANI(env, cpp_result);
    return ani_result;
}
static ani_ref ohos_data_unifiedDataChannel_Hyperlink_GetDetails_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Hyperlink;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Hyperlink;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_Hyperlink_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_Hyperlink_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::Hyperlink cpp_iface = ::ohos::data::unifiedDataChannel::weak::Hyperlink({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::optional<::taihe::map<::taihe::string, ::taihe::string>> cpp_result = ::ohos::data::unifiedDataChannel::weak::Hyperlink(cpp_iface)->GetDetails();
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
static void ohos_data_unifiedDataChannel_Hyperlink_SetDetails_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object, ani_object ani_arg_details) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Hyperlink;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Hyperlink;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_Hyperlink_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_Hyperlink_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::Hyperlink cpp_iface = ::ohos::data::unifiedDataChannel::weak::Hyperlink({cpp_vtbl_ptr, cpp_data_ptr});
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
    ::ohos::data::unifiedDataChannel::weak::Hyperlink(cpp_iface)->SetDetails(cpp_arg_details);
}
static void ohos_data_unifiedDataChannel_Hyperlink_SetUrl_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object, ani_string ani_arg_url) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Hyperlink;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Hyperlink;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_Hyperlink_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_Hyperlink_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::Hyperlink cpp_iface = ::ohos::data::unifiedDataChannel::weak::Hyperlink({cpp_vtbl_ptr, cpp_data_ptr});
    ani_size cpp_arg_url_len;
    env->String_GetUTF8Size(ani_arg_url, &cpp_arg_url_len);
    TString cpp_arg_url_tstr;
    char* cpp_arg_url_buf = tstr_initialize(&cpp_arg_url_tstr, cpp_arg_url_len + 1);
    env->String_GetUTF8(ani_arg_url, cpp_arg_url_buf, cpp_arg_url_len + 1, &cpp_arg_url_len);
    cpp_arg_url_buf[cpp_arg_url_len] = '\0';
    cpp_arg_url_tstr.length = cpp_arg_url_len;
    ::taihe::string cpp_arg_url = ::taihe::string(cpp_arg_url_tstr);
    ::ohos::data::unifiedDataChannel::weak::Hyperlink(cpp_iface)->SetUrl(cpp_arg_url);
}
static ani_string ohos_data_unifiedDataChannel_Hyperlink_GetUrl_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Hyperlink;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Hyperlink;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_Hyperlink_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_Hyperlink_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::Hyperlink cpp_iface = ::ohos::data::unifiedDataChannel::weak::Hyperlink({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::string cpp_result = ::ohos::data::unifiedDataChannel::weak::Hyperlink(cpp_iface)->GetUrl();
    if (::taihe::has_error()) { return ani_string{}; }
    ani_string ani_result;
    env->String_NewUTF8(cpp_result.c_str(), cpp_result.size(), &ani_result);
    return ani_result;
}
static void ohos_data_unifiedDataChannel_Hyperlink_SetDescription_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object, ani_string ani_arg_description) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Hyperlink;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Hyperlink;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_Hyperlink_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_Hyperlink_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::Hyperlink cpp_iface = ::ohos::data::unifiedDataChannel::weak::Hyperlink({cpp_vtbl_ptr, cpp_data_ptr});
    ani_size cpp_arg_description_len;
    env->String_GetUTF8Size(ani_arg_description, &cpp_arg_description_len);
    TString cpp_arg_description_tstr;
    char* cpp_arg_description_buf = tstr_initialize(&cpp_arg_description_tstr, cpp_arg_description_len + 1);
    env->String_GetUTF8(ani_arg_description, cpp_arg_description_buf, cpp_arg_description_len + 1, &cpp_arg_description_len);
    cpp_arg_description_buf[cpp_arg_description_len] = '\0';
    cpp_arg_description_tstr.length = cpp_arg_description_len;
    ::taihe::string cpp_arg_description = ::taihe::string(cpp_arg_description_tstr);
    ::ohos::data::unifiedDataChannel::weak::Hyperlink(cpp_iface)->SetDescription(cpp_arg_description);
}
static ani_string ohos_data_unifiedDataChannel_Hyperlink_GetDescription_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Hyperlink;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Hyperlink;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_Hyperlink_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_Hyperlink_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::Hyperlink cpp_iface = ::ohos::data::unifiedDataChannel::weak::Hyperlink({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::string cpp_result = ::ohos::data::unifiedDataChannel::weak::Hyperlink(cpp_iface)->GetDescription();
    if (::taihe::has_error()) { return ani_string{}; }
    ani_string ani_result;
    env->String_NewUTF8(cpp_result.c_str(), cpp_result.size(), &ani_result);
    return ani_result;
}
static ani_long ohos_data_unifiedDataChannel_Hyperlink_GetInner_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Hyperlink;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/Hyperlink;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_Hyperlink_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_Hyperlink_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::Hyperlink cpp_iface = ::ohos::data::unifiedDataChannel::weak::Hyperlink({cpp_vtbl_ptr, cpp_data_ptr});
    int64_t cpp_result = ::ohos::data::unifiedDataChannel::weak::Hyperlink(cpp_iface)->GetInner();
    if (::taihe::has_error()) { return ani_long{}; }
    ani_long ani_result = (int64_t)cpp_result;
    return ani_result;
}
static void ohos_data_unifiedDataChannel_Hyperlink_static_finalize_ANIFunc4([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_class clazz, ani_long data_ptr) {
    ::taihe::data_holder(reinterpret_cast<DataBlockHead*>(data_ptr));
}
static ani_string ohos_data_unifiedDataChannel_PlainText_GetType_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/PlainText;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/PlainText;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_PlainText_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_PlainText_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::PlainText cpp_iface = ::ohos::data::unifiedDataChannel::weak::PlainText({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::string cpp_result = ::ohos::data::unifiedDataChannel::weak::PlainText(cpp_iface)->GetType();
    if (::taihe::has_error()) { return ani_string{}; }
    ani_string ani_result;
    env->String_NewUTF8(cpp_result.c_str(), cpp_result.size(), &ani_result);
    return ani_result;
}
static ani_ref ohos_data_unifiedDataChannel_PlainText_GetValue_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/PlainText;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/PlainText;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_PlainText_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_PlainText_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::PlainText cpp_iface = ::ohos::data::unifiedDataChannel::weak::PlainText({cpp_vtbl_ptr, cpp_data_ptr});
    ::ohos::data::unifiedDataChannel::ValueType cpp_result = ::ohos::data::unifiedDataChannel::weak::PlainText(cpp_iface)->GetValue();
    if (::taihe::has_error()) { return ani_ref{}; }
    ani_ref ani_result = ohos_data_unifiedDataChannel_ValueType_intoANI(env, cpp_result);
    return ani_result;
}
static ani_ref ohos_data_unifiedDataChannel_PlainText_GetDetails_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/PlainText;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/PlainText;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_PlainText_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_PlainText_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::PlainText cpp_iface = ::ohos::data::unifiedDataChannel::weak::PlainText({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::optional<::taihe::map<::taihe::string, ::taihe::string>> cpp_result = ::ohos::data::unifiedDataChannel::weak::PlainText(cpp_iface)->GetDetails();
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
static void ohos_data_unifiedDataChannel_PlainText_SetDetails_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object, ani_object ani_arg_details) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/PlainText;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/PlainText;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_PlainText_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_PlainText_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::PlainText cpp_iface = ::ohos::data::unifiedDataChannel::weak::PlainText({cpp_vtbl_ptr, cpp_data_ptr});
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
    ::ohos::data::unifiedDataChannel::weak::PlainText(cpp_iface)->SetDetails(cpp_arg_details);
}
static void ohos_data_unifiedDataChannel_PlainText_SetTextContent_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object, ani_string ani_arg_textContent) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/PlainText;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/PlainText;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_PlainText_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_PlainText_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::PlainText cpp_iface = ::ohos::data::unifiedDataChannel::weak::PlainText({cpp_vtbl_ptr, cpp_data_ptr});
    ani_size cpp_arg_textContent_len;
    env->String_GetUTF8Size(ani_arg_textContent, &cpp_arg_textContent_len);
    TString cpp_arg_textContent_tstr;
    char* cpp_arg_textContent_buf = tstr_initialize(&cpp_arg_textContent_tstr, cpp_arg_textContent_len + 1);
    env->String_GetUTF8(ani_arg_textContent, cpp_arg_textContent_buf, cpp_arg_textContent_len + 1, &cpp_arg_textContent_len);
    cpp_arg_textContent_buf[cpp_arg_textContent_len] = '\0';
    cpp_arg_textContent_tstr.length = cpp_arg_textContent_len;
    ::taihe::string cpp_arg_textContent = ::taihe::string(cpp_arg_textContent_tstr);
    ::ohos::data::unifiedDataChannel::weak::PlainText(cpp_iface)->SetTextContent(cpp_arg_textContent);
}
static ani_string ohos_data_unifiedDataChannel_PlainText_GetTextContent_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/PlainText;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/PlainText;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_PlainText_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_PlainText_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::PlainText cpp_iface = ::ohos::data::unifiedDataChannel::weak::PlainText({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::string cpp_result = ::ohos::data::unifiedDataChannel::weak::PlainText(cpp_iface)->GetTextContent();
    if (::taihe::has_error()) { return ani_string{}; }
    ani_string ani_result;
    env->String_NewUTF8(cpp_result.c_str(), cpp_result.size(), &ani_result);
    return ani_result;
}
static void ohos_data_unifiedDataChannel_PlainText_SetAbstract1_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object, ani_string ani_arg_abstract1) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/PlainText;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/PlainText;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_PlainText_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_PlainText_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::PlainText cpp_iface = ::ohos::data::unifiedDataChannel::weak::PlainText({cpp_vtbl_ptr, cpp_data_ptr});
    ani_size cpp_arg_abstract1_len;
    env->String_GetUTF8Size(ani_arg_abstract1, &cpp_arg_abstract1_len);
    TString cpp_arg_abstract1_tstr;
    char* cpp_arg_abstract1_buf = tstr_initialize(&cpp_arg_abstract1_tstr, cpp_arg_abstract1_len + 1);
    env->String_GetUTF8(ani_arg_abstract1, cpp_arg_abstract1_buf, cpp_arg_abstract1_len + 1, &cpp_arg_abstract1_len);
    cpp_arg_abstract1_buf[cpp_arg_abstract1_len] = '\0';
    cpp_arg_abstract1_tstr.length = cpp_arg_abstract1_len;
    ::taihe::string cpp_arg_abstract1 = ::taihe::string(cpp_arg_abstract1_tstr);
    ::ohos::data::unifiedDataChannel::weak::PlainText(cpp_iface)->SetAbstract1(cpp_arg_abstract1);
}
static ani_string ohos_data_unifiedDataChannel_PlainText_GetAbstract1_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/PlainText;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/PlainText;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_PlainText_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_PlainText_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::PlainText cpp_iface = ::ohos::data::unifiedDataChannel::weak::PlainText({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::string cpp_result = ::ohos::data::unifiedDataChannel::weak::PlainText(cpp_iface)->GetAbstract1();
    if (::taihe::has_error()) { return ani_string{}; }
    ani_string ani_result;
    env->String_NewUTF8(cpp_result.c_str(), cpp_result.size(), &ani_result);
    return ani_result;
}
static ani_long ohos_data_unifiedDataChannel_PlainText_GetInner_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/PlainText;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/PlainText;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_PlainText_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_PlainText_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::PlainText cpp_iface = ::ohos::data::unifiedDataChannel::weak::PlainText({cpp_vtbl_ptr, cpp_data_ptr});
    int64_t cpp_result = ::ohos::data::unifiedDataChannel::weak::PlainText(cpp_iface)->GetInner();
    if (::taihe::has_error()) { return ani_long{}; }
    ani_long ani_result = (int64_t)cpp_result;
    return ani_result;
}
static void ohos_data_unifiedDataChannel_PlainText_static_finalize_ANIFunc4([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_class clazz, ani_long data_ptr) {
    ::taihe::data_holder(reinterpret_cast<DataBlockHead*>(data_ptr));
}
static ani_string ohos_data_unifiedDataChannel_SystemDefinedRecord_GetType_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedRecord;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedRecord;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_SystemDefinedRecord_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedRecord_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedRecord cpp_iface = ::ohos::data::unifiedDataChannel::weak::SystemDefinedRecord({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::string cpp_result = ::ohos::data::unifiedDataChannel::weak::SystemDefinedRecord(cpp_iface)->GetType();
    if (::taihe::has_error()) { return ani_string{}; }
    ani_string ani_result;
    env->String_NewUTF8(cpp_result.c_str(), cpp_result.size(), &ani_result);
    return ani_result;
}
static ani_ref ohos_data_unifiedDataChannel_SystemDefinedRecord_GetValue_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedRecord;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedRecord;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_SystemDefinedRecord_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedRecord_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedRecord cpp_iface = ::ohos::data::unifiedDataChannel::weak::SystemDefinedRecord({cpp_vtbl_ptr, cpp_data_ptr});
    ::ohos::data::unifiedDataChannel::ValueType cpp_result = ::ohos::data::unifiedDataChannel::weak::SystemDefinedRecord(cpp_iface)->GetValue();
    if (::taihe::has_error()) { return ani_ref{}; }
    ani_ref ani_result = ohos_data_unifiedDataChannel_ValueType_intoANI(env, cpp_result);
    return ani_result;
}
static ani_ref ohos_data_unifiedDataChannel_SystemDefinedRecord_GetDetails_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedRecord;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedRecord;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_SystemDefinedRecord_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedRecord_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedRecord cpp_iface = ::ohos::data::unifiedDataChannel::weak::SystemDefinedRecord({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::optional<::taihe::map<::taihe::string, ::ohos::data::unifiedDataChannel::DetailsValue>> cpp_result = ::ohos::data::unifiedDataChannel::weak::SystemDefinedRecord(cpp_iface)->GetDetails();
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
static void ohos_data_unifiedDataChannel_SystemDefinedRecord_SetDetails_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object, ani_object ani_arg_details) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedRecord;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedRecord;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_SystemDefinedRecord_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedRecord_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedRecord cpp_iface = ::ohos::data::unifiedDataChannel::weak::SystemDefinedRecord({cpp_vtbl_ptr, cpp_data_ptr});
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
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedRecord(cpp_iface)->SetDetails(cpp_arg_details);
}
static ani_long ohos_data_unifiedDataChannel_SystemDefinedRecord_GetInner_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedRecord;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedRecord;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_SystemDefinedRecord_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedRecord_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedRecord cpp_iface = ::ohos::data::unifiedDataChannel::weak::SystemDefinedRecord({cpp_vtbl_ptr, cpp_data_ptr});
    int64_t cpp_result = ::ohos::data::unifiedDataChannel::weak::SystemDefinedRecord(cpp_iface)->GetInner();
    if (::taihe::has_error()) { return ani_long{}; }
    ani_long ani_result = (int64_t)cpp_result;
    return ani_result;
}
static void ohos_data_unifiedDataChannel_SystemDefinedRecord_static_finalize_ANIFunc4([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_class clazz, ani_long data_ptr) {
    ::taihe::data_holder(reinterpret_cast<DataBlockHead*>(data_ptr));
}
static ani_string ohos_data_unifiedDataChannel_SystemDefinedForm_GetType_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedForm;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedForm;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_SystemDefinedForm_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedForm_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedForm cpp_iface = ::ohos::data::unifiedDataChannel::weak::SystemDefinedForm({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::string cpp_result = ::ohos::data::unifiedDataChannel::weak::SystemDefinedForm(cpp_iface)->GetType();
    if (::taihe::has_error()) { return ani_string{}; }
    ani_string ani_result;
    env->String_NewUTF8(cpp_result.c_str(), cpp_result.size(), &ani_result);
    return ani_result;
}
static ani_ref ohos_data_unifiedDataChannel_SystemDefinedForm_GetValue_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedForm;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedForm;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_SystemDefinedForm_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedForm_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedForm cpp_iface = ::ohos::data::unifiedDataChannel::weak::SystemDefinedForm({cpp_vtbl_ptr, cpp_data_ptr});
    ::ohos::data::unifiedDataChannel::ValueType cpp_result = ::ohos::data::unifiedDataChannel::weak::SystemDefinedForm(cpp_iface)->GetValue();
    if (::taihe::has_error()) { return ani_ref{}; }
    ani_ref ani_result = ohos_data_unifiedDataChannel_ValueType_intoANI(env, cpp_result);
    return ani_result;
}
static ani_ref ohos_data_unifiedDataChannel_SystemDefinedForm_GetDetails_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedForm;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedForm;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_SystemDefinedForm_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedForm_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedForm cpp_iface = ::ohos::data::unifiedDataChannel::weak::SystemDefinedForm({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::optional<::taihe::map<::taihe::string, ::ohos::data::unifiedDataChannel::DetailsValue>> cpp_result = ::ohos::data::unifiedDataChannel::weak::SystemDefinedForm(cpp_iface)->GetDetails();
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
static void ohos_data_unifiedDataChannel_SystemDefinedForm_SetDetails_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object, ani_object ani_arg_details) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedForm;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedForm;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_SystemDefinedForm_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedForm_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedForm cpp_iface = ::ohos::data::unifiedDataChannel::weak::SystemDefinedForm({cpp_vtbl_ptr, cpp_data_ptr});
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
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedForm(cpp_iface)->SetDetails(cpp_arg_details);
}
static ani_double ohos_data_unifiedDataChannel_SystemDefinedForm_GetFormId_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedForm;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedForm;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_SystemDefinedForm_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedForm_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedForm cpp_iface = ::ohos::data::unifiedDataChannel::weak::SystemDefinedForm({cpp_vtbl_ptr, cpp_data_ptr});
    double cpp_result = ::ohos::data::unifiedDataChannel::weak::SystemDefinedForm(cpp_iface)->GetFormId();
    if (::taihe::has_error()) { return ani_double{}; }
    ani_double ani_result = (double)cpp_result;
    return ani_result;
}
static void ohos_data_unifiedDataChannel_SystemDefinedForm_SetFormId_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object, ani_double ani_arg_formId) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedForm;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedForm;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_SystemDefinedForm_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedForm_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedForm cpp_iface = ::ohos::data::unifiedDataChannel::weak::SystemDefinedForm({cpp_vtbl_ptr, cpp_data_ptr});
    double cpp_arg_formId = (double)ani_arg_formId;
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedForm(cpp_iface)->SetFormId(cpp_arg_formId);
}
static ani_string ohos_data_unifiedDataChannel_SystemDefinedForm_GetFormName_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedForm;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedForm;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_SystemDefinedForm_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedForm_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedForm cpp_iface = ::ohos::data::unifiedDataChannel::weak::SystemDefinedForm({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::string cpp_result = ::ohos::data::unifiedDataChannel::weak::SystemDefinedForm(cpp_iface)->GetFormName();
    if (::taihe::has_error()) { return ani_string{}; }
    ani_string ani_result;
    env->String_NewUTF8(cpp_result.c_str(), cpp_result.size(), &ani_result);
    return ani_result;
}
static void ohos_data_unifiedDataChannel_SystemDefinedForm_SetFormName_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object, ani_string ani_arg_formName) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedForm;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedForm;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_SystemDefinedForm_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedForm_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedForm cpp_iface = ::ohos::data::unifiedDataChannel::weak::SystemDefinedForm({cpp_vtbl_ptr, cpp_data_ptr});
    ani_size cpp_arg_formName_len;
    env->String_GetUTF8Size(ani_arg_formName, &cpp_arg_formName_len);
    TString cpp_arg_formName_tstr;
    char* cpp_arg_formName_buf = tstr_initialize(&cpp_arg_formName_tstr, cpp_arg_formName_len + 1);
    env->String_GetUTF8(ani_arg_formName, cpp_arg_formName_buf, cpp_arg_formName_len + 1, &cpp_arg_formName_len);
    cpp_arg_formName_buf[cpp_arg_formName_len] = '\0';
    cpp_arg_formName_tstr.length = cpp_arg_formName_len;
    ::taihe::string cpp_arg_formName = ::taihe::string(cpp_arg_formName_tstr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedForm(cpp_iface)->SetFormName(cpp_arg_formName);
}
static ani_string ohos_data_unifiedDataChannel_SystemDefinedForm_GetBundleName_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedForm;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedForm;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_SystemDefinedForm_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedForm_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedForm cpp_iface = ::ohos::data::unifiedDataChannel::weak::SystemDefinedForm({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::string cpp_result = ::ohos::data::unifiedDataChannel::weak::SystemDefinedForm(cpp_iface)->GetBundleName();
    if (::taihe::has_error()) { return ani_string{}; }
    ani_string ani_result;
    env->String_NewUTF8(cpp_result.c_str(), cpp_result.size(), &ani_result);
    return ani_result;
}
static void ohos_data_unifiedDataChannel_SystemDefinedForm_SetBundleName_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object, ani_string ani_arg_bundleName) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedForm;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedForm;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_SystemDefinedForm_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedForm_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedForm cpp_iface = ::ohos::data::unifiedDataChannel::weak::SystemDefinedForm({cpp_vtbl_ptr, cpp_data_ptr});
    ani_size cpp_arg_bundleName_len;
    env->String_GetUTF8Size(ani_arg_bundleName, &cpp_arg_bundleName_len);
    TString cpp_arg_bundleName_tstr;
    char* cpp_arg_bundleName_buf = tstr_initialize(&cpp_arg_bundleName_tstr, cpp_arg_bundleName_len + 1);
    env->String_GetUTF8(ani_arg_bundleName, cpp_arg_bundleName_buf, cpp_arg_bundleName_len + 1, &cpp_arg_bundleName_len);
    cpp_arg_bundleName_buf[cpp_arg_bundleName_len] = '\0';
    cpp_arg_bundleName_tstr.length = cpp_arg_bundleName_len;
    ::taihe::string cpp_arg_bundleName = ::taihe::string(cpp_arg_bundleName_tstr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedForm(cpp_iface)->SetBundleName(cpp_arg_bundleName);
}
static ani_string ohos_data_unifiedDataChannel_SystemDefinedForm_GetAbilityName_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedForm;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedForm;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_SystemDefinedForm_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedForm_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedForm cpp_iface = ::ohos::data::unifiedDataChannel::weak::SystemDefinedForm({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::string cpp_result = ::ohos::data::unifiedDataChannel::weak::SystemDefinedForm(cpp_iface)->GetAbilityName();
    if (::taihe::has_error()) { return ani_string{}; }
    ani_string ani_result;
    env->String_NewUTF8(cpp_result.c_str(), cpp_result.size(), &ani_result);
    return ani_result;
}
static void ohos_data_unifiedDataChannel_SystemDefinedForm_SetAbilityName_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object, ani_string ani_arg_abilityName) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedForm;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedForm;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_SystemDefinedForm_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedForm_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedForm cpp_iface = ::ohos::data::unifiedDataChannel::weak::SystemDefinedForm({cpp_vtbl_ptr, cpp_data_ptr});
    ani_size cpp_arg_abilityName_len;
    env->String_GetUTF8Size(ani_arg_abilityName, &cpp_arg_abilityName_len);
    TString cpp_arg_abilityName_tstr;
    char* cpp_arg_abilityName_buf = tstr_initialize(&cpp_arg_abilityName_tstr, cpp_arg_abilityName_len + 1);
    env->String_GetUTF8(ani_arg_abilityName, cpp_arg_abilityName_buf, cpp_arg_abilityName_len + 1, &cpp_arg_abilityName_len);
    cpp_arg_abilityName_buf[cpp_arg_abilityName_len] = '\0';
    cpp_arg_abilityName_tstr.length = cpp_arg_abilityName_len;
    ::taihe::string cpp_arg_abilityName = ::taihe::string(cpp_arg_abilityName_tstr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedForm(cpp_iface)->SetAbilityName(cpp_arg_abilityName);
}
static ani_string ohos_data_unifiedDataChannel_SystemDefinedForm_GetModule_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedForm;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedForm;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_SystemDefinedForm_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedForm_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedForm cpp_iface = ::ohos::data::unifiedDataChannel::weak::SystemDefinedForm({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::string cpp_result = ::ohos::data::unifiedDataChannel::weak::SystemDefinedForm(cpp_iface)->GetModule();
    if (::taihe::has_error()) { return ani_string{}; }
    ani_string ani_result;
    env->String_NewUTF8(cpp_result.c_str(), cpp_result.size(), &ani_result);
    return ani_result;
}
static void ohos_data_unifiedDataChannel_SystemDefinedForm_SetModule_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object, ani_string ani_arg_module) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedForm;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedForm;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_SystemDefinedForm_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedForm_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedForm cpp_iface = ::ohos::data::unifiedDataChannel::weak::SystemDefinedForm({cpp_vtbl_ptr, cpp_data_ptr});
    ani_size cpp_arg_module_len;
    env->String_GetUTF8Size(ani_arg_module, &cpp_arg_module_len);
    TString cpp_arg_module_tstr;
    char* cpp_arg_module_buf = tstr_initialize(&cpp_arg_module_tstr, cpp_arg_module_len + 1);
    env->String_GetUTF8(ani_arg_module, cpp_arg_module_buf, cpp_arg_module_len + 1, &cpp_arg_module_len);
    cpp_arg_module_buf[cpp_arg_module_len] = '\0';
    cpp_arg_module_tstr.length = cpp_arg_module_len;
    ::taihe::string cpp_arg_module = ::taihe::string(cpp_arg_module_tstr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedForm(cpp_iface)->SetModule(cpp_arg_module);
}
static ani_long ohos_data_unifiedDataChannel_SystemDefinedForm_GetInner_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedForm;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedForm;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_SystemDefinedForm_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedForm_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedForm cpp_iface = ::ohos::data::unifiedDataChannel::weak::SystemDefinedForm({cpp_vtbl_ptr, cpp_data_ptr});
    int64_t cpp_result = ::ohos::data::unifiedDataChannel::weak::SystemDefinedForm(cpp_iface)->GetInner();
    if (::taihe::has_error()) { return ani_long{}; }
    ani_long ani_result = (int64_t)cpp_result;
    return ani_result;
}
static void ohos_data_unifiedDataChannel_SystemDefinedForm_static_finalize_ANIFunc4([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_class clazz, ani_long data_ptr) {
    ::taihe::data_holder(reinterpret_cast<DataBlockHead*>(data_ptr));
}
static ani_string ohos_data_unifiedDataChannel_SystemDefinedAppItem_GetType_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedAppItem;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedAppItem;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_SystemDefinedAppItem_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedAppItem_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItem cpp_iface = ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItem({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::string cpp_result = ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItem(cpp_iface)->GetType();
    if (::taihe::has_error()) { return ani_string{}; }
    ani_string ani_result;
    env->String_NewUTF8(cpp_result.c_str(), cpp_result.size(), &ani_result);
    return ani_result;
}
static ani_ref ohos_data_unifiedDataChannel_SystemDefinedAppItem_GetValue_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedAppItem;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedAppItem;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_SystemDefinedAppItem_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedAppItem_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItem cpp_iface = ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItem({cpp_vtbl_ptr, cpp_data_ptr});
    ::ohos::data::unifiedDataChannel::ValueType cpp_result = ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItem(cpp_iface)->GetValue();
    if (::taihe::has_error()) { return ani_ref{}; }
    ani_ref ani_result = ohos_data_unifiedDataChannel_ValueType_intoANI(env, cpp_result);
    return ani_result;
}
static ani_ref ohos_data_unifiedDataChannel_SystemDefinedAppItem_GetDetails_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedAppItem;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedAppItem;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_SystemDefinedAppItem_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedAppItem_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItem cpp_iface = ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItem({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::optional<::taihe::map<::taihe::string, ::ohos::data::unifiedDataChannel::DetailsValue>> cpp_result = ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItem(cpp_iface)->GetDetails();
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
static void ohos_data_unifiedDataChannel_SystemDefinedAppItem_SetDetails_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object, ani_object ani_arg_details) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedAppItem;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedAppItem;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_SystemDefinedAppItem_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedAppItem_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItem cpp_iface = ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItem({cpp_vtbl_ptr, cpp_data_ptr});
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
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItem(cpp_iface)->SetDetails(cpp_arg_details);
}
static ani_string ohos_data_unifiedDataChannel_SystemDefinedAppItem_GetAppId_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedAppItem;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedAppItem;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_SystemDefinedAppItem_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedAppItem_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItem cpp_iface = ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItem({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::string cpp_result = ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItem(cpp_iface)->GetAppId();
    if (::taihe::has_error()) { return ani_string{}; }
    ani_string ani_result;
    env->String_NewUTF8(cpp_result.c_str(), cpp_result.size(), &ani_result);
    return ani_result;
}
static void ohos_data_unifiedDataChannel_SystemDefinedAppItem_SetAppId_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object, ani_string ani_arg_appId) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedAppItem;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedAppItem;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_SystemDefinedAppItem_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedAppItem_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItem cpp_iface = ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItem({cpp_vtbl_ptr, cpp_data_ptr});
    ani_size cpp_arg_appId_len;
    env->String_GetUTF8Size(ani_arg_appId, &cpp_arg_appId_len);
    TString cpp_arg_appId_tstr;
    char* cpp_arg_appId_buf = tstr_initialize(&cpp_arg_appId_tstr, cpp_arg_appId_len + 1);
    env->String_GetUTF8(ani_arg_appId, cpp_arg_appId_buf, cpp_arg_appId_len + 1, &cpp_arg_appId_len);
    cpp_arg_appId_buf[cpp_arg_appId_len] = '\0';
    cpp_arg_appId_tstr.length = cpp_arg_appId_len;
    ::taihe::string cpp_arg_appId = ::taihe::string(cpp_arg_appId_tstr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItem(cpp_iface)->SetAppId(cpp_arg_appId);
}
static ani_string ohos_data_unifiedDataChannel_SystemDefinedAppItem_GetAppName_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedAppItem;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedAppItem;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_SystemDefinedAppItem_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedAppItem_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItem cpp_iface = ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItem({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::string cpp_result = ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItem(cpp_iface)->GetAppName();
    if (::taihe::has_error()) { return ani_string{}; }
    ani_string ani_result;
    env->String_NewUTF8(cpp_result.c_str(), cpp_result.size(), &ani_result);
    return ani_result;
}
static void ohos_data_unifiedDataChannel_SystemDefinedAppItem_SetAppName_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object, ani_string ani_arg_appName) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedAppItem;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedAppItem;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_SystemDefinedAppItem_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedAppItem_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItem cpp_iface = ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItem({cpp_vtbl_ptr, cpp_data_ptr});
    ani_size cpp_arg_appName_len;
    env->String_GetUTF8Size(ani_arg_appName, &cpp_arg_appName_len);
    TString cpp_arg_appName_tstr;
    char* cpp_arg_appName_buf = tstr_initialize(&cpp_arg_appName_tstr, cpp_arg_appName_len + 1);
    env->String_GetUTF8(ani_arg_appName, cpp_arg_appName_buf, cpp_arg_appName_len + 1, &cpp_arg_appName_len);
    cpp_arg_appName_buf[cpp_arg_appName_len] = '\0';
    cpp_arg_appName_tstr.length = cpp_arg_appName_len;
    ::taihe::string cpp_arg_appName = ::taihe::string(cpp_arg_appName_tstr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItem(cpp_iface)->SetAppName(cpp_arg_appName);
}
static ani_string ohos_data_unifiedDataChannel_SystemDefinedAppItem_GetAppIconId_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedAppItem;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedAppItem;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_SystemDefinedAppItem_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedAppItem_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItem cpp_iface = ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItem({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::string cpp_result = ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItem(cpp_iface)->GetAppIconId();
    if (::taihe::has_error()) { return ani_string{}; }
    ani_string ani_result;
    env->String_NewUTF8(cpp_result.c_str(), cpp_result.size(), &ani_result);
    return ani_result;
}
static void ohos_data_unifiedDataChannel_SystemDefinedAppItem_SetAppIconId_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object, ani_string ani_arg_appIconId) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedAppItem;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedAppItem;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_SystemDefinedAppItem_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedAppItem_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItem cpp_iface = ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItem({cpp_vtbl_ptr, cpp_data_ptr});
    ani_size cpp_arg_appIconId_len;
    env->String_GetUTF8Size(ani_arg_appIconId, &cpp_arg_appIconId_len);
    TString cpp_arg_appIconId_tstr;
    char* cpp_arg_appIconId_buf = tstr_initialize(&cpp_arg_appIconId_tstr, cpp_arg_appIconId_len + 1);
    env->String_GetUTF8(ani_arg_appIconId, cpp_arg_appIconId_buf, cpp_arg_appIconId_len + 1, &cpp_arg_appIconId_len);
    cpp_arg_appIconId_buf[cpp_arg_appIconId_len] = '\0';
    cpp_arg_appIconId_tstr.length = cpp_arg_appIconId_len;
    ::taihe::string cpp_arg_appIconId = ::taihe::string(cpp_arg_appIconId_tstr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItem(cpp_iface)->SetAppIconId(cpp_arg_appIconId);
}
static ani_string ohos_data_unifiedDataChannel_SystemDefinedAppItem_GetAppLabelId_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedAppItem;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedAppItem;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_SystemDefinedAppItem_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedAppItem_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItem cpp_iface = ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItem({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::string cpp_result = ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItem(cpp_iface)->GetAppLabelId();
    if (::taihe::has_error()) { return ani_string{}; }
    ani_string ani_result;
    env->String_NewUTF8(cpp_result.c_str(), cpp_result.size(), &ani_result);
    return ani_result;
}
static void ohos_data_unifiedDataChannel_SystemDefinedAppItem_SetAppLabelId_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object, ani_string ani_arg_appLabelId) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedAppItem;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedAppItem;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_SystemDefinedAppItem_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedAppItem_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItem cpp_iface = ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItem({cpp_vtbl_ptr, cpp_data_ptr});
    ani_size cpp_arg_appLabelId_len;
    env->String_GetUTF8Size(ani_arg_appLabelId, &cpp_arg_appLabelId_len);
    TString cpp_arg_appLabelId_tstr;
    char* cpp_arg_appLabelId_buf = tstr_initialize(&cpp_arg_appLabelId_tstr, cpp_arg_appLabelId_len + 1);
    env->String_GetUTF8(ani_arg_appLabelId, cpp_arg_appLabelId_buf, cpp_arg_appLabelId_len + 1, &cpp_arg_appLabelId_len);
    cpp_arg_appLabelId_buf[cpp_arg_appLabelId_len] = '\0';
    cpp_arg_appLabelId_tstr.length = cpp_arg_appLabelId_len;
    ::taihe::string cpp_arg_appLabelId = ::taihe::string(cpp_arg_appLabelId_tstr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItem(cpp_iface)->SetAppLabelId(cpp_arg_appLabelId);
}
static ani_string ohos_data_unifiedDataChannel_SystemDefinedAppItem_GetBundleName_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedAppItem;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedAppItem;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_SystemDefinedAppItem_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedAppItem_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItem cpp_iface = ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItem({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::string cpp_result = ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItem(cpp_iface)->GetBundleName();
    if (::taihe::has_error()) { return ani_string{}; }
    ani_string ani_result;
    env->String_NewUTF8(cpp_result.c_str(), cpp_result.size(), &ani_result);
    return ani_result;
}
static void ohos_data_unifiedDataChannel_SystemDefinedAppItem_SetBundleName_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object, ani_string ani_arg_bundleName) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedAppItem;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedAppItem;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_SystemDefinedAppItem_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedAppItem_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItem cpp_iface = ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItem({cpp_vtbl_ptr, cpp_data_ptr});
    ani_size cpp_arg_bundleName_len;
    env->String_GetUTF8Size(ani_arg_bundleName, &cpp_arg_bundleName_len);
    TString cpp_arg_bundleName_tstr;
    char* cpp_arg_bundleName_buf = tstr_initialize(&cpp_arg_bundleName_tstr, cpp_arg_bundleName_len + 1);
    env->String_GetUTF8(ani_arg_bundleName, cpp_arg_bundleName_buf, cpp_arg_bundleName_len + 1, &cpp_arg_bundleName_len);
    cpp_arg_bundleName_buf[cpp_arg_bundleName_len] = '\0';
    cpp_arg_bundleName_tstr.length = cpp_arg_bundleName_len;
    ::taihe::string cpp_arg_bundleName = ::taihe::string(cpp_arg_bundleName_tstr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItem(cpp_iface)->SetBundleName(cpp_arg_bundleName);
}
static ani_string ohos_data_unifiedDataChannel_SystemDefinedAppItem_GetAbilityName_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedAppItem;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedAppItem;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_SystemDefinedAppItem_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedAppItem_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItem cpp_iface = ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItem({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::string cpp_result = ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItem(cpp_iface)->GetAbilityName();
    if (::taihe::has_error()) { return ani_string{}; }
    ani_string ani_result;
    env->String_NewUTF8(cpp_result.c_str(), cpp_result.size(), &ani_result);
    return ani_result;
}
static void ohos_data_unifiedDataChannel_SystemDefinedAppItem_SetAbilityName_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object, ani_string ani_arg_abilityName) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedAppItem;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedAppItem;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_SystemDefinedAppItem_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedAppItem_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItem cpp_iface = ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItem({cpp_vtbl_ptr, cpp_data_ptr});
    ani_size cpp_arg_abilityName_len;
    env->String_GetUTF8Size(ani_arg_abilityName, &cpp_arg_abilityName_len);
    TString cpp_arg_abilityName_tstr;
    char* cpp_arg_abilityName_buf = tstr_initialize(&cpp_arg_abilityName_tstr, cpp_arg_abilityName_len + 1);
    env->String_GetUTF8(ani_arg_abilityName, cpp_arg_abilityName_buf, cpp_arg_abilityName_len + 1, &cpp_arg_abilityName_len);
    cpp_arg_abilityName_buf[cpp_arg_abilityName_len] = '\0';
    cpp_arg_abilityName_tstr.length = cpp_arg_abilityName_len;
    ::taihe::string cpp_arg_abilityName = ::taihe::string(cpp_arg_abilityName_tstr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItem(cpp_iface)->SetAbilityName(cpp_arg_abilityName);
}
static ani_long ohos_data_unifiedDataChannel_SystemDefinedAppItem_GetInner_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedAppItem;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedAppItem;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_SystemDefinedAppItem_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedAppItem_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItem cpp_iface = ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItem({cpp_vtbl_ptr, cpp_data_ptr});
    int64_t cpp_result = ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItem(cpp_iface)->GetInner();
    if (::taihe::has_error()) { return ani_long{}; }
    ani_long ani_result = (int64_t)cpp_result;
    return ani_result;
}
static void ohos_data_unifiedDataChannel_SystemDefinedAppItem_static_finalize_ANIFunc4([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_class clazz, ani_long data_ptr) {
    ::taihe::data_holder(reinterpret_cast<DataBlockHead*>(data_ptr));
}
static ani_string ohos_data_unifiedDataChannel_SystemDefinedPixelMap_GetType_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedPixelMap;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedPixelMap;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_SystemDefinedPixelMap_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedPixelMap_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedPixelMap cpp_iface = ::ohos::data::unifiedDataChannel::weak::SystemDefinedPixelMap({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::string cpp_result = ::ohos::data::unifiedDataChannel::weak::SystemDefinedPixelMap(cpp_iface)->GetType();
    if (::taihe::has_error()) { return ani_string{}; }
    ani_string ani_result;
    env->String_NewUTF8(cpp_result.c_str(), cpp_result.size(), &ani_result);
    return ani_result;
}
static ani_ref ohos_data_unifiedDataChannel_SystemDefinedPixelMap_GetValue_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedPixelMap;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedPixelMap;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_SystemDefinedPixelMap_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedPixelMap_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedPixelMap cpp_iface = ::ohos::data::unifiedDataChannel::weak::SystemDefinedPixelMap({cpp_vtbl_ptr, cpp_data_ptr});
    ::ohos::data::unifiedDataChannel::ValueType cpp_result = ::ohos::data::unifiedDataChannel::weak::SystemDefinedPixelMap(cpp_iface)->GetValue();
    if (::taihe::has_error()) { return ani_ref{}; }
    ani_ref ani_result = ohos_data_unifiedDataChannel_ValueType_intoANI(env, cpp_result);
    return ani_result;
}
static ani_ref ohos_data_unifiedDataChannel_SystemDefinedPixelMap_GetDetails_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedPixelMap;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedPixelMap;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_SystemDefinedPixelMap_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedPixelMap_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedPixelMap cpp_iface = ::ohos::data::unifiedDataChannel::weak::SystemDefinedPixelMap({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::optional<::taihe::map<::taihe::string, ::ohos::data::unifiedDataChannel::DetailsValue>> cpp_result = ::ohos::data::unifiedDataChannel::weak::SystemDefinedPixelMap(cpp_iface)->GetDetails();
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
static void ohos_data_unifiedDataChannel_SystemDefinedPixelMap_SetDetails_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object, ani_object ani_arg_details) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedPixelMap;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedPixelMap;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_SystemDefinedPixelMap_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedPixelMap_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedPixelMap cpp_iface = ::ohos::data::unifiedDataChannel::weak::SystemDefinedPixelMap({cpp_vtbl_ptr, cpp_data_ptr});
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
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedPixelMap(cpp_iface)->SetDetails(cpp_arg_details);
}
static ani_ref ohos_data_unifiedDataChannel_SystemDefinedPixelMap_GetRawData_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedPixelMap;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedPixelMap;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_SystemDefinedPixelMap_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedPixelMap_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedPixelMap cpp_iface = ::ohos::data::unifiedDataChannel::weak::SystemDefinedPixelMap({cpp_vtbl_ptr, cpp_data_ptr});
    ::taihe::optional<::taihe::array<uint8_t>> cpp_result = ::ohos::data::unifiedDataChannel::weak::SystemDefinedPixelMap(cpp_iface)->GetRawData();
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
static void ohos_data_unifiedDataChannel_SystemDefinedPixelMap_SetRawData_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object, ani_object ani_arg_rawData) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedPixelMap;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedPixelMap;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_SystemDefinedPixelMap_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedPixelMap_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedPixelMap cpp_iface = ::ohos::data::unifiedDataChannel::weak::SystemDefinedPixelMap({cpp_vtbl_ptr, cpp_data_ptr});
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
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedPixelMap(cpp_iface)->SetRawData(cpp_arg_rawData);
}
static ani_long ohos_data_unifiedDataChannel_SystemDefinedPixelMap_GetInner_ANIFunc([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_object object) {
    ani_long ani_data_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedPixelMap;", "_data_ptr"), reinterpret_cast<ani_long*>(&ani_data_ptr));
    ani_long ani_vtbl_ptr;
    env->Object_GetField_Long(object, TH_ANI_FIND_CLASS_FIELD(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedPixelMap;", "_vtbl_ptr"), reinterpret_cast<ani_long*>(&ani_vtbl_ptr));
    DataBlockHead* cpp_data_ptr = reinterpret_cast<DataBlockHead*>(ani_data_ptr);
    ohos_data_unifiedDataChannel_SystemDefinedPixelMap_vtable* cpp_vtbl_ptr = reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedPixelMap_vtable*>(ani_vtbl_ptr);
    ::ohos::data::unifiedDataChannel::weak::SystemDefinedPixelMap cpp_iface = ::ohos::data::unifiedDataChannel::weak::SystemDefinedPixelMap({cpp_vtbl_ptr, cpp_data_ptr});
    int64_t cpp_result = ::ohos::data::unifiedDataChannel::weak::SystemDefinedPixelMap(cpp_iface)->GetInner();
    if (::taihe::has_error()) { return ani_long{}; }
    ani_long ani_result = (int64_t)cpp_result;
    return ani_result;
}
static void ohos_data_unifiedDataChannel_SystemDefinedPixelMap_static_finalize_ANIFunc4([[maybe_unused]] ani_env *env, [[maybe_unused]] ani_class clazz, ani_long data_ptr) {
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
            {"CreateFolder_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_CreateFolder_ANIFunc)},
            {"CreateAudio_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_CreateAudio_ANIFunc)},
            {"CreateVideo_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_CreateVideo_ANIFunc)},
            {"CreateImage_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_CreateImage_ANIFunc)},
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
        if (ANI_OK != env->FindClass("L@ohos/data/unifiedDataChannel/unifiedDataChannel/UnifiedData;", &ani_env)) {
            return ANI_ERROR;
        }
        ani_native_function methods[] = {
            {"AddRecord_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_UnifiedData_AddRecord_ANIFunc)},
            {"GetRecords_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_UnifiedData_GetRecords_ANIFunc)},
            {"GetInner_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_UnifiedData_GetInner_ANIFunc)},
            {"_finalize", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_UnifiedData_static_finalize_ANIFunc4)},
        };
        if (ANI_OK != env->Class_BindNativeMethods(ani_env, methods, sizeof(methods) / sizeof(ani_native_function))) {
            return ANI_ERROR;
        }
    }
    {
        ani_class ani_env;
        if (ANI_OK != env->FindClass("L@ohos/data/unifiedDataChannel/unifiedDataChannel/UnifiedRecord;", &ani_env)) {
            return ANI_ERROR;
        }
        ani_native_function methods[] = {
            {"GetType_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_UnifiedRecord_GetType_ANIFunc)},
            {"GetValue_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_UnifiedRecord_GetValue_ANIFunc)},
            {"GetInner_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_UnifiedRecord_GetInner_ANIFunc)},
            {"_finalize", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_UnifiedRecord_static_finalize_ANIFunc4)},
        };
        if (ANI_OK != env->Class_BindNativeMethods(ani_env, methods, sizeof(methods) / sizeof(ani_native_function))) {
            return ANI_ERROR;
        }
    }
    {
        ani_class ani_env;
        if (ANI_OK != env->FindClass("L@ohos/data/unifiedDataChannel/unifiedDataChannel/File;", &ani_env)) {
            return ANI_ERROR;
        }
        ani_native_function methods[] = {
            {"GetType_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_File_GetType_ANIFunc)},
            {"GetValue_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_File_GetValue_ANIFunc)},
            {"GetUri_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_File_GetUri_ANIFunc)},
            {"SetUri_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_File_SetUri_ANIFunc)},
            {"GetDetails_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_File_GetDetails_ANIFunc)},
            {"SetDetails_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_File_SetDetails_ANIFunc)},
            {"GetInner_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_File_GetInner_ANIFunc)},
            {"_finalize", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_File_static_finalize_ANIFunc4)},
        };
        if (ANI_OK != env->Class_BindNativeMethods(ani_env, methods, sizeof(methods) / sizeof(ani_native_function))) {
            return ANI_ERROR;
        }
    }
    {
        ani_class ani_env;
        if (ANI_OK != env->FindClass("L@ohos/data/unifiedDataChannel/unifiedDataChannel/Folder;", &ani_env)) {
            return ANI_ERROR;
        }
        ani_native_function methods[] = {
            {"GetType_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_Folder_GetType_ANIFunc)},
            {"GetValue_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_Folder_GetValue_ANIFunc)},
            {"GetUri_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_Folder_GetUri_ANIFunc)},
            {"SetUri_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_Folder_SetUri_ANIFunc)},
            {"GetDetails_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_Folder_GetDetails_ANIFunc)},
            {"SetDetails_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_Folder_SetDetails_ANIFunc)},
            {"GetFolderUri_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_Folder_GetFolderUri_ANIFunc)},
            {"SetFolderUri_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_Folder_SetFolderUri_ANIFunc)},
            {"GetInner_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_Folder_GetInner_ANIFunc)},
            {"_finalize", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_Folder_static_finalize_ANIFunc4)},
        };
        if (ANI_OK != env->Class_BindNativeMethods(ani_env, methods, sizeof(methods) / sizeof(ani_native_function))) {
            return ANI_ERROR;
        }
    }
    {
        ani_class ani_env;
        if (ANI_OK != env->FindClass("L@ohos/data/unifiedDataChannel/unifiedDataChannel/Audio;", &ani_env)) {
            return ANI_ERROR;
        }
        ani_native_function methods[] = {
            {"GetType_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_Audio_GetType_ANIFunc)},
            {"GetValue_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_Audio_GetValue_ANIFunc)},
            {"GetUri_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_Audio_GetUri_ANIFunc)},
            {"SetUri_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_Audio_SetUri_ANIFunc)},
            {"GetDetails_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_Audio_GetDetails_ANIFunc)},
            {"SetDetails_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_Audio_SetDetails_ANIFunc)},
            {"GetAudioUri_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_Audio_GetAudioUri_ANIFunc)},
            {"SetAudioUri_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_Audio_SetAudioUri_ANIFunc)},
            {"GetInner_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_Audio_GetInner_ANIFunc)},
            {"_finalize", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_Audio_static_finalize_ANIFunc4)},
        };
        if (ANI_OK != env->Class_BindNativeMethods(ani_env, methods, sizeof(methods) / sizeof(ani_native_function))) {
            return ANI_ERROR;
        }
    }
    {
        ani_class ani_env;
        if (ANI_OK != env->FindClass("L@ohos/data/unifiedDataChannel/unifiedDataChannel/Video;", &ani_env)) {
            return ANI_ERROR;
        }
        ani_native_function methods[] = {
            {"GetType_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_Video_GetType_ANIFunc)},
            {"GetValue_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_Video_GetValue_ANIFunc)},
            {"GetUri_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_Video_GetUri_ANIFunc)},
            {"SetUri_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_Video_SetUri_ANIFunc)},
            {"GetDetails_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_Video_GetDetails_ANIFunc)},
            {"SetDetails_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_Video_SetDetails_ANIFunc)},
            {"GetVideoUri_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_Video_GetVideoUri_ANIFunc)},
            {"SetVideoUri_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_Video_SetVideoUri_ANIFunc)},
            {"GetInner_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_Video_GetInner_ANIFunc)},
            {"_finalize", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_Video_static_finalize_ANIFunc4)},
        };
        if (ANI_OK != env->Class_BindNativeMethods(ani_env, methods, sizeof(methods) / sizeof(ani_native_function))) {
            return ANI_ERROR;
        }
    }
    {
        ani_class ani_env;
        if (ANI_OK != env->FindClass("L@ohos/data/unifiedDataChannel/unifiedDataChannel/Image;", &ani_env)) {
            return ANI_ERROR;
        }
        ani_native_function methods[] = {
            {"GetType_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_Image_GetType_ANIFunc)},
            {"GetValue_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_Image_GetValue_ANIFunc)},
            {"GetUri_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_Image_GetUri_ANIFunc)},
            {"SetUri_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_Image_SetUri_ANIFunc)},
            {"GetDetails_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_Image_GetDetails_ANIFunc)},
            {"SetDetails_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_Image_SetDetails_ANIFunc)},
            {"GetImageUri_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_Image_GetImageUri_ANIFunc)},
            {"SetImageUri_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_Image_SetImageUri_ANIFunc)},
            {"GetInner_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_Image_GetInner_ANIFunc)},
            {"_finalize", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_Image_static_finalize_ANIFunc4)},
        };
        if (ANI_OK != env->Class_BindNativeMethods(ani_env, methods, sizeof(methods) / sizeof(ani_native_function))) {
            return ANI_ERROR;
        }
    }
    {
        ani_class ani_env;
        if (ANI_OK != env->FindClass("L@ohos/data/unifiedDataChannel/unifiedDataChannel/Text;", &ani_env)) {
            return ANI_ERROR;
        }
        ani_native_function methods[] = {
            {"GetType_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_Text_GetType_ANIFunc)},
            {"GetValue_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_Text_GetValue_ANIFunc)},
            {"GetDetails_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_Text_GetDetails_ANIFunc)},
            {"SetDetails_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_Text_SetDetails_ANIFunc)},
            {"GetInner_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_Text_GetInner_ANIFunc)},
            {"_finalize", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_Text_static_finalize_ANIFunc4)},
        };
        if (ANI_OK != env->Class_BindNativeMethods(ani_env, methods, sizeof(methods) / sizeof(ani_native_function))) {
            return ANI_ERROR;
        }
    }
    {
        ani_class ani_env;
        if (ANI_OK != env->FindClass("L@ohos/data/unifiedDataChannel/unifiedDataChannel/HTML;", &ani_env)) {
            return ANI_ERROR;
        }
        ani_native_function methods[] = {
            {"GetType_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_HTML_GetType_ANIFunc)},
            {"GetValue_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_HTML_GetValue_ANIFunc)},
            {"GetDetails_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_HTML_GetDetails_ANIFunc)},
            {"SetDetails_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_HTML_SetDetails_ANIFunc)},
            {"SetHtmlContent_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_HTML_SetHtmlContent_ANIFunc)},
            {"GetHtmlContent_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_HTML_GetHtmlContent_ANIFunc)},
            {"SetPlainContent_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_HTML_SetPlainContent_ANIFunc)},
            {"GetPlainContent_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_HTML_GetPlainContent_ANIFunc)},
            {"GetInner_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_HTML_GetInner_ANIFunc)},
            {"_finalize", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_HTML_static_finalize_ANIFunc4)},
        };
        if (ANI_OK != env->Class_BindNativeMethods(ani_env, methods, sizeof(methods) / sizeof(ani_native_function))) {
            return ANI_ERROR;
        }
    }
    {
        ani_class ani_env;
        if (ANI_OK != env->FindClass("L@ohos/data/unifiedDataChannel/unifiedDataChannel/Hyperlink;", &ani_env)) {
            return ANI_ERROR;
        }
        ani_native_function methods[] = {
            {"GetType_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_Hyperlink_GetType_ANIFunc)},
            {"GetValue_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_Hyperlink_GetValue_ANIFunc)},
            {"GetDetails_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_Hyperlink_GetDetails_ANIFunc)},
            {"SetDetails_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_Hyperlink_SetDetails_ANIFunc)},
            {"SetUrl_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_Hyperlink_SetUrl_ANIFunc)},
            {"GetUrl_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_Hyperlink_GetUrl_ANIFunc)},
            {"SetDescription_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_Hyperlink_SetDescription_ANIFunc)},
            {"GetDescription_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_Hyperlink_GetDescription_ANIFunc)},
            {"GetInner_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_Hyperlink_GetInner_ANIFunc)},
            {"_finalize", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_Hyperlink_static_finalize_ANIFunc4)},
        };
        if (ANI_OK != env->Class_BindNativeMethods(ani_env, methods, sizeof(methods) / sizeof(ani_native_function))) {
            return ANI_ERROR;
        }
    }
    {
        ani_class ani_env;
        if (ANI_OK != env->FindClass("L@ohos/data/unifiedDataChannel/unifiedDataChannel/PlainText;", &ani_env)) {
            return ANI_ERROR;
        }
        ani_native_function methods[] = {
            {"GetType_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_PlainText_GetType_ANIFunc)},
            {"GetValue_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_PlainText_GetValue_ANIFunc)},
            {"GetDetails_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_PlainText_GetDetails_ANIFunc)},
            {"SetDetails_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_PlainText_SetDetails_ANIFunc)},
            {"SetTextContent_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_PlainText_SetTextContent_ANIFunc)},
            {"GetTextContent_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_PlainText_GetTextContent_ANIFunc)},
            {"SetAbstract1_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_PlainText_SetAbstract1_ANIFunc)},
            {"GetAbstract1_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_PlainText_GetAbstract1_ANIFunc)},
            {"GetInner_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_PlainText_GetInner_ANIFunc)},
            {"_finalize", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_PlainText_static_finalize_ANIFunc4)},
        };
        if (ANI_OK != env->Class_BindNativeMethods(ani_env, methods, sizeof(methods) / sizeof(ani_native_function))) {
            return ANI_ERROR;
        }
    }
    {
        ani_class ani_env;
        if (ANI_OK != env->FindClass("L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedRecord;", &ani_env)) {
            return ANI_ERROR;
        }
        ani_native_function methods[] = {
            {"GetType_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_SystemDefinedRecord_GetType_ANIFunc)},
            {"GetValue_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_SystemDefinedRecord_GetValue_ANIFunc)},
            {"GetDetails_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_SystemDefinedRecord_GetDetails_ANIFunc)},
            {"SetDetails_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_SystemDefinedRecord_SetDetails_ANIFunc)},
            {"GetInner_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_SystemDefinedRecord_GetInner_ANIFunc)},
            {"_finalize", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_SystemDefinedRecord_static_finalize_ANIFunc4)},
        };
        if (ANI_OK != env->Class_BindNativeMethods(ani_env, methods, sizeof(methods) / sizeof(ani_native_function))) {
            return ANI_ERROR;
        }
    }
    {
        ani_class ani_env;
        if (ANI_OK != env->FindClass("L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedForm;", &ani_env)) {
            return ANI_ERROR;
        }
        ani_native_function methods[] = {
            {"GetType_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_SystemDefinedForm_GetType_ANIFunc)},
            {"GetValue_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_SystemDefinedForm_GetValue_ANIFunc)},
            {"GetDetails_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_SystemDefinedForm_GetDetails_ANIFunc)},
            {"SetDetails_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_SystemDefinedForm_SetDetails_ANIFunc)},
            {"GetFormId_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_SystemDefinedForm_GetFormId_ANIFunc)},
            {"SetFormId_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_SystemDefinedForm_SetFormId_ANIFunc)},
            {"GetFormName_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_SystemDefinedForm_GetFormName_ANIFunc)},
            {"SetFormName_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_SystemDefinedForm_SetFormName_ANIFunc)},
            {"GetBundleName_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_SystemDefinedForm_GetBundleName_ANIFunc)},
            {"SetBundleName_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_SystemDefinedForm_SetBundleName_ANIFunc)},
            {"GetAbilityName_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_SystemDefinedForm_GetAbilityName_ANIFunc)},
            {"SetAbilityName_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_SystemDefinedForm_SetAbilityName_ANIFunc)},
            {"GetModule_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_SystemDefinedForm_GetModule_ANIFunc)},
            {"SetModule_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_SystemDefinedForm_SetModule_ANIFunc)},
            {"GetInner_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_SystemDefinedForm_GetInner_ANIFunc)},
            {"_finalize", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_SystemDefinedForm_static_finalize_ANIFunc4)},
        };
        if (ANI_OK != env->Class_BindNativeMethods(ani_env, methods, sizeof(methods) / sizeof(ani_native_function))) {
            return ANI_ERROR;
        }
    }
    {
        ani_class ani_env;
        if (ANI_OK != env->FindClass("L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedAppItem;", &ani_env)) {
            return ANI_ERROR;
        }
        ani_native_function methods[] = {
            {"GetType_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_SystemDefinedAppItem_GetType_ANIFunc)},
            {"GetValue_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_SystemDefinedAppItem_GetValue_ANIFunc)},
            {"GetDetails_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_SystemDefinedAppItem_GetDetails_ANIFunc)},
            {"SetDetails_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_SystemDefinedAppItem_SetDetails_ANIFunc)},
            {"GetAppId_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_SystemDefinedAppItem_GetAppId_ANIFunc)},
            {"SetAppId_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_SystemDefinedAppItem_SetAppId_ANIFunc)},
            {"GetAppName_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_SystemDefinedAppItem_GetAppName_ANIFunc)},
            {"SetAppName_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_SystemDefinedAppItem_SetAppName_ANIFunc)},
            {"GetAppIconId_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_SystemDefinedAppItem_GetAppIconId_ANIFunc)},
            {"SetAppIconId_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_SystemDefinedAppItem_SetAppIconId_ANIFunc)},
            {"GetAppLabelId_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_SystemDefinedAppItem_GetAppLabelId_ANIFunc)},
            {"SetAppLabelId_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_SystemDefinedAppItem_SetAppLabelId_ANIFunc)},
            {"GetBundleName_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_SystemDefinedAppItem_GetBundleName_ANIFunc)},
            {"SetBundleName_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_SystemDefinedAppItem_SetBundleName_ANIFunc)},
            {"GetAbilityName_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_SystemDefinedAppItem_GetAbilityName_ANIFunc)},
            {"SetAbilityName_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_SystemDefinedAppItem_SetAbilityName_ANIFunc)},
            {"GetInner_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_SystemDefinedAppItem_GetInner_ANIFunc)},
            {"_finalize", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_SystemDefinedAppItem_static_finalize_ANIFunc4)},
        };
        if (ANI_OK != env->Class_BindNativeMethods(ani_env, methods, sizeof(methods) / sizeof(ani_native_function))) {
            return ANI_ERROR;
        }
    }
    {
        ani_class ani_env;
        if (ANI_OK != env->FindClass("L@ohos/data/unifiedDataChannel/unifiedDataChannel/SystemDefinedPixelMap;", &ani_env)) {
            return ANI_ERROR;
        }
        ani_native_function methods[] = {
            {"GetType_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_SystemDefinedPixelMap_GetType_ANIFunc)},
            {"GetValue_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_SystemDefinedPixelMap_GetValue_ANIFunc)},
            {"GetDetails_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_SystemDefinedPixelMap_GetDetails_ANIFunc)},
            {"SetDetails_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_SystemDefinedPixelMap_SetDetails_ANIFunc)},
            {"GetRawData_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_SystemDefinedPixelMap_GetRawData_ANIFunc)},
            {"SetRawData_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_SystemDefinedPixelMap_SetRawData_ANIFunc)},
            {"GetInner_inner", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_SystemDefinedPixelMap_GetInner_ANIFunc)},
            {"_finalize", nullptr, reinterpret_cast<void*>(ohos_data_unifiedDataChannel_SystemDefinedPixelMap_static_finalize_ANIFunc4)},
        };
        if (ANI_OK != env->Class_BindNativeMethods(ani_env, methods, sizeof(methods) / sizeof(ani_native_function))) {
            return ANI_ERROR;
        }
    }
    return ANI_OK;
}
}
