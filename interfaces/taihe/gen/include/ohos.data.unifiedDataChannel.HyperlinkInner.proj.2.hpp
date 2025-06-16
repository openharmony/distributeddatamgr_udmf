#pragma once
#include "ohos.data.unifiedDataChannel.HyperlinkInner.proj.1.hpp"
#include "ohos.data.unifiedDataChannel.HyperlinkInner.abi.2.h"
#include "taihe/string.hpp"
#include "ohos.data.unifiedDataChannel.ValueType.proj.1.hpp"
#include "taihe/optional.hpp"
#include "taihe/map.hpp"
namespace ohos::data::unifiedDataChannel::weak {
inline ::taihe::string HyperlinkInner::virtual_type::GetType() const& {
    return ::taihe::from_abi<::taihe::string>(ohos_data_unifiedDataChannel_HyperlinkInner_GetType_f(*reinterpret_cast<ohos_data_unifiedDataChannel_HyperlinkInner_t const*>(this)));
}
}
namespace ohos::data::unifiedDataChannel::weak {
inline ::ohos::data::unifiedDataChannel::ValueType HyperlinkInner::virtual_type::GetValue() const& {
    return ::taihe::from_abi<::ohos::data::unifiedDataChannel::ValueType>(ohos_data_unifiedDataChannel_HyperlinkInner_GetValue_f(*reinterpret_cast<ohos_data_unifiedDataChannel_HyperlinkInner_t const*>(this)));
}
}
namespace ohos::data::unifiedDataChannel::weak {
inline ::taihe::optional<::taihe::map<::taihe::string, ::taihe::string>> HyperlinkInner::virtual_type::GetDetails() const& {
    return ::taihe::from_abi<::taihe::optional<::taihe::map<::taihe::string, ::taihe::string>>>(ohos_data_unifiedDataChannel_HyperlinkInner_GetDetails_f(*reinterpret_cast<ohos_data_unifiedDataChannel_HyperlinkInner_t const*>(this)));
}
}
namespace ohos::data::unifiedDataChannel::weak {
inline void HyperlinkInner::virtual_type::SetDetails(::taihe::map_view<::taihe::string, ::taihe::string> details) const& {
    return ohos_data_unifiedDataChannel_HyperlinkInner_SetDetails_f(*reinterpret_cast<ohos_data_unifiedDataChannel_HyperlinkInner_t const*>(this), ::taihe::into_abi<::taihe::map_view<::taihe::string, ::taihe::string>>(details));
}
}
namespace ohos::data::unifiedDataChannel::weak {
inline void HyperlinkInner::virtual_type::SetUrl(::taihe::string_view url) const& {
    return ohos_data_unifiedDataChannel_HyperlinkInner_SetUrl_f(*reinterpret_cast<ohos_data_unifiedDataChannel_HyperlinkInner_t const*>(this), ::taihe::into_abi<::taihe::string_view>(url));
}
}
namespace ohos::data::unifiedDataChannel::weak {
inline ::taihe::string HyperlinkInner::virtual_type::GetUrl() const& {
    return ::taihe::from_abi<::taihe::string>(ohos_data_unifiedDataChannel_HyperlinkInner_GetUrl_f(*reinterpret_cast<ohos_data_unifiedDataChannel_HyperlinkInner_t const*>(this)));
}
}
namespace ohos::data::unifiedDataChannel::weak {
inline void HyperlinkInner::virtual_type::SetDescription(::taihe::string_view description) const& {
    return ohos_data_unifiedDataChannel_HyperlinkInner_SetDescription_f(*reinterpret_cast<ohos_data_unifiedDataChannel_HyperlinkInner_t const*>(this), ::taihe::into_abi<::taihe::string_view>(description));
}
}
namespace ohos::data::unifiedDataChannel::weak {
inline ::taihe::string HyperlinkInner::virtual_type::GetDescription() const& {
    return ::taihe::from_abi<::taihe::string>(ohos_data_unifiedDataChannel_HyperlinkInner_GetDescription_f(*reinterpret_cast<ohos_data_unifiedDataChannel_HyperlinkInner_t const*>(this)));
}
}
namespace ohos::data::unifiedDataChannel::weak {
inline int64_t HyperlinkInner::virtual_type::GetInner() const& {
    return ::taihe::from_abi<int64_t>(ohos_data_unifiedDataChannel_HyperlinkInner_GetInner_f(*reinterpret_cast<ohos_data_unifiedDataChannel_HyperlinkInner_t const*>(this)));
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
struct TString HyperlinkInner::methods_impl<Impl>::GetType(struct ohos_data_unifiedDataChannel_HyperlinkInner_t tobj) {
    return ::taihe::into_abi<::taihe::string>(::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->GetType());
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
struct ohos_data_unifiedDataChannel_ValueType_t HyperlinkInner::methods_impl<Impl>::GetValue(struct ohos_data_unifiedDataChannel_HyperlinkInner_t tobj) {
    return ::taihe::into_abi<::ohos::data::unifiedDataChannel::ValueType>(::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->GetValue());
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
struct TOptional HyperlinkInner::methods_impl<Impl>::GetDetails(struct ohos_data_unifiedDataChannel_HyperlinkInner_t tobj) {
    return ::taihe::into_abi<::taihe::optional<::taihe::map<::taihe::string, ::taihe::string>>>(::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->GetDetails());
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
void HyperlinkInner::methods_impl<Impl>::SetDetails(struct ohos_data_unifiedDataChannel_HyperlinkInner_t tobj, void* details) {
    return ::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->SetDetails(::taihe::from_abi<::taihe::map_view<::taihe::string, ::taihe::string>>(details));
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
void HyperlinkInner::methods_impl<Impl>::SetUrl(struct ohos_data_unifiedDataChannel_HyperlinkInner_t tobj, struct TString url) {
    return ::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->SetUrl(::taihe::from_abi<::taihe::string_view>(url));
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
struct TString HyperlinkInner::methods_impl<Impl>::GetUrl(struct ohos_data_unifiedDataChannel_HyperlinkInner_t tobj) {
    return ::taihe::into_abi<::taihe::string>(::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->GetUrl());
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
void HyperlinkInner::methods_impl<Impl>::SetDescription(struct ohos_data_unifiedDataChannel_HyperlinkInner_t tobj, struct TString description) {
    return ::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->SetDescription(::taihe::from_abi<::taihe::string_view>(description));
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
struct TString HyperlinkInner::methods_impl<Impl>::GetDescription(struct ohos_data_unifiedDataChannel_HyperlinkInner_t tobj) {
    return ::taihe::into_abi<::taihe::string>(::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->GetDescription());
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
int64_t HyperlinkInner::methods_impl<Impl>::GetInner(struct ohos_data_unifiedDataChannel_HyperlinkInner_t tobj) {
    return ::taihe::into_abi<int64_t>(::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->GetInner());
}
}
