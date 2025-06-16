#pragma once
#include "taihe/common.h"
#include "ohos.data.unifiedDataChannel.GetDataParams.abi.0.h"
#include "taihe/callback.abi.h"
#include "taihe/optional.abi.h"
struct ohos_data_unifiedDataChannel_GetDataParams_t {
    int progressIndicator;
    struct TCallback dataProgressListener;
    struct TOptional destUri;
    struct TOptional fileConflictOptions;
};
