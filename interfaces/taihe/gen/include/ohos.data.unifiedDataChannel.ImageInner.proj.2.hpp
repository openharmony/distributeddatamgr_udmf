#pragma once
#include "ohos.data.unifiedDataChannel.ImageInner.proj.1.hpp"
#include "ohos.data.unifiedDataChannel.ImageInner.abi.2.h"
#include "taihe/string.hpp"
#include "ohos.data.unifiedDataChannel.ValueType.proj.1.hpp"
#include "taihe/optional.hpp"
#include "taihe/map.hpp"
namespace ohos::data::unifiedDataChannel::weak {
inline ::taihe::string ImageInner::virtual_type::GetType() const& {
    return ::taihe::from_abi<::taihe::string>(ohos_data_unifiedDataChannel_ImageInner_GetType_f(*reinterpret_cast<ohos_data_unifiedDataChannel_ImageInner_t const*>(this)));
}
}
namespace ohos::data::unifiedDataChannel::weak {
inline ::ohos::data::unifiedDataChannel::ValueType ImageInner::virtual_type::GetValue() const& {
    return ::taihe::from_abi<::ohos::data::unifiedDataChannel::ValueType>(ohos_data_unifiedDataChannel_ImageInner_GetValue_f(*reinterpret_cast<ohos_data_unifiedDataChannel_ImageInner_t const*>(this)));
}
}
namespace ohos::data::unifiedDataChannel::weak {
inline ::taihe::string ImageInner::virtual_type::GetUri() const& {
    return ::taihe::from_abi<::taihe::string>(ohos_data_unifiedDataChannel_ImageInner_GetUri_f(*reinterpret_cast<ohos_data_unifiedDataChannel_ImageInner_t const*>(this)));
}
}
namespace ohos::data::unifiedDataChannel::weak {
inline void ImageInner::virtual_type::SetUri(::taihe::string_view uri) const& {
    return ohos_data_unifiedDataChannel_ImageInner_SetUri_f(*reinterpret_cast<ohos_data_unifiedDataChannel_ImageInner_t const*>(this), ::taihe::into_abi<::taihe::string_view>(uri));
}
}
namespace ohos::data::unifiedDataChannel::weak {
inline ::taihe::optional<::taihe::map<::taihe::string, ::taihe::string>> ImageInner::virtual_type::GetDetails() const& {
    return ::taihe::from_abi<::taihe::optional<::taihe::map<::taihe::string, ::taihe::string>>>(ohos_data_unifiedDataChannel_ImageInner_GetDetails_f(*reinterpret_cast<ohos_data_unifiedDataChannel_ImageInner_t const*>(this)));
}
}
namespace ohos::data::unifiedDataChannel::weak {
inline void ImageInner::virtual_type::SetDetails(::taihe::map_view<::taihe::string, ::taihe::string> details) const& {
    return ohos_data_unifiedDataChannel_ImageInner_SetDetails_f(*reinterpret_cast<ohos_data_unifiedDataChannel_ImageInner_t const*>(this), ::taihe::into_abi<::taihe::map_view<::taihe::string, ::taihe::string>>(details));
}
}
namespace ohos::data::unifiedDataChannel::weak {
inline ::taihe::string ImageInner::virtual_type::GetImageUri() const& {
    return ::taihe::from_abi<::taihe::string>(ohos_data_unifiedDataChannel_ImageInner_GetImageUri_f(*reinterpret_cast<ohos_data_unifiedDataChannel_ImageInner_t const*>(this)));
}
}
namespace ohos::data::unifiedDataChannel::weak {
inline void ImageInner::virtual_type::SetImageUri(::taihe::string_view imageUri) const& {
    return ohos_data_unifiedDataChannel_ImageInner_SetImageUri_f(*reinterpret_cast<ohos_data_unifiedDataChannel_ImageInner_t const*>(this), ::taihe::into_abi<::taihe::string_view>(imageUri));
}
}
namespace ohos::data::unifiedDataChannel::weak {
inline int64_t ImageInner::virtual_type::GetInner() const& {
    return ::taihe::from_abi<int64_t>(ohos_data_unifiedDataChannel_ImageInner_GetInner_f(*reinterpret_cast<ohos_data_unifiedDataChannel_ImageInner_t const*>(this)));
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
struct TString ImageInner::methods_impl<Impl>::GetType(struct ohos_data_unifiedDataChannel_ImageInner_t tobj) {
    return ::taihe::into_abi<::taihe::string>(::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->GetType());
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
struct ohos_data_unifiedDataChannel_ValueType_t ImageInner::methods_impl<Impl>::GetValue(struct ohos_data_unifiedDataChannel_ImageInner_t tobj) {
    return ::taihe::into_abi<::ohos::data::unifiedDataChannel::ValueType>(::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->GetValue());
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
struct TString ImageInner::methods_impl<Impl>::GetUri(struct ohos_data_unifiedDataChannel_ImageInner_t tobj) {
    return ::taihe::into_abi<::taihe::string>(::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->GetUri());
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
void ImageInner::methods_impl<Impl>::SetUri(struct ohos_data_unifiedDataChannel_ImageInner_t tobj, struct TString uri) {
    return ::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->SetUri(::taihe::from_abi<::taihe::string_view>(uri));
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
struct TOptional ImageInner::methods_impl<Impl>::GetDetails(struct ohos_data_unifiedDataChannel_ImageInner_t tobj) {
    return ::taihe::into_abi<::taihe::optional<::taihe::map<::taihe::string, ::taihe::string>>>(::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->GetDetails());
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
void ImageInner::methods_impl<Impl>::SetDetails(struct ohos_data_unifiedDataChannel_ImageInner_t tobj, void* details) {
    return ::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->SetDetails(::taihe::from_abi<::taihe::map_view<::taihe::string, ::taihe::string>>(details));
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
struct TString ImageInner::methods_impl<Impl>::GetImageUri(struct ohos_data_unifiedDataChannel_ImageInner_t tobj) {
    return ::taihe::into_abi<::taihe::string>(::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->GetImageUri());
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
void ImageInner::methods_impl<Impl>::SetImageUri(struct ohos_data_unifiedDataChannel_ImageInner_t tobj, struct TString imageUri) {
    return ::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->SetImageUri(::taihe::from_abi<::taihe::string_view>(imageUri));
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
int64_t ImageInner::methods_impl<Impl>::GetInner(struct ohos_data_unifiedDataChannel_ImageInner_t tobj) {
    return ::taihe::into_abi<int64_t>(::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->GetInner());
}
}
