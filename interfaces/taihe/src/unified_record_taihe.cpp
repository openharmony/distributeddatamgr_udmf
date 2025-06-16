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
namespace OHOS {
namespace UDMF {
UnifiedRecordInnerImpl::UnifiedRecordInnerImpl()
{
    this->value_ = std::make_shared<UnifiedRecord>();
}

UnifiedRecordInnerImpl::UnifiedRecordInnerImpl(::taihe::string_view type,
    ::taiheChannel::ValueType const& value)
{
    ValueType valueType = ConvertValueType(::taihe::get_env(), type, value);
    UDType utdType = APPLICATION_DEFINED_RECORD;
    if (UtdUtils::IsValidUtdId(std::string(type))) {
        utdType = static_cast<UDType>(UtdUtils::GetUtdEnumFromUtdId(std::string(type)));
    }
    std::map<UDType, std::function<std::shared_ptr<UnifiedRecord>(
        UDType, ValueType)>> constructors = {
        {TEXT, [](UDType type, ValueType value)
            { return std::make_shared<Text>(type, value); }},
        {PLAIN_TEXT, [](UDType type, ValueType value)
            { return std::make_shared<PlainText>(type, value); }},
        {HTML, [](UDType type, ValueType value)
            { return std::make_shared<Html>(type, value); }},
        {HYPERLINK, [](UDType type, ValueType value)
            { return std::make_shared<Link>(type, value); }},
        {FILE, [](UDType type, ValueType value)
            { return std::make_shared<File>(type, value); }},
        {IMAGE, [](UDType type, ValueType value)
            { return std::make_shared<Image>(type, value); }},
        {VIDEO, [](UDType type, ValueType value)
            { return std::make_shared<Video>(type, value); }},
        {AUDIO, [](UDType type, ValueType value)
            { return std::make_shared<Audio>(type, value); }},
        {FOLDER, [](UDType type, ValueType value)
            { return std::make_shared<Folder>(type, value); }},
        {SYSTEM_DEFINED_RECORD,
            [](UDType type, ValueType value)
            { return std::make_shared<SystemDefinedRecord>(type, value); }},
        {SYSTEM_DEFINED_APP_ITEM,
            [](UDType type, ValueType value)
            { return std::make_shared<SystemDefinedAppItem>(type, value); }},
        {SYSTEM_DEFINED_FORM,
            [](UDType type, ValueType value)
            { return std::make_shared<SystemDefinedForm>(type, value); }},
        {SYSTEM_DEFINED_PIXEL_MAP,
            [](UDType type, ValueType value)
            { return std::make_shared<SystemDefinedPixelMap>(type, value); }},
        {APPLICATION_DEFINED_RECORD,
            [](UDType type, ValueType value)
            { return std::make_shared<ApplicationDefinedRecord>(type, value); }},
    };
    if (utdType == FILE_URI && std::holds_alternative<std::shared_ptr<Object>>(valueType)) {
        ObjectUtils::ProcessFileUriType(utdType, valueType);
    }
    auto constructor = constructors.find(utdType);
    if (constructor == constructors.end()) {
        this->value_ = std::make_shared<UnifiedRecord>(utdType, valueType);
        return;
    }
    auto uRecord = constructor->second(utdType, valueType);
    if (utdType == APPLICATION_DEFINED_RECORD) {
        std::shared_ptr<ApplicationDefinedRecord> applicationDefinedRecord =
            std::static_pointer_cast<ApplicationDefinedRecord>(uRecord);
        applicationDefinedRecord->SetApplicationDefinedType(std::string(type));
    }
    this->value_ = uRecord;
}

::taihe::string UnifiedRecordInnerImpl::GetType()
{
    return ::taihe::string(UtdUtils::GetUtdIdFromUtdEnum(this->value_->GetType()));
}

::taiheChannel::ValueType UnifiedRecordInnerImpl::GetValue()
{
    return ConvertValueType(this->value_->GetValue());
}

int64_t UnifiedRecordInnerImpl::GetInner()
{
    return reinterpret_cast<int64_t>(this);
}

} // namespace UDMF
} // namespace OHOS

::taiheChannel::UnifiedRecordInner CreateUnifiedRecord()
{
    return taihe::make_holder<OHOS::UDMF::UnifiedRecordInnerImpl, ::taiheChannel::UnifiedRecordInner>();
}

::taiheChannel::UnifiedRecordInner CreateUnifiedRecordWithParams(::taihe::string_view type,
    ::taiheChannel::ValueType const& value)
{
    return taihe::make_holder<OHOS::UDMF::UnifiedRecordInnerImpl,
        ::taiheChannel::UnifiedRecordInner>(type, value);
}

TH_EXPORT_CPP_API_CreateUnifiedRecord(CreateUnifiedRecord);
TH_EXPORT_CPP_API_CreateUnifiedRecordWithParams(CreateUnifiedRecordWithParams);