#pragma once
#include "ohos.data.unifiedDataChannel.UnifiedDataInner.proj.1.hpp"
#include "ohos.data.unifiedDataChannel.UnifiedDataInner.abi.2.h"
#include "ohos.data.unifiedDataChannel.AllRecords.proj.1.hpp"
#include "taihe/array.hpp"
namespace ohos::data::unifiedDataChannel::weak {
inline void UnifiedDataInner::virtual_type::AddRecord(::ohos::data::unifiedDataChannel::AllRecords const& unifiedRecord) const& {
    return ohos_data_unifiedDataChannel_UnifiedDataInner_AddRecord_f(*reinterpret_cast<ohos_data_unifiedDataChannel_UnifiedDataInner_t const*>(this), ::taihe::into_abi<::ohos::data::unifiedDataChannel::AllRecords const&>(unifiedRecord));
}
}
namespace ohos::data::unifiedDataChannel::weak {
inline ::taihe::array<::ohos::data::unifiedDataChannel::AllRecords> UnifiedDataInner::virtual_type::GetRecords() const& {
    return ::taihe::from_abi<::taihe::array<::ohos::data::unifiedDataChannel::AllRecords>>(ohos_data_unifiedDataChannel_UnifiedDataInner_GetRecords_f(*reinterpret_cast<ohos_data_unifiedDataChannel_UnifiedDataInner_t const*>(this)));
}
}
namespace ohos::data::unifiedDataChannel::weak {
inline int64_t UnifiedDataInner::virtual_type::GetInner() const& {
    return ::taihe::from_abi<int64_t>(ohos_data_unifiedDataChannel_UnifiedDataInner_GetInner_f(*reinterpret_cast<ohos_data_unifiedDataChannel_UnifiedDataInner_t const*>(this)));
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
void UnifiedDataInner::methods_impl<Impl>::AddRecord(struct ohos_data_unifiedDataChannel_UnifiedDataInner_t tobj, struct ohos_data_unifiedDataChannel_AllRecords_t const* unifiedRecord) {
    return ::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->AddRecord(::taihe::from_abi<::ohos::data::unifiedDataChannel::AllRecords const&>(unifiedRecord));
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
struct TArray UnifiedDataInner::methods_impl<Impl>::GetRecords(struct ohos_data_unifiedDataChannel_UnifiedDataInner_t tobj) {
    return ::taihe::into_abi<::taihe::array<::ohos::data::unifiedDataChannel::AllRecords>>(::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->GetRecords());
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
int64_t UnifiedDataInner::methods_impl<Impl>::GetInner(struct ohos_data_unifiedDataChannel_UnifiedDataInner_t tobj) {
    return ::taihe::into_abi<int64_t>(::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->GetInner());
}
}
