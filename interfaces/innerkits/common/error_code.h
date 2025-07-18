/*
 * Copyright (c) 2023-2024 Huawei Device Co., Ltd.
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
#include <string>
#include <unordered_map>

namespace OHOS {
namespace UDMF {
using ErrCode = int;
constexpr int ERR_OK = 0;
constexpr int SUBSYS_DISTRIBUTEDDATAMNG = 13;

enum UdmfModule {
    UDMF_MODULE_SERVICE_ID = 0x07,
};

constexpr ErrCode ErrCodeOffset(unsigned int subsystem, unsigned int module = 0)
{
    constexpr int SUBSYTSTEM_BIT_NUM = 21;
    constexpr int MODULE_BIT_NUM = 16;
    return (subsystem << SUBSYTSTEM_BIT_NUM) | (module << MODULE_BIT_NUM);
}

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
    E_NO_SYSTEM_PERMISSION,
    E_SYNC_FAILED,
    E_COPY_FILE_FAILED,
    E_IDEMPOTENT_ERROR,
    E_COPY_CANCELED,
    E_DB_CORRUPTED,
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
    { Status::E_SETTINGS_EXISTED, "E_SETTINGS_EXISTED" },
    { Status::E_NO_SYSTEM_PERMISSION, "E_NO_SYSTEM_PERMISSION" }
};
} // namespace UDMF
} // namespace OHOS
#endif // UDMF_ERROR_CODE_H