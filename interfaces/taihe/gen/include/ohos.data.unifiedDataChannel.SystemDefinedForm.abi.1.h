#pragma once
#include "taihe/object.abi.h"
#include "ohos.data.unifiedDataChannel.SystemDefinedForm.abi.0.h"
#include "taihe/string.abi.h"
#include "ohos.data.unifiedDataChannel.ValueType.abi.0.h"
#include "taihe/optional.abi.h"
TH_EXPORT void const* const ohos_data_unifiedDataChannel_SystemDefinedForm_i;
struct ohos_data_unifiedDataChannel_SystemDefinedForm_ftable {
    struct TString (*GetType)(struct ohos_data_unifiedDataChannel_SystemDefinedForm_t tobj);
    struct ohos_data_unifiedDataChannel_ValueType_t (*GetValue)(struct ohos_data_unifiedDataChannel_SystemDefinedForm_t tobj);
    struct TOptional (*GetDetails)(struct ohos_data_unifiedDataChannel_SystemDefinedForm_t tobj);
    void (*SetDetails)(struct ohos_data_unifiedDataChannel_SystemDefinedForm_t tobj, void* details);
    double (*GetFormId)(struct ohos_data_unifiedDataChannel_SystemDefinedForm_t tobj);
    void (*SetFormId)(struct ohos_data_unifiedDataChannel_SystemDefinedForm_t tobj, double formId);
    struct TString (*GetFormName)(struct ohos_data_unifiedDataChannel_SystemDefinedForm_t tobj);
    void (*SetFormName)(struct ohos_data_unifiedDataChannel_SystemDefinedForm_t tobj, struct TString formName);
    struct TString (*GetBundleName)(struct ohos_data_unifiedDataChannel_SystemDefinedForm_t tobj);
    void (*SetBundleName)(struct ohos_data_unifiedDataChannel_SystemDefinedForm_t tobj, struct TString bundleName);
    struct TString (*GetAbilityName)(struct ohos_data_unifiedDataChannel_SystemDefinedForm_t tobj);
    void (*SetAbilityName)(struct ohos_data_unifiedDataChannel_SystemDefinedForm_t tobj, struct TString abilityName);
    struct TString (*GetModule)(struct ohos_data_unifiedDataChannel_SystemDefinedForm_t tobj);
    void (*SetModule)(struct ohos_data_unifiedDataChannel_SystemDefinedForm_t tobj, struct TString module);
    int64_t (*GetInner)(struct ohos_data_unifiedDataChannel_SystemDefinedForm_t tobj);
};
struct ohos_data_unifiedDataChannel_SystemDefinedForm_vtable {
    struct ohos_data_unifiedDataChannel_SystemDefinedForm_ftable const* ftbl_ptr_0;
};
struct ohos_data_unifiedDataChannel_SystemDefinedForm_t {
    struct ohos_data_unifiedDataChannel_SystemDefinedForm_vtable const* vtbl_ptr;
    struct DataBlockHead* data_ptr;
};
TH_INLINE struct ohos_data_unifiedDataChannel_SystemDefinedForm_t ohos_data_unifiedDataChannel_SystemDefinedForm_dynamic(struct DataBlockHead* data_ptr) {
    struct TypeInfo const* rtti_ptr = data_ptr->rtti_ptr;
    struct ohos_data_unifiedDataChannel_SystemDefinedForm_t result;
    result.data_ptr = data_ptr;
    for (size_t i = 0; i < rtti_ptr->len; i++) {
        if (rtti_ptr->idmap[i].id == ohos_data_unifiedDataChannel_SystemDefinedForm_i) {
            result.vtbl_ptr = (struct ohos_data_unifiedDataChannel_SystemDefinedForm_vtable*)rtti_ptr->idmap[i].vtbl_ptr;
            return result;
        }
    }
    result.vtbl_ptr = NULL;
    return result;
}
TH_INLINE struct ohos_data_unifiedDataChannel_SystemDefinedForm_t ohos_data_unifiedDataChannel_SystemDefinedForm_copy(struct ohos_data_unifiedDataChannel_SystemDefinedForm_t tobj) {
    struct DataBlockHead* data_ptr = tobj.data_ptr;
    if (data_ptr) {
        tref_inc(&data_ptr->m_count);
    }
    return tobj;
}
TH_INLINE void ohos_data_unifiedDataChannel_SystemDefinedForm_drop(struct ohos_data_unifiedDataChannel_SystemDefinedForm_t tobj) {
    struct DataBlockHead* data_ptr = tobj.data_ptr;
    if (data_ptr && tref_dec(&data_ptr->m_count)) {
        data_ptr->rtti_ptr->free(data_ptr);
    }
}
