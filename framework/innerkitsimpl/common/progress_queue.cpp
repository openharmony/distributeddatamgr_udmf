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
#include "progress_queue.h"

namespace OHOS::UDMF {

void ProgressQueue::PushBack(ProgressInfo &progress)
{
    std::lock_guard<std::mutex> lock(mutex_);
    queue_.push(progress);
}

std::pair<bool, std::shared_ptr<ProgressInfo>> ProgressQueue::Poll()
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (queue_.empty()) {
        return {false, nullptr};
    }
    auto progressInfo = std::make_shared<ProgressInfo>(queue_.front());
    queue_.pop();
    return {true, progressInfo};
}

bool ProgressQueue::IsCancel() const
{
    std::lock_guard<std::mutex> lock(mutex_);
    return cancelFlag_;
}

void ProgressQueue::Cancel()
{
    std::lock_guard<std::mutex> lock(mutex_);
    cancelFlag_ = true;
}

void ProgressQueue::SetClearable(const bool clearableFlag)
{
    std::lock_guard<std::mutex> lock(mutex_);
    clearableFlag_ = clearableFlag;
}

bool ProgressQueue::Clear()
{
    std::lock_guard<std::mutex> lock(mutex_);
    auto oldClearableFlag = clearableFlag_;
    clearableFlag_ = true;
    return oldClearableFlag;
}

} // namespace OHOS::UDMF