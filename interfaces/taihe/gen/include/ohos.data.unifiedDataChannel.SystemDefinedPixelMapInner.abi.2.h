#pragma once
#include "ohos.data.unifiedDataChannel.SystemDefinedPixelMapInner.abi.1.h"
#include "taihe/string.abi.h"
#include "ohos.data.unifiedDataChannel.ValueType.abi.1.h"
#include "taihe/optional.abi.h"
#include "taihe/array.abi.h"
TH_INLINE struct TString ohos_data_unifiedDataChannel_SystemDefinedPixelMapInner_GetType_f(struct ohos_data_unifiedDataChannel_SystemDefinedPixelMapInner_t tobj) {
    return tobj.vtbl_ptr->ftbl_ptr_0->GetType(tobj);
}
TH_INLINE struct ohos_data_unifiedDataChannel_ValueType_t ohos_data_unifiedDataChannel_SystemDefinedPixelMapInner_GetValue_f(struct ohos_data_unifiedDataChannel_SystemDefinedPixelMapInner_t tobj) {
    return tobj.vtbl_ptr->ftbl_ptr_0->GetValue(tobj);
}
TH_INLINE struct TOptional ohos_data_unifiedDataChannel_SystemDefinedPixelMapInner_GetDetails_f(struct ohos_data_unifiedDataChannel_SystemDefinedPixelMapInner_t tobj) {
    return tobj.vtbl_ptr->ftbl_ptr_0->GetDetails(tobj);
}
TH_INLINE void ohos_data_unifiedDataChannel_SystemDefinedPixelMapInner_SetDetails_f(struct ohos_data_unifiedDataChannel_SystemDefinedPixelMapInner_t tobj, void* details) {
    return tobj.vtbl_ptr->ftbl_ptr_0->SetDetails(tobj, details);
}
TH_INLINE struct TOptional ohos_data_unifiedDataChannel_SystemDefinedPixelMapInner_GetRawData_f(struct ohos_data_unifiedDataChannel_SystemDefinedPixelMapInner_t tobj) {
    return tobj.vtbl_ptr->ftbl_ptr_0->GetRawData(tobj);
}
TH_INLINE void ohos_data_unifiedDataChannel_SystemDefinedPixelMapInner_SetRawData_f(struct ohos_data_unifiedDataChannel_SystemDefinedPixelMapInner_t tobj, struct TArray rawData) {
    return tobj.vtbl_ptr->ftbl_ptr_0->SetRawData(tobj, rawData);
}
TH_INLINE int64_t ohos_data_unifiedDataChannel_SystemDefinedPixelMapInner_GetInner_f(struct ohos_data_unifiedDataChannel_SystemDefinedPixelMapInner_t tobj) {
    return tobj.vtbl_ptr->ftbl_ptr_0->GetInner(tobj);
}
