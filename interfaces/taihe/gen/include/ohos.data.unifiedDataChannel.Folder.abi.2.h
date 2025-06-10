#pragma once
#include "ohos.data.unifiedDataChannel.Folder.abi.1.h"
#include "taihe/string.abi.h"
#include "ohos.data.unifiedDataChannel.ValueType.abi.1.h"
#include "taihe/optional.abi.h"
TH_INLINE struct TString ohos_data_unifiedDataChannel_Folder_GetType_f(struct ohos_data_unifiedDataChannel_Folder_t tobj) {
    return tobj.vtbl_ptr->ftbl_ptr_0->GetType(tobj);
}
TH_INLINE struct ohos_data_unifiedDataChannel_ValueType_t ohos_data_unifiedDataChannel_Folder_GetValue_f(struct ohos_data_unifiedDataChannel_Folder_t tobj) {
    return tobj.vtbl_ptr->ftbl_ptr_0->GetValue(tobj);
}
TH_INLINE struct TString ohos_data_unifiedDataChannel_Folder_GetUri_f(struct ohos_data_unifiedDataChannel_Folder_t tobj) {
    return tobj.vtbl_ptr->ftbl_ptr_0->GetUri(tobj);
}
TH_INLINE void ohos_data_unifiedDataChannel_Folder_SetUri_f(struct ohos_data_unifiedDataChannel_Folder_t tobj, struct TString uri) {
    return tobj.vtbl_ptr->ftbl_ptr_0->SetUri(tobj, uri);
}
TH_INLINE struct TOptional ohos_data_unifiedDataChannel_Folder_GetDetails_f(struct ohos_data_unifiedDataChannel_Folder_t tobj) {
    return tobj.vtbl_ptr->ftbl_ptr_0->GetDetails(tobj);
}
TH_INLINE void ohos_data_unifiedDataChannel_Folder_SetDetails_f(struct ohos_data_unifiedDataChannel_Folder_t tobj, void* details) {
    return tobj.vtbl_ptr->ftbl_ptr_0->SetDetails(tobj, details);
}
TH_INLINE struct TString ohos_data_unifiedDataChannel_Folder_GetFolderUri_f(struct ohos_data_unifiedDataChannel_Folder_t tobj) {
    return tobj.vtbl_ptr->ftbl_ptr_0->GetFolderUri(tobj);
}
TH_INLINE void ohos_data_unifiedDataChannel_Folder_SetFolderUri_f(struct ohos_data_unifiedDataChannel_Folder_t tobj, struct TString folderUri) {
    return tobj.vtbl_ptr->ftbl_ptr_0->SetFolderUri(tobj, folderUri);
}
TH_INLINE int64_t ohos_data_unifiedDataChannel_Folder_GetInner_f(struct ohos_data_unifiedDataChannel_Folder_t tobj) {
    return tobj.vtbl_ptr->ftbl_ptr_0->GetInner(tobj);
}
