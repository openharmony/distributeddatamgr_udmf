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
#ifndef UDMF_ENTRY_CONTANINER_H
#define UDMF_ENTRY_CONTANINER_H

#include <map>
#include "unified_meta.h"
#include "visibility.h"

namespace OHOS {
namespace UDMF {
class API_EXPORT EntryContainer {
public:
    EntryContainer() = default;
    ~EntryContainer() = default;
    std::shared_ptr<std::map<std::string, ValueType>> GetEntries() const;
    void SetEntries(std::shared_ptr<std::map<std::string, ValueType>>);
private:
    std::shared_ptr<std::map<std::string, ValueType>> entries_ = std::make_shared<std::map<std::string, ValueType>>();
};
} // namespace UDMF
} // namespace OHOS

#endif // UDMF_ENTRY_CONTANINER_H
