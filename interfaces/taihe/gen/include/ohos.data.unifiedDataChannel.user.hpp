#pragma once
#include "ohos.data.unifiedDataChannel.proj.hpp"
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
namespace ohos::data::unifiedDataChannel {
inline ::ohos::data::unifiedDataChannel::Summary CreateSummary() {
    return ::taihe::from_abi<::ohos::data::unifiedDataChannel::Summary>(ohos_data_unifiedDataChannel_CreateSummary_f());
}
}
namespace ohos::data::unifiedDataChannel {
inline ::ohos::data::unifiedDataChannel::UnifiedDataInner CreateUnifiedData() {
    return ::taihe::from_abi<::ohos::data::unifiedDataChannel::UnifiedDataInner>(ohos_data_unifiedDataChannel_CreateUnifiedData_f());
}
}
namespace ohos::data::unifiedDataChannel {
inline ::ohos::data::unifiedDataChannel::UnifiedDataInner CreateUnifiedDataWithParams(::ohos::data::unifiedDataChannel::AllRecords const& unifiedRecord) {
    return ::taihe::from_abi<::ohos::data::unifiedDataChannel::UnifiedDataInner>(ohos_data_unifiedDataChannel_CreateUnifiedDataWithParams_f(::taihe::into_abi<::ohos::data::unifiedDataChannel::AllRecords const&>(unifiedRecord)));
}
}
namespace ohos::data::unifiedDataChannel {
inline ::ohos::data::unifiedDataChannel::UnifiedRecordInner CreateUnifiedRecord() {
    return ::taihe::from_abi<::ohos::data::unifiedDataChannel::UnifiedRecordInner>(ohos_data_unifiedDataChannel_CreateUnifiedRecord_f());
}
}
namespace ohos::data::unifiedDataChannel {
inline ::ohos::data::unifiedDataChannel::UnifiedRecordInner CreateUnifiedRecordWithParams(::taihe::string_view type, ::ohos::data::unifiedDataChannel::ValueType const& value) {
    return ::taihe::from_abi<::ohos::data::unifiedDataChannel::UnifiedRecordInner>(ohos_data_unifiedDataChannel_CreateUnifiedRecordWithParams_f(::taihe::into_abi<::taihe::string_view>(type), ::taihe::into_abi<::ohos::data::unifiedDataChannel::ValueType const&>(value)));
}
}
namespace ohos::data::unifiedDataChannel {
inline ::ohos::data::unifiedDataChannel::FileInner CreateUnifiedFile() {
    return ::taihe::from_abi<::ohos::data::unifiedDataChannel::FileInner>(ohos_data_unifiedDataChannel_CreateUnifiedFile_f());
}
}
namespace ohos::data::unifiedDataChannel {
inline ::ohos::data::unifiedDataChannel::FolderInner CreateUnifiedFolder() {
    return ::taihe::from_abi<::ohos::data::unifiedDataChannel::FolderInner>(ohos_data_unifiedDataChannel_CreateUnifiedFolder_f());
}
}
namespace ohos::data::unifiedDataChannel {
inline ::ohos::data::unifiedDataChannel::AudioInner CreateUnifiedAudio() {
    return ::taihe::from_abi<::ohos::data::unifiedDataChannel::AudioInner>(ohos_data_unifiedDataChannel_CreateUnifiedAudio_f());
}
}
namespace ohos::data::unifiedDataChannel {
inline ::ohos::data::unifiedDataChannel::VideoInner CreateUnifiedVideo() {
    return ::taihe::from_abi<::ohos::data::unifiedDataChannel::VideoInner>(ohos_data_unifiedDataChannel_CreateUnifiedVideo_f());
}
}
namespace ohos::data::unifiedDataChannel {
inline ::ohos::data::unifiedDataChannel::ImageInner CreateUnifiedImage() {
    return ::taihe::from_abi<::ohos::data::unifiedDataChannel::ImageInner>(ohos_data_unifiedDataChannel_CreateUnifiedImage_f());
}
}
namespace ohos::data::unifiedDataChannel {
inline ::ohos::data::unifiedDataChannel::TextInner CreateText() {
    return ::taihe::from_abi<::ohos::data::unifiedDataChannel::TextInner>(ohos_data_unifiedDataChannel_CreateText_f());
}
}
namespace ohos::data::unifiedDataChannel {
inline ::ohos::data::unifiedDataChannel::HTMLInner CreateHtml() {
    return ::taihe::from_abi<::ohos::data::unifiedDataChannel::HTMLInner>(ohos_data_unifiedDataChannel_CreateHtml_f());
}
}
namespace ohos::data::unifiedDataChannel {
inline ::ohos::data::unifiedDataChannel::HyperlinkInner CreateHyperlink() {
    return ::taihe::from_abi<::ohos::data::unifiedDataChannel::HyperlinkInner>(ohos_data_unifiedDataChannel_CreateHyperlink_f());
}
}
namespace ohos::data::unifiedDataChannel {
inline ::ohos::data::unifiedDataChannel::PlainTextInner CreatePlainText() {
    return ::taihe::from_abi<::ohos::data::unifiedDataChannel::PlainTextInner>(ohos_data_unifiedDataChannel_CreatePlainText_f());
}
}
namespace ohos::data::unifiedDataChannel {
inline ::ohos::data::unifiedDataChannel::SystemDefinedRecordInner CreateSystemDefinedRecord() {
    return ::taihe::from_abi<::ohos::data::unifiedDataChannel::SystemDefinedRecordInner>(ohos_data_unifiedDataChannel_CreateSystemDefinedRecord_f());
}
}
namespace ohos::data::unifiedDataChannel {
inline ::ohos::data::unifiedDataChannel::SystemDefinedFormInner CreateSystemDefinedForm() {
    return ::taihe::from_abi<::ohos::data::unifiedDataChannel::SystemDefinedFormInner>(ohos_data_unifiedDataChannel_CreateSystemDefinedForm_f());
}
}
namespace ohos::data::unifiedDataChannel {
inline ::ohos::data::unifiedDataChannel::SystemDefinedAppItemInner CreateSystemDefinedAppItem() {
    return ::taihe::from_abi<::ohos::data::unifiedDataChannel::SystemDefinedAppItemInner>(ohos_data_unifiedDataChannel_CreateSystemDefinedAppItem_f());
}
}
namespace ohos::data::unifiedDataChannel {
inline ::ohos::data::unifiedDataChannel::SystemDefinedPixelMapInner CreateSystemDefinedPixelMap() {
    return ::taihe::from_abi<::ohos::data::unifiedDataChannel::SystemDefinedPixelMapInner>(ohos_data_unifiedDataChannel_CreateSystemDefinedPixelMap_f());
}
}
namespace ohos::data::unifiedDataChannel {
inline ::taihe::string InsertDataSync(::ohos::data::unifiedDataChannel::Options const& options, ::ohos::data::unifiedDataChannel::weak::UnifiedDataInner data) {
    return ::taihe::from_abi<::taihe::string>(ohos_data_unifiedDataChannel_InsertDataSync_f(::taihe::into_abi<::ohos::data::unifiedDataChannel::Options const&>(options), ::taihe::into_abi<::ohos::data::unifiedDataChannel::weak::UnifiedDataInner>(data)));
}
}
namespace ohos::data::unifiedDataChannel {
inline ::taihe::array<::ohos::data::unifiedDataChannel::UnifiedDataInner> QueryDataSync(::ohos::data::unifiedDataChannel::Options const& options) {
    return ::taihe::from_abi<::taihe::array<::ohos::data::unifiedDataChannel::UnifiedDataInner>>(ohos_data_unifiedDataChannel_QueryDataSync_f(::taihe::into_abi<::ohos::data::unifiedDataChannel::Options const&>(options)));
}
}
