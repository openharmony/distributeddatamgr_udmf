#pragma once
#include "taihe/object.hpp"
#include "ohos.data.unifiedDataChannel.SystemDefinedAppItem.proj.0.hpp"
#include "ohos.data.unifiedDataChannel.SystemDefinedAppItem.abi.1.h"
#include "taihe/string.hpp"
#include "ohos.data.unifiedDataChannel.ValueType.proj.0.hpp"
#include "taihe/optional.hpp"
#include "taihe/map.hpp"
#include "ohos.data.unifiedDataChannel.DetailsValue.proj.0.hpp"
namespace ohos::data::unifiedDataChannel::weak {
struct SystemDefinedAppItem {
    static constexpr bool is_holder = false;
    struct ohos_data_unifiedDataChannel_SystemDefinedAppItem_t m_handle;
    explicit SystemDefinedAppItem(struct ohos_data_unifiedDataChannel_SystemDefinedAppItem_t handle) : m_handle(handle) {}
    explicit SystemDefinedAppItem(::taihe::data_view other) : SystemDefinedAppItem(ohos_data_unifiedDataChannel_SystemDefinedAppItem_dynamic(other.data_ptr)) {}
    operator ::taihe::data_view() const& {
        struct ohos_data_unifiedDataChannel_SystemDefinedAppItem_t ret_handle = m_handle;
        return ::taihe::data_view(ret_handle.data_ptr);
    }
    operator ::taihe::data_holder() const& {
        struct ohos_data_unifiedDataChannel_SystemDefinedAppItem_t ret_handle = ohos_data_unifiedDataChannel_SystemDefinedAppItem_copy(m_handle);
        return ::taihe::data_holder(ret_handle.data_ptr);
    }
    struct virtual_type {
        ::taihe::string GetType() const&;
        ::ohos::data::unifiedDataChannel::ValueType GetValue() const&;
        ::taihe::optional<::taihe::map<::taihe::string, ::ohos::data::unifiedDataChannel::DetailsValue>> GetDetails() const&;
        void SetDetails(::taihe::map_view<::taihe::string, ::ohos::data::unifiedDataChannel::DetailsValue> details) const&;
        ::taihe::string GetAppId() const&;
        void SetAppId(::taihe::string_view appId) const&;
        ::taihe::string GetAppName() const&;
        void SetAppName(::taihe::string_view appName) const&;
        ::taihe::string GetAppIconId() const&;
        void SetAppIconId(::taihe::string_view appIconId) const&;
        ::taihe::string GetAppLabelId() const&;
        void SetAppLabelId(::taihe::string_view appLabelId) const&;
        ::taihe::string GetBundleName() const&;
        void SetBundleName(::taihe::string_view bundleName) const&;
        ::taihe::string GetAbilityName() const&;
        void SetAbilityName(::taihe::string_view abilityName) const&;
        int64_t GetInner() const&;
    };
    template<typename Impl>
    struct methods_impl {
        static struct TString GetType(struct ohos_data_unifiedDataChannel_SystemDefinedAppItem_t tobj);
        static struct ohos_data_unifiedDataChannel_ValueType_t GetValue(struct ohos_data_unifiedDataChannel_SystemDefinedAppItem_t tobj);
        static struct TOptional GetDetails(struct ohos_data_unifiedDataChannel_SystemDefinedAppItem_t tobj);
        static void SetDetails(struct ohos_data_unifiedDataChannel_SystemDefinedAppItem_t tobj, void* details);
        static struct TString GetAppId(struct ohos_data_unifiedDataChannel_SystemDefinedAppItem_t tobj);
        static void SetAppId(struct ohos_data_unifiedDataChannel_SystemDefinedAppItem_t tobj, struct TString appId);
        static struct TString GetAppName(struct ohos_data_unifiedDataChannel_SystemDefinedAppItem_t tobj);
        static void SetAppName(struct ohos_data_unifiedDataChannel_SystemDefinedAppItem_t tobj, struct TString appName);
        static struct TString GetAppIconId(struct ohos_data_unifiedDataChannel_SystemDefinedAppItem_t tobj);
        static void SetAppIconId(struct ohos_data_unifiedDataChannel_SystemDefinedAppItem_t tobj, struct TString appIconId);
        static struct TString GetAppLabelId(struct ohos_data_unifiedDataChannel_SystemDefinedAppItem_t tobj);
        static void SetAppLabelId(struct ohos_data_unifiedDataChannel_SystemDefinedAppItem_t tobj, struct TString appLabelId);
        static struct TString GetBundleName(struct ohos_data_unifiedDataChannel_SystemDefinedAppItem_t tobj);
        static void SetBundleName(struct ohos_data_unifiedDataChannel_SystemDefinedAppItem_t tobj, struct TString bundleName);
        static struct TString GetAbilityName(struct ohos_data_unifiedDataChannel_SystemDefinedAppItem_t tobj);
        static void SetAbilityName(struct ohos_data_unifiedDataChannel_SystemDefinedAppItem_t tobj, struct TString abilityName);
        static int64_t GetInner(struct ohos_data_unifiedDataChannel_SystemDefinedAppItem_t tobj);
    };
    template<typename Impl>
    static constexpr ohos_data_unifiedDataChannel_SystemDefinedAppItem_ftable ftbl_impl = {
        .GetType = &methods_impl<Impl>::GetType,
        .GetValue = &methods_impl<Impl>::GetValue,
        .GetDetails = &methods_impl<Impl>::GetDetails,
        .SetDetails = &methods_impl<Impl>::SetDetails,
        .GetAppId = &methods_impl<Impl>::GetAppId,
        .SetAppId = &methods_impl<Impl>::SetAppId,
        .GetAppName = &methods_impl<Impl>::GetAppName,
        .SetAppName = &methods_impl<Impl>::SetAppName,
        .GetAppIconId = &methods_impl<Impl>::GetAppIconId,
        .SetAppIconId = &methods_impl<Impl>::SetAppIconId,
        .GetAppLabelId = &methods_impl<Impl>::GetAppLabelId,
        .SetAppLabelId = &methods_impl<Impl>::SetAppLabelId,
        .GetBundleName = &methods_impl<Impl>::GetBundleName,
        .SetBundleName = &methods_impl<Impl>::SetBundleName,
        .GetAbilityName = &methods_impl<Impl>::GetAbilityName,
        .SetAbilityName = &methods_impl<Impl>::SetAbilityName,
        .GetInner = &methods_impl<Impl>::GetInner,
    };
    template<typename Impl>
    static constexpr ohos_data_unifiedDataChannel_SystemDefinedAppItem_vtable vtbl_impl = {
        .ftbl_ptr_0 = &::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItem::template ftbl_impl<Impl>,
    };
    struct rtti_type {
        uint64_t version;
        void (*free)(struct DataBlockHead *);
        uint64_t len;
        struct IdMapItem idmap[1];
    };
    template<typename Impl>
    static constexpr rtti_type rtti_impl = {
        .version = 0,
        .free = &::taihe::del_data_ptr<Impl>,
        .len = 1,
        .idmap = {
            {&ohos_data_unifiedDataChannel_SystemDefinedAppItem_i, &vtbl_impl<Impl>.ftbl_ptr_0},
        },
    };
    static constexpr void const* iid = &ohos_data_unifiedDataChannel_SystemDefinedAppItem_i;
    using vtable_t = ohos_data_unifiedDataChannel_SystemDefinedAppItem_vtable;
    explicit operator bool() const& { return m_handle.vtbl_ptr; }
    virtual_type const& operator*() const& {
        return *reinterpret_cast<virtual_type const*>(&m_handle);
    }
    virtual_type const* operator->() const& {
        return reinterpret_cast<virtual_type const*>(&m_handle);
    }
};
}
namespace ohos::data::unifiedDataChannel {
struct SystemDefinedAppItem : public ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItem {
    static constexpr bool is_holder = true;
    explicit SystemDefinedAppItem(struct ohos_data_unifiedDataChannel_SystemDefinedAppItem_t handle) : ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItem(handle) {}
    SystemDefinedAppItem& operator=(::ohos::data::unifiedDataChannel::SystemDefinedAppItem other) {
        ::std::swap(m_handle, other.m_handle);
        return *this;
    }
    ~SystemDefinedAppItem() {
        ohos_data_unifiedDataChannel_SystemDefinedAppItem_drop(m_handle);
    }
    explicit SystemDefinedAppItem(::taihe::data_holder other) : SystemDefinedAppItem(ohos_data_unifiedDataChannel_SystemDefinedAppItem_dynamic(other.data_ptr)) {
        other.data_ptr = nullptr;
    }
    operator ::taihe::data_view() const& {
        struct ohos_data_unifiedDataChannel_SystemDefinedAppItem_t ret_handle = m_handle;
        return ::taihe::data_view(ret_handle.data_ptr);
    }
    operator ::taihe::data_holder() const& {
        struct ohos_data_unifiedDataChannel_SystemDefinedAppItem_t ret_handle = ohos_data_unifiedDataChannel_SystemDefinedAppItem_copy(m_handle);
        return ::taihe::data_holder(ret_handle.data_ptr);
    }
    operator ::taihe::data_holder() && {
        struct ohos_data_unifiedDataChannel_SystemDefinedAppItem_t ret_handle = m_handle;
        m_handle.data_ptr = nullptr;
        return ::taihe::data_holder(ret_handle.data_ptr);
    }
    SystemDefinedAppItem(::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItem const& other) : SystemDefinedAppItem(ohos_data_unifiedDataChannel_SystemDefinedAppItem_copy(other.m_handle)) {}
    SystemDefinedAppItem(::ohos::data::unifiedDataChannel::SystemDefinedAppItem const& other) : SystemDefinedAppItem(ohos_data_unifiedDataChannel_SystemDefinedAppItem_copy(other.m_handle)) {}
    SystemDefinedAppItem(::ohos::data::unifiedDataChannel::SystemDefinedAppItem&& other) : SystemDefinedAppItem(other.m_handle) {
        other.m_handle.data_ptr = nullptr;
    }
    template<typename Impl, typename... Args>
    static ::ohos::data::unifiedDataChannel::SystemDefinedAppItem from(Args&&... args) {
        return ::ohos::data::unifiedDataChannel::SystemDefinedAppItem{{
            .vtbl_ptr = &vtbl_impl<Impl>,
            .data_ptr = ::taihe::new_data_ptr<Impl>(reinterpret_cast<TypeInfo const*>(&rtti_impl<Impl>), std::forward<Args>(args)...),
        }};
    }
    template<typename Impl>
    static ::ohos::data::unifiedDataChannel::SystemDefinedAppItem from(Impl&& impl) {
        return ::ohos::data::unifiedDataChannel::SystemDefinedAppItem{{
            .vtbl_ptr = &vtbl_impl<Impl>,
            .data_ptr = ::taihe::new_data_ptr<Impl>(reinterpret_cast<TypeInfo const*>(&rtti_impl<Impl>), std::forward<Impl>(impl)),
        }};
    }
};
}
namespace taihe {
template<>
struct as_abi<::ohos::data::unifiedDataChannel::SystemDefinedAppItem> {
    using type = struct ohos_data_unifiedDataChannel_SystemDefinedAppItem_t;
};
template<>
struct as_abi<::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItem> {
    using type = struct ohos_data_unifiedDataChannel_SystemDefinedAppItem_t;
};
template<>
struct as_param<::ohos::data::unifiedDataChannel::SystemDefinedAppItem> {
    using type = ::ohos::data::unifiedDataChannel::weak::SystemDefinedAppItem;
};
}
