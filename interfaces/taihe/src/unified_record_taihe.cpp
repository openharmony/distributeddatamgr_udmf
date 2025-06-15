/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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
#include "unified_record_taihe.h"
#include "taihe/runtime.hpp"
#include "ani_common_want.h"
#include "pixel_map_taihe_ani.h"
#include "taihe_common_utils.h"
#include "plain_text.h"
#include "html.h"
#include "link.h"
#include "image.h"
#include "video.h"
#include "audio.h"
#include "folder.h"
#include "system_defined_appitem.h"
#include "system_defined_form.h"
#include "system_defined_pixelmap.h"
#include "application_defined_record.h"

UnifiedRecordInnerImpl::UnifiedRecordInnerImpl()
{
    this->value_ = std::make_shared<taiheUdmf::UnifiedRecord>();
}

UnifiedRecordInnerImpl::UnifiedRecordInnerImpl(::taihe::string_view type,
    ::ohos::data::unifiedDataChannel::ValueType const& value)
{
    taiheUdmf::ValueType valueType = taiheUdmf::ConvertValueType(::taihe::get_env(), type, value);
    taiheUdmf::UDType utdType = taiheUdmf::APPLICATION_DEFINED_RECORD;
    if (taiheUdmf::UtdUtils::IsValidUtdId(std::string(type))) {
        utdType = static_cast<taiheUdmf::UDType>(taiheUdmf::UtdUtils::GetUtdEnumFromUtdId(std::string(type)));
    }
    std::map<taiheUdmf::UDType, std::function<std::shared_ptr<taiheUdmf::UnifiedRecord>(
        taiheUdmf::UDType, taiheUdmf::ValueType)>> constructors = {
        {taiheUdmf::TEXT, [](taiheUdmf::UDType type, taiheUdmf::ValueType value)
            { return std::make_shared<taiheUdmf::Text>(type, value); }},
        {taiheUdmf::PLAIN_TEXT, [](taiheUdmf::UDType type, taiheUdmf::ValueType value)
            { return std::make_shared<taiheUdmf::PlainText>(type, value); }},
        {taiheUdmf::HTML, [](taiheUdmf::UDType type, taiheUdmf::ValueType value)
            { return std::make_shared<taiheUdmf::Html>(type, value); }},
        {taiheUdmf::HYPERLINK, [](taiheUdmf::UDType type, taiheUdmf::ValueType value)
            { return std::make_shared<taiheUdmf::Link>(type, value); }},
        {taiheUdmf::FILE, [](taiheUdmf::UDType type, taiheUdmf::ValueType value)
            { return std::make_shared<taiheUdmf::File>(type, value); }},
        {taiheUdmf::IMAGE, [](taiheUdmf::UDType type, taiheUdmf::ValueType value)
            { return std::make_shared<taiheUdmf::Image>(type, value); }},
        {taiheUdmf::VIDEO, [](taiheUdmf::UDType type, taiheUdmf::ValueType value)
            { return std::make_shared<taiheUdmf::Video>(type, value); }},
        {taiheUdmf::AUDIO, [](taiheUdmf::UDType type, taiheUdmf::ValueType value)
            { return std::make_shared<taiheUdmf::Audio>(type, value); }},
        {taiheUdmf::FOLDER, [](taiheUdmf::UDType type, taiheUdmf::ValueType value)
            { return std::make_shared<taiheUdmf::Folder>(type, value); }},
        {taiheUdmf::SYSTEM_DEFINED_RECORD,
            [](taiheUdmf::UDType type, taiheUdmf::ValueType value)
            { return std::make_shared<taiheUdmf::SystemDefinedRecord>(type, value); }},
        {taiheUdmf::SYSTEM_DEFINED_APP_ITEM,
            [](taiheUdmf::UDType type, taiheUdmf::ValueType value)
            { return std::make_shared<taiheUdmf::SystemDefinedAppItem>(type, value); }},
        {taiheUdmf::SYSTEM_DEFINED_FORM,
            [](taiheUdmf::UDType type, taiheUdmf::ValueType value)
            { return std::make_shared<taiheUdmf::SystemDefinedForm>(type, value); }},
        {taiheUdmf::SYSTEM_DEFINED_PIXEL_MAP,
            [](taiheUdmf::UDType type, taiheUdmf::ValueType value)
            { return std::make_shared<taiheUdmf::SystemDefinedPixelMap>(type, value); }},
        {taiheUdmf::APPLICATION_DEFINED_RECORD,
            [](taiheUdmf::UDType type, taiheUdmf::ValueType value)
            { return std::make_shared<taiheUdmf::ApplicationDefinedRecord>(type, value); }},
    };
    if (utdType == taiheUdmf::FILE_URI && std::holds_alternative<std::shared_ptr<taiheUdmf::Object>>(valueType)) {
        taiheUdmf::ObjectUtils::ProcessFileUriType(utdType, valueType);
    }
    auto constructor = constructors.find(utdType);
    if (constructor == constructors.end()) {
        this->value_ = std::make_shared<taiheUdmf::UnifiedRecord>(utdType, valueType);
        return;
    }
    auto uRecord = constructor->second(utdType, valueType);
    if (utdType == taiheUdmf::APPLICATION_DEFINED_RECORD) {
        std::shared_ptr<taiheUdmf::ApplicationDefinedRecord> applicationDefinedRecord =
            std::static_pointer_cast<taiheUdmf::ApplicationDefinedRecord>(uRecord);
        applicationDefinedRecord->SetApplicationDefinedType(std::string(type));
    }
    this->value_ = uRecord;
}

::taihe::string UnifiedRecordInnerImpl::GetType()
{
    return ::taihe::string(taiheUdmf::UtdUtils::GetUtdIdFromUtdEnum(this->value_->GetType()));
}

::ohos::data::unifiedDataChannel::ValueType UnifiedRecordInnerImpl::GetValue()
{
    return taiheUdmf::ConvertValueType(this->value_->GetValue());
}

int64_t UnifiedRecordInnerImpl::GetInner()
{
    return reinterpret_cast<int64_t>(this);
}

::ohos::data::unifiedDataChannel::UnifiedRecordInner CreateUnifiedRecord()
{
    return taihe::make_holder<UnifiedRecordInnerImpl, ::ohos::data::unifiedDataChannel::UnifiedRecordInner>();
}

::ohos::data::unifiedDataChannel::UnifiedRecordInner CreateUnifiedRecordWithParams(::taihe::string_view type,
    ::ohos::data::unifiedDataChannel::ValueType const& value)
{
    return taihe::make_holder<UnifiedRecordInnerImpl,
        ::ohos::data::unifiedDataChannel::UnifiedRecordInner>(type, value);
}

TH_EXPORT_CPP_API_CreateUnifiedRecord(CreateUnifiedRecord);
TH_EXPORT_CPP_API_CreateUnifiedRecordWithParams(CreateUnifiedRecordWithParams);