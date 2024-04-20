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

#ifndef UDMF_TEXT_H
#define UDMF_TEXT_H

#include "unified_record.h"

namespace OHOS {
namespace UDMF {
constexpr int MAX_TEXT_LEN = 20 * 1024 * 1024;
class Text : public UnifiedRecord {
public:
    Text();
    explicit Text(UDDetails &variantMap);
    Text(UDType type, ValueType value);

    int64_t GetSize() override;

    void SetDetails(UDDetails &variantMap);
    UDDetails GetDetails() const;

protected:
    UDDetails details_;
};
} // namespace UDMF
} // namespace OHOS

#endif // UDMF_TEXT_H
