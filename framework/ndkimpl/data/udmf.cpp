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
#define LOG_TAG "Udmf"
#include "udmf.h"
#include <cstring>
#include <memory>
#include <new>
#include "unified_data.h"
#include "unified_record.h"
#include "udmf_err_code.h"
#include "udmf_client.h"
#include "securec.h"
#include "udmf_capi_common.h"
#include "int_wrapper.h"
#include "string_wrapper.h"
#include "unified_meta.h"
#include "uds.h"
#include "udmf_meta.h"
#include "logger.h"
#include "plain_text.h"
#include "link.h"
#include "html.h"
#include "system_defined_appitem.h"
#include "application_defined_record.h"

using namespace OHOS::UDMF;

static constexpr uint64_t MAX_RECORDS_COUNT = 4 * 1024 * 1024;
static constexpr uint64_t MAX_RECORDS_SIZE = 4 * 1024 * 1024;
static constexpr uint64_t MAX_KEY_STRING_LEN = 1 * 1024 * 1024;

static void DestroyStringArray(char**& bufArray, unsigned int& count)
{
    if (bufArray == nullptr) {
        return;
    }
    for (unsigned int i = 0; i < count; i++) {
        if (bufArray[i] != nullptr) {
            delete[] bufArray[i];
            bufArray[i] = nullptr;
        }
    }
    delete[] bufArray;
    bufArray = nullptr;
    count = 0;
}

static void DestroyUnifiedRecordArray(OH_UdmfRecord**& records, unsigned int& count)
{
    if (records == nullptr) {
        return;
    }
    for (unsigned int i = 0; i < count; i++) {
        if (records[i] != nullptr) {
            delete records[i];
            records[i] = nullptr;
        }
    }
    delete[] records;
    records = nullptr;
    count = 0;
}

static char** StrVectorToTypesArray(const std::vector<std::string>& strVector)
{
    unsigned int vectorSize = strVector.size();
    if (vectorSize > MAX_RECORDS_COUNT) {
        return nullptr;
    }
    char** typesArray = new (std::nothrow) char* [vectorSize] {nullptr};
    for (unsigned int i = 0; i < vectorSize; ++i) {
        unsigned int strLen = strVector[i].length() + 1;
        if (strLen > MAX_KEY_STRING_LEN) {
            LOG_INFO(UDMF_CAPI, "string exceeds maximum length, length is %{public}d", strLen);
            DestroyStringArray(typesArray, vectorSize);
            return nullptr;
        }
        typesArray[i] = new (std::nothrow) char[strLen];
        if (typesArray[i] == nullptr ||
            (strcpy_s(typesArray[i], strLen, strVector[i].c_str())) != EOK) {
            LOG_ERROR(UDMF_CAPI, "string copy failed");
            DestroyStringArray(typesArray, vectorSize);
            return nullptr;
        }
    }
    return typesArray;
}

static OH_UdmfRecord** CreateUnifiedDataRecordsArray(OH_UdmfData* unifiedData,
                                                     std::vector<std::shared_ptr<UnifiedRecord>>& records)
{
    unsigned int size = static_cast<unsigned int>(records.size());
    if (unifiedData == nullptr || size == 0 || size > MAX_RECORDS_COUNT) {
        return nullptr;
    }
    OH_UdmfRecord** result = new (std::nothrow) OH_UdmfRecord* [size] { nullptr };
    if (result == nullptr) {
        return nullptr;
    }
    for (unsigned int i = 0; i < size; i++) {
        result[i] = new (std::nothrow) OH_UdmfRecord;
        if (result[i] == nullptr) {
            DestroyUnifiedRecordArray(result, size);
            return nullptr;
        }
        result[i]->record_ = records[i];
    }
    unifiedData->records = result;
    unifiedData->recordsCount = size;
    return unifiedData->records;
}

static bool IsUnifiedDataValid(OH_UdmfData* data)
{
    return data != nullptr && data->unifiedData_ != nullptr &&
           data->cid == NdkStructId::UDMF_UNIFIED_DATA_STRUCT_ID;
}

static bool IsUnifiedRecordValid(OH_UdmfRecord* record)
{
    return record != nullptr && record->record_ != nullptr &&
           record->cid == NdkStructId::UDMF_UNIFIED_RECORD_STRUCT_ID;
}

static bool IsUnifiedPropertiesValid(OH_UdmfProperty* properties)
{
    return properties != nullptr && properties->properties_ != nullptr &&
           properties->cid == NdkStructId::UDMF_UNIFIED_DATA_PROPERTIES_ID;
}

OH_UdmfData* OH_UdmfData_Create()
{
    OH_UdmfData* data = new (std::nothrow) OH_UdmfData;
    if (data == nullptr) {
        return nullptr;
    }
    data->unifiedData_ = std::make_shared<UnifiedData>();
    return data;
}

void OH_UdmfData_Destroy(OH_UdmfData* data)
{
    if (data == nullptr) {
        return;
    }
    DestroyStringArray(data->typesArray, data->typesCount);
    DestroyUnifiedRecordArray(data->records, data->recordsCount);
    delete data;
}

int OH_UdmfData_AddRecord(OH_UdmfData* unifiedData, OH_UdmfRecord* record)
{
    if (!IsUnifiedDataValid(unifiedData) || !IsUnifiedRecordValid(record)) {
        return UDMF_E_INVALID_PARAM;
    }
    unifiedData->unifiedData_->AddRecord(record->record_);
    return UDMF_E_OK;
}

bool OH_UdmfData_HasType(OH_UdmfData* unifiedData, const char* type)
{
    return IsUnifiedDataValid(unifiedData) && type != nullptr && unifiedData->unifiedData_->HasType(type);
}

char** OH_UdmfData_GetTypes(OH_UdmfData* unifiedData, unsigned int* count)
{
    if (!IsUnifiedDataValid(unifiedData) || count == nullptr) {
        return nullptr;
    }
    std::lock_guard<std::mutex> lock(unifiedData->mutex);
    if (unifiedData->typesArray != nullptr) {
        LOG_DEBUG(UDMF_CAPI, "return cache value");
        *count = unifiedData->typesCount;
        return unifiedData->typesArray;
    }
    std::vector<std::string> typeLabels = unifiedData->unifiedData_->GetTypesLabels();
    unifiedData->typesArray = StrVectorToTypesArray(typeLabels);
    unifiedData->typesArray == nullptr ? unifiedData->typesCount = 0 : unifiedData->typesCount = typeLabels.size();
    *count = unifiedData->typesCount;
    return unifiedData->typesArray;
}

char** OH_UdmfRecord_GetTypes(OH_UdmfRecord* record, unsigned int* count)
{
    if (!IsUnifiedRecordValid(record) || count == nullptr) {
        return nullptr;
    }
    std::lock_guard<std::mutex> lock(record->mutex);
    if (record->typesArray != nullptr) {
        LOG_DEBUG(UDMF_CAPI, "return cache value");
        *count = record->typesCount;
        return record->typesArray;
    }
    std::string type = UtdUtils::GetUtdIdFromUtdEnum(record->record_->GetType());
    std::vector<std::string> typeLabels;
    typeLabels.push_back(type);
    record->typesArray = StrVectorToTypesArray(typeLabels);
    record->typesArray == nullptr ? record->typesCount = 0 : record->typesCount = typeLabels.size();
    *count = record->typesCount;
    return record->typesArray;
}

OH_UdmfRecord** OH_UdmfData_GetRecords(OH_UdmfData* unifiedData, unsigned int* count)
{
    if (!IsUnifiedDataValid(unifiedData) || count == nullptr) {
        return nullptr;
    }
    std::lock_guard<std::mutex> lock(unifiedData->mutex);
    if (unifiedData->records != nullptr) {
        LOG_DEBUG(UDMF_CAPI, "return cache value");
        *count = unifiedData->recordsCount;
        return unifiedData->records;
    }
    std::vector<std::shared_ptr<UnifiedRecord>> records = unifiedData->unifiedData_->GetRecords();
    CreateUnifiedDataRecordsArray(unifiedData, records);
    *count = unifiedData->recordsCount;
    return unifiedData->records;
}

int OH_Udmf_GetUnifiedData(const char* key, Udmf_Intention intention, OH_UdmfData* data)
{
    if (!IsUnifiedDataValid(data) || key == nullptr) {
        return UDMF_E_INVALID_PARAM;
    }
    Intention queryOptIntent;
    switch (intention) {
        case UDMF_INTENTION_DRAG:
            queryOptIntent = Intention::UD_INTENTION_DRAG;
            break;
        default:
            return UDMF_E_INVALID_PARAM;
    }
    QueryOption query = {.key = std::string(key), .intention = queryOptIntent};
    if (UdmfClient::GetInstance().GetData(query, *(data->unifiedData_)) != E_OK) {
        LOG_ERROR(UDMF_CAPI, "get data error");
        return UDMF_ERR;
    }
    return UDMF_E_OK;
}

int OH_Udmf_SetUnifiedData(Udmf_Intention intention, OH_UdmfData* unifiedData, char* key, unsigned int keyLen)
{
    if (!IsUnifiedDataValid(unifiedData) || key == nullptr || keyLen < UDMF_KEY_BUFFER_LEN) {
        return UDMF_E_INVALID_PARAM;
    }
    enum Intention customOptIntent;
    switch (intention) {
        case UDMF_INTENTION_DRAG:
            customOptIntent = Intention::UD_INTENTION_DRAG;
            break;
        default:
            return UDMF_E_INVALID_PARAM;
    }
    CustomOption option = {.intention = customOptIntent};
    std::string keyStr;
    if ((UdmfClient::GetInstance().SetData(option, *(unifiedData->unifiedData_), keyStr)) != E_OK) {
        LOG_ERROR(UDMF_CAPI, "set data error");
        return UDMF_ERR;
    }
    if (strcpy_s(key, keyLen, keyStr.c_str()) != EOK) {
        LOG_INFO(UDMF_CAPI, "string copy failed");
        return UDMF_ERR;
    }
    return UDMF_E_OK;
}

OH_UdmfRecord* OH_UdmfRecord_Create()
{
    OH_UdmfRecord* record = new (std::nothrow) OH_UdmfRecord;
    if (record == nullptr) {
        return nullptr;
    }
    record->record_ = std::make_shared<UnifiedRecord>();
    return record;
}

void OH_UdmfRecord_Destroy(OH_UdmfRecord* record)
{
    if (record == nullptr) {
        return;
    }
    if (record->recordData != nullptr) {
        delete[] record->recordData;
        record->recordData = nullptr;
    }
    delete record;
}

int OH_UdmfRecord_AddGeneralEntry(OH_UdmfRecord* record, const char* typeId, unsigned char* entry, unsigned int count)
{
    if (!IsUnifiedRecordValid(record) || typeId == nullptr || entry == nullptr || count == 0 ||
        count > MAX_RECORDS_SIZE) {
        return UDMF_E_INVALID_PARAM;
    }
    std::vector<uint8_t> recordValue(count);
    for (unsigned int i = 0; i < count; ++i) {
        recordValue[i] = entry[i];
    }
    std::shared_ptr<ApplicationDefinedRecord> appDef = std::make_shared<ApplicationDefinedRecord>(typeId, recordValue);
    record->record_ = std::move(appDef);
    record->recordDataLen = count;
    return UDMF_E_OK;
}

int OH_UdmfRecord_GetGeneralEntry(OH_UdmfRecord* record, const char* typeId, unsigned char** entry, unsigned int* count)
{
    if (!IsUnifiedRecordValid(record) || typeId == nullptr || entry == nullptr || count == nullptr) {
        return UDMF_E_INVALID_PARAM;
    }
    if (record->record_->GetType() != APPLICATION_DEFINED_RECORD) {
        LOG_ERROR(UDMF_CAPI, "record's type not ApplicationDefinedType");
        return UDMF_E_INVALID_PARAM;
    }
    auto appDef = static_cast<ApplicationDefinedRecord *>((record->record_).get());
    if (appDef == nullptr) {
        LOG_ERROR(UDMF_CAPI, "cast failed");
        return UDMF_ERR;
    }
    if (appDef->GetApplicationDefinedType() != std::string(typeId)) {
        LOG_ERROR(UDMF_CAPI, "query typeId not equals to data type");
        return UDMF_E_INVALID_PARAM;
    }
    std::lock_guard<std::mutex> lock(record->mutex);
    std::vector<uint8_t> recordValue = appDef->GetRawData();
    *count = recordValue.size();
    if (record->recordData != nullptr) {
        LOG_DEBUG(UDMF_CAPI, "return cache value");
        *entry = record->recordData;
        return UDMF_E_OK;
    }
    if (*count > MAX_RECORDS_SIZE) {
        LOG_ERROR(UDMF_CAPI, "data size exceeds maximum size");
        *count = 0;
        return UDMF_ERR;
    }
    record->recordData = new (std::nothrow) unsigned char[*count];
    if (record->recordData == nullptr) {
        LOG_ERROR(UDMF_CAPI, "allocate memory failed");
        return UDMF_ERR;
    }
    for (unsigned int i = 0; i < *count; ++i) {
        (record->recordData)[i] = recordValue[i];
    }
    *entry = record->recordData;
    return UDMF_E_OK;
}

int OH_UdmfRecord_AddPlainText(OH_UdmfRecord* record, OH_UdsPlainText* plainText)
{
    if (!IsUnifiedRecordValid(record) || IsInvalidUdsObjectPtr(plainText, UDS_PLAIN_TEXT_STRUCT_ID)) {
        return UDMF_E_INVALID_PARAM;
    }
    std::shared_ptr<PlainText> text = std::make_shared<PlainText>();
    text->SetContent(OH_UdsPlainText_GetContent(plainText));
    text->SetAbstract(OH_UdsPlainText_GetAbstract(plainText));
    record->record_ = std::move(text);
    record->record_->SetType(static_cast<UDType>(UtdUtils::GetUtdEnumFromUtdId(OH_UdsPlainText_GetType(plainText))));
    return UDMF_E_OK;
}

int OH_UdmfRecord_AddHyperlink(OH_UdmfRecord* record, OH_UdsHyperlink* hyperlink)
{
    if (!IsUnifiedRecordValid(record) || IsInvalidUdsObjectPtr(hyperlink, UDS_HYPERLINK_STRUCT_ID)) {
        return UDMF_E_INVALID_PARAM;
    }
    std::shared_ptr<Link> link = std::make_shared<Link>();
    link->SetUrl(OH_UdsHyperlink_GetUrl(hyperlink));
    link->SetDescription(OH_UdsHyperlink_GetDescription(hyperlink));
    record->record_ = std::move(link);
    record->record_->SetType(static_cast<UDType>(UtdUtils::GetUtdEnumFromUtdId(OH_UdsHyperlink_GetType(hyperlink))));
    return UDMF_E_OK;
}

int OH_UdmfRecord_AddHtml(OH_UdmfRecord* record, OH_UdsHtml* html)
{
    if (!IsUnifiedRecordValid(record) || IsInvalidUdsObjectPtr(html, UDS_HTML_STRUCT_ID)) {
        return UDMF_E_INVALID_PARAM;
    }
    std::shared_ptr<Html> htmlPtr = std::make_shared<Html>();
    htmlPtr->SetHtmlContent(OH_UdsHtml_GetContent(html));
    htmlPtr->SetPlainContent(OH_UdsHtml_GetPlainContent(html));
    record->record_ = std::move(htmlPtr);
    record->record_->SetType(static_cast<UDType>(UtdUtils::GetUtdEnumFromUtdId(OH_UdsHtml_GetType(html))));
    return UDMF_E_OK;
}

int OH_UdmfRecord_AddAppItem(OH_UdmfRecord* record, OH_UdsAppItem* appItem)
{
    if (!IsUnifiedRecordValid(record) || IsInvalidUdsObjectPtr(appItem, UDS_APP_ITEM_STRUCT_ID)) {
        return UDMF_E_INVALID_PARAM;
    }
    std::shared_ptr<SystemDefinedAppItem> appDefRecord = std::make_shared<SystemDefinedAppItem>();
    appDefRecord->SetAppId(OH_UdsAppItem_GetId(appItem));
    appDefRecord->SetAppName(OH_UdsAppItem_GetName(appItem));
    appDefRecord->SetAppIconId(OH_UdsAppItem_GetIconId(appItem));
    appDefRecord->SetAppLabelId(OH_UdsAppItem_GetLabelId(appItem));
    appDefRecord->SetBundleName(OH_UdsAppItem_GetBundleName(appItem));
    appDefRecord->SetAbilityName(OH_UdsAppItem_GetAbilityName(appItem));
    record->record_ = std::move(appDefRecord);
    record->record_->SetType(
        static_cast<OHOS::UDMF::UDType>(UtdUtils::GetUtdEnumFromUtdId(OH_UdsAppItem_GetType(appItem))));
    return UDMF_E_OK;
}

int OH_UdmfRecord_GetPlainText(OH_UdmfRecord* record, OH_UdsPlainText* plainText)
{
    if (!IsUnifiedRecordValid(record) || IsInvalidUdsObjectPtr(plainText, UDS_PLAIN_TEXT_STRUCT_ID)) {
        return UDMF_E_INVALID_PARAM;
    }
    if (record->record_->GetType() != PLAIN_TEXT) {
        return UDMF_ERR;
    }
    auto plain = static_cast<PlainText *>((record->record_).get());
    if (plain == nullptr) {
        return UDMF_ERR;
    }
    OH_UdsPlainText_SetContent(plainText, plain->GetContent().c_str());
    OH_UdsPlainText_SetAbstract(plainText, plain->GetAbstract().c_str());
    plainText->obj->value_[UNIFORM_DATA_TYPE] = UDMF_META_PLAIN_TEXT;
    return UDMF_E_OK;
}

int OH_UdmfRecord_GetHyperlink(OH_UdmfRecord* record, OH_UdsHyperlink* hyperlink)
{
    if (!IsUnifiedRecordValid(record) || IsInvalidUdsObjectPtr(hyperlink, UDS_HYPERLINK_STRUCT_ID)) {
        return UDMF_E_INVALID_PARAM;
    }
    if (record->record_->GetType() != HYPERLINK) {
        return UDMF_ERR;
    }
    auto link = static_cast<Link *>((record->record_).get());
    if (link == nullptr) {
        return UDMF_ERR;
    }
    OH_UdsHyperlink_SetUrl(hyperlink, link->GetUrl().c_str());
    OH_UdsHyperlink_SetDescription(hyperlink, link->GetDescription().c_str());
    hyperlink->obj->value_[UNIFORM_DATA_TYPE] = UDMF_META_HYPERLINK;
    return UDMF_E_OK;
}

int OH_UdmfRecord_GetHtml(OH_UdmfRecord* record, OH_UdsHtml* html)
{
    if (!IsUnifiedRecordValid(record) || IsInvalidUdsObjectPtr(html, UDS_HTML_STRUCT_ID)) {
        return UDMF_E_INVALID_PARAM;
    }
    if (record->record_->GetType() != HTML) {
        return UDMF_ERR;
    }
    auto htmlPtr = static_cast<Html *>((record->record_).get());
    if (htmlPtr == nullptr) {
        return UDMF_ERR;
    }
    OH_UdsHtml_SetContent(html, htmlPtr->GetHtmlContent().c_str());
    OH_UdsHtml_SetPlainContent(html, htmlPtr->GetPlainContent().c_str());
    html->obj->value_[UNIFORM_DATA_TYPE] = UDMF_META_HTML;
    return UDMF_E_OK;
}

int OH_UdmfRecord_GetAppItem(OH_UdmfRecord* record, OH_UdsAppItem* appItem)
{
    if (!IsUnifiedRecordValid(record) || IsInvalidUdsObjectPtr(appItem, UDS_APP_ITEM_STRUCT_ID)) {
        return UDMF_E_INVALID_PARAM;
    }
    if (record->record_->GetType() != SYSTEM_DEFINED_APP_ITEM) {
        return UDMF_ERR;
    }
    auto appDefRecord = static_cast<SystemDefinedAppItem *>((record->record_).get());
    if (appDefRecord == nullptr) {
        return UDMF_ERR;
    }
    OH_UdsAppItem_SetId(appItem, appDefRecord->GetAppId().c_str());
    OH_UdsAppItem_SetName(appItem, appDefRecord->GetAppName().c_str());
    OH_UdsAppItem_SetIconId(appItem, appDefRecord->GetAppIconId().c_str());
    OH_UdsAppItem_SetLabelId(appItem, appDefRecord->GetAppLabelId().c_str());
    OH_UdsAppItem_SetBundleName(appItem, appDefRecord->GetBundleName().c_str());
    OH_UdsAppItem_SetAbilityName(appItem, appDefRecord->GetAbilityName().c_str());
    appItem->obj->value_[UNIFORM_DATA_TYPE] = UDMF_META_OPENHARMONY_APP_ITEM;
    return UDMF_E_OK;
}

OH_UdmfProperty* OH_UdmfProperty_Create(OH_UdmfData* data)
{
    if (!IsUnifiedDataValid(data)) {
        return nullptr;
    }
    OH_UdmfProperty* properties = new (std::nothrow) OH_UdmfProperty;
    if (properties == nullptr) {
        return nullptr;
    }
    properties->properties_ = data->unifiedData_->GetProperties();
    return properties;
}

void OH_UdmfProperty_Destroy(OH_UdmfProperty* properties)
{
    if (properties != nullptr) {
        delete properties;
    }
}

const char* OH_UdmfProperty_GetTag(OH_UdmfProperty* properties)
{
    if (!IsUnifiedPropertiesValid(properties)) {
        return nullptr;
    }
    return properties->properties_->tag.c_str();
}

int64_t OH_UdmfProperty_GetTimestamp(OH_UdmfProperty* properties)
{
    if (!IsUnifiedPropertiesValid(properties)) {
        return -1;
    }
    return properties->properties_->timestamp;
}

Udmf_ShareOption OH_UdmfProperty_GetShareOption(OH_UdmfProperty* properties)
{
    if (!IsUnifiedPropertiesValid(properties)) {
        return Udmf_ShareOption::SHARE_OPTIONS_INVALID;
    }
    switch (properties->properties_->shareOptions) {
        case ShareOptions::IN_APP:
            return Udmf_ShareOption::SHARE_OPTIONS_IN_APP;
        case ShareOptions::CROSS_APP:
            return Udmf_ShareOption::SHARE_OPTIONS_CROSS_APP;
        default:
            return Udmf_ShareOption::SHARE_OPTIONS_INVALID;
    }
}

int OH_UdmfProperty_GetExtrasIntParam(OH_UdmfProperty* properties, const char* key, const int defaultValue)
{
    return (IsUnifiedPropertiesValid(properties) && key != nullptr) ?
           properties->properties_->extras.GetIntParam(key, defaultValue) : defaultValue;
}

const char* OH_UdmfProperty_GetExtrasStringParam(OH_UdmfProperty* properties, const char* key)
{
    if (!IsUnifiedPropertiesValid(properties) || key == nullptr) {
        return nullptr;
    }
    properties->extraStr = properties->properties_->extras.GetStringParam(key);
    return properties->extraStr.c_str();
}

int OH_UdmfProperty_SetTag(OH_UdmfProperty* properties, const char* tag)
{
    if (!IsUnifiedPropertiesValid(properties) || tag == nullptr) {
        return UDMF_E_INVALID_PARAM;
    }
    properties->properties_->tag = tag;
    return UDMF_E_OK;
}

int OH_UdmfProperty_SetShareOption(OH_UdmfProperty* properties, Udmf_ShareOption option)
{
    if (!IsUnifiedPropertiesValid(properties)) {
        return UDMF_E_INVALID_PARAM;
    }
    std::lock_guard<std::mutex> lock(properties->mutex);
    switch (option) {
        case Udmf_ShareOption::SHARE_OPTIONS_IN_APP:
            properties->properties_->shareOptions = ShareOptions::IN_APP;
            break;
        case Udmf_ShareOption::SHARE_OPTIONS_CROSS_APP:
            properties->properties_->shareOptions = ShareOptions::CROSS_APP;
            break;
        default:
            return UDMF_E_INVALID_PARAM;
    }
    return UDMF_E_OK;
}

int OH_UdmfProperty_SetExtrasIntParam(OH_UdmfProperty* properties, const char* key, int param)
{
    if (!IsUnifiedPropertiesValid(properties) || key == nullptr) {
        return UDMF_E_INVALID_PARAM;
    }
    std::lock_guard<std::mutex> lock(properties->mutex);
    properties->properties_->extras.SetParam(key, OHOS::AAFwk::Integer::Box(param));
    return UDMF_E_OK;
}

int OH_UdmfProperty_SetExtrasStringParam(OH_UdmfProperty* properties, const char* key, const char* param)
{
    if (!IsUnifiedPropertiesValid(properties) || key == nullptr || param == nullptr) {
        return UDMF_E_INVALID_PARAM;
    }
    std::lock_guard<std::mutex> lock(properties->mutex);
    properties->properties_->extras.SetParam(key, OHOS::AAFwk::String::Box(param));
    return UDMF_E_OK;
}
