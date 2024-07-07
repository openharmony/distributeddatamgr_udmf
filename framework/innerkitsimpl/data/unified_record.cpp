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
#define LOG_TAG "UnifiedRecord"
#include "unified_record.h"

#include "logger.h"

namespace OHOS {
namespace UDMF {
UnifiedRecord::UnifiedRecord()
{
    dataType_ = UD_BUTT;
}

UnifiedRecord::UnifiedRecord(UDType type)
{
    dataType_ = type;
}

UnifiedRecord::UnifiedRecord(UDType type, ValueType value)
{
    dataType_ = type;
    value_ = value;
}

UDType UnifiedRecord::GetType() const
{
    return this->dataType_;
}

void UnifiedRecord::SetType(const UDType &type)
{
    this->dataType_ = type;
}

int64_t UnifiedRecord::GetSize()
{
    return 0;
}

std::string UnifiedRecord::GetUid() const
{
    return this->uid_;
}

void UnifiedRecord::SetUid(const std::string &id)
{
    this->uid_ = id;
}

ValueType UnifiedRecord::GetValue()
{
    return value_;
}

void UnifiedRecord::SetValue(const ValueType &value)
{
    value_ = value;
}
} // namespace UDMF
} // namespace OHOS