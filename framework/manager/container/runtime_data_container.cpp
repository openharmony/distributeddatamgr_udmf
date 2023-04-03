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

#include "runtime_data_container.h"

namespace OHOS {
namespace UDMF {
RuntimeDataContainer::RuntimeDataContainer(UDContainerMeta meta) : BaseDataContainer(meta)
{
}

int32_t RuntimeDataContainer::InsertData(UnifiedData &unifiedData)
{
    std::lock_guard<decltype(containerLock_)> lock(containerLock_);
    if (containerMeta_.mode == OVERWRITE) {
        container_ = std::make_shared<UnifiedData>(unifiedData);
    }
    return E_OK;
}

int32_t RuntimeDataContainer::UpdateData(std::string groupId, UnifiedData &unifiedData)
{
    std::lock_guard<decltype(containerLock_)> lock(containerLock_);
    if (container_ == nullptr || container_->GetGroupId() != groupId) {
        return E_INVALID_OPERATION;
    }
    unifiedData.SetRuntime(*container_->GetRuntime());
    container_ = std::make_shared<UnifiedData>(unifiedData);
    return E_OK;
}

int32_t RuntimeDataContainer::GetData(UnifiedData &unifiedData)
{
    std::lock_guard<decltype(containerLock_)> lock(containerLock_);
    if (container_ == nullptr) {
        return E_ERROR;
    }
    unifiedData = *container_;
    return E_OK;
}

int32_t RuntimeDataContainer::DeleteData(const std::vector<std::string> &idList)
{
    return E_OK;
}

int32_t RuntimeDataContainer::Clear()
{
    container_ = nullptr;
    return E_OK;
}
} // namespace UDMF
} // namespace OHOS
