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
#define LOG_TAG "UDMFUnifiedDataModule"
#include "application_defined_record_napi.h"
#include "audio_napi.h"
#include "file_napi.h"
#include "folder_napi.h"
#include "html_napi.h"
#include "image_napi.h"
#include "link_napi.h"
#include "logger.h"
#include "plain_text_napi.h"
#include "unified_data_channel_napi.h"
#include "summary_napi.h"
#include "system_defined_appitem_napi.h"
#include "system_defined_form_napi.h"
#include "system_defined_pixelmap_napi.h"
#include "system_defined_record_napi.h"
#include "text_napi.h"
#include "unified_data_napi.h"
#include "unified_record_napi.h"
#include "video_napi.h"

using namespace OHOS::UDMF;

EXTERN_C_START
static napi_value Init(napi_env env, napi_value exports)
{
    OHOS::UDMF::UnifiedDataChannelNapi::UnifiedDataChannelInit(env, exports);

    napi_status status = napi_ok;
    status = napi_set_named_property(env, exports, "UnifiedDataProperties",
        OHOS::UDMF::UnifiedDataPropertiesNapi::Constructor(env));
    LOG_INFO(UDMF_KITS_NAPI, "init UnifiedDataProperties %{public}d", status);
    status = napi_set_named_property(env, exports, "UnifiedData", OHOS::UDMF::UnifiedDataNapi::Constructor(env));
    LOG_INFO(UDMF_KITS_NAPI, "init UnifiedData %{public}d", status);
    status = napi_set_named_property(env, exports, "Summary", OHOS::UDMF::SummaryNapi::Constructor(env));
    LOG_INFO(UDMF_KITS_NAPI, "init Summary %{public}d", status);
    status = napi_set_named_property(env, exports, "UnifiedRecord", OHOS::UDMF::UnifiedRecordNapi::Constructor(env));
    LOG_INFO(UDMF_KITS_NAPI, "init UnifiedRecord %{public}d", status);
    status = napi_set_named_property(env, exports, "Text", OHOS::UDMF::TextNapi::Constructor(env));
    LOG_INFO(UDMF_KITS_NAPI, "init Text %{public}d", status);
    status = napi_set_named_property(env, exports, "PlainText", OHOS::UDMF::PlainTextNapi::Constructor(env));
    LOG_INFO(UDMF_KITS_NAPI, "init PlainText %{public}d", status);
    status = napi_set_named_property(env, exports, "Hyperlink", OHOS::UDMF::LinkNapi::Constructor(env));
    LOG_INFO(UDMF_KITS_NAPI, "init Hyperlink %{public}d", status);
    status = napi_set_named_property(env, exports, "HTML", OHOS::UDMF::HtmlNapi::Constructor(env));
    LOG_INFO(UDMF_KITS_NAPI, "init HTML %{public}d", status);
    status = napi_set_named_property(env, exports, "File", OHOS::UDMF::FileNapi::Constructor(env));
    LOG_INFO(UDMF_KITS_NAPI, "init File %{public}d", status);
    status = napi_set_named_property(env, exports, "Image", OHOS::UDMF::ImageNapi::Constructor(env));
    LOG_INFO(UDMF_KITS_NAPI, "init Image %{public}d", status);
    status = napi_set_named_property(env, exports, "Video", OHOS::UDMF::VideoNapi::Constructor(env));
    LOG_INFO(UDMF_KITS_NAPI, "init Video %{public}d", status);
    status = napi_set_named_property(env, exports, "Audio", OHOS::UDMF::AudioNapi::Constructor(env));
    LOG_INFO(UDMF_KITS_NAPI, "init Audio %{public}d", status);
    status = napi_set_named_property(env, exports, "Folder", OHOS::UDMF::FolderNapi::Constructor(env));
    LOG_INFO(UDMF_KITS_NAPI, "init Folder %{public}d", status);
    status = napi_set_named_property(
        env, exports, "SystemDefinedRecord", OHOS::UDMF::SystemDefinedRecordNapi::Constructor(env));
    LOG_INFO(UDMF_KITS_NAPI, "init SystemDefinedRecord %{public}d", status);
    status = napi_set_named_property(
        env, exports, "SystemDefinedForm", OHOS::UDMF::SystemDefinedFormNapi::Constructor(env));
    LOG_INFO(UDMF_KITS_NAPI, "init SDForm %{public}d", status);
    status = napi_set_named_property(
        env, exports, "SystemDefinedAppItem", OHOS::UDMF::SystemDefinedAppItemNapi::Constructor(env));
    LOG_INFO(UDMF_KITS_NAPI, "init SDAppItem %{public}d", status);
    status = napi_set_named_property(
        env, exports, "SystemDefinedPixelMap", OHOS::UDMF::SystemDefinedPixelMapNapi::Constructor(env));
    LOG_INFO(UDMF_KITS_NAPI, "init SDPixelMap %{public}d", status);
    status = napi_set_named_property(
        env, exports, "ApplicationDefinedRecord", OHOS::UDMF::ApplicationDefinedRecordNapi::Constructor(env));
    LOG_INFO(UDMF_KITS_NAPI, "init ApplicationDefinedRecord %{public}d", status);
    return exports;
}
EXTERN_C_END

static napi_module _module = { .nm_version = 1,
    .nm_flags = 0,
    .nm_filename = nullptr,
    .nm_register_func = Init,
    .nm_modname = "data.unifiedDataChannel",
    .nm_priv = ((void *)0),
    .reserved = { 0 } };

extern "C" __attribute__((constructor)) void RegisterUDMFUnifiedDataModule(void)
{
    napi_module_register(&_module);
    LOG_INFO(UDMF_KITS_NAPI, "module register data.unifiedDataChannel");
}
