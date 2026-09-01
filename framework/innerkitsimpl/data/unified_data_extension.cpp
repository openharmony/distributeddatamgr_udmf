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

#include "unified_data_helper.h"

#include <algorithm>
#include <iterator>

#include "unified_meta.h"
#include "unified_record.h"

namespace OHOS {
namespace UDMF {
namespace {
std::shared_ptr<Object> GetObjectFromRecord(const std::shared_ptr<UnifiedRecord> &record)
{
    if (record == nullptr) {
        return nullptr;
    }
    auto value = record->GetOriginValue();
    if (!std::holds_alternative<std::shared_ptr<Object>>(value)) {
        record->InitObject();
        value = record->GetOriginValue();
    }
    if (!std::holds_alternative<std::shared_ptr<Object>>(value)) {
        return nullptr;
    }
    return std::get<std::shared_ptr<Object>>(value);
}

std::string GetFileUriFromRecord(const std::shared_ptr<UnifiedRecord> &record)
{
    std::string uri;
    auto object = GetObjectFromRecord(record);
    if (object != nullptr) {
        object->GetValue(ORI_URI, uri);
        if (!uri.empty()) {
            return uri;
        }
    }
    auto value = record == nullptr ? ValueType() : record->GetOriginValue();
    if (std::holds_alternative<std::string>(value)) {
        uri = std::get<std::string>(value);
    }
    return uri;
}

bool HasTempUnifiedDataFlag(const std::shared_ptr<UnifiedRecord> &record)
{
    auto object = GetObjectFromRecord(record);
    if (object == nullptr) {
        return false;
    }
    std::shared_ptr<Object> detailsObj = nullptr;
    if (!object->GetValue(DETAILS, detailsObj)) {
        return false;
    }
    auto details = ObjectUtils::ConvertToUDDetails(detailsObj);
    return details.find(TEMP_UNIFIED_DATA_FLAG) != details.end();
}

constexpr UDType FILE_SUMMARY_TYPES[] = { FILE, AUDIO, FOLDER, IMAGE, VIDEO };

std::string ExtractFileExtension(const std::string &uri)
{
    if (uri.empty()) {
        return "";
    }

    std::string path = uri;
    size_t queryPos = path.find('?');
    if (queryPos != std::string::npos) {
        path = path.substr(0, queryPos);
    }
    size_t fragmentPos = path.find('#');
    if (fragmentPos != std::string::npos) {
        path = path.substr(0, fragmentPos);
    }

    size_t lastSlash = path.find_last_of("/\\");
    std::string filename = (lastSlash == std::string::npos) ? path : path.substr(lastSlash + 1);
    if (filename.empty()) {
        return "";
    }

    size_t lastDot = filename.find_last_of('.');
    if (lastDot == std::string::npos || lastDot == 0 || lastDot == filename.length() - 1) {
        return "";
    }

    std::string extension = filename.substr(lastDot);
    for (char &c : extension) {
        if (c >= 'A' && c <= 'Z') {
            c = c - 'A' + 'a';
        }
    }
    return extension;
}
} // namespace

std::vector<std::string> API_EXPORT CollectFilenameExtensions(const UnifiedData &data)
{
    std::vector<std::string> result;
    for (const auto &record : data.GetRecords()) {
        if (record == nullptr
            || std::find(std::begin(FILE_SUMMARY_TYPES), std::end(FILE_SUMMARY_TYPES), record->GetType())
                == std::end(FILE_SUMMARY_TYPES)
            || HasTempUnifiedDataFlag(record)) {
            continue;
        }
        std::string uri = GetFileUriFromRecord(record);
        if (uri.empty() || uri.find("file://") != 0) {
            continue;
        }
        std::string extension = ExtractFileExtension(uri);
        if (extension.empty()) {
            continue;
        }
        if (std::find(result.begin(), result.end(), extension) == result.end()) {
            result.emplace_back(extension);
        }
    }
    return result;
}
} // namespace UDMF
} // namespace OHOS