#pragma once
#include "ohos.data.unifiedDataChannel.UnifiedRecordInner.proj.1.hpp"
#include "ohos.data.unifiedDataChannel.UnifiedRecordInner.abi.2.h"
#include "taihe/string.hpp"
#include "ohos.data.unifiedDataChannel.ValueType.proj.1.hpp"
namespace ohos::data::unifiedDataChannel::weak {
inline ::taihe::string UnifiedRecordInner::virtual_type::GetType() const& {
    return ::taihe::from_abi<::taihe::string>(ohos_data_unifiedDataChannel_UnifiedRecordInner_GetType_f(*reinterpret_cast<ohos_data_unifiedDataChannel_UnifiedRecordInner_t const*>(this)));
}
}
namespace ohos::data::unifiedDataChannel::weak {
inline ::ohos::data::unifiedDataChannel::ValueType UnifiedRecordInner::virtual_type::GetValue() const& {
    return ::taihe::from_abi<::ohos::data::unifiedDataChannel::ValueType>(ohos_data_unifiedDataChannel_UnifiedRecordInner_GetValue_f(*reinterpret_cast<ohos_data_unifiedDataChannel_UnifiedRecordInner_t const*>(this)));
}
}
namespace ohos::data::unifiedDataChannel::weak {
inline int64_t UnifiedRecordInner::virtual_type::GetInner() const& {
    return ::taihe::from_abi<int64_t>(ohos_data_unifiedDataChannel_UnifiedRecordInner_GetInner_f(*reinterpret_cast<ohos_data_unifiedDataChannel_UnifiedRecordInner_t const*>(this)));
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
struct TString UnifiedRecordInner::methods_impl<Impl>::GetType(struct ohos_data_unifiedDataChannel_UnifiedRecordInner_t tobj) {
    return ::taihe::into_abi<::taihe::string>(::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->GetType());
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
struct ohos_data_unifiedDataChannel_ValueType_t UnifiedRecordInner::methods_impl<Impl>::GetValue(struct ohos_data_unifiedDataChannel_UnifiedRecordInner_t tobj) {
    return ::taihe::into_abi<::ohos::data::unifiedDataChannel::ValueType>(::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->GetValue());
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
int64_t UnifiedRecordInner::methods_impl<Impl>::GetInner(struct ohos_data_unifiedDataChannel_UnifiedRecordInner_t tobj) {
    return ::taihe::into_abi<int64_t>(::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->GetInner());
}
}
