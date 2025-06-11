#pragma once
#include "taihe/common.h"
#include "ohos.data.unifiedDataChannel.DetailsValue.abi.0.h"
#include "taihe/string.abi.h"
#include "taihe/array.abi.h"
union ohos_data_unifiedDataChannel_DetailsValue_union {
    double number;
    struct TString string;
    struct TArray Uint8Array;
};
struct ohos_data_unifiedDataChannel_DetailsValue_t {
    int m_tag;
    union ohos_data_unifiedDataChannel_DetailsValue_union m_data;
};
