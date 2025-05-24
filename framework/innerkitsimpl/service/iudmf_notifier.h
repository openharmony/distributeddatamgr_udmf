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

#ifndef IUDMF_NOTIFIER_H
#define IUDMF_NOTIFIER_H

#include <iremote_broker.h>
#include "unified_data.h"
#include "unified_types.h"

namespace OHOS {
namespace UDMF {
class IUdmfNotifier : public IRemoteBroker {
public:
    DECLARE_INTERFACE_DESCRIPTOR(u"IUdmfNotifier descriptor");
    virtual void HandleDelayObserver(const std::string &key, const DataLoadInfo &dataLoadInfo) = 0;
};

class IDelayDataCallback : public IRemoteBroker {
public:
    DECLARE_INTERFACE_DESCRIPTOR(u"IDelayDataCallback descriptor");
    virtual void DelayDataCallback(const std::string &key, const UnifiedData &data) = 0;
};

} // namespace UDMF
} // namespace OHOS
#endif // IUDMF_NOTIFIER_H