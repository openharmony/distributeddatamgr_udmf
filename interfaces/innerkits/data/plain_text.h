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

#ifndef UDMF_PLAIN_TEXT_H
#define UDMF_PLAIN_TEXT_H

#include "text.h"

namespace OHOS {
namespace UDMF {
class PlainText : public Text {
public:
    PlainText();
    explicit PlainText(const std::string &content, const std::string &abstract);
    PlainText(UDType type, ValueType value);

    int64_t GetSize() override;

    std::string GetContent() const;
    void SetContent(const std::string &content);
    std::string GetAbstract() const;
    void SetAbstract(const std::string &abstract);

private:
    std::string content_;
    std::string abstract_;
};
} // namespace UDMF
} // namespace OHOS

#endif // UDMF_PLAIN_TEXT_H
