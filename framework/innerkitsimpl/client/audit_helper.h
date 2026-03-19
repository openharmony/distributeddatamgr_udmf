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
#include "unified_meta.h"
#include "unified_data_properties.h"
#include "unified_record.h"
#include "visibility.h"
#include "pixelmap_loader.h"

namespace OHOS {
namespace UDMF {

class AuditHelper {
public:
    static void ReportDragAuditEvent(const UnifiedData &unifiedData, int32_t userId, uint32_t tokenId);

private:
    static std::string UDTypeToString(UDType type);
    static nlohmann::json ConvertValueToJson(const ValueType &value);
    static nlohmann::json ConvertWantToJson(const std::shared_ptr<OHOS::AAFwk::Want> &want);
    static nlohmann::json ConvertWantParamsToJson(const OHOS::AAFwk::WantParams &wantParams);
    static nlohmann::json ConvertPixelMapToJson(const std::shared_ptr<OHOS::Media::PixelMap> &pixelMap);
    static nlohmann::json ConvertObjectToJson(const std::shared_ptr<Object> &object);
    static nlohmann::json ConvertEntriesToJson(const std::map<std::string, ValueType> &entries);
    static nlohmann::json ConvertRecordToJson(const std::shared_ptr<UnifiedRecord> &record, size_t index);
    static void PublishAuditEvent(const nlohmann::json &auditData);
};

} // namespace UDMF
} // namespace OHOS
#endif // UDMF_AUDIT_HELPER_H
