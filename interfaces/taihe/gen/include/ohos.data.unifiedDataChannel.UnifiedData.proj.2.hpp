#pragma once
#include "ohos.data.unifiedDataChannel.UnifiedData.proj.1.hpp"
#include "ohos.data.unifiedDataChannel.UnifiedData.abi.2.h"
#include "ohos.data.unifiedDataChannel.UnifiedRecord.proj.2.hpp"
#include "taihe/array.hpp"
namespace ohos::data::unifiedDataChannel::weak {
inline void UnifiedData::virtual_type::AddRecord(::ohos::data::unifiedDataChannel::weak::UnifiedRecord unifiedRecord) const& {
    return ohos_data_unifiedDataChannel_UnifiedData_AddRecord_f(*reinterpret_cast<ohos_data_unifiedDataChannel_UnifiedData_t const*>(this), ::taihe::into_abi<::ohos::data::unifiedDataChannel::weak::UnifiedRecord>(unifiedRecord));
}
}
namespace ohos::data::unifiedDataChannel::weak {
inline ::taihe::array<::ohos::data::unifiedDataChannel::UnifiedRecord> UnifiedData::virtual_type::GetRecords() const& {
    return ::taihe::from_abi<::taihe::array<::ohos::data::unifiedDataChannel::UnifiedRecord>>(ohos_data_unifiedDataChannel_UnifiedData_GetRecords_f(*reinterpret_cast<ohos_data_unifiedDataChannel_UnifiedData_t const*>(this)));
}
}
namespace ohos::data::unifiedDataChannel::weak {
inline int64_t UnifiedData::virtual_type::GetInner() const& {
    return ::taihe::from_abi<int64_t>(ohos_data_unifiedDataChannel_UnifiedData_GetInner_f(*reinterpret_cast<ohos_data_unifiedDataChannel_UnifiedData_t const*>(this)));
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
void UnifiedData::methods_impl<Impl>::AddRecord(struct ohos_data_unifiedDataChannel_UnifiedData_t tobj, struct ohos_data_unifiedDataChannel_UnifiedRecord_t unifiedRecord) {
    return ::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->AddRecord(::taihe::from_abi<::ohos::data::unifiedDataChannel::weak::UnifiedRecord>(unifiedRecord));
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
struct TArray UnifiedData::methods_impl<Impl>::GetRecords(struct ohos_data_unifiedDataChannel_UnifiedData_t tobj) {
    return ::taihe::into_abi<::taihe::array<::ohos::data::unifiedDataChannel::UnifiedRecord>>(::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->GetRecords());
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
int64_t UnifiedData::methods_impl<Impl>::GetInner(struct ohos_data_unifiedDataChannel_UnifiedData_t tobj) {
    return ::taihe::into_abi<int64_t>(::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->GetInner());
}
}
