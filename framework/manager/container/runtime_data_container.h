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

#ifndef UDMF_RUNTIME_DATA_CONTAINER_H
#define UDMF_RUNTIME_DATA_CONTAINER_H

#include "base_data_container.h"

namespace OHOS {
namespace UDMF {
class RuntimeDataContainer : public BaseDataContainer {
public:
    explicit RuntimeDataContainer(UDContainerMeta meta);
    ~RuntimeDataContainer() override = default;

    int32_t InsertData(UnifiedData &unifiedData) override;
    int32_t UpdateData(std::string groupId, UnifiedData &unifiedData) override;
    int32_t GetData(UnifiedData &unifiedData) override;
    int32_t Clear() override;
    int32_t DeleteData(const std::vector<std::string> &idList) override;

private:
    std::shared_ptr<UnifiedData> container_;
};
} // namespace UDMF
} // namespace OHOS
#endif //UDMF_RUNTIME_DATA_CONTAINER_H
