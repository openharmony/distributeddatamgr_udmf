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
#include "system_defined_pixelmap.h"

namespace OHOS {
namespace UDMF {

SystemDefinedPixelMap::SystemDefinedPixelMap()
{
}

SystemDefinedPixelMap::SystemDefinedPixelMap(std::vector<uint8_t> &data)
{
}

SystemDefinedPixelMap::SystemDefinedPixelMap(UDType type, ValueType value) : SystemDefinedRecord(type, value)
{
}

int64_t SystemDefinedPixelMap::GetSize()
{
    return 0;
}

std::vector<uint8_t> SystemDefinedPixelMap::GetRawData() const
{
    return this->rawData_;
}

void SystemDefinedPixelMap::SetRawData(const std::vector<uint8_t> &rawData)
{
}

ValueType SystemDefinedPixelMap::GetValue()
{
    value_ = std::make_shared<Object>();
    return value_;
}

void SystemDefinedPixelMap::InitObject()
{
}

} // namespace UDMF
} // namespace OHOS