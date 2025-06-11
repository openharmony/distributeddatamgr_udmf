#pragma once
#include "taihe/common.h"
#include "ohos.data.unifiedDataChannel.AllRecords.abi.0.h"
#include "ohos.data.unifiedDataChannel.FileInner.abi.2.h"
#include "ohos.data.unifiedDataChannel.UnifiedRecordInner.abi.2.h"
union ohos_data_unifiedDataChannel_AllRecords_union {
    struct ohos_data_unifiedDataChannel_FileInner_t file;
    struct ohos_data_unifiedDataChannel_UnifiedRecordInner_t unifiedRecord;
};
struct ohos_data_unifiedDataChannel_AllRecords_t {
    int m_tag;
    union ohos_data_unifiedDataChannel_AllRecords_union m_data;
};
