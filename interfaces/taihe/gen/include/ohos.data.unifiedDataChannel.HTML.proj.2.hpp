#pragma once
#include "ohos.data.unifiedDataChannel.HTML.proj.1.hpp"
#include "ohos.data.unifiedDataChannel.HTML.abi.2.h"
#include "taihe/string.hpp"
#include "ohos.data.unifiedDataChannel.ValueType.proj.1.hpp"
#include "taihe/optional.hpp"
#include "taihe/map.hpp"
namespace ohos::data::unifiedDataChannel::weak {
inline ::taihe::string HTML::virtual_type::GetType() const& {
    return ::taihe::from_abi<::taihe::string>(ohos_data_unifiedDataChannel_HTML_GetType_f(*reinterpret_cast<ohos_data_unifiedDataChannel_HTML_t const*>(this)));
}
}
namespace ohos::data::unifiedDataChannel::weak {
inline ::ohos::data::unifiedDataChannel::ValueType HTML::virtual_type::GetValue() const& {
    return ::taihe::from_abi<::ohos::data::unifiedDataChannel::ValueType>(ohos_data_unifiedDataChannel_HTML_GetValue_f(*reinterpret_cast<ohos_data_unifiedDataChannel_HTML_t const*>(this)));
}
}
namespace ohos::data::unifiedDataChannel::weak {
inline ::taihe::optional<::taihe::map<::taihe::string, ::taihe::string>> HTML::virtual_type::GetDetails() const& {
    return ::taihe::from_abi<::taihe::optional<::taihe::map<::taihe::string, ::taihe::string>>>(ohos_data_unifiedDataChannel_HTML_GetDetails_f(*reinterpret_cast<ohos_data_unifiedDataChannel_HTML_t const*>(this)));
}
}
namespace ohos::data::unifiedDataChannel::weak {
inline void HTML::virtual_type::SetDetails(::taihe::map_view<::taihe::string, ::taihe::string> details) const& {
    return ohos_data_unifiedDataChannel_HTML_SetDetails_f(*reinterpret_cast<ohos_data_unifiedDataChannel_HTML_t const*>(this), ::taihe::into_abi<::taihe::map_view<::taihe::string, ::taihe::string>>(details));
}
}
namespace ohos::data::unifiedDataChannel::weak {
inline void HTML::virtual_type::SetHtmlContent(::taihe::string_view htmlContent) const& {
    return ohos_data_unifiedDataChannel_HTML_SetHtmlContent_f(*reinterpret_cast<ohos_data_unifiedDataChannel_HTML_t const*>(this), ::taihe::into_abi<::taihe::string_view>(htmlContent));
}
}
namespace ohos::data::unifiedDataChannel::weak {
inline ::taihe::string HTML::virtual_type::GetHtmlContent() const& {
    return ::taihe::from_abi<::taihe::string>(ohos_data_unifiedDataChannel_HTML_GetHtmlContent_f(*reinterpret_cast<ohos_data_unifiedDataChannel_HTML_t const*>(this)));
}
}
namespace ohos::data::unifiedDataChannel::weak {
inline void HTML::virtual_type::SetPlainContent(::taihe::string_view plainContent) const& {
    return ohos_data_unifiedDataChannel_HTML_SetPlainContent_f(*reinterpret_cast<ohos_data_unifiedDataChannel_HTML_t const*>(this), ::taihe::into_abi<::taihe::string_view>(plainContent));
}
}
namespace ohos::data::unifiedDataChannel::weak {
inline ::taihe::string HTML::virtual_type::GetPlainContent() const& {
    return ::taihe::from_abi<::taihe::string>(ohos_data_unifiedDataChannel_HTML_GetPlainContent_f(*reinterpret_cast<ohos_data_unifiedDataChannel_HTML_t const*>(this)));
}
}
namespace ohos::data::unifiedDataChannel::weak {
inline int64_t HTML::virtual_type::GetInner() const& {
    return ::taihe::from_abi<int64_t>(ohos_data_unifiedDataChannel_HTML_GetInner_f(*reinterpret_cast<ohos_data_unifiedDataChannel_HTML_t const*>(this)));
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
struct TString HTML::methods_impl<Impl>::GetType(struct ohos_data_unifiedDataChannel_HTML_t tobj) {
    return ::taihe::into_abi<::taihe::string>(::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->GetType());
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
struct ohos_data_unifiedDataChannel_ValueType_t HTML::methods_impl<Impl>::GetValue(struct ohos_data_unifiedDataChannel_HTML_t tobj) {
    return ::taihe::into_abi<::ohos::data::unifiedDataChannel::ValueType>(::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->GetValue());
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
struct TOptional HTML::methods_impl<Impl>::GetDetails(struct ohos_data_unifiedDataChannel_HTML_t tobj) {
    return ::taihe::into_abi<::taihe::optional<::taihe::map<::taihe::string, ::taihe::string>>>(::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->GetDetails());
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
void HTML::methods_impl<Impl>::SetDetails(struct ohos_data_unifiedDataChannel_HTML_t tobj, void* details) {
    return ::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->SetDetails(::taihe::from_abi<::taihe::map_view<::taihe::string, ::taihe::string>>(details));
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
void HTML::methods_impl<Impl>::SetHtmlContent(struct ohos_data_unifiedDataChannel_HTML_t tobj, struct TString htmlContent) {
    return ::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->SetHtmlContent(::taihe::from_abi<::taihe::string_view>(htmlContent));
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
struct TString HTML::methods_impl<Impl>::GetHtmlContent(struct ohos_data_unifiedDataChannel_HTML_t tobj) {
    return ::taihe::into_abi<::taihe::string>(::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->GetHtmlContent());
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
void HTML::methods_impl<Impl>::SetPlainContent(struct ohos_data_unifiedDataChannel_HTML_t tobj, struct TString plainContent) {
    return ::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->SetPlainContent(::taihe::from_abi<::taihe::string_view>(plainContent));
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
struct TString HTML::methods_impl<Impl>::GetPlainContent(struct ohos_data_unifiedDataChannel_HTML_t tobj) {
    return ::taihe::into_abi<::taihe::string>(::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->GetPlainContent());
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
int64_t HTML::methods_impl<Impl>::GetInner(struct ohos_data_unifiedDataChannel_HTML_t tobj) {
    return ::taihe::into_abi<int64_t>(::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->GetInner());
}
}
