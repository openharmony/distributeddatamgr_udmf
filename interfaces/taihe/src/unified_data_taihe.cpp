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
#define LOG_TAG "UDMF_DATA_TAIHE"
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
#include "logger.h"

namespace OHOS {
namespace UDMF {
UnifiedDataImpl::UnifiedDataImpl()
{
    this->value_ = std::make_shared<UnifiedData>();
}

void UnifiedDataImpl::AddRecord(::taiheChannel::AllRecords const& unifiedRecord)
{
    switch (unifiedRecord.get_tag()) {
        case ::taiheChannel::AllRecords::tag_t::unifiedRecord: {
            auto unifiedRecordInnerImpl =
                reinterpret_cast<UnifiedRecordInnerImpl*>(unifiedRecord.get_unifiedRecord_ref()->GetInner());
            this->value_->AddRecord(unifiedRecordInnerImpl->value_);
            break;
        }
        case ::taiheChannel::AllRecords::tag_t::file: {
            auto fileInnerImpl = reinterpret_cast<FileInnerImpl*>(unifiedRecord.get_file_ref()->GetInner());
            this->value_->AddRecord(fileInnerImpl->value_);
            break;
        }
        case ::taiheChannel::AllRecords::tag_t::folder: {
            auto folderInnerImpl = reinterpret_cast<FolderInnerImpl*>(unifiedRecord.get_folder_ref()->GetInner());
            this->value_->AddRecord(folderInnerImpl->value_);
            break;
        }
        case ::taiheChannel::AllRecords::tag_t::audio: {
            auto audioInnerImpl = reinterpret_cast<AudioInnerImpl*>(unifiedRecord.get_audio_ref()->GetInner());
            this->value_->AddRecord(audioInnerImpl->value_);
            break;
        }
        case ::taiheChannel::AllRecords::tag_t::video: {
            auto videoInnerImpl = reinterpret_cast<VideoInnerImpl*>(unifiedRecord.get_video_ref()->GetInner());
            this->value_->AddRecord(videoInnerImpl->value_);
            break;
        }
        case ::taiheChannel::AllRecords::tag_t::image: {
            auto imageInnerImpl = reinterpret_cast<ImageInnerImpl*>(unifiedRecord.get_image_ref()->GetInner());
            this->value_->AddRecord(imageInnerImpl->value_);
            break;
        }
        case ::taiheChannel::AllRecords::tag_t::text: {
            auto textInnerImpl = reinterpret_cast<TextInnerImpl*>(unifiedRecord.get_text_ref()->GetInner());
            this->value_->AddRecord(textInnerImpl->value_);
            break;
        }
        case ::taiheChannel::AllRecords::tag_t::plainText: {
            auto plainTextInnerImpl =
                reinterpret_cast<PlainTextInnerImpl*>(unifiedRecord.get_plainText_ref()->GetInner());
            this->value_->AddRecord(plainTextInnerImpl->value_);
            break;
        }
        case ::taiheChannel::AllRecords::tag_t::html: {
            auto htmlInnerImpl = reinterpret_cast<HTMLInnerImpl*>(unifiedRecord.get_html_ref()->GetInner());
            this->value_->AddRecord(htmlInnerImpl->value_);
            break;
        }
        case ::taiheChannel::AllRecords::tag_t::hyperlink: {
            auto hyperlinkInnerImpl =
                reinterpret_cast<HyperlinkInnerImpl*>(unifiedRecord.get_hyperlink_ref()->GetInner());
            this->value_->AddRecord(hyperlinkInnerImpl->value_);
            break;
        }
        case ::taiheChannel::AllRecords::tag_t::systemDefinedRecord: {
            auto systemDefinedRecordInnerImpl = reinterpret_cast<SystemDefinedRecordInnerImpl*>(
                unifiedRecord.get_systemDefinedRecord_ref()->GetInner());
            this->value_->AddRecord(systemDefinedRecordInnerImpl->value_);
            break;
        }
        case ::taiheChannel::AllRecords::tag_t::systemDefinedForm: {
            auto systemDefinedFormInnerImpl = reinterpret_cast<SystemDefinedFormInnerImpl*>(
                unifiedRecord.get_systemDefinedForm_ref()->GetInner());
            this->value_->AddRecord(systemDefinedFormInnerImpl->value_);
            break;
        }
        case ::taiheChannel::AllRecords::tag_t::systemDefinedAppItem: {
            auto systemDefinedAppItemInnerImpl = reinterpret_cast<SystemDefinedAppItemInnerImpl*>(
                unifiedRecord.get_systemDefinedAppItem_ref()->GetInner());
            this->value_->AddRecord(systemDefinedAppItemInnerImpl->value_);
            break;
        }
        case ::taiheChannel::AllRecords::tag_t::systemDefinedPixelMap: {
            auto systemDefinedPixelMapInnerImpl = reinterpret_cast<SystemDefinedPixelMapInnerImpl*>(
                unifiedRecord.get_systemDefinedPixelMap_ref()->GetInner());
            this->value_->AddRecord(systemDefinedPixelMapInnerImpl->value_);
            break;
        }
        default: {
            LOG_ERROR(UDMF_ANI, "UnifiedRecord type error.");
            taihe::set_business_error(PARAMETERSERROR, "Parameter error.");
        }
    }
}

::taihe::array<::taiheChannel::AllRecords> UnifiedDataImpl::GetRecords()
{
    auto records = this->value_->GetRecords();
    std::vector<::taiheChannel::AllRecords> recordsImpls;
    for (auto &record : records) {
        recordsImpls.push_back(GetRecord(record));
    }
    return ::taihe::array<::taiheChannel::AllRecords>(recordsImpls);
}

::taiheChannel::AllRecords UnifiedDataImpl::GetRecord(std::shared_ptr<UnifiedRecord> in)
{
    switch (in->GetType()) {

        case FILE: {
            auto fileInnerImpl = taihe::make_holder<FileInnerImpl, ::taiheChannel::FileInner>();
            auto fileInnerImplPtr = reinterpret_cast<FileInnerImpl*>(fileInnerImpl->GetInner());
            fileInnerImplPtr->value_ = std::static_pointer_cast<File>(in);
            return ::taiheChannel::AllRecords::make_file(fileInnerImpl);
        }
        case FOLDER: {
            auto folderInnerImpl =
                taihe::make_holder<FolderInnerImpl, ::taiheChannel::FolderInner>();
            auto folderInnerImplPtr = reinterpret_cast<FolderInnerImpl*>(folderInnerImpl->GetInner());
            folderInnerImplPtr->value_ = std::static_pointer_cast<Folder>(in);
            return ::taiheChannel::AllRecords::make_folder(folderInnerImpl);
        }
        case AUDIO: {
            auto audioInnerImpl = taihe::make_holder<AudioInnerImpl, ::taiheChannel::AudioInner>();
            auto audioInnerImplPtr = reinterpret_cast<AudioInnerImpl*>(audioInnerImpl->GetInner());
            audioInnerImplPtr->value_ = std::static_pointer_cast<Audio>(in);
            return ::taiheChannel::AllRecords::make_audio(audioInnerImpl);
        }
        case VIDEO: {
            auto videoInnerImpl = taihe::make_holder<VideoInnerImpl, ::taiheChannel::VideoInner>();
            auto videoInnerImplPtr = reinterpret_cast<VideoInnerImpl*>(videoInnerImpl->GetInner());
            videoInnerImplPtr->value_ = std::static_pointer_cast<Video>(in);
            return ::taiheChannel::AllRecords::make_video(videoInnerImpl);
        }
        case IMAGE: {
            auto imageInnerImpl = taihe::make_holder<ImageInnerImpl, ::taiheChannel::ImageInner>();
            auto imageInnerImplPtr = reinterpret_cast<ImageInnerImpl*>(imageInnerImpl->GetInner());
            imageInnerImplPtr->value_ = std::static_pointer_cast<Image>(in);
            return ::taiheChannel::AllRecords::make_image(imageInnerImpl);
        }
        case TEXT: {
            auto textInnerImpl = taihe::make_holder<TextInnerImpl, ::taiheChannel::TextInner>();
            auto textInnerImplPtr = reinterpret_cast<TextInnerImpl*>(textInnerImpl->GetInner());
            textInnerImplPtr->value_ = std::static_pointer_cast<Text>(in);
            return ::taiheChannel::AllRecords::make_text(textInnerImpl);
        }
        case PLAIN_TEXT: {
            auto plainTextInnerImpl =
                taihe::make_holder<PlainTextInnerImpl, ::taiheChannel::PlainTextInner>();
            auto plainTextInnerImplPtr = reinterpret_cast<PlainTextInnerImpl*>(plainTextInnerImpl->GetInner());
            plainTextInnerImplPtr->value_ = std::static_pointer_cast<PlainText>(in);
            return ::taiheChannel::AllRecords::make_plainText(plainTextInnerImpl);
        }
        case HTML: {
            auto htmlInnerImpl = taihe::make_holder<HTMLInnerImpl, ::taiheChannel::HTMLInner>();
            auto htmlInnerImplPtr = reinterpret_cast<HTMLInnerImpl*>(htmlInnerImpl->GetInner());
            htmlInnerImplPtr->value_ = std::static_pointer_cast<Html>(in);
            return ::taiheChannel::AllRecords::make_html(htmlInnerImpl);
        }
        case HYPERLINK: {
            auto hyperlinkInnerImpl =
                taihe::make_holder<HyperlinkInnerImpl, ::taiheChannel::HyperlinkInner>();
            auto hyperlinkInnerImplPtr = reinterpret_cast<HyperlinkInnerImpl*>(hyperlinkInnerImpl->GetInner());
            hyperlinkInnerImplPtr->value_ = std::static_pointer_cast<Link>(in);
            return ::taiheChannel::AllRecords::make_hyperlink(hyperlinkInnerImpl);
        }
        case SYSTEM_DEFINED_RECORD: {
            auto systemDefinedRecordInnerImpl = taihe::make_holder<SystemDefinedRecordInnerImpl,
                ::taiheChannel::SystemDefinedRecordInner>();
            auto systemDefinedRecordInnerImplPtr =
                reinterpret_cast<SystemDefinedRecordInnerImpl*>(systemDefinedRecordInnerImpl->GetInner());
            systemDefinedRecordInnerImplPtr->value_ = std::static_pointer_cast<SystemDefinedRecord>(in);
            return ::taiheChannel::AllRecords::make_systemDefinedRecord(systemDefinedRecordInnerImpl);
        }
        case SYSTEM_DEFINED_APP_ITEM: {
            auto systemDefinedAppItemInnerImpl = taihe::make_holder<SystemDefinedAppItemInnerImpl,
                ::taiheChannel::SystemDefinedAppItemInner>();
            auto systemDefinedAppItemInnerImplPtr =
                reinterpret_cast<SystemDefinedAppItemInnerImpl*>(systemDefinedAppItemInnerImpl->GetInner());
            systemDefinedAppItemInnerImplPtr->value_ = std::static_pointer_cast<SystemDefinedAppItem>(in);
            return ::taiheChannel::AllRecords::make_systemDefinedAppItem(
                systemDefinedAppItemInnerImpl);
        }
        case SYSTEM_DEFINED_FORM: {
            auto systemDefinedFormInnerImpl =
                taihe::make_holder<SystemDefinedFormInnerImpl,
                ::taiheChannel::SystemDefinedFormInner>();
            auto systemDefinedFormInnerImplPtr =
                reinterpret_cast<SystemDefinedFormInnerImpl*>(systemDefinedFormInnerImpl->GetInner());
            systemDefinedFormInnerImplPtr->value_ = std::static_pointer_cast<SystemDefinedForm>(in);
            return ::taiheChannel::AllRecords::make_systemDefinedForm(systemDefinedFormInnerImpl);
        }
        case SYSTEM_DEFINED_PIXEL_MAP: {
            auto systemDefinedPixelMapInnerImpl = taihe::make_holder<SystemDefinedPixelMapInnerImpl,
                ::taiheChannel::SystemDefinedPixelMapInner>();
            auto systemDefinedPixelMapInnerImplPtr =
                reinterpret_cast<SystemDefinedPixelMapInnerImpl*>(systemDefinedPixelMapInnerImpl->GetInner());
            systemDefinedPixelMapInnerImplPtr->value_ =
                std::static_pointer_cast<SystemDefinedPixelMap>(in);
            return ::taiheChannel::AllRecords::make_systemDefinedPixelMap(
                systemDefinedPixelMapInnerImpl);
        }
        default:
            auto recordImpl = taihe::make_holder<UnifiedRecordInnerImpl,
                ::taiheChannel::UnifiedRecordInner>();
            auto recordImplPtr = reinterpret_cast<UnifiedRecordInnerImpl*>(recordImpl->GetInner());
            recordImplPtr->value_ = std::static_pointer_cast<UnifiedRecord>(in);
            return ::taiheChannel::AllRecords::make_unifiedRecord(recordImpl);
    }
}

int64_t UnifiedDataImpl::GetInner()
{
    return reinterpret_cast<int64_t>(this);
}
} // namespace UDMF
} // namespace OHOS

::taiheChannel::UnifiedDataInner CreateUnifiedData()
{
    return taihe::make_holder<OHOS::UDMF::UnifiedDataImpl, ::taiheChannel::UnifiedDataInner>();
}

::taiheChannel::UnifiedDataInner CreateUnifiedDataWithParams(
    ::taiheChannel::AllRecords const& unifiedRecord)
{
    auto unifiedData = taihe::make_holder<OHOS::UDMF::UnifiedDataImpl, ::taiheChannel::UnifiedDataInner>();
    auto unifiedDataImpl = reinterpret_cast<OHOS::UDMF::UnifiedDataImpl*>(unifiedData->GetInner());
    switch (unifiedRecord.get_tag()) {
        case ::taiheChannel::AllRecords::tag_t::unifiedRecord: {
            auto unifiedRecordInnerImpl = reinterpret_cast<OHOS::UDMF::UnifiedRecordInnerImpl*>(
                unifiedRecord.get_unifiedRecord_ref()->GetInner());
            unifiedDataImpl->value_->AddRecord(unifiedRecordInnerImpl->value_);
            break;
        }
        case ::taiheChannel::AllRecords::tag_t::file: {
            auto fileInnerImpl = reinterpret_cast<OHOS::UDMF::FileInnerImpl*>(unifiedRecord.get_file_ref()->GetInner());
            unifiedDataImpl->value_->AddRecord(fileInnerImpl->value_);
            break;
        }
        case ::taiheChannel::AllRecords::tag_t::folder: {
            auto folderInnerImpl = reinterpret_cast<OHOS::UDMF::FolderInnerImpl*>(unifiedRecord.get_folder_ref()->GetInner());
            unifiedDataImpl->value_->AddRecord(folderInnerImpl->value_);
            break;
        }
        case ::taiheChannel::AllRecords::tag_t::audio: {
            auto audioInnerImpl = reinterpret_cast<OHOS::UDMF::AudioInnerImpl*>(unifiedRecord.get_audio_ref()->GetInner());
            unifiedDataImpl->value_->AddRecord(audioInnerImpl->value_);
            break;
        }
        case ::taiheChannel::AllRecords::tag_t::video: {
            auto videoInnerImpl = reinterpret_cast<OHOS::UDMF::VideoInnerImpl*>(unifiedRecord.get_video_ref()->GetInner());
            unifiedDataImpl->value_->AddRecord(videoInnerImpl->value_);
            break;
        }
        case ::taiheChannel::AllRecords::tag_t::image: {
            auto imageInnerImpl = reinterpret_cast<OHOS::UDMF::ImageInnerImpl*>(unifiedRecord.get_image_ref()->GetInner());
            unifiedDataImpl->value_->AddRecord(imageInnerImpl->value_);
            break;
        }
        case ::taiheChannel::AllRecords::tag_t::text: {
            auto textInnerImpl = reinterpret_cast<OHOS::UDMF::TextInnerImpl*>(unifiedRecord.get_text_ref()->GetInner());
            unifiedDataImpl->value_->AddRecord(textInnerImpl->value_);
            break;
        }
        case ::taiheChannel::AllRecords::tag_t::plainText: {
            auto plainTextInnerImpl = reinterpret_cast<OHOS::UDMF::PlainTextInnerImpl*>(
                unifiedRecord.get_plainText_ref()->GetInner());
            unifiedDataImpl->value_->AddRecord(plainTextInnerImpl->value_);
            break;
        }
        case ::taiheChannel::AllRecords::tag_t::html: {
            auto htmlInnerImpl = reinterpret_cast<OHOS::UDMF::HTMLInnerImpl*>(unifiedRecord.get_html_ref()->GetInner());
            unifiedDataImpl->value_->AddRecord(htmlInnerImpl->value_);
            break;
        }
        case ::taiheChannel::AllRecords::tag_t::hyperlink: {
            auto hyperlinkInnerImpl = reinterpret_cast<OHOS::UDMF::HyperlinkInnerImpl*>(
                unifiedRecord.get_hyperlink_ref()->GetInner());
            unifiedDataImpl->value_->AddRecord(hyperlinkInnerImpl->value_);
            break;
        }
        case ::taiheChannel::AllRecords::tag_t::systemDefinedRecord: {
            auto systemDefinedRecordInnerImpl = reinterpret_cast<OHOS::UDMF::SystemDefinedRecordInnerImpl*>(
                unifiedRecord.get_systemDefinedRecord_ref()->GetInner());
            unifiedDataImpl->value_->AddRecord(systemDefinedRecordInnerImpl->value_);
            break;
        }
        case ::taiheChannel::AllRecords::tag_t::systemDefinedForm: {
            auto systemDefinedFormImplInner = reinterpret_cast<OHOS::UDMF::SystemDefinedFormInnerImpl*>(
                unifiedRecord.get_systemDefinedForm_ref()->GetInner());
            unifiedDataImpl->value_->AddRecord(systemDefinedFormImplInner->value_);
            break;
        }
        case ::taiheChannel::AllRecords::tag_t::systemDefinedAppItem: {
            auto systemDefinedAppItemInnerImpl = reinterpret_cast<OHOS::UDMF::SystemDefinedAppItemInnerImpl*>(
                unifiedRecord.get_systemDefinedAppItem_ref()->GetInner());
            unifiedDataImpl->value_->AddRecord(systemDefinedAppItemInnerImpl->value_);
            break;
        }
        case ::taiheChannel::AllRecords::tag_t::systemDefinedPixelMap: {
            auto systemDefinedPixelMapInnerImpl = reinterpret_cast<OHOS::UDMF::SystemDefinedPixelMapInnerImpl*>(
                unifiedRecord.get_systemDefinedPixelMap_ref()->GetInner());
            unifiedDataImpl->value_->AddRecord(systemDefinedPixelMapInnerImpl->value_);
            break;
        }
    }
    return unifiedData;
}

TH_EXPORT_CPP_API_CreateUnifiedData(CreateUnifiedData);
TH_EXPORT_CPP_API_CreateUnifiedDataWithParams(CreateUnifiedDataWithParams);