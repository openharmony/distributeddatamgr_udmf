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

#include <algorithm>
#include <cerrno>
#include <cctype>
#include <regex>
#include <sys/stat.h>
#include <unordered_set>

#include "file_uri.h"
#include "logger.h"
#include "xml_loader.h"

namespace OHOS {
namespace UDMF {
constexpr const char *IMG_TAG_PATTERN = "<img.*?>";
constexpr const char *IMG_TAG_SRC_PATTERN = "src=(['\"])(.*?)\\1";
constexpr const char *IMG_TAG_SRC_HEAD = "src=\"";
constexpr const char *IMG_LOCAL_URI = "file:///";
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
        auto htmlData = record->GetEntry(utdId);
        if (std::holds_alternative<std::shared_ptr<Object>>(htmlData)) {
            RebuildEntry(record->GetUris(), htmlData);
        }
    }
}

void UnifiedHtmlRecordProcess::RebuildEntry(const std::vector<UriInfo> &uris, const ValueType &value)
{
    auto object = std::get<std::shared_ptr<Object>>(value);
    if (object == nullptr) {
        return;
    }
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

void UnifiedHtmlRecordProcess::GetUriFromHtmlRecord(UnifiedRecord &record)
{
    LOG_DEBUG(UDMF_CLIENT, "start");
    record.ClearUris();
    auto utdId = UtdUtils::GetUtdIdFromUtdEnum(UDType::HTML);
    if (!record.HasType(utdId)) {
        return;
    }
    auto htmlData = record.GetEntry(utdId);
    if (std::holds_alternative<std::shared_ptr<Object>>(htmlData)) {
        auto object = std::get<std::shared_ptr<Object>>(htmlData);
        auto uriInfos = GetValueStr(object);
        if (!uriInfos.empty()) {
            LOG_INFO(UDMF_CLIENT, "split uris size=%{public}zu", uriInfos.size());
            record.SetUris(std::move(uriInfos));
        }
    }
}

std::vector<UriInfo> UnifiedHtmlRecordProcess::GetValueStr(std::shared_ptr<Object> object)
{
    if (object == nullptr) {
        return {};
    }
    auto iter = object->value_.find(HTML_CONTENT);
    if (iter == object->value_.end() || !std::holds_alternative<std::string>(iter->second)) {
        return {};
    }
    auto content = std::get<std::string>(iter->second);
    auto uriInfos = SplitHtmlStr(content);
    if (uriInfos.empty()) {
        return {};
    }
    XmlLoader xmlLoader;
    auto validImgSrcList = xmlLoader.ExtractImgSrc(content);
    RemoveInvalidImgSrc(validImgSrcList, uriInfos);
    return uriInfos;
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
    return uri.substr(0, strlen(IMG_LOCAL_URI)) == std::string(IMG_LOCAL_URI);
}

void UnifiedHtmlRecordProcess::RemoveInvalidImgSrc(const std::vector<std::string> &validImgSrcList,
    std::vector<UriInfo> &imgSrcMap) noexcept
{
    std::unordered_set<std::string> validImgSrcSet(validImgSrcList.begin(), validImgSrcList.end());
    auto new_end = std::remove_if(imgSrcMap.begin(), imgSrcMap.end(),
        [&validImgSrcSet](const UriInfo& uriInfo) {
            return validImgSrcSet.find(uriInfo.oriUri) == validImgSrcSet.end();
        });
    imgSrcMap.erase(new_end, imgSrcMap.end());
}

void UnifiedHtmlRecordProcess::CheckHtmlUris(UnifiedData &unifiedData)
{
    ClearValidatedHtmlUris(unifiedData);
    auto utdId = UtdUtils::GetUtdIdFromUtdEnum(UDType::HTML);
    for (auto &record : unifiedData.GetRecords()) {
        if (record == nullptr || !record->HasType(utdId)) {
            continue;
        }
        auto htmlData = record->GetEntry(utdId);
        if (!std::holds_alternative<std::shared_ptr<Object>>(htmlData)) {
            continue;
        }
        auto object = std::get<std::shared_ptr<Object>>(htmlData);
        if (object == nullptr) {
            continue;
        }
        auto uriInfos = GetValueStr(object);
        auto validUris = ValidateClientUris(uriInfos);
        auto validUriSize = validUris.size();
        record->SetValidatedHtmlUris(std::move(validUris));
        LOG_INFO(UDMF_CLIENT, "client valid uris size=%{public}zu", validUriSize);
    }
}

void UnifiedHtmlRecordProcess::ClearValidatedHtmlUris(UnifiedData &unifiedData)
{
    for (auto &record : unifiedData.GetRecords()) {
        if (record != nullptr) {
            record->ClearValidatedHtmlUris();
        }
    }
}

std::vector<std::string> UnifiedHtmlRecordProcess::ValidateClientUris(const std::vector<UriInfo> &uriInfos)
{
    std::vector<std::string> validUris;
    std::unordered_set<std::string> checkedUriSet;
    for (const auto &uriInfo : uriInfos) {
        if (!IsLocalURI(uriInfo.oriUri) || !checkedUriSet.emplace(uriInfo.oriUri).second) {
            continue;
        }
        if (ValidateClientFileUri(uriInfo.oriUri)) {
            validUris.push_back(uriInfo.oriUri);
        }
    }
    return validUris;
}

bool UnifiedHtmlRecordProcess::MatchImgExtension(const std::string &path)
{
    static const std::unordered_set<std::string> IMG_EXTENSIONS = {
        "png", "jpg", "jpeg", "jpe", "tif", "tiff", "xbm", "gif", "djv", "djvu", "jng", "pcx", "pbm", "pgm",
        "pnm", "ppm", "rgb", "svg", "svgz", "wbmp", "xpm", "xwd", "heif", "heifs", "hif", "heic", "heics",
        "jp2", "jpg2", "jpx", "jpf", "jpm", "ief", "bmp", "bm", "ico", "cur", "dds", "odi", "oti", "psd", "ai",
        "dng", "ras", "dwg", "dxf", "tga", "sgi", "exr", "fpx", "cdr", "cdt", "cpt", "pat", "ilbm", "avif",
        "webp", "xcf", "art", "cr2", "cr3", "crw", "arw", "nef", "nrw", "raf", "rw2", "raw", "pef", "srw",
        "erf", "orf", "apng",
    };

    if (path.empty()) {
        return false;
    }
    auto posSlash = path.find_last_of("/\\");
    std::string fileName = (posSlash == std::string::npos) ? path : path.substr(posSlash + 1);
    auto posDot = fileName.find_last_of('.');
    if (posDot == std::string::npos || posDot == 0 || posDot + 1 >= fileName.size()) {
        return false;
    }
    std::string extension = fileName.substr(posDot + 1);
    std::transform(extension.begin(), extension.end(), extension.begin(),
        [] (unsigned char ch) { return static_cast<char>(std::tolower(ch)); });
    return IMG_EXTENSIONS.find(extension) != IMG_EXTENSIONS.end();
}

bool UnifiedHtmlRecordProcess::ValidateClientFileUri(const std::string &uri)
{
    if (uri.find_first_of("?#") != std::string::npos) {
        LOG_DEBUG(UDMF_CLIENT, "uri contains query or fragment");
        return false;
    }
    AppFileService::ModuleFileUri::FileUri fileUri(uri);
    std::string physicalPath = fileUri.GetRealPath();
    if (physicalPath.empty()) {
        LOG_DEBUG(UDMF_CLIENT, "get real path empty");
        return false;
    }
    if (!MatchImgExtension(physicalPath)) {
        LOG_DEBUG(UDMF_CLIENT, "extension invalid");
        return false;
    }
    errno = 0;
    struct stat buf = {};
    if (stat(physicalPath.c_str(), &buf) != 0) {
        LOG_DEBUG(UDMF_CLIENT, "stat fail, err=%{public}d", errno);
        return false;
    }
    if (!S_ISREG(buf.st_mode)) {
        LOG_DEBUG(UDMF_CLIENT, "not regular file");
        return false;
    }
    return true;
}
} // namespace UDMF
} // namespace OHOS
