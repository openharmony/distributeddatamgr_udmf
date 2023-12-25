/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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

#include "tlv_util.h"

namespace OHOS {
namespace TLVUtil {
template<>
bool CountBufferSize(const std::shared_ptr<UnifiedRecord> &input, TLVObject &data)
{
    if (input == nullptr) {
        return false;
    }
    data.Count(input->GetType());
    data.Count(input->GetUid());
    auto type = input->GetType();
    switch (type) {
        case UDType::TEXT: {
            auto text = static_cast<Text *>(input.get());
            if (text == nullptr) {
                return false;
            }
            data.Count(text->GetDetails());
            break;
        }
        case UDType::PLAIN_TEXT: {
            auto plainText = static_cast<PlainText *>(input.get());
            if (plainText == nullptr) {
                return false;
            }
            data.Count(plainText->GetContent());
            data.Count(plainText->GetAbstract());
            auto text = static_cast<Text *>(input.get());
            if (text == nullptr) {
                return false;
            }
            data.Count(text->GetDetails());
            break;
        }
        case UDType::HTML: {
            auto html = static_cast<Html *>(input.get());
            if (html == nullptr) {
                return false;
            }
            data.Count(html->GetHtmlContent());
            data.Count(html->GetPlainContent());
            auto text = static_cast<Text *>(input.get());
            if (text == nullptr) {
                return false;
            }
            data.Count(text->GetDetails());
            break;
        }
        case UDType::HYPERLINK: {
            auto link = static_cast<Link *>(input.get());
            if (link == nullptr) {
                return false;
            }
            data.Count(link->GetUrl());
            data.Count(link->GetDescription());
            auto text = static_cast<Text *>(input.get());
            if (text == nullptr) {
                return false;
            }
            data.Count(text->GetDetails());
            break;
        }
        case UDType::FILE: {
            auto file = static_cast<File *>(input.get());
            if (file == nullptr) {
                return false;
            }
            data.Count(file->GetUri());
            data.Count(file->GetRemoteUri());
            data.Count(file->GetDetails());
            break;
        }
        case UDType::IMAGE: {
            auto image = static_cast<Image *>(input.get());
            if (image == nullptr) {
                return false;
            }
            data.Count(image->GetUri());
            data.Count(image->GetRemoteUri());
            auto file = static_cast<File *>(input.get());
            if (file == nullptr) {
                return false;
            }
            data.Count(file->GetDetails());
            break;
        }
        case UDType::VIDEO: {
            auto video = static_cast<Video *>(input.get());
            if (video == nullptr) {
                return false;
            }
            data.Count(video->GetUri());
            data.Count(video->GetRemoteUri());
            auto file = static_cast<File *>(input.get());
            if (file == nullptr) {
                return false;
            }
            data.Count(file->GetDetails());
            break;
        }
        case UDType::AUDIO: {
            auto audio = static_cast<Audio *>(input.get());
            if (audio == nullptr) {
                return false;
            }
            data.Count(audio->GetUri());
            data.Count(audio->GetRemoteUri());
            auto file = static_cast<File *>(input.get());
            if (file == nullptr) {
                return false;
            }
            data.Count(file->GetDetails());
            break;
        }
        case UDType::FOLDER: {
            auto folder = static_cast<Folder *>(input.get());
            if (folder == nullptr) {
                return false;
            }
            data.Count(folder->GetUri());
            data.Count(folder->GetRemoteUri());
            auto file = static_cast<File *>(input.get());
            if (file == nullptr) {
                return false;
            }
            data.Count(file->GetDetails());
            break;
        }
        case UDType::SYSTEM_DEFINED_RECORD: {
            auto sdRecord = static_cast<SystemDefinedRecord *>(input.get());
            if (sdRecord == nullptr) {
                return false;
            }
            data.Count(sdRecord->GetDetails());
            break;
        }
        case UDType::SYSTEM_DEFINED_FORM: {
            auto form = static_cast<SystemDefinedForm *>(input.get());
            if (form == nullptr) {
                return false;
            }
            data.Count(form->GetFormId());
            data.Count(form->GetFormName());
            data.Count(form->GetBundleName());
            data.Count(form->GetAbilityName());
            data.Count(form->GetModule());
            auto sdRecord = static_cast<SystemDefinedRecord *>(input.get());
            if (sdRecord == nullptr) {
                return false;
            }
            data.Count(sdRecord->GetDetails());
            break;
        }
        case UDType::SYSTEM_DEFINED_APP_ITEM: {
            auto appItem = static_cast<SystemDefinedAppItem *>(input.get());
            if (appItem == nullptr) {
                return false;
            }
            data.Count(appItem->GetAppId());
            data.Count(appItem->GetAppName());
            data.Count(appItem->GetAppIconId());
            data.Count(appItem->GetAppLabelId());
            data.Count(appItem->GetBundleName());
            data.Count(appItem->GetAbilityName());
            auto sdRecord = static_cast<SystemDefinedRecord *>(input.get());
            if (sdRecord == nullptr) {
                return false;
            }
            data.Count(sdRecord->GetDetails());
            break;
        }
        case UDType::SYSTEM_DEFINED_PIXEL_MAP: {
            auto pixelMap = static_cast<SystemDefinedPixelMap *>(input.get());
            if (pixelMap == nullptr) {
                return false;
            }
            data.Count(pixelMap->GetRawData());
            auto sdRecord = static_cast<SystemDefinedRecord *>(input.get());
            if (sdRecord == nullptr) {
                return false;
            }
            data.Count(sdRecord->GetDetails());
            break;
        }
        case UDType::APPLICATION_DEFINED_RECORD: {
            auto record = static_cast<ApplicationDefinedRecord *>(input.get());
            if (record == nullptr) {
                return false;
            }
            data.Count(record->GetApplicationDefinedType());
            data.Count(record->GetRawData());
            break;
        }
        default: {
            return false;
        }
    }
    return true;
}

template<>
bool CountBufferSize(const Runtime &input, TLVObject &data)
{
    data.Count(input.key);
    data.Count(input.isPrivate);
    uint32_t size = static_cast<uint32_t>(input.privileges.size());
    data.Count(size);
    for (uint32_t i = 0; i < size; ++i) {
        data.Count(input.privileges[i]);
    }
    data.Count(static_cast<int64_t>(input.createTime));
    data.Count(static_cast<int64_t>(input.lastModifiedTime));
    data.Count(input.sourcePackage);
    data.Count(static_cast<int32_t>(input.dataStatus));
    data.Count(input.dataVersion);
    data.Count(input.createPackage);
    data.Count(input.deviceId);
    data.Count(input.recordTotalNum);
    return true;
}

template<>
bool CountBufferSize(const UnifiedData &input, TLVObject &data)
{
    int32_t size = static_cast<int32_t>(input.GetRecords().size());
    data.Count(size);
    for (auto record : input.GetRecords()) {
        if (!CountBufferSize(record, data)) {
            return false;
        }
    }
    return true;
}

template<>
bool CountBufferSize(const std::vector<UnifiedData> &input, TLVObject &data)
{
    int32_t size = static_cast<int32_t>(input.size());
    data.Count(size);
    for (auto unifiedData : input) {
        if (!CountBufferSize(unifiedData, data)) {
            return false;
        }
    }
    return true;
}

template<typename T>
bool Writing(const T &input, TLVObject &data);

template<typename T>
bool Reading(T &output, TLVObject &data);

template<>
bool Writing(const int32_t &input, TLVObject &data)
{
    return data.WriteBasic(TAG::TAG_INT32, input);
}

template<>
bool Reading(int32_t &output, TLVObject &data)
{
    return data.ReadBasic(output);
}

template<>
bool Writing(const int64_t &input, TLVObject &data)
{
    return data.WriteBasic(TAG::TAG_INT64, input);
}

template<>
bool Reading(int64_t &output, TLVObject &data)
{
    return data.ReadBasic(output);
}

template<>
bool Reading(uint32_t &output, TLVObject &data)
{
    return data.ReadBasic(output);
}

template<>
bool Writing(const uint32_t &input, TLVObject &data)
{
    return data.WriteBasic(TAG::TAG_UINT32, input);
}

template<>
bool Reading(uint64_t &output, TLVObject &data)
{
    return data.ReadBasic(output);
}

template<>
bool Writing(const uint64_t &input, TLVObject &data)
{
    return data.WriteBasic(TAG::TAG_UINT64, input);
}

template<>
bool Writing(const bool &input, TLVObject &data)
{
    return data.WriteBasic(TAG::TAG_BOOL, input);
}

template<>
bool Reading(bool &output, TLVObject &data)
{
    return data.ReadBasic(output);
}

template<>
bool Writing(const std::string &input, TLVObject &data)
{
    return data.WriteString(input);
}

template<>
bool Reading(std::string &output, TLVObject &data)
{
    return data.ReadString(output);
}

template<>
bool Writing(const std::vector<uint8_t> &input, TLVObject &data)
{
    return data.WriteVector(input);
}

template<>
bool Reading(std::vector<uint8_t> &output, TLVObject &data)
{
    return data.ReadVector(output);
}

template<>
bool Writing(const UDVariant &input, TLVObject &data)
{
    return data.WriteVariant(input);
}

template<>
bool Reading(UDVariant &output, TLVObject &data)
{
    return data.ReadVariant(output);
}

template<>
bool Writing(const UDDetails &input, TLVObject &data)
{
    return data.WriteMap(input);
}

template<>
bool Reading(UDDetails &output, TLVObject &data)
{
    return data.ReadMap(output);
}

template<>
bool Writing(const UDType &input, TLVObject &data)
{
    int32_t type = input;
    return Writing(type, data);
}

template<>
bool Reading(UDType &output, TLVObject &data)
{
    int32_t type;
    if (!Reading(type, data)) {
        return false;
    }
    if (type < UDType::ENTITY || type >= UDType::UD_BUTT) {
        return false;
    }
    output = static_cast<UDType>(type);
    return true;
}

template<>
bool Writing(const Text &input, TLVObject &data)
{
    return Writing(input.GetDetails(), data);
}

template<>
bool Reading(Text &output, TLVObject &data)
{
    UDDetails details;
    if (!Reading(details, data)) {
        return false;
    }
    output.SetDetails(details);
    return true;
}

template<>
bool Writing(const PlainText &input, TLVObject &data)
{
    if (!Writing(input.GetContent(), data)) {
        return false;
    }
    if (!Writing(input.GetAbstract(), data)) {
        return false;
    }
    return true;
}

template<>
bool Reading(PlainText &output, TLVObject &data)
{
    std::string content;
    std::string abstract;
    UDDetails details;
    if (!Reading(content, data)) {
        return false;
    }
    if (!Reading(abstract, data)) {
        return false;
    }
    if (!Reading(details, data)) {
        return false;
    }
    output.SetContent(content);
    output.SetAbstract(abstract);
    output.SetDetails(details);
    return true;
}

template<>
bool Writing(const Html &input, TLVObject &data)
{
    if (!Writing(input.GetHtmlContent(), data)) {
        return false;
    }
    if (!Writing(input.GetPlainContent(), data)) {
        return false;
    }
    return true;
}

template<>
bool Reading(Html &output, TLVObject &data)
{
    std::string htmlContent;
    std::string plainContent;
    UDDetails details;
    if (!Reading(htmlContent, data)) {
        return false;
    }
    if (!Reading(plainContent, data)) {
        return false;
    }
    if (!Reading(details, data)) {
        return false;
    }
    output.SetHtmlContent(htmlContent);
    output.SetPlainContent(plainContent);
    output.SetDetails(details);
    return true;
}

template<>
bool Writing(const Link &input, TLVObject &data)
{
    if (!Writing(input.GetUrl(), data)) {
        return false;
    }
    if (!Writing(input.GetDescription(), data)) {
        return false;
    }
    return true;
}

template<>
bool Reading(Link &output, TLVObject &data)
{
    std::string url;
    std::string description;
    UDDetails details;
    if (!Reading(url, data)) {
        return false;
    }
    if (!Reading(description, data)) {
        return false;
    }
    if (!Reading(details, data)) {
        return false;
    }
    output.SetUrl(url);
    output.SetDescription(description);
    output.SetDetails(details);
    return true;
}

template<>
bool Writing(const File &input, TLVObject &data)
{
    if (!Writing(input.GetUri(), data)) {
        return false;
    }
    if (!Writing(input.GetRemoteUri(), data)) {
        return false;
    }
    if (!Writing(input.GetDetails(), data)) {
        return false;
    }
    return true;
}

template<>
bool Reading(File &output, TLVObject &data)
{
    std::string uri;
    std::string remoteUri;
    UDDetails details;
    if (!Reading(uri, data)) {
        return false;
    }
    if (!Reading(remoteUri, data)) {
        return false;
    }
    if (!Reading(details, data)) {
        return false;
    }
    output.SetUri(uri);
    output.SetRemoteUri(remoteUri);
    output.SetDetails(details);
    return true;
}

template<>
bool Writing(const Image &input, TLVObject &data)
{
    return true;
}

template<>
bool Reading(Image &output, TLVObject &data)
{
    std::string uri;
    std::string remoteUri;
    UDDetails details;
    if (!Reading(uri, data)) {
        return false;
    }
    if (!Reading(remoteUri, data)) {
        return false;
    }
    if (!Reading(details, data)) {
        return false;
    }
    output.SetUri(uri);
    output.SetRemoteUri(remoteUri);
    output.SetDetails(details);
    return true;
}

template<>
bool Writing(const Video &input, TLVObject &data)
{
    return true;
}

template<>
bool Reading(Video &output, TLVObject &data)
{
    std::string uri;
    std::string remoteUri;
    UDDetails details;
    if (!Reading(uri, data)) {
        return false;
    }
    if (!Reading(remoteUri, data)) {
        return false;
    }
    if (!Reading(details, data)) {
        return false;
    }
    output.SetUri(uri);
    output.SetRemoteUri(remoteUri);
    output.SetDetails(details);
    return true;
}

template<>
bool Writing(const Audio &input, TLVObject &data)
{
    return true;
}

template<>
bool Reading(Audio &output, TLVObject &data)
{
    std::string uri;
    std::string remoteUri;
    UDDetails details;
    if (!Reading(uri, data)) {
        return false;
    }
    if (!Reading(remoteUri, data)) {
        return false;
    }
    if (!Reading(details, data)) {
        return false;
    }
    output.SetUri(uri);
    output.SetRemoteUri(remoteUri);
    output.SetDetails(details);
    return true;
}

template<>
bool Writing(const Folder &input, TLVObject &data)
{
    return true;
}

template<>
bool Reading(Folder &output, TLVObject &data)
{
    std::string uri;
    std::string remoteUri;
    UDDetails details;
    if (!Reading(uri, data)) {
        return false;
    }
    if (!Reading(remoteUri, data)) {
        return false;
    }
    if (!Reading(details, data)) {
        return false;
    }
    output.SetUri(uri);
    output.SetRemoteUri(remoteUri);
    output.SetDetails(details);
    return true;
}

template<>
bool Writing(const SystemDefinedRecord &input, TLVObject &data)
{
    if (!Writing(input.GetDetails(), data)) {
        return false;
    }
    return true;
}

template<>
bool Reading(SystemDefinedRecord &output, TLVObject &data)
{
    UDDetails details;
    if (!Reading(details, data)) {
        return false;
    }
    output.SetDetails(details);
    return true;
}

template<>
bool Writing(const SystemDefinedForm &input, TLVObject &data)
{
    if (!Writing(input.GetFormId(), data)) {
        return false;
    }
    if (!Writing(input.GetFormName(), data)) {
        return false;
    }
    if (!Writing(input.GetBundleName(), data)) {
        return false;
    }
    if (!Writing(input.GetAbilityName(), data)) {
        return false;
    }
    if (!Writing(input.GetModule(), data)) {
        return false;
    }
    return true;
}

template<>
bool Reading(SystemDefinedForm &output, TLVObject &data)
{
    int32_t formId;
    std::string formName;
    std::string bundleName;
    std::string abilityName;
    std::string module;
    UDDetails details;
    if (!Reading(formId, data)) {
        return false;
    }
    if (!Reading(formName, data)) {
        return false;
    }
    if (!Reading(bundleName, data)) {
        return false;
    }
    if (!Reading(abilityName, data)) {
        return false;
    }
    if (!Reading(module, data)) {
        return false;
    }
    if (!Reading(details, data)) {
        return false;
    }
    output.SetFormId(formId);
    output.SetFormName(formName);
    output.SetBundleName(bundleName);
    output.SetAbilityName(abilityName);
    output.SetModule(module);
    output.SetDetails(details);
    return true;
}

template<>
bool Writing(const SystemDefinedAppItem &input, TLVObject &data)
{
    if (!Writing(input.GetAppId(), data)) {
        return false;
    }
    if (!Writing(input.GetAppName(), data)) {
        return false;
    }
    if (!Writing(input.GetAppIconId(), data)) {
        return false;
    }
    if (!Writing(input.GetAppLabelId(), data)) {
        return false;
    }
    if (!Writing(input.GetBundleName(), data)) {
        return false;
    }
    if (!Writing(input.GetAbilityName(), data)) {
        return false;
    }
    return true;
}

template<>
bool Reading(SystemDefinedAppItem &output, TLVObject &data)
{
    std::string appId;
    std::string appName;
    std::string appIconId;
    std::string appLabelId;
    std::string bundleName;
    std::string abilityName;
    UDDetails details;
    if (!Reading(appId, data)) {
        return false;
    }
    if (!Reading(appName, data)) {
        return false;
    }
    if (!Reading(appIconId, data)) {
        return false;
    }
    if (!Reading(appLabelId, data)) {
        return false;
    }
    if (!Reading(bundleName, data)) {
        return false;
    }
    if (!Reading(abilityName, data)) {
        return false;
    }
    if (!Reading(details, data)) {
        return false;
    }
    output.SetAppId(appId);
    output.SetAppName(appName);
    output.SetAppIconId(appIconId);
    output.SetAppLabelId(appLabelId);
    output.SetBundleName(bundleName);
    output.SetAbilityName(abilityName);
    output.SetDetails(details);
    return true;
}

template<>
bool Writing(const SystemDefinedPixelMap &input, TLVObject &data)
{
    if (!Writing(input.GetRawData(), data)) {
        return false;
    }
    return true;
}

template<>
bool Reading(SystemDefinedPixelMap &output, TLVObject &data)
{
    std::vector<uint8_t> rawData;
    UDDetails details;
    if (!Reading(rawData, data)) {
        return false;
    }
    if (!Reading(details, data)) {
        return false;
    }
    output.SetRawData(rawData);
    output.SetDetails(details);
    return true;
}

template<>
bool Writing(const ApplicationDefinedRecord &input, TLVObject &data)
{
    if (!Writing(input.GetApplicationDefinedType(), data)) {
        return false;
    }
    if (!Writing(input.GetRawData(), data)) {
        return false;
    }
    return true;
}

template<>
bool Reading(ApplicationDefinedRecord &output, TLVObject &data)
{
    std::string type;
    std::vector<uint8_t> rawData;
    if (!Reading(type, data)) {
        return false;
    }
    if (!Reading(rawData, data)) {
        return false;
    }
    output.SetApplicationDefinedType(type);
    output.SetRawData(rawData);
    return true;
}

template<>
bool Writing(const std::shared_ptr<UnifiedRecord> &input, TLVObject &data)
{
    if (data.GetBuffer().size() == 0) {
        if (!CountBufferSize(input, data)) {
            return false;
        }
        data.UpdateSize();
    }

    if (!Writing(input->GetType(), data)) {
        return false;
    }
    if (!Writing(input->GetUid(), data)) {
        return false;
    }
    auto type = input->GetType();
    switch (type) {
        case UDType::TEXT: {
            auto text = static_cast<Text *>(input.get());
            if (text == nullptr) {
                return false;
            }
            return Writing(*text, data);
        }
        case UDType::PLAIN_TEXT: {
            auto plainText = static_cast<PlainText *>(input.get());
            if (plainText == nullptr) {
                return false;
            }
            if (!Writing(*plainText, data)) {
                return false;
            }
            auto text = static_cast<Text *>(input.get());
            if (text == nullptr) {
                return false;
            }
            return Writing(*text, data);
        }
        case UDType::HTML: {
            auto html = static_cast<Html *>(input.get());
            if (html == nullptr) {
                return false;
            }
            if (!Writing(*html, data)) {
                return false;
            }
            auto text = static_cast<Text *>(input.get());
            if (text == nullptr) {
                return false;
            }
            return Writing(*text, data);
        }
        case UDType::HYPERLINK: {
            auto link = static_cast<Link *>(input.get());
            if (link == nullptr) {
                return false;
            }
            if (!Writing(*link, data)) {
                return false;
            }
            auto text = static_cast<Text *>(input.get());
            if (text == nullptr) {
                return false;
            }
            return Writing(*text, data);
        }
        case UDType::FILE: {
            auto file = static_cast<File *>(input.get());
            if (file == nullptr) {
                return false;
            }
            return Writing(*file, data);
        }
        case UDType::IMAGE: {
            auto image = static_cast<Image *>(input.get());
            if (image == nullptr) {
                return false;
            }
            if (!Writing(*image, data)) {
                return false;
            }
            auto file = static_cast<File *>(input.get());
            if (file == nullptr) {
                return false;
            }
            return Writing(*file, data);
        }
        case UDType::VIDEO: {
            auto video = static_cast<Video *>(input.get());
            if (video == nullptr) {
                return false;
            }
            if (!Writing(*video, data)) {
                return false;
            }
            auto file = static_cast<File *>(input.get());
            if (file == nullptr) {
                return false;
            }
            return Writing(*file, data);
        }
        case UDType::AUDIO: {
            auto audio = static_cast<Audio *>(input.get());
            if (audio == nullptr) {
                return false;
            }
            if (!Writing(*audio, data)) {
                return false;
            }
            auto file = static_cast<File *>(input.get());
            if (file == nullptr) {
                return false;
            }
            return Writing(*file, data);
        }
        case UDType::FOLDER: {
            auto folder = static_cast<Folder *>(input.get());
            if (folder == nullptr) {
                return false;
            }
            if (!Writing(*folder, data)) {
                return false;
            }
            auto file = static_cast<File *>(input.get());
            if (file == nullptr) {
                return false;
            }
            return Writing(*file, data);
        }
        case UDType::SYSTEM_DEFINED_RECORD: {
            auto sdRecord = static_cast<SystemDefinedRecord *>(input.get());
            if (sdRecord == nullptr) {
                return false;
            }
            return Writing(*sdRecord, data);
        }
        case UDType::SYSTEM_DEFINED_FORM: {
            auto form = static_cast<SystemDefinedForm *>(input.get());
            if (form == nullptr) {
                return false;
            }
            if (!Writing(*form, data)) {
                return false;
            }
            auto sdRecord = static_cast<SystemDefinedRecord *>(input.get());
            if (sdRecord == nullptr) {
                return false;
            }
            return Writing(*sdRecord, data);
        }
        case UDType::SYSTEM_DEFINED_APP_ITEM: {
            auto appItem = static_cast<SystemDefinedAppItem *>(input.get());
            if (appItem == nullptr) {
                return false;
            }
            if (!Writing(*appItem, data)) {
                return false;
            }
            auto sdRecord = static_cast<SystemDefinedRecord *>(input.get());
            if (sdRecord == nullptr) {
                return false;
            }
            return Writing(*sdRecord, data);
        }
        case UDType::SYSTEM_DEFINED_PIXEL_MAP: {
            auto pixelMap = static_cast<SystemDefinedPixelMap *>(input.get());
            if (pixelMap == nullptr) {
                return false;
            }
            if (!Writing(*pixelMap, data)) {
                return false;
            }
            auto sdRecord = static_cast<SystemDefinedRecord *>(input.get());
            if (sdRecord == nullptr) {
                return false;
            }
            return Writing(*sdRecord, data);
        }
        case UDType::APPLICATION_DEFINED_RECORD: {
            auto record = static_cast<ApplicationDefinedRecord *>(input.get());
            if (record == nullptr) {
                return false;
            }
            return Writing(*record, data);
        }
        default: {
            return false;
        }
    }
}

template<>
bool Reading(std::shared_ptr<UnifiedRecord> &output, TLVObject &data)
{
    UDType type ;
    if (!Reading(type, data)) {
        return false;
    }
    std::string uid;
    if (!Reading(uid, data)) {
        return false;
    }
    switch (type) {
        case UDType::TEXT: {
            std::shared_ptr<Text> text = std::make_shared<Text>();
            if (!Reading(*text, data)) {
                return false;
            }
            output = text;
            break;
        }
        case UDType::PLAIN_TEXT: {
            std::shared_ptr<PlainText> plainText = std::make_shared<PlainText>();
            if (!Reading(*plainText, data)) {
                return false;
            }
            output = plainText;
            break;
        }
        case UDType::HTML: {
            std::shared_ptr<Html> html = std::make_shared<Html>();
            if (!Reading(*html, data)) {
                return false;
            }
            output = html;
            break;
        }
        case UDType::HYPERLINK: {
            std::shared_ptr<Link> link = std::make_shared<Link>();
            if (!Reading(*link, data)) {
                return false;
            }
            output = link;
            break;
        }
        case UDType::FILE: {
            std::shared_ptr<File> file = std::make_shared<File>();
            if (!Reading(*file, data)) {
                return false;
            }
            output = file;
            break;
        }
        case UDType::IMAGE: {
            std::shared_ptr<Image> image = std::make_shared<Image>();
            if (!Reading(*image, data)) {
                return false;
            }
            output = image;
            break;
        }
        case UDType::VIDEO: {
            std::shared_ptr<Video> video = std::make_shared<Video>();
            if (!Reading(*video, data)) {
                return false;
            }
            output = video;
            break;
        }
        case UDType::AUDIO: {
            std::shared_ptr<Audio> audio = std::make_shared<Audio>();
            if (!Reading(*audio, data)) {
                return false;
            }
            output = audio;
            break;
        }
        case UDType::FOLDER: {
            std::shared_ptr<Folder> folder = std::make_shared<Folder>();
            if (!Reading(*folder, data)) {
                return false;
            }
            output = folder;
            break;
        }
        case UDType::SYSTEM_DEFINED_RECORD: {
            std::shared_ptr<SystemDefinedRecord> sdRecord = std::make_shared<SystemDefinedRecord>();
            if (!Reading(*sdRecord, data)) {
                return false;
            }
            output = sdRecord;
            break;
        }
        case UDType::SYSTEM_DEFINED_FORM: {
            std::shared_ptr<SystemDefinedForm> form = std::make_shared<SystemDefinedForm>();
            if (!Reading(*form, data)) {
                return false;
            }
            output = form;
            break;
        }
        case UDType::SYSTEM_DEFINED_APP_ITEM: {
            std::shared_ptr<SystemDefinedAppItem> appItem = std::make_shared<SystemDefinedAppItem>();
            if (!Reading(*appItem, data)) {
                return false;
            }
            output = appItem;
            break;
        }
        case UDType::SYSTEM_DEFINED_PIXEL_MAP: {
            std::shared_ptr<SystemDefinedPixelMap> pixelMap = std::make_shared<SystemDefinedPixelMap>();
            if (!Reading(*pixelMap, data)) {
                return false;
            }
            output = pixelMap;
            break;
        }
        case UDType::APPLICATION_DEFINED_RECORD: {
            std::shared_ptr<ApplicationDefinedRecord> record = std::make_shared<ApplicationDefinedRecord>();
            if (!Reading(*record, data)) {
                return false;
            }
            output = record;
            break;
        }
        default: {
            return false;
        }
    }
    output->SetUid(uid);
    output->SetType(type);
    return true;
}

template<>
bool Writing(const UnifiedData &input, TLVObject &data)
{
    if (data.GetBuffer().size() == 0) {
        if (!CountBufferSize(input, data)) {
            return false;
        }
        data.UpdateSize();
    }

    int32_t size = static_cast<int32_t>(input.GetRecords().size());
    if (!Writing(size, data)) {
        return false;
    }

    for (auto record : input.GetRecords()) {
        if (!Writing(record, data)) {
            return false;
        }
    }
    return true;
}

template<>
bool Reading(UnifiedData &output, TLVObject &data)
{
    int32_t size;
    if (!Reading(size, data)) {
        return false;
    }
    while (size-- > 0) {
        std::shared_ptr<UnifiedRecord> record;
        if (!Reading(record, data)) {
            return false;
        }
        output.AddRecord(record);
    }
    return true;
}

template<>
bool Writing(const std::vector<UnifiedData> &input, TLVObject &data)
{
    if (!CountBufferSize(input, data)) {
        return false;
    }
    data.UpdateSize();

    int32_t size = static_cast<int32_t>(input.size());
    if (!Writing(size, data)) {
        return false;
    }

    for (auto unifiedData : input) {
        if (!Writing(unifiedData, data)) {
            return false;
        }
    }
    return true;
}

template<>
bool Reading(std::vector<UnifiedData> &output, TLVObject &data)
{
    int32_t size;
    if (!Reading(size, data)) {
        return false;
    }
    while (size-- > 0) {
        UnifiedData unifiedData;
        if (!Reading(unifiedData, data)) {
            return false;
        }
        output.push_back(unifiedData);
    }
    return true;
}

template<>
bool Writing(const UnifiedKey &input, TLVObject &data)
{
    if (!Writing(input.key, data)) {
        return false;
    }
    if (!Writing(input.intention, data)) {
        return false;
    }
    if (!Writing(input.bundleName, data)) {
        return false;
    }
    if (!Writing(input.groupId, data)) {
        return false;
    }
    return true;
}

template<>
bool Reading(UnifiedKey &output, TLVObject &data)
{
    std::string key;
    std::string intention;
    std::string bundleName;
    std::string groupId;
    if (!Reading(key, data)) {
        return false;
    }
    if (!Reading(intention, data)) {
        return false;
    }
    if (!Reading(bundleName, data)) {
        return false;
    }
    if (!Reading(groupId, data)) {
        return false;
    }
    output.key = key;
    output.intention = intention;
    output.bundleName = bundleName;
    output.groupId = groupId;
    return true;
}

template<>
bool Writing(const Privilege &input, TLVObject &data)
{
    if (!Writing(input.tokenId, data)) {
        return false;
    }
    if (!Writing(input.readPermission, data)) {
        return false;
    }
    if (!Writing(input.writePermission, data)) {
        return false;
    }
    return true;
}

template<>
bool Reading(Privilege &output, TLVObject &data)
{
    uint32_t tokenId;
    std::string readPermission;
    std::string writePermission;
    if (!Reading(tokenId, data)) {
        return false;
    }
    if (!Reading(readPermission, data)) {
        return false;
    }
    if (!Reading(writePermission, data)) {
        return false;
    }
    output.tokenId = tokenId;
    output.readPermission = readPermission;
    output.writePermission = writePermission;
    return true;
}

template<>
bool Writing(const DataStatus &input, TLVObject &data)
{
    int32_t status = input;
    return Writing(status, data);
}

template<>
bool Reading(DataStatus &output, TLVObject &data)
{
    int32_t status;
    if (!Reading(status, data)) {
        return false;
    }
    if (status < DataStatus::WORKING || status >= DataStatus::FADE) {
        return false;
    }
    output = static_cast<DataStatus>(status);
    return true;
}

template<>
bool Writing(const Runtime &input, TLVObject &data)
{
    (void)CountBufferSize(input, data);
    data.UpdateSize();
    if (!Writing(input.key, data)) {
        return false;
    }
    if (!Writing(input.isPrivate, data)) {
        return false;
    }
    uint32_t size = static_cast<uint32_t>(input.privileges.size());
    if (!Writing(size, data)) {
        return false;
    }
    for (uint32_t i = 0; i < size; ++i) {
        if (!Writing(input.privileges[i], data)) {
            return false;
        }
    }
    if (!Writing(static_cast<int64_t>(input.createTime), data)) {
        return false;
    }
    if (!Writing(input.sourcePackage, data)) {
        return false;
    }
    if (!Writing(input.dataStatus, data)) {
        return false;
    }
    if (!Writing(input.dataVersion, data)) {
        return false;
    }
    if (!Writing(static_cast<int64_t>(input.lastModifiedTime), data)) {
        return false;
    }
    if (!Writing(input.createPackage, data)) {
        return false;
    }
    if (!Writing(input.deviceId, data)) {
        return false;
    }
    if (!Writing(input.recordTotalNum, data)) {
        return false;
    }
    return true;
}

template<>
bool Reading(Runtime &output, TLVObject &data)
{
    UnifiedKey key;
    bool isPrivate;
    uint32_t size;
    std::vector<Privilege> privileges;
    int64_t createTime;
    std::string sourcePackage;
    DataStatus dataStatus;
    int32_t dataVersion;
    int64_t lastModifiedTime;
    std::string createPackage;
    std::string deviceId;
    uint32_t recordTotalNum;
    if (!Reading(key, data)) {
        return false;
    }
    if (!Reading(isPrivate, data)) {
        return false;
    }
    if (!Reading(size, data)) {
        return false;
    }
    for (uint32_t i = 0; i < size; ++i) {
        Privilege privilege;
        if (!Reading(privilege, data)) {
            return false;
        }
        privileges.emplace_back(privilege);
    }
    if (!Reading(createTime, data)) {
        return false;
    }
    if (!Reading(sourcePackage, data)) {
        return false;
    }
    if (!Reading(dataStatus, data)) {
        return false;
    }
    if (!Reading(dataVersion, data)) {
        return false;
    }
    if (!Reading(lastModifiedTime, data)) {
        return false;
    }
    if (!Reading(createPackage, data)) {
        return false;
    }
    if (!Reading(deviceId, data)) {
        return false;
    }
    if (!Reading(recordTotalNum, data)) {
        return false;
    }
    output.key = key;
    output.isPrivate = isPrivate;
    output.privileges = privileges;
    output.createTime = createTime;
    output.sourcePackage = sourcePackage;
    output.dataStatus = dataStatus;
    output.dataVersion = dataVersion;
    output.lastModifiedTime = lastModifiedTime;
    output.createPackage = createPackage;
    output.deviceId = deviceId;
    output.recordTotalNum = recordTotalNum;
    return true;
}
} // namespace TLVUtil
} // namespace OHOS