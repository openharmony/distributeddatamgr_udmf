#pragma once
#include "taihe/object.hpp"
#include "ohos.data.unifiedDataChannel.UnifiedDataInner.proj.0.hpp"
#include "ohos.data.unifiedDataChannel.UnifiedDataInner.abi.1.h"
#include "ohos.data.unifiedDataChannel.AllRecords.proj.0.hpp"
#include "taihe/array.hpp"
namespace ohos::data::unifiedDataChannel::weak {
struct UnifiedDataInner {
    static constexpr bool is_holder = false;
    struct ohos_data_unifiedDataChannel_UnifiedDataInner_t m_handle;
    explicit UnifiedDataInner(struct ohos_data_unifiedDataChannel_UnifiedDataInner_t handle) : m_handle(handle) {}
    explicit UnifiedDataInner(::taihe::data_view other) : UnifiedDataInner(ohos_data_unifiedDataChannel_UnifiedDataInner_dynamic(other.data_ptr)) {}
    operator ::taihe::data_view() const& {
        struct ohos_data_unifiedDataChannel_UnifiedDataInner_t ret_handle = m_handle;
        return ::taihe::data_view(ret_handle.data_ptr);
    }
    operator ::taihe::data_holder() const& {
        struct ohos_data_unifiedDataChannel_UnifiedDataInner_t ret_handle = ohos_data_unifiedDataChannel_UnifiedDataInner_copy(m_handle);
        return ::taihe::data_holder(ret_handle.data_ptr);
    }
    struct virtual_type {
        void AddRecord(::ohos::data::unifiedDataChannel::AllRecords const& unifiedRecord) const&;
        ::taihe::array<::ohos::data::unifiedDataChannel::AllRecords> GetRecords() const&;
        int64_t GetInner() const&;
    };
    template<typename Impl>
    struct methods_impl {
        static void AddRecord(struct ohos_data_unifiedDataChannel_UnifiedDataInner_t tobj, struct ohos_data_unifiedDataChannel_AllRecords_t const* unifiedRecord);
        static struct TArray GetRecords(struct ohos_data_unifiedDataChannel_UnifiedDataInner_t tobj);
        static int64_t GetInner(struct ohos_data_unifiedDataChannel_UnifiedDataInner_t tobj);
    };
    template<typename Impl>
    static constexpr ohos_data_unifiedDataChannel_UnifiedDataInner_ftable ftbl_impl = {
        .AddRecord = &methods_impl<Impl>::AddRecord,
        .GetRecords = &methods_impl<Impl>::GetRecords,
        .GetInner = &methods_impl<Impl>::GetInner,
    };
    template<typename Impl>
    static constexpr ohos_data_unifiedDataChannel_UnifiedDataInner_vtable vtbl_impl = {
        .ftbl_ptr_0 = &::ohos::data::unifiedDataChannel::weak::UnifiedDataInner::template ftbl_impl<Impl>,
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
            {&ohos_data_unifiedDataChannel_UnifiedDataInner_i, &vtbl_impl<Impl>.ftbl_ptr_0},
        },
    };
    static constexpr void const* iid = &ohos_data_unifiedDataChannel_UnifiedDataInner_i;
    using vtable_t = ohos_data_unifiedDataChannel_UnifiedDataInner_vtable;
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
struct UnifiedDataInner : public ::ohos::data::unifiedDataChannel::weak::UnifiedDataInner {
    static constexpr bool is_holder = true;
    explicit UnifiedDataInner(struct ohos_data_unifiedDataChannel_UnifiedDataInner_t handle) : ::ohos::data::unifiedDataChannel::weak::UnifiedDataInner(handle) {}
    UnifiedDataInner& operator=(::ohos::data::unifiedDataChannel::UnifiedDataInner other) {
        ::std::swap(m_handle, other.m_handle);
        return *this;
    }
    ~UnifiedDataInner() {
        ohos_data_unifiedDataChannel_UnifiedDataInner_drop(m_handle);
    }
    explicit UnifiedDataInner(::taihe::data_holder other) : UnifiedDataInner(ohos_data_unifiedDataChannel_UnifiedDataInner_dynamic(other.data_ptr)) {
        other.data_ptr = nullptr;
    }
    operator ::taihe::data_view() const& {
        struct ohos_data_unifiedDataChannel_UnifiedDataInner_t ret_handle = m_handle;
        return ::taihe::data_view(ret_handle.data_ptr);
    }
    operator ::taihe::data_holder() const& {
        struct ohos_data_unifiedDataChannel_UnifiedDataInner_t ret_handle = ohos_data_unifiedDataChannel_UnifiedDataInner_copy(m_handle);
        return ::taihe::data_holder(ret_handle.data_ptr);
    }
    operator ::taihe::data_holder() && {
        struct ohos_data_unifiedDataChannel_UnifiedDataInner_t ret_handle = m_handle;
        m_handle.data_ptr = nullptr;
        return ::taihe::data_holder(ret_handle.data_ptr);
    }
    UnifiedDataInner(::ohos::data::unifiedDataChannel::weak::UnifiedDataInner const& other) : UnifiedDataInner(ohos_data_unifiedDataChannel_UnifiedDataInner_copy(other.m_handle)) {}
    UnifiedDataInner(::ohos::data::unifiedDataChannel::UnifiedDataInner const& other) : UnifiedDataInner(ohos_data_unifiedDataChannel_UnifiedDataInner_copy(other.m_handle)) {}
    UnifiedDataInner(::ohos::data::unifiedDataChannel::UnifiedDataInner&& other) : UnifiedDataInner(other.m_handle) {
        other.m_handle.data_ptr = nullptr;
    }
    template<typename Impl, typename... Args>
    static ::ohos::data::unifiedDataChannel::UnifiedDataInner from(Args&&... args) {
        return ::ohos::data::unifiedDataChannel::UnifiedDataInner{{
            .vtbl_ptr = &vtbl_impl<Impl>,
            .data_ptr = ::taihe::new_data_ptr<Impl>(reinterpret_cast<TypeInfo const*>(&rtti_impl<Impl>), std::forward<Args>(args)...),
        }};
    }
    template<typename Impl>
    static ::ohos::data::unifiedDataChannel::UnifiedDataInner from(Impl&& impl) {
        return ::ohos::data::unifiedDataChannel::UnifiedDataInner{{
            .vtbl_ptr = &vtbl_impl<Impl>,
            .data_ptr = ::taihe::new_data_ptr<Impl>(reinterpret_cast<TypeInfo const*>(&rtti_impl<Impl>), std::forward<Impl>(impl)),
        }};
    }
};
}
namespace taihe {
template<>
struct as_abi<::ohos::data::unifiedDataChannel::UnifiedDataInner> {
    using type = struct ohos_data_unifiedDataChannel_UnifiedDataInner_t;
};
template<>
struct as_abi<::ohos::data::unifiedDataChannel::weak::UnifiedDataInner> {
    using type = struct ohos_data_unifiedDataChannel_UnifiedDataInner_t;
};
template<>
struct as_param<::ohos::data::unifiedDataChannel::UnifiedDataInner> {
    using type = ::ohos::data::unifiedDataChannel::weak::UnifiedDataInner;
};
}
