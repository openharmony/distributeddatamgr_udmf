#pragma once
#include "taihe/common.h"
#include "ohos.data.unifiedDataChannel.AllRecords.abi.0.h"
#include "ohos.data.unifiedDataChannel.FileInner.abi.2.h"
#include "ohos.data.unifiedDataChannel.FolderInner.abi.2.h"
#include "ohos.data.unifiedDataChannel.AudioInner.abi.2.h"
#include "ohos.data.unifiedDataChannel.VideoInner.abi.2.h"
#include "ohos.data.unifiedDataChannel.ImageInner.abi.2.h"
#include "ohos.data.unifiedDataChannel.TextInner.abi.2.h"
#include "ohos.data.unifiedDataChannel.PlainTextInner.abi.2.h"
#include "ohos.data.unifiedDataChannel.HTMLInner.abi.2.h"
#include "ohos.data.unifiedDataChannel.HyperlinkInner.abi.2.h"
#include "ohos.data.unifiedDataChannel.SystemDefinedRecordInner.abi.2.h"
#include "ohos.data.unifiedDataChannel.SystemDefinedFormInner.abi.2.h"
#include "ohos.data.unifiedDataChannel.SystemDefinedAppItemInner.abi.2.h"
#include "ohos.data.unifiedDataChannel.SystemDefinedPixelMapInner.abi.2.h"
#include "ohos.data.unifiedDataChannel.UnifiedRecordInner.abi.2.h"
union ohos_data_unifiedDataChannel_AllRecords_union {
    struct ohos_data_unifiedDataChannel_FileInner_t file;
    struct ohos_data_unifiedDataChannel_FolderInner_t folder;
    struct ohos_data_unifiedDataChannel_AudioInner_t audio;
    struct ohos_data_unifiedDataChannel_VideoInner_t video;
    struct ohos_data_unifiedDataChannel_ImageInner_t image;
    struct ohos_data_unifiedDataChannel_TextInner_t text;
    struct ohos_data_unifiedDataChannel_PlainTextInner_t plainText;
    struct ohos_data_unifiedDataChannel_HTMLInner_t html;
    struct ohos_data_unifiedDataChannel_HyperlinkInner_t hyperlink;
    struct ohos_data_unifiedDataChannel_SystemDefinedRecordInner_t systemDefinedRecord;
    struct ohos_data_unifiedDataChannel_SystemDefinedFormInner_t systemDefinedForm;
    struct ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_t systemDefinedAppItem;
    struct ohos_data_unifiedDataChannel_SystemDefinedPixelMapInner_t systemDefinedPixelMap;
    struct ohos_data_unifiedDataChannel_UnifiedRecordInner_t unifiedRecord;
};
struct ohos_data_unifiedDataChannel_AllRecords_t {
    int m_tag;
    union ohos_data_unifiedDataChannel_AllRecords_union m_data;
};
