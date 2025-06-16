#pragma once
#include "taihe/object.abi.h"
#include "ohos.data.unifiedDataChannel.UnifiedDataInner.abi.0.h"
#include "ohos.data.unifiedDataChannel.AllRecords.abi.0.h"
#include "taihe/array.abi.h"
TH_EXPORT void const* const ohos_data_unifiedDataChannel_UnifiedDataInner_i;
struct ohos_data_unifiedDataChannel_UnifiedDataInner_ftable {
    void (*AddRecord)(struct ohos_data_unifiedDataChannel_UnifiedDataInner_t tobj, struct ohos_data_unifiedDataChannel_AllRecords_t const* unifiedRecord);
    struct TArray (*GetRecords)(struct ohos_data_unifiedDataChannel_UnifiedDataInner_t tobj);
    int64_t (*GetInner)(struct ohos_data_unifiedDataChannel_UnifiedDataInner_t tobj);
};
struct ohos_data_unifiedDataChannel_UnifiedDataInner_vtable {
    struct ohos_data_unifiedDataChannel_UnifiedDataInner_ftable const* ftbl_ptr_0;
};
struct ohos_data_unifiedDataChannel_UnifiedDataInner_t {
    struct ohos_data_unifiedDataChannel_UnifiedDataInner_vtable const* vtbl_ptr;
    struct DataBlockHead* data_ptr;
};
TH_INLINE struct ohos_data_unifiedDataChannel_UnifiedDataInner_t ohos_data_unifiedDataChannel_UnifiedDataInner_dynamic(struct DataBlockHead* data_ptr) {
    struct TypeInfo const* rtti_ptr = data_ptr->rtti_ptr;
    struct ohos_data_unifiedDataChannel_UnifiedDataInner_t result;
    result.data_ptr = data_ptr;
    for (size_t i = 0; i < rtti_ptr->len; i++) {
        if (rtti_ptr->idmap[i].id == ohos_data_unifiedDataChannel_UnifiedDataInner_i) {
            result.vtbl_ptr = (struct ohos_data_unifiedDataChannel_UnifiedDataInner_vtable*)rtti_ptr->idmap[i].vtbl_ptr;
            return result;
        }
    }
    result.vtbl_ptr = NULL;
    return result;
}
TH_INLINE struct ohos_data_unifiedDataChannel_UnifiedDataInner_t ohos_data_unifiedDataChannel_UnifiedDataInner_copy(struct ohos_data_unifiedDataChannel_UnifiedDataInner_t tobj) {
    struct DataBlockHead* data_ptr = tobj.data_ptr;
    if (data_ptr) {
        tref_inc(&data_ptr->m_count);
    }
    return tobj;
}
TH_INLINE void ohos_data_unifiedDataChannel_UnifiedDataInner_drop(struct ohos_data_unifiedDataChannel_UnifiedDataInner_t tobj) {
    struct DataBlockHead* data_ptr = tobj.data_ptr;
    if (data_ptr && tref_dec(&data_ptr->m_count)) {
        data_ptr->rtti_ptr->free(data_ptr);
    }
}
