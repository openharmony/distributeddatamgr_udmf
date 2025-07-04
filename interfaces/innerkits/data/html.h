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

#ifndef UDMF_HTML_H
#define UDMF_HTML_H

#include "text.h"
#include "visibility.h"

namespace OHOS {
namespace UDMF {
class Html : public Text {
public:
    API_EXPORT Html();
    explicit API_EXPORT Html(const std::string &htmlContent, const std::string &plainContent);
    API_EXPORT Html(UDType type, ValueType value);

    int64_t API_EXPORT GetSize() override;

    std::string API_EXPORT GetHtmlContent() const;
    void API_EXPORT SetHtmlContent(const std::string &htmlContent);
    std::string API_EXPORT GetPlainContent() const;
    void API_EXPORT SetPlainContent(const std::string &htmlContent);
    void InitObject() override;

private:
    std::string htmlContent_;
    std::string plainContent_;
};
} // namespace UDMF
} // namespace OHOS

#endif // UDMF_HTML_H
