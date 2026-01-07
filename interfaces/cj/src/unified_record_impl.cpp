
/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "unified_record_impl.h"

#include <cstdlib>
#include <iomanip>
#include <map>
#include <string>
#include <variant>
#include <vector>

#include "ffi_remote_data.h"
#include "securec.h"
#include "unified_record_ffi.h"

#include "application_defined_record.h"
#include "audio.h"
#include "folder.h"
#include "html.h"
#include "image.h"
#include "link.h"
#include "pixel_map_impl.h"
#include "pixel_map.h"
#include "plain_text.h"
#include "system_defined_appitem.h"
#include "system_defined_form.h"
#include "system_defined_pixelmap.h"
#include "utils.h"
#include "video.h"
#include "udmf_log.h"

using namespace OHOS::FFI;
using namespace OHOS::UDMF;

namespace OHOS {
namespace UDMF {
static CArrUI8 VectorToByteArray(std::vector<uint8_t> bytes)
{
    if (bytes.size() == 0) {
        return CArrUI8 {};
    }
    uint8_t *head = static_cast<uint8_t*>(malloc(bytes.size() * sizeof(uint8_t)));
    if (head == nullptr) {
        return CArrUI8 {};
    }
    for (size_t i = 0; i < bytes.size(); i++) {
        head[i] = bytes[i];
    }
    CArrUI8 byteArray = {head, bytes.size()};
    return byteArray;
}

CJValueType CUnifiedRecord::ValueType2CJValueType(ValueType value)
{
    CJValueType cjvalue;
    if (std::holds_alternative<std::monostate>(value)) {
        cjvalue.tag = UNDEFINED;
    } else if (std::holds_alternative<nullptr_t>(value)) {
        cjvalue.tag = NULLTAG;
    } else if (auto p = std::get_if<int32_t>(&value)) {
        cjvalue.integer32 = *p;
        cjvalue.tag = INTEGER32;
    } else if (auto p = std::get_if<int64_t>(&value)) {
        cjvalue.integer64 = *p;
        cjvalue.tag = INTEGER64;
    } else if (auto p = std::get_if<double>(&value)) {
        cjvalue.dou = *p;
        cjvalue.tag = DOUBLE;
    } else if (auto p = std::get_if<bool>(&value)) {
        cjvalue.boolean = *p;
        cjvalue.tag = BOOLEAN;
    } else if (auto p = std::get_if<std::string>(&value)) {
        cjvalue.string = Utils::MallocCString(*p);
        cjvalue.tag = STRING;
    } else if (auto p = std::get_if<std::vector<uint8_t>>(&value)) {
        cjvalue.byteArray = VectorToByteArray(*p);
        cjvalue.tag = BYTEARRAY;
    } else if (auto p = std::get_if<std::shared_ptr<OHOS::Media::PixelMap>>(&value)) {
        cjvalue.pixelMapId = this->pixelMapId_;
        cjvalue.tag = PIXELMAP;
    }

    return cjvalue;
}

ValueType CUnifiedRecord::CJValueType2ValueType(CJValueType cjvalue)
{
    ValueType value;
    switch (cjvalue.tag) {
        case INTEGER32:
            value = cjvalue.integer32;
            break;
        case INTEGER64:
            value = cjvalue.integer64;
            break;
        case DOUBLE:
            value = cjvalue.dou;
            break;
        case BOOLEAN:
            value = cjvalue.boolean;
            break;
        case STRING:
            value = cjvalue.string;
            break;
        case BYTEARRAY: {
            std::vector<uint8_t> bytes = std::vector<uint8_t>();
            for (int64_t i = 0; i < cjvalue.byteArray.size; i++) {
                bytes.push_back(cjvalue.byteArray.head[i]);
            }
            value = bytes;
            break;
        }

        case PIXELMAP: {
            auto instance = FFIData::GetData<OHOS::Media::PixelMapImpl>(cjvalue.pixelMapId);
            if (instance == nullptr) {
                value = -1;
                break;
            }
            value = instance->GetRealPixelMap();
            break;
        }

        case NULLTAG: {
            value = nullptr;
            break;
        }

        case UNDEFINED: {
            value = std::monostate();
            break;
        }
        
        default:
            value = -1;
            break;
    }

    return value;
}

CUnifiedRecord::CUnifiedRecord()
{
    unifiedRecord_ = std::make_shared<UnifiedRecord>();
}

CUnifiedRecord::CUnifiedRecord(const char *type)
{
    if (!type) {
        LOGE("CUnifiedRecord failed, type is null.");
        return;
    }
    UDType utdType = APPLICATION_DEFINED_RECORD;
    if (UtdUtils::IsValidUtdId(type)) {
        utdType = static_cast<UDType>(UtdUtils::GetUtdEnumFromUtdId(type));
    }
    static const std::map<UDType, std::function<std::shared_ptr<UnifiedRecord>()>> constructors = {
        {TEXT, []() { return std::make_shared<Text>(); }},
        {PLAIN_TEXT, []() { return std::make_shared<PlainText>(); }},
        {HTML, []() { return std::make_shared<Html>(); }},
        {HYPERLINK, []() { return std::make_shared<Link>(); }},
        {FILE, []() { return std::make_shared<File>(); }},
        {IMAGE, []() { return std::make_shared<Image>(); }},
        {VIDEO, []() { return std::make_shared<Video>(); }},
        {AUDIO, []() { return std::make_shared<Audio>(); }},
        {FOLDER, []() { return std::make_shared<Folder>(); }},
        {SYSTEM_DEFINED_RECORD, []()
            { return std::make_shared<SystemDefinedRecord>(); }},
        {SYSTEM_DEFINED_APP_ITEM, []()
            { return std::make_shared<SystemDefinedAppItem>(); }},
        {SYSTEM_DEFINED_FORM, []()
            { return std::make_shared<SystemDefinedForm>(); }},
        {SYSTEM_DEFINED_PIXEL_MAP, []()
            { return std::make_shared<SystemDefinedPixelMap>(); }},
        {APPLICATION_DEFINED_RECORD, []()
            { return std::make_shared<ApplicationDefinedRecord>(); }},
    };
    auto constructor = constructors.find(utdType);
    if (constructor == constructors.end()) {
        unifiedRecord_ = std::make_shared<UnifiedRecord>(utdType);
        return;
    }
    unifiedRecord_ = constructor->second();
}

CUnifiedRecord::CUnifiedRecord(const char *type, CJValueType cjvalue)
{
    if (!type) {
        LOGE("CUnifiedRecord failed, type is null.");
        return;
    }
    UDType utdType = APPLICATION_DEFINED_RECORD;
    if (UtdUtils::IsValidUtdId(type)) {
        utdType = static_cast<UDType>(UtdUtils::GetUtdEnumFromUtdId(type));
    }
    ValueType value = CJValueType2ValueType(cjvalue);
    if (cjvalue.tag == PIXELMAP) {
        this->pixelMapId_ = cjvalue.pixelMapId;
    }
    static const std::map<UDType, std::function<std::shared_ptr<UnifiedRecord>(UDType, ValueType)>> constructors = {
        {TEXT, [](UDType type, ValueType value) { return std::make_shared<Text>(type, value); }},
        {PLAIN_TEXT, [](UDType type, ValueType value) { return std::make_shared<PlainText>(type, value); }},
        {HTML, [](UDType type, ValueType value) { return std::make_shared<Html>(type, value); }},
        {HYPERLINK, [](UDType type, ValueType value) { return std::make_shared<Link>(type, value); }},
        {FILE, [](UDType type, ValueType value) { return std::make_shared<File>(type, value); }},
        {IMAGE, [](UDType type, ValueType value) { return std::make_shared<Image>(type, value); }},
        {VIDEO, [](UDType type, ValueType value) { return std::make_shared<Video>(type, value); }},
        {AUDIO, [](UDType type, ValueType value) { return std::make_shared<Audio>(type, value); }},
        {FOLDER, [](UDType type, ValueType value) { return std::make_shared<Folder>(type, value); }},
        {SYSTEM_DEFINED_RECORD, [](UDType type, ValueType value)
            { return std::make_shared<SystemDefinedRecord>(type, value); }},
        {SYSTEM_DEFINED_APP_ITEM, [](UDType type, ValueType value)
            { return std::make_shared<SystemDefinedAppItem>(type, value); }},
        {SYSTEM_DEFINED_FORM, [](UDType type, ValueType value)
            { return std::make_shared<SystemDefinedForm>(type, value); }},
        {SYSTEM_DEFINED_PIXEL_MAP, [](UDType type, ValueType value)
            { return std::make_shared<SystemDefinedPixelMap>(type, value); }},
        {APPLICATION_DEFINED_RECORD, [](UDType type, ValueType value)
            { return std::make_shared<ApplicationDefinedRecord>(type, value); }},
    };
    auto constructor = constructors.find(utdType);
    if (constructor == constructors.end()) {
        unifiedRecord_ = std::make_shared<UnifiedRecord>(utdType, value);
        return;
    }
    unifiedRecord_ = constructor->second(utdType, value);
}

char *CUnifiedRecord::GetType()
{
    std::string ret = UtdUtils::GetUtdIdFromUtdEnum(this->unifiedRecord_->GetType());
    return Utils::MallocCString(ret);
}

CJValueType CUnifiedRecord::GetValue()
{
    ValueType value = this->unifiedRecord_->GetValue();
    CJValueType cjvalue = ValueType2CJValueType(value);
    return cjvalue;
}

const std::shared_ptr<UDMF::UnifiedRecord> &CUnifiedRecord::GetUnifiedRecord() const
{
    return unifiedRecord_;
}

char *CUnifiedRecord::GetFileUri()
{
    std::shared_ptr<UDMF::File> resFile = std::static_pointer_cast<UDMF::File>(this->unifiedRecord_);
    if (!resFile) {
        LOGE("GetFileUri failed, resFile is null.");
        return nullptr;
    }
    std::string res = resFile->GetUri();
    return Utils::MallocCString(res);
}

void CUnifiedRecord::SetFileUri(const char *uri)
{
    std::shared_ptr<UDMF::File> resFile = std::static_pointer_cast<UDMF::File>(this->unifiedRecord_);
    if (!resFile) {
        LOGE("SetFileUri failed, resFile is null.");
        return;
    }
    if (!uri) {
        LOGE("SetFileUri failed, uri is null.");
        return;
    }
    resFile->SetUri(uri);
}

CRecord CUnifiedRecord::GetFileDetails()
{
    CRecord ret = { .keys = { .head = nullptr, .size = 0 }, .values = { .head = nullptr, .size = 0 } };
    std::shared_ptr<UDMF::File> resFile = std::static_pointer_cast<UDMF::File>(this->unifiedRecord_);
    if (!resFile) {
        LOGE("GetFileDetails failed, resFile is null.");
        return ret;
    }
    OHOS::UDMF::UDDetails resDetails = resFile->GetDetails();
    std::map<std::string, std::string> params;
    for (auto it : resDetails) {
        if (std::holds_alternative<std::string>(it.second)) {
            const std::string &strValue = std::get<std::string>(it.second);
            params.emplace(it.first, strValue);
        }
    }
    char **keysHead = static_cast<char**>(malloc(sizeof(char*) * params.size()));
    if (keysHead == nullptr) {
        return ret;
    }
    char **valuesHead = static_cast<char**>(malloc(sizeof(char*) * params.size()));
    if (valuesHead == nullptr) {
        free(keysHead);
        return ret;
    }
    int64_t i = 0;
    for (auto &param : params) {
        keysHead[i] = CreateCStringFromString(param.first);
        valuesHead[i] = CreateCStringFromString(param.second);
        i++;
    }
    ret.keys.size = static_cast<int64_t>(params.size());
    ret.keys.head = keysHead;
    ret.values.size = static_cast<int64_t>(params.size());
    ret.values.head = valuesHead;
    return ret;
}

void CUnifiedRecord::SetFileDetails(const std::map<std::string, std::string> &details)
{
    std::shared_ptr<UDMF::File> resFile = std::static_pointer_cast<UDMF::File>(this->unifiedRecord_);
    if (!resFile) {
        LOGE("SetFileDetails failed, resFile is null.");
        return;
    }
    OHOS::UDMF::UDDetails udDetails;
    for (auto &param : details) {
        udDetails[param.first] = param.second;
    }
    resFile->SetDetails(udDetails);
}

char *CUnifiedRecord::GetImageUri()
{
    std::shared_ptr<UDMF::Image> resImage = std::static_pointer_cast<UDMF::Image>(this->unifiedRecord_);
    if (!resImage) {
        LOGE("GetImageUri failed, resImage is null.");
        return nullptr;
    }
    std::string res = resImage->GetUri();
    return Utils::MallocCString(res);
}

void CUnifiedRecord::SetImageUri(const char *uri)
{
    std::shared_ptr<UDMF::Image> resImage = std::static_pointer_cast<UDMF::Image>(this->unifiedRecord_);
    if (!resImage) {
        LOGE("SetImageUri failed, resImage is null.");
        return;
    }
    if (!uri) {
        LOGE("SetImageUri failed, uri is null.");
        return;
    }
    resImage->SetUri(uri);
}

char *CUnifiedRecord::GetVideoUri()
{
    std::shared_ptr<UDMF::Video> resVideo = std::static_pointer_cast<UDMF::Video>(this->unifiedRecord_);
    if (!resVideo) {
        LOGE("GetVideoUri failed, resVideo is null.");
        return nullptr;
    }
    std::string res = resVideo->GetUri();
    return Utils::MallocCString(res);
}

void CUnifiedRecord::SetVideoUri(const char *uri)
{
    std::shared_ptr<UDMF::Video> resVideo = std::static_pointer_cast<UDMF::Video>(this->unifiedRecord_);
    if (!resVideo) {
        LOGE("SetVideoUri failed, resVideo is null.");
        return;
    }
    if (!uri) {
        LOGE("SetVideoUri failed, uri is null.");
        return;
    }
    resVideo->SetUri(uri);
}

CRecord CUnifiedRecord::GetTextDetails()
{
    CRecord ret = { .keys = { .head = nullptr, .size = 0 }, .values = { .head = nullptr, .size = 0 } };
    std::shared_ptr<UDMF::Text> resText = std::static_pointer_cast<UDMF::Text>(this->unifiedRecord_);
    if (!resText) {
        LOGE("GetTextDetails failed, resText is null.");
        return ret;
    }
    OHOS::UDMF::UDDetails resDetails = resText->GetDetails();
    std::map<std::string, std::string> params;
    for (auto it : resDetails) {
        if (std::holds_alternative<std::string>(it.second)) {
            const std::string &strValue = std::get<std::string>(it.second);
            params.emplace(it.first, strValue);
        }
    }
    char **keysHead = static_cast<char**>(malloc(sizeof(char*) * params.size()));
    if (keysHead == nullptr) {
        return ret;
    }
    char **valuesHead = static_cast<char**>(malloc(sizeof(char*) * params.size()));
    if (valuesHead == nullptr) {
        free(keysHead);
        return ret;
    }
    int64_t i = 0;
    for (auto &param : params) {
        keysHead[i] = CreateCStringFromString(param.first);
        valuesHead[i] = CreateCStringFromString(param.second);
        i++;
    }
    ret.keys.size = static_cast<int64_t>(params.size());
    ret.keys.head = keysHead;
    ret.values.size = static_cast<int64_t>(params.size());
    ret.values.head = valuesHead;
    return ret;
}

void CUnifiedRecord::SetTextDetails(const std::map<std::string, std::string> &details)
{
    std::shared_ptr<UDMF::Text> resText = std::static_pointer_cast<UDMF::Text>(this->unifiedRecord_);
    if (!resText) {
        LOGE("SetTextDetails failed, resText is null.");
        return;
    }
    OHOS::UDMF::UDDetails udDetails;
    for (auto &param : details) {
        udDetails[param.first] = param.second;
    }
    resText->SetDetails(udDetails);
}

char *CUnifiedRecord::GetHyperLinkUrl()
{
    std::shared_ptr<UDMF::Link> resLink = std::static_pointer_cast<UDMF::Link>(this->unifiedRecord_);
    if (!resLink) {
        LOGE("GetHyperLinkUrl failed, resLink is null.");
        return nullptr;
    }
    std::string res = resLink->GetUrl();
    return Utils::MallocCString(res);
}

void CUnifiedRecord::SetHyperLinkUrl(const char *url)
{
    std::shared_ptr<UDMF::Link> resLink = std::static_pointer_cast<UDMF::Link>(this->unifiedRecord_);
    if (!resLink) {
        LOGE("SetHyperLinkUrl failed, resLink is null.");
        return;
    }
    if (!url) {
        LOGE("SetHyperLinkUrl failed, url is null.");
        return;
    }
    resLink->SetUrl(url);
}

char *CUnifiedRecord::GetHyperLinkDescription()
{
    std::shared_ptr<UDMF::Link> resLink = std::static_pointer_cast<UDMF::Link>(this->unifiedRecord_);
    if (!resLink) {
        LOGE("GetHyperLinkDescription failed, resLink is null.");
        return nullptr;
    }
    std::string res = resLink->GetDescription();
    return Utils::MallocCString(res);
}

void CUnifiedRecord::SetHyperLinkDescription(const char *description)
{
    std::shared_ptr<UDMF::Link> resLink = std::static_pointer_cast<UDMF::Link>(this->unifiedRecord_);
    if (!resLink) {
        LOGE("SetHyperLinkDescription failed, resLink is null.");
        return;
    }
    if (!description) {
        LOGE("SetHyperLinkDescription failed, description is null.");
        return;
    }
    resLink->SetDescription(description);
}

char *CUnifiedRecord::GetPlainTextContent()
{
    std::shared_ptr<UDMF::PlainText> resText = std::static_pointer_cast<UDMF::PlainText>(this->unifiedRecord_);
    if (!resText) {
        LOGE("GetPlainTextContent failed, resText is null.");
        return nullptr;
    }
    std::string res = resText->GetContent();
    return Utils::MallocCString(res);
}

void CUnifiedRecord::SetPlainTextContent(const char *text)
{
    std::shared_ptr<UDMF::PlainText> resText = std::static_pointer_cast<UDMF::PlainText>(this->unifiedRecord_);
    if (!resText) {
        LOGE("SetPlainTextContent failed, resText is null.");
        return;
    }
    if (!text) {
        LOGE("SetPlainTextContent failed, text is null.");
        return;
    }
    resText->SetContent(text);
}

char *CUnifiedRecord::GetPlainTextAbstract()
{
    std::shared_ptr<UDMF::PlainText> resText = std::static_pointer_cast<UDMF::PlainText>(this->unifiedRecord_);
    if (!resText) {
        LOGE("GetPlainTextAbstract failed, resText is null.");
        return nullptr;
    }
    std::string res = resText->GetAbstract();
    return Utils::MallocCString(res);
}

void CUnifiedRecord::SetPlainTextAbstract(const char *abstr)
{
    std::shared_ptr<UDMF::PlainText> resText = std::static_pointer_cast<UDMF::PlainText>(this->unifiedRecord_);
    if (!resText) {
        LOGE("SetPlainTextAbstract failed, resText is null.");
        return;
    }
    if (!abstr) {
        LOGE("SetPlainTextAbstract failed, abstr is null.");
        return;
    }
    resText->SetAbstract(abstr);
}

char *CreateCStringFromString(const std::string &source)
{
    if (source.size() == 0) {
        return nullptr;
    }
    size_t length = source.size() + 1;
    auto res = static_cast<char*>(malloc(length));
    if (res == nullptr) {
        return nullptr;
    }
    if (strcpy_s(res, length, source.c_str()) != 0) {
        free(res);
        return nullptr;
    }
    return res;
}
} // namespace UDMF
} // namespace OHOS
