/*
 * Copyright (c) 2023 Huawei Device Co., Ltd.
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
#define LOG_TAG "UnifiedDataHelper"
#include "unified_data_helper.h"

#include <cstdio>
#include <string>
#include <sys/stat.h>
#include <cinttypes>
#include "common_func.h"
#include "directory_ex.h"
#include "file_ex.h"
#include "file_uri.h"
#include "file.h"
#include "logger.h"
#include "tlv_object.h"
#include "tlv_util.h"
#include "unified_meta.h"

namespace OHOS {
namespace UDMF {
const mode_t MODE = 0700;
static constexpr int64_t MAX_KV_RECORD_SIZE = 2 * 1024 * 1024;
static constexpr int64_t MAX_KV_DATA_SIZE = 4 * 1024 * 1024;

const std::string TEMP_UNIFIED_DATA_ROOT_PATH = "data/storage/el2/base/temp/udata";
const std::string TEMP_UNIFIED_DATA_SUFFIX = ".ud";
const std::string TEMP_UNIFIED_DATA_FLAG = "temp_udmf_file_flag";

std::string UnifiedDataHelper::rootPath_ = "";

void UnifiedDataHelper::SetRootPath(const std::string &rootPath)
{
    rootPath_ = rootPath;
}

bool UnifiedDataHelper::ExceedKVSizeLimit(UnifiedData &data)
{
    int64_t totalSize = data.GetSize();
    if (data.GetSize() > MAX_KV_DATA_SIZE) {
        LOG_DEBUG(UDMF_FRAMEWORK, "Exceeded KV data limit, totalSize:%{public}" PRId64 " !", totalSize);
        return true;
    }
    for (const auto &record : data.GetRecords()) {
        if (record->GetSize() > MAX_KV_RECORD_SIZE) {
            LOG_DEBUG(UDMF_FRAMEWORK, "Exceeded KV record limit, recordSize:%{public}" PRId64 "!", record->GetSize());
            return true;
        }
    }
    return false;
}

bool UnifiedDataHelper::IsTempUData(UnifiedData &data)
{
    auto records = data.GetRecords();
    if (records.size() != 1) {
        return false;
    }
    if (records[0] == nullptr || records[0]->GetType() != UDType::FILE) {
        return false;
    }
    auto file = static_cast<File*>(records[0].get());
    if (file == nullptr) {
        LOG_ERROR(UDMF_FRAMEWORK, "Invalid file record!");
        return false;
    }
    auto details = file->GetDetails();
    if (details.find(TEMP_UNIFIED_DATA_FLAG) == details.end()) {
        return false;
    }
    LOG_DEBUG(UDMF_FRAMEWORK, "exist temp unified data flag!");
    return true;
}

void UnifiedDataHelper::CreateDirIfNotExist(const std::string& dirPath, const mode_t& mode)
{
    if (OHOS::FileExists(dirPath)) {
        if (!OHOS::ForceRemoveDirectory(dirPath)) {
            LOG_ERROR(UDMF_FRAMEWORK, "remove dir %{public}s failed, errno: %{public}d.", dirPath.c_str(), errno);
        }
    }
    LOG_DEBUG(UDMF_FRAMEWORK, "ForceCreateDirectory, dir: %{public}s", dirPath.c_str());
    bool success = OHOS::ForceCreateDirectory(dirPath);
    if (!success) {
        LOG_ERROR(UDMF_FRAMEWORK, "create dir %{public}s failed, errno: %{public}d.", dirPath.c_str(), errno);
        return;
    }
    if (mode != 0) {
        chmod(dirPath.c_str(), mode);
    }
}

void UnifiedDataHelper::GetSummary(const UnifiedData &data, Summary &summary)
{
    for (const auto &record : data.GetRecords()) {
        int64_t recordSize = record->GetSize();
        auto udType = UD_TYPE_MAP.at(record->GetType());
        auto it = summary.summary.find(udType);
        if (it == summary.summary.end()) {
            summary.summary[udType] = recordSize;
        } else {
            summary.summary[udType] += recordSize;
        }
        summary.totalSize += recordSize;
    }
}

bool UnifiedDataHelper::Pack(UnifiedData &data)
{
    Summary summary;
    GetSummary(data, summary);

    int64_t now = std::chrono::duration_cast<std::chrono::milliseconds>
                    (std::chrono::system_clock::now().time_since_epoch()).count();
    CreateDirIfNotExist(GetRootPath(), MODE);
    std::string filePath = GetRootPath() + std::to_string(now) + TEMP_UNIFIED_DATA_SUFFIX;
    if (!SaveUDataToFile(filePath, data)) {
        LOG_ERROR(UDMF_FRAMEWORK, "fail to save unified data to file");
        return false;
    }
    std::string uri = AppFileService::CommonFunc::GetUriFromPath(filePath);
    auto fileRecord = std::make_shared<File>(uri);
    UDDetails details;
    details.insert(std::make_pair(TEMP_UNIFIED_DATA_FLAG, true));
    for (auto &item : summary.summary) {
        details.insert(std::make_pair(item.first, item.second));
    }
    fileRecord->SetDetails(details);
    std::vector<std::shared_ptr<UnifiedRecord>> records {};
    records.emplace_back(fileRecord);
    data.SetRecords(records);
    return true;
}

bool UnifiedDataHelper::Unpack(UnifiedData &data)
{
    auto records = data.GetRecords();
    if (records.size() != 1) {
        return false;
    }

    auto file = static_cast<File*>(records[0].get());
    if (file == nullptr) {
        LOG_ERROR(UDMF_FRAMEWORK, "Invalid file record!");
        return false;
    }
    UnifiedData tempData;
    if (!LoadUDataFromFile(file->GetUri(), tempData)) {
        LOG_ERROR(UDMF_FRAMEWORK, "Fail to load udata from file!");
        return false;
    }
    data.SetRecords(tempData.GetRecords());
    return true;
}

bool UnifiedDataHelper::SaveUDataToFile(const std::string &dataFile, UnifiedData &data)
{
    std::vector<uint8_t> dataBytes;
    auto recordTlv = TLVObject(dataBytes);

    std::FILE *file = fopen(dataFile.c_str(), "w+");
    if (file == nullptr) {
        LOG_ERROR(UDMF_FRAMEWORK, "failed to open file");
        return false;
    }
    recordTlv.SetFile(file);

    if (!TLVUtil::Writing(data, recordTlv)) {
        LOG_ERROR(UDMF_FRAMEWORK, "TLV Writing failed!");
        (void)fclose(file);
        return false;
    }
    (void)fclose(file);
    return true;
}

bool UnifiedDataHelper::LoadUDataFromFile(const std::string &dataFile, UnifiedData &data)
{
    std::vector<uint8_t> dataBytes;
    auto recordTlv = TLVObject(dataBytes);
    AppFileService::ModuleFileUri::FileUri fileUri(dataFile);
    std::string path = fileUri.GetRealPath();
    std::FILE *file = fopen(path.c_str(), "r");
    if (file == nullptr) {
        LOG_ERROR(UDMF_FRAMEWORK, "failed to open file");
        return false;
    }
    recordTlv.SetFile(file);

    if (!TLVUtil::Reading(data, recordTlv)) {
        LOG_ERROR(UDMF_FRAMEWORK, "TLV Reading failed!");
        (void)fclose(file);
        return false;
    }
    (void)fclose(file);
    return true;
}

std::string UnifiedDataHelper::GetRootPath()
{
    if (rootPath_ == "") {
        return TEMP_UNIFIED_DATA_ROOT_PATH;
    }
    return rootPath_;
}
} // namespace UDMF
} // namespace OHOS