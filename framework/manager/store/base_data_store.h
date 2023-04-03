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

#ifndef UDMF_BASE_DATA_STORE_H
#define UDMF_BASE_DATA_STORE_H

#include <mutex>
#include <string>
#include <vector>

#include "data_mgr_meta.h"
#include "error_code.h"
#include "unified_data.h"
#include "unified_types.h"

namespace OHOS {
namespace UDMF {
/*
 * Interface to define API of manage Unified-Data
 */
class BaseDataStore {
public:
    BaseDataStore() = default;
    virtual ~BaseDataStore() = default;

    virtual int32_t SaveData(CustomOption &option, UnifiedData &unifiedData, std::string &key) = 0;
    virtual int32_t Update(UnifiedKey &key, UnifiedData &unifiedData) = 0;
    virtual int32_t RetrieveData(UnifiedKey &key, UnifiedData &unifiedData) = 0;
    virtual int32_t RetrieveDataAbstract(UnifiedKey &key, Summary &summary) = 0;
    virtual int32_t AddPrivilege(UnifiedKey &key, Privilege &privilege) = 0;
    virtual int32_t Clear(UnifiedKey &key) = 0;
    std::string GetStoreName() const;
    UDStoreType GetStoreType() const;

protected:
    std::mutex storeLock_;
    std::string storeName_;
    UDStoreType storeType_;
};
} // namespace UDMF
} // namespace OHOS
#endif //UDMF_BASE_DATA_STORE_H
