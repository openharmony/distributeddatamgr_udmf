#pragma once
#include "ohos.data.unifiedDataChannel.SystemDefinedAppItemInner.abi.1.h"
#include "taihe/string.abi.h"
#include "ohos.data.unifiedDataChannel.ValueType.abi.1.h"
#include "taihe/optional.abi.h"
TH_INLINE struct TString ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_GetType_f(struct ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_t tobj) {
    return tobj.vtbl_ptr->ftbl_ptr_0->GetType(tobj);
}
TH_INLINE struct ohos_data_unifiedDataChannel_ValueType_t ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_GetValue_f(struct ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_t tobj) {
    return tobj.vtbl_ptr->ftbl_ptr_0->GetValue(tobj);
}
TH_INLINE struct TOptional ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_GetDetails_f(struct ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_t tobj) {
    return tobj.vtbl_ptr->ftbl_ptr_0->GetDetails(tobj);
}
TH_INLINE void ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_SetDetails_f(struct ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_t tobj, void* details) {
    return tobj.vtbl_ptr->ftbl_ptr_0->SetDetails(tobj, details);
}
TH_INLINE struct TString ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_GetAppId_f(struct ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_t tobj) {
    return tobj.vtbl_ptr->ftbl_ptr_0->GetAppId(tobj);
}
TH_INLINE void ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_SetAppId_f(struct ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_t tobj, struct TString appId) {
    return tobj.vtbl_ptr->ftbl_ptr_0->SetAppId(tobj, appId);
}
TH_INLINE struct TString ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_GetAppName_f(struct ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_t tobj) {
    return tobj.vtbl_ptr->ftbl_ptr_0->GetAppName(tobj);
}
TH_INLINE void ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_SetAppName_f(struct ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_t tobj, struct TString appName) {
    return tobj.vtbl_ptr->ftbl_ptr_0->SetAppName(tobj, appName);
}
TH_INLINE struct TString ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_GetAppIconId_f(struct ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_t tobj) {
    return tobj.vtbl_ptr->ftbl_ptr_0->GetAppIconId(tobj);
}
TH_INLINE void ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_SetAppIconId_f(struct ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_t tobj, struct TString appIconId) {
    return tobj.vtbl_ptr->ftbl_ptr_0->SetAppIconId(tobj, appIconId);
}
TH_INLINE struct TString ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_GetAppLabelId_f(struct ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_t tobj) {
    return tobj.vtbl_ptr->ftbl_ptr_0->GetAppLabelId(tobj);
}
TH_INLINE void ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_SetAppLabelId_f(struct ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_t tobj, struct TString appLabelId) {
    return tobj.vtbl_ptr->ftbl_ptr_0->SetAppLabelId(tobj, appLabelId);
}
TH_INLINE struct TString ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_GetBundleName_f(struct ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_t tobj) {
    return tobj.vtbl_ptr->ftbl_ptr_0->GetBundleName(tobj);
}
TH_INLINE void ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_SetBundleName_f(struct ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_t tobj, struct TString bundleName) {
    return tobj.vtbl_ptr->ftbl_ptr_0->SetBundleName(tobj, bundleName);
}
TH_INLINE struct TString ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_GetAbilityName_f(struct ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_t tobj) {
    return tobj.vtbl_ptr->ftbl_ptr_0->GetAbilityName(tobj);
}
TH_INLINE void ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_SetAbilityName_f(struct ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_t tobj, struct TString abilityName) {
    return tobj.vtbl_ptr->ftbl_ptr_0->SetAbilityName(tobj, abilityName);
}
TH_INLINE int64_t ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_GetInner_f(struct ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_t tobj) {
    return tobj.vtbl_ptr->ftbl_ptr_0->GetInner(tobj);
}
