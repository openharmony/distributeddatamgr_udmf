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
#include "visibility.h"

namespace OHOS {
namespace UDMF {
class Link : public Text {
public:
    API_EXPORT Link();
    explicit API_EXPORT Link(const std::string &url);
    explicit API_EXPORT Link(const std::string &url, const std::string &description);
    API_EXPORT Link(UDType type, ValueType value);

    int64_t API_EXPORT GetSize() override;

    std::string API_EXPORT GetUrl() const;
    void API_EXPORT SetUrl(const std::string &url);
    std::string API_EXPORT GetDescription() const;
    void API_EXPORT SetDescription(const std::string &description);
    void InitObject() override;

private:
    std::string url_;
    std::string description_;
};
} // namespace UDMF
} // namespace OHOS
#endif // UDMF_LINK_H
