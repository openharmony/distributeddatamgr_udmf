#pragma once
#include "ohos.data.unifiedDataChannel.Folder.proj.1.hpp"
#include "ohos.data.unifiedDataChannel.Folder.abi.2.h"
#include "taihe/string.hpp"
#include "ohos.data.unifiedDataChannel.ValueType.proj.1.hpp"
#include "taihe/optional.hpp"
#include "taihe/map.hpp"
namespace ohos::data::unifiedDataChannel::weak {
inline ::taihe::string Folder::virtual_type::GetType() const& {
    return ::taihe::from_abi<::taihe::string>(ohos_data_unifiedDataChannel_Folder_GetType_f(*reinterpret_cast<ohos_data_unifiedDataChannel_Folder_t const*>(this)));
}
}
namespace ohos::data::unifiedDataChannel::weak {
inline ::ohos::data::unifiedDataChannel::ValueType Folder::virtual_type::GetValue() const& {
    return ::taihe::from_abi<::ohos::data::unifiedDataChannel::ValueType>(ohos_data_unifiedDataChannel_Folder_GetValue_f(*reinterpret_cast<ohos_data_unifiedDataChannel_Folder_t const*>(this)));
}
}
namespace ohos::data::unifiedDataChannel::weak {
inline ::taihe::string Folder::virtual_type::GetUri() const& {
    return ::taihe::from_abi<::taihe::string>(ohos_data_unifiedDataChannel_Folder_GetUri_f(*reinterpret_cast<ohos_data_unifiedDataChannel_Folder_t const*>(this)));
}
}
namespace ohos::data::unifiedDataChannel::weak {
inline void Folder::virtual_type::SetUri(::taihe::string_view uri) const& {
    return ohos_data_unifiedDataChannel_Folder_SetUri_f(*reinterpret_cast<ohos_data_unifiedDataChannel_Folder_t const*>(this), ::taihe::into_abi<::taihe::string_view>(uri));
}
}
namespace ohos::data::unifiedDataChannel::weak {
inline ::taihe::optional<::taihe::map<::taihe::string, ::taihe::string>> Folder::virtual_type::GetDetails() const& {
    return ::taihe::from_abi<::taihe::optional<::taihe::map<::taihe::string, ::taihe::string>>>(ohos_data_unifiedDataChannel_Folder_GetDetails_f(*reinterpret_cast<ohos_data_unifiedDataChannel_Folder_t const*>(this)));
}
}
namespace ohos::data::unifiedDataChannel::weak {
inline void Folder::virtual_type::SetDetails(::taihe::map_view<::taihe::string, ::taihe::string> details) const& {
    return ohos_data_unifiedDataChannel_Folder_SetDetails_f(*reinterpret_cast<ohos_data_unifiedDataChannel_Folder_t const*>(this), ::taihe::into_abi<::taihe::map_view<::taihe::string, ::taihe::string>>(details));
}
}
namespace ohos::data::unifiedDataChannel::weak {
inline ::taihe::string Folder::virtual_type::GetFolderUri() const& {
    return ::taihe::from_abi<::taihe::string>(ohos_data_unifiedDataChannel_Folder_GetFolderUri_f(*reinterpret_cast<ohos_data_unifiedDataChannel_Folder_t const*>(this)));
}
}
namespace ohos::data::unifiedDataChannel::weak {
inline void Folder::virtual_type::SetFolderUri(::taihe::string_view folderUri) const& {
    return ohos_data_unifiedDataChannel_Folder_SetFolderUri_f(*reinterpret_cast<ohos_data_unifiedDataChannel_Folder_t const*>(this), ::taihe::into_abi<::taihe::string_view>(folderUri));
}
}
namespace ohos::data::unifiedDataChannel::weak {
inline int64_t Folder::virtual_type::GetInner() const& {
    return ::taihe::from_abi<int64_t>(ohos_data_unifiedDataChannel_Folder_GetInner_f(*reinterpret_cast<ohos_data_unifiedDataChannel_Folder_t const*>(this)));
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
struct TString Folder::methods_impl<Impl>::GetType(struct ohos_data_unifiedDataChannel_Folder_t tobj) {
    return ::taihe::into_abi<::taihe::string>(::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->GetType());
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
struct ohos_data_unifiedDataChannel_ValueType_t Folder::methods_impl<Impl>::GetValue(struct ohos_data_unifiedDataChannel_Folder_t tobj) {
    return ::taihe::into_abi<::ohos::data::unifiedDataChannel::ValueType>(::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->GetValue());
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
struct TString Folder::methods_impl<Impl>::GetUri(struct ohos_data_unifiedDataChannel_Folder_t tobj) {
    return ::taihe::into_abi<::taihe::string>(::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->GetUri());
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
void Folder::methods_impl<Impl>::SetUri(struct ohos_data_unifiedDataChannel_Folder_t tobj, struct TString uri) {
    return ::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->SetUri(::taihe::from_abi<::taihe::string_view>(uri));
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
struct TOptional Folder::methods_impl<Impl>::GetDetails(struct ohos_data_unifiedDataChannel_Folder_t tobj) {
    return ::taihe::into_abi<::taihe::optional<::taihe::map<::taihe::string, ::taihe::string>>>(::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->GetDetails());
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
void Folder::methods_impl<Impl>::SetDetails(struct ohos_data_unifiedDataChannel_Folder_t tobj, void* details) {
    return ::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->SetDetails(::taihe::from_abi<::taihe::map_view<::taihe::string, ::taihe::string>>(details));
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
struct TString Folder::methods_impl<Impl>::GetFolderUri(struct ohos_data_unifiedDataChannel_Folder_t tobj) {
    return ::taihe::into_abi<::taihe::string>(::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->GetFolderUri());
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
void Folder::methods_impl<Impl>::SetFolderUri(struct ohos_data_unifiedDataChannel_Folder_t tobj, struct TString folderUri) {
    return ::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->SetFolderUri(::taihe::from_abi<::taihe::string_view>(folderUri));
}
}
namespace ohos::data::unifiedDataChannel::weak {
template<typename Impl>
int64_t Folder::methods_impl<Impl>::GetInner(struct ohos_data_unifiedDataChannel_Folder_t tobj) {
    return ::taihe::into_abi<int64_t>(::taihe::cast_data_ptr<Impl>(tobj.data_ptr)->GetInner());
}
}
