#pragma once
#include "taihe/object.hpp"
#include "ohos.data.unifiedDataChannel.PlainTextInner.proj.0.hpp"
#include "ohos.data.unifiedDataChannel.PlainTextInner.abi.1.h"
#include "taihe/string.hpp"
#include "ohos.data.unifiedDataChannel.ValueType.proj.0.hpp"
#include "taihe/optional.hpp"
#include "taihe/map.hpp"
namespace ohos::data::unifiedDataChannel::weak {
struct PlainTextInner {
    static constexpr bool is_holder = false;
    struct ohos_data_unifiedDataChannel_PlainTextInner_t m_handle;
    explicit PlainTextInner(struct ohos_data_unifiedDataChannel_PlainTextInner_t handle) : m_handle(handle) {}
    explicit PlainTextInner(::taihe::data_view other) : PlainTextInner(ohos_data_unifiedDataChannel_PlainTextInner_dynamic(other.data_ptr)) {}
    operator ::taihe::data_view() const& {
        struct ohos_data_unifiedDataChannel_PlainTextInner_t ret_handle = m_handle;
        return ::taihe::data_view(ret_handle.data_ptr);
    }
    operator ::taihe::data_holder() const& {
        struct ohos_data_unifiedDataChannel_PlainTextInner_t ret_handle = ohos_data_unifiedDataChannel_PlainTextInner_copy(m_handle);
        return ::taihe::data_holder(ret_handle.data_ptr);
    }
    struct virtual_type {
        ::taihe::string GetType() const&;
        ::ohos::data::unifiedDataChannel::ValueType GetValue() const&;
        ::taihe::optional<::taihe::map<::taihe::string, ::taihe::string>> GetDetails() const&;
        void SetDetails(::taihe::map_view<::taihe::string, ::taihe::string> details) const&;
        void SetTextContent(::taihe::string_view textContent) const&;
        ::taihe::string GetTextContent() const&;
        void SetAbstract1(::taihe::string_view abstract1) const&;
        ::taihe::string GetAbstract1() const&;
        int64_t GetInner() const&;
    };
    template<typename Impl>
    struct methods_impl {
        static struct TString GetType(struct ohos_data_unifiedDataChannel_PlainTextInner_t tobj);
        static struct ohos_data_unifiedDataChannel_ValueType_t GetValue(struct ohos_data_unifiedDataChannel_PlainTextInner_t tobj);
        static struct TOptional GetDetails(struct ohos_data_unifiedDataChannel_PlainTextInner_t tobj);
        static void SetDetails(struct ohos_data_unifiedDataChannel_PlainTextInner_t tobj, void* details);
        static void SetTextContent(struct ohos_data_unifiedDataChannel_PlainTextInner_t tobj, struct TString textContent);
        static struct TString GetTextContent(struct ohos_data_unifiedDataChannel_PlainTextInner_t tobj);
        static void SetAbstract1(struct ohos_data_unifiedDataChannel_PlainTextInner_t tobj, struct TString abstract1);
        static struct TString GetAbstract1(struct ohos_data_unifiedDataChannel_PlainTextInner_t tobj);
        static int64_t GetInner(struct ohos_data_unifiedDataChannel_PlainTextInner_t tobj);
    };
    template<typename Impl>
    static constexpr ohos_data_unifiedDataChannel_PlainTextInner_ftable ftbl_impl = {
        .GetType = &methods_impl<Impl>::GetType,
        .GetValue = &methods_impl<Impl>::GetValue,
        .GetDetails = &methods_impl<Impl>::GetDetails,
        .SetDetails = &methods_impl<Impl>::SetDetails,
        .SetTextContent = &methods_impl<Impl>::SetTextContent,
        .GetTextContent = &methods_impl<Impl>::GetTextContent,
        .SetAbstract1 = &methods_impl<Impl>::SetAbstract1,
        .GetAbstract1 = &methods_impl<Impl>::GetAbstract1,
        .GetInner = &methods_impl<Impl>::GetInner,
    };
    template<typename Impl>
    static constexpr ohos_data_unifiedDataChannel_PlainTextInner_vtable vtbl_impl = {
        .ftbl_ptr_0 = &::ohos::data::unifiedDataChannel::weak::PlainTextInner::template ftbl_impl<Impl>,
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
            {&ohos_data_unifiedDataChannel_PlainTextInner_i, &vtbl_impl<Impl>.ftbl_ptr_0},
        },
    };
    static constexpr void const* iid = &ohos_data_unifiedDataChannel_PlainTextInner_i;
    using vtable_t = ohos_data_unifiedDataChannel_PlainTextInner_vtable;
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
struct PlainTextInner : public ::ohos::data::unifiedDataChannel::weak::PlainTextInner {
    static constexpr bool is_holder = true;
    explicit PlainTextInner(struct ohos_data_unifiedDataChannel_PlainTextInner_t handle) : ::ohos::data::unifiedDataChannel::weak::PlainTextInner(handle) {}
    PlainTextInner& operator=(::ohos::data::unifiedDataChannel::PlainTextInner other) {
        ::std::swap(m_handle, other.m_handle);
        return *this;
    }
    ~PlainTextInner() {
        ohos_data_unifiedDataChannel_PlainTextInner_drop(m_handle);
    }
    explicit PlainTextInner(::taihe::data_holder other) : PlainTextInner(ohos_data_unifiedDataChannel_PlainTextInner_dynamic(other.data_ptr)) {
        other.data_ptr = nullptr;
    }
    operator ::taihe::data_view() const& {
        struct ohos_data_unifiedDataChannel_PlainTextInner_t ret_handle = m_handle;
        return ::taihe::data_view(ret_handle.data_ptr);
    }
    operator ::taihe::data_holder() const& {
        struct ohos_data_unifiedDataChannel_PlainTextInner_t ret_handle = ohos_data_unifiedDataChannel_PlainTextInner_copy(m_handle);
        return ::taihe::data_holder(ret_handle.data_ptr);
    }
    operator ::taihe::data_holder() && {
        struct ohos_data_unifiedDataChannel_PlainTextInner_t ret_handle = m_handle;
        m_handle.data_ptr = nullptr;
        return ::taihe::data_holder(ret_handle.data_ptr);
    }
    PlainTextInner(::ohos::data::unifiedDataChannel::weak::PlainTextInner const& other) : PlainTextInner(ohos_data_unifiedDataChannel_PlainTextInner_copy(other.m_handle)) {}
    PlainTextInner(::ohos::data::unifiedDataChannel::PlainTextInner const& other) : PlainTextInner(ohos_data_unifiedDataChannel_PlainTextInner_copy(other.m_handle)) {}
    PlainTextInner(::ohos::data::unifiedDataChannel::PlainTextInner&& other) : PlainTextInner(other.m_handle) {
        other.m_handle.data_ptr = nullptr;
    }
    template<typename Impl, typename... Args>
    static ::ohos::data::unifiedDataChannel::PlainTextInner from(Args&&... args) {
        return ::ohos::data::unifiedDataChannel::PlainTextInner{{
            .vtbl_ptr = &vtbl_impl<Impl>,
            .data_ptr = ::taihe::new_data_ptr<Impl>(reinterpret_cast<TypeInfo const*>(&rtti_impl<Impl>), std::forward<Args>(args)...),
        }};
    }
    template<typename Impl>
    static ::ohos::data::unifiedDataChannel::PlainTextInner from(Impl&& impl) {
        return ::ohos::data::unifiedDataChannel::PlainTextInner{{
            .vtbl_ptr = &vtbl_impl<Impl>,
            .data_ptr = ::taihe::new_data_ptr<Impl>(reinterpret_cast<TypeInfo const*>(&rtti_impl<Impl>), std::forward<Impl>(impl)),
        }};
    }
};
}
namespace taihe {
template<>
struct as_abi<::ohos::data::unifiedDataChannel::PlainTextInner> {
    using type = struct ohos_data_unifiedDataChannel_PlainTextInner_t;
};
template<>
struct as_abi<::ohos::data::unifiedDataChannel::weak::PlainTextInner> {
    using type = struct ohos_data_unifiedDataChannel_PlainTextInner_t;
};
template<>
struct as_param<::ohos::data::unifiedDataChannel::PlainTextInner> {
    using type = ::ohos::data::unifiedDataChannel::weak::PlainTextInner;
};
}
