#pragma once
#include "taihe/object.hpp"
#include "ohos.data.unifiedDataChannel.SystemDefinedRecord.proj.0.hpp"
#include "ohos.data.unifiedDataChannel.SystemDefinedRecord.abi.1.h"
#include "taihe/string.hpp"
#include "ohos.data.unifiedDataChannel.ValueType.proj.0.hpp"
#include "taihe/optional.hpp"
#include "taihe/map.hpp"
#include "ohos.data.unifiedDataChannel.DetailsValue.proj.0.hpp"
namespace ohos::data::unifiedDataChannel::weak {
struct SystemDefinedRecord {
    static constexpr bool is_holder = false;
    struct ohos_data_unifiedDataChannel_SystemDefinedRecord_t m_handle;
    explicit SystemDefinedRecord(struct ohos_data_unifiedDataChannel_SystemDefinedRecord_t handle) : m_handle(handle) {}
    explicit SystemDefinedRecord(::taihe::data_view other) : SystemDefinedRecord(ohos_data_unifiedDataChannel_SystemDefinedRecord_dynamic(other.data_ptr)) {}
    operator ::taihe::data_view() const& {
        struct ohos_data_unifiedDataChannel_SystemDefinedRecord_t ret_handle = m_handle;
        return ::taihe::data_view(ret_handle.data_ptr);
    }
    operator ::taihe::data_holder() const& {
        struct ohos_data_unifiedDataChannel_SystemDefinedRecord_t ret_handle = ohos_data_unifiedDataChannel_SystemDefinedRecord_copy(m_handle);
        return ::taihe::data_holder(ret_handle.data_ptr);
    }
    struct virtual_type {
        ::taihe::string GetType() const&;
        ::ohos::data::unifiedDataChannel::ValueType GetValue() const&;
        ::taihe::optional<::taihe::map<::taihe::string, ::ohos::data::unifiedDataChannel::DetailsValue>> GetDetails() const&;
        void SetDetails(::taihe::map_view<::taihe::string, ::ohos::data::unifiedDataChannel::DetailsValue> details) const&;
        int64_t GetInner() const&;
    };
    template<typename Impl>
    struct methods_impl {
        static struct TString GetType(struct ohos_data_unifiedDataChannel_SystemDefinedRecord_t tobj);
        static struct ohos_data_unifiedDataChannel_ValueType_t GetValue(struct ohos_data_unifiedDataChannel_SystemDefinedRecord_t tobj);
        static struct TOptional GetDetails(struct ohos_data_unifiedDataChannel_SystemDefinedRecord_t tobj);
        static void SetDetails(struct ohos_data_unifiedDataChannel_SystemDefinedRecord_t tobj, void* details);
        static int64_t GetInner(struct ohos_data_unifiedDataChannel_SystemDefinedRecord_t tobj);
    };
    template<typename Impl>
    static constexpr ohos_data_unifiedDataChannel_SystemDefinedRecord_ftable ftbl_impl = {
        .GetType = &methods_impl<Impl>::GetType,
        .GetValue = &methods_impl<Impl>::GetValue,
        .GetDetails = &methods_impl<Impl>::GetDetails,
        .SetDetails = &methods_impl<Impl>::SetDetails,
        .GetInner = &methods_impl<Impl>::GetInner,
    };
    template<typename Impl>
    static constexpr ohos_data_unifiedDataChannel_SystemDefinedRecord_vtable vtbl_impl = {
        .ftbl_ptr_0 = &::ohos::data::unifiedDataChannel::weak::SystemDefinedRecord::template ftbl_impl<Impl>,
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
            {&ohos_data_unifiedDataChannel_SystemDefinedRecord_i, &vtbl_impl<Impl>.ftbl_ptr_0},
        },
    };
    static constexpr void const* iid = &ohos_data_unifiedDataChannel_SystemDefinedRecord_i;
    using vtable_t = ohos_data_unifiedDataChannel_SystemDefinedRecord_vtable;
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
struct SystemDefinedRecord : public ::ohos::data::unifiedDataChannel::weak::SystemDefinedRecord {
    static constexpr bool is_holder = true;
    explicit SystemDefinedRecord(struct ohos_data_unifiedDataChannel_SystemDefinedRecord_t handle) : ::ohos::data::unifiedDataChannel::weak::SystemDefinedRecord(handle) {}
    SystemDefinedRecord& operator=(::ohos::data::unifiedDataChannel::SystemDefinedRecord other) {
        ::std::swap(m_handle, other.m_handle);
        return *this;
    }
    ~SystemDefinedRecord() {
        ohos_data_unifiedDataChannel_SystemDefinedRecord_drop(m_handle);
    }
    explicit SystemDefinedRecord(::taihe::data_holder other) : SystemDefinedRecord(ohos_data_unifiedDataChannel_SystemDefinedRecord_dynamic(other.data_ptr)) {
        other.data_ptr = nullptr;
    }
    operator ::taihe::data_view() const& {
        struct ohos_data_unifiedDataChannel_SystemDefinedRecord_t ret_handle = m_handle;
        return ::taihe::data_view(ret_handle.data_ptr);
    }
    operator ::taihe::data_holder() const& {
        struct ohos_data_unifiedDataChannel_SystemDefinedRecord_t ret_handle = ohos_data_unifiedDataChannel_SystemDefinedRecord_copy(m_handle);
        return ::taihe::data_holder(ret_handle.data_ptr);
    }
    operator ::taihe::data_holder() && {
        struct ohos_data_unifiedDataChannel_SystemDefinedRecord_t ret_handle = m_handle;
        m_handle.data_ptr = nullptr;
        return ::taihe::data_holder(ret_handle.data_ptr);
    }
    SystemDefinedRecord(::ohos::data::unifiedDataChannel::weak::SystemDefinedRecord const& other) : SystemDefinedRecord(ohos_data_unifiedDataChannel_SystemDefinedRecord_copy(other.m_handle)) {}
    SystemDefinedRecord(::ohos::data::unifiedDataChannel::SystemDefinedRecord const& other) : SystemDefinedRecord(ohos_data_unifiedDataChannel_SystemDefinedRecord_copy(other.m_handle)) {}
    SystemDefinedRecord(::ohos::data::unifiedDataChannel::SystemDefinedRecord&& other) : SystemDefinedRecord(other.m_handle) {
        other.m_handle.data_ptr = nullptr;
    }
    template<typename Impl, typename... Args>
    static ::ohos::data::unifiedDataChannel::SystemDefinedRecord from(Args&&... args) {
        return ::ohos::data::unifiedDataChannel::SystemDefinedRecord{{
            .vtbl_ptr = &vtbl_impl<Impl>,
            .data_ptr = ::taihe::new_data_ptr<Impl>(reinterpret_cast<TypeInfo const*>(&rtti_impl<Impl>), std::forward<Args>(args)...),
        }};
    }
    template<typename Impl>
    static ::ohos::data::unifiedDataChannel::SystemDefinedRecord from(Impl&& impl) {
        return ::ohos::data::unifiedDataChannel::SystemDefinedRecord{{
            .vtbl_ptr = &vtbl_impl<Impl>,
            .data_ptr = ::taihe::new_data_ptr<Impl>(reinterpret_cast<TypeInfo const*>(&rtti_impl<Impl>), std::forward<Impl>(impl)),
        }};
    }
};
}
namespace taihe {
template<>
struct as_abi<::ohos::data::unifiedDataChannel::SystemDefinedRecord> {
    using type = struct ohos_data_unifiedDataChannel_SystemDefinedRecord_t;
};
template<>
struct as_abi<::ohos::data::unifiedDataChannel::weak::SystemDefinedRecord> {
    using type = struct ohos_data_unifiedDataChannel_SystemDefinedRecord_t;
};
template<>
struct as_param<::ohos::data::unifiedDataChannel::SystemDefinedRecord> {
    using type = ::ohos::data::unifiedDataChannel::weak::SystemDefinedRecord;
};
}
