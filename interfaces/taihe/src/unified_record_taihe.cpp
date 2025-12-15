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

#define LOG_TAG "UDMF_TAIHE_UNIFIEDRECORD"

#include "ani_common_want.h"
#include "application_defined_record.h"
#include "audio.h"
#include "folder.h"
#include "html.h"
#include "image.h"
#include "link.h"
#include "logger.h"
#include "pixel_map_taihe_ani.h"
#include "plain_text.h"
#include "system_defined_appitem.h"
#include "system_defined_form.h"
#include "system_defined_pixelmap.h"
#include "taihe_common_utils.h"
#include "taihe/runtime.hpp"
#include "unified_record_taihe.h"
#include "video.h"

namespace OHOS {
namespace UDMF {
UnifiedRecordTaihe::UnifiedRecordTaihe()
{
    this->value_ = std::make_shared<UnifiedRecord>();
}

std::shared_ptr<UnifiedRecord> UnifiedRecordTaihe::GenerateNativeRecord(const ::taihe::string_view &type,
    ::taiheChannel::ValueType const& value)
{
    ValueType valueType = ConvertValueType(::taihe::get_env(), type, value);
    UDType utdType = APPLICATION_DEFINED_RECORD;
    if (UtdUtils::IsValidUtdId(std::string(type))) {
        utdType = static_cast<UDType>(UtdUtils::GetUtdEnumFromUtdId(std::string(type)));
    }
    std::map<UDType, std::function<std::shared_ptr<UnifiedRecord>(
        UDType, ValueType)>> constructors = {
        {TEXT, [](UDType type, ValueType value) { return std::make_shared<Text>(type, value); }},
        {PLAIN_TEXT, [](UDType type, ValueType value) { return std::make_shared<PlainText>(type, value); }},
        {HTML, [](UDType type, ValueType value) { return std::make_shared<Html>(type, value); }},
        {HYPERLINK, [](UDType type, ValueType value) { return std::make_shared<Link>(type, value); }},
        {FILE, [](UDType type, ValueType value) { return std::make_shared<File>(type, value); }},
        {IMAGE, [](UDType type, ValueType value) { return std::make_shared<Image>(type, value); }},
        {VIDEO, [](UDType type, ValueType value) { return std::make_shared<Video>(type, value); }},
        {AUDIO, [](UDType type, ValueType value) { return std::make_shared<Audio>(type, value); }},
        {FOLDER, [](UDType type, ValueType value) { return std::make_shared<Folder>(type, value); }},
        {SYSTEM_DEFINED_RECORD, [](UDType type, ValueType value)
            { return std::make_shared<SystemDefinedRecord>(type, value); }},
        {SYSTEM_DEFINED_APP_ITEM, [](UDType type, ValueType value)
            { return std::make_shared<SystemDefinedAppItem>(type, value); }},
        {SYSTEM_DEFINED_FORM, [](UDType type, ValueType value)
            { return std::make_shared<SystemDefinedForm>(type, value); }},
        {SYSTEM_DEFINED_PIXEL_MAP, [](UDType type, ValueType value)
            { return std::make_shared<SystemDefinedPixelMap>(type, value); }},
        {APPLICATION_DEFINED_RECORD, [](UDType type, ValueType value)
            { return std::make_shared<ApplicationDefinedRecord>(type, value); }},
    };
    if (utdType == FILE_URI && std::holds_alternative<std::shared_ptr<Object>>(valueType)) {
        ObjectUtils::ProcessFileUriType(utdType, valueType);
    }
    auto constructor = constructors.find(utdType);
    if (constructor == constructors.end()) {
        this->value_ = std::make_shared<UnifiedRecord>(utdType, valueType);
        return this->value_;
    }
    auto uRecord = constructor->second(utdType, valueType);
    if (utdType == APPLICATION_DEFINED_RECORD) {
        std::shared_ptr<ApplicationDefinedRecord> applicationDefinedRecord =
            std::static_pointer_cast<ApplicationDefinedRecord>(uRecord);
        applicationDefinedRecord->SetApplicationDefinedType(std::string(type));
    }
    return uRecord;
}

UnifiedRecordTaihe::UnifiedRecordTaihe(const ::taihe::string_view &type,
    ::taiheChannel::ValueType const& value)
{
    this->value_ = GenerateNativeRecord(type, value);
}

::taihe::string UnifiedRecordTaihe::GetType()
{
    return ::taihe::string(UtdUtils::GetUtdIdFromUtdEnum(this->value_->GetType()));
}

::taiheChannel::ValueType UnifiedRecordTaihe::GetValue()
{
    return ConvertValueType(this->value_->GetValue());
}

int64_t UnifiedRecordTaihe::GetInner()
{
    return reinterpret_cast<int64_t>(this);
}

::taihe::array<::taihe::string> UnifiedRecordTaihe::GetTypes()
{
    std::vector<std::string> res;
    if (!this->value_) {
        LOG_ERROR(UDMF_ANI, "Inner value is null.");
        taihe::set_business_error(PARAMETERSERROR, "invalid object!");
        return ::taihe::array<::taihe::string>(taihe::copy_data_t{}, res.data(), res.size());
    }
    res = this->value_->GetTypes();
    return ::taihe::array<::taihe::string>(taihe::copy_data_t{}, res.data(), res.size());
}

void UnifiedRecordTaihe::AddEntry(::taihe::string_view type, ::taiheChannel::ValueType value)
{
    if (type.empty()) {
        LOG_ERROR(UDMF_ANI, "Inner value is empty.");
        taihe::set_business_error(PARAMETERSERROR, "Parameter error: parameter type must be string");
        return;
    }

    if (!this->value_) {
        LOG_ERROR(UDMF_ANI, "Inner value is null.");
        taihe::set_business_error(PARAMETERSERROR, "invalid object!");
        return;
    }
    ValueType valueType = ConvertValueType(::taihe::get_env(), type, value);

    if (this->value_->GetType() == UD_BUTT) {
        this->value_ = GenerateNativeRecord(type, value);
        if (!this->value_) {
            taihe::set_business_error(PARAMETERSERROR, "Parameter error: unsupported type");
            return;
        }
    } else {
        this->value_->AddEntry(std::string(type), std::move(valueType));
    }
    return;
}

::taiheChannel::ValueType UnifiedRecordTaihe::GetEntry(::taihe::string_view type)
{
    if (!this->value_) {
        LOG_ERROR(UDMF_ANI, "Inner value is null.");
        taihe::set_business_error(PARAMETERSERROR, "invalid object!");
        return ::taiheChannel::ValueType::make_nullType();
    }
    return ConvertValueType(this->value_->GetEntry(std::string(type)));
}

::taihe::map<::taihe::string, ::taiheChannel::ValueType> UnifiedRecordTaihe::GetEntries()
{
    ::taihe::map<::taihe::string, ::taiheChannel::ValueType> res;
    if (!this->value_) {
        LOG_ERROR(UDMF_ANI, "Inner value is null.");
        taihe::set_business_error(PARAMETERSERROR, "invalid object!");
        return res;
    }
    auto entries = this->value_->GetEntries();
    if (!entries) {
        LOG_ERROR(UDMF_ANI, "entries value is null.");
        return res;
    }
    for (auto &entry : *entries) {
        res.emplace(::taihe::string(entry.first), ConvertValueType(entry.second));
    }
    return res;
}

} // namespace UDMF
} // namespace OHOS

::taiheChannel::UnifiedRecordInner CreateUnifiedRecord()
{
    return taihe::make_holder<OHOS::UDMF::UnifiedRecordTaihe, ::taiheChannel::UnifiedRecordInner>();
}

::taiheChannel::UnifiedRecordInner CreateUnifiedRecordWithParams(::taihe::string_view type,
    ::taiheChannel::ValueType const& value)
{
    return taihe::make_holder<OHOS::UDMF::UnifiedRecordTaihe,
        ::taiheChannel::UnifiedRecordInner>(type, value);
}

TH_EXPORT_CPP_API_CreateUnifiedRecord(CreateUnifiedRecord);
TH_EXPORT_CPP_API_CreateUnifiedRecordWithParams(CreateUnifiedRecordWithParams);