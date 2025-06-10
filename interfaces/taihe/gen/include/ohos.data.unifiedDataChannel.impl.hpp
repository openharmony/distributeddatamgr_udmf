#pragma once
#include "taihe/common.hpp"
#include "ohos.data.unifiedDataChannel.abi.h"
#include "ohos.data.unifiedDataChannel.Summary.proj.1.hpp"
#include "ohos.data.unifiedDataChannel.UnifiedData.proj.2.hpp"
#include "ohos.data.unifiedDataChannel.AllRecords.proj.1.hpp"
#include "ohos.data.unifiedDataChannel.UnifiedRecord.proj.2.hpp"
#include "taihe/string.hpp"
#include "ohos.data.unifiedDataChannel.ValueType.proj.1.hpp"
#include "ohos.data.unifiedDataChannel.File.proj.2.hpp"
#include "ohos.data.unifiedDataChannel.Folder.proj.2.hpp"
#include "ohos.data.unifiedDataChannel.Audio.proj.2.hpp"
#include "ohos.data.unifiedDataChannel.Video.proj.2.hpp"
#include "ohos.data.unifiedDataChannel.Image.proj.2.hpp"
#include "ohos.data.unifiedDataChannel.Text.proj.2.hpp"
#include "ohos.data.unifiedDataChannel.HTML.proj.2.hpp"
#include "ohos.data.unifiedDataChannel.Hyperlink.proj.2.hpp"
#include "ohos.data.unifiedDataChannel.PlainText.proj.2.hpp"
#include "ohos.data.unifiedDataChannel.SystemDefinedRecord.proj.2.hpp"
#include "ohos.data.unifiedDataChannel.SystemDefinedForm.proj.2.hpp"
#include "ohos.data.unifiedDataChannel.SystemDefinedAppItem.proj.2.hpp"
#include "ohos.data.unifiedDataChannel.SystemDefinedPixelMap.proj.2.hpp"
#include "ohos.data.unifiedDataChannel.Options.proj.1.hpp"
#include "taihe/array.hpp"
#define TH_EXPORT_CPP_API_CreateSummary(CPP_FUNC_IMPL) \
    struct ohos_data_unifiedDataChannel_Summary_t ohos_data_unifiedDataChannel_CreateSummary_f() { \
        return ::taihe::into_abi<::ohos::data::unifiedDataChannel::Summary>(CPP_FUNC_IMPL()); \
    }
#define TH_EXPORT_CPP_API_CreateUnifiedData(CPP_FUNC_IMPL) \
    struct ohos_data_unifiedDataChannel_UnifiedData_t ohos_data_unifiedDataChannel_CreateUnifiedData_f() { \
        return ::taihe::into_abi<::ohos::data::unifiedDataChannel::UnifiedData>(CPP_FUNC_IMPL()); \
    }
#define TH_EXPORT_CPP_API_CreateUnifiedDataWithParams(CPP_FUNC_IMPL) \
    struct ohos_data_unifiedDataChannel_UnifiedData_t ohos_data_unifiedDataChannel_CreateUnifiedDataWithParams_f(struct ohos_data_unifiedDataChannel_AllRecords_t const* unifiedRecord) { \
        return ::taihe::into_abi<::ohos::data::unifiedDataChannel::UnifiedData>(CPP_FUNC_IMPL(::taihe::from_abi<::ohos::data::unifiedDataChannel::AllRecords const&>(unifiedRecord))); \
    }
#define TH_EXPORT_CPP_API_CreateUnifiedRecord(CPP_FUNC_IMPL) \
    struct ohos_data_unifiedDataChannel_UnifiedRecord_t ohos_data_unifiedDataChannel_CreateUnifiedRecord_f() { \
        return ::taihe::into_abi<::ohos::data::unifiedDataChannel::UnifiedRecord>(CPP_FUNC_IMPL()); \
    }
#define TH_EXPORT_CPP_API_CreateUnifiedRecordWithParams(CPP_FUNC_IMPL) \
    struct ohos_data_unifiedDataChannel_UnifiedRecord_t ohos_data_unifiedDataChannel_CreateUnifiedRecordWithParams_f(struct TString type, struct ohos_data_unifiedDataChannel_ValueType_t const* value) { \
        return ::taihe::into_abi<::ohos::data::unifiedDataChannel::UnifiedRecord>(CPP_FUNC_IMPL(::taihe::from_abi<::taihe::string_view>(type), ::taihe::from_abi<::ohos::data::unifiedDataChannel::ValueType const&>(value))); \
    }
#define TH_EXPORT_CPP_API_CreateUnifiedFile(CPP_FUNC_IMPL) \
    struct ohos_data_unifiedDataChannel_File_t ohos_data_unifiedDataChannel_CreateUnifiedFile_f() { \
        return ::taihe::into_abi<::ohos::data::unifiedDataChannel::File>(CPP_FUNC_IMPL()); \
    }
#define TH_EXPORT_CPP_API_CreateFolder(CPP_FUNC_IMPL) \
    struct ohos_data_unifiedDataChannel_Folder_t ohos_data_unifiedDataChannel_CreateFolder_f() { \
        return ::taihe::into_abi<::ohos::data::unifiedDataChannel::Folder>(CPP_FUNC_IMPL()); \
    }
#define TH_EXPORT_CPP_API_CreateAudio(CPP_FUNC_IMPL) \
    struct ohos_data_unifiedDataChannel_Audio_t ohos_data_unifiedDataChannel_CreateAudio_f() { \
        return ::taihe::into_abi<::ohos::data::unifiedDataChannel::Audio>(CPP_FUNC_IMPL()); \
    }
#define TH_EXPORT_CPP_API_CreateVideo(CPP_FUNC_IMPL) \
    struct ohos_data_unifiedDataChannel_Video_t ohos_data_unifiedDataChannel_CreateVideo_f() { \
        return ::taihe::into_abi<::ohos::data::unifiedDataChannel::Video>(CPP_FUNC_IMPL()); \
    }
#define TH_EXPORT_CPP_API_CreateImage(CPP_FUNC_IMPL) \
    struct ohos_data_unifiedDataChannel_Image_t ohos_data_unifiedDataChannel_CreateImage_f() { \
        return ::taihe::into_abi<::ohos::data::unifiedDataChannel::Image>(CPP_FUNC_IMPL()); \
    }
#define TH_EXPORT_CPP_API_CreateText(CPP_FUNC_IMPL) \
    struct ohos_data_unifiedDataChannel_Text_t ohos_data_unifiedDataChannel_CreateText_f() { \
        return ::taihe::into_abi<::ohos::data::unifiedDataChannel::Text>(CPP_FUNC_IMPL()); \
    }
#define TH_EXPORT_CPP_API_CreateHtml(CPP_FUNC_IMPL) \
    struct ohos_data_unifiedDataChannel_HTML_t ohos_data_unifiedDataChannel_CreateHtml_f() { \
        return ::taihe::into_abi<::ohos::data::unifiedDataChannel::HTML>(CPP_FUNC_IMPL()); \
    }
#define TH_EXPORT_CPP_API_CreateHyperlink(CPP_FUNC_IMPL) \
    struct ohos_data_unifiedDataChannel_Hyperlink_t ohos_data_unifiedDataChannel_CreateHyperlink_f() { \
        return ::taihe::into_abi<::ohos::data::unifiedDataChannel::Hyperlink>(CPP_FUNC_IMPL()); \
    }
#define TH_EXPORT_CPP_API_CreatePlainText(CPP_FUNC_IMPL) \
    struct ohos_data_unifiedDataChannel_PlainText_t ohos_data_unifiedDataChannel_CreatePlainText_f() { \
        return ::taihe::into_abi<::ohos::data::unifiedDataChannel::PlainText>(CPP_FUNC_IMPL()); \
    }
#define TH_EXPORT_CPP_API_CreateSystemDefinedRecord(CPP_FUNC_IMPL) \
    struct ohos_data_unifiedDataChannel_SystemDefinedRecord_t ohos_data_unifiedDataChannel_CreateSystemDefinedRecord_f() { \
        return ::taihe::into_abi<::ohos::data::unifiedDataChannel::SystemDefinedRecord>(CPP_FUNC_IMPL()); \
    }
#define TH_EXPORT_CPP_API_CreateSystemDefinedForm(CPP_FUNC_IMPL) \
    struct ohos_data_unifiedDataChannel_SystemDefinedForm_t ohos_data_unifiedDataChannel_CreateSystemDefinedForm_f() { \
        return ::taihe::into_abi<::ohos::data::unifiedDataChannel::SystemDefinedForm>(CPP_FUNC_IMPL()); \
    }
#define TH_EXPORT_CPP_API_CreateSystemDefinedAppItem(CPP_FUNC_IMPL) \
    struct ohos_data_unifiedDataChannel_SystemDefinedAppItem_t ohos_data_unifiedDataChannel_CreateSystemDefinedAppItem_f() { \
        return ::taihe::into_abi<::ohos::data::unifiedDataChannel::SystemDefinedAppItem>(CPP_FUNC_IMPL()); \
    }
#define TH_EXPORT_CPP_API_CreateSystemDefinedPixelMap(CPP_FUNC_IMPL) \
    struct ohos_data_unifiedDataChannel_SystemDefinedPixelMap_t ohos_data_unifiedDataChannel_CreateSystemDefinedPixelMap_f() { \
        return ::taihe::into_abi<::ohos::data::unifiedDataChannel::SystemDefinedPixelMap>(CPP_FUNC_IMPL()); \
    }
#define TH_EXPORT_CPP_API_InsertDataSync(CPP_FUNC_IMPL) \
    void ohos_data_unifiedDataChannel_InsertDataSync_f(struct ohos_data_unifiedDataChannel_Options_t const* options, struct ohos_data_unifiedDataChannel_UnifiedData_t data) { \
        return CPP_FUNC_IMPL(::taihe::from_abi<::ohos::data::unifiedDataChannel::Options const&>(options), ::taihe::from_abi<::ohos::data::unifiedDataChannel::weak::UnifiedData>(data)); \
    }
#define TH_EXPORT_CPP_API_QueryDataSync(CPP_FUNC_IMPL) \
    struct TArray ohos_data_unifiedDataChannel_QueryDataSync_f(struct ohos_data_unifiedDataChannel_Options_t const* options) { \
        return ::taihe::into_abi<::taihe::array<::ohos::data::unifiedDataChannel::UnifiedData>>(CPP_FUNC_IMPL(::taihe::from_abi<::ohos::data::unifiedDataChannel::Options const&>(options))); \
    }
