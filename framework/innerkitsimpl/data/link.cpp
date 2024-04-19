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

#include "link.h"

namespace OHOS {
namespace UDMF {
Link::Link() : Link("", "")
{
}

Link::Link(const std::string &url) : Link(url, "")
{
}

Link::Link(UDType type, ValueType value) : Text(type, value)
{
    if (std::holds_alternative<std::string>(value)) {
        url_ = std::get<std::string>(value);
    }
}

Link::Link(const std::string &url, const std::string &description)
{
    if (url.length() >= MAX_TEXT_LEN || description.length() >= MAX_TEXT_LEN) {
        return;
    }
    this->dataType_ = HYPERLINK;
    this->url_ = url;
    this->description_ = description;
}

int64_t Link::GetSize()
{
    return UnifiedDataUtils::GetDetailsSize(this->details_) + this->url_.size() + this->description_.size();
}

std::string Link::GetUrl() const
{
    return this->url_;
}

void Link::SetUrl(const std::string &url)
{
    if (url.length() >= MAX_TEXT_LEN) {
        return;
    }
    this->url_ = url;
}

std::string Link::GetDescription() const
{
    return this->description_;
}

void Link::SetDescription(const std::string &description)
{
    if (description.length() >= MAX_TEXT_LEN) {
        return;
    }
    this->description_ = description;
}
} // namespace UDMF
} // namespace OHOS