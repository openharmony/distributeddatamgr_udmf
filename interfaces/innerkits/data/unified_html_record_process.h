/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef UDMF_UNIFIED_HTML_RECORD_PROCESS_H
#define UDMF_UNIFIED_HTML_RECORD_PROCESS_H

#include "unified_data.h"
#include "visibility.h"
namespace OHOS {
namespace UDMF {
class UnifiedHtmlRecordProcess {
public:
    static void API_EXPORT GetUriFromHtmlRecord(UnifiedData &unifiedData);
    static void API_EXPORT RebuildHtmlRecord(UnifiedData &unifiedData);
private:
    static std::vector<UriInfo> SplitHtmlStr(const std::string &htmlContent);
    static std::vector<std::pair<std::string, uint32_t>> SplitHtmlWithImgLabel(
        const std::string &html) noexcept;
    static std::vector<UriInfo> SplitHtmlWithImgSrcLabel(
        const std::vector<std::pair<std::string, uint32_t>> &matchs) noexcept;
    static bool IsLocalURI(const std::string &uri) noexcept;
    static void RebuildEntry(const std::vector<UriInfo> &uris, const ValueType &value);
    static std::string RebuildHtmlContent(const std::string &str, const std::vector<UriInfo> &uris);
    static std::vector<UriInfo> GetValueStr(const ValueType &value);
    static void ProcessEntry(const std::shared_ptr<UnifiedRecord> &record);
};
} // namespace UDMF
} // namespace OHOS
#endif // UDMF_UNIFIED_HTML_RECORD_PROCESS_H