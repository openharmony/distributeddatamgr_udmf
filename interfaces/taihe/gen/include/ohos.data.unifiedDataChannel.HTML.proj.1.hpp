#pragma once
#include "taihe/object.hpp"
#include "ohos.data.unifiedDataChannel.HTML.proj.0.hpp"
#include "ohos.data.unifiedDataChannel.HTML.abi.1.h"
#include "taihe/string.hpp"
#include "ohos.data.unifiedDataChannel.ValueType.proj.0.hpp"
#include "taihe/optional.hpp"
#include "taihe/map.hpp"
namespace ohos::data::unifiedDataChannel::weak {
struct HTML {
    static constexpr bool is_holder = false;
    struct ohos_data_unifiedDataChannel_HTML_t m_handle;
    explicit HTML(struct ohos_data_unifiedDataChannel_HTML_t handle) : m_handle(handle) {}
    explicit HTML(::taihe::data_view other) : HTML(ohos_data_unifiedDataChannel_HTML_dynamic(other.data_ptr)) {}
    operator ::taihe::data_view() const& {
        struct ohos_data_unifiedDataChannel_HTML_t ret_handle = m_handle;
        return ::taihe::data_view(ret_handle.data_ptr);
    }
    operator ::taihe::data_holder() const& {
        struct ohos_data_unifiedDataChannel_HTML_t ret_handle = ohos_data_unifiedDataChannel_HTML_copy(m_handle);
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
        static struct TString GetType(struct ohos_data_unifiedDataChannel_HTML_t tobj);
        static struct ohos_data_unifiedDataChannel_ValueType_t GetValue(struct ohos_data_unifiedDataChannel_HTML_t tobj);
        static struct TOptional GetDetails(struct ohos_data_unifiedDataChannel_HTML_t tobj);
        static void SetDetails(struct ohos_data_unifiedDataChannel_HTML_t tobj, void* details);
        static void SetHtmlContent(struct ohos_data_unifiedDataChannel_HTML_t tobj, struct TString htmlContent);
        static struct TString GetHtmlContent(struct ohos_data_unifiedDataChannel_HTML_t tobj);
        static void SetPlainContent(struct ohos_data_unifiedDataChannel_HTML_t tobj, struct TString plainContent);
        static struct TString GetPlainContent(struct ohos_data_unifiedDataChannel_HTML_t tobj);
        static int64_t GetInner(struct ohos_data_unifiedDataChannel_HTML_t tobj);
    };
    template<typename Impl>
    static constexpr ohos_data_unifiedDataChannel_HTML_ftable ftbl_impl = {
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
    static constexpr ohos_data_unifiedDataChannel_HTML_vtable vtbl_impl = {
        .ftbl_ptr_0 = &::ohos::data::unifiedDataChannel::weak::HTML::template ftbl_impl<Impl>,
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
            {&ohos_data_unifiedDataChannel_HTML_i, &vtbl_impl<Impl>.ftbl_ptr_0},
        },
    };
    static constexpr void const* iid = &ohos_data_unifiedDataChannel_HTML_i;
    using vtable_t = ohos_data_unifiedDataChannel_HTML_vtable;
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
struct HTML : public ::ohos::data::unifiedDataChannel::weak::HTML {
    static constexpr bool is_holder = true;
    explicit HTML(struct ohos_data_unifiedDataChannel_HTML_t handle) : ::ohos::data::unifiedDataChannel::weak::HTML(handle) {}
    HTML& operator=(::ohos::data::unifiedDataChannel::HTML other) {
        ::std::swap(m_handle, other.m_handle);
        return *this;
    }
    ~HTML() {
        ohos_data_unifiedDataChannel_HTML_drop(m_handle);
    }
    explicit HTML(::taihe::data_holder other) : HTML(ohos_data_unifiedDataChannel_HTML_dynamic(other.data_ptr)) {
        other.data_ptr = nullptr;
    }
    operator ::taihe::data_view() const& {
        struct ohos_data_unifiedDataChannel_HTML_t ret_handle = m_handle;
        return ::taihe::data_view(ret_handle.data_ptr);
    }
    operator ::taihe::data_holder() const& {
        struct ohos_data_unifiedDataChannel_HTML_t ret_handle = ohos_data_unifiedDataChannel_HTML_copy(m_handle);
        return ::taihe::data_holder(ret_handle.data_ptr);
    }
    operator ::taihe::data_holder() && {
        struct ohos_data_unifiedDataChannel_HTML_t ret_handle = m_handle;
        m_handle.data_ptr = nullptr;
        return ::taihe::data_holder(ret_handle.data_ptr);
    }
    HTML(::ohos::data::unifiedDataChannel::weak::HTML const& other) : HTML(ohos_data_unifiedDataChannel_HTML_copy(other.m_handle)) {}
    HTML(::ohos::data::unifiedDataChannel::HTML const& other) : HTML(ohos_data_unifiedDataChannel_HTML_copy(other.m_handle)) {}
    HTML(::ohos::data::unifiedDataChannel::HTML&& other) : HTML(other.m_handle) {
        other.m_handle.data_ptr = nullptr;
    }
    template<typename Impl, typename... Args>
    static ::ohos::data::unifiedDataChannel::HTML from(Args&&... args) {
        return ::ohos::data::unifiedDataChannel::HTML{{
            .vtbl_ptr = &vtbl_impl<Impl>,
            .data_ptr = ::taihe::new_data_ptr<Impl>(reinterpret_cast<TypeInfo const*>(&rtti_impl<Impl>), std::forward<Args>(args)...),
        }};
    }
    template<typename Impl>
    static ::ohos::data::unifiedDataChannel::HTML from(Impl&& impl) {
        return ::ohos::data::unifiedDataChannel::HTML{{
            .vtbl_ptr = &vtbl_impl<Impl>,
            .data_ptr = ::taihe::new_data_ptr<Impl>(reinterpret_cast<TypeInfo const*>(&rtti_impl<Impl>), std::forward<Impl>(impl)),
        }};
    }
};
}
namespace taihe {
template<>
struct as_abi<::ohos::data::unifiedDataChannel::HTML> {
    using type = struct ohos_data_unifiedDataChannel_HTML_t;
};
template<>
struct as_abi<::ohos::data::unifiedDataChannel::weak::HTML> {
    using type = struct ohos_data_unifiedDataChannel_HTML_t;
};
template<>
struct as_param<::ohos::data::unifiedDataChannel::HTML> {
    using type = ::ohos::data::unifiedDataChannel::weak::HTML;
};
}
