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

#include "udmf_executor.h"

namespace OHOS::UDMF {
static constexpr const char *EXECUTOR_MASK = "TaskExecutor_UDMF";

UdmfExecutor::UdmfExecutor(size_t max, size_t min): executor_(max, min, EXECUTOR_MASK) {};

UdmfTaskId UdmfExecutor::Schedule(UdmfDuration delay, UdmfTask task)
{
    return executor_.Schedule(delay, task);
}

bool UdmfExecutor::Remove(UdmfTaskId taskId, bool wait)
{
    return executor_.Remove(taskId, wait);
}

UdmfTaskId UdmfExecutor::Execute(UdmfTask task)
{
    return executor_.Execute(std::move(task));
}

} // namespace OHOS::UDMF