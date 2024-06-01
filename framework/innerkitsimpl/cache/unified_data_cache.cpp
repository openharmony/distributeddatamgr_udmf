/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
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
#define LOG_TAG "UnifiedDataCache"
#include "unified_data_cache.h"
#include "error_code.h"
#include "logger.h"

namespace OHOS {
namespace UDMF {
UnifiedDataCache &UnifiedDataCache::GetInstance()
{
    static auto instance = new UnifiedDataCache();
    return *instance;
}

void UnifiedDataCache::SetUnifiedData(const std::string &key, const UnifiedData &unifiedData)
{
    std::unique_lock<std::shared_mutex> lock(mutex_);
    unifiedDatas.insert({key, unifiedData});
}

Status UnifiedDataCache::GetUnifiedDatas(const std::string &key, UnifiedData &unifiedData)
{
    std::shared_lock<std::shared_mutex> lock(mutex_);
    auto iter = unifiedDatas.find(key);
    if (iter != unifiedDatas.end()) {
        unifiedData = iter->second;
        return E_OK;
    }
    return E_ERROR;
}

void UnifiedDataCache::ClearUnifiedDatas(const std::string &key)
{
    if (unifiedDatas.find(key) != unifiedDatas.end()) {
        std::unique_lock<std::shared_mutex> lock(mutex_);
        unifiedDatas.erase(key);
    }
}
} // namespace UDMF
} // namespace OHOS
