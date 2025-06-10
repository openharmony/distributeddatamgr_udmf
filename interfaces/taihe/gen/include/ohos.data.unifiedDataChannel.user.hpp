#pragma once
#include "ohos.data.unifiedDataChannel.proj.hpp"
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
namespace ohos::data::unifiedDataChannel {
inline ::ohos::data::unifiedDataChannel::Summary CreateSummary() {
    return ::taihe::from_abi<::ohos::data::unifiedDataChannel::Summary>(ohos_data_unifiedDataChannel_CreateSummary_f());
}
}
namespace ohos::data::unifiedDataChannel {
inline ::ohos::data::unifiedDataChannel::UnifiedData CreateUnifiedData() {
    return ::taihe::from_abi<::ohos::data::unifiedDataChannel::UnifiedData>(ohos_data_unifiedDataChannel_CreateUnifiedData_f());
}
}
namespace ohos::data::unifiedDataChannel {
inline ::ohos::data::unifiedDataChannel::UnifiedData CreateUnifiedDataWithParams(::ohos::data::unifiedDataChannel::AllRecords const& unifiedRecord) {
    return ::taihe::from_abi<::ohos::data::unifiedDataChannel::UnifiedData>(ohos_data_unifiedDataChannel_CreateUnifiedDataWithParams_f(::taihe::into_abi<::ohos::data::unifiedDataChannel::AllRecords const&>(unifiedRecord)));
}
}
namespace ohos::data::unifiedDataChannel {
inline ::ohos::data::unifiedDataChannel::UnifiedRecord CreateUnifiedRecord() {
    return ::taihe::from_abi<::ohos::data::unifiedDataChannel::UnifiedRecord>(ohos_data_unifiedDataChannel_CreateUnifiedRecord_f());
}
}
namespace ohos::data::unifiedDataChannel {
inline ::ohos::data::unifiedDataChannel::UnifiedRecord CreateUnifiedRecordWithParams(::taihe::string_view type, ::ohos::data::unifiedDataChannel::ValueType const& value) {
    return ::taihe::from_abi<::ohos::data::unifiedDataChannel::UnifiedRecord>(ohos_data_unifiedDataChannel_CreateUnifiedRecordWithParams_f(::taihe::into_abi<::taihe::string_view>(type), ::taihe::into_abi<::ohos::data::unifiedDataChannel::ValueType const&>(value)));
}
}
namespace ohos::data::unifiedDataChannel {
inline ::ohos::data::unifiedDataChannel::File CreateUnifiedFile() {
    return ::taihe::from_abi<::ohos::data::unifiedDataChannel::File>(ohos_data_unifiedDataChannel_CreateUnifiedFile_f());
}
}
namespace ohos::data::unifiedDataChannel {
inline ::ohos::data::unifiedDataChannel::Folder CreateFolder() {
    return ::taihe::from_abi<::ohos::data::unifiedDataChannel::Folder>(ohos_data_unifiedDataChannel_CreateFolder_f());
}
}
namespace ohos::data::unifiedDataChannel {
inline ::ohos::data::unifiedDataChannel::Audio CreateAudio() {
    return ::taihe::from_abi<::ohos::data::unifiedDataChannel::Audio>(ohos_data_unifiedDataChannel_CreateAudio_f());
}
}
namespace ohos::data::unifiedDataChannel {
inline ::ohos::data::unifiedDataChannel::Video CreateVideo() {
    return ::taihe::from_abi<::ohos::data::unifiedDataChannel::Video>(ohos_data_unifiedDataChannel_CreateVideo_f());
}
}
namespace ohos::data::unifiedDataChannel {
inline ::ohos::data::unifiedDataChannel::Image CreateImage() {
    return ::taihe::from_abi<::ohos::data::unifiedDataChannel::Image>(ohos_data_unifiedDataChannel_CreateImage_f());
}
}
namespace ohos::data::unifiedDataChannel {
inline ::ohos::data::unifiedDataChannel::Text CreateText() {
    return ::taihe::from_abi<::ohos::data::unifiedDataChannel::Text>(ohos_data_unifiedDataChannel_CreateText_f());
}
}
namespace ohos::data::unifiedDataChannel {
inline ::ohos::data::unifiedDataChannel::HTML CreateHtml() {
    return ::taihe::from_abi<::ohos::data::unifiedDataChannel::HTML>(ohos_data_unifiedDataChannel_CreateHtml_f());
}
}
namespace ohos::data::unifiedDataChannel {
inline ::ohos::data::unifiedDataChannel::Hyperlink CreateHyperlink() {
    return ::taihe::from_abi<::ohos::data::unifiedDataChannel::Hyperlink>(ohos_data_unifiedDataChannel_CreateHyperlink_f());
}
}
namespace ohos::data::unifiedDataChannel {
inline ::ohos::data::unifiedDataChannel::PlainText CreatePlainText() {
    return ::taihe::from_abi<::ohos::data::unifiedDataChannel::PlainText>(ohos_data_unifiedDataChannel_CreatePlainText_f());
}
}
namespace ohos::data::unifiedDataChannel {
inline ::ohos::data::unifiedDataChannel::SystemDefinedRecord CreateSystemDefinedRecord() {
    return ::taihe::from_abi<::ohos::data::unifiedDataChannel::SystemDefinedRecord>(ohos_data_unifiedDataChannel_CreateSystemDefinedRecord_f());
}
}
namespace ohos::data::unifiedDataChannel {
inline ::ohos::data::unifiedDataChannel::SystemDefinedForm CreateSystemDefinedForm() {
    return ::taihe::from_abi<::ohos::data::unifiedDataChannel::SystemDefinedForm>(ohos_data_unifiedDataChannel_CreateSystemDefinedForm_f());
}
}
namespace ohos::data::unifiedDataChannel {
inline ::ohos::data::unifiedDataChannel::SystemDefinedAppItem CreateSystemDefinedAppItem() {
    return ::taihe::from_abi<::ohos::data::unifiedDataChannel::SystemDefinedAppItem>(ohos_data_unifiedDataChannel_CreateSystemDefinedAppItem_f());
}
}
namespace ohos::data::unifiedDataChannel {
inline ::ohos::data::unifiedDataChannel::SystemDefinedPixelMap CreateSystemDefinedPixelMap() {
    return ::taihe::from_abi<::ohos::data::unifiedDataChannel::SystemDefinedPixelMap>(ohos_data_unifiedDataChannel_CreateSystemDefinedPixelMap_f());
}
}
namespace ohos::data::unifiedDataChannel {
inline void InsertDataSync(::ohos::data::unifiedDataChannel::Options const& options, ::ohos::data::unifiedDataChannel::weak::UnifiedData data) {
    return ohos_data_unifiedDataChannel_InsertDataSync_f(::taihe::into_abi<::ohos::data::unifiedDataChannel::Options const&>(options), ::taihe::into_abi<::ohos::data::unifiedDataChannel::weak::UnifiedData>(data));
}
}
namespace ohos::data::unifiedDataChannel {
inline ::taihe::array<::ohos::data::unifiedDataChannel::UnifiedData> QueryDataSync(::ohos::data::unifiedDataChannel::Options const& options) {
    return ::taihe::from_abi<::taihe::array<::ohos::data::unifiedDataChannel::UnifiedData>>(ohos_data_unifiedDataChannel_QueryDataSync_f(::taihe::into_abi<::ohos::data::unifiedDataChannel::Options const&>(options)));
}
}
