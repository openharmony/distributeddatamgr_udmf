#pragma once
#include "taihe/common.hpp"
#include "ohos.data.unifiedDataChannel.DetailsValue.proj.0.hpp"
#include "ohos.data.unifiedDataChannel.DetailsValue.abi.1.h"
#include "taihe/string.hpp"
#include "taihe/array.hpp"
namespace ohos::data::unifiedDataChannel {
struct DetailsValue {
    public:
    enum class tag_t : int {
        number,
        string,
        Uint8Array,
    };
    union storage_t {
        storage_t() {}
        ~storage_t() {}
        double number;
        ::taihe::string string;
        ::taihe::array<uint8_t> Uint8Array;
    };
    DetailsValue(DetailsValue const& other) : m_tag(other.m_tag) {
        switch (m_tag) {
        case tag_t::number: {
            new (&m_data.number) decltype(m_data.number)(other.m_data.number);
            break;
        }
        case tag_t::string: {
            new (&m_data.string) decltype(m_data.string)(other.m_data.string);
            break;
        }
        case tag_t::Uint8Array: {
            new (&m_data.Uint8Array) decltype(m_data.Uint8Array)(other.m_data.Uint8Array);
            break;
        }
        default: {
            break;
        }
        }
    }
    DetailsValue(DetailsValue&& other) : m_tag(other.m_tag) {
        switch (m_tag) {
        case tag_t::number: {
            new (&m_data.number) decltype(m_data.number)(::std::move(other.m_data.number));
            break;
        }
        case tag_t::string: {
            new (&m_data.string) decltype(m_data.string)(::std::move(other.m_data.string));
            break;
        }
        case tag_t::Uint8Array: {
            new (&m_data.Uint8Array) decltype(m_data.Uint8Array)(::std::move(other.m_data.Uint8Array));
            break;
        }
        default: {
            break;
        }
        }
    }
    DetailsValue& operator=(DetailsValue const& other) {
        if (this != &other) {
            ::std::destroy_at(this);
            new (this) DetailsValue(other);
        }
        return *this;
    }
    DetailsValue& operator=(DetailsValue&& other) {
        if (this != &other) {
            ::std::destroy_at(this);
            new (this) DetailsValue(::std::move(other));
        }
        return *this;
    }
    ~DetailsValue() {
        switch (m_tag) {
        case tag_t::number: {
            ::std::destroy_at(&m_data.number);
            break;
        }
        case tag_t::string: {
            ::std::destroy_at(&m_data.string);
            break;
        }
        case tag_t::Uint8Array: {
            ::std::destroy_at(&m_data.Uint8Array);
            break;
        }
        default: {
            break;
        }
        }
    }
    template<typename... Args>
    DetailsValue(::taihe::static_tag_t<tag_t::number>, Args&&... args) : m_tag(tag_t::number) {
        new (&m_data.number) decltype(m_data.number)(::std::forward<Args>(args)...);
    }
    template<typename... Args>
    DetailsValue(::taihe::static_tag_t<tag_t::string>, Args&&... args) : m_tag(tag_t::string) {
        new (&m_data.string) decltype(m_data.string)(::std::forward<Args>(args)...);
    }
    template<typename... Args>
    DetailsValue(::taihe::static_tag_t<tag_t::Uint8Array>, Args&&... args) : m_tag(tag_t::Uint8Array) {
        new (&m_data.Uint8Array) decltype(m_data.Uint8Array)(::std::forward<Args>(args)...);
    }
    template<tag_t tag, typename... Args>
    static DetailsValue make(Args&&... args) {
        return DetailsValue(::taihe::static_tag<tag>, ::std::forward<Args>(args)...);
    }
    template<tag_t tag, typename... Args>
    DetailsValue const& emplace(Args&&... args) {
        ::std::destroy_at(this);
        new (this) DetailsValue(::taihe::static_tag<tag>, ::std::forward<Args>(args)...);
        return *this;
    }
    template<tag_t tag>
    auto& get_ref() {
        if constexpr (tag == tag_t::number) {
            return m_data.number;
        }
        if constexpr (tag == tag_t::string) {
            return m_data.string;
        }
        if constexpr (tag == tag_t::Uint8Array) {
            return m_data.Uint8Array;
        }
    }
    template<tag_t tag>
    auto* get_ptr() {
        return m_tag == tag ? &get_ref<tag>() : nullptr;
    }
    template<tag_t tag>
    auto const& get_ref() const {
        if constexpr (tag == tag_t::number) {
            return m_data.number;
        }
        if constexpr (tag == tag_t::string) {
            return m_data.string;
        }
        if constexpr (tag == tag_t::Uint8Array) {
            return m_data.Uint8Array;
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
        case tag_t::number: {
            return visitor(::taihe::static_tag<tag_t::number>, m_data.number);
        }
        case tag_t::string: {
            return visitor(::taihe::static_tag<tag_t::string>, m_data.string);
        }
        case tag_t::Uint8Array: {
            return visitor(::taihe::static_tag<tag_t::Uint8Array>, m_data.Uint8Array);
        }
        }
    }
    template<typename Visitor>
    auto accept_template(Visitor&& visitor) const {
        switch (m_tag) {
        case tag_t::number: {
            return visitor(::taihe::static_tag<tag_t::number>, m_data.number);
        }
        case tag_t::string: {
            return visitor(::taihe::static_tag<tag_t::string>, m_data.string);
        }
        case tag_t::Uint8Array: {
            return visitor(::taihe::static_tag<tag_t::Uint8Array>, m_data.Uint8Array);
        }
        }
    }
    template<typename... Args>
    static DetailsValue make_number(Args&&... args) {
        return make<tag_t::number>(::std::forward<Args>(args)...);
    }
    template<typename... Args>
    DetailsValue const& emplace_number(Args&&... args) {
        return emplace<tag_t::number>(::std::forward<Args>(args)...);
    }
    bool holds_number() const {
        return holds<tag_t::number>();
    }
    auto* get_number_ptr() {
        return get_ptr<tag_t::number>();
    }
    auto const* get_number_ptr() const {
        return get_ptr<tag_t::number>();
    }
    auto& get_number_ref() {
        return get_ref<tag_t::number>();
    }
    auto const& get_number_ref() const {
        return get_ref<tag_t::number>();
    }
    template<typename... Args>
    static DetailsValue make_string(Args&&... args) {
        return make<tag_t::string>(::std::forward<Args>(args)...);
    }
    template<typename... Args>
    DetailsValue const& emplace_string(Args&&... args) {
        return emplace<tag_t::string>(::std::forward<Args>(args)...);
    }
    bool holds_string() const {
        return holds<tag_t::string>();
    }
    auto* get_string_ptr() {
        return get_ptr<tag_t::string>();
    }
    auto const* get_string_ptr() const {
        return get_ptr<tag_t::string>();
    }
    auto& get_string_ref() {
        return get_ref<tag_t::string>();
    }
    auto const& get_string_ref() const {
        return get_ref<tag_t::string>();
    }
    template<typename... Args>
    static DetailsValue make_Uint8Array(Args&&... args) {
        return make<tag_t::Uint8Array>(::std::forward<Args>(args)...);
    }
    template<typename... Args>
    DetailsValue const& emplace_Uint8Array(Args&&... args) {
        return emplace<tag_t::Uint8Array>(::std::forward<Args>(args)...);
    }
    bool holds_Uint8Array() const {
        return holds<tag_t::Uint8Array>();
    }
    auto* get_Uint8Array_ptr() {
        return get_ptr<tag_t::Uint8Array>();
    }
    auto const* get_Uint8Array_ptr() const {
        return get_ptr<tag_t::Uint8Array>();
    }
    auto& get_Uint8Array_ref() {
        return get_ref<tag_t::Uint8Array>();
    }
    auto const& get_Uint8Array_ref() const {
        return get_ref<tag_t::Uint8Array>();
    }
    template<typename Visitor>
    auto accept(Visitor&& visitor) {
        switch (m_tag) {
        case tag_t::number: {
            return visitor.number(m_data.number);
        }
        case tag_t::string: {
            return visitor.string(m_data.string);
        }
        case tag_t::Uint8Array: {
            return visitor.Uint8Array(m_data.Uint8Array);
        }
        }
    }
    template<typename Visitor>
    auto accept(Visitor&& visitor) const {
        switch (m_tag) {
        case tag_t::number: {
            return visitor.number(m_data.number);
        }
        case tag_t::string: {
            return visitor.string(m_data.string);
        }
        case tag_t::Uint8Array: {
            return visitor.Uint8Array(m_data.Uint8Array);
        }
        }
    }
    private:
    tag_t m_tag;
    storage_t m_data;
};
}
namespace taihe {
inline bool same_impl(adl_helper_t, ::ohos::data::unifiedDataChannel::DetailsValue const& lhs, ::ohos::data::unifiedDataChannel::DetailsValue const& rhs) {
    return false || (lhs.holds_number() && rhs.holds_number() && same(lhs.get_number_ref(), rhs.get_number_ref())) || (lhs.holds_string() && rhs.holds_string() && same(lhs.get_string_ref(), rhs.get_string_ref())) || (lhs.holds_Uint8Array() && rhs.holds_Uint8Array() && same(lhs.get_Uint8Array_ref(), rhs.get_Uint8Array_ref()));
}
}
namespace taihe {
inline auto hash_impl(adl_helper_t, ::ohos::data::unifiedDataChannel::DetailsValue const& val) -> ::std::size_t {
    switch (val.get_tag()) {
    case ::ohos::data::unifiedDataChannel::DetailsValue::tag_t::number: {
        ::std::size_t seed = (::std::size_t)::ohos::data::unifiedDataChannel::DetailsValue::tag_t::number;
        return seed ^ (0x9e3779b9 + (seed << 6) + (seed >> 2) + hash(val.get_number_ref()));
    }
    case ::ohos::data::unifiedDataChannel::DetailsValue::tag_t::string: {
        ::std::size_t seed = (::std::size_t)::ohos::data::unifiedDataChannel::DetailsValue::tag_t::string;
        return seed ^ (0x9e3779b9 + (seed << 6) + (seed >> 2) + hash(val.get_string_ref()));
    }
    case ::ohos::data::unifiedDataChannel::DetailsValue::tag_t::Uint8Array: {
        ::std::size_t seed = (::std::size_t)::ohos::data::unifiedDataChannel::DetailsValue::tag_t::Uint8Array;
        return seed ^ (0x9e3779b9 + (seed << 6) + (seed >> 2) + hash(val.get_Uint8Array_ref()));
    }
    }
}
}
namespace taihe {
template<>
struct as_abi<::ohos::data::unifiedDataChannel::DetailsValue> {
    using type = struct ohos_data_unifiedDataChannel_DetailsValue_t;
};
template<>
struct as_abi<::ohos::data::unifiedDataChannel::DetailsValue const&> {
    using type = struct ohos_data_unifiedDataChannel_DetailsValue_t const*;
};
template<>
struct as_param<::ohos::data::unifiedDataChannel::DetailsValue> {
    using type = ::ohos::data::unifiedDataChannel::DetailsValue const&;
};
}
