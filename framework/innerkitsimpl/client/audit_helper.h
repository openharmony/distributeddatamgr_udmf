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

#ifndef UDMF_AUDIT_HELPER_H
#define UDMF_AUDIT_HELPER_H

#include <map>
#include <memory>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include "unified_data.h"
#include "visibility.h"
#include "pixelmap_loader.h"

namespace OHOS {
namespace UDMF {

class AuditHelper {
public:
    static void ReportDragAuditEvent(const UnifiedData &unifiedData, int32_t userId, uint32_t tokenId);

private:
    static size_t GetUtf8PrefixLength(const std::string &value, size_t maxBytes);
    static size_t EstimateStringSize(const std::string &str);
    static size_t EstimateJsonSize(const nlohmann::json &json);
    static void TruncateJsonValue(nlohmann::json &json);
    static void TruncateWantJson(nlohmann::json &wantJson);
    static nlohmann::json ConvertValueToJson(const ValueType &value);
    static nlohmann::json ConvertValueToJson(const ValueType &value, size_t maxValueSize);
    static nlohmann::json ConvertWantToJson(std::shared_ptr<OHOS::AAFwk::Want> want);
    static nlohmann::json ConvertPixelMapToJson(std::shared_ptr<OHOS::Media::PixelMap> pixelMap);
    static nlohmann::json ConvertObjectToJson(std::shared_ptr<Object> object);
    static nlohmann::json ConvertEntriesToJson(const std::map<std::string, ValueType> &entries);
    static nlohmann::json ConvertRecordToJson(std::shared_ptr<UnifiedRecord> record, size_t index);
    static void PublishAuditEvent(const std::string &auditData);
};

} // namespace UDMF
} // namespace OHOS
#endif // UDMF_AUDIT_HELPER_H
