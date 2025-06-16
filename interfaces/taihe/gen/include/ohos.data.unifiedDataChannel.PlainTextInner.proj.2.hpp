#pragma once
#include "ohos.data.unifiedDataChannel.PlainTextInner.proj.1.hpp"
#include "ohos.data.unifiedDataChannel.PlainTextInner.abi.2.h"
#include "taihe/string.hpp"
#include "ohos.data.unifiedDataChannel.ValueType.proj.1.hpp"
#include "taihe/optional.hpp"
#include "taihe/map.hpp"
namespace ohos::data::unifiedDataChannel::weak {
inline ::taihe::string PlainTextInner::virtual_type::GetType() const& {
    return ::taihe::from_abi<::taihe::string>(ohos_data_unifiedDataChannel_PlainTextInner_GetType_f(*reinterpret_cast<ohos_data_unifiedDataChannel_PlainTextInner_t const*>(this)));
}
}
namespace ohos::data::unifiedDataChannel::weak {
inline ::ohos::data::unifiedDataChannel::ValueType PlainTextInner::virtual_type::GetValue() const& {
    return ::taihe::from_abi<::ohos::data::unifiedDataChannel::ValueType>(ohos_data_unifiedDataChannel_PlainTextInner_GetValue_f(*reinterpret_cast<ohos_data_unifiedDataChannel_PlainTextInner_t const*>(this)));
}
}
namespace ohos::data::unifiedDataChannel::weak {
inline ::taihe::optional<::taihe::map<::taihe::string, ::taihe::string>> PlainTextInner::virtual_type::GetDetails() const& {
    return ::taihe::from_abi<::taihe::optional<::taihe::map<::taihe::string, ::taihe::string>>>(ohos_data_unifiedDataChannel_PlainTextInner_GetDetails_f(*reinterpret_cast<ohos_data_unifiedDataChannel_PlainTextInner_t const*>(this)));
}
}
namespace ohos::data::unifiedDataChannel::weak {
inline void PlainTextInner::virtual_type::SetDetails(::taihe::map_view<::taihe::string, ::taihe::string> details) const& {
    return ohos_data_unifiedDataChannel_PlainTextInner_SetDetails_f(*reinterpret_cast<ohos_data_unifiedDataChannel_PlainTextInner_t const*>(this), ::taihe::into_abi<::taihe::map_view<::taihe::string, ::taihe::string>>(details));
}
}
namespace ohos::data::unifiedDataChannel::weak {
inline void PlainTextInner::virtual_type::SetTextContent(::taihe::string_view textContent) const& {
    return ohos_data_unifiedDataChannel_PlainTextInner_SetTextContent_f(*reinterpret_cast<ohos_data_unifiedDataChannel_PlainTextInner_t const*>(this), ::taihe::into_abi<::taihe::string_view>(textContent));
}
}
namespace ohos::data::unifiedDataChannel::weak {
inline ::taihe::string PlainTextInner::virtual_type::GetTextContent() const& {
    return ::taihe::from_abi<::taihe::string>(ohos_data_unifiedDataChannel_PlainTextInner_GetTextContent_f(*reinterpret_cast<ohos_data_unifiedDataChannel_PlainTextInner_t const*>(this)));
}
}
namespace ohos::data::unifiedDataChannel::weak {
inline int64_t PlainTextInner::virtual_type::GetInner() const& {
    return ::taihe::from_abi<int64_t>(ohos_data_unifiedDataChannel_PlainTextInner_GetInner_f(*reinterpret_cast<ohos_data_unifiedDataChannel_PlainTextInner_t const*>(this)));
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
struct TString PlainTextInner::methods_impl<Impl>::GetType(struct ohos_data_unifiedDataChannel_PlainTextInner_t tobj) {
    return ::taihe::into_abi<::taihe::string>(::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->GetType());
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
struct ohos_data_unifiedDataChannel_ValueType_t PlainTextInner::methods_impl<Impl>::GetValue(struct ohos_data_unifiedDataChannel_PlainTextInner_t tobj) {
    return ::taihe::into_abi<::ohos::data::unifiedDataChannel::ValueType>(::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->GetValue());
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
struct TOptional PlainTextInner::methods_impl<Impl>::GetDetails(struct ohos_data_unifiedDataChannel_PlainTextInner_t tobj) {
    return ::taihe::into_abi<::taihe::optional<::taihe::map<::taihe::string, ::taihe::string>>>(::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->GetDetails());
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
void PlainTextInner::methods_impl<Impl>::SetDetails(struct ohos_data_unifiedDataChannel_PlainTextInner_t tobj, void* details) {
    return ::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->SetDetails(::taihe::from_abi<::taihe::map_view<::taihe::string, ::taihe::string>>(details));
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
void PlainTextInner::methods_impl<Impl>::SetTextContent(struct ohos_data_unifiedDataChannel_PlainTextInner_t tobj, struct TString textContent) {
    return ::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->SetTextContent(::taihe::from_abi<::taihe::string_view>(textContent));
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
struct TString PlainTextInner::methods_impl<Impl>::GetTextContent(struct ohos_data_unifiedDataChannel_PlainTextInner_t tobj) {
    return ::taihe::into_abi<::taihe::string>(::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->GetTextContent());
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
int64_t PlainTextInner::methods_impl<Impl>::GetInner(struct ohos_data_unifiedDataChannel_PlainTextInner_t tobj) {
    return ::taihe::into_abi<int64_t>(::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->GetInner());
}
}
