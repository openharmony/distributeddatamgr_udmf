#pragma once
#include "taihe/common.h"
#include "ohos.data.unifiedDataChannel.ValueType.abi.0.h"
#include "taihe/string.abi.h"
#include "taihe/array.abi.h"
union ohos_data_unifiedDataChannel_ValueType_union {
    double number;
    struct TString string;
    bool boolean;
    struct TArray ArrayBuffer;
    // nullType
    // undefinedType
    uintptr_t object;
};
struct ohos_data_unifiedDataChannel_ValueType_t {
    int m_tag;
    union ohos_data_unifiedDataChannel_ValueType_union m_data;
};
