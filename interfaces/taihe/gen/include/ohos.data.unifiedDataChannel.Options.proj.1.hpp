#pragma once
#include "taihe/common.hpp"
#include "ohos.data.unifiedDataChannel.Options.proj.0.hpp"
#include "ohos.data.unifiedDataChannel.Options.abi.1.h"
#include "taihe/optional.hpp"
#include "ohos.data.unifiedDataChannel.Intention.proj.0.hpp"
#include "taihe/string.hpp"
namespace ohos::data::unifiedDataChannel {
struct Options {
    ::taihe::optional<::ohos::data::unifiedDataChannel::Intention> intention;
    ::taihe::optional<::taihe::string> key;
};
}
namespace taihe {
inline auto hash_impl(adl_helper_t, ::ohos::data::unifiedDataChannel::Options const& val) -> ::std::size_t {
    ::std::size_t seed = 0;
    seed ^= hash(val.intention) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    seed ^= hash(val.key) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    return seed;
}
}
namespace taihe {
inline bool same_impl(adl_helper_t, ::ohos::data::unifiedDataChannel::Options const& lhs, ::ohos::data::unifiedDataChannel::Options const& rhs) {
    return true && same(lhs.intention, rhs.intention) && same(lhs.key, rhs.key);
}
}
namespace taihe {
template<>
struct as_abi<::ohos::data::unifiedDataChannel::Options> {
    using type = struct ohos_data_unifiedDataChannel_Options_t;
};
template<>
struct as_abi<::ohos::data::unifiedDataChannel::Options const&> {
    using type = struct ohos_data_unifiedDataChannel_Options_t const*;
};
template<>
struct as_param<::ohos::data::unifiedDataChannel::Options> {
    using type = ::ohos::data::unifiedDataChannel::Options const&;
};
}
