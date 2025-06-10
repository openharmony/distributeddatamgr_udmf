#pragma once
#include "taihe/object.abi.h"
#include "ohos.data.unifiedDataChannel.PlainText.abi.0.h"
#include "taihe/string.abi.h"
#include "ohos.data.unifiedDataChannel.ValueType.abi.0.h"
#include "taihe/optional.abi.h"
TH_EXPORT void const* const ohos_data_unifiedDataChannel_PlainText_i;
struct ohos_data_unifiedDataChannel_PlainText_ftable {
    struct TString (*GetType)(struct ohos_data_unifiedDataChannel_PlainText_t tobj);
    struct ohos_data_unifiedDataChannel_ValueType_t (*GetValue)(struct ohos_data_unifiedDataChannel_PlainText_t tobj);
    struct TOptional (*GetDetails)(struct ohos_data_unifiedDataChannel_PlainText_t tobj);
    void (*SetDetails)(struct ohos_data_unifiedDataChannel_PlainText_t tobj, void* details);
    void (*SetTextContent)(struct ohos_data_unifiedDataChannel_PlainText_t tobj, struct TString textContent);
    struct TString (*GetTextContent)(struct ohos_data_unifiedDataChannel_PlainText_t tobj);
    void (*SetAbstract1)(struct ohos_data_unifiedDataChannel_PlainText_t tobj, struct TString abstract1);
    struct TString (*GetAbstract1)(struct ohos_data_unifiedDataChannel_PlainText_t tobj);
    int64_t (*GetInner)(struct ohos_data_unifiedDataChannel_PlainText_t tobj);
};
struct ohos_data_unifiedDataChannel_PlainText_vtable {
    struct ohos_data_unifiedDataChannel_PlainText_ftable const* ftbl_ptr_0;
};
struct ohos_data_unifiedDataChannel_PlainText_t {
    struct ohos_data_unifiedDataChannel_PlainText_vtable const* vtbl_ptr;
    struct DataBlockHead* data_ptr;
};
TH_INLINE struct ohos_data_unifiedDataChannel_PlainText_t ohos_data_unifiedDataChannel_PlainText_dynamic(struct DataBlockHead* data_ptr) {
    struct TypeInfo const* rtti_ptr = data_ptr->rtti_ptr;
    struct ohos_data_unifiedDataChannel_PlainText_t result;
    result.data_ptr = data_ptr;
    for (size_t i = 0; i < rtti_ptr->len; i++) {
        if (rtti_ptr->idmap[i].id == ohos_data_unifiedDataChannel_PlainText_i) {
            result.vtbl_ptr = (struct ohos_data_unifiedDataChannel_PlainText_vtable*)rtti_ptr->idmap[i].vtbl_ptr;
            return result;
        }
    }
    result.vtbl_ptr = NULL;
    return result;
}
TH_INLINE struct ohos_data_unifiedDataChannel_PlainText_t ohos_data_unifiedDataChannel_PlainText_copy(struct ohos_data_unifiedDataChannel_PlainText_t tobj) {
    struct DataBlockHead* data_ptr = tobj.data_ptr;
    if (data_ptr) {
        tref_inc(&data_ptr->m_count);
    }
    return tobj;
}
TH_INLINE void ohos_data_unifiedDataChannel_PlainText_drop(struct ohos_data_unifiedDataChannel_PlainText_t tobj) {
    struct DataBlockHead* data_ptr = tobj.data_ptr;
    if (data_ptr && tref_dec(&data_ptr->m_count)) {
        data_ptr->rtti_ptr->free(data_ptr);
    }
}
