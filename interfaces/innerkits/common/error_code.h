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

namespace OHOS {
namespace UDMF {
enum UdmfModule {
    UDMF_MODULE_SERVICE_ID = 0x07,
};

// UDMF error offset, used only in this file.
constexpr ErrCode UDMF_ERR_OFFSET = ErrCodeOffset(SUBSYS_DISTRIBUTEDDATAMNG, UDMF_MODULE_SERVICE_ID);

enum Status : int32_t {
    E_OK = ERR_OK,
    E_INVALID_VALUE = UDMF_ERR_OFFSET,
    E_INVALID_OPERATION,
    E_WRITE_PARCEL_ERROR,
    E_READ_PARCEL_ERROR,
    E_IPC,
    E_SA_DIED,
    E_ERROR,
    E_OUT_OF_RANGE,
    E_NO_PERMISSION,
    E_INVALID_PARAMETERS,
    E_DB_ERROR,
    E_TIMEOUT,
    E_CANCELED,
    E_EXCEEDS_LIMIT,
    E_IS_BEGINNING_PROCESSED,
    E_FORBIDDEN,
    E_UNKNOWN,
    E_BUTT,
};
} // namespace UDMF
} // namespace OHOS
#endif //UDMF_ERROR_CODE_H