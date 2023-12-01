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

#include "unified_data_helper.h"

#include <cstdio>
#include <string>
#include "file_uri.h"
#include "file.h"
#include "logger.h"
#include "tlv_object.h"
#include "tlv_util.h"

namespace OHOS {
namespace UDMF {
static constexpr int64_t MAX_KV_RECORD_SIZE = 2 * 1024 * 1024;
static constexpr int64_t MAX_KV_DATA_SIZE = 4 * 1024 * 1024;

const std::string TEMP_UNIFIED_DATA_ROOT_PATH = "data/storage/el2/base/temp/";
const std::string TEMP_UNIFIED_DATA_SUFFIX = ".ud";
const std::string TEMP_UNIFIED_DATA_FLAG = "temp_udmf_file_flag";
bool UnifiedDataHelper::ExceedKVSizeLimit(UnifiedData &data)
{
    if (data.GetSize() > MAX_KV_DATA_SIZE) {
        LOG_DEBUG(UDMF_FRAMEWORK, "Exceeded KV data limit!");
        return true;
    }
    for (const auto &record : data.GetRecords()) {
        if (record->GetSize() > MAX_KV_RECORD_SIZE) {
            LOG_DEBUG(UDMF_FRAMEWORK, "Exceeded KV record limit!");
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

bool UnifiedDataHelper::Pack(UnifiedData &data)
{
    int64_t now = std::chrono::duration_cast<std::chrono::milliseconds>
                    (std::chrono::system_clock::now().time_since_epoch()).count();
    std::string filePath = TEMP_UNIFIED_DATA_ROOT_PATH + std::to_string(now) + TEMP_UNIFIED_DATA_SUFFIX;
    if (!SaveUDataToFile(filePath, data)) {
        LOG_ERROR(UDMF_FRAMEWORK, "fail to save unified data to file");
        return false;
    }
    auto fileRecord = std::make_shared<File>(filePath);
    UDDetails details;
    details.insert(std::make_pair(TEMP_UNIFIED_DATA_FLAG, true));
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
    LoadUDataFromFile(file->GetUri(), data);
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
        LOG_ERROR(UDMF_FRAMEWORK, "TLV writing failed!");
        fclose(file);
        return false;
    }
    fclose(file);
    return true;
}

bool UnifiedDataHelper::LoadUDataFromFile(const std::string &dataFile, UnifiedData &data)
{
    std::vector<uint8_t> dataBytes;
    auto recordTlv = TLVObject(dataBytes);

    std::FILE *file = fopen(dataFile.c_str(), "r");
    if (file == nullptr) {
        LOG_ERROR(UDMF_FRAMEWORK, "failed to open file");
        return false;
    }
    recordTlv.SetFile(file);

    if (!TLVUtil::Reading(data, recordTlv)) {
        LOG_ERROR(UDMF_FRAMEWORK, "TLV writing failed!");
		fclose(file);
        return false;
    }
    fclose(file);
    return true;
}
} // namespace UDMF
} // namespace OHOS