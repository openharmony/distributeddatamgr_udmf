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

#ifndef UNIFIED_DATA_CACHE_H
#define UNIFIED_DATA_CACHE_H

#include <string>
#include <vector>
#include <map>
#include <shared_mutex>

#include "unified_data.h"
#include "error_code.h"
#include "visibility.h"
namespace OHOS {
namespace UDMF {
class API_EXPORT UnifiedDataCache {
public:
    static UnifiedDataCache &GetInstance();
    void SetUnifiedData(const std::string &key, const UnifiedData &unifiedData);
    Status GetUnifiedDatas(const std::string &key, UnifiedData &unifiedData);
    void ClearUnifiedDatas(const std::string &key);
private:
    UnifiedDataCache() = default;
    ~UnifiedDataCache() = default;
    UnifiedDataCache(const UnifiedDataCache &obj) = delete;
    UnifiedDataCache &operator=(const UnifiedDataCache &obj) = delete;

    mutable std::shared_mutex mutex_ {};
    std::map<std::string, UnifiedData> unifiedDatas;
};
} // namespace UDMF
} // namespace OHOS
#endif // UNIFIED_DATA_CACHE_H