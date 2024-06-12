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
#ifndef UDMF_UNIFIED_DATA_PROPERTIES_H
#define UDMF_UNIFIED_DATA_PROPERTIES_H

#include "want_params.h"
#include "unified_meta.h"
namespace OHOS {
namespace UDMF {
class UnifiedDataProperties {
public:
    std::string tag;
    AAFwk::WantParams extras;
    ShareOptions shareOptions = CROSS_APP;
    std::int64_t timestamp;
};
} // namespace UDMF
} // namespace OHOS
#endif // UDMF_UNIFIED_DATA_PROPERTIES_H