#pragma once
#include "taihe/object.hpp"
#include "ohos.data.unifiedDataChannel.HyperlinkInner.proj.0.hpp"
#include "ohos.data.unifiedDataChannel.HyperlinkInner.abi.1.h"
#include "taihe/string.hpp"
#include "ohos.data.unifiedDataChannel.ValueType.proj.0.hpp"
#include "taihe/optional.hpp"
#include "taihe/map.hpp"
namespace ohos::data::unifiedDataChannel::weak {
struct HyperlinkInner {
    static constexpr bool is_holder = false;
    struct ohos_data_unifiedDataChannel_HyperlinkInner_t m_handle;
    explicit HyperlinkInner(struct ohos_data_unifiedDataChannel_HyperlinkInner_t handle) : m_handle(handle) {}
    explicit HyperlinkInner(::taihe::data_view other) : HyperlinkInner(ohos_data_unifiedDataChannel_HyperlinkInner_dynamic(other.data_ptr)) {}
    operator ::taihe::data_view() const& {
        struct ohos_data_unifiedDataChannel_HyperlinkInner_t ret_handle = m_handle;
        return ::taihe::data_view(ret_handle.data_ptr);
    }
    operator ::taihe::data_holder() const& {
        struct ohos_data_unifiedDataChannel_HyperlinkInner_t ret_handle = ohos_data_unifiedDataChannel_HyperlinkInner_copy(m_handle);
        return ::taihe::data_holder(ret_handle.data_ptr);
    }
    struct virtual_type {
        ::taihe::string GetType() const&;
        ::ohos::data::unifiedDataChannel::ValueType GetValue() const&;
        ::taihe::optional<::taihe::map<::taihe::string, ::taihe::string>> GetDetails() const&;
        void SetDetails(::taihe::map_view<::taihe::string, ::taihe::string> details) const&;
        void SetUrl(::taihe::string_view url) const&;
        ::taihe::string GetUrl() const&;
        void SetDescription(::taihe::string_view description) const&;
        ::taihe::string GetDescription() const&;
        int64_t GetInner() const&;
    };
    template<typename Impl>
    struct methods_impl {
        static struct TString GetType(struct ohos_data_unifiedDataChannel_HyperlinkInner_t tobj);
        static struct ohos_data_unifiedDataChannel_ValueType_t GetValue(struct ohos_data_unifiedDataChannel_HyperlinkInner_t tobj);
        static struct TOptional GetDetails(struct ohos_data_unifiedDataChannel_HyperlinkInner_t tobj);
        static void SetDetails(struct ohos_data_unifiedDataChannel_HyperlinkInner_t tobj, void* details);
        static void SetUrl(struct ohos_data_unifiedDataChannel_HyperlinkInner_t tobj, struct TString url);
        static struct TString GetUrl(struct ohos_data_unifiedDataChannel_HyperlinkInner_t tobj);
        static void SetDescription(struct ohos_data_unifiedDataChannel_HyperlinkInner_t tobj, struct TString description);
        static struct TString GetDescription(struct ohos_data_unifiedDataChannel_HyperlinkInner_t tobj);
        static int64_t GetInner(struct ohos_data_unifiedDataChannel_HyperlinkInner_t tobj);
    };
    template<typename Impl>
    static constexpr ohos_data_unifiedDataChannel_HyperlinkInner_ftable ftbl_impl = {
        .GetType = &methods_impl<Impl>::GetType,
        .GetValue = &methods_impl<Impl>::GetValue,
        .GetDetails = &methods_impl<Impl>::GetDetails,
        .SetDetails = &methods_impl<Impl>::SetDetails,
        .SetUrl = &methods_impl<Impl>::SetUrl,
        .GetUrl = &methods_impl<Impl>::GetUrl,
        .SetDescription = &methods_impl<Impl>::SetDescription,
        .GetDescription = &methods_impl<Impl>::GetDescription,
        .GetInner = &methods_impl<Impl>::GetInner,
    };
    template<typename Impl>
    static constexpr ohos_data_unifiedDataChannel_HyperlinkInner_vtable vtbl_impl = {
        .ftbl_ptr_0 = &::ohos::data::unifiedDataChannel::weak::HyperlinkInner::template ftbl_impl<Impl>,
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
            {&ohos_data_unifiedDataChannel_HyperlinkInner_i, &vtbl_impl<Impl>.ftbl_ptr_0},
        },
    };
    static constexpr void const* iid = &ohos_data_unifiedDataChannel_HyperlinkInner_i;
    using vtable_t = ohos_data_unifiedDataChannel_HyperlinkInner_vtable;
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
struct HyperlinkInner : public ::ohos::data::unifiedDataChannel::weak::HyperlinkInner {
    static constexpr bool is_holder = true;
    explicit HyperlinkInner(struct ohos_data_unifiedDataChannel_HyperlinkInner_t handle) : ::ohos::data::unifiedDataChannel::weak::HyperlinkInner(handle) {}
    HyperlinkInner& operator=(::ohos::data::unifiedDataChannel::HyperlinkInner other) {
        ::std::swap(m_handle, other.m_handle);
        return *this;
    }
    ~HyperlinkInner() {
        ohos_data_unifiedDataChannel_HyperlinkInner_drop(m_handle);
    }
    explicit HyperlinkInner(::taihe::data_holder other) : HyperlinkInner(ohos_data_unifiedDataChannel_HyperlinkInner_dynamic(other.data_ptr)) {
        other.data_ptr = nullptr;
    }
    operator ::taihe::data_view() const& {
        struct ohos_data_unifiedDataChannel_HyperlinkInner_t ret_handle = m_handle;
        return ::taihe::data_view(ret_handle.data_ptr);
    }
    operator ::taihe::data_holder() const& {
        struct ohos_data_unifiedDataChannel_HyperlinkInner_t ret_handle = ohos_data_unifiedDataChannel_HyperlinkInner_copy(m_handle);
        return ::taihe::data_holder(ret_handle.data_ptr);
    }
    operator ::taihe::data_holder() && {
        struct ohos_data_unifiedDataChannel_HyperlinkInner_t ret_handle = m_handle;
        m_handle.data_ptr = nullptr;
        return ::taihe::data_holder(ret_handle.data_ptr);
    }
    HyperlinkInner(::ohos::data::unifiedDataChannel::weak::HyperlinkInner const& other) : HyperlinkInner(ohos_data_unifiedDataChannel_HyperlinkInner_copy(other.m_handle)) {}
    HyperlinkInner(::ohos::data::unifiedDataChannel::HyperlinkInner const& other) : HyperlinkInner(ohos_data_unifiedDataChannel_HyperlinkInner_copy(other.m_handle)) {}
    HyperlinkInner(::ohos::data::unifiedDataChannel::HyperlinkInner&& other) : HyperlinkInner(other.m_handle) {
        other.m_handle.data_ptr = nullptr;
    }
    template<typename Impl, typename... Args>
    static ::ohos::data::unifiedDataChannel::HyperlinkInner from(Args&&... args) {
        return ::ohos::data::unifiedDataChannel::HyperlinkInner{{
            .vtbl_ptr = &vtbl_impl<Impl>,
            .data_ptr = ::taihe::new_data_ptr<Impl>(reinterpret_cast<TypeInfo const*>(&rtti_impl<Impl>), std::forward<Args>(args)...),
        }};
    }
    template<typename Impl>
    static ::ohos::data::unifiedDataChannel::HyperlinkInner from(Impl&& impl) {
        return ::ohos::data::unifiedDataChannel::HyperlinkInner{{
            .vtbl_ptr = &vtbl_impl<Impl>,
            .data_ptr = ::taihe::new_data_ptr<Impl>(reinterpret_cast<TypeInfo const*>(&rtti_impl<Impl>), std::forward<Impl>(impl)),
        }};
    }
};
}
namespace taihe {
template<>
struct as_abi<::ohos::data::unifiedDataChannel::HyperlinkInner> {
    using type = struct ohos_data_unifiedDataChannel_HyperlinkInner_t;
};
template<>
struct as_abi<::ohos::data::unifiedDataChannel::weak::HyperlinkInner> {
    using type = struct ohos_data_unifiedDataChannel_HyperlinkInner_t;
};
template<>
struct as_param<::ohos::data::unifiedDataChannel::HyperlinkInner> {
    using type = ::ohos::data::unifiedDataChannel::weak::HyperlinkInner;
};
}
