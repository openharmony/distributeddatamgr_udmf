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

/**
 * @addtogroup UDMF
 * @{
 *
 * @brief The Unified Data Management Framework(UDMF) aims to define various standards
 * for data across applications, devices, and platforms, providing a unified OpenHarmony
 * data language and standardized data access and reading paths.
 *
 * @syscap SystemCapability.DistributedDataManager.UDMF.Core
 *
 * @since 12
 */

/**
 * @file udmf_err_code.h
 *
 * @brief Declaration error code information.
 *
 * @kit ArkData
 * @library libudmf.so
 * @syscap SystemCapability.DistributedDataManager.UDMF.Core
 *
 * @since 12
 */


#ifndef UDMF_ERR_CODE_H
#define UDMF_ERR_CODE_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Indicates the error code information.
 *
 * @since 12
 */
typedef enum Udmf_ErrCode {
    /**
     * The error code in the correct case.
     */
    UDMF_E_OK = 0,
    /**
     * @brief The error when the capability not supported.
     */
    UDMF_E_NOT_SUPPORTED = 801,
    /**
     * @brief The error code for common exceptions.
     */
    UDMF_ERR = 20400000,
    /**
     * @brief The error code for not support this data parse exceptions.
     */
    UDMF_E_NOT_PARSE_DATA = (UDMF_ERR + 1),
    /**
     * @brief The error code for common invalid args.
     */
    UDMF_E_INVALID_PARAM = (UDMF_ERR + 2),
} Udmf_ErrCode;

#ifdef __cplusplus
};
#endif

/** @} */
#endif
