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

#include "kv_store_delegate_manager.h"
#include "store.h"

namespace OHOS {
namespace UDMF {
class RuntimeStore final : public Store {
public:
    explicit RuntimeStore(std::string storeId);
    ~RuntimeStore();
    Status Put(const UnifiedData &unifiedData) override;
    Status Get(const std::string &key, UnifiedData &unifiedData) override;
    Status GetSummary(const std::string &key, Summary &summary) override;
    Status Update(const UnifiedData &unifiedData) override;
    Status Delete(const std::string &key) override;
    Status DeleteBatch(std::vector<std::string> timeoutKeys) override;
    Status Sync(const std::vector<std::string> &devices) override;
    Status Clear() override;
    void Close() override;
    bool Init() override;
    std::vector<UnifiedData> GetDatas(const std::string &dataPrefix) override;

private:
    static const std::string APP_ID;
    static const std::string DATA_PREFIX;
    static const std::string BASE_DIR;
    static const std::int32_t SLASH_COUNT_IN_KEY;
    DistributedDB::KvStoreDelegateManager delegateManager_;
    std::shared_ptr<DistributedDB::KvStoreNbDelegate> kvStore_;
    std::string storeId_;
    std::vector<DistributedDB::Entry> GetEntries(const std::string &dataPrefix);
};
} // namespace UDMF
} // namespace OHOS
#endif //UDMF_RUNTIMESTORE_H
