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

#ifndef UDMF_RUNTIMESTORE_H
#define UDMF_RUNTIMESTORE_H

#include "distributed_kv_data_manager.h"
#include "single_kvstore.h"
#include "store.h"

namespace OHOS {
namespace UDMF {
class RuntimeStore final : public Store {
public:
    explicit RuntimeStore(const std::string &storeId);
    ~RuntimeStore();
    Status Put(const UnifiedData &unifiedData) override;
    Status Get(const std::string &key, UnifiedData &unifiedData) override;
    Status GetSummary(const std::string &key, Summary &summary) override;
    Status Update(const UnifiedData &unifiedData) override;
    Status Delete(const std::string &key) override;
    Status DeleteBatch(const std::vector<std::string> &timeoutKeys) override;
    Status Sync(const std::vector<std::string> &devices) override;
    Status Clear() override;
    void Close() override;
    bool Init() override;
    std::vector<UnifiedData> GetDatas(const std::string &dataPrefix) override;

private:
    static const DistributedKv::AppId APP_ID;
    static const std::string DATA_PREFIX;
    static const std::string BASE_DIR;
    static constexpr std::int32_t SLASH_COUNT_IN_KEY = 4;
    static constexpr std::int32_t MAX_BATCH_SIZE = 128;
    DistributedKv::DistributedKvDataManager dataManager_;
    std::shared_ptr<DistributedKv::SingleKvStore> kvStore_;
    DistributedKv::StoreId storeId_;
    std::vector<DistributedKv::Entry> GetEntries(const std::string &dataPrefix);
    Status PutEntries(const std::vector<DistributedKv::Entry> &entries);
    Status DeleteEntries(const std::vector<DistributedKv::Key> &keys);
};
} // namespace UDMF
} // namespace OHOS
#endif // UDMF_RUNTIMESTORE_H
