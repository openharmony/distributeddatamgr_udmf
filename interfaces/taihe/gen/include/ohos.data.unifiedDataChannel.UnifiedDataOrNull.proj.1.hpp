#pragma once
#include "taihe/common.hpp"
#include "ohos.data.unifiedDataChannel.UnifiedDataOrNull.proj.0.hpp"
#include "ohos.data.unifiedDataChannel.UnifiedDataOrNull.abi.1.h"
#include "ohos.data.unifiedDataChannel.UnifiedData.proj.2.hpp"
namespace ohos::data::unifiedDataChannel {
struct UnifiedDataOrNull {
    public:
    enum class tag_t : int {
        unifiedData,
        nullType,
    };
    union storage_t {
        storage_t() {}
        ~storage_t() {}
        ::ohos::data::unifiedDataChannel::UnifiedData unifiedData;
    };
    UnifiedDataOrNull(UnifiedDataOrNull const& other) : m_tag(other.m_tag) {
        switch (m_tag) {
        case tag_t::unifiedData: {
            new (&m_data.unifiedData) decltype(m_data.unifiedData)(other.m_data.unifiedData);
            break;
        }
        default: {
            break;
        }
        }
    }
    UnifiedDataOrNull(UnifiedDataOrNull&& other) : m_tag(other.m_tag) {
        switch (m_tag) {
        case tag_t::unifiedData: {
            new (&m_data.unifiedData) decltype(m_data.unifiedData)(::std::move(other.m_data.unifiedData));
            break;
        }
        default: {
            break;
        }
        }
    }
    UnifiedDataOrNull& operator=(UnifiedDataOrNull const& other) {
        if (this != &other) {
            ::std::destroy_at(this);
            new (this) UnifiedDataOrNull(other);
        }
        return *this;
    }
    UnifiedDataOrNull& operator=(UnifiedDataOrNull&& other) {
        if (this != &other) {
            ::std::destroy_at(this);
            new (this) UnifiedDataOrNull(::std::move(other));
        }
        return *this;
    }
    ~UnifiedDataOrNull() {
        switch (m_tag) {
        case tag_t::unifiedData: {
            ::std::destroy_at(&m_data.unifiedData);
            break;
        }
        default: {
            break;
        }
        }
    }
    template<typename... Args>
    UnifiedDataOrNull(::taihe::static_tag_t<tag_t::unifiedData>, Args&&... args) : m_tag(tag_t::unifiedData) {
        new (&m_data.unifiedData) decltype(m_data.unifiedData)(::std::forward<Args>(args)...);
    }
    UnifiedDataOrNull(::taihe::static_tag_t<tag_t::nullType>) : m_tag(tag_t::nullType) {}
    template<tag_t tag, typename... Args>
    static UnifiedDataOrNull make(Args&&... args) {
        return UnifiedDataOrNull(::taihe::static_tag<tag>, ::std::forward<Args>(args)...);
    }
    template<tag_t tag, typename... Args>
    UnifiedDataOrNull const& emplace(Args&&... args) {
        ::std::destroy_at(this);
        new (this) UnifiedDataOrNull(::taihe::static_tag<tag>, ::std::forward<Args>(args)...);
        return *this;
    }
    template<tag_t tag>
    auto& get_ref() {
        if constexpr (tag == tag_t::unifiedData) {
            return m_data.unifiedData;
        }
    }
    template<tag_t tag>
    auto* get_ptr() {
        return m_tag == tag ? &get_ref<tag>() : nullptr;
    }
    template<tag_t tag>
    auto const& get_ref() const {
        if constexpr (tag == tag_t::unifiedData) {
            return m_data.unifiedData;
        }
    }
    template<tag_t tag>
    auto const* get_ptr() const {
        return m_tag == tag ? &get_ref<tag>() : nullptr;
    }
    template<tag_t tag>
    bool holds() const {
        return m_tag == tag;
    }
    tag_t get_tag() const {
        return m_tag;
    }
    template<typename Visitor>
    auto accept_template(Visitor&& visitor) {
        switch (m_tag) {
        case tag_t::unifiedData: {
            return visitor(::taihe::static_tag<tag_t::unifiedData>, m_data.unifiedData);
        }
        case tag_t::nullType: {
            return visitor(::taihe::static_tag<tag_t::nullType>);
        }
        }
    }
    template<typename Visitor>
    auto accept_template(Visitor&& visitor) const {
        switch (m_tag) {
        case tag_t::unifiedData: {
            return visitor(::taihe::static_tag<tag_t::unifiedData>, m_data.unifiedData);
        }
        case tag_t::nullType: {
            return visitor(::taihe::static_tag<tag_t::nullType>);
        }
        }
    }
    template<typename... Args>
    static UnifiedDataOrNull make_unifiedData(Args&&... args) {
        return make<tag_t::unifiedData>(::std::forward<Args>(args)...);
    }
    template<typename... Args>
    UnifiedDataOrNull const& emplace_unifiedData(Args&&... args) {
        return emplace<tag_t::unifiedData>(::std::forward<Args>(args)...);
    }
    bool holds_unifiedData() const {
        return holds<tag_t::unifiedData>();
    }
    auto* get_unifiedData_ptr() {
        return get_ptr<tag_t::unifiedData>();
    }
    auto const* get_unifiedData_ptr() const {
        return get_ptr<tag_t::unifiedData>();
    }
    auto& get_unifiedData_ref() {
        return get_ref<tag_t::unifiedData>();
    }
    auto const& get_unifiedData_ref() const {
        return get_ref<tag_t::unifiedData>();
    }
    template<typename... Args>
    static UnifiedDataOrNull make_nullType(Args&&... args) {
        return make<tag_t::nullType>(::std::forward<Args>(args)...);
    }
    template<typename... Args>
    UnifiedDataOrNull const& emplace_nullType(Args&&... args) {
        return emplace<tag_t::nullType>(::std::forward<Args>(args)...);
    }
    bool holds_nullType() const {
        return holds<tag_t::nullType>();
    }
    template<typename Visitor>
    auto accept(Visitor&& visitor) {
        switch (m_tag) {
        case tag_t::unifiedData: {
            return visitor.unifiedData(m_data.unifiedData);
        }
        case tag_t::nullType: {
            return visitor.nullType();
        }
        }
    }
    template<typename Visitor>
    auto accept(Visitor&& visitor) const {
        switch (m_tag) {
        case tag_t::unifiedData: {
            return visitor.unifiedData(m_data.unifiedData);
        }
        case tag_t::nullType: {
            return visitor.nullType();
        }
        }
    }
    private:
    tag_t m_tag;
    storage_t m_data;
};
}
namespace taihe {
inline bool same_impl(adl_helper_t, ::ohos::data::unifiedDataChannel::UnifiedDataOrNull const& lhs, ::ohos::data::unifiedDataChannel::UnifiedDataOrNull const& rhs) {
    return false || (lhs.holds_unifiedData() && rhs.holds_unifiedData() && same(lhs.get_unifiedData_ref(), rhs.get_unifiedData_ref())) || (lhs.holds_nullType() && rhs.holds_nullType());
}
}
namespace taihe {
inline auto hash_impl(adl_helper_t, ::ohos::data::unifiedDataChannel::UnifiedDataOrNull const& val) -> ::std::size_t {
    switch (val.get_tag()) {
    case ::ohos::data::unifiedDataChannel::UnifiedDataOrNull::tag_t::unifiedData: {
        ::std::size_t seed = (::std::size_t)::ohos::data::unifiedDataChannel::UnifiedDataOrNull::tag_t::unifiedData;
        return seed ^ (0x9e3779b9 + (seed << 6) + (seed >> 2) + hash(val.get_unifiedData_ref()));
    }
    case ::ohos::data::unifiedDataChannel::UnifiedDataOrNull::tag_t::nullType: {
        ::std::size_t seed = (::std::size_t)::ohos::data::unifiedDataChannel::UnifiedDataOrNull::tag_t::nullType;
        return seed ^ (0x9e3779b9 + (seed << 6) + (seed >> 2));
    }
    }
}
}
namespace taihe {
template<>
struct as_abi<::ohos::data::unifiedDataChannel::UnifiedDataOrNull> {
    using type = struct ohos_data_unifiedDataChannel_UnifiedDataOrNull_t;
};
template<>
struct as_abi<::ohos::data::unifiedDataChannel::UnifiedDataOrNull const&> {
    using type = struct ohos_data_unifiedDataChannel_UnifiedDataOrNull_t const*;
};
template<>
struct as_param<::ohos::data::unifiedDataChannel::UnifiedDataOrNull> {
    using type = ::ohos::data::unifiedDataChannel::UnifiedDataOrNull const&;
};
}
