#pragma once
#include "ohos.data.unifiedDataChannel.AudioInner.abi.1.h"
#include "taihe/string.abi.h"
#include "ohos.data.unifiedDataChannel.ValueType.abi.1.h"
#include "taihe/optional.abi.h"
TH_INLINE struct TString ohos_data_unifiedDataChannel_AudioInner_GetType_f(struct ohos_data_unifiedDataChannel_AudioInner_t tobj) {
    return tobj.vtbl_ptr->ftbl_ptr_0->GetType(tobj);
}
TH_INLINE struct ohos_data_unifiedDataChannel_ValueType_t ohos_data_unifiedDataChannel_AudioInner_GetValue_f(struct ohos_data_unifiedDataChannel_AudioInner_t tobj) {
    return tobj.vtbl_ptr->ftbl_ptr_0->GetValue(tobj);
}
TH_INLINE struct TString ohos_data_unifiedDataChannel_AudioInner_GetUri_f(struct ohos_data_unifiedDataChannel_AudioInner_t tobj) {
    return tobj.vtbl_ptr->ftbl_ptr_0->GetUri(tobj);
}
TH_INLINE void ohos_data_unifiedDataChannel_AudioInner_SetUri_f(struct ohos_data_unifiedDataChannel_AudioInner_t tobj, struct TString uri) {
    return tobj.vtbl_ptr->ftbl_ptr_0->SetUri(tobj, uri);
}
TH_INLINE struct TOptional ohos_data_unifiedDataChannel_AudioInner_GetDetails_f(struct ohos_data_unifiedDataChannel_AudioInner_t tobj) {
    return tobj.vtbl_ptr->ftbl_ptr_0->GetDetails(tobj);
}
TH_INLINE void ohos_data_unifiedDataChannel_AudioInner_SetDetails_f(struct ohos_data_unifiedDataChannel_AudioInner_t tobj, void* details) {
    return tobj.vtbl_ptr->ftbl_ptr_0->SetDetails(tobj, details);
}
TH_INLINE struct TString ohos_data_unifiedDataChannel_AudioInner_GetAudioUri_f(struct ohos_data_unifiedDataChannel_AudioInner_t tobj) {
    return tobj.vtbl_ptr->ftbl_ptr_0->GetAudioUri(tobj);
}
TH_INLINE void ohos_data_unifiedDataChannel_AudioInner_SetAudioUri_f(struct ohos_data_unifiedDataChannel_AudioInner_t tobj, struct TString audioUri) {
    return tobj.vtbl_ptr->ftbl_ptr_0->SetAudioUri(tobj, audioUri);
}
TH_INLINE int64_t ohos_data_unifiedDataChannel_AudioInner_GetInner_f(struct ohos_data_unifiedDataChannel_AudioInner_t tobj) {
    return tobj.vtbl_ptr->ftbl_ptr_0->GetInner(tobj);
}
