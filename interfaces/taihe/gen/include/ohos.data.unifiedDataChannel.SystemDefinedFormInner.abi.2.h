#pragma once
#include "ohos.data.unifiedDataChannel.SystemDefinedFormInner.abi.1.h"
#include "taihe/string.abi.h"
#include "ohos.data.unifiedDataChannel.ValueType.abi.1.h"
#include "taihe/optional.abi.h"
TH_INLINE struct TString ohos_data_unifiedDataChannel_SystemDefinedFormInner_GetType_f(struct ohos_data_unifiedDataChannel_SystemDefinedFormInner_t tobj) {
    return tobj.vtbl_ptr->ftbl_ptr_0->GetType(tobj);
}
TH_INLINE struct ohos_data_unifiedDataChannel_ValueType_t ohos_data_unifiedDataChannel_SystemDefinedFormInner_GetValue_f(struct ohos_data_unifiedDataChannel_SystemDefinedFormInner_t tobj) {
    return tobj.vtbl_ptr->ftbl_ptr_0->GetValue(tobj);
}
TH_INLINE struct TOptional ohos_data_unifiedDataChannel_SystemDefinedFormInner_GetDetails_f(struct ohos_data_unifiedDataChannel_SystemDefinedFormInner_t tobj) {
    return tobj.vtbl_ptr->ftbl_ptr_0->GetDetails(tobj);
}
TH_INLINE void ohos_data_unifiedDataChannel_SystemDefinedFormInner_SetDetails_f(struct ohos_data_unifiedDataChannel_SystemDefinedFormInner_t tobj, void* details) {
    return tobj.vtbl_ptr->ftbl_ptr_0->SetDetails(tobj, details);
}
TH_INLINE double ohos_data_unifiedDataChannel_SystemDefinedFormInner_GetFormId_f(struct ohos_data_unifiedDataChannel_SystemDefinedFormInner_t tobj) {
    return tobj.vtbl_ptr->ftbl_ptr_0->GetFormId(tobj);
}
TH_INLINE void ohos_data_unifiedDataChannel_SystemDefinedFormInner_SetFormId_f(struct ohos_data_unifiedDataChannel_SystemDefinedFormInner_t tobj, double formId) {
    return tobj.vtbl_ptr->ftbl_ptr_0->SetFormId(tobj, formId);
}
TH_INLINE struct TString ohos_data_unifiedDataChannel_SystemDefinedFormInner_GetFormName_f(struct ohos_data_unifiedDataChannel_SystemDefinedFormInner_t tobj) {
    return tobj.vtbl_ptr->ftbl_ptr_0->GetFormName(tobj);
}
TH_INLINE void ohos_data_unifiedDataChannel_SystemDefinedFormInner_SetFormName_f(struct ohos_data_unifiedDataChannel_SystemDefinedFormInner_t tobj, struct TString formName) {
    return tobj.vtbl_ptr->ftbl_ptr_0->SetFormName(tobj, formName);
}
TH_INLINE struct TString ohos_data_unifiedDataChannel_SystemDefinedFormInner_GetBundleName_f(struct ohos_data_unifiedDataChannel_SystemDefinedFormInner_t tobj) {
    return tobj.vtbl_ptr->ftbl_ptr_0->GetBundleName(tobj);
}
TH_INLINE void ohos_data_unifiedDataChannel_SystemDefinedFormInner_SetBundleName_f(struct ohos_data_unifiedDataChannel_SystemDefinedFormInner_t tobj, struct TString bundleName) {
    return tobj.vtbl_ptr->ftbl_ptr_0->SetBundleName(tobj, bundleName);
}
TH_INLINE struct TString ohos_data_unifiedDataChannel_SystemDefinedFormInner_GetAbilityName_f(struct ohos_data_unifiedDataChannel_SystemDefinedFormInner_t tobj) {
    return tobj.vtbl_ptr->ftbl_ptr_0->GetAbilityName(tobj);
}
TH_INLINE void ohos_data_unifiedDataChannel_SystemDefinedFormInner_SetAbilityName_f(struct ohos_data_unifiedDataChannel_SystemDefinedFormInner_t tobj, struct TString abilityName) {
    return tobj.vtbl_ptr->ftbl_ptr_0->SetAbilityName(tobj, abilityName);
}
TH_INLINE struct TString ohos_data_unifiedDataChannel_SystemDefinedFormInner_GetModule_f(struct ohos_data_unifiedDataChannel_SystemDefinedFormInner_t tobj) {
    return tobj.vtbl_ptr->ftbl_ptr_0->GetModule(tobj);
}
TH_INLINE void ohos_data_unifiedDataChannel_SystemDefinedFormInner_SetModule_f(struct ohos_data_unifiedDataChannel_SystemDefinedFormInner_t tobj, struct TString module) {
    return tobj.vtbl_ptr->ftbl_ptr_0->SetModule(tobj, module);
}
TH_INLINE int64_t ohos_data_unifiedDataChannel_SystemDefinedFormInner_GetInner_f(struct ohos_data_unifiedDataChannel_SystemDefinedFormInner_t tobj) {
    return tobj.vtbl_ptr->ftbl_ptr_0->GetInner(tobj);
}
