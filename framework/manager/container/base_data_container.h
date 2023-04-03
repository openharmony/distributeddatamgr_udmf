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

#ifndef UDMF_BASE_DATA_CONTAINER_H
#define UDMF_BASE_DATA_CONTAINER_H

#include <mutex>
#include <string>
#include <vector>

#include "error_code.h"
#include "data_mgr_meta.h"
#include "unified_data.h"
#include "unified_record.h"

namespace OHOS {
namespace UDMF {
class BaseDataContainer {
public:
    explicit BaseDataContainer(UDContainerMeta meta);
    virtual ~BaseDataContainer() = default;
    // Insert Unified-Data into container
    virtual int32_t InsertData(UnifiedData &unifiedData) = 0;
    virtual int32_t UpdateData(std::string groupId, UnifiedData &unifiedData) = 0;
    // Query Unified-Data in container
    virtual int32_t GetData(UnifiedData &unifiedData) = 0;
    // Delete Unified-Data
    virtual int32_t DeleteData(const std::vector<std::string> &idList) = 0;
    // Clear container
    virtual int32_t Clear() = 0;

    UDContainerMeta GetMode();

protected:
    std::mutex containerLock_;
    UDContainerMeta containerMeta_;
};
} // namespace UDMF
} // namespace OHOS
#endif //UDMF_BASE_DATA_CONTAINER_H
