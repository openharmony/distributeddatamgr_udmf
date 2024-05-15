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

#include "hisysevent.h"

namespace OHOS {
namespace UDMF {
namespace RadarReporter {
enum BizScene : std::int32_t {
    SET_DATA = 1,
    SYNC_DATA = 2,
    GET_DATA = 3, 
};

enum BizStage : std::int32_t {
    SAVE_OBJECT = 1,
};
enum StageRes : std::int32_t {
    IDLE = 0,
    SUCCESS = 1,
    FAILED = 2,
    CANCELLED = 3,
};
enum BizState : std::int32_t {
    START = 1,
    FINISHED = 2,
};

enum ErrorCode : int32_t {
    OFFSET = 27721728,
    DUPLICATE_CREATE = OFFSET,
    WRITE_PARCEL_ERROR = OFFSET,
    READ_PARCEL_ERROR,
    IPC,
    NO_PERMISSION,
    INVALID_PARAMETERS,
    DB_ERROR,
    FS_ERROR,
    NOT_FOUND,
    
};
const constexpr char* BIZ_STATE = "BIZ_STATE";
const constexpr char* ERROR_CODE = "ERROR_CODE";
} // namespace RadarReporter

const constexpr char* DOMAIN = "DISTDATAMGR";
const constexpr char* EVENT_NAME = "DISTRIBUTED_UDMF_BEHAVIOR";
const constexpr HiviewDFX::HiSysEvent::EventType TYPE = HiviewDFX::HiSysEvent::EventType::BEHAVIOR;
const constexpr char* ORG_PKG = "distributeddata";

#define RADAR_REPORT(bizScene, bizStage, stageRes, ...)                                            \
({                                                                                                 \
    HiSysEventWrite(DOMAIN, EVENT_NAME, TYPE, "ORG_PKG", ORG_PKG, "FUNC", __FUNCTION__,            \
        "BIZ_SCENE", bizScene, "BIZ_STAGE", bizStage, "STAGE_RES", stageRes, ##__VA_ARGS__);       \
})
} // namespace UDMF
} // namespace OHOS
#endif // UDMF_RADAR_REPORTER_H