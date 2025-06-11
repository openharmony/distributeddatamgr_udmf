#pragma once
#include "taihe/object.abi.h"
#include "ohos.data.unifiedDataChannel.SystemDefinedAppItem.abi.0.h"
#include "taihe/string.abi.h"
#include "ohos.data.unifiedDataChannel.ValueType.abi.0.h"
#include "taihe/optional.abi.h"
TH_EXPORT void const* const ohos_data_unifiedDataChannel_SystemDefinedAppItem_i;
struct ohos_data_unifiedDataChannel_SystemDefinedAppItem_ftable {
    struct TString (*GetType)(struct ohos_data_unifiedDataChannel_SystemDefinedAppItem_t tobj);
    struct ohos_data_unifiedDataChannel_ValueType_t (*GetValue)(struct ohos_data_unifiedDataChannel_SystemDefinedAppItem_t tobj);
    struct TOptional (*GetDetails)(struct ohos_data_unifiedDataChannel_SystemDefinedAppItem_t tobj);
    void (*SetDetails)(struct ohos_data_unifiedDataChannel_SystemDefinedAppItem_t tobj, void* details);
    struct TString (*GetAppId)(struct ohos_data_unifiedDataChannel_SystemDefinedAppItem_t tobj);
    void (*SetAppId)(struct ohos_data_unifiedDataChannel_SystemDefinedAppItem_t tobj, struct TString appId);
    struct TString (*GetAppName)(struct ohos_data_unifiedDataChannel_SystemDefinedAppItem_t tobj);
    void (*SetAppName)(struct ohos_data_unifiedDataChannel_SystemDefinedAppItem_t tobj, struct TString appName);
    struct TString (*GetAppIconId)(struct ohos_data_unifiedDataChannel_SystemDefinedAppItem_t tobj);
    void (*SetAppIconId)(struct ohos_data_unifiedDataChannel_SystemDefinedAppItem_t tobj, struct TString appIconId);
    struct TString (*GetAppLabelId)(struct ohos_data_unifiedDataChannel_SystemDefinedAppItem_t tobj);
    void (*SetAppLabelId)(struct ohos_data_unifiedDataChannel_SystemDefinedAppItem_t tobj, struct TString appLabelId);
    struct TString (*GetBundleName)(struct ohos_data_unifiedDataChannel_SystemDefinedAppItem_t tobj);
    void (*SetBundleName)(struct ohos_data_unifiedDataChannel_SystemDefinedAppItem_t tobj, struct TString bundleName);
    struct TString (*GetAbilityName)(struct ohos_data_unifiedDataChannel_SystemDefinedAppItem_t tobj);
    void (*SetAbilityName)(struct ohos_data_unifiedDataChannel_SystemDefinedAppItem_t tobj, struct TString abilityName);
    int64_t (*GetInner)(struct ohos_data_unifiedDataChannel_SystemDefinedAppItem_t tobj);
};
struct ohos_data_unifiedDataChannel_SystemDefinedAppItem_vtable {
    struct ohos_data_unifiedDataChannel_SystemDefinedAppItem_ftable const* ftbl_ptr_0;
};
struct ohos_data_unifiedDataChannel_SystemDefinedAppItem_t {
    struct ohos_data_unifiedDataChannel_SystemDefinedAppItem_vtable const* vtbl_ptr;
    struct DataBlockHead* data_ptr;
};
TH_INLINE struct ohos_data_unifiedDataChannel_SystemDefinedAppItem_t ohos_data_unifiedDataChannel_SystemDefinedAppItem_dynamic(struct DataBlockHead* data_ptr) {
    struct TypeInfo const* rtti_ptr = data_ptr->rtti_ptr;
    struct ohos_data_unifiedDataChannel_SystemDefinedAppItem_t result;
    result.data_ptr = data_ptr;
    for (size_t i = 0; i < rtti_ptr->len; i++) {
        if (rtti_ptr->idmap[i].id == ohos_data_unifiedDataChannel_SystemDefinedAppItem_i) {
            result.vtbl_ptr = (struct ohos_data_unifiedDataChannel_SystemDefinedAppItem_vtable*)rtti_ptr->idmap[i].vtbl_ptr;
            return result;
        }
    }
    result.vtbl_ptr = NULL;
    return result;
}
TH_INLINE struct ohos_data_unifiedDataChannel_SystemDefinedAppItem_t ohos_data_unifiedDataChannel_SystemDefinedAppItem_copy(struct ohos_data_unifiedDataChannel_SystemDefinedAppItem_t tobj) {
    struct DataBlockHead* data_ptr = tobj.data_ptr;
    if (data_ptr) {
        tref_inc(&data_ptr->m_count);
    }
    return tobj;
}
TH_INLINE void ohos_data_unifiedDataChannel_SystemDefinedAppItem_drop(struct ohos_data_unifiedDataChannel_SystemDefinedAppItem_t tobj) {
    struct DataBlockHead* data_ptr = tobj.data_ptr;
    if (data_ptr && tref_dec(&data_ptr->m_count)) {
        data_ptr->rtti_ptr->free(data_ptr);
    }
}
