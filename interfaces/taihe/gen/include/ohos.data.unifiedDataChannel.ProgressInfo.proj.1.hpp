#pragma once
#include "taihe/common.hpp"
#include "ohos.data.unifiedDataChannel.ProgressInfo.proj.0.hpp"
#include "ohos.data.unifiedDataChannel.ProgressInfo.abi.1.h"
#include "ohos.data.unifiedDataChannel.ListenerStatus.proj.0.hpp"
namespace ohos::data::unifiedDataChannel {
struct ProgressInfo {
    double progress;
    ::ohos::data::unifiedDataChannel::ListenerStatus status;
};
}
namespace taihe {
inline auto hash_impl(adl_helper_t, ::ohos::data::unifiedDataChannel::ProgressInfo const& val) -> ::std::size_t {
    ::std::size_t seed = 0;
    seed ^= hash(val.progress) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    seed ^= hash(val.status) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    return seed;
}
}
namespace taihe {
inline bool same_impl(adl_helper_t, ::ohos::data::unifiedDataChannel::ProgressInfo const& lhs, ::ohos::data::unifiedDataChannel::ProgressInfo const& rhs) {
    return true && same(lhs.progress, rhs.progress) && same(lhs.status, rhs.status);
}
}
namespace taihe {
template<>
struct as_abi<::ohos::data::unifiedDataChannel::ProgressInfo> {
    using type = struct ohos_data_unifiedDataChannel_ProgressInfo_t;
};
template<>
struct as_abi<::ohos::data::unifiedDataChannel::ProgressInfo const&> {
    using type = struct ohos_data_unifiedDataChannel_ProgressInfo_t const*;
};
template<>
struct as_param<::ohos::data::unifiedDataChannel::ProgressInfo> {
    using type = ::ohos::data::unifiedDataChannel::ProgressInfo const&;
};
}
