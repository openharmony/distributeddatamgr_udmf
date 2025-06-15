#pragma once
#include "taihe/common.hpp"
namespace ohos::data::unifiedDataChannel {
struct FileConflictOptions {
    public:
    enum class key_t: int {
        OVERWRITE,
        SKIP,
    };
    FileConflictOptions(FileConflictOptions const& other) : key(other.key) {}
    FileConflictOptions& operator=(FileConflictOptions other) {
        key = other.key;
        return *this;
    }
    FileConflictOptions(key_t key) : key(key) {}
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
    static ::ohos::data::unifiedDataChannel::FileConflictOptions from_value(int32_t value) {
        for (size_t i = 0; i < 2; ++i) {
            if (::taihe::same(table[i], value)) {
                return ::ohos::data::unifiedDataChannel::FileConflictOptions((key_t)i);
            }
        }
        return ::ohos::data::unifiedDataChannel::FileConflictOptions((key_t)-1);
    }
    private:
    key_t key;
};
}
namespace taihe {
inline bool same_impl(adl_helper_t, ::ohos::data::unifiedDataChannel::FileConflictOptions lhs, ::ohos::data::unifiedDataChannel::FileConflictOptions rhs) {
    return lhs.get_key() == rhs.get_key();
}
}
namespace taihe {
inline auto hash_impl(adl_helper_t, ::ohos::data::unifiedDataChannel::FileConflictOptions val) -> ::std::size_t {
    return ::std::hash<int>{}((int)val.get_key());
}
}
namespace taihe {
template<>
struct as_abi<::ohos::data::unifiedDataChannel::FileConflictOptions> {
    using type = int;
};
template<>
struct as_param<::ohos::data::unifiedDataChannel::FileConflictOptions> {
    using type = ::ohos::data::unifiedDataChannel::FileConflictOptions;
};
}
