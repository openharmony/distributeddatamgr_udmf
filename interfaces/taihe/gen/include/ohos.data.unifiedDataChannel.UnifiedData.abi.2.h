#pragma once
#include "ohos.data.unifiedDataChannel.UnifiedData.abi.1.h"
#include "ohos.data.unifiedDataChannel.UnifiedRecord.abi.2.h"
#include "taihe/array.abi.h"
TH_INLINE void ohos_data_unifiedDataChannel_UnifiedData_AddRecord_f(struct ohos_data_unifiedDataChannel_UnifiedData_t tobj, struct ohos_data_unifiedDataChannel_UnifiedRecord_t unifiedRecord) {
    return tobj.vtbl_ptr->ftbl_ptr_0->AddRecord(tobj, unifiedRecord);
}
TH_INLINE struct TArray ohos_data_unifiedDataChannel_UnifiedData_GetRecords_f(struct ohos_data_unifiedDataChannel_UnifiedData_t tobj) {
    return tobj.vtbl_ptr->ftbl_ptr_0->GetRecords(tobj);
}
TH_INLINE int64_t ohos_data_unifiedDataChannel_UnifiedData_GetInner_f(struct ohos_data_unifiedDataChannel_UnifiedData_t tobj) {
    return tobj.vtbl_ptr->ftbl_ptr_0->GetInner(tobj);
}
