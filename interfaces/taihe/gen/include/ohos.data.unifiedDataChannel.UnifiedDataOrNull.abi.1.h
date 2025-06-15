#pragma once
#include "taihe/common.h"
#include "ohos.data.unifiedDataChannel.UnifiedDataOrNull.abi.0.h"
#include "ohos.data.unifiedDataChannel.UnifiedDataInner.abi.2.h"
union ohos_data_unifiedDataChannel_UnifiedDataOrNull_union {
    struct ohos_data_unifiedDataChannel_UnifiedDataInner_t unifiedData;
    // nullType
};
struct ohos_data_unifiedDataChannel_UnifiedDataOrNull_t {
    int m_tag;
    union ohos_data_unifiedDataChannel_UnifiedDataOrNull_union m_data;
};
