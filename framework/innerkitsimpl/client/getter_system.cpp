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

#include "getter_system.h"

namespace OHOS {
namespace UDMF {
GetterSystem &GetterSystem::GetInstance()
{
    static GetterSystem system;
    return system;
}

void GetterSystem::RegisterCreator(const std::string &name, Creator creator)
{
    creators_.InsertOrAssign(name, std::move(creator));
}

GetterSystem::Getter GetterSystem::GetGetter(const std::string &name)
{
    auto [flag, creator] = creators_.Find(name);
    if (!flag) {
        return nullptr;
    }
    return creator();
}

GetterSystem::GeneralGetter::~GeneralGetter()
{
}

ValueType GetterSystem::GeneralGetter::GetValueByType(uint32_t dataId, uint32_t recordId, const std::string &utdId)
{
    return ValueType();
}
} // namespace UDMF
} // namespace OHOS