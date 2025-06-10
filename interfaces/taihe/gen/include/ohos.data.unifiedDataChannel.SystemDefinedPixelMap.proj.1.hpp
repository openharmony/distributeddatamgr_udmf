#pragma once
#include "taihe/object.hpp"
#include "ohos.data.unifiedDataChannel.SystemDefinedPixelMap.proj.0.hpp"
#include "ohos.data.unifiedDataChannel.SystemDefinedPixelMap.abi.1.h"
#include "taihe/string.hpp"
#include "ohos.data.unifiedDataChannel.ValueType.proj.0.hpp"
#include "taihe/optional.hpp"
#include "taihe/map.hpp"
#include "ohos.data.unifiedDataChannel.DetailsValue.proj.0.hpp"
#include "taihe/array.hpp"
namespace ohos::data::unifiedDataChannel::weak {
struct SystemDefinedPixelMap {
    static constexpr bool is_holder = false;
    struct ohos_data_unifiedDataChannel_SystemDefinedPixelMap_t m_handle;
    explicit SystemDefinedPixelMap(struct ohos_data_unifiedDataChannel_SystemDefinedPixelMap_t handle) : m_handle(handle) {}
    explicit SystemDefinedPixelMap(::taihe::data_view other) : SystemDefinedPixelMap(ohos_data_unifiedDataChannel_SystemDefinedPixelMap_dynamic(other.data_ptr)) {}
    operator ::taihe::data_view() const& {
        struct ohos_data_unifiedDataChannel_SystemDefinedPixelMap_t ret_handle = m_handle;
        return ::taihe::data_view(ret_handle.data_ptr);
    }
    operator ::taihe::data_holder() const& {
        struct ohos_data_unifiedDataChannel_SystemDefinedPixelMap_t ret_handle = ohos_data_unifiedDataChannel_SystemDefinedPixelMap_copy(m_handle);
        return ::taihe::data_holder(ret_handle.data_ptr);
    }
    struct virtual_type {
        ::taihe::string GetType() const&;
        ::ohos::data::unifiedDataChannel::ValueType GetValue() const&;
        ::taihe::optional<::taihe::map<::taihe::string, ::ohos::data::unifiedDataChannel::DetailsValue>> GetDetails() const&;
        void SetDetails(::taihe::map_view<::taihe::string, ::ohos::data::unifiedDataChannel::DetailsValue> details) const&;
        ::taihe::optional<::taihe::array<uint8_t>> GetRawData() const&;
        void SetRawData(::taihe::array_view<uint8_t> rawData) const&;
        int64_t GetInner() const&;
    };
    template<typename Impl>
    struct methods_impl {
        static struct TString GetType(struct ohos_data_unifiedDataChannel_SystemDefinedPixelMap_t tobj);
        static struct ohos_data_unifiedDataChannel_ValueType_t GetValue(struct ohos_data_unifiedDataChannel_SystemDefinedPixelMap_t tobj);
        static struct TOptional GetDetails(struct ohos_data_unifiedDataChannel_SystemDefinedPixelMap_t tobj);
        static void SetDetails(struct ohos_data_unifiedDataChannel_SystemDefinedPixelMap_t tobj, void* details);
        static struct TOptional GetRawData(struct ohos_data_unifiedDataChannel_SystemDefinedPixelMap_t tobj);
        static void SetRawData(struct ohos_data_unifiedDataChannel_SystemDefinedPixelMap_t tobj, struct TArray rawData);
        static int64_t GetInner(struct ohos_data_unifiedDataChannel_SystemDefinedPixelMap_t tobj);
    };
    template<typename Impl>
    static constexpr ohos_data_unifiedDataChannel_SystemDefinedPixelMap_ftable ftbl_impl = {
        .GetType = &methods_impl<Impl>::GetType,
        .GetValue = &methods_impl<Impl>::GetValue,
        .GetDetails = &methods_impl<Impl>::GetDetails,
        .SetDetails = &methods_impl<Impl>::SetDetails,
        .GetRawData = &methods_impl<Impl>::GetRawData,
        .SetRawData = &methods_impl<Impl>::SetRawData,
        .GetInner = &methods_impl<Impl>::GetInner,
    };
    template<typename Impl>
    static constexpr ohos_data_unifiedDataChannel_SystemDefinedPixelMap_vtable vtbl_impl = {
        .ftbl_ptr_0 = &::ohos::data::unifiedDataChannel::weak::SystemDefinedPixelMap::template ftbl_impl<Impl>,
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
            {&ohos_data_unifiedDataChannel_SystemDefinedPixelMap_i, &vtbl_impl<Impl>.ftbl_ptr_0},
        },
    };
    static constexpr void const* iid = &ohos_data_unifiedDataChannel_SystemDefinedPixelMap_i;
    using vtable_t = ohos_data_unifiedDataChannel_SystemDefinedPixelMap_vtable;
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
struct SystemDefinedPixelMap : public ::ohos::data::unifiedDataChannel::weak::SystemDefinedPixelMap {
    static constexpr bool is_holder = true;
    explicit SystemDefinedPixelMap(struct ohos_data_unifiedDataChannel_SystemDefinedPixelMap_t handle) : ::ohos::data::unifiedDataChannel::weak::SystemDefinedPixelMap(handle) {}
    SystemDefinedPixelMap& operator=(::ohos::data::unifiedDataChannel::SystemDefinedPixelMap other) {
        ::std::swap(m_handle, other.m_handle);
        return *this;
    }
    ~SystemDefinedPixelMap() {
        ohos_data_unifiedDataChannel_SystemDefinedPixelMap_drop(m_handle);
    }
    explicit SystemDefinedPixelMap(::taihe::data_holder other) : SystemDefinedPixelMap(ohos_data_unifiedDataChannel_SystemDefinedPixelMap_dynamic(other.data_ptr)) {
        other.data_ptr = nullptr;
    }
    operator ::taihe::data_view() const& {
        struct ohos_data_unifiedDataChannel_SystemDefinedPixelMap_t ret_handle = m_handle;
        return ::taihe::data_view(ret_handle.data_ptr);
    }
    operator ::taihe::data_holder() const& {
        struct ohos_data_unifiedDataChannel_SystemDefinedPixelMap_t ret_handle = ohos_data_unifiedDataChannel_SystemDefinedPixelMap_copy(m_handle);
        return ::taihe::data_holder(ret_handle.data_ptr);
    }
    operator ::taihe::data_holder() && {
        struct ohos_data_unifiedDataChannel_SystemDefinedPixelMap_t ret_handle = m_handle;
        m_handle.data_ptr = nullptr;
        return ::taihe::data_holder(ret_handle.data_ptr);
    }
    SystemDefinedPixelMap(::ohos::data::unifiedDataChannel::weak::SystemDefinedPixelMap const& other) : SystemDefinedPixelMap(ohos_data_unifiedDataChannel_SystemDefinedPixelMap_copy(other.m_handle)) {}
    SystemDefinedPixelMap(::ohos::data::unifiedDataChannel::SystemDefinedPixelMap const& other) : SystemDefinedPixelMap(ohos_data_unifiedDataChannel_SystemDefinedPixelMap_copy(other.m_handle)) {}
    SystemDefinedPixelMap(::ohos::data::unifiedDataChannel::SystemDefinedPixelMap&& other) : SystemDefinedPixelMap(other.m_handle) {
        other.m_handle.data_ptr = nullptr;
    }
    template<typename Impl, typename... Args>
    static ::ohos::data::unifiedDataChannel::SystemDefinedPixelMap from(Args&&... args) {
        return ::ohos::data::unifiedDataChannel::SystemDefinedPixelMap{{
            .vtbl_ptr = &vtbl_impl<Impl>,
            .data_ptr = ::taihe::new_data_ptr<Impl>(reinterpret_cast<TypeInfo const*>(&rtti_impl<Impl>), std::forward<Args>(args)...),
        }};
    }
    template<typename Impl>
    static ::ohos::data::unifiedDataChannel::SystemDefinedPixelMap from(Impl&& impl) {
        return ::ohos::data::unifiedDataChannel::SystemDefinedPixelMap{{
            .vtbl_ptr = &vtbl_impl<Impl>,
            .data_ptr = ::taihe::new_data_ptr<Impl>(reinterpret_cast<TypeInfo const*>(&rtti_impl<Impl>), std::forward<Impl>(impl)),
        }};
    }
};
}
namespace taihe {
template<>
struct as_abi<::ohos::data::unifiedDataChannel::SystemDefinedPixelMap> {
    using type = struct ohos_data_unifiedDataChannel_SystemDefinedPixelMap_t;
};
template<>
struct as_abi<::ohos::data::unifiedDataChannel::weak::SystemDefinedPixelMap> {
    using type = struct ohos_data_unifiedDataChannel_SystemDefinedPixelMap_t;
};
template<>
struct as_param<::ohos::data::unifiedDataChannel::SystemDefinedPixelMap> {
    using type = ::ohos::data::unifiedDataChannel::weak::SystemDefinedPixelMap;
};
}
