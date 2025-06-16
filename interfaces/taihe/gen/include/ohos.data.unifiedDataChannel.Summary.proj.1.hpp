#pragma once
#include "taihe/common.hpp"
#include "ohos.data.unifiedDataChannel.Summary.proj.0.hpp"
#include "ohos.data.unifiedDataChannel.Summary.abi.1.h"
#include "taihe/map.hpp"
#include "taihe/string.hpp"
namespace ohos::data::unifiedDataChannel {
struct Summary {
    ::taihe::map<::taihe::string, double> summary;
    double totalSize;
};
}
namespace taihe {
inline auto hash_impl(adl_helper_t, ::ohos::data::unifiedDataChannel::Summary const& val) -> ::std::size_t {
    ::std::size_t seed = 0;
    seed ^= hash(val.summary) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    seed ^= hash(val.totalSize) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    return seed;
}
}
namespace taihe {
inline bool same_impl(adl_helper_t, ::ohos::data::unifiedDataChannel::Summary const& lhs, ::ohos::data::unifiedDataChannel::Summary const& rhs) {
    return true && same(lhs.summary, rhs.summary) && same(lhs.totalSize, rhs.totalSize);
}
}
namespace taihe {
template<>
struct as_abi<::ohos::data::unifiedDataChannel::Summary> {
    using type = struct ohos_data_unifiedDataChannel_Summary_t;
};
template<>
struct as_abi<::ohos::data::unifiedDataChannel::Summary const&> {
    using type = struct ohos_data_unifiedDataChannel_Summary_t const*;
};
template<>
struct as_param<::ohos::data::unifiedDataChannel::Summary> {
    using type = ::ohos::data::unifiedDataChannel::Summary const&;
};
}
