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
 * @since 12
 */

/**
 * @file udmf.h
 *
 * @brief Provides unified data management framework related functions and enumerations.
 *
 * @kit ArkData
 * @library libudmf.so
 * @syscap SystemCapability.DistributedDataManager.UDMF.Core
 *
 * @since 12
 */

#ifndef UDMF_H
#define UDMF_H

#include <inttypes.h>
#include <stdbool.h>
#include "uds.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief The key minimum memory space size of Unified Data.
 *
 * @since 12
 */
#define UDMF_KEY_BUFFER_LEN (512)

/**
 * @brief Describe the intention type of the udmf.
 *
 * @since 12
 */
typedef enum Udmf_Intention {
    /**
     * @brief The intention is drag.
     */
    UDMF_INTENTION_DRAG,
    /**
     * @brief The intention is pasteboard.
     */
    UDMF_INTENTION_PASTEBOARD,
} Udmf_Intention;

/**
 * @brief Describe intra-device usage range type enumeration.
 *
 * @since 12
 */
typedef enum Udmf_ShareOption {
    /**
     * @brief Invalid share option.
     */
    SHARE_OPTIONS_INVALID,
    /**
     * @brief Allowed to be used in the same application on this device.
     */
    SHARE_OPTIONS_IN_APP,
    /**
     * @brief Allowed to be used in the cross application on this device.
     */
    SHARE_OPTIONS_CROSS_APP
} Udmf_ShareOption;

/**
 * @brief Describes the unified data type.
 *
 * @since 12
 */
typedef struct OH_UdmfData OH_UdmfData;

/**
 * @brief Describes the record type in the unified data.
 *
 * @since 12
 */
typedef struct OH_UdmfRecord OH_UdmfRecord;

/**
 * @brief Describes some property parameters of unified data.
 *
 * @since 12
 */
typedef struct OH_UdmfProperty OH_UdmfProperty;

/**
 * @brief Creation a pointer to the instance of the {@link OH_UdmfData}.
 *
 * @return If the operation is successful, a pointer to the instance of the {@link OH_UdmfData}
 * structure is returned. If the operation is failed, nullptr is returned.
 * @see OH_UdmfData.
 * @since 12
 */
OH_UdmfData* OH_UdmfData_Create();

/**
 * @brief Destroy a pointer that points to the {@link OH_UdmfData} instance.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_UdmfData}.
 * @see OH_UdmfData.
 * @since 12
 */
void OH_UdmfData_Destroy(OH_UdmfData* pThis);

/**
 * @brief Add one {OH_UdmfRecord} record to the {@link OH_UdmfData} data.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_UdmfData}.
 * @param record Represents a pointer to an instance of {@link OH_UdmfRecord}.
 * @return Returns the status code of the execution. See {@link Udmf_ErrCode}.
 *         {@link UDMF_E_OK} success.
 *         {@link UDMF_E_INVALID_PARAM} The error code for common invalid args.
 * @see OH_UdmfData Udmf_ErrCode.
 * @since 12
 */
int OH_UdmfData_AddRecord(OH_UdmfData* pThis, OH_UdmfRecord* record);

/**
 * @brief Check whether the type exists in the {@link OH_UdmfData} data.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_UdmfData}.
 * @param type Represents a string pointer of the type.
 * @return Returns the status of finding type.
 *         {@code false} is not existed.
 *         {@code true} is existed.
 * @see OH_UdmfData.
 * @since 12
 */
bool OH_UdmfData_HasType(OH_UdmfData* pThis, const char* type);

/**
 * @brief Get all types in the {@link OH_UdmfData} data.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_UdmfData}.
 * @param count Represents the types count that is a output param.
 * @return Returns string array that in {@link OH_UdmfData} when input parameters valid,
 * otherwise return nullptr.
 * @see OH_UdmfData.
 * @since 12
 */
char** OH_UdmfData_GetTypes(OH_UdmfData* pThis, unsigned int* count);

/**
 * @brief Get all records in the {@link OH_UdmfData} data.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_UdmfData}.
 * @param count Represents the records count that is a output param.
 * @return Returns {@link OH_UdmfRecord} pointer array when input parameters valid, otherwise return nullptr.
 * @see OH_UdmfData OH_UdmfRecord.
 * @since 12
 */
OH_UdmfRecord** OH_UdmfData_GetRecords(OH_UdmfData* pThis, unsigned int* count);

/**
 * @brief Get primary {@link OH_UdsPlainText} data from the {@link OH_UdmfData}.
 *
 * @param data Represents a pointer to an instance of {@link OH_UdmfData}.
 * @param plainText Represents a pointer to an instance of {@link OH_UdsPlainText}.
 * @return Returns the status code of the execution. See {@link Udmf_ErrCode}.
 *         {@link UDMF_E_OK} success.
 *         {@link UDMF_E_INVALID_PARAM} The error code for common invalid args.
 * @see OH_UdmfData OH_UdsPlainText Udmf_ErrCode.
 * @since 13
 */
int OH_UdmfData_GetPrimaryPlainText(OH_UdmfData* data, OH_UdsPlainText* plainText);

/**
 * @brief Get one {@link OH_UdsHtml} data from the {@link OH_UdmfData}.
 *
 * @param data Represents a pointer to an instance of {@link OH_UdmfData}.
 * @param html Represents a pointer to an instance of {@link OH_UdsHtml}.
 * @return Returns the status code of the execution. See {@link Udmf_ErrCode}.
 *         {@link UDMF_E_OK} success.
 *         {@link UDMF_E_INVALID_PARAM} The error code for common invalid args.
 * @see OH_UdmfData OH_UdsHtml Udmf_ErrCode.
 * @since 13
 */
int OH_UdmfData_GetPrimaryHtml(OH_UdmfData* data, OH_UdsHtml* html);

/**
 * @brief Get the count of {@link OH_UdmfRecord} in the {@link OH_UdmfData}.
 *
 * @param data Represents a pointer to an instance of {@link OH_UdmfData}.
 * @return Returns the count of {@link OH_UdmfRecord}
 * @see OH_UdmfData.
 * @since 13
 */
int OH_UdmfData_GetRecordCount(OH_UdmfData* data);

/**
 * @brief Get the record of the specified index from the {@link OH_UdmfData}.
 *
 * @param data Represents a pointer to an instance of {@link OH_UdmfData}.
 * @param index Represents the index of {@link OH_UdmfRecord} in the {@link OH_UdmfData}.
 * @return Returns the count of {@link OH_UdmfRecord}
 * @see OH_UdmfData.
 * @since 13
 */
OH_UdmfRecord* OH_UdmfData_GetRecord(OH_UdmfData* data, unsigned int index);

/**
 * @brief Checks whether the UDMF data is from a local device.
 *
 * @param data Represents a pointer to an instance of {@link OH_UdmfData}.
 * @return Returns the count of {@link OH_UdmfRecord}
 * @see OH_UdmfData.
 * @since 13
 */
bool OH_UdmfData_IsLocal(OH_UdmfData* data);

/**
 * @brief Creation a pointer to the instance of the {@link OH_UdmfRecord}, it's relate with UDS data.
 *
 * @return If the operation is successful, a pointer to the instance of the {@link OH_UdmfRecord}
 * structure is returned. If the operation is failed, nullptr is returned.
 * @see OH_UdmfRecord.
 * @since 12
 */
OH_UdmfRecord* OH_UdmfRecord_Create();

/**
 * @brief Destroy a pointer that points to an instance of {@link OH_UdmfRecord}.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_UdmfRecord}.
 * @see OH_UdmfRecord.
 * @since 12
 */
void OH_UdmfRecord_Destroy(OH_UdmfRecord* pThis);

/**
 * @brief Add one custom data to the {@link OH_UdmfRecord} record.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_UdmfRecord}.
 * @param typeId Represents record type, reference udmf_meta.h.
 * @param entry Represents custom data.
 * @param count Represents the size of data param.
 * @return Returns the status code of the execution. See {@link Udmf_ErrCode}.
 *         {@link UDMF_E_OK} success.
 *         {@link UDMF_E_INVALID_PARAM} The error code for common invalid args.
 * @see OH_UdmfRecord Udmf_ErrCode.
 * @since 12
 */
int OH_UdmfRecord_AddGeneralEntry(OH_UdmfRecord* record, const char* typeId,
                                  const unsigned char* entry, unsigned int count);

/**
 * @brief Add one {OH_UdsPlainText} data to the {@link OH_UdmfRecord} record.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_UdmfRecord}.
 * @param plainText Represents a pointer to an instance of {@link OH_UdsPlainText}.
 * @return Returns the status code of the execution. See {@link Udmf_ErrCode}.
 *         {@link UDMF_E_OK} success.
 *         {@link UDMF_E_INVALID_PARAM} The error code for common invalid args.
 * @see OH_UdmfRecord OH_UdsPlainText Udmf_ErrCode.
 * @since 12
 */
int OH_UdmfRecord_AddPlainText(OH_UdmfRecord* pThis, OH_UdsPlainText* plainText);

/**
 * @brief Add one {OH_UdsHyperlink} data to the {@link OH_UdmfRecord} record.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_UdmfRecord}.
 * @param hyperlink Represents a pointer to an instance of {@link OH_UdsHyperlink}.
 * @return Returns the status code of the execution. See {@link Udmf_ErrCode}.
 *         {@link UDMF_E_OK} success.
 *         {@link UDMF_E_INVALID_PARAM} The error code for common invalid args.
 * @see OH_UdmfRecord OH_UdsHyperlink Udmf_ErrCode.
 * @since 12
 */
int OH_UdmfRecord_AddHyperlink(OH_UdmfRecord* pThis, OH_UdsHyperlink* hyperlink);

/**
 * @brief Add one {OH_UdsHtml} data to the {@link OH_UdmfRecord} record.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_UdmfRecord}.
 * @param html Represents a pointer to an instance of {@link OH_UdsHtml}.
 * @return Returns the status code of the execution. See {@link Udmf_ErrCode}.
 *         {@link UDMF_E_OK} success.
 *         {@link UDMF_E_INVALID_PARAM} The error code for common invalid args.
 * @see OH_UdmfRecord OH_UdsHtml Udmf_ErrCode.
 * @since 12
 */
int OH_UdmfRecord_AddHtml(OH_UdmfRecord* pThis, OH_UdsHtml* html);

/**
 * @brief Add one {OH_UdsAppItem} data to the {@link OH_UdmfRecord} record.
 *
 * @param repThisord Represents a pointer to an instance of {@link OH_UdmfRecord}.
 * @param appItem Represents a pointer to an instance of {@link OH_UdsAppItem}.
 * @return Returns the status code of the execution. See {@link Udmf_ErrCode}.
 *         {@link UDMF_E_OK} success.
 *         {@link UDMF_E_INVALID_PARAM} The error code for common invalid args.
 * @see OH_UdmfRecord OH_UdsAppItem Udmf_ErrCode.
 * @since 12
 */
int OH_UdmfRecord_AddAppItem(OH_UdmfRecord* pThis, OH_UdsAppItem* appItem);

/**
 * @brief Get all types in the {@link OH_UdmfRecord} record.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_UdmfRecord}.
 * @param count Represents the types count that is a output param.
 * @return Returns string array that in {@link OH_UdmfRecord} when input parameters valid,
 * otherwise return nullptr.
 * @see OH_UdmfRecord.
 * @since 12
 */
char** OH_UdmfRecord_GetTypes(OH_UdmfRecord* pThis, unsigned int* count);

/**
 * @brief Get one entry data from the {@link OH_UdmfRecord} record.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_UdmfRecord}.
 * @param typeId Represents record type, reference udmf_meta.h.
 * @param entry Represents a pointer to entry data that is a output param.
 * @param count Represents the entry data length that is a output param.
 * @return Returns the status code of the execution. See {@link Udmf_ErrCode}.
 *         {@link UDMF_E_OK} success.
 *         {@link UDMF_E_INVALID_PARAM} The error code for common invalid args.
 *         {@link UDMF_ERR} Internal data error.
 * @see OH_UdmfRecord Udmf_ErrCode.
 * @since 12
 */
int OH_UdmfRecord_GetGeneralEntry(OH_UdmfRecord* pThis, const char* typeId,
                                  unsigned char** entry, unsigned int* count);

/**
 * @brief Get one {OH_UdsPlainText} data from the {@link OH_UdmfRecord} record.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_UdmfRecord}.
 * @param plainText Represents a pointer to an instance of {@link OH_UdsPlainText}.
 * @return Returns the status code of the execution. See {@link Udmf_ErrCode}.
 *         {@link UDMF_E_OK} success.
 *         {@link UDMF_E_INVALID_PARAM} The error code for common invalid args.
 *         {@link UDMF_ERR} Internal data error.
 * @see OH_UdmfRecord OH_UdsPlainText Udmf_ErrCode.
 * @since 12
 */
int OH_UdmfRecord_GetPlainText(OH_UdmfRecord* pThis, OH_UdsPlainText* plainText);

/**
 * @brief Get one {OH_UdsHyperlink} data from the {@link OH_UdmfRecord} record.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_UdmfRecord}.
 * @param hyperlink Represents a pointer to an instance of {@link OH_UdsHyperlink}.
 * @return Returns the status code of the execution. See {@link Udmf_ErrCode}.
 *         {@link UDMF_E_OK} success.
 *         {@link UDMF_E_INVALID_PARAM} The error code for common invalid args.
 *         {@link UDMF_ERR} Internal data error.
 * @see OH_UdmfRecord OH_UdsHyperlink Udmf_ErrCode.
 * @since 12
 */
int OH_UdmfRecord_GetHyperlink(OH_UdmfRecord* pThis, OH_UdsHyperlink* hyperlink);

/**
 * @brief Get one {OH_UdsHtml} data from the {@link OH_UdmfRecord} record.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_UdmfRecord}.
 * @param html Represents a pointer to an instance of {@link OH_UdsHtml}.
 * @return Returns the status code of the execution. See {@link Udmf_ErrCode}.
 *         {@link UDMF_E_OK} success.
 *         {@link UDMF_E_INVALID_PARAM} The error code for common invalid args.
 *         {@link UDMF_ERR} Internal data error.
 * @see OH_UdmfRecord OH_UdsHtml Udmf_ErrCode.
 * @since 12
 */
int OH_UdmfRecord_GetHtml(OH_UdmfRecord* pThis, OH_UdsHtml* html);

/**
 * @brief Get one {OH_UdsAppItem} data from the {@link OH_UdmfRecord} record.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_UdmfRecord}.
 * @param appItem Represents a pointer to an instance of {@link OH_UdsAppItem}.
 * @return Returns the status code of the execution. See {@link Udmf_ErrCode}.
 *         {@link UDMF_E_OK} success.
 *         {@link UDMF_E_INVALID_PARAM} The error code for common invalid args.
 *         {@link UDMF_ERR} Internal data error.
 * @see OH_UdmfRecord OH_UdsAppItem Udmf_ErrCode.
 * @since 12
 */
int OH_UdmfRecord_GetAppItem(OH_UdmfRecord* pThis, OH_UdsAppItem* appItem);

/**
 * @brief Creation a pointer to the instance of the {@link OH_UdmfProperty}
 * from a {@link OH_UdmfData} data.
 *
 * @param unifiedData Represents a pointer to an instance of {@link OH_UdmfData}.
 * @return If the operation is successful, a pointer to the instance of the {@link OH_UdmfProperty}
 * structure is returned. If the operation is failed, nullptr is returned.
 * @see OH_UdmfData OH_UdmfProperty.
 * @since 12
 */
OH_UdmfProperty* OH_UdmfProperty_Create(OH_UdmfData* unifiedData);

/**
 * @brief Destroy a pointer that points to the {@link OH_UdmfProperty} instance.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_UdmfProperty}.
 * @see OH_UdmfProperty.
 * @since 12
 */
void OH_UdmfProperty_Destroy(OH_UdmfProperty* pThis);

/**
 * @brief Get tag value from the {@link OH_UdmfProperty}.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_UdmfProperty}.
 * @return Returns a pointer of the tag value string when input parameters valid, otherwise return nullptr.
 * @see OH_UdmfProperty.
 * @since 12
 */
const char* OH_UdmfProperty_GetTag(OH_UdmfProperty* pThis);

/**
 * @brief Get timestamp value from the {@link OH_UdmfProperty}.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_UdmfProperty}.
 * @return Returns timestamp value.
 * @see OH_UdmfProperty
 * @since 12
 */
int64_t OH_UdmfProperty_GetTimestamp(OH_UdmfProperty* pThis);

/**
 * @brief Get share option value from the {@link OH_UdmfProperty}.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_UdmfProperty}.
 * @return Returns {@link Udmf_ShareOption} value.
 * @see OH_UdmfProperty Udmf_ShareOption
 * @since 12
 */
Udmf_ShareOption OH_UdmfProperty_GetShareOption(OH_UdmfProperty* pThis);

/**
 * @brief Get integer value by key from the {@link OH_UdmfProperty}.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_UdmfProperty}.
 * @param key Represents key-value pair's key
 * @param defaultValue Represents when get value failure.
 * @return Returns value associated with the key in successfully, otherwise return defaultValue.
 * @see OH_UdmfProperty.
 * @since 12
 */
int OH_UdmfProperty_GetExtrasIntParam(OH_UdmfProperty* pThis,
                                      const char* key, int defaultValue);

/**
 * @brief Get tag value from the {@link OH_UdmfProperty}.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_UdmfProperty}.
 * @param key Represents key-value pair's key.
 * @return Returns a pointer of the key value string when input parameters valid, otherwise return nullptr.
 * @see OH_UdmfProperty
 * @since 12
 */
const char* OH_UdmfProperty_GetExtrasStringParam(OH_UdmfProperty* pThis, const char* key);

/**
 * @brief Set tag value to {@link OH_UdmfProperty} .
 *
 * @param pThis Represents a pointer to an instance of {@link OH_UdmfProperty}.
 * @param tag Represents new tag param.
 * @return Returns the status code of the execution. See {@link Udmf_ErrCode}.
 *         {@link UDMF_E_OK} success.
 *         {@link UDMF_E_INVALID_PARAM} The error code for common invalid args.
 * @see OH_UdmfProperty Udmf_ErrCode.
 * @since 12
 */
int OH_UdmfProperty_SetTag(OH_UdmfProperty* pThis, const char* tag);

/**
 * @brief Set Udmf_ShareOption value to {@link OH_UdmfProperty}.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_UdmfProperty}.
 * @param option Represents new {@link Udmf_ShareOption} param.
 * @return Returns the status code of the execution. See {@link Udmf_ErrCode}.
 *         {@link UDMF_E_OK} success.
 *         {@link UDMF_E_INVALID_PARAM} The error code for common invalid args.
 * @see OH_UdmfProperty Udmf_ShareOption Udmf_ErrCode.
 * @since 12
 */
int OH_UdmfProperty_SetShareOption(OH_UdmfProperty* pThis, Udmf_ShareOption option);

/**
 * @brief Set extras param to {@link OH_UdmfProperty}.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_UdmfProperty}.
 * @param key Represents extras param's key value.
 * @param param Represents value of k-v pairs.
 * @return Returns the status code of the execution. See {@link Udmf_ErrCode}.
 *         {@link UDMF_E_OK} success.
 *         {@link UDMF_E_INVALID_PARAM} The error code for common invalid args.
 * @see OH_UdmfProperty Udmf_ErrCode.
 * @since 12
 */
int OH_UdmfProperty_SetExtrasIntParam(OH_UdmfProperty* pThis, const char* key, int param);

/**
 * @brief Set extras param to {@link OH_UdmfProperty}.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_UdmfProperty}.
 * @param key Represents extras param's key value.
 * @param param Represents value of k-v pairs.
 * @return Returns the status code of the execution. See {@link Udmf_ErrCode}.
 *         {@link UDMF_E_OK} success.
 *         {@link UDMF_E_INVALID_PARAM} The error code for common invalid args.
 * @see OH_UdmfProperty Udmf_ErrCode.
 * @since 12
 */
int OH_UdmfProperty_SetExtrasStringParam(OH_UdmfProperty* pThis,
                                         const char* key, const char* param);

/**
 * @brief Get {@link OH_UdmfData} data from udmf database.
 *
 * @param key Represents database store's key value.
 * @param intention Represents data type {@link Udmf_Intention}
 * @param unifiedData Represents output params of {@link OH_UdmfData};
 * @return Returns the status code of the execution. See {@link Udmf_ErrCode}.
 *         {@link UDMF_E_OK} success.
 *         {@link UDMF_E_INVALID_PARAM} The error code for common invalid args.
 *         {@link UDMF_ERR} Internal data error.
 * @see OH_UdmfProperty Udmf_Intention Udmf_ErrCode.
 * @since 12
 */
int OH_Udmf_GetUnifiedData(const char* key, Udmf_Intention intention, OH_UdmfData* unifiedData);

/**
 * @brief Set {@link OH_UdmfData} data to database.
 *
 * @param intention Represents data type {@link Udmf_Intention}.
 * @param unifiedData Represents a pointer to an instance of {@link OH_UdmfData}.
 * @param key Represents return value after set data to database successfully,
 * it's memory size not less than {@link UDMF_KEY_BUFFER_LEN}.
 * @param keyLen Represents size of key param.
 * @return Returns the status code of the execution. See {@link Udmf_ErrCode}.
 *         {@link UDMF_E_OK} success.
 *         {@link UDMF_E_INVALID_PARAM} The error code for common invalid args.
 *         {@link UDMF_ERR} Internal data error.
 * @see OH_UdmfProperty Udmf_Intention Udmf_ErrCode.
 * @since 12
 */
int OH_Udmf_SetUnifiedData(Udmf_Intention intention, OH_UdmfData* unifiedData,
                           char* key, unsigned int keyLen);

#ifdef __cplusplus
};
#endif

/** @} */
#endif
