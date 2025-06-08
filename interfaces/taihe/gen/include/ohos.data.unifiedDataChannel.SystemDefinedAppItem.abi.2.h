#pragma once
#include "ohos.data.unifiedDataChannel.SystemDefinedAppItem.abi.1.h"
#include "taihe/string.abi.h"
#include "ohos.data.unifiedDataChannel.ValueType.abi.1.h"
#include "taihe/optional.abi.h"
TH_INLINE struct TString ohos_data_unifiedDataChannel_SystemDefinedAppItem_GetType_f(struct ohos_data_unifiedDataChannel_SystemDefinedAppItem_t tobj) {
    return tobj.vtbl_ptr->ftbl_ptr_0->GetType(tobj);
}
TH_INLINE struct ohos_data_unifiedDataChannel_ValueType_t ohos_data_unifiedDataChannel_SystemDefinedAppItem_GetValue_f(struct ohos_data_unifiedDataChannel_SystemDefinedAppItem_t tobj) {
    return tobj.vtbl_ptr->ftbl_ptr_0->GetValue(tobj);
}
TH_INLINE struct TOptional ohos_data_unifiedDataChannel_SystemDefinedAppItem_GetDetails_f(struct ohos_data_unifiedDataChannel_SystemDefinedAppItem_t tobj) {
    return tobj.vtbl_ptr->ftbl_ptr_0->GetDetails(tobj);
}
TH_INLINE void ohos_data_unifiedDataChannel_SystemDefinedAppItem_SetDetails_f(struct ohos_data_unifiedDataChannel_SystemDefinedAppItem_t tobj, void* details) {
    return tobj.vtbl_ptr->ftbl_ptr_0->SetDetails(tobj, details);
}
TH_INLINE struct TString ohos_data_unifiedDataChannel_SystemDefinedAppItem_GetAppId_f(struct ohos_data_unifiedDataChannel_SystemDefinedAppItem_t tobj) {
    return tobj.vtbl_ptr->ftbl_ptr_0->GetAppId(tobj);
}
TH_INLINE void ohos_data_unifiedDataChannel_SystemDefinedAppItem_SetAppId_f(struct ohos_data_unifiedDataChannel_SystemDefinedAppItem_t tobj, struct TString appId) {
    return tobj.vtbl_ptr->ftbl_ptr_0->SetAppId(tobj, appId);
}
TH_INLINE struct TString ohos_data_unifiedDataChannel_SystemDefinedAppItem_GetAppName_f(struct ohos_data_unifiedDataChannel_SystemDefinedAppItem_t tobj) {
    return tobj.vtbl_ptr->ftbl_ptr_0->GetAppName(tobj);
}
TH_INLINE void ohos_data_unifiedDataChannel_SystemDefinedAppItem_SetAppName_f(struct ohos_data_unifiedDataChannel_SystemDefinedAppItem_t tobj, struct TString appName) {
    return tobj.vtbl_ptr->ftbl_ptr_0->SetAppName(tobj, appName);
}
TH_INLINE struct TString ohos_data_unifiedDataChannel_SystemDefinedAppItem_GetAppIconId_f(struct ohos_data_unifiedDataChannel_SystemDefinedAppItem_t tobj) {
    return tobj.vtbl_ptr->ftbl_ptr_0->GetAppIconId(tobj);
}
TH_INLINE void ohos_data_unifiedDataChannel_SystemDefinedAppItem_SetAppIconId_f(struct ohos_data_unifiedDataChannel_SystemDefinedAppItem_t tobj, struct TString appIconId) {
    return tobj.vtbl_ptr->ftbl_ptr_0->SetAppIconId(tobj, appIconId);
}
TH_INLINE struct TString ohos_data_unifiedDataChannel_SystemDefinedAppItem_GetAppLabelId_f(struct ohos_data_unifiedDataChannel_SystemDefinedAppItem_t tobj) {
    return tobj.vtbl_ptr->ftbl_ptr_0->GetAppLabelId(tobj);
}
TH_INLINE void ohos_data_unifiedDataChannel_SystemDefinedAppItem_SetAppLabelId_f(struct ohos_data_unifiedDataChannel_SystemDefinedAppItem_t tobj, struct TString appLabelId) {
    return tobj.vtbl_ptr->ftbl_ptr_0->SetAppLabelId(tobj, appLabelId);
}
TH_INLINE struct TString ohos_data_unifiedDataChannel_SystemDefinedAppItem_GetBundleName_f(struct ohos_data_unifiedDataChannel_SystemDefinedAppItem_t tobj) {
    return tobj.vtbl_ptr->ftbl_ptr_0->GetBundleName(tobj);
}
TH_INLINE void ohos_data_unifiedDataChannel_SystemDefinedAppItem_SetBundleName_f(struct ohos_data_unifiedDataChannel_SystemDefinedAppItem_t tobj, struct TString bundleName) {
    return tobj.vtbl_ptr->ftbl_ptr_0->SetBundleName(tobj, bundleName);
}
TH_INLINE struct TString ohos_data_unifiedDataChannel_SystemDefinedAppItem_GetAbilityName_f(struct ohos_data_unifiedDataChannel_SystemDefinedAppItem_t tobj) {
    return tobj.vtbl_ptr->ftbl_ptr_0->GetAbilityName(tobj);
}
TH_INLINE void ohos_data_unifiedDataChannel_SystemDefinedAppItem_SetAbilityName_f(struct ohos_data_unifiedDataChannel_SystemDefinedAppItem_t tobj, struct TString abilityName) {
    return tobj.vtbl_ptr->ftbl_ptr_0->SetAbilityName(tobj, abilityName);
}
TH_INLINE int64_t ohos_data_unifiedDataChannel_SystemDefinedAppItem_GetInner_f(struct ohos_data_unifiedDataChannel_SystemDefinedAppItem_t tobj) {
    return tobj.vtbl_ptr->ftbl_ptr_0->GetInner(tobj);
}
