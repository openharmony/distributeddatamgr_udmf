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

static UdmfExecutor &GetAuditExecutor()
{
    static UdmfExecutor auditExecutor(MAX_THREADS, MIN_THREADS);
    return auditExecutor;
}

nlohmann::json AuditHelper::ConvertWantToJson(std::shared_ptr<OHOS::AAFwk::Want> want)
{
    nlohmann::json wantJson;
    if (want != nullptr) {
        wantJson["action"] = want->GetAction();
        wantJson["bundle"] = want->GetBundle();
        wantJson["deviceId"] = want->GetDeviceId();
        wantJson["moduleName"] = want->GetModuleName();
        wantJson["type"] = want->GetType();
        wantJson["uri"] = want->GetUriString();
        wantJson["flags"] = want->GetFlags();

        auto element = want->GetElement();
        nlohmann::json elementJson;
        elementJson["uri"] = element.GetURI();
        wantJson["element"] = elementJson;
    }
    return wantJson;
}

nlohmann::json AuditHelper::ConvertPixelMapToJson(std::shared_ptr<OHOS::Media::PixelMap> pixelMap)
{
    nlohmann::json pixelMapJson;
    std::vector<uint8_t> encodedData;
    PixelMapLoader loader;
    if (loader.EncodeTlv(pixelMap, encodedData)) {
        pixelMapJson["encodedData"] = nlohmann::json::binary(encodedData);
    } else {
        LOG_ERROR(UDMF_CLIENT, "Encode pixelMap error");
    }

    return pixelMapJson;
}

nlohmann::json AuditHelper::ConvertObjectToJson(std::shared_ptr<Object> object)
{
    if (object != nullptr) {
        return ConvertEntriesToJson(object->value_);
    }
    return nlohmann::json::object();
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
        return std::get<std::string>(value);
    } else if (std::holds_alternative<std::vector<uint8_t>>(value)) {
        auto bytes = std::get<std::vector<uint8_t>>(value);
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
    nlohmann::json entriesJson;
    for (const auto &[key, val] : entries) {
        entriesJson[key] = ConvertValueToJson(val);
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

void AuditHelper::PublishAuditEvent(const nlohmann::json &auditData)
{
    std::string jsonString = auditData.dump();

    AAFwk::Want want;
    want.SetAction(DRAG_AUDIT_EVENT);
    want.SetParam("auditData", jsonString);

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
    auto task = [unifiedData, userId, tokenId]() {
        nlohmann::json root;
        nlohmann::json unifiedDataJson = nlohmann::json::object();

        auto runtime = unifiedData.GetRuntime();
        if (runtime != nullptr) {
            root["sourceTokenId"] = runtime->tokenId;
        }

        auto records = unifiedData.GetRecords();
        nlohmann::json recordsJson = nlohmann::json::array();
        for (size_t i = 0; i < records.size(); ++i) {
            recordsJson.push_back(ConvertRecordToJson(records[i], i));
        }
        root["targetTokenId"] = tokenId;
        root["userId"] = userId;
        unifiedDataJson["entries"] = std::move(recordsJson);

        root["content"] = unifiedDataJson;

        auto now = std::chrono::system_clock::now();
        auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
        root["happenTime"] = milliseconds.count();

        PublishAuditEvent(root);
    };

    GetAuditExecutor().Execute(task);
}
} // namespace UDMF
} // namespace OHOS