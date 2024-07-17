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
 * @since 12
 */

/**
 * @file utd.h
 *
 * @brief Provides uniform type descriptor(UTD) related functions and struct.
 *
 * @kit ArkData
 * @library libudmf.so
 * @syscap SystemCapability.DistributedDataManager.UDMF.Core
 * @since 12
 */

#ifndef UTD_H
#define UTD_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Describes the unified data type descriptor.
 *
 * @since 12
 */
typedef struct OH_Utd OH_Utd;

/**
 * @brief Prouct a pointer to the instance of the {@link OH_Utd}.
 *
 * @param typeId Represents type of UTD, reference udmf_meta.h.
 * @return If the operation is successful, a pointer to the instance of the {@link OH_Utd}
 * structure is returned.If the operation is failed, nullptr is returned.
 * Must be destroyed with {@link OH_Utd_DestroyTypeDescriptor} when not needed.
 * @see OH_Utd.
 * @since 12
 */
OH_Utd* OH_Utd_Create(const char* typeId);

/**
 * @brief Destroy a pointer that points to the {@link OH_Utd} instance.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_Utd}.
 * @see OH_Utd.
 * @since 12
 */
void OH_Utd_Destroy(OH_Utd* pThis);

/**
 * @brief Get type id from the {@link OH_Utd}.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_Utd}.
 * @return Returns a string pointer when input args normally, otherwise return nullptr.
 * @see OH_Utd.
 * @since 12
 */
const char* OH_Utd_GetTypeId(OH_Utd* pThis);

/**
 * @brief Get description from the {@link OH_Utd}.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_Utd}.
 * @return Returns a string pointer when input args normally, otherwise return nullptr.
 * @see OH_Utd.
 * @since 12
 */
const char* OH_Utd_GetDescription(OH_Utd* pThis);

/**
 * @brief Get url from the {@link OH_Utd}.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_Utd}.
 * @return Returns a string pointer when input args normally, otherwise return nullptr.
 * @see OH_Utd.
 * @since 12
 */
const char* OH_Utd_GetReferenceUrl(OH_Utd* pThis);

/**
 * @brief Get icon file from the {@link OH_Utd}.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_Utd}.
 * @return Returns a string pointer when input args normally, otherwise return nullptr.
 * @see OH_Utd.
 * @since 12
 */
const char* OH_Utd_GetIconFile(OH_Utd* pThis);

/**
 * @brief Get belong to type id of the current {@link OH_Utd}.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_Utd}.
 * @param count Represents the return types count.
 * @return Returns string array when input args normally, otherwise return nullptr.
 * @see OH_Utd.
 * @since 12
 */
const char** OH_Utd_GetBelongingToTypes(OH_Utd* pThis, unsigned int* count);

/**
 * @brief Get filename extensions of the current {@link OH_Utd}.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_Utd}.
 * @param count Represents the return file extensions count.
 * @return Returns string array when input args normally, otherwise return nullptr.
 * @see OH_Utd.
 * @since 12
 */
const char** OH_Utd_GetFilenameExtensions(OH_Utd* pThis, unsigned int* count);

/**
 * @brief Get mime types of the current {@link OH_Utd}.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_Utd}.
 * @param count Represents the mime types count.
 * @return Returns string array when input args normally, otherwise return nullptr.
 * @see OH_Utd.
 * @since 12
 */
const char** OH_Utd_GetMimeTypes(OH_Utd* pThis, unsigned int* count);

/**
 * @brief Get type id by file name extension.
 *
 * @param extension Represents file name extension.
 * @param count Represents the types count.
 * @return Returns string list of types. Must be destroyed with {@link OH_Utd_DestroyStringList} when not needed.
 * @since 12
 */
const char** OH_Utd_GetTypesByFilenameExtension(const char* extension, unsigned int* count);

/**
 * @brief Get type id by mime type.
 *
 * @param mimeType Represents mime type
 * @param count Represents the types count.
 * @return Returns string list of types. Must be destroyed with {@link OH_Utd_DestroyStringList} when not needed.
 * @since 12
 */
const char** OH_Utd_GetTypesByMimeType(const char* mimeType, unsigned int* count);

/**
 * @brief Calculate relationships of two types.
 *
 * @param srcTypeId Represents source type id.
 * @param destTypeId Represents target type id.
 * @return Returns the status code of the execution.
 *         {@code false} Represents srcTypeId not belongs to destTypeId.
 *         {@code true} Represents srcTypeId belongs to destTypeId.
 * @since 12
 */
bool OH_Utd_BelongsTo(const char* srcTypeId, const char* destTypeId);

/**
 * @brief Calculate relationships of two types.
 *
 * @param srcTypeId Represents source type id.
 * @param destTypeId Represents target type id.
 * @return Returns the status code of the execution.
 *         {@code false} Represents srcTypeId not lower level to destTypeId.
 *         {@code true} Represents srcTypeId lower level to destTypeId.
 * @since 12
 */
bool OH_Utd_IsLower(const char* srcTypeId, const char* destTypeId);

/**
 * @brief Calculate relationships of two types.
 *
 * @param srcTypeId Represents source type id.
 * @param destTypeId Represents target type id.
 * @return Returns the status code of the execution.
 *         {@code false} Represents srcTypeId not higher level to destTypeId.
 *         {@code true} Represents srcTypeId higher level to destTypeId.
 * @since 12
 */
bool OH_Utd_IsHigher(const char* srcTypeId, const char* destTypeId);

/**
 * @brief Calculate two {@link OH_Utd}s are equal.
 *
 * @param utd1 Represents a pointer to {@link OH_Utd} instance.
 * @param utd2 Represents a pointer to {@link OH_Utd} instance.
 * @return Returns the status code of the execution.
 *         {@code false} Represents utd1 and utd2 are not equal.
 *         {@code true} Represents utd1 and utd2 are equal.
 * @since 12
 */
bool OH_Utd_Equals(OH_Utd* utd1, OH_Utd* utd2);

/**
 * @brief Destroy string list memory.
 *
 * @param list Represents a point to string list.
 * @param count Represents string count in list.
 * @since 12
 */
void OH_Utd_DestroyStringList(const char** list, unsigned int count);

#ifdef __cplusplus
};
#endif

/** @} */
#endif
