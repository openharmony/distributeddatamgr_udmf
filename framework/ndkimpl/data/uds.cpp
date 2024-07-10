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
#include <string>
#include "logger.h"
#include "utd_common.h"
#include "unified_record.h"
#include "udmf_ndk_common.h"
#include "udmf_meta.h"
#include "udmf_err_code.h"

using namespace OHOS::UDMF;

bool IsInvalidUdsObjectPtr(const Uds_Object_Ptr* pThis, int id)
{
    return pThis == nullptr || pThis->id != id || pThis->obj == nullptr;
}

Uds_Object_Ptr::Uds_Object_Ptr(const int id) : id(id) {}

OH_UdsPlainText::OH_UdsPlainText() : Uds_Object_Ptr(NdkStructId::UDS_PLAIN_TEXT_STRUCT_ID) {}

OH_UdsHyperlink::OH_UdsHyperlink() : Uds_Object_Ptr(NdkStructId::UDS_HYPERLINK_STRUCT_ID) {}

OH_UdsHtml::OH_UdsHtml() : Uds_Object_Ptr(NdkStructId::UDS_HTML_STRUCT_ID) {}

OH_UdsAppItem::OH_UdsAppItem() : Uds_Object_Ptr(NdkStructId::UDS_APP_ITEM_STRUCT_ID) {}

const char* Uds_Object_Ptr::GetUdsValue(const char* paramName)
{
    if (obj->value_.find(paramName) == obj->value_.end()) {
        LOG_ERROR(UDMF_NDK, "Don't have property %{public}s.", paramName);
        return nullptr;
    }
    return (std::get_if<std::string>(&(obj->value_[paramName])))->c_str();
}

int Uds_Object_Ptr::SetUdsValue(const char* paramName, const char* pramValue)
{
    if (obj->value_.find(paramName) == obj->value_.end()) {
        LOG_ERROR(UDMF_NDK, "Can't set property %{public}s.", paramName);
        return UdmfErrCode::UDMF_E_INVALID_PARAM;
    }
    std::lock_guard<std::mutex> lock(mutex);
    obj->value_[paramName] = pramValue;
    return UdmfErrCode::UDMF_E_OK;
}

OH_UdsPlainText* OH_UdsPlainText_Create()
{
    OH_UdsPlainText* plainText = new (std::nothrow) OH_UdsPlainText();
    if (plainText == nullptr) {
        LOG_ERROR(UDMF_NDK, "Failed to apply for memory.");
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
    if (pThis != nullptr && pThis->id == NdkStructId::UDS_PLAIN_TEXT_STRUCT_ID) {
        delete pThis;
    }
}

const char* OH_UdsPlainText_GetType(OH_UdsPlainText* pThis)
{
    if (IsInvalidUdsObjectPtr(pThis, NdkStructId::UDS_PLAIN_TEXT_STRUCT_ID)) {
        return nullptr;
    }
    return pThis->GetUdsValue(UNIFORM_DATA_TYPE);
}

const char* OH_UdsPlainText_GetContent(OH_UdsPlainText* pThis)
{
    if (IsInvalidUdsObjectPtr(pThis, NdkStructId::UDS_PLAIN_TEXT_STRUCT_ID)) {
        return nullptr;
    }
    return pThis->GetUdsValue(CONTENT);
}

const char* OH_UdsPlainText_GetAbstract(OH_UdsPlainText* pThis)
{
    if (IsInvalidUdsObjectPtr(pThis, NdkStructId::UDS_PLAIN_TEXT_STRUCT_ID)) {
        return nullptr;
    }
    return pThis->GetUdsValue(ABSTRACT);
}

int OH_UdsPlainText_SetContent(OH_UdsPlainText* pThis, const char* content)
{
    if (content == nullptr || IsInvalidUdsObjectPtr(pThis, NdkStructId::UDS_PLAIN_TEXT_STRUCT_ID)) {
        return UdmfErrCode::UDMF_E_INVALID_PARAM;
    }
    return pThis->SetUdsValue(CONTENT, content);
}

int OH_UdsPlainText_SetAbstract(OH_UdsPlainText* pThis, const char* abstract)
{
    if (abstract == nullptr || IsInvalidUdsObjectPtr(pThis, NdkStructId::UDS_PLAIN_TEXT_STRUCT_ID)) {
        return UdmfErrCode::UDMF_E_INVALID_PARAM;
    }
    return pThis->SetUdsValue(ABSTRACT, abstract);
}

OH_UdsHyperlink* OH_UdsHyperlink_Create()
{
    OH_UdsHyperlink* hyperlink = new (std::nothrow) OH_UdsHyperlink();
    if (hyperlink == nullptr) {
        LOG_ERROR(UDMF_NDK, "Failed to apply for memory.");
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
    if (pThis != nullptr && pThis->id == NdkStructId::UDS_HYPERLINK_STRUCT_ID) {
        delete pThis;
    }
}

const char* OH_UdsHyperlink_GetType(OH_UdsHyperlink* pThis)
{
    if (IsInvalidUdsObjectPtr(pThis, NdkStructId::UDS_HYPERLINK_STRUCT_ID)) {
        return nullptr;
    }
    return pThis->GetUdsValue(UNIFORM_DATA_TYPE);
}

const char* OH_UdsHyperlink_GetUrl(OH_UdsHyperlink* pThis)
{
    if (IsInvalidUdsObjectPtr(pThis, NdkStructId::UDS_HYPERLINK_STRUCT_ID)) {
        return nullptr;
    }
    return pThis->GetUdsValue(URL);
}

const char* OH_UdsHyperlink_GetDescription(OH_UdsHyperlink* pThis)
{
    if (IsInvalidUdsObjectPtr(pThis, NdkStructId::UDS_HYPERLINK_STRUCT_ID)) {
        return nullptr;
    }
    return pThis->GetUdsValue(DESCRIPTION);
}

int OH_UdsHyperlink_SetUrl(OH_UdsHyperlink* pThis, const char* url)
{
    if (url == nullptr || IsInvalidUdsObjectPtr(pThis, NdkStructId::UDS_HYPERLINK_STRUCT_ID)) {
        return UdmfErrCode::UDMF_E_INVALID_PARAM;
    }
    return pThis->SetUdsValue(URL, url);
}

int OH_UdsHyperlink_SetDescription(OH_UdsHyperlink* pThis, const char* description)
{
    if (description == nullptr || IsInvalidUdsObjectPtr(pThis, NdkStructId::UDS_HYPERLINK_STRUCT_ID)) {
        return UdmfErrCode::UDMF_E_INVALID_PARAM;
    }
    return pThis->SetUdsValue(DESCRIPTION, description);
}

OH_UdsHtml* OH_UdsHtml_Create()
{
    OH_UdsHtml* html = new (std::nothrow) OH_UdsHtml();
    if (html == nullptr) {
        LOG_ERROR(UDMF_NDK, "Failed to apply for memory.");
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
    if (pThis != nullptr && pThis->id == NdkStructId::UDS_HTML_STRUCT_ID) {
        delete pThis;
    }
}

const char* OH_UdsHtml_GetType(OH_UdsHtml* pThis)
{
    if (IsInvalidUdsObjectPtr(pThis, NdkStructId::UDS_HTML_STRUCT_ID)) {
        return nullptr;
    }
    return pThis->GetUdsValue(UNIFORM_DATA_TYPE);
}

const char* OH_UdsHtml_GetContent(OH_UdsHtml* pThis)
{
    if (IsInvalidUdsObjectPtr(pThis, NdkStructId::UDS_HTML_STRUCT_ID)) {
        return nullptr;
    }
    return pThis->GetUdsValue(HTML_CONTENT);
}

const char* OH_UdsHtml_GetPlainContent(OH_UdsHtml* pThis)
{
    if (IsInvalidUdsObjectPtr(pThis, NdkStructId::UDS_HTML_STRUCT_ID)) {
        return nullptr;
    }
    return pThis->GetUdsValue(PLAIN_CONTENT);
}

int OH_UdsHtml_SetContent(OH_UdsHtml* pThis, const char* content)
{
    if (content == nullptr || IsInvalidUdsObjectPtr(pThis, NdkStructId::UDS_HTML_STRUCT_ID)) {
        return UdmfErrCode::UDMF_E_INVALID_PARAM;
    }
    return pThis->SetUdsValue(HTML_CONTENT, content);
}

int OH_UdsHtml_SetPlainContent(OH_UdsHtml* pThis, const char* plainContent)
{
    if (plainContent == nullptr || IsInvalidUdsObjectPtr(pThis, NdkStructId::UDS_HTML_STRUCT_ID)) {
        return UdmfErrCode::UDMF_E_INVALID_PARAM;
    }
    return pThis->SetUdsValue(PLAIN_CONTENT, plainContent);
}

OH_UdsAppItem* OH_UdsAppItem_Create()
{
    OH_UdsAppItem* appItem = new (std::nothrow) OH_UdsAppItem();
    if (appItem == nullptr) {
        LOG_ERROR(UDMF_NDK, "Failed to apply for memory.");
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
    if (pThis != nullptr && pThis->id == NdkStructId::UDS_APP_ITEM_STRUCT_ID) {
        delete pThis;
    }
}

const char* OH_UdsAppItem_GetType(OH_UdsAppItem* pThis)
{
    if (IsInvalidUdsObjectPtr(pThis, NdkStructId::UDS_APP_ITEM_STRUCT_ID)) {
        return nullptr;
    }
    return pThis->GetUdsValue(UNIFORM_DATA_TYPE);
}

const char* OH_UdsAppItem_GetId(OH_UdsAppItem* pThis)
{
    if (IsInvalidUdsObjectPtr(pThis, NdkStructId::UDS_APP_ITEM_STRUCT_ID)) {
        return nullptr;
    }
    return pThis->GetUdsValue(APP_ID);
}

const char* OH_UdsAppItem_GetName(OH_UdsAppItem* pThis)
{
    if (IsInvalidUdsObjectPtr(pThis, NdkStructId::UDS_APP_ITEM_STRUCT_ID)) {
        return nullptr;
    }
    return pThis->GetUdsValue(APP_NAME);
}

const char* OH_UdsAppItem_GetIconId(OH_UdsAppItem* pThis)
{
    if (IsInvalidUdsObjectPtr(pThis, NdkStructId::UDS_APP_ITEM_STRUCT_ID)) {
        return nullptr;
    }
    return pThis->GetUdsValue(APP_ICON_ID);
}

const char* OH_UdsAppItem_GetLabelId(OH_UdsAppItem* pThis)
{
    if (IsInvalidUdsObjectPtr(pThis, NdkStructId::UDS_APP_ITEM_STRUCT_ID)) {
        return nullptr;
    }
    return pThis->GetUdsValue(APP_LABEL_ID);
}

const char* OH_UdsAppItem_GetBundleName(OH_UdsAppItem* pThis)
{
    if (IsInvalidUdsObjectPtr(pThis, NdkStructId::UDS_APP_ITEM_STRUCT_ID)) {
        return nullptr;
    }
    return pThis->GetUdsValue(BUNDLE_NAME);
}

const char* OH_UdsAppItem_GetAbilityName(OH_UdsAppItem* pThis)
{
    if (IsInvalidUdsObjectPtr(pThis, NdkStructId::UDS_APP_ITEM_STRUCT_ID)) {
        return nullptr;
    }
    return pThis->GetUdsValue(ABILITY_NAME);
}

int OH_UdsAppItem_SetId(OH_UdsAppItem* pThis, const char* appId)
{
    if (appId == nullptr || IsInvalidUdsObjectPtr(pThis, NdkStructId::UDS_APP_ITEM_STRUCT_ID)) {
        return UdmfErrCode::UDMF_E_INVALID_PARAM;
    }
    return pThis->SetUdsValue(APP_ID, appId);
}

int OH_UdsAppItem_SetName(OH_UdsAppItem* pThis, const char* appName)
{
    if (appName == nullptr || IsInvalidUdsObjectPtr(pThis, NdkStructId::UDS_APP_ITEM_STRUCT_ID)) {
        return UdmfErrCode::UDMF_E_INVALID_PARAM;
    }
    return pThis->SetUdsValue(APP_NAME, appName);
}

int OH_UdsAppItem_SetIconId(OH_UdsAppItem* pThis, const char* appIconId)
{
    if (appIconId == nullptr || IsInvalidUdsObjectPtr(pThis, NdkStructId::UDS_APP_ITEM_STRUCT_ID)) {
        return UdmfErrCode::UDMF_E_INVALID_PARAM;
    }
    return pThis->SetUdsValue(APP_ICON_ID, appIconId);
}

int OH_UdsAppItem_SetLabelId(OH_UdsAppItem* pThis, const char* appLabelId)
{
    if (appLabelId == nullptr || IsInvalidUdsObjectPtr(pThis, NdkStructId::UDS_APP_ITEM_STRUCT_ID)) {
        return UdmfErrCode::UDMF_E_INVALID_PARAM;
    }
    return pThis->SetUdsValue(APP_LABEL_ID, appLabelId);
}

int OH_UdsAppItem_SetBundleName(OH_UdsAppItem* pThis, const char* bundleName)
{
    if (bundleName == nullptr || IsInvalidUdsObjectPtr(pThis, NdkStructId::UDS_APP_ITEM_STRUCT_ID)) {
        return UdmfErrCode::UDMF_E_INVALID_PARAM;
    }
    return pThis->SetUdsValue(BUNDLE_NAME, bundleName);
}

int OH_UdsAppItem_SetAbilityName(OH_UdsAppItem* pThis, const char* abilityName)
{
    if (abilityName == nullptr || IsInvalidUdsObjectPtr(pThis, NdkStructId::UDS_APP_ITEM_STRUCT_ID)) {
        return UdmfErrCode::UDMF_E_INVALID_PARAM;
    }
    return pThis->SetUdsValue(ABILITY_NAME, abilityName);
}
