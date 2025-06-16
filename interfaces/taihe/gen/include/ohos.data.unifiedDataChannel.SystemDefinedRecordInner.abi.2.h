#pragma once
#include "ohos.data.unifiedDataChannel.SystemDefinedRecordInner.abi.1.h"
#include "taihe/string.abi.h"
#include "ohos.data.unifiedDataChannel.ValueType.abi.1.h"
#include "taihe/optional.abi.h"
TH_INLINE struct TString ohos_data_unifiedDataChannel_SystemDefinedRecordInner_GetType_f(struct ohos_data_unifiedDataChannel_SystemDefinedRecordInner_t tobj) {
    return tobj.vtbl_ptr->ftbl_ptr_0->GetType(tobj);
}
TH_INLINE struct ohos_data_unifiedDataChannel_ValueType_t ohos_data_unifiedDataChannel_SystemDefinedRecordInner_GetValue_f(struct ohos_data_unifiedDataChannel_SystemDefinedRecordInner_t tobj) {
    return tobj.vtbl_ptr->ftbl_ptr_0->GetValue(tobj);
}
TH_INLINE struct TOptional ohos_data_unifiedDataChannel_SystemDefinedRecordInner_GetDetails_f(struct ohos_data_unifiedDataChannel_SystemDefinedRecordInner_t tobj) {
    return tobj.vtbl_ptr->ftbl_ptr_0->GetDetails(tobj);
}
TH_INLINE void ohos_data_unifiedDataChannel_SystemDefinedRecordInner_SetDetails_f(struct ohos_data_unifiedDataChannel_SystemDefinedRecordInner_t tobj, void* details) {
    return tobj.vtbl_ptr->ftbl_ptr_0->SetDetails(tobj, details);
}
TH_INLINE int64_t ohos_data_unifiedDataChannel_SystemDefinedRecordInner_GetInner_f(struct ohos_data_unifiedDataChannel_SystemDefinedRecordInner_t tobj) {
    return tobj.vtbl_ptr->ftbl_ptr_0->GetInner(tobj);
}
