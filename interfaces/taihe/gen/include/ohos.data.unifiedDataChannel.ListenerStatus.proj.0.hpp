#pragma once
#include "taihe/common.hpp"
namespace ohos::data::unifiedDataChannel {
struct ListenerStatus {
    public:
    enum class key_t: int {
        FINISHED,
        PROCESSING,
        CANCELED,
        INNER_ERROR,
        INVALID_PARAMETERS,
        DATA_NOT_FOUND,
        SYNC_FAILED,
        COPY_FILE_FAILED,
    };
    ListenerStatus(ListenerStatus const& other) : key(other.key) {}
    ListenerStatus& operator=(ListenerStatus other) {
        key = other.key;
        return *this;
    }
    ListenerStatus(key_t key) : key(key) {}
    key_t get_key() const {
        return this->key;
    }
    bool is_valid() const {
        return (int)key >= 0 && (int)key < 8;
    }
    static constexpr int32_t table[] = {
        0,
        1,
        2,
        200,
        201,
        202,
        203,
        204,
    };
    int32_t get_value() const {
        return table[(int)key];
    }
    operator int32_t() const {
        return table[(int)key];
    }
    static ::ohos::data::unifiedDataChannel::ListenerStatus from_value(int32_t value) {
        for (size_t i = 0; i < 8; ++i) {
            if (::taihe::same(table[i], value)) {
                return ::ohos::data::unifiedDataChannel::ListenerStatus((key_t)i);
            }
        }
        return ::ohos::data::unifiedDataChannel::ListenerStatus((key_t)-1);
    }
    private:
    key_t key;
};
}
namespace taihe {
inline bool same_impl(adl_helper_t, ::ohos::data::unifiedDataChannel::ListenerStatus lhs, ::ohos::data::unifiedDataChannel::ListenerStatus rhs) {
    return lhs.get_key() == rhs.get_key();
}
}
namespace taihe {
inline auto hash_impl(adl_helper_t, ::ohos::data::unifiedDataChannel::ListenerStatus val) -> ::std::size_t {
    return ::std::hash<int>{}((int)val.get_key());
}
}
namespace taihe {
template<>
struct as_abi<::ohos::data::unifiedDataChannel::ListenerStatus> {
    using type = int;
};
template<>
struct as_param<::ohos::data::unifiedDataChannel::ListenerStatus> {
    using type = ::ohos::data::unifiedDataChannel::ListenerStatus;
};
}
