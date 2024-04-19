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

#include "file.h"

namespace OHOS {
namespace UDMF {
File::File() : UnifiedRecord(FILE)
{
}

File::File(const std::string &uri) : UnifiedRecord(FILE)
{
    this->oriUri_ = uri;
}

File::File(UDType type, ValueType value) : UnifiedRecord(type, value)
{
    if (std::holds_alternative<std::string>(value)) {
        oriUri_ = std::get<std::string>(value);
    }
}

int64_t File::GetSize()
{
    return this->oriUri_.size() + this->remoteUri_.size();
}

std::string File::GetUri() const
{
    return this->oriUri_;
}

void File::SetUri(const std::string &uri)
{
    this->oriUri_ = uri;
}

std::string File::GetRemoteUri() const
{
    return this->remoteUri_;
}

void File::SetRemoteUri(const std::string &uri)
{
    this->remoteUri_ = uri;
}

void File::SetDetails(UDDetails &variantMap)
{
    this->details_ = variantMap;
}

UDDetails File::GetDetails() const
{
    return this->details_;
}
} // namespace UDMF
} // namespace OHOS
