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

#include "application_defined_record_taihe.h"
#include "audio_taihe.h"
#include "defined_appitem_taihe.h"
#include "defined_form_taihe.h"
#include "defined_pixelmap_taihe.h"
#include "defined_record_taihe.h"
#include "file_taihe.h"
#include "folder_taihe.h"
#include "html_taihe.h"
#include "hyperlink_taihe.h"
#include "image_taihe.h"
#include "logger.h"
#include "plain_text_taihe.h"
#include "taihe_common_utils.h"
#include "taihe/runtime.hpp"
#include "text_taihe.h"
#include "unified_data_taihe.h"
#include "unified_record_taihe.h"
#include "video_taihe.h"

namespace OHOS {
namespace UDMF {
UnifiedDataTaihe::UnifiedDataTaihe()
{
    this->value_ = std::make_shared<UnifiedData>();
}

void UnifiedDataTaihe::AddRecord(::taiheChannel::AllRecords const& unifiedRecord)
{
    if (this->value_ == nullptr) {
        LOG_ERROR(UDMF_ANI, "Inner value is empty.");
        return;
    }
    switch (unifiedRecord.get_tag()) {
        case ::taiheChannel::AllRecords::tag_t::unifiedRecord: {
            auto inner =
                reinterpret_cast<UnifiedRecordTaihe*>(unifiedRecord.get_unifiedRecord_ref()->GetInner());
            this->value_->AddRecord(inner->value_);
            break;
        }
        case ::taiheChannel::AllRecords::tag_t::file: {
            auto inner = reinterpret_cast<FileTaihe*>(unifiedRecord.get_file_ref()->GetInner());
            this->value_->AddRecord(inner->value_);
            break;
        }
        case ::taiheChannel::AllRecords::tag_t::folder: {
            auto inner = reinterpret_cast<FolderTaihe*>(unifiedRecord.get_folder_ref()->GetInner());
            this->value_->AddRecord(inner->value_);
            break;
        }
        case ::taiheChannel::AllRecords::tag_t::audio: {
            auto inner = reinterpret_cast<AudioTaihe*>(unifiedRecord.get_audio_ref()->GetInner());
            this->value_->AddRecord(inner->value_);
            break;
        }
        case ::taiheChannel::AllRecords::tag_t::video: {
            auto inner = reinterpret_cast<VideoTaihe*>(unifiedRecord.get_video_ref()->GetInner());
            this->value_->AddRecord(inner->value_);
            break;
        }
        case ::taiheChannel::AllRecords::tag_t::image: {
            auto inner = reinterpret_cast<ImageTaihe*>(unifiedRecord.get_image_ref()->GetInner());
            this->value_->AddRecord(inner->value_);
            break;
        }
        case ::taiheChannel::AllRecords::tag_t::text: {
            auto inner = reinterpret_cast<TextTaihe*>(unifiedRecord.get_text_ref()->GetInner());
            this->value_->AddRecord(inner->value_);
            break;
        }
        case ::taiheChannel::AllRecords::tag_t::plainText: {
            auto inner =
                reinterpret_cast<PlainTextTaihe*>(unifiedRecord.get_plainText_ref()->GetInner());
            this->value_->AddRecord(inner->value_);
            break;
        }
        case ::taiheChannel::AllRecords::tag_t::html: {
            auto inner = reinterpret_cast<HtmlTaihe*>(unifiedRecord.get_html_ref()->GetInner());
            this->value_->AddRecord(inner->value_);
            break;
        }
        case ::taiheChannel::AllRecords::tag_t::hyperlink: {
            auto inner =
                reinterpret_cast<HyperlinkTaihe*>(unifiedRecord.get_hyperlink_ref()->GetInner());
            this->value_->AddRecord(inner->value_);
            break;
        }
        case ::taiheChannel::AllRecords::tag_t::systemDefinedRecord: {
            auto inner = reinterpret_cast<SystemDefinedRecordTaihe*>(
                unifiedRecord.get_systemDefinedRecord_ref()->GetInner());
            this->value_->AddRecord(inner->value_);
            break;
        }
        case ::taiheChannel::AllRecords::tag_t::systemDefinedForm: {
            auto inner = reinterpret_cast<SystemDefinedFormTaihe*>(
                unifiedRecord.get_systemDefinedForm_ref()->GetInner());
            this->value_->AddRecord(inner->value_);
            break;
        }
        case ::taiheChannel::AllRecords::tag_t::systemDefinedAppItem: {
            auto inner = reinterpret_cast<SystemDefinedAppItemTaihe*>(
                unifiedRecord.get_systemDefinedAppItem_ref()->GetInner());
            this->value_->AddRecord(inner->value_);
            break;
        }
        case ::taiheChannel::AllRecords::tag_t::systemDefinedPixelMap: {
            auto inner = reinterpret_cast<SystemDefinedPixelMapTaihe*>(
                unifiedRecord.get_systemDefinedPixelMap_ref()->GetInner());
            this->value_->AddRecord(inner->value_);
            break;
        }
        case ::taiheChannel::AllRecords::tag_t::applicationDefinedRecord: {
            auto inner = reinterpret_cast<ApplicationDefinedRecordTaihe*>(
                unifiedRecord.get_applicationDefinedRecord_ref()->GetInner());
            this->value_->AddRecord(inner->value_);
            break;
        }
        default: {
            LOG_ERROR(UDMF_ANI, "UnifiedRecord type error.");
            taihe::set_business_error(PARAMETERSERROR, "Parameter error.");
        }
    }
}

::taihe::array<::taiheChannel::AllRecords> UnifiedDataTaihe::GetRecords()
{
    std::vector<::taiheChannel::AllRecords> recordsImpls;
    if (this->value_ == nullptr) {
        LOG_ERROR(UDMF_ANI, "Inner value is empty.");
        return ::taihe::array<::taiheChannel::AllRecords>(recordsImpls);
    }
    auto records = this->value_->GetRecords();
    for (auto &record : records) {
        recordsImpls.push_back(GetRecord(record));
    }
    return ::taihe::array<::taiheChannel::AllRecords>(recordsImpls);
}

::taiheChannel::AllRecords UnifiedDataTaihe::GetRecord(std::shared_ptr<UnifiedRecord> in)
{
    switch (in->GetType()) {
        case FILE: {
            auto fileTaihe = taihe::make_holder<FileTaihe, ::taiheChannel::FileInner>();
            auto fileTaihePtr = reinterpret_cast<FileTaihe*>(fileTaihe->GetInner());
            fileTaihePtr->value_ = std::static_pointer_cast<File>(in);
            return ::taiheChannel::AllRecords::make_file(fileTaihe);
        }
        case FOLDER: {
            auto folderTaihe = taihe::make_holder<FolderTaihe, ::taiheChannel::FolderInner>();
            auto folderTaihePtr = reinterpret_cast<FolderTaihe*>(folderTaihe->GetInner());
            folderTaihePtr->value_ = std::static_pointer_cast<Folder>(in);
            return ::taiheChannel::AllRecords::make_folder(folderTaihe);
        }
        case AUDIO: {
            auto audioTaihe = taihe::make_holder<AudioTaihe, ::taiheChannel::AudioInner>();
            auto audioTaihePtr = reinterpret_cast<AudioTaihe*>(audioTaihe->GetInner());
            audioTaihePtr->value_ = std::static_pointer_cast<Audio>(in);
            return ::taiheChannel::AllRecords::make_audio(audioTaihe);
        }
        case VIDEO: {
            auto videoTaihe = taihe::make_holder<VideoTaihe, ::taiheChannel::VideoInner>();
            auto videoTaihePtr = reinterpret_cast<VideoTaihe*>(videoTaihe->GetInner());
            videoTaihePtr->value_ = std::static_pointer_cast<Video>(in);
            return ::taiheChannel::AllRecords::make_video(videoTaihe);
        }
        case IMAGE: {
            auto imageTaihe = taihe::make_holder<ImageTaihe, ::taiheChannel::ImageInner>();
            auto imageTaihePtr = reinterpret_cast<ImageTaihe*>(imageTaihe->GetInner());
            imageTaihePtr->value_ = std::static_pointer_cast<Image>(in);
            return ::taiheChannel::AllRecords::make_image(imageTaihe);
        }
        case TEXT: {
            auto textTaihe = taihe::make_holder<TextTaihe, ::taiheChannel::TextInner>();
            auto textTaihePtr = reinterpret_cast<TextTaihe*>(textTaihe->GetInner());
            textTaihePtr->value_ = std::static_pointer_cast<Text>(in);
            return ::taiheChannel::AllRecords::make_text(textTaihe);
        }
        case PLAIN_TEXT: {
            auto plainTextTaihe = taihe::make_holder<PlainTextTaihe, ::taiheChannel::PlainTextInner>();
            auto plainTextTaihePtr = reinterpret_cast<PlainTextTaihe*>(plainTextTaihe->GetInner());
            plainTextTaihePtr->value_ = std::static_pointer_cast<PlainText>(in);
            return ::taiheChannel::AllRecords::make_plainText(plainTextTaihe);
        }
        case HTML: {
            auto htmlTaihe = taihe::make_holder<HtmlTaihe, ::taiheChannel::HTMLInner>();
            auto htmlTaihePtr = reinterpret_cast<HtmlTaihe*>(htmlTaihe->GetInner());
            htmlTaihePtr->value_ = std::static_pointer_cast<Html>(in);
            return ::taiheChannel::AllRecords::make_html(htmlTaihe);
        }
        case HYPERLINK: {
            auto hyperlinkTaihe = taihe::make_holder<HyperlinkTaihe, ::taiheChannel::HyperlinkInner>();
            auto hyperlinkTaihePtr = reinterpret_cast<HyperlinkTaihe*>(hyperlinkTaihe->GetInner());
            hyperlinkTaihePtr->value_ = std::static_pointer_cast<Link>(in);
            return ::taiheChannel::AllRecords::make_hyperlink(hyperlinkTaihe);
        }
        case SYSTEM_DEFINED_RECORD: {
            auto systemDefinedRecordTaihe =
                taihe::make_holder<SystemDefinedRecordTaihe, ::taiheChannel::SystemDefinedRecordInner>();
            auto systemDefinedRecordTaihePtr =
                reinterpret_cast<SystemDefinedRecordTaihe*>(systemDefinedRecordTaihe->GetInner());
            systemDefinedRecordTaihePtr->value_ = std::static_pointer_cast<SystemDefinedRecord>(in);
            return ::taiheChannel::AllRecords::make_systemDefinedRecord(systemDefinedRecordTaihe);
        }
        case SYSTEM_DEFINED_APP_ITEM: {
            auto systemDefinedAppItemTaihe =
                taihe::make_holder<SystemDefinedAppItemTaihe, ::taiheChannel::SystemDefinedAppItemInner>();
            auto systemDefinedAppItemTaihePtr =
                reinterpret_cast<SystemDefinedAppItemTaihe*>(systemDefinedAppItemTaihe->GetInner());
            systemDefinedAppItemTaihePtr->value_ = std::static_pointer_cast<SystemDefinedAppItem>(in);
            return ::taiheChannel::AllRecords::make_systemDefinedAppItem(systemDefinedAppItemTaihe);
        }
        case SYSTEM_DEFINED_FORM: {
            auto systemDefinedFormTaihe =
                taihe::make_holder<SystemDefinedFormTaihe, ::taiheChannel::SystemDefinedFormInner>();
            auto systemDefinedFormTaihePtr =
                reinterpret_cast<SystemDefinedFormTaihe*>(systemDefinedFormTaihe->GetInner());
            systemDefinedFormTaihePtr->value_ = std::static_pointer_cast<SystemDefinedForm>(in);
            return ::taiheChannel::AllRecords::make_systemDefinedForm(systemDefinedFormTaihe);
        }
        case SYSTEM_DEFINED_PIXEL_MAP: {
            auto systemDefinedPixelMapTaihe =
                taihe::make_holder<SystemDefinedPixelMapTaihe, ::taiheChannel::SystemDefinedPixelMapInner>();
            auto systemDefinedPixelMapTaihePtr =
                reinterpret_cast<SystemDefinedPixelMapTaihe*>(systemDefinedPixelMapTaihe->GetInner());
            systemDefinedPixelMapTaihePtr->value_ = std::static_pointer_cast<SystemDefinedPixelMap>(in);
            return ::taiheChannel::AllRecords::make_systemDefinedPixelMap(systemDefinedPixelMapTaihe);
        }
        case APPLICATION_DEFINED_RECORD: {
            auto applicationDefinedRecordTaihe =
                taihe::make_holder<ApplicationDefinedRecordTaihe, ::taiheChannel::ApplicationDefinedRecordInner>();
            auto applicationDefinedRecordTaihePtr =
                reinterpret_cast<ApplicationDefinedRecordTaihe*>(applicationDefinedRecordTaihe->GetInner());
            applicationDefinedRecordTaihePtr->value_ = std::static_pointer_cast<ApplicationDefinedRecord>(in);
            return ::taiheChannel::AllRecords::make_applicationDefinedRecord(applicationDefinedRecordTaihe);
        }
        default:
            auto recordImpl = taihe::make_holder<UnifiedRecordTaihe, ::taiheChannel::UnifiedRecordInner>();
            auto recordImplPtr = reinterpret_cast<UnifiedRecordTaihe*>(recordImpl->GetInner());
            recordImplPtr->value_ = std::static_pointer_cast<UnifiedRecord>(in);
            return ::taiheChannel::AllRecords::make_unifiedRecord(recordImpl);
    }
}

int64_t UnifiedDataTaihe::GetInner()
{
    return reinterpret_cast<int64_t>(this);
}
} // namespace UDMF
} // namespace OHOS

::taiheChannel::UnifiedDataInner CreateUnifiedData()
{
    return taihe::make_holder<OHOS::UDMF::UnifiedDataTaihe, ::taiheChannel::UnifiedDataInner>();
}

::taiheChannel::UnifiedDataInner CreateUnifiedDataWithParams(::taiheChannel::AllRecords const &unifiedRecord)
{
    auto unifiedData = taihe::make_holder<OHOS::UDMF::UnifiedDataTaihe, ::taiheChannel::UnifiedDataInner>();
    auto unifiedDataImpl = reinterpret_cast<OHOS::UDMF::UnifiedDataTaihe*>(unifiedData->GetInner());
    switch (unifiedRecord.get_tag()) {
        case ::taiheChannel::AllRecords::tag_t::unifiedRecord: {
            auto inner = reinterpret_cast<OHOS::UDMF::UnifiedRecordTaihe*>(
                unifiedRecord.get_unifiedRecord_ref()->GetInner());
            unifiedDataImpl->value_->AddRecord(inner->value_);
            break;
        }
        case ::taiheChannel::AllRecords::tag_t::file: {
            auto inner = reinterpret_cast<OHOS::UDMF::FileTaihe*>(unifiedRecord.get_file_ref()->GetInner());
            unifiedDataImpl->value_->AddRecord(inner->value_);
            break;
        }
        case ::taiheChannel::AllRecords::tag_t::folder: {
            auto inner = reinterpret_cast<OHOS::UDMF::FolderTaihe*>(unifiedRecord.get_folder_ref()->GetInner());
            unifiedDataImpl->value_->AddRecord(inner->value_);
            break;
        }
        case ::taiheChannel::AllRecords::tag_t::audio: {
            auto inner = reinterpret_cast<OHOS::UDMF::AudioTaihe*>(unifiedRecord.get_audio_ref()->GetInner());
            unifiedDataImpl->value_->AddRecord(inner->value_);
            break;
        }
        case ::taiheChannel::AllRecords::tag_t::video: {
            auto inner = reinterpret_cast<OHOS::UDMF::VideoTaihe*>(unifiedRecord.get_video_ref()->GetInner());
            unifiedDataImpl->value_->AddRecord(inner->value_);
            break;
        }
        case ::taiheChannel::AllRecords::tag_t::image: {
            auto inner = reinterpret_cast<OHOS::UDMF::ImageTaihe*>(unifiedRecord.get_image_ref()->GetInner());
            unifiedDataImpl->value_->AddRecord(inner->value_);
            break;
        }
        case ::taiheChannel::AllRecords::tag_t::text: {
            auto inner = reinterpret_cast<OHOS::UDMF::TextTaihe*>(unifiedRecord.get_text_ref()->GetInner());
            unifiedDataImpl->value_->AddRecord(inner->value_);
            break;
        }
        case ::taiheChannel::AllRecords::tag_t::plainText: {
            auto inner = reinterpret_cast<OHOS::UDMF::PlainTextTaihe*>(
                unifiedRecord.get_plainText_ref()->GetInner());
            unifiedDataImpl->value_->AddRecord(inner->value_);
            break;
        }
        case ::taiheChannel::AllRecords::tag_t::html: {
            auto inner = reinterpret_cast<OHOS::UDMF::HtmlTaihe*>(unifiedRecord.get_html_ref()->GetInner());
            unifiedDataImpl->value_->AddRecord(inner->value_);
            break;
        }
        case ::taiheChannel::AllRecords::tag_t::hyperlink: {
            auto inner = reinterpret_cast<OHOS::UDMF::HyperlinkTaihe*>(
                unifiedRecord.get_hyperlink_ref()->GetInner());
            unifiedDataImpl->value_->AddRecord(inner->value_);
            break;
        }
        case ::taiheChannel::AllRecords::tag_t::systemDefinedRecord: {
            auto inner = reinterpret_cast<OHOS::UDMF::SystemDefinedRecordTaihe*>(
                unifiedRecord.get_systemDefinedRecord_ref()->GetInner());
            unifiedDataImpl->value_->AddRecord(inner->value_);
            break;
        }
        case ::taiheChannel::AllRecords::tag_t::systemDefinedForm: {
            auto inner = reinterpret_cast<OHOS::UDMF::SystemDefinedFormTaihe*>(
                unifiedRecord.get_systemDefinedForm_ref()->GetInner());
            unifiedDataImpl->value_->AddRecord(inner->value_);
            break;
        }
        case ::taiheChannel::AllRecords::tag_t::systemDefinedAppItem: {
            auto inner = reinterpret_cast<OHOS::UDMF::SystemDefinedAppItemTaihe*>(
                unifiedRecord.get_systemDefinedAppItem_ref()->GetInner());
            unifiedDataImpl->value_->AddRecord(inner->value_);
            break;
        }
        case ::taiheChannel::AllRecords::tag_t::systemDefinedPixelMap: {
            auto inner = reinterpret_cast<OHOS::UDMF::SystemDefinedPixelMapTaihe*>(
                unifiedRecord.get_systemDefinedPixelMap_ref()->GetInner());
            unifiedDataImpl->value_->AddRecord(inner->value_);
            break;
        }
        case ::taiheChannel::AllRecords::tag_t::applicationDefinedRecord: {
            auto inner = reinterpret_cast<OHOS::UDMF::ApplicationDefinedRecordTaihe*>(
                unifiedRecord.get_applicationDefinedRecord_ref()->GetInner());
            unifiedDataImpl->value_->AddRecord(inner->value_);
            break;
        }
    }
    return unifiedData;
}

TH_EXPORT_CPP_API_CreateUnifiedData(CreateUnifiedData);
TH_EXPORT_CPP_API_CreateUnifiedDataWithParams(CreateUnifiedDataWithParams);