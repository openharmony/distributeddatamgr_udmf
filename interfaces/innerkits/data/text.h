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
#include "visibility.h"
namespace OHOS {
namespace UDMF {
constexpr int MAX_TEXT_LEN = 20 * 1024 * 1024;
class Text : public UnifiedRecord {
public:
    API_EXPORT Text();
    explicit API_EXPORT Text(UDDetails &variantMap);
    API_EXPORT Text(UDType type, ValueType value);

    int64_t API_EXPORT GetSize() override;

    void API_EXPORT SetDetails(UDDetails &variantMap);
    UDDetails API_EXPORT GetDetails() const;

    void InitObject() override;

protected:
    UDDetails details_;
};
} // namespace UDMF
} // namespace OHOS

#endif // UDMF_TEXT_H
