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

#include "lifecycle_policy.h"

#include <algorithm>

namespace OHOS {
namespace UDMF {
const LifeCyclePolicy::Duration LifeCyclePolicy::INTERVAL = std::chrono::milliseconds(60 * 60 * 1000);
const std::string LifeCyclePolicy::DATA_PREFIX = "udmf://";

Status LifeCyclePolicy::DeleteOnGet(const UnifiedKey &key)
{
    auto store = storeCache_.GetStore(key.intention);
    if (store == nullptr) {
        LOG_ERROR(UDMF_FRAMEWORK, "Get store failed, intention: %{public}s.", key.intention.c_str());
        return E_DB_ERROR;
    }
    if (store->Delete(key.key) != E_OK) {
        LOG_ERROR(UDMF_FRAMEWORK, "Remove data failed, intention: %{public}s.", key.intention.c_str());
        return E_DB_ERROR;
    }
    return E_OK;
}

Status LifeCyclePolicy::DeleteOnStart(const std::string &intention)
{
    auto store = storeCache_.GetStore(intention);
    if (store == nullptr) {
        LOG_ERROR(UDMF_FRAMEWORK, "Get store failed, intention: %{public}s.", intention.c_str());
        return E_DB_ERROR;
    }
    if (store->Clear() != E_OK) {
        LOG_ERROR(UDMF_FRAMEWORK, "Remove data failed, intention: %{public}s.", intention.c_str());
        return E_DB_ERROR;
    }
    return E_OK;
}

Status LifeCyclePolicy::DeleteOnTimeout(const std::string &intention)
{
    auto store = storeCache_.GetStore(intention);
    if (store == nullptr) {
        LOG_ERROR(UDMF_FRAMEWORK, "Get store failed, intention: %{public}s.", intention.c_str());
        return E_DB_ERROR;
    }
    auto timeoutKeys = GetTimeoutKeys(store, INTERVAL);
    if (store->DeleteBatch(timeoutKeys) != E_OK) {
        LOG_ERROR(UDMF_FRAMEWORK, "Remove data failed, intention: %{public}s.", intention.c_str());
        return E_DB_ERROR;
    }
    return E_OK;
}

std::vector<std::string> LifeCyclePolicy::GetTimeoutKeys(const std::shared_ptr<Store> &store, Duration interval)
{
    std::vector<UnifiedData> datas = store->GetDatas(DATA_PREFIX);
    std::vector<std::string> timeoutKeys;
    if (datas.empty()) {
        LOG_INFO(UDMF_FRAMEWORK, "entries is empty.");
        return timeoutKeys;
    }
    auto curTime = PreProcessUtils::GetInstance().GetTimeStamp();
    for (const auto &data : datas) {
        if (curTime > data.GetRuntime()->createTime
                          + std::chrono::duration_cast<std::chrono::milliseconds>(interval).count()) {
            timeoutKeys.push_back(data.GetRuntime()->key.key);
        }
    }
    return timeoutKeys;
}
} // namespace UDMF
} // namespace OHOS