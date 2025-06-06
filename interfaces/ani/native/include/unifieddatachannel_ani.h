/*
 * Copyright (c) 2025 Huawei Device Co., Ltd.
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

#ifndef UNIFIEDDATACHANNEL_H
#define UNIFIEDDATACHANNEL_H

#include <ani.h>
#include <memory>
#include <string>

#include "unified_data.h"
#include "unified_record.h"

namespace OHOS {
namespace UDMF {
class UnifiedRecordHolder {
public:
    explicit UnifiedRecordHolder(ani_env *env, const std::string type, ani_object unionValue);

    const std::shared_ptr<UnifiedRecord> Get();

    void Set(ani_ref saveRemote);

    ~UnifiedRecordHolder();

private:
    ani_ref saveRemote_ = nullptr;
    std::shared_ptr<UnifiedRecord> object_;
};

class UnifiedDataHolder {
public:
    explicit UnifiedDataHolder(UnifiedRecordHolder* recordHolder);

    std::shared_ptr<UnifiedData> Get();

    void Set(ani_ref saveRemote);
    ~UnifiedDataHolder();

private:
    ani_ref saveRemote_ = nullptr;
    std::shared_ptr<UnifiedData> object_;
};
} // namespace UDMF
} // namespace OHOS
#endif // UNIFIEDDATACHANNEL_H