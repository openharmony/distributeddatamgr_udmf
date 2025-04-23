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
#define LOG_TAG "UnifiedHtmlRecordProcess"
#include "unified_html_record_process.h"

#include <regex>

#include "file_uri.h"
#include "html.h"
#include "logger.h"

namespace OHOS {
namespace UDMF {
constexpr const char *IMG_TAG_PATTERN = "<img.*?>";
constexpr const char *IMG_TAG_SRC_PATTERN = "src=(['\"])(.*?)\\1";
constexpr const char *IMG_TAG_SRC_HEAD = "src=\"";
constexpr const char *IMG_LOCAL_URI = "file:///";
constexpr const char *IMG_LOCAL_PATH = "://";
constexpr const char *FILE_SCHEME_PREFIX = "file://";

struct Cmp {
    bool operator()(const uint32_t &lhs, const uint32_t &rhs) const
    {
        return lhs > rhs;
    }
};

void UnifiedHtmlRecordProcess::RebuildHtmlRecord(UnifiedData &unifiedData)
{
    LOG_DEBUG(UDMF_CLIENT, "start");
    auto utdId = UtdUtils::GetUtdIdFromUtdEnum(UDType::HTML);
    for (auto &record : unifiedData.GetRecords()) {
        if (record == nullptr || record->GetUris().empty()) {
            continue;
        }
        if (!record->HasType(utdId)) {
            continue;
        }
        if (record->GetType() == UDType::HTML) {
            auto htmlRecord = std::static_pointer_cast<Html>(record);
            auto rebuildContent = RebuildHtmlContent(htmlRecord->GetHtmlContent(), record->GetUris());
            if (!rebuildContent.empty()) {
                htmlRecord->SetHtmlContent(rebuildContent);
            }
        } else {
            ProcessEntry(record);
        }
    }
}

void UnifiedHtmlRecordProcess::ProcessEntry(const std::shared_ptr<UnifiedRecord> &record)
{
    if (record->GetInnerEntries() == nullptr) {
        return;
    }
    for (auto &entry : *(record->GetInnerEntries())) {
        auto udType = static_cast<UDType>(UtdUtils::GetUtdEnumFromUtdId(entry.first));
        if (udType == UDType::HTML && std::holds_alternative<std::shared_ptr<Object>>(entry.second)) {
            RebuildEntry(record->GetUris(), entry.second);
        }
    }
}

void UnifiedHtmlRecordProcess::RebuildEntry(const std::vector<UriInfo> &uris, const ValueType &value)
{
    auto object = std::get<std::shared_ptr<Object>>(value);
    auto iter = object->value_.find(HTML_CONTENT);
    if (iter != object->value_.end()) {
        if (std::holds_alternative<std::string>(iter->second)) {
            auto content = std::get<std::string>(iter->second);
            auto rebuildContent = RebuildHtmlContent(content, uris);
            if (!rebuildContent.empty()) {
                object->value_[HTML_CONTENT] = rebuildContent;
            }
        }
    }
}

std::string UnifiedHtmlRecordProcess::RebuildHtmlContent(const std::string &str, const std::vector<UriInfo> &uris)
{
    std::map<uint32_t, std::pair<std::string, std::string>, Cmp> replaceUris;
    std::string strResult = str;
    for (auto &uri : uris) {
        std::string tmpUri = uri.dfsUri.empty() ? uri.authUri : uri.dfsUri;
        std::string realUri = tmpUri;
        if (tmpUri.substr(0, strlen(FILE_SCHEME_PREFIX)) == FILE_SCHEME_PREFIX) {
            AppFileService::ModuleFileUri::FileUri fileUri(tmpUri);
            realUri = FILE_SCHEME_PREFIX;
            realUri += fileUri.GetRealPath();
            replaceUris[uri.position] = std::make_pair(std::move(uri.oriUri), std::move(realUri));
        }
    }
    if (replaceUris.empty()) {
        return "";
    }
    LOG_INFO(UDMF_CLIENT, "replaceUris size=%{public}zu", replaceUris.size());
    for (auto &replaceUri : replaceUris) {
        strResult.replace(replaceUri.first, replaceUri.second.first.size(), replaceUri.second.second);
    }
    return strResult;
}

void UnifiedHtmlRecordProcess::GetUriFromHtmlRecord(UnifiedData &unifiedData)
{
    LOG_DEBUG(UDMF_CLIENT, "start");
    auto utdId = UtdUtils::GetUtdIdFromUtdEnum(UDType::HTML);
    for (auto &record : unifiedData.GetRecords()) {
        if (record == nullptr) {
            continue;
        }
        if (!record->HasType(utdId)) {
            continue;
        }
        auto htmlData = record->GetEntry(utdId);
        if (std::holds_alternative<std::shared_ptr<Object>>(htmlData)) {
            auto uriInfos = GetValueStr(htmlData);
            if (!uriInfos.empty()) {
                LOG_INFO(UDMF_CLIENT, "split uris size=%{public}zu", uriInfos.size());
                record->SetUris(std::move(uriInfos));
            }
        }
    }
}

std::vector<UriInfo> UnifiedHtmlRecordProcess::GetValueStr(const ValueType &value)
{
    auto object = std::get<std::shared_ptr<Object>>(value);
    auto iter = object->value_.find(HTML_CONTENT);
    if (iter != object->value_.end()) {
        if (std::holds_alternative<std::string>(iter->second)) {
            auto content = std::get<std::string>(iter->second);
            return SplitHtmlStr(content);
        }
    }
    return {};
}

std::vector<UriInfo> UnifiedHtmlRecordProcess::SplitHtmlStr(const std::string &htmlContent)
{
    std::vector<std::pair<std::string, uint32_t>> matchs = SplitHtmlWithImgLabel(htmlContent);
    if (matchs.empty()) {
        return {};
    }
    LOG_INFO(UDMF_CLIENT, "matchs size=%{public}zu", matchs.size());
    return SplitHtmlWithImgSrcLabel(matchs);
}

std::vector<std::pair<std::string, uint32_t>> UnifiedHtmlRecordProcess::SplitHtmlWithImgLabel(
    const std::string &htmlContent) noexcept
{
    std::smatch match;
    std::string pattern(IMG_TAG_PATTERN);
    std::regex reg(pattern);
    std::string::const_iterator iterStart = htmlContent.begin();
    std::string::const_iterator iterEnd = htmlContent.end();
    std::vector<std::pair<std::string, uint32_t>> matchs;
    while (std::regex_search(iterStart, iterEnd, match, reg)) {
        std::string tmp = match[0];
        iterStart = match[0].second;
        uint32_t position = static_cast<uint32_t>(match[0].first - htmlContent.begin());
        matchs.emplace_back(tmp, position);
    }
    return matchs;
}

std::vector<UriInfo> UnifiedHtmlRecordProcess::SplitHtmlWithImgSrcLabel(
    const std::vector<std::pair<std::string, uint32_t>> &matchs) noexcept
{
    std::vector<UriInfo> splitResult;
    std::smatch match;
    std::string pattern(IMG_TAG_SRC_PATTERN);
    std::regex reg(pattern);
    for (const auto &iter : matchs) {
        std::string::const_iterator iterStart = iter.first.begin();
        std::string::const_iterator iterEnd = iter.first.end();
        while (std::regex_search(iterStart, iterEnd, match, reg)) {
            std::string tmp = match[0];
            iterStart = match[0].second;
            uint32_t position = static_cast<uint32_t>(match[0].first - iter.first.begin());
            tmp = tmp.substr(strlen(IMG_TAG_SRC_HEAD));
            tmp.pop_back();
            if (!IsLocalURI(tmp)) {
                continue;
            }
            position += strlen(IMG_TAG_SRC_HEAD) + iter.second;
            UriInfo uriInfo = {
                .oriUri = tmp,
                .position = position,
            };
            splitResult.push_back(std::move(uriInfo));
        }
    }
    return splitResult;
}

bool UnifiedHtmlRecordProcess::IsLocalURI(const std::string &uri) noexcept
{
    return uri.substr(0, strlen(IMG_LOCAL_URI)) == std::string(IMG_LOCAL_URI) ||
        uri.find(IMG_LOCAL_PATH) == std::string::npos;
}

} // namespace UDMF
} // namespace OHOS