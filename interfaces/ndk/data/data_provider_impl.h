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

#ifndef DATA_PROVIDER_IMPL_H
#define DATA_PROVIDER_IMPL_H

#include "entry_getter.h"
#include "udmf.h"

struct OH_UdmfRecordProvider {
    OH_UdmfRecordProvider_GetData callback { nullptr };
    void* context { nullptr };
    UdmfData_Finalize finalize { nullptr };
};

namespace OHOS {
namespace UDMF {
class DataProviderImpl : public EntryGetter {
public:
    void SetInnerProvider(OH_UdmfRecordProvider* provider);
    OH_UdmfRecordProvider* GetInnerProvider();
    ValueType GetValueByType(const std::string &utdId) override;
private:
    OH_UdmfRecordProvider* innerProvider_ {nullptr};
};

} // namespace UDMF
} // namespace OHOS

#endif /* DATA_PROVIDER_IMPL_H */