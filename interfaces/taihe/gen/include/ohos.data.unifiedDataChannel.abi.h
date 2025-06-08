#pragma once
#include "ohos.data.unifiedDataChannel.Options.abi.1.h"
#include "ohos.data.unifiedDataChannel.Summary.abi.1.h"
#include "ohos.data.unifiedDataChannel.ProgressInfo.abi.1.h"
#include "ohos.data.unifiedDataChannel.GetDataParams.abi.1.h"
#include "ohos.data.unifiedDataChannel.ValueType.abi.1.h"
#include "ohos.data.unifiedDataChannel.DetailsValue.abi.1.h"
#include "ohos.data.unifiedDataChannel.UnifiedDataOrNull.abi.1.h"
#include "ohos.data.unifiedDataChannel.UnifiedData.abi.2.h"
#include "ohos.data.unifiedDataChannel.UnifiedRecord.abi.2.h"
#include "ohos.data.unifiedDataChannel.File.abi.2.h"
#include "ohos.data.unifiedDataChannel.Folder.abi.2.h"
#include "ohos.data.unifiedDataChannel.Audio.abi.2.h"
#include "ohos.data.unifiedDataChannel.Video.abi.2.h"
#include "ohos.data.unifiedDataChannel.Image.abi.2.h"
#include "ohos.data.unifiedDataChannel.Text.abi.2.h"
#include "ohos.data.unifiedDataChannel.HTML.abi.2.h"
#include "ohos.data.unifiedDataChannel.Hyperlink.abi.2.h"
#include "ohos.data.unifiedDataChannel.PlainText.abi.2.h"
#include "ohos.data.unifiedDataChannel.SystemDefinedRecord.abi.2.h"
#include "ohos.data.unifiedDataChannel.SystemDefinedForm.abi.2.h"
#include "ohos.data.unifiedDataChannel.SystemDefinedAppItem.abi.2.h"
#include "ohos.data.unifiedDataChannel.SystemDefinedPixelMap.abi.2.h"
#include "taihe/common.h"
#include "taihe/string.abi.h"
#include "taihe/array.abi.h"
TH_EXPORT struct ohos_data_unifiedDataChannel_Summary_t ohos_data_unifiedDataChannel_CreateSummary_f();
TH_EXPORT struct ohos_data_unifiedDataChannel_UnifiedData_t ohos_data_unifiedDataChannel_CreateUnifiedData_f();
TH_EXPORT struct ohos_data_unifiedDataChannel_UnifiedData_t ohos_data_unifiedDataChannel_CreateUnifiedDataWithParams_f(struct ohos_data_unifiedDataChannel_UnifiedRecord_t unifiedRecord);
TH_EXPORT struct ohos_data_unifiedDataChannel_UnifiedRecord_t ohos_data_unifiedDataChannel_CreateUnifiedRecord_f();
TH_EXPORT struct ohos_data_unifiedDataChannel_UnifiedRecord_t ohos_data_unifiedDataChannel_CreateUnifiedRecordWithParams_f(struct TString type, struct ohos_data_unifiedDataChannel_ValueType_t const* value);
TH_EXPORT struct ohos_data_unifiedDataChannel_File_t ohos_data_unifiedDataChannel_CreateUnifiedFile_f();
TH_EXPORT struct ohos_data_unifiedDataChannel_Folder_t ohos_data_unifiedDataChannel_CreateFolder_f();
TH_EXPORT struct ohos_data_unifiedDataChannel_Audio_t ohos_data_unifiedDataChannel_CreateAudio_f();
TH_EXPORT struct ohos_data_unifiedDataChannel_Video_t ohos_data_unifiedDataChannel_CreateVideo_f();
TH_EXPORT struct ohos_data_unifiedDataChannel_Image_t ohos_data_unifiedDataChannel_CreateImage_f();
TH_EXPORT struct ohos_data_unifiedDataChannel_Text_t ohos_data_unifiedDataChannel_CreateText_f();
TH_EXPORT struct ohos_data_unifiedDataChannel_HTML_t ohos_data_unifiedDataChannel_CreateHtml_f();
TH_EXPORT struct ohos_data_unifiedDataChannel_Hyperlink_t ohos_data_unifiedDataChannel_CreateHyperlink_f();
TH_EXPORT struct ohos_data_unifiedDataChannel_PlainText_t ohos_data_unifiedDataChannel_CreatePlainText_f();
TH_EXPORT struct ohos_data_unifiedDataChannel_SystemDefinedRecord_t ohos_data_unifiedDataChannel_CreateSystemDefinedRecord_f();
TH_EXPORT struct ohos_data_unifiedDataChannel_SystemDefinedForm_t ohos_data_unifiedDataChannel_CreateSystemDefinedForm_f();
TH_EXPORT struct ohos_data_unifiedDataChannel_SystemDefinedAppItem_t ohos_data_unifiedDataChannel_CreateSystemDefinedAppItem_f();
TH_EXPORT struct ohos_data_unifiedDataChannel_SystemDefinedPixelMap_t ohos_data_unifiedDataChannel_CreateSystemDefinedPixelMap_f();
TH_EXPORT void ohos_data_unifiedDataChannel_InsertDataSync_f(struct ohos_data_unifiedDataChannel_Options_t const* options, struct ohos_data_unifiedDataChannel_UnifiedData_t data);
TH_EXPORT struct TArray ohos_data_unifiedDataChannel_QueryDataSync_f(struct ohos_data_unifiedDataChannel_Options_t const* options);
