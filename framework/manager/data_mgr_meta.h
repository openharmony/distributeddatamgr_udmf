/*
 * Copyright (c) 2023-2023 Huawei Device Co., Ltd.
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

#ifndef UDMF_DATA_MGR_META_H
#define UDMF_DATA_MGR_META_H

#include "unified_types.h"

namespace OHOS {
namespace UDMF {
enum UDStoreType { RUNTIME, PERSISTENT };

/*
 * Mode for inserting data
 */
enum UDContainerMode { OVERWRITE, APPEND };

/*
 * Data Life Cycle Settings
 */
struct UDLifeCycleOption {
    bool useOnlyOnce;
    int64_t timeToLive;
};

struct UDContainerMeta {
    UDContainerMode mode;
    UDLifeCycleOption lifeCycle;
};

struct UDStoreMeta {
    CustomOption option;
    UDStoreType storeType;
    UDContainerMeta containerMeta;
};
} // namespace UDMF
} // namespace OHOS

#endif //UDMF_DATA_MGR_META_H
