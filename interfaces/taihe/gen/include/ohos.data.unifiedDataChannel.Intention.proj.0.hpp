#pragma once
#include "taihe/common.hpp"
#include "taihe/string.hpp"
namespace ohos::data::unifiedDataChannel {
struct Intention {
    public:
    enum class key_t: int {
        DATA_HUB,
        DRAG,
    };
    Intention(Intention const& other) : key(other.key) {}
    Intention& operator=(Intention other) {
        key = other.key;
        return *this;
    }
    Intention(key_t key) : key(key) {}
    key_t get_key() const {
        return this->key;
    }
    bool is_valid() const {
        return (int)key >= 0 && (int)key < 2;
    }
    static constexpr char const* table[] = {
        "DataHub",
        "Drag",
    };
    char const* get_value() const {
        return table[(int)key];
    }
    operator char const*() const {
        return table[(int)key];
    }
    static ::ohos::data::unifiedDataChannel::Intention from_value(::taihe::string_view value) {
        for (size_t i = 0; i < 2; ++i) {
            if (::taihe::same(table[i], value)) {
                return ::ohos::data::unifiedDataChannel::Intention((key_t)i);
            }
        }
        return ::ohos::data::unifiedDataChannel::Intention((key_t)-1);
    }
    private:
    key_t key;
};
}
namespace taihe {
inline bool same_impl(adl_helper_t, ::ohos::data::unifiedDataChannel::Intention lhs, ::ohos::data::unifiedDataChannel::Intention rhs) {
    return lhs.get_key() == rhs.get_key();
}
}
namespace taihe {
inline auto hash_impl(adl_helper_t, ::ohos::data::unifiedDataChannel::Intention val) -> ::std::size_t {
    return ::std::hash<int>{}((int)val.get_key());
}
}
namespace taihe {
template<>
struct as_abi<::ohos::data::unifiedDataChannel::Intention> {
    using type = int;
};
template<>
struct as_param<::ohos::data::unifiedDataChannel::Intention> {
    using type = ::ohos::data::unifiedDataChannel::Intention;
};
}
