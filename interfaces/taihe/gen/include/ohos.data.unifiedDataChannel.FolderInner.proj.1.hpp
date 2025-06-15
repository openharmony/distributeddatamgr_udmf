#pragma once
#include "taihe/object.hpp"
#include "ohos.data.unifiedDataChannel.FolderInner.proj.0.hpp"
#include "ohos.data.unifiedDataChannel.FolderInner.abi.1.h"
#include "taihe/string.hpp"
#include "ohos.data.unifiedDataChannel.ValueType.proj.0.hpp"
#include "taihe/optional.hpp"
#include "taihe/map.hpp"
namespace ohos::data::unifiedDataChannel::weak {
struct FolderInner {
    static constexpr bool is_holder = false;
    struct ohos_data_unifiedDataChannel_FolderInner_t m_handle;
    explicit FolderInner(struct ohos_data_unifiedDataChannel_FolderInner_t handle) : m_handle(handle) {}
    explicit FolderInner(::taihe::data_view other) : FolderInner(ohos_data_unifiedDataChannel_FolderInner_dynamic(other.data_ptr)) {}
    operator ::taihe::data_view() const& {
        struct ohos_data_unifiedDataChannel_FolderInner_t ret_handle = m_handle;
        return ::taihe::data_view(ret_handle.data_ptr);
    }
    operator ::taihe::data_holder() const& {
        struct ohos_data_unifiedDataChannel_FolderInner_t ret_handle = ohos_data_unifiedDataChannel_FolderInner_copy(m_handle);
        return ::taihe::data_holder(ret_handle.data_ptr);
    }
    struct virtual_type {
        ::taihe::string GetType() const&;
        ::ohos::data::unifiedDataChannel::ValueType GetValue() const&;
        ::taihe::string GetUri() const&;
        void SetUri(::taihe::string_view uri) const&;
        ::taihe::optional<::taihe::map<::taihe::string, ::taihe::string>> GetDetails() const&;
        void SetDetails(::taihe::map_view<::taihe::string, ::taihe::string> details) const&;
        ::taihe::string GetFolderUri() const&;
        void SetFolderUri(::taihe::string_view folderUri) const&;
        int64_t GetInner() const&;
    };
    template<typename Impl>
    struct methods_impl {
        static struct TString GetType(struct ohos_data_unifiedDataChannel_FolderInner_t tobj);
        static struct ohos_data_unifiedDataChannel_ValueType_t GetValue(struct ohos_data_unifiedDataChannel_FolderInner_t tobj);
        static struct TString GetUri(struct ohos_data_unifiedDataChannel_FolderInner_t tobj);
        static void SetUri(struct ohos_data_unifiedDataChannel_FolderInner_t tobj, struct TString uri);
        static struct TOptional GetDetails(struct ohos_data_unifiedDataChannel_FolderInner_t tobj);
        static void SetDetails(struct ohos_data_unifiedDataChannel_FolderInner_t tobj, void* details);
        static struct TString GetFolderUri(struct ohos_data_unifiedDataChannel_FolderInner_t tobj);
        static void SetFolderUri(struct ohos_data_unifiedDataChannel_FolderInner_t tobj, struct TString folderUri);
        static int64_t GetInner(struct ohos_data_unifiedDataChannel_FolderInner_t tobj);
    };
    template<typename Impl>
    static constexpr ohos_data_unifiedDataChannel_FolderInner_ftable ftbl_impl = {
        .GetType = &methods_impl<Impl>::GetType,
        .GetValue = &methods_impl<Impl>::GetValue,
        .GetUri = &methods_impl<Impl>::GetUri,
        .SetUri = &methods_impl<Impl>::SetUri,
        .GetDetails = &methods_impl<Impl>::GetDetails,
        .SetDetails = &methods_impl<Impl>::SetDetails,
        .GetFolderUri = &methods_impl<Impl>::GetFolderUri,
        .SetFolderUri = &methods_impl<Impl>::SetFolderUri,
        .GetInner = &methods_impl<Impl>::GetInner,
    };
    template<typename Impl>
    static constexpr ohos_data_unifiedDataChannel_FolderInner_vtable vtbl_impl = {
        .ftbl_ptr_0 = &::ohos::data::unifiedDataChannel::weak::FolderInner::template ftbl_impl<Impl>,
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
            {&ohos_data_unifiedDataChannel_FolderInner_i, &vtbl_impl<Impl>.ftbl_ptr_0},
        },
    };
    static constexpr void const* iid = &ohos_data_unifiedDataChannel_FolderInner_i;
    using vtable_t = ohos_data_unifiedDataChannel_FolderInner_vtable;
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
struct FolderInner : public ::ohos::data::unifiedDataChannel::weak::FolderInner {
    static constexpr bool is_holder = true;
    explicit FolderInner(struct ohos_data_unifiedDataChannel_FolderInner_t handle) : ::ohos::data::unifiedDataChannel::weak::FolderInner(handle) {}
    FolderInner& operator=(::ohos::data::unifiedDataChannel::FolderInner other) {
        ::std::swap(m_handle, other.m_handle);
        return *this;
    }
    ~FolderInner() {
        ohos_data_unifiedDataChannel_FolderInner_drop(m_handle);
    }
    explicit FolderInner(::taihe::data_holder other) : FolderInner(ohos_data_unifiedDataChannel_FolderInner_dynamic(other.data_ptr)) {
        other.data_ptr = nullptr;
    }
    operator ::taihe::data_view() const& {
        struct ohos_data_unifiedDataChannel_FolderInner_t ret_handle = m_handle;
        return ::taihe::data_view(ret_handle.data_ptr);
    }
    operator ::taihe::data_holder() const& {
        struct ohos_data_unifiedDataChannel_FolderInner_t ret_handle = ohos_data_unifiedDataChannel_FolderInner_copy(m_handle);
        return ::taihe::data_holder(ret_handle.data_ptr);
    }
    operator ::taihe::data_holder() && {
        struct ohos_data_unifiedDataChannel_FolderInner_t ret_handle = m_handle;
        m_handle.data_ptr = nullptr;
        return ::taihe::data_holder(ret_handle.data_ptr);
    }
    FolderInner(::ohos::data::unifiedDataChannel::weak::FolderInner const& other) : FolderInner(ohos_data_unifiedDataChannel_FolderInner_copy(other.m_handle)) {}
    FolderInner(::ohos::data::unifiedDataChannel::FolderInner const& other) : FolderInner(ohos_data_unifiedDataChannel_FolderInner_copy(other.m_handle)) {}
    FolderInner(::ohos::data::unifiedDataChannel::FolderInner&& other) : FolderInner(other.m_handle) {
        other.m_handle.data_ptr = nullptr;
    }
    template<typename Impl, typename... Args>
    static ::ohos::data::unifiedDataChannel::FolderInner from(Args&&... args) {
        return ::ohos::data::unifiedDataChannel::FolderInner{{
            .vtbl_ptr = &vtbl_impl<Impl>,
            .data_ptr = ::taihe::new_data_ptr<Impl>(reinterpret_cast<TypeInfo const*>(&rtti_impl<Impl>), std::forward<Args>(args)...),
        }};
    }
    template<typename Impl>
    static ::ohos::data::unifiedDataChannel::FolderInner from(Impl&& impl) {
        return ::ohos::data::unifiedDataChannel::FolderInner{{
            .vtbl_ptr = &vtbl_impl<Impl>,
            .data_ptr = ::taihe::new_data_ptr<Impl>(reinterpret_cast<TypeInfo const*>(&rtti_impl<Impl>), std::forward<Impl>(impl)),
        }};
    }
};
}
namespace taihe {
template<>
struct as_abi<::ohos::data::unifiedDataChannel::FolderInner> {
    using type = struct ohos_data_unifiedDataChannel_FolderInner_t;
};
template<>
struct as_abi<::ohos::data::unifiedDataChannel::weak::FolderInner> {
    using type = struct ohos_data_unifiedDataChannel_FolderInner_t;
};
template<>
struct as_param<::ohos::data::unifiedDataChannel::FolderInner> {
    using type = ::ohos::data::unifiedDataChannel::weak::FolderInner;
};
}
