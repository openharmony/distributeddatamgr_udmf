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

#ifndef UDMF_EXECUTOR_H
#define UDMF_EXECUTOR_H

#include "executor.h"
#include "executor_pool.h"

namespace OHOS::UDMF {
using UdmfTaskId = Executor::TaskId;
using UdmfTask = std::function<void()>;
using UdmfDuration = std::chrono::steady_clock::duration;

class UdmfExecutor {
public:
    UdmfExecutor(size_t max, size_t min);
    ~UdmfExecutor() = default;
    UdmfTaskId Schedule(UdmfDuration delay, UdmfTask task);
    bool Remove(UdmfTaskId taskId, bool wait = false);
    UdmfTaskId Execute(UdmfTask task);
private:
    ExecutorPool executor_;
};

} // namespace OHOS::UDMF
#endif // UDMF_EXECUTOR_H