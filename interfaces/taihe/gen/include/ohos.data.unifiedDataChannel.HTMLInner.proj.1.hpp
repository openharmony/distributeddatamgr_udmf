#pragma once
#include "taihe/object.hpp"
#include "ohos.data.unifiedDataChannel.HTMLInner.proj.0.hpp"
#include "ohos.data.unifiedDataChannel.HTMLInner.abi.1.h"
#include "taihe/string.hpp"
#include "ohos.data.unifiedDataChannel.ValueType.proj.0.hpp"
#include "taihe/optional.hpp"
#include "taihe/map.hpp"
namespace ohos::data::unifiedDataChannel::weak {
struct HTMLInner {
    static constexpr bool is_holder = false;
    struct ohos_data_unifiedDataChannel_HTMLInner_t m_handle;
    explicit HTMLInner(struct ohos_data_unifiedDataChannel_HTMLInner_t handle) : m_handle(handle) {}
    explicit HTMLInner(::taihe::data_view other) : HTMLInner(ohos_data_unifiedDataChannel_HTMLInner_dynamic(other.data_ptr)) {}
    operator ::taihe::data_view() const& {
        struct ohos_data_unifiedDataChannel_HTMLInner_t ret_handle = m_handle;
        return ::taihe::data_view(ret_handle.data_ptr);
    }
    operator ::taihe::data_holder() const& {
        struct ohos_data_unifiedDataChannel_HTMLInner_t ret_handle = ohos_data_unifiedDataChannel_HTMLInner_copy(m_handle);
        return ::taihe::data_holder(ret_handle.data_ptr);
    }
    struct virtual_type {
        ::taihe::string GetType() const&;
        ::ohos::data::unifiedDataChannel::ValueType GetValue() const&;
        ::taihe::optional<::taihe::map<::taihe::string, ::taihe::string>> GetDetails() const&;
        void SetDetails(::taihe::map_view<::taihe::string, ::taihe::string> details) const&;
        void SetHtmlContent(::taihe::string_view htmlContent) const&;
        ::taihe::string GetHtmlContent() const&;
        void SetPlainContent(::taihe::string_view plainContent) const&;
        ::taihe::string GetPlainContent() const&;
        int64_t GetInner() const&;
    };
    template<typename Impl>
    struct methods_impl {
        static struct TString GetType(struct ohos_data_unifiedDataChannel_HTMLInner_t tobj);
        static struct ohos_data_unifiedDataChannel_ValueType_t GetValue(struct ohos_data_unifiedDataChannel_HTMLInner_t tobj);
        static struct TOptional GetDetails(struct ohos_data_unifiedDataChannel_HTMLInner_t tobj);
        static void SetDetails(struct ohos_data_unifiedDataChannel_HTMLInner_t tobj, void* details);
        static void SetHtmlContent(struct ohos_data_unifiedDataChannel_HTMLInner_t tobj, struct TString htmlContent);
        static struct TString GetHtmlContent(struct ohos_data_unifiedDataChannel_HTMLInner_t tobj);
        static void SetPlainContent(struct ohos_data_unifiedDataChannel_HTMLInner_t tobj, struct TString plainContent);
        static struct TString GetPlainContent(struct ohos_data_unifiedDataChannel_HTMLInner_t tobj);
        static int64_t GetInner(struct ohos_data_unifiedDataChannel_HTMLInner_t tobj);
    };
    template<typename Impl>
    static constexpr ohos_data_unifiedDataChannel_HTMLInner_ftable ftbl_impl = {
        .GetType = &methods_impl<Impl>::GetType,
        .GetValue = &methods_impl<Impl>::GetValue,
        .GetDetails = &methods_impl<Impl>::GetDetails,
        .SetDetails = &methods_impl<Impl>::SetDetails,
        .SetHtmlContent = &methods_impl<Impl>::SetHtmlContent,
        .GetHtmlContent = &methods_impl<Impl>::GetHtmlContent,
        .SetPlainContent = &methods_impl<Impl>::SetPlainContent,
        .GetPlainContent = &methods_impl<Impl>::GetPlainContent,
        .GetInner = &methods_impl<Impl>::GetInner,
    };
    template<typename Impl>
    static constexpr ohos_data_unifiedDataChannel_HTMLInner_vtable vtbl_impl = {
        .ftbl_ptr_0 = &::ohos::data::unifiedDataChannel::weak::HTMLInner::template ftbl_impl<Impl>,
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
            {&ohos_data_unifiedDataChannel_HTMLInner_i, &vtbl_impl<Impl>.ftbl_ptr_0},
        },
    };
    static constexpr void const* iid = &ohos_data_unifiedDataChannel_HTMLInner_i;
    using vtable_t = ohos_data_unifiedDataChannel_HTMLInner_vtable;
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
struct HTMLInner : public ::ohos::data::unifiedDataChannel::weak::HTMLInner {
    static constexpr bool is_holder = true;
    explicit HTMLInner(struct ohos_data_unifiedDataChannel_HTMLInner_t handle) : ::ohos::data::unifiedDataChannel::weak::HTMLInner(handle) {}
    HTMLInner& operator=(::ohos::data::unifiedDataChannel::HTMLInner other) {
        ::std::swap(m_handle, other.m_handle);
        return *this;
    }
    ~HTMLInner() {
        ohos_data_unifiedDataChannel_HTMLInner_drop(m_handle);
    }
    explicit HTMLInner(::taihe::data_holder other) : HTMLInner(ohos_data_unifiedDataChannel_HTMLInner_dynamic(other.data_ptr)) {
        other.data_ptr = nullptr;
    }
    operator ::taihe::data_view() const& {
        struct ohos_data_unifiedDataChannel_HTMLInner_t ret_handle = m_handle;
        return ::taihe::data_view(ret_handle.data_ptr);
    }
    operator ::taihe::data_holder() const& {
        struct ohos_data_unifiedDataChannel_HTMLInner_t ret_handle = ohos_data_unifiedDataChannel_HTMLInner_copy(m_handle);
        return ::taihe::data_holder(ret_handle.data_ptr);
    }
    operator ::taihe::data_holder() && {
        struct ohos_data_unifiedDataChannel_HTMLInner_t ret_handle = m_handle;
        m_handle.data_ptr = nullptr;
        return ::taihe::data_holder(ret_handle.data_ptr);
    }
    HTMLInner(::ohos::data::unifiedDataChannel::weak::HTMLInner const& other) : HTMLInner(ohos_data_unifiedDataChannel_HTMLInner_copy(other.m_handle)) {}
    HTMLInner(::ohos::data::unifiedDataChannel::HTMLInner const& other) : HTMLInner(ohos_data_unifiedDataChannel_HTMLInner_copy(other.m_handle)) {}
    HTMLInner(::ohos::data::unifiedDataChannel::HTMLInner&& other) : HTMLInner(other.m_handle) {
        other.m_handle.data_ptr = nullptr;
    }
    template<typename Impl, typename... Args>
    static ::ohos::data::unifiedDataChannel::HTMLInner from(Args&&... args) {
        return ::ohos::data::unifiedDataChannel::HTMLInner{{
            .vtbl_ptr = &vtbl_impl<Impl>,
            .data_ptr = ::taihe::new_data_ptr<Impl>(reinterpret_cast<TypeInfo const*>(&rtti_impl<Impl>), std::forward<Args>(args)...),
        }};
    }
    template<typename Impl>
    static ::ohos::data::unifiedDataChannel::HTMLInner from(Impl&& impl) {
        return ::ohos::data::unifiedDataChannel::HTMLInner{{
            .vtbl_ptr = &vtbl_impl<Impl>,
            .data_ptr = ::taihe::new_data_ptr<Impl>(reinterpret_cast<TypeInfo const*>(&rtti_impl<Impl>), std::forward<Impl>(impl)),
        }};
    }
};
}
namespace taihe {
template<>
struct as_abi<::ohos::data::unifiedDataChannel::HTMLInner> {
    using type = struct ohos_data_unifiedDataChannel_HTMLInner_t;
};
template<>
struct as_abi<::ohos::data::unifiedDataChannel::weak::HTMLInner> {
    using type = struct ohos_data_unifiedDataChannel_HTMLInner_t;
};
template<>
struct as_param<::ohos::data::unifiedDataChannel::HTMLInner> {
    using type = ::ohos::data::unifiedDataChannel::weak::HTMLInner;
};
}
