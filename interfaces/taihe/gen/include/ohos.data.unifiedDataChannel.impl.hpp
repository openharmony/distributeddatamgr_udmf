#pragma once
#include "taihe/common.hpp"
#include "ohos.data.unifiedDataChannel.abi.h"
#include "ohos.data.unifiedDataChannel.Summary.proj.1.hpp"
#include "ohos.data.unifiedDataChannel.UnifiedDataInner.proj.2.hpp"
#include "ohos.data.unifiedDataChannel.AllRecords.proj.1.hpp"
#include "ohos.data.unifiedDataChannel.UnifiedRecordInner.proj.2.hpp"
#include "taihe/string.hpp"
#include "ohos.data.unifiedDataChannel.ValueType.proj.1.hpp"
#include "ohos.data.unifiedDataChannel.FileInner.proj.2.hpp"
#include "ohos.data.unifiedDataChannel.FolderInner.proj.2.hpp"
#include "ohos.data.unifiedDataChannel.AudioInner.proj.2.hpp"
#include "ohos.data.unifiedDataChannel.VideoInner.proj.2.hpp"
#include "ohos.data.unifiedDataChannel.ImageInner.proj.2.hpp"
#include "ohos.data.unifiedDataChannel.TextInner.proj.2.hpp"
#include "ohos.data.unifiedDataChannel.HTMLInner.proj.2.hpp"
#include "ohos.data.unifiedDataChannel.HyperlinkInner.proj.2.hpp"
#include "ohos.data.unifiedDataChannel.PlainTextInner.proj.2.hpp"
#include "ohos.data.unifiedDataChannel.SystemDefinedRecordInner.proj.2.hpp"
#include "ohos.data.unifiedDataChannel.SystemDefinedFormInner.proj.2.hpp"
#include "ohos.data.unifiedDataChannel.SystemDefinedAppItemInner.proj.2.hpp"
#include "ohos.data.unifiedDataChannel.SystemDefinedPixelMapInner.proj.2.hpp"
#include "ohos.data.unifiedDataChannel.Options.proj.1.hpp"
#include "taihe/array.hpp"
#define TH_EXPORT_CPP_API_CreateSummary(CPP_FUNC_IMPL) \
    struct ohos_data_unifiedDataChannel_Summary_t ohos_data_unifiedDataChannel_CreateSummary_f() { \
        return ::taihe::into_abi<::ohos::data::unifiedDataChannel::Summary>(CPP_FUNC_IMPL()); \
    }
#define TH_EXPORT_CPP_API_CreateUnifiedData(CPP_FUNC_IMPL) \
    struct ohos_data_unifiedDataChannel_UnifiedDataInner_t ohos_data_unifiedDataChannel_CreateUnifiedData_f() { \
        return ::taihe::into_abi<::ohos::data::unifiedDataChannel::UnifiedDataInner>(CPP_FUNC_IMPL()); \
    }
#define TH_EXPORT_CPP_API_CreateUnifiedDataWithParams(CPP_FUNC_IMPL) \
    struct ohos_data_unifiedDataChannel_UnifiedDataInner_t ohos_data_unifiedDataChannel_CreateUnifiedDataWithParams_f(struct ohos_data_unifiedDataChannel_AllRecords_t const* unifiedRecord) { \
        return ::taihe::into_abi<::ohos::data::unifiedDataChannel::UnifiedDataInner>(CPP_FUNC_IMPL(::taihe::from_abi<::ohos::data::unifiedDataChannel::AllRecords const&>(unifiedRecord))); \
    }
#define TH_EXPORT_CPP_API_CreateUnifiedRecord(CPP_FUNC_IMPL) \
    struct ohos_data_unifiedDataChannel_UnifiedRecordInner_t ohos_data_unifiedDataChannel_CreateUnifiedRecord_f() { \
        return ::taihe::into_abi<::ohos::data::unifiedDataChannel::UnifiedRecordInner>(CPP_FUNC_IMPL()); \
    }
#define TH_EXPORT_CPP_API_CreateUnifiedRecordWithParams(CPP_FUNC_IMPL) \
    struct ohos_data_unifiedDataChannel_UnifiedRecordInner_t ohos_data_unifiedDataChannel_CreateUnifiedRecordWithParams_f(struct TString type, struct ohos_data_unifiedDataChannel_ValueType_t const* value) { \
        return ::taihe::into_abi<::ohos::data::unifiedDataChannel::UnifiedRecordInner>(CPP_FUNC_IMPL(::taihe::from_abi<::taihe::string_view>(type), ::taihe::from_abi<::ohos::data::unifiedDataChannel::ValueType const&>(value))); \
    }
#define TH_EXPORT_CPP_API_CreateUnifiedFile(CPP_FUNC_IMPL) \
    struct ohos_data_unifiedDataChannel_FileInner_t ohos_data_unifiedDataChannel_CreateUnifiedFile_f() { \
        return ::taihe::into_abi<::ohos::data::unifiedDataChannel::FileInner>(CPP_FUNC_IMPL()); \
    }
#define TH_EXPORT_CPP_API_CreateUnifiedFolder(CPP_FUNC_IMPL) \
    struct ohos_data_unifiedDataChannel_FolderInner_t ohos_data_unifiedDataChannel_CreateUnifiedFolder_f() { \
        return ::taihe::into_abi<::ohos::data::unifiedDataChannel::FolderInner>(CPP_FUNC_IMPL()); \
    }
#define TH_EXPORT_CPP_API_CreateUnifiedAudio(CPP_FUNC_IMPL) \
    struct ohos_data_unifiedDataChannel_AudioInner_t ohos_data_unifiedDataChannel_CreateUnifiedAudio_f() { \
        return ::taihe::into_abi<::ohos::data::unifiedDataChannel::AudioInner>(CPP_FUNC_IMPL()); \
    }
#define TH_EXPORT_CPP_API_CreateUnifiedVideo(CPP_FUNC_IMPL) \
    struct ohos_data_unifiedDataChannel_VideoInner_t ohos_data_unifiedDataChannel_CreateUnifiedVideo_f() { \
        return ::taihe::into_abi<::ohos::data::unifiedDataChannel::VideoInner>(CPP_FUNC_IMPL()); \
    }
#define TH_EXPORT_CPP_API_CreateUnifiedImage(CPP_FUNC_IMPL) \
    struct ohos_data_unifiedDataChannel_ImageInner_t ohos_data_unifiedDataChannel_CreateUnifiedImage_f() { \
        return ::taihe::into_abi<::ohos::data::unifiedDataChannel::ImageInner>(CPP_FUNC_IMPL()); \
    }
#define TH_EXPORT_CPP_API_CreateText(CPP_FUNC_IMPL) \
    struct ohos_data_unifiedDataChannel_TextInner_t ohos_data_unifiedDataChannel_CreateText_f() { \
        return ::taihe::into_abi<::ohos::data::unifiedDataChannel::TextInner>(CPP_FUNC_IMPL()); \
    }
#define TH_EXPORT_CPP_API_CreateHtml(CPP_FUNC_IMPL) \
    struct ohos_data_unifiedDataChannel_HTMLInner_t ohos_data_unifiedDataChannel_CreateHtml_f() { \
        return ::taihe::into_abi<::ohos::data::unifiedDataChannel::HTMLInner>(CPP_FUNC_IMPL()); \
    }
#define TH_EXPORT_CPP_API_CreateHyperlink(CPP_FUNC_IMPL) \
    struct ohos_data_unifiedDataChannel_HyperlinkInner_t ohos_data_unifiedDataChannel_CreateHyperlink_f() { \
        return ::taihe::into_abi<::ohos::data::unifiedDataChannel::HyperlinkInner>(CPP_FUNC_IMPL()); \
    }
#define TH_EXPORT_CPP_API_CreatePlainText(CPP_FUNC_IMPL) \
    struct ohos_data_unifiedDataChannel_PlainTextInner_t ohos_data_unifiedDataChannel_CreatePlainText_f() { \
        return ::taihe::into_abi<::ohos::data::unifiedDataChannel::PlainTextInner>(CPP_FUNC_IMPL()); \
    }
#define TH_EXPORT_CPP_API_CreateSystemDefinedRecord(CPP_FUNC_IMPL) \
    struct ohos_data_unifiedDataChannel_SystemDefinedRecordInner_t ohos_data_unifiedDataChannel_CreateSystemDefinedRecord_f() { \
        return ::taihe::into_abi<::ohos::data::unifiedDataChannel::SystemDefinedRecordInner>(CPP_FUNC_IMPL()); \
    }
#define TH_EXPORT_CPP_API_CreateSystemDefinedForm(CPP_FUNC_IMPL) \
    struct ohos_data_unifiedDataChannel_SystemDefinedFormInner_t ohos_data_unifiedDataChannel_CreateSystemDefinedForm_f() { \
        return ::taihe::into_abi<::ohos::data::unifiedDataChannel::SystemDefinedFormInner>(CPP_FUNC_IMPL()); \
    }
#define TH_EXPORT_CPP_API_CreateSystemDefinedAppItem(CPP_FUNC_IMPL) \
    struct ohos_data_unifiedDataChannel_SystemDefinedAppItemInner_t ohos_data_unifiedDataChannel_CreateSystemDefinedAppItem_f() { \
        return ::taihe::into_abi<::ohos::data::unifiedDataChannel::SystemDefinedAppItemInner>(CPP_FUNC_IMPL()); \
    }
#define TH_EXPORT_CPP_API_CreateSystemDefinedPixelMap(CPP_FUNC_IMPL) \
    struct ohos_data_unifiedDataChannel_SystemDefinedPixelMapInner_t ohos_data_unifiedDataChannel_CreateSystemDefinedPixelMap_f() { \
        return ::taihe::into_abi<::ohos::data::unifiedDataChannel::SystemDefinedPixelMapInner>(CPP_FUNC_IMPL()); \
    }
#define TH_EXPORT_CPP_API_InsertDataSync(CPP_FUNC_IMPL) \
    struct TString ohos_data_unifiedDataChannel_InsertDataSync_f(struct ohos_data_unifiedDataChannel_Options_t const* options, struct ohos_data_unifiedDataChannel_UnifiedDataInner_t data) { \
        return ::taihe::into_abi<::taihe::string>(CPP_FUNC_IMPL(::taihe::from_abi<::ohos::data::unifiedDataChannel::Options const&>(options), ::taihe::from_abi<::ohos::data::unifiedDataChannel::weak::UnifiedDataInner>(data))); \
    }
#define TH_EXPORT_CPP_API_QueryDataSync(CPP_FUNC_IMPL) \
    struct TArray ohos_data_unifiedDataChannel_QueryDataSync_f(struct ohos_data_unifiedDataChannel_Options_t const* options) { \
        return ::taihe::into_abi<::taihe::array<::ohos::data::unifiedDataChannel::UnifiedDataInner>>(CPP_FUNC_IMPL(::taihe::from_abi<::ohos::data::unifiedDataChannel::Options const&>(options))); \
    }
