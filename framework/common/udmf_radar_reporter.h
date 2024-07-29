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
    VERIFY_SHARE_PERMISSIONS = 2,
    GERERATE_DFS_URI = 3,
    SET_DATA_END = 4
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
    DFX_BEGIN = 0,
    DFX_NORMAL_END = 1,
    DFX_ABNORMAL_END = 2
};

const constexpr char BIZ_STATE[] = "BIZ_STATE";
const constexpr char ERROR_CODE[] = "ERROR_CODE";
const constexpr char DOMAIN[] = "DISTDATAMGR";
const constexpr char EVENT_NAME[] = "DISTRIBUTED_UDMF_BEHAVIOR";
const constexpr char ORG_PKG_KEY[] = "ORG_PKG";
const constexpr char ORG_PKG_VALUE[] = "distributeddata";
const constexpr char FUNC[] = "FUNC";
const constexpr char BIZ_SCENE[] = "BIZ_SCENE";
const constexpr char BIZ_STAGE[] = "BIZ_STAGE";
const constexpr char STAGE_RES[] = "STAGE_RES";
} // namespace RadarReporter

class RadarReporterAdapter {
public:
    static void ReportSetDataNormal(std::string func, int32_t stage, int32_t stageRes, int32_t state);
    static void ReportSetDataFail(std::string func, int32_t stage, int32_t stageRes, int32_t errorCode, int32_t state);
    static void ReportGetDataNormal(std::string func, int32_t stage, int32_t stageRes, int32_t state);
    static void ReportGetDataFail(std::string func, int32_t stage, int32_t stageRes, int32_t errorCode, int32_t state);
};
} // namespace UDMF
} // namespace OHOS
#endif // UDMF_RADAR_REPORTER_H