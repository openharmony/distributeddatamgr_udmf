#pragma once
#include "taihe/common.hpp"
namespace ohos::data::unifiedDataChannel {
struct ProgressIndicator {
    public:
    enum class key_t: int {
        NONE,
        DEFAULT,
    };
    ProgressIndicator(ProgressIndicator const& other) : key(other.key) {}
    ProgressIndicator& operator=(ProgressIndicator other) {
        key = other.key;
        return *this;
    }
    ProgressIndicator(key_t key) : key(key) {}
    key_t get_key() const {
        return this->key;
    }
    bool is_valid() const {
        return (int)key >= 0 && (int)key < 2;
    }
    static constexpr int32_t table[] = {
        0,
        1,
    };
    int32_t get_value() const {
        return table[(int)key];
    }
    operator int32_t() const {
        return table[(int)key];
    }
    static ::ohos::data::unifiedDataChannel::ProgressIndicator from_value(int32_t value) {
        for (size_t i = 0; i < 2; ++i) {
            if (::taihe::same(table[i], value)) {
                return ::ohos::data::unifiedDataChannel::ProgressIndicator((key_t)i);
            }
        }
        return ::ohos::data::unifiedDataChannel::ProgressIndicator((key_t)-1);
    }
    private:
    key_t key;
};
}
namespace taihe {
inline bool same_impl(adl_helper_t, ::ohos::data::unifiedDataChannel::ProgressIndicator lhs, ::ohos::data::unifiedDataChannel::ProgressIndicator rhs) {
    return lhs.get_key() == rhs.get_key();
}
}
namespace taihe {
inline auto hash_impl(adl_helper_t, ::ohos::data::unifiedDataChannel::ProgressIndicator val) -> ::std::size_t {
    return ::std::hash<int>{}((int)val.get_key());
}
}
namespace taihe {
template<>
struct as_abi<::ohos::data::unifiedDataChannel::ProgressIndicator> {
    using type = int;
};
template<>
struct as_param<::ohos::data::unifiedDataChannel::ProgressIndicator> {
    using type = ::ohos::data::unifiedDataChannel::ProgressIndicator;
};
}
