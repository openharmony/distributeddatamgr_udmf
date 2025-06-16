#pragma once
#include "taihe/object.hpp"
#include "ohos.data.unifiedDataChannel.SystemDefinedFormInner.proj.0.hpp"
#include "ohos.data.unifiedDataChannel.SystemDefinedFormInner.abi.1.h"
#include "taihe/string.hpp"
#include "ohos.data.unifiedDataChannel.ValueType.proj.0.hpp"
#include "taihe/optional.hpp"
#include "taihe/map.hpp"
#include "ohos.data.unifiedDataChannel.DetailsValue.proj.0.hpp"
namespace ohos::data::unifiedDataChannel::weak {
struct SystemDefinedFormInner {
    static constexpr bool is_holder = false;
    struct ohos_data_unifiedDataChannel_SystemDefinedFormInner_t m_handle;
    explicit SystemDefinedFormInner(struct ohos_data_unifiedDataChannel_SystemDefinedFormInner_t handle) : m_handle(handle) {}
    explicit SystemDefinedFormInner(::taihe::data_view other) : SystemDefinedFormInner(ohos_data_unifiedDataChannel_SystemDefinedFormInner_dynamic(other.data_ptr)) {}
    operator ::taihe::data_view() const& {
        struct ohos_data_unifiedDataChannel_SystemDefinedFormInner_t ret_handle = m_handle;
        return ::taihe::data_view(ret_handle.data_ptr);
    }
    operator ::taihe::data_holder() const& {
        struct ohos_data_unifiedDataChannel_SystemDefinedFormInner_t ret_handle = ohos_data_unifiedDataChannel_SystemDefinedFormInner_copy(m_handle);
        return ::taihe::data_holder(ret_handle.data_ptr);
    }
    struct virtual_type {
        ::taihe::string GetType() const&;
        ::ohos::data::unifiedDataChannel::ValueType GetValue() const&;
        ::taihe::optional<::taihe::map<::taihe::string, ::ohos::data::unifiedDataChannel::DetailsValue>> GetDetails() const&;
        void SetDetails(::taihe::map_view<::taihe::string, ::ohos::data::unifiedDataChannel::DetailsValue> details) const&;
        double GetFormId() const&;
        void SetFormId(double formId) const&;
        ::taihe::string GetFormName() const&;
        void SetFormName(::taihe::string_view formName) const&;
        ::taihe::string GetBundleName() const&;
        void SetBundleName(::taihe::string_view bundleName) const&;
        ::taihe::string GetAbilityName() const&;
        void SetAbilityName(::taihe::string_view abilityName) const&;
        ::taihe::string GetModule() const&;
        void SetModule(::taihe::string_view module) const&;
        int64_t GetInner() const&;
    };
    template<typename Impl>
    struct methods_impl {
        static struct TString GetType(struct ohos_data_unifiedDataChannel_SystemDefinedFormInner_t tobj);
        static struct ohos_data_unifiedDataChannel_ValueType_t GetValue(struct ohos_data_unifiedDataChannel_SystemDefinedFormInner_t tobj);
        static struct TOptional GetDetails(struct ohos_data_unifiedDataChannel_SystemDefinedFormInner_t tobj);
        static void SetDetails(struct ohos_data_unifiedDataChannel_SystemDefinedFormInner_t tobj, void* details);
        static double GetFormId(struct ohos_data_unifiedDataChannel_SystemDefinedFormInner_t tobj);
        static void SetFormId(struct ohos_data_unifiedDataChannel_SystemDefinedFormInner_t tobj, double formId);
        static struct TString GetFormName(struct ohos_data_unifiedDataChannel_SystemDefinedFormInner_t tobj);
        static void SetFormName(struct ohos_data_unifiedDataChannel_SystemDefinedFormInner_t tobj, struct TString formName);
        static struct TString GetBundleName(struct ohos_data_unifiedDataChannel_SystemDefinedFormInner_t tobj);
        static void SetBundleName(struct ohos_data_unifiedDataChannel_SystemDefinedFormInner_t tobj, struct TString bundleName);
        static struct TString GetAbilityName(struct ohos_data_unifiedDataChannel_SystemDefinedFormInner_t tobj);
        static void SetAbilityName(struct ohos_data_unifiedDataChannel_SystemDefinedFormInner_t tobj, struct TString abilityName);
        static struct TString GetModule(struct ohos_data_unifiedDataChannel_SystemDefinedFormInner_t tobj);
        static void SetModule(struct ohos_data_unifiedDataChannel_SystemDefinedFormInner_t tobj, struct TString module);
        static int64_t GetInner(struct ohos_data_unifiedDataChannel_SystemDefinedFormInner_t tobj);
    };
    template<typename Impl>
    static constexpr ohos_data_unifiedDataChannel_SystemDefinedFormInner_ftable ftbl_impl = {
        .GetType = &methods_impl<Impl>::GetType,
        .GetValue = &methods_impl<Impl>::GetValue,
        .GetDetails = &methods_impl<Impl>::GetDetails,
        .SetDetails = &methods_impl<Impl>::SetDetails,
        .GetFormId = &methods_impl<Impl>::GetFormId,
        .SetFormId = &methods_impl<Impl>::SetFormId,
        .GetFormName = &methods_impl<Impl>::GetFormName,
        .SetFormName = &methods_impl<Impl>::SetFormName,
        .GetBundleName = &methods_impl<Impl>::GetBundleName,
        .SetBundleName = &methods_impl<Impl>::SetBundleName,
        .GetAbilityName = &methods_impl<Impl>::GetAbilityName,
        .SetAbilityName = &methods_impl<Impl>::SetAbilityName,
        .GetModule = &methods_impl<Impl>::GetModule,
        .SetModule = &methods_impl<Impl>::SetModule,
        .GetInner = &methods_impl<Impl>::GetInner,
    };
    template<typename Impl>
    static constexpr ohos_data_unifiedDataChannel_SystemDefinedFormInner_vtable vtbl_impl = {
        .ftbl_ptr_0 = &::ohos::data::unifiedDataChannel::weak::SystemDefinedFormInner::template ftbl_impl<Impl>,
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
            {&ohos_data_unifiedDataChannel_SystemDefinedFormInner_i, &vtbl_impl<Impl>.ftbl_ptr_0},
        },
    };
    static constexpr void const* iid = &ohos_data_unifiedDataChannel_SystemDefinedFormInner_i;
    using vtable_t = ohos_data_unifiedDataChannel_SystemDefinedFormInner_vtable;
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
struct SystemDefinedFormInner : public ::ohos::data::unifiedDataChannel::weak::SystemDefinedFormInner {
    static constexpr bool is_holder = true;
    explicit SystemDefinedFormInner(struct ohos_data_unifiedDataChannel_SystemDefinedFormInner_t handle) : ::ohos::data::unifiedDataChannel::weak::SystemDefinedFormInner(handle) {}
    SystemDefinedFormInner& operator=(::ohos::data::unifiedDataChannel::SystemDefinedFormInner other) {
        ::std::swap(m_handle, other.m_handle);
        return *this;
    }
    ~SystemDefinedFormInner() {
        ohos_data_unifiedDataChannel_SystemDefinedFormInner_drop(m_handle);
    }
    explicit SystemDefinedFormInner(::taihe::data_holder other) : SystemDefinedFormInner(ohos_data_unifiedDataChannel_SystemDefinedFormInner_dynamic(other.data_ptr)) {
        other.data_ptr = nullptr;
    }
    operator ::taihe::data_view() const& {
        struct ohos_data_unifiedDataChannel_SystemDefinedFormInner_t ret_handle = m_handle;
        return ::taihe::data_view(ret_handle.data_ptr);
    }
    operator ::taihe::data_holder() const& {
        struct ohos_data_unifiedDataChannel_SystemDefinedFormInner_t ret_handle = ohos_data_unifiedDataChannel_SystemDefinedFormInner_copy(m_handle);
        return ::taihe::data_holder(ret_handle.data_ptr);
    }
    operator ::taihe::data_holder() && {
        struct ohos_data_unifiedDataChannel_SystemDefinedFormInner_t ret_handle = m_handle;
        m_handle.data_ptr = nullptr;
        return ::taihe::data_holder(ret_handle.data_ptr);
    }
    SystemDefinedFormInner(::ohos::data::unifiedDataChannel::weak::SystemDefinedFormInner const& other) : SystemDefinedFormInner(ohos_data_unifiedDataChannel_SystemDefinedFormInner_copy(other.m_handle)) {}
    SystemDefinedFormInner(::ohos::data::unifiedDataChannel::SystemDefinedFormInner const& other) : SystemDefinedFormInner(ohos_data_unifiedDataChannel_SystemDefinedFormInner_copy(other.m_handle)) {}
    SystemDefinedFormInner(::ohos::data::unifiedDataChannel::SystemDefinedFormInner&& other) : SystemDefinedFormInner(other.m_handle) {
        other.m_handle.data_ptr = nullptr;
    }
    template<typename Impl, typename... Args>
    static ::ohos::data::unifiedDataChannel::SystemDefinedFormInner from(Args&&... args) {
        return ::ohos::data::unifiedDataChannel::SystemDefinedFormInner{{
            .vtbl_ptr = &vtbl_impl<Impl>,
            .data_ptr = ::taihe::new_data_ptr<Impl>(reinterpret_cast<TypeInfo const*>(&rtti_impl<Impl>), std::forward<Args>(args)...),
        }};
    }
    template<typename Impl>
    static ::ohos::data::unifiedDataChannel::SystemDefinedFormInner from(Impl&& impl) {
        return ::ohos::data::unifiedDataChannel::SystemDefinedFormInner{{
            .vtbl_ptr = &vtbl_impl<Impl>,
            .data_ptr = ::taihe::new_data_ptr<Impl>(reinterpret_cast<TypeInfo const*>(&rtti_impl<Impl>), std::forward<Impl>(impl)),
        }};
    }
};
}
namespace taihe {
template<>
struct as_abi<::ohos::data::unifiedDataChannel::SystemDefinedFormInner> {
    using type = struct ohos_data_unifiedDataChannel_SystemDefinedFormInner_t;
};
template<>
struct as_abi<::ohos::data::unifiedDataChannel::weak::SystemDefinedFormInner> {
    using type = struct ohos_data_unifiedDataChannel_SystemDefinedFormInner_t;
};
template<>
struct as_param<::ohos::data::unifiedDataChannel::SystemDefinedFormInner> {
    using type = ::ohos::data::unifiedDataChannel::weak::SystemDefinedFormInner;
};
}
