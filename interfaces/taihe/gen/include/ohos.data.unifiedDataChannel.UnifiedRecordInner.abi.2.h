#pragma once
#include "ohos.data.unifiedDataChannel.UnifiedRecordInner.abi.1.h"
#include "taihe/string.abi.h"
#include "ohos.data.unifiedDataChannel.ValueType.abi.1.h"
TH_INLINE struct TString ohos_data_unifiedDataChannel_UnifiedRecordInner_GetType_f(struct ohos_data_unifiedDataChannel_UnifiedRecordInner_t tobj) {
    return tobj.vtbl_ptr->ftbl_ptr_0->GetType(tobj);
}
TH_INLINE struct ohos_data_unifiedDataChannel_ValueType_t ohos_data_unifiedDataChannel_UnifiedRecordInner_GetValue_f(struct ohos_data_unifiedDataChannel_UnifiedRecordInner_t tobj) {
    return tobj.vtbl_ptr->ftbl_ptr_0->GetValue(tobj);
}
TH_INLINE int64_t ohos_data_unifiedDataChannel_UnifiedRecordInner_GetInner_f(struct ohos_data_unifiedDataChannel_UnifiedRecordInner_t tobj) {
    return tobj.vtbl_ptr->ftbl_ptr_0->GetInner(tobj);
}
