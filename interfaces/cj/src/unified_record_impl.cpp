
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

#include "unified_record_ffi.h"
#include "unified_record_impl.h"

#include <cstdlib>
#include <string>
#include <variant>
#include <vector>
#include <map>
#include <iomanip>
#include "ffi_remote_data.h"

#include "plain_text.h"
#include "html.h"
#include "link.h"
#include "image.h"
#include "pixel_map_impl.h"
#include "pixel_map.h"

#include "video.h"
#include "audio.h"
#include "folder.h"
#include "system_defined_appitem.h"
#include "system_defined_form.h"
#include "system_defined_pixelmap.h"
#include "application_defined_record.h"
#include "utils.h"

using namespace OHOS::FFI;
using namespace OHOS::UDMF;

namespace OHOS
{
    namespace UDMF
    {

        static CArrByte VectorToByteArray(std::vector<uint8_t> bytes)
        {
            uint8_t *head = static_cast<uint8_t *>(malloc(bytes.size() * sizeof(uint8_t)));
            if (head == nullptr)
            {
                return CArrByte{};
            }
            for (unsigned long i = 0; i < bytes.size(); i++)
            {
                head[i] = bytes[i];
            }
            CArrByte byteArray = {head, bytes.size()};
            return byteArray;
        }

        CJValueType CUnifiedRecord::ValueType2CJValueType(ValueType value)
        {
            CJValueType cjvalue;
            if (auto p = std::get_if<int32_t>(&value))
            {
                cjvalue.integer32 = *p;
                cjvalue.tag = INTEGER32;
            }
            if (auto p = std::get_if<int64_t>(&value))
            {
                cjvalue.integer64 = *p;
                cjvalue.tag = INTEGER64;
            }
            if (auto p = std::get_if<double>(&value))
            {
                cjvalue.dou = *p;
                cjvalue.tag = DOUBLE;
            }
            if (auto p = std::get_if<bool>(&value))
            {
                cjvalue.boolean = *p;
                cjvalue.tag = BOOLEAN;
            }
            if (auto p = std::get_if<std::string>(&value))
            {
                cjvalue.string = Utils::MallocCString(*p);
                cjvalue.tag = STRING;
            }
            if (auto p = std::get_if<std::vector<uint8_t>>(&value))
            {
                cjvalue.byteArray = VectorToByteArray(*p);
                cjvalue.tag = BYTEARRAY;
            }
            if (auto p = std::get_if<std::shared_ptr<OHOS::Media::PixelMap>>(&value))
            {
                cjvalue.pixelMapId = this->pixelMapId_;
                cjvalue.tag = PIXELMAP;
            }

            return cjvalue;
        }

        ValueType CUnifiedRecord::CJValueType2ValueType(CJValueType cjvalue)
        {
            ValueType value;
            switch (cjvalue.tag)
            {
                case INTEGER32:
                    value = cjvalue.integer32;
                    break;
                case INTEGER64:
                    value = cjvalue.integer64;
                    break;
                case DOUBLE:
                    value = cjvalue.dou;
                    break;
                case BOOLEAN:
                    value = cjvalue.boolean;
                    break;
                case STRING:
                    value = cjvalue.string;
                    break;
                case BYTEARRAY:
                {
                    std::vector<uint8_t> bytes = std::vector<uint8_t>();
                    for (int64_t i = 0; i < cjvalue.byteArray.size; i++)
                    {
                        bytes.push_back(cjvalue.byteArray.head[i]);
                    }
                    value = bytes;
                    break;
                }

                case PIXELMAP:
                    auto instance = FFIData::GetData<OHOS::Media::PixelMapImpl>(cjvalue.pixelMapId);
                    if (instance == nullptr)
                    {
                        value = -1;
                        break;
                    }
                    value = instance->GetRealPixelMap();
                    break;

                default:
                    value = -1;
                    break;
            }

            return value;
        }

        CUnifiedRecord::CUnifiedRecord()
        {
            unifiedRecord_ = std::make_shared<UnifiedRecord>();
        }

        CUnifiedRecord::CUnifiedRecord(const char *type, CJValueType cjvalue)
        {
            UDType utdType = APPLICATION_DEFINED_RECORD;
            if (UtdUtils::IsValidUtdId(type))
            {
                utdType = static_cast<UDType>(UtdUtils::GetUtdEnumFromUtdId(type));
            }

            ValueType value = CJValueType2ValueType(cjvalue);
            if (cjvalue.tag == 6)
            {
                this->pixelMapId_ = cjvalue.pixelMapId;
            }

            std::map<UDType, std::function<std::shared_ptr<UnifiedRecord>(UDType, ValueType)>> constructors = {
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

            auto constructor = constructors.find(utdType);
            if (constructor == constructors.end())
            {
                unifiedRecord_ = std::make_shared<UnifiedRecord>(utdType, value);
                return;
            }

            unifiedRecord_ = constructor->second(utdType, value);
        }

        char *CUnifiedRecord::GetType()
        {
            std::string ret = UtdUtils::GetUtdIdFromUtdEnum(this->unifiedRecord_->GetType());

            return Utils::MallocCString(ret);
        }

        CJValueType CUnifiedRecord::GetValue()
        {
            ValueType value = this->unifiedRecord_->GetValue();
            CJValueType cjvalue = ValueType2CJValueType(value);
            return cjvalue;
        }

        const std::shared_ptr<UDMF::UnifiedRecord> &CUnifiedRecord::GetUnifiedRecord() const
        {
            return unifiedRecord_;
        }

    }
}
