#pragma once
#include "ohos.data.unifiedDataChannel.SystemDefinedPixelMapInner.proj.1.hpp"
#include "ohos.data.unifiedDataChannel.SystemDefinedPixelMapInner.abi.2.h"
#include "taihe/string.hpp"
#include "ohos.data.unifiedDataChannel.ValueType.proj.1.hpp"
#include "taihe/optional.hpp"
#include "taihe/map.hpp"
#include "ohos.data.unifiedDataChannel.DetailsValue.proj.1.hpp"
#include "taihe/array.hpp"
namespace ohos::data::unifiedDataChannel::weak {
inline ::taihe::string SystemDefinedPixelMapInner::virtual_type::GetType() const& {
    return ::taihe::from_abi<::taihe::string>(ohos_data_unifiedDataChannel_SystemDefinedPixelMapInner_GetType_f(*reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedPixelMapInner_t const*>(this)));
}
}
namespace ohos::data::unifiedDataChannel::weak {
inline ::ohos::data::unifiedDataChannel::ValueType SystemDefinedPixelMapInner::virtual_type::GetValue() const& {
    return ::taihe::from_abi<::ohos::data::unifiedDataChannel::ValueType>(ohos_data_unifiedDataChannel_SystemDefinedPixelMapInner_GetValue_f(*reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedPixelMapInner_t const*>(this)));
}
}
namespace ohos::data::unifiedDataChannel::weak {
inline ::taihe::optional<::taihe::map<::taihe::string, ::ohos::data::unifiedDataChannel::DetailsValue>> SystemDefinedPixelMapInner::virtual_type::GetDetails() const& {
    return ::taihe::from_abi<::taihe::optional<::taihe::map<::taihe::string, ::ohos::data::unifiedDataChannel::DetailsValue>>>(ohos_data_unifiedDataChannel_SystemDefinedPixelMapInner_GetDetails_f(*reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedPixelMapInner_t const*>(this)));
}
}
namespace ohos::data::unifiedDataChannel::weak {
inline void SystemDefinedPixelMapInner::virtual_type::SetDetails(::taihe::map_view<::taihe::string, ::ohos::data::unifiedDataChannel::DetailsValue> details) const& {
    return ohos_data_unifiedDataChannel_SystemDefinedPixelMapInner_SetDetails_f(*reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedPixelMapInner_t const*>(this), ::taihe::into_abi<::taihe::map_view<::taihe::string, ::ohos::data::unifiedDataChannel::DetailsValue>>(details));
}
}
namespace ohos::data::unifiedDataChannel::weak {
inline ::taihe::optional<::taihe::array<uint8_t>> SystemDefinedPixelMapInner::virtual_type::GetRawData() const& {
    return ::taihe::from_abi<::taihe::optional<::taihe::array<uint8_t>>>(ohos_data_unifiedDataChannel_SystemDefinedPixelMapInner_GetRawData_f(*reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedPixelMapInner_t const*>(this)));
}
}
namespace ohos::data::unifiedDataChannel::weak {
inline void SystemDefinedPixelMapInner::virtual_type::SetRawData(::taihe::array_view<uint8_t> rawData) const& {
    return ohos_data_unifiedDataChannel_SystemDefinedPixelMapInner_SetRawData_f(*reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedPixelMapInner_t const*>(this), ::taihe::into_abi<::taihe::array_view<uint8_t>>(rawData));
}
}
namespace ohos::data::unifiedDataChannel::weak {
inline int64_t SystemDefinedPixelMapInner::virtual_type::GetInner() const& {
    return ::taihe::from_abi<int64_t>(ohos_data_unifiedDataChannel_SystemDefinedPixelMapInner_GetInner_f(*reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedPixelMapInner_t const*>(this)));
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
struct TString SystemDefinedPixelMapInner::methods_impl<Impl>::GetType(struct ohos_data_unifiedDataChannel_SystemDefinedPixelMapInner_t tobj) {
    return ::taihe::into_abi<::taihe::string>(::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->GetType());
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
struct ohos_data_unifiedDataChannel_ValueType_t SystemDefinedPixelMapInner::methods_impl<Impl>::GetValue(struct ohos_data_unifiedDataChannel_SystemDefinedPixelMapInner_t tobj) {
    return ::taihe::into_abi<::ohos::data::unifiedDataChannel::ValueType>(::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->GetValue());
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
struct TOptional SystemDefinedPixelMapInner::methods_impl<Impl>::GetDetails(struct ohos_data_unifiedDataChannel_SystemDefinedPixelMapInner_t tobj) {
    return ::taihe::into_abi<::taihe::optional<::taihe::map<::taihe::string, ::ohos::data::unifiedDataChannel::DetailsValue>>>(::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->GetDetails());
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
void SystemDefinedPixelMapInner::methods_impl<Impl>::SetDetails(struct ohos_data_unifiedDataChannel_SystemDefinedPixelMapInner_t tobj, void* details) {
    return ::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->SetDetails(::taihe::from_abi<::taihe::map_view<::taihe::string, ::ohos::data::unifiedDataChannel::DetailsValue>>(details));
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
struct TOptional SystemDefinedPixelMapInner::methods_impl<Impl>::GetRawData(struct ohos_data_unifiedDataChannel_SystemDefinedPixelMapInner_t tobj) {
    return ::taihe::into_abi<::taihe::optional<::taihe::array<uint8_t>>>(::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->GetRawData());
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
void SystemDefinedPixelMapInner::methods_impl<Impl>::SetRawData(struct ohos_data_unifiedDataChannel_SystemDefinedPixelMapInner_t tobj, struct TArray rawData) {
    return ::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->SetRawData(::taihe::from_abi<::taihe::array_view<uint8_t>>(rawData));
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
int64_t SystemDefinedPixelMapInner::methods_impl<Impl>::GetInner(struct ohos_data_unifiedDataChannel_SystemDefinedPixelMapInner_t tobj) {
    return ::taihe::into_abi<int64_t>(::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->GetInner());
}
}
