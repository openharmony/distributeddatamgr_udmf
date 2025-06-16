#pragma once
#include "ohos.data.unifiedDataChannel.SystemDefinedAppItemInner.proj.1.hpp"
#include "ohos.data.unifiedDataChannel.SystemDefinedAppItemInner.abi.2.h"
#include "taihe/string.hpp"
#include "ohos.data.unifiedDataChannel.ValueType.proj.1.hpp"
#include "taihe/optional.hpp"
#include "taihe/map.hpp"
#include "ohos.data.unifiedDataChannel.DetailsValue.proj.1.hpp"
namespace ohos::data::unifiedDataChannel::weak {
inline ::taihe::string SystemDefinedAppItemInner::virtual_type::GetType() const& {
    return ::taihe::from_abi<::taihe::string>(ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_GetType_f(*reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_t const*>(this)));
}
}
namespace ohos::data::unifiedDataChannel::weak {
inline ::ohos::data::unifiedDataChannel::ValueType SystemDefinedAppItemInner::virtual_type::GetValue() const& {
    return ::taihe::from_abi<::ohos::data::unifiedDataChannel::ValueType>(ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_GetValue_f(*reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_t const*>(this)));
}
}
namespace ohos::data::unifiedDataChannel::weak {
inline ::taihe::optional<::taihe::map<::taihe::string, ::ohos::data::unifiedDataChannel::DetailsValue>> SystemDefinedAppItemInner::virtual_type::GetDetails() const& {
    return ::taihe::from_abi<::taihe::optional<::taihe::map<::taihe::string, ::ohos::data::unifiedDataChannel::DetailsValue>>>(ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_GetDetails_f(*reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_t const*>(this)));
}
}
namespace ohos::data::unifiedDataChannel::weak {
inline void SystemDefinedAppItemInner::virtual_type::SetDetails(::taihe::map_view<::taihe::string, ::ohos::data::unifiedDataChannel::DetailsValue> details) const& {
    return ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_SetDetails_f(*reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_t const*>(this), ::taihe::into_abi<::taihe::map_view<::taihe::string, ::ohos::data::unifiedDataChannel::DetailsValue>>(details));
}
}
namespace ohos::data::unifiedDataChannel::weak {
inline ::taihe::string SystemDefinedAppItemInner::virtual_type::GetAppId() const& {
    return ::taihe::from_abi<::taihe::string>(ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_GetAppId_f(*reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_t const*>(this)));
}
}
namespace ohos::data::unifiedDataChannel::weak {
inline void SystemDefinedAppItemInner::virtual_type::SetAppId(::taihe::string_view appId) const& {
    return ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_SetAppId_f(*reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_t const*>(this), ::taihe::into_abi<::taihe::string_view>(appId));
}
}
namespace ohos::data::unifiedDataChannel::weak {
inline ::taihe::string SystemDefinedAppItemInner::virtual_type::GetAppName() const& {
    return ::taihe::from_abi<::taihe::string>(ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_GetAppName_f(*reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_t const*>(this)));
}
}
namespace ohos::data::unifiedDataChannel::weak {
inline void SystemDefinedAppItemInner::virtual_type::SetAppName(::taihe::string_view appName) const& {
    return ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_SetAppName_f(*reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_t const*>(this), ::taihe::into_abi<::taihe::string_view>(appName));
}
}
namespace ohos::data::unifiedDataChannel::weak {
inline ::taihe::string SystemDefinedAppItemInner::virtual_type::GetAppIconId() const& {
    return ::taihe::from_abi<::taihe::string>(ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_GetAppIconId_f(*reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_t const*>(this)));
}
}
namespace ohos::data::unifiedDataChannel::weak {
inline void SystemDefinedAppItemInner::virtual_type::SetAppIconId(::taihe::string_view appIconId) const& {
    return ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_SetAppIconId_f(*reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_t const*>(this), ::taihe::into_abi<::taihe::string_view>(appIconId));
}
}
namespace ohos::data::unifiedDataChannel::weak {
inline ::taihe::string SystemDefinedAppItemInner::virtual_type::GetAppLabelId() const& {
    return ::taihe::from_abi<::taihe::string>(ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_GetAppLabelId_f(*reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_t const*>(this)));
}
}
namespace ohos::data::unifiedDataChannel::weak {
inline void SystemDefinedAppItemInner::virtual_type::SetAppLabelId(::taihe::string_view appLabelId) const& {
    return ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_SetAppLabelId_f(*reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_t const*>(this), ::taihe::into_abi<::taihe::string_view>(appLabelId));
}
}
namespace ohos::data::unifiedDataChannel::weak {
inline ::taihe::string SystemDefinedAppItemInner::virtual_type::GetBundleName() const& {
    return ::taihe::from_abi<::taihe::string>(ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_GetBundleName_f(*reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_t const*>(this)));
}
}
namespace ohos::data::unifiedDataChannel::weak {
inline void SystemDefinedAppItemInner::virtual_type::SetBundleName(::taihe::string_view bundleName) const& {
    return ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_SetBundleName_f(*reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_t const*>(this), ::taihe::into_abi<::taihe::string_view>(bundleName));
}
}
namespace ohos::data::unifiedDataChannel::weak {
inline ::taihe::string SystemDefinedAppItemInner::virtual_type::GetAbilityName() const& {
    return ::taihe::from_abi<::taihe::string>(ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_GetAbilityName_f(*reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_t const*>(this)));
}
}
namespace ohos::data::unifiedDataChannel::weak {
inline void SystemDefinedAppItemInner::virtual_type::SetAbilityName(::taihe::string_view abilityName) const& {
    return ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_SetAbilityName_f(*reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_t const*>(this), ::taihe::into_abi<::taihe::string_view>(abilityName));
}
}
namespace ohos::data::unifiedDataChannel::weak {
inline int64_t SystemDefinedAppItemInner::virtual_type::GetInner() const& {
    return ::taihe::from_abi<int64_t>(ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_GetInner_f(*reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_t const*>(this)));
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
struct TString SystemDefinedAppItemInner::methods_impl<Impl>::GetType(struct ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_t tobj) {
    return ::taihe::into_abi<::taihe::string>(::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->GetType());
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
struct ohos_data_unifiedDataChannel_ValueType_t SystemDefinedAppItemInner::methods_impl<Impl>::GetValue(struct ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_t tobj) {
    return ::taihe::into_abi<::ohos::data::unifiedDataChannel::ValueType>(::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->GetValue());
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
struct TOptional SystemDefinedAppItemInner::methods_impl<Impl>::GetDetails(struct ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_t tobj) {
    return ::taihe::into_abi<::taihe::optional<::taihe::map<::taihe::string, ::ohos::data::unifiedDataChannel::DetailsValue>>>(::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->GetDetails());
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
void SystemDefinedAppItemInner::methods_impl<Impl>::SetDetails(struct ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_t tobj, void* details) {
    return ::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->SetDetails(::taihe::from_abi<::taihe::map_view<::taihe::string, ::ohos::data::unifiedDataChannel::DetailsValue>>(details));
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
struct TString SystemDefinedAppItemInner::methods_impl<Impl>::GetAppId(struct ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_t tobj) {
    return ::taihe::into_abi<::taihe::string>(::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->GetAppId());
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
void SystemDefinedAppItemInner::methods_impl<Impl>::SetAppId(struct ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_t tobj, struct TString appId) {
    return ::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->SetAppId(::taihe::from_abi<::taihe::string_view>(appId));
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
struct TString SystemDefinedAppItemInner::methods_impl<Impl>::GetAppName(struct ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_t tobj) {
    return ::taihe::into_abi<::taihe::string>(::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->GetAppName());
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
void SystemDefinedAppItemInner::methods_impl<Impl>::SetAppName(struct ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_t tobj, struct TString appName) {
    return ::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->SetAppName(::taihe::from_abi<::taihe::string_view>(appName));
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
struct TString SystemDefinedAppItemInner::methods_impl<Impl>::GetAppIconId(struct ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_t tobj) {
    return ::taihe::into_abi<::taihe::string>(::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->GetAppIconId());
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
void SystemDefinedAppItemInner::methods_impl<Impl>::SetAppIconId(struct ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_t tobj, struct TString appIconId) {
    return ::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->SetAppIconId(::taihe::from_abi<::taihe::string_view>(appIconId));
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
struct TString SystemDefinedAppItemInner::methods_impl<Impl>::GetAppLabelId(struct ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_t tobj) {
    return ::taihe::into_abi<::taihe::string>(::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->GetAppLabelId());
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
void SystemDefinedAppItemInner::methods_impl<Impl>::SetAppLabelId(struct ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_t tobj, struct TString appLabelId) {
    return ::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->SetAppLabelId(::taihe::from_abi<::taihe::string_view>(appLabelId));
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
struct TString SystemDefinedAppItemInner::methods_impl<Impl>::GetBundleName(struct ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_t tobj) {
    return ::taihe::into_abi<::taihe::string>(::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->GetBundleName());
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
void SystemDefinedAppItemInner::methods_impl<Impl>::SetBundleName(struct ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_t tobj, struct TString bundleName) {
    return ::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->SetBundleName(::taihe::from_abi<::taihe::string_view>(bundleName));
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
struct TString SystemDefinedAppItemInner::methods_impl<Impl>::GetAbilityName(struct ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_t tobj) {
    return ::taihe::into_abi<::taihe::string>(::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->GetAbilityName());
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
void SystemDefinedAppItemInner::methods_impl<Impl>::SetAbilityName(struct ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_t tobj, struct TString abilityName) {
    return ::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->SetAbilityName(::taihe::from_abi<::taihe::string_view>(abilityName));
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
int64_t SystemDefinedAppItemInner::methods_impl<Impl>::GetInner(struct ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_t tobj) {
    return ::taihe::into_abi<int64_t>(::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->GetInner());
}
}
