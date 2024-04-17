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

#ifndef UDMF_LINK_H
#define UDMF_LINK_H

#include "text.h"

namespace OHOS {
namespace UDMF {
class Link : public Text {
public:
    Link();
    explicit Link(const std::string &url);
    explicit Link(const std::string &url, const std::string &description);
    Link(UDType type, ValueType value);

    int64_t GetSize() override;

    std::string GetUrl() const;
    void SetUrl(const std::string &url);
    std::string GetDescription() const;
    void SetDescription(const std::string &description);

private:
    std::string url_;
    std::string description_;
};
} // namespace UDMF
} // namespace OHOS
#endif // UDMF_LINK_H
