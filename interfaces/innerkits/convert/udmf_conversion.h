/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef UDMF_UDMF_CONVERSION_H
#define UDMF_UDMF_CONVERSION_H

#include "unified_data.h"
#include "visibility.h"

namespace OHOS::UDMF {
class UdmfConversion {
public:
    static void API_EXPORT ConvertRecordToSubclass(std::shared_ptr<UnifiedRecord> &record);
    static void API_EXPORT ConvertRecordToSubclass(UnifiedData &data);
    static void API_EXPORT ConvertRecordToSubclass(std::vector<UnifiedData> &datas);

    static void API_EXPORT InitValueObject(UnifiedData &data);
    static void API_EXPORT InitValueObject(std::vector<UnifiedData> &datas);

private:
    static void SetValueWhenNotUds(std::shared_ptr<UnifiedRecord> record);
};
}

#endif // UDMF_UDMF_CONVERSION_H
