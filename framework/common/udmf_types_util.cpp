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

#include "udmf_types_util.h"

#include <string>

#include "logger.h"

namespace OHOS {
namespace ITypesUtil {
using namespace UDMF;
template<> bool Marshalling(const std::shared_ptr<UnifiedRecord> &input, MessageParcel &parcel)
{
    if (!ITypesUtil::Marshal(parcel, input->GetType(), input->GetUid())) {
        return false;
    }
    auto type = input->GetType();
    switch (type) {
        case TEXT: {
            auto text = static_cast<Text *>(input.get());
            if (text == nullptr) {
                return false;
            }
            return ITypesUtil::Marshal(parcel, *text);
        }
        case PLAIN_TEXT: {
            auto plainText = static_cast<PlainText *>(input.get());
            if (plainText == nullptr) {
                return false;
            }
            return ITypesUtil::Marshal(parcel, *plainText);
        }
        case HTML: {
            auto html = static_cast<Html *>(input.get());
            if (html == nullptr) {
                return false;
            }
            return ITypesUtil::Marshal(parcel, *html);
        }
        case HYPERLINK: {
            auto link = static_cast<Link *>(input.get());
            if (link == nullptr) {
                return false;
            }
            return ITypesUtil::Marshal(parcel, *link);
        }
        case FILE: {
            auto file = static_cast<File *>(input.get());
            if (file == nullptr) {
                return false;
            }
            return ITypesUtil::Marshal(parcel, *file);
        }
        case FOLDER: {
            auto folder = static_cast<Folder *>(input.get());
            if (folder == nullptr) {
                return false;
            }
            return ITypesUtil::Marshal(parcel, *folder);
        }
        case IMAGE: {
            auto image = static_cast<Image *>(input.get());
            if (image == nullptr) {
                return false;
            }
            return ITypesUtil::Marshal(parcel, *image);
        }
        case VIDEO: {
            auto video = static_cast<Video *>(input.get());
            if (video == nullptr) {
                return false;
            }
            return ITypesUtil::Marshal(parcel, *video);
        }
        case AUDIO: {
            auto audio = static_cast<Audio *>(input.get());
            if (audio == nullptr) {
                return false;
            }
            return ITypesUtil::Marshal(parcel, *audio);
        }
        case SYSTEM_DEFINED_RECORD: {
            auto sdRecord = static_cast<SystemDefinedRecord *>(input.get());
            if (sdRecord == nullptr) {
                return false;
            }
            return ITypesUtil::Marshal(parcel, *sdRecord);
        }
        case SYSTEM_DEFINED_FORM: {
            auto form = static_cast<SystemDefinedForm *>(input.get());
            if (form == nullptr) {
                return false;
            }
            return ITypesUtil::Marshal(parcel, *form);
        }
        case SYSTEM_DEFINED_APP_ITEM: {
            auto appItem = static_cast<SystemDefinedAppItem *>(input.get());
            if (appItem == nullptr) {
                return false;
            }
            return ITypesUtil::Marshal(parcel, *appItem);
        }
        case SYSTEM_DEFINED_PIXEL_MAP: {
            auto pixelMap = static_cast<SystemDefinedPixelMap *>(input.get());
            if (pixelMap == nullptr) {
                return false;
            }
            return ITypesUtil::Marshal(parcel, *pixelMap);
        }
        case APPLICATION_DEFINED_RECORD: {
            auto record = static_cast<ApplicationDefinedRecord *>(input.get());
            if (record == nullptr) {
                return false;
            }
            return ITypesUtil::Marshal(parcel, *record);
        }
        default: {
            return false;
        }
    }
}

template<> bool Unmarshalling(std::shared_ptr<UnifiedRecord> &output, MessageParcel &parcel)
{
    UDType type;
    std::string uid;
    if (!ITypesUtil::Unmarshal(parcel, type, uid)) {
        return false;
    }
    switch (type) {
        case TEXT: {
            std::shared_ptr<Text> text = std::make_shared<Text>();
            if (!ITypesUtil::Unmarshal(parcel, *text)) {
                return false;
            }
            output = text;
            break;
        }
        case PLAIN_TEXT: {
            std::shared_ptr<PlainText> plainText = std::make_shared<PlainText>();
            if (!ITypesUtil::Unmarshal(parcel, *plainText)) {
                return false;
            }
            output = plainText;
            break;
        }
        case HTML: {
            std::shared_ptr<Html> html = std::make_shared<Html>();
            if (!ITypesUtil::Unmarshal(parcel, *html)) {
                return false;
            }
            output = html;
            break;
        }
        case HYPERLINK: {
            std::shared_ptr<Link> link = std::make_shared<Link>();
            if (!ITypesUtil::Unmarshal(parcel, *link)) {
                return false;
            }
            output = link;
            break;
        }
        case FILE: {
            std::shared_ptr<File> file = std::make_shared<File>();
            if (!ITypesUtil::Unmarshal(parcel, *file)) {
                return false;
            }
            output = file;
            break;
        }
        case FOLDER: {
            std::shared_ptr<Folder> folder = std::make_shared<Folder>();
            if (!ITypesUtil::Unmarshal(parcel, *folder)) {
                return false;
            }
            output = folder;
            break;
        }
        case IMAGE: {
            std::shared_ptr<Image> image = std::make_shared<Image>();
            if (!ITypesUtil::Unmarshal(parcel, *image)) {
                return false;
            }
            output = image;
            break;
        }
        case VIDEO: {
            std::shared_ptr<Video> video = std::make_shared<Video>();
            if (!ITypesUtil::Unmarshal(parcel, *video)) {
                return false;
            }
            output = video;
            break;
        }
        case AUDIO: {
            std::shared_ptr<Audio> audio = std::make_shared<Audio>();
            if (!ITypesUtil::Unmarshal(parcel, *audio)) {
                return false;
            }
            output = audio;
            break;
        }
        case SYSTEM_DEFINED_RECORD: {
            std::shared_ptr<SystemDefinedRecord> sdRecord = std::make_shared<SystemDefinedRecord>();
            if (!ITypesUtil::Unmarshal(parcel, *sdRecord)) {
                return false;
            }
            output = sdRecord;
            break;
        }
        case SYSTEM_DEFINED_FORM: {
            std::shared_ptr<SystemDefinedForm> form = std::make_shared<SystemDefinedForm>();
            if (!ITypesUtil::Unmarshal(parcel, *form)) {
                return false;
            }
            output = form;
            break;
        }
        case SYSTEM_DEFINED_APP_ITEM: {
            std::shared_ptr<SystemDefinedAppItem> appItem = std::make_shared<SystemDefinedAppItem>();
            if (!ITypesUtil::Unmarshal(parcel, *appItem)) {
                return false;
            }
            output = appItem;
            break;
        }
        case SYSTEM_DEFINED_PIXEL_MAP: {
            std::shared_ptr<SystemDefinedPixelMap> pixelMap = std::make_shared<SystemDefinedPixelMap>();
            if (!ITypesUtil::Unmarshal(parcel, *pixelMap)) {
                return false;
            }
            output = pixelMap;
            break;
        }
        case APPLICATION_DEFINED_RECORD: {
            std::shared_ptr<ApplicationDefinedRecord> record = std::make_shared<ApplicationDefinedRecord>();
            if (!ITypesUtil::Unmarshal(parcel, *record)) {
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

template<> bool Marshalling(const UnifiedData &input, MessageParcel &parcel)
{
    return ITypesUtil::Marshal(parcel, input.GetRecords());
}

template<> bool Unmarshalling(UnifiedData &output, MessageParcel &parcel)
{
    std::vector<std::shared_ptr<UnifiedRecord>> records;
    if (!ITypesUtil::Unmarshal(parcel, records)) {
        return false;
    }
    output.SetRecords(records);
    return true;
}

template<> bool Marshalling(const Summary &input, MessageParcel &parcel)
{
    return ITypesUtil::Marshal(parcel, input.summary, input.totalSize);
}

template<> bool Unmarshalling(Summary &output, MessageParcel &parcel)
{
    return ITypesUtil::Unmarshal(parcel, output.summary, output.totalSize);
}

template<> bool Marshalling(const Privilege &input, MessageParcel &parcel)
{
    return ITypesUtil::Marshal(parcel, input.tokenId, input.pid, input.readPermission, input.writePermission);
}

template<> bool Unmarshalling(Privilege &output, MessageParcel &parcel)
{
    return ITypesUtil::Unmarshal(parcel, output.tokenId, output.pid, output.readPermission, output.writePermission);
}

template<> bool Marshalling(const CustomOption &input, MessageParcel &parcel)
{
    return ITypesUtil::Marshal(parcel, input.intention);
}

template<> bool Unmarshalling(CustomOption &output, MessageParcel &parcel)
{
    return ITypesUtil::Unmarshal(parcel, output.intention);
}

template<> bool Marshalling(const QueryOption &input, MessageParcel &parcel)
{
    return ITypesUtil::Marshal(parcel, input.key, input.intention);
}

template<> bool Unmarshalling(QueryOption &output, MessageParcel &parcel)
{
    return ITypesUtil::Unmarshal(parcel, output.key, output.intention);
}

template<> bool Marshalling(const Text &input, MessageParcel &parcel)
{
    return ITypesUtil::Marshal(parcel, input.GetDetails());
}

template<> bool Unmarshalling(Text &output, MessageParcel &parcel)
{
    UDDetails details;
    if (!ITypesUtil::Unmarshal(parcel, details)) {
        LOG_ERROR(UDMF_KITS_NAPI, "Unmarshal Text failed!");
        return false;
    }
    output.SetDetails(details);
    return true;
}

template<> bool Marshalling(const PlainText &input, MessageParcel &parcel)
{
    return ITypesUtil::Marshal(parcel, input.GetContent(), input.GetAbstract(), input.GetDetails());
}

template<> bool Unmarshalling(PlainText &output, MessageParcel &parcel)
{
    std::string content;
    std::string abstract;
    UDDetails details;
    if (!ITypesUtil::Unmarshal(parcel, content, abstract, details)) {
        LOG_ERROR(UDMF_KITS_NAPI, "Unmarshal PlainText failed!");
        return false;
    }
    output.SetContent(content);
    output.SetAbstract(abstract);
    output.SetDetails(details);
    return true;
}

template<> bool Marshalling(const Html &input, MessageParcel &parcel)
{
    return ITypesUtil::Marshal(parcel, input.GetHtmlContent(), input.GetPlainContent(), input.GetDetails());
}

template<> bool Unmarshalling(Html &output, MessageParcel &parcel)
{
    std::string htmlContent;
    std::string plainContent;
    UDDetails details;
    if (!ITypesUtil::Unmarshal(parcel, htmlContent, plainContent, details)) {
        LOG_ERROR(UDMF_FRAMEWORK, "Unmarshal Html failed!");
        return false;
    }
    output.SetHtmlContent(htmlContent);
    output.SetPlainContent(plainContent);
    output.SetDetails(details);
    return true;
}

template<> bool Marshalling(const Link &input, MessageParcel &parcel)
{
    return ITypesUtil::Marshal(parcel, input.GetUrl(), input.GetDescription(), input.GetDetails());
}

template<> bool Unmarshalling(Link &output, MessageParcel &parcel)
{
    std::string url;
    std::string description;
    UDDetails details;
    if (!ITypesUtil::Unmarshal(parcel, url, description, details)) {
        LOG_ERROR(UDMF_FRAMEWORK, "Unmarshal Link failed!");
        return false;
    }
    output.SetUrl(url);
    output.SetDescription(description);
    output.SetDetails(details);
    return true;
}

template<> bool Marshalling(const File &input, MessageParcel &parcel)
{
    return ITypesUtil::Marshal(parcel, input.GetUri(), input.GetRemoteUri(), input.GetDetails());
}

template<> bool Unmarshalling(File &output, MessageParcel &parcel)
{
    std::string uri;
    std::string remoteUri;
    UDDetails details;
    if (!ITypesUtil::Unmarshal(parcel, uri, remoteUri, details)) {
        LOG_ERROR(UDMF_FRAMEWORK, "Unmarshal File failed!");
        return false;
    }
    output.SetUri(uri);
    output.SetRemoteUri(remoteUri);
    output.SetDetails(details);
    return true;
}

template<> bool Marshalling(const Image &input, MessageParcel &parcel)
{
    return ITypesUtil::Marshal(parcel, input.GetUri(), input.GetRemoteUri(), input.GetDetails());
}

template<> bool Unmarshalling(Image &output, MessageParcel &parcel)
{
    std::string uri;
    std::string remoteUri;
    UDDetails details;
    if (!ITypesUtil::Unmarshal(parcel, uri, remoteUri, details)) {
        LOG_ERROR(UDMF_FRAMEWORK, "Unmarshal Image failed!");
        return false;
    }
    output.SetUri(uri);
    output.SetRemoteUri(remoteUri);
    output.SetDetails(details);
    return true;
}

template<> bool Marshalling(const Video &input, MessageParcel &parcel)
{
    return ITypesUtil::Marshal(parcel, input.GetUri(), input.GetRemoteUri(), input.GetDetails());
}

template<> bool Unmarshalling(Video &output, MessageParcel &parcel)
{
    std::string uri;
    std::string remoteUri;
    UDDetails details;
    if (!ITypesUtil::Unmarshal(parcel, uri, remoteUri, details)) {
        LOG_ERROR(UDMF_FRAMEWORK, "Unmarshal Video failed!");
        return false;
    }
    output.SetUri(uri);
    output.SetRemoteUri(remoteUri);
    output.SetDetails(details);
    return true;
}

template<> bool Marshalling(const Audio &input, MessageParcel &parcel)
{
    return ITypesUtil::Marshal(parcel, input.GetUri(), input.GetRemoteUri(), input.GetDetails());
}

template<> bool Unmarshalling(Audio &output, MessageParcel &parcel)
{
    std::string uri;
    std::string remoteUri;
    UDDetails details;
    if (!ITypesUtil::Unmarshal(parcel, uri, remoteUri, details)) {
        LOG_ERROR(UDMF_FRAMEWORK, "Unmarshal Audio failed!");
        return false;
    }
    output.SetUri(uri);
    output.SetRemoteUri(remoteUri);
    output.SetDetails(details);
    return true;
}

template<> bool Marshalling(const Folder &input, MessageParcel &parcel)
{
    return ITypesUtil::Marshal(parcel, input.GetUri(), input.GetRemoteUri(), input.GetDetails());
}

template<> bool Unmarshalling(Folder &output, MessageParcel &parcel)
{
    std::string uri;
    std::string remoteUri;
    UDDetails details;
    if (!ITypesUtil::Unmarshal(parcel, uri, remoteUri, details)) {
        LOG_ERROR(UDMF_FRAMEWORK, "Unmarshal Folder failed!");
        return false;
    }
    output.SetUri(uri);
    output.SetRemoteUri(remoteUri);
    output.SetDetails(details);
    return true;
}

template<> bool Marshalling(const SystemDefinedRecord &input, MessageParcel &parcel)
{
    return ITypesUtil::Marshal(parcel, input.GetDetails());
}

template<> bool Unmarshalling(SystemDefinedRecord &output, MessageParcel &parcel)
{
    UDDetails details;
    if (!ITypesUtil::Unmarshal(parcel, details)) {
        LOG_ERROR(UDMF_FRAMEWORK, "Unmarshal SystemDefinedRecord failed!");
        return false;
    }
    output.SetDetails(details);
    return true;
}

template<> bool Marshalling(const SystemDefinedForm &input, MessageParcel &parcel)
{
    return ITypesUtil::Marshal(parcel, input.GetFormId(), input.GetFormName(), input.GetBundleName(),
        input.GetAbilityName(), input.GetModule(), input.GetDetails());
}

template<> bool Unmarshalling(SystemDefinedForm &output, MessageParcel &parcel)
{
    int32_t formId;
    std::string formName;
    std::string bundleName;
    std::string abilityName;
    std::string module;
    UDDetails details;
    if (!ITypesUtil::Unmarshal(parcel, formId, formName, bundleName, abilityName, module, details)) {
        LOG_ERROR(UDMF_FRAMEWORK, "Unmarshal SystemDefinedForm failed!");
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

template<> bool Marshalling(const SystemDefinedAppItem &input, MessageParcel &parcel)
{
    return ITypesUtil::Marshal(parcel, input.GetAppId(), input.GetAppName(), input.GetAppIconId(),
        input.GetAppLabelId(), input.GetBundleName(), input.GetAbilityName(), input.GetDetails());
}

template<> bool Unmarshalling(SystemDefinedAppItem &output, MessageParcel &parcel)
{
    std::string appId;
    std::string appName;
    std::string appIconId;
    std::string appLabelId;
    std::string bundleName;
    std::string abilityName;
    UDDetails details;
    if (!ITypesUtil::Unmarshal(parcel, appId, appName, appIconId, appLabelId, bundleName, abilityName, details)) {
        LOG_ERROR(UDMF_FRAMEWORK, "Unmarshal SystemDefinedAppItem failed!");
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

template<> bool Marshalling(const SystemDefinedPixelMap &input, MessageParcel &parcel)
{
    return ITypesUtil::Marshal(parcel, input.GetRawData(), input.GetDetails());
}

template<> bool Unmarshalling(SystemDefinedPixelMap &output, MessageParcel &parcel)
{
    std::vector<uint8_t> rawData;
    UDDetails details;
    if (!ITypesUtil::Unmarshal(parcel, rawData, details)) {
        LOG_ERROR(UDMF_FRAMEWORK, "Unmarshal SystemDefinedPixelMap failed!");
        return false;
    }
    output.SetRawData(rawData);
    output.SetDetails(details);
    return true;
}

template<> bool Marshalling(const ApplicationDefinedRecord &input, MessageParcel &parcel)
{
    return ITypesUtil::Marshal(parcel, input.GetApplicationDefinedType(), input.GetRawData());
}

template<> bool Unmarshalling(ApplicationDefinedRecord &output, MessageParcel &parcel)
{
    std::string type;
    std::vector<uint8_t> rawData;
    if (!ITypesUtil::Unmarshal(parcel, type, rawData)) {
        LOG_ERROR(UDMF_KITS_NAPI, "Unmarshal ApplicationDefinedRecord failed!");
        return false;
    }
    output.SetApplicationDefinedType(type);
    output.SetRawData(rawData);
    return true;
}

template<> bool Marshalling(const UDType &input, MessageParcel &parcel)
{
    int32_t type = input;
    return ITypesUtil::Marshal(parcel, type);
}

template<> bool Unmarshalling(UDType &output, MessageParcel &parcel)
{
    int32_t type;
    if (!ITypesUtil::Unmarshal(parcel, type)) {
        LOG_ERROR(UDMF_FRAMEWORK, "Unmarshal UDType failed!");
        return false;
    }
    if (type < TEXT || type >= UD_BUTT) {
        LOG_ERROR(UDMF_FRAMEWORK, "invalid UDType!");
        return false;
    }
    output = static_cast<UDType>(type);
    return true;
}

template<> bool Marshalling(const Intention &input, MessageParcel &parcel)
{
    int32_t intention = input;
    return ITypesUtil::Marshal(parcel, intention);
}

template<> bool Unmarshalling(Intention &output, MessageParcel &parcel)
{
    int32_t intention;
    if (!ITypesUtil::Unmarshal(parcel, intention)) {
        LOG_ERROR(UDMF_FRAMEWORK, "Unmarshal Intention failed!");
        return false;
    }
    if (intention < UD_INTENTION_BASE || intention > UD_INTENTION_BUTT) {
        LOG_ERROR(UDMF_FRAMEWORK, "invalid Intention!");
        return false;
    }
    output = static_cast<Intention>(intention);
    return true;
}
} // namespace ITypesUtil
} // namespace OHOS