#pragma once
#include "ohos.data.unifiedDataChannel.AllRecords.ani.0.h"
#include "ohos.data.unifiedDataChannel.AllRecords.proj.1.hpp"
#include "ohos.data.unifiedDataChannel.FileInner.ani.1.h"
#include "ohos.data.unifiedDataChannel.UnifiedRecordInner.ani.1.h"
inline ::ohos::data::unifiedDataChannel::AllRecords ohos_data_unifiedDataChannel_AllRecords_fromANI(ani_env* env, ani_ref ani_value) {
    ani_boolean ani_is_file;
    env->Object_InstanceOf(static_cast<ani_object>(ani_value), TH_ANI_FIND_CLASS(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/FileInner;"), &ani_is_file);
    if (ani_is_file) {
        ::ohos::data::unifiedDataChannel::FileInner cpp_field_file = ohos_data_unifiedDataChannel_FileInner_fromANI(env, static_cast<ani_object>(ani_value));
        return ::ohos::data::unifiedDataChannel::AllRecords(::taihe::static_tag<::ohos::data::unifiedDataChannel::AllRecords::tag_t::file>, std::move(cpp_field_file));
    }
    ani_boolean ani_is_unifiedRecord;
    env->Object_InstanceOf(static_cast<ani_object>(ani_value), TH_ANI_FIND_CLASS(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/UnifiedRecordInner;"), &ani_is_unifiedRecord);
    if (ani_is_unifiedRecord) {
        ::ohos::data::unifiedDataChannel::UnifiedRecordInner cpp_field_unifiedRecord = ohos_data_unifiedDataChannel_UnifiedRecordInner_fromANI(env, static_cast<ani_object>(ani_value));
        return ::ohos::data::unifiedDataChannel::AllRecords(::taihe::static_tag<::ohos::data::unifiedDataChannel::AllRecords::tag_t::unifiedRecord>, std::move(cpp_field_unifiedRecord));
    }
    __builtin_unreachable();
}
inline ani_ref ohos_data_unifiedDataChannel_AllRecords_intoANI(ani_env* env, ::ohos::data::unifiedDataChannel::AllRecords const& cpp_value) {
    ani_ref ani_value;
    switch (cpp_value.get_tag()) {
    case ::ohos::data::unifiedDataChannel::AllRecords::tag_t::file: {
        ani_object ani_field_file = ohos_data_unifiedDataChannel_FileInner_intoANI(env, cpp_value.get_file_ref());
        ani_value = ani_field_file;
        break;
    }
    case ::ohos::data::unifiedDataChannel::AllRecords::tag_t::unifiedRecord: {
        ani_object ani_field_unifiedRecord = ohos_data_unifiedDataChannel_UnifiedRecordInner_intoANI(env, cpp_value.get_unifiedRecord_ref());
        ani_value = ani_field_unifiedRecord;
        break;
    }
    }
    return ani_value;
}
