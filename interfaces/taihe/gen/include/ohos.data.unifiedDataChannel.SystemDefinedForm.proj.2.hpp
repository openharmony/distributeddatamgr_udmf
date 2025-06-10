#pragma once
#include "ohos.data.unifiedDataChannel.SystemDefinedForm.proj.1.hpp"
#include "ohos.data.unifiedDataChannel.SystemDefinedForm.abi.2.h"
#include "taihe/string.hpp"
#include "ohos.data.unifiedDataChannel.ValueType.proj.1.hpp"
#include "taihe/optional.hpp"
#include "taihe/map.hpp"
#include "ohos.data.unifiedDataChannel.DetailsValue.proj.1.hpp"
namespace ohos::data::unifiedDataChannel::weak {
inline ::taihe::string SystemDefinedForm::virtual_type::GetType() const& {
    return ::taihe::from_abi<::taihe::string>(ohos_data_unifiedDataChannel_SystemDefinedForm_GetType_f(*reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedForm_t const*>(this)));
}
}
namespace ohos::data::unifiedDataChannel::weak {
inline ::ohos::data::unifiedDataChannel::ValueType SystemDefinedForm::virtual_type::GetValue() const& {
    return ::taihe::from_abi<::ohos::data::unifiedDataChannel::ValueType>(ohos_data_unifiedDataChannel_SystemDefinedForm_GetValue_f(*reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedForm_t const*>(this)));
}
}
namespace ohos::data::unifiedDataChannel::weak {
inline ::taihe::optional<::taihe::map<::taihe::string, ::ohos::data::unifiedDataChannel::DetailsValue>> SystemDefinedForm::virtual_type::GetDetails() const& {
    return ::taihe::from_abi<::taihe::optional<::taihe::map<::taihe::string, ::ohos::data::unifiedDataChannel::DetailsValue>>>(ohos_data_unifiedDataChannel_SystemDefinedForm_GetDetails_f(*reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedForm_t const*>(this)));
}
}
namespace ohos::data::unifiedDataChannel::weak {
inline void SystemDefinedForm::virtual_type::SetDetails(::taihe::map_view<::taihe::string, ::ohos::data::unifiedDataChannel::DetailsValue> details) const& {
    return ohos_data_unifiedDataChannel_SystemDefinedForm_SetDetails_f(*reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedForm_t const*>(this), ::taihe::into_abi<::taihe::map_view<::taihe::string, ::ohos::data::unifiedDataChannel::DetailsValue>>(details));
}
}
namespace ohos::data::unifiedDataChannel::weak {
inline double SystemDefinedForm::virtual_type::GetFormId() const& {
    return ::taihe::from_abi<double>(ohos_data_unifiedDataChannel_SystemDefinedForm_GetFormId_f(*reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedForm_t const*>(this)));
}
}
namespace ohos::data::unifiedDataChannel::weak {
inline void SystemDefinedForm::virtual_type::SetFormId(double formId) const& {
    return ohos_data_unifiedDataChannel_SystemDefinedForm_SetFormId_f(*reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedForm_t const*>(this), ::taihe::into_abi<double>(formId));
}
}
namespace ohos::data::unifiedDataChannel::weak {
inline ::taihe::string SystemDefinedForm::virtual_type::GetFormName() const& {
    return ::taihe::from_abi<::taihe::string>(ohos_data_unifiedDataChannel_SystemDefinedForm_GetFormName_f(*reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedForm_t const*>(this)));
}
}
namespace ohos::data::unifiedDataChannel::weak {
inline void SystemDefinedForm::virtual_type::SetFormName(::taihe::string_view formName) const& {
    return ohos_data_unifiedDataChannel_SystemDefinedForm_SetFormName_f(*reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedForm_t const*>(this), ::taihe::into_abi<::taihe::string_view>(formName));
}
}
namespace ohos::data::unifiedDataChannel::weak {
inline ::taihe::string SystemDefinedForm::virtual_type::GetBundleName() const& {
    return ::taihe::from_abi<::taihe::string>(ohos_data_unifiedDataChannel_SystemDefinedForm_GetBundleName_f(*reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedForm_t const*>(this)));
}
}
namespace ohos::data::unifiedDataChannel::weak {
inline void SystemDefinedForm::virtual_type::SetBundleName(::taihe::string_view bundleName) const& {
    return ohos_data_unifiedDataChannel_SystemDefinedForm_SetBundleName_f(*reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedForm_t const*>(this), ::taihe::into_abi<::taihe::string_view>(bundleName));
}
}
namespace ohos::data::unifiedDataChannel::weak {
inline ::taihe::string SystemDefinedForm::virtual_type::GetAbilityName() const& {
    return ::taihe::from_abi<::taihe::string>(ohos_data_unifiedDataChannel_SystemDefinedForm_GetAbilityName_f(*reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedForm_t const*>(this)));
}
}
namespace ohos::data::unifiedDataChannel::weak {
inline void SystemDefinedForm::virtual_type::SetAbilityName(::taihe::string_view abilityName) const& {
    return ohos_data_unifiedDataChannel_SystemDefinedForm_SetAbilityName_f(*reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedForm_t const*>(this), ::taihe::into_abi<::taihe::string_view>(abilityName));
}
}
namespace ohos::data::unifiedDataChannel::weak {
inline ::taihe::string SystemDefinedForm::virtual_type::GetModule() const& {
    return ::taihe::from_abi<::taihe::string>(ohos_data_unifiedDataChannel_SystemDefinedForm_GetModule_f(*reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedForm_t const*>(this)));
}
}
namespace ohos::data::unifiedDataChannel::weak {
inline void SystemDefinedForm::virtual_type::SetModule(::taihe::string_view module) const& {
    return ohos_data_unifiedDataChannel_SystemDefinedForm_SetModule_f(*reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedForm_t const*>(this), ::taihe::into_abi<::taihe::string_view>(module));
}
}
namespace ohos::data::unifiedDataChannel::weak {
inline int64_t SystemDefinedForm::virtual_type::GetInner() const& {
    return ::taihe::from_abi<int64_t>(ohos_data_unifiedDataChannel_SystemDefinedForm_GetInner_f(*reinterpret_cast<ohos_data_unifiedDataChannel_SystemDefinedForm_t const*>(this)));
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
struct TString SystemDefinedForm::methods_impl<Impl>::GetType(struct ohos_data_unifiedDataChannel_SystemDefinedForm_t tobj) {
    return ::taihe::into_abi<::taihe::string>(::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->GetType());
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
struct ohos_data_unifiedDataChannel_ValueType_t SystemDefinedForm::methods_impl<Impl>::GetValue(struct ohos_data_unifiedDataChannel_SystemDefinedForm_t tobj) {
    return ::taihe::into_abi<::ohos::data::unifiedDataChannel::ValueType>(::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->GetValue());
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
struct TOptional SystemDefinedForm::methods_impl<Impl>::GetDetails(struct ohos_data_unifiedDataChannel_SystemDefinedForm_t tobj) {
    return ::taihe::into_abi<::taihe::optional<::taihe::map<::taihe::string, ::ohos::data::unifiedDataChannel::DetailsValue>>>(::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->GetDetails());
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
void SystemDefinedForm::methods_impl<Impl>::SetDetails(struct ohos_data_unifiedDataChannel_SystemDefinedForm_t tobj, void* details) {
    return ::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->SetDetails(::taihe::from_abi<::taihe::map_view<::taihe::string, ::ohos::data::unifiedDataChannel::DetailsValue>>(details));
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
double SystemDefinedForm::methods_impl<Impl>::GetFormId(struct ohos_data_unifiedDataChannel_SystemDefinedForm_t tobj) {
    return ::taihe::into_abi<double>(::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->GetFormId());
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
void SystemDefinedForm::methods_impl<Impl>::SetFormId(struct ohos_data_unifiedDataChannel_SystemDefinedForm_t tobj, double formId) {
    return ::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->SetFormId(::taihe::from_abi<double>(formId));
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
struct TString SystemDefinedForm::methods_impl<Impl>::GetFormName(struct ohos_data_unifiedDataChannel_SystemDefinedForm_t tobj) {
    return ::taihe::into_abi<::taihe::string>(::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->GetFormName());
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
void SystemDefinedForm::methods_impl<Impl>::SetFormName(struct ohos_data_unifiedDataChannel_SystemDefinedForm_t tobj, struct TString formName) {
    return ::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->SetFormName(::taihe::from_abi<::taihe::string_view>(formName));
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
struct TString SystemDefinedForm::methods_impl<Impl>::GetBundleName(struct ohos_data_unifiedDataChannel_SystemDefinedForm_t tobj) {
    return ::taihe::into_abi<::taihe::string>(::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->GetBundleName());
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
void SystemDefinedForm::methods_impl<Impl>::SetBundleName(struct ohos_data_unifiedDataChannel_SystemDefinedForm_t tobj, struct TString bundleName) {
    return ::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->SetBundleName(::taihe::from_abi<::taihe::string_view>(bundleName));
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
struct TString SystemDefinedForm::methods_impl<Impl>::GetAbilityName(struct ohos_data_unifiedDataChannel_SystemDefinedForm_t tobj) {
    return ::taihe::into_abi<::taihe::string>(::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->GetAbilityName());
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
void SystemDefinedForm::methods_impl<Impl>::SetAbilityName(struct ohos_data_unifiedDataChannel_SystemDefinedForm_t tobj, struct TString abilityName) {
    return ::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->SetAbilityName(::taihe::from_abi<::taihe::string_view>(abilityName));
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
struct TString SystemDefinedForm::methods_impl<Impl>::GetModule(struct ohos_data_unifiedDataChannel_SystemDefinedForm_t tobj) {
    return ::taihe::into_abi<::taihe::string>(::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->GetModule());
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
void SystemDefinedForm::methods_impl<Impl>::SetModule(struct ohos_data_unifiedDataChannel_SystemDefinedForm_t tobj, struct TString module) {
    return ::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->SetModule(::taihe::from_abi<::taihe::string_view>(module));
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
int64_t SystemDefinedForm::methods_impl<Impl>::GetInner(struct ohos_data_unifiedDataChannel_SystemDefinedForm_t tobj) {
    return ::taihe::into_abi<int64_t>(::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->GetInner());
}
}
