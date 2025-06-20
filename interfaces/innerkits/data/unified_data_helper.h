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

#ifndef UDMF_UNIFIED_DATA_HELPER_H
#define UDMF_UNIFIED_DATA_HELPER_H

#include <sys/stat.h>
#include "unified_data.h"
#include "visibility.h"
namespace OHOS {
namespace UDMF {
class API_EXPORT UnifiedDataHelper {
public:
    static void SetRootPath(const std::string &rootPath);
    static bool ExceedKVSizeLimit(UnifiedData &data);
    static bool IsTempUData(UnifiedData &data);
    static bool Pack(UnifiedData &data);
    static bool Unpack(UnifiedData &data);
    static void GetSummary(const UnifiedData &data, Summary &summary);
    static int32_t ProcessBigData(UnifiedData &data, Intention intention, bool isSaInvoke);
    static void GetSummaryFromLoadInfo(const DataLoadInfo &dataLoadInfo, Summary &summary);
private:
    static void CreateDirIfNotExist(const std::string& dirPath, const mode_t& mode);
    static bool SaveUDataToFile(const std::string &dataFile, UnifiedData &data);
    static bool LoadUDataFromFile(const std::string &dataFile, UnifiedData &data);
    static void CalRecordSummary(std::map<std::string, ValueType> &entries,
        Summary &summary, std::set<std::string> &fileTypes);
    static void ProcessTypeId(const ValueType &value, std::string &typeId);
    static std::string GetRootPath();
    static bool FileClose(std::FILE *file, bool status);

private:
    static std::string rootPath_;
};
} // namespace UDMF
} // namespace OHOS
#endif // UDMF_UNIFIED_DATA_HELPER_H
