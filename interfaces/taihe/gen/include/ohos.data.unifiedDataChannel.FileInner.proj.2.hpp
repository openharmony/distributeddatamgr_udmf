#pragma once
#include "ohos.data.unifiedDataChannel.FileInner.proj.1.hpp"
#include "ohos.data.unifiedDataChannel.FileInner.abi.2.h"
#include "taihe/string.hpp"
#include "ohos.data.unifiedDataChannel.ValueType.proj.1.hpp"
#include "taihe/optional.hpp"
#include "taihe/map.hpp"
namespace ohos::data::unifiedDataChannel::weak {
inline ::taihe::string FileInner::virtual_type::GetType() const& {
    return ::taihe::from_abi<::taihe::string>(ohos_data_unifiedDataChannel_FileInner_GetType_f(*reinterpret_cast<ohos_data_unifiedDataChannel_FileInner_t const*>(this)));
}
}
namespace ohos::data::unifiedDataChannel::weak {
inline ::ohos::data::unifiedDataChannel::ValueType FileInner::virtual_type::GetValue() const& {
    return ::taihe::from_abi<::ohos::data::unifiedDataChannel::ValueType>(ohos_data_unifiedDataChannel_FileInner_GetValue_f(*reinterpret_cast<ohos_data_unifiedDataChannel_FileInner_t const*>(this)));
}
}
namespace ohos::data::unifiedDataChannel::weak {
inline ::taihe::string FileInner::virtual_type::GetUri() const& {
    return ::taihe::from_abi<::taihe::string>(ohos_data_unifiedDataChannel_FileInner_GetUri_f(*reinterpret_cast<ohos_data_unifiedDataChannel_FileInner_t const*>(this)));
}
}
namespace ohos::data::unifiedDataChannel::weak {
inline void FileInner::virtual_type::SetUri(::taihe::string_view uri) const& {
    return ohos_data_unifiedDataChannel_FileInner_SetUri_f(*reinterpret_cast<ohos_data_unifiedDataChannel_FileInner_t const*>(this), ::taihe::into_abi<::taihe::string_view>(uri));
}
}
namespace ohos::data::unifiedDataChannel::weak {
inline ::taihe::optional<::taihe::map<::taihe::string, ::taihe::string>> FileInner::virtual_type::GetDetails() const& {
    return ::taihe::from_abi<::taihe::optional<::taihe::map<::taihe::string, ::taihe::string>>>(ohos_data_unifiedDataChannel_FileInner_GetDetails_f(*reinterpret_cast<ohos_data_unifiedDataChannel_FileInner_t const*>(this)));
}
}
namespace ohos::data::unifiedDataChannel::weak {
inline void FileInner::virtual_type::SetDetails(::taihe::map_view<::taihe::string, ::taihe::string> details) const& {
    return ohos_data_unifiedDataChannel_FileInner_SetDetails_f(*reinterpret_cast<ohos_data_unifiedDataChannel_FileInner_t const*>(this), ::taihe::into_abi<::taihe::map_view<::taihe::string, ::taihe::string>>(details));
}
}
namespace ohos::data::unifiedDataChannel::weak {
inline int64_t FileInner::virtual_type::GetInner() const& {
    return ::taihe::from_abi<int64_t>(ohos_data_unifiedDataChannel_FileInner_GetInner_f(*reinterpret_cast<ohos_data_unifiedDataChannel_FileInner_t const*>(this)));
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
struct TString FileInner::methods_impl<Impl>::GetType(struct ohos_data_unifiedDataChannel_FileInner_t tobj) {
    return ::taihe::into_abi<::taihe::string>(::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->GetType());
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
struct ohos_data_unifiedDataChannel_ValueType_t FileInner::methods_impl<Impl>::GetValue(struct ohos_data_unifiedDataChannel_FileInner_t tobj) {
    return ::taihe::into_abi<::ohos::data::unifiedDataChannel::ValueType>(::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->GetValue());
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
struct TString FileInner::methods_impl<Impl>::GetUri(struct ohos_data_unifiedDataChannel_FileInner_t tobj) {
    return ::taihe::into_abi<::taihe::string>(::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->GetUri());
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
void FileInner::methods_impl<Impl>::SetUri(struct ohos_data_unifiedDataChannel_FileInner_t tobj, struct TString uri) {
    return ::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->SetUri(::taihe::from_abi<::taihe::string_view>(uri));
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
struct TOptional FileInner::methods_impl<Impl>::GetDetails(struct ohos_data_unifiedDataChannel_FileInner_t tobj) {
    return ::taihe::into_abi<::taihe::optional<::taihe::map<::taihe::string, ::taihe::string>>>(::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->GetDetails());
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
void FileInner::methods_impl<Impl>::SetDetails(struct ohos_data_unifiedDataChannel_FileInner_t tobj, void* details) {
    return ::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->SetDetails(::taihe::from_abi<::taihe::map_view<::taihe::string, ::taihe::string>>(details));
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
int64_t FileInner::methods_impl<Impl>::GetInner(struct ohos_data_unifiedDataChannel_FileInner_t tobj) {
    return ::taihe::into_abi<int64_t>(::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->GetInner());
}
}
