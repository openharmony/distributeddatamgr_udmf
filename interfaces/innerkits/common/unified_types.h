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

#ifndef UDMF_UNIFIED_TYPES_H
#define UDMF_UNIFIED_TYPES_H

#include <map>
#include <string>

#include "error_code.h"
#include "unified_key.h"
#include "unified_meta.h"

namespace OHOS {
namespace UDMF {
enum DataStatus : int32_t {
    WORKING = 0,
    HISTORY,
    DELETED,
    FADE
};

struct Summary {
    std::map<std::string, int64_t> summary;
    std::vector<std::string> fileTypes;
    int64_t totalSize;
};

struct Privilege {
    uint32_t tokenId;
    std::string readPermission;
    std::string writePermission;
};

struct Runtime {
    UnifiedKey key;
    bool isPrivate {};
    std::vector<Privilege> privileges;
    // time when the data is created
    time_t createTime {};
    // name of the package for creating data
    std::string sourcePackage;
    // current data status
    DataStatus dataStatus { WORKING };
    // current data version
    std::int32_t dataVersion {};
    // time when the data is last modified
    time_t lastModifiedTime {};
    // time when data is written to the udmf
    std::string createPackage;
    // device ID of the data source
    std::string deviceId;
    std::uint32_t recordTotalNum {};
    uint32_t tokenId;
    std::string sdkVersion;
    Visibility visibility {};
    std::string appId;
};

/*
 * Options for sharing data through UDMF.
 */
struct CustomOption {
    Intention intention {};
    uint32_t tokenId {};
    Visibility visibility {};
};

/*
 * Options for querying data from UDMF.
 */
struct QueryOption {
    std::string key;
    Intention intention {};
    uint32_t  tokenId {};
};

enum AsyncTaskStatus : uint32_t {
    ASYNC_IDLE = 0,
    ASYNC_RUNNING,
    ASYNC_SUCCESS,
    ASYNC_FAILURE,
};

struct AsyncProcessInfo {
    AsyncTaskStatus syncStatus { ASYNC_IDLE };
    AsyncTaskStatus permStatus { ASYNC_IDLE };
    std::string srcDevName;
    uint32_t syncFinished = 0;
    uint32_t syncTotal = 0;
    uint32_t syncId = 0;
    uint32_t permFnished = 0;
    uint32_t permTotal = 0;
    std::string businessUdKey;
};

struct ProgressInfo {
    int32_t progress = 0;
    int32_t progressStatus;
    Status errorCode;
    std::string srcDevName;
};

struct UriInfo {
    std::string oriUri;
    std::string authUri;
    std::string dfsUri;
    uint32_t position;
};

struct DataLoadInfo {
    std::string sequenceKey;
    std::set<std::string> types;
    uint32_t recordCount;
};

using LoadHandler = std::function<void(const std::string &udKey, const DataLoadInfo &dataLoadInfo)>;

struct DataLoadParams {
    LoadHandler loadHandler;
    DataLoadInfo dataLoadInfo;
};

struct DelayGetDataInfo {
    uint32_t tokenId;
#ifndef CROSS_PLATFORM
    sptr<IRemoteObject> dataCallback;
#endif
};
} // namespace UDMF
} // namespace OHOS
#endif // UDMF_UNIFIED_TYPES_H