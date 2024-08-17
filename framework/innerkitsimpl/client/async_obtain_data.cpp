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
#include "async_obtain_data.h"
#define LOG_TAG "AsyncObtainData"
#include <cstdint>
#include <algorithm>
#include "unified_types.h"
#include "logger.h"
#include "udmf_service_client.h"
#include "securec.h"

namespace OHOS {
namespace UDMF {
static constexpr size_t MAX_THREADS = 2;
static constexpr size_t MIN_THREADS = 0;
static constexpr uint32_t MAX_PROGRESS = 100;
static constexpr double MAX_PROGRESS_DOUBLE = 100.0;
static constexpr double SYNC_COEFF = 0.5;
static constexpr double PERM_COEFF = 0.4;

AsyncObtainData::AsyncObtainData() : executor_(MAX_THREADS, MIN_THREADS) {}

Status AsyncObtainData::InitTask(const QueryOption &query, ObtainDataCallback callback)
{
    if (callback == nullptr) {
        LOG_ERROR(UDMF_CLIENT, "callback invalid");
        taskStatus_ = ASYNC_FAILURE;
        return E_INVALID_PARAMETERS;
    }

    serviceClient_ = UdmfServiceClient::GetInstance();
    if (serviceClient_ == nullptr) {
        LOG_ERROR(UDMF_CLIENT, "Service unavailable");
        taskStatus_ = ASYNC_FAILURE;
        return E_IPC;
    }

    initialized_ = true;
    query_ = query;
    callback_ = callback;
    taskStatus_ = ASYNC_RUNNING;
    processInfo_.syncStatus = ASYNC_RUNNING;
    return E_OK;
}

Status AsyncObtainData::RunTask()
{
    LOG_DEBUG(UDMF_CLIENT, "Enter");
    if (serviceClient_ == nullptr) {
        LOG_ERROR(UDMF_CLIENT, "failed! service client is nullptr");
        return E_IPC;
    }
    if (!initialized_) {
        LOG_ERROR(UDMF_CLIENT, "failed! not init");
        return E_ERROR;
    }
    obtainDataTaskId_ = executor_.Execute(std::bind(&AsyncObtainData::ObtainDataTask, this));
    progressTaskId_ = executor_.Execute(std::bind(&AsyncObtainData::ProgressTask, this));

    return E_OK;
}

void AsyncObtainData::ObtainDataTask()
{
    LOG_DEBUG(UDMF_CLIENT, "Enter");
    if ((taskStatus_ == ASYNC_RUNNING) && (processInfo_.syncStatus == ASYNC_RUNNING)) {
        Executor::Duration delay = std::chrono::milliseconds(500);
        obtainDataTaskId_ = executor_.Schedule(delay, std::bind(&AsyncObtainData::ObtainDataTask, this));
        return;
    }

    UnifiedData unifiedData;
    if (taskStatus_ != ASYNC_FAILURE) {
        if (serviceClient_ == nullptr) {
            LOG_ERROR(UDMF_CLIENT, "failed! serviceClient_ is nullptr");
            return;
        }
        int32_t ret = serviceClient_->GetData(query_, unifiedData);
        if (ret != E_OK) {
            LOG_ERROR(UDMF_CLIENT, "failed! ret = %{public}d", ret);
            taskStatus_ = ASYNC_FAILURE;
        } else {
            taskStatus_ = ASYNC_SUCCESS;
        }
    }
    InvokeCallback(unifiedData);
    ClearTask();
}

void AsyncObtainData::ProgressTask()
{
    LOG_DEBUG(UDMF_CLIENT, "Enter");
    if (serviceClient_ == nullptr) {
        LOG_ERROR(UDMF_CLIENT, "failed! serviceClient_ is nullptr");
        return;
    }
    AsyncProcessInfo processInfo;
    int32_t ret = serviceClient_->ObtainAsynProcess(processInfo);
    if (ret != E_OK) {
        LOG_ERROR(UDMF_CLIENT, "failed! ret = %{public}d", ret);
        taskStatus_ = ASYNC_FAILURE;
        return;
    }

    UpdateProcessInfo(processInfo);

    UnifiedData unifiedData;
    InvokeCallback(unifiedData);

    if ((taskStatus_ == ASYNC_RUNNING) &&
        ((processInfo.syncStatus == ASYNC_RUNNING) || (processInfo.permStatus == ASYNC_RUNNING))) {
        Executor::Duration delay = std::chrono::milliseconds(500);
        progressTaskId_ = executor_.Schedule(delay, std::bind(&AsyncObtainData::ProgressTask, this));
    }
}

void AsyncObtainData::InvokeCallback(UnifiedData &data)
{
    ProgressInfo progress{ "", ASYNC_IDLE, 0 };
    progress.status = taskStatus_;
    progress.srcDevName = processInfo_.srcDevName;

    progress.progress = CalProgress();
    if (progress.progress <= lastProgress_) {
        progress.progress = lastProgress_;
    } else {
        lastProgress_ = progress.progress;
    }
    if (callback_ == nullptr) {
        LOG_ERROR(UDMF_CLIENT, "failed! callback_ is nullptr");
        return;
    }
    callback_(progress, data);
}

void AsyncObtainData::UpdateProcessInfo(AsyncProcessInfo &info)
{
    processInfo_.syncStatus = info.syncStatus;
    processInfo_.permStatus = info.permStatus;
    processInfo_.srcDevName = (info.syncStatus == ASYNC_IDLE ? "Local" : info.srcDevName);
    processInfo_.syncFinished = info.syncFinished;
    processInfo_.syncTotal = info.syncTotal;
    processInfo_.syncId = info.syncId;
    processInfo_.permFnished = info.permFnished;
    processInfo_.permTotal = info.permTotal;

    if (processInfo_.syncStatus == ASYNC_FAILURE || processInfo_.permStatus == ASYNC_FAILURE) {
        taskStatus_ = ASYNC_FAILURE;
    }
}

void AsyncObtainData::ClearTask()
{
    initialized_ = false;
    taskStatus_ = ASYNC_IDLE;
    lastProgress_ = 0;
    progressTaskId_ = ExecutorPool::INVALID_TASK_ID;
    obtainDataTaskId_ = ExecutorPool::INVALID_TASK_ID;
    (void)memset_s(&processInfo_, sizeof(processInfo_), 0, sizeof(processInfo_));

    serviceClient_ = UdmfServiceClient::GetInstance();
    if (serviceClient_ == nullptr) {
        return;
    }
    auto ret = serviceClient_->ClearAsynProcess();
    if (ret != E_OK) {
        LOG_ERROR(UDMF_CLIENT, "failed! ret = %{public}d", ret);
    }
    serviceClient_ = nullptr;
}

uint32_t AsyncObtainData::CalProgress()
{
    if (taskStatus_ == ASYNC_SUCCESS) {
        return MAX_PROGRESS;
    }
    if ((taskStatus_ == ASYNC_FAILURE) || (processInfo_.syncStatus == ASYNC_FAILURE) ||
        processInfo_.permStatus == ASYNC_FAILURE) {
        return lastProgress_;
    }

    uint32_t syncProgress = CalSyncProgress();
    uint32_t permProgress = CalPermProgress();
    double totalProgress = syncProgress * SYNC_COEFF + permProgress * PERM_COEFF;
    return static_cast<uint32_t>(totalProgress);
}

uint32_t AsyncObtainData::CalSyncProgress()
{
    if (processInfo_.syncStatus == ASYNC_SUCCESS || processInfo_.syncStatus == ASYNC_IDLE) {
        return MAX_PROGRESS;
    }
    if (processInfo_.syncTotal == 0) {
        return 0;
    }
    return std::min(MAX_PROGRESS,
        static_cast<uint32_t>(processInfo_.syncFinished * MAX_PROGRESS_DOUBLE / processInfo_.syncTotal));
}

uint32_t AsyncObtainData::CalPermProgress()
{
    if (processInfo_.permStatus == ASYNC_SUCCESS) {
        return MAX_PROGRESS;
    }
    if (processInfo_.permTotal == 0) {
        return 0;
    }
    return std::min(MAX_PROGRESS,
        static_cast<uint32_t>(processInfo_.permFnished * MAX_PROGRESS_DOUBLE / processInfo_.permTotal));
}
} // namespace UDMF
} // namespace OHOS