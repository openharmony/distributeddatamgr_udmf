/*
 * Copyright (c) 2024 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ASYNC_OBTAIN_DATA_H
#define ASYNC_OBTAIN_DATA_H

#include "executor_pool.h"
#include "udmf_service.h"

namespace OHOS {
namespace UDMF {
using ObtainDataCallback = std::function<void(ProgressInfo progress, UnifiedData &unifiedData)>;

class AsyncObtainData {
public:
    AsyncObtainData();
    ~AsyncObtainData() = default;

public:
    Status InitTask(const QueryOption &query, ObtainDataCallback callback);
    Status RunTask();
    void ClearTask();

private:
    void InvokeCallback(UnifiedData &data);
    void ObtainDataTask();
    void ProgressTask();

    void UpdateProcessInfo(AsyncProcessInfo &info);
    uint32_t CalProgress();
    uint32_t CalSyncProgress();
    uint32_t CalPermProgress();

private:
    bool initialized_{ false };
    ExecutorPool executor_;
    ExecutorPool::TaskId progressTaskId_ = ExecutorPool::INVALID_TASK_ID;
    ExecutorPool::TaskId obtainDataTaskId_ = ExecutorPool::INVALID_TASK_ID;
    AsyncTaskStatus taskStatus_{ ASYNC_IDLE };
    QueryOption query_;
    ObtainDataCallback callback_{ nullptr };
    uint32_t lastProgress_{ 0 };
    AsyncProcessInfo processInfo_;
    std::shared_ptr<UdmfService> serviceClient_{ nullptr };
};
} // namespace UDMF
} // namespace OHOS

#endif