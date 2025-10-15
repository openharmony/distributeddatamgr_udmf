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
#define LOG_TAG "Uds"

#include "uds.h"

#include "logger.h"
#include "ndk_data_conversion.h"
#include "pixel_map.h"
#include "pixelmap_native_impl.h"
#include "securec.h"
#include "udmf_capi_common.h"
#include "udmf_err_code.h"
#include "udmf_meta.h"
#include "unified_meta.h"

using namespace OHOS::UDMF;

constexpr const int32_t MAX_PARAM_NAME = 1024;

static const char* GetUdsStrValue(UdsObject* pThis, NdkStructId ndkStructId, const char* paramName)
{
    if (IsInvalidUdsObjectPtr(pThis, ndkStructId)) {
        return nullptr;
    }
    auto value = pThis->GetUdsValue<std::string>(paramName);
    return value == nullptr ? nullptr : value->c_str();
}

static int GetUdsUint8Value(UdsObject* pThis, const char* paramName, const char* paramNameLen, unsigned char** data,
    unsigned int* len)
{
    auto value = pThis->GetUdsValue<std::vector<uint8_t>>(paramName);
    if (value == nullptr) {
        return UDMF_ERR;
    }
    auto lengthPtr = pThis->GetUdsValue<int>(paramNameLen);
    int length;
    if (lengthPtr == nullptr) {
        if (value->size() > MAX_GENERAL_ENTRY_SIZE) {
            LOG_ERROR(UDMF_CAPI, "length invalid. value'size = %{public}zu", value->size());
            return UDMF_ERR;
        }
        length = static_cast<int>(value->size());
    } else {
        length = *lengthPtr;
    }
    if (length < 0 || length > MAX_GENERAL_ENTRY_SIZE) {
        LOG_ERROR(UDMF_CAPI, "length invalid! length'size = %{public}d", length);
        return UDMF_ERR;
    }
    *data = value->data();
    *len = length;
    return UDMF_E_OK;
}

bool IsInvalidUdsObjectPtr(const UdsObject *pThis, int cid)
{
    return pThis == nullptr || pThis->cid != cid || pThis->obj == nullptr;
}

bool IsInvalidUdsObjectByType(const UdsObject* pThis, const UDType& type)
{
    switch (type) {
        case PLAIN_TEXT:
            return IsInvalidUdsObjectPtr(pThis, UDS_PLAIN_TEXT_STRUCT_ID);
        case HYPERLINK:
            return IsInvalidUdsObjectPtr(pThis, UDS_HYPERLINK_STRUCT_ID);
        case HTML:
            return IsInvalidUdsObjectPtr(pThis, UDS_HTML_STRUCT_ID);
        case SYSTEM_DEFINED_APP_ITEM:
            return IsInvalidUdsObjectPtr(pThis, UDS_APP_ITEM_STRUCT_ID);
        case FILE_URI:
            return IsInvalidUdsObjectPtr(pThis, UDS_FILE_URI_STRUCT_ID);
        case SYSTEM_DEFINED_PIXEL_MAP:
            return IsInvalidUdsObjectPtr(pThis, UDS_PIXEL_MAP_STRUCT_ID);
        case CONTENT_FORM:
            return IsInvalidUdsObjectPtr(pThis, UDS_CONTENT_FORM_STRUCT_ID);
        default:
            return false;
    }
}

static UDDetails ConvertToDetails(const std::map<std::string, std::string> &details)
{
    UDDetails udDetails;
    for (const auto &item : details) {
        if (item.first.empty()) {
            continue;
        }
        udDetails.insert({item.first, item.second});
    }
    return udDetails;
}

static void ConvertToMap(const UDDetails &details, std::map<std::string, std::string> &outMap)
{
    struct Visitor {
        std::string operator()(int32_t value) const { return std::to_string(value); }
        std::string operator()(int64_t value) const { return std::to_string(value); }
        std::string operator()(double value) const
        {
            std::ostringstream oss;
            oss << std::setprecision(std::numeric_limits<double>::max_digits10) << std::defaultfloat << value;
            return oss.str();
        }
        std::string operator()(const std::string &value) const { return value; }
        std::string operator()(const std::vector<uint8_t> &value) const
        {
            std::string str(value.begin(), value.end());
            return str;
        }
    };
    outMap.clear();
    for (const auto &[key, value] : details) {
        if (!key.empty()) {
            outMap.emplace(key, std::visit(Visitor{}, value));
        }
    }
}

static int GetUdsDetails(UdsObject* pThis, OH_UdsDetails* details, NdkStructId ndkStructId)
{
    if (details == nullptr || IsInvalidUdsObjectPtr(pThis, ndkStructId)) {
        LOG_ERROR(UDMF_CAPI, "invalid para.");
        return UDMF_E_INVALID_PARAM;
    }
    std::shared_ptr<Object> detailObj = nullptr;
    if (!pThis->obj->GetValue(DETAILS, detailObj)) {
        LOG_ERROR(UDMF_CAPI, "get details failed.");
        return UDMF_E_INVALID_PARAM;
    }
    auto udDetails = ObjectUtils::ConvertToUDDetails(detailObj);
    std::lock_guard<std::mutex> lock(pThis->mutex);
    ConvertToMap(udDetails, details->details_);
    details->isUpdate = true;
    return UDMF_E_OK;
}

static int SetUdsDetails(UdsObject* pThis, const OH_UdsDetails* details, NdkStructId ndkStructId)
{
    if (details == nullptr || IsInvalidUdsObjectPtr(pThis, ndkStructId)) {
        LOG_ERROR(UDMF_CAPI, "invalid para.");
        return UDMF_E_INVALID_PARAM;
    }
    auto udDetails = ConvertToDetails(details->details_);
    pThis->obj->value_[DETAILS] = ObjectUtils::ConvertToObject(udDetails);
    return UDMF_E_OK;
}

UdsObject::UdsObject(const int cid) : cid(cid) {}

OH_UdsPlainText::OH_UdsPlainText() : UdsObject(NdkStructId::UDS_PLAIN_TEXT_STRUCT_ID) {}

OH_UdsHyperlink::OH_UdsHyperlink() : UdsObject(NdkStructId::UDS_HYPERLINK_STRUCT_ID) {}

OH_UdsHtml::OH_UdsHtml() : UdsObject(NdkStructId::UDS_HTML_STRUCT_ID) {}

OH_UdsAppItem::OH_UdsAppItem() : UdsObject(NdkStructId::UDS_APP_ITEM_STRUCT_ID) {}

OH_UdsFileUri::OH_UdsFileUri() : UdsObject(NdkStructId::UDS_FILE_URI_STRUCT_ID) {}

OH_UdsPixelMap::OH_UdsPixelMap() : UdsObject(NdkStructId::UDS_PIXEL_MAP_STRUCT_ID) {}

OH_UdsArrayBuffer::OH_UdsArrayBuffer() : UdsObject(NdkStructId::UDS_ARRAY_BUFFER_STRUCT_ID) {}

OH_UdsContentForm::OH_UdsContentForm() : UdsObject(NdkStructId::UDS_CONTENT_FORM_STRUCT_ID) {}

template <typename T> bool UdsObject::HasObjectKey(const char* paramName)
{
    if (strlen(paramName) > MAX_PARAM_NAME) {
        LOG_ERROR(UDMF_CAPI, "paramName too long! paramName size = %{public}zu.", strlen(paramName));
        return false;
    }
    auto it = obj->value_.find(paramName);
    if (it == obj->value_.end() || !std::holds_alternative<T>(it->second)) {
        LOG_ERROR(UDMF_CAPI, "Don't have property paramName");
        return false;
    }
    return true;
}

template<typename T>
T* UdsObject::GetUdsValue(const char* paramName)
{
    if (!HasObjectKey<T>(paramName)) {
        return nullptr;
    }
    return std::get_if<T>(&(obj->value_[paramName]));
}

template<typename T>
int UdsObject::SetUdsValue(const char* paramName, const T &pramValue)
{
    if (!HasObjectKey<T>(paramName)) {
        return Udmf_ErrCode::UDMF_E_INVALID_PARAM;
    }
    std::lock_guard<std::mutex> lock(mutex);
    obj->value_[paramName] = pramValue;
    return Udmf_ErrCode::UDMF_E_OK;
}

OH_UdsPlainText* OH_UdsPlainText_Create()
{
    OH_UdsPlainText* plainText = new (std::nothrow) OH_UdsPlainText();
    if (plainText == nullptr) {
        LOG_ERROR(UDMF_CAPI, "Failed to apply for memory.");
        return nullptr;
    }
    plainText->obj = std::make_shared<Object>();
    plainText->obj->value_[UNIFORM_DATA_TYPE] = UDMF_META_PLAIN_TEXT;
    plainText->obj->value_[CONTENT] = "";
    plainText->obj->value_[ABSTRACT] = "";
    return plainText;
}

void OH_UdsPlainText_Destroy(OH_UdsPlainText* pThis)
{
    if (pThis != nullptr && pThis->cid == NdkStructId::UDS_PLAIN_TEXT_STRUCT_ID) {
        delete pThis;
    }
}

const char* OH_UdsPlainText_GetType(OH_UdsPlainText* pThis)
{
    return GetUdsStrValue(pThis, NdkStructId::UDS_PLAIN_TEXT_STRUCT_ID, UNIFORM_DATA_TYPE);
}

const char* OH_UdsPlainText_GetContent(OH_UdsPlainText* pThis)
{
    return GetUdsStrValue(pThis, NdkStructId::UDS_PLAIN_TEXT_STRUCT_ID, CONTENT);
}

const char* OH_UdsPlainText_GetAbstract(OH_UdsPlainText* pThis)
{
    return GetUdsStrValue(pThis, NdkStructId::UDS_PLAIN_TEXT_STRUCT_ID, ABSTRACT);
}

int OH_UdsPlainText_GetDetails(OH_UdsPlainText* pThis, OH_UdsDetails* details)
{
    return GetUdsDetails(pThis, details, NdkStructId::UDS_PLAIN_TEXT_STRUCT_ID);
}

int OH_UdsPlainText_SetContent(OH_UdsPlainText* pThis, const char* content)
{
    if (content == nullptr || IsInvalidUdsObjectPtr(pThis, NdkStructId::UDS_PLAIN_TEXT_STRUCT_ID)) {
        return Udmf_ErrCode::UDMF_E_INVALID_PARAM;
    }
    return pThis->SetUdsValue<std::string>(CONTENT, content);
}

int OH_UdsPlainText_SetAbstract(OH_UdsPlainText* pThis, const char* abstract)
{
    if (abstract == nullptr || IsInvalidUdsObjectPtr(pThis, NdkStructId::UDS_PLAIN_TEXT_STRUCT_ID)) {
        return Udmf_ErrCode::UDMF_E_INVALID_PARAM;
    }
    return pThis->SetUdsValue<std::string>(ABSTRACT, abstract);
}

int OH_UdsPlainText_SetDetails(OH_UdsPlainText* pThis, const OH_UdsDetails* details)
{
    return SetUdsDetails(pThis, details, NdkStructId::UDS_PLAIN_TEXT_STRUCT_ID);
}

OH_UdsHyperlink* OH_UdsHyperlink_Create()
{
    OH_UdsHyperlink* hyperlink = new (std::nothrow) OH_UdsHyperlink();
    if (hyperlink == nullptr) {
        LOG_ERROR(UDMF_CAPI, "Failed to apply for memory.");
        return nullptr;
    }
    hyperlink->obj = std::make_shared<Object>();
    hyperlink->obj->value_[UNIFORM_DATA_TYPE] = UDMF_META_HYPERLINK;
    hyperlink->obj->value_[URL] = "";
    hyperlink->obj->value_[DESCRIPTION] = "";
    return hyperlink;
}

void OH_UdsHyperlink_Destroy(OH_UdsHyperlink* pThis)
{
    if (pThis != nullptr && pThis->cid == NdkStructId::UDS_HYPERLINK_STRUCT_ID) {
        delete pThis;
    }
}

const char* OH_UdsHyperlink_GetType(OH_UdsHyperlink* pThis)
{
    return GetUdsStrValue(pThis, NdkStructId::UDS_HYPERLINK_STRUCT_ID, UNIFORM_DATA_TYPE);
}

const char* OH_UdsHyperlink_GetUrl(OH_UdsHyperlink* pThis)
{
    return GetUdsStrValue(pThis, NdkStructId::UDS_HYPERLINK_STRUCT_ID, URL);
}

const char* OH_UdsHyperlink_GetDescription(OH_UdsHyperlink* pThis)
{
    return GetUdsStrValue(pThis, NdkStructId::UDS_HYPERLINK_STRUCT_ID, DESCRIPTION);
}

int OH_UdsHyperlink_GetDetails(OH_UdsHyperlink* pThis, OH_UdsDetails* details)
{
    return GetUdsDetails(pThis, details, NdkStructId::UDS_HYPERLINK_STRUCT_ID);
}

int OH_UdsHyperlink_SetUrl(OH_UdsHyperlink* pThis, const char* url)
{
    if (url == nullptr || IsInvalidUdsObjectPtr(pThis, NdkStructId::UDS_HYPERLINK_STRUCT_ID)) {
        return Udmf_ErrCode::UDMF_E_INVALID_PARAM;
    }
    return pThis->SetUdsValue<std::string>(URL, url);
}

int OH_UdsHyperlink_SetDescription(OH_UdsHyperlink* pThis, const char* description)
{
    if (description == nullptr || IsInvalidUdsObjectPtr(pThis, NdkStructId::UDS_HYPERLINK_STRUCT_ID)) {
        return Udmf_ErrCode::UDMF_E_INVALID_PARAM;
    }
    return pThis->SetUdsValue<std::string>(DESCRIPTION, description);
}

int OH_UdsHyperlink_SetDetails(OH_UdsHyperlink* pThis, const OH_UdsDetails* details)
{
    return SetUdsDetails(pThis, details, NdkStructId::UDS_HYPERLINK_STRUCT_ID);
}

OH_UdsHtml* OH_UdsHtml_Create()
{
    OH_UdsHtml* html = new (std::nothrow) OH_UdsHtml();
    if (html == nullptr) {
        LOG_ERROR(UDMF_CAPI, "Failed to apply for memory.");
        return nullptr;
    }
    html->obj = std::make_shared<Object>();
    html->obj->value_[UNIFORM_DATA_TYPE] = UDMF_META_HTML;
    html->obj->value_[HTML_CONTENT] = "";
    html->obj->value_[PLAIN_CONTENT] = "";
    return html;
}

void OH_UdsHtml_Destroy(OH_UdsHtml* pThis)
{
    if (pThis != nullptr && pThis->cid == NdkStructId::UDS_HTML_STRUCT_ID) {
        delete pThis;
    }
}

const char* OH_UdsHtml_GetType(OH_UdsHtml* pThis)
{
    return GetUdsStrValue(pThis, NdkStructId::UDS_HTML_STRUCT_ID, UNIFORM_DATA_TYPE);
}

const char* OH_UdsHtml_GetContent(OH_UdsHtml* pThis)
{
    return GetUdsStrValue(pThis, NdkStructId::UDS_HTML_STRUCT_ID, HTML_CONTENT);
}

const char* OH_UdsHtml_GetPlainContent(OH_UdsHtml* pThis)
{
    return GetUdsStrValue(pThis, NdkStructId::UDS_HTML_STRUCT_ID, PLAIN_CONTENT);
}

int OH_UdsHtml_GetDetails(OH_UdsHtml* pThis, OH_UdsDetails* details)
{
    return GetUdsDetails(pThis, details, NdkStructId::UDS_HTML_STRUCT_ID);
}

int OH_UdsHtml_SetContent(OH_UdsHtml* pThis, const char* content)
{
    if (content == nullptr || IsInvalidUdsObjectPtr(pThis, NdkStructId::UDS_HTML_STRUCT_ID)) {
        return Udmf_ErrCode::UDMF_E_INVALID_PARAM;
    }
    return pThis->SetUdsValue<std::string>(HTML_CONTENT, content);
}

int OH_UdsHtml_SetPlainContent(OH_UdsHtml* pThis, const char* plainContent)
{
    if (plainContent == nullptr || IsInvalidUdsObjectPtr(pThis, NdkStructId::UDS_HTML_STRUCT_ID)) {
        return Udmf_ErrCode::UDMF_E_INVALID_PARAM;
    }
    return pThis->SetUdsValue<std::string>(PLAIN_CONTENT, plainContent);
}

int OH_UdsHtml_SetDetails(OH_UdsHtml* pThis, const OH_UdsDetails* details)
{
    return SetUdsDetails(pThis, details, NdkStructId::UDS_HTML_STRUCT_ID);
}

OH_UdsAppItem* OH_UdsAppItem_Create()
{
    OH_UdsAppItem* appItem = new (std::nothrow) OH_UdsAppItem();
    if (appItem == nullptr) {
        LOG_ERROR(UDMF_CAPI, "Failed to apply for memory.");
        return nullptr;
    }
    appItem->obj = std::make_shared<Object>();
    appItem->obj->value_[UNIFORM_DATA_TYPE] = UDMF_META_OPENHARMONY_APP_ITEM;
    appItem->obj->value_[APP_ID] = "";
    appItem->obj->value_[APP_NAME] = "";
    appItem->obj->value_[APP_ICON_ID] = "";
    appItem->obj->value_[APP_LABEL_ID] = "";
    appItem->obj->value_[BUNDLE_NAME] = "";
    appItem->obj->value_[ABILITY_NAME] = "";
    return appItem;
}

void OH_UdsAppItem_Destroy(OH_UdsAppItem* pThis)
{
    if (pThis != nullptr && pThis->cid == NdkStructId::UDS_APP_ITEM_STRUCT_ID) {
        delete pThis;
    }
}

const char* OH_UdsAppItem_GetType(OH_UdsAppItem* pThis)
{
    return GetUdsStrValue(pThis, NdkStructId::UDS_APP_ITEM_STRUCT_ID, UNIFORM_DATA_TYPE);
}

const char* OH_UdsAppItem_GetId(OH_UdsAppItem* pThis)
{
    return GetUdsStrValue(pThis, NdkStructId::UDS_APP_ITEM_STRUCT_ID, APP_ID);
}

const char* OH_UdsAppItem_GetName(OH_UdsAppItem* pThis)
{
    return GetUdsStrValue(pThis, NdkStructId::UDS_APP_ITEM_STRUCT_ID, APP_NAME);
}

const char* OH_UdsAppItem_GetIconId(OH_UdsAppItem* pThis)
{
    return GetUdsStrValue(pThis, NdkStructId::UDS_APP_ITEM_STRUCT_ID, APP_ICON_ID);
}

const char* OH_UdsAppItem_GetLabelId(OH_UdsAppItem* pThis)
{
    return GetUdsStrValue(pThis, NdkStructId::UDS_APP_ITEM_STRUCT_ID, APP_LABEL_ID);
}

const char* OH_UdsAppItem_GetBundleName(OH_UdsAppItem* pThis)
{
    return GetUdsStrValue(pThis, NdkStructId::UDS_APP_ITEM_STRUCT_ID, BUNDLE_NAME);
}

const char* OH_UdsAppItem_GetAbilityName(OH_UdsAppItem* pThis)
{
    return GetUdsStrValue(pThis, NdkStructId::UDS_APP_ITEM_STRUCT_ID, ABILITY_NAME);
}

int OH_UdsAppItem_GetDetails(OH_UdsAppItem* pThis, OH_UdsDetails* details)
{
    return GetUdsDetails(pThis, details, NdkStructId::UDS_APP_ITEM_STRUCT_ID);
}

int OH_UdsAppItem_SetId(OH_UdsAppItem* pThis, const char* appId)
{
    if (appId == nullptr || IsInvalidUdsObjectPtr(pThis, NdkStructId::UDS_APP_ITEM_STRUCT_ID)) {
        return Udmf_ErrCode::UDMF_E_INVALID_PARAM;
    }
    return pThis->SetUdsValue<std::string>(APP_ID, appId);
}

int OH_UdsAppItem_SetName(OH_UdsAppItem* pThis, const char* appName)
{
    if (appName == nullptr || IsInvalidUdsObjectPtr(pThis, NdkStructId::UDS_APP_ITEM_STRUCT_ID)) {
        return Udmf_ErrCode::UDMF_E_INVALID_PARAM;
    }
    return pThis->SetUdsValue<std::string>(APP_NAME, appName);
}

int OH_UdsAppItem_SetIconId(OH_UdsAppItem* pThis, const char* appIconId)
{
    if (appIconId == nullptr || IsInvalidUdsObjectPtr(pThis, NdkStructId::UDS_APP_ITEM_STRUCT_ID)) {
        return Udmf_ErrCode::UDMF_E_INVALID_PARAM;
    }
    return pThis->SetUdsValue<std::string>(APP_ICON_ID, appIconId);
}

int OH_UdsAppItem_SetLabelId(OH_UdsAppItem* pThis, const char* appLabelId)
{
    if (appLabelId == nullptr || IsInvalidUdsObjectPtr(pThis, NdkStructId::UDS_APP_ITEM_STRUCT_ID)) {
        return Udmf_ErrCode::UDMF_E_INVALID_PARAM;
    }
    return pThis->SetUdsValue<std::string>(APP_LABEL_ID, appLabelId);
}

int OH_UdsAppItem_SetBundleName(OH_UdsAppItem* pThis, const char* bundleName)
{
    if (bundleName == nullptr || IsInvalidUdsObjectPtr(pThis, NdkStructId::UDS_APP_ITEM_STRUCT_ID)) {
        return Udmf_ErrCode::UDMF_E_INVALID_PARAM;
    }
    return pThis->SetUdsValue<std::string>(BUNDLE_NAME, bundleName);
}

int OH_UdsAppItem_SetAbilityName(OH_UdsAppItem* pThis, const char* abilityName)
{
    if (abilityName == nullptr || IsInvalidUdsObjectPtr(pThis, NdkStructId::UDS_APP_ITEM_STRUCT_ID)) {
        return Udmf_ErrCode::UDMF_E_INVALID_PARAM;
    }
    return pThis->SetUdsValue<std::string>(ABILITY_NAME, abilityName);
}

int OH_UdsAppItem_SetDetails(OH_UdsAppItem* pThis, const OH_UdsDetails* details)
{
    return SetUdsDetails(pThis, details, NdkStructId::UDS_APP_ITEM_STRUCT_ID);
}

OH_UdsFileUri* OH_UdsFileUri_Create()
{
    OH_UdsFileUri* fileUri = new (std::nothrow) OH_UdsFileUri();
    if (fileUri == nullptr) {
        LOG_ERROR(UDMF_CAPI, "Failed to apply for memory.");
        return nullptr;
    }
    fileUri->obj = std::make_shared<Object>();
    fileUri->obj->value_[UNIFORM_DATA_TYPE] = UDMF_META_GENERAL_FILE_URI;
    fileUri->obj->value_[FILE_URI_PARAM] = "";
    fileUri->obj->value_[FILE_TYPE] = "";
    return fileUri;
}

void OH_UdsFileUri_Destroy(OH_UdsFileUri* pThis)
{
    if (pThis != nullptr && pThis->cid == NdkStructId::UDS_FILE_URI_STRUCT_ID) {
        delete pThis;
    }
}

const char* OH_UdsFileUri_GetType(OH_UdsFileUri* pThis)
{
    return GetUdsStrValue(pThis, NdkStructId::UDS_FILE_URI_STRUCT_ID, UNIFORM_DATA_TYPE);
}

const char* OH_UdsFileUri_GetFileUri(OH_UdsFileUri* pThis)
{
    return GetUdsStrValue(pThis, NdkStructId::UDS_FILE_URI_STRUCT_ID, FILE_URI_PARAM);
}

const char* OH_UdsFileUri_GetFileType(OH_UdsFileUri* pThis)
{
    return GetUdsStrValue(pThis, NdkStructId::UDS_FILE_URI_STRUCT_ID, FILE_TYPE);
}

int OH_UdsFileUri_GetDetails(OH_UdsFileUri* pThis, OH_UdsDetails* details)
{
    return GetUdsDetails(pThis, details, NdkStructId::UDS_FILE_URI_STRUCT_ID);
}

int OH_UdsFileUri_SetFileUri(OH_UdsFileUri* pThis, const char* fileUri)
{
    if (fileUri == nullptr || IsInvalidUdsObjectPtr(pThis, NdkStructId::UDS_FILE_URI_STRUCT_ID)) {
        return Udmf_ErrCode::UDMF_E_INVALID_PARAM;
    }
    return pThis->SetUdsValue<std::string>(FILE_URI_PARAM, fileUri);
}

int OH_UdsFileUri_SetFileType(OH_UdsFileUri* pThis, const char* fileType)
{
    if (fileType == nullptr || IsInvalidUdsObjectPtr(pThis, NdkStructId::UDS_FILE_URI_STRUCT_ID)) {
        return Udmf_ErrCode::UDMF_E_INVALID_PARAM;
    }
    return pThis->SetUdsValue<std::string>(FILE_TYPE, fileType);
}

int OH_UdsFileUri_SetDetails(OH_UdsFileUri* pThis, const OH_UdsDetails* details)
{
    return SetUdsDetails(pThis, details, NdkStructId::UDS_FILE_URI_STRUCT_ID);
}

OH_UdsPixelMap* OH_UdsPixelMap_Create()
{
    OH_UdsPixelMap* pixelMap = new (std::nothrow) OH_UdsPixelMap();
    if (pixelMap == nullptr) {
        LOG_ERROR(UDMF_CAPI, "Failed to apply for memory.");
        return nullptr;
    }
    pixelMap->obj = std::make_shared<Object>();
    pixelMap->obj->value_[UNIFORM_DATA_TYPE] = UDMF_META_OPENHARMONY_PIXEL_MAP;
    pixelMap->obj->value_[PIXEL_MAP] = std::shared_ptr<OHOS::Media::PixelMap>();
    return pixelMap;
}

void OH_UdsPixelMap_Destroy(OH_UdsPixelMap* pThis)
{
    if (pThis != nullptr && pThis->cid == NdkStructId::UDS_PIXEL_MAP_STRUCT_ID) {
        delete pThis;
    }
}

const char* OH_UdsPixelMap_GetType(OH_UdsPixelMap* pThis)
{
    return GetUdsStrValue(pThis, NdkStructId::UDS_PIXEL_MAP_STRUCT_ID, UNIFORM_DATA_TYPE);
}

void OH_UdsPixelMap_GetPixelMap(OH_UdsPixelMap* pThis, OH_PixelmapNative* pixelmapNative)
{
    if (IsInvalidUdsObjectPtr(pThis, NdkStructId::UDS_PIXEL_MAP_STRUCT_ID)) {
        return;
    }
    if (pixelmapNative == nullptr) {
        LOG_ERROR(UDMF_CAPI, "pixelmapNative is nullptr.");
        return;
    }
    auto pixelMap = pThis->GetUdsValue<std::shared_ptr<OHOS::Media::PixelMap>>(PIXEL_MAP);
    if (pixelMap == nullptr) {
        LOG_ERROR(UDMF_CAPI, "Get pixelMap value is null.");
        return;
    }
    *pixelmapNative = OH_PixelmapNative(*pixelMap);
}

int OH_UdsPixelMap_GetDetails(OH_UdsPixelMap* pThis, OH_UdsDetails* details)
{
    return GetUdsDetails(pThis, details, NdkStructId::UDS_PIXEL_MAP_STRUCT_ID);
}

int OH_UdsPixelMap_SetPixelMap(OH_UdsPixelMap* pThis, OH_PixelmapNative* pixelmapNative)
{
    if (pixelmapNative == nullptr || IsInvalidUdsObjectPtr(pThis, NdkStructId::UDS_PIXEL_MAP_STRUCT_ID)) {
        return Udmf_ErrCode::UDMF_E_INVALID_PARAM;
    }
    return pThis->SetUdsValue<std::shared_ptr<OHOS::Media::PixelMap>>(PIXEL_MAP, pixelmapNative->GetInnerPixelmap());
}

int OH_UdsPixelMap_SetDetails(OH_UdsPixelMap* pThis, const OH_UdsDetails* details)
{
    return SetUdsDetails(pThis, details, NdkStructId::UDS_PIXEL_MAP_STRUCT_ID);
}

OH_UdsArrayBuffer* OH_UdsArrayBuffer_Create()
{
    auto *buffer = new (std::nothrow) OH_UdsArrayBuffer();
    if (buffer == nullptr) {
        LOG_ERROR(UDMF_CAPI, "Failed to apply for memory.");
        return nullptr;
    }
    buffer->obj = std::make_shared<Object>();
    buffer->obj->value_[UNIFORM_DATA_TYPE] = "";
    buffer->obj->value_[ARRAY_BUFFER] = std::vector<uint8_t>();
    buffer->obj->value_[ARRAY_BUFFER_LENGTH] = 0;
    return buffer;
}

int OH_UdsArrayBuffer_Destroy(OH_UdsArrayBuffer* buffer)
{
    if (IsInvalidUdsObjectPtr(buffer, NdkStructId::UDS_ARRAY_BUFFER_STRUCT_ID)) {
        LOG_ERROR(UDMF_CAPI, "Param is invalid.");
        return UDMF_E_INVALID_PARAM;
    }
    delete buffer;
    return UDMF_E_OK;
}

int OH_UdsArrayBuffer_SetData(OH_UdsArrayBuffer* buffer, unsigned char* data, unsigned int len)
{
    if (data == nullptr || len == 0 || IsInvalidUdsObjectPtr(buffer, NdkStructId::UDS_ARRAY_BUFFER_STRUCT_ID) ||
        len > MAX_GENERAL_ENTRY_SIZE) {
        LOG_ERROR(UDMF_CAPI, "Param is invalid.");
        return UDMF_E_INVALID_PARAM;
    }
    std::vector<uint8_t> arrayBuffer(data, data + len);
    int ret = buffer->SetUdsValue<std::vector<uint8_t>>(ARRAY_BUFFER, arrayBuffer);
    if (ret != UDMF_E_OK) {
        LOG_ERROR(UDMF_CAPI, "Failed to apply for memory. ret: %{public}d", ret);
        return ret;
    }
    ret = buffer->SetUdsValue<int>(ARRAY_BUFFER_LENGTH, static_cast<int>(len));
    return ret;
}

int OH_UdsArrayBuffer_GetData(OH_UdsArrayBuffer* buffer, unsigned char** data, unsigned int* len)
{
    if (IsInvalidUdsObjectPtr(buffer, NdkStructId::UDS_ARRAY_BUFFER_STRUCT_ID)) {
        return UDMF_E_INVALID_PARAM;
    }
    return GetUdsUint8Value(buffer, ARRAY_BUFFER, ARRAY_BUFFER_LENGTH, data, len);
}

OH_UdsContentForm* OH_UdsContentForm_Create()
{
    auto contentForm = new (std::nothrow) OH_UdsContentForm();
    if (contentForm == nullptr) {
        LOG_ERROR(UDMF_CAPI, "Failed to apply for memory.");
        return nullptr;
    }
    contentForm->obj = std::make_shared<Object>();
    contentForm->obj->value_[UNIFORM_DATA_TYPE] = UDMF_METE_GENERAL_CONTENT_FORM;
    contentForm->obj->value_[THUMB_DATA] = std::vector<uint8_t>();
    contentForm->obj->value_[THUMB_DATA_LENGTH] = 0;
    contentForm->obj->value_[DESCRIPTION] = "";
    contentForm->obj->value_[TITLE] = "";
    contentForm->obj->value_[APP_ICON] = std::vector<uint8_t>();
    contentForm->obj->value_[APP_ICON_LENGTH] = 0;
    contentForm->obj->value_[APP_NAME] = "";
    contentForm->obj->value_[LINK_URL] = "";
    return contentForm;
}

void OH_UdsContentForm_Destroy(OH_UdsContentForm* pThis)
{
    if (pThis != nullptr && pThis->cid == NdkStructId::UDS_CONTENT_FORM_STRUCT_ID) {
        delete pThis;
    }
}

const char* OH_UdsContentForm_GetType(OH_UdsContentForm* pThis)
{
    return GetUdsStrValue(pThis, NdkStructId::UDS_CONTENT_FORM_STRUCT_ID, UNIFORM_DATA_TYPE);
}

int OH_UdsContentForm_GetThumbData(OH_UdsContentForm* pThis, unsigned char** thumbData, unsigned int* len)
{
    if (thumbData == nullptr || len == nullptr ||
        IsInvalidUdsObjectPtr(pThis, NdkStructId::UDS_CONTENT_FORM_STRUCT_ID)) {
        LOG_ERROR(UDMF_CAPI, "Param is invalid.");
        return UDMF_E_INVALID_PARAM;
    }
    return GetUdsUint8Value(pThis, THUMB_DATA, THUMB_DATA_LENGTH, thumbData, len);
}

const char* OH_UdsContentForm_GetDescription(OH_UdsContentForm* pThis)
{
    return GetUdsStrValue(pThis, NdkStructId::UDS_CONTENT_FORM_STRUCT_ID, DESCRIPTION);
}

const char* OH_UdsContentForm_GetTitle(OH_UdsContentForm* pThis)
{
    return GetUdsStrValue(pThis, NdkStructId::UDS_CONTENT_FORM_STRUCT_ID, TITLE);
}

int OH_UdsContentForm_GetAppIcon(OH_UdsContentForm* pThis, unsigned char** appIcon, unsigned int* len)
{
    if (appIcon == nullptr || len == nullptr || IsInvalidUdsObjectPtr(pThis, NdkStructId::UDS_CONTENT_FORM_STRUCT_ID)) {
        LOG_ERROR(UDMF_CAPI, "Param is invalid.");
        return UDMF_E_INVALID_PARAM;
    }
    return GetUdsUint8Value(pThis, APP_ICON, APP_ICON_LENGTH, appIcon, len);
}

const char* OH_UdsContentForm_GetAppName(OH_UdsContentForm* pThis)
{
    return GetUdsStrValue(pThis, NdkStructId::UDS_CONTENT_FORM_STRUCT_ID, APP_NAME);
}

const char* OH_UdsContentForm_GetLinkUri(OH_UdsContentForm* pThis)
{
    return GetUdsStrValue(pThis, NdkStructId::UDS_CONTENT_FORM_STRUCT_ID, LINK_URL);
}

int OH_UdsContentForm_SetThumbData(OH_UdsContentForm* pThis, const unsigned char* thumbData, unsigned int len)
{
    if (thumbData == nullptr || len == 0 || IsInvalidUdsObjectPtr(pThis, NdkStructId::UDS_CONTENT_FORM_STRUCT_ID) ||
        len > MAX_GENERAL_ENTRY_SIZE) {
        LOG_ERROR(UDMF_CAPI, "Param is invalid.");
        return UDMF_E_INVALID_PARAM;
    }
    std::vector<uint8_t> data(thumbData, thumbData + len);
    int ret = pThis->SetUdsValue<std::vector<uint8_t>>(THUMB_DATA, data);
    if (ret != UDMF_E_OK) {
        LOG_ERROR(UDMF_CAPI, "Failed to apply for memory. ret: %{public}d", ret);
        return ret;
    }
    ret = pThis->SetUdsValue<int>(THUMB_DATA_LENGTH, static_cast<int>(len));
    return ret;
}

int OH_UdsContentForm_SetDescription(OH_UdsContentForm* pThis, const char* description)
{
    if (description == nullptr || IsInvalidUdsObjectPtr(pThis, NdkStructId::UDS_CONTENT_FORM_STRUCT_ID)) {
        return Udmf_ErrCode::UDMF_E_INVALID_PARAM;
    }
    return pThis->SetUdsValue<std::string>(DESCRIPTION, description);
}

int OH_UdsContentForm_SetTitle(OH_UdsContentForm* pThis, const char* title)
{
    if (title == nullptr || IsInvalidUdsObjectPtr(pThis, NdkStructId::UDS_CONTENT_FORM_STRUCT_ID)) {
        return Udmf_ErrCode::UDMF_E_INVALID_PARAM;
    }
    return pThis->SetUdsValue<std::string>(TITLE, title);
}

int OH_UdsContentForm_SetAppIcon(OH_UdsContentForm* pThis, const unsigned char* appIcon, unsigned int len)
{
    if (appIcon == nullptr || len == 0 || IsInvalidUdsObjectPtr(pThis, NdkStructId::UDS_CONTENT_FORM_STRUCT_ID) ||
        len > MAX_GENERAL_ENTRY_SIZE) {
        LOG_ERROR(UDMF_CAPI, "Param is invalid.");
        return UDMF_E_INVALID_PARAM;
    }
    std::vector<uint8_t> data(appIcon, appIcon + len);
    int ret = pThis->SetUdsValue<std::vector<uint8_t>>(APP_ICON, data);
    if (ret != UDMF_E_OK) {
        LOG_ERROR(UDMF_CAPI, "Failed to apply for memory. ret: %{public}d", ret);
        return ret;
    }
    ret = pThis->SetUdsValue<int>(APP_ICON_LENGTH, static_cast<int>(len));
    return ret;
}

int OH_UdsContentForm_SetAppName(OH_UdsContentForm* pThis, const char* appName)
{
    if (appName == nullptr || IsInvalidUdsObjectPtr(pThis, NdkStructId::UDS_CONTENT_FORM_STRUCT_ID)) {
        return Udmf_ErrCode::UDMF_E_INVALID_PARAM;
    }
    return pThis->SetUdsValue<std::string>(APP_NAME, appName);
}

int OH_UdsContentForm_SetLinkUri(OH_UdsContentForm* pThis, const char* linkUri)
{
    if (linkUri == nullptr || IsInvalidUdsObjectPtr(pThis, NdkStructId::UDS_CONTENT_FORM_STRUCT_ID)) {
        return Udmf_ErrCode::UDMF_E_INVALID_PARAM;
    }
    return pThis->SetUdsValue<std::string>(LINK_URL, linkUri);
}

OH_UdsDetails* OH_UdsDetails_Create()
{
    OH_UdsDetails* details = new (std::nothrow) OH_UdsDetails();
    if (details == nullptr) {
        LOG_ERROR(UDMF_CAPI, "obtain the memory error.");
        return nullptr;
    }
    details->details_ = std::map<std::string, std::string>();
    return details;
}

void OH_UdsDetails_Destroy(OH_UdsDetails* pThis)
{
    if (pThis == nullptr) {
        return;
    }
    {
        std::lock_guard<std::mutex> lock(pThis->mutex);
        NdkDataConversion::DestroyStringArray(pThis->keysArray, pThis->keysCount);
    }
    delete pThis;
}

bool OH_UdsDetails_HasKey(const OH_UdsDetails* pThis, const char* key)
{
    if (pThis == nullptr || key == nullptr) {
        LOG_ERROR(UDMF_CAPI, "invalid para.");
        return false;
    }
    return pThis->details_.find(key) != pThis->details_.end();
}

int OH_UdsDetails_Remove(OH_UdsDetails* pThis, const char* key)
{
    if (pThis == nullptr || key == nullptr) {
        LOG_ERROR(UDMF_CAPI, "invalid para.");
        return UDMF_E_INVALID_PARAM;
    }
    std::lock_guard<std::mutex> lock(pThis->mutex);
    pThis->details_.erase(key);
    pThis->isUpdate = true;
    return UDMF_E_OK;
}

int OH_UdsDetails_Clear(OH_UdsDetails* pThis)
{
    if (pThis == nullptr) {
        LOG_ERROR(UDMF_CAPI, "invalid para.");
        return UDMF_E_INVALID_PARAM;
    }
    std::lock_guard<std::mutex> lock(pThis->mutex);
    pThis->details_.clear();
    pThis->isUpdate = true;
    return UDMF_E_OK;
}

int OH_UdsDetails_SetValue(OH_UdsDetails* pThis, const char* key, const char* value)
{
    if (pThis == nullptr || key == nullptr || value == nullptr) {
        LOG_ERROR(UDMF_CAPI, "invalid para.");
        return UDMF_E_INVALID_PARAM;
    }
    if (strlen(key) == 0) {
        LOG_ERROR(UDMF_CAPI, "key is empty string.");
        return UDMF_E_INVALID_PARAM;
    }
    std::lock_guard<std::mutex> lock(pThis->mutex);
    pThis->details_.insert_or_assign(key, value);
    pThis->isUpdate = true;
    return UDMF_E_OK;
}

const char* OH_UdsDetails_GetValue(const OH_UdsDetails* pThis, const char* key)
{
    if (pThis == nullptr || key == nullptr) {
        LOG_ERROR(UDMF_CAPI, "invalid para.");
        return nullptr;
    }
    auto item = pThis->details_.find(key);
    if (item == pThis->details_.end()) {
        LOG_ERROR(UDMF_CAPI, "not has key.");
        return nullptr;
    }
    return item->second.c_str();
}

char** OH_UdsDetails_GetAllKeys(OH_UdsDetails* pThis, unsigned int* count)
{
    if (pThis == nullptr || count == nullptr) {
        LOG_ERROR(UDMF_CAPI, "invalid para.");
        return nullptr;
    }
    std::lock_guard<std::mutex> lock(pThis->mutex);
    if ((!pThis->isUpdate) && (pThis->keysArray != nullptr)) {
        LOG_DEBUG(UDMF_CAPI, "return cache value.");
        *count = pThis->keysCount;
        return pThis->keysArray;
    }
    std::vector<std::string> keys;
    for (const auto &item : pThis->details_) {
        if (item.first.empty()) {
            continue;
        }
        keys.push_back(item.first);
    }
    NdkDataConversion::DestroyStringArray(pThis->keysArray, pThis->keysCount);
    pThis->keysArray = NdkDataConversion::StrVectorToTypesArray(keys);
    pThis->keysArray == nullptr ? pThis->keysCount = 0 : pThis->keysCount = keys.size();
    *count = pThis->keysCount;
    pThis->isUpdate = false;
    return pThis->keysArray;
}