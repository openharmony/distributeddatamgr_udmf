#pragma once
#include "ohos.data.unifiedDataChannel.UnifiedDataOrNull.ani.0.h"
#include "ohos.data.unifiedDataChannel.UnifiedDataOrNull.proj.1.hpp"
#include "ohos.data.unifiedDataChannel.UnifiedDataInner.ani.1.h"
inline ::ohos::data::unifiedDataChannel::UnifiedDataOrNull ohos_data_unifiedDataChannel_UnifiedDataOrNull_fromANI(ani_env* env, ani_ref ani_value) {
    ani_boolean ani_is_nullType;
    env->Reference_IsNull(ani_value, &ani_is_nullType);
    if (ani_is_nullType) {
        return ::ohos::data::unifiedDataChannel::UnifiedDataOrNull(::taihe::static_tag<::ohos::data::unifiedDataChannel::UnifiedDataOrNull::tag_t::nullType>);
    }
    ani_boolean ani_is_unifiedData;
    env->Object_InstanceOf(static_cast<ani_object>(ani_value), TH_ANI_FIND_CLASS(env, "L@ohos/data/unifiedDataChannel/unifiedDataChannel/UnifiedDataInner;"), &ani_is_unifiedData);
    if (ani_is_unifiedData) {
        ::ohos::data::unifiedDataChannel::UnifiedDataInner cpp_field_unifiedData = ohos_data_unifiedDataChannel_UnifiedDataInner_fromANI(env, static_cast<ani_object>(ani_value));
        return ::ohos::data::unifiedDataChannel::UnifiedDataOrNull(::taihe::static_tag<::ohos::data::unifiedDataChannel::UnifiedDataOrNull::tag_t::unifiedData>, std::move(cpp_field_unifiedData));
    }
    __builtin_unreachable();
}
inline ani_ref ohos_data_unifiedDataChannel_UnifiedDataOrNull_intoANI(ani_env* env, ::ohos::data::unifiedDataChannel::UnifiedDataOrNull const& cpp_value) {
    ani_ref ani_value;
    switch (cpp_value.get_tag()) {
    case ::ohos::data::unifiedDataChannel::UnifiedDataOrNull::tag_t::unifiedData: {
        ani_object ani_field_unifiedData = ohos_data_unifiedDataChannel_UnifiedDataInner_intoANI(env, cpp_value.get_unifiedData_ref());
        ani_value = ani_field_unifiedData;
        break;
    }
    case ::ohos::data::unifiedDataChannel::UnifiedDataOrNull::tag_t::nullType: {
        env->GetNull(&ani_value);
        break;
    }
    }
    return ani_value;
}
