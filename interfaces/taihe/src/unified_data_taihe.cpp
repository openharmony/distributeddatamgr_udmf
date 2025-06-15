/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include "unified_data_taihe.h"
#include "unified_record_taihe.h"
#include "file_taihe.h"
#include "folder_taihe.h"
#include "audio_taihe.h"
#include "video_taihe.h"
#include "image_taihe.h"
#include "text_taihe.h"
#include "plain_text_taihe.h"
#include "html_taihe.h"
#include "hyperlink_taihe.h"
#include "defined_form_taihe.h"
#include "defined_appitem_taihe.h"
#include "defined_pixelmap_taihe.h"
#include "defined_record_taihe.h"
#include "taihe_common_utils.h"
#include "taihe/runtime.hpp"

UnifiedDataImpl::UnifiedDataImpl()
{
    this->value_ = std::make_shared<taiheUdmf::UnifiedData>();
}

void UnifiedDataImpl::AddRecord(::ohos::data::unifiedDataChannel::AllRecords const& unifiedRecord)
{
    switch (unifiedRecord.get_tag()) {
        case ::ohos::data::unifiedDataChannel::AllRecords::tag_t::unifiedRecord: {
            auto unifiedRecordInnerImpl =
                reinterpret_cast<UnifiedRecordInnerImpl*>(unifiedRecord.get_unifiedRecord_ref()->GetInner());
            this->value_->AddRecord(unifiedRecordInnerImpl->value_);
            break;
        }
        case ::ohos::data::unifiedDataChannel::AllRecords::tag_t::file: {
            auto fileInnerImpl = reinterpret_cast<FileInnerImpl*>(unifiedRecord.get_file_ref()->GetInner());
            this->value_->AddRecord(fileInnerImpl->value_);
            break;
        }
        case ::ohos::data::unifiedDataChannel::AllRecords::tag_t::folder: {
            auto folderInnerImpl = reinterpret_cast<FolderInnerImpl*>(unifiedRecord.get_folder_ref()->GetInner());
            this->value_->AddRecord(folderInnerImpl->value_);
            break;
        }
        case ::ohos::data::unifiedDataChannel::AllRecords::tag_t::audio: {
            auto audioInnerImpl = reinterpret_cast<AudioInnerImpl*>(unifiedRecord.get_audio_ref()->GetInner());
            this->value_->AddRecord(audioInnerImpl->value_);
            break;
        }
        case ::ohos::data::unifiedDataChannel::AllRecords::tag_t::video: {
            auto videoInnerImpl = reinterpret_cast<VideoInnerImpl*>(unifiedRecord.get_video_ref()->GetInner());
            this->value_->AddRecord(videoInnerImpl->value_);
            break;
        }
        case ::ohos::data::unifiedDataChannel::AllRecords::tag_t::image: {
            auto imageInnerImpl = reinterpret_cast<ImageInnerImpl*>(unifiedRecord.get_image_ref()->GetInner());
            this->value_->AddRecord(imageInnerImpl->value_);
            break;
        }
        case ::ohos::data::unifiedDataChannel::AllRecords::tag_t::text: {
            auto textInnerImpl = reinterpret_cast<TextInnerImpl*>(unifiedRecord.get_text_ref()->GetInner());
            this->value_->AddRecord(textInnerImpl->value_);
            break;
        }
        case ::ohos::data::unifiedDataChannel::AllRecords::tag_t::plainText: {
            auto plainTextInnerImpl =
                reinterpret_cast<PlainTextInnerImpl*>(unifiedRecord.get_plainText_ref()->GetInner());
            this->value_->AddRecord(plainTextInnerImpl->value_);
            break;
        }
        case ::ohos::data::unifiedDataChannel::AllRecords::tag_t::html: {
            auto htmlInnerImpl = reinterpret_cast<HTMLInnerImpl*>(unifiedRecord.get_html_ref()->GetInner());
            this->value_->AddRecord(htmlInnerImpl->value_);
            break;
        }
        case ::ohos::data::unifiedDataChannel::AllRecords::tag_t::hyperlink: {
            auto hyperlinkInnerImpl =
                reinterpret_cast<HyperlinkInnerImpl*>(unifiedRecord.get_hyperlink_ref()->GetInner());
            this->value_->AddRecord(hyperlinkInnerImpl->value_);
            break;
        }
        case ::ohos::data::unifiedDataChannel::AllRecords::tag_t::systemDefinedRecord: {
            auto systemDefinedRecordInnerImpl = reinterpret_cast<SystemDefinedRecordInnerImpl*>(
                unifiedRecord.get_systemDefinedRecord_ref()->GetInner());
            this->value_->AddRecord(systemDefinedRecordInnerImpl->value_);
            break;
        }
        case ::ohos::data::unifiedDataChannel::AllRecords::tag_t::systemDefinedForm: {
            auto systemDefinedFormInnerImpl = reinterpret_cast<SystemDefinedFormInnerImpl*>(
                unifiedRecord.get_systemDefinedForm_ref()->GetInner());
            this->value_->AddRecord(systemDefinedFormInnerImpl->value_);
            break;
        }
        case ::ohos::data::unifiedDataChannel::AllRecords::tag_t::systemDefinedAppItem: {
            auto systemDefinedAppItemInnerImpl = reinterpret_cast<SystemDefinedAppItemInnerImpl*>(
                unifiedRecord.get_systemDefinedAppItem_ref()->GetInner());
            this->value_->AddRecord(systemDefinedAppItemInnerImpl->value_);
            break;
        }
        case ::ohos::data::unifiedDataChannel::AllRecords::tag_t::systemDefinedPixelMap: {
            auto systemDefinedPixelMapInnerImpl = reinterpret_cast<SystemDefinedPixelMapInnerImpl*>(
                unifiedRecord.get_systemDefinedPixelMap_ref()->GetInner());
            this->value_->AddRecord(systemDefinedPixelMapInnerImpl->value_);
            break;
        }
        default: {
            taihe::set_business_error(taiheUdmf::PARAMETERSERROR, "Parameter error.");
        }
    }
}

::taihe::array<::ohos::data::unifiedDataChannel::AllRecords> UnifiedDataImpl::GetRecords()
{
    auto records = this->value_->GetRecords();
    std::vector<::ohos::data::unifiedDataChannel::AllRecords> recordsImpls;
    for (auto &record : records) {
        recordsImpls.push_back(GetRecord(record));
    }
    return ::taihe::array<::ohos::data::unifiedDataChannel::AllRecords>(recordsImpls);
}

::ohos::data::unifiedDataChannel::AllRecords UnifiedDataImpl::GetRecord(std::shared_ptr<taiheUdmf::UnifiedRecord> in)
{
    switch (in->GetType()) {

        case taiheUdmf::FILE: {
            auto fileInnerImpl = taihe::make_holder<FileInnerImpl, ::ohos::data::unifiedDataChannel::FileInner>();
            auto fileInnerImplPtr = reinterpret_cast<FileInnerImpl*>(fileInnerImpl->GetInner());
            fileInnerImplPtr->value_ = std::static_pointer_cast<taiheUdmf::File>(in);
            return ::ohos::data::unifiedDataChannel::AllRecords::make_file(fileInnerImpl);
        }
        case taiheUdmf::FOLDER: {
            auto folderInnerImpl =
                taihe::make_holder<FolderInnerImpl, ::ohos::data::unifiedDataChannel::FolderInner>();
            auto folderInnerImplPtr = reinterpret_cast<FolderInnerImpl*>(folderInnerImpl->GetInner());
            folderInnerImplPtr->value_ = std::static_pointer_cast<taiheUdmf::Folder>(in);
            return ::ohos::data::unifiedDataChannel::AllRecords::make_folder(folderInnerImpl);
        }
        case taiheUdmf::AUDIO: {
            auto audioInnerImpl = taihe::make_holder<AudioInnerImpl, ::ohos::data::unifiedDataChannel::AudioInner>();
            auto audioInnerImplPtr = reinterpret_cast<AudioInnerImpl*>(audioInnerImpl->GetInner());
            audioInnerImplPtr->value_ = std::static_pointer_cast<taiheUdmf::Audio>(in);
            return ::ohos::data::unifiedDataChannel::AllRecords::make_audio(audioInnerImpl);
        }
        case taiheUdmf::VIDEO: {
            auto videoInnerImpl = taihe::make_holder<VideoInnerImpl, ::ohos::data::unifiedDataChannel::VideoInner>();
            auto videoInnerImplPtr = reinterpret_cast<VideoInnerImpl*>(videoInnerImpl->GetInner());
            videoInnerImplPtr->value_ = std::static_pointer_cast<taiheUdmf::Video>(in);
            return ::ohos::data::unifiedDataChannel::AllRecords::make_video(videoInnerImpl);
        }
        case taiheUdmf::IMAGE: {
            auto imageInnerImpl = taihe::make_holder<ImageInnerImpl, ::ohos::data::unifiedDataChannel::ImageInner>();
            auto imageInnerImplPtr = reinterpret_cast<ImageInnerImpl*>(imageInnerImpl->GetInner());
            imageInnerImplPtr->value_ = std::static_pointer_cast<taiheUdmf::Image>(in);
            return ::ohos::data::unifiedDataChannel::AllRecords::make_image(imageInnerImpl);
        }
        case taiheUdmf::TEXT: {
            auto textInnerImpl = taihe::make_holder<TextInnerImpl, ::ohos::data::unifiedDataChannel::TextInner>();
            auto textInnerImplPtr = reinterpret_cast<TextInnerImpl*>(textInnerImpl->GetInner());
            textInnerImplPtr->value_ = std::static_pointer_cast<taiheUdmf::Text>(in);
            return ::ohos::data::unifiedDataChannel::AllRecords::make_text(textInnerImpl);
        }
        case taiheUdmf::PLAIN_TEXT: {
            auto plainTextInnerImpl =
                taihe::make_holder<PlainTextInnerImpl, ::ohos::data::unifiedDataChannel::PlainTextInner>();
            auto plainTextInnerImplPtr = reinterpret_cast<PlainTextInnerImpl*>(plainTextInnerImpl->GetInner());
            plainTextInnerImplPtr->value_ = std::static_pointer_cast<taiheUdmf::PlainText>(in);
            return ::ohos::data::unifiedDataChannel::AllRecords::make_plainText(plainTextInnerImpl);
        }
        case taiheUdmf::HTML: {
            auto htmlInnerImpl = taihe::make_holder<HTMLInnerImpl, ::ohos::data::unifiedDataChannel::HTMLInner>();
            auto htmlInnerImplPtr = reinterpret_cast<HTMLInnerImpl*>(htmlInnerImpl->GetInner());
            htmlInnerImplPtr->value_ = std::static_pointer_cast<taiheUdmf::Html>(in);
            return ::ohos::data::unifiedDataChannel::AllRecords::make_html(htmlInnerImpl);
        }
        case taiheUdmf::HYPERLINK: {
            auto hyperlinkInnerImpl =
                taihe::make_holder<HyperlinkInnerImpl, ::ohos::data::unifiedDataChannel::HyperlinkInner>();
            auto hyperlinkInnerImplPtr = reinterpret_cast<HyperlinkInnerImpl*>(hyperlinkInnerImpl->GetInner());
            hyperlinkInnerImplPtr->value_ = std::static_pointer_cast<taiheUdmf::Link>(in);
            return ::ohos::data::unifiedDataChannel::AllRecords::make_hyperlink(hyperlinkInnerImpl);
        }
        case taiheUdmf::SYSTEM_DEFINED_RECORD: {
            auto systemDefinedRecordInnerImpl = taihe::make_holder<SystemDefinedRecordInnerImpl,
                ::ohos::data::unifiedDataChannel::SystemDefinedRecordInner>();
            auto systemDefinedRecordInnerImplPtr =
                reinterpret_cast<SystemDefinedRecordInnerImpl*>(systemDefinedRecordInnerImpl->GetInner());
            systemDefinedRecordInnerImplPtr->value_ = std::static_pointer_cast<taiheUdmf::SystemDefinedRecord>(in);
            return ::ohos::data::unifiedDataChannel::AllRecords::make_systemDefinedRecord(systemDefinedRecordInnerImpl);
        }
        case taiheUdmf::SYSTEM_DEFINED_APP_ITEM: {
            auto systemDefinedAppItemInnerImpl = taihe::make_holder<SystemDefinedAppItemInnerImpl,
                ::ohos::data::unifiedDataChannel::SystemDefinedAppItemInner>();
            auto systemDefinedAppItemInnerImplPtr =
                reinterpret_cast<SystemDefinedAppItemInnerImpl*>(systemDefinedAppItemInnerImpl->GetInner());
            systemDefinedAppItemInnerImplPtr->value_ = std::static_pointer_cast<taiheUdmf::SystemDefinedAppItem>(in);
            return ::ohos::data::unifiedDataChannel::AllRecords::make_systemDefinedAppItem(
                systemDefinedAppItemInnerImpl);
        }
        case taiheUdmf::SYSTEM_DEFINED_FORM: {
            auto systemDefinedFormInnerImpl =
                taihe::make_holder<SystemDefinedFormInnerImpl,
                ::ohos::data::unifiedDataChannel::SystemDefinedFormInner>();
            auto systemDefinedFormInnerImplPtr =
                reinterpret_cast<SystemDefinedFormInnerImpl*>(systemDefinedFormInnerImpl->GetInner());
            systemDefinedFormInnerImplPtr->value_ = std::static_pointer_cast<taiheUdmf::SystemDefinedForm>(in);
            return ::ohos::data::unifiedDataChannel::AllRecords::make_systemDefinedForm(systemDefinedFormInnerImpl);
        }
        case taiheUdmf::SYSTEM_DEFINED_PIXEL_MAP: {
            auto systemDefinedPixelMapInnerImpl = taihe::make_holder<SystemDefinedPixelMapInnerImpl,
                ::ohos::data::unifiedDataChannel::SystemDefinedPixelMapInner>();
            auto systemDefinedPixelMapInnerImplPtr =
                reinterpret_cast<SystemDefinedPixelMapInnerImpl*>(systemDefinedPixelMapInnerImpl->GetInner());
            systemDefinedPixelMapInnerImplPtr->value_ =
                std::static_pointer_cast<taiheUdmf::SystemDefinedPixelMap>(in);
            return ::ohos::data::unifiedDataChannel::AllRecords::make_systemDefinedPixelMap(
                systemDefinedPixelMapInnerImpl);
        }
        default:
            auto recordImpl = taihe::make_holder<UnifiedRecordInnerImpl,
                ::ohos::data::unifiedDataChannel::UnifiedRecordInner>();
            auto recordImplPtr = reinterpret_cast<UnifiedRecordInnerImpl*>(recordImpl->GetInner());
            recordImplPtr->value_ = std::static_pointer_cast<taiheUdmf::UnifiedRecord>(in);
            return ::ohos::data::unifiedDataChannel::AllRecords::make_unifiedRecord(recordImpl);
    }
}

int64_t UnifiedDataImpl::GetInner()
{
    return reinterpret_cast<int64_t>(this);
}

::ohos::data::unifiedDataChannel::UnifiedDataInner CreateUnifiedData()
{
    return taihe::make_holder<UnifiedDataImpl, ::ohos::data::unifiedDataChannel::UnifiedDataInner>();
}

::ohos::data::unifiedDataChannel::UnifiedDataInner CreateUnifiedDataWithParams(
    ::ohos::data::unifiedDataChannel::AllRecords const& unifiedRecord)
{
    auto unifiedData = taihe::make_holder<UnifiedDataImpl, ::ohos::data::unifiedDataChannel::UnifiedDataInner>();
    auto unifiedDataImpl = reinterpret_cast<UnifiedDataImpl*>(unifiedData->GetInner());
    switch (unifiedRecord.get_tag()) {
        case ::ohos::data::unifiedDataChannel::AllRecords::tag_t::unifiedRecord: {
            auto unifiedRecordInnerImpl = reinterpret_cast<UnifiedRecordInnerImpl*>(
                unifiedRecord.get_unifiedRecord_ref()->GetInner());
            unifiedDataImpl->value_->AddRecord(unifiedRecordInnerImpl->value_);
            break;
        }
        case ::ohos::data::unifiedDataChannel::AllRecords::tag_t::file: {
            auto fileInnerImpl = reinterpret_cast<FileInnerImpl*>(unifiedRecord.get_file_ref()->GetInner());
            unifiedDataImpl->value_->AddRecord(fileInnerImpl->value_);
            break;
        }
        case ::ohos::data::unifiedDataChannel::AllRecords::tag_t::folder: {
            auto folderInnerImpl = reinterpret_cast<FolderInnerImpl*>(unifiedRecord.get_folder_ref()->GetInner());
            unifiedDataImpl->value_->AddRecord(folderInnerImpl->value_);
            break;
        }
        case ::ohos::data::unifiedDataChannel::AllRecords::tag_t::audio: {
            auto audioInnerImpl = reinterpret_cast<AudioInnerImpl*>(unifiedRecord.get_audio_ref()->GetInner());
            unifiedDataImpl->value_->AddRecord(audioInnerImpl->value_);
            break;
        }
        case ::ohos::data::unifiedDataChannel::AllRecords::tag_t::video: {
            auto videoInnerImpl = reinterpret_cast<VideoInnerImpl*>(unifiedRecord.get_video_ref()->GetInner());
            unifiedDataImpl->value_->AddRecord(videoInnerImpl->value_);
            break;
        }
        case ::ohos::data::unifiedDataChannel::AllRecords::tag_t::image: {
            auto imageInnerImpl = reinterpret_cast<ImageInnerImpl*>(unifiedRecord.get_image_ref()->GetInner());
            unifiedDataImpl->value_->AddRecord(imageInnerImpl->value_);
            break;
        }
        case ::ohos::data::unifiedDataChannel::AllRecords::tag_t::text: {
            auto textInnerImpl = reinterpret_cast<TextInnerImpl*>(unifiedRecord.get_text_ref()->GetInner());
            unifiedDataImpl->value_->AddRecord(textInnerImpl->value_);
            break;
        }
        case ::ohos::data::unifiedDataChannel::AllRecords::tag_t::plainText: {
            auto plainTextInnerImpl = reinterpret_cast<PlainTextInnerImpl*>(
                unifiedRecord.get_plainText_ref()->GetInner());
            unifiedDataImpl->value_->AddRecord(plainTextInnerImpl->value_);
            break;
        }
        case ::ohos::data::unifiedDataChannel::AllRecords::tag_t::html: {
            auto htmlInnerImpl = reinterpret_cast<HTMLInnerImpl*>(unifiedRecord.get_html_ref()->GetInner());
            unifiedDataImpl->value_->AddRecord(htmlInnerImpl->value_);
            break;
        }
        case ::ohos::data::unifiedDataChannel::AllRecords::tag_t::hyperlink: {
            auto hyperlinkInnerImpl = reinterpret_cast<HyperlinkInnerImpl*>(
                unifiedRecord.get_hyperlink_ref()->GetInner());
            unifiedDataImpl->value_->AddRecord(hyperlinkInnerImpl->value_);
            break;
        }
        case ::ohos::data::unifiedDataChannel::AllRecords::tag_t::systemDefinedRecord: {
            auto systemDefinedRecordInnerImpl = reinterpret_cast<SystemDefinedRecordInnerImpl*>(
                unifiedRecord.get_systemDefinedRecord_ref()->GetInner());
            unifiedDataImpl->value_->AddRecord(systemDefinedRecordInnerImpl->value_);
            break;
        }
        case ::ohos::data::unifiedDataChannel::AllRecords::tag_t::systemDefinedForm: {
            auto systemDefinedFormImplInner = reinterpret_cast<SystemDefinedFormInnerImpl*>(
                unifiedRecord.get_systemDefinedForm_ref()->GetInner());
            unifiedDataImpl->value_->AddRecord(systemDefinedFormImplInner->value_);
            break;
        }
        case ::ohos::data::unifiedDataChannel::AllRecords::tag_t::systemDefinedAppItem: {
            auto systemDefinedAppItemInnerImpl = reinterpret_cast<SystemDefinedAppItemInnerImpl*>(
                unifiedRecord.get_systemDefinedAppItem_ref()->GetInner());
            unifiedDataImpl->value_->AddRecord(systemDefinedAppItemInnerImpl->value_);
            break;
        }
        case ::ohos::data::unifiedDataChannel::AllRecords::tag_t::systemDefinedPixelMap: {
            auto systemDefinedPixelMapInnerImpl = reinterpret_cast<SystemDefinedPixelMapInnerImpl*>(
                unifiedRecord.get_systemDefinedPixelMap_ref()->GetInner());
            unifiedDataImpl->value_->AddRecord(systemDefinedPixelMapInnerImpl->value_);
            break;
        }
    }
    return unifiedData;
}

TH_EXPORT_CPP_API_CreateUnifiedData(CreateUnifiedData);
TH_EXPORT_CPP_API_CreateUnifiedDataWithParams(CreateUnifiedDataWithParams);