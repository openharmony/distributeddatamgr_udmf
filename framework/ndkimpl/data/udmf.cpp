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
#include "udmf_err_code.h"
#include "data_provider_impl.h"
#include "udmf_client.h"
#include "securec.h"
#include "udmf_capi_common.h"
#include "int_wrapper.h"
#include "string_wrapper.h"
#include "unified_meta.h"
#include "udmf_meta.h"
#include "logger.h"
#include "plain_text.h"
#include "link.h"
#include "html.h"
#include "system_defined_appitem.h"
#include "application_defined_record.h"
#include "system_defined_pixelmap.h"
#include "file.h"
#include "audio.h"
#include "folder.h"
#include "image.h"
#include "video.h"
#include "utd.h"
#include "utd_client.h"
#include "unified_key.h"

using namespace OHOS::UDMF;

static constexpr uint64_t MAX_RECORDS_COUNT = 4 * 1024 * 1024;
static constexpr uint64_t MAX_KEY_STRING_LEN = 1 * 1024 * 1024;
static const std::map<std::string, UDType> FILE_TYPES = {
    { UDMF_META_GENERAL_FILE, UDType::FILE },
    { UDMF_META_AUDIO, UDType::AUDIO },
    { UDMF_META_FOLDER, UDType::FOLDER },
    { UDMF_META_IMAGE, UDType::IMAGE },
    { UDMF_META_VIDEO, UDType::VIDEO }
};
static const std::set<std::string> FILE_SUB_TYPES = {
    "general.image", "general.video", "general.audio", "general.folder" };

static const std::map<Udmf_Intention, Intention> VAILD_INTENTIONS = {
    { UDMF_INTENTION_DRAG, Intention::UD_INTENTION_DRAG },
    { UDMF_INTENTION_SYSTEM_SHARE, Intention::UD_INTENTION_SYSTEM_SHARE },
    { UDMF_INTENTION_PICKER, Intention::UD_INTENTION_PICKER },
    { UDMF_INTENTION_MENU, Intention::UD_INTENTION_MENU }
};

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
    if (vectorSize == 0 || vectorSize > MAX_RECORDS_COUNT) {
        return nullptr;
    }
    char** typesArray = new (std::nothrow) char* [vectorSize];
    if (typesArray == nullptr) {
        LOG_ERROR(UDMF_CAPI, "create types array failed!, vectorSize: %{public}d, MAX_RECORDS_COUNT: %{public}" PRIu64,
            vectorSize, MAX_RECORDS_COUNT);
        return nullptr;
    }
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

static void AddFileUriTypeIfContains(std::vector<std::string>& types)
{
    if (std::find(types.begin(), types.end(), UDMF_META_GENERAL_FILE_URI) != types.end()) {
        return;
    }
    for (auto type : types) {
        if (FILE_TYPES.find(type) != FILE_TYPES.end()) {
            types.push_back(UDMF_META_GENERAL_FILE_URI);
            break;
        }
    }
    return;
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
    return IsUnifiedDataValid(unifiedData) && type != nullptr && unifiedData->unifiedData_->HasTypeInEntries(type);
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
    std::vector<std::string> typeLabels = unifiedData->unifiedData_->GetEntriesTypes();
    AddFileUriTypeIfContains(typeLabels);
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
    auto types = record->record_->GetUtdIdsWithAddFileType();
    std::vector<std::string> typeLabels {types.begin(), types.end()};
    AddFileUriTypeIfContains(typeLabels);
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

static int GetFirstPlainText(OH_UdmfRecord **records, unsigned int recordCount, OH_UdsPlainText* plainText)
{
    int ret = UDMF_ERR;
    if (records == nullptr || recordCount == 0) {
        return ret;
    }
    for (unsigned int i = 0; i < recordCount; i++) {
        const char *type = OH_UdsPlainText_GetType(plainText);
        if (type == nullptr || !records[i]->record_->HasType(type)) {
            continue;
        }
        ret = OH_UdmfRecord_GetPlainText(records[i], plainText);
        if (ret == UDMF_E_OK) {
            return ret;
        }
    }
    return ret;
}

static int GetFirstHtml(OH_UdmfRecord **records, unsigned int recordCount, OH_UdsHtml* html)
{
    int ret = UDMF_ERR;
    if (records == nullptr || recordCount == 0) {
        return ret;
    }
    for (unsigned int i = 0; i < recordCount; i++) {
        const char *type = OH_UdsHtml_GetType(html);
        if (type == nullptr || !records[i]->record_->HasType(type)) {
            continue;
        }
        ret = OH_UdmfRecord_GetHtml(records[i], html);
        if (ret == UDMF_E_OK) {
            return ret;
        }
    }
    return ret;
}

int OH_UdmfData_GetPrimaryPlainText(OH_UdmfData* data, OH_UdsPlainText* plainText)
{
    if (!IsUnifiedDataValid(data) || IsInvalidUdsObjectPtr(plainText, UDS_PLAIN_TEXT_STRUCT_ID)) {
        return UDMF_E_INVALID_PARAM;
    }
    std::lock_guard<std::mutex> lock(data->mutex);
    if (data->records == nullptr) {
        LOG_DEBUG(UDMF_CAPI, "no cache value");
        std::vector<std::shared_ptr<UnifiedRecord>> records = data->unifiedData_->GetRecords();
        CreateUnifiedDataRecordsArray(data, records);
    }

    return GetFirstPlainText(data->records, data->recordsCount, plainText);
}

int OH_UdmfData_GetPrimaryHtml(OH_UdmfData* data, OH_UdsHtml* html)
{
    if (!IsUnifiedDataValid(data) || IsInvalidUdsObjectPtr(html, UDS_HTML_STRUCT_ID)) {
        return UDMF_E_INVALID_PARAM;
    }
    std::lock_guard<std::mutex> lock(data->mutex);
    if (data->records == nullptr) {
        LOG_DEBUG(UDMF_CAPI, "no cache value");
        std::vector<std::shared_ptr<UnifiedRecord>> records = data->unifiedData_->GetRecords();
        CreateUnifiedDataRecordsArray(data, records);
    }

    return GetFirstHtml(data->records, data->recordsCount, html);
}

int OH_UdmfData_GetRecordCount(OH_UdmfData *data)
{
    if (!IsUnifiedDataValid(data)) {
        return 0;
    }
    std::lock_guard<std::mutex> lock(data->mutex);
    if (data->records == nullptr) {
        LOG_DEBUG(UDMF_CAPI, "no cache value");
        std::vector<std::shared_ptr<UnifiedRecord>> records = data->unifiedData_->GetRecords();
        CreateUnifiedDataRecordsArray(data, records);
    }
    return static_cast<int>(data->recordsCount);
}

OH_UdmfRecord* OH_UdmfData_GetRecord(OH_UdmfData* data, unsigned int index)
{
    if (!IsUnifiedDataValid(data)) {
        return nullptr;
    }
    std::lock_guard<std::mutex> lock(data->mutex);
    if (data->records == nullptr) {
        LOG_DEBUG(UDMF_CAPI, "no cache value");
        std::vector<std::shared_ptr<UnifiedRecord>> records = data->unifiedData_->GetRecords();
        CreateUnifiedDataRecordsArray(data, records);
    }
    if (index >= data->recordsCount || data->records == nullptr) {
        return nullptr;
    }
    return data->records[index];
}

bool OH_UdmfData_IsLocal(OH_UdmfData* data)
{
    if (!IsUnifiedDataValid(data) || data->unifiedData_->GetProperties() == nullptr) {
        return true;
    }
    bool isRemote = data->unifiedData_->GetProperties()->isRemote;
    return !isRemote;
}

OH_UdmfOptions* OH_UdmfOptions_Create()
{
    OH_UdmfOptions* options = new (std::nothrow) OH_UdmfOptions;
    if (options == nullptr) {
        LOG_ERROR(UDMF_CAPI, "The OH_UdmfOptions create error");
        return nullptr;
    }
    return options;
}

void OH_UdmfOptions_Destroy(OH_UdmfOptions* pThis)
{
    if (pThis != nullptr) {
        delete pThis;
        pThis = nullptr;
    }
}

const char* OH_UdmfOptions_GetKey(OH_UdmfOptions* pThis)
{
    if (pThis == nullptr) {
        LOG_ERROR(UDMF_CAPI, "The OH_UdmfOptions get key error, invaild params!");
        return nullptr;
    }
    return pThis->key.c_str();
}

int OH_UdmfOptions_SetKey(OH_UdmfOptions* pThis, const char* key)
{
    if (pThis == nullptr || key == nullptr) {
        LOG_ERROR(UDMF_CAPI, "The OH_UdmfOptions set key error, invaild params!");
        return UDMF_E_INVALID_PARAM;
    }
    std::string keyStr(key);
    if (keyStr.length() > UDMF_KEY_BUFFER_LEN) {
        LOG_ERROR(UDMF_CAPI, "key length exceeds maximum length, length is %{public}zu", keyStr.length());
        return UDMF_E_INVALID_PARAM;
    }
    pThis->key = keyStr;
    return UDMF_E_OK;
}

Udmf_Intention OH_UdmfOptions_GetIntention(OH_UdmfOptions* pThis)
{
    if (pThis == nullptr) {
        LOG_ERROR(UDMF_CAPI, "The OH_UdmfOptions get intention error, invaild params!");
        return Udmf_Intention {};
    }
    return pThis->intention;
}

int OH_UdmfOptions_SetIntention(OH_UdmfOptions* pThis, Udmf_Intention intention)
{
    if (pThis == nullptr) {
        LOG_ERROR(UDMF_CAPI, "The OH_UdmfOptions set intention error, invaild params!");
        return UDMF_E_INVALID_PARAM;
    }

    pThis->intention = intention;
    return UDMF_E_OK;
}

int OH_UdmfOptions_Reset(OH_UdmfOptions* pThis)
{
    if (pThis == nullptr) {
        LOG_ERROR(UDMF_CAPI, "The OH_UdmfOptions reset error, invaild params!");
        return UDMF_E_INVALID_PARAM;
    }
    pThis->key.clear();
    pThis->intention = Udmf_Intention {};
    return UDMF_E_OK;
}

int OH_Udmf_GetUnifiedData(const char* key, Udmf_Intention intention, OH_UdmfData* data)
{
    if (!IsUnifiedDataValid(data) || key == nullptr) {
        return UDMF_E_INVALID_PARAM;
    }
    Intention queryOptIntent;
    auto it = VAILD_INTENTIONS.find(intention);
    if (it != VAILD_INTENTIONS.end()) {
        queryOptIntent = it->second;
    } else {
        return UDMF_E_INVALID_PARAM;
    }
    QueryOption query = {.key = std::string(key), .intention = queryOptIntent};
    if (Intention::UD_INTENTION_DRAG == queryOptIntent) {
        if (UdmfClient::GetInstance().GetData(query, *(data->unifiedData_)) != E_OK) {
            LOG_ERROR(UDMF_CAPI, "get data error");
            return UDMF_ERR;
        }
        return UDMF_E_OK;
    }
    if (UnifiedDataUtils::IsFileMangerIntention(UD_INTENTION_MAP.at(queryOptIntent))) {
        std::vector<UnifiedData> unifiedDataSet;
        auto ret = UdmfClient::GetInstance().GetBatchData(query, unifiedDataSet);
        if (ret != E_OK) {
            LOG_ERROR(UDMF_CAPI, "get batchdata error:%{public}d", ret);
            return UDMF_ERR;
        }
        if (unifiedDataSet.empty()) {
            return UDMF_E_OK;
        } else {
            data->unifiedData_ = std::make_shared<OHOS::UDMF::UnifiedData>(unifiedDataSet[0]);
        }
    }
    return UDMF_E_OK;
}

int OH_Udmf_GetUnifiedDataByOptions(OH_UdmfOptions* options, OH_UdmfData** dataArray, unsigned int* dataSize)
{
    if (options == nullptr || dataSize == nullptr || dataArray == nullptr) {
        LOG_ERROR(UDMF_CAPI, "The input param error");
        return UDMF_E_INVALID_PARAM;
    }
    Intention queryOptIntent;
    switch (options->intention) {
        case UDMF_INTENTION_DATA_HUB:
            queryOptIntent = Intention::UD_INTENTION_DATA_HUB;
            break;
        case UDMF_INTENTION_SYSTEM_SHARE:
            queryOptIntent = Intention::UD_INTENTION_SYSTEM_SHARE;
            break;
        case UDMF_INTENTION_PICKER:
            queryOptIntent = Intention::UD_INTENTION_PICKER;
            break;
        case UDMF_INTENTION_MENU:
            queryOptIntent = Intention::UD_INTENTION_MENU;
            break;
        default:
            LOG_ERROR(UDMF_CAPI, "Intention error, it's not one of the above enumerations");
            return UDMF_E_INVALID_PARAM;
    }
    QueryOption query = {.key = std::string(options->key), .intention = queryOptIntent};

    std::vector<UnifiedData> unifiedData;
    int32_t ret = UdmfClient::GetInstance().GetBatchData(query, unifiedData);
    if (ret != E_OK) {
        LOG_ERROR(UDMF_CAPI, "Get batch data error,ret = %{public}d", ret);
        return UDMF_ERR;
    }
    *dataSize = unifiedData.size();
    if (*dataSize == 0) {
        return E_OK;
    }
    *dataArray = new (std::nothrow) OH_UdmfData[*dataSize];
    if (*dataArray == nullptr) {
        LOG_ERROR(UDMF_CAPI, "New dataArray error");
        return UDMF_ERR;
    }
    for (unsigned int i = 0; i < *dataSize; i++) {
        (*dataArray)[i].unifiedData_ = std::make_shared<UnifiedData>(unifiedData[i]);
    }
    return UDMF_E_OK;
}

int OH_Udmf_SetUnifiedData(Udmf_Intention intention, OH_UdmfData* unifiedData, char* key, unsigned int keyLen)
{
    if (!IsUnifiedDataValid(unifiedData) || key == nullptr || keyLen < UDMF_KEY_BUFFER_LEN) {
        return UDMF_E_INVALID_PARAM;
    }
    Intention customOptIntent;
    auto it = VAILD_INTENTIONS.find(intention);
    if (it != VAILD_INTENTIONS.end()) {
        customOptIntent = it->second;
    } else {
        LOG_ERROR(UDMF_CAPI, "The intention is invalid");
        return UDMF_E_INVALID_PARAM;
    }
    CustomOption option = {.intention = customOptIntent};
    std::string keyStr;
    if ((UdmfClient::GetInstance().SetData(option, *(unifiedData->unifiedData_), keyStr)) != E_OK) {
        LOG_ERROR(UDMF_CAPI, "Set data error");
        return UDMF_ERR;
    }
    if (strcpy_s(key, keyLen, keyStr.c_str()) != EOK) {
        LOG_ERROR(UDMF_CAPI, "String copy failed");
        return UDMF_ERR;
    }
    return UDMF_E_OK;
}

int OH_Udmf_SetUnifiedDataByOptions(OH_UdmfOptions* options, OH_UdmfData* unifiedData, char* key, unsigned int keyLen)
{
    if (!IsUnifiedDataValid(unifiedData) || key == nullptr || keyLen < UDMF_KEY_BUFFER_LEN || options == nullptr) {
        LOG_ERROR(UDMF_CAPI, "The set param invalid");
        return UDMF_E_INVALID_PARAM;
    }
    Intention customOptIntent;
    switch (options->intention) {
        case UDMF_INTENTION_DATA_HUB:
            customOptIntent = Intention::UD_INTENTION_DATA_HUB;
            break;
        case UDMF_INTENTION_SYSTEM_SHARE:
            customOptIntent = Intention::UD_INTENTION_SYSTEM_SHARE;
            break;
        case UDMF_INTENTION_PICKER:
            customOptIntent = Intention::UD_INTENTION_PICKER;
            break;
        case UDMF_INTENTION_MENU:
            customOptIntent = Intention::UD_INTENTION_MENU;
            break;
        default:
            LOG_ERROR(UDMF_CAPI, "Intention error, it's not one of the above enumerations");
            return UDMF_E_INVALID_PARAM;
    }
    CustomOption option = {.intention = customOptIntent};
    std::string keyStr;
    int32_t ret = UdmfClient::GetInstance().SetData(option, *(unifiedData->unifiedData_), keyStr);
    if (ret != E_OK) {
        LOG_ERROR(UDMF_CAPI, "Set data error,ret = %{public}d", ret);
        return UDMF_ERR;
    }
    if (strcpy_s(key, keyLen, keyStr.c_str()) != E_OK) {
        LOG_ERROR(UDMF_CAPI, "String copy failed");
        return UDMF_ERR;
    }
    return UDMF_E_OK;
}

int OH_Udmf_UpdateUnifiedData(OH_UdmfOptions* options, OH_UdmfData* unifiedData)
{
    if (!IsUnifiedDataValid(unifiedData) || options->key.empty()) {
        LOG_ERROR(UDMF_CAPI, "The update error, lnvaild params!");
        return UDMF_E_INVALID_PARAM;
    }
    if (options->intention != UDMF_INTENTION_DATA_HUB) {
        LOG_ERROR(UDMF_CAPI, "Intention error, Intention is %{public}d", options->intention);
        return UDMF_E_INVALID_PARAM;
    }
    QueryOption query = {.key = options->key};
    int32_t ret = UdmfClient::GetInstance().UpdateData(query, *(unifiedData->unifiedData_));
    if (ret != E_OK) {
        LOG_ERROR(UDMF_CAPI, "Updata error,ret = %{public}d", ret);
        return UDMF_ERR;
    }
    return UDMF_E_OK;
}

int OH_Udmf_DeleteUnifiedData(OH_UdmfOptions* options, OH_UdmfData** dataArray, unsigned int* dataSize)
{
    if (options == nullptr || dataSize == nullptr || dataArray == nullptr) {
        LOG_ERROR(UDMF_CAPI, "The delete param invalid");
        return UDMF_E_INVALID_PARAM;
    }
    Intention queryOptIntent;
    switch (options->intention) {
        case UDMF_INTENTION_DATA_HUB:
            queryOptIntent = Intention::UD_INTENTION_DATA_HUB;
            break;
        case UDMF_INTENTION_SYSTEM_SHARE:
            queryOptIntent = Intention::UD_INTENTION_SYSTEM_SHARE;
            break;
        case UDMF_INTENTION_PICKER:
            queryOptIntent = Intention::UD_INTENTION_PICKER;
            break;
        case UDMF_INTENTION_MENU:
            queryOptIntent = Intention::UD_INTENTION_MENU;
            break;
        default:
            LOG_ERROR(UDMF_CAPI, "Intention error, it's not one of the above enumerations");
            return UDMF_E_INVALID_PARAM;
    }
    QueryOption query = {.key = options->key, .intention = queryOptIntent};
    std::vector<UnifiedData> unifiedData;
    int32_t ret = UdmfClient::GetInstance().DeleteData(query, unifiedData);
    if (ret != E_OK) {
        LOG_ERROR(UDMF_CAPI, "Delete data error,key is %{public}s, ret = %{public}d",
            query.key.c_str(), ret);
        return UDMF_ERR;
    }
    *dataSize = unifiedData.size();
    *dataArray = new (std::nothrow) OH_UdmfData[*dataSize];
    if (*dataArray == nullptr) {
        LOG_ERROR(UDMF_CAPI, "New dataArray error");
        return UDMF_ERR;
    }
    for (unsigned int i = 0; i < *dataSize; i++) {
        (*dataArray)[i].unifiedData_ = std::make_shared<UnifiedData>(unifiedData[i]);
    }
    return UDMF_E_OK;
}

void OH_Udmf_DestroyDataArray(OH_UdmfData** dataArray, unsigned int dataSize)
{
    if (dataArray == nullptr || *dataArray == nullptr) {
        LOG_ERROR(UDMF_CAPI, "The DestroyDataArray error, invaild params!");
        return;
    }
    delete[] *dataArray;
    *dataArray = nullptr;
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
    DestroyStringArray(record->typesArray, record->typesCount);
    delete record;
}

int OH_UdmfRecord_AddGeneralEntry(OH_UdmfRecord* record, const char* typeId,
                                  const unsigned char* entry, unsigned int count)
{
    if (!IsUnifiedRecordValid(record) || typeId == nullptr || entry == nullptr || count == 0 ||
        count > MAX_GENERAL_ENTRY_SIZE || strlen(typeId) > MAX_KEY_STRING_LEN) {
        return UDMF_E_INVALID_PARAM;
    }
    std::vector<uint8_t> recordValue(entry, entry + count);
    auto obj = std::make_shared<Object>();
    obj->value_[UNIFORM_DATA_TYPE] = typeId;
    obj->value_[ARRAY_BUFFER] = recordValue;
    obj->value_[ARRAY_BUFFER_LENGTH] = static_cast<int>(recordValue.size());
    if (record->record_->GetType() == UD_BUTT) {
        record->record_ = std::make_shared<ApplicationDefinedRecord>(APPLICATION_DEFINED_RECORD, obj);
        record->record_->SetUtdId(typeId);
    } else {
        record->record_->AddEntry(typeId, obj);
    }
    record->recordDataLen = count;
    return UDMF_E_OK;
}

static int GetValueFromUint8Array(OH_UdmfRecord *record, const char *typeId, ValueType value)
{
    if (!std::holds_alternative<std::shared_ptr<Object>>(value)) {
        LOG_ERROR(UDMF_CAPI, "valueType is not object sptr!");
        return UDMF_ERR;
    }
    auto obj = std::get<std::shared_ptr<Object>>(value);
    if (obj == nullptr) {
        LOG_ERROR(UDMF_CAPI, "object is nullptr!");
        return UDMF_ERR;
    }
    std::vector<uint8_t> recordValue;
    int recordDataLen;
    obj->GetValue(ARRAY_BUFFER, recordValue);
    obj->GetValue(ARRAY_BUFFER_LENGTH, recordDataLen);
    record->recordDataLen = recordValue.size();
    if (record->recordDataLen > MAX_GENERAL_ENTRY_SIZE) {
        LOG_INFO(UDMF_CAPI, "data size exceeds maximum size");
        return UDMF_ERR;
    }
    record->recordData = new (std::nothrow) unsigned char[record->recordDataLen];
    if (record->recordData == nullptr) {
        return UDMF_ERR;
    }
    auto err = memcpy_s(record->recordData, record->recordDataLen, recordValue.data(), record->recordDataLen);
    if (err != EOK) {
        LOG_ERROR(UDMF_CAPI, "memcpy error! type:%{public}s", typeId);
        return UDMF_ERR;
    }
    record->lastType = const_cast<char*>(typeId);
    return UDMF_E_OK;
}

int OH_UdmfRecord_GetGeneralEntry(OH_UdmfRecord* record, const char* typeId, unsigned char** entry, unsigned int* count)
{
    if (!IsUnifiedRecordValid(record) || typeId == nullptr || entry == nullptr || count == nullptr) {
        return UDMF_E_INVALID_PARAM;
    }
    std::lock_guard<std::mutex> lock(record->mutex);
    if (!record->record_->HasType(typeId)) {
        LOG_ERROR(UDMF_CAPI, "no type:%{public}s", typeId);
        return UDMF_E_INVALID_PARAM;
    }
    if (record->lastType == typeId && record->recordData != nullptr) {
        LOG_DEBUG(UDMF_CAPI, "return cache value");
        *entry = record->recordData;
        *count = record->recordDataLen;
        return UDMF_E_OK;
    }
    record->record_->InitObject();
    auto value = record->record_->GetEntry(typeId);
    if (!std::holds_alternative<std::shared_ptr<Object>>(value)) {
        LOG_ERROR(UDMF_CAPI, "Not contains right data type.");
        return UDMF_ERR;
    }
    auto result = GetValueFromUint8Array(record, typeId, value);
    if (result != UDMF_E_OK) {
        LOG_ERROR(UDMF_CAPI, "Get value from valueType failed. typeId: %{public}s, result: %{public}d", typeId, result);
        return result;
    }
    *count = record->recordDataLen;
    *entry = record->recordData;
    return UDMF_E_OK;
}

template<typename T>
void AddUds(OH_UdmfRecord* record, UdsObject* udsObject, UDType type)
{
    if (record->record_->GetType() == UD_BUTT) {
        record->record_ = std::make_shared<T>(type, udsObject->obj);
    } else {
        record->record_->AddEntry(UtdUtils::GetUtdIdFromUtdEnum(type), udsObject->obj);
    }
}

int OH_UdmfRecord_AddPlainText(OH_UdmfRecord* record, OH_UdsPlainText* plainText)
{
    if (!IsUnifiedRecordValid(record) || IsInvalidUdsObjectPtr(plainText, UDS_PLAIN_TEXT_STRUCT_ID)) {
        return UDMF_E_INVALID_PARAM;
    }
    AddUds<PlainText>(record, plainText, PLAIN_TEXT);
    return UDMF_E_OK;
}

int OH_UdmfRecord_AddHyperlink(OH_UdmfRecord* record, OH_UdsHyperlink* hyperlink)
{
    if (!IsUnifiedRecordValid(record) || IsInvalidUdsObjectPtr(hyperlink, UDS_HYPERLINK_STRUCT_ID)) {
        return UDMF_E_INVALID_PARAM;
    }
    AddUds<Link>(record, hyperlink, HYPERLINK);
    return UDMF_E_OK;
}

int OH_UdmfRecord_AddHtml(OH_UdmfRecord* record, OH_UdsHtml* html)
{
    if (!IsUnifiedRecordValid(record) || IsInvalidUdsObjectPtr(html, UDS_HTML_STRUCT_ID)) {
        return UDMF_E_INVALID_PARAM;
    }
    AddUds<Html>(record, html, HTML);
    return UDMF_E_OK;
}

int OH_UdmfRecord_AddAppItem(OH_UdmfRecord* record, OH_UdsAppItem* appItem)
{
    if (!IsUnifiedRecordValid(record) || IsInvalidUdsObjectPtr(appItem, UDS_APP_ITEM_STRUCT_ID)) {
        return UDMF_E_INVALID_PARAM;
    }
    AddUds<SystemDefinedAppItem>(record, appItem, SYSTEM_DEFINED_APP_ITEM);
    return UDMF_E_OK;
}

int OH_UdmfRecord_AddFileUri(OH_UdmfRecord* record, OH_UdsFileUri* fileUri)
{
    if (!IsUnifiedRecordValid(record) || IsInvalidUdsObjectPtr(fileUri, UDS_FILE_URI_STRUCT_ID)) {
        return UDMF_E_INVALID_PARAM;
    }
    std::string* fileType = std::get_if<std::string>(&(fileUri->obj->value_[FILE_TYPE]));
    if (fileType == nullptr) {
        return UDMF_ERR;
    }
    std::map<UDType, std::function<void(OH_UdmfRecord*, OH_UdsFileUri*)>> addFileUriFuncs = {
        {UDType::FILE, [](OH_UdmfRecord* record, OH_UdsFileUri* fileUri)
            { AddUds<File>(record, fileUri, UDType::FILE); }},
        {UDType::IMAGE, [](OH_UdmfRecord* record, OH_UdsFileUri* fileUri)
            { AddUds<Image>(record, fileUri, UDType::IMAGE); }},
        {UDType::VIDEO, [](OH_UdmfRecord* record, OH_UdsFileUri* fileUri)
            {  AddUds<Video>(record, fileUri, UDType::VIDEO); }},
        {UDType::AUDIO, [](OH_UdmfRecord* record, OH_UdsFileUri* fileUri)
            {  AddUds<Audio>(record, fileUri, UDType::AUDIO); }},
        {UDType::FOLDER, [](OH_UdmfRecord* record, OH_UdsFileUri* fileUri)
            {  AddUds<Folder>(record, fileUri, UDType::FOLDER); }},
    };
    int32_t utdId = UDType::FILE;
    std::shared_ptr<TypeDescriptor> descriptor;
    UtdClient::GetInstance().GetTypeDescriptor(*fileType, descriptor);
    if (descriptor != nullptr) {
        bool isFileType = false;
        for (const auto &fileSub : FILE_SUB_TYPES) {
            descriptor->BelongsTo(fileSub, isFileType);
            if (isFileType) {
                utdId = static_cast<UDType>(UtdUtils::GetUtdEnumFromUtdId(fileSub));
                break;
            }
        }
    }
    addFileUriFuncs[static_cast<UDType>(utdId)](record, fileUri);
    return UDMF_E_OK;
}

int OH_UdmfRecord_AddPixelMap(OH_UdmfRecord* record, OH_UdsPixelMap* pixelMap)
{
    if (!IsUnifiedRecordValid(record) || IsInvalidUdsObjectPtr(pixelMap, UDS_PIXEL_MAP_STRUCT_ID)) {
        return UDMF_E_INVALID_PARAM;
    }
    AddUds<SystemDefinedPixelMap>(record, pixelMap, UDType::SYSTEM_DEFINED_PIXEL_MAP);
    return UDMF_E_OK;
}

int GetUds(OH_UdmfRecord* record, UdsObject* udsObject, UDType type)
{
    record->record_->InitObject();
    auto value = record->record_->GetEntry(UtdUtils::GetUtdIdFromUtdEnum(type));
    if (!std::holds_alternative<std::shared_ptr<Object>>(value)) {
        return UDMF_ERR;
    }
    udsObject->obj = std::get<std::shared_ptr<Object>>(value);
    return UDMF_E_OK;
}

int OH_UdmfRecord_AddArrayBuffer(OH_UdmfRecord* record, const char* type, OH_UdsArrayBuffer* buffer)
{
    if (!IsUnifiedRecordValid(record) || type == nullptr || strlen(type) > MAX_KEY_STRING_LEN ||
        IsInvalidUdsObjectPtr(buffer, UDS_ARRAY_BUFFER_STRUCT_ID)) {
        return UDMF_E_INVALID_PARAM;
    }
    unsigned char *entry;
    unsigned int size;
    int ret = OH_UdsArrayBuffer_GetData(buffer, &entry, &size);
    if (ret != UDMF_E_OK) {
        return UDMF_E_INVALID_PARAM;
    }
    buffer->obj->value_[UNIFORM_DATA_TYPE] = type;
    return OH_UdmfRecord_AddGeneralEntry(record, type, entry, size);
}

int OH_UdmfRecord_AddContentForm(OH_UdmfRecord* record, OH_UdsContentForm* contentForm)
{
    if (!IsUnifiedRecordValid(record) || IsInvalidUdsObjectPtr(contentForm, UDS_CONTENT_FORM_STRUCT_ID)) {
        return UDMF_E_INVALID_PARAM;
    }
    AddUds<UnifiedRecord>(record, contentForm, UDType::CONTENT_FORM);
    return UDMF_E_OK;
}

int OH_UdmfRecord_GetPlainText(OH_UdmfRecord* record, OH_UdsPlainText* plainText)
{
    if (!IsUnifiedRecordValid(record) || IsInvalidUdsObjectPtr(plainText, UDS_PLAIN_TEXT_STRUCT_ID)) {
        return UDMF_E_INVALID_PARAM;
    }
    return GetUds(record, plainText, PLAIN_TEXT);
}

int OH_UdmfRecord_GetHyperlink(OH_UdmfRecord* record, OH_UdsHyperlink* hyperlink)
{
    if (!IsUnifiedRecordValid(record) || IsInvalidUdsObjectPtr(hyperlink, UDS_HYPERLINK_STRUCT_ID)) {
        return UDMF_E_INVALID_PARAM;
    }
    return GetUds(record, hyperlink, HYPERLINK);
}

int OH_UdmfRecord_GetHtml(OH_UdmfRecord* record, OH_UdsHtml* html)
{
    if (!IsUnifiedRecordValid(record) || IsInvalidUdsObjectPtr(html, UDS_HTML_STRUCT_ID)) {
        return UDMF_E_INVALID_PARAM;
    }
    return GetUds(record, html, HTML);
}

int OH_UdmfRecord_GetAppItem(OH_UdmfRecord* record, OH_UdsAppItem* appItem)
{
    if (!IsUnifiedRecordValid(record) || IsInvalidUdsObjectPtr(appItem, UDS_APP_ITEM_STRUCT_ID)) {
        return UDMF_E_INVALID_PARAM;
    }
    return GetUds(record, appItem, SYSTEM_DEFINED_APP_ITEM);
}

int OH_UdmfRecord_GetFileUri(OH_UdmfRecord* record, OH_UdsFileUri* fileUri)
{
    if (!IsUnifiedRecordValid(record) || IsInvalidUdsObjectPtr(fileUri, UDS_FILE_URI_STRUCT_ID)) {
        return UDMF_E_INVALID_PARAM;
    }
    if (GetUds(record, fileUri, UDType::FILE_URI) == UDMF_E_OK) {
        return UDMF_E_OK;
    }
    for (auto fileType : FILE_TYPES) {
        int ret = GetUds(record, fileUri, fileType.second);
        if (ret == UDMF_E_OK) {
            fileUri->obj->value_[UNIFORM_DATA_TYPE] = UDMF_META_GENERAL_FILE_URI;
            fileUri->obj->value_[FILE_TYPE] = UtdUtils::GetUtdIdFromUtdEnum(fileType.second);
            return UDMF_E_OK;
        }
    }
    LOG_ERROR(UDMF_CAPI, "could't find file uri");
    return UDMF_E_INVALID_PARAM;
}

int OH_UdmfRecord_GetPixelMap(OH_UdmfRecord* record, OH_UdsPixelMap* pixelMap)
{
    if (!IsUnifiedRecordValid(record) || IsInvalidUdsObjectPtr(pixelMap, UDS_PIXEL_MAP_STRUCT_ID)) {
        return UDMF_E_INVALID_PARAM;
    }
    return GetUds(record, pixelMap, UDType::SYSTEM_DEFINED_PIXEL_MAP);
}

int OH_UdmfRecord_GetArrayBuffer(OH_UdmfRecord* record, const char* type, OH_UdsArrayBuffer* buffer)
{
    unsigned int size = 0;
    unsigned char *entry;
    int ret = OH_UdmfRecord_GetGeneralEntry(record, type, &entry, &size);
    if (ret != UDMF_E_OK) {
        LOG_ERROR(UDMF_CAPI, "OH_UdmfRecord_GetGeneralEntry ret: %{public}d.", ret);
        return ret;
    }
    return OH_UdsArrayBuffer_SetData(buffer, entry, size);
}

int OH_UdmfRecord_GetContentForm(OH_UdmfRecord* record, OH_UdsContentForm* contentForm)
{
    if (!IsUnifiedRecordValid(record) || IsInvalidUdsObjectPtr(contentForm, UDS_CONTENT_FORM_STRUCT_ID)) {
        return UDMF_E_INVALID_PARAM;
    }
    return GetUds(record, contentForm, UDType::CONTENT_FORM);
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
        case ShareOptions::CROSS_DEVICE:
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

OH_UdmfRecordProvider* OH_UdmfRecordProvider_Create()
{
    OH_UdmfRecordProvider* provider = new (std::nothrow) OH_UdmfRecordProvider();
    if (provider == nullptr) {
        LOG_ERROR(UDMF_CAPI, "allocate OH_UdmfRecordProvider memory fail");
    }
    return provider;
}

int OH_UdmfRecordProvider_Destroy(OH_UdmfRecordProvider* provider)
{
    if (provider == nullptr) {
        return UDMF_E_INVALID_PARAM;
    }
    if (provider->context != nullptr && provider->finalize != nullptr) {
        (provider->finalize)(provider->context);
        LOG_INFO(UDMF_CAPI, "free context finished");
    }
    delete provider;
    return UDMF_E_OK;
}

int OH_UdmfRecordProvider_SetData(OH_UdmfRecordProvider* provider, void* context,
    const OH_UdmfRecordProvider_GetData callback, const UdmfData_Finalize finalize)
{
    if (provider == nullptr || callback == nullptr) {
        return UDMF_E_INVALID_PARAM;
    }
    provider->callback = callback;
    if (context != nullptr && finalize == nullptr) {
        LOG_ERROR(UDMF_CAPI, "finalize function is null when context not null");
        return UDMF_E_INVALID_PARAM;
    }
    provider->context = context;
    provider->finalize = finalize;
    return UDMF_E_OK;
}

int OH_UdmfRecord_SetProvider(OH_UdmfRecord* record, const char* const* types, unsigned int count,
    OH_UdmfRecordProvider* provider)
{
    if (!IsUnifiedRecordValid(record) || types == nullptr || count == 0 || provider == nullptr) {
        return UDMF_E_INVALID_PARAM;
    }
    std::shared_ptr<DataProviderImpl> providerBox = std::make_shared<DataProviderImpl>();
    providerBox->SetInnerProvider(provider);
    std::vector<std::string> udTypes;
    std::set<std::string> udTypeSet;
    for (unsigned int i = 0; i < count; ++i) {
        if (types[i] == nullptr) {
            LOG_ERROR(UDMF_CAPI, "The type with index %{public}d is empty", i);
            continue;
        }
        if (udTypeSet.count(types[i]) == 0) {
            udTypeSet.emplace(types[i]);
            udTypes.emplace_back(types[i]);
        }
    }
    record->record_->SetEntryGetter(udTypes, providerBox);
    return UDMF_E_OK;
}

int OH_UdmfProgressInfo_GetProgress(OH_Udmf_ProgressInfo* progressInfo)
{
    return progressInfo->progress;
}

int OH_UdmfProgressInfo_GetStatus(OH_Udmf_ProgressInfo* progressInfo)
{
    return progressInfo->status;
}

OH_UdmfGetDataParams* OH_UdmfGetDataParams_Create()
{
    OH_UdmfGetDataParams *params =  new (std::nothrow) OH_UdmfGetDataParams();
    if (params == nullptr) {
        LOG_ERROR(UDMF_CAPI, "allocate OH_UdmfGetDataParams memory fail");
        return nullptr;
    }
    return params;
}

void OH_UdmfGetDataParams_Destroy(OH_UdmfGetDataParams* pThis)
{
    if (pThis == nullptr) {
        return;
    }
    delete pThis;
}

void OH_UdmfGetDataParams_SetDestUri(OH_UdmfGetDataParams* params, const char* destUri)
{
    if (destUri == nullptr) {
        return;
    }
    params->destUri = std::string(destUri);
}

void OH_UdmfGetDataParams_SetFileConflictOptions(OH_UdmfGetDataParams* params, const Udmf_FileConflictOptions options)
{
    if (params == nullptr) {
        return;
    }
    params->fileConflictOptions = options;
}

void OH_UdmfGetDataParams_SetProgressIndicator(OH_UdmfGetDataParams* params,
    const Udmf_ProgressIndicator progressIndicator)
{
    if (params == nullptr) {
        return;
    }
    params->progressIndicator = progressIndicator;
}

void OH_UdmfGetDataParams_SetDataProgressListener(OH_UdmfGetDataParams* params,
    const OH_Udmf_DataProgressListener dataProgressListener)
{
    if (params == nullptr) {
        return;
    }
    params->dataProgressListener = dataProgressListener;
}