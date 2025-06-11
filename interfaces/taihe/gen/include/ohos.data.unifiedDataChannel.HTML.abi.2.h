#pragma once
#include "ohos.data.unifiedDataChannel.HTML.abi.1.h"
#include "taihe/string.abi.h"
#include "ohos.data.unifiedDataChannel.ValueType.abi.1.h"
#include "taihe/optional.abi.h"
TH_INLINE struct TString ohos_data_unifiedDataChannel_HTML_GetType_f(struct ohos_data_unifiedDataChannel_HTML_t tobj) {
    return tobj.vtbl_ptr->ftbl_ptr_0->GetType(tobj);
}
TH_INLINE struct ohos_data_unifiedDataChannel_ValueType_t ohos_data_unifiedDataChannel_HTML_GetValue_f(struct ohos_data_unifiedDataChannel_HTML_t tobj) {
    return tobj.vtbl_ptr->ftbl_ptr_0->GetValue(tobj);
}
TH_INLINE struct TOptional ohos_data_unifiedDataChannel_HTML_GetDetails_f(struct ohos_data_unifiedDataChannel_HTML_t tobj) {
    return tobj.vtbl_ptr->ftbl_ptr_0->GetDetails(tobj);
}
TH_INLINE void ohos_data_unifiedDataChannel_HTML_SetDetails_f(struct ohos_data_unifiedDataChannel_HTML_t tobj, void* details) {
    return tobj.vtbl_ptr->ftbl_ptr_0->SetDetails(tobj, details);
}
TH_INLINE void ohos_data_unifiedDataChannel_HTML_SetHtmlContent_f(struct ohos_data_unifiedDataChannel_HTML_t tobj, struct TString htmlContent) {
    return tobj.vtbl_ptr->ftbl_ptr_0->SetHtmlContent(tobj, htmlContent);
}
TH_INLINE struct TString ohos_data_unifiedDataChannel_HTML_GetHtmlContent_f(struct ohos_data_unifiedDataChannel_HTML_t tobj) {
    return tobj.vtbl_ptr->ftbl_ptr_0->GetHtmlContent(tobj);
}
TH_INLINE void ohos_data_unifiedDataChannel_HTML_SetPlainContent_f(struct ohos_data_unifiedDataChannel_HTML_t tobj, struct TString plainContent) {
    return tobj.vtbl_ptr->ftbl_ptr_0->SetPlainContent(tobj, plainContent);
}
TH_INLINE struct TString ohos_data_unifiedDataChannel_HTML_GetPlainContent_f(struct ohos_data_unifiedDataChannel_HTML_t tobj) {
    return tobj.vtbl_ptr->ftbl_ptr_0->GetPlainContent(tobj);
}
TH_INLINE int64_t ohos_data_unifiedDataChannel_HTML_GetInner_f(struct ohos_data_unifiedDataChannel_HTML_t tobj) {
    return tobj.vtbl_ptr->ftbl_ptr_0->GetInner(tobj);
}
