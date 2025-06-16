#pragma once
#include "ohos.data.unifiedDataChannel.VideoInner.proj.1.hpp"
#include "ohos.data.unifiedDataChannel.VideoInner.abi.2.h"
#include "taihe/string.hpp"
#include "ohos.data.unifiedDataChannel.ValueType.proj.1.hpp"
#include "taihe/optional.hpp"
#include "taihe/map.hpp"
namespace ohos::data::unifiedDataChannel::weak {
inline ::taihe::string VideoInner::virtual_type::GetType() const& {
    return ::taihe::from_abi<::taihe::string>(ohos_data_unifiedDataChannel_VideoInner_GetType_f(*reinterpret_cast<ohos_data_unifiedDataChannel_VideoInner_t const*>(this)));
}
}
namespace ohos::data::unifiedDataChannel::weak {
inline ::ohos::data::unifiedDataChannel::ValueType VideoInner::virtual_type::GetValue() const& {
    return ::taihe::from_abi<::ohos::data::unifiedDataChannel::ValueType>(ohos_data_unifiedDataChannel_VideoInner_GetValue_f(*reinterpret_cast<ohos_data_unifiedDataChannel_VideoInner_t const*>(this)));
}
}
namespace ohos::data::unifiedDataChannel::weak {
inline ::taihe::string VideoInner::virtual_type::GetUri() const& {
    return ::taihe::from_abi<::taihe::string>(ohos_data_unifiedDataChannel_VideoInner_GetUri_f(*reinterpret_cast<ohos_data_unifiedDataChannel_VideoInner_t const*>(this)));
}
}
namespace ohos::data::unifiedDataChannel::weak {
inline void VideoInner::virtual_type::SetUri(::taihe::string_view uri) const& {
    return ohos_data_unifiedDataChannel_VideoInner_SetUri_f(*reinterpret_cast<ohos_data_unifiedDataChannel_VideoInner_t const*>(this), ::taihe::into_abi<::taihe::string_view>(uri));
}
}
namespace ohos::data::unifiedDataChannel::weak {
inline ::taihe::optional<::taihe::map<::taihe::string, ::taihe::string>> VideoInner::virtual_type::GetDetails() const& {
    return ::taihe::from_abi<::taihe::optional<::taihe::map<::taihe::string, ::taihe::string>>>(ohos_data_unifiedDataChannel_VideoInner_GetDetails_f(*reinterpret_cast<ohos_data_unifiedDataChannel_VideoInner_t const*>(this)));
}
}
namespace ohos::data::unifiedDataChannel::weak {
inline void VideoInner::virtual_type::SetDetails(::taihe::map_view<::taihe::string, ::taihe::string> details) const& {
    return ohos_data_unifiedDataChannel_VideoInner_SetDetails_f(*reinterpret_cast<ohos_data_unifiedDataChannel_VideoInner_t const*>(this), ::taihe::into_abi<::taihe::map_view<::taihe::string, ::taihe::string>>(details));
}
}
namespace ohos::data::unifiedDataChannel::weak {
inline ::taihe::string VideoInner::virtual_type::GetVideoUri() const& {
    return ::taihe::from_abi<::taihe::string>(ohos_data_unifiedDataChannel_VideoInner_GetVideoUri_f(*reinterpret_cast<ohos_data_unifiedDataChannel_VideoInner_t const*>(this)));
}
}
namespace ohos::data::unifiedDataChannel::weak {
inline void VideoInner::virtual_type::SetVideoUri(::taihe::string_view videoUri) const& {
    return ohos_data_unifiedDataChannel_VideoInner_SetVideoUri_f(*reinterpret_cast<ohos_data_unifiedDataChannel_VideoInner_t const*>(this), ::taihe::into_abi<::taihe::string_view>(videoUri));
}
}
namespace ohos::data::unifiedDataChannel::weak {
inline int64_t VideoInner::virtual_type::GetInner() const& {
    return ::taihe::from_abi<int64_t>(ohos_data_unifiedDataChannel_VideoInner_GetInner_f(*reinterpret_cast<ohos_data_unifiedDataChannel_VideoInner_t const*>(this)));
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
struct TString VideoInner::methods_impl<Impl>::GetType(struct ohos_data_unifiedDataChannel_VideoInner_t tobj) {
    return ::taihe::into_abi<::taihe::string>(::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->GetType());
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
struct ohos_data_unifiedDataChannel_ValueType_t VideoInner::methods_impl<Impl>::GetValue(struct ohos_data_unifiedDataChannel_VideoInner_t tobj) {
    return ::taihe::into_abi<::ohos::data::unifiedDataChannel::ValueType>(::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->GetValue());
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
struct TString VideoInner::methods_impl<Impl>::GetUri(struct ohos_data_unifiedDataChannel_VideoInner_t tobj) {
    return ::taihe::into_abi<::taihe::string>(::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->GetUri());
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
void VideoInner::methods_impl<Impl>::SetUri(struct ohos_data_unifiedDataChannel_VideoInner_t tobj, struct TString uri) {
    return ::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->SetUri(::taihe::from_abi<::taihe::string_view>(uri));
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
struct TOptional VideoInner::methods_impl<Impl>::GetDetails(struct ohos_data_unifiedDataChannel_VideoInner_t tobj) {
    return ::taihe::into_abi<::taihe::optional<::taihe::map<::taihe::string, ::taihe::string>>>(::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->GetDetails());
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
void VideoInner::methods_impl<Impl>::SetDetails(struct ohos_data_unifiedDataChannel_VideoInner_t tobj, void* details) {
    return ::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->SetDetails(::taihe::from_abi<::taihe::map_view<::taihe::string, ::taihe::string>>(details));
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
struct TString VideoInner::methods_impl<Impl>::GetVideoUri(struct ohos_data_unifiedDataChannel_VideoInner_t tobj) {
    return ::taihe::into_abi<::taihe::string>(::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->GetVideoUri());
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
void VideoInner::methods_impl<Impl>::SetVideoUri(struct ohos_data_unifiedDataChannel_VideoInner_t tobj, struct TString videoUri) {
    return ::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->SetVideoUri(::taihe::from_abi<::taihe::string_view>(videoUri));
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
int64_t VideoInner::methods_impl<Impl>::GetInner(struct ohos_data_unifiedDataChannel_VideoInner_t tobj) {
    return ::taihe::into_abi<int64_t>(::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->GetInner());
}
}
