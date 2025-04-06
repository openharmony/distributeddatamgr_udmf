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

#include "video.h"

namespace OHOS {
namespace UDMF {
Video::Video() : Video("")
{
    SetType(VIDEO);
    utdId2_ = GENERAL_FILE_URI;
}

Video::Video(const std::string &uri) : File(uri)
{
    SetType(VIDEO);
    utdId2_ = GENERAL_FILE_URI;
}

Video::Video(UDType type, ValueType value) : File(type, value)
{
    SetType(VIDEO);
    utdId2_ = GENERAL_FILE_URI;
}

void Video::InitObject()
{
    File::InitObject();
    auto object = std::get<std::shared_ptr<Object>>(value_);
    if (!fileType_.empty()) {
        object->value_[FILE_TYPE] = fileType_;
    } else {
        object->value_[FILE_TYPE] = "general.video";
    }
}
} // namespace UDMF
} // namespace OHOS