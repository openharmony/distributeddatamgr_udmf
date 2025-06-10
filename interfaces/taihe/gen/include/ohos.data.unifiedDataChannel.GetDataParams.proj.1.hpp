#pragma once
#include "taihe/common.hpp"
#include "ohos.data.unifiedDataChannel.GetDataParams.proj.0.hpp"
#include "ohos.data.unifiedDataChannel.GetDataParams.abi.1.h"
#include "ohos.data.unifiedDataChannel.ProgressIndicator.proj.0.hpp"
#include "taihe/callback.hpp"
#include "ohos.data.unifiedDataChannel.ProgressInfo.proj.1.hpp"
#include "ohos.data.unifiedDataChannel.UnifiedDataOrNull.proj.1.hpp"
#include "taihe/optional.hpp"
#include "taihe/string.hpp"
#include "ohos.data.unifiedDataChannel.FileConflictOptions.proj.0.hpp"
namespace ohos::data::unifiedDataChannel {
struct GetDataParams {
    ::ohos::data::unifiedDataChannel::ProgressIndicator progressIndicator;
    ::taihe::callback<void(::ohos::data::unifiedDataChannel::ProgressInfo const&, ::ohos::data::unifiedDataChannel::UnifiedDataOrNull const&)> dataProgressListener;
    ::taihe::optional<::taihe::string> destUri;
    ::taihe::optional<::ohos::data::unifiedDataChannel::FileConflictOptions> fileConflictOptions;
};
}
namespace taihe {
inline auto hash_impl(adl_helper_t, ::ohos::data::unifiedDataChannel::GetDataParams const& val) -> ::std::size_t {
    ::std::size_t seed = 0;
    seed ^= hash(val.progressIndicator) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    seed ^= hash(val.dataProgressListener) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    seed ^= hash(val.destUri) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    seed ^= hash(val.fileConflictOptions) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    return seed;
}
}
namespace taihe {
inline bool same_impl(adl_helper_t, ::ohos::data::unifiedDataChannel::GetDataParams const& lhs, ::ohos::data::unifiedDataChannel::GetDataParams const& rhs) {
    return true && same(lhs.progressIndicator, rhs.progressIndicator) && same(lhs.dataProgressListener, rhs.dataProgressListener) && same(lhs.destUri, rhs.destUri) && same(lhs.fileConflictOptions, rhs.fileConflictOptions);
}
}
namespace taihe {
template<>
struct as_abi<::ohos::data::unifiedDataChannel::GetDataParams> {
    using type = struct ohos_data_unifiedDataChannel_GetDataParams_t;
};
template<>
struct as_abi<::ohos::data::unifiedDataChannel::GetDataParams const&> {
    using type = struct ohos_data_unifiedDataChannel_GetDataParams_t const*;
};
template<>
struct as_param<::ohos::data::unifiedDataChannel::GetDataParams> {
    using type = ::ohos::data::unifiedDataChannel::GetDataParams const&;
};
}
