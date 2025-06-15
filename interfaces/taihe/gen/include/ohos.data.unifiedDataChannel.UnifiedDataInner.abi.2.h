#pragma once
#include "ohos.data.unifiedDataChannel.UnifiedDataInner.abi.1.h"
#include "ohos.data.unifiedDataChannel.AllRecords.abi.1.h"
#include "taihe/array.abi.h"
TH_INLINE void ohos_data_unifiedDataChannel_UnifiedDataInner_AddRecord_f(struct ohos_data_unifiedDataChannel_UnifiedDataInner_t tobj, struct ohos_data_unifiedDataChannel_AllRecords_t const* unifiedRecord) {
    return tobj.vtbl_ptr->ftbl_ptr_0->AddRecord(tobj, unifiedRecord);
}
TH_INLINE struct TArray ohos_data_unifiedDataChannel_UnifiedDataInner_GetRecords_f(struct ohos_data_unifiedDataChannel_UnifiedDataInner_t tobj) {
    return tobj.vtbl_ptr->ftbl_ptr_0->GetRecords(tobj);
}
TH_INLINE int64_t ohos_data_unifiedDataChannel_UnifiedDataInner_GetInner_f(struct ohos_data_unifiedDataChannel_UnifiedDataInner_t tobj) {
    return tobj.vtbl_ptr->ftbl_ptr_0->GetInner(tobj);
}
