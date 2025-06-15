#pragma once
#include "ohos.data.unifiedDataChannel.Options.abi.1.h"
#include "ohos.data.unifiedDataChannel.Summary.abi.1.h"
#include "ohos.data.unifiedDataChannel.ProgressInfo.abi.1.h"
#include "ohos.data.unifiedDataChannel.GetDataParams.abi.1.h"
#include "ohos.data.unifiedDataChannel.ValueType.abi.1.h"
#include "ohos.data.unifiedDataChannel.DetailsValue.abi.1.h"
#include "ohos.data.unifiedDataChannel.AllRecords.abi.1.h"
#include "ohos.data.unifiedDataChannel.UnifiedDataOrNull.abi.1.h"
#include "ohos.data.unifiedDataChannel.UnifiedDataInner.abi.2.h"
#include "ohos.data.unifiedDataChannel.UnifiedRecordInner.abi.2.h"
#include "ohos.data.unifiedDataChannel.FileInner.abi.2.h"
#include "ohos.data.unifiedDataChannel.FolderInner.abi.2.h"
#include "ohos.data.unifiedDataChannel.AudioInner.abi.2.h"
#include "ohos.data.unifiedDataChannel.VideoInner.abi.2.h"
#include "ohos.data.unifiedDataChannel.ImageInner.abi.2.h"
#include "ohos.data.unifiedDataChannel.TextInner.abi.2.h"
#include "ohos.data.unifiedDataChannel.HTMLInner.abi.2.h"
#include "ohos.data.unifiedDataChannel.HyperlinkInner.abi.2.h"
#include "ohos.data.unifiedDataChannel.PlainTextInner.abi.2.h"
#include "ohos.data.unifiedDataChannel.SystemDefinedRecordInner.abi.2.h"
#include "ohos.data.unifiedDataChannel.SystemDefinedFormInner.abi.2.h"
#include "ohos.data.unifiedDataChannel.SystemDefinedAppItemInner.abi.2.h"
#include "ohos.data.unifiedDataChannel.SystemDefinedPixelMapInner.abi.2.h"
#include "taihe/common.h"
#include "taihe/string.abi.h"
#include "taihe/array.abi.h"
TH_EXPORT struct ohos_data_unifiedDataChannel_Summary_t ohos_data_unifiedDataChannel_CreateSummary_f();
TH_EXPORT struct ohos_data_unifiedDataChannel_UnifiedDataInner_t ohos_data_unifiedDataChannel_CreateUnifiedData_f();
TH_EXPORT struct ohos_data_unifiedDataChannel_UnifiedDataInner_t ohos_data_unifiedDataChannel_CreateUnifiedDataWithParams_f(struct ohos_data_unifiedDataChannel_AllRecords_t const* unifiedRecord);
TH_EXPORT struct ohos_data_unifiedDataChannel_UnifiedRecordInner_t ohos_data_unifiedDataChannel_CreateUnifiedRecord_f();
TH_EXPORT struct ohos_data_unifiedDataChannel_UnifiedRecordInner_t ohos_data_unifiedDataChannel_CreateUnifiedRecordWithParams_f(struct TString type, struct ohos_data_unifiedDataChannel_ValueType_t const* value);
TH_EXPORT struct ohos_data_unifiedDataChannel_FileInner_t ohos_data_unifiedDataChannel_CreateUnifiedFile_f();
TH_EXPORT struct ohos_data_unifiedDataChannel_FolderInner_t ohos_data_unifiedDataChannel_CreateUnifiedFolder_f();
TH_EXPORT struct ohos_data_unifiedDataChannel_AudioInner_t ohos_data_unifiedDataChannel_CreateUnifiedAudio_f();
TH_EXPORT struct ohos_data_unifiedDataChannel_VideoInner_t ohos_data_unifiedDataChannel_CreateUnifiedVideo_f();
TH_EXPORT struct ohos_data_unifiedDataChannel_ImageInner_t ohos_data_unifiedDataChannel_CreateUnifiedImage_f();
TH_EXPORT struct ohos_data_unifiedDataChannel_TextInner_t ohos_data_unifiedDataChannel_CreateText_f();
TH_EXPORT struct ohos_data_unifiedDataChannel_HTMLInner_t ohos_data_unifiedDataChannel_CreateHtml_f();
TH_EXPORT struct ohos_data_unifiedDataChannel_HyperlinkInner_t ohos_data_unifiedDataChannel_CreateHyperlink_f();
TH_EXPORT struct ohos_data_unifiedDataChannel_PlainTextInner_t ohos_data_unifiedDataChannel_CreatePlainText_f();
TH_EXPORT struct ohos_data_unifiedDataChannel_SystemDefinedRecordInner_t ohos_data_unifiedDataChannel_CreateSystemDefinedRecord_f();
TH_EXPORT struct ohos_data_unifiedDataChannel_SystemDefinedFormInner_t ohos_data_unifiedDataChannel_CreateSystemDefinedForm_f();
TH_EXPORT struct ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_t ohos_data_unifiedDataChannel_CreateSystemDefinedAppItem_f();
TH_EXPORT struct ohos_data_unifiedDataChannel_SystemDefinedPixelMapInner_t ohos_data_unifiedDataChannel_CreateSystemDefinedPixelMap_f();
TH_EXPORT struct TString ohos_data_unifiedDataChannel_InsertDataSync_f(struct ohos_data_unifiedDataChannel_Options_t const* options, struct ohos_data_unifiedDataChannel_UnifiedDataInner_t data);
TH_EXPORT struct TArray ohos_data_unifiedDataChannel_QueryDataSync_f(struct ohos_data_unifiedDataChannel_Options_t const* options);
