/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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

#ifndef UDMF_RADAR_REPORTER_H
#define UDMF_RADAR_REPORTER_H

#include "hisysevent_c.h"
#include "visibility.h"
#include <string>

namespace OHOS {
namespace UDMF {
namespace RadarReporter {
enum BizScene : int32_t {
    SET_DATA = 1,
    SYNC_DATA = 2,
    GET_DATA = 3,
    UTD_REGISTER = 4
};

enum SetDataStage : int32_t {
    SET_DATA_BEGIN = 1,
    SET_DATA_SERVICE_BEGIN = 2,
    VERIFY_SHARE_PERMISSIONS = 3,
    GERERATE_DFS_URI = 4,
    SET_DATA_END = 5
};

enum SyncDataStage : int32_t {
    SYNC_BEGIN = 1,
    SYNC_END = 2
};

enum GetDataStage : int32_t {
    GET_DATA_BEGIN = 1,
    VERIFY_PRIVILEGE = 2,
    GRANT_URI_PERMISSION = 3,
    GET_DATA_END = 4
};

enum UtdRegisterStage : int32_t {
    UTD_REGISTER_BEGIN = 1,
    UTD_REGISTER_END = 2,
};

enum StageRes : int32_t {
    IDLE = 0,
    SUCCESS = 1,
    FAILED = 2,
    CANCELLED = 3
};

enum BizState : int32_t {
    DFX_BEGIN = 1,
    DFX_END = 2
};
const constexpr char DOMAIN[] = "DISTDATAMGR";
const constexpr char EVENT_NAME[] = "DISTRIBUTED_UDMF_BEHAVIOR";
const constexpr char ORG_PKG[] = "distributeddata";
} // namespace RadarReporter

class API_EXPORT RadarReporterAdapter {
public:
    static void ReportNormal(std::string func, int32_t scene, int32_t stage, int32_t stageRes, int32_t state);
    static void ReportNormal(std::string func, int32_t scene, int32_t stage, int32_t stageRes);
    static void ReportNormal(std::string func, int32_t scene, int32_t stage, int32_t stageRes, std::string &bundleName);
    static void ReportFail(
        std::string func, int32_t scene, int32_t stage, int32_t stageRes, int32_t errorCode, int32_t state);
    static void ReportFail(std::string func, int32_t scene, int32_t stage, int32_t stageRes, int32_t errorCode);
};
} // namespace UDMF
} // namespace OHOS
#endif // UDMF_RADAR_REPORTER_H