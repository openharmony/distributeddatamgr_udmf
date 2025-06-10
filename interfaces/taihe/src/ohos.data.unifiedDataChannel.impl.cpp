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

#include "ohos.data.unifiedDataChannel.proj.hpp"
#include "ohos.data.unifiedDataChannel.impl.hpp"
#include "audio.h"
#include "folder.h"
#include "html.h"
#include "image.h"
#include "link.h"
#include "plain_text.h"
#include "stdexcept"
#include "system_defined_appitem.h"
#include "system_defined_form.h"
#include "system_defined_pixelmap.h"
#include "system_defined_record.h"
#include "taihe_common_utils.h"
#include "taihe/runtime.hpp"
#include "text.h"
#include "udmf_client.h"
#include "unified_data.h"
#include "unified_data_taihe.h"
#include "unified_record.h"
#include "video.h"

namespace {
namespace taiheUdmf = OHOS::UDMF;
static constexpr int PARAMETERSERROR = 401;



class FolderImpl {
    public:
    FolderImpl()
    {
        this->value_ = std::make_shared<taiheUdmf::Folder>();
    }

    ::taihe::string GetType()
    {
        return ::taihe::string(taiheUdmf::UtdUtils::GetUtdIdFromUtdEnum(this->value_->GetType()));
    }

    ::ohos::data::unifiedDataChannel::ValueType GetValue()
    {
        return taiheUdmf::ConvertValueType(this->value_->GetValue());
    }

    ::taihe::string GetUri()
    {
        return ::taihe::string(this->value_->GetUri());
    }

    void SetUri(::taihe::string_view uri)
    {
        std::string uriStr(uri);
        this->value_->SetUri(uriStr);
    }

    ::taihe::optional<::taihe::map<::taihe::string, ::taihe::string>> GetDetails()
    {
        return ::taihe::optional<::taihe::map<::taihe::string, ::taihe::string>>::make(
            taiheUdmf::ConvertUDDetailsToString(this->value_->GetDetails()));
    }

    void SetDetails(::taihe::map_view<::taihe::string, ::taihe::string> details)
    {
        if (details.size() == 0) {
            return;
        }
        auto udmfDetails = taiheUdmf::ConvertUDDetails(details);
        this->value_->SetDetails(udmfDetails);
    }

    ::taihe::string GetFolderUri()
    {
        return ::taihe::string(this->value_->GetUri());
    }

    void SetFolderUri(::taihe::string_view folderUri)
    {
        std::string folderUriStr(folderUri);
        this->value_->SetUri(folderUriStr);
    }

    int64_t GetInner()
    {
        return reinterpret_cast<int64_t>(this);
    }

    std::shared_ptr<taiheUdmf::Folder> value_;
};

class AudioImpl {
    public:
    AudioImpl()
    {
        this->value_ = std::make_shared<taiheUdmf::Audio>();
    }

    ::taihe::string GetType()
    {
        return ::taihe::string(taiheUdmf::UtdUtils::GetUtdIdFromUtdEnum(this->value_->GetType()));
    }

    ::ohos::data::unifiedDataChannel::ValueType GetValue()
    {
        return taiheUdmf::ConvertValueType(this->value_->GetValue());
    }

    ::taihe::string GetUri()
    {
        return ::taihe::string(this->value_->GetUri());
    }

    void SetUri(::taihe::string_view uri)
    {
        std::string uriStr(uri);
        this->value_->SetUri(uriStr);
    }

    ::taihe::optional<::taihe::map<::taihe::string, ::taihe::string>> GetDetails()
    {
        return ::taihe::optional<::taihe::map<::taihe::string, ::taihe::string>>::make(
            taiheUdmf::ConvertUDDetailsToString(this->value_->GetDetails()));
    }

    void SetDetails(::taihe::map_view<::taihe::string, ::taihe::string> details)
    {
        if (details.size() == 0) {
            return;
        }
        auto udmfDetails = taiheUdmf::ConvertUDDetails(details);
        this->value_->SetDetails(udmfDetails);
    }

    ::taihe::string GetAudioUri()
    {
        return ::taihe::string(this->value_->GetUri());
    }

    void SetAudioUri(::taihe::string_view audioUri)
    {
        std::string audioUriStr(audioUri);
        this->value_->SetUri(audioUriStr);
    }

    int64_t GetInner()
    {
        return reinterpret_cast<int64_t>(this);
    }

    std::shared_ptr<taiheUdmf::Audio> value_;
};

class VideoImpl {
    public:
    VideoImpl()
    {
        this->value_ = std::make_shared<taiheUdmf::Video>();
    }

    ::taihe::string GetType()
    {
        return ::taihe::string(taiheUdmf::UtdUtils::GetUtdIdFromUtdEnum(this->value_->GetType()));
    }

    ::ohos::data::unifiedDataChannel::ValueType GetValue()
    {
        return taiheUdmf::ConvertValueType(this->value_->GetValue());
    }

    ::taihe::string GetUri()
    {
        return ::taihe::string(this->value_->GetUri());
    }

    void SetUri(::taihe::string_view uri)
    {
        std::string uriStr(uri);
        this->value_->SetUri(uriStr);
    }

    ::taihe::optional<::taihe::map<::taihe::string, ::taihe::string>> GetDetails()
    {
        return ::taihe::optional<::taihe::map<::taihe::string, ::taihe::string>>::make(
            taiheUdmf::ConvertUDDetailsToString(this->value_->GetDetails()));
    }

    void SetDetails(::taihe::map_view<::taihe::string, ::taihe::string> details)
    {
        if (details.size() == 0) {
            return;
        }
        auto udmfDetails = taiheUdmf::ConvertUDDetails(details);
        this->value_->SetDetails(udmfDetails);
    }

    ::taihe::string GetVideoUri()
    {
        return ::taihe::string(this->value_->GetUri());
    }

    void SetVideoUri(::taihe::string_view videoUri)
    {
        std::string videoUriStr(videoUri);
        this->value_->SetUri(videoUriStr);
    }

    int64_t GetInner()
    {
        return reinterpret_cast<int64_t>(this);
    }

    std::shared_ptr<taiheUdmf::Video> value_;
};

class ImageImpl {
    public:
    ImageImpl()
    {
        this->value_ = std::make_shared<taiheUdmf::Image>();
    }

    ::taihe::string GetType()
    {
        return ::taihe::string(taiheUdmf::UtdUtils::GetUtdIdFromUtdEnum(this->value_->GetType()));
    }

    ::ohos::data::unifiedDataChannel::ValueType GetValue()
    {
        return taiheUdmf::ConvertValueType(this->value_->GetValue());
    }

    ::taihe::string GetUri()
    {
        return ::taihe::string(this->value_->GetUri());
    }

    void SetUri(::taihe::string_view uri)
    {
        std::string uriStr(uri);
        this->value_->SetUri(uriStr);
    }

    ::taihe::optional<::taihe::map<::taihe::string, ::taihe::string>> GetDetails()
    {
        return ::taihe::optional<::taihe::map<::taihe::string, ::taihe::string>>::make(
            taiheUdmf::ConvertUDDetailsToString(this->value_->GetDetails()));
    }

    void SetDetails(::taihe::map_view<::taihe::string, ::taihe::string> details)
    {
        if (details.size() == 0) {
            return;
        }
        auto udmfDetails = taiheUdmf::ConvertUDDetails(details);
        this->value_->SetDetails(udmfDetails);
    }

    ::taihe::string GetImageUri()
    {
        return ::taihe::string(this->value_->GetUri());
    }

    void SetImageUri(::taihe::string_view imageUri)
    {
        std::string imageUriStr(imageUri);
        this->value_->SetUri(imageUriStr);
    }

    int64_t GetInner()
    {
        return reinterpret_cast<int64_t>(this);
    }

    std::shared_ptr<taiheUdmf::Image> value_;
};

class HTMLImpl {
    public:
    HTMLImpl()
    {
        this->value_ = std::make_shared<taiheUdmf::Html>();
    }

    ::taihe::string GetType()
    {
        return ::taihe::string(taiheUdmf::UtdUtils::GetUtdIdFromUtdEnum(this->value_->GetType()));
    }

    ::ohos::data::unifiedDataChannel::ValueType GetValue()
    {
        return taiheUdmf::ConvertValueType(this->value_->GetValue());
    }

    ::taihe::optional<::taihe::map<::taihe::string, ::taihe::string>> GetDetails()
    {
        return ::taihe::optional<::taihe::map<::taihe::string, ::taihe::string>>::make(
            taiheUdmf::ConvertUDDetailsToString(this->value_->GetDetails()));
    }

    void SetDetails(::taihe::map_view<::taihe::string, ::taihe::string> details)
    {
        if (details.size() == 0) {
            return;
        }
        auto udmfDetails = taiheUdmf::ConvertUDDetails(details);
        this->value_->SetDetails(udmfDetails);
    }

    void SetHtmlContent(::taihe::string_view htmlContent)
    {
        std::string content(htmlContent);
        this->value_->SetHtmlContent(content);
    }

    ::taihe::string GetHtmlContent()
    {
        return ::taihe::string(this->value_->GetHtmlContent());
    }

    void SetPlainContent(::taihe::string_view plainContent)
    {
        std::string content(plainContent);
        this->value_->SetPlainContent(content);
    }

    ::taihe::string GetPlainContent()
    {
        return ::taihe::string(this->value_->GetPlainContent());
    }

    int64_t GetInner()
    {
        return reinterpret_cast<int64_t>(this);
    }

    std::shared_ptr<taiheUdmf::Html> value_;
};

class TextImpl {
    public:
    TextImpl()
    {
        this->value_ = std::make_shared<taiheUdmf::Text>();
    }

    ::taihe::string GetType()
    {
        return ::taihe::string(taiheUdmf::UtdUtils::GetUtdIdFromUtdEnum(this->value_->GetType()));
    }

    ::ohos::data::unifiedDataChannel::ValueType GetValue()
    {
        return taiheUdmf::ConvertValueType(this->value_->GetValue());
    }

    ::taihe::optional<::taihe::map<::taihe::string, ::taihe::string>> GetDetails()
    {
        return ::taihe::optional<::taihe::map<::taihe::string, ::taihe::string>>::make(
            taiheUdmf::ConvertUDDetailsToString(this->value_->GetDetails()));
    }

    void SetDetails(::taihe::map_view<::taihe::string, ::taihe::string> details)
    {
        if (details.size() == 0) {
            return;
        }
        auto udmfDetails = taiheUdmf::ConvertUDDetails(details);
        this->value_->SetDetails(udmfDetails);
    }

    int64_t GetInner()
    {
        return reinterpret_cast<int64_t>(this);
    }

    std::shared_ptr<taiheUdmf::Text> value_;
};

class HyperlinkImpl {
    public:
    HyperlinkImpl()
    {
        this->value_ = std::make_shared<taiheUdmf::Link>();
    }

    ::taihe::string GetType()
    {
        return ::taihe::string(taiheUdmf::UtdUtils::GetUtdIdFromUtdEnum(this->value_->GetType()));
    }

    ::ohos::data::unifiedDataChannel::ValueType GetValue()
    {
        return taiheUdmf::ConvertValueType(this->value_->GetValue());
    }

    ::taihe::optional<::taihe::map<::taihe::string, ::taihe::string>> GetDetails()
    {
        return ::taihe::optional<::taihe::map<::taihe::string, ::taihe::string>>::make(
            taiheUdmf::ConvertUDDetailsToString(this->value_->GetDetails()));
    }

    void SetDetails(::taihe::map_view<::taihe::string, ::taihe::string> details)
    {
        if (details.size() == 0) {
            return;
        }
        auto udmfDetails = taiheUdmf::ConvertUDDetails(details);
        this->value_->SetDetails(udmfDetails);
    }

    void SetUrl(::taihe::string_view url)
    {
        std::string urlStr(url);
        this->value_->SetUrl(urlStr);
    }

    ::taihe::string GetUrl()
    {
        return ::taihe::string(this->value_->GetUrl());
    }

    void SetDescription(::taihe::string_view description)
    {
        std::string desc(description);
        this->value_->SetDescription(desc);
    }

    ::taihe::string GetDescription()
    {
        return ::taihe::string(this->value_->GetDescription());
    }

    int64_t GetInner()
    {
        return reinterpret_cast<int64_t>(this);
    }

    std::shared_ptr<taiheUdmf::Link> value_;
};

class PlainTextImpl {
    public:
    PlainTextImpl()
    {
        this->value_ = std::make_shared<taiheUdmf::PlainText>();
    }

    ::taihe::string GetType()
    {
        return ::taihe::string(taiheUdmf::UtdUtils::GetUtdIdFromUtdEnum(this->value_->GetType()));
    }

    ::ohos::data::unifiedDataChannel::ValueType GetValue()
    {
        return taiheUdmf::ConvertValueType(this->value_->GetValue());
    }

    ::taihe::optional<::taihe::map<::taihe::string, ::taihe::string>> GetDetails()
    {
        return ::taihe::optional<::taihe::map<::taihe::string, ::taihe::string>>::make(
            taiheUdmf::ConvertUDDetailsToString(this->value_->GetDetails()));
    }

    void SetDetails(::taihe::map_view<::taihe::string, ::taihe::string> details)
    {
        if (details.size() == 0) {
            return;
        }
        auto udmfDetails = taiheUdmf::ConvertUDDetails(details);
        this->value_->SetDetails(udmfDetails);
    }

    void SetTextContent(::taihe::string_view textContent)
    {
        std::string content(textContent);
        this->value_->SetContent(content);
    }

    ::taihe::string GetTextContent()
    {
        return ::taihe::string(this->value_->GetContent());
    }

    void SetAbstract1(::taihe::string_view abstract)
    {
        std::string abstractStr(abstract);
        this->value_->SetAbstract(abstractStr);
    }

    ::taihe::string GetAbstract1()
    {
        return ::taihe::string(this->value_->GetAbstract());
    }

    int64_t GetInner()
    {
        return reinterpret_cast<int64_t>(this);
    }

    std::shared_ptr<taiheUdmf::PlainText> value_;
};

class SystemDefinedRecordImpl {
    public:
    SystemDefinedRecordImpl()
    {
        this->value_ = std::make_shared<taiheUdmf::SystemDefinedRecord>();
    }

    ::taihe::string GetType()
    {
        return ::taihe::string(taiheUdmf::UtdUtils::GetUtdIdFromUtdEnum(this->value_->GetType()));
    }

    ::ohos::data::unifiedDataChannel::ValueType GetValue()
    {
        return taiheUdmf::ConvertValueType(this->value_->GetValue());
    }

    ::taihe::optional<::taihe::map<::taihe::string, ::ohos::data::unifiedDataChannel::DetailsValue>> GetDetails()
    {
        return ::taihe::optional<::taihe::map<::taihe::string, ::ohos::data::unifiedDataChannel::DetailsValue>>::make(
            taiheUdmf::ConvertUDDetailsToUnion(this->value_->GetDetails()));
    }

    void SetDetails(::taihe::map_view<::taihe::string, ::ohos::data::unifiedDataChannel::DetailsValue> details)
    {
        taiheUdmf::UDDetails udmfDetails = taiheUdmf::ConvertUDDetailsToUnion(details);
        this->value_->SetDetails(udmfDetails);
    }

    int64_t GetInner()
    {
        return reinterpret_cast<int64_t>(this);
    }

    std::shared_ptr<taiheUdmf::SystemDefinedRecord> value_;
};

class SystemDefinedFormImpl {
    public:
    SystemDefinedFormImpl()
    {
        this->value_ = std::make_shared<taiheUdmf::SystemDefinedForm>();
    }

    ::taihe::string GetType()
    {
        return ::taihe::string(taiheUdmf::UtdUtils::GetUtdIdFromUtdEnum(this->value_->GetType()));
    }

    ::ohos::data::unifiedDataChannel::ValueType GetValue()
    {
        return taiheUdmf::ConvertValueType(this->value_->GetValue());
    }

    ::taihe::optional<::taihe::map<::taihe::string, ::ohos::data::unifiedDataChannel::DetailsValue>> GetDetails()
    {
        return ::taihe::optional<::taihe::map<::taihe::string, ::ohos::data::unifiedDataChannel::DetailsValue>>::make(
            taiheUdmf::ConvertUDDetailsToUnion(this->value_->GetDetails()));
    }

    void SetDetails(::taihe::map_view<::taihe::string, ::ohos::data::unifiedDataChannel::DetailsValue> details)
    {
        taiheUdmf::UDDetails udmfDetails = taiheUdmf::ConvertUDDetailsToUnion(details);
        this->value_->SetDetails(udmfDetails);
    }

    double GetFormId()
    {
        return this->value_->GetFormId();
    }

    void SetFormId(double formId)
    {
        this->value_->SetFormId(formId);
    }

    ::taihe::string GetFormName()
    {
        return ::taihe::string(this->value_->GetFormName());
    }

    void SetFormName(::taihe::string_view formName)
    {
        std::string name(formName);
        this->value_->SetFormName(name);
    }

    ::taihe::string GetBundleName()
    {
        return ::taihe::string(this->value_->GetBundleName());
    }

    void SetBundleName(::taihe::string_view bundleName)
    {
        std::string name(bundleName);
        this->value_->SetBundleName(name);
    }

    ::taihe::string GetAbilityName()
    {
        return ::taihe::string(this->value_->GetAbilityName());
    }

    void SetAbilityName(::taihe::string_view abilityName)
    {
        std::string name(abilityName);
        this->value_->SetAbilityName(name);
    }

    ::taihe::string GetModule()
    {
        return ::taihe::string(this->value_->GetModule());
    }

    void SetModule(::taihe::string_view module)
    {
        std::string mudule(module);
        this->value_->SetModule(mudule);
    }

    int64_t GetInner()
    {
        return reinterpret_cast<int64_t>(this);
    }

    std::shared_ptr<taiheUdmf::SystemDefinedForm> value_;
};

class SystemDefinedAppItemImpl {
    public:
    SystemDefinedAppItemImpl()
    {
        this->value_ = std::make_shared<taiheUdmf::SystemDefinedAppItem>();
    }

    ::taihe::string GetType()
    {
        return ::taihe::string(taiheUdmf::UtdUtils::GetUtdIdFromUtdEnum(this->value_->GetType()));
    }

    ::ohos::data::unifiedDataChannel::ValueType GetValue()
    {
        return taiheUdmf::ConvertValueType(this->value_->GetValue());
    }

    ::taihe::optional<::taihe::map<::taihe::string, ::ohos::data::unifiedDataChannel::DetailsValue>> GetDetails()
    {
        return ::taihe::optional<::taihe::map<::taihe::string, ::ohos::data::unifiedDataChannel::DetailsValue>>::make(
            taiheUdmf::ConvertUDDetailsToUnion(this->value_->GetDetails()));
    }

    void SetDetails(::taihe::map_view<::taihe::string, ::ohos::data::unifiedDataChannel::DetailsValue> details)
    {
        taiheUdmf::UDDetails udmfDetails = taiheUdmf::ConvertUDDetailsToUnion(details);
        this->value_->SetDetails(udmfDetails);
    }

    ::taihe::string GetAppId()
    {
        return ::taihe::string(this->value_->GetAppId());
    }

    void SetAppId(::taihe::string_view appId)
    {
        std::string appIdStr(appId);
        this->value_->SetAppId(appIdStr);
    }

    ::taihe::string GetAppName()
    {
        return ::taihe::string(this->value_->GetAppName());
    }

    void SetAppName(::taihe::string_view appName)
    {
        std::string appNameStr(appName);
        this->value_->SetAppName(appNameStr);
    }

    ::taihe::string GetAppIconId()
    {
        return ::taihe::string(this->value_->GetAppIconId());
    }

    void SetAppIconId(::taihe::string_view appIconId)
    {
        std::string appIconIdStr(appIconId);
        this->value_->SetAppIconId(appIconIdStr);
    }

    ::taihe::string GetAppLabelId()
    {
        return ::taihe::string(this->value_->GetAppLabelId());
    }

    void SetAppLabelId(::taihe::string_view appLabelId)
    {
        std::string appLabelIdStr(appLabelId);
        this->value_->SetAppLabelId(appLabelIdStr);
    }

    ::taihe::string GetBundleName()
    {
        return ::taihe::string(this->value_->GetBundleName());
    }

    void SetBundleName(::taihe::string_view bundleName)
    {
        std::string bundleNameStr(bundleName);
        this->value_->SetBundleName(bundleNameStr);
    }

    ::taihe::string GetAbilityName()
    {
        return ::taihe::string(this->value_->GetAbilityName());
    }

    void SetAbilityName(::taihe::string_view abilityName)
    {
        std::string abilityNameStr(abilityName);
        this->value_->SetAbilityName(abilityNameStr);
    }

    int64_t GetInner()
    {
        return reinterpret_cast<int64_t>(this);
    }

    std::shared_ptr<taiheUdmf::SystemDefinedAppItem> value_;
};

class SystemDefinedPixelMapImpl {
    public:
    SystemDefinedPixelMapImpl()
    {
        this->value_ = std::make_shared<taiheUdmf::SystemDefinedPixelMap>();
    }

    ::taihe::string GetType()
    {
        return ::taihe::string(taiheUdmf::UtdUtils::GetUtdIdFromUtdEnum(this->value_->GetType()));
    }

    ::ohos::data::unifiedDataChannel::ValueType GetValue()
    {
        return taiheUdmf::ConvertValueType(this->value_->GetValue());
    }

    ::taihe::optional<::taihe::map<::taihe::string, ::ohos::data::unifiedDataChannel::DetailsValue>> GetDetails()
    {
        return ::taihe::optional<::taihe::map<::taihe::string, ::ohos::data::unifiedDataChannel::DetailsValue>>::make(
            taiheUdmf::ConvertUDDetailsToUnion(this->value_->GetDetails()));
    }

    void SetDetails(::taihe::map_view<::taihe::string, ::ohos::data::unifiedDataChannel::DetailsValue> details)
    {
        taiheUdmf::UDDetails udmfDetails = taiheUdmf::ConvertUDDetailsToUnion(details);
        this->value_->SetDetails(udmfDetails);
    }

    ::taihe::optional<::taihe::array<uint8_t>> GetRawData()
    {
        auto rawData = this->value_->GetRawData();
        return ::taihe::optional<::taihe::array<uint8_t>>::make(
            ::taihe::array<uint8_t>(rawData));
    }

    void SetRawData(::taihe::array_view<uint8_t> rawData)
    {
        if (rawData.size() == 0) {
            return;
        }
        std::vector<uint8_t> rawDataVec(rawData.begin(), rawData.end());
        this->value_->SetRawData(rawDataVec);
    }

    int64_t GetInner()
    {
        return reinterpret_cast<int64_t>(this);
    }

    std::shared_ptr<taiheUdmf::SystemDefinedPixelMap> value_;
};

::ohos::data::unifiedDataChannel::Summary CreateSummary()
{
    ::taihe::map<::taihe::string, double> summary;
    return {summary, 0};
}


::ohos::data::unifiedDataChannel::Folder CreateFolder()
{
    return taihe::make_holder<FolderImpl, ::ohos::data::unifiedDataChannel::Folder>();
}

::ohos::data::unifiedDataChannel::Audio CreateAudio()
{
    return taihe::make_holder<AudioImpl, ::ohos::data::unifiedDataChannel::Audio>();
}

::ohos::data::unifiedDataChannel::Video CreateVideo()
{
    return taihe::make_holder<VideoImpl, ::ohos::data::unifiedDataChannel::Video>();
}

::ohos::data::unifiedDataChannel::Image CreateImage()
{
    return taihe::make_holder<ImageImpl, ::ohos::data::unifiedDataChannel::Image>();
}

::ohos::data::unifiedDataChannel::Text CreateText()
{
    return taihe::make_holder<TextImpl, ::ohos::data::unifiedDataChannel::Text>();
}

::ohos::data::unifiedDataChannel::HTML CreateHtml()
{
    return taihe::make_holder<HTMLImpl, ::ohos::data::unifiedDataChannel::HTML>();
}

::ohos::data::unifiedDataChannel::Hyperlink CreateHyperlink()
{
    return taihe::make_holder<HyperlinkImpl, ::ohos::data::unifiedDataChannel::Hyperlink>();
}

::ohos::data::unifiedDataChannel::PlainText CreatePlainText()
{
    return taihe::make_holder<PlainTextImpl, ::ohos::data::unifiedDataChannel::PlainText>();
}

::ohos::data::unifiedDataChannel::SystemDefinedRecord CreateSystemDefinedRecord()
{
    return taihe::make_holder<SystemDefinedRecordImpl, ::ohos::data::unifiedDataChannel::SystemDefinedRecord>();
}

::ohos::data::unifiedDataChannel::SystemDefinedForm CreateSystemDefinedForm()
{
    return taihe::make_holder<SystemDefinedFormImpl, ::ohos::data::unifiedDataChannel::SystemDefinedForm>();
}

::ohos::data::unifiedDataChannel::SystemDefinedAppItem CreateSystemDefinedAppItem()
{
    return taihe::make_holder<SystemDefinedAppItemImpl, ::ohos::data::unifiedDataChannel::SystemDefinedAppItem>();
}

::ohos::data::unifiedDataChannel::SystemDefinedPixelMap CreateSystemDefinedPixelMap()
{
    return taihe::make_holder<SystemDefinedPixelMapImpl, ::ohos::data::unifiedDataChannel::SystemDefinedPixelMap>();
}

void InsertDataSync(::ohos::data::unifiedDataChannel::Options const& options,
    ::ohos::data::unifiedDataChannel::weak::UnifiedData data)
{
    taiheUdmf::CustomOption customOption;
    if (!options.intention.has_value()) {
        taihe::set_business_error(PARAMETERSERROR, "Parameter error.");
        return;
    }
    customOption.intention = taiheUdmf::ConvertIntention(options.intention.value());
    auto unifiedDataImpl = reinterpret_cast<UnifiedDataImpl*>(data->GetInner());
    auto unifiedData = unifiedDataImpl->value_;
    std::string key;
    auto status = taiheUdmf::UdmfClient::GetInstance().SetData(customOption, *unifiedData, key);
    if (status != taiheUdmf::E_OK) {
        taihe::set_business_error(PARAMETERSERROR, "Parameter error.");
        return;
    }
}

::taihe::array<::ohos::data::unifiedDataChannel::UnifiedData> QueryDataSync(
    ::ohos::data::unifiedDataChannel::Options const& options)
{
    taiheUdmf::QueryOption queryOption;
    std::vector<::ohos::data::unifiedDataChannel::UnifiedData> dataImpls;
    if (!options.intention.has_value() && !options.key.has_value()) {
        taihe::set_business_error(PARAMETERSERROR, "Parameter error.");
        return ::taihe::array<::ohos::data::unifiedDataChannel::UnifiedData>(dataImpls);
    }
    queryOption.intention = taiheUdmf::ConvertIntention(options.intention.value());
    queryOption.key = options.key.value();
    std::vector<taiheUdmf::UnifiedData> unifiedDataSet;
    auto status = taiheUdmf::UdmfClient::GetInstance().GetBatchData(queryOption, unifiedDataSet);
    if (status != taiheUdmf::E_OK) {
        taihe::set_business_error(PARAMETERSERROR, "Parameter error.");
        return ::taihe::array<::ohos::data::unifiedDataChannel::UnifiedData>(dataImpls);
    }
    for (auto &data : unifiedDataSet) {
        auto dataImpl = taihe::make_holder<UnifiedDataImpl, ::ohos::data::unifiedDataChannel::UnifiedData>();
        auto dataImplPtr = reinterpret_cast<UnifiedDataImpl*>(dataImpl->GetInner());
        dataImplPtr->value_ = std::make_shared<taiheUdmf::UnifiedData>(data);
        dataImpls.push_back(dataImpl);
    }
    return ::taihe::array<::ohos::data::unifiedDataChannel::UnifiedData>(dataImpls);
}
}  // namespace

TH_EXPORT_CPP_API_CreateSummary(CreateSummary);
TH_EXPORT_CPP_API_CreateFolder(CreateFolder);
TH_EXPORT_CPP_API_CreateAudio(CreateAudio);
TH_EXPORT_CPP_API_CreateVideo(CreateVideo);
TH_EXPORT_CPP_API_CreateImage(CreateImage);
TH_EXPORT_CPP_API_CreateText(CreateText);
TH_EXPORT_CPP_API_CreateHtml(CreateHtml);
TH_EXPORT_CPP_API_CreateHyperlink(CreateHyperlink);
TH_EXPORT_CPP_API_CreatePlainText(CreatePlainText);
TH_EXPORT_CPP_API_CreateSystemDefinedRecord(CreateSystemDefinedRecord);
TH_EXPORT_CPP_API_CreateSystemDefinedForm(CreateSystemDefinedForm);
TH_EXPORT_CPP_API_CreateSystemDefinedAppItem(CreateSystemDefinedAppItem);
TH_EXPORT_CPP_API_CreateSystemDefinedPixelMap(CreateSystemDefinedPixelMap);
TH_EXPORT_CPP_API_InsertDataSync(InsertDataSync);
TH_EXPORT_CPP_API_QueryDataSync(QueryDataSync);
// NOLINTEND
