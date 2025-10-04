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
 * @file uds.h
 *
 * @brief Provides uniform data struct(UDS).
 *
 * @kit ArkData
 * @library libudmf.so
 * @syscap SystemCapability.DistributedDataManager.UDMF.Core
 * @since 12
 */

#ifndef UDS_H
#define UDS_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Describes the unified data struct of plaintext.
 *
 * @since 12
 */
typedef struct OH_UdsPlainText OH_UdsPlainText;

/**
 * @brief Describes the unified data struct of hyperlink.
 *
 * @since 12
 */
typedef struct OH_UdsHyperlink OH_UdsHyperlink;

/**
 * @brief Describes the unified data struct of html.
 *
 * @since 12
 */
typedef struct OH_UdsHtml OH_UdsHtml;

/**
 * @brief Describes the unified data struct of open harmony application item.
 *
 * @since 12
 */
typedef struct OH_UdsAppItem OH_UdsAppItem;

/**
 * @brief Describes the unified data struct of file uri.
 *
 * @since 13
 */
typedef struct OH_UdsFileUri OH_UdsFileUri;

/**
 * @brief Describes the unified data struct of open harmony pixel map.
 *
 * @since 13
 */
typedef struct OH_UdsPixelMap OH_UdsPixelMap;

/**
 * @brief Describes the unified data struct of content form.
 *
 * @since 14
 */
typedef struct OH_UdsContentForm OH_UdsContentForm;

/**
 * @brief Describes the of pixel map native.
 *
 * @since 13
 */
struct OH_PixelmapNative;

/**
 * @brief Describes the unified data struct of array buffer.
 *
 * @since 13
 */
typedef struct OH_UdsArrayBuffer OH_UdsArrayBuffer;

/**
 * @brief Describes the key-value object of UDS data.
 *
 * @since 22
 */
typedef struct OH_UdsDetails OH_UdsDetails;

/**
 * @brief Creation a pointer to the instance of the {@link OH_UdsPlainText}.
 *
 * @return If the operation is successful, a pointer to the instance of the {@link OH_UdsPlainText}
 * structure is returned. If the operation is failed, nullptr is returned.
 * @see OH_UdsPlainText
 * @since 12
 */
OH_UdsPlainText* OH_UdsPlainText_Create();

/**
 * @brief Destroy a pointer that points to the {@link OH_UdsPlainText} instance.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_UdsPlainText}.
 * @see OH_UdsPlainText
 * @since 12
 */
void OH_UdsPlainText_Destroy(OH_UdsPlainText* pThis);

/**
 * @brief Get type id from the {@link OH_UdsPlainText}.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_UdsPlainText}.
 * @return Returns a pointer of the value string when input args normally, otherwise return nullptr.
 * @see OH_UdsPlainText
 * @since 12
 */
const char* OH_UdsPlainText_GetType(OH_UdsPlainText* pThis);

/**
 * @brief Get content from the {@link OH_UdsPlainText}.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_UdsPlainText}.
 * @return Returns a pointer of the value string when input args normally, otherwise return nullptr.
 * @see OH_UdsPlainText
 * @since 12
 */
const char* OH_UdsPlainText_GetContent(OH_UdsPlainText* pThis);

/**
 * @brief Get abstract from the {@link OH_UdsPlainText}.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_UdsPlainText}.
 * @return Returns a pointer of the value string when input args normally, otherwise return nullptr.
 * @see OH_UdsPlainText
 * @since 12
 */
const char* OH_UdsPlainText_GetAbstract(OH_UdsPlainText* pThis);

/**
 * @brief Get details from the {@link OH_UdsPlainText}.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_UdsPlainText}.
 * @param details Represents a pointer to an instance of {@link OH_UdsDetails}. The pointer cannot be null.
 * @return Returns the status code of the execution. See {@link Udmf_ErrCode}.
 *         {@link UDMF_E_OK} success.
 *         {@link UDMF_E_INVALID_PARAM} The error code for common invalid args.
 * @see OH_UdsPlainText OH_UdsDetails Udmf_ErrCode
 * @since 22
 */
int OH_UdsPlainText_GetDetails(OH_UdsPlainText* pThis, OH_UdsDetails* details);

/**
 * @brief Set content to the {@link OH_UdsPlainText}.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_UdsPlainText}.
 * @param content Represents a new content string.
 * @return Returns the status code of the execution. See {@link Udmf_ErrCode}.
 *         {@link UDMF_E_OK} success.
 *         {@link UDMF_E_INVALID_PARAM} The error code for common invalid args.
 * @see OH_UdsPlainText Udmf_ErrCode
 * @since 12
 */
int OH_UdsPlainText_SetContent(OH_UdsPlainText* pThis, const char* content);

/**
 * @brief Set abstract to the {@link OH_UdsPlainText}.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_UdsPlainText}.
 * @param abstract Represents a new string value.
 * @return Returns the status code of the execution. See {@link Udmf_ErrCode}.
 *         {@link UDMF_E_OK} success.
 *         {@link UDMF_E_INVALID_PARAM} The error code for common invalid args.
 * @see OH_UdsPlainText Udmf_ErrCode
 * @since 12
 */
int OH_UdsPlainText_SetAbstract(OH_UdsPlainText* pThis, const char* abstract);

/**
 * @brief Set details to the {@link OH_UdsPlainText}.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_UdsPlainText}.
 * @param details Represents a pointer to an instance of {@link OH_UdsDetails}. The pointer cannot be null.
 * @return Returns the status code of the execution. See {@link Udmf_ErrCode}.
 *         {@link UDMF_E_OK} success.
 *         {@link UDMF_E_INVALID_PARAM} The error code for common invalid args.
 * @see OH_UdsPlainText OH_UdsDetails Udmf_ErrCode
 * @since 22
 */
int OH_UdsPlainText_SetDetails(OH_UdsPlainText* pThis, const OH_UdsDetails* details);

/**
 * @brief Creation a pointer to the instance of the {@link OH_UdsHyperlink}.
 *
 * @return If the operation is successful, a pointer to the instance of {@link OH_UdsHyperlink}
 * structure is returned. If the operation is failed, nullptr is returned.
 * @see OH_UdsHyperlink
 * @since 12
 */
OH_UdsHyperlink* OH_UdsHyperlink_Create();

/**
 * @brief Destroy a pointer that points to the {@link OH_UdsHyperlink} instance.
 *
 * @param pThis Represents a pointer to an  instance of {@link OH_UdsHyperlink}.
 * @see OH_UdsHyperlink
 * @since 12
 */
void OH_UdsHyperlink_Destroy(OH_UdsHyperlink* pThis);

/**
 * @brief Get type from the {@link OH_UdsHyperlink}.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_UdsHyperlink}.
 * @return Returns a pointer of the value string when input args normally, otherwise return nullptr.
 * @see OH_UdsHyperlink
 * @since 12
 */
const char* OH_UdsHyperlink_GetType(OH_UdsHyperlink* pThis);

/**
 * @brief Get url from the {@link OH_UdsHyperlink}.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_UdsHyperlink}.
 * @return Returns a pointer of the value string when input args normally, otherwise return nullptr.
 * @see OH_UdsHyperlink
 * @since 12
 */
const char* OH_UdsHyperlink_GetUrl(OH_UdsHyperlink* pThis);

/**
 * @brief Get description from the {@link OH_UdsHyperlink}.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_UdsHyperlink}.
 * @return Returns a pointer of the value string when input args normally, otherwise return nullptr.
 * @see OH_UdsHyperlink
 * @since 12
 */
const char* OH_UdsHyperlink_GetDescription(OH_UdsHyperlink* pThis);

/**
 * @brief Get details from the {@link OH_UdsHyperlink}.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_UdsHyperlink}.
 * @param details Represents a pointer to an instance of {@link OH_UdsDetails}. The pointer cannot be null.
 * @return Returns the status code of the execution. See {@link Udmf_ErrCode}.
 *         {@link UDMF_E_OK} success.
 *         {@link UDMF_E_INVALID_PARAM} The error code for common invalid args.
 * @see OH_UdsHyperlink OH_UdsDetails Udmf_ErrCode
 * @since 22
 */
int OH_UdsHyperlink_GetDetails(OH_UdsHyperlink* pThis, OH_UdsDetails* details);

/**
 * @brief Set url to the {@link OH_UdsHyperlink}.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_UdsHyperlink}.
 * @param url Represents a new string value.
 * @return Returns the status code of the execution. See {@link Udmf_ErrCode}.
 *         {@link UDMF_E_OK} success.
 *         {@link UDMF_E_INVALID_PARAM} The error code for common invalid args.
 * @see OH_UdsHyperlink Udmf_ErrCode
 * @since 12
 */
int OH_UdsHyperlink_SetUrl(OH_UdsHyperlink* pThis, const char* url);

/**
 * @brief Set description to the {@link OH_UdsHyperlink}.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_UdsHyperlink}.
 * @param description Represents a new string value.
 * @return Returns the status code of the execution. See {@link Udmf_ErrCode}.
 *         {@link UDMF_E_OK} success.
 *         {@link UDMF_E_INVALID_PARAM} The error code for common invalid args.
 * @see OH_UdsHyperlink Udmf_ErrCode
 * @since 12
 */
int OH_UdsHyperlink_SetDescription(OH_UdsHyperlink* pThis, const char* description);

/**
 * @brief Set details to the {@link OH_UdsHyperlink}.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_UdsHyperlink}.
 * @param details Represents a pointer to an instance of {@link OH_UdsDetails}. The pointer cannot be null.
 * @return Returns the status code of the execution. See {@link Udmf_ErrCode}.
 *         {@link UDMF_E_OK} success.
 *         {@link UDMF_E_INVALID_PARAM} The error code for common invalid args.
 * @since 22
 * @see OH_UdsHyperlink OH_UdsDetails Udmf_ErrCode
 */
int OH_UdsHyperlink_SetDetails(OH_UdsHyperlink* pThis, const OH_UdsDetails* details);

/**
 * @brief Creation a pointer to the instance of the {@link OH_UdsHtml}.
 *
 * @return If the operation is successful, a pointer to the instance of the {@link OH_UdsHtml}
 * structure is returned. If the operation is failed, nullptr is returned.
 * @see OH_UdsHtml
 * @since 12
 */
OH_UdsHtml* OH_UdsHtml_Create();

/**
 * @brief Destroy a pointer that points to the {@link OH_UdsHtml} instance.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_UdsHtml}.
 * @see OH_UdsHtml
 * @since 12
 */
void OH_UdsHtml_Destroy(OH_UdsHtml* pThis);

/**
 * @brief Get html from the {@link OH_UdsHtml}.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_UdsHtml}.
 * @return Returns a pointer of the value string when input args normally, otherwise return nullptr.
 * @see OH_UdsHtml
 * @since 12
 */
const char* OH_UdsHtml_GetType(OH_UdsHtml* pThis);

/**
 * @brief Get content from the {@link OH_UdsHtml}.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_UdsHtml}.
 * @return Returns a pointer of the value string when input args normally, otherwise return nullptr.
 * @see OH_UdsHtml
 * @since 12
 */
const char* OH_UdsHtml_GetContent(OH_UdsHtml* pThis);

/**
 * @brief Get plain content from the {@link OH_UdsHtml}.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_UdsHtml}.
 * @return Returns a pointer of the value string when input args normally, otherwise return nullptr.
 * @see OH_UdsHtml
 * @since 12
 */
const char* OH_UdsHtml_GetPlainContent(OH_UdsHtml* pThis);

/**
 * @brief Get details from the {@link OH_UdsHtml}.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_UdsHtml}.
 * @param details Represents a pointer to an instance of {@link OH_UdsDetails}. The pointer cannot be null.
 * @return Returns the status code of the execution. See {@link Udmf_ErrCode}.
 *         {@link UDMF_E_OK} success.
 *         {@link UDMF_E_INVALID_PARAM} The error code for common invalid args.
 * @since 22
 * @see OH_UdsHtml OH_UdsDetails Udmf_ErrCode
 */
int OH_UdsHtml_GetDetails(OH_UdsHtml* pThis, OH_UdsDetails* details);

/**
 * @brief Set content to the {@link OH_UdsHtml}.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_UdsHtml}.
 * @param content Represents a new string value.
 * @return Returns the status code of the execution. See {@link Udmf_ErrCode}.
 *         {@link UDMF_E_OK} success.
 *         {@link UDMF_E_INVALID_PARAM} The error code for common invalid args.
 * @see OH_UdsHtml Udmf_ErrCode
 * @since 12
 */
int OH_UdsHtml_SetContent(OH_UdsHtml* pThis, const char* content);

/**
 * @brief Set plain content to the {@link OH_UdsHtml}.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_UdsHtml}.
 * @param plainContent Represents a new string value.
 * @return Returns the status code of the execution. See {@link Udmf_ErrCode}.
 *         {@link UDMF_E_OK} success.
 *         {@link UDMF_E_INVALID_PARAM} The error code for common invalid args.
 * @see OH_UdsHtml Udmf_ErrCode
 * @since 12
 */
int OH_UdsHtml_SetPlainContent(OH_UdsHtml* pThis, const char* plainContent);

/**
 * @brief Set details to the {@link OH_UdsHtml}.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_UdsHtml}.
 * @param details Represents a pointer to an instance of {@link OH_UdsDetails}. The pointer cannot be null.
 * @return Returns the status code of the execution. See {@link Udmf_ErrCode}.
 *         {@link UDMF_E_OK} success.
 *         {@link UDMF_E_INVALID_PARAM} The error code for common invalid args.
 * @since 22
 * @see OH_UdsHtml OH_UdsDetails Udmf_ErrCode
 */
int OH_UdsHtml_SetDetails(OH_UdsHtml* pThis, const OH_UdsDetails* details);

/**
 * @brief Creation a pointer to the instance of the {@link OH_UdsAppItem}.
 *
 * @return If the operation is successful, a pointer to the instance of the {@link OH_UdsAppItem}
 * structure is returned. sIf the operation is failed, nullptr is returned.
 * @see OH_UdsAppItem
 * @since 12
 */
OH_UdsAppItem* OH_UdsAppItem_Create();

/**
 * @brief Destroy a pointer that points to the {@link OH_UdsAppItem} instance.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_UdsAppItem}.
 * @see OH_UdsAppItem
 * @since 12
 */
void OH_UdsAppItem_Destroy(OH_UdsAppItem* pThis);

/**
 * @brief Get type from the {@link OH_UdsAppItem}.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_UdsAppItem}.
 * @return Returns a pointer of the value string when input args normally, otherwise return nullptr.
 * @see OH_UdsAppItem
 * @since 12
 */
const char* OH_UdsAppItem_GetType(OH_UdsAppItem* pThis);

/**
 * @brief Get app id from the {@link OH_UdsAppItem}.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_UdsAppItem}.
 * @return Returns a pointer of the value string when input args normally, otherwise return nullptr.
 * @see OH_UdsAppItem
 * @since 12
 */
const char* OH_UdsAppItem_GetId(OH_UdsAppItem* pThis);

/**
 * @brief Get app name from the {@link OH_UdsAppItem}.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_UdsAppItem}.
 * @return Returns a pointer of the value string when input args normally, otherwise return nullptr.
 * @see OH_UdsAppItem
 * @since 12
 */
const char* OH_UdsAppItem_GetName(OH_UdsAppItem* pThis);

/**
 * @brief Get app icon id from the {@link OH_UdsAppItem}.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_UdsAppItem}.
 * @return Returns a pointer of the value string when input args normally, otherwise return nullptr.
 * @see OH_UdsAppItem
 * @since 12
 */
const char* OH_UdsAppItem_GetIconId(OH_UdsAppItem* pThis);

/**
 * @brief Get app label id from the {@link OH_UdsAppItem}.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_UdsAppItem}.
 * @return Returns a pointer of the value string when input args normally, otherwise return nullptr.
 * @see OH_UdsAppItem
 * @since 12
 */
const char* OH_UdsAppItem_GetLabelId(OH_UdsAppItem* pThis);

/**
 * @brief Get bundle name from the {@link OH_UdsAppItem}.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_UdsAppItem}.
 * @return Returns a pointer of the value string when input args normally, otherwise return nullptr.
 * @see OH_UdsAppItem
 * @since 12
 */
const char* OH_UdsAppItem_GetBundleName(OH_UdsAppItem* pThis);

/**
 * @brief Get ability name from the {@link OH_UdsAppItem}.
 *
 * @param pThis Represents a pointer to an instance {@link OH_UdsAppItem}.
 * @return Returns a pointer of the value string when input args normally, otherwise return nullptr.
 * @see OH_UdsAppItem
 * @since 12
 */
const char* OH_UdsAppItem_GetAbilityName(OH_UdsAppItem* pThis);

/**
 * @brief Get details from the {@link OH_UdsAppItem}.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_UdsAppItem}.
 * @param details Represents a pointer to an instance of {@link OH_UdsDetails}. The pointer cannot be null.
 * @return Returns the status code of the execution. See {@link Udmf_ErrCode}.
 *         {@link UDMF_E_OK} success.
 *         {@link UDMF_E_INVALID_PARAM} The error code for common invalid args.
 * @since 22
 * @see OH_UdsAppItem OH_UdsDetails Udmf_ErrCode
 */
int OH_UdsAppItem_GetDetails(OH_UdsAppItem* pThis, OH_UdsDetails* details);

/**
 * @brief Set application id to the {@link OH_UdsAppItem}.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_UdsAppItem}.
 * @param appId Represents a new string value.
 * @return Returns the status code of the execution. See {@link Udmf_ErrCode}.
 *         {@link UDMF_E_OK} success.
 *         {@link UDMF_E_INVALID_PARAM} The error code for common invalid args.
 * @see OH_UdsAppItem Udmf_ErrCode
 * @since 12
 */
int OH_UdsAppItem_SetId(OH_UdsAppItem* pThis, const char* appId);

/**
 * @brief Set application name to the {@link OH_UdsAppItem}.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_UdsAppItem}.
 * @param appName Represents a new string value.
 * @return Returns the status code of the execution. See {@link Udmf_ErrCode}.
 *         {@link UDMF_E_OK} success.
 *         {@link UDMF_E_INVALID_PARAM} The error code for common invalid args.
 * @see OH_UdsAppItem Udmf_ErrCode
 * @since 12
 */
int OH_UdsAppItem_SetName(OH_UdsAppItem* pThis, const char* appName);

/**
 * @brief Set application icon id to the {@link OH_UdsAppItem}.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_UdsAppItem}.
 * @param appIconId Represents a new string value.
 * @return Returns the status code of the execution. See {@link Udmf_ErrCode}.
 *         {@link UDMF_E_OK} success.
 *         {@link UDMF_E_INVALID_PARAM} The error code for common invalid args.
 * @see OH_UdsAppItem Udmf_ErrCode
 * @since 12
 */
int OH_UdsAppItem_SetIconId(OH_UdsAppItem* pThis, const char* appIconId);

/**
 * @brief Set application label id to the {@link OH_UdsAppItem}.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_UdsAppItem}.
 * @param appLabelId Represents a new string value.
 * @return Returns the status code of the execution. See {@link Udmf_ErrCode}.
 *         {@link UDMF_E_OK} success.
 *         {@link UDMF_E_INVALID_PARAM} The error code for common invalid args.
 * @see OH_UdsAppItem Udmf_ErrCode
 * @since 12
 */
int OH_UdsAppItem_SetLabelId(OH_UdsAppItem* pThis, const char* appLabelId);

/**
 * @brief Set bundle name to the {@link OH_UdsAppItem}.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_UdsAppItem}.
 * @param bundleName Represents a new string value.
 * @return Returns the status code of the execution. See {@link Udmf_ErrCode}.
 *         {@link UDMF_E_OK} success.
 *         {@link UDMF_E_INVALID_PARAM} The error code for common invalid args.
 * @see OH_UdsAppItem Udmf_ErrCode
 * @since 12
 */
int OH_UdsAppItem_SetBundleName(OH_UdsAppItem* pThis, const char* bundleName);

/**
 * @brief Set ability name to the {@link OH_UdsAppItem}.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_UdsAppItem}.
 * @param abilityName Represents a new string value.
 * @return Returns the status code of the execution. See {@link Udmf_ErrCode}.
 *         {@link UDMF_E_OK} success.
 *         {@link UDMF_E_INVALID_PARAM} The error code for common invalid args.
 * @see OH_UdsAppItem Udmf_ErrCode
 * @since 12
 */
int OH_UdsAppItem_SetAbilityName(OH_UdsAppItem* pThis, const char* abilityName);

/**
 * @brief Set details to the {@link OH_UdsAppItem}.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_UdsAppItem}.
 * @param details Represents a pointer to an instance of {@link OH_UdsDetails}. The pointer cannot be null.
 * @return Returns the status code of the execution. See {@link Udmf_ErrCode}.
 *         {@link UDMF_E_OK} success.
 *         {@link UDMF_E_INVALID_PARAM} The error code for common invalid args.
 * @see OH_UdsAppItem OH_UdsDetails Udmf_ErrCode
 * @since 22
 */
int OH_UdsAppItem_SetDetails(OH_UdsAppItem* pThis, const OH_UdsDetails* details);

/**
 * @brief Creation a pointer to the instance of the {@link OH_UdsFileUri}.
 *
 * @return If the operation is successful, a pointer to the instance of the {@link OH_UdsFileUri}
 * structure is returned. If the operation is failed, nullptr is returned.
 * @see OH_UdsFileUri
 * @since 13
 */
OH_UdsFileUri* OH_UdsFileUri_Create();

/**
 * @brief Destroy a pointer that points to the {@link OH_UdsFileUri} instance.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_UdsFileUri}.
 * @see OH_UdsFileUri
 * @since 13
 */
void OH_UdsFileUri_Destroy(OH_UdsFileUri* pThis);

/**
 * @brief Get type id from the {@link OH_UdsFileUri}.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_UdsFileUri}.
 * @return Returns a pointer of the value string when input args normally, otherwise return nullptr.
 * @see OH_UdsFileUri
 * @since 13
 */
const char* OH_UdsFileUri_GetType(OH_UdsFileUri* pThis);

/**
 * @brief Get file uri from the {@link OH_UdsFileUri}.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_UdsFileUri}.
 * @return Returns a pointer of the value string when input args normally, otherwise return nullptr.
 * @see OH_UdsFileUri
 * @since 13
 */
const char* OH_UdsFileUri_GetFileUri(OH_UdsFileUri* pThis);

/**
 * @brief Get file type from the {@link OH_UdsFileUri}.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_UdsFileUri}.
 * @return Returns a pointer of the value string when input args normally, otherwise return nullptr.
 * @see OH_UdsFileUri
 * @since 13
 */
const char* OH_UdsFileUri_GetFileType(OH_UdsFileUri* pThis);

/**
 * @brief Get details from the {@link OH_UdsFileUri}.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_UdsFileUri}.
 * @param details Represents a pointer to an instance of {@link OH_UdsDetails}. The pointer cannot be null.
 * @return Returns the status code of the execution. See {@link Udmf_ErrCode}.
 *         {@link UDMF_E_OK} success.
 *         {@link UDMF_E_INVALID_PARAM} The error code for common invalid args.
 * @since 22
 * @see OH_UdsFileUri OH_UdsDetails Udmf_ErrCode
 */
int OH_UdsFileUri_GetDetails(OH_UdsFileUri* pThis, OH_UdsDetails* details);

/**
 * @brief Set file uri to the {@link OH_UdsFileUri}.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_UdsFileUri}.
 * @param fileUri Represents a new file uri string.
 * @return Returns the status code of the execution. See {@link Udmf_ErrCode}.
 *         {@link UDMF_E_OK} success.
 *         {@link UDMF_E_INVALID_PARAM} The error code for common invalid args.
 * @see OH_UdsFileUri Udmf_ErrCode
 * @since 13
 */
int OH_UdsFileUri_SetFileUri(OH_UdsFileUri* pThis, const char* fileUri);

/**
 * @brief Set file type to the {@link OH_UdsFileUri}.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_UdsFileUri}.
 * @param fileType Represents a new file type string.
 * @return Returns the status code of the execution. See {@link Udmf_ErrCode}.
 *         {@link UDMF_E_OK} success.
 *         {@link UDMF_E_INVALID_PARAM} The error code for common invalid args.
 * @see OH_UdsFileUri Udmf_ErrCode
 * @since 13
 */
int OH_UdsFileUri_SetFileType(OH_UdsFileUri* pThis, const char* fileType);

/**
 * @brief Set details to the {@link OH_UdsFileUri}.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_UdsFileUri}.
 * @param details Represents a pointer to an instance of {@link OH_UdsDetails}. The pointer cannot be null.
 * @return Returns the status code of the execution. See {@link Udmf_ErrCode}.
 *         {@link UDMF_E_OK} success.
 *         {@link UDMF_E_INVALID_PARAM} The error code for common invalid args.
 * @see OH_UdsFileUri OH_UdsDetails Udmf_ErrCode
 * @since 22
 */
int OH_UdsFileUri_SetDetails(OH_UdsFileUri* pThis, const OH_UdsDetails* details);

/**
 * @brief Creation a pointer to the instance of the {@link OH_UdsPixelMap}.
 *
 * @return If the operation is successful, a pointer to the instance of the {@link OH_UdsPixelMap}
 * structure is returned. If the memory is not enough, nullptr is returned.
 * @see OH_UdsPixelMap
 * @since 13
 */
OH_UdsPixelMap* OH_UdsPixelMap_Create();

/**
 * @brief Destroy a pointer that points to the {@link OH_UdsPixelMap} instance.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_UdsPixelMap}.
 * @see OH_UdsPixelMap
 * @since 13
 */
void OH_UdsPixelMap_Destroy(OH_UdsPixelMap* pThis);

/**
 * @brief Get type id from the {@link OH_UdsPixelMap}.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_UdsPixelMap}.
 * @return Returns a pointer of the value string when input args normally, otherwise return nullptr.
 * @see OH_UdsPixelMap
 * @since 13
 */
const char* OH_UdsPixelMap_GetType(OH_UdsPixelMap* pThis);

/**
 * @brief Get pixel map from the {@link OH_UdsPixelMap}.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_UdsPixelMap}.
 * @param pixelmapNative Represents output params of {@link OH_PixelmapNative}.
 * @see OH_UdsPixelMap
 * @since 13
 */
void OH_UdsPixelMap_GetPixelMap(OH_UdsPixelMap* pThis, OH_PixelmapNative* pixelmapNative);

/**
 * @brief Get details from the {@link OH_UdsPixelMap}.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_UdsPixelMap}.
 * @param details Represents a pointer to an instance of {@link OH_UdsDetails}. The pointer cannot be null.
 * @return Returns the status code of the execution. See {@link Udmf_ErrCode}.
 *         {@link UDMF_E_OK} success.
 *         {@link UDMF_E_INVALID_PARAM} The error code for common invalid args.
 * @since 22
 * @see OH_UdsPixelMap OH_UdsDetails Udmf_ErrCode
 */
int OH_UdsPixelMap_GetDetails(OH_UdsPixelMap* pThis, OH_UdsDetails* details);

/**
 * @brief Set pixel map to the {@link OH_UdsPixelMap}.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_UdsPixelMap}.
 * @param pixelmapNative Represents a new {@link OH_PixelmapNative}.
 * @return Returns the status code of the execution. See {@link Udmf_ErrCode}.
 *         {@link UDMF_E_OK} success.
 *         {@link UDMF_E_INVALID_PARAM} The error code for common invalid args.
 * @see OH_UdsPixelMap Udmf_ErrCode
 * @since 13
 */
int OH_UdsPixelMap_SetPixelMap(OH_UdsPixelMap* pThis, OH_PixelmapNative* pixelmapNative);

/**
 * @brief Set details to the {@link OH_UdsPixelMap}.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_UdsPixelMap}.
 * @param details Represents a pointer to an instance of {@link OH_UdsDetails}. The pointer cannot be null.
 * @return Returns the status code of the execution. See {@link Udmf_ErrCode}.
 *         {@link UDMF_E_OK} success.
 *         {@link UDMF_E_INVALID_PARAM} The error code for common invalid args.
 * @since 22
 * @see OH_UdsPixelMap OH_UdsDetails Udmf_ErrCode
 */
int OH_UdsPixelMap_SetDetails(OH_UdsPixelMap* pThis, const OH_UdsDetails* details);

/**
 * @brief Creation a pointer to the instance of the {@link OH_UdsArrayBuffer}.
 *
 * @return If the operation is successful, a pointer to the instance of the {@link OH_UdsArrayBuffer}
 * structure is returned. If the memory is not enough, nullptr is returned.
 * @see OH_UdsArrayBuffer
 * @since 13
 */
OH_UdsArrayBuffer* OH_UdsArrayBuffer_Create();

/**
 * @brief Destroy a pointer that points to the {@link OH_UdsArrayBuffer} instance.
 *
 * @param buffer Represents a pointer to an instance of {@link OH_UdsArrayBuffer}.
 * @return Returns the status code of the execution. See {@link Udmf_ErrCode}.
 *         {@link UDMF_E_OK} success.
 *         {@link UDMF_E_INVALID_PARAM} The error code for common invalid args.
 * @see OH_UdsArrayBuffer Udmf_ErrCode
 * @since 13
 */
int OH_UdsArrayBuffer_Destroy(OH_UdsArrayBuffer* buffer);

/**
 * @brief Set array buffer data to the {@link OH_UdsArrayBuffer}.
 *
 * @param buffer Represents a pointer to an instance of {@link OH_UdsArrayBuffer}.
 * @param data Represents the array buffer data.
 * @param len Represents the length of data param.
 * @return Returns the status code of the execution. See {@link Udmf_ErrCode}.
 *         {@link UDMF_E_OK} success.
 *         {@link UDMF_E_INVALID_PARAM} The error code for common invalid args.
 * @see OH_UdsArrayBuffer Udmf_ErrCode
 * @since 13
 */
int OH_UdsArrayBuffer_SetData(OH_UdsArrayBuffer* buffer, unsigned char* data, unsigned int len);

/**
 * @brief Get array buffer data from the {@link OH_UdsArrayBuffer}.
 *
 * @param buffer Represents a pointer to an instance of {@link OH_UdsArrayBuffer}.
 * @param data Represents a pointer to array buffer data that is a output param.
 * @param len Represents the array buffer data length that is a output param.
 * @return Returns the status code of the execution. See {@link Udmf_ErrCode}.
 *         {@link UDMF_E_OK} success.
 *         {@link UDMF_E_INVALID_PARAM} The error code for common invalid args.
 * @see OH_UdsArrayBuffer Udmf_ErrCode
 * @since 13
 */
int OH_UdsArrayBuffer_GetData(OH_UdsArrayBuffer* buffer, unsigned char** data, unsigned int* len);

/**
 * @brief Creation a pointer to the instance of the {@link OH_UdsContentForm}.
 *
 * @return If the operation is successful, a pointer to the instance of the {@link OH_UdsContentForm}
 * structure is returned. If the operation is failed, nullptr is returned.
 * @see OH_UdsContentForm
 * @since 14
 */
OH_UdsContentForm* OH_UdsContentForm_Create();

/**
 * @brief Destroy a pointer that points to the {@link OH_UdsContentForm} instance.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_UdsContentForm}.
 * @see OH_UdsContentForm
 * @since 14
 */
void OH_UdsContentForm_Destroy(OH_UdsContentForm* pThis);

/**
 * @brief Get type id from the {@link OH_UdsContentForm}.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_UdsContentForm}.
 * @return Returns a pointer of the value string when input args normally, otherwise return nullptr.
 * @see OH_UdsContentForm
 * @since 14
 */
const char* OH_UdsContentForm_GetType(OH_UdsContentForm* pThis);

/**
 * @brief Get thumb data from the {@link OH_UdsContentForm}.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_UdsContentForm}.
 * @param thumbData Represents a pointer to thumb data that is a output param.
 * @param len Represents the thumb data length that is a output param.
 * @return Returns the status code of the execution. See {@link Udmf_ErrCode}.
 *         {@link UDMF_E_OK} success.
 *         {@link UDMF_E_INVALID_PARAM} The error code for common invalid args.
 *         {@link UDMF_ERR} Internal data error.
 * @see OH_UdsContentForm Udmf_ErrCode
 * @since 14
 */
int OH_UdsContentForm_GetThumbData(OH_UdsContentForm* pThis, unsigned char** thumbData, unsigned int* len);

/**
 * @brief Get description from the {@link OH_UdsContentForm}.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_UdsContentForm}.
 * @return Returns a pointer of the value string when input args normally, otherwise return nullptr.
 * @see OH_UdsContentForm
 * @since 14
 */
const char* OH_UdsContentForm_GetDescription(OH_UdsContentForm* pThis);

/**
 * @brief Get title from the {@link OH_UdsContentForm}.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_UdsContentForm}.
 * @return Returns a pointer of the value string when input args normally, otherwise return nullptr.
 * @see OH_UdsContentForm
 * @since 14
 */
const char* OH_UdsContentForm_GetTitle(OH_UdsContentForm* pThis);

/**
 * @brief Get thumb data from the {@link OH_UdsContentForm}.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_UdsContentForm}.
 * @param appIcon Represents a pointer to app icon that is a output param.
 * @param len Represents the app icon length that is a output param.
 * @return Returns the status code of the execution. See {@link Udmf_ErrCode}.
 *         {@link UDMF_E_OK} success.
 *         {@link UDMF_E_INVALID_PARAM} The error code for common invalid args.
 *         {@link UDMF_ERR} Internal data error.
 * @see OH_UdsContentForm Udmf_ErrCode
 * @since 14
 */
int OH_UdsContentForm_GetAppIcon(OH_UdsContentForm* pThis, unsigned char** appIcon, unsigned int* len);

/**
 * @brief Get app name from the {@link OH_UdsContentForm}.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_UdsContentForm}.
 * @return Returns a pointer of the value string when input args normally, otherwise return nullptr.
 * @see OH_UdsContentForm
 * @since 14
 */
const char* OH_UdsContentForm_GetAppName(OH_UdsContentForm* pThis);

/**
 * @brief Get link url from the {@link OH_UdsContentForm}.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_UdsContentForm}.
 * @return Returns a pointer of the value string when input args normally, otherwise return nullptr.
 * @see OH_UdsContentForm
 * @since 14
 */
const char* OH_UdsContentForm_GetLinkUri(OH_UdsContentForm* pThis);

/**
 * @brief Set thumb data to the {@link OH_UdsContentForm}.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_UdsContentForm}.
 * @param thumbData Represents the thumb data.
 * @param len Represents the length of thumb data param.
 * @return Returns the status code of the execution. See {@link Udmf_ErrCode}.
 *         {@link UDMF_E_OK} success.
 *         {@link UDMF_E_INVALID_PARAM} The error code for common invalid args.
 * @see OH_UdsContentForm Udmf_ErrCode
 * @since 14
 */
int OH_UdsContentForm_SetThumbData(OH_UdsContentForm* pThis, const unsigned char* thumbData, unsigned int len);

/**
 * @brief Set description to the {@link OH_UdsContentForm}.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_UdsContentForm}.
 * @param description Represents a description string.
 * @return Returns the status code of the execution. See {@link Udmf_ErrCode}.
 *         {@link UDMF_E_OK} success.
 *         {@link UDMF_E_INVALID_PARAM} The error code for common invalid args.
 * @see OH_UdsContentForm Udmf_ErrCode
 * @since 14
 */
int OH_UdsContentForm_SetDescription(OH_UdsContentForm* pThis, const char* description);

/**
 * @brief Set title to the {@link OH_UdsContentForm}.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_UdsContentForm}.
 * @param title Represents a title string.
 * @return Returns the status code of the execution. See {@link Udmf_ErrCode}.
 *         {@link UDMF_E_OK} success.
 *         {@link UDMF_E_INVALID_PARAM} The error code for common invalid args.
 * @see OH_UdsContentForm Udmf_ErrCode
 * @since 14
 */
int OH_UdsContentForm_SetTitle(OH_UdsContentForm* pThis, const char* title);

/**
 * @brief Set thumb data to the {@link OH_UdsContentForm}.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_UdsContentForm}.
 * @param appIcon Represents the app icon.
 * @param len Represents the length of app icon param.
 * @return Returns the status code of the execution. See {@link Udmf_ErrCode}.
 *         {@link UDMF_E_OK} success.
 *         {@link UDMF_E_INVALID_PARAM} The error code for common invalid args.
 * @see OH_UdsContentForm Udmf_ErrCode
 * @since 14
 */
int OH_UdsContentForm_SetAppIcon(OH_UdsContentForm* pThis, const unsigned char* appIcon, unsigned int len);

/**
 * @brief Set app name to the {@link OH_UdsContentForm}.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_UdsContentForm}.
 * @param appName Represents a app name string.
 * @return Returns the status code of the execution. See {@link Udmf_ErrCode}.
 *         {@link UDMF_E_OK} success.
 *         {@link UDMF_E_INVALID_PARAM} The error code for common invalid args.
 * @see OH_UdsContentForm Udmf_ErrCode
 * @since 14
 */
int OH_UdsContentForm_SetAppName(OH_UdsContentForm* pThis, const char* appName);

/**
 * @brief Set link uri to the {@link OH_UdsContentForm}.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_UdsContentForm}.
 * @param linkUri Represents a link uri string.
 * @return Returns the status code of the execution. See {@link Udmf_ErrCode}.
 *         {@link UDMF_E_OK} success.
 *         {@link UDMF_E_INVALID_PARAM} The error code for common invalid args.
 * @see OH_UdsContentForm Udmf_ErrCode
 * @since 14
 */
int OH_UdsContentForm_SetLinkUri(OH_UdsContentForm* pThis, const char* linkUri);

/**
 * @brief Creation a pointer to the instance of the {@link OH_UdsDetails}.
 *
 * @return If the operation is successful, a pointer to the instance of the {@link OH_UdsDetails}
 * structure is returned. If the operation is failed, nullptr is returned.
 * @since 22
 * @see OH_UdsDetails
 */
OH_UdsDetails* OH_UdsDetails_Create();

/**
 * @brief Destroy a pointer that points to the {@link OH_UdsDetails} instance.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_UdsDetails}.
 * @since 22
 * @see OH_UdsDetails
 */
void OH_UdsDetails_Destroy(OH_UdsDetails* pThis);

/**
 * @brief Determine whether the {@link OH_UdsDetails} contain the specified key.
 *
 * @param pThis Represents a pointer to an instance of the {@link OH_UdsDetails}.
 * @param key Represents key in the details.
 * @return Returns the status code of the execution.
 *         {@code false} Represents The details do not contain the key.
 *         {@code true} Represents The details contain the key.
 * @see OH_UdsDetails
 * @since 22
 */
bool OH_UdsDetails_HasKey(const OH_UdsDetails* pThis, const char* key);

/**
 * @brief Remove the value corresponding to this key from the {@link OH_UdsDetails}.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_UdsDetails}.
 * @param key Represents key in the details.
 * @return Returns the status code of the execution. See {@link Udmf_ErrCode}.
 *         {@link UDMF_E_OK} success.
 *         {@link UDMF_E_INVALID_PARAM} The error code for common invalid args.
 * @since 22
 * @see OH_UdsDetails Udmf_ErrCode
 */
int OH_UdsDetails_Remove(OH_UdsDetails* pThis, const char* key);

/**
 * @brief Clear all data in the {@link OH_UdsDetails}.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_UdsDetails}.
 * @return Returns the status code of the execution. See {@link Udmf_ErrCode}.
 *         {@link UDMF_E_OK} success.
 *         {@link UDMF_E_INVALID_PARAM} The error code for common invalid args.
 * @since 22
 * @see OH_UdsDetails Udmf_ErrCode
 */
int OH_UdsDetails_Clear(OH_UdsDetails* pThis);

/**
 * @brief Set key-value data to the {@link OH_UdsDetails}.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_UdsDetails}.
 * @param key Represents the key data to be written.
 * @param value Represents the value data to be written.
 * @return Returns the status code of the execution. See {@link Udmf_ErrCode}.
 *         {@link UDMF_E_OK} success.
 *         {@link UDMF_E_INVALID_PARAM} The error code for common invalid args.
 * @since 22
 * @see OH_UdsDetails Udmf_ErrCode
 */
int OH_UdsDetails_SetValue(OH_UdsDetails* pThis, const char* key, const char* value);

/**
 * @brief Get the value from the {@link OH_UdsDetails} using the key.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_UdsDetails}.
 * @param key Represents key in the details.
 * @return Returns a string pointer when input args normally, otherwise return nullptr.
 * @since 22
 * @see OH_UdsDetails
 */
const char* OH_UdsDetails_GetValue(const OH_UdsDetails* pThis, const char* key);

/**
 * @brief Get the all keys from the {@link OH_UdsDetails}.
 *
 * @param pThis Represents a pointer to an instance of {@link OH_UdsDetails}.
 * @param count Represents the keys count.
 * @return Returns string list of keys. Memory will be released after calling the OH_UdsDetails_Destroy function.
 * @since 22
 * @see OH_UdsDetails
 */
char** OH_UdsDetails_GetAllKeys(OH_UdsDetails* pThis, unsigned int* count);

#ifdef __cplusplus
};
#endif

/** @} */
#endif
