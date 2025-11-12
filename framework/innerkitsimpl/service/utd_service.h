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

#ifndef UTD_SERVICE_H
#define UTD_SERVICE_H

#include <string>
#include <vector>
#include "error_code.h"
#include "iremote_broker.h"
#include "type_descriptor.h"

namespace OHOS {
namespace UDMF {

class UtdService {
public:
    DECLARE_INTERFACE_DESCRIPTOR(u"OHOS.UDMF.UtdService");
    virtual ~UtdService() = default;
    virtual int32_t RegServiceNotifier(sptr<IRemoteObject> iUtdNotifier) = 0;
    virtual int32_t RegisterTypeDescriptors(const std::vector<TypeDescriptorCfg> &descriptors) = 0;
    virtual int32_t UnregisterTypeDescriptors(const std::vector<std::string> &typeIds) = 0;
};
} // namespace UDMF
} // namespace OHOS
#endif // UTD_SERVICE_H
