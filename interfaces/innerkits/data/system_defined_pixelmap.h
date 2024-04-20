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

#ifndef UDMF_SYSTEM_DEFINED_PIXELMAP_H
#define UDMF_SYSTEM_DEFINED_PIXELMAP_H

#include "system_defined_record.h"

namespace OHOS {
namespace UDMF {
class SystemDefinedPixelMap : public SystemDefinedRecord {
public:
    SystemDefinedPixelMap();
    explicit SystemDefinedPixelMap(std::vector<uint8_t> &data);
    SystemDefinedPixelMap(UDType type, ValueType value);

    int64_t GetSize() override;

    std::vector<uint8_t> GetRawData() const;
    void SetRawData(const std::vector<uint8_t> &rawData);
private:
    std::vector<uint8_t> rawData_;
};
} // namespace UDMF
} // namespace OHOS
#endif // UDMF_SYSTEM_DEFINED_PIXELMAP_H
