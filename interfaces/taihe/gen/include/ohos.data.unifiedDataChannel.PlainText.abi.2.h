#pragma once
#include "ohos.data.unifiedDataChannel.PlainText.abi.1.h"
#include "taihe/string.abi.h"
#include "ohos.data.unifiedDataChannel.ValueType.abi.1.h"
#include "taihe/optional.abi.h"
TH_INLINE struct TString ohos_data_unifiedDataChannel_PlainText_GetType_f(struct ohos_data_unifiedDataChannel_PlainText_t tobj) {
    return tobj.vtbl_ptr->ftbl_ptr_0->GetType(tobj);
}
TH_INLINE struct ohos_data_unifiedDataChannel_ValueType_t ohos_data_unifiedDataChannel_PlainText_GetValue_f(struct ohos_data_unifiedDataChannel_PlainText_t tobj) {
    return tobj.vtbl_ptr->ftbl_ptr_0->GetValue(tobj);
}
TH_INLINE struct TOptional ohos_data_unifiedDataChannel_PlainText_GetDetails_f(struct ohos_data_unifiedDataChannel_PlainText_t tobj) {
    return tobj.vtbl_ptr->ftbl_ptr_0->GetDetails(tobj);
}
TH_INLINE void ohos_data_unifiedDataChannel_PlainText_SetDetails_f(struct ohos_data_unifiedDataChannel_PlainText_t tobj, void* details) {
    return tobj.vtbl_ptr->ftbl_ptr_0->SetDetails(tobj, details);
}
TH_INLINE void ohos_data_unifiedDataChannel_PlainText_SetTextContent_f(struct ohos_data_unifiedDataChannel_PlainText_t tobj, struct TString textContent) {
    return tobj.vtbl_ptr->ftbl_ptr_0->SetTextContent(tobj, textContent);
}
TH_INLINE struct TString ohos_data_unifiedDataChannel_PlainText_GetTextContent_f(struct ohos_data_unifiedDataChannel_PlainText_t tobj) {
    return tobj.vtbl_ptr->ftbl_ptr_0->GetTextContent(tobj);
}
TH_INLINE void ohos_data_unifiedDataChannel_PlainText_SetAbstract1_f(struct ohos_data_unifiedDataChannel_PlainText_t tobj, struct TString abstract1) {
    return tobj.vtbl_ptr->ftbl_ptr_0->SetAbstract1(tobj, abstract1);
}
TH_INLINE struct TString ohos_data_unifiedDataChannel_PlainText_GetAbstract1_f(struct ohos_data_unifiedDataChannel_PlainText_t tobj) {
    return tobj.vtbl_ptr->ftbl_ptr_0->GetAbstract1(tobj);
}
TH_INLINE int64_t ohos_data_unifiedDataChannel_PlainText_GetInner_f(struct ohos_data_unifiedDataChannel_PlainText_t tobj) {
    return tobj.vtbl_ptr->ftbl_ptr_0->GetInner(tobj);
}
