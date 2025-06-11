#pragma once
#include "taihe/common.hpp"
#include "ohos.data.unifiedDataChannel.ValueType.proj.0.hpp"
#include "ohos.data.unifiedDataChannel.ValueType.abi.1.h"
#include "taihe/string.hpp"
#include "taihe/array.hpp"
namespace ohos::data::unifiedDataChannel {
struct ValueType {
    public:
    enum class tag_t : int {
        number,
        string,
        boolean,
        ArrayBuffer,
        nullType,
        undefinedType,
        object,
    };
    union storage_t {
        storage_t() {}
        ~storage_t() {}
        double number;
        ::taihe::string string;
        bool boolean;
        ::taihe::array<uint8_t> ArrayBuffer;
        uintptr_t object;
    };
    ValueType(ValueType const& other) : m_tag(other.m_tag) {
        switch (m_tag) {
        case tag_t::number: {
            new (&m_data.number) decltype(m_data.number)(other.m_data.number);
            break;
        }
        case tag_t::string: {
            new (&m_data.string) decltype(m_data.string)(other.m_data.string);
            break;
        }
        case tag_t::boolean: {
            new (&m_data.boolean) decltype(m_data.boolean)(other.m_data.boolean);
            break;
        }
        case tag_t::ArrayBuffer: {
            new (&m_data.ArrayBuffer) decltype(m_data.ArrayBuffer)(other.m_data.ArrayBuffer);
            break;
        }
        case tag_t::object: {
            new (&m_data.object) decltype(m_data.object)(other.m_data.object);
            break;
        }
        default: {
            break;
        }
        }
    }
    ValueType(ValueType&& other) : m_tag(other.m_tag) {
        switch (m_tag) {
        case tag_t::number: {
            new (&m_data.number) decltype(m_data.number)(::std::move(other.m_data.number));
            break;
        }
        case tag_t::string: {
            new (&m_data.string) decltype(m_data.string)(::std::move(other.m_data.string));
            break;
        }
        case tag_t::boolean: {
            new (&m_data.boolean) decltype(m_data.boolean)(::std::move(other.m_data.boolean));
            break;
        }
        case tag_t::ArrayBuffer: {
            new (&m_data.ArrayBuffer) decltype(m_data.ArrayBuffer)(::std::move(other.m_data.ArrayBuffer));
            break;
        }
        case tag_t::object: {
            new (&m_data.object) decltype(m_data.object)(::std::move(other.m_data.object));
            break;
        }
        default: {
            break;
        }
        }
    }
    ValueType& operator=(ValueType const& other) {
        if (this != &other) {
            ::std::destroy_at(this);
            new (this) ValueType(other);
        }
        return *this;
    }
    ValueType& operator=(ValueType&& other) {
        if (this != &other) {
            ::std::destroy_at(this);
            new (this) ValueType(::std::move(other));
        }
        return *this;
    }
    ~ValueType() {
        switch (m_tag) {
        case tag_t::number: {
            ::std::destroy_at(&m_data.number);
            break;
        }
        case tag_t::string: {
            ::std::destroy_at(&m_data.string);
            break;
        }
        case tag_t::boolean: {
            ::std::destroy_at(&m_data.boolean);
            break;
        }
        case tag_t::ArrayBuffer: {
            ::std::destroy_at(&m_data.ArrayBuffer);
            break;
        }
        case tag_t::object: {
            ::std::destroy_at(&m_data.object);
            break;
        }
        default: {
            break;
        }
        }
    }
    template<typename... Args>
    ValueType(::taihe::static_tag_t<tag_t::number>, Args&&... args) : m_tag(tag_t::number) {
        new (&m_data.number) decltype(m_data.number)(::std::forward<Args>(args)...);
    }
    template<typename... Args>
    ValueType(::taihe::static_tag_t<tag_t::string>, Args&&... args) : m_tag(tag_t::string) {
        new (&m_data.string) decltype(m_data.string)(::std::forward<Args>(args)...);
    }
    template<typename... Args>
    ValueType(::taihe::static_tag_t<tag_t::boolean>, Args&&... args) : m_tag(tag_t::boolean) {
        new (&m_data.boolean) decltype(m_data.boolean)(::std::forward<Args>(args)...);
    }
    template<typename... Args>
    ValueType(::taihe::static_tag_t<tag_t::ArrayBuffer>, Args&&... args) : m_tag(tag_t::ArrayBuffer) {
        new (&m_data.ArrayBuffer) decltype(m_data.ArrayBuffer)(::std::forward<Args>(args)...);
    }
    ValueType(::taihe::static_tag_t<tag_t::nullType>) : m_tag(tag_t::nullType) {}
    ValueType(::taihe::static_tag_t<tag_t::undefinedType>) : m_tag(tag_t::undefinedType) {}
    template<typename... Args>
    ValueType(::taihe::static_tag_t<tag_t::object>, Args&&... args) : m_tag(tag_t::object) {
        new (&m_data.object) decltype(m_data.object)(::std::forward<Args>(args)...);
    }
    template<tag_t tag, typename... Args>
    static ValueType make(Args&&... args) {
        return ValueType(::taihe::static_tag<tag>, ::std::forward<Args>(args)...);
    }
    template<tag_t tag, typename... Args>
    ValueType const& emplace(Args&&... args) {
        ::std::destroy_at(this);
        new (this) ValueType(::taihe::static_tag<tag>, ::std::forward<Args>(args)...);
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
        if constexpr (tag == tag_t::boolean) {
            return m_data.boolean;
        }
        if constexpr (tag == tag_t::ArrayBuffer) {
            return m_data.ArrayBuffer;
        }
        if constexpr (tag == tag_t::object) {
            return m_data.object;
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
        if constexpr (tag == tag_t::boolean) {
            return m_data.boolean;
        }
        if constexpr (tag == tag_t::ArrayBuffer) {
            return m_data.ArrayBuffer;
        }
        if constexpr (tag == tag_t::object) {
            return m_data.object;
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
        case tag_t::boolean: {
            return visitor(::taihe::static_tag<tag_t::boolean>, m_data.boolean);
        }
        case tag_t::ArrayBuffer: {
            return visitor(::taihe::static_tag<tag_t::ArrayBuffer>, m_data.ArrayBuffer);
        }
        case tag_t::nullType: {
            return visitor(::taihe::static_tag<tag_t::nullType>);
        }
        case tag_t::undefinedType: {
            return visitor(::taihe::static_tag<tag_t::undefinedType>);
        }
        case tag_t::object: {
            return visitor(::taihe::static_tag<tag_t::object>, m_data.object);
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
        case tag_t::boolean: {
            return visitor(::taihe::static_tag<tag_t::boolean>, m_data.boolean);
        }
        case tag_t::ArrayBuffer: {
            return visitor(::taihe::static_tag<tag_t::ArrayBuffer>, m_data.ArrayBuffer);
        }
        case tag_t::nullType: {
            return visitor(::taihe::static_tag<tag_t::nullType>);
        }
        case tag_t::undefinedType: {
            return visitor(::taihe::static_tag<tag_t::undefinedType>);
        }
        case tag_t::object: {
            return visitor(::taihe::static_tag<tag_t::object>, m_data.object);
        }
        }
    }
    template<typename... Args>
    static ValueType make_number(Args&&... args) {
        return make<tag_t::number>(::std::forward<Args>(args)...);
    }
    template<typename... Args>
    ValueType const& emplace_number(Args&&... args) {
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
    static ValueType make_string(Args&&... args) {
        return make<tag_t::string>(::std::forward<Args>(args)...);
    }
    template<typename... Args>
    ValueType const& emplace_string(Args&&... args) {
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
    static ValueType make_boolean(Args&&... args) {
        return make<tag_t::boolean>(::std::forward<Args>(args)...);
    }
    template<typename... Args>
    ValueType const& emplace_boolean(Args&&... args) {
        return emplace<tag_t::boolean>(::std::forward<Args>(args)...);
    }
    bool holds_boolean() const {
        return holds<tag_t::boolean>();
    }
    auto* get_boolean_ptr() {
        return get_ptr<tag_t::boolean>();
    }
    auto const* get_boolean_ptr() const {
        return get_ptr<tag_t::boolean>();
    }
    auto& get_boolean_ref() {
        return get_ref<tag_t::boolean>();
    }
    auto const& get_boolean_ref() const {
        return get_ref<tag_t::boolean>();
    }
    template<typename... Args>
    static ValueType make_ArrayBuffer(Args&&... args) {
        return make<tag_t::ArrayBuffer>(::std::forward<Args>(args)...);
    }
    template<typename... Args>
    ValueType const& emplace_ArrayBuffer(Args&&... args) {
        return emplace<tag_t::ArrayBuffer>(::std::forward<Args>(args)...);
    }
    bool holds_ArrayBuffer() const {
        return holds<tag_t::ArrayBuffer>();
    }
    auto* get_ArrayBuffer_ptr() {
        return get_ptr<tag_t::ArrayBuffer>();
    }
    auto const* get_ArrayBuffer_ptr() const {
        return get_ptr<tag_t::ArrayBuffer>();
    }
    auto& get_ArrayBuffer_ref() {
        return get_ref<tag_t::ArrayBuffer>();
    }
    auto const& get_ArrayBuffer_ref() const {
        return get_ref<tag_t::ArrayBuffer>();
    }
    template<typename... Args>
    static ValueType make_nullType(Args&&... args) {
        return make<tag_t::nullType>(::std::forward<Args>(args)...);
    }
    template<typename... Args>
    ValueType const& emplace_nullType(Args&&... args) {
        return emplace<tag_t::nullType>(::std::forward<Args>(args)...);
    }
    bool holds_nullType() const {
        return holds<tag_t::nullType>();
    }
    template<typename... Args>
    static ValueType make_undefinedType(Args&&... args) {
        return make<tag_t::undefinedType>(::std::forward<Args>(args)...);
    }
    template<typename... Args>
    ValueType const& emplace_undefinedType(Args&&... args) {
        return emplace<tag_t::undefinedType>(::std::forward<Args>(args)...);
    }
    bool holds_undefinedType() const {
        return holds<tag_t::undefinedType>();
    }
    template<typename... Args>
    static ValueType make_object(Args&&... args) {
        return make<tag_t::object>(::std::forward<Args>(args)...);
    }
    template<typename... Args>
    ValueType const& emplace_object(Args&&... args) {
        return emplace<tag_t::object>(::std::forward<Args>(args)...);
    }
    bool holds_object() const {
        return holds<tag_t::object>();
    }
    auto* get_object_ptr() {
        return get_ptr<tag_t::object>();
    }
    auto const* get_object_ptr() const {
        return get_ptr<tag_t::object>();
    }
    auto& get_object_ref() {
        return get_ref<tag_t::object>();
    }
    auto const& get_object_ref() const {
        return get_ref<tag_t::object>();
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
        case tag_t::boolean: {
            return visitor.boolean(m_data.boolean);
        }
        case tag_t::ArrayBuffer: {
            return visitor.ArrayBuffer(m_data.ArrayBuffer);
        }
        case tag_t::nullType: {
            return visitor.nullType();
        }
        case tag_t::undefinedType: {
            return visitor.undefinedType();
        }
        case tag_t::object: {
            return visitor.object(m_data.object);
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
        case tag_t::boolean: {
            return visitor.boolean(m_data.boolean);
        }
        case tag_t::ArrayBuffer: {
            return visitor.ArrayBuffer(m_data.ArrayBuffer);
        }
        case tag_t::nullType: {
            return visitor.nullType();
        }
        case tag_t::undefinedType: {
            return visitor.undefinedType();
        }
        case tag_t::object: {
            return visitor.object(m_data.object);
        }
        }
    }
    private:
    tag_t m_tag;
    storage_t m_data;
};
}
namespace taihe {
inline bool same_impl(adl_helper_t, ::ohos::data::unifiedDataChannel::ValueType const& lhs, ::ohos::data::unifiedDataChannel::ValueType const& rhs) {
    return false || (lhs.holds_number() && rhs.holds_number() && same(lhs.get_number_ref(), rhs.get_number_ref())) || (lhs.holds_string() && rhs.holds_string() && same(lhs.get_string_ref(), rhs.get_string_ref())) || (lhs.holds_boolean() && rhs.holds_boolean() && same(lhs.get_boolean_ref(), rhs.get_boolean_ref())) || (lhs.holds_ArrayBuffer() && rhs.holds_ArrayBuffer() && same(lhs.get_ArrayBuffer_ref(), rhs.get_ArrayBuffer_ref())) || (lhs.holds_nullType() && rhs.holds_nullType()) || (lhs.holds_undefinedType() && rhs.holds_undefinedType()) || (lhs.holds_object() && rhs.holds_object() && same(lhs.get_object_ref(), rhs.get_object_ref()));
}
}
namespace taihe {
inline auto hash_impl(adl_helper_t, ::ohos::data::unifiedDataChannel::ValueType const& val) -> ::std::size_t {
    switch (val.get_tag()) {
    case ::ohos::data::unifiedDataChannel::ValueType::tag_t::number: {
        ::std::size_t seed = (::std::size_t)::ohos::data::unifiedDataChannel::ValueType::tag_t::number;
        return seed ^ (0x9e3779b9 + (seed << 6) + (seed >> 2) + hash(val.get_number_ref()));
    }
    case ::ohos::data::unifiedDataChannel::ValueType::tag_t::string: {
        ::std::size_t seed = (::std::size_t)::ohos::data::unifiedDataChannel::ValueType::tag_t::string;
        return seed ^ (0x9e3779b9 + (seed << 6) + (seed >> 2) + hash(val.get_string_ref()));
    }
    case ::ohos::data::unifiedDataChannel::ValueType::tag_t::boolean: {
        ::std::size_t seed = (::std::size_t)::ohos::data::unifiedDataChannel::ValueType::tag_t::boolean;
        return seed ^ (0x9e3779b9 + (seed << 6) + (seed >> 2) + hash(val.get_boolean_ref()));
    }
    case ::ohos::data::unifiedDataChannel::ValueType::tag_t::ArrayBuffer: {
        ::std::size_t seed = (::std::size_t)::ohos::data::unifiedDataChannel::ValueType::tag_t::ArrayBuffer;
        return seed ^ (0x9e3779b9 + (seed << 6) + (seed >> 2) + hash(val.get_ArrayBuffer_ref()));
    }
    case ::ohos::data::unifiedDataChannel::ValueType::tag_t::nullType: {
        ::std::size_t seed = (::std::size_t)::ohos::data::unifiedDataChannel::ValueType::tag_t::nullType;
        return seed ^ (0x9e3779b9 + (seed << 6) + (seed >> 2));
    }
    case ::ohos::data::unifiedDataChannel::ValueType::tag_t::undefinedType: {
        ::std::size_t seed = (::std::size_t)::ohos::data::unifiedDataChannel::ValueType::tag_t::undefinedType;
        return seed ^ (0x9e3779b9 + (seed << 6) + (seed >> 2));
    }
    case ::ohos::data::unifiedDataChannel::ValueType::tag_t::object: {
        ::std::size_t seed = (::std::size_t)::ohos::data::unifiedDataChannel::ValueType::tag_t::object;
        return seed ^ (0x9e3779b9 + (seed << 6) + (seed >> 2) + hash(val.get_object_ref()));
    }
    }
}
}
namespace taihe {
template<>
struct as_abi<::ohos::data::unifiedDataChannel::ValueType> {
    using type = struct ohos_data_unifiedDataChannel_ValueType_t;
};
template<>
struct as_abi<::ohos::data::unifiedDataChannel::ValueType const&> {
    using type = struct ohos_data_unifiedDataChannel_ValueType_t const*;
};
template<>
struct as_param<::ohos::data::unifiedDataChannel::ValueType> {
    using type = ::ohos::data::unifiedDataChannel::ValueType const&;
};
}
