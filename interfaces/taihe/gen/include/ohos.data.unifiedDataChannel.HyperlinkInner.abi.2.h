#pragma once
#include "ohos.data.unifiedDataChannel.HyperlinkInner.abi.1.h"
#include "taihe/string.abi.h"
#include "ohos.data.unifiedDataChannel.ValueType.abi.1.h"
#include "taihe/optional.abi.h"
TH_INLINE struct TString ohos_data_unifiedDataChannel_HyperlinkInner_GetType_f(struct ohos_data_unifiedDataChannel_HyperlinkInner_t tobj) {
    return tobj.vtbl_ptr->ftbl_ptr_0->GetType(tobj);
}
TH_INLINE struct ohos_data_unifiedDataChannel_ValueType_t ohos_data_unifiedDataChannel_HyperlinkInner_GetValue_f(struct ohos_data_unifiedDataChannel_HyperlinkInner_t tobj) {
    return tobj.vtbl_ptr->ftbl_ptr_0->GetValue(tobj);
}
TH_INLINE struct TOptional ohos_data_unifiedDataChannel_HyperlinkInner_GetDetails_f(struct ohos_data_unifiedDataChannel_HyperlinkInner_t tobj) {
    return tobj.vtbl_ptr->ftbl_ptr_0->GetDetails(tobj);
}
TH_INLINE void ohos_data_unifiedDataChannel_HyperlinkInner_SetDetails_f(struct ohos_data_unifiedDataChannel_HyperlinkInner_t tobj, void* details) {
    return tobj.vtbl_ptr->ftbl_ptr_0->SetDetails(tobj, details);
}
TH_INLINE void ohos_data_unifiedDataChannel_HyperlinkInner_SetUrl_f(struct ohos_data_unifiedDataChannel_HyperlinkInner_t tobj, struct TString url) {
    return tobj.vtbl_ptr->ftbl_ptr_0->SetUrl(tobj, url);
}
TH_INLINE struct TString ohos_data_unifiedDataChannel_HyperlinkInner_GetUrl_f(struct ohos_data_unifiedDataChannel_HyperlinkInner_t tobj) {
    return tobj.vtbl_ptr->ftbl_ptr_0->GetUrl(tobj);
}
TH_INLINE void ohos_data_unifiedDataChannel_HyperlinkInner_SetDescription_f(struct ohos_data_unifiedDataChannel_HyperlinkInner_t tobj, struct TString description) {
    return tobj.vtbl_ptr->ftbl_ptr_0->SetDescription(tobj, description);
}
TH_INLINE struct TString ohos_data_unifiedDataChannel_HyperlinkInner_GetDescription_f(struct ohos_data_unifiedDataChannel_HyperlinkInner_t tobj) {
    return tobj.vtbl_ptr->ftbl_ptr_0->GetDescription(tobj);
}
TH_INLINE int64_t ohos_data_unifiedDataChannel_HyperlinkInner_GetInner_f(struct ohos_data_unifiedDataChannel_HyperlinkInner_t tobj) {
    return tobj.vtbl_ptr->ftbl_ptr_0->GetInner(tobj);
}
