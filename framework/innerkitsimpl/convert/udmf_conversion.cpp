/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "udmf_conversion.h"
#include "unified_data.h"
#include "application_defined_record.h"
#include "audio.h"
#include "file.h"
#include "folder.h"
#include "html.h"
#include "image.h"
#include "link.h"
#include "plain_text.h"
#include "system_defined_appitem.h"
#include "system_defined_form.h"
#include "system_defined_pixelmap.h"
#include "system_defined_record.h"
#include "text.h"
#include "unified_record.h"
#include "video.h"
#include <memory>
#include <utility>

namespace OHOS::UDMF {

void UdmfConversion::SetValueWhenNotUds(std::shared_ptr<UnifiedRecord> record)
{
    if (!std::holds_alternative<std::shared_ptr<Object>>(record->GetValue())) {
        return;
    }
    auto object = std::get<std::shared_ptr<Object>>(record->GetValue());
    auto it = object->value_.find("VALUE_TYPE");
    if (it == object->value_.end()) {
        return;
    }
    if (std::holds_alternative<std::shared_ptr<Object>>(it->second)) {
        return;
    }
    record->SetValue(it->second);
}

void UdmfConversion::ConvertRecordToSubclass(std::shared_ptr<UnifiedRecord> &record)
{
    auto type = record->GetType();
    auto value = record->GetOriginValue();
    auto uid = record->GetUid();
    auto entries = record->GetInnerEntries();
    auto utdId = record->GetUtdId();
    switch (type) {
        case UDType::TEXT: {
            record = std::make_shared<Text>(type, value);
            break;
        }
        case UDType::PLAIN_TEXT: {
            record = std::make_shared<PlainText>(type, value);
            break;
        }
        case UDType::HTML: {
            record = std::make_shared<Html>(type, value);
            break;
        }
        case UDType::HYPERLINK: {
            record = std::make_shared<Link>(type, value);
            break;
        }
        case UDType::FILE: {
            record = std::make_shared<File>(type, value);
            break;
        }
        case UDType::IMAGE: {
            record = std::make_shared<Image>(type, value);
            break;
        }
        case UDType::VIDEO: {
            record = std::make_shared<Video>(type, value);
            break;
        }
        case UDType::AUDIO: {
            record = std::make_shared<Audio>(type, value);
            break;
        }
        case UDType::FOLDER: {
            record = std::make_shared<Folder>(type, value);
            break;
        }
        case UDType::SYSTEM_DEFINED_RECORD: {
            record = std::make_shared<SystemDefinedRecord>(type, value);
            break;
        }
        case UDType::SYSTEM_DEFINED_FORM: {
            record = std::make_shared<SystemDefinedForm>(type, value);
            break;
        }
        case UDType::SYSTEM_DEFINED_APP_ITEM: {
            record = std::make_shared<SystemDefinedAppItem>(type, value);
            break;
        }
        case UDType::SYSTEM_DEFINED_PIXEL_MAP: {
            record = std::make_shared<SystemDefinedPixelMap>(type, value);
            break;
        }
        case UDType::APPLICATION_DEFINED_RECORD: {
            record = std::make_shared<ApplicationDefinedRecord>(type, value);
            break;
        }
        default: {
            record = std::make_shared<UnifiedRecord>(type, value);
        }
    }
    record->SetUid(uid);
    record->SetUtdId(utdId);
    record->SetInnerEntries(entries);
    SetValueWhenNotUds(record);
}

void UdmfConversion::ConvertRecordToSubclass(UnifiedData &data)
{
    std::vector<std::shared_ptr<UnifiedRecord>> records;
    for (auto &record : data.GetRecords()) {
        ConvertRecordToSubclass(record);
        records.push_back(std::move(record));
    }
    data.SetRecords(records);
}

void UdmfConversion::ConvertRecordToSubclass(std::vector<UnifiedData> &datas)
{
    for (auto &data : datas) {
        ConvertRecordToSubclass(data);
    }
}

void UdmfConversion::InitValueObject(UnifiedData &data)
{
    for (auto &record : data.GetRecords()) {
        record->InitObject();
    }
}

void UdmfConversion::InitValueObject(std::vector<UnifiedData> &datas)
{
    for (auto &data : datas) {
        InitValueObject(data);
    }
}
}
