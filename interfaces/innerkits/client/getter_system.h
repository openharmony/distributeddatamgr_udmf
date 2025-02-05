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

#ifndef UDMF_GETTER_SYSTEM_H
#define UDMF_GETTER_SYSTEM_H

#include "concurrent_map.h"
#include "unified_meta.h"
#include "visibility.h"

namespace OHOS {
namespace UDMF {
class GetterSystem {
public:
    class GeneralGetter {
    public:
        virtual ~GeneralGetter();
        virtual ValueType GetValueByType(uint32_t dataId, uint32_t recordId, const std::string &utdId);
    };
    using Creator = std::function<std::shared_ptr<GeneralGetter>()>;
    using Getter = std::shared_ptr<GeneralGetter>;
    static GetterSystem &GetInstance();
    void RegisterCreator(const std::string& name, Creator creator);
    Getter GetGetter(const std::string& name);
private:
    GetterSystem() = default;
    GetterSystem(const GetterSystem &) = delete;
    GetterSystem(GetterSystem &&) noexcept = delete;
    GetterSystem &operator=(const GetterSystem &) = delete;
    GetterSystem &operator=(GetterSystem &&) = delete;
    ConcurrentMap<std::string, Creator> creators_;
};
} // namespace UDMF
} // namespace OHOS
#endif // UDMF_GETTER_SYSTEM_H