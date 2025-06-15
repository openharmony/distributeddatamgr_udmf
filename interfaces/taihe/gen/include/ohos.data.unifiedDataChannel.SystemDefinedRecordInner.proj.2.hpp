#pragma once
#include "ohos.data.unifiedDataChannel.SystemDefinedRecordInner.proj.1.hpp"
#include "ohos.data.unifiedDataChannel.SystemDefinedRecordInner.abi.2.h"
#include "taihe/string.hpp"
#include "ohos.data.unifiedDataChannel.ValueType.proj.1.hpp"
#include "taihe/optional.hpp"
#include "taihe/map.hpp"
#include "ohos.data.unifiedDataChannel.DetailsValue.proj.1.hpp"
namespace ohos::data::unifiedDataChannel::weak {
inline ::taihe::string SystemDefinedRecordInner::virtual_type::GetType() const& {
    return ::taihe::from_abi<::taihe::string>(ohos_data_unifiedDataChannel_SystemDefinedRecordInner_GetType_f(*reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedRecordInner_t const*>(this)));
}
}
namespace ohos::data::unifiedDataChannel::weak {
inline ::ohos::data::unifiedDataChannel::ValueType SystemDefinedRecordInner::virtual_type::GetValue() const& {
    return ::taihe::from_abi<::ohos::data::unifiedDataChannel::ValueType>(ohos_data_unifiedDataChannel_SystemDefinedRecordInner_GetValue_f(*reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedRecordInner_t const*>(this)));
}
}
namespace ohos::data::unifiedDataChannel::weak {
inline ::taihe::optional<::taihe::map<::taihe::string, ::ohos::data::unifiedDataChannel::DetailsValue>> SystemDefinedRecordInner::virtual_type::GetDetails() const& {
    return ::taihe::from_abi<::taihe::optional<::taihe::map<::taihe::string, ::ohos::data::unifiedDataChannel::DetailsValue>>>(ohos_data_unifiedDataChannel_SystemDefinedRecordInner_GetDetails_f(*reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedRecordInner_t const*>(this)));
}
}
namespace ohos::data::unifiedDataChannel::weak {
inline void SystemDefinedRecordInner::virtual_type::SetDetails(::taihe::map_view<::taihe::string, ::ohos::data::unifiedDataChannel::DetailsValue> details) const& {
    return ohos_data_unifiedDataChannel_SystemDefinedRecordInner_SetDetails_f(*reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedRecordInner_t const*>(this), ::taihe::into_abi<::taihe::map_view<::taihe::string, ::ohos::data::unifiedDataChannel::DetailsValue>>(details));
}
}
namespace ohos::data::unifiedDataChannel::weak {
inline int64_t SystemDefinedRecordInner::virtual_type::GetInner() const& {
    return ::taihe::from_abi<int64_t>(ohos_data_unifiedDataChannel_SystemDefinedRecordInner_GetInner_f(*reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedRecordInner_t const*>(this)));
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
struct TString SystemDefinedRecordInner::methods_impl<Impl>::GetType(struct ohos_data_unifiedDataChannel_SystemDefinedRecordInner_t tobj) {
    return ::taihe::into_abi<::taihe::string>(::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->GetType());
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
struct ohos_data_unifiedDataChannel_ValueType_t SystemDefinedRecordInner::methods_impl<Impl>::GetValue(struct ohos_data_unifiedDataChannel_SystemDefinedRecordInner_t tobj) {
    return ::taihe::into_abi<::ohos::data::unifiedDataChannel::ValueType>(::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->GetValue());
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
struct TOptional SystemDefinedRecordInner::methods_impl<Impl>::GetDetails(struct ohos_data_unifiedDataChannel_SystemDefinedRecordInner_t tobj) {
    return ::taihe::into_abi<::taihe::optional<::taihe::map<::taihe::string, ::ohos::data::unifiedDataChannel::DetailsValue>>>(::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->GetDetails());
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
void SystemDefinedRecordInner::methods_impl<Impl>::SetDetails(struct ohos_data_unifiedDataChannel_SystemDefinedRecordInner_t tobj, void* details) {
    return ::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->SetDetails(::taihe::from_abi<::taihe::map_view<::taihe::string, ::ohos::data::unifiedDataChannel::DetailsValue>>(details));
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
int64_t SystemDefinedRecordInner::methods_impl<Impl>::GetInner(struct ohos_data_unifiedDataChannel_SystemDefinedRecordInner_t tobj) {
    return ::taihe::into_abi<int64_t>(::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->GetInner());
}
}
