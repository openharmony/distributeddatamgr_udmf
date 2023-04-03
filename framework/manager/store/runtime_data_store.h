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

#ifndef UDMF_RUNTIME_DATA_STORE_H
#define UDMF_RUNTIME_DATA_STORE_H

#include <string>

#include "base_data_store.h"
#include "runtime_data_container.h"

namespace OHOS {
namespace UDMF {
/*
 * Runtime store impl of BaseDataStore
 */
class RuntimeDataStore : public BaseDataStore {
public:
    RuntimeDataStore() = default;
    ~RuntimeDataStore() override = default;

    int32_t SaveData(CustomOption &option, UnifiedData &unifiedData, std::string &key) override;
    int32_t Update(UnifiedKey &key, UnifiedData &unifiedData) override;
    int32_t RetrieveData(UnifiedKey &key, UnifiedData &unifiedData) override;
    int32_t RetrieveDataAbstract(UnifiedKey &key, Summary &summary) override;
    int32_t AddPrivilege(UnifiedKey &key, Privilege &privilege) override;
    int32_t Clear(UnifiedKey &key) override;

private:
    std::shared_ptr<BaseDataContainer> GetContainer(UnifiedKey &key);
    std::map<std::string, std::shared_ptr<BaseDataContainer>> containerMap_;
};
} // namespace UDMF
} // namespace OHOS

#endif // UDMF_RUNTIME_DATA_STORE_H
