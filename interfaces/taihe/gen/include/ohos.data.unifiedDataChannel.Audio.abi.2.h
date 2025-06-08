#pragma once
#include "ohos.data.unifiedDataChannel.Audio.abi.1.h"
#include "taihe/string.abi.h"
#include "ohos.data.unifiedDataChannel.ValueType.abi.1.h"
#include "taihe/optional.abi.h"
TH_INLINE struct TString ohos_data_unifiedDataChannel_Audio_GetType_f(struct ohos_data_unifiedDataChannel_Audio_t tobj) {
    return tobj.vtbl_ptr->ftbl_ptr_0->GetType(tobj);
}
TH_INLINE struct ohos_data_unifiedDataChannel_ValueType_t ohos_data_unifiedDataChannel_Audio_GetValue_f(struct ohos_data_unifiedDataChannel_Audio_t tobj) {
    return tobj.vtbl_ptr->ftbl_ptr_0->GetValue(tobj);
}
TH_INLINE struct TString ohos_data_unifiedDataChannel_Audio_GetUri_f(struct ohos_data_unifiedDataChannel_Audio_t tobj) {
    return tobj.vtbl_ptr->ftbl_ptr_0->GetUri(tobj);
}
TH_INLINE void ohos_data_unifiedDataChannel_Audio_SetUri_f(struct ohos_data_unifiedDataChannel_Audio_t tobj, struct TString uri) {
    return tobj.vtbl_ptr->ftbl_ptr_0->SetUri(tobj, uri);
}
TH_INLINE struct TOptional ohos_data_unifiedDataChannel_Audio_GetDetails_f(struct ohos_data_unifiedDataChannel_Audio_t tobj) {
    return tobj.vtbl_ptr->ftbl_ptr_0->GetDetails(tobj);
}
TH_INLINE void ohos_data_unifiedDataChannel_Audio_SetDetails_f(struct ohos_data_unifiedDataChannel_Audio_t tobj, void* details) {
    return tobj.vtbl_ptr->ftbl_ptr_0->SetDetails(tobj, details);
}
TH_INLINE struct TString ohos_data_unifiedDataChannel_Audio_GetAudioUri_f(struct ohos_data_unifiedDataChannel_Audio_t tobj) {
    return tobj.vtbl_ptr->ftbl_ptr_0->GetAudioUri(tobj);
}
TH_INLINE void ohos_data_unifiedDataChannel_Audio_SetAudioUri_f(struct ohos_data_unifiedDataChannel_Audio_t tobj, struct TString audioUri) {
    return tobj.vtbl_ptr->ftbl_ptr_0->SetAudioUri(tobj, audioUri);
}
TH_INLINE int64_t ohos_data_unifiedDataChannel_Audio_GetInner_f(struct ohos_data_unifiedDataChannel_Audio_t tobj) {
    return tobj.vtbl_ptr->ftbl_ptr_0->GetInner(tobj);
}
