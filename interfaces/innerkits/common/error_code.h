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

#ifndef UDMF_ERROR_CODE_H
#define UDMF_ERROR_CODE_H

#include <cstdint>
#include <errors.h>
#include <map>
#include <string>

namespace OHOS {
namespace UDMF {
enum UdmfModule {
    UDMF_MODULE_SERVICE_ID = 0x07,
};

// UDMF error offset, used only in this file.
constexpr ErrCode UDMF_ERR_OFFSET = ErrCodeOffset(SUBSYS_DISTRIBUTEDDATAMNG, UDMF_MODULE_SERVICE_ID);

enum Status : int32_t {
    E_OK = ERR_OK,
    E_ERROR,
    E_WRITE_PARCEL_ERROR = UDMF_ERR_OFFSET,
    E_READ_PARCEL_ERROR,
    E_IPC,
    E_NO_PERMISSION,
    E_INVALID_PARAMETERS,
    E_DB_ERROR,
    E_FS_ERROR,
    E_NOT_FOUND,
    E_SETTINGS_EXISTED,
    E_BUTT,
};

static const std::unordered_map<int32_t, std::string> ERROR_MAP {
    { Status::E_OK, "E_OK" },
    { Status::E_ERROR, "E_ERROR" },
    { Status::E_WRITE_PARCEL_ERROR, "E_WRITE_PARCEL_ERROR" },
    { Status::E_READ_PARCEL_ERROR, "E_READ_PARCEL_ERROR" },
    { Status::E_IPC, "E_IPC" },
    { Status::E_NO_PERMISSION, "E_NO_PERMISSION" },
    { Status::E_INVALID_PARAMETERS, "E_INVALID_PARAMETERS" },
    { Status::E_DB_ERROR, "E_DB_ERROR" },
    { Status::E_FS_ERROR, "E_FS_ERROR" },
    { Status::E_NOT_FOUND, "E_NOT_FOUND" },
    { Status::E_SETTINGS_EXISTED, "E_SETTINGS_EXISTED" }
};
} // namespace UDMF
} // namespace OHOS
#endif // UDMF_ERROR_CODE_H