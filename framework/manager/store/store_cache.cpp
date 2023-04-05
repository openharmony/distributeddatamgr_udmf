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

#include "store_cache.h"

#include "logger.h"
#include "runtime_store.h"
#include "unified_meta.h"

namespace OHOS {
namespace UDMF {
std::shared_ptr<Store> StoreCache::GetStore(std::string intention)
{
    std::shared_ptr<Store> store;
    stores_.Compute(intention, [&store](const auto &intention, std::shared_ptr<Store> &storePtr) -> bool {
        if (storePtr != nullptr) {
            store = storePtr;
            return true;
        }

        if (intention == UD_INTENTION_MAP.at(UD_INTENTION_DRAG)) {
            storePtr = std::make_shared<RuntimeStore>(intention);
            if (!storePtr->Init()) {
                LOG_ERROR(UDMF_SERVICE, "Init runtime store failed.");
                return false;
            }
            store = storePtr;
            return true;
        }
        return false;
    });
    return store;
}
} // namespace UDMF
} // namespace OHOS
