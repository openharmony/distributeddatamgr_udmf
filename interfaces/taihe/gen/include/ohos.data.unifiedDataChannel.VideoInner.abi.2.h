#pragma once
#include "ohos.data.unifiedDataChannel.VideoInner.abi.1.h"
#include "taihe/string.abi.h"
#include "ohos.data.unifiedDataChannel.ValueType.abi.1.h"
#include "taihe/optional.abi.h"
TH_INLINE struct TString ohos_data_unifiedDataChannel_VideoInner_GetType_f(struct ohos_data_unifiedDataChannel_VideoInner_t tobj) {
    return tobj.vtbl_ptr->ftbl_ptr_0->GetType(tobj);
}
TH_INLINE struct ohos_data_unifiedDataChannel_ValueType_t ohos_data_unifiedDataChannel_VideoInner_GetValue_f(struct ohos_data_unifiedDataChannel_VideoInner_t tobj) {
    return tobj.vtbl_ptr->ftbl_ptr_0->GetValue(tobj);
}
TH_INLINE struct TString ohos_data_unifiedDataChannel_VideoInner_GetUri_f(struct ohos_data_unifiedDataChannel_VideoInner_t tobj) {
    return tobj.vtbl_ptr->ftbl_ptr_0->GetUri(tobj);
}
TH_INLINE void ohos_data_unifiedDataChannel_VideoInner_SetUri_f(struct ohos_data_unifiedDataChannel_VideoInner_t tobj, struct TString uri) {
    return tobj.vtbl_ptr->ftbl_ptr_0->SetUri(tobj, uri);
}
TH_INLINE struct TOptional ohos_data_unifiedDataChannel_VideoInner_GetDetails_f(struct ohos_data_unifiedDataChannel_VideoInner_t tobj) {
    return tobj.vtbl_ptr->ftbl_ptr_0->GetDetails(tobj);
}
TH_INLINE void ohos_data_unifiedDataChannel_VideoInner_SetDetails_f(struct ohos_data_unifiedDataChannel_VideoInner_t tobj, void* details) {
    return tobj.vtbl_ptr->ftbl_ptr_0->SetDetails(tobj, details);
}
TH_INLINE struct TString ohos_data_unifiedDataChannel_VideoInner_GetVideoUri_f(struct ohos_data_unifiedDataChannel_VideoInner_t tobj) {
    return tobj.vtbl_ptr->ftbl_ptr_0->GetVideoUri(tobj);
}
TH_INLINE void ohos_data_unifiedDataChannel_VideoInner_SetVideoUri_f(struct ohos_data_unifiedDataChannel_VideoInner_t tobj, struct TString videoUri) {
    return tobj.vtbl_ptr->ftbl_ptr_0->SetVideoUri(tobj, videoUri);
}
TH_INLINE int64_t ohos_data_unifiedDataChannel_VideoInner_GetInner_f(struct ohos_data_unifiedDataChannel_VideoInner_t tobj) {
    return tobj.vtbl_ptr->ftbl_ptr_0->GetInner(tobj);
}
