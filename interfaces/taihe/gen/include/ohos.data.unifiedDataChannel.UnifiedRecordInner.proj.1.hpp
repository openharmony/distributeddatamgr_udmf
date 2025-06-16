#pragma once
#include "taihe/object.hpp"
#include "ohos.data.unifiedDataChannel.UnifiedRecordInner.proj.0.hpp"
#include "ohos.data.unifiedDataChannel.UnifiedRecordInner.abi.1.h"
#include "taihe/string.hpp"
#include "ohos.data.unifiedDataChannel.ValueType.proj.0.hpp"
namespace ohos::data::unifiedDataChannel::weak {
struct UnifiedRecordInner {
    static constexpr bool is_holder = false;
    struct ohos_data_unifiedDataChannel_UnifiedRecordInner_t m_handle;
    explicit UnifiedRecordInner(struct ohos_data_unifiedDataChannel_UnifiedRecordInner_t handle) : m_handle(handle) {}
    explicit UnifiedRecordInner(::taihe::data_view other) : UnifiedRecordInner(ohos_data_unifiedDataChannel_UnifiedRecordInner_dynamic(other.data_ptr)) {}
    operator ::taihe::data_view() const& {
        struct ohos_data_unifiedDataChannel_UnifiedRecordInner_t ret_handle = m_handle;
        return ::taihe::data_view(ret_handle.data_ptr);
    }
    operator ::taihe::data_holder() const& {
        struct ohos_data_unifiedDataChannel_UnifiedRecordInner_t ret_handle = ohos_data_unifiedDataChannel_UnifiedRecordInner_copy(m_handle);
        return ::taihe::data_holder(ret_handle.data_ptr);
    }
    struct virtual_type {
        ::taihe::string GetType() const&;
        ::ohos::data::unifiedDataChannel::ValueType GetValue() const&;
        int64_t GetInner() const&;
    };
    template<typename Impl>
    struct methods_impl {
        static struct TString GetType(struct ohos_data_unifiedDataChannel_UnifiedRecordInner_t tobj);
        static struct ohos_data_unifiedDataChannel_ValueType_t GetValue(struct ohos_data_unifiedDataChannel_UnifiedRecordInner_t tobj);
        static int64_t GetInner(struct ohos_data_unifiedDataChannel_UnifiedRecordInner_t tobj);
    };
    template<typename Impl>
    static constexpr ohos_data_unifiedDataChannel_UnifiedRecordInner_ftable ftbl_impl = {
        .GetType = &methods_impl<Impl>::GetType,
        .GetValue = &methods_impl<Impl>::GetValue,
        .GetInner = &methods_impl<Impl>::GetInner,
    };
    template<typename Impl>
    static constexpr ohos_data_unifiedDataChannel_UnifiedRecordInner_vtable vtbl_impl = {
        .ftbl_ptr_0 = &::ohos::data::unifiedDataChannel::weak::UnifiedRecordInner::template ftbl_impl<Impl>,
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
            {&ohos_data_unifiedDataChannel_UnifiedRecordInner_i, &vtbl_impl<Impl>.ftbl_ptr_0},
        },
    };
    static constexpr void const* iid = &ohos_data_unifiedDataChannel_UnifiedRecordInner_i;
    using vtable_t = ohos_data_unifiedDataChannel_UnifiedRecordInner_vtable;
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
struct UnifiedRecordInner : public ::ohos::data::unifiedDataChannel::weak::UnifiedRecordInner {
    static constexpr bool is_holder = true;
    explicit UnifiedRecordInner(struct ohos_data_unifiedDataChannel_UnifiedRecordInner_t handle) : ::ohos::data::unifiedDataChannel::weak::UnifiedRecordInner(handle) {}
    UnifiedRecordInner& operator=(::ohos::data::unifiedDataChannel::UnifiedRecordInner other) {
        ::std::swap(m_handle, other.m_handle);
        return *this;
    }
    ~UnifiedRecordInner() {
        ohos_data_unifiedDataChannel_UnifiedRecordInner_drop(m_handle);
    }
    explicit UnifiedRecordInner(::taihe::data_holder other) : UnifiedRecordInner(ohos_data_unifiedDataChannel_UnifiedRecordInner_dynamic(other.data_ptr)) {
        other.data_ptr = nullptr;
    }
    operator ::taihe::data_view() const& {
        struct ohos_data_unifiedDataChannel_UnifiedRecordInner_t ret_handle = m_handle;
        return ::taihe::data_view(ret_handle.data_ptr);
    }
    operator ::taihe::data_holder() const& {
        struct ohos_data_unifiedDataChannel_UnifiedRecordInner_t ret_handle = ohos_data_unifiedDataChannel_UnifiedRecordInner_copy(m_handle);
        return ::taihe::data_holder(ret_handle.data_ptr);
    }
    operator ::taihe::data_holder() && {
        struct ohos_data_unifiedDataChannel_UnifiedRecordInner_t ret_handle = m_handle;
        m_handle.data_ptr = nullptr;
        return ::taihe::data_holder(ret_handle.data_ptr);
    }
    UnifiedRecordInner(::ohos::data::unifiedDataChannel::weak::UnifiedRecordInner const& other) : UnifiedRecordInner(ohos_data_unifiedDataChannel_UnifiedRecordInner_copy(other.m_handle)) {}
    UnifiedRecordInner(::ohos::data::unifiedDataChannel::UnifiedRecordInner const& other) : UnifiedRecordInner(ohos_data_unifiedDataChannel_UnifiedRecordInner_copy(other.m_handle)) {}
    UnifiedRecordInner(::ohos::data::unifiedDataChannel::UnifiedRecordInner&& other) : UnifiedRecordInner(other.m_handle) {
        other.m_handle.data_ptr = nullptr;
    }
    template<typename Impl, typename... Args>
    static ::ohos::data::unifiedDataChannel::UnifiedRecordInner from(Args&&... args) {
        return ::ohos::data::unifiedDataChannel::UnifiedRecordInner{{
            .vtbl_ptr = &vtbl_impl<Impl>,
            .data_ptr = ::taihe::new_data_ptr<Impl>(reinterpret_cast<TypeInfo const*>(&rtti_impl<Impl>), std::forward<Args>(args)...),
        }};
    }
    template<typename Impl>
    static ::ohos::data::unifiedDataChannel::UnifiedRecordInner from(Impl&& impl) {
        return ::ohos::data::unifiedDataChannel::UnifiedRecordInner{{
            .vtbl_ptr = &vtbl_impl<Impl>,
            .data_ptr = ::taihe::new_data_ptr<Impl>(reinterpret_cast<TypeInfo const*>(&rtti_impl<Impl>), std::forward<Impl>(impl)),
        }};
    }
};
}
namespace taihe {
template<>
struct as_abi<::ohos::data::unifiedDataChannel::UnifiedRecordInner> {
    using type = struct ohos_data_unifiedDataChannel_UnifiedRecordInner_t;
};
template<>
struct as_abi<::ohos::data::unifiedDataChannel::weak::UnifiedRecordInner> {
    using type = struct ohos_data_unifiedDataChannel_UnifiedRecordInner_t;
};
template<>
struct as_param<::ohos::data::unifiedDataChannel::UnifiedRecordInner> {
    using type = ::ohos::data::unifiedDataChannel::weak::UnifiedRecordInner;
};
}
