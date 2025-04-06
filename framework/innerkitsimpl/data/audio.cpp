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

#include "audio.h"
#include "unified_meta.h"

namespace OHOS {
namespace UDMF {
Audio::Audio() : Audio("")
{
    SetType(AUDIO);
    utdId2_ = GENERAL_FILE_URI;
}

Audio::Audio(const std::string &uri) : File(uri)
{
    SetType(AUDIO);
    utdId2_ = GENERAL_FILE_URI;
}

Audio::Audio(UDType type, ValueType value) : File(type, value)
{
    SetType(AUDIO);
    utdId2_ = GENERAL_FILE_URI;
}

void Audio::InitObject()
{
    if (!std::holds_alternative<std::shared_ptr<Object>>(value_)) {
        auto value = value_;
        value_ = std::make_shared<Object>();
        auto object = std::get<std::shared_ptr<Object>>(value_);
        object->value_[UNIFORM_DATA_TYPE] = GENERAL_FILE_URI;
        object->value_[ORI_URI] = oriUri_;
        object->value_[REMOTE_URI] = remoteUri_;
        if (!fileType_.empty()) {
            object->value_[FILE_TYPE] = fileType_;
        } else {
            object->value_[FILE_TYPE] = "general.audio";
        }
        object->value_[DETAILS] = ObjectUtils::ConvertToObject(details_);
        object->value_.insert_or_assign(VALUE_TYPE, std::move(value));
    }
}
} // namespace UDMF
} // namespace OHOS