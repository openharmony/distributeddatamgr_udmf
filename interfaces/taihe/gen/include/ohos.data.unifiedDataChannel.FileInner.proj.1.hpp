#pragma once
#include "taihe/object.hpp"
#include "ohos.data.unifiedDataChannel.FileInner.proj.0.hpp"
#include "ohos.data.unifiedDataChannel.FileInner.abi.1.h"
#include "taihe/string.hpp"
#include "ohos.data.unifiedDataChannel.ValueType.proj.0.hpp"
#include "taihe/optional.hpp"
#include "taihe/map.hpp"
namespace ohos::data::unifiedDataChannel::weak {
struct FileInner {
    static constexpr bool is_holder = false;
    struct ohos_data_unifiedDataChannel_FileInner_t m_handle;
    explicit FileInner(struct ohos_data_unifiedDataChannel_FileInner_t handle) : m_handle(handle) {}
    explicit FileInner(::taihe::data_view other) : FileInner(ohos_data_unifiedDataChannel_FileInner_dynamic(other.data_ptr)) {}
    operator ::taihe::data_view() const& {
        struct ohos_data_unifiedDataChannel_FileInner_t ret_handle = m_handle;
        return ::taihe::data_view(ret_handle.data_ptr);
    }
    operator ::taihe::data_holder() const& {
        struct ohos_data_unifiedDataChannel_FileInner_t ret_handle = ohos_data_unifiedDataChannel_FileInner_copy(m_handle);
        return ::taihe::data_holder(ret_handle.data_ptr);
    }
    struct virtual_type {
        ::taihe::string GetType() const&;
        ::ohos::data::unifiedDataChannel::ValueType GetValue() const&;
        ::taihe::string GetUri() const&;
        void SetUri(::taihe::string_view uri) const&;
        ::taihe::optional<::taihe::map<::taihe::string, ::taihe::string>> GetDetails() const&;
        void SetDetails(::taihe::map_view<::taihe::string, ::taihe::string> details) const&;
        int64_t GetInner() const&;
    };
    template<typename Impl>
    struct methods_impl {
        static struct TString GetType(struct ohos_data_unifiedDataChannel_FileInner_t tobj);
        static struct ohos_data_unifiedDataChannel_ValueType_t GetValue(struct ohos_data_unifiedDataChannel_FileInner_t tobj);
        static struct TString GetUri(struct ohos_data_unifiedDataChannel_FileInner_t tobj);
        static void SetUri(struct ohos_data_unifiedDataChannel_FileInner_t tobj, struct TString uri);
        static struct TOptional GetDetails(struct ohos_data_unifiedDataChannel_FileInner_t tobj);
        static void SetDetails(struct ohos_data_unifiedDataChannel_FileInner_t tobj, void* details);
        static int64_t GetInner(struct ohos_data_unifiedDataChannel_FileInner_t tobj);
    };
    template<typename Impl>
    static constexpr ohos_data_unifiedDataChannel_FileInner_ftable ftbl_impl = {
        .GetType = &methods_impl<Impl>::GetType,
        .GetValue = &methods_impl<Impl>::GetValue,
        .GetUri = &methods_impl<Impl>::GetUri,
        .SetUri = &methods_impl<Impl>::SetUri,
        .GetDetails = &methods_impl<Impl>::GetDetails,
        .SetDetails = &methods_impl<Impl>::SetDetails,
        .GetInner = &methods_impl<Impl>::GetInner,
    };
    template<typename Impl>
    static constexpr ohos_data_unifiedDataChannel_FileInner_vtable vtbl_impl = {
        .ftbl_ptr_0 = &::ohos::data::unifiedDataChannel::weak::FileInner::template ftbl_impl<Impl>,
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
            {&ohos_data_unifiedDataChannel_FileInner_i, &vtbl_impl<Impl>.ftbl_ptr_0},
        },
    };
    static constexpr void const* iid = &ohos_data_unifiedDataChannel_FileInner_i;
    using vtable_t = ohos_data_unifiedDataChannel_FileInner_vtable;
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
struct FileInner : public ::ohos::data::unifiedDataChannel::weak::FileInner {
    static constexpr bool is_holder = true;
    explicit FileInner(struct ohos_data_unifiedDataChannel_FileInner_t handle) : ::ohos::data::unifiedDataChannel::weak::FileInner(handle) {}
    FileInner& operator=(::ohos::data::unifiedDataChannel::FileInner other) {
        ::std::swap(m_handle, other.m_handle);
        return *this;
    }
    ~FileInner() {
        ohos_data_unifiedDataChannel_FileInner_drop(m_handle);
    }
    explicit FileInner(::taihe::data_holder other) : FileInner(ohos_data_unifiedDataChannel_FileInner_dynamic(other.data_ptr)) {
        other.data_ptr = nullptr;
    }
    operator ::taihe::data_view() const& {
        struct ohos_data_unifiedDataChannel_FileInner_t ret_handle = m_handle;
        return ::taihe::data_view(ret_handle.data_ptr);
    }
    operator ::taihe::data_holder() const& {
        struct ohos_data_unifiedDataChannel_FileInner_t ret_handle = ohos_data_unifiedDataChannel_FileInner_copy(m_handle);
        return ::taihe::data_holder(ret_handle.data_ptr);
    }
    operator ::taihe::data_holder() && {
        struct ohos_data_unifiedDataChannel_FileInner_t ret_handle = m_handle;
        m_handle.data_ptr = nullptr;
        return ::taihe::data_holder(ret_handle.data_ptr);
    }
    FileInner(::ohos::data::unifiedDataChannel::weak::FileInner const& other) : FileInner(ohos_data_unifiedDataChannel_FileInner_copy(other.m_handle)) {}
    FileInner(::ohos::data::unifiedDataChannel::FileInner const& other) : FileInner(ohos_data_unifiedDataChannel_FileInner_copy(other.m_handle)) {}
    FileInner(::ohos::data::unifiedDataChannel::FileInner&& other) : FileInner(other.m_handle) {
        other.m_handle.data_ptr = nullptr;
    }
    template<typename Impl, typename... Args>
    static ::ohos::data::unifiedDataChannel::FileInner from(Args&&... args) {
        return ::ohos::data::unifiedDataChannel::FileInner{{
            .vtbl_ptr = &vtbl_impl<Impl>,
            .data_ptr = ::taihe::new_data_ptr<Impl>(reinterpret_cast<TypeInfo const*>(&rtti_impl<Impl>), std::forward<Args>(args)...),
        }};
    }
    template<typename Impl>
    static ::ohos::data::unifiedDataChannel::FileInner from(Impl&& impl) {
        return ::ohos::data::unifiedDataChannel::FileInner{{
            .vtbl_ptr = &vtbl_impl<Impl>,
            .data_ptr = ::taihe::new_data_ptr<Impl>(reinterpret_cast<TypeInfo const*>(&rtti_impl<Impl>), std::forward<Impl>(impl)),
        }};
    }
};
}
namespace taihe {
template<>
struct as_abi<::ohos::data::unifiedDataChannel::FileInner> {
    using type = struct ohos_data_unifiedDataChannel_FileInner_t;
};
template<>
struct as_abi<::ohos::data::unifiedDataChannel::weak::FileInner> {
    using type = struct ohos_data_unifiedDataChannel_FileInner_t;
};
template<>
struct as_param<::ohos::data::unifiedDataChannel::FileInner> {
    using type = ::ohos::data::unifiedDataChannel::weak::FileInner;
};
}
