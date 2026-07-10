/*
 * Copyright (c) 2026 Huawei Device Co., Ltd.
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

#define LOG_TAG "AuditHelper"
#include "audit_helper.h"
#include "common_event_manager.h"
#include "common_event_data.h"
#include "common_event_publish_info.h"
#include "want.h"
#include "logger.h"
#include "unified_data.h"
#include "unified_record.h"
#include "unified_meta.h"
#include "udmf_executor.h"
#include <nlohmann/json.hpp>
#include <chrono>

namespace OHOS {
namespace UDMF {

constexpr const char *DRAG_AUDIT_EVENT = "usual.event.DRAG_AUDIT";
static constexpr size_t MAX_THREADS = 10;
static constexpr size_t MIN_THREADS = 0;
static constexpr size_t MAX_DATA_SIZE = 10 * 1024;
static constexpr size_t ENTRIES_BUDGET_RATIO = 60;
static constexpr size_t JSON_NULL_SIZE = 4;
static constexpr size_t JSON_BOOL_SIZE = 5;
static constexpr size_t JSON_NUMBER_SIZE = 16;
static constexpr size_t JSON_STRING_DELIMITER_SIZE = 2;
static constexpr size_t JSON_ESCAPED_CHAR_SIZE = 2;
static constexpr size_t JSON_ARRAY_OVERHEAD = 2;
static constexpr size_t JSON_OBJECT_OVERHEAD = 2;
static constexpr size_t JSON_KEY_OVERHEAD = 4;
static constexpr size_t JSON_KEY_VALUE_SEPARATOR = 4;
static constexpr size_t JSON_CHAR_SIZE = 1;
static constexpr size_t JSON_ARRAY_SEPARATOR_SIZE = 1;
static constexpr size_t BASE64_ENCODING_RATIO_NUMERATOR = 4;
static constexpr size_t BASE64_ENCODING_RATIO_DENOMINATOR = 3;
static constexpr size_t PERCENTAGE_DENOMINATOR = 100;
static constexpr size_t MAX_WANT_TRUNCATE_ITERATIONS = 20;
static constexpr size_t MAX_ROOT_TRUNCATE_ITERATIONS = 100;

static UdmfExecutor &GetAuditExecutor()
{
    static UdmfExecutor auditExecutor(MAX_THREADS, MIN_THREADS);
    return auditExecutor;
}

size_t AuditHelper::GetUtf8PrefixLength(const std::string &value, size_t maxBytes)
{
    size_t end = std::min(value.size(), maxBytes);
    while (end > 0 && end < value.size() && ((static_cast<uint8_t>(value[end]) & 0xC0U) == 0x80U)) {
        --end;
    }
    return end;
}

size_t AuditHelper::EstimateJsonSize(const nlohmann::json &json)
{
    if (json.is_null()) {
        return JSON_NULL_SIZE;
    }
    if (json.is_boolean()) {
        return JSON_BOOL_SIZE;
    }
    if (json.is_number()) {
        return JSON_NUMBER_SIZE;
    }
    if (json.is_string()) {
        size_t size = JSON_STRING_DELIMITER_SIZE;
        for (char c : json.get_ref<const std::string&>()) {
            if (c == '"' || c == '\\' || c == '\n' || c == '\r' || c == '\t' || c < 0x20) {
                size += JSON_ESCAPED_CHAR_SIZE;
            } else {
                size += JSON_CHAR_SIZE;
            }
        }
        return size;
    }
    if (json.is_binary()) {
        size_t binarySize = json.get_binary().size();
        return binarySize * BASE64_ENCODING_RATIO_NUMERATOR / BASE64_ENCODING_RATIO_DENOMINATOR +
               JSON_STRING_DELIMITER_SIZE;
    }
    if (json.is_array()) {
        size_t size = JSON_ARRAY_OVERHEAD;
        for (const auto &item : json) {
            size += EstimateJsonSize(item) + JSON_ARRAY_SEPARATOR_SIZE;
        }
        return size > JSON_ARRAY_OVERHEAD ? size - JSON_ARRAY_SEPARATOR_SIZE : size;
    }
    if (json.is_object()) {
        size_t size = JSON_OBJECT_OVERHEAD;
        for (auto it = json.begin(); it != json.end(); ++it) {
            size += it.key().size() + EstimateJsonSize(it.value()) + JSON_KEY_VALUE_SEPARATOR;
        }
        return size;
    }
    return JSON_NUMBER_SIZE;
}

void AuditHelper::TruncateJsonValue(nlohmann::json &json)
{
    auto it = json.begin();
    if (!it->is_string()) {
        return;
    }
    std::string val = it->get<std::string>();
    size_t maxLen = MAX_DATA_SIZE - 10;
    if (val.size() <= maxLen) {
        return;
    }
    size_t end = GetUtf8PrefixLength(val, maxLen);
    it.value() = val.substr(0, end);
}

void AuditHelper::TruncateWantJson(nlohmann::json &wantJson)
{
    for (size_t i = 0; i < MAX_WANT_TRUNCATE_ITERATIONS && EstimateJsonSize(wantJson) > MAX_DATA_SIZE; ++i) {
        if (wantJson.size() > 1) {
            wantJson.erase(std::prev(wantJson.end()));
        } else {
            TruncateJsonValue(wantJson);
            break;
        }
    }
}

nlohmann::json AuditHelper::ConvertWantToJson(std::shared_ptr<OHOS::AAFwk::Want> want)
{
    nlohmann::json wantJson;
    if (want == nullptr) {
        return wantJson;
    }

    wantJson["action"] = want->GetAction();
    wantJson["bundle"] = want->GetBundle();
    wantJson["deviceId"] = want->GetDeviceId();
    wantJson["moduleName"] = want->GetModuleName();
    wantJson["type"] = want->GetType();
    wantJson["flags"] = want->GetFlags();
    wantJson["uri"] = want->GetUriString();

    auto element = want->GetElement();
    nlohmann::json elementJson;
    elementJson["uri"] = element.GetURI();
    wantJson["element"] = elementJson;

    TruncateWantJson(wantJson);
    return wantJson;
}

nlohmann::json AuditHelper::ConvertPixelMapToJson(std::shared_ptr<OHOS::Media::PixelMap> pixelMap)
{
    nlohmann::json pixelMapJson;
    if (pixelMap == nullptr) {
        return pixelMapJson;
    }
    std::vector<uint8_t> encodedData;
    PixelMapLoader loader;
    if (loader.EncodeTlv(pixelMap, encodedData)) {
        if (encodedData.size() > MAX_DATA_SIZE) {
            LOG_WARN(UDMF_CLIENT, "PixelMap data size %{public}zu exceeds limit %{public}zu, truncated",
                     encodedData.size(), MAX_DATA_SIZE);
            encodedData.resize(MAX_DATA_SIZE);
        }
        pixelMapJson["encodedData"] = nlohmann::json::binary(encodedData);
    } else {
        LOG_ERROR(UDMF_CLIENT, "Encode pixelMap error");
    }

    return pixelMapJson;
}

nlohmann::json AuditHelper::ConvertObjectToJson(std::shared_ptr<Object> object)
{
    if (object == nullptr) {
        return nlohmann::json::object();
    }

    return ConvertEntriesToJson(object->value_);
}

nlohmann::json AuditHelper::ConvertValueToJson(const ValueType &value)
{
    if (std::holds_alternative<std::monostate>(value)) {
        return nullptr;
    } else if (std::holds_alternative<int32_t>(value)) {
        return std::get<int32_t>(value);
    } else if (std::holds_alternative<int64_t>(value)) {
        return std::get<int64_t>(value);
    } else if (std::holds_alternative<double>(value)) {
        return std::get<double>(value);
    } else if (std::holds_alternative<bool>(value)) {
        return std::get<bool>(value);
    } else if (std::holds_alternative<std::string>(value)) {
        auto str = std::get<std::string>(value);
        if (str.size() > MAX_DATA_SIZE) {
            LOG_WARN(UDMF_CLIENT, "String data size %{public}zu exceeds limit %{public}zu, truncated",
                     str.size(), MAX_DATA_SIZE);
            str.resize(MAX_DATA_SIZE);
        }
        return str;
    } else if (std::holds_alternative<std::vector<uint8_t>>(value)) {
        auto bytes = std::get<std::vector<uint8_t>>(value);
        if (bytes.size() > MAX_DATA_SIZE) {
            LOG_WARN(UDMF_CLIENT, "Bytes data size %{public}zu exceeds limit %{public}zu, truncated",
                     bytes.size(), MAX_DATA_SIZE);
            bytes.resize(MAX_DATA_SIZE);
        }
        return nlohmann::json::binary(bytes);
    } else if (std::holds_alternative<std::shared_ptr<OHOS::AAFwk::Want>>(value)) {
        auto want = std::get<std::shared_ptr<OHOS::AAFwk::Want>>(value);
        return ConvertWantToJson(want);
    } else if (std::holds_alternative<std::shared_ptr<OHOS::Media::PixelMap>>(value)) {
        auto pixelMap = std::get<std::shared_ptr<OHOS::Media::PixelMap>>(value);
        return ConvertPixelMapToJson(pixelMap);
    } else if (std::holds_alternative<std::shared_ptr<Object>>(value)) {
        auto object = std::get<std::shared_ptr<Object>>(value);
        return ConvertObjectToJson(object);
    } else if (std::holds_alternative<std::nullptr_t>(value)) {
        return nullptr;
    }
    return nullptr;
}

nlohmann::json AuditHelper::ConvertEntriesToJson(const std::map<std::string, ValueType> &entries)
{
    nlohmann::json entriesJson = nlohmann::json::object();
    size_t budget = MAX_DATA_SIZE * ENTRIES_BUDGET_RATIO / PERCENTAGE_DENOMINATOR;
    size_t currentSize = JSON_OBJECT_OVERHEAD;
    
    for (const auto &[key, val] : entries) {
        nlohmann::json valueJson = ConvertValueToJson(val);
        size_t valueSize = EstimateJsonSize(valueJson);
        
        size_t entryCost = key.size() + valueSize + JSON_KEY_OVERHEAD;
        if (currentSize + entryCost > budget) {
            break;
        }
        
        entriesJson[key] = valueJson;
        currentSize += entryCost;
    }
    
    return entriesJson;
}

nlohmann::json AuditHelper::ConvertRecordToJson(std::shared_ptr<UnifiedRecord> record, size_t index)
{
    auto entries = record->GetEntries();
    if (entries != nullptr && !entries->empty()) {
        return ConvertEntriesToJson(*entries);
    }
    return nlohmann::json::object();
}

void AuditHelper::PublishAuditEvent(const std::string &auditData)
{
    AAFwk::Want want;
    want.SetAction(DRAG_AUDIT_EVENT);
    want.SetParam("auditData", auditData);

    EventFwk::CommonEventData event(want);
    EventFwk::CommonEventPublishInfo publishInfo;
    publishInfo.SetOrdered(true);
    int32_t ret = EventFwk::CommonEventManager::NewPublishCommonEvent(event, publishInfo);
    if (ret != 0) {
        LOG_ERROR(UDMF_CLIENT, "Failed to publish drag audit event, ret = %{public}d", ret);
    } else {
        LOG_INFO(UDMF_CLIENT, "Drag audit event published successfully");
    }
}

void AuditHelper::ReportDragAuditEvent(const UnifiedData &unifiedData, int32_t userId, uint32_t tokenId)
{
    nlohmann::json root;
    root["sourceTokenId"] = 0;
    root["targetTokenId"] = tokenId;
    root["userId"] = userId;
    root["content"] = nlohmann::json::object();
    root["happenTime"] = 0;

    size_t overhead = root.dump().size();
    if (overhead >= MAX_DATA_SIZE) {
        LOG_ERROR(UDMF_CLIENT, "Fixed overhead %{public}zu exceeds limit", overhead);
        return;
    }
    size_t budget = MAX_DATA_SIZE - overhead;

    nlohmann::json recordsJson = nlohmann::json::array();
    auto records = unifiedData.GetRecords();

    auto runtime = unifiedData.GetRuntime();
    if (runtime != nullptr) {
        root["sourceTokenId"] = runtime->tokenId;
    }

    for (size_t i = 0; i < records.size(); ++i) {
        nlohmann::json recordJson = ConvertRecordToJson(records[i], i);
        std::string recordStr = recordJson.dump();
        if (recordStr.size() > budget) {
            break;
        }
        recordsJson.push_back(std::move(recordJson));
        budget -= recordStr.size();
    }

    nlohmann::json unifiedDataJson;
    unifiedDataJson["entries"] = std::move(recordsJson);
    root["content"] = std::move(unifiedDataJson);
    auto now = std::chrono::system_clock::now();
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
    root["happenTime"] = milliseconds.count();
    for (size_t i = 0; i < MAX_ROOT_TRUNCATE_ITERATIONS && EstimateJsonSize(root) > MAX_DATA_SIZE; ++i) {
        auto &entries = root["content"]["entries"];
        if (entries.empty()) {
            break;
        }
        entries.erase(entries.size() - 1);
    }
    
    std::string auditData = root.dump();
    auto task = [auditData = std::move(auditData)]() {
        PublishAuditEvent(auditData);
    };
    
    GetAuditExecutor().Execute(std::move(task));
}
} // namespace UDMF
} // namespace OHOS
